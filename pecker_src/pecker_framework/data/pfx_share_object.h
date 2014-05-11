/*
 * pfx_share_object.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHARE_OBJECT_H_
#define		PFX_SHARE_OBJECT_H_

#include "pfx_data_traits.h"
#include "pfx_clist.h"

PECKER_BEGIN

template < class allocable_object >
class cauto_release_object
{
public:
	typedef typename  allocatable_object_type < allocable_object >::element_t reference_object_t;
private:
	reference_object_t* m_reference_object_ptr;
	
protected:
	cauto_release_object ();
public:
	explicit cauto_release_object (reference_object_t* PARAM_INOUT reference_object_ptr);
	virtual ~cauto_release_object ();
};

template < class allocable_object >
class cshare_object_base 
{
public:
	typedef typename  allocatable_handle_object_type < allocable_object >::handle_t		reference_handle_t;
	//typedef reference_object_t*																									reference_handle_t;
private:
	friend clist_base < cshare_object_base < allocable_object > >;

protected:
	reference_handle_t m_reference_object_handle;

private:
	cshare_object_base < allocable_object >* m_prev_object_ptr;
	cshare_object_base < allocable_object >* m_next_object_ptr;
public:
	cshare_object_base ();
	cshare_object_base (cshare_object_base < allocable_object > PARAM_INOUT &other_object);
	virtual ~cshare_object_base();

public:
	PFX_INLINE const cshare_object_base < allocable_object >* get_prev_node () const;
	PFX_INLINE const cshare_object_base < allocable_object >* get_next_node () const;
private:
	PFX_INLINE void set_prev_node (cshare_object_base < allocable_object >* PARAM_IN node_ptr);
	PFX_INLINE void set_next_node (cshare_object_base < allocable_object >* PARAM_IN node_ptr);

protected:
	virtual PFX_INLINE result_t			bind_object (reference_handle_t PARAM_IN bind_obj_ptr);
public:
	virtual PFX_INLINE result_t			unbind_object ();
	virtual PFX_INLINE boolean_t	is_sharing_object ();
protected:
	virtual result_t release_object (reference_handle_t PARAM_INOUT handle_);
	virtual result_t create_object ();
public:
	virtual PFX_INLINE reference_handle_t get_reference_object () const;
	virtual PFX_INLINE result_t	init_reference_object (const reference_handle_t& PARAM_INOUT other_ptr);

public:
	virtual PFX_INLINE cshare_object_base < allocable_object >* share_object (cshare_object_base < allocable_object >* PARAM_INOUT other_object); 
};


//////////////////////////////////////////////////////////////////////////
#define AUTO_RELEASE_OBJECT_TEMPALTE_DEFINES template < class allocable_object >
#define AUTO_RELEASE_OBJECT_TEMPALTE_PARAMS < allocable_object >
#define auto_release_refobject_type typename  allocatable_object_type < allocable_object >::element_t

AUTO_RELEASE_OBJECT_TEMPALTE_DEFINES
cauto_release_object AUTO_RELEASE_OBJECT_TEMPALTE_PARAMS ::
		cauto_release_object ():m_reference_object_ptr(null)
{
	;
}
AUTO_RELEASE_OBJECT_TEMPALTE_DEFINES
cauto_release_object AUTO_RELEASE_OBJECT_TEMPALTE_PARAMS ::
		cauto_release_object (auto_release_refobject_type* PARAM_INOUT reference_object_ptr):m_reference_object_ptr(reference_object_ptr)
{
	;
}
AUTO_RELEASE_OBJECT_TEMPALTE_DEFINES
cauto_release_object AUTO_RELEASE_OBJECT_TEMPALTE_PARAMS ::
	~cauto_release_object ()
{
	if (m_reference_object_ptr)
	{
		typedef typename  allocatable_object_type < allocable_object >::allocator_t alloc;
		alloc::deallocate_object (m_reference_object_ptr);
		m_reference_object_ptr = null;
	}

}

//////////////////////////////////////////////////////////////////////////
#define SHARE_OBJECT_TEMPALTE_DEFINES template < class allocable_object >
#define SHARE_OBJECT_TEMPALTE_PARAMS < allocable_object >
#define share_refobject_handle_t typename  allocatable_handle_object_type < allocable_object >::handle_t

SHARE_OBJECT_TEMPALTE_DEFINES
cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS:: cshare_object_base ():
m_prev_object_ptr(null), m_next_object_ptr(null)
{
	m_reference_object_handle = null;
}
SHARE_OBJECT_TEMPALTE_DEFINES
cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS:: cshare_object_base (cshare_object_base < allocable_object > PARAM_INOUT &other_object)
{
	if (this != &other_object)
	{
		m_reference_object_handle = null;
		m_prev_object_ptr = null; 
		m_next_object_ptr = null;

		other_object.share_object (this);
	}

}
SHARE_OBJECT_TEMPALTE_DEFINES
cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::~cshare_object_base()
{
	unbind_object ();
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE const cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS* 
		cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::get_prev_node () const
{
	return m_prev_object_ptr;
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE const cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS* 
		cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::get_next_node () const
{
	return m_next_object_ptr;
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE void cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::
	set_prev_node (cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS* PARAM_IN node_ptr)
{
	m_prev_object_ptr = node_ptr;
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE void cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::
	set_next_node (cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS* PARAM_IN node_ptr)
{
	m_next_object_ptr = node_ptr;
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE result_t	cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::
		bind_object (share_refobject_handle_t PARAM_IN bind_obj_ptr)
{
	result_t status;
	FOR_ONE_LOOP_BEGIN
	if (null != bind_obj_ptr)
	{
		status = unbind_object();
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
		m_reference_object_handle = bind_obj_ptr;
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	FOR_ONE_LOOP_END
	return status;
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE result_t	cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::unbind_object ()
{
	result_t status;
	boolean_t sharing_object;
	sharing_object = is_sharing_object();
	if (PFX_BOOL_TRUE == sharing_object)
	{
		cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS* remove_node_ptr;
		remove_node_ptr = clist_base < cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS > ::remove_list_node_unsafe(this);
		if (remove_node_ptr != this)
		{
			status = PFX_STATUS_MEM_ERR;
		}
		else
		{
			status = clist_base < cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS > ::init_list_node(this);
		}
	}
	else
	{
		status = release_object (m_reference_object_handle);
		m_reference_object_handle = null;
	}
	return status;
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE boolean_t cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::is_sharing_object ()
{
	if (!get_prev_node() && !get_next_node())
	{
		return PFX_BOOL_FALSE;
	}
	else
	{
		return PFX_BOOL_TRUE;
	}
}

SHARE_OBJECT_TEMPALTE_DEFINES
result_t cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::release_object (share_refobject_handle_t handle_)
{
	result_t status = PFX_STATUS_OK;
	if (null != handle_)
	{
		typedef typename  allocatable_handle_object_type < allocable_object >::allocator_t alloc;
		status = alloc::deallocate_object (handle_);
		handle_ = null;
	}
	return status;
}

SHARE_OBJECT_TEMPALTE_DEFINES
result_t cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::create_object ()
{
	result_t status;
	status = unbind_object();
	if (PFX_STATUS_OK == status)
	{
		typedef typename  allocatable_handle_object_type < allocable_object >::allocator_t alloc;
		m_reference_object_handle = alloc::allocate_object ();
		if (null != m_reference_object_handle)
		{
			status = PFX_STATUS_MEM_LOW;
		}
	}
	return status;
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE share_refobject_handle_t cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::get_reference_object () const
{
	return m_reference_object_handle;
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE result_t	cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::init_reference_object (const share_refobject_handle_t& PARAM_INOUT other_ptr)
{
	if (null != other_ptr)
	{
		m_reference_object_handle = other_ptr;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
}

SHARE_OBJECT_TEMPALTE_DEFINES
PFX_INLINE cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS* 
cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS::share_object 
	(cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS* PARAM_INOUT other_object)
{
	result_t status;

	FOR_ONE_LOOP_BEGIN
	if (other_object && other_object != this)
	{
		status = other_object->unbind_object();
		BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);

		if (null != clist_base < cshare_object_base SHARE_OBJECT_TEMPALTE_PARAMS > ::insert_list_node_back(this,other_object))
		{
			other_object->m_reference_object_handle = this->m_reference_object_handle;
		}
		else
		{
			status = PFX_STATUS_MEM_ERR;
		}	
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	FOR_ONE_LOOP_END

	if (PFX_STATUS_OK == status)
	{
		return other_object;
	}
	else
	{
		return null;
	}
}

PECKER_END

#endif			//PFX_SHARE_OBJECT_H_
