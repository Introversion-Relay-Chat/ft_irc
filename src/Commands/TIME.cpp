#include "../Utils.hpp"

std::string TIME(const Message &message, User *sender) {
	std::string	sender_prefix = sender->getServerPrefix();
	std::string target = sender->getNickname();
	
	return join(sender_prefix, "391", target, RPL_TIME(sender_prefix, sender->getServer()->currTime()));
}