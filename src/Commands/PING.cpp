#include "../../include/Utils.hpp"

std::string PING(const Message &message, User *sender) {
	(void) message;
	std::string	sender_prefix = sender->getServerPrefix();

	sender->setMode(sender->getMode() | FLAG_USER_P);
	sender->setPingTime();
	sender->getServer()->sendMsg(join(sender_prefix, "PING", sender->getNickname(), ""), sender);
	
	return std::string();
}