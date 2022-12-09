#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Utils.hpp"

class Channel {

	private:
		Server					*_server;
		std::string				_channelname;
		std::string				_topic;
		std::string				_key;
		int						_operator;
		int						_limit;
		int						_mode;
		std::set<int>			_users;
		std::set<int>			_invited;

	public:
		Channel(std::string channelname, User *user);
		~Channel();

		std::string				getChannelname(void);
		std::string				getTopic(void);
		void					setTopic(std::string topic);
		std::string				getKey(void);
		void					setKey(std::string key);
		int						getOperator(void);
		void					setOperator(int op);
		int						getLimit(void);
		void					setLimit(int limit);
		int						getMode(void);
		std::set<int>			getUsers(void);
		std::set<int>			getInvited(void);

		void					addUser(User *user);
		void					removeUser(User *user);

};

#endif