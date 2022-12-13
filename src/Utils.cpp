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

bool isIncluded(std::string ban, std::string user) {
	size_t u = 0, i = 0;

	while (i < ban.length()) {
		if (ban[i] == '*') {
			while (++i < ban.length()) {
				if (!(ban[i] == '*' || ban[i] == '?')) {
					break;
				}
			}
			if (i == ban.length()) {
				return true;
			}
			while (ban[i] != user[u]) {
				if (u == user.length()) {
					return false;
				}
				u++;
			}
		} else if (ban[i] == '?') {
			if (u == user.length()) {
				return false;
			}
			u++;
		} else {
			if (u == user.length() || ban[i] != user[u]) {
				return false;
			}
			u++;
		}
		i++;
	}
	return true;
}

bool checkMask(std::set<std::string> banlist, std::string prefix) {
	std::string user = prefix.substr(0, prefix.find("@", 0));
	std::string nickname = user.substr(0, user.find("!", 0));
	std::string username = user.substr(user.find("!", 0) + 1);
	std::string bannick;
	std::string banuser;

	for (std::set<std::string>::iterator it = banlist.begin();it != banlist.end();it++) {
		bannick = (*it).substr(0, (*it).find("!", 0));
		banuser = (*it).substr((*it).find("!", 0) + 1);
		if (isIncluded(bannick, nickname) && isIncluded(banuser, banuser)) {
			return true;
		}
	}
	return false;
}