#include "Utils.hpp"

// 331
std::string RPL_NOTOPIC(const std::string &channel) {
	return channel + " :No topic is set";
}

// 332
std::string RPL_TOPIC(const std::string &channel, const std::string &topic) {
	return channel + " :" + topic;
}

// 353
std::string RPL_NAMREPLY(const std::string &channel, const std::string &nicknames) {
	return channel + " :" + nicknames;
}

// 403
std::string ERR_NOSUCHCHANNEL(const std::string &channel) {
	return channel + " :No such channel";
}

// 405
std::string ERR_TOOMANYCHANNELS(const std::string &channel) {
	return channel + " :You have joined too many channels";
}

// 421
std::string ERR_UNKNOWNCOMMAND(const std::string &command) {
	return command + " :Unknown command" ;
}

// 442
std::string ERR_NOTONCHANNEL(const std::string &command) {
	return command + " :You're not on that channel" ;
}

// 461
std::string ERR_NEEDMOREPARAMS(const std::string &command) {
	return command + " :Not enough parameters" ;
}

// 462
std::string ERR_ALREADYREGISTRED(void) {
	return ":You may not reregister" ;
}

// 471
std::string ERR_CHANNELISFULL(const std::string &channel) {
	return channel + " :Cannot join channel (+l)" ;
}

// 473
std::string ERR_INVITEONLYCHAN(const std::string &channel) {
	return channel + " :Cannot join channel (+i)" ;
}

// 475
std::string ERR_BADCHANNELKEY(const std::string &channel) {
	return channel + " :Cannot join channel (+k)" ;
}

