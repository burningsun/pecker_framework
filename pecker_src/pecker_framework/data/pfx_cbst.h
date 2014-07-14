﻿/*
 * pfx_cbst.h
 *
 *  Created on: 2013-12-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBST_H_
#define		PFX_CBST_H_

#include "pecker_value_compare.h"
#include "pfx_data_traits.h"


PECKER_BEGIN

// 二叉树迭代器
// 中序遍历
template < class node_type_ >
struct PFX_DATA_TEMPALE_API const_bst_inoreder_operate
{
	typedef node_type_		node_t;
	static const node_t* begin (const node_t* PARAM_IN root_ptr);
	static const node_t* end (const node_t* PARAM_IN root_ptr);
	static const node_t* increase (const node_t* PARAM_IN root_ptr, const node_t* cur_node_ptr);
	static const node_t* decrease (const node_t* PARAM_IN root_ptr, const node_t* cur_node_ptr);
};
template < class friend_obj >
class PFX_DATA_TEMPALE_API const_bst_inorder_iterator
{
public:
	friend  friend_obj;
	typedef friend_obj																			friend_t;
	typedef typename friend_t::node_t											node_t;
	typedef typename const_bst_inoreder_operate< node_t >	operate_t;
	typedef typename const_bst_inorder_iterator < friend_t >	iterator_t;

private:
	const node_t*	m_cur_node_ptr;
	const node_t*	m_root_node_ptr;	
public:
	PFX_INLINE void init (const node_t* PARAM_IN cur_node_ptr)
	{
		m_cur_node_ptr = cur_node_ptr;
	}
protected:
	PFX_INLINE void init (const node_t* PARAM_IN root_node_ptr, 
						const node_t* PARAM_IN cur_node_ptr)
	{
		m_root_node_ptr	= root_node_ptr;
		m_cur_node_ptr = cur_node_ptr;
	}
public:
	const_bst_inorder_iterator():m_root_node_ptr(null),m_cur_node_ptr(null)
	{
		;
	}
	PFX_INLINE const node_t*	root_node () const
	{
		return m_root_node_ptr;
	}
	PFX_INLINE const node_t*	cur_node() const
	{
		return m_cur_node_ptr;
	}
	PFX_INLINE iterator_t*		cur_ptr ()
	{
		return this;
	}
	PFX_INLINE const iterator_t* cur_ptr () const
	{
		return this;
	}
	PFX_INLINE iterator_t*		to_begin ()
	{
		m_cur_node_ptr = operate_t::begin(m_root_node_ptr);
		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t*		to_end ()
	{
		m_cur_node_ptr = operate_t::end (m_root_node_ptr);
		
		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t*		increase ()
	{
		const node_t* next_node_ptr;
		next_node_ptr = operate_t::increase(m_root_node_ptr, m_cur_node_ptr);
		if (next_node_ptr)
		{
			m_cur_node_ptr = next_node_ptr;
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t*		decrease ()
	{
		const node_t* next_node_ptr;
		next_node_ptr = operate_t::decrease(m_root_node_ptr, m_cur_node_ptr);
		if (next_node_ptr)
		{
			m_cur_node_ptr = next_node_ptr;
			return this;
		}
		else
		{
			return null;
		}
	}
};

template < class node_type_ >
struct PFX_DATA_TEMPALE_API const_bst_preorder_operate
{
	typedef node_type_ node_t;
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

	typedef struct st_iterator
	{
		const node_t*	m_root_node_ptr;
		const node_t*	m_cur_node_ptr;
		enum_t				m_next_node_type;
		result_t				m_last_result;
		st_iterator () : m_root_node_ptr(null), m_cur_node_ptr(null),
			m_next_node_type (PREORDER_NEXT_LEFT),m_last_result(PFX_STATUS_OK){;}
	}st_iterator_t;

	static st_iterator_t* begin (const node_t* PARAM_IN root_ptr, 
														st_iterator_t&  PARAM_INOUT  cur_itr);
	static st_iterator_t* end (const node_t* PARAM_IN root_ptr,
														st_iterator_t&  PARAM_INOUT  cur_itr);
	static st_iterator_t* increase (st_iterator_t&  PARAM_INOUT  cur_itr);
};
// 前序遍历
template < class friend_obj >
class PFX_DATA_TEMPALE_API const_bst_preorder_iterator
{
public:
	friend  friend_obj;
	typedef friend_obj										friend_t;
	typedef typename friend_t::node_t		node_t;
	typedef typename const_bst_preorder_operate	< node_t >		operate_t;	
	typedef typename const_bst_preorder_iterator < friend_t >	iterator_t;

	typedef typename operate_t::st_iterator_t		st_iterator_t;
private:
	st_iterator_t m_iter;
protected:
	PFX_INLINE void init (const node_t* PARAM_IN root_node_ptr)
	{
		m_iter.m_root_node_ptr	= root_node_ptr;
	}
public:

	PFX_INLINE const node_t*	root_node () const
	{
		return m_iter.m_root_node_ptr;
	}
	PFX_INLINE const node_t*	cur_node() const
	{
		return m_iter.m_cur_node_ptr;
	}
	PFX_INLINE iterator_t*		cur_ptr ()
	{
		return this;
	}
	PFX_INLINE const iterator_t* cur_ptr () const
	{
		return this;
	}
	PFX_INLINE iterator_t*		to_begin ()
	{
		st_iterator_t* cur_ = operate_t::begin(m_iter.m_root_node_ptr, m_iter);
		if (cur_)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t*		to_end ()
	{
		st_iterator_t* cur_ = operate_t::end(m_iter.m_root_node_ptr, m_iter);
		if (cur_)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t*		increase ()
	{
		st_iterator_t* cur_ = operate_t::increase(m_iter);
		if (cur_)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
};

// 后序遍历
template < class node_type_ >
struct PFX_DATA_TEMPALE_API const_bst_posorder_operate
{
	typedef node_type_ node_t;

	static const node_t* begin (const node_t* PARAM_IN root_ptr);
	static const node_t* reverse_begin (const node_t* PARAM_IN root_ptr);
	static const node_t* end (const node_t* PARAM_IN root_ptr);
	static const node_t* increase (const node_t* PARAM_IN root_ptr, 
															const node_t* cur_node_ptr);
	static const node_t* reverse_increase (const node_t* PARAM_IN root_ptr, 
																			const node_t* cur_node_ptr);
};
template < class friend_obj >
class PFX_DATA_TEMPALE_API const_bst_posorder_iterator
{
public:
	friend  friend_obj;
	typedef friend_obj										friend_t;
	typedef typename friend_t::node_t		node_t;
	typedef typename const_bst_posorder_operate< node_t >		operate_t;
	typedef typename const_bst_posorder_iterator < friend_t >	iterator_t;

private:
	const node_t*	m_cur_node_ptr;
	const node_t*	m_root_node_ptr;
	bool_t					m_reversed;
protected:
	PFX_INLINE void init (const node_t* PARAM_IN root_node_ptr)
	{
		m_root_node_ptr	= root_node_ptr;
	}
public:
	const_bst_posorder_iterator():m_root_node_ptr(null),m_cur_node_ptr(null),m_reversed(PFX_BOOL_FALSE)
	{
		;
	}
	PFX_INLINE const node_t*	root_node () const
	{
		return m_root_node_ptr;
	}
	PFX_INLINE const node_t*	cur_node() const
	{
		return m_cur_node_ptr;
	}
	PFX_INLINE iterator_t*		cur_ptr ()
	{
		return this;
	}
	PFX_INLINE const iterator_t* cur_ptr () const
	{
		return this;
	}
	PFX_INLINE iterator_t*		to_begin ()
	{
		m_cur_node_ptr = operate_t::begin(m_root_node_ptr);
		if (m_cur_node_ptr)
		{
			m_reversed = PFX_BOOL_FALSE;
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t*		to_reverse_begin ()
	{
		m_cur_node_ptr = operate_t::reverse_begin(m_root_node_ptr);
		if (m_cur_node_ptr)
		{
			m_reversed = PFX_BOOL_TRUE;
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t*		to_end ()
	{
		m_cur_node_ptr = operate_t::end (m_root_node_ptr);

		if (m_cur_node_ptr)
		{
			return this;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t*		increase ()
	{
		const node_t* next_node_ptr;
		if (!m_reversed)
		{
			next_node_ptr = operate_t::increase(m_root_node_ptr, m_cur_node_ptr);
		}
		else
		{
			next_node_ptr = operate_t::reverse_increase(m_root_node_ptr, m_cur_node_ptr);
		}
		
		if (next_node_ptr)
		{
			m_cur_node_ptr = next_node_ptr;
			return this;
		}
		else
		{
			return null;
		}
	}
};

// 二叉树基本操作
// 最大最小值
template < class node_type_ >
struct PFX_DATA_TEMPALE_API BST_node_minmax
{
	typedef node_type_ node_t;
	typedef typename BST_node_minmax< node_t > minmax_t;

	static PFX_INLINE const node_t* max_node (const node_t* root_node_ptr, const node_t* null_node_ptr = null);
	static PFX_INLINE const node_t* min_node (const node_t* root_node_ptr, const node_t* null_node_ptr = null);

	static PFX_INLINE node_t* max_node (node_t* root_node_ptr, const node_t* null_node_ptr = null);
	static PFX_INLINE node_t* min_node (node_t* root_node_ptr, const node_t* null_node_ptr = null);
};

// 基本初始化
template < class node_type_ >
struct PFX_DATA_TEMPALE_API BST_node_init
{
	typedef node_type_ node_t;
	typedef typename BST_node_init< node_t > init_t;

	static PFX_INLINE result_t init_node_leaves (node_t* PARAM_INOUT tree_node_ptr,
		node_t* PARAM_IN left_node_ptr = null,
		node_t* PARAM_IN right_node_ptr = null,
		node_t* PARAM_IN parent_node_ptr = null);

	static PFX_INLINE result_t init_node_leaves (node_t& PARAM_INOUT tree_node,
		node_t* PARAM_IN left_node_ptr = null,
		node_t* PARAM_IN right_node_ptr = null,
		node_t* PARAM_IN parent_node_ptr = null);
};

//AVL旋转类型
typedef enum  enumAVLTREE_ROTATE_TYPE
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

// AVL树基本初始化
template < class node_type_ >
struct PFX_DATA_TEMPALE_API AVL_BST_node_init
{
	typedef node_type_ node_t;
	typedef typename BST_node_init< node_t >			BST_init_t;
	typedef typename AVL_BST_node_init< node_t >	init_t;
	typedef AVLTREE_ROTATE_t											AVLTREE_ROTATE_t;


	static PFX_INLINE result_t init_node_leaves (node_t* PARAM_INOUT tree_node_ptr,
		node_t* PARAM_IN left_node_ptr = null,
		node_t* PARAM_IN right_node_ptr = null,
		node_t* PARAM_IN parent_node_ptr = null);

	static PFX_INLINE result_t init_node_leaves (node_t& PARAM_INOUT tree_node,
		node_t* PARAM_IN left_node_ptr = null,
		node_t* PARAM_IN right_node_ptr = null,
		node_t* PARAM_IN parent_node_ptr = null);

	static PFX_INLINE nsize__t get_avl_height (const node_type_* PARAM_IN node_ptr);
	static PFX_INLINE nsize__t calculate_avl_height (const node_type_* PARAM_IN left_node_ptr,
		const node_type_* PARAM_IN right_node_ptr);
	static PFX_INLINE nsize__t calculate_avl_height (const node_type_* PARAM_IN node_ptr);
	static PFX_INLINE nsize__t calculate_avl_balance_value (const node_type_* PARAM_IN node_ptr);

	static PFX_INLINE void update_avl_height (node_type_* PARAM_IN node_ptr);

	static PFX_INLINE node_type_* avl_rr_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_ll_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_lr_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_rl_rotate (node_type_* PARAM_INOUT node_ptr);

	static PFX_INLINE AVLTREE_ROTATE_t avl_single_rotate (nsize__t balance_value,
		node_type_* PARAM_INOUT node_ptr, 
		node_type_* & PARAM_INOUT parent_ref_node_ptr);

	static PFX_INLINE result_t						avl_update_insert_rotate (node_type_* & PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT begin_node_ptr);

	static PFX_INLINE result_t						avl_update_fixed (node_type_* & PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT begin_node_ptr);
};

typedef enum  enumRB_COLOR
{
	BLACK_COLOR_NODE_TYPE = 0,
	RED_COLOR_NODE_TYPE,
	RB_COLOR_TYPE_COUNT
}RB_COLOR_t;

//黑红树基本初始化
template < class node_type_ >
struct PFX_DATA_TEMPALE_API RB_BST_node_init
{
	typedef node_type_ node_t;
	typedef typename BST_node_init< node_t >		BST_init_t;
	typedef typename RB_BST_node_init< node_t >	init_t;
	typedef RB_COLOR_t													RB_COLOR_t;


	static PFX_INLINE result_t	init_node_leaves (node_t* PARAM_INOUT tree_node_ptr,
		node_t* PARAM_IN left_node_ptr = null,
		node_t* PARAM_IN right_node_ptr = null,
		node_t* PARAM_IN parent_node_ptr = null);

	static PFX_INLINE result_t	init_node_leaves (node_t& PARAM_INOUT tree_node,
		node_t* PARAM_IN left_node_ptr = null,
		node_t* PARAM_IN right_node_ptr = null,
		node_t* PARAM_IN parent_node_ptr = null);

	static PFX_INLINE	void		set_rbt_color_red (node_type_* PARAM_INOUT pnode);
	static PFX_INLINE	void		set_rbt_color_black (node_type_* PARAM_INOUT pnode);
	static PFX_INLINE	bool	is_rbt_color_red (node_type_* PARAM_INOUT pnode);
	static PFX_INLINE	bool	is_rbt_color_black (node_type_* PARAM_INOUT pnode);
	static PFX_INLINE void	copy_tree_color (node_type_* PARAM_INOUT pdec_node,
		const node_type_* PARAM_IN psrc_node);

	static PFX_INLINE  void	rbt_left_rotate (node_type_ *& PARAM_INOUT root_node_ptr, 
		node_type_ *	PARAM_INOUT sentinel_node_ptr,
		node_type_ *	PARAM_INOUT node_ptr);

	static PFX_INLINE void	rbt_right_rotate (node_type_ *& PARAM_INOUT	root_node_ptr, 
		node_type_ *	PARAM_INOUT	sentinel_node_ptr,
		node_type_ *	PARAM_INOUT	node_ptr);

	static PFX_INLINE result_t rbt_add_rotate_fixup (node_type_ *& PARAM_INOUT root_node_ptr,
		node_type_*  PARAM_INOUT add_node_ptr);

	static PFX_INLINE result_t rbt_remove_rotate_fixup (node_type_ *& PARAM_INOUT root_ptr,
		node_type_*  PARAM_INOUT ref_node_ptr);
};

// 移除
template < class node_type_ >
struct PFX_DATA_TEMPALE_API BST_node_remove
{
	typedef node_type_ node_t;
	typedef typename BST_node_minmax< node_t >	minmax_t;
	typedef typename BST_node_remove< node_t >	remove_t;
	typedef typename BST_node_init< node_t >			init_t;


	static  node_t*		find_remove_replace_node (node_t* PARAM_IN remove_node_ptr,
		node_t*& PARAM_OUT sub_remove_node_ptr,
		const node_t* PARAM_IN null_node_ptr = null);

	static PFX_INLINE node_t* remove_node (node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT remove_node_ptr,
		result_t& __status);

	static result_t remove_node (node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT remove_node_ptr,
		const node_t* PARAM_IN null_node_ptr = null);

	static result_t	remove_node_internal (node_t*& PARAM_INOUT root_node_ptrptr,
		node_t* PARAM_INOUT remove_node_ptr,
		node_t* PARAM_INOUT sub_remove_node_ptr,
		node_t* PARAM_INOUT sub_remove_node_ref_ptr,
		const node_t* PARAM_IN null_node_ptr = null);
};
// AVL移除节点
template < class node_type_ >
struct PFX_DATA_TEMPALE_API AVL_BST_node_remove
{
	typedef node_type_ node_t;
	typedef typename BST_node_remove< node_t >			bst_remove_t;
	typedef typename AVL_BST_node_remove< node_t >	remove_t;
	typedef typename AVL_BST_node_init< node_t >			init_t;

	static node_t* remove_node (node_t*& PARAM_INOUT root_node_ptr,
															node_t* PARAM_INOUT remove_node_ptr,
															result_t& __status);
};
// 黑红树移除节点
template < class node_type_ >
struct PFX_DATA_TEMPALE_API RB_BST_node_remove
{
	typedef node_type_ node_t;
	typedef typename BST_node_remove< node_t >		bst_remove_t;
	typedef typename RB_BST_node_remove< node_t >	remove_t;
	typedef typename RB_BST_node_init< node_t >			init_t;

	static node_t* remove_node (node_t*& PARAM_INOUT root_node_ptr,
															node_t* PARAM_INOUT remove_node_ptr,
															result_t& __status);
};

// 通过节点查找结点
template < class node_type_, class compare_two_node_ >
struct PFX_DATA_TEMPALE_API BST_find_node
{
	typedef node_type_						node_t;
	typedef compare_two_node_		compare_two_node_t;

	typedef typename BST_node_minmax< node_t >										minmax_t;
	typedef typename BST_find_node< node_t, compare_two_node_t >	find_t;

	static const node_t*	find_node (const node_t* PARAM_IN key_node_ptr, 
																const node_t* PARAM_IN root_node_ptr);

	static const node_t*	find_near_node  (const node_t* PARAM_IN key_node_ptr,
																					const node_t* PARAM_IN root_node_ptr,
																					int& PARAM_INOUT last_cmp_result);
};
// 通过节点查找迭代器
template < class tree_type >
struct PFX_DATA_TEMPALE_API BST_find_iterator
{
	typedef tree_type																tree_t;
	typedef typename	tree_type::node_t							node_t;
	typedef  typename	node_t::	compare_two_node_t	compare_two_node_t;

	typedef typename BST_node_minmax< node_t >										minmax_t;
	typedef typename BST_find_node< node_t, compare_two_node_t >	node_find_t;
	typedef typename BST_find_iterator< tree_t >												find_t;	
	typedef  typename const_bst_inorder_iterator< tree_t >							const_iterator_t;

	static PFX_INLINE const_iterator_t*	find_node (const node_t* PARAM_IN key_node_ptr, 
																						const_iterator_t& itr);

	static PFX_INLINE const_iterator_t*	find_near_node  (const node_t* PARAM_IN key_node_ptr,
																				const_iterator_t& itr,
																				int& PARAM_INOUT last_cmp_result );
};
// 通过关键元素查找迭代器
template < class tree_type >
struct PFX_DATA_TEMPALE_API BST_find_element
{
	typedef tree_type																	tree_t;
	typedef typename	tree_type::element_t							element_t;
	typedef typename	tree_type::node_t								node_t;
	typedef  typename	tree_t::cmp_t										compare_two_node_t;

	typedef  typename	compare_two_node_t::	compare_two_elemen_t	compare_two_elemen_t;
	

	typedef typename BST_node_minmax< node_t >										minmax_t;
	typedef typename BST_find_node< node_t, compare_two_node_t >	find_t;

	typedef  typename const_bst_inorder_iterator< tree_t > const_iterator_t;

	static const_iterator_t*	find_node (const element_t& PARAM_IN __key, 
																	 const_iterator_t& itr);

	static const_iterator_t*	find_near_node  (const element_t& PARAM_IN __key,
																				const_iterator_t& itr,
																				int& PARAM_INOUT last_cmp_result);
};

// 插入
template < class node_type_, class compare_two_node_ >
struct PFX_DATA_TEMPALE_API BST_insert_node
{
	typedef node_type_						node_t;
	typedef compare_two_node_		compare_two_node_t;
		
	typedef typename BST_node_init< node_t >												init_t;
		typedef typename BST_find_node< node_t, compare_two_node_t >find_t;
	typedef typename BST_insert_node< node_t, compare_two_node_t >	insert_t;

	static result_t add_node (node_t*& PARAM_INOUT root_node_ptr,
		node_t* PARAM_INOUT add_node_ptr,
		node_t*& PARAM_INOUT added_node_ptr);

	static PFX_INLINE const node_t* add_node (node_t*& PARAM_INOUT root_node_ptr,
																node_t* PARAM_INOUT add_node_ptr,
																result_t& PARAM_OUT status_);
};
// AVL 树插入节点
template < class node_type_, class compare_two_node_ >
struct PFX_DATA_TEMPALE_API AVL_BST_insert_node
{
	typedef node_type_						node_t;
	typedef compare_two_node_		compare_two_node_t;

	typedef typename AVL_BST_node_init< node_t >													init_t;
	typedef typename BST_insert_node< node_t, compare_two_node_t >				BST_insert_t;
	typedef typename AVL_BST_insert_node< node_t, compare_two_node_t >	insert_t;

	static PFX_INLINE const node_t* add_node (node_t*& PARAM_INOUT root_node_ptr,
																					node_t* PARAM_INOUT add_node_ptr,
																					result_t& PARAM_OUT status_);
};
// 黑红树插入节点
template < class node_type_, class compare_two_node_ >
struct PFX_DATA_TEMPALE_API RB_BST_insert_node
{
	typedef node_type_						node_t;
	typedef compare_two_node_		compare_two_node_t;

	typedef typename RB_BST_node_init< node_t >													init_t;
	typedef typename BST_insert_node< node_t, compare_two_node_t >			BST_insert_t;
	typedef typename RB_BST_insert_node< node_t, compare_two_node_t >	insert_t;

	static PFX_INLINE const node_t* add_node (node_t*& PARAM_INOUT root_node_ptr,
																					node_t* PARAM_INOUT add_node_ptr,
																					result_t& PARAM_OUT status_);
};

// 创建和删除节点
template < class node_alloc >
struct PFX_DATA_TEMPALE_API BST_new_delete
{
	typedef node_alloc											allocate_t;
	typedef typename allocate_t::element_t	node_t;
	typedef	typename	BST_new_delete< allocate_t >	new_delete_t;	

	static PFX_INLINE node_t* new_node ()
	{
		return allocate_t::allocate_object ();
	}
	static PFX_INLINE result_t delete_node (node_t*& PARAM_INOUT node_ptr)
	{
		return allocate_t::deallocate_object (node_ptr);
	}
};
// 清除
template < class node_alloc >
struct PFX_DATA_TEMPALE_API BST_clean
{
	typedef node_alloc											allocate_t;
	typedef typename allocate_t::element_t	node_t;

	typedef	typename BST_new_delete< node_alloc >	new_delete_t;
	typedef	typename BST_node_minmax< node_t >		minmax_t;

	typedef	typename BST_clean< node_alloc >				clean_t;

	static  result_t clean (node_t*& PARAM_INOUT root_dec_ptr);
};
// 克隆
template < class node_alloc, class node_init >
struct PFX_DATA_TEMPALE_API XBST_clone
{
	typedef node_alloc											allocate_t;
	typedef typename allocate_t::element_t	node_t;

	typedef	typename BST_new_delete< node_alloc >	new_delete_t;
	typedef	typename BST_node_minmax< node_t >		minmax_t;
	typedef	typename node_init											init_t;
	typedef	typename BST_clean< allocate_t >					clean_t;

	typedef	typename XBST_clone< allocate_t, init_t >		clone_t;

	static  result_t clone (node_t*& PARAM_INOUT root_dec_ptr, 
		const node_t* PARAM_IN other_root_ptr);
};

// 复制
template < class node_alloc, class node_insert >
struct PFX_DATA_TEMPALE_API XBST_copy
{
	typedef node_alloc											allocate_t;
	typedef typename allocate_t::element_t	node_t;

	typedef	typename BST_new_delete< node_alloc >	new_delete_t;
	typedef	typename BST_node_minmax< node_t >		minmax_t;
	typedef	typename node_insert										insert_t;
	typedef	typename BST_clean< allocate_t >					clean_t;

	typedef	typename XBST_copy< allocate_t, insert_t >		clone_t;

	static  result_t copy (node_t*& PARAM_INOUT root_dec_ptr, 
		const node_t* PARAM_IN other_root_ptr);
};

template < class node_alloc, class compare_two_node_ >
struct BST_operate
{
	typedef node_alloc																		allocate_t;
	typedef typename allocate_t::element_t								node_t;	
	typedef compare_two_node_													cmp_t;

	typedef	typename	BST_node_init< node_t >						init_t;
	typedef	typename	BST_new_delete< allocate_t >				new_delete_t;	
	typedef	typename	BST_node_minmax< node_t >				minmax_t;
	typedef	typename	BST_find_node< node_t, cmp_t >		find_t;	
	typedef	typename	BST_insert_node< node_t, cmp_t>		insert_t;
	typedef	typename	BST_node_remove< node_t >				remove_t;

	typedef typename	BST_clean < allocate_t >							clean_t;
	typedef typename	XBST_clone < allocate_t, init_t >			clone_t;
	typedef typename	XBST_copy < allocate_t, insert_t >		copy_t;
};

template < class node_alloc, class compare_two_node_ >
struct AVL_BST_operate
{
	typedef node_alloc																				allocate_t;
	typedef typename allocate_t::element_t										node_t;	
	typedef compare_two_node_															cmp_t;

	typedef	typename	AVL_BST_node_init< node_t >						init_t;
	typedef	typename	BST_new_delete< allocate_t >						new_delete_t;	
	typedef	typename	BST_node_minmax< node_t >						minmax_t;
	typedef	typename	BST_find_node< node_t, cmp_t >				find_t;	
	typedef	typename	AVL_BST_insert_node< node_t, cmp_t>		insert_t;
	typedef	typename	AVL_BST_node_remove< node_t >				remove_t;

	typedef typename	BST_clean < allocate_t >									clean_t;
	typedef typename	XBST_clone < allocate_t, init_t >					clone_t;
	typedef typename	XBST_copy < allocate_t, insert_t >				copy_t;
};

template < class node_alloc, class compare_two_node_ >
struct RB_BST_operate
{
	typedef node_alloc																				allocate_t;
	typedef typename allocate_t::element_t										node_t;	
	typedef compare_two_node_															cmp_t;

	typedef	typename	RB_BST_node_init< node_t >						init_t;
	typedef	typename	BST_new_delete< allocate_t >						new_delete_t;	
	typedef	typename	BST_node_minmax< node_t >						minmax_t;
	typedef	typename	BST_find_node< node_t, cmp_t >				find_t;	
	typedef	typename	RB_BST_insert_node< node_t, cmp_t>		insert_t;
	typedef	typename	RB_BST_node_remove< node_t >				remove_t;

	typedef typename	BST_clean < allocate_t >									clean_t;
	typedef typename	XBST_clone < allocate_t, init_t >					clone_t;
	typedef typename	XBST_copy < allocate_t, insert_t >				copy_t;
};

// 搜索二叉树
template <	class BST_operate_type >
class PFX_DATA_TEMPALE_API cbst
{
public:
	typedef BST_operate_type														operator_t;
	typedef	typename operator_t::allocate_t								allocate_t;
	typedef	typename operator_t::node_t									node_t;	
	typedef	typename operator_t::cmp_t									cmp_t;

	typedef	typename cbst< operator_t >									bst_t;
  
	typedef	typename operator_t::init_t										init_t;
	typedef	typename operator_t::new_delete_t						new_delete_t;	
	typedef	typename operator_t::minmax_t							minmax_t;
	typedef	typename operator_t::find_t									find_t;
	typedef	typename operator_t::insert_t									insert_t;
	typedef	typename operator_t::remove_t								remove_t;

	typedef typename	operator_t::clean_t									clean_t;
	typedef typename	operator_t::clone_t									clone_t;
	typedef typename	operator_t::copy_t									copy_t;

	typedef	typename	BST_find_iterator< bst_t >						itr_find_t;

	typedef	typename	const_bst_inorder_iterator< bst_t >	const_iterator_t;
	typedef	typename	const_iterator_t										const_inorder_itr_t;
	typedef	typename	const_bst_preorder_iterator< bst_t >	const_preorder_itr_t;
	typedef	typename	const_bst_posorder_iterator< bst_t >const_posorder_itr_t;

protected:
	node_t* m_root_ptr;
public:
	cbst ():m_root_ptr(null)
	{
		;
	}
	cbst (const bst_t& other_tree) throw (result_t)
	{
		if (&other_tree != this)
		{
			result_t status;
			m_root_ptr = null;
			status = clone(other_tree);
			if (PFX_STATUS_OK != status)
			{
				throw (status);
			}
		}
	}
	virtual ~cbst()
	{
		clean();
	}
public:
	PFX_INLINE void swap (bst_t& PARAM_IN other_tree)
	{
		node_t* temp_root_ptr	= other_tree.m_root_ptr;
		other_tree.m_root_ptr	= this->m_root_ptr;
		this->m_root_ptr				= temp_root_ptr;
	}

	PFX_INLINE result_t		copy (const node_t* PARAM_IN other_tree_root_ptr)
	{
		RETURN_INVALID_RESULT (!other_tree_root_ptr, PFX_STATUS_INVALID_PARAMS);
		RETURN_RESULT(other_tree_root_ptr == this->get_root(), PFX_STATUS_OK);
		bst_t clean_tree;
		result_t status = copy_t::copy (clean_tree.m_root_ptr, other_tree_root_ptr);
		if (PFX_STATUS_OK == status)
		{
			swap(clean_tree);
		}
		return status;
	}
	PFX_INLINE result_t		clean ()
	{
		return clean_t::clean(m_root_ptr);
	}
	PFX_INLINE result_t		clone (const bst_t& PARAM_IN other_bst)
	{
		RETURN_RESULT(&other_bst == this, PFX_STATUS_OK);
		bst_t clean_tree;
		result_t status = clone_t::clone(clean_tree.m_root_ptr, other_bst.m_root_ptr);
		if (PFX_STATUS_OK == status)
		{
			swap(clean_tree);
		}
		return status;
	}
	
	static PFX_INLINE node_t*	new_node () 
	{
		return new_delete_t::new_node();
	}
	static PFX_INLINE result_t		release_node (node_t*& PARAM_IN node_ptr)
	{
		return new_delete_t::delete_node(node_ptr);
	}

public:
	PFX_INLINE const_posorder_itr_t*	begin (const_posorder_itr_t& __itr) const
	{
		__itr.init(m_root_ptr);
		return __itr.to_begin();
	}
	PFX_INLINE const_posorder_itr_t*	end(const_posorder_itr_t& __itr) const
	{
		__itr.init(m_root_ptr);
		return __itr.to_end();
	}

	PFX_INLINE const_preorder_itr_t*	begin (const_preorder_itr_t& __itr) const
	{
		__itr.init (m_root_ptr);
		return __itr.to_begin();
	}

	PFX_INLINE const_preorder_itr_t*	end(const_preorder_itr_t& __itr) const
	{
		__itr.init(m_root_ptr);
		return __itr.to_end();
	}

	PFX_INLINE const_iterator_t*			begin (const_iterator_t& __itr) const
	{
		__itr.init(m_root_ptr, null);
		return __itr.to_begin();
	}
	PFX_INLINE const_iterator_t*			end(const_iterator_t& __itr) const
	{
		__itr.init(m_root_ptr, null);
		return __itr.to_end();
	}

	PFX_INLINE const_iterator_t*			set_itr (const node_t* PARAM_IN cur_node_ptr, 
																				const_iterator_t& __itr) const
	{
		if (__itr.root_node() == m_root_ptr)
		{
			__itr.init(cur_node_ptr);
			return &__itr;
		}
		else
		{
			return null;
		}
	}
protected:
	PFX_INLINE const_iterator_t*			set_itr_internal (const node_t* PARAM_IN cur_node_ptr, 
		const_iterator_t& __itr) const
	{
		__itr.init(m_root_ptr, cur_node_ptr);
		return &__itr;
	}
public:
	PFX_INLINE const node_t*					find(const node_t* PARAM_IN key_node_ptr) const
	{
		return find_t::find_node(key_node_ptr, m_root_ptr);
	}
	PFX_INLINE const_iterator_t*			find(const_iterator_t& __itr, 
																			const node_t* PARAM_IN key_node_ptr) const
	{
		const node_t*	find_node_ptr = find(key_node_ptr);
		if (find_node_ptr)
		{
			return set_itr (find_node_ptr, __itr);
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE const node_t*					find_near_node (const node_t* PARAM_IN key_node_ptr, 
																									int & last_cmp_result) const
	{
		return find_t::find_near_node(key_node_ptr, m_root_ptr, last_cmp_result);
	}
	PFX_INLINE const_iterator_t*			find_near_node (const_iterator_t& __itr, 
																									const node_t* PARAM_IN key_node_ptr, 
																									int & last_cmp_result) const
	{
		const node_t*	find_node_ptr = find_near_node(key_node_ptr,	last_cmp_result);
		if (find_node_ptr)
		{
			return set_itr (find_node_ptr, __itr);
		}
		else
		{
			return null;
		}
	}
public:
	PFX_INLINE const node_t*					add (node_t* PARAM_INOUT add_node_ptr,
																			result_t& PARAM_OUT status_)
	{
		return insert_t::add_node(m_root_ptr, add_node_ptr, status_);
	}

	PFX_INLINE node_t*							remove (node_t* PARAM_INOUT remove_node_ptr,
																					result_t& PARAM_OUT __status)
	{
		return remove_t::remove_node(m_root_ptr, remove_node_ptr, __status);
	}

	PFX_INLINE node_t*							remove (const_iterator_t& PARAM_IN __itr,
		result_t& PARAM_OUT __status)
	{
		if (__itr.cur_ptr() && __itr.root_node() == get_root())
		{
			node_t* remove_ptr = (node_t*)(__itr.cur_node());
			remove_ptr = remove(remove_ptr, __status);
			if (__status == __status)
			{
				set_itr(null, __itr);
			}
			return remove_ptr;
		}
		else
		{
			__status = PFX_STATUS_INVALID_PARAMS;
			return null;
		}
	}
	PFX_INLINE result_t								erase (const_iterator_t& PARAM_IN __itr)
	{
		node_t* remove_ptr;
		result_t	status;
		remove_ptr = remove(__itr, status);
		if (remove_ptr)
		{
			status = release_node(remove_ptr);
		}
		return status;
	}

	PFX_INLINE const node_t*					get_root () const
	{
		return m_root_ptr;
	}
};

template < class BST_operate_type >
class PFX_DATA_TEMPALE_API cbst_set : public  cbst< BST_operate_type >
{
public:
	typedef typename cbst< BST_operate_type >					base_bst_t;
	typedef	typename cbst_set< BST_operate_type >			bst_t;
	typedef typename BST_find_element< bst_t >					find_elem_t;

	typedef	typename base_bst_t::operator_t						operator_t;
	typedef	typename base_bst_t::allocate_t							allocate_t;
	typedef	typename base_bst_t::node_t								node_t;	
	typedef	typename base_bst_t::cmp_t								cmp_t;
	typedef typename node_t::element_t								element_t;

	

	typedef	typename base_bst_t::init_t									init_t;
	typedef	typename base_bst_t::new_delete_t					new_delete_t;	
	typedef	typename base_bst_t::minmax_t						minmax_t;
	typedef	typename base_bst_t::find_t								find_t;
	typedef	typename base_bst_t::insert_t								insert_t;
	typedef	typename base_bst_t::remove_t							remove_t;

	typedef typename	base_bst_t::clean_t								clean_t;
	typedef typename	base_bst_t::clone_t								clone_t;
	typedef typename	base_bst_t::copy_t								copy_t;

	typedef	typename	base_bst_t::itr_find_t							itr_find_t;

	typedef	typename	base_bst_t::const_iterator_t				const_iterator_t;
	typedef	typename	base_bst_t::const_inorder_itr_t		const_inorder_itr_t;
	typedef	typename	base_bst_t::const_preorder_itr_t	const_preorder_itr_t;
	typedef	typename	base_bst_t::const_posorder_itr_t	const_posorder_itr_t;

	typedef	typename	const_bst_inorder_iterator< bst_t >	const_iterator_ex_t;
public:
	PFX_INLINE const_iterator_t*	find_node (const element_t& PARAM_IN __key, const_iterator_t& itr)
	{
		const_iterator_ex_t __itr;
		__itr.init(m_root_ptr, itr.cur_node());
		const_iterator_ex_t* __itr_ptr = find_elem_t::find_node(__key, __itr);
		if (__itr_ptr)
		{
			set_itr_internal(__itr_ptr->cur_node(), itr);
			return &itr;
		}
		else
		{
			return null;
		}
		
		
	}

	PFX_INLINE const_iterator_t*	find_near_node  (const_iterator_t& itr,
																							const element_t& PARAM_IN __key,
																							int& PARAM_INOUT last_cmp_result)
	{
		return find_elem_t::find_near_node(__key, last_cmp_result, itr);
	}
	PFX_INLINE const node_t*			add_element (const element_t& PARAM_IN __key,
																	result_t& PARAM_OUT __status)
	{
		node_t*				new_node_ptr = new_node();
		const node_t*	retn_node_ptr = null;
		if (new_node_ptr)
		{
			new_node_ptr->set_item (__key);
			retn_node_ptr = add_node(new_node_ptr, __status);
			if (PFX_STATUS_OK != __status)
			{
				release_node(retn_node_ptr);
			}
		}
		else
		{
			__status = PFX_STATUS_MEM_LOW;
		}
		return retn_node_ptr;
	}



};
PECKER_END

#endif			//PFX_CBST_H_
