#include "../../include/Utils.hpp"

std::string NAMES(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	Channel								*channel;
	User								*user;
	std::vector<std::string>			channels;
	std::map<int, User *>				server_users;
	std::string							userlist;
	std::set<std::string>				user_channels;
	std::set<std::string>::iterator		chan_it;

	if (message.middle.size() < 1) {
		channels = sender->getServer()->getChannelNames();
	}
	else {
		channels = split(message.middle[0], ",");
	}

	for (unsigned long i=0; i < channels.size(); i++){
		channel = sender->getServer()->getChannelByName(channels[i]);
		if (!channel) {
			continue ;
		}

		if (!channel->checkVisible(sender)) {
			continue ;
		}

		userlist = channel->getUserList(sender);
		// RPL_NAMREPLY
		sender->getServer()->sendMsg(join(sender_prefix, "353", target, RPL_NAMREPLY(channels[i], userlist)), sender);
		// RPL_ENDOFNAMES
		sender->getServer()->sendMsg(join(sender_prefix, "366", target, RPL_ENDOFNAMES(channels[i])), sender);
	}

	server_users = sender->getServer()->getUsers();
	userlist = std::string();
	for (std::map<int, User *>::iterator it=server_users.begin(); it!=server_users.end(); it++) {
		user = (*it).second;
		user_channels = user->getJoinedChannels();
		if (user->getMode() & FLAG_USER_I) {
			continue ;
		}
		if (!user_channels.empty()) {
			for (chan_it=user_channels.begin(); chan_it!=user_channels.end(); chan_it++) {
				channel = sender->getServer()->getChannelByName(*chan_it);
				if (channel->checkVisible(sender)) {
					continue ;
				}
				break ;
			}
			if (chan_it != user_channels.end()) {
				continue;
			}
		}
		userlist += user->getNickname() + " ";
	}
	// RPL_NAMREPLY
	sender->getServer()->sendMsg(join(sender_prefix, "353", target, RPL_NAMREPLY("*", userlist)), sender);
	// RPL_ENDOFNAMES
	sender->getServer()->sendMsg(join(sender_prefix, "366", target, RPL_ENDOFNAMES("*")), sender);
	return std::string();
}
