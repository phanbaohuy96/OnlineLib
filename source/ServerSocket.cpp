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
	listen_wrapper(skListening, SOMAXCONN);

	FD_ZERO_wrapper(&master);
	FD_SET_wrapper(skListening, &master);

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
		fd_set_wp copy = master;

		int socketCount = select_wrapper(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET_wp client = copy.fd_array[i];
			if (client == skListening)
			{
				//Accept a new client
				SOCKET_wp nClient = accept(skListening, nullptr, nullptr);

				//Add the new client to the list of clients
				FD_SET_wrapper(nClient, &master);

				//Send connection successfully message.
				string mess = " :: Connect successfully!!";
				send_wrapper(nClient, mess.c_str(), mess.size() + 1, 0);
				cerr << currentDateTime().c_str() << " :: Client #" << nClient << " has joined.... " << endl;
			}
			else
			{
				//Accept new message
				char buf[1024];
				ZeroMemory(buf, 1024);

				int byteReceived = recv_wrapper(client, buf, 1024, 0);

				if (byteReceived <= 0)
				{
					//Drop client
					closesocket_wrapper(client);
					cerr << currentDateTime().c_str() << " :: Client #" << client << " disconnected.... " << endl;
					FD_CLR_wrapper(client, &master);
				}else
				{
					// Send message to other clients and definitely NOT the listening socket
					for (unsigned j = 0; j < master.fd_count; j++)
					{
						SOCKET_wp outSock = master.fd_array[j];
						if (outSock != skListening && outSock != client)
						{
							ostringstream ss;
							ss << " [CLIENT #" << client << "]: " << buf ;
							string mess = ss.str();
							send_wrapper(outSock, mess.c_str(), mess.size() + 1, 0);
						}
					}
				}
			}

		}
	}

}