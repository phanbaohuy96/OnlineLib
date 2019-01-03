#pragma once
#include <iostream>
#include "SocketWrapper.h"
#include <time.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class TCPSocketBase
{
public:
	enum SocketType
	{
		SERVER,
		CLIENT
	};

	enum SocketStatus
	{
		ERRORS,
		OK
	};

	TCPSocketBase();
	TCPSocketBase(SocketType type, const char *IpAdrr, int port);
	~TCPSocketBase();
	SocketStatus Sendmessage(char *message);
	SocketStatus Recievemessage(int *buffer);
	const std::string currentDateTime();
	void Shutdown();

protected:
	WSADATA_wp wsData;
	WORD_wp ver;
	int wsOk;
	SocketStatus STT = OK;
	sockaddr_in_wp hint, client;
	SOCKET_wp skListening;
};

