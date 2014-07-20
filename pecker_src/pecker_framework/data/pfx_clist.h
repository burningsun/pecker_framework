/*
 * pfx_clist.h
 *
 *  Created on: 2013-12-17
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CLIST_H_
#define		PFX_CLIST_H_

#include "../pfx_defines.h"

PECKER_BEGIN
	template < class __elem >
class clist_node
{
public:
	typedef __elem								element_t;
	typedef clist_node< element_t >	clist_node_t;
private:
	clist_node_t*	m_prev_ptr;
	clist_node_t*	m_next_ptr;
	element_t			m_elem;
public:
	clist_node () : m_next_ptr (null), m_prev_ptr(null){;}
	~clist_node()
	{
		m_next_ptr = null;
		m_prev_ptr = null;
	}
	PFX_INLINE const clist_node_t*	get_prev_node () const
	{
		return m_prev_ptr;
	}
	PFX_INLINE const clist_node_t*	get_next_node () const
	{
		return m_next_ptr;
	}
	PFX_INLINE const element_t&		get_element () const
	{
		return m_elem;
	}

	PFX_INLINE clist_node_t*	get_prev_node ()
	{
		return m_prev_ptr;
	}
	PFX_INLINE clist_node_t*	get_next_node ()
	{
		return m_next_ptr;
	}
	PFX_INLINE element_t&		get_element ()
	{
		return m_elem;
	}

	PFX_INLINE void	set_prev_node (clist_node_t* PARAM_IN node_ptr)
	{
		m_prev_ptr = node_ptr;
	}
	PFX_INLINE void	set_next_node  (clist_node_t* PARAM_IN node_ptr)
	{
		m_next_ptr = node_ptr;
	}
};

template < class __node_type >
struct linked_list_operation
{
	typedef __node_type											list_node_t;
	typedef typename list_node_t::element_t		element_t;

	static  PFX_INLINE result_t init_list_node (list_node_t* PARAM_INOUT node_ptr);
	static PFX_INLINE  list_node_t*	insert_list_node_back (list_node_t* PARAM_INOUT node_ptr,
		list_node_t* PARAM_INOUT insert_node_ptr);
	static PFX_INLINE list_node_t*	insert_list_node_front (list_node_t* PARAM_INOUT node_ptr,
		list_node_t* PARAM_INOUT insert_node_ptr);
	static PFX_INLINE list_node_t*	remove_list_node (list_node_t* PARAM_INOUT node_ptr);
};

template < class __node_type >
class clinked_list_iterator
{
public:
	typedef __node_type											list_node_t;
	typedef clinked_list_iterator < list_node_t > iterator_t;
private:
	list_node_t*		m_cur_node_ptr;
	list_node_t**	m_begin_node_ptr;
public:
	clinked_list_iterator () : m_cur_node_ptr(null), m_begin_node_ptr(null){;}
	~clinked_list_iterator (){ m_cur_node_ptr = null;}
public:
	PFX_INLINE result_t bind_list (list_node_t*& PARAM_IN __list_ptr)
	{
		m_begin_node_ptr = &__list_ptr;
		m_cur_node_ptr = __list_ptr;
		return PFX_STATUS_OK;
	}
	PFX_INLINE  list_node_t** const get_bind_list () const
	{
		return m_begin_node_ptr;
	}
	PFX_INLINE list_node_t* init (list_node_t* PARAM_IN __init_node_ptr)
	{
		m_cur_node_ptr = __init_node_ptr;
		return m_cur_node_ptr;
	}
	PFX_INLINE const list_node_t* cur_node () const
	{
		return m_cur_node_ptr;
	}
	PFX_INLINE list_node_t* cur_node ()
	{
		return m_cur_node_ptr;
	}

	PFX_INLINE iterator_t* increase ()
	{
		iterator_t* retn_ptr = null;
		if (m_cur_node_ptr && m_cur_node_ptr->get_next_node())
		{
			m_cur_node_ptr = m_cur_node_ptr->get_next_node();
			retn_ptr = this;
		}
		return retn_ptr;
	}
	PFX_INLINE iterator_t* decrease ()
	{
		iterator_t* retn_ptr = null;
		if (m_cur_node_ptr && m_cur_node_ptr->get_prev_node())
		{
			m_cur_node_ptr = m_cur_node_ptr->get_prev_node();
			retn_ptr = this;
		}
		return retn_ptr;
	}
};

template < class __alloc >
class clinked_list
{
public:
	typedef __alloc									allocate_t;
	typedef typename allocate_t::element_t			list_node_t;
	typedef clinked_list_iterator< list_node_t >	iterator_t;
	typedef linked_list_operation< list_node_t >	list_op_t;
	typedef clinked_list< allocate_t >				list_t;
private:
	list_node_t* m_begn_ptr;
	list_node_t* m_end_ptr;
	usize__t	 m_size;
public:
	clinked_list (): m_begn_ptr(null), m_end_ptr(null),m_size(0){;}
	~clinked_list(){dispose();}
	PFX_INLINE result_t swap(list_t& __other_list)
	{
		list_node_t*	temp_node_ptr;
		usize__t		temp_size;

		temp_node_ptr			= __other_list.m_begn_ptr;
		__other_list.m_begn_ptr = this->m_begn_ptr;
		this->m_begn_ptr		= temp_node_ptr;

		temp_node_ptr			= __other_list.m_end_ptr;
		__other_list.m_end_ptr	= this->m_end_ptr;
		this->m_end_ptr			= temp_node_ptr;

		temp_size				= __other_list.m_size;
		__other_list.m_size		= this->m_size;
		this->m_size			= temp_size;

		return PFX_STATUS_OK;

	}

	static PFX_INLINE list_node_t* new_node ()
	{
		return allocate_t::allocate_object ();
	}
	static PFX_INLINE result_t release_node (list_node_t*& node_ptr)
	{
		return allocate_t::deallocate_object (node_ptr);
	}

	PFX_INLINE list_node_t* begin_node ()
	{
		return m_begn_ptr;
	}
	PFX_INLINE list_node_t* end_node ()
	{
		return m_end_ptr;
	}
	PFX_INLINE const list_node_t* begin_node () const
	{
		return m_begn_ptr;
	}
	PFX_INLINE const list_node_t* end_node () const
	{
		return m_end_ptr;
	}
	PFX_INLINE iterator_t* begin (iterator_t& __itr)
	{
		result_t status = __itr.bind_list (m_begn_ptr);
		if (PFX_STATUS_OK == status)
		{
			__itr.init (m_begn_ptr);
			return &__itr;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE iterator_t* end (iterator_t& __itr)
	{
		result_t status = __itr.bind_list (m_begn_ptr);
		if (PFX_STATUS_OK == status)
		{
			__itr.init (m_end_ptr);
			return &__itr;
		}
		else
		{
			return null;
		}
	}


	PFX_INLINE usize__t size () const
	{
		return m_size;
	}

	PFX_INLINE list_node_t* insert_back (iterator_t& __iter, 
		list_node_t* PARAM_INOUT node_ptr)
	{
		if (__iter.get_bind_list() != &(this->m_begn_ptr))
		{
			return null;
		}

		list_node_t* be_insert_node_ptr = __iter.cur_node();
		if (!be_insert_node_ptr)
		{
			return null;
		}

		list_node_t* inserted_node_ptr = null;

		inserted_node_ptr = list_op_t::insert_list_node_back
			(be_insert_node_ptr, node_ptr);

		if (inserted_node_ptr)
		{
			if (be_insert_node_ptr == m_end_ptr)
			{
				m_end_ptr = inserted_node_ptr;
			}
			++m_size;
		}

		return inserted_node_ptr;
	}

	PFX_INLINE list_node_t* insert_front (iterator_t& __iter, 
		list_node_t* PARAM_INOUT node_ptr)
	{
		if (__iter.get_bind_list() != &(this->m_begn_ptr))
		{
			return null;
		}


		list_node_t* be_insert_node_ptr = __iter.cur_node();
		if (!be_insert_node_ptr)
		{
			return null;
		}

		list_node_t* inserted_node_ptr = null;

		inserted_node_ptr = list_op_t::insert_list_node_front
			(be_insert_node_ptr, node_ptr);

		if (inserted_node_ptr)
		{
			if (be_insert_node_ptr == m_begn_ptr)
			{
				m_begn_ptr = inserted_node_ptr;
			}
			++m_size;
		}

		return inserted_node_ptr;
	}

	PFX_INLINE list_node_t* remove (iterator_t& __iter)
	{
		if (__iter.get_bind_list() != &(this->m_begn_ptr))
		{
			return null;
		}

		list_node_t* be_remove_node_ptr = __iter.cur_node();

		if (!be_remove_node_ptr)
		{
			return null;
		}

		list_node_t* removed_node_ptr = null;
		list_node_t* new_begin_ptr = null;
		list_node_t* new_end_ptr = null;

		if (m_begn_ptr == be_remove_node_ptr)
		{
			new_begin_ptr = be_remove_node_ptr->get_next_node ();
		}

		if (m_end_ptr == be_remove_node_ptr)
		{
			new_end_ptr = be_remove_node_ptr->get_prev_node();
		}

		removed_node_ptr = list_op_t::remove_list_node(be_remove_node_ptr);

		if (removed_node_ptr)
		{
			if (m_begn_ptr == be_remove_node_ptr)
			{
				m_begn_ptr = new_begin_ptr;
			}

			if (m_end_ptr == be_remove_node_ptr)
			{
				m_end_ptr = new_end_ptr;
			}
			--m_size;
		}

		return removed_node_ptr;
	}

	PFX_INLINE list_node_t* push_back (list_node_t* PARAM_INOUT node_ptr)
	{
		if (!node_ptr)
		{
			return null;
		}
		if (!m_end_ptr)
		{
			m_begn_ptr	= node_ptr;
			m_end_ptr	= node_ptr;
			node_ptr->set_prev_node (null);
			node_ptr->set_next_node (null);
			++m_size;
			return node_ptr;
		}

		list_node_t* inserted_node_ptr = null;
		inserted_node_ptr = list_op_t::insert_list_node_back
			(m_end_ptr, node_ptr);
		if (inserted_node_ptr)
		{
			m_end_ptr = inserted_node_ptr;
			++m_size;
		}
		return inserted_node_ptr;
	}

	PFX_INLINE list_node_t* push_fornt (list_node_t* PARAM_INOUT node_ptr)
	{
		if (!node_ptr)
		{
			return null;
		}
		if (!m_begn_ptr)
		{
			m_begn_ptr	= node_ptr;
			m_end_ptr	= node_ptr;
			node_ptr->set_prev_node (null);
			node_ptr->set_next_node (null);
			++m_size;
			return node_ptr;
		}

		list_node_t* inserted_node_ptr = null;
		inserted_node_ptr = list_op_t::insert_list_node_front
			(m_begn_ptr, node_ptr);
		if (inserted_node_ptr)
		{
			m_begn_ptr = inserted_node_ptr;
			++m_size;
		}
		return inserted_node_ptr;
	}

	PFX_INLINE list_node_t* pop_back ()
	{
		if (!m_end_ptr)
		{
			return null;
		}
		list_node_t* prev_node_ptr = m_end_ptr->get_prev_node ();
		list_node_t* removed_node_ptr;
		removed_node_ptr = list_op_t::remove_list_node(m_end_ptr);
		if (removed_node_ptr)
		{
			m_end_ptr = prev_node_ptr;
			if (!prev_node_ptr)
			{
				m_begn_ptr = null;
			}
			--m_size;
		}

		return removed_node_ptr;
	}
	PFX_INLINE list_node_t* pop_fornt ()
	{
		if (!m_begn_ptr)
		{
			return null;
		}
		list_node_t* next_node_ptr = m_begn_ptr->get_next_node ();
		list_node_t* removed_node_ptr;
		removed_node_ptr = list_op_t::remove_list_node(m_begn_ptr);
		if (removed_node_ptr)
		{
			m_begn_ptr = next_node_ptr;
			if (!next_node_ptr)
			{
				m_end_ptr = null;
			}
			--m_size;
		}
		return removed_node_ptr;
	}

	PFX_INLINE bool is_empty () const
	{
		//return (0 == m_size);
		return (!m_begn_ptr || !m_end_ptr || (0 == m_size));
	}

	PFX_INLINE result_t dispose ()
	{
		iterator_t __itr;
		iterator_t* __itr_ptr;
		__itr_ptr = begin(__itr);
		while (__itr_ptr)
		{
			iterator_t __remove_itr = __itr;
			__itr_ptr = __itr_ptr->increase ();
			list_node_t* remove_node_ptr = remove(__remove_itr);
			if (remove_node_ptr)
			{
				release_node(remove_node_ptr);
			}
		}
		return PFX_STATUS_OK;
	}
	PFX_INLINE result_t clean ()
	{
		return dispose();
	}

};


// struct linked_list_operation
#define LINKED_LIST_OPERATION_TEMPLATE_DEF template < class __node_type >
#define CLST_OP linked_list_operation< __node_type >
#define CLST_OP_TPYE typename linked_list_operation< __node_type >

LINKED_LIST_OPERATION_TEMPLATE_DEF
	PFX_INLINE result_t CLST_OP::init_list_node 
	(CLST_OP_TPYE::list_node_t* PARAM_INOUT node_ptr)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (node_ptr)
	{
		node_ptr->set_prev_node (null);
		node_ptr->set_next_node (null);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

LINKED_LIST_OPERATION_TEMPLATE_DEF
	PFX_INLINE CLST_OP_TPYE::list_node_t*	CLST_OP::insert_list_node_back 
	(CLST_OP_TPYE::list_node_t* PARAM_INOUT node_ptr,
	CLST_OP_TPYE::list_node_t* PARAM_INOUT insert_node_ptr)
{
	typedef CLST_OP_TPYE::list_node_t list_node_t;

	list_node_t* inserted_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

		BREAK_LOOP_CONDITION (null == node_ptr || null == insert_node_ptr);
	list_node_t* node_next_ptr = (list_node_t*)node_ptr->get_next_node ();
	node_ptr->set_next_node (insert_node_ptr);
	insert_node_ptr->set_prev_node (node_ptr);
	insert_node_ptr->set_next_node (node_next_ptr);
	if (node_next_ptr)
	{
		node_next_ptr->set_prev_node (insert_node_ptr);
	}
	inserted_node_ptr = insert_node_ptr;
	FOR_ONE_LOOP_END

		return inserted_node_ptr;
}

LINKED_LIST_OPERATION_TEMPLATE_DEF
	PFX_INLINE  CLST_OP_TPYE::list_node_t*	CLST_OP::insert_list_node_front 
	(CLST_OP_TPYE::list_node_t* PARAM_INOUT node_ptr,
	CLST_OP_TPYE::list_node_t* PARAM_INOUT insert_node_ptr)
{
	typedef CLST_OP_TPYE::list_node_t list_node_t;

	list_node_t* inserted_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

		BREAK_LOOP_CONDITION (null == node_ptr || null == insert_node_ptr);
	list_node_t* node_prev_ptr = (list_node_t*)node_ptr->get_prev_node ();
	node_ptr->set_prev_node (insert_node_ptr);
	insert_node_ptr->set_next_node (node_ptr);
	insert_node_ptr->set_prev_node (node_prev_ptr);
	if (node_prev_ptr)
	{
		node_prev_ptr->set_next_node (insert_node_ptr);
	}
	inserted_node_ptr = insert_node_ptr;

	FOR_ONE_LOOP_END

		return inserted_node_ptr;
}

LINKED_LIST_OPERATION_TEMPLATE_DEF
	PFX_INLINE  CLST_OP_TPYE::list_node_t*	CLST_OP::remove_list_node 
	(CLST_OP_TPYE::list_node_t* PARAM_INOUT node_ptr)
{
	typedef CLST_OP_TPYE::list_node_t list_node_t;

	list_node_t* removed_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

		BREAK_LOOP_CONDITION (null == node_ptr);

	removed_node_ptr = node_ptr;
	list_node_t* next_node_ptr =  node_ptr->get_next_node ();
	list_node_t* prev_node_ptr = node_ptr->get_prev_node ();
	if (next_node_ptr)
	{
		next_node_ptr->set_prev_node (prev_node_ptr);
		removed_node_ptr->set_next_node (null);
	}

	if (prev_node_ptr)
	{
		prev_node_ptr->set_next_node (next_node_ptr);
		removed_node_ptr->set_prev_node (null);
	}

	FOR_ONE_LOOP_END

		return removed_node_ptr;
}
//class clinked_list

PECKER_END

#endif			//PFX_CLIST_H_
