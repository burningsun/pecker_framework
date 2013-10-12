/*
 * pfx_balance_tst_algorithm.cpp
 *
 *  Created on: 2013-10-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_balance_tst_algorithm.h"

#define BST_NODE_COV_TO_TST_NODE(X) ((tenary_tree_node_t*)(X))
//#define LIST_NODE_COV_TO_TST_NODE(X) ((tenary_tree_node_t*)((X)-sizeof(tenary_blance_part)))

#define BST_NODE_COV_TO_CONST_TST_NODE(x) ((const tenary_tree_node_t*)(x))
//#define LIST_NODE_COV_TO_CONST_TST_NODE(x) ((const tenary_tree_node_t*)((x)-sizeof(tenary_blance_part)))


PFX_INLINE_CODE const tenary_tree_node_t*  find_tenary_binary_node (const tenary_tree_node_t* PARAM_IN proot_node,
	pfx_share_string_t* PARAM_IN pkey_string,
	const tenary_tree_internal_method_t* ptenary_tree_method,
	pfx_nsize_t* psame_size,
	pfx_result_t* pstatus)
{
	const binary_search_tree_node_t* pbst_node = (const binary_search_tree_node_t*)proot_node;
	const binary_search_tree_node_t* preturn_node = null;
	int cmp_result = 0;
	while( null != pbst_node )
	{
		cmp_result = ptenary_tree_method->m_find_same_cmp_method (pkey_string,
			(const pfx_share_string_t*)pbst_node->m_key,psame_size);

		preturn_node = pbst_node;

		if (cmp_result < 0)
		{
			pbst_node = pbst_node->m_pleft_node;
		}
		else if (cmp_result > 0)
		{
			pbst_node = pbst_node->m_pright_node;
		}
		else
		{
			break;
		}
	}
	return BST_NODE_COV_TO_TST_NODE (preturn_node);
}


// 创建一个三叉树节点
tenary_tree_node_t* new_tenary_tree_node (size_t char_size,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method)
{
	tenary_tree_node_t* preturn_node = null;
	tenary_tree_node_t* ptmp_node = null;

	RETURN_INVALID_RESULT (null == ptenary_tree_method ||
		null == ptenary_tree_method->m_nodes_allocator || 
		ptenary_tree_method->m_defualt_cache_size > 0x3FFF,
		null);


	preturn_node = (tenary_tree_node_t*) ptenary_tree_method->m_nodes_allocator->allocate_obj 
		((pfx_long_t)(ptenary_tree_method->m_nodes_allocator),
		sizeof (tenary_tree_node_t) + ptenary_tree_method->m_defualt_cache_size);

	if (null == preturn_node)
	{
		return null;
	}

	ptmp_node = init_tenary_tree_node (preturn_node,char_size,ptenary_tree_method);

	if (null == ptmp_node)
	{
		ptenary_tree_method->m_nodes_allocator->dellocate_obj ((pfx_long_t)ptenary_tree_method->m_nodes_allocator,preturn_node);
		preturn_node = null;
	}

	return preturn_node;

}

// 删除三叉树节点的内存空间 (仅删内存，不涉及链表操作)
pfx_result_t delete_tenary_tree_node (tenary_tree_node_t* PARAM_INOUT pdel_node,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method)
{
	pfx_result_t status = PFX_STATUS_OK;

	RETURN_INVALID_RESULT (null == pdel_node || 
		null == ptenary_tree_method ||
		null == ptenary_tree_method->m_nodes_allocator ||
		null == ptenary_tree_method->m_key_string_allocator,
		PFX_STATUS_INVALID_PARAMS);

	status = clear_share_string((pfx_share_string_t*)&(pdel_node->m_string_key),ptenary_tree_method->m_key_string_allocator);
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	ptenary_tree_method->m_nodes_allocator->dellocate_obj ((pfx_long_t)(ptenary_tree_method->m_nodes_allocator),pdel_node);

	return PFX_STATUS_OK;
}


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
		//const linked_list_node_t* plist_node = &(preturn_tst_node->m_key_linked_node);
		const tenary_tree_node_t* plist_node = preturn_tst_node;
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
		
		//proot_node = LIST_NODE_COV_TO_TST_NODE (plist_node->m_pnext_node);
		proot_node = plist_node->m_pnext_node;

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

//插入节点
const tenary_tree_node_t* add_tenary_tree_node_unsafe (tenary_tree_node_t** PARAM_INOUT pproot_node,
	const tenary_tree_internal_method_t* ptenary_tree_method,
	const pfx_char_t* PARAM_IN pkey_string, 
	size_t char_size,
	size_t key_string_buffer_size,
	tenary_tree_node_t* PARAM_INOUT paddnode,	
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_string_t temp_string;
	pfx_share_string_t temp_share_string;

	tenary_tree_node_t* ptst_node = null;
	tenary_tree_node_t* proot_node;
	tenary_tree_node_t** pptemp_root_node;
	int cmp_result = 0;
	pfx_nsize_t same_size = 0;

	pfx_result_t status = PFX_STATUS_OK;

	RETURN_INVALID_BY_ACT_RESULT ((null == pproot_node||null == ptenary_tree_method 
		|| null == pkey_string || 0 == key_string_buffer_size || 0 == char_size),
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS),
		null);

	proot_node = *pproot_node;

	// 插入第一个节点
	if (null == proot_node)
	{
		pfx_share_string_t* pstring_key = null;
		//paddnode = init_tenary_tree_node_no_cache_change (paddnode,char_size);
		paddnode = init_tenary_tree_node_no_cache_change (paddnode,char_size,ptenary_tree_method);
		
		RETURN_INVALID_BY_ACT_RESULT (null == paddnode,
			SET_POINTER_VALUE(pstatus,PFX_STATUS_ERROR_),
			null);
		pstring_key = (pfx_share_string_t*)get_tenary_tree_node_string (paddnode);

		status = init_share_string_by_charsbuffer (pstring_key,
			pkey_string,
			key_string_buffer_size,
			ptenary_tree_method->m_key_string_allocator);

		RETURN_INVALID_BY_ACT_RESULT ((PFX_STATUS_OK != status),
			SET_POINTER_VALUE (pstatus,status),null);

		*pproot_node = paddnode;
		
		return paddnode;
	}

	// 初始化搜索字符串
	init_string_direct_unsafe (&temp_string,char_size,(pfx_char_t*)pkey_string,key_string_buffer_size);
	init_share_string_direct_unsafe (&temp_share_string,&temp_string);

	// 查找一个二叉节点
	pptemp_root_node = pproot_node;
	ptst_node = (tenary_tree_node_t*)find_tenary_binary_node(proot_node,&temp_share_string,ptenary_tree_method,&same_size,&status);

	//
	do 
	{
		size_t search_str_size;
		size_t node_str_size;

		// 从开头开始顺序数，存在字符相同就像等，第一个字符比较字符串大小
		// 按这样的规则出来，null == ptst_node 的时候必定是个二叉树节点
		if (null == ptst_node)
		{
			pfx_share_string_t* pstring_key = null;
			//paddnode = init_tenary_tree_node_no_cache_change (paddnode,char_size);
			paddnode = init_tenary_tree_node_no_cache_change(paddnode,char_size,ptenary_tree_method);

			RETURN_INVALID_BY_ACT_RESULT (null == paddnode,
				SET_POINTER_VALUE(pstatus,PFX_STATUS_ERROR_),
				null);
			pstring_key = (pfx_share_string_t*)get_tenary_tree_node_string (paddnode);

			status = init_share_string_by_charsbuffer (pstring_key,
				pkey_string,
				key_string_buffer_size,
				ptenary_tree_method->m_key_string_allocator);

			RETURN_INVALID_BY_ACT_RESULT ((PFX_STATUS_OK != status),
				SET_POINTER_VALUE (pstatus,status),null);

			ptst_node = (tenary_tree_node_t*)ptenary_tree_method->m_bst_add_method ((balance_bst_node_t**)pptemp_root_node,
				(balance_bst_node_t*)&paddnode,ptenary_tree_method->m_find_cmp_method,&status);

			if (PFX_STATUS_UNIQUE == status)
			{
				// 字符非法标识识别
				if (!check_binary_search_tree_node_valid((const binary_search_tree_node_t*)ptst_node))
				{
					set_binary_search_tree_node_valid((binary_search_tree_node_t*)ptst_node,pfx_true);
					return  ptst_node;
				}
				set_binary_search_tree_node_valid((binary_search_tree_node_t*)ptst_node,pfx_true);
				SET_POINTER_VALUE (pstatus,PFX_STATUS_UNIQUE);
				return ptst_node;
			}
			else if (PFX_STATUS_OK != status)
			{
				SET_POINTER_VALUE (pstatus,status);
				clear_share_string(pstring_key,ptenary_tree_method->m_key_string_allocator);
				return null;
			}

			if (null != *pptemp_root_node) 
			{
				ptst_node->m_prev_node = (*pptemp_root_node)->m_prev_node;
			}

			return ptst_node;
			//break;
		}


		search_str_size = get_share_string_char_buffer_size (&temp_share_string);
		node_str_size = get_share_string_char_buffer_size ((const pfx_share_string_t*)&(ptst_node->m_string_key));

		if (search_str_size == same_size)
		{
			// 相同字符数与字符长度相等且跟当前节点长度相等，则为已存在节点
			if (search_str_size == node_str_size)
			{
				// 字符非法标识识别
				if (!check_binary_search_tree_node_valid((const binary_search_tree_node_t*)ptst_node))
				{
					set_binary_search_tree_node_valid((binary_search_tree_node_t*)ptst_node,pfx_true);
					return BST_NODE_COV_TO_CONST_TST_NODE (ptst_node);
				}

				set_binary_search_tree_node_valid((binary_search_tree_node_t*)ptst_node,pfx_true);
				SET_POINTER_VALUE (pstatus,PFX_STATUS_UNIQUE);
				return ptst_node;
			}

			// 剩下的搜索字符串比节点字符串小，但相同字符个数与搜索字符串长度一样
			// 这时候需要对节点字符串进行前截断，节点分为2个结点
			if (search_str_size < node_str_size)
			{
				tenary_tree_node_t* ptemp_node = null;
				paddnode = init_tenary_tree_node_no_cache_change (paddnode,char_size,ptenary_tree_method);

				status = seprate_share_string_unsafe_to_new_begin ((pfx_share_string_t*)&ptst_node->m_string_key,
						same_size,
						(pfx_share_string_t*)&paddnode->m_string_key,sizeof (pfx_share_string_extern_t) + get_tenary_tree_node_cache_size(ptst_node));

				RETURN_INVALID_BY_ACT_RESULT (PFX_STATUS_OK != status,
					SET_POINTER_VALUE (pstatus,status),
					null);

				if (null != ptst_node->m_prev_node && 
					ptst_node->m_prev_node->m_pnext_node != ptst_node)
				{ // 非主干通道的链表关系
					paddnode->m_prev_node = ptst_node->m_prev_node;
					paddnode->m_pnext_node = ptst_node;
					ptst_node->m_prev_node = paddnode;
				}
				else 
				{ // 主干道的链表关系
					PFX_INSERT_LIST_NODE_BEGIN (ptst_node,paddnode,ptemp_node);
				}

				// 使用新的节点替代原有的节点
				status = replace_binary_node_direct_unsafe((binary_search_tree_node_t*)ptst_node,(binary_search_tree_node_t*)paddnode);
				
				RETURN_INVALID_BY_ACT_RESULT (PFX_STATUS_OK != status,
					SET_POINTER_VALUE (pstatus,status),
					null);

				// 原有节点的二叉树部分的指针强行设置为默认值
				ptenary_tree_method->m_bst_default_init_method ((balance_bst_node_t*)ptst_node);
				
				return paddnode;
			}

			// 
			SET_POINTER_VALUE (pstatus,PFX_STATUS_MEM_ERR);
			return null;
		}
		
		RETURN_INVALID_BY_ACT_RESULT ((search_str_size < same_size),
			SET_POINTER_VALUE (pstatus,PFX_STATUS_MEM_ERR),null);

		// 最蛋疼的情况,相同字符串数量介于搜索字符串与节点字符串长度之间，
		// 这时候需要将节点字符串分为2个结点，然后再插入新节点
		if (same_size != node_str_size)
		{
			tenary_tree_node_t* ptemp_node = null;
			tenary_tree_node_t* pnew_node;

			RETURN_INVALID_BY_ACT_RESULT (same_size > node_str_size || same_size > search_str_size,
				SET_POINTER_VALUE (pstatus,PFX_STATUS_MEM_ERR), null);

			pnew_node = new_tenary_tree_node (char_size,ptenary_tree_method);
			RETURN_INVALID_BY_ACT_RESULT (null == pnew_node,SET_POINTER_VALUE (pstatus,status),null);

			status = seprate_share_string_unsafe_to_new_begin ((pfx_share_string_t*)&ptst_node->m_string_key,
				same_size,
				(pfx_share_string_t*)&pnew_node->m_string_key,sizeof (pfx_share_string_extern_t) + get_tenary_tree_node_cache_size(ptst_node));

			if (PFX_STATUS_OK != status)
			{
				delete_tenary_tree_node (pnew_node,ptenary_tree_method);
				SET_POINTER_VALUE (pstatus,status);
				return null;
			}

			if (null != ptst_node->m_prev_node && 
				ptst_node->m_prev_node->m_pnext_node != ptst_node)
			{ // 非主干通道的链表关系
				pnew_node->m_prev_node = ptst_node->m_prev_node;
				pnew_node->m_pnext_node = ptst_node;
				ptst_node->m_prev_node = pnew_node;
			}
			else 
			{ // 主干道的链表关系
				PFX_INSERT_LIST_NODE_BEGIN (ptst_node,pnew_node,ptemp_node);
			}

			// 使用新的节点替代原有的节点
			status = replace_binary_node_direct_unsafe((binary_search_tree_node_t*)ptst_node,(binary_search_tree_node_t*)pnew_node);

			RETURN_INVALID_BY_ACT_RESULT (PFX_STATUS_OK != status,
				SET_POINTER_VALUE (pstatus,status),
				null);

			// 原有节点的二叉树部分的指针强行设置为默认值
			ptenary_tree_method->m_bst_default_init_method ((balance_bst_node_t*)ptst_node);

			// 将新节点设置为无效节点，因为该节点不存在元素
			set_binary_search_tree_node_valid ((binary_search_tree_node_t*)pnew_node,pfx_false);

			// 更新新的搜索字符串
			resize_share_string_direct_unsafe_ownoffset (&temp_share_string,same_size, (search_str_size - same_size));

			pptemp_root_node = &pnew_node->m_pnext_node;
			proot_node = pnew_node->m_pnext_node;
			// 因为新的ptst_node与剩下的搜索字符串100%不相同，
			// 所以搜索结果肯定有ptst_node = null;

			ptst_node = null;
			continue;
		}

		// 更新新的搜索字符串
		if (search_str_size > node_str_size)
		{
			search_str_size -= node_str_size;
			resize_share_string_direct_unsafe_ownoffset (&temp_share_string,node_str_size,search_str_size);
		}

		// 搜索字符串长度不为0，但节点没有后续节点了
		// 这时候，新增节点为ptst_node的中节点（m_pnext_node）
		if (null == ptst_node->m_pnext_node)
		{
			tenary_tree_node_t* ptemp_node = null;
			paddnode = init_tenary_tree_node_no_cache_change (paddnode,char_size,ptenary_tree_method);
			
			status = init_share_string_by_charsbuffer ((pfx_share_string_t*)&paddnode->m_string_key,
				get_share_string_chars_buffer (&temp_share_string),
				get_share_string_char_buffer_size (&temp_share_string),
				ptenary_tree_method->m_key_string_allocator);

			SET_POINTER_VALUE (pstatus,status);

			RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

			PFX_INSERT_LIST_NODE_END (ptst_node,paddnode,ptemp_node);
			
			return paddnode;
		}

		// 继续往下查找
		pptemp_root_node = &ptst_node->m_pnext_node;
		proot_node = ptst_node->m_pnext_node;
		ptst_node = (tenary_tree_node_t*)find_tenary_binary_node(proot_node,&temp_share_string,ptenary_tree_method,&same_size,&status);

	} while (1);
	
	SET_POINTER_VALUE (pstatus,PFX_STATUS_ERROR_);
	return null;
}


//移除节点
const tenary_tree_node_t* remove_tenary_tree_node_unsafe (tenary_tree_node_t** PARAM_INOUT pproot_node,
	const tenary_tree_internal_method_t* ptenary_tree_method,
	tenary_tree_node_t* PARAM_INOUT premove_node,	
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_result_t status = PFX_STATUS_OK;
	pfx_bool_t	is_leaf = pfx_false;
	tenary_tree_node_t* proot_node;
	tenary_tree_node_t* ptemp_node;
	tenary_tree_node_t* ptemp_next_remove_node = null;

	RETURN_INVALID_BY_ACT_RESULT ((null == pproot_node||null == ptenary_tree_method 
		|| null == premove_node || null == *pproot_node),
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS),
		null);

	proot_node = *pproot_node;
	ptemp_node = premove_node;
	
	do
	{
		ptemp_next_remove_node = ptemp_node->m_prev_node;
		is_leaf = check_binary_search_tree_leaf_node_unsafe ((binary_search_tree_node_t*)ptemp_node);

		if (null != ptemp_next_remove_node)
		{
			RETURN_INVALID_BY_ACT_RESULT (null == ptemp_next_remove_node->m_pnext_node,
				SET_POINTER_VALUE (pstatus,PFX_STATUS_MEM_ERR), null);

			ptemp_node = (tenary_tree_node_t*) ptenary_tree_method->m_bst_remove_method (
				(balance_bst_node_t**)&(ptemp_next_remove_node->m_pnext_node),
				(balance_bst_node_t*)ptemp_node,ptenary_tree_method->m_find_cmp_method,&status);

			RETURN_INVALID_BY_ACT_RESULT (PFX_STATUS_OK != status,
				SET_POINTER_VALUE (pstatus,status),null);
		}
		else
		{
			RETURN_INVALID_BY_ACT_RESULT (null != proot_node->m_prev_node,
				SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_OPERATION),
				null);

			ptemp_node = (tenary_tree_node_t*) ptenary_tree_method->m_bst_remove_method ((balance_bst_node_t**)pproot_node,
				(balance_bst_node_t*)ptemp_node,ptenary_tree_method->m_find_cmp_method,&status);

			RETURN_INVALID_BY_ACT_RESULT (PFX_STATUS_OK != status,
				SET_POINTER_VALUE (pstatus,status),null);
		}
		PFX_INIT_LIST_NODE (ptemp_node);
		if (null != ptemp_node && ptemp_node != premove_node)
		{
			tenary_tree_node_t* ptemp_list_node = null;
			PFX_INSERT_LIST_NODE_BEGIN (premove_node,ptemp_node,ptemp_list_node);
		}

		SET_POINTER_VALUE (pstatus,PFX_STATUS_OK);

		RETURN_RESULT (null == ptemp_node,null);
		RETURN_RESULT (null == ptemp_next_remove_node,ptemp_node);
		RETURN_RESULT (pfx_false == is_leaf,ptemp_node);

		ptemp_node = ptemp_next_remove_node;

	} while (1);
	
	SET_POINTER_VALUE (pstatus,PFX_STATUS_ERROR_);
	return null;


}
