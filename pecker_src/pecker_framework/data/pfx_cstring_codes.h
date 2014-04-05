/*
 * pfx_cstring_codes.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CSTRING_CODES_H_
#define		PFX_CSTRING_CODES_H_

#include "../pfx_defines.h"
#include "pfx_cstring.h"



PECKER_BEGIN

PFX_CSTRING_TEMPLATE_DEFINES
pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::pfx_cstring () : m_extern_string_buffer_ptr (null)
{
	if (CACHE_BUFFER_SIZE > 0)
	{
		m_header.m_element_ptr = m_cache_buffer;
		m_header.m_element_buffer_size = CACHE_BUFFER_SIZE;
		m_header.m_element_count = 0;
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::pfx_cstring (const pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & other_) throw (pfx_result_t)
{
	m_extern_string_buffer_ptr = null;
	if (CACHE_BUFFER_SIZE > 0)
	{
		m_header.m_element_ptr = m_cache_buffer;
		m_header.m_element_buffer_size = CACHE_BUFFER_SIZE;
		m_header.m_element_count = 0;
	}

	pfx_result_t status;
	status = append_string(&other_);

	if (PFX_STATUS_OK != status)
	{
		throw (status);
	}


}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS :: ~pfx_cstring ()
{
	resize_string(0);
	garbage_collection();
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS :: reset_header ()
{
	if (CACHE_BUFFER_SIZE > 0)
	{
		m_header.m_element_ptr = m_cache_buffer;
		m_header.m_element_buffer_size = CACHE_BUFFER_SIZE;
		m_header.m_element_count = 0;
	}
	else
	{
		m_header.m_element_ptr = null;
		m_header.m_element_buffer_size = 0;
		m_header.m_element_count = 0;
	}
	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE element_*		pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS :: resize_new_stringbuffer 
																(const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																pfx_usize_t elememt_size, 
																pfx_result_t& PARAM_INOUT status_)
{
	element_* result_elem_ptr;
	element_* last_elem_ptr;

	status_ = PFX_STATUS_OK;
	// 当新指定的BUF小于或者等于原有的BUF，不再重现申请
	if (elememt_size <= header.m_element_buffer_size)
	{
		result_elem_ptr = null;
		return result_elem_ptr;
	}
	last_elem_ptr = (element_*) header.m_element_ptr;

	//// 
	//if (CACHE_BUFFER_SIZE > 0 && last_elem_ptr == m_cache_buffer)
	//{
	//	result_elem_ptr = new_string_buffer (elememt_size);
	//	if (null == result_elem_ptr)
	//	{
	//		status_ = PFX_STATUS_MEM_LOW;
	//	}
	//	return result_elem_ptr;
	//}
	// 当新指定的BUF大于原有的BUF，先从原有系统BUF中重新申请
	result_elem_ptr = reallocate_string_buffer (last_elem_ptr,elememt_size);
	// 如果重新申请失败，则新建一个BUF
	if (!result_elem_ptr)
	{
		result_elem_ptr = new_string_buffer (elememt_size);
		if (null == result_elem_ptr)
		{
			status_ = PFX_STATUS_MEM_LOW;
		}
	}
	else
	{
		result_elem_ptr = null;
	}
	return result_elem_ptr;
	
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t		pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::remove_referance ()
{
	pfx_result_t status;

	if (is_reference ())
	{
		//enable_reference (PFX_BOOL_TRUE);
		IPfx_string PFX_STRING_TEMPLATE_PARAMS* this_ptr = this;
		pfx_clist_base <  IPfx_string PFX_STRING_TEMPLATE_PARAMS  >  :: remove_list_node_unsafe (this_ptr);
		pfx_clist_base <  IPfx_string PFX_STRING_TEMPLATE_PARAMS  >  :: init_list_node (this_ptr);
		//enable_reference (PFX_BOOL_FALSE);

		status = reset_header ();
		m_extern_string_buffer_ptr = null;
	}
	else
	{
		status = PFX_STATUS_OK;
	}
	return status;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE  pfx_result_t		pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::add_referance (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr)
{
	const IPfx_string PFX_STRING_TEMPLATE_PARAMS* insert_ptr;
	//enable_reference (PFX_BOOL_TRUE);
	//other_ptr->enable_reference (PFX_BOOL_TRUE);
	insert_ptr = pfx_clist_base < IPfx_string PFX_STRING_TEMPLATE_PARAMS >  :: insert_list_node_back (this,other_ptr);
	//enable_reference (PFX_BOOL_FALSE);
	if (insert_ptr)
	{
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_FAIL;
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE  pfx_boolean_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::is_reference ()
{
	return (pfx_boolean_t) (get_next_node () || get_prev_node ());
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE element_*		pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::reallocate_string_buffer 
																																			(element_* PARAM_INOUT elem_ptr, 
																																			pfx_usize_t element_count)
{
	return null;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE  element_*	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::new_string_buffer (pfx_usize_t element_count)
{
	return new element_[element_count];
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE  pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::delete_string_buffer (element_* PARAM_IN elem_ptr)
{
	if (elem_ptr)
	{
		delete [] elem_ptr;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE pfx_ulong_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::get_string_type_code () const
{
	return PFX_CSTRING_CODE;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																																	pfx_boolean_t	bheader_cache_buffer, 
																																	pfx_boolean_t & PARAM_INOUT is_reference)
{
	pfx_result_t status;
	is_reference = PFX_BOOL_FALSE;
	if (bheader_cache_buffer)
	{
		if (CACHE_BUFFER_SIZE && header.m_element_count <= CACHE_BUFFER_SIZE)
		{
			set_charbuffer_at (0,header.m_element_ptr,header.m_element_count);
			garbage_collection (GC_USER_MODE,CACHE_BUFFER_SIZE);	
		}
		else
		{
			//is_reference = pfx_true;
			//m_header.m_element_ptr = header.m_element_ptr;
			//m_header.m_element_count = header.m_element_count;
			//m_header.m_element_buffer_size = header.m_element_buffer_size;
			status = init_string (header.m_element_ptr,header.m_element_count);
		}
	}
	else
	{
		//is_reference = pfx_true;
		//m_header.m_element_ptr = header.m_element_ptr;
		//m_header.m_element_count = header.m_element_count;
		//m_header.m_element_buffer_size = header.m_element_buffer_size;
		status = init_string (header.m_element_ptr,header.m_element_count);
	}
	

	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t  pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::attach_extern_string_buffer (element_* PARAM_IN elem_ptr)
{
	pfx_result_t status; 
	status = PFX_STATUS_OK;
	//if (is_reference())
	//{
	//	status = remove_referance();
	//}

	//if (PFX_STATUS_OK == status)
	//{
	//		m_extern_string_buffer_ptr = elem_ptr;
	//}
	m_extern_string_buffer_ptr = elem_ptr;
	return status;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE const element_* pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::get_string () const
{
	return m_header.m_element_ptr;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::get_length () const
{
	return m_header.m_element_count;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::get_string_buffer_size () const
{
	return m_header.m_element_buffer_size;
}

PFX_CSTRING_TEMPLATE_DEFINES
const element_*		pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::get_charbuffer_at (pfx_uindex_t index_) const
{
	if (index_ < m_header.m_element_count)
	{
		return  (m_header.m_element_ptr + index_);
	}
	else
	{
		return null;
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_usize_t					pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::set_charbuffer_at (pfx_uindex_t index_, 
																														const element_* PARAM_IN char_buffer, 
																														pfx_usize_t buf_size)
{
	pfx_usize_t success_count;
	success_count = 0;
	if (null == char_buffer || 0 == buf_size)
	{
		return success_count;
	}

	if (null != char_buffer && index_ < m_header.m_element_count)
	{
		pfx_result_t status;
		element_* element_ptr;
		status = PFX_STATUS_OK;

		// 消除共享BUF的影响
		if (is_reference ())
		{
			// 如果BUF与其他字符串共享
			pfx_usize_t  new_size;
			element_* new_buffer_ptr;
			
			new_size = m_header.m_element_count;
			new_buffer_ptr = null;

			// 先移除BUF共享
			status = remove_referance ();

			if (PFX_STATUS_OK ==  status)
			{
				// 移除BUF成功后，重定义BUF大小，期间可能会产生新的BUF，
				// 或者沿用原来的BUF
				new_buffer_ptr = resize_new_stringbuffer (m_header,new_size,status);
			}

			if (PFX_STATUS_OK == status)
			{
				m_header.m_element_count = new_size;
				if (new_buffer_ptr)
				{
					m_header.m_element_buffer_size = new_size;
					m_header.m_element_ptr				= new_buffer_ptr;
					m_extern_string_buffer_ptr			= new_buffer_ptr;
				}
			}

		}

		// 对char_buffer是否为当字符串中某段BUF进行鉴定，并做出移动或者直接拷贝的操作
		FOR_ONE_LOOP_BEGIN

		success_count = (buf_size + index_) > m_header.m_element_count ?
			 m_header.m_element_count - index_ : buf_size;

		if (!success_count)
		{
			break;
		}

		if (m_header.m_element_ptr <= char_buffer && 
			char_buffer < (m_header.m_element_ptr + m_header.m_element_count))
		{
			//char_buffer为当字符串中某段BUF
			pfx_uindex_t offset;
			offset = (pfx_uindex_t)char_buffer - (pfx_uindex_t)m_header.m_element_ptr;
			if (offset == index_)
			{
				break;
			}

			if (offset < index_ && offset + success_count > index_)
			{
				element_ptr = m_header.m_element_ptr + index_;
				pfx_uindex_t i = success_count - 1;
				for (;i>=0;--i)
				{
					element_ptr [i] = char_buffer [i];
				}
				break;
			}
		}
		
		element_ptr = m_header.m_element_ptr + index_;
		for (pfx_uindex_t i=0;i<success_count; ++i)
		{
			element_ptr [i] = char_buffer [i];
		}
				
		FOR_ONE_LOOP_END
	}

	return success_count;
}

PFX_CSTRING_TEMPLATE_DEFINES
const element_*		pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::sub_string_buffer (pfx_uindex_t index_) const
{
	return get_charbuffer_at (index_);
}

PFX_CSTRING_TEMPLATE_DEFINES
const IPfx_string PFX_STRING_TEMPLATE_PARAMS*		pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::sub_string (pfx_uindex_t index_, 
																																													IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)
{
	return sub_string (index_, (pfx_usize_t) (-1), sub_string_ptr);
}

PFX_CSTRING_TEMPLATE_DEFINES
const IPfx_string PFX_STRING_TEMPLATE_PARAMS*		pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::sub_string (pfx_uindex_t index_, 
																																													pfx_usize_t		sub_string_size, 
																																													IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)
{
	pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS header;

	pfx_boolean_t		is_reference_header;
	pfx_result_t			status;
	pfx_boolean_t		using_cache_buffer;
	element_*				elem_ptr;
	IPfx_string_header_operate < element_ >* cov_string_ptr;

	RETURN_INVALID_RESULT (null == sub_string_ptr,null);

	if ((sub_string_ptr == this) || 
		(sub_string_ptr->get_string_type_code () != this->get_string_type_code ()))
	{
		const element_* string_buffer_ptr;
		pfx_usize_t			string_size;
		string_buffer_ptr = get_charbuffer_at(index_);
		if (string_buffer_ptr)
		{
			string_size = m_header.m_element_count - index_;
			if (string_size > sub_string_size)
			{
				string_size = sub_string_size;
			}
		}
		else
		{
			string_size = 0;
		}
		status = sub_string_ptr->init_string (string_buffer_ptr, string_size);
		if (PFX_STATUS_OK == status)
		{
			return sub_string_ptr;
		}
		else
		{
			return null;
		}
	}

	elem_ptr = m_extern_string_buffer_ptr;
	is_reference_header = PFX_BOOL_FALSE;

	if ((CACHE_BUFFER_SIZE > 0) && 
		(m_cache_buffer <= m_header.m_element_ptr) && 
		((m_cache_buffer + CACHE_BUFFER_SIZE) > m_header.m_element_ptr))
	{
		using_cache_buffer = PFX_BOOL_TRUE;
	}
	else
	{
		using_cache_buffer = PFX_BOOL_FALSE;
	}

	
	if (index_ > m_header.m_element_count)
	{
		header.m_element_buffer_size	= m_header.m_element_buffer_size;
		header.m_element_count			= 0;
		header.m_element_ptr				= m_header.m_element_ptr;
	}
	else
	{
		header.m_element_buffer_size	= m_header.m_element_buffer_size - index_;
		header.m_element_count = m_header.m_element_count - index_;

		if (header.m_element_count > sub_string_size)
		{
			header.m_element_count = sub_string_size;
		}

		header.m_element_ptr = m_header.m_element_ptr + index_;
	}


	cov_string_ptr = sub_string_ptr;
	status = cov_string_ptr->copy_header (header,using_cache_buffer,is_reference_header);
	
	if (PFX_STATUS_OK == status && is_reference_header)
	{
		status = cov_string_ptr->attach_extern_string_buffer (elem_ptr);
	}
	
	if (PFX_STATUS_OK == status && is_reference_header)
	{		
		status = add_referance (sub_string_ptr);
		if (PFX_STATUS_OK != status)
		{
			if (!using_cache_buffer)
			{
				cov_string_ptr->reset_header ();
			}
			else
			{
				sub_string_ptr->init_string ((pfx_usize_t)0);
				sub_string_ptr->garbage_collection ();
			}
		
			sub_string_ptr = null;
		}
	}

	return sub_string_ptr;



}

PFX_CSTRING_TEMPLATE_DEFINES
const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::sub_string_const (pfx_uindex_t index_,
																																																				pfx_usize_t		sub_string_size, 
																																																				IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)  const
{
	return sub_string_const (index_, (pfx_usize_t)(-1), sub_string_ptr);
}

PFX_CSTRING_TEMPLATE_DEFINES
const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::sub_string_const (pfx_uindex_t index_,
	IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)  const
{
	RETURN_INVALID_RESULT (null == sub_string_ptr || this == sub_string_ptr,null);

	const element_*	string_buffer_ptr;
	pfx_usize_t				string_size;
	pfx_usize_t				sub_string_size;
	pfx_result_t			status;

	string_buffer_ptr = get_charbuffer_at(index_);
	sub_string_size = get_length ();

	if (string_buffer_ptr)
	{
		string_size = m_header.m_element_count - index_;
		if (string_size > sub_string_size)
		{
			string_size = sub_string_size;
		}
	}
	else
	{
		string_size = 0;
	}

	status = sub_string_ptr->init_string (string_buffer_ptr, string_size);

	if (PFX_STATUS_OK == status)
	{
		return sub_string_ptr;
	}
	else
	{
		return null;
	}
}



PFX_CSTRING_TEMPLATE_DEFINES
pfx_boolean_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::find_first_string (const element_* PARAM_IN str_chars_buffer_ptr,
																																		pfx_usize_t buffer_size,pfx_uindex_t& find_index) const
{
	pfx_boolean_t is_find;
	is_find = PFX_BOOL_FALSE;
	
	RETURN_RESULT (null == str_chars_buffer_ptr || 
		0 == buffer_size || 
		buffer_size > m_header.m_element_count,is_find);

	if (str_chars_buffer_ptr >= m_header.m_element_ptr && 
		str_chars_buffer_ptr < m_header.m_element_ptr + m_header.m_element_count)
	{
		pfx_uindex_t offset = str_chars_buffer_ptr - m_header.m_element_ptr;
		if (buffer_size <= m_header.m_element_count - offset)
		{
			find_index = offset;
			is_find = PFX_BOOL_TRUE;
		}
	}
	else
	{
		pfx_uindex_t i;
		pfx_uindex_t same_count;
		pfx_usize_t		cmp_count;
		int					cmp_result;
		i = 0;
		same_count = 0;
		cmp_count = m_header.m_element_count - buffer_size;

		for (; i<cmp_count; ++i)
		{
			for (same_count = 0; same_count < buffer_size; ++same_count)
			{
				cmp_result = elem_compare::compare (m_header.m_element_ptr [i+same_count], str_chars_buffer_ptr[same_count]);
				if (cmp_result)
				{
					break;
				}
			}
			if (same_count == buffer_size)
			{
				is_find = PFX_BOOL_TRUE;
				find_index = i;
				break;
			}
		}
		
	}
	return is_find;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_boolean_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::find_first_string (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN find_string_ptr,
																																		pfx_uindex_t & find_index) const
{
	pfx_boolean_t is_find;
	if (find_string_ptr)
	{
		if (find_string_ptr == this)
		{
			is_find = PFX_BOOL_TRUE;
		}
		else
		{
			is_find = find_first_string (find_string_ptr->get_string (), find_string_ptr->get_length (), find_index);
		}
	}
	else
	{
		is_find = PFX_BOOL_FALSE;
	}
	return is_find;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_boolean_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::find_string (pfx_uindex_t begin_index, const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size,pfx_uindex_t& find_index) const
{
	pfx_boolean_t is_find;
	is_find = PFX_BOOL_FALSE;
	const element_* this_search_elem_ptr;
	pfx_usize_t			  this_search_elem_size;


	RETURN_RESULT (null == str_chars_buffer_ptr || 
		0 == buffer_size || 
		begin_index >= m_header.m_element_count,is_find);

	this_search_elem_ptr	= m_header.m_element_ptr + begin_index;
	this_search_elem_size =  m_header.m_element_count - begin_index;

	RETURN_RESULT (buffer_size > this_search_elem_size, is_find);

	if (str_chars_buffer_ptr >= this_search_elem_ptr && 
		str_chars_buffer_ptr < this_search_elem_ptr + this_search_elem_size)
	{
		pfx_uindex_t offset;
		offset = str_chars_buffer_ptr - m_header.m_element_ptr;
		if (buffer_size <= m_header.m_element_count - offset)
		{
			find_index = offset;
			is_find = PFX_BOOL_TRUE;
		}
	}
	else
	{
		pfx_uindex_t i;
		pfx_uindex_t same_count;
		pfx_usize_t		cmp_count;
		int					cmp_result;
		i = begin_index;
		same_count = 0;
		cmp_count = this_search_elem_size - buffer_size;

		for (; i<cmp_count; ++i)
		{
			for (same_count = 0; same_count < buffer_size; ++same_count)
			{
				cmp_result = elem_compare::compare (m_header.m_element_ptr [i+same_count], str_chars_buffer_ptr[same_count]);
				if (cmp_result)
				{
					break;
				}
			}
			if (same_count == buffer_size)
			{
				is_find = PFX_BOOL_TRUE;
				find_index = i;// + begin_index;
				break;
			}
		}

	}
	return is_find;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_boolean_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::find_string (pfx_uindex_t begin_index, IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT find_string_ptr,pfx_uindex_t& find_index) const
{
	pfx_boolean_t is_find;
	if (find_string_ptr)
	{
		if (find_string_ptr == this)
		{
			is_find = (0 == begin_index) ? PFX_BOOL_TRUE : PFX_BOOL_FALSE;
		}
		else
		{
			is_find = find_string (begin_index, find_string_ptr->get_string (), find_string_ptr->get_length (), find_index);
		}
	}
	else
	{
		is_find = PFX_BOOL_FALSE;
	}
	return is_find;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_boolean_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::find_near_string (pfx_uindex_t begin_index, const element_* PARAM_IN str_chars_buffer_ptr,
																																				pfx_usize_t buffer_size,pfx_uindex_t& find_index, pfx_usize_t& same_chars_count) const
{
	pfx_boolean_t is_find;
	is_find = PFX_BOOL_FALSE;
	const element_* this_search_elem_ptr;
	pfx_usize_t			  this_search_elem_size;


	RETURN_RESULT (null == str_chars_buffer_ptr || 
		0 == buffer_size || 
		begin_index >= m_header.m_element_count,
		is_find);

	this_search_elem_ptr	= m_header.m_element_ptr + begin_index;
	this_search_elem_size =  m_header.m_element_count - begin_index;

	//RETURN_RESULT (buffer_size > this_search_elem_size, is_find);

	if (str_chars_buffer_ptr >= this_search_elem_ptr && 
		str_chars_buffer_ptr < this_search_elem_ptr + this_search_elem_size)
	{
		pfx_uindex_t offset;
		pfx_uindex_t to_cmp_size;
		offset = str_chars_buffer_ptr - m_header.m_element_ptr;
		to_cmp_size = m_header.m_element_count - offset;
		is_find = PFX_BOOL_TRUE;
		find_index = offset;
		same_chars_count = (buffer_size <= to_cmp_size) ? buffer_size : to_cmp_size;
	}
	else
	{
		pfx_uindex_t i;
		pfx_uindex_t same_count;
		pfx_usize_t		cmp_count;
		int					cmp_result;
		i = begin_index;
		same_count = 0;
		cmp_count = this_search_elem_size - buffer_size;

		for (; i<cmp_count; ++i)
		{
			for (same_count = 0; same_count < buffer_size; ++same_count)
			{
				cmp_result = elem_compare::compare (m_header.m_element_ptr [i+same_count], str_chars_buffer_ptr[same_count]);
				if (cmp_result)
				{
					break;
				}
			}
			if (same_count > 0)
			{
				is_find = PFX_BOOL_TRUE;
				find_index = i;// + begin_index;
				same_chars_count = same_count;
				break;
			}
		}
	}

	return is_find;
}
PFX_CSTRING_TEMPLATE_DEFINES
pfx_boolean_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::find_near_string (pfx_uindex_t begin_index, 
																												IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT find_string_ptr,
																												pfx_uindex_t& find_index, pfx_usize_t& same_chars_count) const
{
	pfx_boolean_t is_find;
	if (find_string_ptr)
	{
		if (find_string_ptr == this && 0 == begin_index)
		{
			is_find =	PFX_BOOL_TRUE;
			find_index = 0;
			same_chars_count = get_length();
		}
		else
		{
			is_find = find_near_string (begin_index, find_string_ptr->get_string (), 
															find_string_ptr->get_length (), find_index, same_chars_count);
		}
	}
	else
	{
		is_find = PFX_BOOL_FALSE;
	}
	return is_find;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::init_string (pfx_usize_t buffer_size,element_*& PARAM_INOUT del_element_ptr)
{
	pfx_result_t			status;
	//const element_*	str_chars_buffer_ptr;
	pfx_usize_t				new_size;
	element_*				new_buffer_ptr;

	//RETURN_INVALID_RESULT (0 == buffer_size,PFX_STATUS_INVALID_PARAMS);
	if (0 == buffer_size)
	{
		if (is_reference ())
		{
			// 先移除BUF共享
			status = remove_referance ();
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
		}
		m_header.m_element_count = 0;
		del_element_ptr = null;
		return PFX_STATUS_OK;
	}



	del_element_ptr = null;
	status = PFX_STATUS_OK;

	new_size = (buffer_size > m_header.m_element_count) ? buffer_size : m_header.m_element_count;
	new_buffer_ptr = null;

	del_element_ptr = null;
	//str_chars_buffer_ptr = get_charbuffer_at (0);

	// 消除共享BUF的影响
	if (is_reference ())
	{
		// 先移除BUF共享
		status = remove_referance ();

		if (PFX_STATUS_OK ==  status)
		{
			// 移除BUF成功后，重定义BUF大小，期间可能会产生新的BUF，
			// 或者沿用原来的BUF
			new_buffer_ptr = resize_new_stringbuffer (m_header,new_size,status);
		}

		if (PFX_STATUS_OK == status)
		{
			m_header.m_element_count = buffer_size;
			if (new_buffer_ptr)
			{
				m_header.m_element_buffer_size = new_size;
				m_header.m_element_ptr				= new_buffer_ptr;
				m_extern_string_buffer_ptr			= new_buffer_ptr;
			}
		}
	}
	else
	{
		new_buffer_ptr = resize_new_stringbuffer (m_header,new_size,status);
		if (PFX_STATUS_OK == status)
		{
			m_header.m_element_count = buffer_size;
			if (new_buffer_ptr)
			{
				if (m_header.m_element_ptr)
				{
					del_element_ptr = m_extern_string_buffer_ptr;
				}

				m_header.m_element_buffer_size = new_size;
				m_header.m_element_ptr				= new_buffer_ptr;
				m_extern_string_buffer_ptr			= new_buffer_ptr;
			}
		}
	}

	//RETURN_INVALID_RESULT (PFX_STATUS_OK != status, status);

	//pfx_usize_t success_count;
	//success_count = set_charbuffer_at (0, str_chars_buffer_ptr, buffer_size);
	//if (success_count != buffer_size)
	//{
	//	status = PFX_STATUS_FAIL;
	//}
	return status;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::init_string (pfx_usize_t size_)
{
	element_* del_element_ptr;
	pfx_result_t status;

	del_element_ptr = null;
	status = init_string (size_,del_element_ptr);
	if (del_element_ptr)
	{
		delete_string_buffer (del_element_ptr);
	}
	return status;
}


PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::init_string (const element_* PARAM_IN str_chars_buffer_ptr,
																																pfx_usize_t buffer_size)
{
	element_* del_element_ptr;
	pfx_result_t status;

	del_element_ptr = null;
	status = init_string (buffer_size,del_element_ptr);
	
	if (PFX_STATUS_OK == status)
	{
		pfx_usize_t successed_count;
		successed_count = set_charbuffer_at (0,str_chars_buffer_ptr,buffer_size);
		if (successed_count != buffer_size)
		{
			status = PFX_STATUS_FAIL;
		}
	}

	if (del_element_ptr)
	{
		delete_string_buffer (del_element_ptr);
	}
	return status;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::init_string (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr)
{
		RETURN_INVALID_RESULT (null == other_ptr,PFX_STATUS_INVALID_PARAMS);
		return init_string (other_ptr->get_string (),other_ptr->get_length ());
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::resize_string (pfx_usize_t size_)
{

	const element_*	str_chars_buffer_ptr;
	element_*				del_element_ptr;
	pfx_usize_t				buffer_size;
	pfx_result_t			status;

	str_chars_buffer_ptr = get_string ();
	buffer_size = get_length ();

	del_element_ptr = null;
	status = init_string (size_,del_element_ptr);

	if (size_ < buffer_size)
	{
		buffer_size = size_;
	}

	if (PFX_STATUS_OK == status)
	{
		pfx_usize_t successed_count;
		successed_count = set_charbuffer_at (0,str_chars_buffer_ptr,buffer_size);
		if (successed_count != buffer_size)
		{
			status = PFX_STATUS_FAIL;
		}
	}

	if (del_element_ptr)
	{
		delete_string_buffer (del_element_ptr);
	}
	return status;


}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::garbage_collection (GarbageCollectionMODE_t mode /*= GC_DEFUALT_MODE*/,
	pfx_usize_t size_ /*= 0*/)
{
	RETURN_INVALID_RESULT (get_length() > get_string_buffer_size (),PFX_STATUS_MEM_ERR);
	RETURN_RESULT (get_length() == get_string_buffer_size (),PFX_STATUS_OK);

	pfx_result_t status;
	switch (mode)
	{
	case GC_DEFUALT_MODE:
		{
			pfx_usize_t pre_size;

			if (get_length() > CACHE_BUFFER_SIZE)
			{
				pre_size = get_length() + CACHE_BUFFER_SIZE;
				if (pre_size > get_string_buffer_size())
				{
					pre_size = get_string_buffer_size();
				}
			}
			else
			{
				pre_size = CACHE_BUFFER_SIZE;
			}
			status = garbage_collection (GC_USER_MODE,pre_size);
		}
		break;
	case GC_USER_MODE:
		{
			const element_*  str_chars_buffer_ptr;
			pfx_usize_t				buffer_size;
			pfx_usize_t				success_count;

			str_chars_buffer_ptr = get_string ();
			buffer_size = get_length ();

			//element_* element_ptr;
			element_* del_element_ptr;

			del_element_ptr = null;

			status = PFX_STATUS_OK;

			pfx_usize_t  new_size;
			element_* new_buffer_ptr;

			if (size_ < get_length())
			{
				new_size = get_length();
			}
			else if (size_ < get_string_buffer_size())
			{
				new_size = size_;
			}
			else
			{
				new_size = get_string_buffer_size();
			}		

			RETURN_RESULT (new_size == get_string_buffer_size (),PFX_STATUS_OK);

			// 可以使用CACHE BUF的时候，使用CACHE BUF，删除外部BUF
			if (CACHE_BUFFER_SIZE && new_size <= CACHE_BUFFER_SIZE)
			{
				if (is_reference ())
				{
					// 先移除BUF共享
					status = remove_referance ();
					RETURN_INVALID_RESULT (PFX_STATUS_OK !=  status,status);
				}

				status = reset_header ();
				RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
				status = resize_string (buffer_size);
				RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
				success_count = set_charbuffer_at (0,str_chars_buffer_ptr,buffer_size);

				if (m_extern_string_buffer_ptr)
				{
					delete_string_buffer (m_extern_string_buffer_ptr);
					m_extern_string_buffer_ptr = null;
				}

				if (success_count != buffer_size)
				{
					status = PFX_STATUS_FAIL;
				}
				return status;
			}

			// 使用新、短的外部BUF
			new_buffer_ptr = null;

			// 消除共享BUF的影响
			if (is_reference ())
			{
				// 先移除BUF共享
				status = remove_referance ();

				if (PFX_STATUS_OK ==  status)
				{
					new_buffer_ptr = new_string_buffer (new_size);
					RETURN_INVALID_RESULT (null == new_buffer_ptr,PFX_STATUS_MEM_LOW);
				}
			}
			else
			{
				new_buffer_ptr = new_string_buffer (new_size);
				RETURN_INVALID_RESULT (null == new_buffer_ptr,PFX_STATUS_MEM_LOW);
				
				del_element_ptr = m_extern_string_buffer_ptr;
			}

			RETURN_INVALID_RESULT (PFX_STATUS_OK != status, status);

			m_header.m_element_buffer_size = new_size;
			m_header.m_element_ptr				= new_buffer_ptr;
			m_extern_string_buffer_ptr			= new_buffer_ptr;

			
			buffer_size = (buffer_size > size_) ? size_ : buffer_size;
			success_count = set_charbuffer_at (0, str_chars_buffer_ptr, buffer_size);
			if (del_element_ptr)
			{
				delete_string_buffer (del_element_ptr);
			}
			if (success_count != buffer_size)
			{
				status = PFX_STATUS_FAIL;
			}
		}
		break;
	default:
		status = PFX_STATUS_INVALID_PARAMS;
		break;
	}
	return status;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::append_string (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size_)
{
	//const element_*	str_chars_buffer_ptr;
	element_*				del_element_ptr;
	pfx_usize_t				this_buffer_size;
	pfx_result_t			status;
	const element_*	str_this_chars_buffer_ptr;
	str_this_chars_buffer_ptr = get_string ();
	this_buffer_size = get_length ();

	del_element_ptr = null;
	status = init_string (this_buffer_size+buffer_size_,del_element_ptr);

	if (PFX_STATUS_OK == status)
	{
		pfx_usize_t successed_count;
		successed_count = set_charbuffer_at (0,str_this_chars_buffer_ptr,this_buffer_size);
		if (successed_count != this_buffer_size)
		{
			status = PFX_STATUS_FAIL;
		}

		if (PFX_STATUS_OK == status)
		{
			successed_count = set_charbuffer_at(this_buffer_size,str_chars_buffer_ptr,buffer_size_);
			if (successed_count != buffer_size_)
			{
				status = PFX_STATUS_FAIL;
			}
		}

	}
	

	if (del_element_ptr)
	{
		delete_string_buffer (del_element_ptr);
	}
	return status;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::append_string (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN append_string_ptr)
{
	if (append_string_ptr)
	{
		return append_string (append_string_ptr->get_string (), append_string_ptr->get_length ());
	}
	else
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::clip_string_remain_left (pfx_uindex_t clip_index, 
																																						IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr)
{
	RETURN_INVALID_RESULT (this == other_ptr, PFX_STATUS_INVALID_PARAMS);

	const IPfx_string PFX_STRING_TEMPLATE_PARAMS* substring_ptr;
	substring_ptr = sub_string(clip_index, other_ptr);
	if (substring_ptr)
	{
		m_header.m_element_count = (get_length() - substring_ptr->get_length ());
	}
	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::clip_string_remain_right (pfx_uindex_t clip_index, IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr)
{
	RETURN_INVALID_RESULT (this == other_ptr, PFX_STATUS_INVALID_PARAMS);

	const IPfx_string PFX_STRING_TEMPLATE_PARAMS* substring_ptr;
	substring_ptr = sub_string(0, clip_index, other_ptr);
	if (substring_ptr)
	{
		if (clip_index < m_header.m_element_count)
		{
			m_header.m_element_ptr += clip_index;
			m_header.m_element_count -= clip_index;
		}
		else
		{
			m_header.m_element_count = 0;
		}
	}
	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
int	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::compare (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* other_ptr) const
{
	RETURN_RESULT (null == other_ptr,1);
	pfx_usize_t compare_count;
	const element_* this_string_buffer;
	const element_* other_string_buffer;
	int cmp_result;
	this_string_buffer = get_string();
	other_string_buffer = other_ptr->get_string ();
	compare_count = (get_length() > (other_ptr->get_length ())) ?(other_ptr->get_length()):get_length();
	cmp_result = get_length() - other_ptr->get_length ();
	for (pfx_uindex_t i=0;i<compare_count;++i)
	{
		cmp_result = elem_compare::compare (this_string_buffer[i], other_string_buffer[i]);

		if (cmp_result)
		{
			break;
		}
	}
	if (!cmp_result)
	{
		cmp_result = get_length() - other_ptr->get_length ();
	}
	return cmp_result;
}
PFX_CSTRING_TEMPLATE_DEFINES
int	pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS ::compare (const pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & other_) const
{
	return compare(&other_);
}
//////////////////////////////////////////////////////////////////////////
PFX_CSTRING_TEMPLATE_DEFINES
pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS :: pfx_cshare_string ():
			m_prev_string_ptr (null),m_next_string_ptr(null)//,m_enable_set_reference_string(PFX_BOOL_FALSE)
{

}
PFX_CSTRING_TEMPLATE_DEFINES
pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS ::pfx_cshare_string (const pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS & other_) throw (pfx_result_t)
{
	m_extern_string_buffer_ptr = null;
	if (CACHE_BUFFER_SIZE > 0)
	{
		m_header.m_element_ptr = m_cache_buffer;
		m_header.m_element_buffer_size = CACHE_BUFFER_SIZE;
		m_header.m_element_count = 0;
	}

	pfx_result_t status;
	status = append_string(&other_);

	if (PFX_STATUS_OK != status)
	{
		throw (status);
	}
}
PFX_CSTRING_TEMPLATE_DEFINES
pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS ::~pfx_cshare_string ()
{
	resize_string(0);
	garbage_collection();
}

//PFX_CSTRING_TEMPLATE_DEFINES
//PFX_INLINE	 void pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS :: enable_reference (pfx_boolean_t bEnable)
//{
//	m_enable_set_reference_string = bEnable;
//}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE const  IPfx_string PFX_STRING_TEMPLATE_PARAMS* pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS:: get_prev_node () const
{
	return m_prev_string_ptr;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE const  IPfx_string PFX_STRING_TEMPLATE_PARAMS*  pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS:: get_next_node () const
{
	return m_next_string_ptr;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE void pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS:: set_prev_node (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN node_ptr)
{
	//if (m_enable_set_reference_string)
	//{
	//	m_prev_string_ptr = node_ptr;
	//}
	m_prev_string_ptr = node_ptr;
}

PFX_CSTRING_TEMPLATE_DEFINES
PFX_INLINE void pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS:: set_next_node  (IPfx_string PFX_STRING_TEMPLATE_PARAMS*  PARAM_IN node_ptr)
{
	//if (m_enable_set_reference_string)
	//{
	//	m_next_string_ptr = node_ptr;
	//}
	m_next_string_ptr = node_ptr;
}

PFX_CSTRING_TEMPLATE_DEFINES
pfx_result_t	pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS::copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
	pfx_boolean_t	bheader_cache_buffer, 
	pfx_boolean_t & PARAM_INOUT is_reference)
{
	pfx_result_t status;
	is_reference = PFX_BOOL_FALSE;
	if (bheader_cache_buffer)
	{
		if (CACHE_BUFFER_SIZE && header.m_element_count <= CACHE_BUFFER_SIZE)
		{
			set_charbuffer_at (0,header.m_element_ptr,header.m_element_count);
			garbage_collection (GC_USER_MODE,CACHE_BUFFER_SIZE);	
		}
		else
		{
			is_reference = PFX_BOOL_TRUE;
			m_header.m_element_ptr = header.m_element_ptr;
			m_header.m_element_count = header.m_element_count;
			m_header.m_element_buffer_size = header.m_element_buffer_size;
			//status = init_string (header.m_element_ptr,header.m_element_count);
		}
	}
	else
	{
		is_reference = PFX_BOOL_TRUE;
		m_header.m_element_ptr = header.m_element_ptr;
		m_header.m_element_count = header.m_element_count;
		m_header.m_element_buffer_size = header.m_element_buffer_size;
		//status = init_string (header.m_element_ptr,header.m_element_count);
	}


	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE_DEFINES
int pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS::compare (const pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS & other_) const
{
	return compare (&other_);
}
//PFX_CSTRING_TEMPLATE_DEFINES
//PFX_INLINE pfx_result_t pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS:: remove_referance ()
//{
//	pfx_result_t status;
//
//	if (is_reference ())
//	{
//		m_enable_set_reference_string = pfx_true;
//		pfx_clist_base < pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS* >  ::remove_list_node_unsafe (this);
//		m_prev_string_ptr = null;
//		m_next_string_ptr = null;
//		m_enable_set_reference_string = pfx_false;
//
//		status = reset_header ();
//		m_extern_string_buffer_ptr = null;
//	}
//	else
//	{
//		status = PFX_STATUS_OK;
//	}
//	return status;
//}
//
//PFX_CSTRING_TEMPLATE_DEFINES
//PFX_INLINE pfx_result_t	pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS::add_referance 
//														(pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS * PARAM_IN other_ptr)
//{
//	if (other_ptr && this != other_ptr)
//	{
//		pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS* string_ptr = (pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS*) other_ptr;
//		
//	}
//}
//PFX_INLINE pfx_boolean_t	is_reference ();


PECKER_END

#endif			//PFX_CSTRING_CODES_H_
