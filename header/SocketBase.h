#pragma once
#include <iostream>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class SocketBase
{


private:
	SOCKET listening;

public:
	enum SocketType
	{
		SERVER,
		CLIENT
	};

	SocketBase(SocketType type, string ip, int port);


	~SocketBase();
};

