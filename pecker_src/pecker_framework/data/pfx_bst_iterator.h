/*
 * pfx_bst_iterator.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BST_ITERATOR_H_
#define		PFX_BST_ITERATOR_H_


#include "pfx_bst_algorithm.h"
#include "pecker_collection.h"

PFX_C_EXTERN_BEGIN
//////////////////////////////////////////////////////////////////////////
// 中序遍历 & 逆中序遍历
PFX_DATA_API const binary_search_tree_node_t*  get_binary_search_tree_inorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node);
PFX_DATA_API const binary_search_tree_node_t*  get_binary_search_tree_inorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node);

PFX_DATA_API const binary_search_tree_node_t*  binary_search_tree_inorder_increase (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
																																	const binary_search_tree_node_t* PARAM_IN proot_node);

PFX_DATA_API const binary_search_tree_node_t*  binary_search_tree_inorder_decrease (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
																																	const binary_search_tree_node_t* PARAM_IN proot_node);

//////////////////////////////////////////////////////////////////////////
// 后序遍历
PFX_DATA_API const binary_search_tree_node_t*  get_binary_search_tree_posorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node);

PFX_DATA_API const binary_search_tree_node_t*  get_binary_search_tree_posorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node);

PFX_DATA_API const binary_search_tree_node_t*  binary_search_tree_posorder_increase (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
	const binary_search_tree_node_t* PARAM_IN proot_node);

//////////////////////////////////////////////////////////////////////////
// 逆后序遍历
PFX_DATA_API const binary_search_tree_node_t*  get_binary_search_tree_reverse_posorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node);

PFX_DATA_API const binary_search_tree_node_t*  get_binary_search_tree_reverse_posorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node);

PFX_DATA_API const binary_search_tree_node_t*  binary_search_tree_reverse_posorder_increase (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
	const binary_search_tree_node_t* PARAM_IN proot_node);

//////////////////////////////////////////////////////////////////////////
// 先序遍历
typedef struct PFX_DATA_API st_preorder_iterator
{
	const binary_search_tree_node_t*	m_pcurrent_node;
	pfx_enum_t											m_next_node_type;
	pfx_result_t											m_last_result;
}pfx_preorder_iterator_t;

typedef enum PFX_DATA_API enum_preorder_iterator_next_node_type
{
	PREORDER_NEXT_SUB_ROOT_RIGHT = 0,
	PREORDER_NEXT_SUB_ROOT_LEFT,
	PREORDER_NEXT_LEFT,
	PREORDER_NEXT_RIGHT,
	PREORDER_NEXT_BEGIN,
	PREORDER_NEXT_END,
	PREORDER_FIN,

	enum_preorder_iterator_next_node_type_COUNT
}pfx_preorder_iterator_next_node_type_t;

PFX_DATA_API const binary_search_tree_node_t*  get_binary_search_tree_preorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node);

PFX_DATA_API const binary_search_tree_node_t*  get_binary_search_tree_preorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node);

PFX_DATA_API const pfx_preorder_iterator_t*  get_binary_search_tree_preorder_begin_iterator(const binary_search_tree_node_t* PARAM_IN proot_node,pfx_preorder_iterator_t* PARAM_INOUT piterator);

PFX_DATA_API const pfx_preorder_iterator_t*  get_binary_search_tree_preorder_end_iterator(const binary_search_tree_node_t* PARAM_IN proot_node,pfx_preorder_iterator_t* PARAM_INOUT piterator);

PFX_DATA_API const pfx_preorder_iterator_t*  binary_search_tree_preorder_increase (pfx_preorder_iterator_t* PARAM_INOUT piterator,const binary_search_tree_node_t* PARAM_IN proot_node);



PFX_C_EXTERN_END


#endif			//PFX_BST_ITERATOR_H_
