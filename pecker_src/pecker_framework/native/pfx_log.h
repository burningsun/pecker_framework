/*
 * pfx_log.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城 (cut / cutxyz)
 */

#ifndef		PFX_LOG_H_
#define		PFX_LOG_H_

#include "../pfx_defines.h"

#if (OS_CONFIG == OS_ANDROID)
#include <android/log.h>
#define PECKER_LOG_X(X,...)((void)__android_log_print(ANDROID_LOG_INFO, (X), __VA_ARGS__))
#define PECKER_LOG_(X,...) ((void)__android_log_print(ANDROID_LOG_INFO, (X), __VA_ARGS__))
#define PECKER_LOG_INFO(X,...) ((void)__android_log_print(ANDROID_LOG_INFO, (X), __VA_ARGS__))
#define PECKER_LOG_ERR(X,...) ((void)__android_log_print(ANDROID_LOG_ERROR, (X), __VA_ARGS__))
#define PECKER_LOG_ENDLINE ((void)__android_log_print(ANDROID_LOG_INFO, ("......ENDLINE......"),("......")))
#else
#if (OS_CONFIG == OS_WINDOWS)
#include <stdio.h>
#define PECKER_LOG_DIRECT_A(X,...){ printf(X, __VA_ARGS__);}
#define PECKER_LOG_DIRECT_W(X,...){ wprintf(X, __VA_ARGS__);}
#define PECKER_LOG_DIRECT(X,...){ pfx_printf(X, __VA_ARGS__);}
#define PECKER_LOG_(X,...){ pfx_printf((pfx_char_type(X)), __VA_ARGS__);}
#define PECKER_LOG_INFO(X,Y,...){pfx_printf(pfx_char_type("LOG_INFO "));pfx_printf(pfx_char_type(X));pfx_printf(pfx_char_type("\n")); pfx_printf(pfx_char_type(Y), __VA_ARGS__);pfx_printf(pfx_char_type("\n"));}
#define PECKER_LOG_ERR(X,Y,...){pfx_printf(pfx_char_type("ERROR_INFO "));pfx_printf(pfx_char_type(X));pfx_printf(pfx_char_type("\n"));pfx_printf( pfx_char_type(Y), __VA_ARGS__);pfx_printf(pfx_char_type("\n"));}
#define PECKER_LOG_ENDLINE { pfx_printf(pfx_char_type("\n......ENDLINE......\n"));}
#endif
#endif


#endif			//PFX_LOG_H_
