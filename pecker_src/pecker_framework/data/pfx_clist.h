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

#define PFX_CLIST_BASE_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_CLIST_BASE_TEMPLATE_PARAMS  < node_type_ >

template < class item_type >
class pfx_clist_node_base
{
protected:
	pfx_clist_node_base < item_type >* m_prev_node_ptr;
	pfx_clist_node_base < item_type >* m_netx_node_ptr;
	item_type	m_item;
public:
	pfx_clist_node_base () : m_netx_node_ptr (null),m_prev_node_ptr(null)
	{
		;
	}
	pfx_clist_node_base (const pfx_clist_node_base < item_type >& other_)
	{
		if (&other_ != this)
		{
			this->m_netx_node_ptr = other_.m_netx_node_ptr;
			this->m_prev_node_ptr = other_.m_prev_node_ptr;
			this->m_item = other_.m_item;
		}
	}
	PFX_INLINE const pfx_clist_node_base < item_type >* get_prev_node () const
	{
		return m_prev_node_ptr;
	}
	PFX_INLINE const pfx_clist_node_base < item_type >* get_next_node () const
	{
		return m_netx_node_ptr;
	}
	PFX_INLINE const item_type& get_item () const
	{
		return m_item;
	}
	PFX_INLINE void set_prev_node (pfx_clist_node_base < item_type >* PARAM_IN node_ptr)
	{
		m_prev_node_ptr = node_ptr;
	}
	PFX_INLINE void set_next_node  (pfx_clist_node_base < item_type >* PARAM_IN node_ptr)
	{
		m_netx_node_ptr = node_ptr;
	}
	PFX_INLINE item_type& get_item_ref ()
	{
		return m_item;
	}
	PFX_INLINE pfx_clist_node_base < item_type >*& get_prev_node_ref () 
	{
		return m_prev_node_ptr;
	}
	PFX_INLINE pfx_clist_node_base < item_type >*& get_next_node_ref () 
	{
		return m_netx_node_ptr;
	}
};

template < class node_type_ >
class pfx_clist_base
{
protected:
	node_type_* m_first_node_ptr;
	node_type_* m_last_node_ptr;
public:
	pfx_clist_base ();
	virtual ~pfx_clist_base();

	virtual node_type_* new_node () {return null;};
	virtual	pfx_result_t release_node (node_type_* PARAM_IN node_ptr) {return PFX_STATUS_FAIL;};
public:
	pfx_result_t push_back (node_type_* PARAM_INOUT node_ptr);
	node_type_* pop_back ();

	pfx_result_t push_front (node_type_* PARAM_INOUT node_ptr);
	node_type_* pop_front ();

	const node_type_* begin_node () const;
	const node_type_* end_node () const;

	pfx_result_t dispose_list ();
	pfx_result_t clear_list ();
public:
	node_type_* remove_list_node (node_type_* PARAM_INOUT node_ptr);
protected:
	static node_type_* remove_list_node_unsafe (node_type_* PARAM_INOUT node_ptr);
public:
	static pfx_result_t init_list_node (node_type_* PARAM_INOUT node_ptr);
	static const node_type_* insert_list_node_back (node_type_* PARAM_INOUT node_ptr,
		node_type_* PARAM_INOUT insert_node_ptr);
	static const node_type_* insert_list_node_front (node_type_* PARAM_INOUT node_ptr,
		node_type_* PARAM_INOUT insert_node_ptr);
	
	static const node_type_* get_first_list_node (const node_type_* PARAM_INOUT node_ptr);
	static const node_type_* get_last_list_node (const node_type_* PARAM_INOUT node_ptr);
	static pfx_bool_t is_first_list_node (const node_type_* PARAM_INOUT node_ptr);
	static pfx_bool_t is_last_list_node (const node_type_* PARAM_INOUT node_ptr);
};

#define PFX_CLIST_TEMPLATE_DEFINES template < class node_type_, typename node_allocator_ >
#define PFX_CLIST_TEMPLATE_PARAMS  < node_type_, node_allocator_ >

template < class node_type_, typename node_allocator_ >
class pfx_clist : public virtual pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS
{
private:
	node_allocator_* m_allocator_ptr;
public:
	pfx_clist (node_allocator_* PARAM_INOUT alloator_ptr = null);
public:
	virtual node_type_* new_node ();
	virtual	pfx_result_t release_node (node_type_* PARAM_IN node_ptr);
};


//////////////////////////////////////////////////////////////////////////
PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::pfx_clist_base () : m_first_node_ptr (null),
	m_last_node_ptr (null){;}

PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::~pfx_clist_base()
{
	pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::dispose_list ();
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_result_t pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::push_back (node_type_* PARAM_INOUT node_ptr)
{
	pfx_result_t status_;

	FOR_ONE_LOOP_BEGIN
	status_ = pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::init_list_node (node_ptr);
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
		node_ptr = (node_type_*)pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::insert_list_node_back (m_last_node_ptr,node_ptr);
		BREAK_LOOP_CONDITION_SETS (null == node_ptr,status_,PFX_STATUS_FAIL);
		m_last_node_ptr = node_ptr;
	}

	
	FOR_ONE_LOOP_END

	return status_;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::pop_back ()
{

	node_type_* remove_node_ptr = null;

	if (null !=  m_last_node_ptr)
	{
		remove_node_ptr  = m_last_node_ptr;
		m_last_node_ptr = (node_type_*) m_last_node_ptr->get_prev_node ();
		if (null == m_last_node_ptr)
		{
			m_first_node_ptr = null;
		}
		remove_node_ptr = pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::remove_list_node (remove_node_ptr);
	}

	return remove_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_result_t pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::push_front (node_type_* PARAM_INOUT node_ptr)
{
	pfx_result_t status_;

	FOR_ONE_LOOP_BEGIN
	
	status_ = pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::init_list_node (node_ptr);
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
		node_ptr = (node_type_*) pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::insert_list_node_front (m_first_node_ptr,node_ptr);
		BREAK_LOOP_CONDITION_SETS (null == node_ptr,status_,PFX_STATUS_FAIL);
		m_first_node_ptr = node_ptr;
	}

	FOR_ONE_LOOP_END

	return status_;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::pop_front ()
{
	node_type_* remove_node_ptr = null;

	if (null !=  m_first_node_ptr)
	{
		remove_node_ptr  = m_first_node_ptr;
		m_first_node_ptr = (node_type_*) m_first_node_ptr->get_next_node ();
		if (null == m_first_node_ptr)
		{
			m_last_node_ptr = null;
		}
		remove_node_ptr = (node_type_*) pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::remove_list_node (remove_node_ptr);
	}

	return remove_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::begin_node () const
{
	return m_first_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::end_node () const
{
	return m_last_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_result_t pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::dispose_list ()
{
	const node_type_* current_node_ptr = begin_node ();
	pfx_result_t status_ = PFX_STATUS_OK;
	while (null != m_last_node_ptr)
	{
		node_type_* remove_node_ptr = (node_type_*)current_node_ptr;
		current_node_ptr = current_node_ptr->get_next_node ();
		remove_node_ptr = (node_type_*) 
			pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::remove_list_node (remove_node_ptr);
		status_ = pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::release_node (remove_node_ptr);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status_);
	}
	return status_;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::remove_list_node (node_type_* PARAM_INOUT node_ptr)
{
	node_type_* removed_node_ptr = null;
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
		removed_node_ptr = pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS :: remove_list_node_unsafe (node_ptr);
	}
	return removed_node_ptr;
}


PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_result_t pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::clear_list ()
{
	return pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::dispose_list();
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_result_t pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::init_list_node (node_type_* PARAM_INOUT node_ptr)
{
	pfx_result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (node_ptr)
	{
		node_ptr->set_prev_node (null);
		node_ptr->set_next_node (null);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::insert_list_node_back (node_type_* PARAM_INOUT node_ptr,
	node_type_* PARAM_INOUT insert_node_ptr)
{
	node_type_* inserted_node_ptr = null;

	FOR_ONE_LOOP_BEGIN
	BREAK_LOOP_CONDITION (null == node_ptr || null == insert_node_ptr);
	node_type_* node_next_ptr = (node_type_*)node_ptr->get_next_node ();
	node_ptr->set_next_node (insert_node_ptr);
	insert_node_ptr->set_prev_node (node_ptr);
	insert_node_ptr->set_next_node (node_next_ptr);
	if (node_next_ptr)
	{
		node_next_ptr->set_prev_node (node_ptr);
	}
	inserted_node_ptr = insert_node_ptr;
	FOR_ONE_LOOP_END

	return inserted_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::insert_list_node_front (node_type_* PARAM_INOUT node_ptr,
	node_type_* PARAM_INOUT insert_node_ptr)
{
	node_type_* inserted_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

	BREAK_LOOP_CONDITION (null == node_ptr || null == insert_node_ptr);
	node_type_* node_prev_ptr = (node_type_*)node_ptr->get_prev_node ();
	node_ptr->set_prev_node (insert_node_ptr);
	insert_node_ptr->set_next_node (node_ptr);
	insert_node_ptr->set_prev_node (node_prev_ptr);
	if (node_prev_ptr)
	{
		node_prev_ptr->set_next_node (node_ptr);
	}
	inserted_node_ptr = insert_node_ptr;

	FOR_ONE_LOOP_END

	return inserted_node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::remove_list_node_unsafe (node_type_* PARAM_INOUT node_ptr)
{
	node_type_* removed_node_ptr = null;

	FOR_ONE_LOOP_BEGIN

	BREAK_LOOP_CONDITION (null == node_ptr);

	removed_node_ptr = node_ptr;
	node_type_* next_node_ptr = (node_type_*) node_ptr->get_next_node ();
	node_type_* prev_node_ptr = (node_type_*) node_ptr->get_prev_node ();
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
const node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::get_first_list_node (const node_type_* PARAM_INOUT node_ptr)
{
	FOR_ONE_LOOP_BEGIN
	BREAK_LOOP_CONDITION (null == node_ptr);
	const node_type_* node_bk_ptr = node_ptr;	
	while (null != node_ptr->get_prev_node() || node_bk_ptr != node_ptr->get_prev_node())
	{
		node_ptr = node_ptr->get_prev_node();
	}
	FOR_ONE_LOOP_END
	return node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
const node_type_* pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::get_last_list_node (const node_type_* PARAM_INOUT node_ptr)
{
	FOR_ONE_LOOP_BEGIN
	BREAK_LOOP_CONDITION (null == node_ptr);
	const node_type_* node_bk_ptr = node_ptr;	
	while (null != node_ptr->get_next_node() || node_bk_ptr != node_ptr->get_next_node())
	{
		node_ptr = node_ptr->get_next_node();
	}
	FOR_ONE_LOOP_END
	return node_ptr;
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_bool_t pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::is_first_list_node (const node_type_* PARAM_INOUT node_ptr)
{
	if (node_ptr && (null == node_ptr->get_prev_node()))
	{
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}

PFX_CLIST_BASE_TEMPLATE_DEFINES
pfx_bool_t pfx_clist_base PFX_CLIST_BASE_TEMPLATE_PARAMS ::is_last_list_node (const node_type_* PARAM_INOUT node_ptr)
{
	if (node_ptr && (null == node_ptr->get_next_node()))
	{
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}
 

//////////////////////////////////////////////////////////////////////////
PFX_CLIST_TEMPLATE_DEFINES
pfx_clist PFX_CLIST_TEMPLATE_PARAMS::pfx_clist (node_allocator_* PARAM_INOUT alloator_ptr) :
	m_allocator_ptr (alloator_ptr)
{
}

PFX_CLIST_TEMPLATE_DEFINES
node_type_* pfx_clist PFX_CLIST_TEMPLATE_PARAMS::new_node ()
{
	if (m_allocator_ptr)
	{
		return (node_type_*)(m_allocator_ptr->allocate_obj ());
	}
	else
	{
		return null;
	}
}

PFX_CLIST_TEMPLATE_DEFINES
pfx_result_t pfx_clist PFX_CLIST_TEMPLATE_PARAMS::release_node (node_type_* PARAM_IN node_ptr)
{
	if (m_allocator_ptr)
	{
		if (node_ptr)
		{
			m_allocator_ptr->dellocate_obj (node_ptr);
		}

		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}
}

PECKER_END

#endif			//PFX_CLIST_H_
