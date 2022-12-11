#ifndef USER_HPP
#define USER_HPP

#include "Utils.hpp"

class	Server;
class	Channel;
struct	Message;

class User {

	private:
		Server					*_server;
		int						_status;
		int						_user_socket;
		std::string				_nickname;
		std::string				_username;
		std::string				_hostname;
		std::string				_realname;
		int						_mode;
		std::set<std::string>	_joined;
		time_t	_login_time;

	public:
		User(int user_socket, std::string hostname, Server *server);
		~User();

		int			getStatus(void);
		void		setStatus(int status);
		std::string	getNickname(void);
		void		setNickname(std::string nickname);
		std::string	getUsername(void);
		void		setUsername(std::string username);
		std::string	getHostname(void);
		void		setHostname(std::string hostname);
		std::string	getRealname(void);
		void		setRealname(std::string realname);
		time_t getLoginTime(void);
		int			getMode(void);
		void		setMode(int mode);
		Server		*getServer(void);
		int			getUserSocket(void);
		std::set<std::string>	getJoinedChannels(void);

		std::string	getServerPrefix(void);
		std::string	getUserPrefix(void);

		void		joinChannel(std::string channel_name);
		void		leaveChannel(std::string channel_name);

		void printStatus(void);
};

#endif
