#include "../include/Server.hpp"

Server::Server(std::string port, std::string password) {
	_password = password;
	_port = atoi(port.c_str());
	_executor[std::string("PASS")] = PASS;
	_executor[std::string("NICK")] = NICK;
	_executor[std::string("USER")] = USER;
	_executor[std::string("OPER")] = OPER;
	_executor[std::string("QUIT")] = QUIT;
	_executor[std::string("JOIN")] = JOIN;
	_executor[std::string("PART")] = PART;
	_executor[std::string("MODE")] = MODE;
	_executor[std::string("TOPIC")] = TOPIC;
	_executor[std::string("NAMES")] = NAMES;
	_executor[std::string("LIST")] = LIST;
	_executor[std::string("INVITE")] = INVITE;
	_executor[std::string("KICK")] = KICK;
	_executor[std::string("VERSION")] = VERSION;
	_executor[std::string("TIME")] = TIME;
	_executor[std::string("ADMIN")] = ADMIN;
	_executor[std::string("INFO")] = INFO;
	_executor[std::string("KILL")] = KILL;
	_executor[std::string("PRIVMSG")] = PRIVMSG;
	_executor[std::string("NOTICE")] = NOTICE;
	_executor[std::string("PING")] = PING;
	_executor[std::string("PONG")] = PONG;
	_servername = SERVER_NAME;
	_server_version = SERVER_VERSION;
	_start_time = currTime();
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

std::map<std::string, Channel *> Server::getChannels(void) {
	return _channels;
}

std::map<int, User *> Server::getUsers(void) {
	return _users;
}

User *Server::getUserByName(std::string nickname) {
	for (std::map<int, User *>::iterator it=_users.begin(); it != _users.end() ; it++) {
		if ((*it).second->getNickname() == nickname) {
			return (*it).second;
		}
	}
	return NULL;
}

Channel *Server::getChannelByName(std::string channel_name) {
	return _channels[channel_name];
}

std::vector<std::string> Server::getChannelNames(void) {
	std::vector<std::string> channels;
	for (std::map<std::string, Channel *>::iterator c = _channels.begin(); c != _channels.end(); c++) {
		channels.push_back((*c).first);
	}
	return channels;
}

std::string Server::getServerVersion(void) {
	return _server_version;
}

std::string Server::getStartTime(void) {
	return _start_time;
}

std::string Server::currTime(void) {
	time_t curr_time;
	struct tm *local_time;
	std::string local_time_str;

	time(&curr_time);
	local_time = localtime(&curr_time);
	local_time_str = asctime(local_time);
	local_time_str.erase(--local_time_str.end());
	return local_time_str;
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
	if (poll(&_sockets[0], _sockets.size(), 1000) == -1)
		return;

	if (_sockets[0].revents == POLLIN) {
		acceptNewUser();
	}
	else {
		for (std::vector<pollfd>::iterator socket = _sockets.begin(); socket != _sockets.end(); socket++) {
			if ((*socket).revents == POLLIN) {
				receiveMsg((*socket).fd);
			}
		}
	}

	// check user and send ping + check user received ping
	for (std::map<int, User *>::iterator it = _users.begin();it != _users.end();it++) {
		User *user = (*it).second;
		time_t now = time(0);

		if (user->getStatus() == REGISTERED) {
			if (now - user->getLastCmdTime() > PING_CHECK) {
				_executor["PING"](Message(), user);
			}
		}
		else if (user->getStatus() == NEED_PONG) {
			if (now - user->getPingTime() > TIMEOUT) {
				_quitters.push_back(user->getUserSocket());
			}
		}
	}

	// delete quitters
	while (!_quitters.empty()) {
		deleteUser(_quitters.back());
		_quitters.pop_back();
	}
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
	for (size_t i = 0; i < command.length(); i++) {
		command[i] = std::toupper(command[i]);
	}
	parsed_message.command = command;
	parsed_message.middle = middle;
	parsed_message.trailing = trailing;
	return parsed_message;
}

void Server::runCommand(const Message &message, User *user) {
	std::string	reply;

	if (DEBUG) {
		std::cout << message << std::endl;
	}
	if ((user->getStatus() == NEED_PASSWORD && message.command != "PASS")
			|| (user->getStatus() == NEED_NICKNAME && message.command != "PASS" && message.command != "NICK")
			|| (user->getStatus() == NEED_USERREGISTER && message.command != "PASS" && message.command != "NICK" && message.command != "USER"))
			{
				sendMsg(join(user->getServer()->getServername(), "451", user->getNickname(), ERR_NOTREGISTERED()), user);
				return ;
		}
	if (_executor.find(message.command) != _executor.end()) {
		sendMsg(_executor[message.command](message, user), user);
	}
	else {
		sendMsg(join(user->getServer()->getServername(), "421", user->getNickname(), ERR_UNKNOWNCOMMAND(message.command)), user);
	}
	if (user->getStatus() >= REGISTERED) {
		user->setLastCmdTime();
		user->setStatus(REGISTERED);
	}
}

void Server::sendMsg(const std::string &message, User *user) {
	std::string reply;

	if (message.length()) {
		reply = message + std::string(MESSAGE_END);
		if (send(user->getUserSocket(), reply.c_str(), reply.length(), 0) == -1) {
			error("send", false);
		}
	}
}

void Server::createChannel(std::string channel_name, User *user) {
	Channel *new_channel = new Channel(channel_name, user);

	_channels[channel_name] = new_channel;
}

void Server::deleteChannel(std::string channel_name) {
	delete getChannelByName(channel_name);
	_channels.erase(channel_name);
}

void Server::deleteUser(int user_socket) {
	for (std::vector<pollfd>::iterator it = _sockets.begin(); it != _sockets.end(); it++) {
		if ((*it).fd == user_socket) {
			_sockets.erase(it);
			break;
		}
	}
	delete _users[user_socket];
	_users.erase(user_socket);
}

void Server::killUser(User *user) {
	Message					part_message;
	std::set<std::string>	channels;

	part_message.command = "PART";
	part_message.trailing = "";
	channels = user->getJoinedChannels();
	for (std::set<std::string>::iterator it=channels.begin(); it!=channels.end(); it++) {
		part_message.middle.push_back(*it);
		_executor["PART"](part_message, user);
		part_message.middle.pop_back();
	}
	_quitters.push_back(user->getUserSocket());
}