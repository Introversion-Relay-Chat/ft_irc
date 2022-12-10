#include "../Utils.hpp"

std::string VERSION(const Message &message, User *sender) {
	std::string	sender_prefix = sender->getServerPrefix();
	std::string target = sender->getNickname();
	std::string comments = "Server named " + sender_prefix + "'s version is " + sender->getServer()->getServerVersion() + ".0";

	return join(sender_prefix, "351", target, RPL_VERSION(sender->getServer()->getServerVersion(), "0", sender_prefix, comments));
}