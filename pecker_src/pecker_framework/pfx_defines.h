/*
 * pfx_defines.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_DEFINES_H_
#define		PFX_DEFINES_H_

#include "pfx_configs.h"
#include "pfx_os_hal.h"

#define PFX_API 
#define PFX_Interface struct

//#define PFX_INLINE inline
#define PFX_INLINE __inline //msvc
#define PFX_INLINE_CODE PFX_INLINE //有些编译器不支持c/cpp文件内写inline

// VC不支持指定类型的异常抛出声明，加上后忽略warning
#pragma warning (disable:4290)

// msvc
#define PFX_EXPORT_API __declspec(dllexport) 
#define PFX_IMPORT_API __declspec(dllimport)

#ifdef PFX_CORE_EXPORT
#define PFX_CORE_API			PFX_EXPORT_API
#define PFX_TEMPLATE_API	PFX_EXPORT_API
#else
#define PFX_CORE_API			PFX_IMPORT_API
#define PFX_TEMPLATE_API
#endif

#ifdef PFX_DATA_EXPORT
#define PFX_DATA_API						PFX_EXPORT_API
#define PFX_DATA_TEMPLATE_API	PFX_EXPORT_API
#else
#define PFX_DATA_API PFX_IMPORT_API
#define PFX_DATA_TEMPLATE_API  
#endif

#ifdef PFX_NATIVE_EXPORT
#define PFX_NATIVE_API			PFX_EXPORT_API
#define PFX_NATIVE_TEMPLATE_API	PFX_EXPORT_API
#else
#define PFX_NATIVE_API PFX_IMPORT_API
#define PFX_NATIVE_TEMPLATE_API	
#endif


#ifdef PFX_RENDER_SYSTEM_EXPORT
#define PFX_RENDER_SYSTEM_API PFX_EXPORT_API 
#define PFX_RENDER_SYS_TEMPLATE_API PFX_EXPORT_API
#else
#define PFX_RENDER_SYSTEM_API PFX_IMPORT_API
#define PFX_RENDER_SYS_TEMPLATE_API 
#endif


#ifdef PFX_RENDER_EXPORT
#define PFX_RENDER_API PFX_EXPORT_API 
#define PFX_RENDER_TEMPLATE_API PFX_EXPORT_API 
#else
#define PFX_RENDER_API PFX_IMPORT_API
#define PFX_RENDER_TEMPLATE_API 
#endif

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
	PFX_STATUS_ERROR_COUNT = -26,

	PFX_STATUS_FULL,
	PFX_STATUS_EMPTY,

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
#define PECKER_PI (3.141592653)
#define PECKER_TWO_PI (6.283185306)


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

#define FOR_ONE_LOOP_BEGIN do{
#define FOR_ONE_LOOP_END ;break;}while(1);
#define BREAK_LOOP(STATUS_PARAM,ERROR_CODE) {STATUS_PARAM = ERROR_CODE; break;}
#define BREAK_LOOP_CONDITION(condition_)if (condition_){break;}
#define BREAK_LOOP_CONDITION_ACT(condition_,ACT)if (condition_){{ACT;}break;}
#define BREAK_LOOP_CONDITION_SETS(condition_,STATUS_PARAM,ERROR_CODE)if (condition_){STATUS_PARAM = ERROR_CODE;break;}

#define PARAM_IN
#define PARAM_OUT
#define PARAM_INOUT

PFX_C_EXTERN_BEGIN
// 类型定义
typedef unsigned char			u8_t;
typedef unsigned short			u16_t;
typedef unsigned int				u32_t;
typedef unsigned long long	u64_t;

typedef char							s8_t;
typedef short						s16_t;
typedef int								s32_t;
typedef long long					s64_t;

typedef float							float_t;
typedef double						double_t;

typedef void*						handle_t;
typedef void*						pvoid_t;
typedef char							char_t;
typedef wchar_t					widechar_t;
typedef char*						charstr_t;

typedef s32_t				sint_t;
typedef u32_t				uint_t;
typedef s16_t				short_t;
typedef u16_t				ushort_t;
typedef long							long_t;
typedef unsigned long		ulong_t; 

typedef long							address_t;
typedef long							result_t;
typedef long							flag_t;
typedef unsigned char		u8flag_t;
typedef unsigned short		u16flag_t;
typedef unsigned long		enum_t;
typedef int								coord_t;
typedef int								nsize__t;
typedef unsigned int			usize__t;
typedef int								index_t;
typedef unsigned int			uindex_t;
typedef unsigned char		byte_t;
typedef unsigned int			enum_int_t;
typedef unsigned int			bitfield_t;
typedef unsigned int			boolean_t;
//typedef char pfx_boolean_t;

typedef enum enum_bool
{
	PFX_BOOL_FALSE = 0,
	PFX_BOOL_TRUE,
	PFX_BOOL_INVALID,
	PFX_BOOL_TRUE_VAL2
}bool_t;
//#define pfx_true (1)
//#define pfx_false (0)
typedef struct st_float_type
{
	unsigned		m_signed_bit:1;
	unsigned		m_exponent :8;
	unsigned		m_value : 23; 
}float_struct_t;

typedef struct st_double_type
{
	unsigned		m_signed_bit:1;
	unsigned		m_exponent :11;
	unsigned		m_value_1 : 20;
	unsigned		m_value_2	: 32;
}double_struct_t;

typedef union PFX_16bit_DataType
{
	short_t		m_short_type;
	ushort_t		m_ushort_type;
	char_t			m_char_type[2];
	byte_t			m_uchar_type[2];
}PFX_16bit_t;

typedef union PFX_32bit_DataType
{
	sint_t									m_int_type;
	uint_t									m_uint_type;
	float_t								m_float_type;
	long_t									m_long_type;
	ulong_t								m_ulong_type;
	short_t								m_short_type[2];
	ushort_t								m_ushort_type[2];
	char_t									m_char_type[4];
	byte_t									m_uchar_type[4];
	PFX_16bit_t								m_16bit_type[2];
	float_struct_t					m_float_st_type;
}PFX_32_bit_t;

typedef union PFX_64bit_DataType
{
	long long						m_longlong_type;
	unsigned long long		m_ullong_type;
	double							m_double_type;
	sint_t						m_int_type[2];
	uint_t						m_uint_type[2];
	float_t					m_float_type[2];
	long_t						m_long_type[2];
	ulong_t					m_ulong_type[2];
	short_t					m_short_type[4];
	ushort_t					m_ushort_type[4];
	char_t						m_char_type[8];
	byte_t						m_uchar_type[8];
	PFX_32_bit_t					m_32bit_type[2];
	PFX_16bit_t					m_16bit_type[4];
	double_struct_t	m_double_st_type;
}PFX_64bit_t;

typedef union PFX_128bit_DataType
{
	long long						m_longlong_type[2];
	unsigned long long		m_ullong_type[2];
	double							m_double_type[2];
	sint_t						m_int_type[4];
	uint_t						m_uint_type[4];
	float_t					m_float_type[4];
	long_t						m_long_type[4];
	ulong_t					m_ulong_type[4];
	short_t					m_short_type[8];
	ushort_t					m_ushort_type[8];
	char_t						m_char_type[16];
	byte_t						m_uchar_type[16];
	PFX_64bit_t					m_64bit_type[2];
	PFX_32_bit_t					m_32bit_type[4];
	PFX_16bit_t					m_16bit_type[8];
}PFX_128bit_t;

#define RETURN_RESULT(condition,return_status) {if (condition) {return (return_status);} };

#define RETURN_BY_ACT_RESULT(condition,action_,return_status) {if (condition) {{action_;};return (return_status);} };

#define RETURN_INVALID_RESULT(condition,return_status) {if (condition) {return (return_status);} };

#define RETURN_INVALID_BY_ACT_RESULT(condition,action_,return_status) {if (condition) {{action_;};return (return_status);} };

#define  SET_POINTER_VALUE(ptr_,val_){if (ptr_){*(ptr_) = (val_);};};

PFX_INLINE usize__t get_32bit_onemask_count (bitfield_t bitmask)
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
PFX_INLINE void set_bytes_in_bitfield_mask(bitfield_t& bitfield32bit,byte_t bit0to7,byte_t bit8to15,byte_t bit16to23,byte_t bit24to31)
{
	bitfield32bit = (((bitfield_t)bit0to7 << 24) & 0xFF000000)| 
		(((bitfield_t)bit8to15 << 16) & 0x00FF0000)|
		(((bitfield_t)bit16to23 << 8) & 0x0000FF00)|
		(((bitfield_t)bit24to31) & 0x000000FF);
}

PFX_INLINE void set_u16_in_bitfield_mask(bitfield_t& bitfield32bit,u16_t bit0to15,u16_t bit16to31)
{
	bitfield32bit = (((bitfield_t)bit0to15 << 16) & 0xFFFF0000)| 
		(((bitfield_t)bit16to31) & 0x0000FFFF);
}
#else
#define  set_bytes_in_bitfield_mask( bitfield32bit,bit0to7,bit8to15,bit16to23,bit24to31)  \
{																																							\
	bitfield32bit = (((bitfield_t)bit0to7 << 24) & 0xFF000000)|														\
		(((bitfield_t)bit8to15 << 16) & 0x00FF0000)|																			\
		(((bitfield_t)bit16to23 << 8) & 0x0000FF00)|																			\
		(((bitfield_t)bit24to31) & 0x000000FF);																					\
}

#define  set_u16_in_bitfield_mask(bitfield32bit,bit0to15,bit16to31)										\
{																																							\
	bitfield32bit = (((bitfield_t)bit0to15 << 16) & 0xFFFF0000)|														\
		(((bitfield_t)bit16to31) & 0x0000FFFF);																					\
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

PFX_INLINE bitfield_t get_bitfield_mask(bitfield_t bitfield,enum_t masktype)
{
	bitfield_t return_value = 0;

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

PFX_INLINE bitfield_t set_bitfield_mask(bitfield_t bitfield,bitfield_t mask_value,enum_t masktype)
{
	bitfield_t return_value = bitfield;

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

typedef struct st_pfx_api_version
{
	unsigned int version_code[4];
}pfx_version_t;

typedef union un_pfx_instance_version
{
	typedef struct st_ins_ver 
	{
		u16_t m_sub_version[4];
	}ins_ver_t;
	ins_ver_t	m_sub_ver;
	u64_t		m_version;
}instance_version_t;


#define FIRST_BITINDEX_0(X,Y) (Y)
#define FIRST_BITINDEX_1(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_0((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_2(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_1((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_3(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_2((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_4(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_3((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_5(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_4((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_6(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_5((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_7(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_6((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_8(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_7((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_9(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_8((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_10(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_9((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_11(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_10((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_12(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_11((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_13(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_12((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_14(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_13((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_15(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_14((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_16(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_15((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_17(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_16((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_18(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_17((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_19(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_18((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_20(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_19((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_21(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_20((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_22(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_21((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_23(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_22((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_24(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_23((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_25(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_24((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_26(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_25((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_27(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_26((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_28(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_27((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_29(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_28((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_30(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_29((X)>>1,((Y)+1))):(Y))
#define FIRST_BITINDEX_31(X,Y) ((((X)>>1)>0)?(FIRST_BITINDEX_30((X)>>1,((Y)+1))):(Y))


#define MIP_BUFFER_SIZE_00(X,Y,F) (Y)
#define MIP_BUFFER_SIZE_01(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_00( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_02(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_01( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_03(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_02( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_04(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_03( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_05(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_04( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_06(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_05( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_07(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_06( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_08(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_07( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_09(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_08( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_10(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_09( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_11(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_10( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_12(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_11( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_13(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_12( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_14(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_13( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_15(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_14( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_16(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_15( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_17(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_16( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_18(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_17( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_19(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_18( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_20(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_19( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_21(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_20( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_22(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_21( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_23(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_22( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_24(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_23( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_26(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_24( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_27(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_26( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_28(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_27( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_29(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_28( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_30(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_29( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))
#define MIP_BUFFER_SIZE_31(X,Y,F) ((((X)>>1)>0)?(MIP_BUFFER_SIZE_30( ((X)>>1), ((Y)+(((X)*(X)*(F))>>2)) , (F) )):(Y))

PFX_C_EXTERN_END

PECKER_BEGIN

typedef struct object_id
{
	typedef uint_t (*__final_type_id) ();
	typedef boolean_t (*__check_id) (uint_t test_id);
	typedef object_id object_id__t;

	__final_type_id			final_type_id;
	__check_id					check_id;
	const object_id__t*		next;
}object_id_t;

struct PFX_DATA_API __type_id
{
	static uint_t&	ID ();
	static uint_t NEW_ID ();
	static boolean_t __IS_type (const object_id_t& type_a, const object_id_t& test_type);
};

template < class this_type_t, 
					class base_type_t = this_type_t >
class PFX_DATA_TEMPLATE_API cobject_id
{
public:
	typedef this_type_t										this_type_t;
	typedef base_type_t									base_type_t;
	typedef typename cobject_id< this_type_t, base_type_t >	cobject_id_t;
public:
	static uint_t final_type_id ()
	{
		static const uint_t static_id = __type_id::NEW_ID();
		return static_id;
	}
	static boolean_t check_id (uint_t test_id)
	{
		uint_t __id = final_type_id();
		if (test_id == __id)
		{
			return PFX_BOOL_TRUE; 
		}
		else
		{
			boolean_t retn_res = PFX_BOOL_FALSE;

			const struct object_id& __idlist = base_type_t::final_type ();
			const struct object_id* list_ptr = & __idlist;
			do 
			{
				uint_t __base_id = list_ptr->final_type_id();
				if (__id != __base_id)
				{
					retn_res = list_ptr->check_id (test_id);
					if (PFX_BOOL_TRUE == retn_res)
					{
						break;
					}
				}
				list_ptr = list_ptr->next;
			} while (list_ptr);

			return retn_res;

		}
	}
	static struct object_id& to_object_id (struct object_id& obj_id)
	{
		obj_id.check_id = check_id;
		obj_id.final_type_id = final_type_id;
		obj_id.next = null;
		return obj_id;
	}
};





PECKER_END

#endif		//PFX_DEFINES_H_
