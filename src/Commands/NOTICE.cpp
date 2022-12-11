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
				std::vector<std::string> user_list = split(channel->getUserList(sender), " ");
				for (std::vector<std::string>::iterator it2 = user_list.begin();it2 != user_list.end();it2++) {
					if ((*it2)[0] == '@') {
						(*it2).erase((*it2).begin());
					}
					responses.push_back(make_pair("301", *it2));
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
		sender->getServer()->sendMsg(join(sender_prefix, "301", user->getNickname(), RPL_AWAY(user->getNickname(), message.trailing)), user);
	}
	return std::string();
}