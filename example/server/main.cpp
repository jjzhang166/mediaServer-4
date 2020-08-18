#include <iostream>
#include "server.h"
using namespace qp_Server;
int main(int argc, char **argv)
{
	Server *server = new Server();
	if (server)
	{
		server->run();
	}
	return 0;
}
