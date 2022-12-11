#include "../include/Utils.hpp"

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
	Server server = Server(av[1], av[2]);
	server.run(stop);
	return 0;
}
