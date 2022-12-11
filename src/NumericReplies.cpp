#include "Utils.hpp"

// 256
std::string RPL_ADMINME(const std::string &server) {
	return server + " :Administrative info";
}

// 257
std::string RPL_ADMINLOC1(const std::string &info) {
	return ":" + info;
}

// 258
std::string RPL_ADMINLOC2(const std::string &info) {
	return ":" + info;
}

// 259
std::string RPL_ADMINEMAIL(const std::string &info) {
	return ":" + info;
}

// 301
std::string RPL_AWAY(const std::string &nickname, const std::string &message) {
	return nickname + " :" + message;
}

// 321
std::string RPL_LISTSTART(void) {
	return "Channel :Topic";
}

// 322
std::string RPL_LIST(const std::string &channel, const std::string &visible, const std::string &topic) {
	return channel + " " + visible + " :" + topic;
}

// 323
std::string RPL_LISTEND(void) {
	return ":End of /LIST";
}

// 331
std::string RPL_NOTOPIC(const std::string &channel) {
	return channel + " :No topic is set";
}

// 332
std::string RPL_TOPIC(const std::string &channel, const std::string &topic) {
	return channel + " :" + topic;
}

// 341
std::string RPL_INVITING(const std::string &channel, const std::string &nickname) {
	return channel + " " + nickname;
}

// 351
std::string RPL_VERSION(const std::string &version, const std::string &debuglevel, const std::string &server, const std::string &comments) {
	return version + "." + debuglevel + " " + server + " :" + comments;
}

// 353
std::string RPL_NAMREPLY(const std::string &channel, const std::string &userlist) {
	return channel + " :" + userlist;
}

// 366
std::string RPL_ENDOFNAMES(const std::string &channel) {
	return channel + " :End of /NAMES list";
}

// 371
std::string RPL_INFO(const std::string &string) {
	return ":" + string;
}

// 374
std::string RPL_ENDOFINFO(void) {
	return ":End of /INFO list";
}

// 381
std::string RPL_YOUREOPER(void) {
	return ":You are now an IRC operator";
}

// 391
std::string RPL_TIME(const std::string &server, const std::string &string) {
	return server + " :" + string;
}

// 401
std::string ERR_NOSUCHNICK(const std::string &nickname) {
	return nickname + " :No such nick/channel";
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

// 422
std::string ERR_NOMOTD(void) {
	return ":MOTD File is missing" ;
}

// 423
std::string ERR_NOADMININFO(const std::string &server) {
	return server + " :No administrative info available" ;
}

// 424
std::string ERR_FILEERROR(void) {
	return ":File error doing <file op> on <file>" ;
}

// 431
std::string ERR_NONICKNAMEGIVEN(void) {
	return ":No nickname given" ;
}

// 432
std::string ERR_ERRONEUSNICKNAME(const std::string &nickname) {
	return nickname + " :Erroneus nickname" ;
}

// 433
std::string ERR_NICKNAMEINUSE(const std::string &nickname) {
	return nickname + " :Nickname is already in use" ;
}

// 436
std::string ERR_NICKCOLLISION(const std::string &nickname) {
	return nickname + " :Nickname collision KILL from <user>@<host>" ;
}

// 441
std::string ERR_USERNOTINCHANNEL(const std::string &nickname, const std::string &channel) {
	return nickname + " " + channel + " :They aren't on that channel" ;
}

// 442
std::string ERR_NOTONCHANNEL(const std::string &channel) {
	return channel + " :You're not on that channel" ;
}

// 443
std::string ERR_USERONCHANNEL(const std::string &nickname, const std::string &channel) {
	return nickname + " " + channel + " :is already on channel" ;
}

// 444
std::string ERR_NOLOGIN(const std::string &nickname) {
	return nickname + " :User not logged in" ;
}

// 445
std::string ERR_SUMMONDISABLED(void) {
	return ":SUMMON has been disabled" ;
}

// 446
std::string ERR_USERSDISABLED(void) {
	return ":USERS has been disabled" ;
}

// 451
std::string ERR_NOTREGISTERED(void) {
	return ":You have not registered" ;
}

// 461
std::string ERR_NEEDMOREPARAMS(const std::string &command) {
	return command + " :Not enough parameters" ;
}

// 462
std::string ERR_ALREADYREGISTRED(void) {
	return ":You may not reregister" ;
}

// 463
std::string ERR_NOPERMFORHOST(void) {
	return ":Your host isn't among the privileged" ;
}

// 464
std::string ERR_PASSWDMISMATCH(void) {
	return ":Password incorrect" ;
}

// 465
std::string ERR_YOUREBANNEDCREEP(void) {
	return ":You are banned from this server" ;
}

// 467
std::string ERR_KEYSET(const std::string &channel) {
	return channel + " :Channel key already set" ;
}

// 471
std::string ERR_CHANNELISFULL(const std::string &channel) {
	return channel + " :Cannot join channel (+l)" ;
}

// 472
std::string ERR_UNKNOWNMODE(const std::string &char_) {
	return char_ + " :is unknown mode char to me for <channel>" ;
}

// 473
std::string ERR_INVITEONLYCHAN(const std::string &channel) {
	return channel + " :Cannot join channel (+i)" ;
}

// 474
std::string ERR_BANNEDFROMCHAN(const std::string &channel) {
	return channel + " :Cannot join channel (+b)" ;
}

// 475
std::string ERR_BADCHANNELKEY(const std::string &channel) {
	return channel + " :Cannot join channel (+k)" ;
}

// 481
std::string ERR_NOPRIVILEGES(void) {
	return ":Permission Denied- You're not an IRC operator" ;
}

// 482
std::string ERR_CHANOPRIVSNEEDED(const std::string &channel) {
	return channel + " :You're not channel operator" ;
}

// 483
std::string ERR_CANTKILLSERVER(void) {
	return ":You cant kill a server!" ;
}

// 491
std::string ERR_NOOPERHOST(void) {
	return ":No O-lines for your host" ;
}

// 501
std::string ERR_UMODEUNKNOWNFLAG(void) {
	return ":Unknown MODE flag" ;
}

// 502
std::string ERR_USERSDONTMATCH(void) {
	return ":Cant change mode for other users" ;
}
