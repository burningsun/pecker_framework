/*
 * pfx_balance_tst_algorithm.cpp
 *
 *  Created on: 2013-10-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_balance_tst_algorithm.h"

#define BST_NODE_COV_TO_TST_NODE(X) ((tenary_tree_node_t*)(X))
#define LIST_NODE_COV_TO_TST_NODE(X) ((tenary_tree_node_t*)((X)-sizeof(tenary_blance_part)))

#define BST_NODE_COV_TO_CONST_TST_NODE(x) ((const tenary_tree_node_t*)(x))
#define LIST_NODE_COV_TO_CONST_TST_NODE(x) ((const tenary_tree_node_t*)((x)-sizeof(tenary_blance_part)))

//查找结点
const tenary_tree_node_t* find_node_form_tenary_tree (const tenary_tree_node_t* PARAM_IN proot_node,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method,
	const pfx_char_t* PARAM_IN pkey_string, 
	size_t char_size,
	size_t key_string_buffer_size)
{
	pfx_string_t temp_string;
	pfx_share_string_t temp_share_string;
	const binary_search_tree_node_t* pbst_node = null;
	const tenary_tree_node_t* preturn_tst_node = null;

	RETURN_INVALID_RESULT ((null == proot_node||null == ptenary_tree_method 
		|| null == pkey_string || 0 == key_string_buffer_size || 0 == char_size),null);

	init_string_direct_unsafe (&temp_string,char_size,(pfx_char_t*)pkey_string,key_string_buffer_size);
	init_share_string_direct_unsafe (&temp_share_string,&temp_string);

	pbst_node = find_node_form_binary_search_tree ((pfx_long_t)&(temp_share_string),
		(const binary_search_tree_node_t*)proot_node,
		ptenary_tree_method->m_find_cmp_method);

	preturn_tst_node = BST_NODE_COV_TO_CONST_TST_NODE (pbst_node);

	while (null != preturn_tst_node)
	{
		size_t search_str_size;
		size_t node_str_size;
		const linked_list_node_t* plist_node = &(preturn_tst_node->m_key_linked_node);
		if (null == plist_node->m_pnext_node)
		{
			break;
		}
		search_str_size = get_share_string_char_buffer_size (&temp_share_string);
		node_str_size = get_share_string_char_buffer_size ((const pfx_share_string_t*)&(preturn_tst_node->m_string_key));

		if (search_str_size >= node_str_size)
		{
			search_str_size -= node_str_size;
			resize_share_string_direct_unsafe_ownoffset (&temp_share_string,node_str_size,search_str_size);
		}
		else
		{
			break;
		}
		
		proot_node = LIST_NODE_COV_TO_TST_NODE (plist_node->m_pnext_node);

		pbst_node = find_node_form_binary_search_tree((pfx_long_t)&(temp_share_string),
			(const binary_search_tree_node_t*)proot_node,
			ptenary_tree_method->m_find_cmp_method);

		preturn_tst_node = BST_NODE_COV_TO_CONST_TST_NODE (pbst_node);
	}

	if (0 == get_share_string_char_buffer_size(&temp_share_string))
	{
		return preturn_tst_node;
	}
	else
	{
		return null;
	}
	
}
