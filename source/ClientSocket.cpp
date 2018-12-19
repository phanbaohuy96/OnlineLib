#include "ClientSocket.h"



ClientSocket::ClientSocket(const char *IpAdrr, int port) : TCPSocketBase(SocketType::CLIENT, IpAdrr, port)
{
	hint.sin_family = AF_INET;
	InetPton(AF_INET, IpAdrr, &hint.sin_addr.s_addr);
	hint.sin_port = htons(port);
	bind(socket, (sockaddr *)&hint, sizeof(hint));

	if (connect(skListening, (struct sockaddr *)&hint, sizeof(hint)) < 0)
	{
		cerr << currentDateTime().c_str() << " :: ERROR connecting to server." << endl;
		STT = ERRORS;
		return;
	}

	//close socket bridge
	closesocket(socket);
}

void ClientSocket::Recievemessage()
{
	cout << currentDateTime().c_str() << " :: Starting receive message from server..." << endl;
	if (STT == ERRORS)
	{
		cerr << currentDateTime().c_str() << " :: Client error.... Shutdown!" << endl;
		return;
	}

	char buf[1024];
	while (true)
	{
		ZeroMemory(buf, 1024);

		//wait for client send data
		int byteReceived = recv(skListening, buf, 1024, 0);
		if (byteReceived == SOCKET_ERROR)
		{
			cerr << currentDateTime().c_str() << " :: Error in when receive data.... Shutdown!" << endl;
			break;
		}

		if (byteReceived == 0)
		{
			cout << currentDateTime().c_str() << " :: Client disconnection.... Shutdown!" << endl;
			break;
		}

		//Echo data from server
		char buf_1[1024]; 
		buf_1[0] = 0;
		strcat_s(buf_1, buf);
		cout << buf_1 << endl;
	}
}

void ClientSocket::Sendmessage()
{
	while (STT == OK)
	{
		char buffer[1024];
		cout << currentDateTime().c_str() << " :: Client: ";
		fgets(buffer, 1024, stdin);
		send(skListening, buffer, sizeof(buffer) + 1, 0);
	}
}

void ClientSocket::Shutdown()
{
	//close socket
	closesocket(skListening);

	//Clean wks data
	WSACleanup();
}



ClientSocket::~ClientSocket()
{
}
