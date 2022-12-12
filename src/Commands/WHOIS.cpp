#include "../../include/Utils.hpp"

std::string WHOIS(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();
	Server *server = sender->getServer();

	// nickname이 주어지지 않은 경우, 431 ERR_NONICKNAMEGIVEN
	if (message.middle.size() < 1) {
		return join(sender_prefix, "431", sender->getNickname(), ERR_NONICKNAMEGIVEN());
	}
	std::string nickname = message.middle[0];
	std::map<int, User *> users = server->getUsers();
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++) {
		if (it->second->getNickname() == nickname) {
			User *user = it->second;
			std::string nickname = user->getNickname();
			std::string hostname = user->getHostname();
			std::string username = user->getUsername();
			std::string realname = user->getRealname();

			// 311 RPL_WHOISUSER
			server->sendMsg(
				join(sender_prefix, "311", nickname,
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
					join(sender_prefix, "319", nickname,
					RPL_WHOISCHANNELS(nickname, channel_list)
					), sender);
			}

			std::string info = std::string("\nThis is IRC server from Introversion-Relay-Chat\n")
			+ std::string("Version is ") + server->getServerVersion() + std::string(".0\n")
			+ std::string("Server started at ") + server->getStartTime();
			// 312 RPL_WHOISSERVER
			server->sendMsg(
				join(sender_prefix, "312", nickname,
				RPL_WHOISSERVER(nickname, server->getServername(), info)
				), sender);

			// 301 RPL_AWAY
			server->sendMsg(
				join(sender_prefix, "301", nickname,
				RPL_AWAY(message.middle[0], "This is message from IRC server.")
				), sender);

			// 313 RPL_WHOISOPERATOR
			if (it->second->getMode() & FLAG_CHANNEL_O) {
				server->sendMsg(
					join(sender_prefix, "313", nickname,
					RPL_WHOISOPERATOR(nickname)
					), sender);
			}
			time_t cur_time = time(NULL);
			// 317 RPL_WHOISIDLE
			server->sendMsg(
				join(sender_prefix, "317", nickname,
				RPL_WHOISIDLE(nickname, static_cast<int>(difftime(cur_time, user->getLoginTime())))
				), sender);

			// 318 RPL_ENDOFWHOIS
			server->sendMsg(
				join(sender_prefix, "318", nickname,
				RPL_ENDOFWHOIS(nickname)
				), sender);
			return std::string();
		}
	}
	// nickname이 존재하지 않는 경우, 401 ERR_NOSUCHNICK
	return join(sender_prefix, "401", nickname, ERR_NOSUCHNICK(nickname));
}
