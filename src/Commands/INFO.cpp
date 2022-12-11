#include "../Utils.hpp"

std::string INFO(const Message &message, User *sender) {
	(void) message;
	std::string	sender_prefix = sender->getServerPrefix();
	std::string target = sender->getNickname();
	std::vector<std::string> info;
	
	info.push_back("This is IRC server from Introversion-Relay-Chat");
	info.push_back("Version is " + sender->getServer()->getServerVersion() + ".0");
	info.push_back("Server started at " + sender->getServer()->getStartTime());

	// RPL_INFO 371
	for (std::vector<std::string>::iterator it = info.begin();it != info.end();it++) {
		sender->getServer()->sendMsg(join(sender_prefix, "371", target, RPL_INFO(*it)), sender);
	}
	// RPL_ENDOFINFO 374
	sender->getServer()->sendMsg(join(sender_prefix, "374", target, RPL_ENDOFINFO()), sender);
	return std::string();
}