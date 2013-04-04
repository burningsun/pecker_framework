/*
 * PeckerDefines.h
 *
 *  Created on: 2012-6-19
 *      Author: ¿Ó’Ú≥« (cut / cutxyz)
 */

#include "PeckerConfig.h"

#ifndef PECKER_DEFINE_H
#define PECKER_DEFINE_H

#ifdef __cplusplus
#define PECKER_BEGIN namespace pecker_sdk{
#define PECKER_END  }
#define PECKER_SDK ::pecker_sdk::
#define USING_PECKER_SDK using namespace pecker_sdk;
#else
#define PECKER_BEGIN
#define PECKER_END
#define PECKER_SDK
#define USING_PECKER_SDK
#endif

PECKER_BEGIN

typedef unsigned char U8bit;
typedef unsigned short U16bit;
typedef unsigned int U32bit;
typedef unsigned long long U64bit;

typedef char S8bit;
typedef short S16bit;
typedef int S32bit;
typedef long long S64bit;

typedef float Float;
typedef double Double;

typedef void* Handle;
typedef void* PVoid;
typedef char Char;
typedef char* CharStr;

typedef S32bit SInt;
typedef U32bit UInt;
typedef long Long;
typedef unsigned long Ulong; 

typedef long HADDR;
typedef long HResult;
typedef long HFlag;
typedef int nPosCoord;
typedef int nSize;
typedef unsigned int uSize;
typedef int nINDEX;
typedef unsigned char Byte;
typedef unsigned int HEnum;
typedef unsigned int BitField;

typedef bool Bool;
typedef Char Boolc;
typedef SInt Boolean;
typedef enum enumBooleanType
{
	BOOL_INVALID_VAL = -1,
	BOOL_FALSE = 0,
	BOOL_TRUE,
}BOOLEANTYPE;
//typedef unsigned char* Bytes;

union INT_FLOAT_SHARE_MEM_VAL
{
	SInt _M_sinteger;
	UInt _M_uinteger;
	Float _M_float;
};

#define PeckerInterface struct
#define P_IN
#define P_OUT
#define P_REF &
#define P_INOUT

#define null 0
#define P_OK    0
#define P_FAIL 	1
#define P_ERR	-1
#define P_INVALID_ENUM -1
#define P_INVALID_VALUE -2
#define P_INVALID_OPERATION -3
#define P_OUT_OF_MEMORY -6
#define P_WAITRESULT 2
#define P_FIN 3
#define P_STACKOVERFLOW 4
#define P_OVERFLOW 5
#define P_SUCCESS      6
#define P_NULLITEM	7
#define  P_TIMEOUT	8
#define  P_RUNNING_WAIT 9
#define  P_UNIQUE_ERR -4
#define  P_MAXUNSIGNEDVAL -1

#define PECKER_PI 3.141592653

PECKER_END

#endif
