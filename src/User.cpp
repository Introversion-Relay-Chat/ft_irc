#include "IRC.hpp"

ft::User::User(int user_socket) {
	_user_socket = user_socket;
	_nickname = "NONAME";
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