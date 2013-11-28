/*
 * pfx_allocator.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_ALLOCATOR_H_
#define		PFX_ALLOCATOR_H_

#include "../pfx_defines.h"

PFX_INLINE void*	simple_allocate_object(size_t size)
{
	return malloc(size);
}

PFX_INLINE void		simple_deallocate_object(void* PARAM_INOUT pobject)
{
	free(pobject);
}

#define	allocate_object		simple_allocate_object
#define	deallocate_object	simple_deallocate_object

#define ALLOCATE_OBJECT(TYPE)	(##TYPE *)allocate_object
#define DEALLOCATE_OBJECT			deallocate_object

#define ALLOCATE_OBJECTS(TYPE,size)	(##TYPE *)allocate_object(size * sizeof(##TYPE))
#define DEALLOCATE_OBJECTS				deallocate_object

PFX_C_EXTERN_BEGIN

typedef PFX_Interface Iallocator
{
	 void*	(*allocate_obj)(pfx_long_t handle, size_t size);
	 void	(*dellocate_obj)(pfx_long_t handle,void* PARAM_INOUT pobject);
}IAllocator;

PFX_INLINE void* default_allocator_allocate_obj(pfx_long_t handle,size_t size)
{
	return allocate_object(size);
}

PFX_INLINE void default_allocator_deallocate_obj(pfx_long_t handle,void* PARAM_INOUT pobject)
{
	 deallocate_object(pobject);
}


const IAllocator gDefualt_allocator = {default_allocator_allocate_obj,default_allocator_deallocate_obj}; 
PFX_C_EXTERN_END

#endif			//PFX_ALLOCATOR_H_
