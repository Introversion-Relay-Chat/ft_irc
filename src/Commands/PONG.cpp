#include "../../include/Utils.hpp"

std::string PONG(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();
	std::string	target = sender->getNickname();

	if (message.middle.size() < 1) {
		return join(sender_prefix, "409", target, ERR_NOORIGIN());
	}
	if (message.middle[0] != sender->getNickname()) {
		return join(sender_prefix, "401", target, ERR_NOSUCHNICK(sender->getNickname()));
	}

	sender->setMode(sender->getMode() & ~FLAG_USER_P);
	
	return std::string();
}