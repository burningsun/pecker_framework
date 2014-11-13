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

#define PFX_CSTRING_TEMPLATE template < class __alloc,  const unsigned int CACHE_BUFFER_SIZE  >
#define PFX_CSTRING cstring < __alloc, CACHE_BUFFER_SIZE >
#define PFX_CSTRING_TYPE typename cstring < __alloc, CACHE_BUFFER_SIZE >

PFX_CSTRING_TEMPLATE    
result_t	PFX_CSTRING::init_string(const PFX_CSTRING_TYPE::cstring_t& __otherstr)
{
	RETURN_RESULT (&__otherstr==this,PFX_STATUS_OK);
	result_t status;
	usize__t succeed_size;
	FOR_ONE_LOOP_BEGIN
	status = init_string(__otherstr.get_length ());
	BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
	succeed_size = set_charbuffer_at(0,__otherstr.get_string(), __otherstr.get_length());
	if (succeed_size != __otherstr.get_length())
	{
		status = PFX_STATUS_FAIL;
	}
	this->m_size = succeed_size;
	FOR_ONE_LOOP_END
	return status;
}
PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::init_string (usize__t __size)
{
	result_t status;

	if (__size <= this->get_string_buffer_size())
	{
		this->m_size = __size;
		status = PFX_STATUS_OK;
	}
	else
	{
		status = this->m_block.init_buffer(__size);
		if (PFX_STATUS_OK == status)
		{
			this->m_this_string_ptr = this->m_block.begin();
			this->m_size = __size;
		}
	}

	return status;
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::init_string (const PFX_CSTRING_TYPE::element_t* PARAM_IN str_chars_buffer_ptr,
																usize__t buffer_size)
{
	typedef PFX_CSTRING_TYPE::element_t element_t;
	typedef PFX_CSTRING_TYPE::cblock_t cblock_t;
	if (!str_chars_buffer_ptr || !buffer_size)
	{
		return this->clean();
	}

	result_t status;

	if (buffer_size <= get_string_buffer_size() )
	{
		usize__t succeed_size;
		succeed_size = block_operate< element_t >::set_buffer (this->m_this_string_ptr, cache_buffer_size(), 
			str_chars_buffer_ptr, buffer_size);
		if (succeed_size != buffer_size)
		{
			status = PFX_STATUS_FAIL;
		}
		else
		{
			status = PFX_STATUS_OK;
		}
	}
	else
	{
		cblock_t new_block;
		status = new_block.init_buffer (str_chars_buffer_ptr, buffer_size);
		if (PFX_STATUS_OK == status)
		{
			new_block.swap(this->m_block);
			this->m_this_string_ptr = this->m_block.begin();
		}
	}

	if (PFX_STATUS_OK == status)
	{
		this->m_size = buffer_size;
	}
	return status;
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::init_string (const PFX_CSTRING_TYPE::IString_t* PARAM_IN other_ptr)
{
	RETURN_RESULT (null == other_ptr, PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (other_ptr == this, PFX_STATUS_OK);
	return init_string(other_ptr->get_string(),other_ptr->get_length());
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::resize_string (usize__t __size)
{
	typedef PFX_CSTRING_TYPE::element_t element_t;
	typedef PFX_CSTRING_TYPE::cblock_t cblock_t;

	if (__size <= get_string_buffer_size())
	{
		this->m_size = __size;
		return PFX_STATUS_OK;
	}
	else
	{
		cblock_t new_block;
		result_t status;
		usize__t succeed_size;
		FOR_ONE_LOOP_BEGIN
		status = new_block.init_buffer (__size);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		succeed_size = new_block.set_buffer_direct (this->m_this_string_ptr, get_length());
		BREAK_LOOP_CONDITION_SETS (succeed_size != get_length(), status, PFX_STATUS_FAIL);
		new_block.swap(this->m_block);
		this->m_this_string_ptr = this->m_block.begin();
		this->m_size = __size;
		status = PFX_STATUS_OK;
		FOR_ONE_LOOP_END
		return status;
	}
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::garbage_collection (GarbageCollectionMODE_t mode, //= GC_DEFUALT_MODE, 
																				usize__t new_size)//= 0)
{
	typedef PFX_CSTRING_TYPE::element_t element_t;
	typedef PFX_CSTRING_TYPE::cblock_t cblock_t;

	if (this->get_string_buffer_size() < new_size)
	{
		return PFX_STATUS_OK;
	}

	if (get_length() > cache_buffer_size())
	{
		if (new_size > get_length())
		{
			if (this->m_this_string_ptr == this->m_cache_buffer)
			{
				return PFX_STATUS_OK;
			}
		}
		else
		{
			new_size = get_length();
		}
		cblock_t new_block;
		result_t status;
		usize__t succeed_size;
		FOR_ONE_LOOP_BEGIN
		status = new_block.init_buffer (new_size);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		succeed_size = new_block.set_buffer_direct (this->m_this_string_ptr, get_length());
		BREAK_LOOP_CONDITION_SETS (succeed_size != get_length(), status, PFX_STATUS_FAIL);
		new_block.swap(this->m_block);
		this->m_this_string_ptr = this->m_block.begin();
		this->m_size = succeed_size;
		status = PFX_STATUS_OK;
		FOR_ONE_LOOP_END
		return status;
	}
	else
	{
		new_size = get_length();
		usize__t succeed_size;
		succeed_size = block_operate< element_t >::set_buffer (this->m_cache_buffer, cache_buffer_size(), 
			this->m_this_string_ptr, get_length());
		if (succeed_size == get_length())
		{
			dispose ();
			this->m_size = new_size;
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_FAIL;
		}
	}

}


PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::append_string (const PFX_CSTRING_TYPE::element_t* PARAM_IN str_chars_buffer_ptr,
																		usize__t buffer_size)
{
	return insert_string(get_length(), str_chars_buffer_ptr,buffer_size);
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::append_string (const PFX_CSTRING_TYPE::IString_t* PARAM_IN append_string_ptr)
{
	RETURN_RESULT (!append_string_ptr, PFX_STATUS_OK);
	return append_string(append_string_ptr->get_string(), append_string_ptr->get_length());
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::append_string (const PFX_CSTRING_TYPE::cstring_t& PARAM_IN __append_str)
{
	return append_string(__append_str.get_string(), __append_str.get_length());
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::append_front (const PFX_CSTRING_TYPE::element_t* PARAM_IN str_chars_buffer_ptr,
																		usize__t buffer_size)
{
	return insert_string(0,str_chars_buffer_ptr,buffer_size);
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::append_front (const PFX_CSTRING_TYPE::IString_t* PARAM_IN append_string_ptr)
{
	RETURN_RESULT (!append_string_ptr, PFX_STATUS_OK);
	return append_front(append_string_ptr->get_string(), append_string_ptr->get_length());
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::append_front (const PFX_CSTRING_TYPE::cstring_t& PARAM_IN __append_str)
{
	return append_front(__append_str.get_string(), __append_str.get_length());
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::insert_string (uindex_t __offset, 
				const PFX_CSTRING_TYPE::element_t* PARAM_IN str_chars_buffer_ptr, 
				usize__t buffer_size)
{
	typedef PFX_CSTRING_TYPE::element_t element_t;
	typedef PFX_CSTRING_TYPE::cblock_t cblock_t;
	result_t status;

	RETURN_INVALID_RESULT (__offset > this->get_length(),PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (!str_chars_buffer_ptr || !buffer_size, PFX_STATUS_OK);

	if ((this->get_length()+buffer_size) <= this->get_string_buffer_size())
	{
		usize__t	succeed_size;
		if (__offset != this->get_length())
		{
			succeed_size = block_operate< element_t >::move_buffer(this->m_this_string_ptr, 
				get_string_buffer_size(), __offset, (this->get_length() - __offset), (__offset+buffer_size));
		}
		else
		{
			succeed_size = __offset+buffer_size;
		}

		if (succeed_size == (__offset + buffer_size))
		{
			succeed_size = block_operate< element_t >::set_buffer(this->m_this_string_ptr, 
				get_string_buffer_size(), str_chars_buffer_ptr, buffer_size, __offset);
			if (succeed_size == buffer_size)
			{
				this->m_size = get_length() + buffer_size;
				status = PFX_STATUS_OK;
			}
			else
			{
				status = PFX_STATUS_FAIL;
			}
		}
		else
		{
			status = PFX_STATUS_FAIL;
		}
	}
	else
	{
		cblock_t new_block;
		result_t status;
		usize__t succeed_size;
		FOR_ONE_LOOP_BEGIN
		status = new_block.init_buffer ((this->get_length()+buffer_size));
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		succeed_size = new_block.set_buffer_direct (this->m_this_string_ptr, __offset);
		BREAK_LOOP_CONDITION_SETS (succeed_size != __offset, status, PFX_STATUS_FAIL);
		succeed_size = new_block.set_buffer_direct_down (str_chars_buffer_ptr, __offset, buffer_size);
		BREAK_LOOP_CONDITION_SETS (succeed_size != buffer_size, status, PFX_STATUS_FAIL);
		succeed_size = new_block.set_buffer_direct_down (this->m_this_string_ptr + __offset, 
			__offset+buffer_size, (this->get_length() - __offset));
		BREAK_LOOP_CONDITION_SETS (succeed_size != (this->get_length() - __offset), status, PFX_STATUS_FAIL);

		new_block.swap(this->m_block);
		this->m_this_string_ptr = this->m_block.begin();
		this->m_size						= this->m_block.size();
		status = PFX_STATUS_OK;
		FOR_ONE_LOOP_END
		return status;
	}


	return status;
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::insert_string (uindex_t __offset, 
				const PFX_CSTRING_TYPE::IString_t* PARAM_IN insert_string_ptr)
{
	RETURN_RESULT (!insert_string_ptr, null);
	return insert_string(__offset, insert_string_ptr->get_string(), insert_string_ptr->get_length());
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::insert_string (uindex_t __offset, 
				const PFX_CSTRING_TYPE::cstring_t& PARAM_IN __append_str)
{
	return insert_string(__offset, __append_str.get_string(), __append_str.get_length());
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::clip_string_remain_left (uindex_t clip_index, 
																		 PFX_CSTRING_TYPE::IString_t* PARAM_OUT other_ptr)
{
	typedef PFX_CSTRING_TYPE::IString_t IString_t;

	RETURN_INVALID_RESULT (other_ptr == this, PFX_STATUS_DENIED);
	const IString_t* str_ptr = sub_string(clip_index, other_ptr);
	if (str_ptr)
	{
		return this->sub_string(0, clip_index);
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::clip_string_remain_left (uindex_t clip_index, 
	PFX_CSTRING_TYPE::cstring_t& PARAM_OUT __other)
{
	RETURN_INVALID_RESULT (&__other == this, PFX_STATUS_DENIED);
	const cstring_t* str_ptr = sub_string(clip_index, __other);
	if (str_ptr)
	{
		return this->sub_string(0, clip_index);
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}
}


PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::clip_string_remain_right (uindex_t clip_index, 
	PFX_CSTRING_TYPE::IString_t* PARAM_OUT other_ptr)
{
	typedef PFX_CSTRING_TYPE::IString_t IString_t;
	RETURN_INVALID_RESULT (null == other_ptr, PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT (other_ptr == this, PFX_STATUS_DENIED);
	const IString_t* str_ptr = sub_string(0, clip_index, other_ptr);
	if (str_ptr)
	{
		return this->sub_string(clip_index, get_length());
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::clip_string_remain_right (uindex_t clip_index, 
																	PFX_CSTRING_TYPE::cstring_t& PARAM_OUT __other)
{
	typedef PFX_CSTRING_TYPE::cstring_t cstring_t;

	RETURN_INVALID_RESULT (&__other == this, PFX_STATUS_DENIED);
	const cstring_t* str_ptr = sub_string(0,clip_index,__other);
	if (str_ptr)
	{
		return this->sub_string(clip_index,get_length());
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}
}

PFX_CSTRING_TEMPLATE
PFX_INLINE usize__t	PFX_CSTRING::get_cache_buffer_size () const
{
	return cache_buffer_size ();
}

PFX_CSTRING_TEMPLATE
PFX_INLINE const PFX_CSTRING_TYPE::element_t*	PFX_CSTRING::get_string () const
{
	return this->m_this_string_ptr;
}

PFX_CSTRING_TEMPLATE
PFX_INLINE  PFX_CSTRING_TYPE::element_t*	PFX_CSTRING::get_string() 
{
	return this->m_this_string_ptr;
}

PFX_CSTRING_TEMPLATE
PFX_INLINE usize__t	PFX_CSTRING::get_length () const
{
	return this->m_size;
}

PFX_CSTRING_TEMPLATE
PFX_INLINE usize__t	PFX_CSTRING::get_string_buffer_size () const
{
	if (this->m_block.size() > 0)
	{
		return this->m_block.size();
	}
	else
	{
		return cache_buffer_size (); 
	}
}

PFX_CSTRING_TEMPLATE
PFX_INLINE PFX_CSTRING_TYPE::element_t&	PFX_CSTRING::reference (uindex_t __index)
{
	typedef PFX_CSTRING::cblock_t cblock_t;
	if (__index < get_length())
	{
		return this->m_this_string_ptr[__index];
	}
	else
	{
		return cblock_t::error_element();
	}
}

PFX_CSTRING_TEMPLATE
PFX_INLINE const PFX_CSTRING_TYPE::element_t&	PFX_CSTRING::reference (uindex_t __index) const
{
	typedef PFX_CSTRING::cblock_t cblock_t;
	if (__index < get_length())
	{
		return this->m_this_string_ptr[__index];
	}
	else
	{
		return cblock_t::error_element();
	}
}

PFX_CSTRING_TEMPLATE
PFX_INLINE const PFX_CSTRING_TYPE::element_t*	PFX_CSTRING::get_charbuffer_at (uindex_t index_) const
{
	if (index_ < get_length())
	{
		return (this->m_this_string_ptr + index_);
	}
	else
	{
		return null;
	}
}

PFX_CSTRING_TEMPLATE
PFX_INLINE usize__t	PFX_CSTRING::set_charbuffer_at (uindex_t index_, 
	const PFX_CSTRING_TYPE::element_t* PARAM_IN char_buffer, 
	usize__t buf_size)
{
	typedef PFX_CSTRING_TYPE::element_t element_t;
	return block_operate< element_t >::set_buffer (this->m_this_string_ptr, this->m_size, 
		char_buffer, buf_size, index_);
}

PFX_CSTRING_TEMPLATE
PFX_INLINE const PFX_CSTRING_TYPE::element_t*	PFX_CSTRING::sub_string_buffer (uindex_t index_) const
{
	return get_charbuffer_at(index_);
}

PFX_CSTRING_TEMPLATE
const  PFX_CSTRING_TYPE::IString_t * PFX_CSTRING::sub_string (uindex_t index_,
	PFX_CSTRING_TYPE::IString_t* PARAM_OUT sub_string_ptr)  const
{
	RETURN_RESULT (!sub_string_ptr, null);
	result_t status;
	status = sub_string_ptr->init_string (sub_string_buffer(index_), 
		(index_ > get_length())?(0):(get_length() - index_));

	RETURN_RESULT (PFX_STATUS_OK > status, null);
	return sub_string_ptr;
}

PFX_CSTRING_TEMPLATE
const PFX_CSTRING_TYPE::IString_t*	PFX_CSTRING::sub_string (uindex_t	index_,
	usize__t		sub_string_size, 
	PFX_CSTRING_TYPE::IString_t* PARAM_OUT sub_string_ptr)  const
{
	RETURN_RESULT (!sub_string_ptr, null);
	usize__t new_size = (index_ > get_length())?(0):(get_length() - index_);
	if (new_size > sub_string_size)
	{
		new_size = sub_string_size;
	}
	result_t status;
	status = sub_string_ptr->init_string (sub_string_buffer(index_), new_size);
	RETURN_RESULT (PFX_STATUS_OK > status, null);
	return sub_string_ptr;
}

PFX_CSTRING_TEMPLATE
const PFX_CSTRING_TYPE::cstring_t *	 PFX_CSTRING::sub_string (uindex_t index_, 
PFX_CSTRING_TYPE::cstring_t& PARAM_OUT __sub_string)  const
{
	result_t status;
	usize__t new_size = (index_ > get_length())?(0):(get_length() - index_);
	if (new_size > __sub_string.get_length())
	{
		new_size = __sub_string.get_length ();
	}
	status = __sub_string.init_string (sub_string_buffer(index_),new_size);
	RETURN_RESULT (PFX_STATUS_OK > status, null);
	return &__sub_string;
}

PFX_CSTRING_TEMPLATE
const PFX_CSTRING_TYPE::cstring_t*	PFX_CSTRING::sub_string (uindex_t index_,
	usize__t		sub_string_size, 
	PFX_CSTRING_TYPE::cstring_t& PARAM_OUT __sub_string)  const
{
	result_t status;
	usize__t new_size = (index_ > get_length())?(0):(get_length() - index_);
	status = __sub_string.init_string (sub_string_buffer(index_),new_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK > status, null);
	return &__sub_string;
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::sub_string (uindex_t __index, usize__t __size)
{
	typedef PFX_CSTRING_TYPE::element_t element_t;
	usize__t succeed_size;
	if (__index > get_length())
	{
		__size = 0;
	}
	else if (__size + __index > get_length())
	{
		__size =  get_length() - __index;
	}
	
	succeed_size = block_operate< element_t >::move_buffer(this->m_this_string_ptr, 
		get_length(), __index, __size, 0);

	RETURN_INVALID_RESULT (succeed_size != __size, PFX_STATUS_ERROR_);
	this->m_size = succeed_size;
	return PFX_STATUS_OK;
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::to_same_string (PFX_CSTRING_TYPE::IString_t* PARAM_OUT same_string_ptr)
{
	return copy_to(same_string_ptr);
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::to_same_string (PFX_CSTRING_TYPE::cstring_t& PARAM_OUT __same_string)
{
	return copy_to(__same_string);
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::copy_to (PFX_CSTRING_TYPE::IString_t* PARAM_OUT to_string_ptr)  const
{
		RETURN_RESULT (!to_string_ptr, PFX_STATUS_INVALID_PARAMS);
		result_t status;
		status = to_string_ptr->init_string (this);
		return status;
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::copy_to (PFX_CSTRING_TYPE::cstring_t& PARAM_OUT __to_string)  const
{	
	result_t status;
	status = __to_string.init_string (*this);
	return status;
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::dispose ()
{
	result_t status = this->m_block.clean();
	m_size = 0;
	m_this_string_ptr = m_cache_buffer;
	return status;
}

PFX_CSTRING_TEMPLATE
result_t	PFX_CSTRING::clean ()
{
	m_size = 0;
	return PFX_STATUS_OK;
}



PECKER_END

#endif			//PFX_CSTRING_CODES_H_
