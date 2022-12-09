#include "Server.hpp"

Server::Server(std::string port, std::string password) {
	_password = password;
	_port = atoi(port.c_str());
	_executor[std::string("PASS")] = PASS;
	_executor[std::string("NICK")] = NICK;
	_executor[std::string("USER")] = USER;
	_servername = SERVER_NAME;
}

Server::~Server() {
	_users.clear();
	_channels.clear();
}

std::string Server::getPassword(void) {
	return _password;
}

std::string Server::getServername(void) {
	return _servername;
}

std::map<int, User *> Server::getUsers(void) {
	return _users;
}

void Server::run(bool &stop) {
	int enable = 1;
	if ((_server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		error("socket", true);
	if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR , &enable, sizeof(enable)))
		error("setsockopt", true);
	if (fcntl(_server_socket, F_SETFL, O_NONBLOCK) < 0)
		error("fcntl", true);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(_port);

	if (bind(_server_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
		error("bind", true);
	if (listen(_server_socket, address.sin_port) < 0)
		error("listen", true);

	_sockets.push_back(pollfd());
	_sockets.back().fd = _server_socket;
	_sockets.back().events = POLLIN;

	while (!stop)
		loop();
}

void Server::loop(void) {
	if (poll(&_sockets[0], _sockets.size(), 3000) == -1)
		return;

	if (_sockets[0].revents == POLLIN)
		acceptNewUser();
	else
		for (std::vector<pollfd>::iterator socket = _sockets.begin(); socket != _sockets.end(); socket++)
			if ((*socket).revents == POLLIN)
				receiveMsg((*socket).fd);

}

void Server::acceptNewUser(void) {
	int user_socket;

	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	user_socket = accept(_server_socket, (struct sockaddr *)&address, &addrlen);
	if (user_socket == -1)
		return ;

	_users[user_socket] = new User(user_socket, std::string(inet_ntoa(address.sin_addr)), this);

	_sockets.push_back(pollfd());
	_sockets.back().fd = user_socket;
	_sockets.back().events = POLLIN;
}

void Server::receiveMsg(int user_socket) {
	char 						buffer[BUFFER_SIZE];
	ssize_t						size;
	std::vector<std::string>	messages;
	Message					parsed_message;

	if ((size = recv(user_socket, &buffer, BUFFER_SIZE, 0)) <= 0)
		return;
	buffer[size] = '\0';
	messages = split(std::string(buffer), MESSAGE_END);
	for (std::vector<std::string>::iterator msg = messages.begin(); msg != messages.end(); msg++) {
		parsed_message = parseMsg(*msg);
		runCommand(parsed_message, _users[user_socket]);
	}
}

Message Server::parseMsg(std::string message) {
	std::string					command;
	std::vector<std::string>	middle;
	std::string					trailing;
	std::string					delimiter(":");
	size_t						pos;
	Message						parsed_message;

	if ((pos = message.find(delimiter)) != std::string::npos) {
		std::string tmp = message.substr(0, pos);
		message.erase(0, pos + delimiter.length());
		trailing = message;
		message = tmp;
	}

	middle = split(message, " ");
	command = *(middle.begin());
	middle.erase(middle.begin());
	for (size_t i = 0; i < command.length(); i++)
		command[i] = std::toupper(command[i]);
	parsed_message.command = command;
	parsed_message.middle = middle;
	parsed_message.trailing = trailing;
	return parsed_message;
}

void Server::runCommand(const Message &message, User *user) {
	std::string	reply;

	if (_executor.find(message.command) != _executor.end())
		reply = _executor[message.command](message, user) + std::string(MESSAGE_END);
	else
		reply = join(user->getServer()->getServername(), "421", user->getNickname(), ERR_UNKNOWNCOMMAND(message.command)) + std::string(MESSAGE_END);
	if (user->getStatus() == REGISTERED) {
		std::cout << user->getNickname() << " registered!" << std::endl;
	}
	if (reply.length())
		if (send(user->getUserSocket(), reply.c_str(), reply.length(), 0) == -1)
			error("send", false);
}
