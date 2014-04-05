/*
 * pfx_block_codes.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BLOCK_CODES_H_
#define		PFX_BLOCK_CODES_H_

#include "pfx_block.h"
#include "pfx_clist.h"

PECKER_BEGIN

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: bind_block_header 
	(const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & block_header)
{
	m_header = block_header;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: reset_header ()
{
	if (CACHE_BUFFER_SIZE > 0)
	{
		m_header.m_element_ptr = &m_cache_buffer;
		m_header.m_element_buffer_size = CACHE_BUFFER_SIZE;
		m_header.m_element_count = 0;
	}
	else
	{
		m_header.m_element_ptr = null;
		m_header.m_element_buffer_size = 0;
		m_header.m_element_count = 0;
	}
}


PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::pfx_static_block ()
{
	if (CACHE_BUFFER_SIZE > 0)
	{
		m_header.m_element_ptr = &m_cache_buffer;
		m_header.m_element_buffer_size = CACHE_BUFFER_SIZE;
		m_header.m_element_count = 0;
	}
	//else
	//{
	//}
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::pfx_static_block 
	(const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS & other_) throw (pfx_result_t)
{
	if (&other_ != this)
	{
		pfx_result_t status_;
		status_ = copy (&other_);
		if (PFX_STATUS_OK > status_)
		{
			throw (status_);
		}
	}
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
	pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::pfx_static_block 
	(const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS * other_ptr) throw (pfx_result_t)
{
	if (other_ptr != this)
	{
		pfx_result_t status_;
		status_ = copy (&other_ptr);
		if (PFX_STATUS_OK > status_)
		{
			throw (status_);
		}
	}
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
	pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::~pfx_static_block ()
{
	dispose ();
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::init (pfx_usize_t element_size, pfx_usize_t allocate_step/* = 0*/, 
	pfx_boolean_t new_buffer/* = pfx_false*/)
{
	RETURN_INVALID_RESULT ((new_buffer || element_size > m_header.m_element_buffer_size),PFX_STATUS_MEM_LOW);
	m_header.m_element_count = 0;
	return PFX_STATUS_OK;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::resize (pfx_usize_t element_size, pfx_usize_t allocate_step/* = 0*/,
	pfx_boolean_t new_buffer/* = pfx_false*/)
{
	RETURN_INVALID_RESULT ((new_buffer || element_size > m_header.m_element_buffer_size),PFX_STATUS_MEM_LOW);
	m_header.m_element_count = element_size;
	return PFX_STATUS_OK;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t	pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS::dispose()
{
	return clear (PFX_BOOL_TRUE);
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t	pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: copy (const IPfx_block PFX_BLOCK_TEMPLATE_PARAMS * other_ptr)
{
	RETURN_INVALID_RESULT (null == other_ptr,PFX_STATUS_INVALID_PARAMS);

	if (other_ptr != this)
	{
		PFX_BLOCK_STATUS_t	status_;
		pfx_usize_t						copy_size;
		const element_*			other_element_ptr;
		copy_size					=	other_ptr->size ();
		other_element_ptr	=	other_ptr->get_buffer ();

		for (pfx_uindex_t i=0; i<copy_size; ++i)
		{
			status_ = push_back (other_element_ptr[i]);
			if (PFX_BLOCK_FULL == status_ || PFX_BLOCK_ERROR == status_)
			{
				break;
			}
		}
		if (PFX_BLOCK_ERROR == status_)
		{
			return PFX_STATUS_ERROR_;
		}
		else
		{
			return PFX_STATUS_OK;
		}
	}
	return PFX_STATUS_OK;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::copy 
		(const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS * other_ptr)
{
	RETURN_INVALID_RESULT (null == other_ptr,PFX_STATUS_INVALID_PARAMS);

	if (other_ptr != this)
	{
		PFX_BLOCK_STATUS_t	status_;
		pfx_usize_t						copy_size;
		const element_*			other_element_ptr;
		copy_size					=	other_ptr->size ();
		other_element_ptr	=	other_ptr->get_buffer ();

		for (pfx_uindex_t i=0; i<copy_size; ++i)
		{
			status_ = push_back (other_element_ptr[i]);
			if (PFX_BLOCK_FULL == status_ || PFX_BLOCK_ERROR == status_)
			{
				break;
			}
		}
		if (PFX_BLOCK_ERROR == status_)
		{
			return PFX_STATUS_ERROR_;
		}
		else
		{
			return PFX_STATUS_OK;
		}
	}
	return PFX_STATUS_OK;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE PFX_BLOCK_STATUS_t	pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
				push_back (const element_& elem)
{
	PFX_BLOCK_STATUS_t status_;
	if (is_full ())
	{
		status_ = PFX_BLOCK_FULL;
	}
	else if ((0		== m_header.m_element_buffer_size) ||
				(null	== m_header.m_element_ptr))
	{
		status_ = PFX_BLOCK_ERROR;
	}
	else
	{
		m_header.m_element_ptr[m_header.m_element_count] = elem;
		++m_header.m_element_count;
		status_ = PFX_BLOCK_NORMAL;
	}
	return status_;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE element_*	pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	pop_back (PFX_BLOCK_STATUS_t& status_)
{
	element_* pop_value = null;
	if (is_empty ())
	{
		status_ = PFX_BLOCK_EMPTY;
	}
	else if ((0		== m_header.m_element_buffer_size) ||
				(null	== m_header.m_element_ptr))
	{
		status_ = PFX_BLOCK_ERROR;
	}
	else
	{
		--m_header.m_element_count;
		pop_value = m_header.m_element_ptr + m_header.m_element_count;
		status_ = PFX_BLOCK_NORMAL;
	}
	return pop_value;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE PFX_BLOCK_STATUS_t	pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	push_front (const element_& elem)
{
	pfx_usize_t moved_size;
	PFX_BLOCK_STATUS_t status_;
	if (is_full ())
	{
		status_ = PFX_BLOCK_FULL;
	}
	else if ((0		== m_header.m_element_buffer_size) ||
				(null	== m_header.m_element_ptr))
	{
		status_ = PFX_BLOCK_ERROR;
	}
	else
	{
		moved_size = move_data (0,size(),1);
		if (moved_size != size())
		{
			status_ = PFX_STATUS_FAIL;
		}
		else
		{
			m_header.m_element_ptr[0] = elem;
			++m_header.m_element_count;
			status_ = PFX_BLOCK_NORMAL;
		}
	}
	return status_;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE  element_*	pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	pop_front (PFX_BLOCK_STATUS_t& status_)
{
	element_* pop_value = null;
	pfx_usize_t moved_size;
	if (is_empty ())
	{
		status_ = PFX_BLOCK_EMPTY;
	}
	else if ((0		== m_header.m_element_buffer_size) ||
		(null	== m_header.m_element_ptr))
	{
		status_ = PFX_BLOCK_ERROR;
	}
	else 	if (1 ==m_header.m_element_count)
	{
		m_header.m_element_count = 0;
		status_ = PFX_BLOCK_NORMAL;
		pop_value = m_header.m_element_ptr;
	}
	else
	{
		element_ tmp_element = m_header.m_element_ptr[0];
		moved_size = move_data (1,size()-1,0);
		if (moved_size != (size()-1))
		{
			status_ = PFX_STATUS_FAIL;
		}
		else
		{
			--m_header.m_element_count;
			m_header.m_element_ptr[m_header.m_element_count] = tmp_element;
			status_ = PFX_BLOCK_NORMAL;
			pop_value = m_header.m_element_ptr + m_header.m_element_count;
		}
	}
	return pop_value;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	get_buffer_size () const
{
	return m_header.m_element_buffer_size;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	size () const
{
	return m_header.m_element_count;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE const  element_* pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	get_buffer (pfx_uindex_t index_ /*= 0*/) const
{
	if (index_ >= m_header.m_element_count)
	{
		return null;
	}
	else
	{
		return m_header.m_element_ptr;
	}
	
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::set_buffer 
	(pfx_uindex_t index_, const element_* elements_ptr,pfx_usize_t element_size,pfx_result_t& status_)
{
	RETURN_INVALID_BY_ACT_RESULT (null == elements_ptr,status_ = PFX_STATUS_INVALID_PARAMS,0);
	RETURN_INVALID_BY_ACT_RESULT (null == m_header.m_element_ptr,status_ = PFX_STATUS_UNINIT,0);
	if (index_ > m_header.m_element_count)
	{
		status_ = PFX_STATUS_OK;
		return 0;
	}
	
	pfx_usize_t set_element_size;
	if (index_ + element_size > m_header.m_element_count)
	{
		set_element_size = m_header.m_element_count - index_;
	}
	else
	{
		set_element_size = element_size;
	}

	for (pfx_uindex_t i=0; i<set_element_size; ++i)
	{
		m_header.m_element_ptr [i+index_] = elements_ptr [i];
	}
	status_ = PFX_STATUS_OK;
	return set_element_size;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE element_*	 pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
get_buffer_reference (pfx_uindex_t index_/* = 0*/)
{
	if (index_ >= m_header.m_element_count)
	{
		return null;
	}
	else
	{
		return m_header.m_element_ptr;
	}
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t  pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	move_data (pfx_uindex_t first_element_index,pfx_usize_t move_size,pfx_uindex_t move_to_index)
{
	pfx_usize_t element_count = size();
	
	if ((move_to_index+1) > element_count || 
		0 == move_size)
	{
		return 0;
	}

	if ((0	== m_header.m_element_buffer_size) ||
		(null	== m_header.m_element_ptr))
	{
		return 0;
	}

	if (first_element_index + move_size > element_count)
	{
		move_size = element_count - first_element_index;
	}

	if (first_element_index == move_to_index)
	{
		return move_size;
	}
	
	if (first_element_index > move_to_index)
	{
		pfx_uindex_t i=(move_size-1);
		for (; i>=0; --i)
		{
			m_header.m_element_ptr[move_to_index+i] = m_header.m_element_ptr[first_element_index+i];
		}
	}
	else
	{
		pfx_uindex_t i=0;
		for (; i<move_size; ++i)
		{
			m_header.m_element_ptr[move_to_index+i] = m_header.m_element_ptr[first_element_index+i];
		}
	}
	 return move_size;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	clear (pfx_boolean_t release_buffer /*= pfx_false*/)
{
	m_header.m_element_count = 0;
	return PFX_STATUS_OK;
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_boolean_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	is_full () const
{
	return (pfx_boolean_t)(m_header.m_element_count == m_header.m_element_buffer_size);
}

PFX_STATIC_BLOCK_TEMPLATE_DEFINES
	PFX_INLINE pfx_boolean_t pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS ::
	is_empty () const
{
	return (pfx_boolean_t)(0 == m_header.m_element_count);
}

//////////////////////////////////////////////////////////////////////////
PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::pfx_dynamic_block () : m_lock_dynamic_resize (PFX_BOOL_FALSE),
	m_resize_step (CACHE_BUFFER_SIZE)
{

}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::pfx_dynamic_block (const pfx_dynamic_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS & other_) throw (pfx_result_t)
{
	if (&other_ != this)
	{
		pfx_result_t status_;
		status_ = copy (&other_);
		if (PFX_STATUS_OK > status_)
		{
			throw (status_);
		}
	}
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::pfx_dynamic_block (const pfx_dynamic_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS * other_ptr) throw (pfx_result_t)
{
	if (other_ptr != this)
	{
		pfx_result_t status_;
		status_ = copy (&other_ptr);
		if (PFX_STATUS_OK > status_)
		{
			throw (status_);
		}
	}
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::~pfx_dynamic_block ()
{
	dispose ();
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
	pfx_result_t pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::block_init (pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS &header, 
	pfx_usize_t element_size,pfx_boolean_t new_buffer/* = pfx_false*/)
{
	pfx_result_t status_;
	RETURN_INVALID_RESULT (header.m_element_buffer_size < CACHE_BUFFER_SIZE,
		PFX_STATUS_ERROR_);

	if (element_size == header.m_element_buffer_size)
	{
		header.m_element_count = 0;
		return PFX_STATUS_OK;
	}

	element_* new_element_ptr = null;
	status_ = PFX_STATUS_OK;

	if (new_buffer || element_size > header.m_element_buffer_size)
	{
		new_element_ptr = element_allocator :: reallocate_objects (header.m_element_ptr,element_size);
		if (!new_element_ptr)
		{
			new_element_ptr = element_allocator :: allocate_objects (element_size);
			RETURN_INVALID_RESULT (null == new_element_ptr,PFX_STATUS_MEM_LOW);
		}
		header.m_element_buffer_size = element_size;
		header.m_element_count = 0;
		header.m_element_ptr = new_element_ptr;
		status_ = PFX_STATUS_OK;
	}
	else
	{
		header.m_element_count = 0;
		status_ = PFX_STATUS_OK;
	}

	return status_;
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_dynamic_block PFX_BLOCKHEADER_TEMPLATE_PARAMS :: block_resize (pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS &header,
	pfx_usize_t element_size,pfx_boolean_t new_buffer/* = pfx_false*/)
{
	pfx_result_t status_;
	RETURN_INVALID_RESULT (header.m_element_buffer_size < CACHE_BUFFER_SIZE,
		PFX_STATUS_ERROR_);

	if (element_size == header.m_element_buffer_size)
	{
		//header.m_element_count = 0;
		return PFX_STATUS_OK;
	}

	element_* new_element_ptr = null;
	status_ = PFX_STATUS_OK;

	if (new_buffer || element_size > header.m_element_buffer_size)
	{
		new_element_ptr = element_allocator :: reallocate_objects (header.m_element_ptr,element_size);
		if (!new_element_ptr)
		{
			new_element_ptr = element_allocator :: allocate_objects (element_size);
			if (null == new_element_ptr)
			{
				status_ = PFX_STATUS_MEM_LOW;
			}
			else
			{
				pfx_usize_t copy_size = (header.m_element_count > element_size) ? (element_size) : (header.m_element_count);
				header.m_element_buffer_size = element_size;
				header.m_element_count = element_size;
				for (pfx_uindex_t i=0;i<copy_size;++i)
				{
					new_element_ptr [i] = header.m_element_ptr[i];
				}
				element_allocator :: deallocate_objects (header.m_element_ptr);
				header.m_element_ptr = new_element_ptr;
				//status_ = PFX_STATUS_OK;
			}
		}
		else
		{
			//header.m_element_buffer_size = element_size;
			header.m_element_count = element_size;
			header.m_element_ptr = new_element_ptr;
			//status_ = PFX_STATUS_OK;
		}
	}
	else
	{
		header.m_element_count = 0;
		//status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
void pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::lock_resize ()
{
	m_lock_dynamic_resize = PFX_BOOL_TRUE;
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
void pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::unlock_resize ()
{
	m_lock_dynamic_resize = PFX_BOOL_FALSE;
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_dynamic_block PFX_BLOCKHEADER_TEMPLATE_PARAMS :: init (pfx_usize_t element_size, 
	pfx_usize_t allocate_step, 
	pfx_boolean_t new_buffer /*= pfx_false*/)
{
//	pfx_result_t status_;
	if (0 == allocate_step)
	{
		if (0 == m_resize_step)
		{
			allocate_step = CACHE_BUFFER_SIZE;
		}
		else
		{
			allocate_step = m_resize_step;
		}
		if (0 == allocate_step)
		{
			allocate_step = 1;
		}
	}
	m_resize_step = allocate_step;
	


	if (m_lock_dynamic_resize)
	{
		element_size = get_buffer_size ();
		new_buffer = PFX_BOOL_FALSE;
	}
	else
	{

		pfx_usize_t mod;
		mod = element_size % allocate_step;
		if (mod > 0)
		{
			element_size = element_size - mod + allocate_step;
		}
	}
	
	if (element_size <= CACHE_BUFFER_SIZE && new_buffer)
	{
		return clear (PFX_BOOL_TRUE);
	}
	else
	{
		return block_init (m_header, element_size, new_buffer);
	}
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS :: resize (pfx_usize_t element_size, 
	pfx_usize_t allocate_step,
	pfx_boolean_t new_buffer/* = pfx_false*/)
{

	if (0 == allocate_step)
	{
		if (0 == m_resize_step)
		{
			allocate_step = CACHE_BUFFER_SIZE;
		}
		else
		{
			allocate_step = m_resize_step;
		}
	}
	m_resize_step = allocate_step;

	pfx_usize_t new_element_count;
	if (m_lock_dynamic_resize)
	{
		new_element_count = get_buffer_size ();
		new_buffer = PFX_BOOL_FALSE;
	}
	else
	{
		pfx_usize_t mod;
		mod = element_size % allocate_step;
		if (mod > 0)
		{
			new_element_count = element_size - mod + allocate_step;
		}
	}

	if (element_size <= CACHE_BUFFER_SIZE && new_buffer)
	{
		for (pfx_usize_t i=0; i<CACHE_BUFFER_SIZE; ++i)
		{
			m_cache_buffer[i] = m_header.m_element_ptr[i];
		}
		 status_ = clear (PFX_BOOL_TRUE);
		 if (PFX_STATUS_OK == status_)
		 {
			 m_header.m_element_count = element_size;
		 }
		 return status_;
	}

	pfx_result_t status_;
	status_ = block_resize (m_header,new_element_count,new_buffer);
	if (PFX_STATUS_OK == status_)
	{
		m_header.m_element_count = element_size;
	}
	return status_;
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::copy 
	(const IPfx_block PFX_BLOCK_TEMPLATE_PARAMS * other_ptr)
{
	pfx_result_t status_;
	pfx_usize_t element_size;
	element_size = other_ptr->get_buffer_size();
	if (m_lock_dynamic_resize)
	{
		element_size = get_buffer_size ();
	}

	status_ = pfx_dynamic_block PFX_BLOCKHEADER_TEMPLATE_PARAMS ::block_init (m_header,element_size);
	if (PFX_STATUS_OK == status_)
	{
		status_ = pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: copy (other_ptr);
	}
	return status_;
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::copy 
	(const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS * other_ptr)
{
	pfx_result_t status_;
	pfx_usize_t element_size;
	element_size = other_ptr->get_buffer_size();
	if (m_lock_dynamic_resize)
	{
		element_size = get_buffer_size ();
	}

	status_ = pfx_dynamic_block PFX_BLOCKHEADER_TEMPLATE_PARAMS ::block_init (m_header,element_size);
	if (PFX_STATUS_OK == status_)
	{
		status_ = pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: copy (other_ptr);
	}
	return status_;
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::copy 
			(const pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS * other_ptr)
{
	return copy ((const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS)other_ptr);
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE PFX_BLOCK_STATUS_t pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::push_back (const element_& elem)
{
	pfx_result_t status_;
	if (is_full () && m_lock_dynamic_resize)
	{
		return PFX_BLOCK_FULL;
	}
	pfx_usize_t this_size = size ();
	status_ = resize (this_size+1,0);
	if (PFX_STATUS_OK == status_)
	{
		resize (this_size,0);
		return pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: push_back (elem);
	}
	else
	{
		return PFX_BLOCK_ERROR;
	}
}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE PFX_BLOCK_STATUS_t pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS ::push_front (const element_& elem)
{
	if (is_full () && m_lock_dynamic_resize)
	{
		return PFX_BLOCK_FULL;
	}

	PFX_BLOCK_STATUS_t status_;
	RETURN_INVALID_RESULT (header.m_element_buffer_size < CACHE_BUFFER_SIZE,
		PFX_BLOCK_ERROR);

	pfx_usize_t element_size;
	element_size = size () + 1;

	if (m_lock_dynamic_resize)
	{
		element_size = get_buffer_size ();
	}
	else
	{
		pfx_usize_t mod;
		mod = element_size % m_resize_step;
		if (mod > 0)
		{
			element_size = element_size - mod + m_resize_step;
		}
	}

	if (element_size == header.m_element_buffer_size)
	{
		return pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: push_front (elem);
	}

	element_* new_element_ptr = null;
	//status_ = PFX_STATUS_OK;

	if (element_size > header.m_element_buffer_size)
	{
		new_element_ptr = element_allocator :: reallocate_objects (header.m_element_ptr,element_size);
		if (!new_element_ptr)
		{
			new_element_ptr = element_allocator :: allocate_objects (element_size);
			if (null == new_element_ptr)
			{
				status_ = PFX_BLOCK_ERROR;
			}
			else
			{
				header.m_element_buffer_size = element_size;
				pfx_usize_t copy_size = size ();
				new_element_ptr [0] = elem;
				for (pfx_uindex_t i=0;i<copy_size;++i)
				{
					new_element_ptr [i+1] = header.m_element_ptr[i];
				}
				element_allocator :: deallocate_objects (header.m_element_ptr);
				header.m_element_ptr = new_element_ptr;
				++(header.m_element_count);
				//status_ = PFX_STATUS_OK;
				status_ = PFX_BLOCK_NORMAL;
			}
		}
		else
		{
			//header.m_element_buffer_size = element_size;
			header.m_element_ptr = new_element_ptr;
			//status_ = PFX_STATUS_OK;
			status_ = pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: push_front (elem);
		}
	}
	else
	{
		status_ = pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: push_front (elem);
	}
	return status_;

}

PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS :: clear (pfx_boolean_t release_buffer /*= pfx_false*/)
{
	pfx_result_t status_;
	status_ = PFX_STATUS_OK;
	if (release_buffer)
	{
		element_* release_buffer_ptr = m_header.m_element_ptr;
		if (m_header.m_element_buffer_size > CACHE_BUFFER_SIZE)
		{
			status_ = element_allocator :: deallocate_objects (m_header.m_element_ptr);
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);
		}
		status_ = reset_header ();
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);
	}
	else
	{
		status_ = pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS :: clear (release_buffer);
	}
	return status_;
}


//////////////////////////////////////////////////////////////////////////
PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::pfx_share_block_base () : m_prev_block_ptr (null),
	m_next_block_ptr (null),m_block_ptr (null)
{
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::pfx_share_block_base 
	(const pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS & other_) throw (pfx_result_t)
{
	if (&other_ != this)
	{
		m_prev_block_ptr = null;
		m_next_block_ptr = null;
		m_block_ptr = null;
		pfx_result_t status_;
		status_ = copy (&other_);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::pfx_share_block_base 
	(const pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS * other_ptr) throw (pfx_result_t)
{
	if (other_ptr != this)
	{
		m_prev_block_ptr = null;
		m_next_block_ptr = null;
		m_block_ptr = null;
		pfx_result_t status_;
		status_ = copy (other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::~pfx_share_block_base ()
{
	dispose ();
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_boolean_t	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::is_reference () const
{
	return (pfx_boolean_t) ((bool)(get_prev_node () || get_next_node ()));
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t		pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::swap 
	(pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS & other_)
{
	pfx_result_t status_;
	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* this_prev_ptr;
	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* this_next_ptr;
	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* other_prev_ptr;
	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* other_next_ptr;
	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* insert_ptr;

	if (this == &other_)
	{
		return PFX_STATUS_OK;
	}
	
	this_prev_ptr		= (pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS*) get_prev_node ();
	this_next_ptr		= (pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS*) get_next_node ();
	other_prev_ptr	= (pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS*) other_.get_prev_node ();
	other_next_ptr	= (pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS*) other_.get_next_node ();

	if (is_reference())
	{
		pfx_share_block_base  PFX_SHARE_BLOCK_TEMPLATE_PARAMS* remove_ptr;
		remove_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::remove_list_node_unsafe (this);
		RETURN_INVALID_RESULT (null == remove_ptr,PFX_STATUS_ERROR_);
		status_ = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::init_list_node (this);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);
	}
	

	status_ = PFX_STATUS_OK;
	

	if (other_.is_reference())
	{
		FOR_ONE_LOOP_BEGIN
		pfx_share_block_base  PFX_SHARE_BLOCK_TEMPLATE_PARAMS* remove_ptr;
		remove_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::remove_list_node_unsafe (&other_);
		BREAK_LOOP_CONDITION_SETS (null == remove_ptr,status_,PFX_STATUS_ERROR_);
		status_ = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::init_list_node (&other_);
		FOR_ONE_LOOP_END

		if (PFX_STATUS_OK != status_)
		{
			if (this_prev_ptr)
			{
				insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_back(this_prev_ptr,this);
				RETURN_INVALID_RESULT (null == insert_ptr,PFX_STATUS_ERROR_);
			}
			else if (this_next_ptr)
			{
				insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_front(this_next_ptr,this);
				RETURN_INVALID_RESULT (null == insert_ptr,PFX_STATUS_ERROR_);
			}
			return status_;
		}
	}

	if (other_prev_ptr)
	{
		insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_back(other_prev_ptr,this);
		if (null == insert_ptr)
		{
			status_ = PFX_STATUS_ERROR_;
		}
	}
	else if (other_next_ptr)
	{
		insert_ptr =  pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_front(other_next_ptr,this);
		if (null == insert_ptr)
		{
			status_ = PFX_STATUS_ERROR_;
		}
	}

	if (PFX_STATUS_OK != status_)
	{
		if (this_prev_ptr)
		{
			insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_back(this_prev_ptr,this);
		}
		else if (this_next_ptr)
		{
			insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_front(this_next_ptr,this);
		}

		if (other_prev_ptr)
		{
			insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_back(other_prev_ptr,&other_);
		}
		else if (other_next_ptr)
		{
			insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_front(other_next_ptr,&other_);
		}
		return status_;
	}

	
	
	if (this_next_ptr)
	{
		insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_back(this_prev_ptr,&other_);
		if (null == insert_ptr)
		{
			status_ = PFX_STATUS_ERROR_;
		}
	}
	else if (this_prev_ptr)
	{
		insert_ptr =  pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_front(this_next_ptr,&other_next_ptr);
		if (null == insert_ptr)
		{
			status_ = PFX_STATUS_ERROR_;
		}
	}

	if (PFX_STATUS_OK != status_)
	{
		if (this_prev_ptr)
		{
			insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_back(this_prev_ptr,this);
		}
		else if (this_next_ptr)
		{
			insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_front(this_next_ptr,this);
		}

		if (other_prev_ptr)
		{
			insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_back(other_prev_ptr,&other_);
		}
		else if (other_next_ptr)
		{
			insert_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::insert_list_node_front(other_next_ptr,&other_);
		}
		return status_;
	}

	pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS	tmp_header;
	elements_block*																			tmp_block_ptr;

	tmp_header				= m_header;
	tmp_block_ptr			= m_block_ptr;
	m_header					= other_.m_header;
	m_block_ptr				= other_.m_block_ptr;
	other_.m_header		= tmp_header;
	other_.m_block_ptr	= tmp_block_ptr;

	return PFX_STATUS_OK;

}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::dispose ()
{
	pfx_result_t status_;

	if (is_reference ())
	{
		pfx_share_block_base  PFX_SHARE_BLOCK_TEMPLATE_PARAMS* remove_ptr;
		remove_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::remove_list_node_unsafe (this);
		if (null == remove_ptr)
		{
			status_ = PFX_STATUS_ERROR_;
		}
		else
		{
			status_ = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::init_list_node (this);
			if (PFX_STATUS_OK == status_)
			{
				m_block_ptr = null;
				m_header.m_element_buffer_size = 0;
				m_header.m_element_count = 0;
				m_header.m_element_ptr = null;
			}
			//status_ = PFX_STATUS_OK;
		}
	}
	else
	{
		if (m_block_ptr)
		{
			status_ = m_block_ptr->dispose ();
			if (PFX_STATUS_OK == status_)
			{
				status_ = release_block (m_block_ptr);
			}

			if (PFX_STATUS_OK == status_)
			{
				m_block_ptr = null;
				m_header.m_element_buffer_size = 0;
				m_header.m_element_count = 0;
				m_header.m_element_ptr = null;
			}
			
		}

	}
	return status_;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::copy (const IPfx_block PFX_BLOCK_TEMPLATE_PARAMS * other_ptr)
{
	if (other_ptr == this)
	{
		return PFX_STATUS_OK;
	}

	pfx_result_t status_;
	if (is_reference())
	{
		pfx_share_block_base  PFX_SHARE_BLOCK_TEMPLATE_PARAMS* remove_ptr;
		remove_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::remove_list_node_unsafe (this);
		RETURN_INVALID_RESULT (null == remove_ptr,PFX_STATUS_ERROR_);
		status_ = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::init_list_node (this);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);
	}

	if (null == m_block_ptr)
	{
		m_block_ptr = new_block ();

		RETURN_INVALID_RESULT (null == m_block_ptr,PFX_STATUS_MEM_LOW);

		status_ = m_block_ptr->init (other_ptr->size ());

		if (PFX_STATUS_OK == status_)
		{
			status_ = m_block_ptr->copy (other_ptr);
		}

		if (PFX_STATUS_OK != status_)
		{
			release_block (m_block_ptr);
			m_block_ptr = null;
		}

	}
	else
	{
		status_ = m_block_ptr->init (other_ptr->size ());

		if (PFX_STATUS_OK == status_)
		{
			status_ = m_block_ptr->copy (other_ptr);
		}
	}
	return status_;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::init (pfx_usize_t element_size, pfx_usize_t allocate_step/* = 0*/, 
	pfx_boolean_t new_buffer/* = pfx_false*/)
{
	if (is_reference())
	{
		pfx_share_block_base  PFX_SHARE_BLOCK_TEMPLATE_PARAMS* remove_ptr;
		remove_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::remove_list_node_unsafe (this);
		RETURN_INVALID_RESULT (null == remove_ptr,PFX_STATUS_ERROR_);
		status_ = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::init_list_node (this);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);
		m_block_ptr = null;
	}

	if (null == m_block_ptr)
	{
		m_block_ptr = new_block ();
		RETURN_INVALID_RESULT (null == m_block_ptr,PFX_STATUS_MEM_LOW);	
	}

	status_ = m_block_ptr->init (element_size,allocate_step,new_buffer);
	if (PFX_STATUS_OK == status_)
	{
		m_header.m_element_ptr				= m_block_ptr->get_buffer_reference ();
		m_header.m_element_count			= 0;
		m_header.m_element_buffer_size	= m_block_ptr->get_buffer_size ();
	}

	return status_;

}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::resize (pfx_usize_t element_size, pfx_usize_t allocate_step/* = 0*/, 
	pfx_boolean_t new_buffer/* = pfx_false*/)
{
	elements_block* copy_block_ptr;
	elements_block* new_block_ptr;
	elements_block* tmp_block_ptr;
	copy_block_ptr = null;
	new_block_ptr = null;
	tmp_block_ptr = m_block_ptr;

	if (is_reference())
	{
		pfx_share_block_base  PFX_SHARE_BLOCK_TEMPLATE_PARAMS* remove_ptr;
		remove_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::remove_list_node_unsafe (this);
		RETURN_INVALID_RESULT (null == remove_ptr,PFX_STATUS_ERROR_);
		status_ = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::init_list_node (this);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);
		copy_block_ptr = m_block_ptr;
		m_block_ptr = null;
	}

	if (null == m_block_ptr)
	{
		new_block_ptr = new_block ();
		RETURN_INVALID_RESULT (null == new_block_ptr,PFX_STATUS_MEM_LOW);	
		tmp_block_ptr = new_block_ptr;
	}

	FOR_ONE_LOOP_BEGIN

	if (0 == element_size)
	{
		m_header.m_element_count			= 0;
		m_header.m_element_ptr				= tmp_block_ptr->get_buffer_reference ();
		m_header.m_element_buffer_size	= tmp_block_ptr->get_buffer_size ();

		BREAK_LOOP (status_,PFX_STATUS_OK);
	}

	if (copy_block_ptr)
	{
		status_ = tmp_block_ptr->init (element_size,allocate_step);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);

		status_ = tmp_block_ptr->copy (copy_block_ptr);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);

		status_ = tmp_block_ptr->resize (element_size,allocate_step);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
	}
	else
	{
		status_ = tmp_block_ptr->resize (element_size,allocate_step,new_buffer);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
	}

	if (PFX_STATUS_OK == status_)
	{
		m_header.m_element_ptr				= tmp_block_ptr->get_buffer_reference ();
		m_header.m_element_count			= tmp_block_ptr->size ();
		m_header.m_element_buffer_size	= tmp_block_ptr->get_buffer_size ();
	}
	FOR_ONE_LOOP_END

	if (PFX_STATUS_OK == status_)
	{
		m_block_ptr = tmp_block_ptr;
	}
	else
	{
		if (new_block_ptr)
		{
			release_block (new_block_ptr);
			new_block_ptr = null;
		}
	}

	return status_;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
pfx_result_t pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::sub_share_block 
	(pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* PARAM_INOUT sub_share_block_ptr, 
	pfx_uindex_t first_index,pfx_usize_t sub_size)
{
	pfx_result_t status_;
	RETURN_INVALID_RESULT (null == sub_share_block_ptr,PFX_STATUS_INVALID_PARAMS);
	if (sub_share_block_ptr->is_reference())
	{
		pfx_share_block_base  PFX_SHARE_BLOCK_TEMPLATE_PARAMS* remove_ptr;
		remove_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::remove_list_node_unsafe (sub_share_block_ptr);
		RETURN_INVALID_RESULT (null == remove_ptr,PFX_STATUS_ERROR_);
		status_ = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::init_list_node (sub_share_block_ptr);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);

		sub_share_block_ptr->m_block_ptr = null;
	}
	else
	{
		if (sub_share_block_ptr->m_block_ptr)
		{
			status_ = release_block (sub_share_block_ptr->m_block_ptr);
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);

			sub_share_block_ptr->m_block_ptr = null;

		}
	}
	sub_share_block_ptr->m_header.m_element_buffer_size = 0;
	sub_share_block_ptr->m_header.m_element_count			= 0;
	sub_share_block_ptr->m_header.m_element_ptr				= 0;
	if ((first_index >= size ()) || (0 == sub_size))
	{
		return PFX_STATUS_OK;
	}
	sub_share_block_ptr->m_header.m_element_ptr = m_header.m_element_ptr + first_index;
	if ((first_index + sub_size) > size ())
	{
		sub_size = size () - first_index;
	}
	sub_share_block_ptr->m_header.m_element_count			= sub_size;
	sub_share_block_ptr->m_header.m_element_buffer_size = sub_size;
	return PFX_STATUS_OK;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE PFX_BLOCK_STATUS_t pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::push_back 
	(const element_& elem)
{
	pfx_result_t status_;
	pfx_usize_t this_size = size ();
	status_ = resize (this_size + 1);
	if (PFX_STATUS_OK == status_)
	{
		status_ = resize (this_size);
	}
	if (PFX_STATUS_OK == status_)
	{
		status_ = m_block_ptr->push_back (elem);
	}
	return status_;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE const element_* pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::pop_back 
	(PFX_BLOCK_STATUS_t& status_)
{
	pfx_result_t status;
	pfx_usize_t this_size = size ();
	status = resize (this_size);
	if (PFX_STATUS_OK == status_)
	{
		return m_block_ptr->pop_back (status_);
	}
	else
	{
		status_ = PFX_BLOCK_ERROR;
		return null;
	}
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
	PFX_INLINE PFX_BLOCK_STATUS_t pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::push_front 
	(const element_& elem)
{
	pfx_result_t status_;
	pfx_usize_t this_size = size ();
	status_ = resize (this_size + 1);
	if (PFX_STATUS_OK == status_)
	{
		status_ = resize (this_size);
	}
	if (PFX_STATUS_OK == status_)
	{
		status_ = m_block_ptr->push_front (elem);
	}
	return status_;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
	PFX_INLINE const element_* pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::pop_front
	(PFX_BLOCK_STATUS_t& status_)
{
	pfx_result_t status;
	pfx_usize_t this_size = size ();
	status = resize (this_size);
	if (PFX_STATUS_OK == status_)
	{
		return m_block_ptr->pop_front (status_);
	}
	else
	{
		status_ = PFX_BLOCK_ERROR;
		return null;
	}
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t			pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::get_buffer_size () const
{
	return m_header.m_element_buffer_size;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE	 pfx_usize_t			pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::size () const
{
	return m_header.m_element_count;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE	 const element_*	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::get_buffer (pfx_uindex_t index_/* = 0*/) const
{
	if (index_ < m_header.m_element_count)
	{
		return m_header.m_element_ptr;
	}
	else
	{
		return null;
	}
	
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::set_buffer (pfx_uindex_t index_, 
	const element_* elements_ptr,pfx_usize_t element_size,pfx_result_t& status_)
{

	RETURN_INVALID_BY_ACT_RESULT (null == m_block_ptr,status_ = PFX_STATUS_UNINIT,0);
	
	pfx_result_t status;
	status = resize (this_size);
	if (PFX_STATUS_OK != status)
	{
		status_ = status;
		return 0;
	}
	else
	{
		return m_block_ptr->set_buffer (index_, elements_ptr, element_size, status_);
	}
}
PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE	 pfx_result_t			pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::clear (pfx_boolean_t release_buffer/* = pfx_false*/)
{
	pfx_result_t status_;

	if (is_reference ())
	{
		pfx_share_block_base  PFX_SHARE_BLOCK_TEMPLATE_PARAMS* remove_ptr;
		remove_ptr = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::remove_list_node_unsafe (this);
		if (null == remove_ptr)
		{
			status_ = PFX_STATUS_ERROR_;
		}
		else
		{
			status_ = pfx_clist_base < pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS > ::init_list_node (this);
			if (PFX_STATUS_OK == status_)
			{
				m_block_ptr = null;
				m_header.m_element_buffer_size = 0;
				m_header.m_element_count = 0;
				m_header.m_element_ptr = null;
			}
			//status_ = PFX_STATUS_OK;
		}
	}
	else
	{
		if (m_block_ptr)
		{
			status_ = m_block_ptr->clear (release_buffer);
			if (PFX_STATUS_OK == status_)
			{
				m_header.m_element_count			= 0;
				m_header.m_element_ptr				= m_block_ptr->get_buffer_reference ();
				m_header.m_element_buffer_size	= m_block_ptr->get_buffer_size ();
			}
		}

	}
	return status_;
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE	 pfx_boolean_t		pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::is_full () const
{
	return (pfx_boolean_t)(m_header.m_element_count == m_header.m_element_buffer_size);
}

PFX_SHARE_BLOCK_TEMPLATE_DEFINES
PFX_INLINE pfx_boolean_t		pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS ::is_empty () const
{
	return (pfx_boolean_t)(0 == m_header.m_element_count); 
}

PECKER_END

#endif			//PFX_BLOCK_CODES_H_
