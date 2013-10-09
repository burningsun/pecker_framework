/*
 * pfx_string.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_STRING_H_
#define		PFX_STRING_H_
 
#include "../pfx_defines.h"
#include "../native/pfx_allocator.h"
//#include "pfx_list.h"

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

	pfx_char_t* m_pthis_string_data;
}pfx_string_t;

// 强制转换一个buffer成为字符串
pfx_string_t* init_string_by_buffer(size_t char_size,size_t min_buffer_size,pfx_char_t* PARAM_INOUT string_obj_buffer,pfx_result_t* PARAM_INOUT pstatus);

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
	const pfx_char_t* PARAM_IN pstr_chars,size_t chars_buffer_size,
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
pfx_result_t append_string_by_chars(pfx_string_t* PARAM_INOUT pstr,const pfx_char_t* PARAM_IN str_chars, size_t chars_buffer_size,const IAllocator* PARAM_IN pchar_allocator);

// 给字符串后面加入新的字符串
PFX_INLINE pfx_result_t append_string_by_string(pfx_string_t* PARAM_INOUT pstr,const pfx_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator);

// 获取字符串的缓冲区
PFX_INLINE const pfx_char_t* get_string_chars_buffer(const pfx_string_t* PARAM_IN pstr);
// 获取字符串有效字符串字节数
PFX_INLINE size_t get_string_chars_length(const pfx_string_t* PARAM_IN pstr);

// 获取指定位置的字节
PFX_INLINE pfx_char_t get_string_buffer_at_unsafe(const pfx_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus);
PFX_INLINE pfx_char_t get_string_buffer_at(const pfx_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus);

// 设置指定位置的字节
PFX_INLINE pfx_result_t set_string_buffer_at_unsafe( pfx_string_t* PARAM_INOUT pstr,size_t index,char set_char);
PFX_INLINE pfx_result_t set_string_buffer_at(pfx_string_t* PARAM_INOUT pstr,size_t index,char set_char);

// 设定指定位置的buffer
PFX_INLINE pfx_result_t set_string_buffer_chars_at(pfx_string_t* PARAM_INOUT pstr,size_t index,const pfx_char_t* PARAM_INOUT set_chars,size_t set_buffer_size);
PFX_INLINE const pfx_char_t* get_string_buffer_chars_at(const pfx_string_t* PARAM_IN pstr,size_t index);


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
PFX_INLINE pfx_char_t get_string_buffer_at_unsafe(const pfx_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus)
{
	if (index < pstr->m_string_buffer_length)
	{
		*pstatus = PFX_STATUS_OK;
		return pstr->m_pthis_string_data[index];
	}
	else
	{
		*pstatus = PFX_STATUS_INVALID_PARAMS;
		return (pfx_char_t)0xFF;
	}
}
PFX_INLINE pfx_char_t get_string_buffer_at(const pfx_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus)
{
	pfx_result_t status;
	pfx_char_t return_char = (pfx_char_t)0xFF;
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
PFX_INLINE pfx_result_t set_string_buffer_chars_at(pfx_string_t* PARAM_INOUT pstr,size_t index,const pfx_char_t* PARAM_INOUT set_chars,size_t set_buffer_size)
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
PFX_INLINE const pfx_char_t* get_string_buffer_chars_at(const pfx_string_t* PARAM_IN pstr,size_t index)
{
	const pfx_char_t* preturn_buffer = null;
	if (null != pstr)
	{
		if (null != pstr->m_pthis_string_data && index < pstr->m_string_buffer_length)
		{
			preturn_buffer = pstr->m_pthis_string_data + index;
		}
	}
	return preturn_buffer;
}

// 获取字符串的缓冲区
PFX_INLINE const pfx_char_t* get_string_chars_buffer(const pfx_string_t* PARAM_IN pstr)
{
	RETURN_INVALID_RESULT (null == pstr,null);
	return pstr->m_pthis_string_data;
}
// 获取字符串有效字符串字节数
PFX_INLINE size_t get_string_chars_length(const pfx_string_t* PARAM_IN pstr)
{
	RETURN_INVALID_RESULT (null == pstr,0);
	return pstr->m_string_buffer_length;
}

PFX_C_EXTERN_END


#endif			//PFX_STRING_H_
