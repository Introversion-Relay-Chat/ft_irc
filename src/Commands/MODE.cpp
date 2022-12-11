#include "../../include/Utils.hpp"

"""
           ERR_NEEDMOREPARAMS              
		   
		   RPL_CHANNELMODEIS
           ERR_CHANOPRIVSNEEDED            
		   ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                
		   ERR_KEYSET
           RPL_BANLIST                     
		   RPL_ENDOFBANLIST
           ERR_UNKNOWNMODE     

           ERR_USERSDONTMATCH              RPL_UMODEIS
           ERR_UMODEUNKNOWNFLAG
"""
std::string MODE(const Message &message, User *sender) {
	std::string											sender_prefix;
	std::string											target;
	std::string											name;
	Channel												*channel;
	User												*user;
	char												sign;
	std::string											flags;
	std::vector<std::pair<std::string, std::string> >	responses;
	std::string						param;
	std::vector<std::string>		params;

	sender_prefix = sender->getServerPrefix();
	target = sender->getNickname();
	// ERR_NEEDMOREPARAMS
	if (message.middle.size() < 2)
		return join(sender_prefix, "461", target, ERR_NEEDMOREPARAMS(message.command));

	name = message.middle[0];
	channel = sender->getServer()->getChannelByName(name);
	user = sender->getServer()->getUserByName(name);
	flags = message.middle[1];
	// channel mode
	if (channel) {
		sign = flags[0];
		for (int i=1; i < flags.length(); i++) {
			flags[i];
			param = message.middle[i-1];
		}
		sign = ;

	}
	// user mode
	else if (user) {
		
	}
	else {
		// ERR_NOSUCHCHANNEL
		return join(sender_prefix, "403", target, ERR_NOSUCHCHANNEL(name));
	}

	return std::string();
}
