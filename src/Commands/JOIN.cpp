#include "../Utils.hpp"

/*
NEED TO ADD

MAX_CHANNEL
sender->getSocket()
sender->getServer()->getChannel()
sender->getServer()->createNewChannel(sender)
channel->getUsers()
channel->getLimit()
channel->getInvited();
std::set<int> _invited
std::set<int> banlist = channel->getBanlist();
channel->getMode()
channel->getKey()

*/
std::string JOIN(const Message &message, User *sender)
{
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;
	Channel						*channel;

	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 1)
		return NumericReply(sender->getUserPrefix(), "461", sender->getNickname(), message);
	
	channels = ft.split(message.middle[0]);
	if (message.middle.size() >= 2)
		keys = ft.split(message.middle[1]);
	while (keys.size() < channels.size())
		keys.push_back(std::string());

	for (int i=0; i < channels.size(); i++){
		channel = sender->getServer()->getChannel()[channels[i]];
		// Create Channel
		if (!channel) {
			// ERR_TOOMANYCHANNELS
			if (sender->getServer()->getChannel().size() == MAX_CHANNEL)
				return NumericReply(sender->getServerPrefix(), "405", sender->getNickname(), message);
			else {
				sender->getServer()->createNewChannel(sender);
				channel = sender->getServer()->getChannel()[channels[i]];
			}
		}
		// ERR_CHANNELISFULL
		if (channel->getUsers().size() >= channel->getLimit())
			return NumericReply(sender->getServerPrefix(), "471", sender->getNickname(), message);

		// 1. invite-only
		// ERR_INVITEONLYCHAN
		std::set<int> invited = channel->getInvited();
		if (channel->getMode() & FLAG_CHANNEL_I)
			if (invited.find(sender->getSocket()) == invited.end())
				return NumericReply(sender->getServerPrefix(), "473", sender->getNickname(), message);
		
		/*
		// 2. nick/username/hostname not in active bans.
		// ERR_BANNEDFROMCHAN
		std::set<int> banlist = channel->getBanlist();
		if (channel->getModes & FLAG_CHANNEL_B)
			if (banlist.find(sender->getSocket()) != banlist.end())
				return NumericReply(sender->getServerPrefix(), "474", sender->getNickname(), message);
		*/

		// 3. passowrd if needed
		// ERR_BADCHANNELKEY
		if (channel->getMode() & FLAG_CHANNEL_K)
			if (keys[i] != channel->getKey())
				return NumericReply(sender->getServerPrefix(), "475", sender->getNickname(), message);

		// RPL_TOPIC
		RPL_TOPIC(channel, topic);
		NumericReply(sender->getServerPrefix(), "332", sender->getNickname(), message);
		// RPL_NAMREPLY
		NumericReply(sender->getServerPrefix(), "353", sender->getNickname(), message);
	}




	if (message.middle.size() < 1)
		return NumericReply(sender_prefix, "461", target, message);
	if (sender->getStatus() != PASSWORD)
		return NumericReply(sender_prefix, "462", target, message);

	if (sender->getServer()->getPassword() == message.middle[0])
		sender->setStatus(REGISTER);
	return std::string();
}
