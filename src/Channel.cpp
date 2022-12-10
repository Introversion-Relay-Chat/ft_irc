#include "Channel.hpp"

Channel::Channel(std::string channelname, User *user) {
	_channelname = channelname;
	_topic = std::string();
	_key = std::string();
	_operator = user->getUserSocket();
	_limit = 100;
	_mode = 0;
	_users.insert(user->getUserSocket());
}

Channel::~Channel() {
}

std::string Channel::getChannelname(void) {
	return _channelname;
}

std::string Channel::getTopic(void) {
	return _topic;
}

void Channel::setTopic(std::string topic) {
	_topic = topic;
}

std::string Channel::getKey(void) {
	return _key;
}

void Channel::setKey(std::string key) {
	_key = key;
}

int Channel::getOperator(void) {
	return _operator;
}

void Channel::setOperator(int op) {
	_operator = op;
}

int Channel::getLimit(void) {
	return _limit;
}

void Channel::setLimit(int limit) {
	_limit = limit;
}

int Channel::getMode(void) {
	return _mode;
}

std::set<int> Channel::getUsers(void) {
	return _users;
}

std::set<int> Channel::getInvited(void) {
	return _invited;
}

std::string Channel::getUserList(User *sender) {
	std::string				userlist;
	std::map<int, User *>	server_users;

	server_users = sender->getServer()->getUsers();
	for (std::set<int>::iterator user=_users.begin(); user != _users.end(); user++) {
		if (server_users[*user]->getMode() & FLAG_USER_I) {
			continue ;
		}
		if (*user == _operator) {
			userlist += "@" + server_users[*user]->getNickname() + " ";
		}
		else {
			userlist += server_users[*user]->getNickname() + " ";
		}
	}
	return userlist;
}

void Channel::addUser(User *user) {
	_users.insert(user->getUserSocket());
}

void Channel::removeUser(User *user) {
	_users.erase(user->getUserSocket());
}

void Channel::inviteUser(User *user) {
	_invited.insert(user->getUserSocket());
}

void Channel::kickUser(User *user) {
	_invited.erase(user->getUserSocket());
	removeUser(user);
	user->leaveChannel(_channelname);
	if (_users.size() == 0) {
		user->getServer()->deleteChannel(_channelname);
	}
}

bool Channel::checkInvited(User *user) {
	if (_invited.find(user->getUserSocket()) == _invited.end()) {
		return false;
	}
	else {
		return true ;
	}
}

bool Channel::checkVisible(User *user) {
	if (_mode & FLAG_CHANNEL_P || _mode & FLAG_CHANNEL_S) {
		if (_users.find(user->getUserSocket()) == _users.end()) {
			return false;
		}
	}
	return true;
}