#include "../../include/Utils.hpp"

std::string TOPIC(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	std::string							channel_name;
	std::string							topic;
	Channel								*channel;

	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 1) {
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	}

	// ERR_NOSUCHCHANNEL
	channel_name = message.middle[0];
	channel = sender->getServer()->getChannelByName(channel_name);
	if (!channel) {
		return join(sender_prefix, "403", target, ERR_NOSUCHCHANNEL(channel_name));
	}

	// ERR_NOTONCHANNEL
	if (!channel->checkOnChannel(sender)) {
		return join(sender_prefix, "442", target, ERR_NOTONCHANNEL(channel_name));
	}
	if (message.trailing.length() > 0) {
		topic = message.trailing;
		// ERR_CHANOPRIVSNEEDED
		if (channel->getMode() & FLAG_CHANNEL_T && !channel->checkPrivilege(sender)) {
			return join(sender_prefix, "482", target, ERR_CHANOPRIVSNEEDED(channel_name));
		}
		if (topic[0] == ':') {
			topic.erase(0, 1);
		}
		channel->setTopic(topic);
		if (topic.length() > 0) {
			sender->getServer()->sendMsg(join(sender_prefix, "332", target, RPL_TOPIC(channel_name, topic)), sender);
		}
		else {
			sender->getServer()->sendMsg(join(sender_prefix, "331", target, RPL_NOTOPIC(channel_name)), sender);
		}
	}
	else {
		topic = channel->getTopic();
		// RPL_TOPIC
		if (topic.length() > 0) {
			sender->getServer()->sendMsg(join(sender_prefix, "332", target, RPL_TOPIC(channel_name, topic)), sender);
		}
		else {
			sender->getServer()->sendMsg(join(sender_prefix, "331", target, RPL_NOTOPIC(channel_name)), sender);
		}
	}
	return std::string();
}
