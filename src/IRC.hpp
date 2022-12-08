#ifndef IRC_HPP
#define IRC_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <fcntl.h>
# include <csignal>
# include <string>
# include <cstdlib>
# include <map>
# include <vector>
# include <poll.h>
# include <unistd.h>

# define BUFFER_SIZE 4096
# define MESSAGE_END "\n" 

namespace ft {

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

		private:
			UserStatus		_status;
			int				_user_socket;
			std::string		_nickname;

		public:
			User(int user_socket);
			~User();

			UserStatus	getStatus(void);
			void		setStatus(UserStatus status);
			std::string	getNickname(void);
			void		setNickname(std::string nickname);
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

		private:
			std::string							_password;
			int									_port;
			int									_server_socket;
			std::map<int, User *>				_users;
			std::vector<pollfd>					_sockets;

			std::map<std::string, std::string(*)(const ft::Message &, User *, ft::Server *)>	_executor;

		public:
			Server(std::string port, std::string password);
			~Server();

			std::string	getPassword(void);
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

	// Commands
	std::string PASS(const ft::Message &message, ft::User *user, ft::Server *server);

	// Numeric Replies
	std::string ERR_UNKNOWNCOMMAND(const std::string &command);
	std::string ERR_NEEDMOREPARAMS(const std::string &command);
	std::string ERR_ALREADYREGISTRED(void);
	std::string NumericReply(std::string code, const ft::Message &message, User *user);

}

#endif
