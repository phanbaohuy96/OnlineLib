#pragma once
#include "TCPSocketBase.h"
class ServerSocket :
	public TCPSocketBase
{
public:
	ServerSocket(int port);
	~ServerSocket();
	TCPSocketBase::SocketStatus Listening();
	void SocketLoop();

private:
	struct fd_set master;
};

