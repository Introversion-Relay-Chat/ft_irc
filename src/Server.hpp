#ifndef SERVER_HPP
#define SERVER_HPP

#include "Utils.hpp"

class User;
class Channel;
struct Message;

class Server {

	private:
		std::string							_password;
		std::string							_servername;
		int									_port;
		int									_server_socket;

		std::vector<pollfd>					_sockets;
		std::map<int, User *>				_users;
		std::map<std::string, Channel *>	_channels;

		std::map<std::string, std::string(*)(const Message &, User *)>	_executor;

	public:
		Server(std::string port, std::string password);
		~Server();

		std::string							getPassword(void);
		std::string							getServername(void);
		std::map<std::string, Channel *>	getChannels(void);
		std::map<int, User *>				getUsers();

		void		run(bool &stop);
		void		loop(void);
		void		acceptNewUser(void);
		void		receiveMsg(int user_socket);
		Message		parseMsg(std::string message);
		void		runCommand(const Message &message, User *user);
		void		sendMsg(const std::string &message, User *user);

		void		createChannel(std::string channel_name, User *user);

};

#endif