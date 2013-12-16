/*
 * pfx_carray.h
 *
 *  Created on: 2013-12-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CARRAY_H_
#define		PFX_CARRAY_H_

#include "pfx_cstring.h"

PECKER_BEGIN

#define PFX_CARRAY_TEMPLATE_DEFINES template < class item_type_,  const int array_defualt_size_ >
#define PFX_CARRAY_TEMPLATE_PARAMS  < item_type_, array_defualt_size_ >

#define ARRAY_DEFUALT_SIZE STRING_DEFUALT_SIZE
#define ARRAY_DEFUALT_RESIZE_STEP	ARRAY_DEFUALT_SIZE

template < class item_type_,  
const int array_defualt_size_ = ARRAY_DEFUALT_SIZE >
class pfx_carray_linear : public pfx_cstring < item_type_, array_defualt_size_ > 
{
public:
	// 重定义数组大小
	pfx_result_t resize_array (pfx_usize_t nstring_chars_count, pfx_bool_t bnew_allocate = pfx_false,
		pfx_usize_t resize_step = ARRAY_DEFUALT_RESIZE_STEP);
	// 更新数组元素
	pfx_result_t update_array (const item_type_* PARAM_IN  update_data,
		pfx_usize_t update_data_count,
		pfx_usize_t offset = 0, 
		pfx_bool_t  auto_resize = pfx_false,
		pfx_usize_t resize_step = ARRAY_DEFUALT_RESIZE_STEP);
	// 获取数组长度
	PFX_INLINE pfx_usize_t get_length () const
	{
		return get_chars_count();
	}

};

PFX_CARRAY_TEMPLATE_DEFINES
pfx_result_t pfx_carray_linear PFX_CARRAY_TEMPLATE_PARAMS ::resize_array (pfx_usize_t nstring_chars_count, 
	pfx_bool_t bnew_allocate /*= pfx_false*/,
	pfx_usize_t resize_step/* = ARRAY_DEFUALT_RESIZE_STEP*/)
{
	pfx_usize_t current_count = get_buffer_size () / sizeof (item_type_);
	pfx_result_t status_;
	if (0 == resize_step) 
	{
		resize_step = 1;
	}
	if (current_count > nstring_chars_count)
	{
		status_ = resize_string (nstring_chars_count,bnew_allocate);
	}
	else
	{
		pfx_usize_t new_chars_count = nstring_chars_count / resize_step * resize_step;
		if (new_chars_count < nstring_chars_count)
		{
			new_chars_count += resize_step;
		}
		status_ = resize_string (new_chars_count,bnew_allocate);
	}
	return status_;
}

PFX_CARRAY_TEMPLATE_DEFINES
pfx_result_t pfx_carray_linear PFX_CARRAY_TEMPLATE_PARAMS ::update_array (const item_type_* PARAM_IN  update_data,
	pfx_usize_t update_data_count,
	pfx_usize_t offset /*= 0*/, 
	pfx_bool_t  auto_resize /*= pfx_false*/,
	pfx_usize_t resize_step /*= ARRAY_DEFUALT_RESIZE_STEP*/)
{
	RETURN_INVALID_RESULT (null == update_data || 0 == update_data_count,PFX_STATUS_INVALID_PARAMS);
	pfx_usize_t current_count = get_length ();
	pfx_result_t status_ = PFX_STATUS_OK;
	FOR_ONE_LOOP_BEGIN

	if (ioffset >= current_count)
	{
		BREAK_LOOP (status_,PFX_STATUS_OVERRANGE);
	}

	if (offset + update_data_count > current_count)
	{
		if (auto_resize)
		{
			status_ = resize_array(offset + update_data_count,pfx_false,resize_step);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
		}
		else
		{
			update_data_count = current_count - offset; 
		}
	}

	cstring_instance_ PFX_CARRAY_TEMPLATE_PARAMS & instance = get_string_instance ();
	item_type_* items_ = (item_type_*)(instance.m_string_header.m_pthis_string_data);
	pfx_usize_t i=0;
	for (i=0;i<update_data_count;++i)
	{
		items_[i + offset] =  update_data[i];
	}
	status_ = i;


	FOR_ONE_LOOP_END

	return status_;
}

PECKER_END

#endif			//PFX_CARRAY_H_
