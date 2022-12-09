#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Utils.hpp"

class Channel {

	private:
		Server					*_server;
		std::string				_channelname;
		User					*_operator;
		int						_limit;
		int						_modes;
		std::set<int>			_users;

	public:
		Channel(std::string channelname);
		~Channel();

};

#endif