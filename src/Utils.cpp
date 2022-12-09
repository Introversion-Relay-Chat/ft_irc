#include "Utils.hpp"

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
