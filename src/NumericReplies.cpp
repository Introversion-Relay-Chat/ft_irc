#include "IRC.hpp"

// 421     
std::string ft::ERR_UNKNOWNCOMMAND(const std::string &command) {
	return command + " :Unknown command" ;
}

// 461
std::string ft::ERR_NEEDMOREPARAMS(const std::string &command) {
	return command + " :Not enough parameters" ;
}

// 462
std::string ft::ERR_ALREADYREGISTRED(void) {
	return ":You may not reregister" ;
}

std::string ft::NumericReply(std::string code, const ft::Message &message, ft::User *user) {
	switch (atoi(code.c_str())) {
		case 421:
			return ":" + user->getNickname() + " 421 " + ft::ERR_UNKNOWNCOMMAND(message.command);
		case 461:
			return ":" + user->getNickname() + " 461 " + ft::ERR_NEEDMOREPARAMS(message.command);
		case 462:
			return ":" + user->getNickname() + " 462 " + ft::ERR_ALREADYREGISTRED();
		default:
			return std::string();
	}
}