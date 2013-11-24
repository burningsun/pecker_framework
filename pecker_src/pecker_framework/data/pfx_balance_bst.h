/*
 * pfx_balance_bst.h
 *
 *  Created on: 2013-10-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BALANCE_BST_H_
#define		PFX_BALANCE_BST_H_

#include "pfx_avl_tree_algorithm.h"
#include "pfx_redblack_tree_algorithm.h"

PFX_C_EXTERN_BEGIN

typedef union PFX_DATA_API un_bbst_node
{
	binary_search_tree_node_t		m_bst_node;
	avl_tree_node_t						m_avl_node;
	redblack_tree_node_t				m_rb_node;
}balance_bst_node_t;

//插入节点
typedef const balance_bst_node_t* (*add_bbst_node_unsafe_func) (balance_bst_node_t** PARAM_INOUT ppAvl_root_node_ref,
	balance_bst_node_t* PARAM_INOUT pAdd_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus);

//移除节点
typedef balance_bst_node_t* (*remove_bbst_node_unsafe_func) (balance_bst_node_t** PARAM_INOUT ppAvl_root_node_ref,
	balance_bst_node_t* PARAM_INOUT premove_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus);

//默认初始化节点
typedef void (*init_bbst_node_default_func) (balance_bst_node_t* PARAM_INOUT pnode);


// avl tree
PFX_INLINE const balance_bst_node_t* add_bbst_avl_node_unsafe (balance_bst_node_t** PARAM_INOUT ppAvl_root_node_ref,
	balance_bst_node_t* PARAM_INOUT pAdd_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus)
{
	return (const balance_bst_node_t*)add_avl_node_unsafe ((avl_tree_node_t**)ppAvl_root_node_ref,
		(avl_tree_node_t*)pAdd_node,
		cmp_method,
		pstatus);
}

PFX_INLINE balance_bst_node_t* remove_bbst_avl_node_unsafe (balance_bst_node_t** PARAM_INOUT ppAvl_root_node_ref,
	balance_bst_node_t* PARAM_INOUT premove_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus)
{
	return (balance_bst_node_t*) remove_avl_node_unsafe ((avl_tree_node_t**)ppAvl_root_node_ref,
		(avl_tree_node_t*)premove_node,cmp_method,pstatus);
}

PFX_INLINE void init_bbst_avl_node_default_func (balance_bst_node_t* PARAM_INOUT pnode)
{
	init_avl_tree_node_nokey_default((avl_tree_node_t*)pnode);
}


// red-black tree
PFX_INLINE const balance_bst_node_t* add_bbst_redblack_node_unsafe (balance_bst_node_t** PARAM_INOUT ppAvl_root_node_ref,
	balance_bst_node_t* PARAM_INOUT pAdd_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus)
{
	return (const balance_bst_node_t*)add_redblack_node_unsafe ((redblack_tree_node_t**)ppAvl_root_node_ref,
		(redblack_tree_node_t*)pAdd_node,
		cmp_method,
		pstatus);
}

PFX_INLINE balance_bst_node_t* remove_bbst_redblack_node_unsafe (balance_bst_node_t** PARAM_INOUT ppAvl_root_node_ref,
	balance_bst_node_t* PARAM_INOUT premove_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus)
{
	return (balance_bst_node_t*) remove_redblack_node_unsafe ((redblack_tree_node_t**)ppAvl_root_node_ref,
		(redblack_tree_node_t*)premove_node,cmp_method,pstatus);
}

PFX_INLINE void init_bbst_redblack_node_default_func (balance_bst_node_t* PARAM_INOUT pnode)
{
	init_redblack_tree_node_nokey_default((redblack_tree_node_t*)pnode);
}

PFX_C_EXTERN_END

#endif			//PFX_BALANCE_BST_H_
