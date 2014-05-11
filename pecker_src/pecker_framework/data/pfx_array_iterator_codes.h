/*
 * pfx_array_iterator_codes.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_ARRAY_ITERATOR_CODES_H_
#define		PFX_ARRAY_ITERATOR_CODES_H_

#include "pfx_array.h"

PECKER_BEGIN

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
const_array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::const_array_iterator () : 
					m_attach_array_ptr (null),
					m_index (0)
{

}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
const_array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::~const_array_iterator ()
{
	m_attach_array_ptr = null;
	m_index = 0;
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
result_t const_array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::init (const IPfx_array < element_ >* attach_array_ptr, uindex_t current_index)
{
	const element_*	element_ptr;
	RETURN_INVALID_RESULT (null == attach_array_ptr,PFX_STATUS_INVALID_PARAMS);
	element_ptr = attach_array_ptr->get_element_at (current_index);
	RETURN_INVALID_RESULT (null == element_ptr,PFX_STATUS_INVALID_PARAMS);
	m_attach_array_ptr = attach_array_ptr;
	m_index = current_index;
	return PFX_STATUS_OK;
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
IPfx_array_iterator < element_ >*		const_array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::increase ()
{
	uindex_t			next_index;
	const element_*	next_element_ptr;
	RETURN_RESULT (null == m_attach_array_ptr,null);
	next_index = m_index + 1;
	next_element_ptr = m_attach_array_ptr->get_element_at (next_index);
	RETURN_RESULT (null == next_element_ptr,null);
	m_index = next_index;
	return this;
};

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
IPfx_array_iterator < element_ >*		const_array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::decrease ()
{
	uindex_t			next_index;
	const element_*	next_element_ptr;
	RETURN_RESULT (null == m_attach_array_ptr || 0 == m_index,null);
	next_index = m_index - 1;
	next_element_ptr = m_attach_array_ptr->get_element_at (next_index);
	RETURN_RESULT (null == next_element_ptr,null);
	m_index = next_index;
	return this;
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
IPfx_increase_iterator < element_ >*	const_array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::increase_iterator ()
{
	return increase ();
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
IPfx_decrease_iterator < element_ >* const_array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::decrease_iterator ()
{
	return decrease ();
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
const element_*							const_array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::get_current_element () const
{
	RETURN_RESULT (null == m_attach_array_ptr,null);
	return m_attach_array_ptr->get_element_at (m_index);
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
	array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::array_iterator () : 
m_attach_array_ptr (null),
	m_index (0)
{

}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
	array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::~array_iterator ()
{
	m_attach_array_ptr = null;
	m_index = 0;
}



PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
result_t array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::init (const IPfx_array < element_ >* attach_array_ptr, uindex_t current_index)
{
	const element_*	element_ptr;
	RETURN_INVALID_RESULT (null == attach_array_ptr,PFX_STATUS_INVALID_PARAMS);
	element_ptr = attach_array_ptr->get_element_at (current_index);
	RETURN_INVALID_RESULT (null == element_ptr,PFX_STATUS_INVALID_PARAMS);
	m_attach_array_ptr = (IPfx_array < element_ >*) attach_array_ptr;
	m_index = current_index;
	return PFX_STATUS_OK;
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
IPfx_array_iterator < element_ >*		array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::increase ()
{
	uindex_t			next_index;
	const element_*	next_element_ptr;
	RETURN_RESULT (null == m_attach_array_ptr,null);
	next_index = m_index + 1;
	next_element_ptr = m_attach_array_ptr->get_element_at (next_index);
	RETURN_RESULT (null == next_element_ptr,null);
	m_index = next_index;
	return this;
};

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
	IPfx_array_iterator < element_ >*		array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::decrease ()
{
	uindex_t			next_index;
	const element_*	next_element_ptr;
	RETURN_RESULT (null == m_attach_array_ptr || 0 == m_index,null);
	next_index = m_index - 1;
	next_element_ptr = m_attach_array_ptr->get_element_at (next_index);
	RETURN_RESULT (null == next_element_ptr,null);
	m_index = next_index;
	return this;
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
	IPfx_increase_iterator < element_ >*	array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::increase_iterator ()
{
	return increase ();
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
	IPfx_decrease_iterator < element_ >* array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::decrease_iterator ()
{
	return decrease ();
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
const element_*							array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::get_current_element () const
{
	RETURN_RESULT (null == m_attach_array_ptr,null);
	return m_attach_array_ptr->get_element_at (m_index);
}

PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES
element_*							array_iterator PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS ::get_current_element_reference ()
{
	RETURN_RESULT (null == m_attach_array_ptr,null);
	return m_attach_array_ptr->get_element_reference_at (m_index);
}



PECKER_END

#endif			//PFX_ARRAY_ITERATOR_CODES_H_
