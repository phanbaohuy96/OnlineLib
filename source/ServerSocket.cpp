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

	FD_ZERO(&master);
	FD_SET(skListening, &master);

	return OK;
}

void ServerSocket::SocketLoop()
{
	cout << currentDateTime().c_str() << " :: Starting receive message from client..." << endl;
	if (STT == ERRORS)
	{
		cerr << currentDateTime().c_str() << " :: Server error.... Shutdown!" << endl;
		return;
	}

	while (true)
	{
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET client = copy.fd_array[i];
			if (client == skListening)
			{
				//Accept a new client
				SOCKET nClient = accept(skListening, nullptr, nullptr);

				//Add the new client to the list of clients
				FD_SET(nClient, &master);

				//Send connection successfully message.
				string mess = " :: Connect successfully!!";
				send(nClient, mess.c_str(), mess.size() + 1, 0);
				cerr << currentDateTime().c_str() << " :: Client #" << nClient << " has joined.... " << endl;
			}
			else
			{
				//Accept new message
				char buf[1024];
				ZeroMemory(buf, 1024);

				int byteReceived = recv(client, buf, 1024, 0);

				if (byteReceived <= 0)
				{
					//Drop client
					closesocket(client);
					cerr << currentDateTime().c_str() << " :: Client #" << client << " disconnected.... " << endl;
					FD_CLR(client, &master);
				}else
				{
					// Send message to other clients and definitely NOT the listening socket
					for (unsigned j = 0; j < master.fd_count; j++)
					{
						SOCKET outSock = master.fd_array[j];
						if (outSock != skListening && outSock != client)
						{
							ostringstream ss;
							ss << " [CLIENT #" << client << "]: " << buf ;
							string mess = ss.str();
							send(outSock, mess.c_str(), mess.size() + 1, 0);
						}
					}
				}
			}

		}
	}

}