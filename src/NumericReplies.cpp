#include "utils.hpp"

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

std::string NumericReply(std::string sender_prefix, std::string code, std::string target, const Message &message) {
	switch (atoi(code.c_str())) {
		case 421:
			return join(sender_prefix, code, target, ERR_UNKNOWNCOMMAND(message.command));
		case 461:
			return join(sender_prefix, code, target, ERR_NEEDMOREPARAMS(message.command));
		case 462:
			return join(sender_prefix, code, target, ERR_ALREADYREGISTRED());
		default:
			return std::string();
	}
}