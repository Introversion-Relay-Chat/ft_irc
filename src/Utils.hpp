#ifndef UTILS_HPP
#define UTILS_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
# include <fcntl.h>
# include <csignal>
# include <string>
# include <cstdlib>
# include <map>
# include <set>
# include <vector>
# include <poll.h>
# include <unistd.h>
# include "Server.hpp"
# include "User.hpp"
# include "Channel.hpp"

# define BUFFER_SIZE	4096
# define MESSAGE_END	"\n"
# define SERVER_NAME	"tmp.server.name"

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
	PASSWORD,
	REGISTER,
	ONLINE,
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

// Commands
std::string PASS(const Message &message, User *sender);

// Numeric Replies
std::string ERR_UNKNOWNCOMMAND(const std::string &command);
std::string ERR_NEEDMOREPARAMS(const std::string &command);
std::string ERR_ALREADYREGISTRED(void);
std::string NumericReply(std::string sender_prefix, std::string code, std::string target, const Message &message);

#endif