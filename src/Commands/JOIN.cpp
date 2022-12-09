#include "../Utils.hpp"

// TODO: server name rule, banmask related job;
std::string JOIN(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	std::vector<std::string>			channels;
	std::vector<std::string>			keys;
	std::map<std::string, Channel *>	all_channels;
	Channel								*channel;
	std::set<int> 						invited;
	std::set<int>						channel_users;
	std::map<int, User *>				server_users;
	std::string							topic;
	std::string							nicknames;

	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 1)
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	
	channels = split(message.middle[0], ",");
	if (message.middle.size() >= 2)
		keys = split(message.middle[1], ",");
	while (keys.size() < channels.size())
		keys.push_back(std::string());

	all_channels = sender->getServer()->getChannels();
	for (unsigned long i=0; i < channels.size(); i++){
		channel = all_channels[channels[i]];
		// create channel if doesnt exist
		if (!channel) {
			// ERR_TOOMANYCHANNELS
			if (all_channels.size() == MAX_CHANNEL) {
				return join(sender_prefix, "405", target, ERR_TOOMANYCHANNELS(channels[i]));
			}
			else {
				sender->getServer()->createChannel(channels[i], sender);
				all_channels = sender->getServer()->getChannels();
				channel = all_channels[channels[i]];
			}
		}
		// ERR_CHANNELISFULL
		if (static_cast<int>(channel->getUsers().size()) >= channel->getLimit()) {
			return join(sender_prefix, "471", target, ERR_CHANNELISFULL(channels[i]));
		}

		// 1. invite-only
		// ERR_INVITEONLYCHAN
		invited = channel->getInvited();
		if (channel->getMode() & FLAG_CHANNEL_I) {
			if (invited.find(sender->getUserSocket()) == invited.end()) {
				return join(sender_prefix, "473", target, ERR_INVITEONLYCHAN(channels[i]));
			}
		}
		
		/*
		// 2. nick/username/hostname not in active bans.
		// ERR_BANNEDFROMCHAN
		std::set<int> banlist = channel->getBanlist();
		if (channel->getModes & FLAG_CHANNEL_B)
			if (banlist.find(sender->getUserSocket()) != banlist.end())
				return join(sender->getServerPrefix(), "474", sender->getNickname(), message);
		*/

		// 3. passowrd if needed
		// ERR_BADCHANNELKEY
		if (channel->getMode() & FLAG_CHANNEL_K)
			if (keys[i] != channel->getKey())
				return join(sender_prefix, "475", target, ERR_BADCHANNELKEY(channels[i]));

		// join channel
		channel->addUser(sender);
		sender->joinChannel(channels[i]);

		// RPL_TOPIC
		topic = channel->getTopic();
		if (topic.length())
			sender->getServer()->sendMsg(join(sender_prefix, "332", target, RPL_TOPIC(channels[i], topic)), sender);
		else
			sender->getServer()->sendMsg(join(sender_prefix, "332", target, RPL_NOTOPIC(channels[i])), sender);
		
		// RPL_NAMREPLY
		channel_users = channel->getUsers();
		server_users = sender->getServer()->getUsers();
    	for (std::set<int>::iterator user=channel_users.begin(); user != channel_users.end(); user++) {
			if (*user == channel->getOperator())
				nicknames += "@" + server_users[*user]->getNickname() + " ";
			else
				nicknames += server_users[*user]->getNickname() + " ";
		}
		sender->getServer()->sendMsg(join(sender_prefix, "353", target, RPL_NAMREPLY(channels[i], nicknames)), sender);
	}

	return std::string();
}
