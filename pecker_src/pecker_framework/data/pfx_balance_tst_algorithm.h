/*
 * pfx_balance_tst_algorithm.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BALANCE_TST_ALGORITHM_H_
#define		PFX_BALANCE_TST_ALGORITHM_H_

#include "pecker_value_compare.h"
#include "pfx_balance_bst.h"
#include "pfx_share_string.h"
#include "pfx_list.h"

PFX_C_EXTERN_BEGIN

// 三叉字符树中的二叉树节点部分
typedef struct st_tenary_blance_part
{
	binary_search_tree_node_t*				m_parent_node;	// 父节点，主要用于优化遍历，以及可修改型迭代器的应用
	binary_search_tree_node_t*				m_pleft_node;		// 左子树
	binary_search_tree_node_t*				m_pright_node;	// 右子树
	binary_search_tree_node_mask_t		m_mask;				// 内部标记，平衡树扩展应用

	pfx_share_string_t*								m_pstringkey;		//	 键
}_tenary_blance_part_t;

typedef union un_tenary_blance_part
{
	_tenary_blance_part_t	m_blance_part;
	balance_bst_node_t		m_bbst_node;
}tenary_blance_part;

// 三叉字符树节点
typedef struct st_tenary_tree_node tenary_tree_node_t;

struct st_tenary_tree_node
{
	tenary_blance_part				m_blance_part;				//二叉树部分
	linked_list_node_t					m_key_linked_node;		//链表部分
	st_pfx_share_string_extern	m_string_key;				//字符串键
};

// 初始化三叉树节点
PFX_INLINE tenary_tree_node_t* init_tenary_tree_node (tenary_tree_node_t* PARAM_INOUT pnode,size_t char_size);

// 定义带有字符缓存的三叉树节点
#define  TENERY_CACHE_NODE_NAME(X)  st_tenary_tree_node_byte_cache_##X

#define  TENERY_CACHE_NODE(X) typedef struct  \
{	\
	tenary_tree_node_t		m_base_node;	\
	pfx_byte_t						m_cache[X];		\
}TENERY_CACHE_NODE_NAME(X);

// 通过宏来扩展定义带有字符缓存的三叉树节点
TENERY_CACHE_NODE(16);
TENERY_CACHE_NODE(32);
TENERY_CACHE_NODE(64);
TENERY_CACHE_NODE(128);
TENERY_CACHE_NODE(256);

typedef TENERY_CACHE_NODE_NAME(16) tenary_tree_node_byte_cache16_t;
typedef TENERY_CACHE_NODE_NAME(32) tenary_tree_node_byte_cache32_t;
typedef TENERY_CACHE_NODE_NAME(64) tenary_tree_node_byte_cache64_t;
typedef TENERY_CACHE_NODE_NAME(128) tenary_tree_node_byte_cache128_t;
typedef TENERY_CACHE_NODE_NAME(256) tenary_tree_node_byte_cache256_t;

// 初始化带有字符缓存的三叉树节点
#define INIT_TENERY_CACHE_NODE (NODE,CHAR_SIZE,PSATUS) \
{	\
	init_binary_search_tree_node_unsafe((binary_search_tree_node_t*)(NODE),null,null,null,(pfx_long_t)&((NODE)->m_base_node.m_string_key));\
	init_linked_list_node(&((NODE)->m_key_linked_node)); \
	init_share_string_by_buffer((CHAR_SIZE),sizeof(st_pfx_share_string_extern) + sizeof ((NODE)->m_cache),(pfx_char_t*)&((NODE)->m_base_node.m_string_key),PSATUS);\
};

// 比较字符串函数指针类型
typedef int (*tenery_tree_string_key_cmp_func) (const pfx_share_string_t* pstra,const pfx_share_string_t* pstrb);
typedef int (*tenery_tree_same_string_key_cmp_func) (const pfx_share_string_t* pstra,const pfx_share_string_t* pstrb,pfx_nsize_t* PARAM_INOUT nsame_count);

// 三叉树内部调用方法
typedef struct st_tenary_tree_internal_method
{
	const IAllocator*														m_nodes_allocator;
	const IAllocator*														m_key_string_allocator;
	compare_two_value_func										m_find_cmp_method;
	tenery_tree_same_string_key_cmp_func				m_find_same_cmp_method;
	add_bbst_node_unsafe_func									m_bst_add_method;
	remove_bbst_node_unsafe_func							m_bst_remove_method;
}tenary_tree_internal_method_t;

// 初始化三叉树内部调用方法对象
PFX_INLINE tenary_tree_internal_method_t* init_tenary_tree_internal_method (
	tenary_tree_internal_method_t* PARAM_INOUT pmethod_obj,
	const IAllocator*			pnodes_allocator,
	const IAllocator*			pkey_string_allocator,
	compare_two_value_func	pfind_cmp_method,
	tenery_tree_same_string_key_cmp_func	find_same_cmp_method,
	add_bbst_node_unsafe_func	pbst_add_method,
	remove_bbst_node_unsafe_func	pbst_remove_method);

// 三叉树用的字符比较函数
PFX_INLINE int tenery_tree_string_key_cmp_for_find_defualt_  (const pfx_share_string_t* pstra,const pfx_share_string_t* pstrb);
PFX_INLINE int tenery_tree_string_key_cmp_for_find_same_defualt  (const pfx_share_string_t* pstra,const pfx_share_string_t* pstrb,
	pfx_nsize_t* PARAM_INOUT nsame_count);

PFX_INLINE int tenery_tree_string_key_cmp_for_find_defualt  (pfx_long_t pstra,pfx_long_t pstrb);


//////////////////////////////////////////////////////////////////////////
//查找结点
const tenary_tree_node_t* find_node_form_tenary_tree (const tenary_tree_node_t* PARAM_IN proot_node,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method,
	const pfx_char_t* PARAM_IN pkey_string, 
	size_t char_size,
	size_t key_string_buffer_size);

const tenary_tree_node_t* find_first_near_node_form_tenary_tree (const tenary_tree_node_t* PARAM_IN proot_node,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method,	
	const pfx_char_t* PARAM_IN pkey_string, 
	size_t char_size,
	size_t key_string_buffer_size);

//插入节点
const tenary_tree_node_t* add_tenary_tree_node_unsafe (tenary_tree_node_t** PARAM_INOUT pproot_node,
	const tenary_tree_internal_method_t* ptenary_tree_method,
	const pfx_char_t* PARAM_IN pkey_string, 
	size_t char_size,
	size_t key_string_buffer_size,
	tenary_tree_node_t* PARAM_INOUT paddnode,	
	pfx_result_t* PARAM_INOUT pstatus);

//移除节点
const tenary_tree_node_t* remove_tenary_tree_node_unsafe (tenary_tree_node_t** PARAM_INOUT pproot_node,
	const tenary_tree_internal_method_t* ptenary_tree_method,
	tenary_tree_node_t* PARAM_INOUT premove_node,	
	pfx_result_t* PARAM_INOUT pstatus);



//////////////////////////////////////////////////////////////////////////

PFX_INLINE tenary_tree_node_t* init_tenary_tree_node (tenary_tree_node_t* PARAM_INOUT pnode,size_t char_size)
{
	pfx_result_t status;
	init_binary_search_tree_node_unsafe((binary_search_tree_node_t*)(pnode),null,null,null,(pfx_long_t)&(pnode->m_string_key));
	init_linked_list_node(&(pnode->m_key_linked_node)); 
	init_share_string_by_buffer(char_size,sizeof(st_pfx_share_string_extern),(pfx_char_t*)&(pnode->m_string_key),&status);
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);
	return pnode;
}

PFX_INLINE tenary_tree_internal_method_t* init_tenary_tree_internal_method (
	tenary_tree_internal_method_t* PARAM_INOUT pmethod_obj,
	const IAllocator*			pnodes_allocator,
	const IAllocator*			pkey_string_allocator,
	compare_two_value_func	pfind_cmp_method,
	tenery_tree_same_string_key_cmp_func	find_same_cmp_method,
	add_bbst_node_unsafe_func	pbst_add_method,
	remove_bbst_node_unsafe_func	pbst_remove_method)
{
	RETURN_INVALID_RESULT ((null == pmethod_obj ||
		null == pnodes_allocator ||
		null == pkey_string_allocator ||
		null == pfind_cmp_method ||
		null == find_same_cmp_method ||
		null == pbst_add_method ||
		null == pbst_remove_method),null);

	pmethod_obj->m_nodes_allocator = pnodes_allocator;
	pmethod_obj->m_key_string_allocator = pkey_string_allocator;
	pmethod_obj->m_find_cmp_method = pfind_cmp_method;
	pmethod_obj->m_find_same_cmp_method = find_same_cmp_method;
	pmethod_obj->m_bst_add_method = pbst_add_method;
	pmethod_obj->m_bst_remove_method = pbst_remove_method;
	return pmethod_obj;
}

PFX_C_EXTERN_END



#endif			//PFX_BALANCE_TST_ALGORITHM_H_
