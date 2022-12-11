#include "../../include/Utils.hpp"

std::string ADMIN(const Message &message, User *sender) {
	(void) message;
	std::string	sender_prefix = sender->getServerPrefix();
	std::string target = sender->getNickname();

	// RPL_ADMINME
	sender->getServer()->sendMsg(join(sender_prefix, "256", target, RPL_ADMINME(sender_prefix)), sender);
	// RPL_ADMINLOC1
	std::string admin_loc1 = "This is for IRC server";
	sender->getServer()->sendMsg(join(sender_prefix, "257", target, RPL_ADMINLOC1(admin_loc1)), sender);
	// RPL_ADMINLOC2
	std::string admin_loc2 = "From Introversion-Relay-Chat";
	sender->getServer()->sendMsg(join(sender_prefix, "258", target, RPL_ADMINLOC2(admin_loc2)), sender);
	// RPL_ADMINEMAIL
	std::string admin_email = "\"sichoi@student.42seoul.kr\" \"donghyun@student.42seoul.kr\" \"chaekim@student.42seoul.kr\"";
	sender->getServer()->sendMsg(join(sender_prefix, "259", target, RPL_ADMINEMAIL(admin_email)), sender);
	return std::string();
}
