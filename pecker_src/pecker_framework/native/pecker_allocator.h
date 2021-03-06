﻿/*
 * pecker_allocator.h
 *
 *  Created on: 2012-6-19
 *      Author: 李镇城 (cut / cutxyz)
 */
//#pragma once
#ifndef PECKER_ALLOCATOR_H_
#define PECKER_ALLOCATOR_H_

//#include "../pecker_reference.h"
#include <new>
#include "../pfx_defines.h"
//#include "../data/pfx_data_traits.h"

PECKER_BEGIN

template< class source_type, class target_type >
struct pecker_force_adapter
{
	static PFX_INLINE target_type* convert_to(source_type* PARAM_IN __src)
	{ 
		if (__src)
		{
			return new(__src)target_type();
		}
		return null;
	}
};

#define PFX_ALLOCATOR_TEMPLATE_DEFINES template < class element_ >
#define PFX_ALLOCATOR_TEMPLATE_PARAMS < element_ >

PFX_Interface Ialloacate
{
	virtual ~Ialloacate()
	{	;}
	virtual void* allocate_object () = 0;
	virtual result_t deallocate_object(void*& PARAM_INOUT del_element_ptr) = 0;
};

template < class element_ >
struct pecker_simple_allocator
{

	typedef element_                              element_t;
	typedef element_*                             handle_t;
	typedef pecker_simple_allocator < element_t > allocator_t;

	static PFX_INLINE element_t* allocate_object ();
	static PFX_INLINE result_t deallocate_object(element_t*& PARAM_INOUT del_element_ptr);

	static PFX_INLINE element_t* reallocate_objects (element_t* PARAM_INOUT del_element_ptr,usize__t new_count);

	static PFX_INLINE element_t* allocate_objects (usize__t count);
	static PFX_INLINE result_t deallocate_objects(element_t*& PARAM_INOUT del_element_ptr);
};
//////////////////////////////////////////////////////////////////////////
#define SIMPLEALLOCATOR_TYPE typename pecker_simple_allocator< element_ >
#define SIMPLEALLOCATOR    pecker_simple_allocator< element_ >

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE SIMPLEALLOCATOR_TYPE::element_t* SIMPLEALLOCATOR::allocate_object ()
{
	return new element_t;
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE result_t SIMPLEALLOCATOR::deallocate_object
(element_t*& PARAM_INOUT del_element_ptr)
{
	result_t status;
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
PFX_INLINE SIMPLEALLOCATOR_TYPE::element_t* SIMPLEALLOCATOR::reallocate_objects
(element_t* PARAM_INOUT del_element_ptr,usize__t new_count)
{
	return null;
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE SIMPLEALLOCATOR_TYPE::element_t* SIMPLEALLOCATOR::allocate_objects (usize__t count)
{
	return new element_t[count];
}

PFX_ALLOCATOR_TEMPLATE_DEFINES
PFX_INLINE result_t SIMPLEALLOCATOR::deallocate_objects
(element_t*& PARAM_INOUT del_element_ptr)
{
	result_t status;
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

PECKER_END

#endif
