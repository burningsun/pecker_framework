/*
* pfx_ctst_codes.h
*
*  Created on: 2015-2-3
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_CTST_CODES_H_
#define		PFX_CTST_CODES_H_

#include "pfx_ctst.h"

#define PFX_CTST_MINMAX_TEMPLATE_DEFINES template < class __BST_node_minmax >
#define PFX_CTST_MINMAX				TST_node_minmax< __BST_node_minmax >
#define PFX_CTST_MINMAX_TYPE	typename TST_node_minmax< __BST_node_minmax >

#define PFX_CTST_INIT_TEMPLATE_DEFINES template < class __BST_node_init >
#define PFX_CTST_INIT						TST_node_init< __BST_node_init	>
#define PFX_CTST_INIT_TYPE			typename TST_node_init< __BST_node_init	>

#define PFX_CTST_STR_FIND_NODE_TEMPLATE_DEFINES template < class __BST_find_string_node >
#define PFX_CTST_STR_FIND_NODE	            TST_find_string_node < __BST_find_string_node >
#define PFX_CTST_STR_FIND_NODE_TYPE		typename TST_find_string_node < __BST_find_string_node >

#define PFX_CTST_INSERT_TEMPLATE_DEFINES template < class __find_same_string, class __BST_insert_node >
#define PFX_CTST_INSERT						TST_insert_node< __find_same_string, __BST_insert_node >
#define PFX_CTST_INSERT_TYPE				typename TST_insert_node< __find_same_string, __BST_insert_node >

#define PFX_CTST_RM_TEMPLATE_DEFINES template <  class __BST_node_remove >
#define PFX_CTST_RM						TST_node_remove< __BST_node_remove	>
#define PFX_CTST_RM_TYPE				typename TST_node_remove< __BST_node_remove >	


//////////////////////////////////////////////////////////////////////////
#define PFX_CTST_INS_RM_TEMPLATE_DEFINES template < class __BST_new_delete, class __find_same_string, class __BST_insert_node, class __BST_node_remove >
#define PFX_CTST_INS_RM                 TST_node_insert_remove < __BST_new_delete, __find_same_string, __BST_insert_node, __BST_node_remove > 
#define PFX_CTST_INS_RM_TYPE            typename TST_node_insert_remove < __BST_new_delete, __find_same_string, __BST_insert_node, __BST_node_remove > 

PECKER_BEGIN

//////////////////////////////////////////////////////////////////////////
// 最大最小值
PFX_CTST_MINMAX_TEMPLATE_DEFINES
PFX_INLINE const PFX_CTST_MINMAX_TYPE::node_t  PFX_CTST_MINMAX::min_node
(const PFX_CTST_MINMAX_TYPE::node_t* root_node_ptr,
const PFX_CTST_MINMAX_TYPE::node_t* null_node_ptr /* = null */)
{
	typedef PFX_CTST_MINMAX_TYPE::node_t       node_t;
	typedef PFX_CTST_MINMAX_TYPE::bst_minmax_t bst_minmax_t;

	const node_t* node_ptr;
	const node_t* mid_node_ptr;
	
	node_ptr = bst_minmax_t::min_node(root_node_ptr, null_node_ptr);
	

	while (node_ptr && 
		   null_node_ptr != node_ptr)
	{ 
		mid_node_ptr = node_ptr->get_middle_node ();

		if (mid_node_ptr && null_node_ptr != mid_node_ptr)
		{
			node_ptr = bst_minmax_t::min_node(mid_node_ptr,
				null_node_ptr);
		}
		else
		{
			break;
		}

	}

	return node_ptr;
}

PFX_CTST_MINMAX_TEMPLATE_DEFINES
PFX_INLINE const PFX_CTST_MINMAX_TYPE::node_t  PFX_CTST_MINMAX::max_node
(const PFX_CTST_MINMAX_TYPE::node_t* root_node_ptr,
const PFX_CTST_MINMAX_TYPE::node_t* null_node_ptr /* = null */)
{
	typedef PFX_CTST_MINMAX_TYPE::node_t       node_t;
	typedef PFX_CTST_MINMAX_TYPE::bst_minmax_t bst_minmax_t;

	const node_t* node_ptr;
	const node_t* mid_node_ptr;

	node_ptr = bst_minmax_t::max_node(root_node_ptr, null_node_ptr);


	while (node_ptr &&
		null_node_ptr != node_ptr)
	{
		mid_node_ptr = node_ptr->get_middle_node();

		if (mid_node_ptr && null_node_ptr != mid_node_ptr)
		{
			node_ptr = bst_minmax_t::max_node(mid_node_ptr,
				null_node_ptr);
		}
		else
		{
			break;
		}

	}

	return node_ptr;
}

PFX_CTST_MINMAX_TEMPLATE_DEFINES
PFX_INLINE PFX_CTST_MINMAX_TYPE::node_t* PFX_CTST_MINMAX::min_node
( PFX_CTST_MINMAX_TYPE::node_t* root_node_ptr,
 const PFX_CTST_MINMAX_TYPE::node_t* null_node_ptr /* = null */)
{
	typedef PFX_CTST_MINMAX_TYPE::node_t       node_t;
	return (node_t*)min_node((const node_t*)root_node_ptr, null_node_ptr);
}

PFX_CTST_MINMAX_TEMPLATE_DEFINES
PFX_INLINE PFX_CTST_MINMAX_TYPE::node_t* PFX_CTST_MINMAX::max_node
(PFX_CTST_MINMAX_TYPE::node_t* root_node_ptr,
PFX_INLINE const PFX_CTST_MINMAX_TYPE::node_t* null_node_ptr /* = null */)
{
	typedef PFX_CTST_MINMAX_TYPE::node_t       node_t;
	return (node_t*)max_node((const node_t*)root_node_ptr, null_node_ptr);
}

//////////////////////////////////////////////////////////////////////////
//
// 基本初始化
PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::init_node_leaves
(PFX_CTST_INIT_TYPE::node_t* PARAM_INOUT tree_node_ptr,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN left_node_ptr /* = null */,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN right_node_ptr /* = null */,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN parent_node_ptr /* = null */,
bool    init_mid_channal /*= true*/,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN mid_parent_node_ptr /* = null */,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN mid_leaf_node_ptr /* = null */)
{
	typedef PFX_CTST_INIT_TYPE::bst_init_t 	bst_init_t;

	result_t status_ = bst_init_t::init_node_leaves(tree_node_ptr,
		left_node_ptr, right_node_ptr, parent_node_ptr);

	if (PFX_STATUS_OK == status_)
	{
		if (init_mid_channal)
		{
			tree_node_ptr->set_mid_parent_node(mid_parent_node_ptr);
			tree_node_ptr->set_mid_leaf_node(mid_leaf_node_ptr);
		}
	}
	return status_;
}

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::init_node_leaves(
PFX_CTST_INIT_TYPE::node_t& PARAM_INOUT tree_node,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN left_node_ptr /* = null */,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN right_node_ptr /* = null */,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN parent_node_ptr /* = null */,
bool    init_mid_channal /*= true*/,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN mid_parent_node_ptr /* = null */,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN mid_leaf_node_ptr /* = null */)
{
	typedef PFX_CTST_INIT_TYPE::bst_init_t 	bst_init_t;

	result_t status_ = bst_init_t::init_node_leaves(tree_node,
		left_node_ptr, right_node_ptr, parent_node_ptr);

	if (PFX_STATUS_OK == status_)
	{
		if (init_mid_channal)
		{
			tree_node.set_mid_parent_node(mid_parent_node_ptr);
			tree_node.set_mid_leaf_node(mid_leaf_node_ptr);
		}
	}
	return status_;
}

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::set_middle_node(
PFX_CTST_INIT_TYPE::node_t* PARAM_INOUT tree_node_ptr,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN mid_leaf_node_ptr /* = null */)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_mid_leaf_node(mid_leaf_node_ptr);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::set_middle_node(
PFX_CTST_INIT_TYPE::node_t& PARAM_INOUT tree_node,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN mid_leaf_node_ptr /* = null */)
{
	tree_node.set_mid_leaf_node(mid_leaf_node_ptr);
	return PFX_STATUS_OK;
}  

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::set_middle_parent_node(
PFX_CTST_INIT_TYPE::node_t* PARAM_INOUT tree_node_ptr,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN mid_parent_node_ptr /* = null */)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_mid_parent_node(mid_leaf_node_ptr);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::set_middle_parent_node(
PFX_CTST_INIT_TYPE::node_t& PARAM_INOUT tree_node,
PFX_CTST_INIT_TYPE::node_t* PARAM_IN mid_parent_node_ptr /* = null */)
{
	tree_node.set_mid_parent_node(mid_leaf_node_ptr);
	return PFX_STATUS_OK;
}

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::set_null_element_node(
PFX_CTST_INIT_TYPE::node_t* PARAM_INOUT tree_node_ptr, bool enable)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_null_element_flag(enable);
		status_ = PFX_STATUS_OK;
	}
	return status_;
} 

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::set_null_element_node(
PFX_CTST_INIT_TYPE::node_t& PARAM_INOUT tree_node, bool enable)
{
	tree_node.set_null_element_flag(enable);
	return PFX_STATUS_OK;
}


PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE bool PFX_CTST_INIT::is_leaf_node(
const PFX_CTST_INIT_TYPE::node_t* PARAM_IN tree_node_ptr)
{
	if (null == tree_node_ptr)
	{
		return true;
	}
	else if (null == tree_node_ptr->get_left_node() &&
		null == tree_node_ptr->get_right_node() &&
		null == tree_node_ptr->get_middle_node())
	{
		return true;
	}
	else
	{
		return false;
	}
}

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE bool PFX_CTST_INIT::is_null_elem_node(
const PFX_CTST_INIT_TYPE::node_t* PARAM_IN tree_node_ptr)
{
	if (null == tree_node_ptr || tree_node_ptr->get_null_flag())
	{
		return true
	}
	else
	{
		return false;
	}
}


PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::set_node_string(
PFX_CTST_INIT_TYPE::node_t* PARAM_INOUT tree_node_ptr,
const PFX_CTST_INIT_TYPE::key_char_t* PARAM_IN str_ptr,
usize__t str_size)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		status_ = tree_node_ptr->set_string(str_ptr, str_size);
	}
	return status_;
}

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INIT::set_node_string(node_t& PARAM_INOUT tree_node,
const key_char_t* PARAM_IN str_ptr,
usize__t str_size)
{
	return tree_node.set_string(str_ptr, str_size);
}

PFX_CTST_INIT_TEMPLATE_DEFINES
PFX_INLINE  PFX_CTST_INIT_TYPE::node_t* PFX_CTST_INIT::sepreate_node(
PFX_CTST_INIT_TYPE::node_t* PARAM_INOUT node_ptr,
PFX_CTST_INIT_TYPE::node_t* PARAM_OUT sub_node_ptr,
usize__t chars_offset,
result_t& PARAM_OUT status_)
{
	typedef PFX_CTST_INIT_TYPE::node_t node_t;
	status_ = PFX_STATUS_INVALID_PARAMS;
	RETURN_INVALID_RESULT(null == node_ptr || null == sub_node_ptr, null);

	return node_ptr->sepreate_node(sub_node_ptr, chars_offset, status_);
	//if (null == node_ptr->get_left_node() && 
	//	null == node_ptr->get_right_node() &&
	//	null == node_ptr->get_parent_node())
	//{
	//	node_t* last_node_ptr = node_ptr->sepreate_node_remain_r(sub_node_ptr, 
	//		chars_offset, 
	//		status_);

	//	node_ptr = sub_node_ptr;
	//	return last_node_ptr;
	//}
	//else
	//{
	//	return node_ptr->sepreate_node_remain_l(sub_node_ptr, chars_offset, status_);
	//}

}

//////////////////////////////////////////////////////////////////////////
//
// 通过字符串查找迭节点
PFX_CTST_STR_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CTST_STR_FIND_NODE::find_node(
const PFX_CTST_STR_FIND_NODE_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count,
const PFX_CTST_STR_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr)
{
	typedef PFX_CTST_STR_FIND_NODE_TYPE::key_char_t 	key_char_t;
	typedef PFX_CTST_STR_FIND_NODE_TYPE::node_t         node_t;
	typedef PFX_CTST_STR_FIND_NODE_TYPE::find_string_t  find_string_t;
	
	const node_t* find_node_ptr = root_node_ptr
	int same_count = 0;
	while (find_node_ptr)
	{
		same_count = 0;
		int cmp_result = find_string_t::same_string(find_node_ptr->get_string_buffer(),
			find_node_ptr->get_string_buffer_size(),
			__chars_ptr, chars_count, same_count);

		chars_count -= same_count;
		__chars_ptr += same_count;

		if (find_node_ptr->get_string_buffer_size() == same_count)
		{
			if (chars_count)
			{
				find_node_ptr = find_node_ptr->get_middle_node();
				continue;
			}
			else
			{
				break;
			}
		}

		if (same_count > 0)
		{
			find_node_ptr = null; 
			break;
		}

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


PFX_CTST_STR_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CTST_STR_FIND_NODE::find_near_node(
const PFX_CTST_STR_FIND_NODE_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count,
const PFX_CTST_STR_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr,
usize__t& PARAM_OUT __match_count,
usize__t& PARAM_OUT last_node_match_count,
int& PARAM_INOUT last_cmp_result)
{
	
	typedef PFX_CTST_STR_FIND_NODE_TYPE::key_char_t 	key_char_t;
	typedef PFX_CTST_STR_FIND_NODE_TYPE::node_t         node_t;
	typedef PFX_CTST_STR_FIND_NODE_TYPE::find_string_t  find_string_t;

	const node_t* find_node_ptr = root_node_ptr;
	const node_t* traved_node_ptr = root_node_ptr;
	int cmp_result = 0;
	usize__t same_count = 0;
	usize__t match_count = 0;

	last_node_match_count = 0;

	while (find_node_ptr && chars_count)
	{
		same_count = 0;
		cmp_result = find_string_t::same_string(find_node_ptr->get_string_buffer(),
			find_node_ptr->get_string_buffer_size(),
			__chars_ptr, chars_count, same_count);

		traved_node_ptr = find_node_ptr;

		chars_count -= same_count;
		__chars_ptr += same_count;

		if (find_node_ptr->get_string_buffer_size() == same_count)
		{
			match_count += same_count;
			if (chars_count)
			{
				find_node_ptr = find_node_ptr->get_middle_node();

				if (null == find_node_ptr)
				{
					cmp_result = 0;
					break;
				}

				continue;
			}
			else
			{
				last_node_match_count = same_count;
				break;
			}
		}

		if (same_count > 0)
		{	
			cmp_result = 0;
			match_count += same_count;
			last_node_match_count = same_count;
			break;
		}

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
	last_cmp_result = cmp_result;

	return traved_node_ptr;
}


PFX_CTST_STR_FIND_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CTST_STR_FIND_NODE::find_last_same_node(
const PFX_CTST_STR_FIND_NODE_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count,
const PFX_CTST_STR_FIND_NODE_TYPE::node_t* PARAM_IN root_node_ptr,
usize__t& PARAM_OUT   __match_count,
usize__t& PARAM_INOUT lastnode_match_count,
int& PARAM_INOUT last_cmp_result)
{
	typedef PFX_CTST_STR_FIND_NODE_TYPE::key_char_t 	key_char_t;
	typedef PFX_CTST_STR_FIND_NODE_TYPE::node_t         node_t;
	typedef PFX_CTST_STR_FIND_NODE_TYPE::find_string_t  find_string_t;

	const node_t* find_node_ptr = root_node_ptr;
	const node_t* traved_node_ptr = root_node_ptr;
	int cmp_result = 0;
	usize__t same_count = 0;
	usize__t match_count = 0;

	lastnode_match_count = 0;

	while (find_node_ptr && chars_count)
	{
		same_count = 0;
		cmp_result = find_string_t::same_string(find_node_ptr->get_string_buffer(),
			find_node_ptr->get_string_buffer_size(),
			__chars_ptr, chars_count, same_count);

		chars_count -= same_count;
		__chars_ptr += same_count;

		if (find_node_ptr->get_string_buffer_size() == same_count)
		{
			traved_node_ptr = find_node_ptr;
			match_count += same_count;
			if (chars_count)
			{
				find_node_ptr = find_node_ptr->get_middle_node();
				continue;
			}
			else
			{
				lastnode_match_count = same_count;
				break;
			}
		}

		if (same_count > 0)
		{
			cmp_result = 0;
			match_count += same_count;
			lastnode_match_count = same_count;
			traved_node_ptr = find_node_ptr;
			break;
		}

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
	__match_count = match_count;
	last_cmp_result = cmp_result;

	return traved_node_ptr;
}



PFX_CTST_INSERT_TEMPLATE_DEFINES
PFX_INLINE const PFX_CTST_INSERT_TYPE::node_t* PFX_CTST_INSERT::add_node(
const PFX_CTST_INSERT_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count,
PFX_CTST_INSERT_TYPE::node_t*& PARAM_INOUT root_node_ptr,
PFX_CTST_INSERT_TYPE::node_t* PARAM_INOUT add_node_ptr,
usize__t& PARAM_OUT match_count,
usize__t& PARAM_OUT last_node_match,
result_t& PARAM_OUT status_)
{
	typedef PFX_CTST_INSERT_TYPE::node_t node_t;
	typedef PFX_CTST_INSERT_TYPE::key_char_t key_char_t;
	typedef PFX_CTST_INSERT_TYPE::find_t  find_t;
	typedef PFX_CTST_INSERT_TYPE::bst_insert_t bst_insert_t;
	typedef PFX_CTST_INSERT_TYPE::init_t       init_t;

	const node_t* retn_node_ptr = null;
	if (null == root_node_ptr)
	{
		FOR_ONE_LOOP_BEGIN
		status_ = init_t::set_node_string(add_node_ptr, 
			__chars_ptr, chars_count);
		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status_);
		retn_node_ptr = bst_insert_t::add_node(root_node_ptr,
			add_node_ptr, 
			status_);
		FOR_ONE_LOOP_END
		return retn_node_ptr;
	}

	int last_cmp_result = 0;
	const node_t* find_insert_node_ptr =
		find_t::find_last_same_node(__chars_ptr, chars_count, root_node_ptr,
		match_count, last_node_match, last_cmp_result);

	FOR_ONE_LOOP_BEGIN
	usize__t new_node_str_size = chars_count - match_count;
	if (new_node_str_size > 0)
	{
		BREAK_LOOP_CONDITION_SETS(null == find_insert_node_ptr, 
			status_, 
			PFX_STATUS_MEM_ERR);
	}
	else
	{
		BREAK_LOOP_CONDITION_SETS(
			find_insert_node_ptr->get_string_buffer_size() >
			last_node_match,
			status_,
			last_node_match);
		BREAK_LOOP_CONDITION_SETS(
			find_insert_node_ptr->get_string_buffer_size() <
			last_node_match,
			status_,
			PFX_STATUS_MEM_ERR);

		retn_node_ptr = find_insert_node_ptr;
		BREAK_LOOP(status_, PFX_STATUS_UNIQUE);
	}

	if (last_node_match > 0)
	{
		BREAK_LOOP_CONDITION_SETS(
			find_insert_node_ptr->get_string_buffer_size() >
			last_node_match,
			status_,
			last_node_match);
		BREAK_LOOP_CONDITION_SETS(
			find_insert_node_ptr->get_string_buffer_size() <
			last_node_match,
			status_,
			PFX_STATUS_MEM_ERR);
	}

	node_t* tmp_node_ptr = (node_t*)find_insert_node_ptr;
	node_t*& mid_root_ptr = tmp_node_ptr->get_middle_node_ref();
	
	key_char_t* new_node_str_ptr = __chars_ptr + match_count;
	status_ = init_t::set_node_string(add_node_ptr,
		new_node_str_ptr, new_node_str_size);

	BREAK_LOOP_CONDITION(PFX_STATUS_OK != status_);

	status_ = init_t::set_middle_parent_node(add_node_ptr, tmp_node_ptr);
	BREAK_LOOP_CONDITION(PFX_STATUS_OK != status_);

	retn_node_ptr = bst_insert_t::add_node(mid_root_ptr,
		add_node_ptr,
		status_);

	FOR_ONE_LOOP_END
		
	return retn_node_ptr;
}


PFX_CTST_RM_TEMPLATE_DEFINES
PFX_INLINE PFX_CTST_RM_TYPE::node_t* PFX_CTST_RM::remove_node(
PFX_CTST_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
PFX_CTST_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
result_t& __status)
{
	typedef PFX_CTST_RM_TYPE::node_t       node_t;
	typedef PFX_CTST_RM_TYPE::bst_remove_t bst_remove_t;
	typedef PFX_CTST_RM_TYPE::init_t       init_t;

	RETURN_INVALID_RESULT(null == root_node_ptr || null == remove_node_ptr,
		PFX_STATUS_INVALID_PARAMS);

	if (null != remove_node_ptr->get_middle_node())
	{
		if (!init_t::is_null_elem_node(remove_node_ptr))
		{
			init_t::set_null_element_node(remove_node_ptr, true);
		}
		__status = PFX_STATUS_SUCCESS;
		return remove_node_ptr;
	}
										  
	if (null == remove_node_ptr->get_middle_parent_node())
	{
		return bst_remove_t::remove_node(root_node_ptr, remove_node_ptr, status_);	
	}
	else
	{
		node_t* tmp_root_ptr = remove_node_ptr->get_middle_parent_node_ref();
		node_t*& mid_root_node_ptr = tmp_root_ptr->get_middle_node_ref();
		return bst_remove_t::remove_node(mid_root_node_ptr, remove_node_ptr, status_);
	}


}

PFX_CTST_RM_TEMPLATE_DEFINES
PFX_INLINE PFX_CTST_RM_TYPE::node_t* PFX_CTST_RM::remove_next(
PFX_CTST_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
PFX_CTST_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
result_t& __status)
{
	typedef PFX_CTST_RM_TYPE::node_t       node_t;
	typedef PFX_CTST_RM_TYPE::bst_remove_t bst_remove_t;
	typedef PFX_CTST_RM_TYPE::init_t       init_t;

	RETURN_INVALID_RESULT(null == root_node_ptr || null == remove_node_ptr,
		PFX_STATUS_INVALID_PARAMS);

	if (null == remove_node_ptr->get_middle_parent_node())
	{
		__status = PFX_STATUS_OK;
		return null;
	}

	node_t* tmp_parent_ptr = remove_node_ptr->get_middle_parent_node_ref();
	if (null == tmp_parent_ptr->get_middle_node())
	{
		return remove_node(root_node_ptr, tmp_parent_ptr);
	}
	else
	{
		__status = PFX_STATUS_OK;
		return null;
	}
}


//////////////////////////////////////////////////////////////////////////
PFX_CTST_INS_RM_TEMPLATE_DEFINES
PFX_INLINE const PFX_CTST_INS_RM_TYPE::node_t* PFX_CTST_INS_RM::add_node(
const PFX_CTST_INS_RM_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count,
PFX_CTST_INS_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
PFX_CTST_INS_RM_TYPE::node_t* PARAM_INOUT add_node_ptr,
result_t& PARAM_OUT status_)
{
	typedef PFX_CTST_INS_RM_TYPE::insert_t     insert_t;
	typedef PFX_CTST_INS_RM_TYPE::node_t       node_t;
	typedef PFX_CTST_INS_RM_TYPE::new_delete_t new_delete_t;
	typedef PFX_CTST_INS_RM_TYPE::init_t       init_t;

	usize__t match_count = 0;
	usize__t last_node_match_count = 0;
	const node_t* inserted_node_ptr = insert_t::add_node(__chars_ptr,
		chars_count, root_node_ptr, add_node_ptr,
		match_count,
		last_node_match_count,
		status_);

	RETURN_RESULT((PFX_STATUS_OK == status_ ||
		PFX_STATUS_UNIQUE == status_), inserted_node_ptr);

	RETURN_INVALID_RESULT(PFX_STATUS_MEM_ERR == status_, null);
	RETURN_INVALID_RESULT(status_ < PFX_STATUS_OK || 
		status_ != last_node_match_count, null);

	status_ = PFX_STATUS_MEM_ERR;
	RETURN_INVALID_RESULT(null == inserted_node_ptr, null);
	RETURN_INVALID_RESULT(0 >= last_node_match_count, null);

	FOR_ONE_LOOP_BEGIN

	node_t* new_node_ptr = new_delete_t::new_node();
	//status_ = init_t::init_node_leaves(new_node_ptr);
	//BREAK_LOOP_CONDITION(PFX_STATUS_OK != status_);
	BREAK_LOOP_CONDITION_SETS(null == new_node_ptr, status_, PFX_STATUS_MEM_LOW);

	node_t* to_seperate_node_ptr = (node_t*)inserted_node_ptr;
	inserted_node_ptr = null;

	node_t*	last_seperate_node_ptr = init_t::sepreate_node(to_seperate_node_ptr,
		new_node_ptr, last_node_match_count, status_);

	BREAK_LOOP_CONDITION_ACT(PFX_STATUS_OK != status_,
	if (new_node_ptr)
	{
		new_delete_t::delete_node(new_node_ptr);
		new_node_ptr = null;
	}
	);

	if (last_seperate_node_ptr == new_node_ptr)
	{
		status_ = init_t::set_null_element_node(to_seperate_node_ptr, true);
	}
	else if (last_seperate_node_ptr == to_seperate_node_ptr)
	{
		status_ = init_t::set_null_element_node(new_node_ptr, true);
	}
	else
	{
		status_ = PFX_STATUS_MEM_ERR;
	}

	BREAK_LOOP_CONDITION_ACT(PFX_STATUS_OK != status_,
	if (new_node_ptr)
	{
		new_delete_t::delete_node(new_node_ptr);
		new_node_ptr = null;
	}
	);

	inserted_node_ptr = insert_t::add_node(__chars_ptr,
		chars_count, root_node_ptr, add_node_ptr,
		match_count,
		last_node_match_count,
		status_);

	FOR_ONE_LOOP_END

	return inserted_node_ptr;
}

PFX_CTST_INS_RM_TEMPLATE_DEFINES
PFX_INLINE const PFX_CTST_INS_RM_TYPE::node_t* PFX_CTST_INS_RM::add_node(
PFX_CTST_INS_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
PFX_CTST_INS_RM_TYPE::node_t* PARAM_INOUT add_node_ptr,
result_t& PARAM_OUT status_)
{
	status_ = PFX_STATUS_INVALID_PARAMS;
	RETURN_INVALID_RESULT(null == add_node_ptr, null);

	return add_node(add_node_ptr->get_string_buffer(),
		add_node_ptr->get_string_buffer_size(),
		root_node_ptr,
		add_node_ptr,
		status_);
	
}

PFX_CTST_INS_RM_TEMPLATE_DEFINES
PFX_INLINE PFX_CTST_INS_RM_TYPE::node_t* PFX_CTST_INS_RM::remove_node(
PFX_CTST_INS_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
PFX_CTST_INS_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
result_t& __status)
{
	typedef PFX_CTST_INS_RM_TYPE::remove_t remove_t;
	return remove_t::remove_node(root_node_ptr, remove_node_ptr, __status);
}

PFX_CTST_INS_RM_TEMPLATE_DEFINES
PFX_INLINE PFX_CTST_INS_RM_TYPE::node_t* PFX_CTST_INS_RM::remove_node(
const PFX_CTST_INS_RM_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count, 
PFX_CTST_INS_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
result_t& PARAM_OUT status_)
{
	typedef  PFX_CTST_INS_RM_TYPE::node_t   node_t;
	typedef  PFX_CTST_INS_RM_TYPE::remove_t remove_t;
	typedef  PFX_CTST_INS_RM_TYPE::find_t   find_t;

	node_t* find_node_ptr = (node_t*)find_t::find_node(__chars_ptr, chars_count, root_node_ptr);

	if (find_node_ptr)
	{
		return remove_t::remove_node(root_node_ptr, find_node_ptr, __status);
	}
	else
	{
		__status = PFX_STATUS_NOT_EXISTS;
		return null;
	}
	
}

PFX_CTST_INS_RM_TEMPLATE_DEFINES
PFX_INLINE PFX_CTST_INS_RM_TYPE::node_t* PFX_CTST_INS_RM::remove_next(
PFX_CTST_INS_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr,
PFX_CTST_INS_RM_TYPE::node_t* PARAM_INOUT remove_node_ptr,
result_t& __status)
{
	typedef PFX_CTST_INS_RM_TYPE::remove_t remove_t;
	return remove_t::remove_next(root_node_ptr, remove_node_ptr, __status);
}

PFX_CTST_INS_RM_TEMPLATE_DEFINES
PFX_INLINE result_t  PFX_CTST_INS_RM::release_nodes(node_t*& PARAM_INOUT root_node_ptr,
node_t*& PARAM_INOUT remove_node_ptr)
{
	typedef PFX_CTST_INS_RM_TYPE::node_t       node_t;
	typedef PFX_CTST_INS_RM_TYPE::new_delete_t new_delete_t;
	typedef PFX_CTST_INS_RM_TYPE::remove_t     remove_t;

	node_t* removed_node_ptr = remove_t::remove_next(root_node_ptr, remove_node_ptr, __status);
	
	if (remove_node_ptr)
	{
		new_delete_t::delete_node(remove_node_ptr);
		remove_node_ptr = null;
	}

	while (removed_node_ptr && PFX_STATUS_OK == __status)
	{
		node_t* next_removed_node_ptr = remove_t::remove_next(root_node_ptr, 
			removed_node_ptr, __status);
		new_delete_t::delete_node(removed_node_ptr);
		removed_node_ptr = next_removed_node_ptr;
	}

	return __status;
	
}

PFX_CTST_INS_RM_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CTST_INS_RM::release_nodes(
const PFX_CTST_INS_RM_TYPE::key_char_t* PARAM_IN __chars_ptr,
usize__t chars_count,
PFX_CTST_INS_RM_TYPE::node_t*& PARAM_INOUT root_node_ptr)
{
	typedef  PFX_CTST_INS_RM_TYPE::node_t   node_t;
	result_t __status;
	node_t* remove_node_ptr = remove_node(__chars_ptr, chars_count, root_node_ptr, __status);
	if (PFX_STATUS_OK == __status)
	{
		return release_nodes(root_node_ptr, remove_node_ptr);
	}
	else
	{
		return __status;
	}
}


PECKER_END

#endif			//PFX_CTST_CODES_H_
