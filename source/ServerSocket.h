#pragma once
#include "TCPSocketBase.h"
class ServerSocket :
	public TCPSocketBase
{
public:
	ServerSocket(SocketType type, char *IpAdrr, int port);
	~ServerSocket();
};

