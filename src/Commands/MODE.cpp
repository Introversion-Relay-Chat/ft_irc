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
	std::set<int>										operators;
	std::set<std::string>								banlist;
	

	sender_prefix = sender->getServerPrefix();
	target = sender->getNickname();
	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 2) {
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));
	}

	name = message.middle[0];
	channel = sender->getServer()->getChannelByName(name);
	user = sender->getServer()->getUserByName(name);
	flags = message.middle[1];
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
					if (message.middle.size() < 3) {
						sender->getServer()->sendMsg(join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command)), sender);
					} else {
						user = sender->getServer()->getUserByName(message.middle[2]);
						// ERR_NOSUCHNICK
						if (!user || !channel->checkOnChannel(user)) {
							sender->getServer()->sendMsg(join(sender_prefix, "401", target, ERR_NOSUCHNICK(message.middle[2])), sender);
							break ;
						}
						if (sign == '+') {
							channel->addOperator(user);
							channel->setMode(channel->getMode() | FLAG_CHANNEL_O);
						}
						else if (sign == '-') {
							channel->removeOperator(user);
							if (channel->getOperators().empty()) {
								channel->setMode(channel->getMode() & ~FLAG_CHANNEL_O);
							}
						}
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
						if (message.middle.size() < 3) {
							sender->getServer()->sendMsg(join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command)), sender);
						} else {
							channel->setLimit(atoi(message.middle[2].c_str()));
							channel->setMode(channel->getMode() | FLAG_CHANNEL_L);
						}
					}
					else if (sign == '-') {
						channel->setLimit(DEFAULT_LIMIT);
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_L);
					}
					break ;
				case 'b':
					// ERR_NEEDMOREPARAMS
					if (message.middle.size() < 3) {
						sender->getServer()->sendMsg(join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command)), sender);
						break ;
					}
					if (sign == '+') {
						channel->setBanMask(message.middle[2]);
						channel->setMode(channel->getMode() | FLAG_CHANNEL_B);
					}
					else if (sign == '-') {
						channel->removeBanMask(message.middle[2]);
						if (channel->getBanList().empty()) {
							channel->setMode(channel->getMode() & ~FLAG_CHANNEL_B);
						}
					}
					// RPL_BANLIST
					banlist = channel->getBanList();
					for (std::set<std::string>::iterator it = banlist.begin();it != banlist.end();it++) {
						sender->getServer()->sendMsg(join(sender_prefix, "367", target, RPL_BANLIST(name, *it)), sender);
					}
					// RPL_ENDOFBANLIST
					sender->getServer()->sendMsg(join(sender_prefix, "368", target, RPL_ENDOFBANLIST(name)), sender);
					break ;
				case 'k':
					if (sign == '+') {
						// ERR_NEEDMOREPARAMS
						if (message.middle.size() < 3) {
							sender->getServer()->sendMsg(join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command)), sender);
						}
						// ERR_KEYSET
						else if (channel->getKey().length() > 0) {
							sender->getServer()->sendMsg(join(sender_prefix, "467", target, ERR_KEYSET(name)), sender);
						}
						else {
							channel->setKey(message.middle[2]);
							channel->setMode(channel->getMode() | FLAG_CHANNEL_K);
						}
					}
					else if (sign == '-') {
						channel->setKey("");
						channel->setMode(channel->getMode() & ~FLAG_CHANNEL_K);
					}
					break ;
			}
		}
		// RPL_CHANNELMODEIS
		if (channel->getMode() & FLAG_CHANNEL_O) {
			mode += "o";
		}
		if (channel->getMode() & FLAG_CHANNEL_P) {
			mode += "p";
		}
		if (channel->getMode() & FLAG_CHANNEL_S) {
			mode += "s";
		}
		if (channel->getMode() & FLAG_CHANNEL_I) {
			mode += "i";
		}
		if (channel->getMode() & FLAG_CHANNEL_T) {
			mode += "t";
		}
		if (channel->getMode() & FLAG_CHANNEL_N) {
			mode += "n";
		}
		if (channel->getMode() & FLAG_CHANNEL_B) {
			mode += "b";
		}
		if (channel->getMode() & FLAG_CHANNEL_L) {
			mode += "l";
		}
		if (channel->getMode() & FLAG_CHANNEL_K) {
			mode += "k";
		}
		return join(sender_prefix, "324", target, RPL_CHANNELMODEIS(name, mode));
	}
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
		if (user->getMode() & FLAG_USER_I) {
			mode += "i";
		}
		if (user->getMode() & FLAG_USER_O) {
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
