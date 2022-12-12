#include "../../include/Utils.hpp"

std::string MODE(const Message &message, User *sender) {
	std::string											sender_prefix;
	std::string											target;
	std::string											name;
	Channel												*channel;
	User												*user;
	char												sign;
	std::string											flags;
	std::string											mode;
	std::string											mode_params;
	

	sender_prefix = sender->getServerPrefix();
	target = sender->getNickname();
	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 2)
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));

	name = message.middle[0];
	channel = sender->getServer()->getChannelByName(name);
	user = sender->getServer()->getUserByName(name);
	flags = message.middle[1];
	// channel mode 
	if (channel) {
		// ERR_NOTONCHANNEL
		if (!channel->checkOnChannel(sender)) {
			return join(sender_prefix, "442", target, ERR_NOTONCHANNEL(name));
		}
		// ERR_CHANOPRIVSNEEDED
		if (!channel->checkPrivilege(sender)) {
			return join(sender_prefix, "482", target, ERR_CHANOPRIVSNEEDED(name));
		}
		sign = flags[0];
		// ERR_UNKNOWNMODE
		for (unsigned long i=1; i < flags.length(); i++) {
			switch (flags[i]) {
				case 'o':
					break ;
				case 'p':
					break ;
				case 's':
					break ;
				case 'i':
					break ;
				case 't':
					break ;
				case 'n':
					break ;
				case 'l':
					break ;
				case 'b':
					break ;
				case 'k':
					break ;
				default:
					mode = flags[i];
					return join(sender_prefix, "472", target, ERR_UNKNOWNMODE(mode));
			}
		}
		for (unsigned long i=1; i < flags.length(); i++) {
			switch (flags[i]) {
				case 'o':
					// ERR_NEEDMOREPARAMS
					if (message.middle.size() < 3)
						sender->getServer()->sendMsg(join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command)), sender);
					user = sender->getServer()->getUserByName(message.middle[2]);
					// ERR_NOSUCHNICK
					if (!user || !channel->checkOnChannel(user)) {
						return join(sender_prefix, "401", target, ERR_NOSUCHNICK(message.middle[2]));
					}
					if (sign == '+') {
						channel->addOperator(user);
						channel->setMode(channel->getMode() | FLAG_CHANNEL_O);
					}
					else if (sign == '-') {
						channel->removeOperator(user);
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_O);
					}
					break ;
				case 'p':
					if (sign == '+') {
						channel->setMode(channel->getMode() | FLAG_CHANNEL_P);
					}
					else if (sign == '-') {
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_P);
					}
					break ;
				case 's':
					if (sign == '+') {
						channel->setMode(channel->getMode() | FLAG_CHANNEL_S);
					}
					else if (sign == '-') {
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_S);
					}
					break ;
				case 'i':
					if (sign == '+') {
						channel->setMode(channel->getMode() | FLAG_CHANNEL_I);
					}
					else if (sign == '-') {
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_I);
					}
					break ;
				case 't':
					if (sign == '+') {
						channel->setMode(channel->getMode() | FLAG_CHANNEL_T);
					}
					else if (sign == '-') {
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_T);
					}
					break ;
				case 'n':
					if (sign == '+') {
						channel->setMode(channel->getMode() | FLAG_CHANNEL_N);
					}
					else if (sign == '-') {
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_N);
					}
					break ;
				case 'l':
					if (sign == '+') {
						// ERR_NEEDMOREPARAMS
						if (message.middle.size() < 3)
							sender->getServer()->sendMsg(join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command)), sender);
						channel->setLimit(atoi(message.middle[2].c_str()));
						channel->setMode(channel->getMode() | FLAG_CHANNEL_L);
					}
					else if (sign == '-') {
						channel->setLimit(DEFAULT_LIMIT);
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_L);
					}
					break ;
				case 'b':
           			// RPL_BANLIST                     
		   			// RPL_ENDOFBANLIST
					break ;
				case 'k':
					if (sign == '+') {
						// ERR_NEEDMOREPARAMS
						if (message.middle.size() < 3)
							sender->getServer()->sendMsg(join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command)), sender);
						// ERR_KEYSET
						if (channel->getKey().length() > 0) {
							sender->getServer()->sendMsg(join(sender_prefix, "467", target, ERR_KEYSET(name)), sender);
						}
						channel->setKey(message.middle[2]);
						channel->setMode(channel->getMode() | FLAG_CHANNEL_K);
					}
					else if (sign == '-') {
						channel->setKey("");
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_K);
					}
					break ;
				}
		
		}
		// RPL_CHANNELMODEIS opsitnlbk
		if (user->getMode() | FLAG_CHANNEL_O) {
			mode += "o";
			mode_params += "o: <operator>";
		}
		if (user->getMode() | FLAG_CHANNEL_P) {
			mode += "p";
		}
		if (user->getMode() | FLAG_CHANNEL_S) {
			mode += "s";
		}
		if (user->getMode() | FLAG_CHANNEL_I) {
			mode += "i";
		}
		if (user->getMode() | FLAG_CHANNEL_T) {
			mode += "t";
		}
		if (user->getMode() | FLAG_CHANNEL_N) {
			mode += "n";
		}
		if (user->getMode() | FLAG_CHANNEL_B) {
			mode += "b";
			mode_params += "b: <banmask>";
		}
		if (user->getMode() | FLAG_CHANNEL_L) {
			mode += "l";
			mode_params += "l: " + toString(channel->getLimit()) + " ";
		}
		if (user->getMode() | FLAG_CHANNEL_K) {
			mode += "k";
			mode_params += "k: " + channel->getKey() + " ";
		}
		return join(sender_prefix, "324", target, RPL_CHANNELMODEIS(name, mode, mode_params));
	}
	// user mode
	else if (user) {
		// ERR_USERSDONTMATCH
		if (user != sender) {
			return join(sender_prefix, "502", target, ERR_USERSDONTMATCH());
		}
		sign = flags[0];
		// ERR_UMODEUNKNOWNFLAG
		for (unsigned long i=1; i < flags.length(); i++) {
			switch (flags[i]) {
				case 'i':
					break ;
				case 'o':
					break ;
				default:
					return join(sender_prefix, "501", target, ERR_UMODEUNKNOWNFLAG());
			}
		}
		for (unsigned long i=1; i < flags.length(); i++) {
			switch (flags[i]) {
				case 'i':
					if (sign == '+') {
						user->setMode(user->getMode() | FLAG_USER_I);
					}
					else if (sign == '-') {
						user->setMode(user->getMode() & ~FLAG_USER_I);
					}
					break ;
				case 'o':
					if (sign == '-') {
						user->setMode(user->getMode() & ~FLAG_USER_O);
					}
					break ;
			}
		}
		// RPL_UMODEIS
		if (user->getMode() | FLAG_USER_I) {
			mode += "i";
		}
		if (user->getMode() | FLAG_USER_O) {
			mode += "o";
		}
		return join(sender_prefix, "221", target, RPL_UMODEIS(mode));
	}
	else {
		// ERR_NOSUCHCHANNEL
		return join(sender_prefix, "403", target, ERR_NOSUCHCHANNEL(name));
	}
	return std::string();
}
