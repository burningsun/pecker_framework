/*
 * pfx_binary_search_tree.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BINARY_SEARCH_TREE_H_
#define		PFX_BINARY_SEARCH_TREE_H_

#include "data/pfx_cbst.h"
#include "data/pfx_cbst_codes.h"
#include "data/pfx_cbst_iterator_codes.h"
#include "native/pecker_allocator.h"

PECKER_BEGIN


#define PFX_CBST_EX_TEMPLATE_DEFINES template < class binary_search_tree, class node_allocator >
#define PFX_CBST_EX_TEMPLATE_PARAMS  < binary_search_tree, node_allocator >
#define PFX_CBST_EX_TEMPLATE_NODE typename bst_member_reference_type < binary_search_tree >::node_type_t

template < class binary_search_tree, class node_allocator >
class PFX_DATA_TEMPALE_API binary_search_tree_base : public  binary_search_tree
{
public:
	typedef node_allocator node_allocator_t;
public:
	virtual PFX_INLINE PFX_CBST_EX_TEMPLATE_NODE*	new_node ();
	virtual PFX_INLINE result_t	release_node (PFX_CBST_EX_TEMPLATE_NODE* PARAM_IN node_ptr);
};

template < class node_type_, class compare_two_node_ = pecker_value_compare_extern < node_type_ >, class node_allocator = pecker_simple_allocator < node_type_ > >
struct PFX_DATA_TEMPALE_API pfx_binary_search_tree_type
{
	typedef binary_search_tree_base <  cbst < node_type_,  compare_two_node_ >,			node_allocator >			binary_search_tree_t;
	typedef binary_search_tree_base <  cavl_tree < node_type_,  compare_two_node_ >,	node_allocator >			avl_binary_search_tree_t;
	typedef binary_search_tree_base <  crb_tree < node_type_,  compare_two_node_ >,		node_allocator >			redblack_binary_search_tree_t;
};

template < class item_type,class compare_two_value = pecker_value_compare < item_type > >
class PFX_DATA_TEMPALE_API cbst_node
{
public:
	typedef item_type					item_type_t;
	typedef compare_two_value	compare_two_item_t;
protected:
	cbst_node < item_type, compare_two_value >*	m_parent_node_ptr;
	cbst_node < item_type, compare_two_value >*	m_left_node_ptr;
	cbst_node < item_type, compare_two_value >*	m_right_node_ptr;
	item_type										m_item;
public:
	cbst_node () : m_right_node_ptr (null),m_left_node_ptr(null),m_parent_node_ptr(null)
	{
		;
	}
	cbst_node (const cbst_node < item_type, compare_two_value >& other_)
	{
		if (&other_ != this)
		{
			this->m_right_node_ptr = other_.m_right_node_ptr;
			this->m_left_node_ptr = other_.m_left_node_ptr;
			this->m_parent_node_ptr = other_.m_parent_node_ptr;
			this->m_item = other_.m_item;
		}
	}
	PFX_INLINE const cbst_node < item_type, compare_two_value >* get_left_node () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE const cbst_node < item_type, compare_two_value >* get_right_node () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE const cbst_node < item_type, compare_two_value >* get_parent_node () const
	{
		return m_parent_node_ptr;
	}

	PFX_INLINE const item_type& get_item () const
	{
		return m_item;
	}
public:
	PFX_INLINE void set_left_node (cbst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_left_node_ptr = node_ptr;
	}
	PFX_INLINE void set_right_node  (cbst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_right_node_ptr = node_ptr;
	}
	PFX_INLINE void set_parent_node (cbst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_parent_node_ptr = node_ptr;
	}
public:
	PFX_INLINE item_type& get_item_ref ()
	{
		return m_item;
	}
	PFX_INLINE  cbst_node < item_type, compare_two_value >* const & get_left_node_ref () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE cbst_node < item_type, compare_two_value >* const& get_right_node_ref () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE cbst_node < item_type, compare_two_value >* const& get_parent_node_ref () const
	{
		return m_parent_node_ptr;
	}

	PFX_INLINE int compare (const cbst_node < item_type, compare_two_value >& other_node) const
	{
		return compare_two_value :: compare (this->get_item(),other_node.get_item());
	}
	
	PFX_INLINE int compare (const cbst_node < item_type, compare_two_value >* other_node_ptr) const
	{
		if (null == other_node_ptr)
		{
			return 1;
		}
		else
		{
			return compare_two_value :: compare (this->get_item(),other_node_ptr->get_item());
		}
	}
	PFX_INLINE int compare (const item_type* PARAM_IN item_ptr) const
	{
		if (null == item_ptr)
		{
			return 1;
		}
		else
		{
			return compare_two_value :: compare (this->get_item(),*item_ptr);
		}
	}
};

template < class item_type, class compare_two_value = pecker_value_compare < item_type > >
class PFX_DATA_TEMPALE_API cavl_bst_node
{
public:
	typedef item_type					item_type_t;
	typedef compare_two_value	compare_two_item_t;
protected:
	cavl_bst_node < item_type, compare_two_value >* m_parent_node_ptr;
	cavl_bst_node < item_type, compare_two_value >* m_left_node_ptr;
	cavl_bst_node < item_type, compare_two_value >* m_right_node_ptr;
	nsize__t											m_height;
	item_type											m_item;
public:
	cavl_bst_node () : m_right_node_ptr (null),m_left_node_ptr(null),m_parent_node_ptr(null),m_height (0)
	{
		;
	}
	cavl_bst_node (const cavl_bst_node < item_type, compare_two_value >& other_)
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
	PFX_INLINE const cavl_bst_node < item_type, compare_two_value >* get_left_node () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE const cavl_bst_node < item_type, compare_two_value >* get_right_node () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE const cavl_bst_node < item_type, compare_two_value >* get_parent_node () const
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
	PFX_INLINE void set_left_node (cavl_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_left_node_ptr = node_ptr;
	}
	PFX_INLINE void set_right_node  (cavl_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_right_node_ptr = node_ptr;
	}
	PFX_INLINE void set_parent_node (cavl_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
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
	PFX_INLINE cavl_bst_node < item_type, compare_two_value >* const & get_left_node_ref () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE cavl_bst_node < item_type, compare_two_value >* const & get_right_node_ref () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE cavl_bst_node < item_type, compare_two_value >* const & get_parent_node_ref () const
	{
		return m_parent_node_ptr;
	}

	PFX_INLINE int compare (const cavl_bst_node < item_type, compare_two_value >& other_node) const
	{
		return compare_two_value :: compare (this->get_item(),other_node.get_item());
	}

	PFX_INLINE int compare (const cavl_bst_node < item_type, compare_two_value >* other_node_ptr) const
	{
		if (null == other_node_ptr)
		{
			return 1;
		}
		else
		{
			return compare_two_value :: compare (this->get_item(),other_node_ptr->get_item());
		}
	}
	PFX_INLINE int compare (const item_type* PARAM_IN item_ptr) const
	{
		if (null == item_ptr)
		{
			return 1;
		}
		else
		{
			return compare_two_value :: compare (this->get_item(),*item_ptr);
		}
	}
};

template < class item_type,  class compare_two_value = pecker_value_compare < item_type > >
class PFX_DATA_TEMPALE_API crb_bst_node
{
public:
	typedef item_type					item_type_t;
	typedef compare_two_value	compare_two_item_t;
protected:
	crb_bst_node < item_type, compare_two_value >*	m_parent_node_ptr;
	crb_bst_node < item_type, compare_two_value >*	m_left_node_ptr;
	crb_bst_node < item_type, compare_two_value >*	m_right_node_ptr;
	flag_t											m_color;
	item_type											m_item;
public:
	crb_bst_node () : m_right_node_ptr (null),m_left_node_ptr(null),m_parent_node_ptr(null),m_color(BLACK_COLOR_NODE_TYPE)
	{
		;
	}
	crb_bst_node (const crb_bst_node < item_type, compare_two_value >& other_)
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
	PFX_INLINE const crb_bst_node < item_type, compare_two_value >* get_left_node () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE const crb_bst_node < item_type, compare_two_value >* get_right_node () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE const crb_bst_node < item_type, compare_two_value >* get_parent_node () const
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
	PFX_INLINE void set_left_node (crb_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_left_node_ptr = node_ptr;
	}
	PFX_INLINE void set_right_node  (crb_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_right_node_ptr = node_ptr;
	}
	PFX_INLINE void set_parent_node (crb_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
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
	PFX_INLINE crb_bst_node < item_type, compare_two_value >* const & get_left_node_ref () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE crb_bst_node < item_type, compare_two_value >* const & get_right_node_ref () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE crb_bst_node < item_type, compare_two_value >* const & get_parent_node_ref () const
	{
		return m_parent_node_ptr;
	}

	PFX_INLINE int compare (const crb_bst_node < item_type, compare_two_value >& other_node) const
	{
		return compare_two_value :: compare (this->get_item(),other_node.get_item());
	}

	PFX_INLINE int compare (const crb_bst_node < item_type, compare_two_value >* other_node_ptr) const
	{
		if (null == other_node_ptr)
		{
			return 1;
		}
			else
		{
			return compare_two_value :: compare (this->get_item(),other_node_ptr->get_item());
		}
	}
	PFX_INLINE int compare (const item_type* PARAM_IN item_ptr) const
	{
		if (null == item_ptr)
		{
			return 1;
		}
		else
		{
			return compare_two_value :: compare (this->get_item(),*item_ptr);
		}
	}
};

template < class item_type, class compare_two_value = pecker_value_compare < item_type > >
class PFX_DATA_TEMPALE_API cbalance_bst_node
{
public:
	typedef item_type					item_type_t;
	typedef compare_two_value	compare_two_item_t;
protected:
	cbalance_bst_node < item_type, compare_two_value >* m_parent_node_ptr;
	cbalance_bst_node < item_type, compare_two_value >* m_left_node_ptr;
	cbalance_bst_node < item_type, compare_two_value >* m_right_node_ptr;
	nsize__t											m_balance_value;
	item_type											m_item;
public:
	cbalance_bst_node () : m_right_node_ptr (null),m_left_node_ptr(null),m_parent_node_ptr(null),m_balance_value (0)
	{
		;
	}
	cbalance_bst_node (const cbalance_bst_node < item_type, compare_two_value >& other_)
	{
		if (&other_ != this)
		{
			this->m_right_node_ptr = other_.m_right_node_ptr;
			this->m_left_node_ptr = other_.m_left_node_ptr;
			this->m_parent_node_ptr = other_.m_parent_node_ptr;
			this->m_balance_value = other_.m_height;
			this->m_item = other_.m_item;
		}
	}
	PFX_INLINE const cbalance_bst_node < item_type, compare_two_value >* get_left_node () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE const cbalance_bst_node < item_type, compare_two_value >* get_right_node () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE const cbalance_bst_node < item_type, compare_two_value >* get_parent_node () const
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
	PFX_INLINE void set_left_node (cbalance_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_left_node_ptr = node_ptr;
	}
	PFX_INLINE void set_right_node  (cbalance_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
	{
		m_right_node_ptr = node_ptr;
	}
	PFX_INLINE void set_parent_node (cbalance_bst_node < item_type, compare_two_value >* PARAM_IN node_ptr)
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
	PFX_INLINE cbalance_bst_node < item_type, compare_two_value >* const & get_left_node_ref () const
	{
		return m_left_node_ptr;
	}
	PFX_INLINE cbalance_bst_node < item_type, compare_two_value >* const & get_right_node_ref () const
	{
		return m_right_node_ptr;
	}
	PFX_INLINE cbalance_bst_node < item_type, compare_two_value >* const & get_parent_node_ref () const
	{
		return m_parent_node_ptr;
	}

	PFX_INLINE int compare (const cbalance_bst_node < item_type, compare_two_value >& other_node) const
	{
		return compare_two_value :: compare (this->get_item(),other_node.get_item());
	}

	PFX_INLINE int compare (const cbalance_bst_node < item_type, compare_two_value >* other_node_ptr) const
	{
		if (null == other_node_ptr)
		{
			return 1;
		}
		else
		{
			return compare_two_value :: compare (this->get_item(),other_node_ptr->get_item());
		}
	}

	PFX_INLINE int compare (const item_type* PARAM_IN item_ptr) const
	{
		if (null == item_ptr)
		{
			return 1;
		}
		else
		{
			return compare_two_value :: compare (this->get_item(),*item_ptr);
		}
	}
};

template < class item_type, class compare_two_value = pecker_value_compare < item_type >, class node_allocator = pecker_simple_allocator < node_type_ > >
struct PFX_DATA_TEMPALE_API set_
{
	typedef cbst_node < item_type, compare_two_value >			bst_node_t;
	typedef cavl_bst_node < item_type, compare_two_value >	avlbst_node_t;
	typedef crb_bst_node < item_type, compare_two_value >	rbbst_node_t;

	typedef typename pfx_binary_search_tree_type <  bst_node_t, 
		pecker_value_compare_extern < bst_node_t >, 
		node_allocator >::binary_search_tree_t										binary_search_tree_t;

	typedef typename pfx_binary_search_tree_type <  avlbst_node_t, 
		pecker_value_compare_extern < avlbst_node_t >, 
		node_allocator >::avl_binary_search_tree_t									avl_binary_search_tree_t;

	typedef typename pfx_binary_search_tree_type <  rbbst_node_t, 
		pecker_value_compare_extern < rbbst_node_t >, 
		node_allocator >::redblack_binary_search_tree_t						redblack_binary_search_tree_t;
};

//////////////////////////////////////////////////////////////////////////
PFX_CBST_EX_TEMPLATE_DEFINES
PFX_INLINE PFX_CBST_EX_TEMPLATE_NODE* binary_search_tree_base PFX_CBST_EX_TEMPLATE_PARAMS :: new_node ()
{
	return node_allocator::allocate_object ();
}
PFX_CBST_EX_TEMPLATE_DEFINES
PFX_INLINE result_t binary_search_tree_base PFX_CBST_EX_TEMPLATE_PARAMS :: release_node (PFX_CBST_EX_TEMPLATE_NODE* PARAM_IN node_ptr)
{
	return node_allocator::deallocate_object (node_ptr);
}

PECKER_END

#endif			//PFX_BINARY_SEARCH_TREE_H_
