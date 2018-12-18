#include "TCPSocketBase.h"


TCPSocketBase::TCPSocketBase()
{
}

TCPSocketBase::TCPSocketBase(SocketType type, char * IpAdrr, int port)
{
	//create 
	ver = MAKEWORD(2, 2);
	wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		STT = SocketStatus::ERRORS;
		cerr << "Can't initialize winsok.. Shutting down..." << endl;
		return;
	}
	skListening = socket(AF_INET, SOCK_STREAM, 0);
	if(skListening == INVALID_SOCKET)
	{
		STT = SocketStatus::ERRORS;
		cerr << "Can't create socket.. Shutting down..." << endl;
		return;
	}

	//bind socket
	hint.sin_family = AF_INET;
	if (type == SocketType::SERVER)
		hint.sin_addr.S_un.S_addr = INADDR_ANY;
	else
		hint.sin_addr.S_un.S_addr = inet_addr(IpAdrr);
	hint.sin_port = htons(port);
	bind(skListening, (sockaddr *)&hint, sizeof(hint));
}

TCPSocketBase::~TCPSocketBase()
{
}

TCPSocketBase::SocketStatus TCPSocketBase::Sendmessage(char * message)
{
	return OK;
}

TCPSocketBase::SocketStatus TCPSocketBase::Recievemessage(int * buffer)
{
	return OK;
}

void TCPSocketBase::SocketLoop()
{
}

void TCPSocketBase::CloseSocket()
{
}
