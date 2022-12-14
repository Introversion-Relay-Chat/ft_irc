#include "../../include/Utils.hpp"

bool isInSameChannel(const std::set<std::string> &channels, const std::set<std::string> &target_channels) {
	std::vector<std::string> common_channels;
	std::set_intersection(channels.begin(), channels.end(),
	target_channels.begin(), target_channels.end(),
	std::back_inserter(common_channels));
	if (common_channels.size() > 0) {
		return true;
	}
	return false;
}

std::string WHO(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();
	Server *server = sender->getServer();

	// name이 주어지지 않았거나 '0'이나 '*'로 주어진 경우 모든 visible한 리스트를 보여준다.
	// 1. 서버에 존재하는 모든 채널을 하나씩 확인한다.
	// 2. 채널에 속한 유저를 하나씩 확인한다.
	// 3. sender와 공통 채널이 있는지를 확인한다.
	// 4. sender와 공통 채널이 없고, +i user mode가 아니라면 visible한 유저이다.
	// 5. visible한 유저의 정보를 RPL_WHOREPLY로 응답한다.
	if (message.middle.size() < 1 || (message.middle.size() == 1 && (message.middle[0] == "*" || message.middle[0] == "0"))) {
		std::map<std::string, Channel *> channels = server->getChannels();
		for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++) {
			Channel *channel = it->second;
			std::set<int> user_fds = channel->getUsers();
			for (std::set<int>::iterator it = user_fds.begin(); it != user_fds.end(); it++) {
				User *target_user = server->getUserByFd(*it);
				if (isInSameChannel(sender->getJoinedChannels(), target_user->getJoinedChannels())) {
					continue;
				}
				if (target_user->getMode() & FLAG_USER_I) {
					continue;
				}
				// 352 RPL_WHOREPLY
				server->sendMsg(
					join(sender_prefix, "352", sender->getNickname(),
					RPL_WHOREPLY(channel->getChannelname(), target_user->getUsername(),
											target_user->getHostname(), target_user->getServerPrefix(),
											target_user->getNickname(), target_user->getRealname())
					), sender);
			}
		}
		// 315 RPL_ENDOFWHO
		return join(sender_prefix, "315", sender->getNickname(), RPL_ENDOFWHO("*"));
	}

	// 'o'가 주어진 경우 운영자만 매칭되도록 한다.
	std::string name = message.middle[0];
	bool is_op = false;
	if (message.middle.size() == 2 && message.middle[1] == "o") {
		is_op = true;
	}

	// name이 주어진 경우 name과 일치하는 패턴의 채널에 속한 유저들의 정보를 응답한다.
	std::map<std::string, Channel *> channels = server->getChannels();
	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++) {
		Channel *channel = it->second;
		if (confirmMatch(name, channel->getChannelname())) {
			std::set<int> user_fds = channel->getUsers();
			for (std::set<int>::iterator it = user_fds.begin(); it != user_fds.end(); it++) {
				User *target_user = server->getUserByFd(*it);
				if (is_op && !(target_user->getMode() & FLAG_USER_O)) {
					continue;
				}
				// 352 RPL_WHOREPLY
				server->sendMsg(
					join(sender_prefix, "352", sender->getNickname(),
					RPL_WHOREPLY(channel->getChannelname(), target_user->getUsername(),
											target_user->getHostname(), target_user->getServerPrefix(),
											target_user->getNickname(), target_user->getRealname())
					), sender);
			}
			// 315 RPL_ENDOFWHO
			return join(sender_prefix, "315", sender->getNickname(), RPL_ENDOFWHO(name));
		}
	}

	// name과 일치하는 채널이 없으면 서버에서 hostname or realname or nickname과 패턴이 일치하는 유저들을 응답한다.
	std::map<int, User *> users = server->getUsers();
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++) {
		User *target_user = it->second;
		if (is_op && !(target_user->getMode() & FLAG_USER_O)) {
			continue;
		}
			if (confirmMatch(name, target_user->getHostname())
			|| confirmMatch(name, target_user->getRealname())
			|| confirmMatch(name, target_user->getNickname())) {
			// 352 RPL_WHOREPLY
			server->sendMsg(
				join(sender_prefix, "352", sender->getNickname(),
				RPL_WHOREPLY("*", target_user->getUsername(),
											target_user->getHostname(), target_user->getServerPrefix(),
											target_user->getNickname(), target_user->getRealname())
				), sender);
		}
	}
	return join(sender_prefix, "315", sender->getNickname(), RPL_ENDOFWHO(name));
}
