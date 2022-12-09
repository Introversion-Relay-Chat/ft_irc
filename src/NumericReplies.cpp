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

std::string NumericReply(std::string sender_prefix, std::string code, std::string target, std::string message) {
	switch (atoi(code.c_str())) {
		case 421:
			return join(sender_prefix, code, target, message);
		case 461:
			return join(sender_prefix, code, target, message);
		case 462:
			return join(sender_prefix, code, target, message);
		default:
			return std::string();
	}
}