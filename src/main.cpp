#include "IRC.hpp"

bool stop = false;

void handler(int) { 
	stop = true;
}

int main(int ac, char **av)
{
	if (ac != 3) {
		std::cerr << "./ircserv <port> <password>" << std::endl;
		return 1;
	}

	signal(SIGINT, handler);
	ft::Server server = ft::Server(av[1], av[2]);
	server.run(stop);
	return 0;
}
