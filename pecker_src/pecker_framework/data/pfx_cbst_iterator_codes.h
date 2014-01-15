/*
 * pfx_cbst_iterator_codes.h
 *
 *  Created on: 2014-1-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBST_ITERATOR_CODES_H_
#define		PFX_CBST_ITERATOR_CODES_H_

#include "pfx_cbst.h"

PECKER_BEGIN

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: pfx_cbst_iterator () : m_current_node_ptr (null), 
																																				m_root_node_ptr (null)
{

}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: ~pfx_cbst_iterator()
{
	m_current_node_ptr = null;
	m_root_node_ptr = null;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
const node_type_* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: get_current_node () const
{
	return m_current_node_ptr;
}
	
PFX_CBST_ITERATOR_TEMPLATE_DEFINES
const node_type_* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: get_root_node () const
{
	return m_root_node_ptr;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_result_t pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (const node_type_*	current_node_ptr,
		const node_type_*   root_node_ptr)
{
	m_root_node_ptr = root_node_ptr;
	m_current_node_ptr = current_node_ptr;
	return PFX_STATUS_OK;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: begin 
		(pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_INOUT 
		set_begin_iterator_ptr) const
{
	if (set_begin_iterator_ptr)
	{
		const node_type_* min_node_ptr = pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: min_node (m_root_node_ptr);
		pfx_result_t status_ = set_begin_iterator_ptr->init (min_node_ptr,m_root_node_ptr);
		if (PFX_STATUS_OK == status_)
		{
			return set_begin_iterator_ptr;
		}
		else
		{
			return null;
		}
	}
	else
	{
		return null;
	}

}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: end 		
	(pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_INOUT 
	set_end_iterator_ptr) const
{
	if (set_end_iterator_ptr)
	{
		const node_type_* max_node_ptr = pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: max_node (m_root_node_ptr);
		pfx_result_t status_ = set_end_iterator_ptr->init (max_node_ptr,m_root_node_ptr);
		if (PFX_STATUS_OK == status_)
		{
			return set_end_iterator_ptr;
		}
		else
		{
			return null;
		}
	}
	else
	{
		return null;
	}
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: begin ()
{
	if (m_root_node_ptr)
	{
		m_current_node_ptr = pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: min_node (m_root_node_ptr);
		return this;
	}
	else
	{
		return null;
	}
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: end ()
{
	if (m_root_node_ptr)
	{
		m_current_node_ptr = pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: max_node (m_root_node_ptr);
		return this;
	}
	else
	{
		return null;
	}
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: next ()
{
	if (null == m_current_node_ptr || null == m_root_node_ptr)
	{
		return null;
	}

	const node_type_* right_node_ptr;
	const node_type_* parent_node_ptr;

	right_node_ptr = m_current_node_ptr->get_right_node ();

	if (m_current_node_ptr == m_root_node_ptr)
	{
		if (null != right_node_ptr)
		{
			return pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: min_node (right_node_ptr);
		}
		else
		{
			return null;
		}
	}

	if (null != right_node_ptr)
	{
		return pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: min_node (right_node_ptr);
	}

	parent_node_ptr = m_current_node_ptr->get_parent_node ();

	if (parent_node_ptr->get_left_node () == m_current_node_ptr)
	{
		return parent_node_ptr;
	}

	if (m_current_node_ptr == parent_node_ptr)
	{
		return null;
	}

	m_current_node_ptr =  m_current_node_ptr->m_parent_node;

	while (1)
	{
		parent_node_ptr = m_current_node_ptr->get_parent_node ();
		if (null == parent_node_ptr)
		{
			break;
		}

		if (parent_node_ptr->get_right_node () == m_current_node_ptr)
		{
			m_current_node_ptr = m_current_node_ptr->m_parent_node;
			continue;
		}

		if (parent_node_ptr->get_left_node () == m_current_node_ptr)
		{
			m_current_node_ptr = m_current_node_ptr->m_parent_node;
			break;
		}

	}
	return m_current_node_ptr;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: prev ()
{
	if (null == m_current_node_ptr || null == m_root_node_ptr)
	{
		return null;
	}

	const node_type_* left_node_ptr;
	const node_type_* parent_node_ptr;

	left_node_ptr = m_current_node_ptr->get_left_node ();

	if (m_current_node_ptr == m_root_node_ptr)
	{
		if (null != left_node_ptr)
		{
			return pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: max_node (left_node_ptr);
		}
		else
		{
			return null;
		}
	}

	if (null != left_node_ptr)
	{
		return pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: max_node (left_node_ptr);
	}

	if (parent_node_ptr->get_right_node () == m_current_node_ptr)
	{
		return parent_node_ptr;
	}

	if (m_current_node_ptr == parent_node_ptr)
	{
		return null;
	}

	m_current_node_ptr =  parent_node_ptr;
	while (1)
	{
		parent_node_ptr = m_current_node_ptr->get_parent_node ();
		if (null == parent_node_ptr)
		{
			break;
		}
		if (parent_node_ptr->get_left_node () == m_current_node_ptr)
		{
			m_current_node_ptr = parent_node_ptr;
			continue;
		}
		if (parent_node_ptr->get_right_node () == m_current_node_ptr)
		{
			m_current_node_ptr = parent_node_ptr;
			break;
		}

	}
	return m_current_node_ptr;
}

PECKER_END

#endif			//PFX_CBST_ITERATOR_CODES_H_
