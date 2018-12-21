#include "ClientSocket.h"
#include <thread>
#include <string>


ClientSocket::ClientSocket(const char *IpAdrr, int port) : TCPSocketBase(SocketType::CLIENT, IpAdrr, port)
{
	hint.sin_family = AF_INET;
	InetPton(AF_INET, IpAdrr, &hint.sin_addr.s_addr);
	hint.sin_port = htons(port);

	if (connect(skListening, (struct sockaddr *)&hint, sizeof(hint)) < 0)
	{
		cerr << currentDateTime().c_str() << " :: ERROR connecting to server." << endl;
		STT = ERRORS;
		return;
	}
}

void ClientSocket::Recievemessage()
{
	if (STT == ERRORS)
	{
		cerr << currentDateTime().c_str() << " :: Client error.... Shutdown!" << endl;
		return;
	}
	else
	{
		cout << currentDateTime().c_str() << " :: Starting receive message from server..." << endl;
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
			STT = ERRORS;
			break;
		}

		if (byteReceived == 0)
		{
			cout << currentDateTime().c_str() << " :: Server disconnection.... Shutdown!" << endl;
			STT = ERRORS;
			break;
		}

		//Echo data from server
		cout << currentDateTime().c_str() << buf << "\r\n" << endl;
	}
}

void ClientSocket::MessageListening()
{
	 thread task = thread(&ClientSocket::Recievemessage, this);
	 task.detach();
};


void ClientSocket::Sendmessage()
{
	while (STT == OK)
	{
		string buf;
		getline(cin, buf);
		if (buf != "")
			send(skListening, buf.c_str() , buf.size() + 1, 0);
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
