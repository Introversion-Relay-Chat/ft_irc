#include "../../include/Utils.hpp"

class UserName {
	public:
		UserName(std::string nickname, std::string username, std::string hostname, std::string realname) {
			this->nickname = nickname;
			this->username = username;
			this->hostname = hostname;
			this->realname = realname;
		}
		~UserName() {}

		std::string nickname;
		std::string username;
		std::string hostname;
		std::string realname;
};

bool comp(const std::pair<UserName *, time_t>& a, const std::pair<UserName *, time_t>& b) {
	return a.second > b.second;
};

std::string WHOWAS(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();
	Server *server = sender->getServer();
	(void)sender;
	(void)server;

	// nickname이 입력되지 않은 경우, 431 ERR_NONICKNAMEGIVEN
	if (message.middle.size() < 1) {
		return join(sender_prefix, "431", sender->getNickname(), ERR_NONICKNAMEGIVEN());
	}
	std::string search_nickname = message.middle[0];

	int count = INT_MAX;
	if (message.middle.size() == 2) {
		count = atoi(message.middle[1].c_str());
		if (count < 0) {
			count = INT_MAX;
		}
	}

	// 서버에 존재하는 모든 유저를 검색하여 nickname 히스토리를 확인하고, 그 중 search_nickname과 일치하는 값을 results에 저장.
	std::map<int, User *> users = server->getUsers();
	std::map<UserName *, time_t> results;
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++) {
		std::map<std::string, time_t> nick_history = it->second->getNickHistory();
		for (std::map<std::string, time_t>::iterator it2 = nick_history.begin(); it2 != nick_history.end(); it2++) {
			if (it2->first == search_nickname) {
				UserName *user = new UserName(it->second->getNickname(), it->second->getUsername(), it->second->getHostname(), it->second->getRealname());
				results.insert(std::pair<UserName *, time_t>(user, it2->second));
			}
		}
	}

	// results를 second 기준으로 내림차순 정렬
	std::vector<std::pair<UserName *, time_t> > sorted_results(results.begin(), results.end());
	std::sort(sorted_results.begin(), sorted_results.end(), comp);

	// nickname 히스토리가 존재하지 않는 경우, 401 ERR_NOSUCHNICK
	if (results.size() == 0) {
		return join(sender_prefix, "401", sender->getNickname(), ERR_NOSUCHNICK(search_nickname));
	}

	// 정렬된 결과를 순회하며 314 RPL_WHOWASUSER, 312 WHOISSERVER를 응답
	int i = 0;
	for (std::vector<std::pair<UserName *, time_t> >::iterator it = sorted_results.begin(); it != sorted_results.end(); it++) {
		if (i >= count) {
			break;
		}
		// 314 RPL_WHOWASUSER
		server->sendMsg(
				join(sender_prefix, "314", it->first->nickname,
				RPL_WHOWASUSER(it->first->nickname, it->first->username, it->first->hostname, it->first->realname)
				), sender);
		// 312 WHOISSERVER
		server->sendMsg(
				join(sender_prefix, "312", it->first->nickname,
				RPL_WHOISSERVER(it->first->nickname, it->first->hostname, it->first->realname)
				), sender);
		++i;
	}

	// 369 RPL_ENDOFWHOWAS
	return join(sender_prefix, "369", sender->getNickname(), RPL_ENDOFWHOWAS(search_nickname));
}
