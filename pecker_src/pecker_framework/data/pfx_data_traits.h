/*
 * pfx_data_traits.h
 *
 *  Created on: 2014-1-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#ifndef		PFX_DATA_TRATITS_H_
#define		PFX_DATA_TRATITS_H_

#include "../pfx_defines.h"
//#include "../native/pecker_allocator.h"

PECKER_BEGIN
// object
template < typename obj_type >
struct PFX_DATA_TEMPALE_API object_reference_type
{
	typedef typename	 obj_type	obj_type_t;
};
template < typename obj_type >
struct PFX_DATA_TEMPALE_API object_reference_type < obj_type* >
{
	typedef typename	 obj_type	obj_type_t;
};
template < typename obj_type >
struct PFX_DATA_TEMPALE_API object_reference_type < const obj_type* >
{
	typedef typename	 obj_type	obj_type_t;
};
// share object
template < typename obj_type>
struct PFX_DATA_TEMPALE_API share_object_reference_type
{
	typedef typename obj_type::allocator_t allocator_t;
};

template < typename obj_type >
struct PFX_DATA_TEMPALE_API share_object_reference_type < obj_type* >
{
	typedef typename obj_type::allocator_t allocator_t;
};


// string
template < typename string_ >
struct PFX_DATA_TEMPALE_API string_member_reference_type
{
	typedef typename	 string_::item_type_t						item_type_t;
	typedef typename	 string_::compare_two_item_t		compare_two_item_t;
};

template < typename string_ >
struct PFX_DATA_TEMPALE_API string_ex_member_reference_type
{
	typedef typename	 string_::item_type_t						item_type_t;
	typedef typename	 string_::compare_two_item_t		compare_two_item_t;
	typedef typename	 string_::node_allocator_t				node_allocator_t;
};

// ARRAY
template < typename array_ >
struct PFX_DATA_TEMPALE_API array_member_reference_type
{
	typedef typename	 array_::item_type_t						item_type_t;
};
template < typename array_ >
struct PFX_DATA_TEMPALE_API array_member_reference_type < array_* >
{
	typedef typename	 array_::item_type_t						item_type_t;
};
template < typename array_ >
struct PFX_DATA_TEMPALE_API array_member_reference_type < const array_* >
{
	typedef typename	 array_::item_type_t						item_type_t;
};

//list
template < typename list_node >
struct PFX_DATA_TEMPALE_API list_node_member_reference_type
{
	typedef typename	 list_node::item_type_t				item_type_t;
};

template < typename list_ >
struct PFX_DATA_TEMPALE_API list_member_reference_type
{
	typedef typename	 list_::node_type_t						node_type_t;
	typedef typename	 list_::node_type_ptr_t				node_type_ptr_t;
	typedef typename	 list_::const_node_type_ptr_t		const_node_type_ptr_t;
};

template < typename list_ >
struct PFX_DATA_TEMPALE_API list_ex_member_reference_type
{
	typedef typename	 list_::node_type_t						node_type_t;
	typedef typename	 list_::node_type_ptr_t				node_type_ptr_t;
	typedef typename	 list_::const_node_type_ptr_t		const_node_type_ptr_t;
	typedef typename	 list_::node_allocator_t				node_allocator_t;
};

//bst
template < typename binary_search_tree_node >
struct PFX_DATA_TEMPALE_API bst_node_member_reference_type
{
	typedef typename	 binary_search_tree_node::item_type_t						item_type_t;
	typedef typename	 binary_search_tree_node::compare_two_item_t		compare_two_item_t;
};

template < typename binary_search_tree >
struct PFX_DATA_TEMPALE_API bst_member_reference_type
{
	typedef typename	 binary_search_tree::node_type_t						node_type_t;
	typedef typename	 binary_search_tree::node_type_ptr_t				node_type_ptr_t;
	typedef typename	 binary_search_tree::const_node_type_ptr_t	const_node_type_ptr_t;
	typedef typename	 binary_search_tree::compare_two_node_t		compare_two_node_t;
};

template < typename binary_search_tree >
struct PFX_DATA_TEMPALE_API bst_ex_member_reference_type
{
	typedef typename	 binary_search_tree::node_type_t						node_type_t;
	typedef typename	 binary_search_tree::node_type_ptr_t				node_type_ptr_t;
	typedef typename	 binary_search_tree::const_node_type_ptr_t	const_node_type_ptr_t;
	typedef typename	 binary_search_tree::compare_two_node_t		compare_two_node_t;
	typedef typename	 binary_search_tree::node_allocator_t				node_allocator_t;
};

template < typename binary_search_tree >
struct PFX_DATA_TEMPALE_API bstree_method
{
	typedef typename	 binary_search_tree::node_type_t						node_type_t;
	typedef typename	 binary_search_tree::node_type_ptr_t				node_type_ptr_t;
	typedef typename	 binary_search_tree::const_node_type_ptr_t	const_node_type_ptr_t;
	typedef typename	 binary_search_tree::compare_two_node_t		compare_two_node_t;

	static PFX_INLINE pfx_result_t init_node_leaves (node_type_t* PARAM_INOUT tree_node_ptr,
		node_type_t* PARAM_IN left_node_ptr = null,
		node_type_t* PARAM_IN right_node_ptr = null,
		node_type_t* PARAM_IN parent_node_ptr = null)
	{
		return binary_search_tree::init_node_leaves (tree_node_ptr, left_node_ptr, right_node_ptr, parent_node_ptr);
	}

	static PFX_INLINE pfx_result_t add_node (node_type_t*& PARAM_INOUT root_node_ptr,
		node_type_t* PARAM_INOUT add_node_ptr,
		node_type_t*& PARAM_OUT added_node_ptr)
	{
		return binary_search_tree::add_node (root_node_ptr, add_node_ptr, added_node_ptr);
	}

	static PFX_INLINE pfx_result_t remove_node (node_type_t*& PARAM_INOUT root_node_ptr,
		node_type_t* PARAM_INOUT remove_node_ptr,
		const node_type_t* PARAM_IN null_node_ptr = null)
	{
		return binary_search_tree::remove_node (root_node_ptr,remove_node_ptr,null_node_ptr);
	}

	//////////////////////////////////////////////////////////////////////////
	static PFX_INLINE const node_type_t* find_node (const node_type_t* PARAM_IN key_node_ptr,
		const node_type_t* PARAM_IN root_node_ptr)
	{
		return binary_search_tree::find_node (key_node_ptr,root_node_ptr);
	}

	static PFX_INLINE const node_type_t* find_near_node  (const node_type_t* PARAM_IN key_node_ptr,
		const node_type_t* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result)
	{
		return binary_search_tree::find_near_node (key_node_ptr, root_node_ptr, last_cmp_result);
	}

	static PFX_INLINE const node_type_t* find_node_by_item (const typename bst_node_member_reference_type< node_type_t >::item_type_t* PARAM_IN key_ptr,
		const node_type_t* PARAM_IN root_node_ptr)
	{
		return binary_search_tree::find_node_by_item (key_ptr, root_node_ptr);
	}

	static PFX_INLINE const node_type_t* find_near_node_by_item  (const typename bst_node_member_reference_type< node_type_t >::item_type_t* PARAM_IN key_ptr,
		const node_type_t* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result)
	{
		return binary_search_tree::find_near_node_by_item (key_ptr, root_node_ptr, last_cmp_result);
	}
};

template < typename binary_search_tree >
struct PFX_DATA_TEMPALE_API avltree_method
{
	typedef typename	 binary_search_tree::node_type_t						node_type_t;
	typedef typename	 binary_search_tree::node_type_ptr_t				node_type_ptr_t;
	typedef typename	 binary_search_tree::const_node_type_ptr_t	const_node_type_ptr_t;
	typedef typename	 binary_search_tree::compare_two_node_t		compare_two_node_t;

	static PFX_INLINE pfx_result_t init_node_leaves (node_type_t* PARAM_INOUT tree_node_ptr,
		node_type_t* PARAM_IN left_node_ptr = null,
		node_type_t* PARAM_IN right_node_ptr = null,
		node_type_t* PARAM_IN parent_node_ptr = null)
	{
		return binary_search_tree::init_avl_node_leaves (tree_node_ptr, left_node_ptr, right_node_ptr, parent_node_ptr);
	}

	static PFX_INLINE pfx_result_t add_node (node_type_t*& PARAM_INOUT root_node_ptr,
		node_type_t* PARAM_INOUT add_node_ptr,
		node_type_t*& PARAM_OUT added_node_ptr)
	{
		return binary_search_tree::add_avl_node (root_node_ptr, add_node_ptr, added_node_ptr);
	}

	static PFX_INLINE pfx_result_t remove_node (node_type_t*& PARAM_INOUT root_node_ptr,
		node_type_t* PARAM_INOUT remove_node_ptr,
		const node_type_t* PARAM_IN null_node_ptr = null)
	{
		return binary_search_tree::remove_avl_node (root_node_ptr,remove_node_ptr,null_node_ptr);
	}

	//////////////////////////////////////////////////////////////////////////
	static PFX_INLINE const node_type_t* find_node (const node_type_t* PARAM_IN key_node_ptr,
		const node_type_t* PARAM_IN root_node_ptr)
	{
		return binary_search_tree::find_node (key_node_ptr,root_node_ptr);
	}

	static PFX_INLINE const node_type_t* find_near_node  (const node_type_t* PARAM_IN key_node_ptr,
		const node_type_t* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result)
	{
		return binary_search_tree::find_near_node (key_node_ptr, root_node_ptr, last_cmp_result);
	}

	static PFX_INLINE const node_type_t* find_node_by_item (const typename bst_node_member_reference_type< node_type_t >::item_type_t* PARAM_IN key_ptr,
		const node_type_t* PARAM_IN root_node_ptr)
	{
		return binary_search_tree::find_node_by_item (key_ptr, root_node_ptr);
	}

	static PFX_INLINE const node_type_t* find_near_node_by_item  (const typename bst_node_member_reference_type< node_type_t >::item_type_t* PARAM_IN key_ptr,
		const node_type_t* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result)
	{
		return binary_search_tree::find_near_node_by_item (key_ptr, root_node_ptr, last_cmp_result);
	}
};

template < typename binary_search_tree >
struct PFX_DATA_TEMPALE_API rbtree_method
{
	typedef typename	 binary_search_tree::node_type_t						node_type_t;
	typedef typename	 binary_search_tree::node_type_ptr_t				node_type_ptr_t;
	typedef typename	 binary_search_tree::const_node_type_ptr_t	const_node_type_ptr_t;
	typedef typename	 binary_search_tree::compare_two_node_t		compare_two_node_t;

	static PFX_INLINE pfx_result_t init_node_leaves (node_type_t* PARAM_INOUT tree_node_ptr,
		node_type_t* PARAM_IN left_node_ptr = null,
		node_type_t* PARAM_IN right_node_ptr = null,
		node_type_t* PARAM_IN parent_node_ptr = null)
	{
		return binary_search_tree::init_rb_node_leaves (tree_node_ptr, left_node_ptr, right_node_ptr, parent_node_ptr);
	}

	static PFX_INLINE pfx_result_t add_node (node_type_t*& PARAM_INOUT root_node_ptr,
		node_type_t* PARAM_INOUT add_node_ptr,
		node_type_t*& PARAM_OUT added_node_ptr)
	{
		return binary_search_tree::add_rb_node (root_node_ptr, add_node_ptr, added_node_ptr);
	}

	static PFX_INLINE pfx_result_t remove_node (node_type_t*& PARAM_INOUT root_node_ptr,
		node_type_t* PARAM_INOUT remove_node_ptr,
		const node_type_t* PARAM_IN null_node_ptr = null)
	{
		return binary_search_tree::remove_rb_node (root_node_ptr,remove_node_ptr,null_node_ptr);
	}
	//////////////////////////////////////////////////////////////////////////
	static PFX_INLINE const node_type_t* find_node (const node_type_t* PARAM_IN key_node_ptr,
		const node_type_t* PARAM_IN root_node_ptr)
	{
		return binary_search_tree::find_node (key_node_ptr,root_node_ptr);
	}

	static PFX_INLINE const node_type_t* find_near_node  (const node_type_t* PARAM_IN key_node_ptr,
		const node_type_t* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result)
	{
		return binary_search_tree::find_near_node (key_node_ptr, root_node_ptr, last_cmp_result);
	}

	static PFX_INLINE const node_type_t* find_node_by_item (const typename bst_node_member_reference_type< node_type_t >::item_type_t* PARAM_IN key_ptr,
		const node_type_t* PARAM_IN root_node_ptr)
	{
		return binary_search_tree::find_node_by_item (key_ptr, root_node_ptr);
	}

	static PFX_INLINE const node_type_t* find_near_node_by_item  (const typename bst_node_member_reference_type< node_type_t >::item_type_t* PARAM_IN key_ptr,
		const node_type_t* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result)
	{
		return binary_search_tree::find_near_node_by_item (key_ptr, root_node_ptr, last_cmp_result);
	}
};

PECKER_END

#endif			//PFX_DATA_TRATITS_H_
