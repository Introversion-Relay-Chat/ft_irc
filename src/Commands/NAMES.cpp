#include "../Utils.hpp"

std::string NAMES(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	Channel								*channel;
	User								*user;
	std::vector<std::string>			channels;
	std::map<std::string, Channel *>	all_channels;
	std::set<int>						channel_users;
	std::map<int, User *>				server_users;
	std::string							userlist;
	std::set<std::string>				user_channels;
	std::set<std::string>				sender_channels;
	std::set<std::string>::iterator		chan_it;

	// return users from all channels 
	if (message.middle.size() < 1) {
		all_channels = sender->getServer()->getChannels();
		for (std::map<std::string, Channel *>::iterator chan = all_channels.begin(); chan != all_channels.end(); chan++) {
			channels.push_back((*chan).first);
		}
	}
	// return users from chosen channels
	else {
		channels = split(message.middle[0], ",");
	}
	for (unsigned long i=0; i < channels.size(); i++){
		channel = all_channels[channels[i]];
		// pass if channel not exist
		if (!channel) {
			continue ;
		}

		channel_users = channel->getUsers();
		// pass if channel (private or secret) and not on channel
		if (((channel->getMode() & FLAG_CHANNEL_P) || \
		(channel->getMode() & FLAG_CHANNEL_S)) && \
		(channel_users.find(sender->getUserSocket()) == channel_users.end())) {
			continue ;
		}

		// RPL_NAMREPLY
		userlist = channel->getUserList(sender);
		sender->getServer()->sendMsg(join(sender_prefix, "353", target, RPL_NAMREPLY(channels[i], userlist)), sender);
		// RPL_ENDOFNAMES
		sender->getServer()->sendMsg(join(sender_prefix, "366", target, RPL_ENDOFNAMES(channels[i])), sender);
	}

	// users visible but not on any channel or not on a visible channel are listed as being on channel *
	server_users = sender->getServer()->getUsers();
	userlist = std::string();
	sender_channels = sender->getJoinedChannels();
	for (std::map<int, User *>::iterator it=server_users.begin(); it!=server_users.end(); it++) {
		user = (*it).second;
		user_channels = user->getJoinedChannels();
		// unvisible or empty
		if ((user->getMode() & FLAG_USER_I) || user_channels.empty()) {
			continue ;
		}
		// all user_channels unvisible (private or secret) and not on
		for (chan_it=user_channels.begin(); chan_it!=user_channels.end(); chan_it++) {
			channel = all_channels[*chan_it];
			if (((channel->getMode() & FLAG_CHANNEL_P) || \
			(channel->getMode() & FLAG_CHANNEL_S)) && \
			(channel_users.find(sender->getUserSocket()) == channel_users.end())) {
				continue ;
			}
			break ;
		}
		if (chan_it == user_channels.end())
			userlist += user->getNickname() + " ";
	}
	// RPL_NAMREPLY
	sender->getServer()->sendMsg(join(sender_prefix, "353", target, RPL_NAMREPLY("*", userlist)), sender);
	// RPL_ENDOFNAMES
	sender->getServer()->sendMsg(join(sender_prefix, "366", target, RPL_ENDOFNAMES("*")), sender);
	return std::string();
}
