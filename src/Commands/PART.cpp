#include "../../include/Utils.hpp"

// TODO: server name rule
std::string PART(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	std::vector<std::string>			channels;
	Channel								*channel;

	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 1)
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));

	channels = split(message.middle[0], ",");
	for (unsigned long i=0; i < channels.size(); i++){
		channel = sender->getServer()->getChannelByName(channels[i]);
		// ERR_NOSUCHCHANNEL
		if (!channel) {
			sender->getServer()->sendMsg(join(sender_prefix, "403", target, ERR_NOSUCHCHANNEL(channels[i])), sender);
			continue ;
		}

		// ERR_NOTONCHANNEL
		if (!channel->checkOnChannel(sender)) {
			sender->getServer()->sendMsg(join(sender_prefix, "442", target, ERR_NOTONCHANNEL(channels[i])), sender);
			continue ;
		}

		// leave channel
		channel->removeUser(sender);
		sender->leaveChannel(channels[i]);
		if (channel->getUsers().size() == 0) {
			sender->getServer()->deleteChannel(channels[i]);
		}
		else if (channel->getOperators().size() == 0) {
			channel->addOperator(*(channel->getUsers().begin()));
		}
	}
	return std::string();
}
