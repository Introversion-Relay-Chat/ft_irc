#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include "Utils.hpp"

class	Server;
class	User;
struct	Message;

class Channel {

	private:
		std::string				_channelname;
		std::string				_topic;
		std::string				_key;
		std::set<int>			_operators;
		int						_limit;
		int						_mode;
		std::set<int>			_users;
		std::set<int>			_invited;
		std::set<std::string>	_banlist;

	public:
		Channel(std::string channelname, User *user);
		~Channel();

		std::string				getChannelname(void);
		std::string				getTopic(void);
		void					setTopic(std::string topic);
		std::string				getKey(void);
		void					setKey(std::string key);
		std::set<int>			getOperators(void);
		void					addOperator(User *user);
		void					addOperator(int user_socket);
		void					removeOperator(User *user);
		void					removeOperator(int user_socket);
		int						getLimit(void);
		void					setLimit(int limit);
		int						getMode(void);
		void					setMode(int mode);
		std::set<int>			getUsers(void);
		std::set<int>			getInvited(void);
		std::string				getUserList(User *user);
		int						getVisibleUsers(User *user);
		std::set<std::string>	getBanList(void);
		void					setBanMask(std::string mask);
		void					removeBanMask(std::string mask);

		void					addUser(User *user);
		void					removeUser(User *user);
		void					inviteUser(User *user);
		void					kickUser(User *user);

		bool					checkInvited(User *user);
		bool					checkVisible(User *user);
		bool					checkPrivilege(User *user);
		bool					checkOnChannel(User *user);

};

#endif