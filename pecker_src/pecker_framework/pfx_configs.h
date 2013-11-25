/*
 * pfx_configs.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CONFIGS_H_
#define		PFX_CONFIGS_H_

#define	WINDOW_XP			(1)
#define	WINDOW_7_8		(1<<1)
#define	WINDOW_RT			(1<<2)
#define	WINDOW_PHONE	(1<<3)
#define	WINDOW_CE			(1<<4)

#define	ANDROID				(1)

#define	OS_WINDOWS		(1)
#define	OS_ANDROID			(1<<1)


//CONFIGS
#define OS_CONFIG						OS_WINDOWS
#define OS_VERSION_CONFIG		WINDOW_7_8

#if (OS_CONFIG == OS_WINDOWS)
//#include <Windows.h>
#include <WinSock2.h>
#include <ws2ipdef.h>
#include <Windows.h>
#pragma comment(lib,"Ws2_32.lib")
#define SOCK_LAST_ERROR_CODE WSAGetLastError
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (~0)
#endif

#endif			//PFX_CONFIGS_H_
