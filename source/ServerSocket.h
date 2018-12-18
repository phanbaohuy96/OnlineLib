#pragma once
#include "TCPSocketBase.h"
class ServerSocket :
	public TCPSocketBase
{
public:
	ServerSocket(SocketType type, const char *IpAdrr, int port);
	~ServerSocket();
};

