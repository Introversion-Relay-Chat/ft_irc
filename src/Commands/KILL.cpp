#include "../Utils.hpp"

std::string KILL(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	std::string							nickname;
	User								*user;

	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 2)
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	
	// ERR_NOPRIVILEGES
	if (!(sender->getMode() & FLAG_USER_O)) {
		return join(sender_prefix, "481", target, ERR_NOPRIVILEGES());
	}

	nickname = message.middle[0];
	user = sender->getServer()->getUserByName(nickname);
	// ERR_NOSUCHNICK
	if (!user) {
		return join(sender_prefix, "401", target, ERR_NOSUCHNICK(nickname));
	}

	// ERR_CANTKILLSERVER
	if (nickname == SERVER_NAME) {
		return join(sender_prefix, "483", target, ERR_CANTKILLSERVER());
	}

	// kill user
	sender->getServer()->killUser(user);

	return std::string();
}
