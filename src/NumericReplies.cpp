#include "Utils.hpp"

// ---------------------------- Command Responses ----------------------------
// 200
std::string RPL_TRACELINK(const std::string &version, const std::string &debuglevel, const std::string &server, const std::string &nextserver, const std::string &info) {
	return "Link " + version + " " + debuglevel + " " + server + " " + nextserver + " " + info ;
}

// 201
std::string RPL_TRACECONNECTING(const std::string &server) {
	return "Try. " + server ;
}

// 202
std::string RPL_TRACEHANDSHAKE(const std::string &server) {
	return "H.S. " + server ;
}

// 203
std::string RPL_TRACEUNKNOWN(const std::string &server) {
	return "???? " + server ;
}

// 204
std::string RPL_TRACEOPERATOR(const std::string &server) {
	return "Oper " + server ;
}

// 205
std::string RPL_TRACEUSER(const std::string &server) {
	return "User " + server ;
}

// 206
std::string RPL_TRACESERVER(const std::string &server, const std::string &hopcount, const std::string &info) {
	return "Serv " + server + " " + hopcount + "S " + info ;
}

// 208
std::string RPL_TRACENEWTYPE(const std::string &newtype, const std::string &clientname) {
	return newtype + " 0 " + clientname ;
}

// 211
std::string RPL_STATSLINKINFO(const std::string &linkname, const std::string &sendq, const std::string &sentmessages, const std::string &sentbytes, const std::string &receivedmessages, const std::string &receivedbytes, const std::string &timeopen) {
	return linkname + " " + sendq + " " + sentmessages + " " + sentbytes + " " + receivedmessages + " " + receivedbytes + " " + timeopen ;
}

// 212
std::string RPL_STATSCOMMANDS(const std::string &command, const std::string &count, const std::string &bytecount, const std::string &remotecount) {
	return command + " " + count + " " + bytecount + " " + remotecount ;
}

// 213
std::string RPL_STATSCLINE(const std::string &host, const std::string &name, const std::string &port, const std::string &class_) {
	return "C " + host + " * " + name + " " + port + " " + class_ ;
}

// 214
std::string RPL_STATSNLINE(const std::string &host, const std::string &name, const std::string &port, const std::string &class_) {
	return "N " + host + " * " + name + " " + port + " " + class_ ;
}

// 215
std::string RPL_STATSILINE(const std::string &host, const std::string &name, const std::string &port, const std::string &class_) {
	return "I " + host + " * " + name + " " + port + " " + class_ ;
}

// 216
std::string RPL_STATSKLINE(const std::string &host, const std::string &name, const std::string &port, const std::string &class_) {
	return "K " + host + " * " + name + " " + port + " " + class_ ;
}

// 218
std::string RPL_STATSYLINE(const std::string &class_, const std::string &pingfrequency, const std::string &connectfrequency, const std::string &maxconnects) {
	return "Y " + class_ + " " + pingfrequency + " " + connectfrequency + " " + maxconnects ;
}

// 219
std::string RPL_ENDOFSTATS(const std::string &query) {
	return query + " :End of /STATS report" ;
}

// 221
std::string RPL_UMODEIS(const std::string &mode) {
	return mode ;
}

// 241
std::string RPL_STATSLLINE(const std::string &hostmask, const std::string &servername, const std::string &maxdepth) {
	return "L " + hostmask + " * " + servername + " " + maxdepth ;
}

// 242
std::string RPL_STATSUPTIME(const std::string &uptime) {
	return ":Server Up " + uptime ;
}

// 243
std::string RPL_STATSOLINE(const std::string &hostmask, const std::string &name) {
	return "O " + hostmask + " * " + name ;
}

// 244
std::string RPL_STATSHLINE(const std::string &hostmask, const std::string &servername) {
	return "H " + hostmask + " * " + servername ;
}

// 251
std::string RPL_LUSERCLIENT(const std::string &users, const std::string &servers, const std::string &services) {
	(void)services;
	return ":There are " + users + " users and " + servers + " servers" ;
}

// 252
std::string RPL_LUSEROP(const std::string &operators) {
	return operators + " :operator(s) online" ;
}

// 253
std::string RPL_LUSERUNKNOWN(const std::string &unknown) {
	return unknown + " :unknown connection(s)" ;
}

// 254
std::string RPL_LUSERCHANNELS(const std::string &channels) {
	return channels + " :channels formed" ;
}

// 255
std::string RPL_LUSERME(const std::string &clients, const std::string &servers) {
	return ":I have " + clients + " clients and " + servers + " servers" ;
}

// 256
std::string RPL_ADMINME(const std::string &server) {
	return server + " :Administrative info" ;
}

// 257
std::string RPL_ADMINLOC1(const std::string &info) {
	return ":" + info ;
}

// 258
std::string RPL_ADMINLOC2(const std::string &info) {
	return ":" + info ;
}

// 259
std::string RPL_ADMINEMAIL(const std::string &info) {
	return ":" + info ;
}

// 261
std::string RPL_TRACELOG(const std::string &loglevel, const std::string &debuglevel) {
	return "File " + loglevel + " " + debuglevel ;
}

// 300
std::string RPL_NONE(void) {
	return ":Nobody logged in" ;
}

// 301
std::string RPL_AWAY(const std::string &nickname, const std::string &message) {
	return nickname + " :" + message ;
}

// 305
std::string RPL_UNAWAY(void) {
	return ":You are no longer marked as being away" ;
}

// 306
std::string RPL_NOWAWAY(void) {
	return ":You have been marked as being away" ;
}

// 311
std::string RPL_WHOISUSER(const std::string &nickname, const std::string &username, const std::string &host, const std::string &realname) {
	return nickname + " " + username + " " + host + " * :" + realname ;
}

// 312
std::string RPL_WHOISSERVER(const std::string &nickname, const std::string &server, const std::string &serverinfo) {
	return nickname + " " + server + " :" + serverinfo ;
}

// 313
std::string RPL_WHOISOPERATOR(const std::string &nickname) {
	return nickname + " :is an IRC operator" ;
}

// 314
std::string RPL_WHOWASUSER(const std::string &nickname, const std::string &username, const std::string &host, const std::string &realname) {
	return nickname + " " + username + " " + host + " * :" + realname ;
}

// 315
std::string RPL_ENDOFWHO(const std::string &name) {
	return name + " :End of WHO list" ;
}

// 317
std::string RPL_WHOISIDLE(const std::string &nickname, const std::string &seconds, const std::string &signon) {
	return nickname + " " + seconds + " :" + signon ;
}

// 318
std::string RPL_ENDOFWHOIS(const std::string &nickname) {
	return nickname + " :End of WHOIS list" ;
}

// 319
std::string RPL_WHOISCHANNELS(const std::string &nickname, const std::string &channels) {
	return nickname + " :" + channels ;
}

// 321
std::string RPL_LISTSTART(void) {
	return "Channel :Users  Name" ;
}

// 322
std::string RPL_LIST(const std::string &channel, const std::string &visible, const std::string &topic) {
	return channel + " " + visible + " :" + topic ;
}

// 323
std::string RPL_LISTEND(void) {
	return ":End of LIST" ;
}

// 324
std::string RPL_CHANNELMODEIS(const std::string &channel, const std::string &mode) {
	return channel + " " + mode ;
}

// 331
std::string RPL_NOTOPIC(const std::string &channel) {
	return channel + " :No topic is set" ;
}

// 332
std::string RPL_TOPIC(const std::string &channel, const std::string &topic) {
	return channel + " :" + topic ;
}

// 341
std::string RPL_INVITING(const std::string &channel, const std::string &nickname) {
	return nickname + " " + channel ;
}

// 342
std::string RPL_SUMMONING(const std::string &user) {
	return user + " :Summoning user to IRC" ;
}

// 351
std::string RPL_VERSION(const std::string &version, const std::string &debuglevel, const std::string &server, const std::string &comments) {
	return version + " " + debuglevel + " " + server + " :" + comments ;
}

// 352
std::string RPL_WHOREPLY(const std::string &channel, const std::string &user, const std::string &host, const std::string &server, const std::string &nickname, const std::string &hops, const std::string &realname) {
	return channel + " " + user + " " + host + " " + server + " " + nickname + " " + hops + " :" + realname ;
}

// 353
std::string RPL_NAMREPLY(const std::string &channel, const std::string &userlist) {
	return "= " + channel + " :" + userlist ;
}

// 364
std::string RPL_LINKS(const std::string &mask, const std::string &server, const std::string &hopcount, const std::string &serverinfo) {
	return mask + " " + server + " " + hopcount + " :" + serverinfo ;
}

// 365
std::string RPL_ENDOFLINKS(const std::string &mask) {
	return mask + " :End of LINKS list" ;
}

// 366
std::string RPL_ENDOFNAMES(const std::string &channel) {
	return channel + " :End of NAMES list" ;
}

// 367
std::string RPL_BANLIST(const std::string &channel, const std::string &banmask) {
	return channel + " " + banmask ;
}

// 368
std::string RPL_ENDOFBANLIST(const std::string &channel) {
	return channel + " :End of channel ban list" ;
}

// 369
std::string RPL_ENDOFWHOWAS(const std::string &nickname) {
	return nickname + " :End of WHOWAS" ;
}

// 371
std::string RPL_INFO(const std::string &string) {
	return ":" + string ;
}

// 372
std::string RPL_MOTD(const std::string &string) {
	return ":" + string ;
}

// 374
std::string RPL_ENDOFINFO(void) {
	return ":End of INFO list" ;
}

// 375
std::string RPL_MOTDSTART(const std::string &server) {
	return "- " + server + " Message of the day - " ;
}

// 376
std::string RPL_ENDOFMOTD(void) {
	return ":End of MOTD command" ;
}

// 381
std::string RPL_YOUREOPER(void) {
	return ":You are now an IRC operator" ;
}

// 382
std::string RPL_REHASHING(const std::string &configfile) {
	return configfile + " :Rehashing" ;
}

// 391
std::string RPL_TIME(const std::string &server, const std::string &string) {
	return server + " :" + string ;
}

// 392
std::string RPL_USERSSTART(void) {
	return ":UserID   Terminal  Host" ;
}

// 393
std::string RPL_USERS(const std::string &username, const std::string &ttyline, const std::string &hostname) {
	return username + " " + ttyline + " " + hostname ;
}

// 394
std::string RPL_ENDOFUSERS(void) {
	return ":End of users" ;
}

// 395
std::string RPL_NOUSERS(void) {
	return ":Nobody logged in" ;
}

// ---------------------------- Error Replies ----------------------------

// 401
std::string ERR_NOSUCHNICK(const std::string &nickname) {
	return nickname + " :No such nick/channel" ;
}

// 402
std::string ERR_NOSUCHSERVER(const std::string &server) {
	return server + " :No such server" ;
}

// 403
std::string ERR_NOSUCHCHANNEL(const std::string &channel) {
	return channel + " :No such channel" ;
}

// 404
std::string ERR_CANNOTSENDTOCHAN(const std::string &channel) {
	return channel + " :Cannot send to channel" ;
}

// 405
std::string ERR_TOOMANYCHANNELS(const std::string &channel) {
	return channel + " :You have joined too many channels" ;
}

// 406
std::string ERR_WASNOSUCHNICK(const std::string &nickname) {
	return nickname + " :There was no such nickname" ;
}

// 407
std::string ERR_TOOMANYTARGETS(const std::string &target) {
	return target + " :Duplicate recipients. No message delivered" ;
}

// 408
std::string ERR_NOSUCHSERVICE(const std::string &service) {
	return service + " :No such service" ;
}

// 409
std::string ERR_NOORIGIN(void) {
	return ":No origin specified" ;
}

// 411
std::string ERR_NORECIPIENT(void) {
	return ":No recipient given (PRIVMSG)" ;
}

// 412
std::string ERR_NOTEXTTOSEND(void) {
	return ":No text to send" ;
}

// 413
std::string ERR_NOTOPLEVEL(const std::string &mask) {
	return mask + " :No toplevel domain specified" ;
}

// 414
std::string ERR_WILDTOPLEVEL(const std::string &mask) {
	return mask + " :Wildcard in toplevel domain" ;
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
