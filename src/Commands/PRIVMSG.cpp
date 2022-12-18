#include "../../include/Utils.hpp"

std::string PRIVMSG(const Message &message, User *sender) {
	std::string											server_prefix = sender->getServerPrefix();
	std::string											sender_prefix = sender->getUserPrefix();
	std::string											target = sender->getNickname();
	std::vector<std::string>							recipient;
	Channel												*channel;
	std::vector<std::pair<std::string, std::string> >	responses;

	// ERR_NORECIPIENT
	if (message.middle.empty()) {
		return join(server_prefix, "411", target, ERR_NORECIPIENT(message.command));
	}
	// ERR_NOTEXTTOSEND
	if (!message.trailing.length()) {
		return join(server_prefix, "412", target, ERR_NOTEXTTOSEND());
	}

	recipient = split(message.middle[0], ",");
	for (std::vector<std::string>::iterator it = recipient.begin();it != recipient.end();it++) {
		if ((*it)[0] == '#') {//channel
			channel = sender->getServer()->getChannelByName(*it);
			if (!channel) {
				responses.push_back(make_pair("401", *it));
			} else {
				if (channel->getMode() & FLAG_CHANNEL_N) {
					if (!channel->checkOnChannel(sender)) {
						responses.push_back(make_pair("404", *it));
						continue;
					}
				}
				std::set<int> user_fds = channel->getUsers();
				for (std::set<int>::iterator it2 = user_fds.begin(); it2 != user_fds.end(); ++it2)
				{
					User *user = sender->getServer()->getUserByFd(*it2);
					if (user && user->getNickname() != sender->getNickname()) {
						sender->getServer()->sendMsg(join(sender_prefix, "PRIVMSG", *it, ":" + message.trailing), user);
					}
				}
			}
		} else {//user
			if (!sender->getServer()->getUserByName(*it)) {
				responses.push_back(make_pair("401", *it));
			} else {
				responses.push_back(make_pair("301", *it));
			}
		}
	}

	for (std::vector<std::pair<std::string, std::string> >::iterator it = responses.begin();it != responses.end();it++) {
		if (it->first == "401") {
			sender->getServer()->sendMsg(join(server_prefix, "401", target, ERR_NOSUCHNICK(it->second)), sender);
		} else if (it->first == "404") {
			sender->getServer()->sendMsg(join(server_prefix, "404", target, ERR_CANNOTSENDTOCHAN(it->second)), sender);
		} else {
			User *user = sender->getServer()->getUserByName(it->second);
			sender->getServer()->sendMsg(join(sender_prefix, "PRIVMSG", user->getNickname(), ":" + message.trailing), user);
		}
	}
	return std::string();
}
