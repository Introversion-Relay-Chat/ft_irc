#include "User.hpp"

User::User(int user_socket, std::string hostname, Server *server) {
	_status = PASSWORD;
	_user_socket = user_socket;
	_nickname = "*";
	_server = server;
	_hostname = hostname;
}

User::~User() {
	close(_user_socket);
}

int User::getStatus(void) {
	return _status;
}

void User::setStatus(int status) {
	_status = status;
}

std::string User::getNickname(void) {
	return _nickname;
}

void User::setNickname(std::string nickname) {
	_nickname = nickname;
}

std::string User::getUsername(void) {
	return _username;
}

void User::setUsername(std::string username) {
	_username = username;
}

Server *User::getServer(void) {
	return _server;
}

std::string	User::getServerPrefix(void) {
	return _server->getServername();
}

std::string	User::getUserPrefix(void) {
	std::string prefix = _nickname;

	if (prefix == "*")
		return std::string("*");
	if (_username.length())
		prefix += "!" + _username;
	if (_hostname.length())
		prefix += "@" + _hostname;
	return prefix;
}

int User::getUserSocket(void) {
	return _user_socket;
}

void User::joinChannel(std::string channel_name){
	_joined.insert(channel_name);
}

void User::leaveChannel(std::string channel_name){
	_joined.erase(channel_name);
}