#include "../../include/Utils.hpp"

std::string NOTICE(const Message &message, User *sender) {
	std::string											sender_prefix = sender->getUserPrefix();
	std::string											target = sender->getNickname();
	std::vector<std::string>							recipient;
	Channel												*channel;
	std::vector<std::pair<std::string, std::string> >	responses;

	if (message.middle.empty()) {
		return std::string();
	}
	if (!message.trailing.length()) {
		return std::string();
	}

	recipient = split(message.middle[0], ",");
	for (std::vector<std::string>::iterator it = recipient.begin();it != recipient.end();it++) {
		if ((*it)[0] == '#') {//channel
			channel = sender->getServer()->getChannelByName(*it);
			if (channel) {
				if (channel->getMode() & FLAG_CHANNEL_N) {
					if (!channel->checkOnChannel(sender)) {
						continue;
					}
				}
				std::set<int> user_fds = channel->getUsers();
				for (std::set<int>::iterator it2 = user_fds.begin(); it2 != user_fds.end(); ++it2)
				{
					User *user = sender->getServer()->getUserByFd(*it2);
					if (user && user->getNickname() != sender->getNickname()) {
						sender->getServer()->sendMsg(join(sender_prefix, "NOTICE", *it, ":" + message.trailing), user);
					}
				}
			}
		} else {//user
			if (sender->getServer()->getUserByName(*it)) {
				responses.push_back(make_pair("301", *it));
			}
		}
	}

	for (std::vector<std::pair<std::string, std::string> >::iterator it = responses.begin();it != responses.end();it++) {
		User *user = sender->getServer()->getUserByName(it->second);
		sender->getServer()->sendMsg(join(sender_prefix, "NOTICE", user->getNickname(), ":" + message.trailing), user);
	}
	return std::string();
}
