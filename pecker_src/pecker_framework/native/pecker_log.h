/*
 * pecker_log.h
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_LOG_H_
#define PECKER_LOG_H_

#include "../CPeckerObject.h"
#ifdef ANDROID_OS
#include <android/log.h>
#define PECKER_LOG_(X,...) ((void)__android_log_print(ANDROID_LOG_INFO, (X), __VA_ARGS__))
#define PECKER_LOG_INFO(X,...) ((void)__android_log_print(ANDROID_LOG_INFO, (X), __VA_ARGS__))
#define PECKER_LOG_ERR(X,...) ((void)__android_log_print(ANDROID_LOG_ERROR, (X), __VA_ARGS__))
#define PECKER_LOG_ENDLINE ((void)__android_log_print(ANDROID_LOG_INFO, ("......ENDLINE......"),("......")))
#else
#ifdef WINDOWS_PC
#include <stdio.h>
#define PECKER_LOG_(X,...){ printf((X), __VA_ARGS__);}
#define PECKER_LOG_INFO(X,Y,...){printf("LOG_INFO ");printf((X));printf("\n"); printf((Y), __VA_ARGS__);printf("\n");}
#define PECKER_LOG_ERR(X,Y,...){printf("ERROR_INFO ");printf((X));printf("\n");printf( (Y), __VA_ARGS__);printf("\n");}
#define PECKER_LOG_ENDLINE { printf("\n......ENDLINE......\n");}
#endif
#endif

#define MAX_ERROR_INFO_BYTES 2048
extern char g_error_info[MAX_ERROR_INFO_BYTES];
PECKER_BEGIN

PECKER_END


#endif /* PECKER_LOG_H_ */
