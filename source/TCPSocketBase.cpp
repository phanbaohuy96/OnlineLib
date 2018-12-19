#include "TCPSocketBase.h"


TCPSocketBase::TCPSocketBase()
{
}

TCPSocketBase::TCPSocketBase(SocketType type, const char * IpAdrr, int port)
{
	if(type == CLIENT)
		cout << currentDateTime().c_str() << " :: Starting client..." << endl;
	else
		cout << currentDateTime().c_str() << " :: Starting server..." << endl;

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
	if (skListening == INVALID_SOCKET)
	{
		STT = SocketStatus::ERRORS;
		cerr << currentDateTime().c_str() << " :: Can't create socket.. Shutting down..." << endl;
		return;
	}
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

void TCPSocketBase::SocketLoop(SOCKET clientSocket = NULL)
{
	cout << currentDateTime().c_str() << " :: Starting receive message from client..." << endl;
	if (STT == ERRORS)
	{
		cerr << currentDateTime().c_str() << " :: Server error.... Shutdown!" << endl;
		return;
	}

	char buf[1024];
	while (true)
	{
		ZeroMemory(buf, 1024);
		
		//wait for client send data
		int byteReceived = recv(m_Socket, buf, 1024, 0);
		if (byteReceived == SOCKET_ERROR)
		{
			cerr << currentDateTime().c_str() << " :: Error when receive data.... Shutdown!" << endl;
			break;
		}

		if (byteReceived == 0)
		{
			cout << currentDateTime().c_str() << " :: Client disconnected.... Shutdown!" << endl;
			break;
		}

		//Send data back to client
		send(m_Socket, buf, byteReceived + 1, 0);
		cout << currentDateTime().c_str() << " :: " << buf << endl;
	}

}

const std::string TCPSocketBase::currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];

	localtime_s(&tstruct,&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

void TCPSocketBase::Shutdown()
{
	//close clientSocket
	closesocket(m_Socket);

	//Clean wks data
	WSACleanup();
}
