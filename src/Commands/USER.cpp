#include "../../include/Utils.hpp"

std::string USER(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();
	if (message.middle.size() < 3 || message.trailing.length() == 0) {
		return join(sender_prefix, "461", sender->getNickname(), ERR_NEEDMOREPARAMS(message.command));
	}

  std::string username = message.middle[0];
	std::string realname = message.trailing;

	if (sender->getStatus() == REGISTERED) {
    return join(sender_prefix, "462", sender->getNickname(), ERR_ALREADYREGISTRED());
	}

	sender->setUsername(username);
	sender->setRealname(realname);
	if (sender->getStatus() == NEED_USERREGISTER) {
		sender->setStatus(REGISTERED);
	}
	return join(sender_prefix, "001", sender->getNickname(), RPL_WELCOME());
}
