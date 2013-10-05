/*
 * pfx_bst_algorithm.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BST_ALGORITHM_H_
#define		PFX_BST_ALGORITHM_H_

#include "../native/pfx_allocator.h"
#include "../pfx_defines.h"
#include "pecker_value_compare.h"
#include "../native/pfx_allocator.h"

PFX_C_EXTERN_BEGIN

// 二叉树内部标记，主要用于平衡树应用
typedef struct st_binary_search_tree_node_mask
{
	unsigned		m_valid_mask		: 2;		// 合法性判断位，用于假删除
	unsigned		m_revered_mask	: 14;	// 保留位
	unsigned 	m_balance_mask	: 16;	// 平衡树标志位
}st_binary_search_tree_node_mask_t;

typedef union un_binary_search_tree_node_mask
{
	st_binary_search_tree_node_mask_t	m_mask;
	pfx_bitfield_t												m_mask_bits;
}binary_search_tree_node_mask_t;

// 二叉树节点基本结构
typedef struct st_binary_search_tree_node binary_search_tree_node_t;

struct st_binary_search_tree_node
{
	binary_search_tree_node_t*				m_parent_node;	// 父节点，主要用于优化遍历，以及可修改型迭代器的应用
	binary_search_tree_node_t*				m_pleft_node;		// 左子树
	binary_search_tree_node_t*				m_pright_node;	// 右子树
	binary_search_tree_node_mask_t		m_mask;				// 内部标记，平衡树扩展应用
	pfx_long_t												m_key;					//	 键
};

// 分配新的二叉树节点的内存
typedef binary_search_tree_node_t* (*new_bst_node_func)(const IAllocator* PARAM_IN pallocator,const binary_search_tree_node_t* PARAM_IN pother_node);

// 删除二叉树节点所占的内存，注意这不实现移除二叉树节点
typedef pfx_result_t (*delete_bst_node_func)(const IAllocator* PARAM_IN pallocator,binary_search_tree_node_t* PARAM_IN pdel_node);

// 检查是否为叶子节点
PFX_INLINE pfx_bool_t check_binary_search_tree_leaf_node_unsafe(const binary_search_tree_node_t* PARAM_IN pnode);

// 检查节点是否为定义好的叶子节点
PFX_INLINE pfx_bool_t check_binary_search_tree_define_leaf_node_unsafe(const binary_search_tree_node_t* PARAM_IN pnode,
	const binary_search_tree_node_t* pnull_node);

// 初始化二叉树节点
PFX_INLINE void init_binary_search_tree_node_unsafe (binary_search_tree_node_t* PARAM_INOUT ptree_node,
	binary_search_tree_node_t*  PARAM_IN pleft_node,
	binary_search_tree_node_t*  PARAM_IN pright_node,
	binary_search_tree_node_t*  PARAM_IN parent_node,
	pfx_long_t key);

// 初始化二叉树节点不含键初始化
PFX_INLINE void init_binary_search_tree_node_nokey_unsafe (binary_search_tree_node_t* PARAM_INOUT ptree_node,
	binary_search_tree_node_t*  PARAM_IN pleft_node,
	binary_search_tree_node_t*  PARAM_IN pright_node,
	binary_search_tree_node_t*  PARAM_IN parent_node);

// 查找指定根节点下最小的节点
PFX_INLINE const binary_search_tree_node_t* min_binary_search_tree_node_unsafe (const binary_search_tree_node_t* PARAM_IN proot_node);

// 查找指定根节点下最小的节点
PFX_INLINE const binary_search_tree_node_t* min_binary_search_tree_define_leaf_node_unsafe (const binary_search_tree_node_t* PARAM_IN proot_node,
	const binary_search_tree_node_t* pnull_node);

// 查找指定根节点下最大的节点
PFX_INLINE const binary_search_tree_node_t* max_binary_search_tree_node_unsafe (const binary_search_tree_node_t* PARAM_IN proot_node);

// 查找指定根节点下最大的节点
PFX_INLINE const binary_search_tree_node_t* max_binary_search_tree_define_leaf_node_unsafe (const binary_search_tree_node_t* PARAM_IN proot_node,
	const binary_search_tree_node_t* pnull_node);

// 查找指定键的节点
PFX_INLINE const binary_search_tree_node_t* find_node_form_binary_search_tree (pfx_long_t find_key,
	const binary_search_tree_node_t* PARAM_IN proot_node,
	compare_two_value_func cmp_method);

// 查找指定键最接近的节点
PFX_INLINE const binary_search_tree_node_t* find_first_near_node_form_binary_search_tree (pfx_long_t find_key,
	const binary_search_tree_node_t* PARAM_IN proot_node,
	compare_two_value_func cmp_method,
	int* PARAM_INOUT plast_cmp_result);

// 查找需要移除的节点，用于平衡树扩展
PFX_INLINE const binary_search_tree_node_t* find_remove_replace_node_form_binary_search_tree_unsafe (
	const binary_search_tree_node_t* PARAM_IN premove_node,
	binary_search_tree_node_t** PARAM_INOUT ppsub_remove_node,
	const binary_search_tree_node_t* pnull_node);

// 移除节点
//PFX_INLINE pfx_result_t remove_bst_node_unsafe_ex1 (
//	binary_search_tree_node_t**				PARAM_INOUT pproot_node,
//	binary_search_tree_node_t*				PARAM_INOUT	premove_node,
//	binary_search_tree_node_t**				PARAM_INOUT	pprepalce_ref_lr_node,
//	binary_search_tree_node_t**				PARAM_INOUT	pprepalce_ref_p_node,
//	const binary_search_tree_node_t*	PARAM_IN			pnull_node);
//
//PFX_INLINE pfx_result_t remove_bst_node_unsafe_ex2 (
//	binary_search_tree_node_t**				PARAM_INOUT pproot_node,
//	binary_search_tree_node_t*				PARAM_INOUT	premove_node,
//	binary_search_tree_node_t**				PARAM_INOUT	pprepalce_ref_lr_node,
//	const binary_search_tree_node_t*	PARAM_IN			pnull_node);

PFX_INLINE pfx_result_t remove_bst_node_unsafe (
	binary_search_tree_node_t**				PARAM_INOUT pproot_node,
	binary_search_tree_node_t*				PARAM_INOUT	premove_node,
	const binary_search_tree_node_t*	PARAM_IN			pnull_node);

// 添加节点
PFX_INLINE pfx_result_t add_bst_node_unsafe (
	binary_search_tree_node_t** PARAM_INOUT pproot_node,
	binary_search_tree_node_t*	PARAM_INOUT	padd_node,
	binary_search_tree_node_t**	PARAM_INOUT	ppadded_node,
	compare_two_value_func		cmp_method);

// 默认
// 分配新的二叉树节点的内存
binary_search_tree_node_t* new_bst_node_func_default(const IAllocator* PARAM_IN pallocator,const binary_search_tree_node_t* PARAM_IN pother_node);

// 默认
// 删除二叉树节点所占的内存
pfx_result_t delete_bst_node_func_default(const IAllocator* PARAM_IN pallocator,binary_search_tree_node_t* PARAM_IN pdel_node);

// 复制树
pfx_result_t copy_binary_search_tree_unsafe (binary_search_tree_node_t** PARAM_INOUT ppdec_root_node,const binary_search_tree_node_t* PARAM_IN psrc_root_node,
	const IAllocator* PARAM_IN pallocator,new_bst_node_func new_node_method);

// 删除树
pfx_result_t clear_binary_search_tree_unsafe (binary_search_tree_node_t** PARAM_INOUT ppdec_root_node,const IAllocator* PARAM_IN pallocator,delete_bst_node_func delete_node_method);

//////////////////////////////////////////////////////////////////////////

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
	//ptree_node->m_mask.m_mask_bits = 0;
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
	//ptree_node->m_mask.m_mask_bits = 0;
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
		//else if (psub_remove_node->m_pright_node != pnull_node)
		//{
		//	psub_remove_ref_node = psub_remove_node->m_pright_node;
		//}
		//else
		//{
		//	psub_remove_ref_node = psub_remove_node->m_parent_node;
		//}
	}

	*ppsub_remove_node = (binary_search_tree_node_t*)psub_remove_node;
	return psub_remove_ref_node;
}

PFX_INLINE pfx_result_t remove_bst_node_unsafe_in(	
	binary_search_tree_node_t**				PARAM_INOUT pproot_node,
	binary_search_tree_node_t*				PARAM_INOUT	premove_node,
	binary_search_tree_node_t*				PARAM_INOUT	psub_remove_node,
	binary_search_tree_node_t*				PARAM_INOUT	psub_romove_ref_node,
	const binary_search_tree_node_t*	PARAM_IN			pnull_node)
{
	binary_search_tree_node_t* proot_node = *pproot_node;
	
	// 处理替换节点
	if (psub_remove_node == proot_node) 
	{
		if (null != proot_node->m_parent_node)
		{
			if (proot_node->m_parent_node->m_pleft_node == proot_node)
			{
				proot_node->m_parent_node->m_pleft_node  = psub_romove_ref_node;
			}
			else if (proot_node->m_parent_node->m_pright_node == proot_node)
			{
				proot_node->m_parent_node->m_pright_node  = psub_romove_ref_node;
			}
			else
			{
				return PFX_STATUS_MEM_ERR;
			}
		}
		if (null != psub_romove_ref_node)
		{
			psub_romove_ref_node->m_parent_node = proot_node->m_parent_node;
		}
		
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

//PFX_INLINE pfx_result_t remove_bst_node_unsafe_ex1 (
//	binary_search_tree_node_t**				PARAM_INOUT pproot_node,
//	binary_search_tree_node_t*				PARAM_INOUT	premove_node,
//	binary_search_tree_node_t**				PARAM_INOUT	pprepalce_ref_lr_node,
//	binary_search_tree_node_t**				PARAM_INOUT	pprepalce_ref_node_parent,
//	const binary_search_tree_node_t*	PARAM_IN			pnull_node)
//{
//	binary_search_tree_node_t* proot_node = *pproot_node;
//	binary_search_tree_node_t* psub_romove_ref_node;
//	binary_search_tree_node_t* psub_remove_node;
//
//	psub_romove_ref_node = (binary_search_tree_node_t*)find_remove_replace_node_form_binary_search_tree_unsafe (premove_node,&psub_remove_node,pnull_node);
//	*pprepalce_ref_lr_node = psub_romove_ref_node;
//	if (null != psub_remove_node)
//	{
//		if (premove_node != psub_remove_node->m_parent_node)
//		{
//			*pprepalce_ref_node_parent = psub_remove_node->m_parent_node;
//		}
//		else
//		{
//			*pprepalce_ref_node_parent = null;
//		}
//		
//	}
//	else
//	{
//		*pprepalce_ref_node_parent = null;
//	}
//	
//
//	// 处理替换节点
//	if (psub_remove_node == proot_node) 
//	{
//		if (null != proot_node->m_parent_node)
//		{
//			if (proot_node->m_parent_node->m_pleft_node == proot_node)
//			{
//				proot_node->m_parent_node->m_pleft_node  = psub_romove_ref_node;
//			}
//			else if (proot_node->m_parent_node->m_pright_node == proot_node)
//			{
//				proot_node->m_parent_node->m_pright_node  = psub_romove_ref_node;
//			}
//			else
//			{
//				return PFX_STATUS_MEM_ERR;
//			}
//		}
//		if (null != psub_romove_ref_node)
//		{
//			psub_romove_ref_node->m_parent_node = proot_node->m_parent_node;
//		}
//		
//		*pproot_node = psub_romove_ref_node;
//		init_binary_search_tree_node_nokey_unsafe(premove_node,null,null,null);
//		return PFX_STATUS_OK;
//	}
//
//	if (psub_remove_node == psub_remove_node->m_parent_node->m_pleft_node)
//	{
//		psub_remove_node->m_parent_node->m_pleft_node = psub_romove_ref_node;
//	}
//	else
//	{
//		psub_remove_node->m_parent_node->m_pright_node = psub_romove_ref_node;
//	}
//
//	if (psub_remove_node == premove_node)
//	{
//		if (psub_romove_ref_node)
//		{
//			psub_romove_ref_node->m_parent_node = psub_remove_node->m_parent_node;
//		}
//
//		init_binary_search_tree_node_nokey_unsafe(premove_node,null,null,null);
//		return PFX_STATUS_OK;
//	}
//
//	if (psub_remove_node->m_parent_node == premove_node)
//	{
//		if (psub_romove_ref_node)
//		{
//			psub_romove_ref_node->m_parent_node = psub_remove_node;
//		}
//	}
//	else
//	{
//		if (psub_romove_ref_node)
//		{
//			psub_romove_ref_node->m_parent_node = psub_remove_node->m_parent_node;
//		}
//	}
//	
//
//	// 将remove node相关的指针复制
//	psub_remove_node->m_pleft_node = premove_node->m_pleft_node;
//	psub_remove_node->m_pright_node = premove_node->m_pright_node;
//	psub_remove_node->m_parent_node = premove_node->m_parent_node;
//	//*pprepalce_ref_node = psub_romove_ref_node;
//	
//
//	if (premove_node == proot_node) // 移除节点是根节点
//	{
//		*pproot_node = psub_remove_node;		// 将根节点替换为psub_node
//	}
//	else
//	{
//		// 替换移除节点父节点的相关指针
//		if (premove_node == premove_node->m_parent_node->m_pleft_node)
//		{
//			premove_node->m_parent_node->m_pleft_node = psub_remove_node;
//		}
//		else
//		{
//			premove_node->m_parent_node->m_pright_node = psub_remove_node;
//		}
//	}
//
//	// 更新现在新的左右节点的父节点指针
//	if (psub_remove_node->m_pleft_node != pnull_node)
//	{
//		psub_remove_node->m_pleft_node->m_parent_node = psub_remove_node;
//	}
//	if (psub_remove_node->m_pright_node != pnull_node)
//	{
//		psub_remove_node->m_pright_node->m_parent_node = psub_remove_node;
//	}
//
//	init_binary_search_tree_node_nokey_unsafe(premove_node,null,null,null);
//
//	return PFX_STATUS_OK;
//}

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

//PFX_INLINE pfx_result_t remove_bst_node_unsafe_ex2 (
//	binary_search_tree_node_t**				PARAM_INOUT pproot_node,
//	binary_search_tree_node_t*				PARAM_INOUT	premove_node,
//	binary_search_tree_node_t**				PARAM_INOUT	pprepalce_ref_lr_node,
//	const binary_search_tree_node_t*	PARAM_IN			pnull_node)
//{
//	binary_search_tree_node_t* tmp;
//
//	return remove_bst_node_unsafe_ex1(pproot_node,premove_node,pprepalce_ref_lr_node,&tmp,pnull_node);
//}

PFX_INLINE pfx_result_t remove_bst_node_unsafe (
	binary_search_tree_node_t**				PARAM_INOUT pproot_node,
	binary_search_tree_node_t*				PARAM_INOUT	premove_node,
	const binary_search_tree_node_t*	PARAM_IN			pnull_node)
{
	binary_search_tree_node_t* proot_node = *pproot_node;
	binary_search_tree_node_t* psub_romove_ref_node;
	binary_search_tree_node_t* psub_remove_node;
	
	psub_romove_ref_node = 
		(binary_search_tree_node_t*)find_remove_replace_node_form_binary_search_tree_unsafe (premove_node,&psub_remove_node,pnull_node);

	return remove_bst_node_unsafe_in(pproot_node,premove_node,psub_remove_node,psub_romove_ref_node,pnull_node);
}

PFX_C_EXTERN_END


#endif			//PFX_BST_ALGORITHM_H_
