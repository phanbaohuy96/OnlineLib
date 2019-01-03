#pragma once
#if ANDROID
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#else
#include <WS2tcpip.h>
#endif

#if ANDROID
//datatype
typedef SOCKET SOCKET_wp;
typedef WSADATA WSADATA_wp;
typedef WORD WORD_wp;
typedef struct sockaddr_in sockaddr_in_wp;
typedef struct fd_set fd_set_wp;
typedef const struct timeval timeval_wp;
typedef struct sockaddr_in sockaddr_in_wp;
typedef USHORT USHORT_wp;
typedef struct sockaddr sockaddr_wp;

//func
#define FD_SET_wrapper(sk, s) FD_SET(sk, s)
#define FD_ZERO_wrapper(s) FD_ZERO(s)
#define FD_CLR_wrapper(sk, fd_s) FD_CLR(sk, fd_s)
#define InetPton_wrapper(af, ip, s_addr) InetPton(af, ip, s_addr)
#else
//datatype
typedef SOCKET SOCKET_wp;
typedef WSADATA WSADATA_wp;
typedef WORD WORD_wp;
typedef struct sockaddr_in sockaddr_in_wp;
typedef struct fd_set fd_set_wp;
typedef const struct timeval timeval_wp;
typedef struct sockaddr_in sockaddr_in_wp;
typedef USHORT USHORT_wp;
typedef struct sockaddr sockaddr_wp;

//func
#define FD_SET_wrapper(sk, s) FD_SET(sk, s)
#define FD_ZERO_wrapper(s) FD_ZERO(s)
#define FD_CLR_wrapper(sk, fd_s) FD_CLR(sk, fd_s)
#define InetPton_wrapper(af, ip, s_addr) InetPton(af, ip, s_addr)

#endif

static WORD_wp MAKEWORD_wrapper(int a, int b)
{
#if ANDROID
	//
#else
	return MAKEWORD(a, b);
#endif
}

static int WSAStartup_wrapper(WORD_wp ver, WSADATA_wp *data)
{
#if ANDROID
	//
#else
	return WSAStartup(ver, data);
#endif
}

static SOCKET_wp socket_wrapper(int af, int type, int protocol)
{
#if ANDROID
	//
#else
	return socket(af, type, protocol);
#endif
}

static void listen_wrapper(SOCKET_wp s, int backlog)
{
#if ANDROID
	//
#else
	listen(s, backlog);
#endif
}

static int select_wrapper(int nfds, fd_set_wp *readfds, fd_set_wp  * writefds, fd_set_wp  * exceptfds, timeval_wp  * timeout)
{
#if ANDROID
	//
#else
	return select(nfds, readfds, writefds, exceptfds, timeout);
#endif
}

static int recv_wrapper( SOCKET_wp s, char * buf, int len, int flags)
{
#if ANDROID
	//
#else
	return recv(s, buf, len, flags);
#endif
}

static void send_wrapper( SOCKET_wp s, const char * buf, int len, int flags)
{
#if ANDROID
	//
#else
	send(s, buf, len, flags);
#endif
}

static USHORT_wp htons_wrapper(int port)
{
#if ANDROID
	//
#else
	return htons(port);
#endif
}

static int connect_wrapper(SOCKET_wp s, const sockaddr_wp * name, int namelen)
{
#if ANDROID
	//
#else
	return connect(s, name, namelen);
#endif
}

static void closesocket_wrapper(SOCKET_wp sk)
{
#if ANDROID
	//
#else
	closesocket(sk);
#endif
}