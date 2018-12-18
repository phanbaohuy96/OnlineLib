#include "ClientSocket.h"



ClientSocket::ClientSocket(SocketType type, const char *IpAdrr, int port) : TCPSocketBase(type, IpAdrr, port)
{
}


ClientSocket::~ClientSocket()
{
}
