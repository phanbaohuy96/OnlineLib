#include "ServerSocket.h"

int main()
{
	const char *ipAdrr = "";
	ServerSocket *server = new ServerSocket(ServerSocket::SERVER, ipAdrr, 25643);

	server->Listening();

	server->SocketLoop();

	server->Shutdown();

	return 0;
}