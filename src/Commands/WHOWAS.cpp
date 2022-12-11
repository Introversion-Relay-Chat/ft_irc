#include "../../include/Utils.hpp"

std::string WHOWAS(const Message &message, User *sender) {
	std::string sender_prefix = sender->getServerPrefix();
	Server *server = sender->getServer();
  (void)sender;
  (void)server;

  // nickname이 입력되지 않은 경우, 431 ERR_NONICKNAMEGIVEN
  if (message.middle.size() < 1) {
    return join(sender_prefix, "431", sender->getNickname(), ERR_NONICKNAMEGIVEN());
  }
  std::string nickname = message.middle[0];

  // TODO: 서버에 존재하는 모든 유저를 검색하여 nickname 히스토리를 확인하고, 그 중 nickname과 일치하는 값을 results에 저장.
  // results에 저장된 값을 second에 대해 내림차순으로 정렬.
  // 정렬 후 각각의 값에 대해 314 RPL_WHOWASUSER, 312 WHOISSERVER를 응답.
  // 369 RPL_ENDOFWHOWAS를 마지막에 응답.



  // nickname 히스토리가 존재하지 않는 경우, 401 ERR_NOSUCHNICK
  return join(sender_prefix, "401", sender->getNickname(), ERR_NOSUCHNICK(nickname));
}
