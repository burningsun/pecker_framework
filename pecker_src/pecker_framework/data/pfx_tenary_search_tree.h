/*
 * pfx_tenary_search_tree.h
 *
 *  Created on: 2015-2-9
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_TENARY_SEARCH_TREE_H_
#define		PFX_TENARY_SEARCH_TREE_H_

#include "pfx_binary_search_tree.h"

PECKER_BEGIN

template < class string_type, class item_type >
class PFX_DATA_TEMPLATE_API cavl_tst_node
{
public:
	typedef item_type    item_type_t;
	typedef item_type    element_t;
	typedef string_type	 key_string_t;
	typedef typename key_string_t::item_type_t          key_char_t;
	typedef cavl_tst_node < key_string_t, item_type_t > node_t;
protected:
	//////////////////////////////////////////////////////////////////////////
	node_t* m_parent_node_ptr;
	node_t* m_left_node_ptr;
	node_t* m_right_node_ptr;
	
	//////////////////////////////////////////////////////////////////////////
	node_t* m_mid_node_ptr;
	node_t* m_mid_parent_node_ptr;
	
	nsize__t m_height;

	key_string_t m_key;

	bool     m_null_flag;

	item_type m_item;
public:
	cavl_tst_node() : m_right_node_ptr(null), 
		m_left_node_ptr(null), 
		m_parent_node_ptr(null), 
		m_height(0),
		m_mid_node_ptr(null), 
		m_mid_parent_node_ptr(null), 
		m_null_flag(false)
	{
		;
	}
	cavl_tst_node(const node_t& other_)
	{
		if (&other_ != this)
		{
			this->m_right_node_ptr = other_.m_right_node_ptr;
			this->m_left_node_ptr = other_.m_left_node_ptr;
			this->m_parent_node_ptr = other_.m_parent_node_ptr;
			this->m_height = other_.m_height;
			this->m_item = other_.m_item;

			this->m_mid_node_ptr = other_.m_mid_node_ptr;
			this->m_mid_parent_node_ptr = other_.m_mid_parent_node_ptr;
			this->m_null_flag = other_.m_is_null_node;
		}
	}

	PFX_INLINE node_t* sepreate_node(
		node_t* PARAM_OUT sub_node_ptr,
		usize__t chars_offset,
		result_t& PARAM_OUT status_)
	{
		node_t* retn_node_ptr = null;

		FOR_ONE_LOOP_BEGIN

		BREAK_LOOP_CONDITION_SETS((null == sub_node_ptr), 
			status_, PFX_STATUS_INVALID_PARAMS);

		BREAK_LOOP_CONDITION_SETS((this->get_string_buffer_size() <= chars_offset), 
			status_, PFX_STATUS_OVERRANGE);
		

		status_ = this->m_key.clip_string_remain_right(chars_offset, sub_node_ptr->m_key);
		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status_);

		//////////////////////////////////////////////////////////////////////////
		sub_node_ptr->m_mid_parent_node_ptr = this->m_mid_parent_node_ptr;
		sub_node_ptr->m_mid_node_ptr = this;

		sub_node_ptr->m_left_node_ptr = this->m_left_node_ptr;
		sub_node_ptr->m_right_node_ptr = this->m_right_node_ptr;
		sub_node_ptr->m_parent_node_ptr = this->m_parent_node_ptr;

		sub_node_ptr->m_height = 0;
		//////////////////////////////////////////////////////////////////////////
		sub_node_ptr->m_null_flag = true;

		if (this->m_left_node_ptr)
		{
			this->m_left_node_ptr->m_parent_node_ptr = sub_node_ptr;
		}
		
		if (this->m_right_node_ptr)
		{
			this->m_right_node_ptr->m_parent_node_ptr = sub_node_ptr;
		}
		
		if (this->m_mid_parent_node_ptr && 
			this->m_mid_parent_node_ptr->m_mid_node_ptr == this)
		{
			this->m_mid_parent_node_ptr->m_mid_node_ptr = sub_node_ptr;
		}
		//////////////////////////////////////////////////////////////////////////
		this->m_left_node_ptr = null; 
		this->m_right_node_ptr = null;
		this->m_parent_node_ptr = null;
		this->m_mid_parent_node_ptr = sub_node_ptr;
		retn_node_ptr = this;

		FOR_ONE_LOOP_END

		return retn_node_ptr;
	}

	PFX_INLINE const key_char_t* get_string_buffer() const
	{
		return m_key.get_string();
	}

	PFX_INLINE usize__t get_string_buffer_size() const
	{
		return m_key.get_length();
	}

	PFX_INLINE const key_string_t& get_key() const
	{
		return m_key;
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

	PFX_INLINE const node_t* get_middle_parent_node() const
	{
		return m_mid_parent_node_ptr;
	}
	PFX_INLINE const node_t* get_middle_node() const
	{
		return m_mid_node_ptr;
	}
	PFX_INLINE const node_t* get_middle_parent_node() const
	{
		return m_mid_parent_node_ptr;
	}
	PFX_INLINE const node_t* get_middle_node() const
	{
		return m_mid_node_ptr;
	}

	PFX_INLINE bool get_null_flag() const
	{
		return m_null_flag;
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
	PFX_INLINE void set_mid_parent_node(node_t* PARAM_IN node_ptr)
	{
		m_mid_parent_node_ptr = node_ptr;
	}
	PFX_INLINE void set_mid_leaf_node(node_t* PARAM_IN node_ptr)
	{
		m_mid_node_ptr = node_ptr;
	}

	PFX_INLINE void set_null_element_flag(bool set_null = true)
	{
		m_null_flag = set_null;
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
	PFX_INLINE node_t* const & get_middle_parent_node_ref () const
	{
		return m_mid_parent_node_ptr;
	}
	PFX_INLINE node_t* const & get_middle_node_ref () const
	{
		return m_mid_node_ptr;
	}
};

//template < class item_type >
//class PFX_DATA_TEMPLATE_API crb_bst_node
//{
//public:
//	typedef item_type item_type_t;
//	typedef item_type element_t;
//	typedef crb_bst_node < item_type_t > node_t;
//protected:
//	node_t* m_parent_node_ptr;
//	node_t* m_left_node_ptr;
//	node_t* m_right_node_ptr;
//	flag_t m_color;
//	item_type m_item;
//public:
//	crb_bst_node () : m_right_node_ptr (null),
//	m_left_node_ptr(null),m_parent_node_ptr(null),
//	m_color(BLACK_COLOR_NODE_TYPE)
//	{
//		;
//	}
//	crb_bst_node (const node_t& other_)
//	{
//		if (&other_ != this)
//		{
//			this->m_right_node_ptr = other_.m_right_node_ptr;
//			this->m_left_node_ptr = other_.m_left_node_ptr;
//			this->m_parent_node_ptr = other_.m_parent_node_ptr;
//			this->m_color = other_.m_color;
//			this->m_item = other_.m_item;
//		}
//	}
//	PFX_INLINE const node_t* get_left_node () const
//	{
//		return m_left_node_ptr;
//	}
//	PFX_INLINE const node_t* get_right_node () const
//	{
//		return m_right_node_ptr;
//	}
//	PFX_INLINE const node_t* get_parent_node () const
//	{
//		return m_parent_node_ptr;
//	}
//	PFX_INLINE flag_t get_color () const
//	{
//		return m_color;
//	}
//
//	PFX_INLINE const item_type& get_item () const
//	{
//		return m_item;
//	}
//	PFX_INLINE void set_left_node (node_t* PARAM_IN node_ptr)
//	{
//		m_left_node_ptr = node_ptr;
//	}
//	PFX_INLINE void set_right_node (node_t* PARAM_IN node_ptr)
//	{
//		m_right_node_ptr = node_ptr;
//	}
//	PFX_INLINE void set_parent_node (node_t* PARAM_IN node_ptr)
//	{
//		m_parent_node_ptr = node_ptr;
//	}
//	PFX_INLINE void set_color (flag_t color)
//	{
//		m_color = color;
//	}
//
//	PFX_INLINE item_type& get_item_ref ()
//	{
//		return m_item;
//	}
//	PFX_INLINE node_t* const & get_left_node_ref () const
//	{
//		return m_left_node_ptr;
//	}
//	PFX_INLINE node_t* const & get_right_node_ref () const
//	{
//		return m_right_node_ptr;
//	}
//	PFX_INLINE node_t* const & get_parent_node_ref () const
//	{
//		return m_parent_node_ptr;
//	}
//};





PECKER_END

#endif			//PFX_TENARY_SEARCH_TREE_H_
