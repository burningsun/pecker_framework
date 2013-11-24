/*
 * pfx_avl_tree_algorithm.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_AVL_TREE_ALGORITHM_H_
#define		PFX_AVL_TREE_ALGORITHM_H_

#include "pfx_bst_algorithm.h"

PFX_C_EXTERN_BEGIN

typedef struct PFX_DATA_API st_avl_tree_balance_flag
{
	pfx_s16_t	m_mask_value;
	pfx_s16_t	m_height;
}avl_tree_balance_flag_t;

typedef union PFX_DATA_API un_avl_tree_balance_bitmask
{
	avl_tree_balance_flag_t						m_balance_value;
	binary_search_tree_node_mask_t		m_bst_mask;
	pfx_s32_t												m_s32bitmask;
	pfx_u32_t												m_u32bitmask;

}avl_tree_balance_bitmask_t;

typedef struct PFX_DATA_API st_avl_tree_node _avl_tree_node_t;

struct PFX_DATA_API st_avl_tree_node
{
	_avl_tree_node_t*						m_parent_node;
	_avl_tree_node_t*						m_pleft_node;
	_avl_tree_node_t*						m_pright_node;
	avl_tree_balance_bitmask_t		m_balance_value;
	pfx_long_t										m_key;
};

typedef union PFX_DATA_API un_avl_tree_node
{
	binary_search_tree_node_t		m_bst_node;
	_avl_tree_node_t						m_avl_node;
}avl_tree_node_t;

//AVL旋转类型
typedef enum PFX_DATA_API enumAVLTREE_ROTATE_TYPE
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

PFX_INLINE void init_avl_tree_node_nokey_default (avl_tree_node_t* PARAM_INOUT ptree_node);
// 取得节点的高度值
PFX_INLINE pfx_s16_t get_avl_node_height (const _avl_tree_node_t* PARAM_IN pAvl_node);

//计算节点的高度值
PFX_INLINE pfx_s16_t calculate_avl_node_height_by_two_leave (const _avl_tree_node_t* PARAM_IN pAvl_left_node,const _avl_tree_node_t* PARAM_IN pAvl_right_node) ;

PFX_INLINE pfx_s16_t calculate_avl_node_height (const _avl_tree_node_t* PARAM_IN pAvl_node);

//计算节点平衡系数
PFX_INLINE pfx_s16_t calculate_avl_node_balance_val (const _avl_tree_node_t* PARAM_IN pAvl_node);

//更新节点高度值
PFX_INLINE void update_avl_node_height_unsafe (_avl_tree_node_t* PARAM_INOUT pAvl_node);

//插入节点
PFX_DATA_API const avl_tree_node_t*  add_avl_node_unsafe (avl_tree_node_t** PARAM_INOUT ppAvl_root_node_ref,
	avl_tree_node_t* PARAM_INOUT pAdd_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus);

//移除节点
PFX_DATA_API avl_tree_node_t*  remove_avl_node_unsafe (avl_tree_node_t** PARAM_INOUT ppAvl_root_node_ref,
	avl_tree_node_t* PARAM_INOUT premove_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus);




//////////////////////////////////////////////////////////////////////////
PFX_INLINE void init_avl_tree_node_nokey_default (avl_tree_node_t* PARAM_INOUT ptree_node)
{
	init_binary_search_tree_node_nokey_unsafe((binary_search_tree_node_t*)ptree_node,null,null,null);
	ptree_node->m_avl_node.m_balance_value.m_balance_value.m_height = 0;
}

// 取得节点的高度值
PFX_INLINE pfx_s16_t get_avl_node_height (const _avl_tree_node_t* PARAM_IN pAvl_node)
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
PFX_INLINE pfx_s16_t calculate_avl_node_height_by_two_leave (const _avl_tree_node_t* PARAM_IN pAvl_left_node,const _avl_tree_node_t* PARAM_IN pAvl_right_node) 
{
	pfx_s16_t left_height = get_avl_node_height (pAvl_left_node);
	pfx_s16_t right_height =  get_avl_node_height (pAvl_right_node);

	if (left_height > right_height)
	{
		return (left_height+1);
	}
	else
	{
		return (right_height+1);
	}
}

PFX_INLINE pfx_s16_t calculate_avl_node_height (const _avl_tree_node_t* PARAM_IN pAvl_node)
{
	if (null == pAvl_node)
	{
		return -1;
	}
	else
	{
		return calculate_avl_node_height_by_two_leave (pAvl_node->m_pleft_node,pAvl_node->m_pright_node);
	}
}

//计算节点平衡系数
PFX_INLINE pfx_s16_t calculate_avl_node_balance_val (const _avl_tree_node_t* PARAM_IN pAvl_node)
{
	if (null != pAvl_node)
	{
		return get_avl_node_height (pAvl_node->m_pleft_node) - get_avl_node_height (pAvl_node->m_pright_node);
	}
	else
	{
		return 0;
	}
}

PFX_INLINE void update_avl_node_height_unsafe (_avl_tree_node_t* PARAM_INOUT pAvl_node)
{
	pAvl_node->m_balance_value.m_balance_value.m_height = (get_avl_node_height (pAvl_node->m_pleft_node) - get_avl_node_height (pAvl_node->m_pright_node));
}

PFX_C_EXTERN_END

#endif			//PFX_AVL_TREE_ALGORITHM_H_
