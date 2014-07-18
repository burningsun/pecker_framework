/*
 * pfx_configs.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_OS_HAL_H_
#define		PFX_OS_HAL_H_

#include "pfx_configs.h"
#include <stdio.h>

#if (OS_CONFIG == OS_WINDOWS)

#include <WinSock2.h>
#include <ws2tcpip.h>

#include <MSTcpIP.h>

#pragma comment (lib, "Ws2_32.lib")

#define CriticalSection							CRITICAL_SECTION

inline int GetNetLastErrorCode()
{
	return ::WSAGetLastError();
}
#define InitCriticalSection(X)					::InitializeCriticalSection(X)
#define LockCriticalSection(X)				::EnterCriticalSection(X)
#define UnlockCriticalSection(X)			::LeaveCriticalSection(X)
#define DelCriticalSection(X)					::DeleteCriticalSection(X)
#define GetEscapeTickCount()				::GetTickCount64();
#define SleepMS(X)									::Sleep(X);
inline int SocketStart ()
{
	static WSADATA	wsaData;
	int iResult = ::WSAStartup(MAKEWORD(2,2), &wsaData);
	return iResult;
}
inline int SocketCleanUp()						
{
	return ::WSACleanup();
}

#ifdef OS_32BIT
inline INT WSAAPI inet_str_2_addr(__in                                INT             Family,
	__in                                PCSTR           pszAddrString,
	__out_bcount(sizeof(IN6_ADDR))      PVOID           pAddrBuf)
{
	if (!pAddrBuf)
	{
		return -1;
	}
	int len = 0;
	int status = 0;
	sockaddr result_addr;
	ZeroMemory(&result_addr,sizeof(sockaddr));
	switch (Family)
	{
	case AF_INET:
		len																= sizeof (sockaddr_in);
		status =::WSAStringToAddressA((LPSTR)pszAddrString, Family, NULL, (LPSOCKADDR)&result_addr, &len);
		break;
	case AF_INET6:
		len =  sizeof (sockaddr_in6);
		status =::WSAStringToAddressA((LPSTR)pszAddrString, Family, NULL, (LPSOCKADDR)&result_addr, &len);

		break;
	default:
		break;
	}
	memcpy_s(pAddrBuf, sizeof(IN6_ADDR),  &(((sockaddr_in*)&result_addr)->sin_addr), sizeof(IN6_ADDR));

	return status;
}
#else
#define inet_str_2_addr inet_pton
#endif

typedef int socket_len;
#else


#if ((OS_CONFIG == OS_ANDROID)||(OS_CONFIG == OS_LINUX))
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#include <sys/socket.h>  
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string.h>
#include <errno.h>


#define CriticalSection							pthread_mutex_t

inline void print_error_info (int __error)
{
	printf("%s,%d\n", gai_strerror(__error),__error);
}

inline int GetNetLastErrorCode()
{
	int err_code = errno;
	if (err_code)
	{
		printf("%s,%d\n", gai_strerror(err_code),err_code);
		printf("%s %d\n", strerror(err_code), err_code);
	}
	return err_code;
}
#define InitCriticalSection(X)					::pthread_mutex_init((X),NULL);
#define LockCriticalSection(X)					::pthread_mutex_lock((X));
#define UnlockCriticalSection(X)				::pthread_mutex_unlock((X));
#define DelCriticalSection(X)					::pthread_mutex_destroy((X)); 
#define SleepMS(X)								(((X)>=1000)?(::sleep((X)/1000)):(::usleep(X*1000)));
inline unsigned long long GetEscapeTickCount()
{
	struct timeval tv;
	int status;
	status = gettimeofday(&tv, 0);
	if (status)
	{
		return 0;
	}
	else
	{
		return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}
#define closesocket									close


#define CS_LOCK(X) 

typedef sa_family_t 	ADDRESS_FAMILY;
typedef int 			SOCKET;
typedef long 			HANDLE;
typedef unsigned long	DWORD;
typedef int				BOOL;
#define FALSE			(0)

#define WSA_INFINITE	(0xFFFFFFFF)

inline void ZeroMemory(
	void* Destination,
	size_t Length
	)
{
	memset(Destination, 0, Length);
}

inline int memcpy_s(
	void *dest,
	size_t numberOfElements,
	const void *src,
	size_t count)
{
	if (dest && src)
	{
		if (count > numberOfElements)
		{
			count = numberOfElements;
		}
		memcpy (dest, src, count);
		return 0;
	}
	else
	{
		return -1;
	}
}

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#define WAIT_FAILED 			((DWORD)0xFFFFFFFF)
#define WAIT_TIMEOUT            258L    // dderror
#define WSA_WAIT_FAILED         (WAIT_FAILED)
#define WSA_WAIT_TIMEOUT        (WAIT_TIMEOUT)

#define sprintf_s				snprintf

inline int SocketStart ()
{
	return 0;
}
inline int SocketCleanUp()
{
	return 0;
}

typedef socklen_t 	socket_len;

#define SOCKADDR_IN sockaddr_in

#define inet_str_2_addr inet_pton

#endif
#endif



#endif			//PFX_CONFIGS_H_
