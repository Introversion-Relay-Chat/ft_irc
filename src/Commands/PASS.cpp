#include "../../include/Utils.hpp"

std::string PASS(const Message &message, User *sender)
{
	std::string sender_prefix = sender->getServerPrefix();
	std::string	target = sender->getNickname();

	if (message.middle.size() < 1) {
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	}
	if (sender->getStatus() != NEED_PASSWORD) {
		return join(sender_prefix, "462", target, ERR_ALREADYREGISTRED());
	}
	if (sender->getServer()->getPassword() == message.middle[0]) {
		sender->setStatus(NEED_NICKNAME);
	}
	return std::string();
}
