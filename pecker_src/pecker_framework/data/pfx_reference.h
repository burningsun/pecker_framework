/*
 * pfx_reference.h
 *
 *  Created on: 2014-7-20
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_REFERENCE_H_
#define		PFX_REFERENCE_H_

#include "../native/syn_lock.h"
#include "../native/pfx_disposeable.h"
#include "pfx_clist.h"

PECKER_BEGIN

class creference_object
{
public:
	typedef typename creference_object											clist_node_t;
	typedef typename linked_list_operation < clist_node_t >		clist_op_t; 
private:
	creference_object*	m_prev_ptr;
	creference_object*	m_next_ptr;
protected:
	IDisposeAble* m_reference_ptr;
public:
	creference_object () : m_next_ptr (null), m_prev_ptr(null), m_reference_ptr(null)
	{
		;
	}
	~creference_object()
	{
		release();
	}
	PFX_INLINE const clist_node_t*	get_prev_node () const
	{
		return m_prev_ptr;
	}
	PFX_INLINE const clist_node_t*	get_next_node () const
	{
		return m_next_ptr;
	}
	PFX_INLINE clist_node_t*	get_prev_node ()
	{
		return m_prev_ptr;
	}
	PFX_INLINE clist_node_t*	get_next_node ()
	{
		return m_next_ptr;
	}

	PFX_INLINE void	set_prev_node (clist_node_t* PARAM_IN node_ptr)
	{
		m_prev_ptr = node_ptr;
	}
	PFX_INLINE void	set_next_node  (clist_node_t* PARAM_IN node_ptr)
	{
		m_next_ptr = node_ptr;
	} 

protected:
	PFX_INLINE result_t dispose_reference ()
	{
		if (m_reference_ptr && null == this->m_next_ptr && null == this->m_prev_ptr)
		{
			return m_reference_ptr->dispose();
		}
		return PFX_STATUS_OK;
	}
	PFX_INLINE creference_object* create (creference_object* __ref_ptr)
	{
		if (__ref_ptr)
		{
			__ref_ptr->m_next_ptr = null;
			__ref_ptr->m_prev_ptr = null;
			__ref_ptr->m_reference_ptr = this->m_reference_ptr;
			return clist_op_t::insert_list_node_back(this, __ref_ptr);
		}
		return null;
	}
public:
	PFX_INLINE result_t release ()
	 {
		 result_t status;
		 status = dispose_reference ();
		 if (PFX_STATUS_OK == status)
		 {
			  clist_op_t::remove_list_node(this);
		 }
		 return status;
	 }
};






PECKER_END


#endif			//PFX_REFERENCE_H_
