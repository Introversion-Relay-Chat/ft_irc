#include "../Utils.hpp"

std::string LIST(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	Channel								*channel;
	std::vector<std::string>			channels;
	std::map<std::string, Channel *>	all_channels;
	std::string							topic;
	std::string							visible;
	std::set<int>						channel_users;

	all_channels = sender->getServer()->getChannels();
	// return all channels 
	if (message.middle.size() < 1) {
		for (std::map<std::string, Channel *>::iterator chan = all_channels.begin(); chan != all_channels.end(); chan++) {
			channels.push_back((*chan).first);
		}
	}
	// return chosen channels
	else {
		channels = split(message.middle[0], ",");
	}

	// RPL_LISTSTART
	sender->getServer()->sendMsg(join(sender_prefix, "321", target, RPL_LISTSTART()), sender);
	for (unsigned long i=0; i < channels.size(); i++){
		channel = all_channels[channels[i]];
		channel_users = channel->getUsers();
		visible = "";
		topic = channel->getTopic();
		// pass if channel not exist
		if (!channel) {
			continue ;
		}
		// Secret
		if (channel->getMode() & FLAG_CHANNEL_S) {
			if (channel_users.find(sender->getUserSocket()) == channel_users.end()) {
				continue ;
			}
			visible = " Scr";
		}

		// Private
		if (channel->getMode() & FLAG_CHANNEL_P) {
			if (channel_users.find(sender->getUserSocket()) == channel_users.end()) {
				visible = " Prv";
				topic = "";
			}
		}

		// RPL_LIST
		sender->getServer()->sendMsg(join(sender_prefix, "322", target, RPL_LIST(channels[i], visible, topic)), sender);
	}
	// RPL_LISTEND
	sender->getServer()->sendMsg(join(sender_prefix, "323", target, RPL_LISTEND()), sender);
	return std::string();
}
