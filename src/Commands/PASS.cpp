#include "../IRC.hpp"

std::string ft::PASS(const ft::Message &message, ft::User *sender)
{
	std::string sender_prefix = sender->getServerPrefix();
	std::string	target = sender->getNickname();

	if (message.middle.size() < 1)
		return NumericReply(sender_prefix, "461", target, message);
	if (sender->getStatus() != ft::PASSWORD)
		return NumericReply(sender_prefix, "462", target, message);

	if (sender->getServer()->getPassword() == message.middle[0])
		sender->setStatus(ft::REGISTER);
	return std::string();
}
