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

PFX_BEGIN

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
pfx_string_t* init_string_by_buffer(size_t char_size,size_t min_buffer_size,char* PARAM_INOUT string_obj_buffer,pfx_result* PARAM_INOUT pstatus);

// 从内存分配器中新建一个字符串
pfx_string_t* new_string(size_t char_size,size_t min_char_count,const IAllocator* PARAM_IN pAllocator,pfx_result* PARAM_INOUT pstatus);

// 释放一个字符串占有的额外的内存资源
pfx_result relese_string_extern_buffer(pfx_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator);

// 从内存分配器中删除一个字符串
inline pfx_result delete_string(pfx_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator)
{
	pfx_result status = relese_string_extern_buffer(pstr,pAllocator);

	if (pAllocator && PFX_STATUS_OK == status)
	{
		pAllocator->dellocate_obj((Long)pAllocator, pstr);
	}

	return status;
}

// 初始化字符串
pfx_result init_string(pfx_string_t* PARAM_INOUT pstr,
	size_t string_len,
	const IAllocator* PARAM_IN pchar_allocator);

pfx_result init_string_by_charsbuffer(pfx_string_t* PARAM_INOUT pstr,
	const void* PARAM_IN pstr_chars,size_t chars_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator);

pfx_result copy_string(pfx_string_t* PARAM_INOUT pstr_dec,
	const pfx_string_t* PARAM_IN pstr_src,const IAllocator* PARAM_IN pchar_allocator);

inline pfx_result clear_string(pfx_string_t* PARAM_INOUT pstr,
const IAllocator* PARAM_IN pAllocator)
{
	return relese_string_extern_buffer(pstr,pAllocator);
}

pfx_result swap_string(pfx_string_t* PARAM_INOUT pstrA,pfx_string_t* PARAM_INOUT pstrB);

pfx_result swap_string_by_allocator(pfx_string_t* PARAM_INOUT pstrA,pfx_string_t* PARAM_INOUT pstrB,
	const IAllocator* PARAM_IN pchar_allocator);

pfx_result resize_string(pfx_string_t* PARAM_INOUT pstr,size_t string_len,Bool bnew_allocate, const IAllocator* PARAM_IN pchar_allocator);

pfx_result get_sub_string(const pfx_string_t* PARAM_IN porign_string, pfx_string_t* PARAM_INOUT preference_sub_string,size_t ioffset,size_t sub_string_length,const IAllocator* PARAM_IN pchar_allocator);

pfx_result append_string_by_chars(pfx_string_t* PARAM_INOUT pstr,const char* PARAM_IN str_chars, size_t chars_buffer_size,const IAllocator* PARAM_IN pchar_allocator);

inline pfx_result append_string_by_string(pfx_string_t* PARAM_INOUT pstr,const pfx_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator)
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

// 共享字符串内存的字符串
typedef struct st_pfx_share_buffer_string
{
	//struct st_pfx_share_buffer_string*	m_prev_string;
	//struct st_pfx_share_buffer_string*	m_next_string;
	linked_list_node_t							m_list_node;

	pfx_string_t*									m_reference_string;

	size_t												m_offset;
	size_t												m_this_string_length;
}pfx_share_buffer_string_t;

inline pfx_share_buffer_string_t* init_share_buffer_string_by_buffer(size_t char_size,size_t min_buffer_size,char* PARAM_INOUT string_obj_buffer,pfx_result* PARAM_INOUT pstatus)
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
		pfx_result status_res = PFX_STATUS_OK;

		preturn_string = (pfx_share_buffer_string_t*)string_obj_buffer;
		
		if (min_buffer_size >= (sizeof(pfx_share_buffer_string_t) + sizeof(pfx_string_t)))
		{
			preturn_string->m_reference_string = (pfx_string_t*)(string_obj_buffer + sizeof(pfx_share_buffer_string_t));
			init_string_by_buffer(char_size,min_buffer_size-sizeof(pfx_share_buffer_string_t),(char*)(preturn_string->m_reference_string) ,&status_res);
		}
		else
		{
			preturn_string->m_reference_string = null;
		}
		
		
		if (PFX_STATUS_OK == status_res)
		{
			//preturn_string->m_next_string = null;
			//preturn_string->m_prev_string = null;
			if (null == init_linked_list_node(&preturn_string->m_list_node))
			{
				status_res = PFX_STATUS_MEM_ERR;
				preturn_string = null;
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
inline pfx_share_buffer_string_t* new_share_string(size_t char_size,size_t min_char_count,const IAllocator* PARAM_IN pAllocator,pfx_result* PARAM_INOUT pstatus)
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
	ptemp_string = (char*)(pAllocator->allocate_obj((Long)pAllocator,allocate_size));

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
			pAllocator->dellocate_obj((Long)pAllocator,ptemp_string);
		}
	}

	return preturn_string;
}

pfx_result get_share_buffer_sub_string(const pfx_share_buffer_string_t* PARAM_IN porign_string,pfx_share_buffer_string_t* PARAM_INOUT preference_sub_string,size_t ioffset,size_t sub_string_length);


pfx_result delete_share_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator);

PFX_END


#endif			//PFX_STRING_H_
