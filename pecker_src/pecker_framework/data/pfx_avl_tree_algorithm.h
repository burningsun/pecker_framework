/*
 * pfx_avl_tree_algorithm.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城 (cut / cutxyz)
 */

#ifndef		PFX_AVL_TREE_ALGORITHM_H_
#define		PFX_AVL_TREE_ALGORITHM_H_

#include "pfx_bst_algorithm.h"

PFX_C_EXTERN_BEGIN

typedef struct st_avl_tree_balance_flag
{
	pfx_s16_t	m_mask_value;
	pfx_s16_t	m_height;
}avl_tree_balance_flag_t;

typedef union un_avl_tree_balance_bitmask
{
	avl_tree_balance_flag_t	m_balance_value;
	pfx_s32_t								m_s32bitmask;
	pfx_u32_t								m_u32bitmask;
}avl_tree_balance_bitmask_t;

typedef struct st_avl_tree_node
{
	binary_search_tree_node_t		m_bst_node;
	avl_tree_balance_bitmask_t	m_balance_value;
}avl_tree_node_t;

//AVL旋转类型
typedef enum enumAVLTREE_ROTATE_TYPE
{
	AVLTREE_NONE_ROTATE = 0,
	AVLTREE_ROTATE_ERR,
	AVLTREE_NOT_SIMPLE_ROTATE,
	AVLTREE_LL_ROTATE,
	AVLTREE_RR_ROTATE,
	AVLTREE_RL_ROTATE,
	AVLTREE_LR_ROTATE,
	AVLTREE_ROTATE_TYPE_COUNT
}AVLTREE_ROTATE_t;

// 取得节点的高度值
PFX_INLINE pfx_s16_t get_avl_node_height(const avl_tree_node_t* PARAM_IN pAvl_node)
{
	if (null == pAvl_node)
	{
		return -1;
	}
	else
	{
		return pAvl_node->m_balance_value.m_balance_value.m_height;
	}
}

//计算节点的高度值
PFX_INLINE pfx_s16_t calculate_avl_node_height_by_two_leave(const avl_tree_node_t* PARAM_IN pAvl_left_node,const avl_tree_node_t* PARAM_IN pAvl_right_node) 
{
	pfx_s16_t left_height = get_avl_node_height(pAvl_left_node);
	pfx_s16_t right_height =  get_avl_node_height(pAvl_right_node);

	if (left_height > right_height)
	{
		return (left_height+1);
	}
	else
	{
		return (right_height+1);
	}
}

PFX_INLINE pfx_s16_t calculate_avl_node_height(const avl_tree_node_t* PARAM_IN pAvl_node)
{
	if (null == pAvl_node)
	{
		return -1;
	}
	else
	{
		return calculate_avl_node_height_by_two_leave((avl_tree_node_t*)pAvl_node->m_bst_node.m_pleft_node,(avl_tree_node_t*)pAvl_node->m_bst_node.m_pright_node);
	}
}

//计算节点平衡系数
PFX_INLINE pfx_s16_t calculate_avl_node_balance_val(const avl_tree_node_t* PARAM_IN pAvl_node)
{
	if (null != pAvl_node)
	{
		return get_avl_node_height((avl_tree_node_t*)pAvl_node->m_bst_node.m_pleft_node) - get_avl_node_height((avl_tree_node_t*)pAvl_node->m_bst_node.m_pright_node);
	}
	else
	{
		return 0;
	}
}

//插入节点
const avl_tree_node_t* add_avl_node_unsafe(avl_tree_node_t** PARAM_INOUT ppAvl_root_node_ref,
	avl_tree_node_t* PARAM_INOUT pAdd_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus);

//移除节点
avl_tree_node_t* remove_avl_node_unsafe(avl_tree_node_t** PARAM_INOUT ppAvl_root_node_ref,
	avl_tree_node_t* PARAM_INOUT premove_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus);



PFX_C_EXTERN_END

#endif			//PFX_AVL_TREE_ALGORITHM_H_
