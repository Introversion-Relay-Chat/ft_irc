#include "../IRC.hpp"

std::string ft::PASS(const ft::Message &message, ft::User *user, ft::Server *server)
{
	if (message.middle.size() < 1)
		return NumericReply("461", message, user);
	if (user->getStatus() != ft::PASSWORD)
		return NumericReply("462", message, user);

	if (server->getPassword() == message.middle[0])
		user->setStatus(ft::REGISTER);
	return std::string();
}
