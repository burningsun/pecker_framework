/*
 * pfx_share_string.h
 *
 *  Created on: 2013-10-7
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHARE_STRING_H_
#define		PFX_SHARE_STRING_H_
 
#include "pfx_string.h"
#include "pfx_list.h"

PFX_C_EXTERN_BEGIN

// 共享字符串内存的字符串

typedef struct st_pfx_share_string_base pfx_share_string_t;

struct st_pfx_share_string_base
{
	linked_list_node_t							m_list_node;
	pfx_string_t*									m_reference_string;
	size_t												m_char_buffer_offset;
	size_t												m_char_buffer_size;

	unsigned											m_using_internal_buffer : 2;
	unsigned											m_char_size : 14;
	unsigned											m_interbuffer_defualt_buffer_size : 16;											
};

typedef struct st_pfx_share_string_extern pfx_share_string_extern_t;

struct st_pfx_share_string_extern
{
	pfx_share_string_t	m_share_ref;
	pfx_string_t				m_string_instance;
};

// 强制转换一个buffer成为字符串
pfx_share_string_t* init_share_string_by_buffer(size_t char_size,size_t min_buffer_size,
	pfx_char_t* PARAM_INOUT string_obj_buffer,
	pfx_result_t* PARAM_INOUT pstatus);

// 从内存分配器中新建一个字符串
pfx_share_string_t* new_share_string(size_t char_size,size_t min_charbuffer_size,
	const IAllocator* PARAM_IN pAllocator,
	pfx_result_t* PARAM_INOUT pstatus);

// 初始化字符串
pfx_result_t init_share_string(pfx_share_string_t* PARAM_INOUT pstr,
	size_t string_len,
	const IAllocator* PARAM_IN pchar_allocator);

// 使用现有buffer初始化字符串结构体，同时原有buffer转化为字符结构体
pfx_result_t init_share_string_by_charsbuffer(pfx_share_string_t* PARAM_INOUT pstr,
	const pfx_char_t* PARAM_IN pstr_chars,size_t chars_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator);


// 释放一个字符串占有的额外的内存资源
pfx_result_t relese_share_string_extern_buffer(pfx_share_string_t* PARAM_INOUT pstr,
	const IAllocator* PARAM_IN pAllocator);

//pfx_result_t share_string_set_to_independent_buffer(pfx_share_string_t* PARAM_INOUT pstr);

// 从内存分配器中删除一个字符串
PFX_INLINE pfx_result_t delete_share_string(pfx_share_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator);


// 字符串拷贝
pfx_result_t copy_share_string(pfx_share_string_t* PARAM_INOUT pstr_dec,
	const pfx_share_string_t* PARAM_IN pstr_src,const IAllocator* PARAM_IN pchar_allocator);


// 清除字符串buffer中的字符串
PFX_INLINE pfx_result_t clear_share_string(pfx_share_string_t* PARAM_INOUT pstr,
	const IAllocator* PARAM_IN pAllocator);

pfx_share_string_t* get_share_sub_string	(pfx_share_string_t* PARAM_INOUT porign_string,
															size_t ioffset,size_t sub_string_length,
															pfx_bool_t	bnew_buffer,
															const IAllocator* PARAM_IN pchar_allocator,
															pfx_result_t* PARAM_INOUT pstatus);

// 重新定义共享字符串大小
pfx_result_t resize_share_string (pfx_share_string_t* PARAM_INOUT pstr,
	//size_t char_size,
	size_t string_len,pfx_bool_t busing_internal_buffer, pfx_bool_t bnew_allocate, 
	const IAllocator* PARAM_IN pchar_allocator);


// 给字符串后面加入新的字符串
pfx_result_t append_share_string_by_chars (pfx_share_string_t* PARAM_INOUT pstr,
	const char* PARAM_IN str_chars, size_t chars_buffer_size,const IAllocator* PARAM_IN pchar_allocator);

// 获取字符串的缓冲区
PFX_INLINE const pfx_char_t* get_share_string_chars_buffer(const pfx_share_string_t* PARAM_IN pstr);
// 获取字符串有效字符串字节数
PFX_INLINE size_t get_share_string_char_buffer_size(const pfx_share_string_t* PARAM_IN pstr);

// 给字符串后面加入新的字符串
PFX_INLINE pfx_result_t append_share_string_by_string(pfx_share_string_t* PARAM_INOUT pstr,
	const pfx_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator);

// 给字符串后面加入新的字符串
PFX_INLINE pfx_result_t append_share_string_by_share_string(pfx_share_string_t* PARAM_INOUT pstr,
	const pfx_share_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator);


// 获取指定位置的字节
PFX_INLINE pfx_char_t get_share_string_buffer_at(const pfx_share_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus);

// 设置指定位置的字节
PFX_INLINE pfx_result_t set_share_string_buffer_at(pfx_share_string_t* PARAM_INOUT pstr,size_t index,char set_char,const IAllocator* PARAM_IN pchar_allocator);

// 设定指定位置的buffer
PFX_INLINE pfx_result_t set_share_string_buffer_chars_at(pfx_share_string_t* PARAM_INOUT pstr,size_t index,
	const char* PARAM_INOUT set_chars,size_t set_buffer_size,const IAllocator* PARAM_IN pchar_allocator);

PFX_INLINE const pfx_char_t* get_share_string_buffer_chars_at(const pfx_share_string_t* PARAM_IN pstr,size_t index);

//////////////////////////////////////////////////////////////////////////

// 从内存分配器中删除一个字符串
PFX_INLINE pfx_result_t delete_share_string(pfx_share_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator)
{
	pfx_result_t status = relese_share_string_extern_buffer(pstr,pAllocator);

	if (pAllocator && PFX_STATUS_OK == status)
	{
		pAllocator->dellocate_obj((pfx_long_t)pAllocator, pstr);
	}

	return status;
}

// 获取字符串的缓冲区
PFX_INLINE const pfx_char_t* get_share_string_chars_buffer(const pfx_share_string_t* PARAM_IN pstr)
{
	RETURN_INVALID_RESULT ((null == pstr || null == pstr->m_reference_string || 
		pstr->m_char_buffer_offset > pstr->m_reference_string->m_string_buffer_length),null);

	return (pstr->m_reference_string->m_pthis_string_data + pstr->m_char_buffer_offset);
	
}
// 获取字符串有效字符串字节数
PFX_INLINE size_t get_share_string_char_buffer_size(const pfx_share_string_t* PARAM_IN pstr)
{
	RETURN_INVALID_RESULT ( (null == pstr || null == pstr->m_reference_string || 
		(pstr->m_char_buffer_size + pstr->m_char_buffer_offset) > pstr->m_reference_string->m_string_buffer_length),
		0);
	return pstr->m_char_buffer_size;
}


// 给字符串后面加入新的字符串
PFX_INLINE pfx_result_t append_share_string_by_string(pfx_share_string_t* PARAM_INOUT pstr,
	const pfx_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator)
{
	RETURN_INVALID_RESULT (null == pstr || null == pchar_allocator,PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (null == pappend_string,PFX_STATUS_OK);


	return append_share_string_by_chars(pstr,
		pappend_string->m_pthis_string_data,
		pappend_string->m_string_buffer_length,pchar_allocator);
}

// 给字符串后面加入新的字符串
PFX_INLINE pfx_result_t append_share_string_by_share_string(pfx_share_string_t* PARAM_INOUT pstr,
	const pfx_share_string_t* PARAM_IN pappend_string, const IAllocator* PARAM_IN pchar_allocator)
{

	RETURN_INVALID_RESULT (null == pstr || null == pchar_allocator,PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (null == pappend_string || null == pappend_string->m_reference_string,PFX_STATUS_OK);

	return append_share_string_by_chars(pstr,
		pappend_string->m_reference_string->m_pthis_string_data,
		pappend_string->m_reference_string->m_string_buffer_length,pchar_allocator);
}

// 获取指定位置的字节
PFX_INLINE pfx_char_t get_share_string_buffer_at(const pfx_share_string_t* PARAM_IN pstr,size_t index,pfx_result_t* pstatus)
{
	const pfx_char_t * ptemp_char = null;
	ptemp_char = get_share_string_chars_buffer(pstr);
	
	RETURN_INVALID_BY_ACT_RESULT (null == ptemp_char,SET_POINTER_VALUE (pstatus,PFK_STATUS_NULLITEM),(pfx_char_t)(0xFF));
	RETURN_INVALID_BY_ACT_RESULT ((index >= pstr->m_char_buffer_size),SET_POINTER_VALUE (pstatus,PFX_STATUS_OVERRANGE),(pfx_char_t)(0xFF));

	return ptemp_char[index];
}

// 设置指定位置的字节
PFX_INLINE pfx_result_t set_share_string_buffer_at(pfx_share_string_t* PARAM_INOUT pstr,size_t index,char set_char,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_char_t * ptemp_char = null;
	pfx_result_t status;

	status = resize_share_string(pstr,pstr->m_char_buffer_size,pfx_true,pfx_false,pchar_allocator);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	ptemp_char = (pfx_char_t*)get_share_string_chars_buffer(pstr);

	RETURN_INVALID_RESULT (null == ptemp_char,PFK_STATUS_NULLITEM);

	RETURN_INVALID_RESULT ((index >= pstr->m_char_buffer_size),PFX_STATUS_OVERRANGE);

	ptemp_char[index] = set_char;
	return PFX_STATUS_OK;
}

// 设定指定位置的buffer
PFX_INLINE pfx_result_t set_share_string_buffer_chars_at(pfx_share_string_t* PARAM_INOUT pstr,size_t index,
	const char* PARAM_INOUT set_chars,size_t set_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_char_t * ptemp_char = null;
	pfx_result_t status;

	status = resize_share_string(pstr,pstr->m_char_buffer_size,pfx_true,pfx_false,pchar_allocator);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	RETURN_INVALID_RESULT (null == pstr,PFX_STATUS_INVALID_PARAMS);

	ptemp_char = (pfx_char_t*)get_share_string_chars_buffer(pstr);
	
	RETURN_INVALID_RESULT (null == ptemp_char || index >= pstr->m_char_buffer_size,null);

	if (index + set_buffer_size > pstr->m_char_buffer_size)
	{
		set_buffer_size = pstr->m_char_buffer_size - index;
	}
	memcpy (ptemp_char+index,set_chars,set_buffer_size);
	return PFX_STATUS_OK;
}

PFX_INLINE const pfx_char_t* get_share_string_buffer_chars_at(const pfx_share_string_t* PARAM_IN pstr,size_t index)
{
	const pfx_char_t * ptemp_char = null;
	ptemp_char = get_share_string_chars_buffer(pstr);
	RETURN_INVALID_RESULT (null == ptemp_char || index >= pstr->m_char_buffer_size,null);
	return (ptemp_char + index);
}

PFX_C_EXTERN_END


#endif			//PFX_SHARE_STRING_H_
