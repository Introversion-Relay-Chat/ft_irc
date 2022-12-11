#ifndef UTILS_HPP
#define UTILS_HPP

#ifndef DEBUG
#define DEBUG 0
#endif

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
# include <sstream>
# include <fcntl.h>
# include <csignal>
# include <string>
# include <cstdlib>
# include <map>
# include <set>
# include <vector>
# include <poll.h>
# include <unistd.h>
# include <ctime>
# include "Server.hpp"
# include "User.hpp"
# include "Channel.hpp"

# define MAX_CHANNEL	10
# define BUFFER_SIZE	4096
# define MESSAGE_END	"\r\n"
# define SERVER_NAME	"tmp.server.name"
# define SERVER_VERSION	"2.8"
# define ADMIN_HOST		"127.0.0.1"
# define ADMIN_PASSWORD	"pass"

# define FLAG_CHANNEL_O	1
# define FLAG_CHANNEL_P	2
# define FLAG_CHANNEL_S	4
# define FLAG_CHANNEL_I	8
# define FLAG_CHANNEL_T	16
# define FLAG_CHANNEL_N	32
# define FLAG_CHANNEL_L	64
# define FLAG_CHANNEL_B	128
# define FLAG_CHANNEL_K	256
# define FLAG_USER_I	1
# define FLAG_USER_O	2

// User Status
enum UserStatus {
	NEED_PASSWORD,
	NEED_NICKNAME,
	NEED_USERREGISTER,
	REGISTERED,
	DELETE
};

// Message Struct
struct Message {
	std::string					command;
	std::vector<std::string>	middle;
	std::string					trailing;
};

// Utils
void						error(std::string message, bool stop);
std::vector<std::string>	split(std::string str, std::string delimiter);
std::string					join(std::string sender_prefix, std::string code, std::string target, std::string message);
std::string					toString(int var);
std::ostream& operator<<(std::ostream& os, const Message& message);

// Commands
std::string PASS(const Message &message, User *sender);
std::string NICK(const Message &message, User *sender);
std::string USER(const Message &message, User *sender);
std::string OPER(const Message &message, User *sender);
std::string QUIT(const Message &message, User *sender);
std::string JOIN(const Message &message, User *sender);
std::string PART(const Message &message, User *sender);
std::string TOPIC(const Message &message, User *sender);
std::string NAMES(const Message &message, User *sender);
std::string LIST(const Message &message, User *sender);
std::string INVITE(const Message &message, User *sender);
std::string KICK(const Message &message, User *sender);
std::string VERSION(const Message &message, User *sender);
std::string TIME(const Message &message, User *sender);
std::string ADMIN(const Message &message, User *sender);
std::string INFO(const Message &message, User *sender);
std::string KILL(const Message &message, User *sender);
std::string PRIVMSG(const Message &message, User *sender);
std::string NOTICE(const Message &message, User *sender);

// Numeric Replies
std::string RPL_TRACELINK(const std::string &version, const std::string &debuglevel, const std::string &server, const std::string &nextserver, const std::string &info);
std::string RPL_TRACECONNECTING(const std::string &server);
std::string RPL_TRACEHANDSHAKE(const std::string &server);
std::string RPL_TRACEUNKNOWN(const std::string &server);
std::string RPL_TRACEOPERATOR(const std::string &server);
std::string RPL_TRACEUSER(const std::string &server);
std::string RPL_TRACESERVER(const std::string &server, const std::string &hopcount, const std::string &info);
std::string RPL_TRACENEWTYPE(const std::string &newtype, const std::string &clientname);
std::string RPL_STATSLINKINFO(const std::string &linkname, const std::string &sendq, const std::string &sentmessages, const std::string &sentbytes, const std::string &receivedmessages, const std::string &receivedbytes, const std::string &timeopen);
std::string RPL_STATSCOMMANDS(const std::string &command, const std::string &count, const std::string &bytecount, const std::string &remotecount);
std::string RPL_STATSCLINE(const std::string &host, const std::string &name, const std::string &port, const std::string &class_);
std::string RPL_STATSNLINE(const std::string &host, const std::string &name, const std::string &port, const std::string &class_);
std::string RPL_STATSILINE(const std::string &host, const std::string &name, const std::string &port, const std::string &class_);
std::string RPL_STATSKLINE(const std::string &host, const std::string &name, const std::string &port, const std::string &class_);
std::string RPL_STATSYLINE(const std::string &class_, const std::string &pingfrequency, const std::string &connectfrequency, const std::string &maxconnects);
std::string RPL_ENDOFSTATS(const std::string &query);
std::string RPL_UMODEIS(const std::string &mode);
std::string RPL_STATSLLINE(const std::string &hostmask, const std::string &servername, const std::string &maxdepth);
std::string RPL_STATSUPTIME(const std::string &uptime);
std::string RPL_STATSOLINE(const std::string &hostmask, const std::string &name);
std::string RPL_STATSHLINE(const std::string &hostmask, const std::string &servername);
std::string RPL_LUSERCLIENT(const std::string &users, const std::string &servers, const std::string &services);
std::string RPL_LUSEROP(const std::string &operators);
std::string RPL_LUSERUNKNOWN(const std::string &unknown);
std::string RPL_LUSERCHANNELS(const std::string &channels);
std::string RPL_LUSERME(const std::string &clients, const std::string &servers);
std::string RPL_ADMINME(const std::string &server);
std::string RPL_ADMINLOC1(const std::string &info);
std::string RPL_ADMINLOC2(const std::string &info);
std::string RPL_ADMINEMAIL(const std::string &info);
std::string RPL_TRACELOG(const std::string &loglevel, const std::string &debuglevel);
std::string RPL_NONE(void);
std::string RPL_AWAY(const std::string &nickname, const std::string &message);
std::string RPL_UNAWAY(void);
std::string RPL_NOWAWAY(void);
std::string RPL_WHOISUSER(const std::string &nickname, const std::string &username, const std::string &host, const std::string &realname);
std::string RPL_WHOISSERVER(const std::string &nickname, const std::string &server, const std::string &serverinfo);
std::string RPL_WHOISOPERATOR(const std::string &nickname);
std::string RPL_WHOWASUSER(const std::string &nickname, const std::string &username, const std::string &host, const std::string &realname);
std::string RPL_ENDOFWHO(const std::string &name);
std::string RPL_WHOISIDLE(const std::string &nickname, const std::string &seconds, const std::string &signon);
std::string RPL_ENDOFWHOIS(const std::string &nickname);
std::string RPL_WHOISCHANNELS(const std::string &nickname, const std::string &channels);
std::string RPL_LISTSTART(void);
std::string RPL_LIST(const std::string &channel, const std::string &visible, const std::string &topic);
std::string RPL_LISTEND(void);
std::string RPL_CHANNELMODEIS(const std::string &channel, const std::string &mode);
std::string RPL_NOTOPIC(const std::string &channel);
std::string RPL_TOPIC(const std::string &channel, const std::string &topic);
std::string RPL_INVITING(const std::string &channel, const std::string &nickname);
std::string RPL_SUMMONING(const std::string &user);
std::string RPL_VERSION(const std::string &version, const std::string &debuglevel, const std::string &server, const std::string &comments);
std::string RPL_WHOREPLY(const std::string &channel, const std::string &user, const std::string &host, const std::string &server, const std::string &nickname, const std::string &hops, const std::string &realname);
std::string RPL_NAMREPLY(const std::string &channel, const std::string &userlist);
std::string RPL_LINKS(const std::string &mask, const std::string &server, const std::string &hopcount, const std::string &serverinfo);
std::string RPL_ENDOFLINKS(const std::string &mask);
std::string RPL_ENDOFNAMES(const std::string &channel);
std::string RPL_BANLIST(const std::string &channel, const std::string &banmask);
std::string RPL_ENDOFBANLIST(const std::string &channel);
std::string RPL_ENDOFWHOWAS(const std::string &nickname);
std::string RPL_INFO(const std::string &string);
std::string RPL_MOTD(const std::string &string);
std::string RPL_ENDOFINFO(void);
std::string RPL_MOTDSTART(const std::string &server);
std::string RPL_ENDOFMOTD(void);
std::string RPL_YOUREOPER(void);
std::string RPL_REHASHING(const std::string &configfile);
std::string RPL_TIME(const std::string &server, const std::string &string);
std::string RPL_USERSSTART(void);
std::string RPL_USERS(const std::string &username, const std::string &ttyline, const std::string &hostname);
std::string RPL_ENDOFUSERS(void);
std::string RPL_NOUSERS(void);
std::string ERR_NOSUCHNICK(const std::string &nickname);
std::string ERR_NOSUCHSERVER(const std::string &server);
std::string ERR_NOSUCHCHANNEL(const std::string &channel);
std::string ERR_CANNOTSENDTOCHAN(const std::string &channel);
std::string ERR_TOOMANYCHANNELS(const std::string &channel);
std::string ERR_WASNOSUCHNICK(const std::string &nickname);
std::string ERR_TOOMANYTARGETS(const std::string &target);
std::string ERR_NOSUCHSERVICE(const std::string &service);
std::string ERR_NOORIGIN(void);
std::string ERR_NORECIPIENT(std::string command);
std::string ERR_NOTEXTTOSEND(void);
std::string ERR_NOTOPLEVEL(const std::string &mask);
std::string ERR_WILDTOPLEVEL(const std::string &mask);
std::string ERR_UNKNOWNCOMMAND(const std::string &command);
std::string ERR_NOMOTD(void);
std::string ERR_NOADMININFO(const std::string &server);
std::string ERR_FILEERROR(void);
std::string ERR_NONICKNAMEGIVEN(void);
std::string ERR_ERRONEUSNICKNAME(const std::string &nickname);
std::string ERR_NICKNAMEINUSE(const std::string &nickname);
std::string ERR_NICKCOLLISION(const std::string &nickname);
std::string ERR_USERNOTINCHANNEL(const std::string &nickname, const std::string &channel);
std::string ERR_NOTONCHANNEL(const std::string &channel);
std::string ERR_USERONCHANNEL(const std::string &nickname, const std::string &channel);
std::string ERR_NOLOGIN(const std::string &nickname);
std::string ERR_SUMMONDISABLED(void);
std::string ERR_USERSDISABLED(void);
std::string ERR_NOTREGISTERED(void);
std::string ERR_NEEDMOREPARAMS(const std::string &command);
std::string ERR_ALREADYREGISTRED(void);
std::string ERR_NOPERMFORHOST(void);
std::string ERR_PASSWDMISMATCH(void);
std::string ERR_YOUREBANNEDCREEP(void);
std::string ERR_KEYSET(const std::string &channel);
std::string ERR_CHANNELISFULL(const std::string &channel);
std::string ERR_UNKNOWNMODE(const std::string &char_);
std::string ERR_INVITEONLYCHAN(const std::string &channel);
std::string ERR_BANNEDFROMCHAN(const std::string &channel);
std::string ERR_BADCHANNELKEY(const std::string &channel);
std::string ERR_NOPRIVILEGES(void);
std::string ERR_CHANOPRIVSNEEDED(const std::string &channel);
std::string ERR_CANTKILLSERVER(void);
std::string ERR_NOOPERHOST(void);
std::string ERR_UMODEUNKNOWNFLAG(void);
std::string ERR_USERSDONTMATCH(void);

#endif
