/*
* pfx_ctst.h
*
*  Created on: 2015-2-3
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_CTST_H_
#define		PFX_CTST_H_

#include "pfx_cbst.h"
#include "pfx_cbst_codes.h"

#include "pfx_cstring.h"
#include "pfx_cstring_codes.h"

PECKER_BEGIN


// 三叉树基本操作
// 最大最小值
template < class __BST_node_minmax >
struct PFX_DATA_TEMPLATE_API TST_node_minmax
{
	typedef __BST_node_minmax             bst_minmax_t;
	typedef typename bst_minmax_t::node_t node_t;
	typedef TST_node_minmax< bst_minmax_t > minmax_t;


	
	static PFX_INLINE const node_t* max_node(const node_t* root_node_ptr, const node_t* null_node_ptr = null);
	static PFX_INLINE const node_t* min_node(const node_t* root_node_ptr, const node_t* null_node_ptr = null);

	static PFX_INLINE node_t* max_node(node_t* root_node_ptr, const node_t* null_node_ptr = null);
	static PFX_INLINE node_t* min_node(node_t* root_node_ptr, const node_t* null_node_ptr = null);
};

// 基本初始化
template < class __BST_node_init >
struct PFX_DATA_TEMPLATE_API TST_node_init
{
	typedef __BST_node_init              bst_init_t;
	typedef typename bst_init_t::node_t	 node_t;
	typedef typename node_t::key_char_t  key_char_t;
	typedef TST_node_init< bst_init_t >  init_t;
	

	static PFX_INLINE result_t init_node_leaves(node_t* PARAM_INOUT tree_node_ptr,
		node_t* PARAM_IN left_node_ptr = null,
		node_t* PARAM_IN right_node_ptr = null,
		node_t* PARAM_IN parent_node_ptr = null,
		bool    init_mid_channal = true,
		node_t* PARAM_IN mid_parent_node_ptr = null,
		node_t* PARAM_IN mid_leaf_node_ptr = null);

	static PFX_INLINE result_t init_node_leaves(node_t& PARAM_INOUT tree_node,
		node_t* PARAM_IN left_node_ptr = null,
		node_t* PARAM_IN right_node_ptr = null,
		node_t* PARAM_IN parent_node_ptr = null,
		bool    init_mid_channal = true,
		node_t* PARAM_IN mid_parent_node_ptr = null,
		node_t* PARAM_IN mid_leaf_node_ptr = null);
	//////////////////////////////////////////////////////////////////////////
	static PFX_INLINE result_t set_middle_node(node_t* PARAM_INOUT tree_node_ptr,
		node_t* PARAM_IN mid_leaf_node_ptr = null);

	static PFX_INLINE result_t set_middle_node(node_t& PARAM_INOUT tree_node,
		node_t* PARAM_IN mid_leaf_node_ptr = null);
	//////////////////////////////////////////////////////////////////////////
	static PFX_INLINE result_t set_middle_parent_node(node_t* PARAM_INOUT tree_node_ptr,
		node_t* PARAM_IN mid_parent_node_ptr = null);

	static PFX_INLINE result_t set_middle_parent_node(node_t& PARAM_INOUT tree_node,
		node_t* PARAM_IN mid_parent_node_ptr = null);

	//////////////////////////////////////////////////////////////////////////
	static PFX_INLINE result_t set_null_element_node(node_t* PARAM_INOUT tree_node_ptr, bool enable);

	static PFX_INLINE result_t set_null_element_node(node_t& PARAM_INOUT tree_node, bool enable);

	static PFX_INLINE bool is_leaf_node(const node_t* PARAM_IN tree_node_ptr);
	static PFX_INLINE bool is_null_elem_node(const node_t* PARAM_IN tree_node_ptr);
	//////////////////////////////////////////////////////////////////////////
	static PFX_INLINE result_t set_node_string(node_t* PARAM_INOUT tree_node_ptr, 
		const key_char_t* PARAM_IN str_ptr,
		usize__t str_size);

	static PFX_INLINE result_t set_node_string(node_t& PARAM_INOUT tree_node,
		const key_char_t* PARAM_IN str_ptr,
		usize__t str_size);

	static PFX_INLINE  node_t* sepreate_node(node_t* PARAM_INOUT node_ptr,
		node_t* PARAM_OUT sub_node_ptr,
		usize__t chars_offset,
		result_t& PARAM_OUT status_);

};


// 通过字符串查找迭节点
template < class tst_node, class __find_same_string >
struct PFX_DATA_TEMPLATE_API TST_find_string_node
{
	typedef __find_same_string                        find_string_t;
	typedef tst_node                                  node_t;
	typedef typename find_string_t::element_t         key_char_t;
	typedef	TST_find_string_node< find_string_t >	  find_t;

	static PFX_INLINE const node_t* find_node(const key_char_t* PARAM_IN __chars_ptr,
		usize__t chars_count,
		const node_t* PARAM_IN root_node_ptr);

	static PFX_INLINE const node_t* find_near_node(const key_char_t* PARAM_IN __chars_ptr,
		usize__t chars_count,
		const node_t* PARAM_IN root_node_ptr,
		usize__t& PARAM_OUT   match_count,
		usize__t& PARAM_OUT   last_node_match_count,
		int& PARAM_INOUT last_cmp_result);

	static PFX_INLINE const node_t* find_last_same_node(const key_char_t* PARAM_IN __chars_ptr,
		usize__t chars_count,
		const node_t* PARAM_IN root_node_ptr,
		usize__t& PARAM_OUT   match_count,
		usize__t& PARAM_INOUT  node_chars_offset,
		int& PARAM_INOUT last_cmp_result);
};


// 插入节点
template <
	class __find_same_string,
	class __BST_insert_node
	 >
struct PFX_DATA_TEMPLATE_API TST_insert_node
{
	typedef __BST_insert_node                         bst_insert_t;
	typedef typename bst_insert_t::node_t             node_t;
	typedef typename bst_insert_t::compare_two_node_t compare_two_node_t;

	typedef TST_insert_node< bst_insert_t >                    insert_t;
	typedef TST_node_init< typename bst_insert_t::init_t >     init_t;
	typedef TST_find_string_node< node_t, __find_same_string > find_t;
	typedef typename find_t::key_char_t	                       key_char_t;

	static PFX_INLINE const node_t* add_node(
		const key_char_t* PARAM_IN __chars_ptr,
		usize__t chars_count,
		node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT add_node_ptr,
		usize__t& PARAM_OUT match_count,
		usize__t& PARAM_OUT last_node_match_count,
		result_t& PARAM_OUT status_);
};

//移除
template < class __BST_node_remove >
struct PFX_DATA_TEMPLATE_API TST_node_remove
{
	typedef typename __BST_node_remove::node_t       node_t;
	typedef typename __BST_node_remove::bst_remove_t basebst_remove_t;
	typedef typename __BST_node_remove               bst_remove_t;

	typedef TST_node_remove< bst_remove_t >  remove_t;

	typedef TST_node_init< typename bst_remove_t::init_t >     init_t;

	static PFX_INLINE node_t* remove_node(node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT remove_node_ptr,
		result_t& __status);
	static PFX_INLINE node_t* remove_next(node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT remove_node_ptr,
		result_t& __status);
};

//
//////////////////////////////////////////////////////////////////////////
// 带内存动态分配的插入与删除
template < 
	class __BST_new_delete, 
	class __find_same_string,
	class __BST_insert_node,
	class __BST_node_remove >
struct PFX_DATA_TEMPLATE_API TST_node_insert_remove
{
	typedef __BST_new_delete                          new_delete_t;
	typedef typename new_delete_t::node_t             node_t;

	//////////////////////////////////////////////////////////////////////////
	typedef __BST_insert_node                         bst_insert_t;
	typedef typename bst_insert_t::compare_two_node_t compare_two_node_t;

	//////////////////////////////////////////////////////////////////////////
	typedef TST_insert_node< bst_insert_t >                    insert_t;
	typedef TST_node_init< typename bst_insert_t::init_t >     init_t;
	typedef TST_find_string_node< node_t, __find_same_string > find_t;
	typedef typename find_t::key_char_t	                       key_char_t;

	typedef typename __BST_node_remove::bst_remove_t basebst_remove_t;
	typedef typename __BST_node_remove               bst_remove_t;

	typedef TST_node_remove< bst_remove_t >          remove_t;


	static PFX_INLINE const node_t* add_node(
		const key_char_t* PARAM_IN __chars_ptr,
		usize__t chars_count,
		node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT status_);

	static PFX_INLINE const node_t* add_node(
		node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT status_);

	static PFX_INLINE node_t* remove_node(node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT remove_node_ptr,
		result_t& __status);

	static PFX_INLINE const node_t* remove_node(
		const key_char_t* PARAM_IN __chars_ptr,
		usize__t chars_count,
		node_t*& PARAM_INOUT root_node_ptr,
		result_t& PARAM_OUT status_);

	static PFX_INLINE node_t* remove_next(node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT remove_node_ptr,
		result_t& __status);

	static PFX_INLINE result_t release_nodes(node_t*& PARAM_INOUT root_node_ptr,
		node_t*& PARAM_INOUT remove_node_ptr);

	static PFX_INLINE result_t release_nodes(
		const key_char_t* PARAM_IN __chars_ptr,
		usize__t chars_count,
		node_t*& PARAM_INOUT root_node_ptr);
};

PECKER_END

#endif			//PFX_CTST_H_
