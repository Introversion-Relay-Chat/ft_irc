#include "IRC.hpp"

ft::User::User(int user_socket, std::string hostname, ft::Server *server) {
	_status = PASSWORD;
	_user_socket = user_socket;
	_nickname = "*";
	_server = server;
	_hostname = hostname;
}

ft::User::~User() {
	close(_user_socket);
}

ft::UserStatus ft::User::getStatus(void) {
	return _status;
}

void ft::User::setStatus(UserStatus status) {
	_status = status;
}

std::string ft::User::getNickname(void) {
	return _nickname;
}

void ft::User::setNickname(std::string nickname) {
	_nickname = nickname;
}

std::string ft::User::getUsername(void) {
	return _username;
}

void ft::User::setUsername(std::string username) {
	_username = username;
}

ft::Server *ft::User::getServer(void) {
	return _server;
}

std::string	ft::User::getServerPrefix(void) {
	return _server->_servername;
}

std::string	ft::User::getUserPrefix(void) {
	std::string prefix = _nickname;

	if (prefix == "*")
		return std::string("*");
	if (_username.length())
		prefix += "!" + _username;
	if (_hostname.length())
		prefix += "@" + _hostname;
	return prefix;
}