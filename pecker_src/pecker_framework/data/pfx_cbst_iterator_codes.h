﻿/*
 * pfx_cbst_iterator_codes.h
 *
 *  Created on: 2014-1-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBST_ITERATOR_CODES_H_
#define		PFX_CBST_ITERATOR_CODES_H_

#include "pfx_cbst.h"

PECKER_BEGIN

// 搜索二叉树中序遍历
PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: pfx_cbst_iterator () : m_current_node_ptr (null), 
																																				m_root_node_ptr (null)
{

}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: ~pfx_cbst_iterator()
{
	m_current_node_ptr	= null;
	m_root_node_ptr			= null;
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
	RETURN_INVALID_RESULT ((null == root_node_ptr),PFX_STATUS_INVALID_PARAMS);
	m_root_node_ptr			= root_node_ptr;
	m_current_node_ptr	= current_node_ptr;
	return PFX_STATUS_OK;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: begin 
		(pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_INOUT 
		set_begin_iterator_ptr) const
{
	if (set_begin_iterator_ptr)
	{
		//const node_type_* min_node_ptr = pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: min_node (m_root_node_ptr);
		pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS		tmp_itr						= *this;
		pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*	tmp_begin_itr_ptr	= tmp_itr.begin();

		if (null == tmp_begin_itr_ptr)
		{
			return null;
		}

		pfx_result_t status_ = set_begin_iterator_ptr->init (tmp_begin_itr_ptr->get_current_node (),
			tmp_begin_itr_ptr->get_root_node());

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
		//const node_type_* max_node_ptr = pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: max_node (m_root_node_ptr);
		pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS		tmp_itr					= *this;
		pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*	tmp_end_itr_ptr	= tmp_itr.end ();

		if (null == tmp_end_itr_ptr)
		{
			return null;
		}

		//pfx_result_t status_ = set_end_iterator_ptr->init (max_node_ptr,m_root_node_ptr);
		pfx_result_t status_ = set_begin_iterator_ptr->init (tmp_end_itr_ptr->get_current_node (),
			tmp_end_itr_ptr->get_root_node());

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

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
const node_type_* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: get_inorder_begin_node (const node_type_* root_node_ptr)
{
	return pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: min_node (root_node_ptr);
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
const node_type_* pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: get_inorder_end_node (const node_type_* root_node_ptr)
{
	return pfx_cbst PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: max_node (m_root_node_ptr);
}

// 搜索二叉树前序遍历
PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_result_t pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (const node_type_*	current_node_ptr,
	const node_type_*   root_node_ptr)
{
	const node_type_* begin_node_ptr;
	const node_type_* end_node_ptr;

	pfx_result_t status_;
	
	status_ = pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (current_node_ptr,root_node_ptr);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status_),status_);

	m_last_result = PFX_STATUS_OK;
	begin_node_ptr = root_node_ptr;

	// 找出前序遍历最后一个值
	end_node_ptr = pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_preorder_end_node (root_node_ptr);

	// 初始化m_next_node_type
	if (null == m_current_node_ptr)
	{
		m_current_node_ptr = begin_node_ptr;
	}

	if (end_node_ptr != m_current_node_ptr)
	{
		// 非最后一个节点
		if (m_current_node_ptr->get_left_node ())
		{
			m_next_node_type = PREORDER_NEXT_LEFT;
		}
		else if (m_current_node_ptr->get_right_node ())
		{
			m_next_node_type = PREORDER_NEXT_RIGHT;
		}
		else
		{
			m_next_node_type = PREORDER_FIN;
		}
	}
	else
	{
		// 最后一个节点
		m_next_node_type = PREORDER_NEXT_END;
	}

	return status_;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::begin () const
{

	pfx_result_t status_;

	status_ =  pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (m_root_node_ptr,m_root_node_ptr);

	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,null);

	m_last_result = PFX_STATUS_OK;
	
	if (m_current_node_ptr)
	{
		if (m_current_node_ptr->get_left_node ())
		{
			m_next_node_type = PREORDER_NEXT_LEFT;
		}
		else if (m_current_node_ptr->get_right_node ())
		{
			m_next_node_type = PREORDER_NEXT_RIGHT;
		}
		else
		{
			m_next_node_type = PREORDER_FIN;
		}
	}

	return this;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::end () const
{
	const node_type_* end_node_ptr;

	pfx_result_t status_;
	m_last_result		= PFX_STATUS_OK;
	// 找出前序遍历最后一个值
	end_node_ptr	= pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_preorder_end_node (root_node_ptr);
	status_				= pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (end_node_ptr,m_root_node_ptr);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status_),null);

	m_last_result = PFX_STATUS_OK;
	m_next_node_type = PREORDER_NEXT_END;

	return this;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::next ()
{
	pfx_enum_t				back_up_next_type;
	pfx_enum_t				next_type;
	const node_type_*	next_node_ptr;
	pfx_result_t				status = PFX_STATUS_OK;

	RETURN_INVALID_RESULT (null == m_root_node_ptr ||
		null == m_current_node_ptr ||
		enum_preorder_iterator_next_node_type_COUNT <= m_next_node_type||
		PFX_STATUS_OK != m_last_result), null);

	back_up_next_type = m_next_node_type;

	switch (back_up_next_type)
	{
	case PREORDER_NEXT_SUB_ROOT_RIGHT:
		{
			const node_type_* cur_node_ptr =  m_pcurrent_node;
			do 
			{
				next_node_ptr = cur_node_ptr->get_parent_node ();
				if (cur_node_ptr == m_root_node_ptr)
				{
					status			= PFX_STATUS_OK;
					next_type	= PREORDER_FIN;
					break;
				}
				else if (null == next_node_ptr)
				{
					status			= PFX_STATUS_OK;
					next_type	= PREORDER_FIN;
					break;
				}
				else if (next_node_ptr->get_right_node () == cur_node_ptr)
				{
					cur_node_ptr = next_node_ptr;
					continue;
				}
				else if (next_node_ptr->get_left_node () == cur_node_ptr)
				{
					if (null == next_node_ptr->get_right_node ())
					{
						cur_node_ptr = next_node_ptr;
						continue;
					}
					next_node_ptr	= next_node_ptr->get_right_node ();
					status					= PFX_STATUS_OK;

					if (null != next_node_ptr->get_left_node ())
					{
						next_type = PREORDER_NEXT_LEFT;
						break;
					}
					else if (null != next_node_ptr->get_right_node ())
					{
						next_type = PREORDER_NEXT_RIGHT;
						break;
					}
					else
					{
						next_type = PREORDER_NEXT_SUB_ROOT_RIGHT;
						break;
					}

				}
				else
				{
					status					= PFX_STATUS_MEM_ERR;
					next_type			= PREORDER_FIN;
					next_node_ptr	= null;
				}
			} while (1);
			m_pcurrent_node		= next_node_ptr;
			m_next_node_type	= next_type;
			m_last_result				= status;
		}
		break;
	case PREORDER_NEXT_LEFT:
		{
			next_node_ptr = m_current_node_ptr->get_left_node ();
			if (null == next_node_ptr)
			{
				status			= PFX_STATUS_MEM_ERR;
				next_type	= PREORDER_FIN;
			}
			else if (null != next_node_ptr->m_pleft_node)
			{
				next_type = PREORDER_NEXT_LEFT;
			}
			else if (null != next_node_ptr->m_pright_node)
			{
				next_type = PREORDER_NEXT_RIGHT;
			}
			else
			{
				next_type = PREORDER_NEXT_SUB_ROOT_RIGHT;
			}
			m_current_node_ptr	= next_node_ptr;
			m_next_node_type		= next_type;
			m_last_result					= status;
		}
		break;
	case PREORDER_NEXT_RIGHT:
		{
			next_node_ptr = m_current_node_ptr->get_right_node ();
			if (null == next_node_ptr)
			{
				status = PFX_STATUS_MEM_ERR;
				next_type = PREORDER_FIN;
			}
			else if (null != next_node_ptr->get_left_node ())
			{
				next_type = PREORDER_NEXT_LEFT;
			}
			else if (null != next_node_ptr->get_right_node ())
			{
				next_type = PREORDER_NEXT_RIGHT;
			}
			else
			{
				next_type = PREORDER_NEXT_SUB_ROOT_RIGHT;
			}
			m_current_node_ptr = next_node_ptr;
			m_next_node_type = next_type;
			m_last_result = PFX_STATUS_OK;
		}
		break;
	case PREORDER_NEXT_BEGIN:
		{
			//get_binary_search_tree_preorder_begin_iterator (proot_node,piterator);
			begin();
		}
		break;
	case PREORDER_NEXT_END:
		{
			m_current_node_ptr = null;
			m_next_node_type = PREORDER_FIN;
			m_last_result = PFX_STATUS_OK;
		}
		break;
	default:
		{
			m_current_node_ptr = null;
			m_next_node_type = PREORDER_FIN;
			m_last_result = PFX_STATUS_INVALID_OPERATION;
		}
		break;
	}

	return this;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::prev ()
{
	return null;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
const node_type_* pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_preorder_begin_node (const node_type_* root_node_ptr)
{
	return root_node_ptr;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
const node_type_* pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_preorder_end_node (const node_type_* root_node_ptr)
{
	const node_type_* temp_node_ptr;
	const node_type_* end_node_ptr;
	const node_type_* temp_rl_node_ptr;

	temp_node_ptr	= root_node_ptr;
	end_node_ptr	= null;

	while (temp_node_ptr)
	{
		end_node_ptr		= temp_node_ptr;
		temp_rl_node_ptr	= temp_node_ptr->get_right_node ();
		if (temp_rl_node_ptr)
		{
			temp_node_ptr = temp_rl_node_ptr;
			continue;
		}

		temp_rl_node_ptr = temp_node_ptr->get_left_node ();
		if (temp_rl_node_ptr)
		{
			temp_node_ptr = temp_rl_node_ptr;
			continue;
		}

		break;
	}

	return end_node_ptr;

}

// 搜索二叉树后序遍历
PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::begin () const
{
	const node_type_*	end_node_ptr;
	pfx_result_t				status_;

	m_last_result		= PFX_STATUS_OK;
	// 找出前序遍历最后一个值
	end_node_ptr	= pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_posorder_begin_node (root_node_ptr);
	status_				= pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (end_node_ptr,m_root_node_ptr);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status_),null);
	return this;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::end () const
{
	pfx_result_t status_;

	status_ =  pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (m_root_node_ptr,m_root_node_ptr);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,null);
	return this;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::next ()
{
	const node_type_* tmp_parent_node_ptr;
	const node_type_* tmp_r_node_ptr;
	const node_type_* tmp_l_node_ptr;
	const node_type_* temp_node_next_ptr;

	if (m_current_node_ptr == m_root_node_ptr)
	{
		return null;
	}

	tmp_parent_node_ptr = m_current_node_ptr->get_parent_node ();
	if (null == tmp_parent_node_ptr)
	{
		return null;
	}

	FOR_ONE_LOOP_BEGIN
	tmp_r_node_ptr = tmp_parent_node_ptr->get_right_node ();

	if (tmp_r_node_ptr == m_current_node_ptr)
	{
		temp_node_next_ptr = tmp_parent_node_ptr;
		break;
	}


	tmp_l_node_ptr = tmp_parent_node_ptr->get_left_node ();
	if (tmp_l_node_ptr == m_current_node_ptr)
	{		
		if (tmp_r_node_ptr)
		{
			temp_node_next_ptr = pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_posorder_begin_node (tmp_r_node_ptr);
		}
		else
		{
			temp_node_next_ptr	= tmp_parent_node_ptr;
		}
		break;
	}
	FOR_ONE_LOOP_END


	status_ =  pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (temp_node_next_ptr,m_root_node_ptr);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,null);

	return this;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::prev ()
{
	const node_type_* tmp_parent_node_ptr;
	const node_type_* tmp_l_node_ptr;
	const node_type_* tmp_r_node_ptr;
	const node_type_* temp_node_next_ptr;

	if (m_current_node_ptr == m_root_node_ptr)
	{
		return null;
	}

	tmp_parent_node_ptr = m_current_node_ptr->get_parent_node ();
	if (null == tmp_parent_node_ptr)
	{
		return null;
	}

	FOR_ONE_LOOP_BEGIN
		tmp_l_node_ptr = tmp_parent_node_ptr->get_left_node ();

	if (tmp_l_node_ptr == m_current_node_ptr)
	{
		temp_node_next_ptr = tmp_parent_node_ptr;
		break;
	}


	tmp_r_node_ptr = tmp_parent_node_ptr->get_right_node ();
	if (tmp_r_node_ptr == m_current_node_ptr)
	{		
		if (tmp_l_node_ptr)
		{
			temp_node_next_ptr = pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_reverse_posorder_begin_node (tmp_l_node_ptr);
		}
		else
		{
			temp_node_next_ptr	= tmp_parent_node_ptr;
		}
		break;
	}
	FOR_ONE_LOOP_END


	status_ =  pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS :: init (temp_node_next_ptr,m_root_node_ptr);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,null);

	return this;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
	const node_type_* pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_posorder_begin_node (const node_type_* root_node_ptr)
{
	const node_type_* begin_node_ptr;
	const node_type_* tmp_node_ptr;
	const node_type_* tmp_lr_node_ptr;

	tmp_node_ptr = root_node_ptr;

	while (tmp_node_ptr)
	{
		begin_node_ptr		= tmp_node_ptr;
		tmp_lr_node_ptr	= tmp_node_ptr->get_left_node ();

		if (tmp_lr_node_ptr)
		{
			tmp_node_ptr = tmp_lr_node_ptr;
			continue;
		}

		tmp_lr_node_ptr	= tmp_node_ptr->get_right_node ();

		if (tmp_lr_node_ptr)
		{
			tmp_node_ptr = tmp_lr_node_ptr;
			continue;
		}

		break;
	}
	return begin_node_ptr;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
	const node_type_* pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_posorder_end_node (const node_type_* root_node_ptr)
{
		return root_node_ptr;
}

PFX_CBST_ITERATOR_TEMPLATE_DEFINES
static const node_type_* pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS ::get_reverse_posorder_begin_node (const node_type_* root_node_ptr)
{
	const node_type_* begin_node_ptr;
	const node_type_* tmp_node_ptr;
	const node_type_* tmp_lr_node_ptr;

	begin_node_ptr = null;

	while (tmp_node_ptr)
	{
		begin_node_ptr = tmp_node_ptr;

		tmp_lr_node_ptr	= tmp_node_ptr->get_right_node ();

		if (tmp_lr_node_ptr)
		{
			tmp_node_ptr = tmp_lr_node_ptr;
			continue;
		}

		tmp_lr_node_ptr	= tmp_node_ptr->get_left_node ();

		if (tmp_lr_node_ptr)
		{
			tmp_node_ptr = tmp_lr_node_ptr;
			continue;
		}

		break;
	}
	return begin_node_ptr;

}

PECKER_END

#endif			//PFX_CBST_ITERATOR_CODES_H_