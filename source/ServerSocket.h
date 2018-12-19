#pragma once
#include "TCPSocketBase.h"
class ServerSocket :
	public TCPSocketBase
{
public:
	ServerSocket(int port);
	~ServerSocket();
	TCPSocketBase::SocketStatus Listening();

private:
	SOCKET * clientSocketList;
};

