#include "../../include/Utils.hpp"

void	WHOISONE(std::string sender_prefix, std::string nickname, User *sender, Server *server) {
	std::map<int, User *> users = server->getUsers();
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++) {
			if (confirmMatch(nickname, it->second->getNickname())) {
			User *user = it->second;
			std::string nickname = user->getNickname();
			std::string hostname = user->getHostname();
			std::string username = user->getUsername();
			std::string realname = user->getRealname();

			// 311 RPL_WHOISUSER
			server->sendMsg(
				join(sender_prefix, "311", sender->getNickname(),
				RPL_WHOISUSER(nickname, username, hostname, realname)
				), sender);

			// 참여중인 채널이 있는 경우, 319 RPL_WHOISCHANNELS
			std::set<std::string> channels = user->getJoinedChannels();
			if (channels.size() != 0) {
				std::string channel_list = "";
				for (std::set<std::string>::iterator it2 = channels.begin(); it2 != channels.end(); it2++) {
					channel_list += *it2 + " ";
				}
				server->sendMsg(
					join(sender_prefix, "319", sender->getNickname(),
					RPL_WHOISCHANNELS(nickname, channel_list)
					), sender);
			}

			std::string info = std::string("\nThis is IRC server from Introversion-Relay-Chat\n")
			+ std::string("Version is ") + server->getServerVersion() + std::string(".0\n")
			+ std::string("Server started at ") + server->getStartTime();
			// 312 RPL_WHOISSERVER
			server->sendMsg(
				join(sender_prefix, "312", sender->getNickname(),
				RPL_WHOISSERVER(nickname, server->getServername(), info)
				), sender);

			// 301 RPL_AWAY
			server->sendMsg(
				join(sender_prefix, "301", sender->getNickname(),
				RPL_AWAY(nickname, "This is message from IRC server.")
				), sender);

			// 313 RPL_WHOISOPERATOR
			if (it->second->getMode() & FLAG_USER_O) {
				server->sendMsg(
					join(sender_prefix, "313", sender->getNickname(),
					RPL_WHOISOPERATOR(nickname)
					), sender);
			}
			time_t cur_time = time(NULL);
			// 317 RPL_WHOISIDLE
			server->sendMsg(
				join(sender_prefix, "317", sender->getNickname(),
				RPL_WHOISIDLE(nickname, static_cast<int>(difftime(cur_time, user->getLoginTime())))
				), sender);
			// 318 RPL_ENDOFWHOIS
			server->sendMsg(
				join(sender_prefix, "318", sender->getNickname(),
				RPL_ENDOFWHOIS(nickname)
				), sender);
		}
	}
	server->sendMsg(
		join(sender_prefix, "401", sender->getNickname(),
		ERR_NOSUCHNICK(nickname)
		), sender);
}

std::string WHOIS(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();
	Server *server = sender->getServer();

	// nickname이 주어지지 않은 경우, 431 ERR_NONICKNAMEGIVEN
	if (message.middle.size() < 1) {
		return join(sender_prefix, "431", sender->getNickname(), ERR_NONICKNAMEGIVEN());
	}
	std::vector<std::string> nicknames = split(message.middle[0], ",");
	for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); it++) {
		WHOISONE(sender_prefix, *it, sender, server);
	}
	return std::string();
}
