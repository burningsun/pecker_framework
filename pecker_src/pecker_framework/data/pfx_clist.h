/*
 * pfx_clist.h
 *
 *  Created on: 2013-12-17
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CLIST_H_
#define		PFX_CLIST_H_

#include "../pfx_defines.h"
#include "pfx_iterator.h"
#include "pfx_data_traits.h"

PECKER_BEGIN
#define PFX_LIST_NODE_TEMPLATE_DEFINES template < class item_type >
//#define PFX_LIST_NODE_TEMPLATE_PARAMS < item_type >
#define PFX_CLIST_NODE  clist_node < item_type >
#define PFX_CLIST_NODE_TYPE typename clist_node < item_type >

#define PFX_CLIST_ITR  clist_iterator_base < node_type_t >
#define PFX_CLIST_ITR_TYPE typename clist_iterator_base < node_type_t >

#define PFX_CLIST_BASE_TEMPLATE_DEFINES template < class node_type_t >
//#define PFX_CLIST_BASE_TEMPLATE_PARAMS  < node_type_t >
#define PFX_CLIST  clist_base < node_type_t >
#define PFX_CLIST_TYPE  typename clist_base < node_type_t >

template < class item_type >
class PFX_DATA_TEMPALE_API clist_node
{
public:
	typedef 	typename item_type							item_type_t;
	typedef  typename clist_node< item_type > clist_node_t;
protected:
	clist_node_t* m_prev_node_ptr;
	clist_node_t* m_netx_node_ptr;
	item_type	m_item;
public:
	clist_node ();
	clist_node (const clist_node_t& other_);

	PFX_INLINE const clist_node_t*	get_prev_node () const;
	PFX_INLINE const clist_node_t*	get_next_node () const;
	PFX_INLINE const item_type&		get_item () const;
	PFX_INLINE void								set_prev_node (clist_node_t* PARAM_IN node_ptr);
	PFX_INLINE void								set_next_node  (clist_node_t* PARAM_IN node_ptr);
	PFX_INLINE item_type_t&				get_item_ref ();
	PFX_INLINE clist_node_t*				get_prev_node_ref ();
	PFX_INLINE clist_node_t*				get_next_node_ref ();
};

template < class node_type_t >
class PFX_DATA_TEMPALE_API clist_base;

template < class node_type_t >
class PFX_DATA_TEMPALE_API clist_iterator_base : 
	public IPfx_increase_iterator < node_type_t >, 
	public IPfx_decrease_iterator< node_type_t >
{
	friend class clist_base< node_type_t > ;
public:
	typedef typename node_type_t											node_type_t;
	typedef typename node_type_t*											node_type_ptr_t;
	typedef typename const node_type_t*								const_node_type_ptr_t;
	typedef typename clist_iterator_base< node_type_t >	clist_itr_t;
	typedef typename clist_base< node_type_t >					clist_t;
private:
	node_type_t*	m_item_ptr;
	const clist_t*		m_bind_list_ptr;
public:
	clist_iterator_base ();
	~clist_iterator_base();
public:
	const node_type_t* get_item () const;
	clist_itr_t*					increase ();
	clist_itr_t*					decrease ();

	virtual IPfx_increase_iterator < node_type_t >*	increase_iterator ();
	virtual	const node_type_t*										get_current_element () const;

	virtual IPfx_decrease_iterator < node_type_t >*	decrease_iterator ();

public:
	const clist_t* get_bind_list () const;
};

template < class node_type_t >
class PFX_DATA_TEMPALE_API clist_base
{
public:
	typedef node_type_t																node_type_t;
	typedef node_type_t*															node_type_ptr_t;
	typedef const node_type_t*													const_node_type_ptr_t;
	typedef typename clist_iterator_base< node_type_t >	clist_itr_t;
protected:
	node_type_t* m_first_node_ptr;
	node_type_t* m_last_node_ptr;
public:
	clist_base ();
	virtual ~clist_base();

	virtual node_type_t*	new_node () {return null;}
	virtual	result_t				release_node (node_type_t* PARAM_IN node_ptr) {return PFX_STATUS_FAIL;}
public:
	result_t							push_back (node_type_t* PARAM_INOUT node_ptr);
	node_type_t*				pop_back ();

	result_t							push_front (node_type_t* PARAM_INOUT node_ptr);
	node_type_t*				pop_front ();

	const node_type_t*	begin_node () const;
	const node_type_t*	end_node () const;

	boolean_t						is_empty () const;

	clist_itr_t *					begin (clist_itr_t* PARAM_INOUT iterator_ptr) const;
	clist_itr_t *					end (clist_itr_t* PARAM_INOUT iterator_ptr) const;

	result_t							dispose_list ();
	result_t							clear_list ();
	
protected:
	node_type_t*				remove_list_node (node_type_t* PARAM_INOUT node_ptr);
public:
	node_type_t*				remove_list_node (clist_itr_t* PARAM_INOUT iterator_ptr);
	result_t							insert_list_node_back(clist_itr_t* PARAM_INOUT iterator_ptr, node_type_t* PARAM_INOUT node_ptr);
	result_t							insert_list_node_front(clist_itr_t* PARAM_INOUT iterator_ptr, node_type_t* PARAM_INOUT node_ptr);


public:
	static node_type_t*			remove_list_node_unsafe (node_type_t* PARAM_INOUT node_ptr);
public:
	static result_t						init_list_node (node_type_t* PARAM_INOUT node_ptr);
	static const node_type_t*	insert_list_node_back (node_type_t* PARAM_INOUT node_ptr,
														node_type_t* PARAM_INOUT insert_node_ptr);
	static const node_type_t*	insert_list_node_front (node_type_t* PARAM_INOUT node_ptr,
														node_type_t* PARAM_INOUT insert_node_ptr);
	
	static const node_type_t*	get_first_list_node (const node_type_t* PARAM_INOUT node_ptr);
	static const node_type_t*	get_last_list_node (const node_type_t* PARAM_INOUT node_ptr);
	static bool_t							is_first_list_node (const node_type_t* PARAM_INOUT node_ptr);
	static bool_t							is_last_list_node (const node_type_t* PARAM_INOUT node_ptr);
};

#define PFX_CLIST_TEMPLATE_DEFINES template < class node_type_t, typename node_allocator_ >
#define PFX_CLIST_TEMPLATE_PARAMS  < node_type_t, node_allocator_ >

template < class node_type_t, typename node_allocator_ >
class PFX_DATA_TEMPALE_API pfx_clist : public virtual PFX_CLIST
{
public:
	typedef node_allocator_	node_allocator_t;
	typedef node_allocator_	allocator_t;
public:
	virtual node_type_t* new_node ();
	virtual	result_t release_node (node_type_t* PARAM_IN node_ptr);
};

//////////////////////////////////////////////////////////////////////////
PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_CLIST_NODE:: clist_node () : m_netx_node_ptr (null),m_prev_node_ptr(null)
{
	;
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_CLIST_NODE:: clist_node (const PFX_CLIST_NODE_TYPE::clist_node_t& other_)
{
	if (&other_ != this)
	{
		this->m_netx_node_ptr = other_.m_netx_node_ptr;
		this->m_prev_node_ptr = other_.m_prev_node_ptr;
		this->m_item = other_.m_item;
	}
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CLIST_NODE_TYPE::clist_node_t* PFX_CLIST_NODE:: get_prev_node () const
{
	return m_prev_node_ptr;
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CLIST_NODE_TYPE::clist_node_t* PFX_CLIST_NODE ::get_next_node () const
{
	return m_netx_node_ptr;
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_INLINE const PFX_CLIST_NODE_TYPE::item_type_t& PFX_CLIST_NODE ::get_item () const
{
	return m_item;
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_INLINE void PFX_CLIST_NODE ::set_prev_node (PFX_CLIST_NODE_TYPE::clist_node_t* PARAM_IN node_ptr)
{
	m_prev_node_ptr = node_ptr;
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_INLINE void PFX_CLIST_NODE ::set_next_node  (PFX_CLIST_NODE_TYPE::clist_node_t* PARAM_IN node_ptr)
{
	m_netx_node_ptr = node_ptr;
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_INLINE PFX_CLIST_NODE_TYPE::item_type_t& PFX_CLIST_NODE ::get_item_ref ()
{
	return m_item;
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_INLINE PFX_CLIST_NODE_TYPE::clist_node_t* PFX_CLIST_NODE ::get_prev_node_ref () 
{
	return m_prev_node_ptr;
}

PFX_LIST_NODE_TEMPLATE_DEFINES
PFX_INLINE PFX_CLIST_NODE_TYPE::clist_node_t* PFX_CLIST_NODE :: get_next_node_ref () 
{
	return m_netx_node_ptr;
}
//////////////////////////////////////////////////////////////////////////
PFX_CLIST_BASE_TEMPLATE_DEFINES
PFX_CLIST_ITR::clist_iterator_base () : m_item_ptr (null),m_bind_list_ptr(null)
{
	;
}
PFX_CLIST_BASE_TEMPLATE_DEFINES
PFX_CLIST_ITR::~clist_iterator_base ()
{
	m_item_ptr = null;
	m_bind_list_ptr = null;
}
PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_t* PFX_CLIST_ITR::get_item () const
{
	return m_item_ptr;
}
PFX_CLIST_BASE_TEMPLATE_DEFINES
PFX_CLIST_ITR_TYPE::clist_itr_t* PFX_CLIST_ITR::increase ()
{
	PFX_CLIST_ITR_TYPE::clist_itr_t* return_ptr = null;
	if (m_item_ptr && m_item_ptr->get_next_node ())
	{
		m_item_ptr = m_item_ptr->get_next_node_ref ();
		return_ptr = this;
	}
	return return_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
PFX_CLIST_ITR_TYPE::clist_itr_t*  PFX_CLIST_ITR::decrease ()
{
	PFX_CLIST_ITR_TYPE::clist_itr_t* return_ptr = null;
	if (m_item_ptr && m_item_ptr->get_prev_node ())
	{
		m_item_ptr = m_item_ptr->get_prev_node_ref ();
		return_ptr = this;
	}
	return return_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
IPfx_increase_iterator < node_type_t >*	PFX_CLIST_ITR::increase_iterator ()
{
	return increase();
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_t*	PFX_CLIST_ITR::get_current_element () const
{
	return get_item();
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
IPfx_decrease_iterator < node_type_t >*	PFX_CLIST_ITR::decrease_iterator ()
{
	return decrease();
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const PFX_CLIST_ITR_TYPE::clist_t* PFX_CLIST_ITR::get_bind_list () const
{
	return m_bind_list_ptr;
}

//////////////////////////////////////////////////////////////////////////
PFX_CLIST_BASE_TEMPLATE_DEFINES
PFX_CLIST ::clist_base () : m_first_node_ptr (null),
	m_last_node_ptr (null){;}

PFX_CLIST_BASE_TEMPLATE_DEFINES
PFX_CLIST ::~clist_base()
{
	PFX_CLIST ::dispose_list ();
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
result_t PFX_CLIST ::push_back (node_type_t* PARAM_INOUT node_ptr)
{
	result_t status_;

	FOR_ONE_LOOP_BEGIN
	status_ = PFX_CLIST ::init_list_node (node_ptr);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
	if (null == m_first_node_ptr)
	{
		m_first_node_ptr = node_ptr;
	}
	if (null == m_last_node_ptr)
	{
		m_last_node_ptr = node_ptr;
	}
	if (m_last_node_ptr != node_ptr)
	{
		node_ptr = (node_type_t*)PFX_CLIST ::insert_list_node_back (m_last_node_ptr,node_ptr);
		BREAK_LOOP_CONDITION_SETS (null == node_ptr,status_,PFX_STATUS_FAIL);
		m_last_node_ptr = node_ptr;
	}

	
	FOR_ONE_LOOP_END

	return status_;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_t* PFX_CLIST ::pop_back ()
{

	node_type_t* remove_node_ptr = null;

	if (null !=  m_last_node_ptr)
	{
		remove_node_ptr  = m_last_node_ptr;
		m_last_node_ptr = (node_type_t*) m_last_node_ptr->get_prev_node ();
		if (null == m_last_node_ptr)
		{
			m_first_node_ptr = null;
		}
		remove_node_ptr =  (node_type_t*) PFX_CLIST :: remove_list_node_unsafe (remove_node_ptr);
		//remove_node_ptr = PFX_CLIST ::remove_list_node (remove_node_ptr);
	}

	return remove_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
result_t PFX_CLIST ::push_front (node_type_t* PARAM_INOUT node_ptr)
{
	result_t status_;

	FOR_ONE_LOOP_BEGIN
	
	status_ = PFX_CLIST ::init_list_node (node_ptr);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
	if (null == m_first_node_ptr)
	{
		m_first_node_ptr = node_ptr;
	}
	if (null == m_last_node_ptr)
	{
		m_last_node_ptr = node_ptr;
	}
	if (m_first_node_ptr != node_ptr)
	{
		node_ptr = (node_type_t*) PFX_CLIST ::insert_list_node_front (m_first_node_ptr,node_ptr);
		BREAK_LOOP_CONDITION_SETS (null == node_ptr,status_,PFX_STATUS_FAIL);
		m_first_node_ptr = node_ptr;
	}

	FOR_ONE_LOOP_END

	return status_;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_t* PFX_CLIST ::pop_front ()
{
	node_type_t* remove_node_ptr = null;

	if (null !=  m_first_node_ptr)
	{
		remove_node_ptr  = m_first_node_ptr;
		m_first_node_ptr = (node_type_t*) m_first_node_ptr->get_next_node ();
		if (null == m_first_node_ptr)
		{
			m_last_node_ptr = null;
		}
		remove_node_ptr =  (node_type_t*) PFX_CLIST :: remove_list_node_unsafe (remove_node_ptr);
			//(node_type_t*) PFX_CLIST ::remove_list_node (remove_node_ptr);
	}

	return remove_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_t* PFX_CLIST ::begin_node () const
{
	return m_first_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_t* PFX_CLIST ::end_node () const
{
	return m_last_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
boolean_t PFX_CLIST ::is_empty () const
{
	boolean_t b_empty;
	if (!m_first_node_ptr && !m_last_node_ptr)
	{
		b_empty = PFX_BOOL_TRUE;
	}
	else if (m_first_node_ptr && m_last_node_ptr)
	{
		b_empty = PFX_BOOL_FALSE;
	}
	else
	{
		b_empty = PFX_BOOL_INVALID;
	}
	return b_empty;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
PFX_CLIST_TYPE::clist_itr_t * PFX_CLIST ::begin (PFX_CLIST_TYPE::clist_itr_t* PARAM_INOUT iterator_ptr) const
{
	if (iterator_ptr)
	{
		//const PFX_CLIST* this_ptr = this;
		iterator_ptr->m_bind_list_ptr = this;
		iterator_ptr->m_item_ptr = m_first_node_ptr;
	}
	return iterator_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
PFX_CLIST_TYPE::clist_itr_t * PFX_CLIST ::end (PFX_CLIST_TYPE::clist_itr_t* PARAM_INOUT iterator_ptr) const
{
	if (iterator_ptr)
	{
		//const PFX_CLIST* this_ptr = this;
		iterator_ptr->m_bind_list_ptr = this;
		iterator_ptr->m_item_ptr = m_last_node_ptr;
	}
	return iterator_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
result_t PFX_CLIST ::dispose_list ()
{
	const node_type_t* current_node_ptr = begin_node ();
	result_t status_ = PFX_STATUS_OK;
	while (null != m_last_node_ptr)
	{
		node_type_t* remove_node_ptr = (node_type_t*)current_node_ptr;
		current_node_ptr = current_node_ptr->get_next_node ();
		remove_node_ptr = (node_type_t*) PFX_CLIST ::remove_list_node (remove_node_ptr);
		status_ = PFX_CLIST ::release_node (remove_node_ptr);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
	}
	return status_;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_t* PFX_CLIST ::remove_list_node (node_type_t* PARAM_INOUT node_ptr)
{
	node_type_t* removed_node_ptr = null;
	if (node_ptr == m_first_node_ptr)
	{
		removed_node_ptr = pop_front();
	}
	else if (node_ptr == m_last_node_ptr)
	{
		removed_node_ptr = pop_back();
	}
	else
	{
		removed_node_ptr = PFX_CLIST :: remove_list_node_unsafe (node_ptr);
	}
	return removed_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_t* PFX_CLIST ::remove_list_node (PFX_CLIST_TYPE::clist_itr_t* PARAM_INOUT iterator_ptr)
{
	if (iterator_ptr && iterator_ptr->get_bind_list ())
	{
		node_type_t* remove_node = remove_list_node(iterator_ptr->m_item_ptr);
		PFX_CLIST_TYPE::clist_itr_t* next_iterator =  iterator_ptr->increase ();
		if (null == next_iterator)
		{
			next_iterator = iterator_ptr->decrease ();
		}
		if (null == next_iterator)
		{
			iterator_ptr->m_item_ptr = null;
		}		
	}
	return null;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
result_t PFX_CLIST ::insert_list_node_back(PFX_CLIST_TYPE::clist_itr_t* PARAM_INOUT iterator_ptr, node_type_t* PARAM_INOUT node_ptr)
{
	result_t status;
	if (node_ptr && iterator_ptr && iterator_ptr->get_bind_list ())
	{
		node_type_t* node_added;
		node_type_t* node_to_be_add_ptr;
		node_added = null;
		node_to_be_add_ptr = iterator_ptr->m_item_ptr;
		if (node_to_be_add_ptr == m_last_node_ptr)
		{
			status = push_back(node_ptr);
		}
		else
		{
			FOR_ONE_LOOP_BEGIN
			status = PFX_CLIST ::init_list_node (node_ptr);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
			
			if (is_empty())
			{
				m_first_node_ptr = node_ptr;
				m_last_node_ptr = node_ptr;
			}
			else if (node_to_be_add_ptr)
			 {
				 node_ptr = (node_type_t*)PFX_CLIST ::insert_list_node_back (node_to_be_add_ptr,node_ptr);
				 BREAK_LOOP_CONDITION_SETS (null == node_ptr,status,PFX_STATUS_FAIL);
			 }
			else
			{
				status = PFX_STATUS_INVALID_PARAMS;
			}
			FOR_ONE_LOOP_END
		}
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	return status;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
result_t PFX_CLIST ::insert_list_node_front(PFX_CLIST_TYPE::clist_itr_t* PARAM_INOUT iterator_ptr, node_type_t* PARAM_INOUT node_ptr)
{
	result_t status;
	if (node_ptr && iterator_ptr && iterator_ptr->get_bind_list ())
	{
		node_type_t* node_added;
		node_type_t* node_to_be_add_ptr;
		node_added = null;
		node_to_be_add_ptr = iterator_ptr->m_item_ptr;
		if (node_to_be_add_ptr == m_first_node_ptr)
		{
			status = push_front(node_ptr);
		}
		else
		{
			FOR_ONE_LOOP_BEGIN
				
			status = PFX_CLIST ::init_list_node (node_ptr);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

			if (is_empty())
			{
				m_first_node_ptr = node_ptr;
				m_last_node_ptr = node_ptr;
			}
			else if (node_to_be_add_ptr)
			{
				node_ptr = (node_type_t*)PFX_CLIST ::insert_list_node_front (node_to_be_add_ptr,node_ptr);
				BREAK_LOOP_CONDITION_SETS (null == node_ptr,status,PFX_STATUS_FAIL);
			}
			else
			{
				status = PFX_STATUS_INVALID_PARAMS;
			}
			FOR_ONE_LOOP_END
		}
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	return status;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
result_t PFX_CLIST ::clear_list ()
{
	return PFX_CLIST ::dispose_list();
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
result_t PFX_CLIST ::init_list_node (node_type_t* PARAM_INOUT node_ptr)
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

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_t* PFX_CLIST ::insert_list_node_back (node_type_t* PARAM_INOUT node_ptr,
	node_type_t* PARAM_INOUT insert_node_ptr)
{
	node_type_t* inserted_node_ptr = null;

	FOR_ONE_LOOP_BEGIN
	BREAK_LOOP_CONDITION (null == node_ptr || null == insert_node_ptr);
	node_type_t* node_next_ptr = (node_type_t*)node_ptr->get_next_node ();
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

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_t* PFX_CLIST ::insert_list_node_front (node_type_t* PARAM_INOUT node_ptr,
	node_type_t* PARAM_INOUT insert_node_ptr)
{
	node_type_t* inserted_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

	BREAK_LOOP_CONDITION (null == node_ptr || null == insert_node_ptr);
	node_type_t* node_prev_ptr = (node_type_t*)node_ptr->get_prev_node ();
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

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_t* PFX_CLIST ::remove_list_node_unsafe (node_type_t* PARAM_INOUT node_ptr)
{
	node_type_t* removed_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

	BREAK_LOOP_CONDITION (null == node_ptr);

	removed_node_ptr = node_ptr;
	node_type_t* next_node_ptr = (node_type_t*) node_ptr->get_next_node ();
	node_type_t* prev_node_ptr = (node_type_t*) node_ptr->get_prev_node ();
	if (next_node_ptr)
	{
		next_node_ptr->set_prev_node (prev_node_ptr);
	}

	if (prev_node_ptr)
	{
		prev_node_ptr->set_next_node (next_node_ptr);
	}

	FOR_ONE_LOOP_END

	return removed_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_t* PFX_CLIST ::get_first_list_node (const node_type_t* PARAM_INOUT node_ptr)
{
	FOR_ONE_LOOP_BEGIN
	BREAK_LOOP_CONDITION (null == node_ptr);
	const node_type_t* node_bk_ptr = node_ptr;	
	while (null != node_ptr->get_prev_node() || node_bk_ptr != node_ptr->get_prev_node())
	{
		node_ptr = node_ptr->get_prev_node();
	}
	FOR_ONE_LOOP_END
	return node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_t* PFX_CLIST ::get_last_list_node (const node_type_t* PARAM_INOUT node_ptr)
{
	FOR_ONE_LOOP_BEGIN
	BREAK_LOOP_CONDITION (null == node_ptr);
	const node_type_t* node_bk_ptr = node_ptr;	
	while (null != node_ptr->get_next_node() || node_bk_ptr != node_ptr->get_next_node())
	{
		node_ptr = node_ptr->get_next_node();
	}
	FOR_ONE_LOOP_END
	return node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
bool_t PFX_CLIST ::is_first_list_node (const node_type_t* PARAM_INOUT node_ptr)
{
	if (node_ptr && (null == node_ptr->get_prev_node()))
	{
		return PFX_BOOL_TRUE;
	}
	else
	{
		return PFX_BOOL_FALSE;
	}
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
bool_t PFX_CLIST ::is_last_list_node (const node_type_t* PARAM_INOUT node_ptr)
{
	if (node_ptr && (null == node_ptr->get_next_node()))
	{
		return PFX_BOOL_TRUE;
	}
	else
	{
		return PFX_BOOL_FALSE;
	}
}
 

//////////////////////////////////////////////////////////////////////////
PFX_CLIST_TEMPLATE_DEFINES
node_type_t* pfx_clist PFX_CLIST_TEMPLATE_PARAMS::new_node ()
{
		return (node_type_t*)(node_allocator_::allocate_object ());
}

PFX_CLIST_TEMPLATE_DEFINES
result_t pfx_clist PFX_CLIST_TEMPLATE_PARAMS::release_node (node_type_t* PARAM_IN node_ptr)
{
	if (node_ptr)
	{
		return node_allocator_::deallocate_object (node_ptr);
	}

	return PFX_STATUS_OK;
}

PECKER_END

#endif			//PFX_CLIST_H_
