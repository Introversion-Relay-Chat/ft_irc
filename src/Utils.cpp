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
