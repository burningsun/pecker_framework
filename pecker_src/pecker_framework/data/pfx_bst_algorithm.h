/*
 * pfx_bst_algorithm.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城 (cut / cutxyz)
 */

#ifndef		PFX_BST_ALGORITHM_H_
#define		PFX_BST_ALGORITHM_H_

#include "../native/pfx_allocator.h"
#include "../pfx_defines.h"
#include "pecker_value_compare.h"

PFX_C_EXTERN_BEGIN

typedef struct st_binary_search_tree_node binary_search_tree_node_t;

struct st_binary_search_tree_node
{
	binary_search_tree_node_t*	m_parent_node;
	binary_search_tree_node_t*	m_pleft_node;
	binary_search_tree_node_t*	m_pright_node;
	pfx_long_t											m_key;
};

PFX_INLINE pfx_bool_t check_binary_search_tree_leaf_node_unsafe(const binary_search_tree_node_t* PARAM_IN pnode)
{
	if (null == pnode->m_pleft_node && null == pnode->m_pright_node)
	{
		return pfx_true;
	}
	return pfx_false;
}

PFX_INLINE pfx_bool_t check_binary_search_tree_define_leaf_node_unsafe(const binary_search_tree_node_t* PARAM_IN pnode,
	const binary_search_tree_node_t* pnull_node)
{
	if (pnull_node == pnode->m_pleft_node && pnull_node == pnode->m_pright_node)
	{
		return pfx_true;
	}
	return pfx_false;
}

PFX_INLINE void init_binary_search_tree_node_unsafe (binary_search_tree_node_t* PARAM_INOUT ptree_node,
	binary_search_tree_node_t*  PARAM_IN pleft_node,
	binary_search_tree_node_t*  PARAM_IN pright_node,
	binary_search_tree_node_t*  PARAM_IN parent_node,
	pfx_long_t key)
{
	ptree_node->m_pleft_node = pleft_node;
	ptree_node->m_pright_node = pright_node;
	ptree_node->m_parent_node = parent_node;
	ptree_node->m_key = key;
}

PFX_INLINE void init_binary_search_tree_node_nokey_unsafe (binary_search_tree_node_t* PARAM_INOUT ptree_node,
	binary_search_tree_node_t*  PARAM_IN pleft_node,
	binary_search_tree_node_t*  PARAM_IN pright_node,
	binary_search_tree_node_t*  PARAM_IN parent_node)
{
	ptree_node->m_pleft_node = pleft_node;
	ptree_node->m_pright_node = pright_node;
	ptree_node->m_parent_node = parent_node;
}

PFX_INLINE const binary_search_tree_node_t* min_binary_search_tree_node_unsafe (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	while( null != proot_node->m_pleft_node )
	{
		proot_node = proot_node->m_pleft_node;
	}
	return proot_node;
}

PFX_INLINE const binary_search_tree_node_t* min_binary_search_tree_define_leaf_node_unsafe (const binary_search_tree_node_t* PARAM_IN proot_node,
	const binary_search_tree_node_t* pnull_node)
{
	while (pnull_node != proot_node->m_pleft_node)
	{
		proot_node = proot_node->m_pleft_node;
	}
	return proot_node;
}

PFX_INLINE const binary_search_tree_node_t* max_binary_search_tree_node_unsafe (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	while (null != proot_node->m_pright_node)
	{
		proot_node = proot_node->m_pright_node;
	}
	return proot_node;
}

PFX_INLINE const binary_search_tree_node_t* max_binary_search_tree_define_leaf_node_unsafe (const binary_search_tree_node_t* PARAM_IN proot_node,
	const binary_search_tree_node_t* pnull_node)
{
	while (pnull_node != proot_node->m_pright_node)
	{
		proot_node = proot_node->m_pright_node;
	}
	return proot_node;
}

PFX_INLINE const binary_search_tree_node_t* find_node_form_binary_search_tree (pfx_long_t find_key,
	const binary_search_tree_node_t* PARAM_IN proot_node,
	compare_two_value_func cmp_method)
{
	const binary_search_tree_node_t* preturn_node = null;
	while( null != proot_node )
	{
		int cmp_result = cmp_method(find_key,(proot_node->m_key));
		if (cmp_result < 0)
		{
			proot_node = proot_node->m_pleft_node;
		}
		else if (cmp_result > 0)
		{
			proot_node = proot_node->m_pright_node;
		}
		else
		{
			preturn_node = proot_node;
			break;
		}
		
	}
	return preturn_node;
}

PFX_INLINE const binary_search_tree_node_t* find_first_near_node_form_binary_search_tree (pfx_long_t find_key,
	const binary_search_tree_node_t* PARAM_IN proot_node,
	compare_two_value_func cmp_method,
	int* PARAM_INOUT plast_cmp_result)
{
	const binary_search_tree_node_t* preturn_node = null;
	int cmp_result = 0;
	while( null != proot_node )
	{
		cmp_result = cmp_method(find_key,proot_node->m_key);

		preturn_node = proot_node;

		if (cmp_result < 0)
		{
			proot_node = proot_node->m_pleft_node;
		}
		else if (cmp_result > 0)
		{
			proot_node = proot_node->m_pright_node;
		}
		else
		{
			break;
		}

	}
	if (plast_cmp_result)
	{
		*plast_cmp_result = cmp_result;
	}

	return preturn_node;
}


PFX_INLINE const binary_search_tree_node_t* find_remove_replace_node_form_binary_search_tree_unsafe (
	const binary_search_tree_node_t* PARAM_IN premove_node,
	binary_search_tree_node_t** PARAM_INOUT ppsub_remove_node,
	const binary_search_tree_node_t* pnull_node)
{
	const binary_search_tree_node_t* psub_remove_ref_node = null;
	const binary_search_tree_node_t* psub_remove_node = null;

	if (pnull_node == premove_node->m_pleft_node)
	{
		psub_remove_ref_node = premove_node->m_pright_node;
		psub_remove_node = premove_node;
	}
	else if (pnull_node == premove_node->m_pright_node)
	{
		psub_remove_ref_node = premove_node->m_pleft_node;
		psub_remove_node = premove_node;
	}
	else
	{
		psub_remove_node = min_binary_search_tree_define_leaf_node_unsafe (premove_node->m_pright_node,pnull_node);
		if ( psub_remove_node->m_pleft_node != pnull_node)
		{
			psub_remove_ref_node = psub_remove_node->m_pleft_node;
		}
		else
		{
			psub_remove_ref_node = psub_remove_node->m_pright_node;
		}
	}

	*ppsub_remove_node = (binary_search_tree_node_t*)psub_remove_node;
	return psub_remove_ref_node;
}


PFX_INLINE pfx_result_t remove_bst_node_unsafe (
	binary_search_tree_node_t**				PARAM_INOUT pproot_node,
	binary_search_tree_node_t*				PARAM_INOUT	premove_node,
	binary_search_tree_node_t**				PARAM_INOUT	pprepalce_ref_node,
	const binary_search_tree_node_t*	PARAM_IN			pnull_node)
{
	binary_search_tree_node_t* proot_node = *pproot_node;
	binary_search_tree_node_t* psub_romove_ref_node;
	binary_search_tree_node_t* psub_remove_node;

	psub_romove_ref_node = (binary_search_tree_node_t*)find_remove_replace_node_form_binary_search_tree_unsafe (premove_node,&psub_remove_node,pnull_node);
	*pprepalce_ref_node = psub_romove_ref_node;

	// 处理替换节点
	if (psub_remove_node == proot_node) 
	{
		*pproot_node = psub_romove_ref_node;
		init_binary_search_tree_node_nokey_unsafe(premove_node,null,null,null);
		return PFX_STATUS_OK;
	}

	if (psub_remove_node == psub_remove_node->m_parent_node->m_pleft_node)
	{
		psub_remove_node->m_parent_node->m_pleft_node = psub_romove_ref_node;
	}
	else
	{
		psub_remove_node->m_parent_node->m_pright_node = psub_romove_ref_node;
	}

	if (psub_remove_node == premove_node)
	{
		if (psub_romove_ref_node)
		{
			psub_romove_ref_node->m_parent_node = psub_remove_node->m_parent_node;
		}

		init_binary_search_tree_node_nokey_unsafe(premove_node,null,null,null);
		return PFX_STATUS_OK;
	}

	if (psub_remove_node->m_parent_node == premove_node)
	{
		if (psub_romove_ref_node)
		{
			psub_romove_ref_node->m_parent_node = psub_remove_node;
		}
	}
	else
	{
		if (psub_romove_ref_node)
		{
			psub_romove_ref_node->m_parent_node = psub_remove_node->m_parent_node;
		}
	}
	

	// 将remove node相关的指针复制
	psub_remove_node->m_pleft_node = premove_node->m_pleft_node;
	psub_remove_node->m_pright_node = premove_node->m_pright_node;
	psub_remove_node->m_parent_node = premove_node->m_parent_node;
	//*pprepalce_ref_node = psub_romove_ref_node;
	

	if (premove_node == proot_node) // 移除节点是根节点
	{
		*pproot_node = psub_remove_node;		// 将根节点替换为psub_node
	}
	else
	{
		// 替换移除节点父节点的相关指针
		if (premove_node == premove_node->m_parent_node->m_pleft_node)
		{
			premove_node->m_parent_node->m_pleft_node = psub_remove_node;
		}
		else
		{
			premove_node->m_parent_node->m_pright_node = psub_remove_node;
		}
	}

	// 更新现在新的左右节点的父节点指针
	if (psub_remove_node->m_pleft_node != pnull_node)
	{
		psub_remove_node->m_pleft_node->m_parent_node = psub_remove_node;
	}
	if (psub_remove_node->m_pright_node != pnull_node)
	{
		psub_remove_node->m_pright_node->m_parent_node = psub_remove_node;
	}

	init_binary_search_tree_node_nokey_unsafe(premove_node,null,null,null);

	return PFX_STATUS_OK;
}

PFX_INLINE pfx_result_t add_bst_node_unsafe (
	binary_search_tree_node_t** PARAM_INOUT pproot_node,
	binary_search_tree_node_t*	PARAM_INOUT	padd_node,
	binary_search_tree_node_t**	PARAM_INOUT	ppadded_node,
	compare_two_value_func		cmp_method)
{
	pfx_result_t								status;
	int												cmp_result;
	binary_search_tree_node_t*	proot_node;
	binary_search_tree_node_t*	pnode_to_be_add;
	binary_search_tree_node_t*	parent_node;

	proot_node = *pproot_node;

	// 添加第一个节点
	if (null == proot_node)
	{
		*pproot_node = padd_node;
		init_binary_search_tree_node_nokey_unsafe ((binary_search_tree_node_t*)padd_node,null,null,null);
		*ppadded_node = padd_node;
		return PFX_STATUS_OK;
	}

	status = PFX_STATUS_OK;
	do 
	{
		pnode_to_be_add		=	(binary_search_tree_node_t*) find_first_near_node_form_binary_search_tree 
			(padd_node->m_key,proot_node,cmp_method,&cmp_result);

		// 已经存在一个同样key的节点, ppadded_node返回的是已有节点的指针
		if (null != pnode_to_be_add && 0 == cmp_result)
		{
			*ppadded_node = pnode_to_be_add;
			status = PFX_STATUS_UNIQUE;
			break;
		}

		parent_node = pnode_to_be_add->m_parent_node;
		if (0 > cmp_result)
		{
			if (null == pnode_to_be_add->m_pleft_node)
			{
				pnode_to_be_add->m_pleft_node = padd_node;
				init_binary_search_tree_node_nokey_unsafe(padd_node,null,null,pnode_to_be_add);
			}
			else
			{
				if (pnode_to_be_add == proot_node) // 内存数据被损坏
				{
					status = PFX_STATUS_MEM_ERR;
					break;
				}
				else	// 正常情况
				{
					proot_node = pnode_to_be_add;
					continue;
				}

			}
		}
		else
		{
			if (null == pnode_to_be_add->m_pright_node)
			{
				pnode_to_be_add->m_pright_node = padd_node;
				init_binary_search_tree_node_nokey_unsafe(padd_node,null,null,pnode_to_be_add);
			}
			else
			{
				if (pnode_to_be_add == proot_node)  // 内存数据被损坏
				{
					status = PFX_STATUS_MEM_ERR;
					break;
				}
				else // 正常情况
				{
					proot_node = pnode_to_be_add;
					continue;
				}

			}
		}

		*ppadded_node = padd_node;

	} while (0);

	return status;
	
}

PFX_C_EXTERN_END


#endif			//PFX_BST_ALGORITHM_H_
