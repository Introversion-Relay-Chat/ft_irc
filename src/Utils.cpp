#include "../include/Utils.hpp"

void error(std::string message, bool stop) {
	std::cerr << "error: " << message << std::endl;
	if (stop)
		exit(EXIT_FAILURE);
}

std::vector<std::string> split(std::string str, std::string delimiter) {
	std::vector<std::string>	splitted;
	std::string					tmp;
	size_t 						pos;

	while ((pos = str.find(delimiter)) != std::string::npos) {
		tmp = str.substr(0, pos);
		str.erase(0, pos + delimiter.length());
		if (!tmp.length())
			continue;
		splitted.push_back(tmp);
	}
	if (str.length())
		splitted.push_back(str);
	return splitted;
}

std::string join(std::string sender_prefix, std::string code, std::string target, std::string message) {
	return ":" + sender_prefix + " " + code + " " + target + " " + message;
}

std::string toString(int num)
{
	std::stringstream stream;
	stream << num;
	return stream.str();
}

std::ostream& operator<<(std::ostream& os, const Message& message) {
	os << "command: " << "|" << message.command << "|" << std::endl;
	os << "middle: " << std::endl;
	for (std::vector<std::string>::const_iterator m = message.middle.begin(); m != message.middle.end(); m++) {
		os << "|" << *m << "|" << std::endl;
	}
	os << "trailing: " << "|" << message.trailing << "|" << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::map<std::string, time_t>& nick_history) {
	std::cout << "nickname history: " << std::endl;
	for (std::map<std::string, time_t>::const_iterator pn = nick_history.begin(); pn != nick_history.end(); pn++) {
		os << "|" << pn->first << "|" << " update_time: " << pn->second << std::endl;
	}
	return os;
}

std::string currTime(void) {
	time_t curr_time;
	struct tm *local_time;
	std::string local_time_str;

	time(&curr_time);
	local_time = localtime(&curr_time);
	local_time_str = asctime(local_time);
	local_time_str.erase(--local_time_str.end());
	return local_time_str;
}

// bool isIncluded(std::string pattern, std::string target) {
// 	size_t u = 0, i = 0;

// 	while (i < pattern.length()) {
// 		if (pattern[i] == '*') {
// 			while (++i < pattern.length()) {
// 				if (!(pattern[i] == '*' || pattern[i] == '?')) {
// 					break;
// 				}
// 			}
// 			if (i == pattern.length()) {
// 				return true;
// 			}
// 			while (pattern[i] != target[u]) {
// 				if (u == target.length()) {
// 					return false;
// 				}
// 				u++;
// 			}
// 		} else if (pattern[i] == '?') {
// 			if (u == target.length()) {
// 				return false;
// 			}
// 			u++;
// 		} else {
// 			if (u == target.length() || pattern[i] != target[u]) {
// 				return false;
// 			}
// 			u++;
// 		}
// 		i++;
// 	}
// 	return true;
// }

bool confirmMatch(std::string pattern, std::string target) {
	size_t cur = 0;
	while (cur < target.length() && cur < pattern.length()
	&& (pattern[cur] == '?' || pattern[cur] == target[cur])) {
		++cur;
	}

	if (cur == pattern.length()) {
		return cur == target.size();
	}

	if (pattern[cur] == '*') {
		for (size_t i = 0; cur + i <= target.length(); ++i)
		{
			if (confirmMatch(pattern.substr(cur + 1), target.substr(cur + i))) {
				return true;
			}
		}
	}
	return false;
}

bool checkMask(std::set<std::string> banlist, std::string prefix) {
	std::string user = prefix.substr(0, prefix.find("@", 0));
	std::string nickname = user.substr(0, user.find("!", 0));
	std::string username = user.substr(user.find("!", 0) + 1);
	std::string bannick;
	std::string banuser;

	std::cout << "user: " << user << std::endl;
	std::cout << "nickname: " << nickname << std::endl;
	std::cout << "username: " << username << std::endl;
	for (std::set<std::string>::iterator it = banlist.begin();it != banlist.end();it++) {
		bannick = (*it).substr(0, (*it).find("!", 0));
		banuser = (*it).substr((*it).find("!", 0) + 1);
		if (confirmMatch(bannick, nickname) && confirmMatch(bannick, username)) {
		// if (isIncluded(bannick, nickname) && isIncluded(banuser, banuser)) {
			return true;
		}
	}
	return false;
}
