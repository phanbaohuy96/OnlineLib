#pragma once
#include "TCPSocketBase.h"
class ClientSocket :
	public TCPSocketBase
{
public:
	ClientSocket(SocketType type, const char *IpAdrr, int port);
	~ClientSocket();
};

