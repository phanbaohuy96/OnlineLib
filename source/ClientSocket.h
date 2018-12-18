#pragma once
#include "TCPSocketBase.h"
class ClientSocket :
	public TCPSocketBase
{
public:
	ClientSocket(SocketType type, char *IpAdrr, int port);
	~ClientSocket();
};

