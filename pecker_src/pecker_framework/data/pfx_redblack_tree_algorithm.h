/*
 * pfx_redblack_tree_algorithm.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_REDBLACK_TREE_ALGORITHM_H_
#define		PFX_REDBLACK_TREE_ALGORITHM_H_

#include "pfx_bst_algorithm.h"

PFX_C_EXTERN_BEGIN

typedef struct PFX_DATA_API st_redblack_tree_balance_flag
{
	pfx_u16_t	m_mask_value;
	pfx_u16_t	m_color;
}redblack_tree_balance_flag_t;

typedef union PFX_DATA_API un_redblack_tree_balance_bitmask
{
	redblack_tree_balance_flag_t				m_balance_value;
	binary_search_tree_node_mask_t		m_bst_mask;
	pfx_s32_t												m_s32bitmask;
	pfx_u32_t												m_u32bitmask;

}redblack_tree_balance_bitmask_t;

typedef struct PFX_DATA_API st_redblack_tree_node _redblack_tree_node_t;

struct PFX_DATA_API st_redblack_tree_node
{
	_redblack_tree_node_t*						m_parent_node;
	_redblack_tree_node_t*						m_pleft_node;
	_redblack_tree_node_t*						m_pright_node;
	redblack_tree_balance_bitmask_t		m_balance_value;
	pfx_long_t												m_key;
};
//
typedef union PFX_DATA_API un_redblack_tree_node
{
	binary_search_tree_node_t		m_bst_node;
	_redblack_tree_node_t			m_rb_node;
}redblack_tree_node_t;

#define RED_COLOR_NODE_TYPE		(0x3AAA)
#define BLACK_COLOR_NODE_TYPE	(0x3BBB)

PFX_INLINE	void  set_rb_tree_color_red_unsafe (_redblack_tree_node_t* PARAM_INOUT pnode);
PFX_INLINE	void  set_rb_tree_color_black_unsafe (_redblack_tree_node_t* PARAM_INOUT pnode);
PFX_INLINE	pfx_bool_t	check_rb_tree_color_is_red (const _redblack_tree_node_t* PARAM_INOUT pnode);
PFX_INLINE	pfx_bool_t	check_rb_tree_color_is_black (const _redblack_tree_node_t* PARAM_INOUT pnode);
PFX_INLINE	void copy_rb_tree_color_unsafe (_redblack_tree_node_t* PARAM_INOUT pdec_node,const _redblack_tree_node_t* PARAM_IN psrc_node);

PFX_INLINE	void rb_tree_sentinel_init_unsafe (_redblack_tree_node_t* PARAM_INOUT pnode);
PFX_INLINE void init_redblack_tree_node_nokey_default (redblack_tree_node_t* PARAM_INOUT ptree_node);

//插入节点
PFX_DATA_API const redblack_tree_node_t*  add_redblack_node_unsafe (redblack_tree_node_t** PARAM_INOUT pproot_node_ref,
	redblack_tree_node_t* PARAM_INOUT padd_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus);

//移除节点
PFX_DATA_API redblack_tree_node_t*  remove_redblack_node_unsafe (redblack_tree_node_t** PARAM_INOUT pproot_node_ref,
	redblack_tree_node_t* PARAM_INOUT premove_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus);

//////////////////////////////////////////////////////////////////////////

PFX_INLINE	void  set_rb_tree_color_red_unsafe (_redblack_tree_node_t* PARAM_INOUT pnode)
{
	pnode->m_balance_value.m_balance_value.m_color = RED_COLOR_NODE_TYPE;
}
PFX_INLINE	void  set_rb_tree_color_black_unsafe (_redblack_tree_node_t* PARAM_INOUT pnode)
{
	pnode->m_balance_value.m_balance_value.m_color = BLACK_COLOR_NODE_TYPE;
}
PFX_INLINE	pfx_bool_t	check_rb_tree_color_is_red (const _redblack_tree_node_t* PARAM_INOUT pnode)
{
	if (null == pnode)
	{
		return pfx_false;
	}
	else if (RED_COLOR_NODE_TYPE == pnode->m_balance_value.m_balance_value.m_color)
	{
		return pfx_true;
	}
	else if (BLACK_COLOR_NODE_TYPE == pnode->m_balance_value.m_balance_value.m_color)
	{
		return pfx_false;
	}
	else
	{
		return pfx_invalid;
	}
}
PFX_INLINE	pfx_bool_t	check_rb_tree_color_is_black (const _redblack_tree_node_t* PARAM_INOUT pnode)
{
	if (null == pnode)
	{
		return pfx_true;
	}
	else if (BLACK_COLOR_NODE_TYPE == pnode->m_balance_value.m_balance_value.m_color)
	{
		return pfx_true;
	}
	else if (RED_COLOR_NODE_TYPE == pnode->m_balance_value.m_balance_value.m_color)
	{
		return pfx_false;
	}
	else
	{
		return pfx_invalid;
	}
}
PFX_INLINE	void copy_rb_tree_color_unsafe (_redblack_tree_node_t* PARAM_INOUT pdec_node,const _redblack_tree_node_t* PARAM_IN psrc_node)
{
	pdec_node->m_balance_value.m_balance_value.m_color = psrc_node->m_balance_value.m_balance_value.m_color;
}

PFX_INLINE	void rb_tree_sentinel_init_unsafe (_redblack_tree_node_t* PARAM_INOUT pnode)
{
	set_rb_tree_color_black_unsafe(pnode);
}


PFX_INLINE void init_redblack_tree_node_nokey_default (redblack_tree_node_t* PARAM_INOUT ptree_node)
{
	init_binary_search_tree_node_nokey_unsafe((binary_search_tree_node_t*)ptree_node,null,null,null);
	set_rb_tree_color_black_unsafe((_redblack_tree_node_t*)ptree_node);
}




PFX_C_EXTERN_END

#endif			//PFX_REDBLACK_TREE_ALGORITHM_H_
