/*
 * pfx_bst_iterator.cpp
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城 (cut / cutxyz)
 */




#include "pfx_bst_iterator.h"


const binary_search_tree_node_t* get_binary_search_tree_inorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null != proot_node)
	{
		return min_binary_search_tree_node_unsafe(proot_node);
	}
	else
	{
		return null;
	}
}

const binary_search_tree_node_t* get_binary_search_tree_inorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null != proot_node)
	{
		return max_binary_search_tree_node_unsafe(proot_node);
	}
	else
	{
		return null;
	}
}

const binary_search_tree_node_t* binary_search_tree_inorder_increase (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
																																	const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null == pcurrent_node || null == proot_node)
	{
		return null;
	}

	do 
	{
		if (pcurrent_node == proot_node)
		{
			return min_binary_search_tree_node_unsafe(pcurrent_node->m_pright_node);
		}

		if (null != pcurrent_node->m_pright_node)
		{
			return min_binary_search_tree_node_unsafe(pcurrent_node->m_pright_node);
		}

		if (pcurrent_node->m_parent_node->m_pleft_node == pcurrent_node)
		{
			return pcurrent_node->m_parent_node;
		}

		if (pcurrent_node == pcurrent_node->m_parent_node)
		{
			break;
		}

		pcurrent_node = pcurrent_node->m_parent_node;

	} while (1);

	return null;
}
const binary_search_tree_node_t* binary_search_tree_inorder_decrease (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
																																	const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null == pcurrent_node || null == proot_node)
	{
		return null;
	}

	do 
	{
		if (pcurrent_node == proot_node)
		{
			return max_binary_search_tree_node_unsafe(pcurrent_node->m_pleft_node);
		}

		if (null != pcurrent_node->m_pright_node)
		{
			return max_binary_search_tree_node_unsafe(pcurrent_node->m_pleft_node);
		}

		if (pcurrent_node->m_parent_node->m_pright_node == pcurrent_node)
		{
			return pcurrent_node->m_parent_node;
		}

		if (pcurrent_node == pcurrent_node->m_parent_node)
		{
			break;
		}

		pcurrent_node = pcurrent_node->m_parent_node;

	} while (1);

	return null;
}


pfx_result_t binary_search_tree_preorder_travel_recursion(const binary_search_tree_node_t* PARAM_IN proot_node,
	const binary_search_tree_node_t* PARAM_IN pmin_left_node,
	const binary_search_tree_node_t* PARAM_IN pmax_right_node,
	collection_t*	PARAM_INOUT	ptravel_collection)
{
	pfx_result_t status = PFX_STATUS_OK;
	if (null == proot_node)
	{
		return PFX_STATUS_OK;
	}

	status = ptravel_collection->m_method.m_push(ptravel_collection,(binary_search_tree_node_t*)proot_node);

	if (PFX_STATUS_OK != status)
	{
		return status;
	}

	if (pmin_left_node != proot_node && pmax_right_node != proot_node)
	{
		status = binary_search_tree_preorder_travel_recursion(proot_node->m_pleft_node,pmin_left_node,pmax_right_node,ptravel_collection);
		if (PFX_STATUS_OK != status)
		{
			return status;
		}

		status = binary_search_tree_preorder_travel_recursion(proot_node->m_pright_node,pmin_left_node,pmax_right_node,ptravel_collection);
		if (PFX_STATUS_OK != status)
		{
			return status;
		}
	}
	else if (pmin_left_node != proot_node)
	{
		status = binary_search_tree_preorder_travel_recursion(proot_node->m_pright_node,pmin_left_node,pmax_right_node,ptravel_collection);
		if (PFX_STATUS_OK != status)
		{
			return status;
		}
	}
	else if (pmax_right_node == proot_node)
	{
		status = binary_search_tree_preorder_travel_recursion(proot_node->m_pleft_node,pmin_left_node,pmax_right_node,ptravel_collection);
		if (PFX_STATUS_OK != status)
		{
			return status;
		}
	}

	return status;
}

pfx_result_t binary_search_tree_posorder_travel_recursion(const binary_search_tree_node_t* PARAM_IN proot_node,
	const binary_search_tree_node_t* PARAM_IN pmin_left_node,
	const binary_search_tree_node_t* PARAM_IN pmax_right_node,
	collection_t*	PARAM_INOUT	ptravel_collection)
{
	pfx_result_t status = PFX_STATUS_OK;
	if (null == proot_node)
	{
		return PFX_STATUS_OK;
	}

	if (pmin_left_node != proot_node && pmax_right_node != proot_node)
	{
		status = binary_search_tree_posorder_travel_recursion(proot_node->m_pleft_node,pmin_left_node,pmax_right_node,ptravel_collection);
		if (PFX_STATUS_OK != status)
		{
			return status;
		}

		status = binary_search_tree_posorder_travel_recursion(proot_node->m_pright_node,pmin_left_node,pmax_right_node,ptravel_collection);
		if (PFX_STATUS_OK != status)
		{
			return status;
		}
	}
	else if (pmin_left_node != proot_node)
	{
		status = binary_search_tree_posorder_travel_recursion(proot_node->m_pright_node,pmin_left_node,pmax_right_node,ptravel_collection);
		if (PFX_STATUS_OK != status)
		{
			return status;
		}
	}
	else if (pmax_right_node == proot_node)
	{
		status = binary_search_tree_posorder_travel_recursion(proot_node->m_pleft_node,pmin_left_node,pmax_right_node,ptravel_collection);
		if (PFX_STATUS_OK != status)
		{
			return status;
		}
	}

	status = ptravel_collection->m_method.m_push(ptravel_collection,(binary_search_tree_node_t*)proot_node);

	if (PFX_STATUS_OK != status)
	{
		return status;
	}

	return status;
}

