#include "../../include/Utils.hpp"

std::string INVITE(const Message &message, User *sender) {
	std::string							sender_prefix;
	std::string							target;
	User								*user;
	Channel								*channel;
	std::string							invite_message;

	sender_prefix = sender->getServerPrefix();
	target = sender->getNickname();
	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 2)
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));

	user = sender->getServer()->getUserByName(message.middle[0]);
	channel = sender->getServer()->getChannelByName(message.middle[1]);
    // ERR_NOSUCHNICK
	if (!user) {
		return join(sender_prefix, "401", target, ERR_NOSUCHNICK(message.middle[0]));
	}
	if (!channel) {
		return join(sender_prefix, "401", target, ERR_NOSUCHNICK(message.middle[1]));
	}

	// ERR_NOTONCHANNEL
	if (!channel->checkOnChannel(sender)) {
		return join(sender_prefix, "442", target, ERR_NOTONCHANNEL(message.middle[1]));
	}

	// ERR_CHANOPRIVSNEEDED
	if (channel->getMode() & FLAG_CHANNEL_I && !channel->checkPrivilege(sender)) {
		return join(sender_prefix, "482", target, ERR_CHANOPRIVSNEEDED(message.middle[1]));
	}

	// ERR_USERONCHANNEL
	if (channel->checkOnChannel(user)) {
		return join(sender_prefix, "443", target, ERR_USERONCHANNEL(message.middle[0], message.middle[1]));
	}

	// invite
	channel->inviteUser(user);

	// RPL_INVITING
	sender->getServer()->sendMsg(join(sender_prefix, "341", target, RPL_INVITING(message.middle[1], message.middle[0])), sender);

	sender_prefix = sender->getUserPrefix();
	target = user->getNickname();
	invite_message = "invited from channel: " + channel->getChannelname();
	// RPL_AWAY
	sender->getServer()->sendMsg(join(sender_prefix, "301", target, RPL_AWAY(message.middle[0], invite_message)), user);

	return std::string();
}
