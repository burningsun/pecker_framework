﻿/*
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
#include "pfx_linked_mem_pool.h"
#include "../native/pecker_allocator.h"

PECKER_BEGIN

template <class __ref>
struct new_reference_method;

#define REF_NEW_FLAG (0xAABB)
//(0xAABBCCDD)
#define LOCK_SHARE_FLAG (0xCCDD)

template < class _ref_obejct >
class creference_base
{

public:
	typedef _ref_obejct									element_t;
	typedef creference_base< element_t >				ref_t;
	typedef creference_base< element_t >				clist_node_t;
	typedef linked_list_operation < clist_node_t >		clist_op_t;

private:
	ref_t*		m_prev_ptr;
	ref_t*		m_next_ptr;
	u16flag_t	m_reference_flag;
	u16flag_t	m_lock_share_flag;
	element_t*	m_reference_ptr;
public:
	PFX_INLINE void set_new_reference(u16flag_t key)
	{
		if (REF_NEW_FLAG == key)
		{
			dispose();
			m_reference_flag = REF_NEW_FLAG;
			m_reference_ptr = create_element();
		}
	}
protected:
	PFX_INLINE element_t* get_reference()
	{
		return m_reference_ptr;
	}
	PFX_INLINE const element_t* get_reference()	const
	{
		return m_reference_ptr;
	}
protected:
	critical_section_lock_ins_t*	m_list_lock_ptr;

	static PFX_INLINE critical_section_lock_ins_t& ref_lock()
	{
		static 	 critical_section_lock_ins_t __lock;
		return __lock;
	}
public:
	creference_base() : m_next_ptr(null), 
		m_prev_ptr(null), 
		m_reference_ptr(null), 
		m_reference_flag(0),
		m_lock_share_flag(0)
	{
		m_list_lock_ptr = &ref_lock();
	}
	creference_base(ref_t& __other)
	{
		if (&__other != this)
		{
			critical_section_lock_t __lock;
			this->m_list_lock_ptr = __other.m_list_lock_ptr;
			if (this->m_list_lock_ptr)
			{
				__lock.lock(this->m_list_lock_ptr->m_cs);
			}	
			__other.create_reference(this);
		}
	}
	virtual ~creference_base()
	{
		
		if (m_list_lock_ptr)
		{
			critical_section_lock_t __lock;
			__lock.lock(m_list_lock_ptr->m_cs);
			dispose();
		}
		else
		{
			dispose();
		}
		
	}
	PFX_INLINE const clist_node_t*	get_prev_node() const
	{
		return m_prev_ptr;
	}
	PFX_INLINE const clist_node_t*	get_next_node() const
	{
		return m_next_ptr;
	}
	PFX_INLINE clist_node_t*	get_prev_node()
	{
		return m_prev_ptr;
	}
	PFX_INLINE clist_node_t*	get_next_node()
	{
		return m_next_ptr;
	}

	PFX_INLINE void	set_prev_node(clist_node_t* PARAM_IN node_ptr)
	{
		m_prev_ptr = node_ptr;
	}
	PFX_INLINE void	set_next_node(clist_node_t* PARAM_IN node_ptr)
	{
		m_next_ptr = node_ptr;
	}
private:
	PFX_INLINE result_t dispose_reference()
	{
		if (m_reference_ptr && 
			null == this->m_next_ptr && null == this->m_prev_ptr)
		{
			return dispose_element(m_reference_ptr);
		}
		return PFX_STATUS_OK;
	}
	PFX_INLINE ref_t* create_reference(ref_t* __ref_ptr)
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

	PFX_INLINE result_t dispose()
	{
		//critical_section_lock_t __lock;
		//if (m_list_lock_ptr)
		//{
		//	__lock.lock(m_list_lock_ptr->m_cs);
		//}

		result_t status;
		status = dispose_reference();
		if (PFX_STATUS_OK == status)
		{
			clist_op_t::remove_list_node(this);
			m_reference_ptr = null;
		}
		return status;
	}
//public:
//	static PFX_INLINE ref_t* new_reference()
//	{
//		ref_t* new_obj = new ref_t;
//		if (new_obj)
//		{
//			new_obj->m_reference_flag = REF_NEW_FLAG;
//			new_obj->m_reference_ptr = new_obj->create_element();
//		}
//		return new_obj;
//	}
public:
	PFX_INLINE bool is_referenced() const
	{
		return (m_next_ptr || m_prev_ptr);
	}
	PFX_INLINE ref_t* create_reference(bool bref_this = true)
	{
		if (LOCK_SHARE_FLAG == m_lock_share_flag)
		{
			return null;
		}
		critical_section_lock_t __lock;
		if (m_list_lock_ptr)
		{
			__lock.lock(m_list_lock_ptr->m_cs);
		}
		if (LOCK_SHARE_FLAG == m_lock_share_flag)
		{
			return null;
		}

		if (m_reference_ptr)
		{
			ref_t* new_obj = new ref_t;
			if (new_obj)
			{
				new_obj->m_reference_flag = REF_NEW_FLAG;
				return create_reference(new_obj);
			}
		}
		else
		{
			m_reference_ptr = create_element();
			if (bref_this)
			{
				return this;
			}
			else
			{
				ref_t* new_obj = new ref_t;
				if (new_obj)
				{
					new_obj->m_reference_flag = REF_NEW_FLAG;
					return create_reference(new_obj);
				}
			}
			
		}

		return null;
	}
	PFX_INLINE element_t* create_ref_element()
	{
		ref_t* ref_ptr;
		ref_ptr = create_reference();
		if (ref_ptr)
		{
			return ref_ptr->m_reference_ptr;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE void release_reference()
	{
		critical_section_lock_t __lock;
		if (m_list_lock_ptr)
		{
			__lock.lock(m_list_lock_ptr->m_cs);
		}
		if (LOCK_SHARE_FLAG == this->m_lock_share_flag)
		{
			return;
		}
		else if (REF_NEW_FLAG == this->m_reference_flag)
		{
			delete this;
		}
		else
		{
			dispose();
		}
		
	}
	PFX_INLINE ref_t* share_to(ref_t* PARAM_INOUT __ref_ptr)
	{
		if (!__ref_ptr)
		{
			return null;
		}
		if (__ref_ptr != this)
		{
			
			if (__ref_ptr->m_list_lock_ptr)
			{
				critical_section_lock_t __lock_ref;
				__lock_ref.lock(__ref_ptr->m_list_lock_ptr->m_cs);
				__ref_ptr->m_lock_share_flag = LOCK_SHARE_FLAG;
				__ref_ptr->dispose();
				__lock_ref.unlock();
			}
			else
			{
				__ref_ptr->m_lock_share_flag = LOCK_SHARE_FLAG;
				__ref_ptr->dispose();
			}
			critical_section_lock_t __lock;
			if (this->m_list_lock_ptr)
			{
				__lock.lock(this->m_list_lock_ptr->m_cs);
			}
	
			__ref_ptr->m_list_lock_ptr = this->m_list_lock_ptr;
			ref_t* retn_ptr = this->create_reference(__ref_ptr);
			__ref_ptr->m_lock_share_flag = 0;
			return retn_ptr;
		}
		else
		{
			return this;
		}
	}

protected:
	virtual element_t* create_element(){ return null; }
	virtual result_t dispose_element(element_t*& elem_ptr){ return PFX_STATUS_ERROR_; }
};


template <class __ref>
struct new_reference_method
{
	static PFX_INLINE __ref* new_reference()
	{
		__ref* new_obj_ptr;
		new_obj_ptr = new __ref;
		
		if (new_obj_ptr)
		{
			new_obj_ptr->set_new_reference (REF_NEW_FLAG);
		}
		return new_obj_ptr;
	}
};



PECKER_END


#endif			//PFX_REFERENCE_H_
