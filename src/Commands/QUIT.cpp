#include "../../include/Utils.hpp"

std::string QUIT(const Message &message, User *sender) {
	(void) message;

	sender->getServer()->killUser(sender);
	return std::string();
}
