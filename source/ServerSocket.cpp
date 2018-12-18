#include "ServerSocket.h"



ServerSocket::ServerSocket(SocketType type, const char *IpAdrr, int port) : TCPSocketBase(type, IpAdrr, port)
{
}


ServerSocket::~ServerSocket()
{
}
