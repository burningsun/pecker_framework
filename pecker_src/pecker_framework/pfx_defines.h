/*
 * pfx_defines.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_DEFINES_H_
#define		PFX_DEFINES_H_

#include "pfx_configs.h"

#define PFX_API 
#define PFX_Interface struct

//#define PFX_INLINE inline
#define PFX_INLINE __inline //msvc
#define PFX_INLINE_CODE PFX_INLINE //有些编译器不支持c/cpp文件内写inline

#ifdef _UNICODE
#define pfx_char wchar_t
#define pfx_char_type(x) L ## x
#define pfx_printf wprintf
#define pfx_sscanf swscanf
#define pfx_sprintf swprintf
#define pfx_strlen wcslen
#else
#define pfx_char char
#define pfx_char_type(x) x
#define pfx_printf printf
#define pfx_sscanf sscanf
#define pfx_sprintf sprintf
#define pfx_strlen strlen
#endif

// 状态
enum PFX_STATUS_CODE
{
	PFX_STATUS_ERROR_COUNT = -24,
	PFX_STATUS_OVERRANGE,

	PFX_STATUS_DENIED,
	PFX_STATUS_NOT_EXISTS,

	PFX_STATUS_DIFF_TYPE,
	
	PFX_STATUS_REFERENCED,

	PFX_STATUS_UNIQUE,
	PFX_STATUS_UNINIT,

	PFX_STATUS_TIMEOUT,
	PFK_STATUS_NULLITEM,
	
	PFX_STATUS_OPENED,
	PFX_STATUS_CLOSED,
	
	PFX_STATUS_MEM_ERR,
	PFX_STATUS_MEM_LOW,
	PFX_STATUS_OUT_OF_MEMORY,
	PFX_STATUS_STACKOVERFLOW,
	
	PFX_STATUS_WAITRESULT,
	PFX_STATUS_FIN,

	PFX_STATUS_FAIL,
	PFX_STATUS_ERROR_,

	PFX_STATUS_INVALID_PARAMS,


	PFX_STATUS_INVALID_OPERATION,
	PFX_STATUS_INVALID_VALUE,
	PFX_STATUS_INVALID_ENUM,
	
	PFX_STATUS_OK = 0,
	PFK_STATUS_SUCCESS,
	
	PFX_STATUS_OK_COUNT,
	PFX_STATUS_CODE_COUNT = (PFX_STATUS_OK_COUNT - PFX_STATUS_ERROR_COUNT)
};


// 常用定义
#ifdef null
#if null != 0
#undef null
#define null (0)
#endif
#else
#define null (0)
#endif
#define INVALID_VALUE	(-1)
#define MAX_UNSIGNED_VALUE (-1)
#define PECKER_PI 3.141592653

#ifdef __cplusplus
#define	PFX_C_EXTERN_BEGIN extern "C" {
#else // __cplusplus
#define	PFX_C_EXTERN_BEGIN
#endif // __cplusplus

#ifdef __cplusplus
#define	PFX_C_EXTERN_END  };
#else// __cplusplus
#define	PFX_C_EXTERN_END
#endif // __cplusplus

#ifdef __cplusplus
#define PECKER_BEGIN namespace pecker_sdk{
#define PECKER_END  }
#define PECKER_SDK ::pecker_sdk::
#define USING_PECKER_SDK using namespace pecker_sdk;
#else // __cplusplus
#define PECKER_BEGIN
#define PECKER_END
#define PECKER_SDK
#define USING_PECKER_SDK
#endif // __cplusplus

#define FOR_ONE_LOOP_BEGIN {
#define FOR_ONE_LOOP_END }while(0);
#define BREAK_LOOP(STATUS_PARAM,ERROR_CODE) {STATUS_PARAM = ERROR_CODE; break;}


#define PARAM_IN
#define PARAM_OUT
#define PARAM_INOUT

PFX_C_EXTERN_BEGIN
// 类型定义
typedef unsigned char			pfx_u8_t;
typedef unsigned short		pfx_u16_t;
typedef unsigned int				pfx_u32_t;
typedef unsigned long long pfx_u64_t;

typedef char							pfx_s8_t;
typedef short							pfx_s16_t;
typedef int								pfx_s32_t;
typedef long long					pfx_s64_t;

typedef float							pfx_float_t;
typedef double						pfx_double_t;

typedef void*							pfx_handle_t;
typedef void*							pfx_pvoid_t;
typedef char							pfx_char_t;
typedef wchar_t					pfx_wchar_t;
typedef char*							pfx_charstr_t;

typedef pfx_s32_t					pfx_sint_t;
typedef pfx_u32_t					pfx_uint_t;
typedef pfx_s16_t					pfx_short_t;
typedef pfx_u16_t					pfx_ushort_t;
typedef long							pfx_long_t;
typedef unsigned long			pfx_ulong_t; 

typedef long							pfx_address_t;
typedef long							pfx_result_t;
typedef long							pfx_flag_t;
typedef unsigned long			pfx_enum_t;
typedef int								pfx_pos_coord_t;
typedef int								pfx_nsize_t;
typedef unsigned int				pfx_usize_t;
typedef int								pfx_index_t;
typedef unsigned char			pfx_byte_t;
typedef unsigned int				pfx_enum_int_t;
typedef unsigned int				pfx_bitfield_t;
//typedef char Bool;

typedef enum enum_bool
{
	pfx_false = 0,
	pfx_true,
	pfx_invalid,
}pfx_bool_t;
//#define pfx_true (1)
//#define pfx_false (0)
typedef struct st_float_type
{
	unsigned		m_signed_bit:1;
	unsigned		m_exponent :8;
	unsigned		m_value : 23; 
}pfx_float_struct_t;

typedef struct st_double_type
{
	unsigned		m_signed_bit:1;
	unsigned		m_exponent :11;
	unsigned		m_value_1 : 20;
	unsigned		m_value_2	: 32;
}pfx_double_struct_t;

typedef union PFX_16bit_DataType
{
	pfx_short_t		m_short_type;
	pfx_ushort_t		m_ushort_type;
	pfx_char_t			m_char_type[2];
	pfx_byte_t			m_uchar_type[2];
}pfx_16bit_t;

typedef union PFX_32bit_DataType
{
	pfx_sint_t									m_int_type;
	pfx_uint_t									m_uint_type;
	pfx_float_t									m_float_type;
	pfx_long_t									m_long_type;
	pfx_ulong_t								m_ulong_type;
	pfx_short_t								m_short_type[2];
	pfx_ushort_t								m_ushort_type[2];
	pfx_char_t									m_char_type[4];
	pfx_byte_t									m_uchar_type[4];
	pfx_16bit_t								m_16bit_type[2];
	pfx_float_struct_t						m_float_st_type;
}pfx_32_bit_t;

typedef union PFX_64bit_DataType
{
	long long						m_longlong_type;
	unsigned long long		m_ullong_type;
	double							m_double_type;
	pfx_sint_t						m_int_type[2];
	pfx_uint_t						m_uint_type[2];
	pfx_float_t						m_float_type[2];
	pfx_long_t						m_long_type[2];
	pfx_ulong_t					m_ulong_type[2];
	pfx_short_t					m_short_type[4];
	pfx_ushort_t					m_ushort_type[4];
	pfx_char_t						m_char_type[8];
	pfx_byte_t						m_uchar_type[8];
	pfx_32_bit_t					m_32bit_type[2];
	pfx_16bit_t					m_16bit_type[4];
	pfx_double_struct_t		m_double_st_type;
}pfx_64bit_t;

typedef union PFX_128bit_DataType
{
	long long						m_longlong_type[2];
	unsigned long long		m_ullong_type[2];
	double							m_double_type[2];
	pfx_sint_t						m_int_type[4];
	pfx_uint_t						m_uint_type[4];
	pfx_float_t						m_float_type[4];
	pfx_long_t						m_long_type[4];
	pfx_ulong_t					m_ulong_type[4];
	pfx_short_t					m_short_type[8];
	pfx_ushort_t					m_ushort_type[8];
	pfx_char_t						m_char_type[16];
	pfx_byte_t						m_uchar_type[16];
	pfx_64bit_t					m_64bit_type[2];
	pfx_32_bit_t					m_32bit_type[4];
	pfx_16bit_t					m_16bit_type[8];
}pfx_128bit_t;

#define RETURN_RESULT(condition,return_status) {if (condition) {return (return_status);} };

#define RETURN_INVALID_RESULT(condition,return_status) {if (condition) {return (return_status);} };

#define RETURN_INVALID_BY_ACT_RESULT(condition,action_,return_status) {if (condition) {{action_};return (return_status);} };

#define  SET_POINTER_VALUE(ptr_,val_){if (ptr_){*(ptr_) = (val_);};};

PFX_INLINE pfx_usize_t get_32bit_onemask_count (pfx_bitfield_t bitmask)
{
	bitmask = (bitmask&0x55555555) + ((bitmask>>1)&0x55555555);     
	bitmask = (bitmask&0x33333333) + ((bitmask>>2)&0x33333333);
	bitmask = (bitmask&0x0f0f0f0f) + ((bitmask>>4)&0x0f0f0f0f);     
	bitmask = (bitmask&0x00ff00ff) + ((bitmask>>8)&0x00ff00ff);     
	bitmask = (bitmask&0x0000ffff) + ((bitmask>>16)&0x0000ffff);
	return bitmask;
}

#ifdef __cplusplus
// 位操作
PFX_INLINE void set_bytes_in_bitfield_mask(pfx_bitfield_t& bitfield32bit,pfx_byte_t bit0to7,pfx_byte_t bit8to15,pfx_byte_t bit16to23,pfx_byte_t bit24to31)
{
	bitfield32bit = (((pfx_bitfield_t)bit0to7 << 24) & 0xFF000000)| 
		(((pfx_bitfield_t)bit8to15 << 16) & 0x00FF0000)|
		(((pfx_bitfield_t)bit16to23 << 8) & 0x0000FF00)|
		(((pfx_bitfield_t)bit24to31) & 0x000000FF);
}

PFX_INLINE void set_u16_in_bitfield_mask(pfx_bitfield_t& bitfield32bit,pfx_u16_t bit0to15,pfx_u16_t bit16to31)
{
	bitfield32bit = (((pfx_bitfield_t)bit0to15 << 16) & 0xFFFF0000)| 
		(((pfx_bitfield_t)bit16to31) & 0x0000FFFF);
}
#else
#define  set_bytes_in_bitfield_mask( bitfield32bit,bit0to7,bit8to15,bit16to23,bit24to31)  \
{																																							\
	bitfield32bit = (((pfx_bitfield_t)bit0to7 << 24) & 0xFF000000)|														\
		(((pfx_bitfield_t)bit8to15 << 16) & 0x00FF0000)|																			\
		(((pfx_bitfield_t)bit16to23 << 8) & 0x0000FF00)|																			\
		(((pfx_bitfield_t)bit24to31) & 0x000000FF);																					\
}

#define  set_u16_in_bitfield_mask(bitfield32bit,bit0to15,bit16to31)										\
{																																							\
	bitfield32bit = (((pfx_bitfield_t)bit0to15 << 16) & 0xFFFF0000)|														\
		(((pfx_bitfield_t)bit16to31) & 0x0000FFFF);																					\
}
#endif

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

PFX_INLINE pfx_bitfield_t get_bitfield_mask(pfx_bitfield_t bitfield,pfx_enum_t masktype)
{
	pfx_bitfield_t return_value = 0;

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

PFX_INLINE pfx_bitfield_t set_bitfield_mask(pfx_bitfield_t bitfield,pfx_bitfield_t mask_value,pfx_enum_t masktype)
{
	pfx_bitfield_t return_value = bitfield;

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

PFX_C_EXTERN_END

#endif		//PFX_DEFINES_H_
