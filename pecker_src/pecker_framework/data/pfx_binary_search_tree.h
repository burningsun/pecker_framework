﻿/*
 * pfx_binary_search_tree.h
 *
 *  Created on: 2014-2-1
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BINARY_SEARCH_TREE_H_
#define		PFX_BINARY_SEARCH_TREE_H_

#include "pfx_cbst.h"
#include "pfx_cbst_codes.h"
#include "pfx_cbst_iterator_codes.h"
#include "../native/pecker_allocator.h"

PECKER_BEGIN

template < class node_A_type,
class node_B_type,
class compare_two_elem >
struct xcompare_two_node
{
	typedef node_A_type node_t;
	typedef node_A_type node_a_t;
	typedef node_B_type node_b_t;
	typedef compare_two_elem compare_two_elemen_t;
	typedef xcompare_two_node< node_a_t, node_b_t, compare_two_elemen_t > cmp_t;

	static PFX_INLINE int compare(const node_a_t& node_a, const node_b_t& node_b)
	{
		return compare_two_elemen_t::compare (node_a, node_b);
	}
	static PFX_INLINE int compare (const node_a_t* PARAM_IN node_a_ptr, const node_b_t* PARAM_IN node_b_ptr)
	{
		return compare_two_elemen_t::compare (*node_a_ptr, *node_a_ptr);
	}
};

template < class node_A_type,
class node_B_type = node_A_type,
class compare_two_elem = pecker_value_compare < typename node_A_type::element_t > >
struct compare_two_node
{
	typedef node_A_type node_t;
	typedef node_A_type node_a_t;
	typedef node_B_type node_b_t;
	typedef compare_two_elem compare_two_elemen_t;
	typedef compare_two_node< node_a_t, node_b_t, compare_two_elemen_t > cmp_t;

	static PFX_INLINE int compare(const node_a_t& node_a, const node_b_t& node_b)
	{
		return compare_two_elemen_t::compare (node_a.get_item(), node_b.get_item());
	}
	static PFX_INLINE int compare (const node_a_t* PARAM_IN node_a_ptr, const node_b_t* PARAM_IN node_b_ptr)
	{
		return compare_two_elemen_t::compare ((node_a_ptr->get_item()), (node_b_ptr->get_item()));
	}
};

template < class item_type >
class PFX_DATA_TEMPLATE_API cbst_node
{
public:
	typedef item_type item_type_t;
	typedef item_type element_t;
	typedef cbst_node < item_type_t > node_t;
protected:
	node_t* m_parent_node_ptr;
	node_t* m_left_node_ptr;
	node_t* m_right_node_ptr;
	item_type_t m_item;
public:
	cbst_node () : m_right_node_ptr (null),m_left_node_ptr(null),m_parent_node_ptr(null)
	{
		;
	}
	cbst_node (const node_t& other_)
	{
		if (&other_ != this)
		{
			this->m_right_node_ptr = other_.m_right_node_ptr;
			this->m_left_node_ptr = other_.m_left_node_ptr;
			this->m_parent_node_ptr = other_.m_parent_node_ptr;
			this->m_item = other_.m_item;
		}
	}
	PFX_INLINE const node_t* get_left_node () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE const node_t* get_right_node () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE const node_t* get_parent_node () const
	{
		return m_parent_node_ptr;
	}

	PFX_INLINE const item_type& get_item () const
	{
		return m_item;
	}
	PFX_INLINE result_t set_item (const item_type_t& __item)
	{
		if (null == m_parent_node_ptr &&
				null == m_left_node_ptr &&
				null == m_right_node_ptr)
		{
			m_item = __item;
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_DENIED;
		}
	}
public:
	PFX_INLINE void set_left_node (node_t* PARAM_IN node_ptr)
	{
		m_left_node_ptr = node_ptr;
	}
	PFX_INLINE void set_right_node (node_t* PARAM_IN node_ptr)
	{
		m_right_node_ptr = node_ptr;
	}
	PFX_INLINE void set_parent_node (node_t* PARAM_IN node_ptr)
	{
		m_parent_node_ptr = node_ptr;
	}
public:
	PFX_INLINE item_type& get_item_ref ()
	{
		return m_item;
	}
	PFX_INLINE node_t* const & get_left_node_ref () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE node_t* const& get_right_node_ref () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE node_t* const& get_parent_node_ref () const
	{
		return m_parent_node_ptr;
	}
};

template < class item_type >
class PFX_DATA_TEMPLATE_API cavl_bst_node
{
public:
	typedef item_type item_type_t;
	typedef item_type element_t;
	typedef cavl_bst_node < item_type_t > node_t;
protected:
	node_t* m_parent_node_ptr;
	node_t* m_left_node_ptr;
	node_t* m_right_node_ptr;
	nsize__t m_height;
	item_type m_item;
public:
	cavl_bst_node () : m_right_node_ptr (null),m_left_node_ptr(null),m_parent_node_ptr(null),m_height (0)
	{
		;
	}
	cavl_bst_node (const node_t& other_)
	{
		if (&other_ != this)
		{
			this->m_right_node_ptr = other_.m_right_node_ptr;
			this->m_left_node_ptr = other_.m_left_node_ptr;
			this->m_parent_node_ptr = other_.m_parent_node_ptr;
			this->m_height = other_.m_height;
			this->m_item = other_.m_item;
		}
	}
	PFX_INLINE const node_t* get_left_node () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE const node_t* get_right_node () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE const node_t* get_parent_node () const
	{
		return m_parent_node_ptr;
	}
	PFX_INLINE nsize__t get_height () const
	{
		return m_height;
	}

	PFX_INLINE const item_type& get_item () const
	{
		return m_item;
	}

	PFX_INLINE result_t set_item (const item_type_t& __item)
	{
		if (null == m_parent_node_ptr &&
				null == m_left_node_ptr &&
				null == m_right_node_ptr)
		{
			m_item = __item;
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_DENIED;
		}
	}

	PFX_INLINE void set_left_node (node_t* PARAM_IN node_ptr)
	{
		m_left_node_ptr = node_ptr;
	}
	PFX_INLINE void set_right_node (node_t* PARAM_IN node_ptr)
	{
		m_right_node_ptr = node_ptr;
	}
	PFX_INLINE void set_parent_node (node_t* PARAM_IN node_ptr)
	{
		m_parent_node_ptr = node_ptr;
	}
	PFX_INLINE void set_height (nsize__t height)
	{
		m_height = height;
	}

	PFX_INLINE item_type& get_item_ref ()
	{
		return m_item;
	}
	PFX_INLINE node_t* const & get_left_node_ref () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE node_t* const & get_right_node_ref () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE node_t* const & get_parent_node_ref () const
	{
		return m_parent_node_ptr;
	}
};

template < class item_type >
class PFX_DATA_TEMPLATE_API crb_bst_node
{
public:
	typedef item_type item_type_t;
	typedef item_type element_t;
	typedef crb_bst_node < item_type_t > node_t;
protected:
	node_t* m_parent_node_ptr;
	node_t* m_left_node_ptr;
	node_t* m_right_node_ptr;
	flag_t m_color;
	item_type m_item;
public:
	crb_bst_node () : m_right_node_ptr (null),
	m_left_node_ptr(null),m_parent_node_ptr(null),
	m_color(BLACK_COLOR_NODE_TYPE)
	{
		;
	}
	crb_bst_node (const node_t& other_)
	{
		if (&other_ != this)
		{
			this->m_right_node_ptr = other_.m_right_node_ptr;
			this->m_left_node_ptr = other_.m_left_node_ptr;
			this->m_parent_node_ptr = other_.m_parent_node_ptr;
			this->m_color = other_.m_color;
			this->m_item = other_.m_item;
		}
	}
	PFX_INLINE const node_t* get_left_node () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE const node_t* get_right_node () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE const node_t* get_parent_node () const
	{
		return m_parent_node_ptr;
	}
	PFX_INLINE flag_t get_color () const
	{
		return m_color;
	}

	PFX_INLINE const item_type& get_item () const
	{
		return m_item;
	}
	PFX_INLINE void set_left_node (node_t* PARAM_IN node_ptr)
	{
		m_left_node_ptr = node_ptr;
	}
	PFX_INLINE void set_right_node (node_t* PARAM_IN node_ptr)
	{
		m_right_node_ptr = node_ptr;
	}
	PFX_INLINE void set_parent_node (node_t* PARAM_IN node_ptr)
	{
		m_parent_node_ptr = node_ptr;
	}
	PFX_INLINE void set_color (flag_t color)
	{
		m_color = color;
	}

	PFX_INLINE item_type& get_item_ref ()
	{
		return m_item;
	}
	PFX_INLINE node_t* const & get_left_node_ref () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE node_t* const & get_right_node_ref () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE node_t* const & get_parent_node_ref () const
	{
		return m_parent_node_ptr;
	}
};

template < class item_type >
class PFX_DATA_TEMPLATE_API cbalance_bst_node
{
public:
	typedef item_type item_type_t;
	typedef item_type element_t;
	typedef cbalance_bst_node < item_type_t > node_t;
protected:
	node_t* m_parent_node_ptr;
	node_t* m_left_node_ptr;
	node_t* m_right_node_ptr;
	nsize__t m_balance_value;
	item_type m_item;
public:
	cbalance_bst_node () : m_right_node_ptr (null),
	m_left_node_ptr(null),
	m_parent_node_ptr(null),
	m_balance_value (0)
	{
		;
	}
	cbalance_bst_node (const node_t& other_)
	{
		if (&other_ != this)
		{
			this->m_right_node_ptr = other_.m_right_node_ptr;
			this->m_left_node_ptr = other_.m_left_node_ptr;
			this->m_parent_node_ptr = other_.m_parent_node_ptr;
			this->m_balance_value = other_.m_balance_value;
			this->m_item = other_.m_item;
		}
	}
	PFX_INLINE const node_t* get_left_node () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE const node_t* get_right_node () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE const node_t* get_parent_node () const
	{
		return m_parent_node_ptr;
	}
	PFX_INLINE nsize__t get_height () const
	{
		return m_balance_value;
	}
	PFX_INLINE flag_t get_color () const
	{
		return m_balance_value;
	}
	PFX_INLINE const item_type& get_item () const
	{
		return m_item;
	}
	PFX_INLINE void set_left_node (node_t* PARAM_IN node_ptr)
	{
		m_left_node_ptr = node_ptr;
	}
	PFX_INLINE void set_right_node (node_t* PARAM_IN node_ptr)
	{
		m_right_node_ptr = node_ptr;
	}
	PFX_INLINE void set_parent_node (node_t* PARAM_IN node_ptr)
	{
		m_parent_node_ptr = node_ptr;
	}
	PFX_INLINE void set_height (nsize__t height)
	{
		m_balance_value = height;
	}
	PFX_INLINE void set_color (flag_t color)
	{
		m_balance_value = color;
	}

	PFX_INLINE item_type& get_item_ref ()
	{
		return m_item;
	}
	PFX_INLINE node_t* const & get_left_node_ref () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE node_t* const & get_right_node_ref () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE node_t* const & get_parent_node_ref () const
	{
		return m_parent_node_ptr;
	}
};

template < class node_type_, class compare_two_node_, class node_allocator = pecker_simple_allocator< node_type_ > >
struct PFX_DATA_TEMPLATE_API pfx_binary_search_tree_type
{
	typedef node_type_ node_t;
	typedef compare_two_node_ cmp_t;
	typedef node_allocator allocate_t;
	typedef cbst < BST_operate < allocate_t, cmp_t > > binary_search_tree_t;
	typedef cbst < AVL_BST_operate < allocate_t, cmp_t > > avl_binary_search_tree_t;
	typedef cbst < RB_BST_operate < allocate_t, cmp_t > > redblack_binary_search_tree_t;
};

typedef enum enumTREE_TYPE
{
	BINARY_SEARCH_TREE_TYPE = 0,
	AVL_BINARY_SEARCH_TREE_TYPE,
	RB_BINARY_SEARCH_TREE_TYPE,

	BINARY_SEARCH_TREE_TYPE_COUNT
}BST_TYPE_t;

PECKER_END

#endif			//PFX_BINARY_SEARCH_TREE_H_
