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

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::pfx_consecutive_array_base () : m_auto_size_step (0),m_max_elements_count(0)
{

}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::pfx_consecutive_array_base (const pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS &other_) throw (pfx_result_t)
{
	if (&other_ != this)
	{
		m_auto_size_step = other_.get_auto_step ();
		m_max_elements_count = other_.get_max_elements_count ();

		pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_TEMPLATE_PARAMS* other_ptr = 
			(pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_TEMPLATE_PARAMS*)(&other_);

		if (null == other_ptr->sub_string (0,this))
		{
			throw (PFX_STATUS_ERROR_);
		}
	}
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::~pfx_consecutive_array_base()
{
	m_auto_size_step = 0;
	m_max_elements_count = 0;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE		pfx_usize_t pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_new_buffer_size (pfx_usize_t new_size, pfx_usize_t auto_size_step, pfx_usize_t max_size)
{
	//RETURN_RESULT (new_size > max_size && max_size,0);
	if (0 == auto_size_step)
	{
		auto_size_step = get_auto_step ();
	}

	if (0 == auto_size_step)
	{
		auto_size_step = get_cache_buffer_size ();
	}

	if (0 != auto_size_step)
	{
		new_size = new_size / auto_size_step + (pfx_usize_t)(new_size % auto_size_step != 0);
		new_size *= auto_size_step;
	}

	if (max_size && new_size > max_size)
	{
		new_size = max_size;
	}
	
	return new_size;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::init (pfx_usize_t element_count, pfx_usize_t allocate_step_size/* = 0*/, 
pfx_boolean_t release_buffer/* = PFX_BOOL_FALSE*/)
{
	pfx_result_t status;
	pfx_usize_t new_size;

	RETURN_RESULT (is_full() && element_count > size(),PFX_STATUS_FULL);
	new_size = get_new_buffer_size(element_count,allocate_step_size,get_max_elements_count());
	status = init_string (new_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	if (release_buffer)
	{
		status = garbage_collection ();
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	if (new_size > element_count)
	{
		status = resize_string (element_count);
	}
	
	status = set_auto_step (allocate_step_size);
	return status;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::resize (pfx_usize_t element_size, pfx_boolean_t release_buffer/* = PFX_BOOL_FALSE*/)
{
	pfx_result_t status;
	pfx_usize_t new_size;

	RETURN_RESULT (is_full() && element_size > size(),PFX_STATUS_FULL);
	new_size = get_new_buffer_size(element_size,get_auto_step(),get_max_elements_count());
	status = resize_string (new_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	if (release_buffer)
	{
		status = garbage_collection ();
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}
	if (new_size > element_size)
	{
		status = resize_string (element_size);
	}
	return status;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::set_max_elements_count (pfx_usize_t max_count/* = 0*/)
{
	m_max_elements_count = max_count;
	return PFX_STATUS_OK;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::set_auto_step (pfx_usize_t auto_step/* = 0*/)
{
	m_auto_size_step = auto_step;
	return PFX_STATUS_OK;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_max_elements_count () const
{
	return m_max_elements_count;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_auto_step () const
{
	return m_auto_size_step;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::copy (const IPfx_array PFX_IARRAY_TEMPLATE_PARAMS * PARAM_IN other_ptr)
{
	pfx_result_t status = PFX_STATUS_OK;
	RETURN_INVALID_RESULT (null == other_ptr,PFX_STATUS_INVALID_PARAMS);

	if (other_ptr != this)
	{
		if (other_ptr->get_array_type_code () != this->get_array_type_code ())
		{
			pfx_usize_t success_size = 0;
			FOR_ONE_LOOP_BEGIN
			status = set_max_elements_count(other_ptr->get_max_elements_count());
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

			status = set_auto_step(other_ptr->get_auto_step());
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

			status = resize (other_ptr->size());
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

			success_size = set_element_buffers_at(0,other_ptr->get_element_at(0),other_ptr->size ());
			if (success_size != other_ptr->size())
			{
				status = PFX_STATUS_FAIL;
			}
			FOR_ONE_LOOP_END
		}
		else
		{
			status = copy ((pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS*)other_ptr);
		}
	}

	return status;

}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::copy (pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS * PARAM_INOUT other_ptr)
{
	pfx_result_t status = PFX_STATUS_OK;
	RETURN_INVALID_RESULT (null == other_ptr,PFX_STATUS_INVALID_PARAMS);
	if (other_ptr != this)
	{
		FOR_ONE_LOOP_BEGIN
			
		status = set_max_elements_count(other_ptr->get_max_elements_count());
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

		status = set_auto_step(other_ptr->get_auto_step());
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

		if (null == other_ptr->sub_string (0,this))
		{
			status = PFX_STATUS_FAIL;
		}
		FOR_ONE_LOOP_END
	}
	return status;
}


PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::push_back (const element_& elem)
{
	pfx_result_t status;	
	FOR_ONE_LOOP_BEGIN
	pfx_usize_t this_size = size();
	status = resize(this_size+1);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
	if (1 != set_element_buffers_at(this_size,&elem,1))
	{
		status = PFX_STATUS_FAIL;
	}
	FOR_ONE_LOOP_END
	return status;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::pop_back ()
{
	RETURN_RESULT (is_empty(),PFX_STATUS_EMPTY);
	return resize (size()-1);
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_buffer_size () const
{
	return get_string_buffer_size ();
}
PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::size () const
{
	return get_length ();
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE const element_*	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_element_at (pfx_uindex_t index_) const
{
	return get_charbuffer_at (index_);
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE element_*	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_element_reference_at (pfx_uindex_t index_)
{
	return (element_*)  get_charbuffer_at (index_);
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::set_element_buffers_at (pfx_uindex_t index_, const element_* PARAM_IN elements_ptr, pfx_usize_t element_size)
{
	return set_charbuffer_at (index_, elements_ptr, element_size);
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::clear (pfx_boolean_t release_buffer /*= PFX_BOOL_FALSE*/)
{
	pfx_result_t status;
	status = resize_string (0);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	if (release_buffer)
	{
		status = garbage_collection ();
	}
	return status;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_boolean_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::is_full () const
{
	return (pfx_boolean_t)(get_max_elements_count() && size() >= get_max_elements_count());
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_boolean_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::is_empty () const
{
	return (pfx_boolean_t)(0 == size());
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_ulong_t	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_array_type_code () const
{
	return PFX_CONSECUTIVE_ARRAY_CODE;
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE const element_*	pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_buffer () const
{
	return get_string ();
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_const_array_iterator < element_ >* pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::begin (pfx_const_array_iterator < element_ >* PARAM_INOUT iterator_ptr) const
{
	RETURN_INVALID_RESULT (null == iterator_ptr,null);
	pfx_result_t status;
	status = iterator_ptr->init(this,0);
	if (PFX_STATUS_OK == status)
	{
		return iterator_ptr;
	}
	else
	{
		return null;
	}
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_const_array_iterator < element_ >* pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::end (pfx_const_array_iterator < element_ >* PARAM_INOUT iterator_ptr) const
{
	RETURN_INVALID_RESULT (null == iterator_ptr,null);
	RETURN_RESULT (is_empty(),null);

	pfx_result_t status;
	status = iterator_ptr->init(this,size()-1);
	if (PFX_STATUS_OK == status)
	{
		return iterator_ptr;
	}
	else
	{
		return null;
	}
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_array_iterator < element_ >* pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::begin (pfx_array_iterator < element_ >* PARAM_INOUT iterator_ptr)
{
	RETURN_INVALID_RESULT (null == iterator_ptr,null);
	pfx_result_t status;
	status = iterator_ptr->init(this,0);
	if (PFX_STATUS_OK == status)
	{
		return iterator_ptr;
	}
	else
	{
		return null;
	}
}

PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_array_iterator < element_ >* pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::end (pfx_array_iterator < element_ >* PARAM_INOUT iterator_ptr)
{
	RETURN_INVALID_RESULT (null == iterator_ptr,null);
	RETURN_RESULT (is_empty(),null);

	pfx_result_t status;
	status = iterator_ptr->init(this,size()-1);
	if (PFX_STATUS_OK == status)
	{
		return iterator_ptr;
	}
	else
	{
		return null;
	}
}


//////////////////////////////////////////////////////////////////////////
PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::pfx_inconsecutive_array_base () :
m_auto_size_step (0),
m_max_elements_count (0),
m_elements_count (0)
{
	pfx_result_t					status;
	consecutive_array**		array_ptr_ptr;

	FOR_ONE_LOOP_BEGIN
	status = m_array_array.init (m_array_array.get_buffer_size ());
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
	
	array_ptr_ptr = m_array_array.get_element_reference_at (0);
	BREAK_LOOP_CONDITION (null == array_ptr_ptr);

	pfx_usize_t arr_size;
	arr_size = m_array_array.get_buffer_size ();
	for (pfx_uindex_t i=0; i<arr_size; ++i)
	{
		array_ptr_ptr [i] = null;
	}

	m_array_array.resize (0);
	FOR_ONE_LOOP_END
}


PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::pfx_inconsecutive_array_base (const pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS &other_) throw (pfx_result_t)
{
	if (&other_ != this)
	{
		pfx_result_t					status;
		consecutive_array**		array_ptr_ptr;

		FOR_ONE_LOOP_BEGIN
		
		status = m_array_array.init (other_.m_array_array.get_buffer_size ());
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

		array_ptr_ptr = m_array_array.get_element_reference_at (0);
		BREAK_LOOP_CONDITION (null == array_ptr_ptr);

		pfx_usize_t arr_size;
		arr_size = m_array_array.get_buffer_size ();
		for (pfx_uindex_t i=0; i<arr_size; ++i)
		{
			array_ptr_ptr [i] = null;
		}
		m_array_array.resize (0);
		
		set_max_elements_count (other_.get_max_elements_count ());
		//set_auto_step (other_.get_auto_step ());

		status = init (other_.size (),other_.get_auto_step());
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

		consecutive_array**	other_array_ptr_ptr;

		array_ptr_ptr = m_array_array.get_element_reference_at (0);
		other_array_ptr_ptr = (consecutive_array**) (other_.m_array_array.get_element_at (0));

		for (pfx_uindex_t i=0; i < m_array_array.size(); ++i)
		{	
			status = array_ptr_ptr [i]->copy (other_array_ptr_ptr[i]);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
		}

		FOR_ONE_LOOP_END

		if (PFX_STATUS_OK != status)
		{
			throw (status);
		}

		//m_elements_count = other_.size();
	}

}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::~pfx_inconsecutive_array_base()
{
	pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::clear (PFX_BOOL_TRUE);
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE consecutive_array*	pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::new_array_block ()
{
	return new consecutive_array;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::delete_array_block (consecutive_array* PARAM_INOUT array_ptr)
{
	if (array_ptr)
	{
		delete array_ptr;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_INVALID_PARAMS;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
	PFX_INLINE pfx_usize_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
	get_step_cache_size () const
{
	return PFX_DEFUALT_ARRAY_SIZE;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
			get_current_auto_step () const
{
	pfx_usize_t current_auto_step;
	consecutive_array* const*	array_ptr_ptr;

	current_auto_step = 0;

	if (m_array_array.size () > 0)
	{
		array_ptr_ptr = m_array_array.get_element_at (0);
		if (array_ptr_ptr)
		{
			current_auto_step = (*array_ptr_ptr)->get_max_elements_count ();
		}
	}

	if (0 == current_auto_step)
	{
		current_auto_step = get_auto_step();
	}

	if (0 == current_auto_step)
	{
		current_auto_step = get_step_cache_size ();
	}

	if (0 == current_auto_step)
	{
		current_auto_step = PFX_DEFUALT_ARRAY_SIZE;
	}
	return current_auto_step;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE element_*	pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::get_element_reference_at (pfx_uindex_t index_, pfx_usize_t step_size)
{
	pfx_uindex_t arr_i;
	pfx_uindex_t arr_j;
	element_* elem_ptr;
	consecutive_array**	array_ptr_ptr;
	elem_ptr = null;
	array_ptr_ptr = (consecutive_array**) m_array_array.get_buffer ();
	if (array_ptr_ptr)
	{
		arr_i = index_ / step_size;
		arr_j = index_ % step_size;

		consecutive_array* array_ptr;
		array_ptr = array_ptr_ptr [arr_i];
		if (array_ptr)
		{
			elem_ptr = (element_*) array_ptr->get_buffer ();
			if (elem_ptr)
			{
				elem_ptr += arr_j;
			}	
		}
	}
	return elem_ptr;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
init_remian_element (pfx_usize_t element_count, pfx_usize_t allocate_step_size /*= 0*/, pfx_boolean_t release_buffer /*= PFX_BOOL_FALSE*/)
{
	pfx_result_t status;
	pfx_usize_t arr_arr_auto_step;
	pfx_usize_t arr_arr_size;
	pfx_usize_t old_auto_step;
	consecutive_array**	array_ptr_ptr;

	RETURN_RESULT (is_full() && element_count > size(),PFX_STATUS_FULL);

	arr_arr_auto_step = 0;
	arr_arr_size			= 0;
	old_auto_step		= get_current_auto_step();

	if (0== allocate_step_size)
	{
		allocate_step_size = old_auto_step;
	}

	arr_arr_size = element_count / allocate_step_size + (pfx_usize_t)(element_count % allocate_step_size != 0);

	pfx_usize_t old_size = m_array_array.size ();
	pfx_usize_t old_buffer_size = m_array_array.get_buffer_size ();

	status = m_array_array.resize (old_buffer_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	status = m_array_array.resize (arr_arr_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	pfx_usize_t new_size = m_array_array.size ();
	pfx_usize_t new_buffer_size = m_array_array.get_buffer_size ();


	array_ptr_ptr = m_array_array.get_element_reference_at (0);
	for (pfx_uindex_t i = old_buffer_size; i<new_buffer_size; ++i)
	{
		array_ptr_ptr [i] = null;
	}

	for (pfx_uindex_t i=old_size; i<new_size; ++i)
	{
		if (null == array_ptr_ptr[i])
		{
			array_ptr_ptr [i] = new_array_block();
		}
		RETURN_INVALID_RESULT (null == array_ptr_ptr[i],PFX_STATUS_MEM_LOW);

		status = array_ptr_ptr [i] -> set_max_elements_count (allocate_step_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

		//status = array_ptr_ptr [i] -> init (allocate_step_size);
		status = array_ptr_ptr [i] -> resize (allocate_step_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	if (old_auto_step != allocate_step_size)
	{
		for (pfx_uindex_t i=0; i<old_size; ++i)
		{
			status = array_ptr_ptr [i] -> set_max_elements_count (allocate_step_size);
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

			//status = array_ptr_ptr [i] -> init (allocate_step_size);
			status = array_ptr_ptr [i] -> resize (allocate_step_size);
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
		}
	}

	if (new_size > 1)
	{
		//status = array_ptr_ptr [new_size - 2] -> init (allocate_step_size);
		//status = array_ptr_ptr [new_size - 1] -> init (element_count % allocate_step_size);
		status = array_ptr_ptr [new_size - 2] -> resize (allocate_step_size);
		status = array_ptr_ptr [new_size -1] -> resize (element_count % allocate_step_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}
	else if (new_size > 0 && element_count != allocate_step_size)
	{
		//status = array_ptr_ptr [0] -> init (element_count);
		status = array_ptr_ptr [0] -> resize (element_count);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	m_elements_count = element_count;
	m_auto_size_step = allocate_step_size;

	if (release_buffer)
	{
		for (pfx_uindex_t i = new_size; i<old_buffer_size; ++i)
		{
			status = delete_array_block(array_ptr_ptr [i]);
			array_ptr_ptr [i] = null;
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
		}
		status = m_array_array.resize (arr_arr_size, release_buffer);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	return status;
}
PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
			init (pfx_usize_t element_count, pfx_usize_t allocate_step_size/* = 0*/, pfx_boolean_t release_buffer/* = PFX_BOOL_FALSE*/)
{
	pfx_result_t status;
	pfx_usize_t arr_arr_auto_step;
	pfx_usize_t arr_arr_size;
	pfx_usize_t old_auto_step;
	consecutive_array**	array_ptr_ptr;

	RETURN_RESULT (is_full() && element_count > size(),PFX_STATUS_FULL);

	arr_arr_auto_step = 0;
	arr_arr_size			= 0;
	old_auto_step		= get_current_auto_step();

	if (0== allocate_step_size)
	{
		allocate_step_size = old_auto_step;
	}

	arr_arr_size = element_count / allocate_step_size + (pfx_usize_t)(element_count % allocate_step_size != 0);

	pfx_usize_t old_size = m_array_array.size ();
	pfx_usize_t old_buffer_size = m_array_array.get_buffer_size ();

	status = m_array_array.resize (old_buffer_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	status = m_array_array.resize (arr_arr_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	pfx_usize_t new_size = m_array_array.size ();
	pfx_usize_t new_buffer_size = m_array_array.get_buffer_size ();
	

	array_ptr_ptr = m_array_array.get_element_reference_at (0);
	for (pfx_uindex_t i = old_buffer_size; i<new_buffer_size; ++i)
	{
		array_ptr_ptr [i] = null;
	}

	for (pfx_uindex_t i=old_size; i<new_size; ++i)
	{
		if (null == array_ptr_ptr[i])
		{
			array_ptr_ptr [i] = new_array_block();
		}
		RETURN_INVALID_RESULT (null == array_ptr_ptr[i],PFX_STATUS_MEM_LOW);

		status = array_ptr_ptr [i] -> set_max_elements_count (allocate_step_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

		status = array_ptr_ptr [i] -> init (allocate_step_size);
		//status = array_ptr_ptr [i] -> resize (allocate_step_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	if (old_auto_step != allocate_step_size)
	{
		for (pfx_uindex_t i=0; i<old_size; ++i)
		{
			status = array_ptr_ptr [i] -> set_max_elements_count (allocate_step_size);
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

			status = array_ptr_ptr [i] -> init (allocate_step_size);
			//status = array_ptr_ptr [i] -> resize (allocate_step_size);
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
		}
	}

	if (new_size > 1)
	{
		status = array_ptr_ptr [new_size - 2] -> init (allocate_step_size);
		status = array_ptr_ptr [new_size - 1] -> init (element_count % allocate_step_size);
		//status = array_ptr_ptr [new_size - 2] -> resize (allocate_step_size);
		//status = array_ptr_ptr [new_size -1] -> resize (element_count % allocate_step_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}
	else if (new_size > 0 && element_count != allocate_step_size)
	{
		status = array_ptr_ptr [0] -> init (element_count);
		//status = array_ptr_ptr [0] -> resize (element_count);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	m_elements_count = element_count;
	m_auto_size_step = allocate_step_size;

	if (release_buffer)
	{
		for (pfx_uindex_t i = new_size; i<old_buffer_size; ++i)
		{
			status = delete_array_block(array_ptr_ptr [i]);
			array_ptr_ptr [i] = null;
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
		}
		status = m_array_array.resize (arr_arr_size, release_buffer);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	return status;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
			resize (pfx_usize_t element_size, pfx_boolean_t release_buffer/* = PFX_BOOL_FALSE*/)
{
	pfx_result_t status;
	pfx_usize_t arr_arr_auto_step;
	pfx_usize_t arr_arr_size;

	RETURN_RESULT (is_full() && element_size > size(),PFX_STATUS_FULL);

	arr_arr_auto_step = 0;
	arr_arr_size			= 0;

	pfx_usize_t	allocate_step_size = get_current_auto_step();
	if (0 == allocate_step_size)
	{
		allocate_step_size = PFX_DEFUALT_ARRAY_SIZE;
	}

	arr_arr_size = element_size / allocate_step_size + (pfx_usize_t)(element_size % allocate_step_size != 0);

	pfx_usize_t old_size = m_array_array.size ();
	pfx_usize_t old_buffer_size = m_array_array.get_buffer_size ();
	
	status = m_array_array.resize (old_buffer_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	status = m_array_array.resize (arr_arr_size);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	pfx_usize_t new_size = m_array_array.size ();
	pfx_usize_t new_buffer_size = m_array_array.get_buffer_size ();
	consecutive_array**	array_ptr_ptr;

	array_ptr_ptr = (consecutive_array**) m_array_array.get_buffer();
	for (pfx_uindex_t i = old_buffer_size; i<new_buffer_size; ++i)
	{
		array_ptr_ptr [i] = null;
	}

	for (pfx_uindex_t i=old_size; i<new_size; ++i)
	{
		if (null == array_ptr_ptr[i])
		{
			array_ptr_ptr [i] = new_array_block();
		}
		RETURN_INVALID_RESULT (null == array_ptr_ptr[i],PFX_STATUS_MEM_LOW);

		status = array_ptr_ptr [i] -> set_max_elements_count (allocate_step_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

		status = array_ptr_ptr [i] -> resize (allocate_step_size,release_buffer);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	if (new_size > 1)
	{
		status = array_ptr_ptr [new_size - 2] -> resize (allocate_step_size);
		status = array_ptr_ptr [new_size - 1] -> resize (element_size % allocate_step_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}
	else if (new_size > 0 && element_size != allocate_step_size)
	{
		status = array_ptr_ptr [0] -> resize (element_size);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	m_elements_count	= element_size;
	m_auto_size_step		= allocate_step_size;

	if (release_buffer)
	{
		for (pfx_uindex_t i = new_size; i<old_buffer_size; ++i)
		{
			status = delete_array_block(array_ptr_ptr [i]);
			array_ptr_ptr [i] = null;
			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
		}
		status = m_array_array.resize (arr_arr_size, release_buffer);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
	}

	return status;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
			set_max_elements_count (pfx_usize_t max_count /*= 0*/)
{
	m_max_elements_count = max_count;
	return PFX_STATUS_OK;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
			set_auto_step (pfx_usize_t auto_step /*= 0*/)
{
	pfx_result_t status;

	FOR_ONE_LOOP_BEGIN
	if (0 == auto_step)
	{
		if (0 == m_auto_size_step)
		{
			m_auto_size_step = get_current_auto_step();
		}
		BREAK_LOOP (status,PFX_STATUS_OK);
	}

	pfx_usize_t current_step;
	pfx_usize_t size_;

	current_step = get_current_auto_step();
	if (current_step < auto_step)
	{
		size_ = size();
		status = init_remian_element(size_,auto_step);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

		for (pfx_uindex_t i=current_step; i<size_; ++i)
		{
			element_* elem_dec_ptr =	get_element_reference_at (i,auto_step);
			element_* elem_src_ptr = get_element_reference_at(i,current_step);

			if (elem_dec_ptr && elem_src_ptr)
			{
				*elem_dec_ptr = *elem_src_ptr;
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
				break;
			}
			
		}
	}
	else if (current_step > auto_step)
	{
		size_ = size();
		status = init_remian_element(size_,auto_step);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

		for (pfx_uindex_t i=size_; i>current_step; ++i)
		{
			element_* elem_dec_ptr =	get_element_reference_at (i,auto_step);
			element_* elem_src_ptr = get_element_reference_at(i,current_step);

			if (elem_dec_ptr && elem_src_ptr)
			{
				*elem_dec_ptr = *elem_src_ptr;
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
				break;
			}

		}
	}
	FOR_ONE_LOOP_END

	return status;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
			get_max_elements_count () const
{
	return m_max_elements_count;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
			get_auto_step () const
{
	return m_auto_size_step;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
			copy (const IPfx_array PFX_IARRAY_TEMPLATE_PARAMS * PARAM_IN other_ptr)
{
	pfx_result_t status = PFX_STATUS_OK;

	FOR_ONE_LOOP_BEGIN
	if (other_ptr != this)
	{
		if (other_ptr->get_array_type_code () != this->get_array_type_code ())
		{
			status = this->init (other_ptr->size (),other_ptr->get_auto_step());
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

			pfx_usize_t size_ = size();
			
			for (pfx_uindex_t i=0; i<size_;++i)
			{
				element_* dec_ptr = get_element_reference_at(i);
				const element_* src_ptr = get_element_at(i);
				if (dec_ptr && src_ptr)
				{
					*dec_ptr = *src_ptr;
				}
				else
				{
					status = PFX_STATUS_MEM_ERR;
					break;
				}
			}
		}
		else
		{
			status = copy((pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS * )other_ptr);
		}
	}

	FOR_ONE_LOOP_END

	return status;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t	pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		copy (pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS * PARAM_INOUT other_)
{
	pfx_result_t	status;
	status = PFX_STATUS_OK;

	if (other_ != this)
	{
		FOR_ONE_LOOP_BEGIN
		consecutive_array**	array_ptr_ptr;
		consecutive_array**	other_array_ptr_ptr;

		set_max_elements_count (other_->get_max_elements_count ());
		
		status = init (other_->size (),other_->get_auto_step());
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
		
		BREAK_LOOP_CONDITION (0 == other_->size ());

		array_ptr_ptr = m_array_array.get_element_reference_at (0);
		other_array_ptr_ptr = (consecutive_array**) (other_->m_array_array.get_element_at (0));

		BREAK_LOOP_CONDITION (null == array_ptr_ptr || null == other_array_ptr_ptr);

		for (pfx_uindex_t i=0; i < m_array_array.size(); ++i)
		{	
			status = array_ptr_ptr [i]->copy (other_array_ptr_ptr[i]);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
		}

		FOR_ONE_LOOP_END
	}

	return status;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		push_back (const element_& elem)
{
	pfx_result_t	status;
	pfx_usize_t		size_;

	FOR_ONE_LOOP_BEGIN
	size_ = size();
	status = resize(size_+1);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

	if (1 != set_element_buffers_at(size_,&elem,1))
	{
		status = PFX_STATUS_FAIL;
	}
	FOR_ONE_LOOP_END
	
	return status;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		pop_back ()
{
	RETURN_RESULT (is_empty(),PFX_STATUS_EMPTY);
	return resize(size()-1);
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		get_buffer_size () const
{
	pfx_result_t step_size;
	step_size = get_current_auto_step();
	return (m_elements_count - m_elements_count % step_size + step_size);
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		size () const
{
	return m_elements_count;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE const element_*	pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		get_element_at (pfx_uindex_t index_) const
{
	pfx_uindex_t arr_i;
	pfx_uindex_t arr_j;
	pfx_usize_t		step_size;
	const element_* elem_ptr;
	consecutive_array * const *	array_ptr_ptr;
	elem_ptr = null;
	array_ptr_ptr = m_array_array.get_element_at (0);
	step_size = get_current_auto_step();

	if (array_ptr_ptr)
	{
		arr_i = index_ / step_size;
		arr_j = index_ % step_size;

		const consecutive_array* array_ptr;
		array_ptr = array_ptr_ptr [arr_i];
		if (array_ptr)
		{
			//elem_ptr = array_ptr->get_element_at (0);
			//if (elem_ptr)
			//{
			//	elem_ptr += arr_j;
			//}
			elem_ptr = array_ptr->get_element_at (arr_j);
		}
	}
	return elem_ptr;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE element_*				pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		get_element_reference_at (pfx_uindex_t index_)
{
	return (element_*)get_element_at(index_);
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_usize_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		set_element_buffers_at (pfx_uindex_t index_, const element_* PARAM_IN elements_ptr, pfx_usize_t element_size)
{
	RETURN_RESULT (index_ > m_elements_count || null == elements_ptr || 0 == element_size,0);

	pfx_uindex_t arr_i;
	pfx_uindex_t arr_j;
	pfx_usize_t		step_size;
	pfx_usize_t success_size;
	pfx_usize_t total_success_size;

	element_* elem_ptr;
	consecutive_array**	array_ptr_ptr;
	elem_ptr = null;
	step_size = get_current_auto_step ();
	arr_i = index_ / step_size;
	arr_j = index_ % step_size;
	total_success_size = 0;

	FOR_ONE_LOOP_BEGIN
	array_ptr_ptr = (consecutive_array**) m_array_array.get_element_reference_at (arr_i);
	if (array_ptr_ptr)
	{
		consecutive_array* array_ptr;
		array_ptr = *array_ptr_ptr;
		BREAK_LOOP_CONDITION (null == array_ptr);

		success_size = array_ptr->set_element_buffers_at (arr_j,elements_ptr,element_size);

		BREAK_LOOP_CONDITION (0 == success_size);

		element_size -= success_size;
		total_success_size += success_size;
		elements_ptr += success_size;
		BREAK_LOOP_CONDITION (0 == element_size);

		
		while (arr_i < size())
		{
			++arr_i;
			array_ptr_ptr = (consecutive_array**) m_array_array.get_element_reference_at (arr_i);
			if (array_ptr_ptr)
			{
				array_ptr = *array_ptr_ptr;
				BREAK_LOOP_CONDITION (null == array_ptr);

				success_size = array_ptr->set_element_buffers_at (0,elements_ptr,element_size);

				BREAK_LOOP_CONDITION (0 == success_size);

				element_size -= success_size;
				total_success_size += success_size;
				elements_ptr += success_size;
				BREAK_LOOP_CONDITION (0 == element_size);
			}
			else
			{
				break;
			}

		}
		



	}
	FOR_ONE_LOOP_END

	return total_success_size;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE)
{
	return resize(0,release_buffer);
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_boolean_t		pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		is_full () const
{
	return (pfx_boolean_t) (m_max_elements_count && m_max_elements_count <= m_elements_count);
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_boolean_t		pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		is_empty () const
{
	return (pfx_boolean_t) (0 == m_elements_count);
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
PFX_INLINE pfx_ulong_t			pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		get_array_type_code () const
{
	return PFX_INCONSECUTIVE_ARRAY_CODE;
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_const_array_iterator < element_ >* pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		begin (pfx_const_array_iterator < element_ >* PARAM_INOUT iterator_ptr) const
{
	RETURN_INVALID_RESULT (null == iterator_ptr,null);
	pfx_result_t status;
	status = iterator_ptr->init(this,0);
	if (PFX_STATUS_OK == status)
	{
		return iterator_ptr;
	}
	else
	{
		return null;
	}
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_const_array_iterator < element_ >* pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		end (pfx_const_array_iterator < element_ >* PARAM_INOUT iterator_ptr) const
{
	RETURN_INVALID_RESULT (null == iterator_ptr,null);
	RETURN_RESULT (is_empty(),null);

	pfx_result_t status;
	status = iterator_ptr->init(this,size()-1);
	if (PFX_STATUS_OK == status)
	{
		return iterator_ptr;
	}
	else
	{
		return null;
	}
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_array_iterator < element_ >* pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		begin (pfx_array_iterator < element_ >* PARAM_INOUT iterator_ptr)
{
	RETURN_INVALID_RESULT (null == iterator_ptr,null);
	pfx_result_t status;
	status = iterator_ptr->init(this,0);
	if (PFX_STATUS_OK == status)
	{
		return iterator_ptr;
	}
	else
	{
		return null;
	}
}

PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES
pfx_array_iterator < element_ >* pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS ::
		end (pfx_array_iterator < element_ >* PARAM_INOUT iterator_ptr)
{
	RETURN_INVALID_RESULT (null == iterator_ptr,null);
	RETURN_RESULT (is_empty(),null);

	pfx_result_t status;
	status = iterator_ptr->init(this,size()-1);
	if (PFX_STATUS_OK == status)
	{
		return iterator_ptr;
	}
	else
	{
		return null;
	}
}


PECKER_END

#endif			//PFX_ARRAY_CODES_H_
