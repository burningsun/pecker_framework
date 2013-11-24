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

typedef struct PFX_DATA_API st_tenary_search_tree_node_mask
{
	unsigned		m_valid_mask		: 2;		// 合法性判断位，用于假删除
	unsigned		m_cache_size			: 14;	// 附加缓存的大小,最大附加缓存0x3fff
	unsigned 	m_balance_mask	: 16;	// 平衡树标志位
}tenary_search_tree_node_mask_t;

// 三叉字符树中的二叉树节点部分
typedef struct PFX_DATA_API st_tenary_blance_part
{
	binary_search_tree_node_t*				m_parent_node;	// 父节点，主要用于优化遍历，以及可修改型迭代器的应用
	binary_search_tree_node_t*				m_pleft_node;		// 左子树
	binary_search_tree_node_t*				m_pright_node;	// 右子树
	tenary_search_tree_node_mask_t		m_mask;				// 内部标记，平衡树扩展应用

	pfx_share_string_t*								m_pstringkey;		//	 键
}_tenary_blance_part_t;

typedef union PFX_DATA_API un_tenary_blance_part
{
	_tenary_blance_part_t	m_blance_part;
	balance_bst_node_t		m_bbst_node;
}tenary_blance_part;

// 三叉字符树节点
typedef struct PFX_DATA_API st_tenary_tree_node tenary_tree_node_t;

struct PFX_DATA_API st_tenary_tree_node
{
	tenary_blance_part				m_blance_part;				//二叉树部分
	
	//linked_list_node_t				m_key_linked_node;		//链表部分
	tenary_tree_node_t*			m_prev_node;
	tenary_tree_node_t*			m_pnext_node;

	st_pfx_share_string_extern	m_string_key;				//字符串键
};

// 获取三叉树节点的字符串
PFX_INLINE const pfx_share_string_t* get_tenary_tree_node_string (const tenary_tree_node_t* pnode);
// 获取三叉树节点附加缓存的大小
PFX_INLINE size_t get_tenary_tree_node_cache_size (const tenary_tree_node_t* pnode);

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
	(NODE)->m_base_node.m_blance_part.m_blance_part.m_mask.m_cache_size = sizeof ((NODE)->m_cache);\
};

// 比较字符串函数指针类型
typedef int (*tenery_tree_string_key_cmp_func) (const pfx_share_string_t* pstra,const pfx_share_string_t* pstrb);
typedef int (*tenery_tree_same_string_key_cmp_func) (const pfx_share_string_t* pstra,const pfx_share_string_t* pstrb,pfx_nsize_t* PARAM_INOUT nsame_count);

// 三叉树内部调用方法
typedef struct PFX_DATA_API st_tenary_tree_internal_method
{
	size_t																			m_defualt_cache_size;
	const IAllocator*														m_nodes_allocator;
	const IAllocator*														m_key_string_allocator;
	compare_two_value_func										m_find_cmp_method;
	compare_two_value_func										m_add_cmp_method;
	tenery_tree_same_string_key_cmp_func				m_find_same_cmp_method;
	add_bbst_node_unsafe_func									m_bst_add_method;
	remove_bbst_node_unsafe_func							m_bst_remove_method;
	init_bbst_node_default_func									m_bst_default_init_method;
}tenary_tree_internal_method_t;

// 初始化三叉树内部调用方法对象
PFX_INLINE tenary_tree_internal_method_t* init_tenary_tree_internal_method (
	tenary_tree_internal_method_t* PARAM_INOUT pmethod_obj,
	size_t								defualt_cache_size,
	const IAllocator*			pnodes_allocator,
	const IAllocator*			pkey_string_allocator,
	compare_two_value_func	pfind_cmp_method,
	compare_two_value_func	padd_cmp_method,
	tenery_tree_same_string_key_cmp_func	find_same_cmp_method,
	add_bbst_node_unsafe_func	pbst_add_method,
	remove_bbst_node_unsafe_func	pbst_remove_method,
	init_bbst_node_default_func pbst_default_init_method);


// 初始化三叉树节点
PFX_INLINE tenary_tree_node_t* init_tenary_tree_node_no_cache_change (tenary_tree_node_t* PARAM_INOUT pnode,
	size_t char_size,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method);

PFX_INLINE tenary_tree_node_t* init_tenary_tree_node (tenary_tree_node_t* PARAM_INOUT pnode,
	size_t char_size,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method);

// 三叉树用的字符比较函数
PFX_INLINE int tenery_tree_string_key_cmp_for_find_defualt_  (const pfx_share_string_t* pstra,const pfx_share_string_t* pstrb);
PFX_INLINE int tenery_tree_string_key_cmp_for_find_same_defualt  (const pfx_share_string_t* pstra,const pfx_share_string_t* pstrb,
	pfx_nsize_t* PARAM_INOUT nsame_count);

PFX_INLINE int tenery_tree_string_key_cmp_for_find_defualt  (pfx_long_t pstra,pfx_long_t pstrb);


//////////////////////////////////////////////////////////////////////////
// 创建一个三叉树节点
PFX_DATA_API tenary_tree_node_t*  new_tenary_tree_node (size_t char_size,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method);

// 删除三叉树节点的内存空间 (仅删内存，不涉及链表操作)
PFX_DATA_API pfx_result_t  delete_tenary_tree_node (tenary_tree_node_t* PARAM_INOUT pdel_node,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method);

//查找结点
PFX_DATA_API const tenary_tree_node_t*  find_node_form_tenary_tree (const tenary_tree_node_t* PARAM_IN proot_node,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method,
	const pfx_char_t* PARAM_IN pkey_string, 
	size_t char_size,
	size_t key_string_buffer_size);

PFX_DATA_API const tenary_tree_node_t*  find_first_near_node_form_tenary_tree (const tenary_tree_node_t* PARAM_IN proot_node,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method,	
	const pfx_char_t* PARAM_IN pkey_string, 
	size_t char_size,
	size_t key_string_buffer_size);

//插入节点
PFX_DATA_API const tenary_tree_node_t*  add_tenary_tree_node_unsafe (tenary_tree_node_t** PARAM_INOUT pproot_node,
	const tenary_tree_internal_method_t* ptenary_tree_method,
	const pfx_char_t* PARAM_IN pkey_string, 
	size_t char_size,
	size_t key_string_buffer_size,
	tenary_tree_node_t* PARAM_INOUT paddnode,	
	pfx_result_t* PARAM_INOUT pstatus);

//移除节点
PFX_DATA_API const tenary_tree_node_t*  remove_tenary_tree_node_unsafe (tenary_tree_node_t** PARAM_INOUT pproot_node,
	const tenary_tree_internal_method_t* ptenary_tree_method,
	tenary_tree_node_t* PARAM_INOUT premove_node,	
	pfx_result_t* PARAM_INOUT pstatus);



//////////////////////////////////////////////////////////////////////////
PFX_INLINE const pfx_share_string_t* get_tenary_tree_node_string (const tenary_tree_node_t* pnode)
{
	RETURN_INVALID_RESULT (null == pnode,null);
	return (pfx_share_string_t*)&(pnode->m_string_key);
}

PFX_INLINE size_t get_tenary_tree_node_cache_size (const tenary_tree_node_t* pnode)
{
	RETURN_INVALID_RESULT (null == pnode,0);
	return pnode->m_blance_part.m_blance_part.m_mask.m_cache_size;
}

PFX_INLINE tenary_tree_internal_method_t* init_tenary_tree_internal_method (
	tenary_tree_internal_method_t* PARAM_INOUT pmethod_obj,
	size_t								defualt_cache_size,
	const IAllocator*			pnodes_allocator,
	const IAllocator*			pkey_string_allocator,
	compare_two_value_func	pfind_cmp_method,
	compare_two_value_func	padd_cmp_method,
	tenery_tree_same_string_key_cmp_func	find_same_cmp_method,
	add_bbst_node_unsafe_func	pbst_add_method,
	remove_bbst_node_unsafe_func	pbst_remove_method,
	init_bbst_node_default_func pbst_default_init_method)
{
	RETURN_INVALID_RESULT ((null == pmethod_obj ||
		defualt_cache_size > 0x3FFF ||
		null == pnodes_allocator ||
		null == pkey_string_allocator ||
		null == pfind_cmp_method ||
		null == padd_cmp_method ||
		null == find_same_cmp_method ||
		null == pbst_add_method ||
		null == pbst_remove_method ||
		null == pbst_default_init_method),null);
	pmethod_obj->m_defualt_cache_size = defualt_cache_size;
	pmethod_obj->m_nodes_allocator = pnodes_allocator;
	pmethod_obj->m_key_string_allocator = pkey_string_allocator;
	pmethod_obj->m_find_cmp_method = pfind_cmp_method;
	pmethod_obj->m_find_same_cmp_method = find_same_cmp_method;
	pmethod_obj->m_bst_add_method = pbst_add_method;
	pmethod_obj->m_bst_remove_method = pbst_remove_method;
	pmethod_obj->m_bst_default_init_method = pbst_default_init_method;

	return pmethod_obj;
}

// 初始化三叉树节点
PFX_INLINE tenary_tree_node_t* init_tenary_tree_node_no_cache_change (tenary_tree_node_t* PARAM_INOUT pnode,
	size_t char_size,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method)
{
	pfx_result_t status;
	RETURN_INVALID_RESULT (null == pnode || null == ptenary_tree_method || 
		null == ptenary_tree_method->m_bst_default_init_method,null);

	ptenary_tree_method->m_bst_default_init_method ((balance_bst_node_t*)pnode);
	pnode->m_blance_part.m_blance_part.m_pstringkey = (pfx_share_string_t*)&(pnode->m_string_key);

	PFX_INIT_LIST_NODE (pnode);
	init_share_string_by_buffer (char_size,sizeof(st_pfx_share_string_extern),(pfx_char_t*)&(pnode->m_string_key),&status);

	if (PFX_STATUS_OK != status)
	{
		clear_share_string ((pfx_share_string_t*)&(pnode->m_string_key),ptenary_tree_method->m_key_string_allocator);
		return null;
	}

	status = set_binary_search_tree_node_valid ((binary_search_tree_node_t*)pnode,pfx_true);
	
	if (PFX_STATUS_OK != status)
	{
		clear_share_string ((pfx_share_string_t*)&(pnode->m_string_key),ptenary_tree_method->m_key_string_allocator);
		return null;
	}

	return pnode;
}

PFX_INLINE tenary_tree_node_t* init_tenary_tree_node (tenary_tree_node_t* PARAM_INOUT pnode,
	size_t char_size,
	const tenary_tree_internal_method_t* PARAM_IN ptenary_tree_method)
{
	pfx_result_t status;
	RETURN_INVALID_RESULT (null == pnode || null == ptenary_tree_method || 
		null == ptenary_tree_method->m_bst_default_init_method || 
		ptenary_tree_method->m_defualt_cache_size > 0x3FFF,null);

	ptenary_tree_method->m_bst_default_init_method ((balance_bst_node_t*)pnode);
	pnode->m_blance_part.m_blance_part.m_pstringkey = (pfx_share_string_t*)&(pnode->m_string_key);

	PFX_INIT_LIST_NODE (pnode);

	pnode->m_blance_part.m_blance_part.m_mask.m_cache_size = ptenary_tree_method->m_defualt_cache_size;
	init_share_string_by_buffer (char_size,sizeof(st_pfx_share_string_extern),(pfx_char_t*)&(pnode->m_string_key),&status);

	if (PFX_STATUS_OK != status)
	{
		clear_share_string ((pfx_share_string_t*)&(pnode->m_string_key),ptenary_tree_method->m_key_string_allocator);
		return null;
	}

	status = set_binary_search_tree_node_valid ((binary_search_tree_node_t*)pnode,pfx_true);


	if (PFX_STATUS_OK != status)
	{
		clear_share_string ((pfx_share_string_t*)&(pnode->m_string_key),ptenary_tree_method->m_key_string_allocator);
		return null;
	}

	return pnode;
}

PFX_C_EXTERN_END



#endif			//PFX_BALANCE_TST_ALGORITHM_H_
