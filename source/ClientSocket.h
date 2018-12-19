#pragma once
#include "TCPSocketBase.h"
// void bzero(void *s, size_t n);
#define bzero(s, n) memset((s), 0, (n))

// void bcopy(const void *s1, void *s2, size_t n);
#define bcopy(s1, s2, n) memmove((s2), (s1), (n))

class ClientSocket :
	public TCPSocketBase
{
public:
	ClientSocket(const char *IpAdrr, int port);
	void Recievemessage();
	void Sendmessage();
	void Shutdown();

	~ClientSocket();
private:
	SOCKET socket;
	struct hostent *server;
	struct sockaddr_in serv_addr;
};

