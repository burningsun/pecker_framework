/*
 * pfx_bst_iterator.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城 (cut / cutxyz)
 */

#ifndef		PFX_BST_ITERATOR_H_
#define		PFX_BST_ITERATOR_H_


#include "pfx_bst_algorithm.h"
#include "pecker_collection.h"

PFX_C_EXTERN_BEGIN

const binary_search_tree_node_t* get_binary_search_tree_inorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node);
const binary_search_tree_node_t* get_binary_search_tree_inorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node);

const binary_search_tree_node_t* binary_search_tree_inorder_increase (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
																																	const binary_search_tree_node_t* PARAM_IN proot_node);

const binary_search_tree_node_t* binary_search_tree_inorder_decrease (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
																																	const binary_search_tree_node_t* PARAM_IN proot_node);



pfx_result_t binary_search_tree_preorder_travel_recursion(const binary_search_tree_node_t* PARAM_IN proot_node,
																					const binary_search_tree_node_t* PARAM_IN pmin_left_node,
																					const binary_search_tree_node_t* PARAM_IN pmax_right_node,
																					collection_t*	PARAM_INOUT	ptravel_collection);

pfx_result_t binary_search_tree_posorder_travel_recursion(const binary_search_tree_node_t* PARAM_IN proot_node,
																					const binary_search_tree_node_t* PARAM_IN pmin_left_node,
																					const binary_search_tree_node_t* PARAM_IN pmax_right_node,
																					collection_t*	PARAM_INOUT	ptravel_collection);

PFX_C_EXTERN_END


#endif			//PFX_BST_ITERATOR_H_
