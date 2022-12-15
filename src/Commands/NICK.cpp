#include "../../include/Utils.hpp"

std::string NICK(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();

	// nickname이 입력되지 않은 경우, 431 ERR_NONICKNAMEGIVEN
	if (message.middle.size() < 1) {
		return join(sender_prefix, "431", sender->getNickname(), ERR_NONICKNAMEGIVEN());
	}

	std::string nickname = message.middle[0];

	// nickname이 9자를 초과한 경우, 432 ERR_ERRONEUSNICKNAME
	if (nickname.length() > 9) {
		return join(sender_prefix, "432", nickname, ERR_ERRONEUSNICKNAME(nickname));
	}
	// TODO: 유효하지 않은 문자 예외 처리

	// nickname이 이미 사용중인 경우, 433 ERR_NICKNAMEINUSE
	std::map<int, User *> users = sender->getServer()->getUsers();
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++) {
		if (it->second->getNickname() == nickname) {
			return join(sender_prefix, "433", nickname, ERR_NICKNAMEINUSE(nickname));
		}
	}

	// 기존 nickname을 nick_history에 추가하고, nickname을 업데이트
	sender->reNewNickUpdateTime();
	sender->addNickHistory(sender->getNickname(), sender->getNickUpdateTime());
	sender->setNickname(nickname);

	if (sender->getStatus() == NEED_NICKNAME) {
		sender->setStatus(NEED_USERREGISTER);
	}
	return std::string();
}
