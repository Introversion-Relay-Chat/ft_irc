#include "../../include/Utils.hpp"

std::string JOIN(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	std::vector<std::string>			channels;
	std::vector<std::string>			keys;
	Channel								*channel;
	std::string							topic;
	std::string							userlist;

	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 1) {
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	}

	channels = split(message.middle[0], ",");
	if (message.middle.size() >= 2) {
		keys = split(message.middle[1], ",");
	}
	while (keys.size() < channels.size()) {
		keys.push_back(std::string());
	}

	for (unsigned long i=0; i < channels.size(); i++){
		if (channels[i][0] != '#') {
			continue ;
		}
		channel = sender->getServer()->getChannelByName(channels[i]);
		if (!channel) {
			// ERR_TOOMANYCHANNELS
			if (static_cast<int>(sender->getServer()->getChannels().size()) >= MAX_CHANNEL) {
				return join(sender_prefix, "405", target, ERR_TOOMANYCHANNELS(channels[i]));
			}
			else {
				sender->getServer()->createChannel(channels[i], sender);
				channel = sender->getServer()->getChannelByName(channels[i]);
			}
		}
		// ERR_CHANNELISFULL
		if (static_cast<int>(channel->getUsers().size()) >= channel->getLimit()) {
			sender->getServer()->sendMsg(join(sender_prefix, "471", target, ERR_CHANNELISFULL(channels[i])), sender);
			continue ;
		}

		// ERR_INVITEONLYCHAN
		if (channel->getMode() & FLAG_CHANNEL_I) {
			if (!channel->checkInvited(sender)) {
				sender->getServer()->sendMsg(join(sender_prefix, "473", target, ERR_INVITEONLYCHAN(channels[i])), sender);
				continue ;
			}
		}

		// ERR_BANNEDFROMCHAN
		std::set<std::string> banlist = channel->getBanList();
		if (channel->getMode() & FLAG_CHANNEL_B) {
			if (checkMask(banlist, sender->getUserPrefix())) {
				sender->getServer()->sendMsg(join(sender_prefix, "474", target, ERR_BANNEDFROMCHAN(channels[i])), sender);
				continue ;
			}
		}

		// ERR_BADCHANNELKEY
		if (channel->getMode() & FLAG_CHANNEL_K) {
			if (keys[i] != channel->getKey()) {
				sender->getServer()->sendMsg(join(sender_prefix, "475", target, ERR_BADCHANNELKEY(channels[i])), sender);
				continue ;
			}
		}
		channel->addUser(sender);
		sender->joinChannel(channels[i]);

		topic = channel->getTopic();
		// RPL_TOPIC
		if (topic.length()) {
			sender->getServer()->sendMsg(join(sender_prefix, "332", target, RPL_TOPIC(channels[i], topic)), sender);
		}
		else {
			sender->getServer()->sendMsg(join(sender_prefix, "331", target, RPL_NOTOPIC(channels[i])), sender);
		}

		// RPL_NAMREPLY
		userlist = channel->getUserList(sender);
		sender->getServer()->sendMsg(join(sender_prefix, "353", target, RPL_NAMREPLY(channels[i], userlist)), sender);
	}

	return std::string();
}
