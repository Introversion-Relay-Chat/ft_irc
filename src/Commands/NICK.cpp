#include "../Utils.hpp"

std::string NICK(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();

	if (message.middle.size() < 1) {
		return join(sender_prefix, "431", sender->getNickname(), ERR_NONICKNAMEGIVEN());
	}

	std::string nickname = message.middle[0];

	if (nickname.length() > 9) {
		return join(sender_prefix, "432", nickname, ERR_ERRONEUSNICKNAME(nickname));
	}
	// TODO: 유효하지 않은 문자 예외 처리

	std::map<int, User *> users = sender->getServer()->getUsers();
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++) {
		if (it->second->getNickname() == nickname) {
			return join(sender_prefix, "433", nickname, ERR_NICKNAMEINUSE(nickname));
		}
	}

	sender->setNickname(nickname);
	if (sender->getStatus() != NEED_PASSWORD && sender->getStatus() == NEED_NICKNAME) {
		sender->setStatus(NEED_USERREGISTER);
	}
	return std::string();
}
