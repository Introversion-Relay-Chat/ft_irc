#include "../../include/Utils.hpp"

std::string OPER(const Message &message, User *sender) {
	std::string		sender_prefix;
	std::string		target;
	User			*user;

	sender_prefix = sender->getServerPrefix();
	target = sender->getNickname();
	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 2) {
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	}

    // ERR_NOOPERHOST
	if (sender->getHostname() != ADMIN_HOST) {
		return join(sender_prefix, "491", target, ERR_NOOPERHOST());
	}
	
	// ERR_PASSWDMISMATCH
	if (message.middle[1] != ADMIN_PASSWORD) {
		return join(sender_prefix, "464", target, ERR_PASSWDMISMATCH());
	}

	user = sender->getServer()->getUserByName(message.middle[0]);
	if (user) {
		user->setMode(user->getMode() | FLAG_USER_O);
		sender_prefix = sender->getUserPrefix();
		target = user->getNickname();

		// RPL_YOUREOPER
		return join(sender_prefix, "381", target, RPL_YOUREOPER());
	}
	return std::string();
}
