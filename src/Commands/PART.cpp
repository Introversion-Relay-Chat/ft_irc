#include "../Utils.hpp"

// TODO: server name rule
std::string PART(const Message &message, User *sender) {
	std::string							sender_prefix = sender->getServerPrefix();
	std::string							target = sender->getNickname();
	std::vector<std::string>			channels;
	std::map<std::string, Channel *>	all_channels;
	Channel								*channel;
	std::set<int>						channel_users;

	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 1)
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	channels = split(message.middle[0], ",");
	all_channels = sender->getServer()->getChannels();
	for (unsigned long i=0; i < channels.size(); i++){
		// ERR_NOSUCHCHANNEL
		if (!all_channels[channels[i]]) {
			return join(sender_prefix, "403", target, ERR_NOSUCHCHANNEL(channels[i]));
		}
		channel = all_channels[channels[i]];
		channel_users = channel->getUsers();
		// ERR_NOTONCHANNEL
		if (channel_users.find(sender->getUserSocket()) == channel_users.end()) {
			return join(sender_prefix, "442", target, ERR_NOTONCHANNEL(channels[i]));
		}
		// leave channel
		channel->removeUser(sender);
		sender->leaveChannel(channels[i]);
		channel_users = channel->getUsers();
		if (channel_users.size() == 0) {
			sender->getServer()->deleteChannel(channels[i]);
		}
	}
	return std::string();
}
