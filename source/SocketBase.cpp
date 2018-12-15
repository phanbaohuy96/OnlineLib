#include "..\header\SocketBase.h"



SocketBase::SocketBase(SocketType type, string ip, int port)
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	
	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't initialize winsock! Closing...." << endl;
		return;
	}

	// create listening socket
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create socket! Closing...." << endl;
		return;
	}

	//Bind ip adress and port to socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = 30496;
	in_addr arrFocus;
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //uses inet_pton for client



}


SocketBase::~SocketBase()
{
}
