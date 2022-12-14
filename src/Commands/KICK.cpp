#include "../../include/Utils.hpp"

std::string KICK(const Message &message, User *sender) {
	std::string							sender_prefix;
	std::string							target;
	User								*user;
	Channel								*channel;
	std::string							kick_message;

	sender_prefix = sender->getServerPrefix();
	target = sender->getNickname();
	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 2) {
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	}

	user = sender->getServer()->getUserByName(message.middle[1]);
	channel = sender->getServer()->getChannelByName(message.middle[0]);

	// ERR_NOSUCHCHANNEL
	if (!channel) {
		return join(sender_prefix, "403", target, ERR_NOSUCHCHANNEL(message.middle[0]));
	}

	// ERR_NOSUCHNICK
	if (!user) {
		return join(sender_prefix, "401", target, ERR_NOSUCHNICK(message.middle[1]));
	}

	// ERR_NOTONCHANNEL
	if (!channel->checkOnChannel(sender)) {
		return join(sender_prefix, "442", target, ERR_NOTONCHANNEL(message.middle[1]));
	}

	// ERR_CHANOPRIVSNEEDED
	if (!channel->checkPrivilege(sender)) {
		return join(sender_prefix, "482", target, ERR_CHANOPRIVSNEEDED(message.middle[0]));
	}

	channel->kickUser(user);

	sender_prefix = sender->getUserPrefix();
	target = user->getNickname();
	kick_message = "kicked from channel: " + channel->getChannelname();
	if (message.trailing != "") {
		kick_message += " reason: " + message.trailing;
	}
	// RPL_AWAY
	sender->getServer()->sendMsg(join(sender_prefix, "301", target, RPL_AWAY(message.middle[1], kick_message)), user);

	return std::string();
}
