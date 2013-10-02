/*
 * pfx_string.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城 (cut / cutxyz)
 */

#ifndef		PFX_STRING_H_
#define		PFX_STRING_H_
 
#include "../pfx_defines.h"
#include "../native/pfx_allocator.h"
#include "pfx_list.h"

#define MIN_STRING_BUFFER_SIZE (16)

PFX_C_EXTERN_BEGIN

// 字符串使用的IAllocator*必须使用能一次分配一块连续内存的分配器

// 字符串
typedef struct st_pfx_string
{
	unsigned m_revered : 1;
	unsigned m_using_extern_buffer : 1;
	unsigned m_char_size : 14;
	unsigned m_defualt_buffer_size : 16;

	size_t m_string_buffer_size;
	size_t m_string_buffer_length;

	char* m_pthis_string_data;
}pfx_string_t;

// 强制转换一个buffer成为字符串
pfx_string_t* init_string_by_buffer(size_t char_size,size_t min_buffer_size,char* PARAM_INOUT string_obj_buffer,pfx_result_t* PARAM_INOUT pstatus);

// 从内存分配器中新建一个字符串
pfx_string_t* new_string(size_t char_size,size_t min_char_count,const IAllocator* PARAM_IN pAllocator,pfx_result_t* PARAM_INOUT pstatus);

// 释放一个字符串占有的额外的内存资源
pfx_result_t relese_string_extern_buffer(pfx_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator);

// 从内存分配器中删除一个字符串
PFX_INLINE pfx_result_t delete_string(pfx_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator);

// 初始化字符串
pfx_result_t init_string(pfx_string_t* PARAM_INOUT pstr,
	size_t string_len,
	const IAllocator* PARAM_IN pchar_allocator);
// 使用现有buffer初始化字符串结构体，同时原有buffer转化为字符结构体
pfx_result_t init_string_by_charsbuffer(pfx_string_t* PARAM_INOUT pstr,
	const char* PARAM_IN pstr_chars,size_t chars_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator);

// 字符串拷贝
pfx_result_t copy_string(pfx_string_t* PARAM_INOUT pstr_dec,
	const pfx_string_t* PARAM_IN pstr_src,const IAllocator* PARAM_IN pchar_allocator);

// 清除字符串buffer中的字符串
PFX_INLINE pfx_result_t clear_string(pfx_string_t* PARAM_INOUT pstr,
const IAllocator* PARAM_IN pAllocator);

// 交换默认大小一样的字符串 
pfx_result_t swap_string(pfx_string_t* PARAM_INOUT pstrA,pfx_string_t* PARAM_INOUT pstrB);

// 交换默认大小不一样的字符串 
pfx_result_t swap_string_by_allocator(pfx_string_t* PARAM_INOUT pstrA,pfx_string_t* PARAM_INOUT pstrB,
	const IAllocator* PARAM_IN pchar_allocator);

// 重新定义字符串大小
pfx_result_t resize_string(pfx_string_t* PARAM_INOUT pstr,size_t string_len,pfx_bool_t bnew_allocate, const IAllocator* PARAM_IN pchar_allocator);

// 获取子字符串
pfx_result_t get_sub_string(const pfx_string_t* PARAM_IN porign_string, pfx_string_t* PARAM_INOUT preference_sub_string,size_t ioffset,size_t sub_string_length,const IAllocator* PARAM_IN pchar_allocator);

// 给字符串后面加入新的字符串
pfx_result_t append_string_by_chars(pfx_string_t* PARAM_INOUT pstr,const char* PARAM_IN str_chars, size_t chars_buffer_size,const IAllocator* PARAM_IN pchar_allocator);

// 给字符串后面加入新的字符串
PFX_INLINE pfx_result_t append_string_by_string(pfx_string_t* PARAM_INOUT pstr,const pfx_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator);

// 获取指定位置的字节
PFX_INLINE char get_string_buffer_at_unsafe(const pfx_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus);
PFX_INLINE char get_string_buffer_at(const pfx_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus);

// 设置指定位置的字节
PFX_INLINE pfx_result_t set_string_buffer_at_unsafe( pfx_string_t* PARAM_INOUT pstr,size_t index,char set_char);
PFX_INLINE pfx_result_t set_string_buffer_at(pfx_string_t* PARAM_INOUT pstr,size_t index,char set_char);

// 设定指定位置的buffer
PFX_INLINE pfx_result_t set_string_buffer_chars_at(pfx_string_t* PARAM_INOUT pstr,size_t index,const char* PARAM_INOUT set_chars,size_t set_buffer_size);
PFX_INLINE const char* get_string_buffer_chars_at(const pfx_string_t* PARAM_IN pstr,size_t index);

// 共享字符串内存的字符串
typedef struct st_pfx_share_buffer_string
{
	linked_list_node_t							m_list_node;
	pfx_string_t*									m_reference_string;

	unsigned											m_using_own_buffer:1;
	unsigned											m_using_reference_buffer:1;
	unsigned											m_is_referenced:1;
	unsigned											m_is_removed:1;
	unsigned											m_is_defualt_null_string:1;
	unsigned											m_reserverd:27;

	size_t												m_offset;
	size_t												m_this_string_length;
}pfx_share_buffer_string_t;

// 强制转换一个buffer成为共享字符串
PFX_INLINE pfx_share_buffer_string_t* init_share_buffer_string_by_buffer(size_t char_size,size_t min_buffer_size,char* PARAM_INOUT string_obj_buffer,pfx_result_t* PARAM_INOUT pstatus);
// 新建一个共享字符串
PFX_INLINE pfx_share_buffer_string_t* new_share_string(size_t char_size,size_t min_char_count,const IAllocator* PARAM_IN pAllocator,pfx_result_t* PARAM_INOUT pstatus);

// 初始化共享字符串
PFX_INLINE pfx_result_t init_share_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,
	size_t string_len,
	const IAllocator* PARAM_IN pchar_allocator);

// 使用现有buffer初始化字符串结构体，同时原有buffer转化为字符结构体
PFX_INLINE pfx_result_t init_share_string_by_charsbuffer(pfx_share_buffer_string_t* PARAM_INOUT pstr,
	const char* PARAM_IN pstr_chars,size_t chars_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator);

pfx_result_t get_share_buffer_sub_string(const pfx_share_buffer_string_t* PARAM_INOUT porign_string,
																	 pfx_share_buffer_string_t* PARAM_INOUT preference_sub_string,size_t ioffset,size_t sub_string_length,
																	 const IAllocator* PARAM_IN pchar_allocator);
pfx_result_t delete_share_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator);

// 重新定义共享字符串大小
PFX_INLINE pfx_result_t resize_share_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,size_t string_len,pfx_bool_t bnew_allocate, const IAllocator* PARAM_IN pchar_allocator);

// 在共享字符串后面添加新的字符串
pfx_result_t append_share_string_by_chars(pfx_share_buffer_string_t* PARAM_INOUT pstr,const char* PARAM_IN str_chars, size_t chars_buffer_size,const IAllocator* PARAM_IN pchar_allocator);
PFX_INLINE pfx_result_t append_share_string_by_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,const pfx_share_buffer_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator);

// 修改共享字符串内的字符
pfx_result_t set_share_string_buffer_chars_at(pfx_share_buffer_string_t* PARAM_INOUT pstr,size_t index,
	const char* PARAM_INOUT set_chars,size_t set_buffer_size,const IAllocator* PARAM_IN pchar_allocator);

PFX_INLINE pfx_result_t set_share_string_buffer_by_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,size_t index,
	const pfx_share_buffer_string_t* PARAM_IN pset_string,const IAllocator* PARAM_IN pchar_allocator);

// 获取共享字符串内的字符
PFX_INLINE char get_share_string_buffer_at(const pfx_share_buffer_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus);

PFX_INLINE const char* get_share_string_buffer_chars_at(const pfx_share_buffer_string_t* PARAM_IN pstr,size_t index);

//////////////////////////////////////////////////////////////////////////



#define BEGIN_SAME_CHAR_STRING_SIZE(CHAR_TYPE,STR_A,STR_A_LEN,STR_B,STR_B_LEN,CMP_FUNC,INDEX)					\
FOR_ONE_LOOP_BEGIN																																										\
	size_t string_len = STR_A_LEN > STR_B_LEN ? STR_B_LEN : STR_A_LEN;																					\
	INDEX = 0;																																															\
																																																				\
	if (null == STR_A || 0 >= STR_A_LEN || null == STR_B || 0 >= STR_B_LEN)																				\
	{																																																			\
		break;																																																\
	}																																																			\
																																																				\
	for (;INDEX< string_len;++INDEX)																																					\
	{																																																			\
		int cmp_result = CMP_FUNC( (CHAR_TYPE)*(STR_A+INDEX),(CHAR_TYPE)*(STR_B+INDEX) );											\
		if (0 != cmp_result)																																										\
		{																																																		\
			break;																																															\
		}																																																		\
	}																																																			\
FOR_ONE_LOOP_END																																											\

typedef enum
{
	DIFFERENCE_STRING = 0,
	STRINGA_BEGIN_INCLUDE_B,
	STRINGB_BEIGN_INCLUDE_A,
}CMP_STRING_TYPE;

#define CMP_TWO_STRING(CHAR_TYPE,STR_A,STR_A_LEN,STR_B,STR_B_LEN,CMP_FUNC,RESULT,EX_RESULT)						\
(FOR_ONE_LOOP_BEGIN																																										\
int iminlen = STR_A_LEN > STR_B_LEN ? STR_B_LEN : STR_A_LEN;																									\
size_t index=0;																																														\
EX_RESULT = STRINGA_BEGIN_INCLUDE_B;																																		\
for (;index<iminlen;++index)																																								\
{																																																				\
	RESULT = CMP_FUNC( (CHAR_TYPE)*(STR_A+INDEX),(CHAR_TYPE)*(STR_B+INDEX) );																\
	if (0 != RESULT)																																													\
	{																																																			\
		EX_RESULT = DIFFERENCE_STRING;																																				\
		break;																																																\
	}																																																			\
}																																																				\
if (0 == RESULT)																																														\
{																																																				\
	RESULT = (int)STR_A_LEN - (int)STR_B_LEN;																																	\
	if (RESULT < 0)																																													\
	{																																																			\
		EX_RESULT = STRINGB_BEIGN_INCLUDE_A;																																\
	}																																																			\
}																																																				\
FOR_ONE_LOOP_END;RESULT;)																																						    \

#define FIND_FIRST_STRING_INDEX(CHAR_TYPE,STR_A,STR_A_LEN,STR_B,STR_B_LEN,CMP_FUNC,INDEX)								\
(FOR_ONE_LOOP_BEGIN																																										\
	size_t loop_count = 0;																																										\
	int icmp_result = 0;																																											\
	int icmp_result_ex = DIFFERENCE_STRING;																																	\
	INDEX = -1;																																															\
	if (STR_A_LEN < STR_B_LEN || null == STR_A || null == STR_B || 0 == STR_B_LEN || 0 == STR_A_LEN)								\
	{																																																			\
		break;																																																\
	}																																																			\
	SAME_COUNT = 0;																																											\
	MAX_SAME_INDEX	= 0;																																									\
	INDEX = 0;																																															\
	loop_count = STR_A_LEN - STR_B_LEN + 1;																																	\
	for (;INDEX<loop_count;++INDEX)																																					\
	{																																																			\
		icmp_result = CMP_TWO_STRING(CHAR_TYPE,STR_A+INDEX,STR_B_LEN,STR_B,STR_B_LEN,CMP_FUNC,icmp_result,icmp_result_ex); \
		if (0 == icmp_result)																																										\
		{																																																		\
			break;																																															\
		}																																																		\
	};																																																			\
	if (0 != icmp_result)																																											\
	{																																																			\
		INDEX = -1;																																														\
	}																																																			\
\
FOR_ONE_LOOP_END;INDEX;)\

#define FIND_FIRST_STRING_INDEX_EX(CHAR_TYPE,STR_A,STR_A_LEN,STR_B,STR_B_LEN,CMP_FUNC,INDEX,SAME_COUNT,MAX_SAME_INDEX)	\
(FOR_ONE_LOOP_BEGIN																																										\
	INDEX = -1;																																															\
	if (STR_A_LEN < STR_B_LEN || null == STR_A || null == STR_B || 0 == STR_B_LEN || 0 == STR_A_LEN)								\
	{																																																			\
		break;																																																\
	}																																																			\
	SAME_COUNT = 0;																																											\
	MAX_SAME_INDEX	= 0;																																									\
	INDEX = 0;																																															\
	for (;INDEX<STR_A_LEN;++INDEX)																																					\
	{																																																			\
		int icmp_result = CMP_FUNC( (CHAR_TYPE)*(STR_A+INDEX),(CHAR_TYPE)*STR_B );															\
		if (0 == icmp_result)																																										\
		{																																																		\
			size_t itemp_index = INDEX + 1;																																				\
			BEGIN_SAME_CHAR_STRING_SIZE(CHAR_TYPE,STR_A+INDEX,STR_A_LEN-INDEX,STR_B,STR_B_LEN,CMP_FUNC,itemp_index);		\
			if (itemp_index == STR_B_LEN)																																				\
			{																																																	\
				MAX_SAME_INDEX = INDEX;																																				\
				SAME_COUNT = STR_B_LEN;																																				\
				break;																																														\
			}																																																	\
			else																																																\
			{																																																	\
				if (SAME_COUNT < itemp_index)																																		\
				{																																																\
					MAX_SAME_INDEX = INDEX;																																			\
					SAME_COUNT = itemp_index;																																			\
				}																																																\
			}																																																	\
		}																																																		\
	};																																																			\
	\
	FOR_ONE_LOOP_END;INDEX;)\


//////////////////////////////////////////////////////////////////////////

// 从内存分配器中删除一个字符串
PFX_INLINE pfx_result_t delete_string(pfx_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator)
{
	pfx_result_t status = relese_string_extern_buffer(pstr,pAllocator);

	if (pAllocator && PFX_STATUS_OK == status)
	{
		pAllocator->dellocate_obj((pfx_long_t)pAllocator, pstr);
	}

	return status;
}

// 清除字符串buffer中的字符串
PFX_INLINE pfx_result_t clear_string(pfx_string_t* PARAM_INOUT pstr,
	const IAllocator* PARAM_IN pAllocator)
{
	return relese_string_extern_buffer(pstr,pAllocator);
}

// 给字符串后面加入新的字符串
PFX_INLINE pfx_result_t append_string_by_string(pfx_string_t* PARAM_INOUT pstr,const pfx_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator)
{
	if (null == pstr || null == pappend_string)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	if (pstr->m_char_size != pappend_string->m_char_size)
	{
		return PFX_STATUS_DIFF_TYPE;
	}
	return append_string_by_chars(pstr,pappend_string->m_pthis_string_data,pappend_string->m_string_buffer_length,pchar_allocator);
}

// 获取指定位置的字节
PFX_INLINE char get_string_buffer_at_unsafe(const pfx_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus)
{
	if (index < pstr->m_string_buffer_length)
	{
		*pstatus = PFX_STATUS_OK;
		return pstr->m_pthis_string_data[index];
	}
	else
	{
		*pstatus = PFX_STATUS_INVALID_PARAMS;
		return (char)0xFF;
	}
}
PFX_INLINE char get_string_buffer_at(const pfx_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus)
{
	pfx_result_t status;
	char return_char = (char)0xFF;
	if (null != pstr)
	{
		if (null != pstr->m_pthis_string_data)
		{
			return_char = get_string_buffer_at_unsafe(pstr,index,&status);
		}
		else
		{
			status = PFX_STATUS_MEM_ERR;
		}

	}
	if (pstatus)
	{
		*pstatus = status;
	}
	return return_char;

}

// 设置指定位置的字节
PFX_INLINE pfx_result_t set_string_buffer_at_unsafe( pfx_string_t* PARAM_INOUT pstr,size_t index,char set_char)
{
	pfx_result_t status = PFX_STATUS_INVALID_PARAMS;
	if (index < pstr->m_string_buffer_length)
	{
		status = PFX_STATUS_OK;
		pstr->m_pthis_string_data[index] = set_char;
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	return status;
}
PFX_INLINE pfx_result_t set_string_buffer_at(pfx_string_t* PARAM_INOUT pstr,size_t index,char set_char)
{
	pfx_result_t status = PFX_STATUS_INVALID_PARAMS;
	if (null != pstr)
	{
		if (null != pstr->m_pthis_string_data)
		{
			status = set_string_buffer_at_unsafe(pstr,index,set_char);
		}
		else
		{
			status = PFX_STATUS_MEM_ERR;
		}

	}
	return status;
}

// 设定指定位置的buffer
PFX_INLINE pfx_result_t set_string_buffer_chars_at(pfx_string_t* PARAM_INOUT pstr,size_t index,const char* PARAM_INOUT set_chars,size_t set_buffer_size)
{
	pfx_result_t status = PFX_STATUS_INVALID_PARAMS;
	if (null != pstr)
	{
		size_t i;
		size_t copy_max_index = set_buffer_size + index;
		if (copy_max_index > pstr->m_string_buffer_length)
		{
			copy_max_index = pstr->m_string_buffer_length;
		}
		for (i=index;i<copy_max_index;++i)
		{
			pstr->m_pthis_string_data[i] = set_chars[i-index];
		}
		status = PFX_STATUS_OK;
	}
	return status;
}
PFX_INLINE const char* get_string_buffer_chars_at(const pfx_string_t* PARAM_IN pstr,size_t index)
{
	const char* preturn_buffer = null;
	if (null != pstr)
	{
		if (null != pstr->m_pthis_string_data && index < pstr->m_string_buffer_length)
		{
			preturn_buffer = pstr->m_pthis_string_data + index;
		}
	}
	return preturn_buffer;
}

//////////////////////////////////////////////////////////////////////////
// 强制转换一个buffer成为共享字符串
PFX_INLINE pfx_share_buffer_string_t* init_share_buffer_string_by_buffer(size_t char_size,size_t min_buffer_size,char* PARAM_INOUT string_obj_buffer,pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_share_buffer_string_t* preturn_string = null;


	if (min_buffer_size < sizeof(pfx_share_buffer_string_t))
	{
		if (null != pstatus)
		{
			*pstatus = PFX_STATUS_INVALID_PARAMS;
		}
		return null;
	}
	else
	{
		pfx_result_t status_res = PFX_STATUS_OK;

		preturn_string = (pfx_share_buffer_string_t*)string_obj_buffer;

		if (min_buffer_size >= (sizeof(pfx_share_buffer_string_t) + sizeof(pfx_string_t)))
		{
			preturn_string->m_reference_string = (pfx_string_t*)(string_obj_buffer + sizeof(pfx_share_buffer_string_t));
			init_string_by_buffer(char_size,min_buffer_size-sizeof(pfx_share_buffer_string_t),(char*)(preturn_string->m_reference_string) ,&status_res);
			preturn_string->m_is_defualt_null_string = 0;
		}
		else
		{
			preturn_string->m_reference_string = null;
			preturn_string->m_is_defualt_null_string = 1;
		}


		if (PFX_STATUS_OK == status_res)
		{
			if (null == init_linked_list_node(&preturn_string->m_list_node))
			{
				status_res = PFX_STATUS_MEM_ERR;
				preturn_string = null;
			}
			else
			{
				preturn_string->m_using_own_buffer = 1;
				preturn_string->m_using_reference_buffer = 0;
				preturn_string->m_is_referenced = 0;
				preturn_string->m_is_removed = 0;
				preturn_string->m_reserverd = 0;
				preturn_string->m_offset = 0;
				preturn_string->m_this_string_length = 0;
			}
			if (null != pstatus)
			{
				*pstatus = status_res;
			}
			return preturn_string;
		}
		else
		{
			return null;
		}
	}
}
// 新建一个共享字符串
PFX_INLINE pfx_share_buffer_string_t* new_share_string(size_t char_size,size_t min_char_count,const IAllocator* PARAM_IN pAllocator,pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_share_buffer_string_t* preturn_string = null;
	char* ptemp_string = null;

	size_t allocate_size = char_size * min_char_count;

	if (null == pAllocator || allocate_size > 0xFFFF)
	{
		if (pstatus)
		{
			*pstatus = PFX_STATUS_INVALID_PARAMS;
		}
		return preturn_string;
	}

	allocate_size += sizeof(pfx_share_buffer_string_t) + sizeof(pfx_string_t);
	ptemp_string = (char*)(pAllocator->allocate_obj((pfx_long_t)pAllocator,allocate_size));

	if (null == ptemp_string)
	{
		if (null != pstatus)
		{
			*pstatus = PFX_STATUS_MEM_LOW;
		}
	}
	else
	{
		preturn_string = init_share_buffer_string_by_buffer(char_size,allocate_size,ptemp_string,pstatus);
		if (null == preturn_string)
		{
			pAllocator->dellocate_obj((pfx_long_t)pAllocator,ptemp_string);
		}
	}

	return preturn_string;
}

// 初始化共享字符串
PFX_INLINE pfx_result_t init_share_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,
	size_t string_len,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	if (null != pstr)
	{
		if (!check_is_linked_list_only_one_node(&pstr->m_list_node))
		{
			linked_list_node_t* pnode = remove_linked_list_node(&pstr->m_list_node);
			pnode = init_linked_list_node(pnode);
			if (null == pnode)
			{
				status = PFX_STATUS_MEM_ERR;
			}
			else  
			{
				if (pstr->m_is_defualt_null_string)
				{
					status = PFX_STATUS_MEM_ERR;
					pstr->m_reference_string = null;
				}
				else
				{
					pstr->m_reference_string = (pfx_string_t*)((pfx_long_t)pstr + sizeof(pfx_share_buffer_string_t));
				}

			}

		}

		if (PFX_STATUS_OK == status)
		{
			status = init_string(pstr->m_reference_string,string_len,pchar_allocator);
		}


	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	if (PFX_STATUS_OK == status)
	{
		pstr->m_using_own_buffer = 1;
		pstr->m_using_reference_buffer = 0;
		pstr->m_is_referenced = 0;
		pstr->m_is_removed = 0;
		pstr->m_reserverd = 0;
		pstr->m_offset = 0;
		pstr->m_this_string_length = pstr->m_reference_string->m_string_buffer_length;
	}
	return status;
};
// 使用现有buffer初始化字符串结构体，同时原有buffer转化为字符结构体
PFX_INLINE pfx_result_t init_share_string_by_charsbuffer(pfx_share_buffer_string_t* PARAM_INOUT pstr,
	const char* PARAM_IN pstr_chars,size_t chars_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	if (null != pstr)
	{
		if (!check_is_linked_list_only_one_node(&pstr->m_list_node))
		{
			linked_list_node_t* pnode = remove_linked_list_node(&pstr->m_list_node);
			pnode = init_linked_list_node(pnode);
			if (null == pnode)
			{
				status = PFX_STATUS_MEM_ERR;
			}
			else 
			{
				if (pstr->m_is_defualt_null_string)
				{
					status = PFX_STATUS_MEM_ERR;
					pstr->m_reference_string = null;
				}
				else
				{
					pstr->m_reference_string = (pfx_string_t*)((pfx_long_t)pstr + sizeof(pfx_share_buffer_string_t));
				}
			}

		}
		if (PFX_STATUS_OK == status)
		{
			status = init_string_by_charsbuffer(pstr->m_reference_string,pstr_chars,chars_buffer_size,pchar_allocator);
		}

	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	if (PFX_STATUS_OK == status)
	{
		pstr->m_using_own_buffer = 1;
		pstr->m_using_reference_buffer = 0;
		pstr->m_is_referenced = 0;
		pstr->m_is_removed = 0;
		pstr->m_reserverd = 0;
		pstr->m_offset = 0;
		pstr->m_this_string_length = pstr->m_reference_string->m_string_buffer_length;
	}
	return status;
}


// 重新定义共享字符串大小
PFX_INLINE pfx_result_t resize_share_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,size_t string_len,pfx_bool_t bnew_allocate, const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	if (null != pstr)
	{
		if (!check_is_linked_list_only_one_node(&pstr->m_list_node))
		{
			linked_list_node_t* pnode = remove_linked_list_node(&pstr->m_list_node);
			pnode = init_linked_list_node(pnode);
			if (null == pnode)
			{
				status = PFX_STATUS_MEM_ERR;
			}
			else 
			{
				if (pstr->m_is_defualt_null_string)
				{
					status = PFX_STATUS_MEM_ERR;
					pstr->m_reference_string = null;
				}
				else
				{
					pstr->m_reference_string = (pfx_string_t*)((pfx_long_t)pstr + sizeof(pfx_share_buffer_string_t));
				}
			}

		}
		if (PFX_STATUS_OK == status)
		{
			status = resize_string(pstr->m_reference_string,string_len,bnew_allocate,pchar_allocator);
		}

	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	if (PFX_STATUS_OK == status)
	{
		pstr->m_using_own_buffer = 1;
		pstr->m_using_reference_buffer = 0;
		pstr->m_is_referenced = 0;
		pstr->m_is_removed = 0;
		pstr->m_reserverd = 0;
		pstr->m_offset = 0;
		pstr->m_this_string_length = pstr->m_reference_string->m_string_buffer_length;
	}
	return status;
}

// 在共享字符串后面添加新的字符串
PFX_INLINE pfx_result_t append_share_string_by_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,const pfx_share_buffer_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator)
{
	if (null == pstr || null == pappend_string || null == pstr->m_reference_string)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	if (null == pappend_string->m_reference_string || 0 >= pappend_string->m_this_string_length)
	{
		return PFX_STATUS_OK;
	}

	if (pstr->m_reference_string->m_char_size != pappend_string->m_reference_string->m_char_size)
	{
		return PFX_STATUS_DIFF_TYPE;
	}

	return append_share_string_by_chars(pstr,pappend_string->m_reference_string->m_pthis_string_data + pappend_string->m_offset,pappend_string->m_this_string_length,pchar_allocator);
}

// 修改共享字符串内的字符

PFX_INLINE pfx_result_t set_share_string_buffer_by_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,size_t index,
	const pfx_share_buffer_string_t* PARAM_IN pset_string,const IAllocator* PARAM_IN pchar_allocator)
{
	if (null == pstr || null == pset_string || null == pstr->m_reference_string)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	if (null == pstr->m_reference_string || 0 >= pset_string->m_this_string_length)
	{
		return PFX_STATUS_OK;
	}

	if (pstr->m_reference_string->m_char_size != pset_string->m_reference_string->m_char_size)
	{
		return PFX_STATUS_DIFF_TYPE;
	}

	return set_share_string_buffer_chars_at(pstr,index,pset_string->m_reference_string->m_pthis_string_data + pset_string->m_offset,pset_string->m_this_string_length,pchar_allocator);
}

// 获取共享字符串内的字符
PFX_INLINE char get_share_string_buffer_at(const pfx_share_buffer_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus)
{
	pfx_result_t status;
	char return_char = (char)0xFF;
	if (null != pstr)
	{
		if (null != pstr->m_reference_string)
		{
			return_char = get_string_buffer_at_unsafe(pstr->m_reference_string,index+pstr->m_offset,&status);
		}
		else
		{
			status = PFX_STATUS_MEM_ERR;
		}

	}
	if (pstatus)
	{
		*pstatus = status;
	}
	return return_char;

}
PFX_INLINE const char* get_share_string_buffer_chars_at(const pfx_share_buffer_string_t* PARAM_IN pstr,size_t index)
{
	const char* preturn_buffer = null;
	if (null != pstr)
	{
		preturn_buffer = get_string_buffer_chars_at(pstr->m_reference_string,index+pstr->m_offset);
	}
	return preturn_buffer;
}

PFX_C_EXTERN_END


#endif			//PFX_STRING_H_
