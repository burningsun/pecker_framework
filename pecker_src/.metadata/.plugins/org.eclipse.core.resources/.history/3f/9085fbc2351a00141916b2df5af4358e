/*
	* pfx_cshare_string_codes.h
	*
	*  Created on: 2014-2-1
	*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
	*/

#ifndef		PFX_CSHARE_STRING_CODES_H_
#define		PFX_CSHARE_STRING_CODES_H_

#include "../pfx_defines.h"
#include "pfx_cshare_string.h"

PECKER_BEGIN

#define PFX_CSHARE_STRING_TEMPLATE template < class __alloc  >
#define PFX_CSHARE_STRING cshare_string < __alloc >
#define PFX_CSHARE_STRING_TYPE typename cshare_string < __alloc >

PFX_CSHARE_STRING_TEMPLATE    
result_t	PFX_CSHARE_STRING::init_string(const PFX_CSHARE_STRING_TYPE::cstring_t& __otherstr)
{
	RETURN_RESULT (&__otherstr==this,PFX_STATUS_OK);
	result_t status;
	usize__t succeed_size;
	FOR_ONE_LOOP_BEGIN
	status = init_string(__otherstr.get_length ());
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
	succeed_size = set_charbuffer_at(0,__otherstr.get_string(), __otherstr.get_length());
	if (succeed_size != __otherstr.get_length())
	{
		status = PFX_STATUS_FAIL;
	}
	this->m_size = succeed_size;
	FOR_ONE_LOOP_END
	return status;
}
PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::init_string (usize__t __size)
{
	typedef PFX_CSHARE_STRING_TYPE::element_t				element_t;
	typedef PFX_CSHARE_STRING_TYPE::cblock_t					cblock_t;
	typedef PFX_CSHARE_STRING_TYPE::cshare_block_t	cshare_block_t;

	result_t status;

	if (__size <= this->get_string_buffer_size())
	{
		this->m_size = __size;
		status = PFX_STATUS_OK;
	}
	else
	{
		cshare_block_t::lock_object_t __lock;

		m_block.lock_bits(__lock);
		FOR_ONE_LOOP_BEGIN

		cshare_block_t::leakable_object_t* lock_ptr =  __lock.lock_modify_object();
		if (lock_ptr)
		{
			status = lock_ptr->init_buffer (__size);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
			this->m_this_string_ptr = lock_ptr->begin();
			this->m_size = __size;
		}
		else
		{
			status = PFX_STATUS_ERROR_;
		}
		FOR_ONE_LOOP_END
		result_t _status = this->m_block.unlock_bits(__lock);

		if (PFX_STATUS_OK != _status)
		{
			status = _status;
		}
		
	}

	return status;
}
PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::init_string (const PFX_CSHARE_STRING_TYPE::element_t* PARAM_IN str_chars_buffer_ptr,
																usize__t buffer_size)
{
	typedef PFX_CSHARE_STRING_TYPE::element_t				element_t;
	typedef PFX_CSHARE_STRING_TYPE::cblock_t					cblock_t;
	typedef PFX_CSHARE_STRING_TYPE::cshare_block_t	cshare_block_t;
	if (!str_chars_buffer_ptr || !buffer_size)
	{
		return this->clean();
	}

	result_t status;

	cshare_block_t::lock_object_t __lock;
	m_block.lock_bits(__lock);

	FOR_ONE_LOOP_BEGIN

	cshare_block_t::leakable_object_t * lock_ptr =  __lock.lock_modify_object();
	BREAK_LOOP_CONDITION_SETS (!lock_ptr, status, PFX_STATUS_ERROR_);
	if (buffer_size > get_string_buffer_size())
	{
		status = lock_ptr->init_buffer(str_chars_buffer_ptr, buffer_size);
	}
	else
	{
		status = lock_ptr->set_buffer(str_chars_buffer_ptr, buffer_size);
	}
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
	this->m_this_string_ptr = lock_ptr->begin();
	FOR_ONE_LOOP_END

	result_t _status = this->m_block.unlock_bits(__lock);
	if (PFX_STATUS_OK != _status)
	{
		status = _status;
	}

	if (PFX_STATUS_OK == status)
	{
		this->m_size = buffer_size;
	}
	return status;
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::init_string (const PFX_CSHARE_STRING_TYPE::IString_t* PARAM_IN other_ptr)
{
	RETURN_RESULT (null == other_ptr, PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (other_ptr == this, PFX_STATUS_OK);
	return init_string(other_ptr->get_string(), other_ptr->get_length());
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::share_to (PFX_CSHARE_STRING_TYPE::cstring_t&  __share)
{
	result_t status;
	__share.clean ();
	FOR_ONE_LOOP_BEGIN
	status = this->m_block.share(__share.m_block);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK!=status);
	__share.m_this_string_ptr = this->m_this_string_ptr;
	__share.m_size = this->m_size;
	status = PFX_STATUS_OK;
	FOR_ONE_LOOP_END

	return status;


}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::resize_string (usize__t __size)
{
	typedef PFX_CSHARE_STRING_TYPE::element_t				element_t;
	typedef PFX_CSHARE_STRING_TYPE::cblock_t					cblock_t;
	typedef PFX_CSHARE_STRING_TYPE::cshare_block_t	cshare_block_t;

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
		
		cshare_block_t::lock_object_t __lock;
		m_block.lock_bits(__lock);
		
		FOR_ONE_LOOP_BEGIN
		
		cshare_block_t::leakable_object_t* lock_ptr =  __lock.lock_modify_object();
		BREAK_LOOP_CONDITION_SETS (!lock_ptr, status, PFX_STATUS_ERROR_);

		status = new_block.init_buffer (__size);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
		succeed_size = new_block.set_buffer_direct (this->m_this_string_ptr, get_length());
		BREAK_LOOP_CONDITION_SETS (succeed_size != get_length(), status, PFX_STATUS_FAIL);
		new_block.swap(*lock_ptr);

		this->m_this_string_ptr = lock_ptr->begin();
		this->m_size = __size;
		status = PFX_STATUS_OK;
		
		FOR_ONE_LOOP_END

		result_t _status = m_block.unlock_bits(__lock);
		if (PFX_STATUS_OK != _status)
		{
			status = _status;
		}

		return status;
	}
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::garbage_collection (GarbageCollectionMODE_t mode, //= GC_DEFUALT_MODE, 
																				usize__t new_size)//= 0)
{
	typedef PFX_CSHARE_STRING_TYPE::element_t				element_t;
	typedef PFX_CSHARE_STRING_TYPE::cblock_t					cblock_t;
	typedef PFX_CSHARE_STRING_TYPE::cshare_block_t	cshare_block_t;

	if (new_size < get_length())
	{
		new_size = get_length();
	}

	if (this->get_string_buffer_size() <= new_size)
	{
		return PFX_STATUS_OK;
	}	

	cblock_t new_block;
	result_t status;
	usize__t succeed_size;

	cshare_block_t::lock_object_t __lock;
	m_block.lock_bits(__lock);

	FOR_ONE_LOOP_BEGIN


	cshare_block_t::leakable_object_t* lock_ptr =  __lock.lock_modify_object();
	BREAK_LOOP_CONDITION_SETS (!lock_ptr, status, PFX_STATUS_ERROR_);

	status = new_block.init_buffer (new_size);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

	succeed_size = new_block.set_buffer_direct (this->m_this_string_ptr, get_length());
	BREAK_LOOP_CONDITION_SETS (succeed_size != get_length(), status, PFX_STATUS_FAIL);

	new_block.swap(*lock_ptr);
	this->m_this_string_ptr = lock_ptr->begin();
	this->m_size = succeed_size;
	status = PFX_STATUS_OK;

	FOR_ONE_LOOP_END
		
	result_t _status = m_block.unlock_bits(__lock);
	if (PFX_STATUS_OK != _status)
	{
		status = _status;
	}

	return status;
	
}


PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::append_string (const PFX_CSHARE_STRING_TYPE::element_t* PARAM_IN str_chars_buffer_ptr,
																		usize__t buffer_size)
{
	return insert_string(get_length(), str_chars_buffer_ptr,buffer_size);
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::append_string (const PFX_CSHARE_STRING_TYPE::IString_t* PARAM_IN append_string_ptr)
{
	RETURN_RESULT (!append_string_ptr, PFX_STATUS_OK);
	if (__type_id::__IS_type(final_type(), append_string_ptr->type_id()))
	{
		return append_string((const PFX_CSHARE_STRING_TYPE::cstring_t&)(*append_string_ptr));
	}
	else
	{
		return append_string(append_string_ptr->get_string(), append_string_ptr->get_length());
	}
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::append_string (const PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_IN __append_str)
{
	if (this->m_this_string_ptr + this->get_length() == __append_str.m_this_string_ptr && 
		!__append_str.m_block.is_shared())
	{
		this->m_size += __append_str.get_length ();
		return PFX_STATUS_OK;
	}
	else
	{
		return append_string(__append_str.get_string(), __append_str.get_length());
	}
	
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::append_front (const PFX_CSHARE_STRING_TYPE::element_t* PARAM_IN str_chars_buffer_ptr,
																		usize__t buffer_size)
{
	return insert_string(0,str_chars_buffer_ptr,buffer_size);
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::append_front (const PFX_CSHARE_STRING_TYPE::IString_t* PARAM_IN append_string_ptr)
{
	RETURN_RESULT (!append_string_ptr, PFX_STATUS_OK);
	if (__type_id::__IS_type(final_type(), append_string_ptr->type_id()))
	{
		return append_front((const PFX_CSHARE_STRING_TYPE::cstring_t&)(*append_string_ptr));
	}
	else
	{
		return append_front(append_string_ptr->get_string(), append_string_ptr->get_length());
	}
	
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::append_front (const PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_IN __append_str)
{
	if (this->m_this_string_ptr + this->get_length() == __append_str.m_this_string_ptr && 
		!__append_str.m_block.is_shared())
	{
		this->m_size += __append_str.get_length ();
		return PFX_STATUS_OK;
	}
	else
	{
		return append_front(__append_str.get_string(), __append_str.get_length());
	}
	
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::insert_string (uindex_t __offset, 
				const PFX_CSHARE_STRING_TYPE::element_t* PARAM_IN str_chars_buffer_ptr, 
				usize__t buffer_size)
{
	typedef PFX_CSHARE_STRING_TYPE::element_t				element_t;
	typedef PFX_CSHARE_STRING_TYPE::cblock_t					cblock_t;
	typedef PFX_CSHARE_STRING_TYPE::cshare_block_t	cshare_block_t;
	result_t status;

	RETURN_INVALID_RESULT (__offset > this->get_length(),PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (!str_chars_buffer_ptr || !buffer_size, PFX_STATUS_OK);

	cblock_t new_block;
	usize__t succeed_size;

	cshare_block_t::lock_object_t __lock;
	m_block.lock_bits(__lock);
	
	FOR_ONE_LOOP_BEGIN

	cshare_block_t::leakable_object_t* lock_ptr =  __lock.lock_modify_object();
	BREAK_LOOP_CONDITION_SETS (!lock_ptr, status, PFX_STATUS_ERROR_);

	if (!this->m_block.is_shared() && 
		(this->get_length()+buffer_size) <= this->get_string_buffer_size())
	{
		usize__t	succeed_size;
		element_t*	ptr					= this->m_this_string_ptr;
		uindex_t		_offset	= __offset;
		if ((this->m_this_string_ptr > lock_ptr->begin ()) && 
			this->m_this_string_ptr <= (lock_ptr->begin() + lock_ptr->size() - 1))
		{
			ptr = lock_ptr->begin ();
			_offset += __offset + (lock_ptr->begin() - this->m_this_string_ptr);
		}

		if (__offset != _offset)
		{
			succeed_size = lock_ptr->move_buffer(_offset, __offset, __offset);
			if (succeed_size == __offset)
			{
				this->m_this_string_ptr = lock_ptr->begin ();
			}
			else
			{
				status = PFX_STATUS_FAIL;
				break;
			}
		}

		if (__offset != this->get_length())
		{		
			succeed_size = lock_ptr->move_buffer(_offset, (this->get_length() - __offset), (_offset+buffer_size));
		}
		else
		{
			succeed_size = __offset+buffer_size;
		}

		if (succeed_size == (__offset + buffer_size))
		{
			succeed_size = lock_ptr->set_buffer(str_chars_buffer_ptr, buffer_size, _offset);
			if (succeed_size == buffer_size)
			{
				this->m_this_string_ptr = lock_ptr->begin ();
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
		status = new_block.init_buffer ((this->get_length()+buffer_size));
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
		succeed_size = new_block.set_buffer_direct (this->m_this_string_ptr, __offset);
		BREAK_LOOP_CONDITION_SETS (succeed_size != __offset, status, PFX_STATUS_FAIL);
		succeed_size = new_block.set_buffer_direct_down (str_chars_buffer_ptr, __offset, buffer_size);
		BREAK_LOOP_CONDITION_SETS (succeed_size != buffer_size, status, PFX_STATUS_FAIL);
		succeed_size = new_block.set_buffer_direct_down (this->m_this_string_ptr + __offset, 
			__offset+buffer_size, (this->get_length() - __offset));
		BREAK_LOOP_CONDITION_SETS (succeed_size != (this->get_length() - __offset), status, PFX_STATUS_FAIL);
		new_block.swap(*lock_ptr);
		this->m_this_string_ptr = lock_ptr->begin();
		this->m_size						= lock_ptr->size();
	}


	status = PFX_STATUS_OK;
	FOR_ONE_LOOP_END

	result_t _status = m_block.unlock_bits(__lock);
	if (PFX_STATUS_OK != _status)
	{
		status = _status;
	}

	return status;
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::insert_string (uindex_t __offset, 
				const PFX_CSHARE_STRING_TYPE::IString_t* PARAM_IN insert_string_ptr)
{
	RETURN_RESULT (!insert_string_ptr, null);
	return insert_string(__offset, insert_string_ptr->get_string(), insert_string_ptr->get_length());
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::insert_string (uindex_t __offset, 
				const PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_IN __append_str)
{
	return insert_string(__offset, __append_str.get_string(), __append_str.get_length());
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::clip_string_remain_left (uindex_t clip_index, 
																		 PFX_CSHARE_STRING_TYPE::IString_t* PARAM_OUT other_ptr)
{
	typedef PFX_CSHARE_STRING_TYPE::IString_t IString_t;

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

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::clip_string_remain_left (uindex_t clip_index, 
	PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_OUT __other)
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


PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::clip_string_remain_right (uindex_t clip_index, 
	PFX_CSHARE_STRING_TYPE::IString_t* PARAM_OUT other_ptr)
{
	typedef PFX_CSHARE_STRING_TYPE::IString_t IString_t;
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

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::clip_string_remain_right (uindex_t clip_index, 
																	PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_OUT __other)
{
	typedef PFX_CSHARE_STRING_TYPE::cstring_t cstring_t;

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

PFX_CSHARE_STRING_TEMPLATE
PFX_INLINE usize__t	PFX_CSHARE_STRING::get_cache_buffer_size () const
{
	return cache_buffer_size ();
}

PFX_CSHARE_STRING_TEMPLATE
PFX_INLINE const PFX_CSHARE_STRING_TYPE::element_t*	PFX_CSHARE_STRING::get_string () const
{
	return this->m_this_string_ptr;
}

PFX_CSHARE_STRING_TEMPLATE
PFX_INLINE usize__t	PFX_CSHARE_STRING::get_length () const
{
	return this->m_size;
}

PFX_CSHARE_STRING_TEMPLATE
PFX_INLINE usize__t	PFX_CSHARE_STRING::get_string_buffer_size () const
{
	typedef PFX_CSHARE_STRING_TYPE::element_t				element_t;
	typedef PFX_CSHARE_STRING_TYPE::cblock_t					cblock_t;
	typedef PFX_CSHARE_STRING_TYPE::cshare_block_t	cshare_block_t;

	const cshare_block_t::leakable_object_t& block_ref = 
		this->m_block.const_reference();
	if (this->m_this_string_ptr)
	{
			return block_ref.size() -  (this->m_this_string_ptr - block_ref.begin());
	}
	else
	{
		return block_ref.size ();
	}

}


PFX_CSHARE_STRING_TEMPLATE
PFX_INLINE const PFX_CSHARE_STRING_TYPE::element_t&	PFX_CSHARE_STRING::reference (uindex_t __index) const
{
	typedef PFX_CSHARE_STRING_TYPE::element_t				element_t;
	typedef PFX_CSHARE_STRING_TYPE::cblock_t					cblock_t;
	typedef PFX_CSHARE_STRING_TYPE::cshare_block_t	cshare_block_t;

	if (__index < get_length())
	{
		return this->m_this_string_ptr[__index];
	}
	else
	{
		return cblock_t::error_element();
	}
}

PFX_CSHARE_STRING_TEMPLATE
PFX_INLINE const PFX_CSHARE_STRING_TYPE::element_t*	PFX_CSHARE_STRING::get_charbuffer_at (uindex_t index_) const
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

PFX_CSHARE_STRING_TEMPLATE
PFX_INLINE usize__t	PFX_CSHARE_STRING::set_charbuffer_at (uindex_t index_, 
	const PFX_CSHARE_STRING_TYPE::element_t* PARAM_IN char_buffer, 
	usize__t buf_size)
{
	typedef PFX_CSHARE_STRING_TYPE::element_t				element_t;
	typedef PFX_CSHARE_STRING_TYPE::cshare_block_t		cshare_block_t;
	result_t status;
	cshare_block_t::lock_object_t __lock;
	m_block.lock_bits(__lock);
	cshare_block_t::leakable_object_t* lock_ptr = __lock.lock_modify_object();
	if (lock_ptr)
	{
		status = block_operate< element_t >::set_buffer (this->m_this_string_ptr, this->m_size, char_buffer, buf_size, index_);
	}
	else
	{
		status = PFX_STATUS_OVERRANGE;
	}

	result_t _status  = m_block.unlock_bits(__lock);
	if (PFX_STATUS_OK != _status)
	{
		status = _status;
	}

	return status;

}

PFX_CSHARE_STRING_TEMPLATE
PFX_INLINE const PFX_CSHARE_STRING_TYPE::element_t*	PFX_CSHARE_STRING::sub_string_buffer (uindex_t index_) const
{
	return get_charbuffer_at(index_);
}

PFX_CSHARE_STRING_TEMPLATE
const  PFX_CSHARE_STRING_TYPE::IString_t * PFX_CSHARE_STRING::sub_string (uindex_t index_,
	PFX_CSHARE_STRING_TYPE::IString_t* PARAM_OUT sub_string_ptr)  const
{
	RETURN_RESULT (!sub_string_ptr, null);
	

	//if (__type_id::__IS_type(final_type(), sub_string_ptr->type_id()))
	//{
	//	return sub_string (index_, (PFX_CSHARE_STRING_TYPE::cstring_t&)(*sub_string_ptr));
	//}
	//else
	//{
		result_t status;
		status = sub_string_ptr->init_string (sub_string_buffer(index_), 
			(index_ > get_length())?(0):(get_length() - index_));

		RETURN_RESULT (PFX_STATUS_OK != status, null);
		return sub_string_ptr;
	//}

}

PFX_CSHARE_STRING_TEMPLATE
const PFX_CSHARE_STRING_TYPE::IString_t*	PFX_CSHARE_STRING::sub_string (uindex_t	index_,
	usize__t		sub_string_size, 
	PFX_CSHARE_STRING_TYPE::IString_t* PARAM_OUT sub_string_ptr)  const
{
	RETURN_RESULT (!sub_string_ptr, null);
	//if (__type_id::__IS_type(final_type(), sub_string_ptr->type_id()))
	//{
	//	return sub_string (index_, sub_string_size, 
	//		(PFX_CSHARE_STRING_TYPE::cstring_t&)(*sub_string_ptr));
	//}
	//else
	//{
		usize__t new_size = (index_ > get_length())?(0):(get_length() - index_);
		if (new_size > sub_string_size)
		{
			new_size = sub_string_size;
		}
		result_t status;
		status = sub_string_ptr->init_string (sub_string_buffer(index_), new_size);
		RETURN_RESULT (PFX_STATUS_OK != status, null);
		return sub_string_ptr;
	//}

}

PFX_CSHARE_STRING_TEMPLATE
const PFX_CSHARE_STRING_TYPE::cstring_t *	 PFX_CSHARE_STRING::sub_string (uindex_t index_, 
PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_OUT __sub_string) 
{ 
	result_t status;
	FOR_ONE_LOOP_BEGIN
	__sub_string.clean();
	status = this->share_to(__sub_string);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK!=status);
	usize__t new_size = (index_ > get_length())?(0):(get_length() - index_);
	if (new_size > __sub_string.get_length())
	{
		new_size = __sub_string.get_length ();
	}
	status = __sub_string.sub_string (index_, new_size);
	FOR_ONE_LOOP_END
	//usize__t new_size = (index_ > get_length())?(0):(get_length() - index_);
	//if (new_size > __sub_string.get_length())
	//{
	//	new_size = __sub_string.get_length ();
	//}
	//status = __sub_string.init_string (sub_string_buffer(index_),new_size);
	//RETURN_RESULT (PFX_STATUS_OK != status, null);
	return &__sub_string;
}

PFX_CSHARE_STRING_TEMPLATE
const PFX_CSHARE_STRING_TYPE::cstring_t*	PFX_CSHARE_STRING::sub_string (uindex_t index_,
	usize__t		sub_string_size, 
	PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_OUT __sub_string)
{
	result_t status;
	FOR_ONE_LOOP_BEGIN
	__sub_string.clean();
	status = this->share_to(__sub_string);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK!=status);
	usize__t new_size = (index_ > get_length())?(0):(get_length() - index_);
	status = __sub_string.sub_string (index_, new_size);
	FOR_ONE_LOOP_END

	//result_t status;
	//usize__t new_size = (index_ > get_length())?(0):(get_length() - index_);
	//status = __sub_string.init_string (sub_string_buffer(index_),new_size);
	//RETURN_INVALID_RESULT (PFX_STATUS_OK != status, null);
	return &__sub_string;
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::sub_string (uindex_t __index, usize__t __size)
{
	typedef PFX_CSHARE_STRING_TYPE::element_t element_t;
	if (__index > get_length())
	{
		__size = 0;
	}
	else if (__size + __index > get_length())
	{
		__size =  get_length() - __index;
	}

	this->m_this_string_ptr += __index;
	this->m_size = __size;
	//usize__t succeed_size;
	//if (__index > get_length())
	//{
	//	__size = 0;
	//}
	//else if (__size + __index > get_length())
	//{
	//	__size =  get_length() - __index;
	//}
	//
	//succeed_size = block_operate< element_t >::move_buffer(this->m_this_string_ptr, 
	//	get_length(), __index, __size, 0);

	//RETURN_INVALID_RESULT (succeed_size != __size, PFX_STATUS_ERROR_);
	//this->m_size = succeed_size;
	return PFX_STATUS_OK;
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::to_same_string (PFX_CSHARE_STRING_TYPE::IString_t* PARAM_OUT same_string_ptr)
{
	RETURN_INVALID_RESULT (!same_string_ptr, PFX_STATUS_INVALID_PARAMS);

	if (__type_id::__IS_type(final_type(), same_string_ptr->type_id()))
	{
		return to_same_string((PFX_CSHARE_STRING_TYPE::cstring_t&)(*same_string_ptr));
	}
	else
	{
		return copy_to(same_string_ptr);
	}
	
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::to_same_string (PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_OUT __same_string)
{
	return share_to(__same_string);
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::copy_to (PFX_CSHARE_STRING_TYPE::IString_t* PARAM_OUT to_string_ptr)  const
{
		RETURN_RESULT (!to_string_ptr, PFX_STATUS_INVALID_PARAMS);
		result_t status;
		status = to_string_ptr->init_string (this);
		return status;
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::copy_to (PFX_CSHARE_STRING_TYPE::cstring_t& PARAM_OUT __to_string)  const
{	
	result_t status;
	status = __to_string.init_string (*this);
	return status;
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::dispose ()
{
	result_t status = this->m_block.release_object();
	m_size = 0;
	m_this_string_ptr = (PFX_CSHARE_STRING_TYPE::element_t*)
		this->m_block.const_reference().begin();
	return status;
}

PFX_CSHARE_STRING_TEMPLATE
result_t	PFX_CSHARE_STRING::clean ()
{

	result_t status = this->m_block.release_object();
	m_size = 0;
	m_this_string_ptr = (PFX_CSHARE_STRING_TYPE::element_t*)
		this->m_block.const_reference().begin();
	return status;
}



PECKER_END

#endif			//PFX_CSHARE_STRING_CODES_H_
