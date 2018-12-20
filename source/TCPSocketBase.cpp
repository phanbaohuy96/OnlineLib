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
	//Clean wks data
	WSACleanup();
}
