#include "../Utils.hpp"

std::string TOPIC(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	std::string							channel_name;
	std::string							topic;
	Channel								*channel;
	std::set<int>						channel_users;

	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 1) {
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	}

	channel_name = message.middle[0];
	channel = sender->getServer()->getChannels()[channel_name];
	// ERR_NOSUCHCHANNEL
	if (!channel) {
		return join(sender_prefix, "403", target, ERR_NOSUCHCHANNEL(channel_name));
	}
	channel_users = channel->getUsers();
	// ERR_NOTONCHANNEL
	if (channel_users.find(sender->getUserSocket()) == channel_users.end()) {
		return join(sender_prefix, "442", target, ERR_NOTONCHANNEL(channel_name));
	}

	// change topic
	if (message.middle.size() >= 2) {
		topic = message.middle[1];
		// ERR_CHANOPRIVSNEEDED
		if (sender->getUserSocket() != channel->getOperator()) {
			return join(sender_prefix, "482", target, ERR_CHANOPRIVSNEEDED(channel_name));
		}
		channel->setTopic(topic);
	}
	// return topic
	else {
		topic = channel->getTopic();
		// RPL_TOPIC
		if (topic.length()) {
			sender->getServer()->sendMsg(join(sender_prefix, "332", target, RPL_TOPIC(channel_name, topic)), sender);
		}
		else {
			sender->getServer()->sendMsg(join(sender_prefix, "331", target, RPL_NOTOPIC(channel_name)), sender);
		}
	}
	return std::string();
}
