/*
 * pfx_array_codes.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_ARRAY_CODES_H_
#define		PFX_ARRAY_CODES_H_

#include "pfx_array.h"

PECKER_BEGIN

PFX_ARRAYBASE_TEMPLATE_DEFINES
void	 pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS:: lock_auto_step ()
{
	m_lock_auto_step = PFX_BOOL_TRUE;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
void	 pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::unlock_auto_step ()
{
	m_lock_auto_step = PFX_BOOL_FALSE;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::pfx_carray_base () : m_element_buffer_size (0),
	m_element_count (0), m_lock_auto_step (0)
{
	dynamic_block		tmp_block;
	dynamic_block**	block_ptr;
	m_auto_step = tmp_block.get_buffer_size ();
	block_ptr		= (dynamic_block**) m_element_blocks.get_buffer ();
	if (block_ptr)
	{
		pfx_usize_t buffer_size;
		buffer_size = m_element_blocks.get_buffer_size ();
		for (pfx_uindex_t i=0; i<buffer_size; ++i)
		{
			block_ptr [i] = null;
		}
	}
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::pfx_carray_base (const pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS& other_) throw (pfx_result_t)
{
	if (&other_ != this)
	{
		dynamic_block** block_ptrptr;
		block_ptrptr = (dynamic_block**) m_element_blocks.get_buffer ();
		if (block_ptrptr)
		{
			pfx_usize_t buffer_size;
			buffer_size = m_element_blocks.get_buffer_size ();
			for (pfx_uindex_t i=0; i<buffer_size; ++i)
			{
				block_ptrptr [i] = null;
			}
		}

		pfx_result_t status_;
		status_ = copy (&other_);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::~pfx_carray_base ()
{
	dispose ();
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE element_* pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::get_element_at 
	(dynamic_blockptr_collection& blockptr_collection,
	 pfx_uindex_t index_i, pfx_uindex_t index_j, pfx_usize_t step_size, pfx_usize_t block_count)
{
	RETURN_INVALID_RESULT ((index_i >= block_count) || (index_j >= step_size),null);

	dynamic_block** dynamic_block_ptrptr;
	dynamic_block_ptrptr = (dynamic_block**) blockptr_collection.get_buffer ();
	RETURN_INVALID_RESULT ((null == dynamic_block_ptrptr) || (null == dynamic_block_ptrptr[index_i]),null);
	
	element_* elem_ptr = (element_*) (dynamic_block_ptrptr[index_i]->get_buffer (0));
	RETURN_INVALID_RESULT ((null == elem_ptr),null);
	return elem_ptr [index_j];
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE element_* pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::get_element_at (dynamic_blockptr_collection& blockptr_collection,
	pfx_uindex_t index, pfx_usize_t step_size, pfx_usize_t block_count)
{
	pfx_uindex_t index_i;
	pfx_uindex_t index_j;

	index_i = index / step_size;
	index_j = index % step_size;
	
	return get_element_at(blockptr_collection,index_i,index_j,step_size,block_count);
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
pfx_result_t	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::init 
	(pfx_usize_t element_count,pfx_usize_t allocate_step_size /*= 0*/,
	pfx_boolean_t new_buffer/* = pfx_false*/)
{
	dynamic_block**	block_ptrptr;
	dynamic_block*	block_ptr;
	dynamic_block*	tmp_block_ptr;
	pfx_usize_t				auto_step;
	pfx_usize_t				real_auto_step;
	pfx_result_t			status_;

	block_ptrptr		= (dynamic_block**) m_element_blocks.get_buffer ();
	block_ptr			= null;
	auto_step			= m_auto_step;
	
	if (block_ptrptr)
	{
		block_ptr = *block_ptrptr;
	}

	if (block_ptr)
	{
		tmp_block_ptr = block_ptr;
	}
	else
	{
		tmp_block_ptr = new_dynamic_block ();
		RETURN_INVALID_RESULT (null == tmp_block_ptr,PFX_STATUS_MEM_LOW);
		status_ = tmp_block_ptr->init (m_auto_step);
	}

	auto_step = tmp_block_ptr->get_buffer_size ();
	if (auto_step != m_auto_step)
	{
		m_auto_step = auto_step;
	}

	tmp_block_ptr->unlock_resize ();
	status_ = tmp_block_ptr->resize (allocate_step_size);
	tmp_block_ptr->lock_resize ();

	real_auto_step =  tmp_block_ptr->get_buffer_size ();

	if (real_auto_step != m_auto_step && m_lock_auto_step)
	{
		if (block_ptr)
		{
			tmp_block_ptr->unlock_resize ();
			status_ = tmp_block_ptr->resize (m_auto_step);
			tmp_block_ptr->lock_resize ();
		}
		else
		{
			tmp_block_ptr->dispose ();
			release_dynamic_block (tmp_block_ptr);
		}
		return PFX_STATUS_INVALID_OPERATION;
	}
	
	pfx_usize_t block_count;
	block_count = element_count / real_auto_step;
	if (element_count % real_auto_step)
	{
		++block_count;
	}
	pfx_usize_t old_block_buffer_size;
	old_block_buffer_size = m_element_blocks.get_buffer_size ();
	status_ = m_element_blocks.resize (block_count);

	pfx_usize_t new_block_buffer_size;
	new_block_buffer_size = m_element_blocks.get_buffer_size ();

	if (new_block_buffer_size > old_block_buffer_size)
	{
		block_ptrptr = (dynamic_block**) m_element_blocks.get_buffer ();
		if (block_ptrptr)
		{
			for (pfx_uindex_t i=old_block_buffer_size; i<new_block_buffer_size; ++i)
			{
				block_ptrptr [i] = null;
			}
		}
		else
		{
			if (block_ptr)
			{
				tmp_block_ptr->unlock_resize ();
				status_ = tmp_block_ptr->resize (m_auto_step);
				tmp_block_ptr->lock_resize ();
			}
			else
			{
				tmp_block_ptr->dispose ();
				release_dynamic_block (tmp_block_ptr);
			}
			return PFX_STATUS_INVALID_OPERATION;
		}
	}

	block_ptrptr = (dynamic_block**) m_element_blocks.get_buffer ();

	if (null == block_ptrptr)
	{
		if (block_ptr)
		{
			tmp_block_ptr->unlock_resize ();
			status_ = tmp_block_ptr->resize (m_auto_step);
			tmp_block_ptr->lock_resize ();
		}
		else
		{
			tmp_block_ptr->dispose ();
			release_dynamic_block (tmp_block_ptr);
		}
		return PFX_STATUS_INVALID_OPERATION;
	}

	pfx_boolean_t	using_temp_ptr = PFX_BOOL_FALSE;
	pfx_uindex_t		resize_count = 0;
	for (; resize_count<block_count; ++resize_count)
	{
		if (block_ptrptr[resize_count])
		{
			block_ptrptr[resize_count]->unlock_resize ();
			status_ = block_ptrptr[resize_count]->resize (real_auto_step,0,new_buffer);
			block_ptrptr[resize_count]->lock_resize ();
		}
		else
		{
			using_temp_ptr= PFX_BOOL_TRUE; 
			if (null == tmp_block_ptr)
			{
				tmp_block_ptr	= new_dynamic_block ();
				BREAK_LOOP_CONDITION_SETS (null == tmp_block_ptr,
					status_,PFX_STATUS_MEM_LOW);

				status_ = tmp_block_ptr->init (real_auto_step);
				if (PFX_STATUS_OK != status_)
				{
					release_dynamic_block (tmp_block_ptr);
					break;
				}
			}
			block_ptrptr[resize_count] = tmp_block_ptr;
			tmp_block_ptr = null;
		}
		if (PFX_STATUS_OK != status_)
		{
			break;
		}
	}

	if (PFX_STATUS_OK != status_)
	{
		for (pfx_uindex_t i=0; i<resize_count; ++i)
		{
			if (block_ptrptr[resize_count])
			{
				block_ptrptr[resize_count]->unlock_resize ();
				block_ptrptr[resize_count]->resize (m_auto_step);
				block_ptrptr[resize_count]->lock_resize ();
			}
		}
	}
	else
	{
		m_element_buffer_size	= real_auto_step * block_count;
		m_element_count				= 0;
		m_auto_step						= real_auto_step;
	}
	return status_;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
pfx_result_t	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::resize (pfx_usize_t element_size, 
	pfx_usize_t allocate_step/* = 0*/,
	pfx_boolean_t new_buffer/* = pfx_false*/)
{
	pfx_usize_t		old_buffer_size;
	pfx_usize_t		old_count;
	pfx_usize_t		old_step;
	pfx_usize_t		new_step;
	pfx_result_t	status_;

	old_buffer_size	= m_element_buffer_size;
	old_count			= m_element_count;
	old_step				= m_auto_step;

	status_ = init (element_size,allocate_step,PFX_BOOL_FALSE);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,status_);

	new_step = m_auto_step;


	element_* set_element_ptr;
	element_* get_element_ptr;
	pfx_usize_t move_count;
	if (old_count > m_element_count)
	{
		move_count = m_element_count;
	}
	else
	{
		move_count = old_count;
	}

	if (new_step > old_step)
	{
		pfx_uindex_t index_= old_step;
		do 
		{
			get_element_ptr = get_element_at (m_element_blocks, index_, old_step, old_count);
			set_element_ptr = set_element_at (m_element_blocks, index_, new_step, m_element_count);
			*set_element_ptr = *get_element_ptr;
			++index_;
		} while (index_ < move_count);
	}
	else if (new_step < old_step)
	{
		pfx_uindex_t index_= move_count;
		do 
		{
			get_element_ptr = get_element_at (m_element_blocks, index_, old_step, old_count);
			set_element_ptr = set_element_at (m_element_blocks, index_, new_step, m_element_count);
			*set_element_ptr = *get_element_ptr;
			--index_;
		} while (index_ > 0);
	}

	return status_;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
pfx_result_t	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::copy (const IPfx_array PFX_IARRAY_TEMPLATE_PARAMS * other_ptr)
{
	if (this == other_ptr)
	{
		return PFX_STATUS_OK;
	}
	pfx_usize_t		copy_size;
	pfx_result_t	status_;
	copy_size	= other_ptr->size ();
	status_		= this->resize (copy_size);
	for (pfx_uindex_t i=0; i<copy_size; ++i)
	{
		set_buffer (i,other_ptr->get_element_at (i), 1, status_);
	}
	return status_;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
pfx_result_t	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::dispose ()
{
	pfx_result_t	status_;
	pfx_usize_t		block_count;
	dynamic_block**	block_ptrptr;

	block_ptrptr		= (dynamic_block**) m_element_blocks.get_buffer ();

	block_count = m_element_blocks.get_buffer_size ();

	RETURN_INVALID_RESULT (null == block_ptrptr && block_count > 0,PFX_STATUS_MEM_ERR);
	RETURN_RESULT (null == block_ptrptr,PFX_STATUS_OK);

	for (pfx_uindex_t i=0; i<block_count; ++i)
	{
		if (block_ptrptr[i])
		{
			status_ = release_dynamic_block (block_ptrptr[i]);
			block_ptrptr[i] = null;
		}
	}                                                       
	status_ = m_element_blocks.dispose ();

	return PFX_STATUS_OK;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_BLOCK_STATUS_t	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::push_back 
	(const element_& elem)
{
	PFX_BLOCK_STATUS_t	status;
	dynamic_block*			last_block_ptr;
	pfx_usize_t						old_block_buffer_count;
	dynamic_block**			block_ptrptr;
	block_ptrptr		= (dynamic_block**) m_element_blocks.get_buffer ();

	old_block_buffer_count = m_element_blocks.get_buffer_size ();
	RETURN_INVALID_RESULT (null == block_ptrptr && 0 != old_block_buffer_count,PFX_BLOCK_ERROR);

	if (0 == old_block_buffer_count || m_element_count == m_element_buffer_size)
	{
		pfx_usize_t		new_block_buffer_count;

		last_block_ptr = new_dynamic_block ();
		RETURN_INVALID_RESULT (null == last_block_ptr,PFX_BLOCK_MEM_LOW);
		status = m_element_blocks.push_back (last_block_ptr);
		RETURN_INVALID_BY_ACT_RESULT (PFX_BLOCK_NORMAL != status,
			release_dynamic_block (last_block_ptr),
			status);

		new_block_buffer_count = m_element_blocks.get_buffer_size ();
		block_ptrptr						= (dynamic_block**) m_element_blocks.get_buffer ();

		RETURN_INVALID_RESULT (null == block_ptrptr && 0 != new_block_buffer_count,PFX_BLOCK_ERROR);
		for (pfx_uindex_t i=m_element_blocks.size (); i<new_block_buffer_count; ++i)
		{
			block_ptrptr [i] = null;
		}
		m_element_buffer_size += last_block_ptr->get_buffer_size ();

		status = last_block_ptr->push_back (elem);
		if (PFX_BLOCK_NORMAL == status)
		{
			++m_element_count;
		}
		return status;
	}
	else
	{
		pfx_uindex_t last_block_index = m_element_blocks.size ();
		if (last_block_index > 0)
		{
			-- last_block_index;
		}
		else
		{
			m_element_blocks.resize (1);
			block_ptrptr	= (dynamic_block**) m_element_blocks.get_buffer ();
		}

		last_block_ptr	= block_ptrptr [last_block_index];

		if (null != last_block_ptr && last_block_ptr->is_full ())
		{
			pfx_result_t status_;
			status_ = m_element_blocks.resize (m_element_blocks.size () + 1);
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,PFX_BLOCK_ERROR);

			block_ptrptr	= (dynamic_block**) m_element_blocks.get_buffer ();
			++last_block_index;
			last_block_ptr	= block_ptrptr [last_block_index];
		}

		if (null == last_block_ptr)
		{
			last_block_ptr = new_dynamic_block ();
			RETURN_INVALID_RESULT (null == last_block_ptr,PFX_BLOCK_MEM_LOW);
			block_ptrptr [last_block_index] = last_block_ptr;
			m_element_buffer_size += last_block_ptr->get_buffer_size ();
		}
		status = last_block_ptr->push_back (elem);
		if (PFX_BLOCK_NORMAL == status)
		{
			++m_element_count;
		}
		
	}
	return status;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
const element_*	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::pop_back (PFX_BLOCK_STATUS_t& status_)
{
	const element_*			pop_elem_ptr;
	dynamic_block*			last_block_ptr;
	pfx_usize_t						old_block_buffer_count;
	dynamic_block**			block_ptrptr;
	block_ptrptr	= (dynamic_block**) m_element_blocks.get_buffer ();
	old_block_buffer_count = m_element_blocks.size ();
	RETURN_INVALID_RESULT (null == block_ptrptr && 0 != old_block_buffer_count,PFX_BLOCK_ERROR);
	RETURN_RESULT (null == block_ptrptr || 0 == old_block_buffer_count,PFX_BLOCK_EMPTY);

	last_block_ptr = block_ptrptr [old_block_buffer_count-1];

	RETURN_INVALID_RESULT (null == last_block_ptr,PFX_BLOCK_ERROR);

	pop_elem_ptr = last_block_ptr->pop_back (status_);

	if (last_block_ptr->is_empty ())
	{
		--m_element_count;
		m_element_blocks.resize (old_block_buffer_count-1);
		return pop_elem_ptr;
	}

	if (PFX_BLOCK_NORMAL == status_)
	{
		pfx_usize_t block_size;
		block_size = last_block_ptr->get_buffer_size ();
		--m_element_count;

		if (old_block_buffer_count == block_size)
		{
			last_block_ptr = block_ptrptr [old_block_buffer_count];
			if (null != last_block_ptr && last_block_ptr->size () > 0)
			{
				release_dynamic_block (last_block_ptr);
				block_ptrptr [old_block_buffer_count] = null;
				m_element_buffer_size -= block_size;
				//m_element_block.resize (old_block_buffer_count - 1);
			}
		}
		
	}

	return pop_elem_ptr;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::get_buffer_size () const
{
	return m_element_buffer_size;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t  pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::size () const
{
	return m_element_count;
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE const element_*	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::get_element_at (pfx_uindex_t index_) const
{
	return get_element_at (m_element_blocks,index_,m_auto_step,m_element_blocks.size());
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE	pfx_usize_t	 pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::set_buffer (pfx_uindex_t index_, const element_* elements_ptr,
	pfx_usize_t element_size,pfx_result_t& status_)
{
	if (index_ >= m_element_count)
	{
		status_ = PFX_STATUS_OVERRANGE;
		return 0;
	}

	element_* elem_ptr;
	pfx_uindex_t i=0;
	do 
	{
		elem_ptr = get_element_at (m_element_blocks,index_,m_auto_step,m_element_blocks.size());
		++i;
		if (elem_ptr)
		{
			*elem_ptr = elements_ptr [i];
		}
		else
		{
			break;
		}
	} while (i<element_size);

	if (0 == i && 0 != element_size)
	{
		status_ = PFX_STATUS_FAIL;
	}
	else
	{
		status_ = PFX_STATUS_OK;
	}

	return i;

}

PFX_ARRAYBASE_TEMPLATE_DEFINES
pfx_result_t	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::clear 
	(pfx_boolean_t release_buffer /*= pfx_false*/)
{
	if (release_buffer)
	{
		return dispose();
	}
	else
	{
		pfx_usize_t size_;
		dynamic_block** block_ptrptr;

		size_				= m_element_blocks.size ();
		block_ptrptr	= m_element_blocks.get_buffer ();
		if (null == block_ptrptr)
		{
			if (size_ != 0)
			{
				return PFX_STATUS_MEM_ERR;
			}
			else
			{
				return PFX_STATUS_OK;
			}
		}
		for (pfx_uindex_t i=0; i<size_; ++i)
		{
			if (block_ptrptr[i])
			{
				block_ptrptr[i]->clear ();
			}
		}
		return PFX_STATUS_OK;
	}
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE pfx_boolean_t pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::is_full () const
{
	return (pfx_boolean_t) (m_element_count == m_element_buffer_size);
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE pfx_boolean_t pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::is_empty () const
{
	return (pfx_boolean_t) (0 == m_element_count);
}

PFX_ARRAYBASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS ::copy 
	(const pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS &other_)
{
	return copy(&other_);
}


PECKER_END

#endif			//PFX_ARRAY_CODES_H_
