#include "Utils.hpp"

// 421
std::string ERR_UNKNOWNCOMMAND(const std::string &command) {
	return command + " :Unknown command" ;
}

// 461
std::string ERR_NEEDMOREPARAMS(const std::string &command) {
	return command + " :Not enough parameters" ;
}

// 462
std::string ERR_ALREADYREGISTRED(void) {
	return ":You may not reregister" ;
}

std::string ERR_NONICKNAMEGIVEN(void) {
	return ":No nickname given" ;
}

std::string ERR_ERRONEUSNICKNAME(const std::string &nickname) {
	return nickname + " :Erroneus nickname" ;
}

std::string ERR_NICKNAMEINUSE(const std::string &nickname) {
	return nickname + " :Nickname is already in use" ;
}
