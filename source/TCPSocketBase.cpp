#include "TCPSocketBase.h"


TCPSocketBase::TCPSocketBase()
{
}

TCPSocketBase::TCPSocketBase(SocketType type, const char * IpAdrr, int port)
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
		InetPton(AF_INET, IpAdrr, &hint.sin_addr.s_addr);
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
	if (STT == ERRORS)
	{
		cerr << "Server error.... Shutdown!" << endl;
		return;
	}

	char buf[1024];
	while (true)
	{
		ZeroMemory(buf, 1024);
		
		//wait for client send data
		int byteReceived = recv(clientSocket, buf, 1024, 0);
		if (byteReceived == SOCKET_ERROR)
		{
			cerr << "Error in when receive data.... Maybe must shutdown!" << endl;
			break;
		}

		if (byteReceived == 0)
		{
			cout << "Client disconnection.... Maybe must shutdown!" << endl;
			break;
		}

		//Send data back to client
		send(clientSocket, buf, byteReceived + 1, 0);
	}

	delete[1024] buf;
}

void TCPSocketBase::Shutdown()
{
	//close clientSocket
	closesocket(clientSocket);

	//Clean wks data
	WSACleanup();
}

TCPSocketBase::SocketStatus TCPSocketBase::Listening()
{
	if (STT == ERRORS)
	{
		cerr << "Server error.... Shutdown!" << endl;
		return;
	}
	//tell winsock the socket is for listening
	listen(skListening, SOMAXCONN);

	//wait for a connection
	int clientSize = sizeof(client);

	clientSocket = accept(skListening, (sockaddr *)&client, &clientSize);

	char host[NI_MAXHOST],		// CLient's remote name
		 services[NI_MAXSERV];	// Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);		//Same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(services, NI_MAXSERV);

	if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, services, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << services << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	}

	//close listening
	closesocket(skListening);

	return OK;
}
