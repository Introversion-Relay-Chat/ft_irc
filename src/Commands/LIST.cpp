#include "../Utils.hpp"

std::string LIST(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	Channel								*channel;
	std::vector<std::string>			channels;
	std::set<int>						channel_users;

	// return all channels 
	if (message.middle.size() < 1) {
		channels = sender->getServer()->getChannelNames();
	}
	// return chosen channels
	else {
		channels = split(message.middle[0], ",");
	}

	// RPL_LISTSTART
	sender->getServer()->sendMsg(join(sender_prefix, "321", target, RPL_LISTSTART()), sender);
	for (unsigned long i=0; i < channels.size(); i++){
		channel = sender->getServer()->getChannelByName(channels[i]);
		channel_users = channel->getUsers();
		// pass if channel not exist
		if (!channel) {
			continue ;
		}

		// Secret
		if (channel->getMode() & FLAG_CHANNEL_S) {
			// pass if not on channel
			if (channel_users.find(sender->getUserSocket()) == channel_users.end()) {
				continue ;
			}
			// RPL_LIST
			sender->getServer()->sendMsg(join(sender_prefix, "322", target, RPL_LIST(channels[i], " Scr", "")), sender);
			continue ;
		}

		// Private
		if (channel->getMode() & FLAG_CHANNEL_P) {
			// hide topic if not on channel
			if (channel_users.find(sender->getUserSocket()) == channel_users.end()) {
				// RPL_LIST
				sender->getServer()->sendMsg(join(sender_prefix, "322", target, RPL_LIST(channels[i], " Prv", "")), sender);
				continue ;
			}
		}

		// RPL_LIST
		sender->getServer()->sendMsg(join(sender_prefix, "322", target, RPL_LIST(channels[i], "", channel->getTopic())), sender);
	}
	// RPL_LISTEND
	sender->getServer()->sendMsg(join(sender_prefix, "323", target, RPL_LISTEND()), sender);
	return std::string();
}
