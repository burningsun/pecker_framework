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
#define PFX_CBST_ITR_OP_TEMPLATE_DEFINES  template < class node_type_ >

#define  PFX_CBST_IN_ITR_OP					const_bst_inoreder_operate< node_type_ >
#define  PFX_CBST_IN_ITR_OP_TYPE		typename const_bst_inoreder_operate< node_type_ >

#define  PFX_CBST_PRE_ITR_OP				const_bst_preorder_operate< node_type_ >
#define  PFX_CBST_PRE_ITR_OP_TYPE	typename const_bst_preorder_operate< node_type_ >

#define  PFX_CBST_POS_ITR_OP				const_bst_posorder_operate< node_type_ >
#define  PFX_CBST_POS_ITR_OP_TYPE	typename const_bst_posorder_operate< node_type_ >

// 搜索二叉树中序遍历
PFX_CBST_ITR_OP_TEMPLATE_DEFINES
const PFX_CBST_IN_ITR_OP_TYPE::node_t* PFX_CBST_IN_ITR_OP ::begin
	(const PFX_CBST_IN_ITR_OP_TYPE::node_t* root_node_ptr)
{
	typedef PFX_CBST_IN_ITR_OP_TYPE::node_t node_t;
	typedef typename BST_node_minmax< node_t > minmax_t;
	return minmax_t::min_node(root_node_ptr);
}

PFX_CBST_ITR_OP_TEMPLATE_DEFINES
const PFX_CBST_IN_ITR_OP_TYPE::node_t* PFX_CBST_IN_ITR_OP ::end
	(const PFX_CBST_IN_ITR_OP_TYPE::node_t* root_node_ptr)
{
	typedef PFX_CBST_IN_ITR_OP_TYPE::node_t node_t;
	typedef typename BST_node_minmax< node_t > minmax_t;
	return minmax_t::max_node(root_node_ptr);
}


PFX_CBST_ITR_OP_TEMPLATE_DEFINES
const PFX_CBST_IN_ITR_OP_TYPE::node_t* PFX_CBST_IN_ITR_OP::increase 
	(const PFX_CBST_IN_ITR_OP_TYPE::node_t* root_node_ptr, 
		const PFX_CBST_IN_ITR_OP_TYPE::node_t* current_node_ptr)
{
	typedef PFX_CBST_IN_ITR_OP_TYPE::node_t node_t;
	typedef typename BST_node_minmax< node_t > minmax_t;

	if (null == current_node_ptr || null == root_node_ptr)
	{
		return null;
	}

	const node_t* right_node_ptr;
	const node_t* parent_node_ptr;
	const node_t* return_node_ptr;

	FOR_ONE_LOOP_BEGIN
	right_node_ptr = current_node_ptr->get_right_node ();

	if (current_node_ptr == root_node_ptr)
	{
		BREAK_LOOP_CONDITION_SETS (!right_node_ptr, 
			return_node_ptr, null);

		BREAK_LOOP(return_node_ptr, minmax_t::min_node (right_node_ptr));
	}

	if (null != right_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, minmax_t::min_node (right_node_ptr));
	}

	parent_node_ptr = current_node_ptr->get_parent_node ();

	if (parent_node_ptr->get_left_node () == current_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, parent_node_ptr);
	}

	if (current_node_ptr == parent_node_ptr)
	{
		BREAK_LOOP(return_node_ptr, null);
	}

	current_node_ptr =  current_node_ptr->get_parent_node ();
	//return_node_ptr = current_node_ptr;
	while (1)
	{
		parent_node_ptr = current_node_ptr->get_parent_node ();
		if (null == parent_node_ptr)
		{
			return_node_ptr = null;
			break;
		}

		if (parent_node_ptr->get_right_node () == current_node_ptr)
		{
			current_node_ptr = current_node_ptr->get_parent_node ();
			continue;
		}

		if (parent_node_ptr->get_left_node () == current_node_ptr)
		{
			return_node_ptr = current_node_ptr->get_parent_node ();
			break;
		}

	}

	FOR_ONE_LOOP_END
	return return_node_ptr;
}

PFX_CBST_ITR_OP_TEMPLATE_DEFINES
const PFX_CBST_IN_ITR_OP_TYPE::node_t* PFX_CBST_IN_ITR_OP::decrease 
	(const PFX_CBST_IN_ITR_OP_TYPE::node_t* root_node_ptr, 
	const PFX_CBST_IN_ITR_OP_TYPE::node_t* current_node_ptr)
{
	typedef PFX_CBST_IN_ITR_OP_TYPE::node_t node_t;
	typedef typename BST_node_minmax< node_t > minmax_t;

	if (null == current_node_ptr || null == root_node_ptr)
	{
		return null;
	}

	const node_t* left_node_ptr;
	const node_t* parent_node_ptr;
	const node_t* return_node_ptr;

	FOR_ONE_LOOP_BEGIN
	left_node_ptr = current_node_ptr->get_left_node ();

	if (current_node_ptr == root_node_ptr)
	{
		BREAK_LOOP_CONDITION_SETS (!left_node_ptr,return_node_ptr,null);
		BREAK_LOOP(return_node_ptr, minmax_t::max_node(left_node_ptr));
	}

	if (null != left_node_ptr)
	{
		BREAK_LOOP (return_node_ptr, minmax_t::max_node(left_node_ptr));
	}

	parent_node_ptr = current_node_ptr->get_parent_node ();
	if (parent_node_ptr->get_right_node () == current_node_ptr)
	{
		BREAK_LOOP (return_node_ptr, parent_node_ptr);
	}

	if (current_node_ptr == parent_node_ptr)
	{
		BREAK_LOOP (return_node_ptr, null);
	}

	current_node_ptr =  parent_node_ptr;
	//iterator_return_ptr = this;
	while (1)
	{
		parent_node_ptr = current_node_ptr->get_parent_node ();
		if (null == parent_node_ptr)
		{
			return_node_ptr = null;
			break;
		}
		if (parent_node_ptr->get_left_node () == current_node_ptr)
		{
			current_node_ptr = parent_node_ptr;
			continue;
		}
		if (parent_node_ptr->get_right_node () == current_node_ptr)
		{
			return_node_ptr = parent_node_ptr;
			break;
		}

	}
	FOR_ONE_LOOP_END
	return return_node_ptr;
}

// 搜索二叉树前序遍历
PFX_CBST_ITR_OP_TEMPLATE_DEFINES
PFX_CBST_PRE_ITR_OP_TYPE::st_iterator_t* 
	PFX_CBST_PRE_ITR_OP ::begin(const PFX_CBST_PRE_ITR_OP_TYPE::node_t* root_node_ptr, 
	PFX_CBST_PRE_ITR_OP_TYPE::st_iterator_t& cur_itr)
{
	if (root_node_ptr)
	{
		cur_itr.m_root_node_ptr		= root_node_ptr;
		cur_itr.m_cur_node_ptr		= root_node_ptr;
		if (cur_itr.m_cur_node_ptr->get_left_node ())
		{
			cur_itr.m_next_node_type = PREORDER_NEXT_LEFT;
		}
		else if (cur_itr.m_cur_node_ptr->get_right_node ())
		{
			cur_itr.m_next_node_type = PREORDER_NEXT_RIGHT;
		}
		else
		{
			cur_itr.m_next_node_type = PREORDER_FIN;
		}
		cur_itr.m_last_result = PFX_STATUS_OK;
		return &cur_itr;
	}
	else
	{
		return null;
	}
	
}

PFX_CBST_ITR_OP_TEMPLATE_DEFINES
PFX_CBST_PRE_ITR_OP_TYPE::st_iterator_t* 
	PFX_CBST_PRE_ITR_OP ::end(const PFX_CBST_PRE_ITR_OP_TYPE::node_t* root_node_ptr, 
	PFX_CBST_PRE_ITR_OP_TYPE::st_iterator_t& cur_itr)
{
	typedef PFX_CBST_PRE_ITR_OP_TYPE::node_t node_t;
	if (root_node_ptr)
	{
		const node_t* temp_node_ptr;
		const node_t* end_node_ptr;
		const node_t* temp_rl_node_ptr;

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
		cur_itr.m_root_node_ptr		= root_node_ptr;
		cur_itr.m_cur_node_ptr		= end_node_ptr;

		cur_itr.m_next_node_type = PREORDER_FIN;
		cur_itr.m_last_result = PFX_STATUS_OK;
		return &cur_itr;
	}
	else
	{
		return null;
	}

}


PFX_CBST_ITR_OP_TEMPLATE_DEFINES
PFX_CBST_PRE_ITR_OP_TYPE::st_iterator_t* PFX_CBST_PRE_ITR_OP::increase 
	(PFX_CBST_PRE_ITR_OP_TYPE::st_iterator_t& cur_itr)
{
	typedef PFX_CBST_PRE_ITR_OP_TYPE::node_t				node_t;
	typedef PFX_CBST_PRE_ITR_OP_TYPE::st_iterator_t	st_iterator_t;

	enum_t				back_up_next_type;
	enum_t				next_type;
	const node_t*	next_node_ptr;
	result_t				status = PFX_STATUS_OK;
	st_iterator_t*	itr_retn_ptr = &cur_itr;

	RETURN_INVALID_RESULT ((null == cur_itr.m_root_node_ptr ||
		null == cur_itr.m_cur_node_ptr ||
		enum_preorder_iterator_next_node_type_COUNT <= cur_itr.m_next_node_type||
		PREORDER_FIN == cur_itr.m_next_node_type ||
		PFX_STATUS_OK != cur_itr.m_last_result),
		null);

	back_up_next_type = cur_itr.m_next_node_type;
	

	switch (back_up_next_type)
	{
	case PREORDER_NEXT_SUB_ROOT_RIGHT:
		{
			const node_t* cur_node_ptr =  cur_itr.m_cur_node_ptr;
			do 
			{
				next_node_ptr = cur_node_ptr->get_parent_node ();
				if (cur_node_ptr == cur_itr.m_root_node_ptr)
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
			if (next_node_ptr)
			{
				cur_itr.m_cur_node_ptr	= next_node_ptr;
			}
			else
			{
				itr_retn_ptr							= null;
			}
			cur_itr.m_next_node_type	= next_type;
			cur_itr.m_last_result				= status;
		}
		break;
	case PREORDER_NEXT_LEFT:
		{
			next_node_ptr = cur_itr.m_cur_node_ptr->get_left_node ();
			if (null == next_node_ptr)
			{
				status			= PFX_STATUS_MEM_ERR;
				next_type	= PREORDER_FIN;
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
			if (next_node_ptr)
			{
				cur_itr.m_cur_node_ptr		= next_node_ptr;
			}
			else
			{
				itr_retn_ptr = null;
			}
			
			cur_itr.m_next_node_type	= next_type;
			cur_itr.m_last_result				= status;
		}
		break;
	case PREORDER_NEXT_RIGHT:
		{
			next_node_ptr = cur_itr.m_cur_node_ptr->get_right_node ();
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
			if (next_node_ptr)
			{
				cur_itr.m_cur_node_ptr		= next_node_ptr;
				//itr_retn_ptr = null;
			}
			else
			{
				itr_retn_ptr = null;
			}
			cur_itr.m_next_node_type	= next_type;
			cur_itr.m_last_result				= status;
		}
		break;
	case PREORDER_NEXT_BEGIN:
		{
			itr_retn_ptr = begin(cur_itr.m_root_node_ptr, cur_itr);
		}
		break;
	case PREORDER_NEXT_END:
		{
			//cur_itr.m_cur_node_ptr		= null;
			cur_itr.m_next_node_type	= PREORDER_FIN;
			cur_itr.m_last_result				= PFX_STATUS_OK;
			itr_retn_ptr								= null;
		}
		break;
	default:
		{
			//cur_itr.m_cur_node_ptr		= null;
			cur_itr.m_next_node_type	= PREORDER_FIN;
			cur_itr.m_last_result				= PFX_STATUS_INVALID_OPERATION;
			itr_retn_ptr								= null;
		}
		break;
	}
	return itr_retn_ptr;
	
}


// 搜索二叉树后序遍历
PFX_CBST_ITR_OP_TEMPLATE_DEFINES
const PFX_CBST_POS_ITR_OP_TYPE::node_t* PFX_CBST_POS_ITR_OP::begin
(const PFX_CBST_POS_ITR_OP_TYPE::node_t* PARAM_IN root_node_ptr)
{
	typedef PFX_CBST_POS_ITR_OP_TYPE::node_t				node_t;

	const node_t* begin_node_ptr;
	const node_t* tmp_node_ptr;
	const node_t* tmp_lr_node_ptr;

	tmp_node_ptr = root_node_ptr;
	begin_node_ptr = null;
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

PFX_CBST_ITR_OP_TEMPLATE_DEFINES
const PFX_CBST_POS_ITR_OP_TYPE::node_t* PFX_CBST_POS_ITR_OP::reverse_begin
	(const PFX_CBST_POS_ITR_OP_TYPE::node_t* PARAM_IN root_node_ptr)
{
	typedef PFX_CBST_POS_ITR_OP_TYPE::node_t				node_t;

	const node_t* begin_node_ptr;
	const node_t* tmp_node_ptr;
	const node_t* tmp_lr_node_ptr;

	begin_node_ptr = null;
	tmp_node_ptr = root_node_ptr;
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

PFX_CBST_ITR_OP_TEMPLATE_DEFINES
const PFX_CBST_POS_ITR_OP_TYPE::node_t* PFX_CBST_POS_ITR_OP::end
	(const PFX_CBST_POS_ITR_OP_TYPE::node_t* PARAM_IN root_node_ptr)
{
	return root_node_ptr;
}

PFX_CBST_ITR_OP_TEMPLATE_DEFINES
const PFX_CBST_POS_ITR_OP_TYPE::node_t* PFX_CBST_POS_ITR_OP::increase 
(const node_t* PARAM_IN root_node_ptr, 
const node_t* current_node_ptr)
{
	typedef PFX_CBST_POS_ITR_OP_TYPE::node_t				node_t;

	//result_t status_;
	const node_t* tmp_parent_node_ptr;
	const node_t* tmp_r_node_ptr;
	const node_t* tmp_l_node_ptr;
	const node_t* temp_node_next_ptr;

	if (current_node_ptr == root_node_ptr)
	{
		return null;
	}

	tmp_parent_node_ptr = current_node_ptr->get_parent_node ();
	if (null == tmp_parent_node_ptr)
	{
		return null;
	}

	FOR_ONE_LOOP_BEGIN
	tmp_r_node_ptr = tmp_parent_node_ptr->get_right_node ();

	if (tmp_r_node_ptr == current_node_ptr)
	{
		temp_node_next_ptr = tmp_parent_node_ptr;
		break;
	}


	tmp_l_node_ptr = tmp_parent_node_ptr->get_left_node ();
	if (tmp_l_node_ptr == current_node_ptr)
	{		
		if (tmp_r_node_ptr)
		{
			temp_node_next_ptr = begin (tmp_r_node_ptr);
		}
		else
		{
			temp_node_next_ptr	= tmp_parent_node_ptr;
		}
		break;
	}
	FOR_ONE_LOOP_END

	return temp_node_next_ptr;
}

PFX_CBST_ITR_OP_TEMPLATE_DEFINES
	const PFX_CBST_POS_ITR_OP_TYPE::node_t* PFX_CBST_POS_ITR_OP::reverse_increase 
	(const node_t* PARAM_IN root_node_ptr, 
	const node_t* current_node_ptr)
{
	typedef PFX_CBST_POS_ITR_OP_TYPE::node_t				node_t;

	//result_t status_;
	const node_t* tmp_parent_node_ptr;
	const node_t* tmp_l_node_ptr;
	const node_t* tmp_r_node_ptr;
	const node_t* temp_node_next_ptr;

	if (current_node_ptr == root_node_ptr)
	{
		return null;
	}

	tmp_parent_node_ptr = current_node_ptr->get_parent_node ();
	if (null == tmp_parent_node_ptr)
	{
		return null;
	}

	FOR_ONE_LOOP_BEGIN
		tmp_l_node_ptr = tmp_parent_node_ptr->get_left_node ();

	if (tmp_l_node_ptr == current_node_ptr)
	{
		temp_node_next_ptr = tmp_parent_node_ptr;
		break;
	}


	tmp_r_node_ptr = tmp_parent_node_ptr->get_right_node ();
	if (tmp_r_node_ptr == current_node_ptr)
	{		
		if (tmp_l_node_ptr)
		{
			temp_node_next_ptr = reverse_begin (tmp_l_node_ptr);
		}
		else
		{
			temp_node_next_ptr	= tmp_parent_node_ptr;
		}
		break;
	}
	FOR_ONE_LOOP_END

	return temp_node_next_ptr;
}


PECKER_END

#endif			//PFX_CBST_ITERATOR_CODES_H_
