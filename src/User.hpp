#ifndef USER_HPP
#define USER_HPP

#include "Utils.hpp"

class Server;
struct Message;

class User {

	private:
		Server					*_server;
		int						_status;
		int						_user_socket;
		std::string				_nickname;
		std::string				_username;
		std::string				_hostname;
		// int						_modes;
		std::set<std::string>	_joined;

	public:
		User(int user_socket, std::string hostname, Server *server);
		~User();
		
		int			getStatus(void);
		void		setStatus(int status);
		std::string	getNickname(void);
		void		setNickname(std::string nickname);
		std::string	getUsername(void);
		void		setUsername(std::string username);
		Server		*getServer(void);
		int			getUserSocket(void);

		std::string	getServerPrefix(void);
		std::string	getUserPrefix(void);

		void		joinChannel(std::string channel_name);
		void		leaveChannel(std::string channel_name);

};

#endif
