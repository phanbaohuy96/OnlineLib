#pragma once
#include <iostream>
#include <WS2tcpip.h>
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
	TCPSocketBase(SocketType type, char *IpAdrr, int port);
	~TCPSocketBase();
	SocketStatus Sendmessage(char *message);
	SocketStatus Recievemessage(int *buffer);
	void SocketLoop();
	void CloseSocket();

private:
	WSADATA wsData;
	WORD ver;
	int wsOk;
	SocketStatus STT = OK;
	SOCKET skListening;
	struct sockaddr_in hint;
};
