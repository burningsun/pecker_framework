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

PFX_INLINE void	simple_deallocate_object(void* PARAM_INOUT pobject)
{
	free(pobject);
}

PFX_INLINE void* simple_reallocate_object(void* pblock_begin, size_t size)
{
	return null;
}

#define	allocate_object		simple_allocate_object
#define	reallocte_object		simple_reallocate_object
#define	deallocate_object	simple_deallocate_object

#define ALLOCATE_OBJECT(TYPE)	(##TYPE *)allocate_object
#define REALLOCATE_OBJECT(TYPE)	(##TYPE *)reallocte_object
#define DEALLOCATE_OBJECT			deallocate_object

#define ALLOCATE_OBJECTS(TYPE,size)	(##TYPE *)allocate_object(size * sizeof(##TYPE))
#define REALLOCATE_OBJECTS(TYPE,block_ptr,size)	(##TYPE *)reallocte_object(block_ptr,size * sizeof(##TYPE))
#define DEALLOCATE_OBJECTS				deallocate_object

PFX_C_EXTERN_BEGIN

typedef void*	(*allocate_obj_callback)(pfx_long_t handle, size_t size);
typedef void* (*reallocate_obj_callback)(pfx_long_t handle, void* pblock_begin, size_t size);
typedef void	(*dellocate_obj_callback)(pfx_long_t handle,void* PARAM_INOUT pobject);
typedef PFX_Interface PFX_CORE_API Iallocator
{
	allocate_obj_callback		allocate_obj;
	dellocate_obj_callback		dellocate_obj;
	reallocate_obj_callback	reallocate_obj;
}IAllocator;

typedef PFX_Interface PFX_CORE_API Iextern_allocator
{
	allocate_obj_callback		allocate_obj;
	dellocate_obj_callback		dellocate_obj;
	reallocate_obj_callback	reallocate_obj;
	const IAllocator*				m_orignal_allocator;		
}Iextern_allocator_t;

PFX_INLINE const IAllocator* get_extern_allocator (const Iextern_allocator* PARAM_IN alloc)
{
	return (const IAllocator*)(alloc);
}

PFX_INLINE void* default_allocator_allocate_obj(pfx_long_t handle,size_t size)
{
	return allocate_object(size);
}

PFX_INLINE void default_allocator_deallocate_obj(pfx_long_t handle,void* PARAM_INOUT pobject)
{
	 deallocate_object(pobject);
}

PFX_INLINE void* default_allocator_reallocate_obj(pfx_long_t handle,void* PARAM_INOUT pblock_old_object,size_t size)
{
	return reallocte_object(pblock_old_object,size);
}



const IAllocator gDefualt_allocator = {default_allocator_allocate_obj,default_allocator_deallocate_obj,default_allocator_reallocate_obj}; 
PFX_C_EXTERN_END


#ifdef __cplusplus
#include <new>
	
PECKER_BEGIN
#define  TEMPLATE_ITEM_DEFINE template < class item_type >
#define  TEMPLATE_ITEM_PARAMS  < item_type >

TEMPLATE_ITEM_DEFINE
item_type* init_buffer_with_item_defualt_constactor (void* PARAM_INOUT buffer,pfx_usize_t buffer_size)
{
	if (sizeof (item_type) > buffer_size)
	{
		return null;
	}
	else
	{
		return new ( static_cast< item_type* > (buffer))item_type();
	}
}

TEMPLATE_ITEM_DEFINE
void*	tempalte_extern_allocate_obj_callback	(pfx_long_t handle, size_t size)
{
	RETURN_INVALID_RESULT (null == handle || 0 == size,null);

	Iextern_allocator_t* alloc = (Iextern_allocator_t*)handle;
	if (null == alloc->m_orignal_allocator)
	{
		return null;
	}

	void* pobjc = alloc->m_orignal_allocator->allocate_obj((pfx_long_t)&(alloc->m_orignal_allocator),size * sizeof(item_type)+sizeof(size));
	if (null != pobjc)
	{
		size_t* size_ = (size_t*)pobjc;
		size_[0] = size;
		pfx_byte_t* alloc_bytes = ((pfx_byte_t*)pobjc) + sizeof (size);
		item_type* item_objs = (item_type*)alloc_bytes;
		for (pfx_usize_t i=0;i<size;++i)			
		{																		
			item_type* item_obj = item_objs + i;		
			new ( static_cast< item_type* > (item_obj))item_type();	
		}
		return item_objs;
	}
	return null;
}

TEMPLATE_ITEM_DEFINE
void*	tempalte_extern_reallocate_obj_callback(pfx_long_t handle, void* pblock_begin, size_t size)
{
	RETURN_INVALID_RESULT (null == handle || null == pblock_begin || 0 == size,null);

	Iextern_allocator_t* alloc = (Iextern_allocator_t*)handle;
	if (null == alloc->m_orignal_allocator)
	{
		return null;
	}

	void* pobjc = alloc->m_orignal_allocator->reallocate_obj ((pfx_long_t)(&alloc->m_orignal_allocator),((pfx_byte_t*)pblock_begin - sizeof(size_t)),size);
	if (null != pobjc)
	{
		size_t* size_ = (size_t*)pobjc;
		size_t old_size = size_[0];
		if (old_size < size)
		{
			size_[0] = size;
		}
		pfx_byte_t* alloc_bytes = ((pfx_byte_t*)pobjc) + sizeof (size);
		item_type* item_objs = (item_type*)alloc_bytes;
		for (pfx_usize_t i=old_size;i<size;++i)			
		{																		
			item_type* item_obj = item_objs + i;		
			new ( static_cast< item_type* > (item_obj))item_type();	
		}
		return item_objs;
	}
	return null;
}

TEMPLATE_ITEM_DEFINE
void		tempalte_extern_dellocate_obj_callback	(pfx_long_t handle,void* PARAM_INOUT pobject)
{
	if (null == handle || null == pobject)
		return;

	Iextern_allocator_t* alloc = (Iextern_allocator_t*)handle;
	if (null == alloc->m_orignal_allocator)
	{
		return;
	}
	pfx_byte_t* objc_bytes = ((pfx_byte_t*)pobject) - sizeof (size_t);
	size_t* size_ = (size_t*)objc_bytes;
	size_t old_size = size_[0];
	item_type* item_objs = (item_type*)pobject;

	for (pfx_usize_t i=0;i<old_size;++i)
	{
		item_objs->~item_type();
	}

	alloc->dellocate_obj((pfx_long_t)&(alloc->m_orignal_allocator),objc_bytes); 
}

TEMPLATE_ITEM_DEFINE
const Iextern_allocator_t* init_extern_allocator (const IAllocator* PARAM_IN allocator_, Iextern_allocator_t* PARAM_OUT out_allocator_)
{
	RETURN_INVALID_RESULT (null == allocator_||null == out_allocator_,null);
	out_allocator_->m_orignal_allocator = allocator_;
	out_allocator_->allocate_obj =  tempalte_extern_allocate_obj_callback TEMPLATE_ITEM_PARAMS ;
	out_allocator_->dellocate_obj =  tempalte_extern_dellocate_obj_callback TEMPLATE_ITEM_PARAMS ;
	out_allocator_->reallocate_obj =  tempalte_extern_reallocate_obj_callback TEMPLATE_ITEM_PARAMS ;
	return out_allocator_;
}

//
//#define TEMPLATE_ALLOCATE_OBJECT (item_type_,size_,item_objs) \
//{																																\
//	item_objs = (item_type_*) (m_allocate.allocate_obj((pfx_long_t)(&m_allocate),size_ * sizeof (item_type_)));\	
//	for (pfx_usize_t i=0;i<size;++i)			\
//	{																		\
//		item_type_* item_obj = item_objs + i;		\
//		new ( static_cast< item_type_* > (item_obj))item_type_();	\
//	}\
//}
//
//#define TEMPLATE_DEALLOCATE_OBJECT  (item_type_,size_,item_objs) \
//if (null != item_objs)							\
//{																\
//	for (pfx_usize_t i=0;i<size;++i)			\
//	{																		\
//		item_type_* item_obj = item_objs + i;		\
//		item_obj->~item_type_();	\
//	}\
//	m_allocate.dellocate_obj((pfx_long_t)(&m_allocate),item_objs);\
//	item_objs = null;\
//}
//
//#define TEMPLATE_REALLOCATE_OBJECT (item_type_,size_,begin_obj_ptr,reallocate_objs) \
//{\
//	void* objs = m_allocate.reallocate_obj ((pfx_long_t)(&m_allocate),begin_obj_ptr,size_ * sizeof (item_type_)));\
//	if (null != objs)	\
//	{	\
//		item_type_ item_objs = (item_type_*) objs;\
//		pfx_usize_t constract_offset = get_item_count();\
//		for (pfx_usize_t i=constract_offset;i<size_;++i)\
//		{\
//			item_type_* item_obj = item_objs + i;		\
//			new ( static_cast< item_type_* > (item_obj))item_type_();	\
//		}\
//	}\
//	reallocate_objs = objs;\
//}


PECKER_END
#endif


#endif			//PFX_ALLOCATOR_H_
