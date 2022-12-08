#ifndef IRC_HPP
#define IRC_HPP

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

namespace ft {
	class Server ;
	class User ;
	class Channel;

	// User Status
	enum UserStatus {
		PASSWORD,
		REGISTER,
		ONLINE,
		DELETE
	};

	// User
	class User {

		friend class Server;
		friend class Channel;

		private:
			Server					*_server;
			UserStatus				_status;
			int						_user_socket;
			std::string				_nickname;
			std::string				_username;
			std::string				_hostname;
			int						_modes;
			std::set<std::string>	_joined_channels;

		public:
			User(int user_socket, std::string hostname, ft::Server *server);
			~User();
			
			UserStatus	getStatus(void);
			void		setStatus(UserStatus status);
			std::string	getNickname(void);
			void		setNickname(std::string nickname);
			std::string	getUsername(void);
			void		setUsername(std::string username);
			ft::Server *getServer(void);

			std::string	getServerPrefix(void);
			std::string	getUserPrefix(void);
	};

	// Channel
	class Channel {

		friend class User;
		friend class Server;

		private:
			Server					*_server;
			std::string				_channelname;
			User					*_operator;
			int						_limit;
			int						_modes;
			std::set<int>			_users;

		public:
			Channel();
			~Channel();

	};

	// Message Struct
	struct Message {
		std::string					command;
		std::vector<std::string>	middle;
		std::string					trailing;
	};

	// Server
	class Server {

		friend class User;
		friend class Channel;

		private:
			std::string							_password;
			std::string							_servername;
			int									_port;
			int									_server_socket;

			std::vector<pollfd>							_sockets;
			std::map<int, User *>						_users;
			std::map<std::string, ft::Channel *>		_channels;

			std::map<std::string, std::string(*)(const ft::Message &, User *)>	_executor;

		public:
			Server(std::string port, std::string password);
			~Server();

			std::string	getPassword(void);
			std::string getServername(void);

			void		run(bool &stop);
			void		loop(void);
			void		acceptNewUser(void);
			void		receiveMsg(int user_socket);
			Message		parseMsg(std::string message);
			void		runCommand(const Message &message, User *user);

	};

	// Utils
	void						error(std::string message, bool stop);
	std::vector<std::string>	split(std::string str, std::string delimiter);
	std::string					join(std::string sender_prefix, std::string code, std::string target, std::string message);

	// Commands
	std::string PASS(const ft::Message &message, ft::User *sender);

	// Numeric Replies
	std::string ERR_UNKNOWNCOMMAND(const std::string &command);
	std::string ERR_NEEDMOREPARAMS(const std::string &command);
	std::string ERR_ALREADYREGISTRED(void);
	std::string NumericReply(std::string sender_prefix, std::string code, std::string target, const ft::Message &message);

}

#endif
