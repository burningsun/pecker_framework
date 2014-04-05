/*
 * pecker_allocator.h
 *
 *  Created on: 2012-6-19
 *      Author: 李镇城 (cut / cutxyz)
 */
//#pragma once
#ifndef PECKER_ALLOCATOR_H_
#define PECKER_ALLOCATOR_H_

//#include "../pecker_reference.h"
//#include <new>
#include "../pfx_defines.h"

PECKER_BEGIN

#define PFX_ALLOCATOR_TEMPLATE_DEFINES template < class element_ >
#define PFX_ALLOCATOR_TEMPLATE_PARAMS < element_ >

template < class element_ >
PFX_Interface IPfx_allocator
{
	virtual element_* allocate_obj () = 0;
	virtual pfx_result_t dellocate_obj (element_*& PARAM_INOUT del_element_ptr) = 0;

	virtual element_* reallocate_objs (element_* PARAM_INOUT del_element_ptr,pfx_usize_t new_count) = 0;
	virtual element_* allocate_objs (pfx_usize_t count) = 0;
	virtual pfx_result_t dellocate_objs (element_*& PARAM_INOUT del_element_ptr) = 0;
};

template < class element_ >
class pecker_simple_allocator : public IPfx_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS
{
public:
	PFX_INLINE element_* allocate_obj ();
	PFX_INLINE pfx_result_t dellocate_obj (element_*& PARAM_INOUT del_element_ptr);

	PFX_INLINE element_* reallocate_objs (element_* PARAM_INOUT del_element_ptr,pfx_usize_t new_count);

	PFX_INLINE element_* allocate_objs (pfx_usize_t count);
	PFX_INLINE pfx_result_t dellocate_objs (element_*& PARAM_INOUT del_element_ptr);

public:
	static PFX_INLINE element_* allocate_object ();
	static PFX_INLINE pfx_result_t deallocate_object(element_*&  PARAM_INOUT del_element_ptr);

	static PFX_INLINE element_* reallocate_objects (element_* PARAM_INOUT del_element_ptr,pfx_usize_t new_count);
	
	static PFX_INLINE element_* allocate_objects (pfx_usize_t count);
	static PFX_INLINE pfx_result_t deallocate_objects(element_*&  PARAM_INOUT del_element_ptr);
};


//////////////////////////////////////////////////////////////////////////
PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE element_* pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::allocate_object ()
{
	return new element_;
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::deallocate_object 
																			(element_*& PARAM_INOUT del_element_ptr)
{
	pfx_result_t status;
	if (del_element_ptr)
	{
		delete del_element_ptr;
		del_element_ptr = null;
		status = PFX_STATUS_OK;
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	return status;
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE element_* pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::reallocate_objects 
																(element_* PARAM_INOUT del_element_ptr,pfx_usize_t new_count)
{
	return null;
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE element_* pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::allocate_objects (pfx_usize_t count)
{
	return new element_[count];
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::deallocate_objects 
																											(element_*& PARAM_INOUT del_element_ptr)
{
	pfx_result_t status;
	if (del_element_ptr)
	{
		delete [] del_element_ptr;
		del_element_ptr = null;
		status = PFX_STATUS_OK;
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	return status;
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE element_* pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::allocate_obj ()
{
	return pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS ::allocate_object ();
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::dellocate_obj 
																		(element_*& PARAM_INOUT del_element_ptr)
{
	return pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::deallocate_object (del_element_ptr);
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
	PFX_INLINE element_* pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::reallocate_objs 
	(element_* PARAM_INOUT del_element_ptr,pfx_usize_t new_count)
{
	return pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS ::reallocate_objects (del_element_ptr,new_count);
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
	PFX_INLINE element_* pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::allocate_objs (pfx_usize_t count)
{
	return pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS ::allocate_objects (count);
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
	PFX_INLINE pfx_result_t pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS::dellocate_objs 
	(element_*& PARAM_INOUT del_element_ptr)
{
	return pecker_simple_allocator PFX_ALLOCATOR_TEMPLATE_PARAMS ::deallocate_objects (del_element_ptr);
}



PECKER_END

#endif
