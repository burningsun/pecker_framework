﻿/*
 * cbst.h
 *
 *  Created on: 2013-12-16
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBST_CODES_H_
#define		PFX_CBST_CODES_H_

#include "pfx_cbst.h"
#include "pfx_cbst_iterator_codes.h"
PECKER_BEGIN

#define PFX_CBST_MINMAX_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_CBST_MINMAX				BST_node_minmax< node_type_ >
#define PFX_CBST_MINMAX_TYPE	typename BST_node_minmax< node_type_ >

#define PFX_CBST_INIT_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_CBST_INIT						BST_node_init< node_type_	>
#define PFX_CBST_INIT_TYPE			typename BST_node_init< node_type_	>

#define PFX_AVL_BST_INIT_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_AVL_BST_INIT				AVL_BST_node_init< node_type_	>
#define PFX_AVL_BST_INIT_TYPE		typename AVL_BST_node_init< node_type_	>

#define PFX_RB_BST_INIT_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_RB_BST_INIT					RB_BST_node_init< node_type_	>
#define PFX_RB_BST_INIT_TYPE		typename RB_BST_node_init< node_type_	>

#define PFX_CBST_RM_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_CBST_RM						BST_node_remove< node_type_	>
#define PFX_CBST_RM_TYPE				typename BST_node_remove< node_type_ >

#define PFX_AVL_BST_RM_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_AVL_BST_RM					AVL_BST_node_remove< node_type_	>
#define PFX_AVL_BST_RM_TYPE		typename AVL_BST_node_remove< node_type_	>

#define PFX_RB_BST_RM_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_RB_BST_RM					RB_BST_node_remove< node_type_	>
#define PFX_RB_BST_RM_TYPE		typename RB_BST_node_remove< node_type_	>

#define PFX_CBST_NFIND_TEMPLATE_DEFINES template < class node_type_, class compare_two_node_ >
#define PFX_CBST_NFIND					BST_find_node< node_type_, compare_two_node_ >
#define PFX_CBST_NFIND_TYPE		typename BST_find_node< node_type_, compare_two_node_ >

#define PFX_CBST_ITR_FIND_TEMPLATE_DEFINES template < class tree_type >
#define PFX_CBST_ITR_FIND					BST_find_iterator< tree_type >
#define PFX_CBST_ITR_FIND_TYPE		typename BST_find_iterator< tree_type >

#define PFX_CBST_ELEM_FIND_TEMPLATE_DEFINES template < class tree_type >
#define PFX_CBST_ELEM_FIND					BST_find_element< tree_type >
#define PFX_CBST_ELEM_FIND_TYPE		typename BST_find_element< tree_type >

#define PFX_CBST_ELEM_FIND_NODE_TEMPLATE_DEFINES template < class node_type_, class key_element, class key_cmp_node_t>
#define PFX_CBST_ELEM_FIND_NODE             BST_find_element_node< node_type_, key_element, key_cmp_node_t >
#define PFX_CBST_ELEM_FIND_NODE_TYPE typename BST_find_element_node< node_type_, key_element, key_cmp_node_t >

#define PFX_CBST_ELEM_FINDX_TEMPLATE_DEFINES template < class tree_type, class key_element, class key_cmp_node_t>
#define PFX_CBST_ELEM_FINDX					BST_find_elementx< tree_type, key_element, key_cmp_node_t >
#define PFX_CBST_ELEM_FINDX_TYPE		typename BST_find_elementx< tree_type, key_element, key_cmp_node_t > 

#define PFX_CBST_STR_FIND_NODE_TEMPLATE_DEFINES template < class node_type_, class string_type, class string_cmp_node_t >
#define PFX_CBST_STR_FIND_NODE	            BST_find_string_node < node_type_, string_type, string_cmp_node_t >
#define PFX_CBST_STR_FIND_NODE_TYPE		typename BST_find_string_node < node_type_, string_type, string_cmp_node_t >

#define PFX_CBST_INSERT_TEMPLATE_DEFINES template < class node_type_, class compare_two_node_ >
#define PFX_CBST_INSERT							BST_insert_node< node_type_, compare_two_node_ >
#define PFX_CBST_INSERT_TYPE				typename BST_insert_node< node_type_, compare_two_node_ >

#define PFX_AVL_BST_INSERT_TEMPLATE_DEFINES template < class node_type_, class compare_two_node_ >
#define PFX_AVL_BST_INSERT					AVL_BST_insert_node< node_type_, compare_two_node_ >
#define PFX_AVL_BST_INSERT_TYPE		typename AVL_BST_insert_node< node_type_, compare_two_node_ >

#define PFX_RB_BST_INSERT_TEMPLATE_DEFINES template < class node_type_, class compare_two_node_ >
#define PFX_RB_BST_INSERT					RB_BST_insert_node< node_type_, compare_two_node_ >
#define PFX_RB_BST_INSERT_TYPE			typename RB_BST_insert_node< node_type_, compare_two_node_ >

#define PFX_CBST_CLEAN_TEMPLATE_DEFINES template < class node_alloc >
#define PFX_CBST_CLEAN							BST_clean< node_alloc >
#define PFX_CBST_CLEAN_TYPE				typename BST_clean< node_alloc >

#define PFX_CBST_CLONE_TEMPLATE_DEFINES template < class node_alloc, class node_init >
#define PFX_CBST_CLONE							XBST_clone< node_alloc, node_init >
#define PFX_CBST_CLONE_TYPE				typename XBST_clone< node_alloc, node_init >

#define PFX_CBST_COPY_TEMPLATE_DEFINES template < class node_alloc, class node_insert >
#define PFX_CBST_COPY							XBST_copy< node_alloc, node_insert >
#define PFX_CBST_COPY_TYPE				typename XBST_copy< node_alloc, node_insert >

//最大最小值
PFX_CBST_MINMAX_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_MINMAX_TYPE::node_t* PFX_CBST_MINMAX ::max_node
(const PFX_CBST_MINMAX_TYPE::node_t* root_node_ptr,
		const PFX_CBST_MINMAX_TYPE::node_t* null_node_ptr /*= null*/)
{
	typedef PFX_CBST_MINMAX_TYPE::node_t node_t;

	if (root_node_ptr)
	{
		const node_t* right_node_ptr = root_node_ptr->get_right_node();
		if (!null_node_ptr)
		{
			while (right_node_ptr)
			{
				root_node_ptr = right_node_ptr;
				right_node_ptr = root_node_ptr->get_right_node();
			}
		}
		else
		{
			while (right_node_ptr && null_node_ptr != right_node_ptr)
			{
				root_node_ptr = right_node_ptr;
				right_node_ptr = root_node_ptr->get_right_node();
			}
		}
	}
	return root_node_ptr;
}

PFX_CBST_MINMAX_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_MINMAX_TYPE::node_t* PFX_CBST_MINMAX ::min_node
(const PFX_CBST_MINMAX_TYPE::node_t* root_node_ptr,
		const PFX_CBST_MINMAX_TYPE::node_t* null_node_ptr /*= null*/)
{
	typedef PFX_CBST_MINMAX_TYPE::node_t node_t;

	if (root_node_ptr)
	{
		const node_t* left_node_ptr = root_node_ptr->get_left_node();
		if (!null_node_ptr)
		{
			while (left_node_ptr)
			{
				root_node_ptr = left_node_ptr;
				left_node_ptr = root_node_ptr->get_left_node();
			}
		}
		else
		{
			while (left_node_ptr && null_node_ptr != left_node_ptr)
			{
				root_node_ptr = left_node_ptr;
				left_node_ptr = root_node_ptr->get_left_node();
			}
		}
	}
	return root_node_ptr;
}

PFX_CBST_MINMAX_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_MINMAX_TYPE::node_t* PFX_CBST_MINMAX ::max_node
(PFX_CBST_MINMAX_TYPE::node_t* root_node_ptr,
		const PFX_CBST_MINMAX_TYPE::node_t* null_node_ptr /*= null*/)
{
	typedef PFX_CBST_MINMAX_TYPE::node_t node_t;
	return (node_t*)max_node((node_t*)root_node_ptr, null_node_ptr);
}

PFX_CBST_MINMAX_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_MINMAX_TYPE::node_t* PFX_CBST_MINMAX ::min_node
(PFX_CBST_MINMAX_TYPE::node_t* root_node_ptr,
		const PFX_CBST_MINMAX_TYPE::node_t* null_node_ptr /*= null*/)
{
	typedef PFX_CBST_MINMAX_TYPE::node_t node_t;
	return (node_t*)min_node((node_t*)root_node_ptr, null_node_ptr);
}

// 初始化
PFX_CBST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBST_INIT::init_node_leaves (
		PFX_CBST_INIT_TYPE::node_t* PARAM_INOUT tree_node_ptr,
		PFX_CBST_INIT_TYPE::node_t* PARAM_IN left_node_ptr /*= null*/,
		PFX_CBST_INIT_TYPE::node_t* PARAM_IN right_node_ptr /*= null*/,
		PFX_CBST_INIT_TYPE::node_t* PARAM_IN parent_node_ptr /*= null*/)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_left_node (left_node_ptr);
		tree_node_ptr->set_right_node (right_node_ptr);
		tree_node_ptr->set_parent_node (parent_node_ptr);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_CBST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBST_INIT::init_node_leaves (
		PFX_CBST_INIT_TYPE::node_t& PARAM_INOUT tree_node,
		PFX_CBST_INIT_TYPE::node_t* PARAM_IN left_node_ptr /*= null*/,
		PFX_CBST_INIT_TYPE::node_t* PARAM_IN right_node_ptr /*= null*/,
		PFX_CBST_INIT_TYPE::node_t* PARAM_IN parent_node_ptr /*= null*/)
{
	tree_node.set_left_node (left_node_ptr);
	tree_node.set_right_node (right_node_ptr);
	tree_node.set_parent_node (parent_node_ptr);
	return PFX_STATUS_OK;
}
// AVL树基本初始化
PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_AVL_BST_INIT::init_node_leaves
(PFX_AVL_BST_INIT_TYPE::node_t* PARAM_INOUT tree_node_ptr,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN left_node_ptr /*= null*/,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN right_node_ptr /*= null*/,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN parent_node_ptr/* = null*/)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_left_node (left_node_ptr);
		tree_node_ptr->set_right_node (right_node_ptr);
		tree_node_ptr->set_parent_node (parent_node_ptr);
		tree_node_ptr->set_height (0);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_AVL_BST_INIT::init_node_leaves
(PFX_AVL_BST_INIT_TYPE::node_t& PARAM_INOUT tree_node,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN left_node_ptr /*= null*/,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN right_node_ptr /*= null*/,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN parent_node_ptr/* = null*/)
{
	tree_node.set_left_node (left_node_ptr);
	tree_node.set_right_node (right_node_ptr);
	tree_node.set_parent_node (parent_node_ptr);
	tree_node.set_height (0);
	return PFX_STATUS_OK;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE nsize__t PFX_AVL_BST_INIT ::get_avl_height
(const PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN node_ptr)
{
	nsize__t height_value = -1;
	if (node_ptr)
	{
		height_value = node_ptr->get_height ();
	}
	return height_value;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE nsize__t PFX_AVL_BST_INIT ::calculate_avl_height
(const PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN left_node_ptr,
		const PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN right_node_ptr)
{
	nsize__t left_height = get_avl_height (left_node_ptr);
	nsize__t right_height = get_avl_height (right_node_ptr);
	if (left_height > right_height)
	{
		return (left_height+1);
	}
	else
	{
		return (right_height+1);
	}
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE nsize__t PFX_AVL_BST_INIT ::calculate_avl_height
(const PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN node_ptr)
{
	nsize__t height_value = -1;
	if (node_ptr)
	{
		height_value = calculate_avl_height
		(node_ptr->get_left_node(),node_ptr->get_right_node ());
	}
	return height_value;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE nsize__t PFX_AVL_BST_INIT ::calculate_avl_balance_value
(const PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN node_ptr)
{
	nsize__t balance_value = 0;
	if (node_ptr)
	{
		balance_value = get_avl_height
		(node_ptr->get_left_node ()) - get_avl_height (node_ptr->get_right_node ());
	}
	return balance_value;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE void PFX_AVL_BST_INIT ::update_avl_height
(PFX_AVL_BST_INIT_TYPE::node_t* PARAM_IN node_ptr)
{
	nsize__t height_value = calculate_avl_height (node_ptr);
	node_ptr->set_height (height_value);
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE PFX_AVL_BST_INIT_TYPE::node_t* PFX_AVL_BST_INIT ::avl_rr_rotate
(PFX_AVL_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	typedef PFX_AVL_BST_INIT_TYPE::node_t node_t;
	node_t* rotate_node_ptr = node_ptr->get_right_node_ref ();

	node_ptr->set_right_node (rotate_node_ptr->get_left_node_ref ());
	rotate_node_ptr->set_left_node (node_ptr);

	node_t* tmp_right_node_ptr = node_ptr->get_right_node_ref ();
	if (tmp_right_node_ptr)
	{
		tmp_right_node_ptr->set_parent_node (node_ptr);
	}
	rotate_node_ptr->set_parent_node (node_ptr->get_parent_node_ref ());
	node_ptr->set_parent_node (rotate_node_ptr);

	update_avl_height (node_ptr);
	update_avl_height (rotate_node_ptr);

	return rotate_node_ptr;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE PFX_AVL_BST_INIT_TYPE::node_t* PFX_AVL_BST_INIT ::avl_ll_rotate
(PFX_AVL_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	typedef PFX_AVL_BST_INIT_TYPE::node_t node_t;
	node_t* rotate_node_ptr = node_ptr->get_left_node_ref ();

	node_ptr->set_left_node (rotate_node_ptr->get_right_node_ref ());
	rotate_node_ptr->set_right_node (node_ptr);

	node_t* tmp_left_node_ptr = node_ptr->get_left_node_ref ();
	if (tmp_left_node_ptr)
	{
		tmp_left_node_ptr->set_parent_node (node_ptr);
	}
	rotate_node_ptr->set_parent_node (node_ptr->get_parent_node_ref ());
	node_ptr->set_parent_node (rotate_node_ptr);

	update_avl_height (node_ptr);
	update_avl_height (rotate_node_ptr);

	return rotate_node_ptr;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE PFX_AVL_BST_INIT_TYPE::node_t* PFX_AVL_BST_INIT ::avl_lr_rotate
(PFX_AVL_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	// LR = RR(node_ptr->letf) + LL(node_ptr)
	typedef PFX_AVL_BST_INIT_TYPE::node_t node_t;
	node_t* tmp_node_ptr = avl_rr_rotate (node_ptr->get_left_node_ref ());
	node_ptr->set_left_node (tmp_node_ptr);
	return avl_ll_rotate (node_ptr);
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE PFX_AVL_BST_INIT_TYPE::node_t* PFX_AVL_BST_INIT ::avl_rl_rotate
(PFX_AVL_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	// RL = LL(node_ptr->right)) + RR(node_ptr)
	typedef PFX_AVL_BST_INIT_TYPE::node_t node_t;
	node_t* tmp_node_ptr = avl_ll_rotate (node_ptr->get_right_node_ref ());
	node_ptr->set_right_node (tmp_node_ptr);
	return avl_rr_rotate (node_ptr);
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE AVLTREE_ROTATE_t PFX_AVL_BST_INIT ::avl_single_rotate
(nsize__t balance_value,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr,
		PFX_AVL_BST_INIT_TYPE::node_t* & PARAM_INOUT parent_ref_node_ptr)
{
	typedef PFX_AVL_BST_INIT_TYPE::node_t node_t;

	AVLTREE_ROTATE_t rotate_type = AVLTREE_NOT_SIMPLE_ROTATE;

	FOR_ONE_LOOP_BEGIN

	if (-2 < balance_value && balance_value < 2)
	{
		BREAK_LOOP (rotate_type,AVLTREE_NONE_ROTATE);
	}

	if (2 == balance_value)
	{
		node_t * left_node_ptr = node_ptr->get_left_node_ref ();

		if (null == left_node_ptr)
		{
			BREAK_LOOP (rotate_type,AVLTREE_ROTATE_ERR);
		}
		else if (get_avl_height (left_node_ptr->get_left_node ()) >=
				get_avl_height (left_node_ptr->get_right_node ()))
		{
			parent_ref_node_ptr = avl_ll_rotate (node_ptr);
			BREAK_LOOP (rotate_type,AVLTREE_LL_ROTATE);
		}
		else
		{
			parent_ref_node_ptr = avl_lr_rotate (node_ptr);
			BREAK_LOOP (rotate_type,AVLTREE_LR_ROTATE);
		}
	}

	if(-2 == balance_value)
	{
		node_t * right_node_ptr = node_ptr->get_right_node_ref ();
		if (null == right_node_ptr)
		{
			BREAK_LOOP (rotate_type,AVLTREE_ROTATE_ERR);
		}

		if ( get_avl_height (right_node_ptr->get_right_node ()) >=
				get_avl_height (right_node_ptr->get_left_node ()))
		{
			parent_ref_node_ptr = avl_rr_rotate (node_ptr);
			BREAK_LOOP (rotate_type,AVLTREE_RR_ROTATE);
		}
		else
		{
			parent_ref_node_ptr = avl_rl_rotate (node_ptr);
			BREAK_LOOP (rotate_type,AVLTREE_RL_ROTATE);
		}
	}

	FOR_ONE_LOOP_END
	return rotate_type;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_AVL_BST_INIT ::avl_update_insert_rotate
(PFX_AVL_BST_INIT_TYPE::node_t* & PARAM_INOUT root_node_ptr,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_INOUT begin_node_ptr)
{
	typedef PFX_AVL_BST_INIT_TYPE::node_t node_t;

	result_t status = PFX_STATUS_OK;
	nsize__t height;
	node_t* tmp_root_node_ptr;
	const node_t* tmp_root_parent_node_ptr;
	node_t* parent_node_ptr;
	AVLTREE_ROTATE_t rotate_type;

	tmp_root_node_ptr = root_node_ptr;
	tmp_root_parent_node_ptr = root_node_ptr->get_parent_node ();

	// 当起始节点为根节点的处理流程
	if (tmp_root_node_ptr == begin_node_ptr)
	{
		update_avl_height (begin_node_ptr);

		rotate_type = avl_single_rotate
		(calculate_avl_balance_value (tmp_root_node_ptr), tmp_root_node_ptr, root_node_ptr);

		if (AVLTREE_ROTATE_ERR == rotate_type ||
				AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			status = PFX_STATUS_ERROR_;
		}
		else
		{
			status = PFX_STATUS_OK;
		}
		return status;
	}

	nsize__t balance_value;
	node_t* parent_parent_node_ptr;

	update_avl_height (begin_node_ptr);

	nsize__t same_count = 0;
	// 从第一个节点的跟节点开始翻转
	do
	{
		parent_node_ptr = begin_node_ptr->get_parent_node_ref ();

		//一般情况下必须达成 null == parent_node的条件，即轮寻翻转到跟节点的时候
		//才退出翻转处理流程
		if (tmp_root_parent_node_ptr == parent_node_ptr)
		{
			BREAK_LOOP (status,PFX_STATUS_OK);
		}

		// 节点与他的父节点的指针一样，证明内存已经出错
		if (begin_node_ptr == parent_node_ptr)
		{
			BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
		}

		height = parent_node_ptr->get_height ();
		update_avl_height (parent_node_ptr);
		balance_value = calculate_avl_balance_value (parent_node_ptr);

		if (height == parent_node_ptr->get_height ())
		{
			BREAK_LOOP (status,PFX_STATUS_OK);
		}

		parent_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();
		begin_node_ptr = parent_node_ptr;

		node_t** reference_node_ptr_ptr = null;
		// 注：这利用相关节点的关联引用进行操作，在翻转过程中快速替换被关联节点对应的节点指针
		if (parent_node_ptr == tmp_root_node_ptr || tmp_root_parent_node_ptr == parent_parent_node_ptr)
		{
			rotate_type = avl_single_rotate
			(balance_value, parent_node_ptr, root_node_ptr);
		}
		else
		{
			if (parent_parent_node_ptr->get_left_node () == parent_node_ptr)
			{
				reference_node_ptr_ptr = (node_t**)(&parent_parent_node_ptr->get_left_node_ref ());
				rotate_type = avl_single_rotate
				(balance_value, parent_node_ptr, *reference_node_ptr_ptr);

			}
			else if (parent_parent_node_ptr->get_right_node () == parent_node_ptr)
			{
				reference_node_ptr_ptr = (node_t**)(&parent_parent_node_ptr->get_right_node_ref ());
				rotate_type = avl_single_rotate
				(balance_value, parent_node_ptr, *reference_node_ptr_ptr);
			}
			else
			{
				BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
			}
		}

		if (AVLTREE_ROTATE_ERR == rotate_type ||
				AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			// 翻转出错，退出流程
			BREAK_LOOP (status,PFX_STATUS_ERROR_);
		}
		else
		{
			status = PFX_STATUS_OK;
		}

	}while (1);
	return status;
}

PFX_AVL_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_AVL_BST_INIT ::avl_update_fixed
(PFX_AVL_BST_INIT_TYPE::node_t* & PARAM_INOUT root_node_ptr,
		PFX_AVL_BST_INIT_TYPE::node_t* PARAM_INOUT begin_node_ptr)
{
	typedef PFX_AVL_BST_INIT_TYPE::node_t node_t;

	result_t status = PFX_STATUS_OK;
	nsize__t height;
	node_t* tmp_root_node_ptr;
	const node_t* tmp_root_parent_node_ptr;
	node_t* parent_node_ptr;
	AVLTREE_ROTATE_t rotate_type;

	tmp_root_node_ptr = root_node_ptr;
	tmp_root_parent_node_ptr = root_node_ptr->get_parent_node ();

	// 当起始节点为根节点的处理流程
	if (tmp_root_node_ptr == begin_node_ptr)
	{
		update_avl_height (begin_node_ptr);

		rotate_type = avl_single_rotate
		(calculate_avl_balance_value (tmp_root_node_ptr), tmp_root_node_ptr, root_node_ptr);

		if (AVLTREE_ROTATE_ERR == rotate_type ||
				AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			status = PFX_STATUS_ERROR_;
		}
		else
		{
			status = PFX_STATUS_OK;
		}
		return status;
	}

	nsize__t balance_value;
	node_t* parent_parent_node_ptr;

	balance_value = calculate_avl_balance_value (begin_node_ptr);

	FOR_ONE_LOOP_BEGIN

	if (2 == balance_value)
	{
		begin_node_ptr = begin_node_ptr->get_left_node_ref ();
	}
	else if (-2 == balance_value)
	{
		begin_node_ptr = begin_node_ptr->get_right_node_ref ();
	}

	update_avl_height (begin_node_ptr);

	nsize__t same_count = 0;
	// 从第一个节点的跟节点开始翻转
	do
	{
		parent_node_ptr = begin_node_ptr->get_parent_node_ref ();

		//一般情况下必须达成 null == parent_node的条件，即轮寻翻转到跟节点的时候
		//才退出翻转处理流程
		if (tmp_root_parent_node_ptr == parent_node_ptr)
		{
			BREAK_LOOP (status,PFX_STATUS_OK);
		}

		// 节点与他的父节点的指针一样，证明内存已经出错
		if (begin_node_ptr == parent_node_ptr)
		{
			BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
		}

		height = parent_node_ptr->get_height ();
		update_avl_height (parent_node_ptr);
		balance_value = calculate_avl_balance_value (parent_node_ptr);

		// 高度一样，平衡，连续出现2次，则退出
		if (height == parent_node_ptr->get_height () && balance_value > -2 && balance_value <2)
		{
			++same_count;
			if (same_count > 1)
			{
				BREAK_LOOP (status,PFX_STATUS_OK);
			}
		}
		else
		{
			same_count = 0;
		}

		parent_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();
		begin_node_ptr = parent_node_ptr;

		node_t** reference_node_ptr_ptr = null;
		// 注：这利用相关节点的关联引用进行操作，在翻转过程中快速替换被关联节点对应的节点指针
		if (parent_node_ptr == tmp_root_node_ptr || tmp_root_parent_node_ptr == parent_parent_node_ptr)
		{
			rotate_type = avl_single_rotate
			(balance_value, parent_node_ptr, root_node_ptr);
		}
		else
		{
			if (parent_parent_node_ptr->get_left_node () == parent_node_ptr)
			{
				reference_node_ptr_ptr = (node_t**)(&parent_parent_node_ptr->get_left_node_ref ());
				rotate_type = avl_single_rotate
				(balance_value, parent_node_ptr, *reference_node_ptr_ptr);

			}
			else if (parent_parent_node_ptr->get_right_node () == parent_node_ptr)
			{
				reference_node_ptr_ptr = (node_t**)(&parent_parent_node_ptr->get_right_node_ref ());
				rotate_type = avl_single_rotate
				(balance_value, parent_node_ptr, *reference_node_ptr_ptr);
			}
			else
			{
				BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
			}
		}

		if (AVLTREE_ROTATE_ERR == rotate_type ||
				AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			// 翻转出错，退出流程
			BREAK_LOOP (status,PFX_STATUS_ERROR_);
		}
		else
		{
			status = PFX_STATUS_OK;
		}

	}while (1);

	FOR_ONE_LOOP_END

	return status;
}

//黑红树基本初始化
PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_RB_BST_INIT ::init_node_leaves
(PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT tree_node_ptr,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_IN left_node_ptr /*= null*/,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_IN right_node_ptr /*= null*/,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_IN parent_node_ptr /*= null*/)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_left_node (left_node_ptr);
		tree_node_ptr->set_right_node (right_node_ptr);
		tree_node_ptr->set_parent_node (parent_node_ptr);
		tree_node_ptr->set_color (BLACK_COLOR_NODE_TYPE);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_RB_BST_INIT ::init_node_leaves
(PFX_RB_BST_INIT_TYPE::node_t& PARAM_INOUT tree_node,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_IN left_node_ptr /*= null*/,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_IN right_node_ptr /*= null*/,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_IN parent_node_ptr /*= null*/)
{
	tree_node.set_left_node (left_node_ptr);
	tree_node.set_right_node (right_node_ptr);
	tree_node.set_parent_node (parent_node_ptr);
	tree_node.set_color (BLACK_COLOR_NODE_TYPE);
	return PFX_STATUS_OK;
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE void PFX_RB_BST_INIT ::set_rbt_color_red
(PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	node_ptr->set_color (RED_COLOR_NODE_TYPE);
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE void PFX_RB_BST_INIT ::set_rbt_color_black
(PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	node_ptr->set_color (BLACK_COLOR_NODE_TYPE);
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE bool PFX_RB_BST_INIT ::is_rbt_color_red
(PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	return (node_ptr && RED_COLOR_NODE_TYPE == node_ptr->get_color ());
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE bool PFX_RB_BST_INIT ::is_rbt_color_black
(PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	return (!node_ptr || BLACK_COLOR_NODE_TYPE == node_ptr->get_color ());
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE void PFX_RB_BST_INIT ::copy_tree_color
(PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT dec_node_ptr,
		const PFX_RB_BST_INIT_TYPE::node_t* PARAM_IN src_node_ptr)
{
	dec_node_ptr->set_color (src_node_ptr->get_color());
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE void PFX_RB_BST_INIT ::rbt_left_rotate
(PFX_RB_BST_INIT_TYPE::node_t *& PARAM_INOUT root_node_ptr,
		PFX_RB_BST_INIT_TYPE::node_t * PARAM_INOUT sentinel_node_ptr,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT node_ptr)
{
	typedef PFX_RB_BST_INIT_TYPE::node_t node_t;
	node_t* temp_node_ptr;
	node_t* tmp_letf_node_ptr;

	temp_node_ptr = node_ptr->get_right_node_ref ();
	node_ptr->set_right_node (temp_node_ptr->get_left_node_ref ());

	tmp_letf_node_ptr = temp_node_ptr->get_left_node_ref ();
	if (tmp_letf_node_ptr != sentinel_node_ptr)
	{
		tmp_letf_node_ptr->set_parent_node (node_ptr);
	}

	temp_node_ptr->set_parent_node (node_ptr->get_parent_node_ref ());

	if (node_ptr == root_node_ptr)
	{
		root_node_ptr = temp_node_ptr;
	}
	else
	{
		node_t* tmp_parent_node_ptr = node_ptr->get_parent_node_ref ();
		if (node_ptr == tmp_parent_node_ptr->get_left_node ())
		{
			tmp_parent_node_ptr->set_left_node (temp_node_ptr);
		}
		else
		{
			tmp_parent_node_ptr->set_right_node (temp_node_ptr);
		}
	}

	temp_node_ptr->set_left_node (node_ptr);
	node_ptr->set_parent_node (temp_node_ptr);
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE void PFX_RB_BST_INIT ::rbt_right_rotate
(PFX_RB_BST_INIT_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_RB_BST_INIT_TYPE::node_t * PARAM_INOUT sentinel_node_ptr,
		PFX_RB_BST_INIT_TYPE::node_t * PARAM_INOUT node_ptr)
{
	typedef PFX_RB_BST_INIT_TYPE::node_t node_t;
	node_t* temp_node_ptr;
	node_t* temp_right_node_ptr;

	temp_node_ptr = node_ptr->get_left_node_ref ();
	node_ptr->set_left_node (temp_node_ptr->get_right_node_ref ());

	temp_right_node_ptr = temp_node_ptr->get_right_node_ref ();

	if (temp_right_node_ptr != sentinel_node_ptr)
	{
		temp_right_node_ptr->set_parent_node (node_ptr);
	}

	temp_node_ptr->set_parent_node (node_ptr->get_parent_node_ref ());

	if (node_ptr == root_node_ptr)
	{
		root_node_ptr = temp_node_ptr;
	}
	else
	{
		node_t* tmp_parent_node_ptr = node_ptr->get_parent_node_ref ();
		if (tmp_parent_node_ptr->get_right_node () == node_ptr)
		{
			tmp_parent_node_ptr->set_right_node (temp_node_ptr);
		}
		else
		{
			tmp_parent_node_ptr->set_left_node (temp_node_ptr);
		}
	}

	temp_node_ptr->set_right_node (node_ptr);
	node_ptr->set_parent_node (temp_node_ptr);
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_RB_BST_INIT :: rbt_add_rotate_fixup
(PFX_RB_BST_INIT_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT add_node_ptr)
{
	typedef PFX_RB_BST_INIT_TYPE::node_t node_t;
	node_t* temp_node_ptr;
	bool is_red_node = false;

	// 根节点的颜色一定是黑的
	if (add_node_ptr == root_node_ptr)
	{
		set_rbt_color_black (add_node_ptr);
		return PFX_STATUS_OK;
	}

	while (add_node_ptr != root_node_ptr)
	{
		is_red_node = is_rbt_color_red
		(add_node_ptr->get_parent_node_ref ());

		if (!is_red_node)
		{
			break;
		}
		// 新添加的父节点为红色

		node_t* parent_node_ptr = add_node_ptr->get_parent_node_ref ();
		node_t* grand_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();

		RETURN_INVALID_RESULT (null == grand_parent_node_ptr,PFX_STATUS_MEM_ERR);

		// 当爷爷的左孩子节点为父节点的时候
		if (grand_parent_node_ptr->get_left_node () == parent_node_ptr)
		{
			temp_node_ptr = grand_parent_node_ptr->get_right_node_ref ();
			is_red_node = is_rbt_color_red (temp_node_ptr);

			//RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp),PFX_STATUS_MEM_ERR);
			if (is_red_node)
			{
				// 叔叔节点红色
				// 将叔叔节点变黑
				// 父节点变黑，（解决新增节点与父节点都是红色的问题）
				// 将爷爷节点变红，当作新增节点，指针上移两代
				set_rbt_color_black (parent_node_ptr);
				set_rbt_color_black (temp_node_ptr);
				set_rbt_color_red (grand_parent_node_ptr);
				add_node_ptr = grand_parent_node_ptr;
			}
			else
			{
				// 叔叔节点黑色
				if (parent_node_ptr->get_right_node () == add_node_ptr)
				{
					// 新增节点是父节点的右孩子
					// 左旋操作
					// 然后孩子父亲互换角色
					add_node_ptr = parent_node_ptr;
					rbt_left_rotate (root_node_ptr,null,add_node_ptr);

					parent_node_ptr = add_node_ptr->get_parent_node_ref ();
					grand_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();
				}

				set_rbt_color_black (parent_node_ptr);
				set_rbt_color_red (grand_parent_node_ptr);
				rbt_right_rotate (root_node_ptr,null,grand_parent_node_ptr);
			}

		}
		// 当爷爷的右孩子节点为父节点的时候
		else if (grand_parent_node_ptr->get_right_node () == parent_node_ptr)
		{
			temp_node_ptr = grand_parent_node_ptr->get_left_node_ref ();
			is_red_node = is_rbt_color_red (temp_node_ptr);

			if (is_red_node)
			{
				set_rbt_color_black (parent_node_ptr);
				set_rbt_color_black (temp_node_ptr);
				set_rbt_color_red (grand_parent_node_ptr);
				add_node_ptr = grand_parent_node_ptr;
			}
			else
			{
				if (parent_node_ptr->get_left_node () == add_node_ptr)
				{
					add_node_ptr = parent_node_ptr;
					rbt_right_rotate (root_node_ptr,null,add_node_ptr);

					parent_node_ptr = add_node_ptr->get_parent_node_ref ();
					grand_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();
				}
				set_rbt_color_black (parent_node_ptr);
				set_rbt_color_red (grand_parent_node_ptr);
				rbt_left_rotate (root_node_ptr,null,grand_parent_node_ptr);
			}
		}
		// 父节点既不是爷爷的左孩子也不是右孩子，内存出错
		else
		{
			RETURN_INVALID_RESULT (true,PFX_STATUS_MEM_ERR);
		}
	}
	set_rbt_color_black (root_node_ptr);

	return PFX_STATUS_OK;
}

PFX_RB_BST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_RB_BST_INIT :: rbt_remove_rotate_fixup
(PFX_RB_BST_INIT_TYPE::node_t *& PARAM_INOUT root_node_ptr,
		PFX_RB_BST_INIT_TYPE::node_t* PARAM_INOUT ref_node_ptr)
{
	typedef PFX_RB_BST_INIT_TYPE::node_t node_t;
	node_t* temp_node_ptr;
	bool check_color = false;
	bool check_color_ = false;

	RETURN_INVALID_RESULT ((null == ref_node_ptr),PFX_STATUS_OK);

	while (ref_node_ptr != root_node_ptr)
	{
		check_color = is_rbt_color_black (ref_node_ptr);

		if (!check_color)
		{
			break;
		}

		node_t* parent_node_ptr = ref_node_ptr->get_parent_node_ref ();

		if (parent_node_ptr->get_left_node() == ref_node_ptr)
		{
			temp_node_ptr = parent_node_ptr->get_right_node_ref ();
			check_color = is_rbt_color_red (temp_node_ptr);

			if (check_color)
			{
				if (temp_node_ptr)
				{
					set_rbt_color_black (temp_node_ptr);
				}

				set_rbt_color_red (parent_node_ptr);
				rbt_left_rotate (root_node_ptr,null,parent_node_ptr);

				temp_node_ptr = parent_node_ptr->get_right_node_ref ();
			}

			if (null == temp_node_ptr)
			{
				ref_node_ptr = parent_node_ptr;
				continue;
			}

			check_color = is_rbt_color_black (temp_node_ptr->get_left_node_ref ());
			check_color_ = is_rbt_color_black (temp_node_ptr->get_right_node_ref ());

			if (check_color && check_color_)
			{
				set_rbt_color_red (temp_node_ptr);
				ref_node_ptr = parent_node_ptr;
			}
			else
			{
				check_color = is_rbt_color_black (temp_node_ptr->get_right_node_ref ());

				if (check_color)
				{
					node_t* temp_left_node_ptr = temp_node_ptr->get_left_node_ref ();

					if (temp_left_node_ptr)
					{
						set_rbt_color_black (temp_left_node_ptr);
					}

					set_rbt_color_red (temp_node_ptr);
					rbt_right_rotate (root_node_ptr, null, temp_node_ptr);

					temp_node_ptr = parent_node_ptr->get_right_node_ref ();
				}

				node_t* temp_right_node_ptr = temp_node_ptr->get_right_node_ref ();

				copy_tree_color (temp_node_ptr, parent_node_ptr);
				set_rbt_color_black (parent_node_ptr);
				if (temp_right_node_ptr)
				{
					set_rbt_color_black (temp_right_node_ptr);
				}
				rbt_right_rotate (root_node_ptr, null, parent_node_ptr);

				ref_node_ptr = root_node_ptr;
			}
		}
		else if (parent_node_ptr->get_right_node() == ref_node_ptr)
		{
			temp_node_ptr = parent_node_ptr->get_left_node_ref ();
			check_color = is_rbt_color_red (temp_node_ptr);

			if (check_color)
			{
				if (temp_node_ptr)
				{
					set_rbt_color_black (temp_node_ptr);
				}
				set_rbt_color_red (parent_node_ptr);
				rbt_right_rotate (root_node_ptr, null, parent_node_ptr);

				temp_node_ptr = parent_node_ptr->get_left_node_ref ();
			}

			if (null == temp_node_ptr)
			{
				ref_node_ptr = parent_node_ptr;
				continue;
			}

			check_color = is_rbt_color_black (temp_node_ptr->get_left_node_ref ());
			check_color_ = is_rbt_color_black (temp_node_ptr->get_right_node_ref ());

			if (check_color && check_color_)
			{
				set_rbt_color_black (temp_node_ptr);
				ref_node_ptr = parent_node_ptr;
			}
			else
			{
				check_color = is_rbt_color_black (temp_node_ptr->get_left_node_ref ());

				if (check_color)
				{
					node_t* temp_right_node_ptr = temp_node_ptr->get_right_node_ref ();
					if (temp_right_node_ptr)
					{
						set_rbt_color_black (temp_right_node_ptr);
					}
					set_rbt_color_red (temp_node_ptr);
					rbt_left_rotate (root_node_ptr,null,temp_node_ptr);

					temp_node_ptr = parent_node_ptr->get_left_node_ref ();
				}

				node_t* temp_left_node_ptr = temp_node_ptr->get_right_node_ref ();

				copy_tree_color (temp_node_ptr,parent_node_ptr);
				set_rbt_color_black (parent_node_ptr);
				if (temp_left_node_ptr)
				{
					set_rbt_color_black (temp_left_node_ptr);
				}
				rbt_right_rotate (root_node_ptr,null,parent_node_ptr);

				ref_node_ptr = root_node_ptr;
			}
		}
		else
		{
			RETURN_INVALID_RESULT (true, PFX_STATUS_MEM_ERR);
		}
	}

	set_rbt_color_black (ref_node_ptr);
	return PFX_STATUS_OK;
}

//移除
PFX_CBST_RM_TEMPLATE_DEFINES
PFX_CBST_RM_TYPE::node_t* PFX_CBST_RM ::find_remove_replace_node
(PFX_CBST_RM_TYPE::node_t* PARAM_IN remove_node_ptr,
		PFX_CBST_RM_TYPE::node_t*& PARAM_OUT sub_remove_node_ptr,
		const PFX_CBST_RM_TYPE::node_t* PARAM_IN null_node_ptr /*= null*/)
{
	typedef PFX_CBST_RM_TYPE::node_t node_t;
	typedef PFX_CBST_RM_TYPE::minmax_t minmax_t;

	const node_t* sub_remove_ref_node_ptr = null;
	const node_t* tmp_sub_remove_node_ptr = null;

	if (null_node_ptr == remove_node_ptr->get_left_node ())
	{
		sub_remove_ref_node_ptr = remove_node_ptr->get_right_node ();
		tmp_sub_remove_node_ptr = remove_node_ptr;
	}
	else if (null_node_ptr == remove_node_ptr->get_right_node ())
	{
		sub_remove_ref_node_ptr = remove_node_ptr->get_left_node ();
		tmp_sub_remove_node_ptr = remove_node_ptr;
	}
	else
	{
		tmp_sub_remove_node_ptr = minmax_t::min_node (remove_node_ptr->get_right_node(), null_node_ptr);
		if (tmp_sub_remove_node_ptr->get_left_node () != null_node_ptr)
		{
			sub_remove_ref_node_ptr = tmp_sub_remove_node_ptr->get_left_node ();
		}
		else
		{
			sub_remove_ref_node_ptr = tmp_sub_remove_node_ptr->get_right_node ();
		}
	}

	sub_remove_node_ptr = (node_t*)tmp_sub_remove_node_ptr;
	return (node_t*)sub_remove_ref_node_ptr;
}

PFX_CBST_RM_TEMPLATE_DEFINES
PFX_CBST_RM_TYPE::node_t* PFX_CBST_RM ::remove_node
(PFX_CBST_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_CBST_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
		result_t& __status)
{
	__status = remove_node(root_node_ptr, remove_node_ptr);
	if (PFX_STATUS_OK == __status)
	{
		return remove_node_ptr;
	}
	else
	{
		return null;
	}
}

PFX_CBST_RM_TEMPLATE_DEFINES
result_t PFX_CBST_RM ::remove_node
(PFX_CBST_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_CBST_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
		const PFX_CBST_RM_TYPE::node_t* PARAM_IN null_node_ptr /*= null*/)
{
	typedef PFX_CBST_RM_TYPE::node_t node_t;
	typedef PFX_CBST_RM_TYPE::minmax_t minmax_t;

	RETURN_INVALID_RESULT (null == remove_node_ptr,PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (null == root_node_ptr,PFX_STATUS_OK);

	node_t* sub_romove_ref_node_ptr;
	node_t* sub_remove_node_ptr;
	result_t status = PFX_STATUS_OK;

	sub_romove_ref_node_ptr = find_remove_replace_node
	(remove_node_ptr, sub_remove_node_ptr, null_node_ptr);

	status = remove_node_internal (root_node_ptr, remove_node_ptr, sub_remove_node_ptr,
			sub_romove_ref_node_ptr, null_node_ptr);
	return status;
}

PFX_CBST_RM_TEMPLATE_DEFINES
result_t PFX_CBST_RM ::remove_node_internal
(PFX_CBST_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_CBST_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
		PFX_CBST_RM_TYPE::node_t* PARAM_INOUT sub_remove_node_ptr,
		PFX_CBST_RM_TYPE::node_t* PARAM_INOUT sub_remove_node_ref_ptr,
		const PFX_CBST_RM_TYPE::node_t* PARAM_IN null_node_ptr /*= null*/)
{
	typedef PFX_CBST_RM_TYPE::node_t node_t;
	typedef PFX_CBST_RM_TYPE::init_t init_t;

	node_t* tmp_root_node_ptr = root_node_ptr;
	node_t* parant_node_ptr = null;
	result_t status = PFX_STATUS_OK;

	FOR_ONE_LOOP_BEGIN
	// 处理替换节点
	if (sub_remove_node_ptr == tmp_root_node_ptr)
	{
		parant_node_ptr = tmp_root_node_ptr->get_parent_node_ref ();
		if (null != parant_node_ptr)
		{
			if (parant_node_ptr->get_left_node() == tmp_root_node_ptr)
			{
				parant_node_ptr->set_left_node (sub_remove_node_ref_ptr);
			}
			else if (parant_node_ptr->get_right_node() == tmp_root_node_ptr)
			{
				parant_node_ptr->set_right_node (sub_remove_node_ref_ptr);
			}
			else
			{
				BREAK_LOOP (status, PFX_STATUS_MEM_ERR);
			}
		}
		if (sub_remove_node_ref_ptr)
		{
			sub_remove_node_ref_ptr->set_parent_node (parant_node_ptr);
		}

		root_node_ptr = sub_remove_node_ref_ptr;
		init_t::init_node_leaves (remove_node_ptr);
		BREAK_LOOP (status,PFX_STATUS_OK);
	}

	parant_node_ptr = sub_remove_node_ptr->get_parent_node_ref ();
	if (sub_remove_node_ptr == parant_node_ptr->get_left_node ())
	{
		parant_node_ptr->set_left_node (sub_remove_node_ref_ptr);
	}
	else
	{
		parant_node_ptr->set_right_node (sub_remove_node_ref_ptr);
	}

	if (sub_remove_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			sub_remove_node_ref_ptr->set_parent_node (parant_node_ptr);
		}

		init_t::init_node_leaves (remove_node_ptr);
		BREAK_LOOP (status,PFX_STATUS_OK);
	}

	if (parant_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			sub_remove_node_ref_ptr->set_parent_node (sub_remove_node_ptr);
		}
	}
	else
	{
		if (sub_remove_node_ref_ptr)
		{
			sub_remove_node_ref_ptr->set_parent_node (parant_node_ptr);
		}
	}

	// 将remove node相关的指针复制
	sub_remove_node_ptr->set_left_node (remove_node_ptr->get_left_node_ref ());
	sub_remove_node_ptr->set_right_node (remove_node_ptr->get_right_node_ref ());
	sub_remove_node_ptr->set_parent_node (remove_node_ptr->get_parent_node_ref ());

	if (remove_node_ptr == tmp_root_node_ptr)// 移除节点是根节点
	{
		root_node_ptr = sub_remove_node_ptr;		// 将根节点替换为psub_node
	}
	else
	{
		parant_node_ptr = remove_node_ptr->get_parent_node_ref ();
		// 替换移除节点父节点的相关指针
		if (remove_node_ptr == parant_node_ptr->get_left_node())
		{
			parant_node_ptr->set_left_node (sub_remove_node_ptr);
		}
		else if (remove_node_ptr == parant_node_ptr->get_right_node())
		{
			parant_node_ptr->set_right_node (sub_remove_node_ptr);
		}
		else
		{
			BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
		}
	}

	// 更新现在新的左右节点的父节点指针
	node_t* left_node_ptr = sub_remove_node_ptr->get_left_node_ref ();
	node_t* right_node_ptr = sub_remove_node_ptr->get_right_node_ref ();

	if (null_node_ptr)
	{
		if (left_node_ptr != null_node_ptr && left_node_ptr)
		{
			left_node_ptr->set_parent_node (sub_remove_node_ptr);
		}

		if (right_node_ptr != null_node_ptr && right_node_ptr)
		{
			right_node_ptr->set_parent_node (sub_remove_node_ptr);
		}
	}
	else
	{
		if (left_node_ptr)
		{
			left_node_ptr->set_parent_node (sub_remove_node_ptr);
		}

		if (right_node_ptr)
		{
			right_node_ptr->set_parent_node (sub_remove_node_ptr);
		}
	}

	init_t::init_node_leaves (remove_node_ptr);
	BREAK_LOOP (status,PFX_STATUS_OK);
	FOR_ONE_LOOP_END

	return status;
}

// AVL移除节点
PFX_AVL_BST_RM_TEMPLATE_DEFINES
PFX_AVL_BST_RM_TYPE::node_t* PFX_AVL_BST_RM ::remove_node
(PFX_AVL_BST_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_AVL_BST_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
		result_t& __status)
{
	typedef PFX_AVL_BST_RM_TYPE::node_t node_t;
	typedef PFX_AVL_BST_RM_TYPE::bst_remove_t bst_remove_t;
	typedef PFX_AVL_BST_RM_TYPE::init_t init_t;

	result_t status;
	node_t* temp_node_ptr = null;
	node_t* parent_node_ptr;
	node_t* sub_romove_ref_node_ptr;
	node_t* sub_remove_node_ptr;

	RETURN_INVALID_BY_ACT_RESULT ((null == remove_node_ptr),
			__status = PFX_STATUS_INVALID_PARAMS,null);

	sub_romove_ref_node_ptr =
	bst_remove_t :: find_remove_replace_node
	(remove_node_ptr,sub_remove_node_ptr,null);

	if (sub_remove_node_ptr)
	{
		parent_node_ptr = sub_remove_node_ptr->get_parent_node_ref();
	}

	status = bst_remove_t :: remove_node_internal
	(root_node_ptr, remove_node_ptr,
			sub_remove_node_ptr, sub_romove_ref_node_ptr, null);

	__status = status;

	if (PFX_STATUS_OK > status)
	{
		return remove_node_ptr;
	}
	if (sub_remove_node_ptr)
	{
		sub_remove_node_ptr->set_height (remove_node_ptr->get_height ());
	}

	RETURN_RESULT ((null == root_node_ptr),remove_node_ptr);

	temp_node_ptr = sub_romove_ref_node_ptr;
	if (null == temp_node_ptr)
	{
		if (null != sub_remove_node_ptr)
		{
			if (remove_node_ptr != parent_node_ptr)
			{
				temp_node_ptr = parent_node_ptr;
			}
			else
			{
				temp_node_ptr = sub_remove_node_ptr;
			}
		}

		if (null == temp_node_ptr)
		{
			temp_node_ptr = root_node_ptr;
		}
	}
	status = init_t :: avl_update_fixed (root_node_ptr,temp_node_ptr);

	__status = status;
	if (PFX_STATUS_OK > status)
	{
		return null;
	}

	return remove_node_ptr;
}

// 黑红树移除节点
PFX_RB_BST_RM_TEMPLATE_DEFINES
PFX_RB_BST_RM_TYPE::node_t* PFX_RB_BST_RM ::remove_node
(PFX_RB_BST_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_RB_BST_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
		result_t& __status)
{
	typedef PFX_RB_BST_RM_TYPE::node_t node_t;
	typedef PFX_RB_BST_RM_TYPE::bst_remove_t bst_remove_t;
	typedef PFX_RB_BST_RM_TYPE::init_t init_t;

	result_t status;
	bool is_red_node;

	node_t* sub_romove_ref_node_ptr;
	node_t* sub_remove_node_ptr;

	RETURN_INVALID_BY_ACT_RESULT (null == remove_node_ptr,
			__status = PFX_STATUS_INVALID_PARAMS,null);

	sub_romove_ref_node_ptr =
	bst_remove_t :: find_remove_replace_node
	(remove_node_ptr, sub_remove_node_ptr, null);

	if (sub_remove_node_ptr == root_node_ptr)
	{
		status = bst_remove_t :: remove_node_internal
		(root_node_ptr, remove_node_ptr, sub_remove_node_ptr, sub_romove_ref_node_ptr, null);

		__status = status;

		if (PFX_STATUS_OK == status)
		{
			if (null != sub_romove_ref_node_ptr)
			{
				init_t ::set_rbt_color_black (sub_romove_ref_node_ptr);
			}

			return remove_node_ptr;
		}
		return null;
	}

	is_red_node = init_t :: is_rbt_color_red (sub_remove_node_ptr);

	status = bst_remove_t :: remove_node_internal
	(root_node_ptr, remove_node_ptr, sub_remove_node_ptr, sub_romove_ref_node_ptr, null);

	if (null != sub_remove_node_ptr && sub_remove_node_ptr != remove_node_ptr)
	{
		init_t :: copy_tree_color (sub_remove_node_ptr,remove_node_ptr);
	}

	__status = status;

	RETURN_INVALID_RESULT ((PFX_STATUS_OK > status),null);

	RETURN_RESULT ((is_red_node || null == root_node_ptr), remove_node_ptr);

	status = init_t :: rbt_remove_rotate_fixup (root_node_ptr, sub_romove_ref_node_ptr);

	__status = status;

	RETURN_INVALID_RESULT ((PFX_STATUS_OK > status), null);

	return remove_node_ptr;
}

// 通过节点查找结点
PFX_CBST_NFIND_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_NFIND_TYPE::node_t* PFX_CBST_NFIND ::find_node
(const PFX_CBST_NFIND_TYPE::node_t* PARAM_IN key_node_ptr,
		const PFX_CBST_NFIND_TYPE::node_t* PARAM_IN root_node_ptr)
{
	typedef PFX_CBST_NFIND_TYPE::node_t node_t;
	typedef PFX_CBST_NFIND_TYPE::compare_two_node_t compare_two_node_t;

	RETURN_INVALID_RESULT (!key_node_ptr, null);

	const node_t* traval_node_ptr = root_node_ptr;

	while (traval_node_ptr)
	{
		int cmp_result = compare_two_node_t :: compare (key_node_ptr, traval_node_ptr);
		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node ();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node ();
		}
		else
		{
			break;
		}
	}
	return traval_node_ptr;
}
//
PFX_CBST_NFIND_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_NFIND_TYPE::node_t* PFX_CBST_NFIND ::find_near_node
(const PFX_CBST_NFIND_TYPE::node_t* PARAM_IN key_node_ptr,
		const PFX_CBST_NFIND_TYPE::node_t* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result)
{
	typedef PFX_CBST_NFIND_TYPE::node_t node_t;
	typedef PFX_CBST_NFIND_TYPE::compare_two_node_t compare_two_node_t;

	RETURN_INVALID_RESULT (!key_node_ptr, null);

	const node_t* near_node_ptr = null;
	const node_t* traval_node_ptr = root_node_ptr;

	int cmp_result = 0;
	while (traval_node_ptr)
	{
		cmp_result = compare_two_node_t :: compare (key_node_ptr,traval_node_ptr);
		near_node_ptr = traval_node_ptr;

		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node ();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node ();
		}
		else
		{
			break;
		}
	}
	last_cmp_result = cmp_result;
	return near_node_ptr;
}

PFX_CBST_ITR_FIND_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_ITR_FIND_TYPE::const_iterator_t* PFX_CBST_ITR_FIND::find_node
(const PFX_CBST_ITR_FIND_TYPE::node_t* PARAM_IN key_node_ptr,
		PFX_CBST_ITR_FIND_TYPE::const_iterator_t& itr)
{
	typedef PFX_CBST_ITR_FIND_TYPE::node_find_t node_find_t;
	typedef PFX_CBST_ITR_FIND_TYPE::node_t node_t;
	const node_t* find_node_ptr = node_find_t::find_node (key_node_ptr, itr.root_node());
	if (find_node_ptr)
	{
		itr.init(find_node_ptr);
		return &itr;
	}
	else
	{
		return null;
	}
}

PFX_CBST_ITR_FIND_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_ITR_FIND_TYPE::const_iterator_t* PFX_CBST_ITR_FIND::find_near_node
(const PFX_CBST_ITR_FIND_TYPE::node_t* PARAM_IN key_node_ptr,
		PFX_CBST_ITR_FIND_TYPE::const_iterator_t& itr,
		int& PARAM_INOUT last_cmp_result)
{
	typedef PFX_CBST_ITR_FIND_TYPE::node_find_t node_find_t;
	typedef PFX_CBST_ITR_FIND_TYPE::node_t node_t;
	const node_t* find_node_ptr = node_find_t::find_near_node (key_node_ptr, itr.root_node(), last_cmp_result);
	if (find_node_ptr)
	{
		itr.init(find_node_ptr);
		return &itr;
	}
	else
	{
		return null;
	}
}

PFX_CBST_ELEM_FIND_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_ELEM_FIND_TYPE::const_iterator_t* PFX_CBST_ELEM_FIND::find_node
(const PFX_CBST_ELEM_FIND_TYPE::element_t& PARAM_IN __key,
		PFX_CBST_ELEM_FIND_TYPE::const_iterator_t& itr)
{
	//typedef PFX_CBST_ELEM_FIND_TYPE::node_find_t							node_find_t;
	typedef PFX_CBST_ELEM_FIND_TYPE::node_t node_t;
	typedef PFX_CBST_ELEM_FIND_TYPE::compare_two_elemen_t cmp_t;

	const node_t* find_node_ptr = itr.root_node();
	while (find_node_ptr)
	{
		int cmp_result =  cmp_t::compare (find_node_ptr->get_item(), __key);
		if (cmp_result > 0)
		{
			find_node_ptr = find_node_ptr->get_left_node ();
		}
		else if (cmp_result < 0)
		{
			find_node_ptr = find_node_ptr->get_right_node ();
		}
		else
		{
			break;
		}
	}

	if (find_node_ptr)
	{
		itr.init(find_node_ptr);
		return &itr;
	}
	else
	{
		return null;
	}
}

PFX_CBST_ELEM_FIND_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_ELEM_FIND_TYPE::const_iterator_t* PFX_CBST_ELEM_FIND::find_near_node
(const PFX_CBST_ELEM_FIND_TYPE::element_t& PARAM_IN __key,
		PFX_CBST_ELEM_FIND_TYPE::const_iterator_t& itr,
		int& PARAM_INOUT last_cmp_result)
{
	//typedef PFX_CBST_ELEM_FIND_TYPE::node_find_t							node_find_t;
	typedef PFX_CBST_ELEM_FIND_TYPE::node_t node_t;
	typedef PFX_CBST_ELEM_FIND_TYPE::compare_two_elemen_t cmp_t;

	const node_t* near_node_ptr = null;
	const node_t* traval_node_ptr = itr.root_node();

	int cmp_result = 0;
	while (traval_node_ptr)
	{
		cmp_result = cmp_t::compare(__key, traval_node_ptr->get_item());
		near_node_ptr = traval_node_ptr;

		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node ();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node ();
		}
		else
		{
			break;
		}
	}
	last_cmp_result = cmp_result;
	if (near_node_ptr)
	{
		itr.init(near_node_ptr);
		return &itr;
	}
	else
	{
		return null;
	}
}

PFX_CBST_ELEM_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_ELEM_FIND_NODE_TYPE::node_t*
PFX_CBST_ELEM_FIND_NODE::find_node(const PFX_CBST_ELEM_FIND_NODE_TYPE::key_t& PARAM_IN __key, 
const PFX_CBST_ELEM_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr)
{
	typedef PFX_CBST_ELEM_FIND_NODE_TYPE::node_t node_t;
	typedef PFX_CBST_ELEM_FIND_NODE_TYPE::compare_two_elemen_t cmp_t;

	const node_t* find_node_ptr = root_node_ptr;
	while (find_node_ptr)
	{
		int cmp_result = cmp_t::compare(find_node_ptr->get_item(), __key);
		if (cmp_result > 0)
		{
			find_node_ptr = find_node_ptr->get_left_node();
		}
		else if (cmp_result < 0)
		{
			find_node_ptr = find_node_ptr->get_right_node();
		}
		else
		{
			break;
		}
	}

	return find_node_ptr;
}

PFX_CBST_ELEM_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_ELEM_FIND_NODE_TYPE::node_t*
PFX_CBST_ELEM_FIND_NODE::find_near_node
(const PFX_CBST_ELEM_FIND_NODE_TYPE::key_t& PARAM_IN __key,
const PFX_CBST_ELEM_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr,
int& PARAM_INOUT last_cmp_result)
{
	typedef PFX_CBST_ELEM_FIND_NODE_TYPE::node_t               node_t;
	typedef PFX_CBST_ELEM_FIND_NODE_TYPE::compare_two_elemen_t cmp_t;

	const node_t* near_node_ptr = null;
	const node_t* traval_node_ptr = root_node_ptr;

	int cmp_result = 0;
	while (traval_node_ptr)
	{
		cmp_result = cmp_t::compare(__key, traval_node_ptr->get_item());
		near_node_ptr = traval_node_ptr;

		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node();
		}
		else
		{
			break;
		}
	}
	last_cmp_result = cmp_result;
	return near_node_ptr;
}


PFX_CBST_ELEM_FINDX_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_ELEM_FINDX_TYPE::const_iterator_t* PFX_CBST_ELEM_FINDX::find_node
(const PFX_CBST_ELEM_FINDX_TYPE::key_t& PARAM_IN __key,
		PFX_CBST_ELEM_FINDX_TYPE::const_iterator_t& itr)
{
	typedef PFX_CBST_ELEM_FINDX_TYPE::node_t node_t;
	typedef PFX_CBST_ELEM_FINDX_TYPE::compare_two_elemen_t cmp_t;

	const node_t* find_node_ptr = itr.root_node();
	while (find_node_ptr)
	{
		int cmp_result = cmp_t::compare(find_node_ptr->get_item(), __key);
		if (cmp_result > 0)
		{
			find_node_ptr = find_node_ptr->get_left_node();
		}
		else if (cmp_result < 0)
		{
			find_node_ptr = find_node_ptr->get_right_node();
		}
		else
		{
			break;
		}
	}

	if (find_node_ptr)
	{
		itr.init(find_node_ptr);
		return &itr;
	}
	else
	{
		return null;
	}
}

PFX_CBST_ELEM_FINDX_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_ELEM_FINDX_TYPE::const_iterator_t* PFX_CBST_ELEM_FINDX::find_near_node
(const PFX_CBST_ELEM_FINDX_TYPE::key_t& PARAM_IN __key,
		PFX_CBST_ELEM_FINDX_TYPE::const_iterator_t& itr,
		int& PARAM_INOUT last_cmp_result)
{
	typedef PFX_CBST_ELEM_FINDX_TYPE::node_t node_t;
	typedef PFX_CBST_ELEM_FINDX_TYPE::compare_two_elemen_t cmp_t;

	const node_t* near_node_ptr = null;
	const node_t* traval_node_ptr = itr.root_node();

	int cmp_result = 0;
	while (traval_node_ptr)
	{
		cmp_result = cmp_t::compare(__key, traval_node_ptr->get_item());
		near_node_ptr = traval_node_ptr;

		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node();
		}
		else
		{
			break;
		}
	}
	last_cmp_result = cmp_result;
	if (near_node_ptr)
	{
		itr.init(near_node_ptr);
		return &itr;
	}
	else
	{
		return null;
	}
}

PFX_CBST_STR_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_STR_FIND_NODE_TYPE::node_t* PFX_CBST_STR_FIND_NODE::
find_node(const PFX_CBST_STR_FIND_NODE_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count,
const PFX_CBST_STR_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr)
{
	typedef PFX_CBST_STR_FIND_NODE_TYPE::node_t node_t;
	typedef PFX_CBST_STR_FIND_NODE_TYPE::compare_two_elemen_t cmp_t;

	const node_t* find_node_ptr = root_node_ptr;
	while (find_node_ptr)
	{
		int cmp_result = cmp_t::compare(find_node_ptr->get_item(), __chars_ptr, chars_count);
		if (cmp_result > 0)
		{
			find_node_ptr = find_node_ptr->get_left_node();
		}
		else if (cmp_result < 0)
		{
			find_node_ptr = find_node_ptr->get_right_node();
		}
		else
		{
			break;
		}
	}

	return find_node_ptr;
}

PFX_CBST_STR_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_STR_FIND_NODE_TYPE::node_t* PFX_CBST_STR_FIND_NODE::find_near_node
(const PFX_CBST_STR_FIND_NODE_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count,
const PFX_CBST_STR_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr,
int& PARAM_INOUT last_cmp_result)
{
	typedef PFX_CBST_STR_FIND_NODE_TYPE::node_t node_t;
	typedef PFX_CBST_STR_FIND_NODE_TYPE::compare_two_elemen_t cmp_t;

	const node_t* near_node_ptr = null;
	const node_t* traval_node_ptr = root_node_ptr;

	int cmp_result = 0;
	while (traval_node_ptr)
	{
		cmp_result = cmp_t::compare(traval_node_ptr->get_item(), 
			__chars_ptr, 
			chars_count);

		near_node_ptr = traval_node_ptr;

		if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node();
		}
		else if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node();
		}
		else
		{
			break;
		}
	}
	last_cmp_result = cmp_result;
	return near_node_ptr;
}

PFX_CBST_STR_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_STR_FIND_NODE_TYPE::node_t*
PFX_CBST_STR_FIND_NODE::find_node(
const PFX_CBST_STR_FIND_NODE_TYPE::key_t& PARAM_IN __key, 
const PFX_CBST_STR_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr)
{
	typedef PFX_CBST_STR_FIND_NODE_TYPE::node_t node_t;
	typedef PFX_CBST_STR_FIND_NODE_TYPE::compare_two_elemen_t cmp_t;

	const node_t* find_node_ptr = root_node_ptr;
	while (find_node_ptr)
	{
		int cmp_result = cmp_t::compare(find_node_ptr->get_item(), __key);
		if (cmp_result > 0)
		{
			find_node_ptr = find_node_ptr->get_left_node();
		}
		else if (cmp_result < 0)
		{
			find_node_ptr = find_node_ptr->get_right_node();
		}
		else
		{
			break;
		}
	}

	return find_node_ptr;
}

PFX_CBST_STR_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_STR_FIND_NODE_TYPE::node_t*
PFX_CBST_STR_FIND_NODE::find_near_node
(const PFX_CBST_STR_FIND_NODE_TYPE::key_t& PARAM_IN __key,
const PFX_CBST_STR_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr,
int& PARAM_INOUT last_cmp_result)
{
	typedef PFX_CBST_STR_FIND_NODE_TYPE::node_t               node_t;
	typedef PFX_CBST_STR_FIND_NODE_TYPE::compare_two_elemen_t cmp_t;

	const node_t* near_node_ptr = null;
	const node_t* traval_node_ptr = root_node_ptr;

	int cmp_result = 0;
	while (traval_node_ptr)
	{
		cmp_result = cmp_t::compare(__key, traval_node_ptr->get_item());
		near_node_ptr = traval_node_ptr;

		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node();
		}
		else
		{
			break;
		}
	}
	last_cmp_result = cmp_result;
	return near_node_ptr;
}

// 插入
PFX_CBST_INSERT_TEMPLATE_DEFINES
PFX_INLINE const PFX_CBST_INSERT_TYPE::node_t* PFX_CBST_INSERT::add_node
(PFX_CBST_INSERT_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_CBST_INSERT_TYPE::node_t* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT status_)
{
	typedef PFX_CBST_INSERT_TYPE::node_t node_t;
	node_t* return_node_ptr = null;
	status_ = add_node(root_node_ptr, add_node_ptr, return_node_ptr);
	return return_node_ptr;
}

PFX_CBST_INSERT_TEMPLATE_DEFINES
result_t PFX_CBST_INSERT ::add_node
(PFX_CBST_INSERT_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_CBST_INSERT_TYPE::node_t* PARAM_INOUT add_node_ptr,
		PFX_CBST_INSERT_TYPE::node_t*& PARAM_OUT added_node_ptr)
{
	typedef PFX_CBST_INSERT_TYPE::node_t node_t;
	typedef PFX_CBST_INSERT_TYPE::compare_two_node_t cmp_t;
	typedef PFX_CBST_INSERT_TYPE::init_t init_t;
	typedef PFX_CBST_INSERT_TYPE::find_t find_t;

	result_t status = PFX_STATUS_OK;
	int cmp_result;
	node_t* tmp_root_node_ptr;
	node_t* node_to_be_add_ptr;
	node_t* parent_node_ptr;

	tmp_root_node_ptr = root_node_ptr;

	// 添加第一个节点
	if (null == tmp_root_node_ptr)
	{
		root_node_ptr = add_node_ptr;
		init_t ::init_node_leaves (add_node_ptr);
		added_node_ptr = add_node_ptr;
		return PFX_STATUS_OK;
	}

	FOR_ONE_LOOP_BEGIN

	node_to_be_add_ptr = (node_t*) find_t::find_near_node
	(add_node_ptr, tmp_root_node_ptr, cmp_result);

	// 已经存在一个同样key的节点, added_node_ptr返回的是已有节点的指针
	if (null != node_to_be_add_ptr && 0 == cmp_result)
	{
		added_node_ptr = node_to_be_add_ptr;
		status = PFX_STATUS_UNIQUE;
		break;
	}

	parent_node_ptr = node_to_be_add_ptr->get_parent_node_ref ();

	if (0 > cmp_result)
	{
		if (null == node_to_be_add_ptr->get_left_node())
		{
			node_to_be_add_ptr->set_left_node (add_node_ptr);
			init_t ::init_node_leaves (add_node_ptr, null, null, node_to_be_add_ptr);
		}
		else
		{
			// 内存数据被损坏
			status = PFX_STATUS_MEM_ERR;
			break;
		}
	}
	else
	{
		if (null == node_to_be_add_ptr->get_right_node())
		{
			init_t ::init_node_leaves (add_node_ptr,null,null,node_to_be_add_ptr);
			node_to_be_add_ptr->set_right_node ((node_t*)add_node_ptr);
		}
		else
		{
			// 内存数据被损坏
			status = PFX_STATUS_MEM_ERR;
			break;
		}
	}

	added_node_ptr = add_node_ptr;
	status = PFX_STATUS_OK;
	FOR_ONE_LOOP_END

	return status;
}

// AVL 树插入节点
PFX_AVL_BST_INSERT_TEMPLATE_DEFINES
PFX_INLINE const PFX_AVL_BST_INSERT_TYPE::node_t* PFX_AVL_BST_INSERT ::add_node
(PFX_AVL_BST_INSERT_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_AVL_BST_INSERT_TYPE::node_t* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT __status)
{
	typedef PFX_AVL_BST_INSERT_TYPE::node_t node_t;
	typedef PFX_AVL_BST_INSERT_TYPE::compare_two_node_t cmp_t;
	typedef PFX_AVL_BST_INSERT_TYPE::init_t init_t;
	typedef PFX_AVL_BST_INSERT_TYPE::BST_insert_t BST_insert_t;

	result_t status;
	node_t* return_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

	BREAK_LOOP_CONDITION_SETS (!add_node_ptr,
			status, PFX_STATUS_INVALID_PARAMS);

	status = BST_insert_t ::add_node (root_node_ptr,
			add_node_ptr, return_node_ptr);

	BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);

	init_t :: update_avl_height (add_node_ptr);
	status = init_t :: avl_update_insert_rotate (root_node_ptr,add_node_ptr);

	BREAK_LOOP_CONDITION_SETS ((PFX_STATUS_OK > status),
			return_node_ptr, null);

	FOR_ONE_LOOP_END

	__status = status;
	return return_node_ptr;
}

// 黑红树插入节点
PFX_RB_BST_INSERT_TEMPLATE_DEFINES
PFX_INLINE const PFX_RB_BST_INSERT_TYPE::node_t* PFX_RB_BST_INSERT ::add_node
(PFX_RB_BST_INSERT_TYPE::node_t*& PARAM_INOUT root_node_ptr,
		PFX_RB_BST_INSERT_TYPE::node_t* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT __status)
{
	typedef PFX_RB_BST_INSERT_TYPE::node_t node_t;
	typedef PFX_RB_BST_INSERT_TYPE::compare_two_node_t cmp_t;
	typedef PFX_RB_BST_INSERT_TYPE::init_t init_t;
	typedef PFX_RB_BST_INSERT_TYPE::BST_insert_t BST_insert_t;

	result_t status;
	node_t* return_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

	BREAK_LOOP_CONDITION_SETS (!add_node_ptr,
			status, PFX_STATUS_INVALID_PARAMS);

	// 插入的初始节点的颜色为红色
	init_t ::set_rbt_color_red (add_node_ptr);

	status = BST_insert_t::add_node (root_node_ptr,
			add_node_ptr,return_node_ptr);

	BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);

	// 平衡变换
	status = init_t ::rbt_add_rotate_fixup (root_node_ptr,add_node_ptr);

	BREAK_LOOP_CONDITION_SETS ((PFX_STATUS_OK > status),
			return_node_ptr, null);

	FOR_ONE_LOOP_END

	__status = status;

	return return_node_ptr;
}

// 清除
PFX_CBST_CLEAN_TEMPLATE_DEFINES
result_t PFX_CBST_CLEAN::clean
(PFX_CBST_CLEAN_TYPE::node_t*& PARAM_INOUT root_dec_ptr)
{
	typedef PFX_CBST_CLEAN_TYPE::node_t node_t;
	typedef const_bst_posorder_operate< node_t > itr_t;
	typedef PFX_CBST_CLEAN_TYPE::new_delete_t new_delete_t;

	result_t status = PFX_STATUS_OK;

	RETURN_RESULT (null == root_dec_ptr, status);

	const node_t* iterator_begin_ptr = itr_t::begin (root_dec_ptr);
	const node_t* iterator_end_ptr = itr_t::end(root_dec_ptr);

	const node_t* cur_node_ptr;
	cur_node_ptr = iterator_begin_ptr;

	do
	{
		node_t* del_node_ptr = (node_t*) cur_node_ptr;

		if (null == del_node_ptr)
		{
			break;
		}

		if (cur_node_ptr == iterator_end_ptr)
		{
			status = new_delete_t::delete_node (del_node_ptr);
			break;
		}

		cur_node_ptr = itr_t::increase(root_dec_ptr, cur_node_ptr);

		if (cur_node_ptr)
		{
			if (root_dec_ptr == del_node_ptr)
			{
				root_dec_ptr = null;
			}
			if (null == del_node_ptr->get_parent_node())
			{
				status = new_delete_t::delete_node (del_node_ptr);
				break;
			}

			status = new_delete_t::delete_node (del_node_ptr);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		}
	}while (1);
	root_dec_ptr = null;

	return status;
}

// 克隆
PFX_CBST_CLONE_TEMPLATE_DEFINES
result_t PFX_CBST_CLONE ::clone
(PFX_CBST_CLONE_TYPE::node_t*& PARAM_INOUT root_dec_ptr,
		const PFX_CBST_CLONE_TYPE::node_t * PARAM_IN other_root_ptr)
{
	typedef PFX_CBST_CLONE_TYPE::node_t node_t;
	typedef PFX_CBST_CLONE_TYPE::init_t init_t;
	typedef PFX_CBST_CLONE_TYPE::clean_t clean_t;
	typedef PFX_CBST_CLONE_TYPE::new_delete_t new_delete_t;

	RETURN_RESULT (other_root_ptr == root_dec_ptr,PFX_STATUS_OK);
	RETURN_RESULT (!root_dec_ptr, PFX_STATUS_UNIQUE);
	RETURN_RESULT (null == other_root_ptr,PFX_STATUS_OK);

	result_t status;
	node_t* temp_dec_node_ptr;
	const node_t* temp_src_node_ptr;
	node_t* new_node_ptr = new_delete_t::new_node ();
	RETURN_INVALID_RESULT (null == new_node_ptr,PFX_STATUS_MEM_LOW);

	*new_node_ptr = *other_root_ptr;

	init_t ::init_node_leaves (new_node_ptr);
	root_dec_ptr = new_node_ptr;

	temp_dec_node_ptr = new_node_ptr;
	temp_src_node_ptr = other_root_ptr;

	status = PFX_STATUS_OK;
	do
	{
		if (null == temp_dec_node_ptr->get_left_node())
		{
			if (null != temp_src_node_ptr->get_left_node())
			{
				new_node_ptr = new_delete_t::new_node ();
				BREAK_LOOP_CONDITION_SETS (!new_node_ptr, status, PFX_STATUS_MEM_LOW);

				*new_node_ptr = *(temp_src_node_ptr->get_left_node());

				init_t ::init_node_leaves (new_node_ptr,null,null,temp_dec_node_ptr);

				temp_dec_node_ptr->set_left_node (new_node_ptr);
				temp_dec_node_ptr = new_node_ptr;

				temp_src_node_ptr = temp_src_node_ptr->get_left_node_ref ();
				continue;
			}
		}

		if (null == temp_dec_node_ptr->get_right_node())
		{
			if (null != temp_src_node_ptr->get_right_node())
			{
				new_node_ptr = new_delete_t::new_node ();
				BREAK_LOOP_CONDITION_SETS (!new_node_ptr, status, PFX_STATUS_MEM_LOW);
				*new_node_ptr = *(temp_src_node_ptr->get_right_node());

				init_t ::init_node_leaves (new_node_ptr,null,null,temp_dec_node_ptr);

				temp_dec_node_ptr->set_right_node (new_node_ptr);
				temp_dec_node_ptr = new_node_ptr;

				temp_src_node_ptr = temp_src_node_ptr->get_right_node_ref ();
				continue;
			}
		}

		temp_dec_node_ptr = temp_dec_node_ptr->get_parent_node_ref ();
		temp_src_node_ptr = temp_src_node_ptr->get_parent_node_ref ();
	}while(temp_dec_node_ptr);

	if (PFX_STATUS_OK > status)
	{
		clean_t::clean (root_dec_ptr);
	}
	return status;
}

PFX_CBST_COPY_TEMPLATE_DEFINES
result_t PFX_CBST_COPY::copy
(PFX_CBST_COPY_TYPE::node_t*& PARAM_INOUT root_dec_ptr,
		const PFX_CBST_COPY_TYPE::node_t * PARAM_IN other_root_ptr)
{
	typedef PFX_CBST_COPY_TYPE::node_t node_t;
	typedef PFX_CBST_COPY_TYPE::insert_t insert_t;
	typedef PFX_CBST_COPY_TYPE::clean_t clean_t;
	typedef PFX_CBST_COPY_TYPE::new_delete_t new_delete_t;

	typedef const_bst_preorder_operate < node_t > itr_t;

	RETURN_RESULT (other_root_ptr == root_dec_ptr, PFX_STATUS_OK);
	RETURN_RESULT (!root_dec_ptr, PFX_STATUS_UNIQUE);
	RETURN_RESULT (null == other_root_ptr,PFX_STATUS_OK);

	result_t status = PFX_STATUS_OK;

	typename itr_t::st_iterator_t iterator_begin;
	typename itr_t::st_iterator_t iterator_end;

	typename itr_t::st_iterator_t* iterator_begin_ptr = itr_t::begin (other_root_ptr, iterator_begin);
	typename itr_t::st_iterator_t* iterator_end_ptr = itr_t::end (other_root_ptr, iterator_end);

	const node_t* cur_node_ptr;
	cur_node_ptr = iterator_begin_ptr->m_cur_node_ptr;
	const node_t* add_node_ptr = null;
	do
	{
		//node_t* copy_node_ptr = (node_t*) cur_node_ptr;
		//BREAK_LOOP_CONDITION (null == copy_node_ptr);
		BREAK_LOOP_CONDITION (null == cur_node_ptr);

		if (cur_node_ptr && cur_node_ptr == iterator_end_ptr->m_cur_node_ptr )
		{
			node_t* new_node_ptr = new_delete_t::new_node ();
			BREAK_LOOP_CONDITION_SETS (null == new_node_ptr, status, PFX_STATUS_MEM_LOW);

			*new_node_ptr = *(cur_node_ptr);

			add_node_ptr = insert_t::add_node (root_dec_ptr, new_node_ptr, status);

			if (null == add_node_ptr)
			{
				new_delete_t::delete_node (new_node_ptr);
				BREAK_LOOP (status, PFX_STATUS_FAIL);
			}

			BREAK_LOOP (status, PFX_STATUS_OK);
		}

		iterator_begin_ptr = itr_t::increase(iterator_begin);
		cur_node_ptr = iterator_begin_ptr->m_cur_node_ptr;

		if (cur_node_ptr)
		{
			node_t* new_node_ptr = new_delete_t::new_node ();
			BREAK_LOOP_CONDITION_SETS (null == new_node_ptr, status, PFX_STATUS_MEM_LOW);

			*new_node_ptr = *(cur_node_ptr);
			add_node_ptr = insert_t::add_node (root_dec_ptr, new_node_ptr, status);

			if (null == add_node_ptr)
			{
				new_delete_t::delete_node (new_node_ptr);
				BREAK_LOOP (status, PFX_STATUS_FAIL);
			}

			if (cur_node_ptr == iterator_end_ptr->m_cur_node_ptr)
			{
				BREAK_LOOP (status,PFX_STATUS_OK);
			}
			else
			{
				continue;
			}
		}

	}while (1);

	if (PFX_STATUS_OK > status)
	{
		clean_t::clean (root_dec_ptr);
	}

	return status;
}

//////////////////////////////////////////////////////////////////////////
PECKER_END

#endif			//PFX_CBST_CODES_H_
