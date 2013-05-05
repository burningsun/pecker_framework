/*
 * PeckerDefines.h
 *
 *  Created on: 2012-6-19
 *      Author: 李镇城 (cut / cutxyz)
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
#define  P_UNINIT 10
#define  P_UNIQUE_ERR -4
#define  P_MAXUNSIGNEDVAL -1

#define PECKER_PI 3.141592653


inline void set_bytes_in_bitfield_mask(BitField& bitfield32bit,Byte bit0to7,Byte bit8to15,Byte bit16to23,Byte bit24to31)
{
	bitfield32bit = (((BitField)bit0to7 << 24) & 0xFF000000)| 
		(((BitField)bit8to15 << 16) & 0x00FF0000)|
		(((BitField)bit16to23 << 8) & 0x0000FF00)|
		(((BitField)bit24to31) & 0x000000FF);
}

inline void set_u16_in_bitfield_mask(BitField& bitfield32bit,U16bit bit0to15,U16bit bit16to31)
{
	bitfield32bit = (((BitField)bit0to15 << 16) & 0xFFFF0000)| 
		(((BitField)bit16to31) & 0x0000FFFF);
}

enum BIT_MASK_TYPE
{
	BYTE_1ST_MASK = 0,
	BYTE_2ND_MASK,
	BYTE_3TH_MASK,
	BYTE_4TH_MASK,

	SHORT_1ST_MASK,
	SHORT_2ND_MASK,

	BIT_MASK_TYPE_COUNT
};
#define BIT_0_to_7_MASK_0_to_31 BYTE_1ST_MASK
#define BIT_8_to_15_MASK_0_to_31 BYTE_2ND_MASK
#define BIT_16_to_23_MASK_0_to_31 BYTE_3TH_MASK
#define BIT_24_to_31_MASK_0_to_31 BYTE_4TH_MASK

#define  BIT_0_to_15_MASK_0_to_31 SHORT_1ST_MASK
#define  BIT_16_to_31_MASK_0_to_31 SHORT_2ND_MASK

#define BIT_0_to_7_MASK_31_to_0 BYTE_4TH_MASK
#define BIT_8_to_15_MASK_31_to_0 BYTE_3TH_MASK
#define BIT_16_to_23_MASK_31_to_0 BYTE_2ND_MASK
#define BIT_24_to_31_MASK_31_to_0 BYTE_1ST_MASK

#define  BIT_0_to_15_MASK_31_to_0 SHORT_2ND_MASK
#define  BIT_16_to_31_MASK_31_to_0  SHORT_1ST_MASK

inline BitField get_bitfield_mask(BitField bitfield,HEnum masktype)
{
	BitField return_value = 0;

	switch (masktype)
	{
	case BYTE_1ST_MASK:
		return_value = ((bitfield & 0xFF000000) >> 24);
		break;
	case BYTE_2ND_MASK:
		return_value = ((bitfield & 0x00FF0000) >> 16);
		break;
	case BYTE_3TH_MASK:
		return_value = ((bitfield & 0x0000FF00) >> 8);
		break;
	case BYTE_4TH_MASK:
		return_value = (bitfield & 0x000000FF);
		break;
	case SHORT_1ST_MASK:
		return_value = ((bitfield & 0xFFFF0000)>>16);
		break;
	case SHORT_2ND_MASK:
		return_value = (bitfield&0x0000FFFF);
		break;
	default:
		break;
	}

	return return_value;
}

inline BitField set_bitfield_mask(BitField bitfield,BitField mask_value,HEnum masktype)
{
	BitField return_value = bitfield;

	switch (masktype)
	{
	case BYTE_1ST_MASK:
		return_value = (bitfield & 0x00FFFFFF) | ((mask_value & 0xFF000000) >> 24);
		break;
	case BYTE_2ND_MASK:
		return_value = (bitfield & 0xFF00FFFF) | ((mask_value & 0x00FF0000) >> 16);
		break;
	case BYTE_3TH_MASK:
		return_value = (bitfield & 0xFFFF00FF) | ((mask_value & 0x0000FF00) >> 8);
		break;
	case BYTE_4TH_MASK:
		return_value = (bitfield & 0xFFFFFF00) | (mask_value & 0x000000FF);
		break;
	case SHORT_1ST_MASK:
		return_value = (bitfield & 0x0000FFFF) | ((mask_value & 0xFFFF0000)>>16);
		break;
	case SHORT_2ND_MASK:
		return_value =  (bitfield & 0xFFFF0000) | (mask_value&0x0000FFFF);
		break;
	default:
		break;
	}

	return return_value;
}

// bit order 0 ~31
#define BIT_0_MASK_0_to_31		(1 << 31) 
#define BIT_1_MASK_0_to_31		(1 << 30) 
#define BIT_2_MASK_0_to_31		(1 << 29) 
#define BIT_3_MASK_0_to_31		(1 << 28) 
#define BIT_4_MASK_0_to_31		(1 << 27) 
#define BIT_5_MASK_0_to_31		(1 << 26) 
#define BIT_6_MASK_0_to_31		(1 << 25) 
#define BIT_7_MASK_0_to_31		(1 << 24) 
#define BIT_8_MASK_0_to_31		(1 << 23) 
#define BIT_9_MASK_0_to_31		(1 << 22) 
#define BIT_10_MASK_0_to_31		(1 << 21) 
#define BIT_11_MASK_0_to_31		(1 << 20) 
#define BIT_12_MASK_0_to_31		(1 << 19) 
#define BIT_13_MASK_0_to_31		(1 << 18) 
#define BIT_14_MASK_0_to_31		(1 << 17) 
#define BIT_15_MASK_0_to_31		(1 << 16) 

#define BIT_16_MASK_0_to_31		(1 << 15) 
#define BIT_17_MASK_0_to_31		(1 << 14) 
#define BIT_18_MASK_0_to_31		(1 << 13) 
#define BIT_19_MASK_0_to_31		(1 << 12) 
#define BIT_20_MASK_0_to_31		(1 << 11) 
#define BIT_21_MASK_0_to_31		(1 << 10) 
#define BIT_22_MASK_0_to_31		(1 << 9) 
#define BIT_23_MASK_0_to_31		(1 << 8) 
#define BIT_24_MASK_0_to_31		(1 << 7) 
#define BIT_25_MASK_0_to_31		(1 << 6) 
#define BIT_26_MASK_0_to_31		(1 << 5) 
#define BIT_27_MASK_0_to_31		(1 << 4) 
#define BIT_28_MASK_0_to_31		(1 << 3) 
#define BIT_29_MASK_0_to_31		(1 << 2) 
#define BIT_30_MASK_0_to_31		(1 << 1) 
#define BIT_31_MASK_0_to_31		(1) 

// bit order 31~0
#define BIT_0_MASK_31_to_0		(1) 
#define BIT_1_MASK_31_to_0		(1 << 1) 
#define BIT_2_MASK_31_to_0		(1 << 2) 
#define BIT_3_MASK_31_to_0		(1 << 3) 
#define BIT_4_MASK_31_to_0		(1 << 4) 
#define BIT_5_MASK_31_to_0		(1 << 5) 
#define BIT_6_MASK_31_to_0		(1 << 6) 
#define BIT_7_MASK_31_to_0		(1 << 7) 
#define BIT_8_MASK_31_to_0		(1 << 8) 
#define BIT_9_MASK_31_to_0		(1 << 9) 
#define BIT_10_MASK_31_to_0		(1 << 10) 
#define BIT_11_MASK_31_to_0		(1 << 11) 
#define BIT_12_MASK_31_to_0		(1 << 12) 
#define BIT_13_MASK_31_to_0		(1 << 13) 
#define BIT_14_MASK_31_to_0		(1 << 14) 
#define BIT_15_MASK_31_to_0		(1 << 15) 

#define BIT_16_MASK_31_to_0		(1 << 16) 
#define BIT_17_MASK_31_to_0		(1 << 17) 
#define BIT_18_MASK_31_to_0		(1 << 18) 
#define BIT_19_MASK_31_to_0		(1 << 19) 
#define BIT_20_MASK_31_to_0		(1 << 20) 
#define BIT_21_MASK_31_to_0		(1 << 21) 
#define BIT_22_MASK_31_to_0		(1 << 22) 
#define BIT_23_MASK_31_to_0		(1 << 23) 
#define BIT_24_MASK_31_to_0		(1 << 24) 
#define BIT_25_MASK_31_to_0		(1 << 25) 
#define BIT_26_MASK_31_to_0		(1 << 26) 
#define BIT_27_MASK_31_to_0		(1 << 27) 
#define BIT_28_MASK_31_to_0		(1 << 28) 
#define BIT_29_MASK_31_to_0		(1 << 29) 
#define BIT_30_MASK_31_to_0		(1 << 30) 
#define BIT_31_MASK_31_to_0		(1 << 31) 

PECKER_END

#endif