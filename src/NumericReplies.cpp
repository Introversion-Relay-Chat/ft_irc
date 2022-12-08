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

std::string ft::NumericReply(std::string sender_prefix, std::string code, std::string target, const ft::Message &message) {
	switch (atoi(code.c_str())) {
		case 421:
			return ft::join(sender_prefix, code, target, ft::ERR_UNKNOWNCOMMAND(message.command));
		case 461:
			return ft::join(sender_prefix, code, target, ft::ERR_NEEDMOREPARAMS(message.command));
		case 462:
			return ft::join(sender_prefix, code, target, ft::ERR_ALREADYREGISTRED());
		default:
			return std::string();
	}
}