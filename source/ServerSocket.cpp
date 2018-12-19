#include "ServerSocket.h"



ServerSocket::ServerSocket(int port) : TCPSocketBase(SocketType::SERVER, "", port)
{
	//bind socket
	hint.sin_family = AF_INET;
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	hint.sin_port = htons(port);
	bind(skListening, (sockaddr *)&hint, sizeof(hint));
}


ServerSocket::~ServerSocket()
{
}

TCPSocketBase::SocketStatus ServerSocket::Listening()
{
	cout << currentDateTime().c_str() << " :: Starting listening client socket conection..." << endl;
	if (STT == ERRORS)
	{
		cerr << currentDateTime().c_str() << " :: Server error.... Shutdown!" << endl;
		return ERRORS;
	}
	//tell winsock the socket is for listening
	listen(skListening, SOMAXCONN);

	//wait for a connection
	int clientSize = sizeof(client);

	m_Socket = accept(skListening, (sockaddr *)&client, &clientSize);

	char host[NI_MAXHOST],		// CLient's remote name
		services[NI_MAXSERV];	// Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);		//Same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(services, NI_MAXSERV);

	if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, services, NI_MAXSERV, 0) == 0)
	{
		cout << currentDateTime().c_str() << " :: " <<  host << " connected on port " << services << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << currentDateTime().c_str() << " :: " << host << " connected on port " << ntohs(client.sin_port) << endl;
	}

	//close listening
	closesocket(skListening);

	return OK;
}
