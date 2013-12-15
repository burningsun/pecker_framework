/*
 * pfx_array_algorithm.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_ARRAY_ALGORITHM_H_
#define		PFX_ARRAY_ALGORITHM_H_

#include "../pfx_defines.h"
#include "../native/pfx_allocator.h"
#include "pfx_list.h" 

PFX_C_EXTERN_BEGIN

typedef struct PFX_DATA_API st_pfx_base_array
{
	unsigned m_using_extern_buffer : 1;
	unsigned m_defualt_array_size : 31;

	size_t						m_item_size;
	size_t						m_buffer_size;
	size_t						m_buffer_length;
	size_t						m_auto_allocate_step;

	const IAllocator*	m_pitem_allocator;
	void*						m_parray_data;
}pfx_base_array_t;

PFX_DATA_API pfx_base_array_t*  init_base_array_by_buffer (size_t item_size,
	size_t allocate_step,
	char* PARAM_INOUT pbuffer,
	size_t buffer_size,
	const IAllocator* PARAM_IN pitem_allocator,
	pfx_result_t* PARAM_INOUT pstatus);

PFX_DATA_API pfx_base_array_t*  new_base_array (const IAllocator* PARAM_IN parray_allocator,
										size_t item_size,
										size_t default_item_count,
										size_t allocate_step,
										const IAllocator* PARAM_IN parray_item_allocator,
										pfx_result_t* PARAM_INOUT pstatus);

PFX_DATA_API pfx_result_t  delete_base_array (pfx_base_array_t* pdel_array, const IAllocator* PARAM_IN parray_allocator);

PFX_DATA_API pfx_result_t  resize_base_array (pfx_base_array_t* PARAM_INOUT parray,size_t item_count,pfx_bool_t bnew_buffer,size_t new_resize_step);

PFX_INLINE pfx_result_t clear_base_array (pfx_base_array_t* PARAM_INOUT parray,pfx_bool_t bnew_buffer,size_t new_resize_step);

// 只能取一个item，不安全获取，单线程应用在任何会改变array长度的操作后，都应该重新获取，多线程应用必须加锁
PFX_INLINE void* get_item_at_base_array (pfx_base_array_t* PARAM_INOUT parray,size_t item_index);

// 只用于c语言的，c++涉及对象构造，会出bug
PFX_INLINE void* base_array_push_back (pfx_base_array_t* PARAM_INOUT parray,const void* PARAM_IN pitem_obj,pfx_result_t* pstatus);

PFX_INLINE void* base_array_pop_back (pfx_base_array_t* PARAM_INOUT parray,pfx_bool_t bnew_buffer, pfx_result_t* pstatus);

PFX_INLINE void* base_array_push_back_n (pfx_base_array_t* PARAM_INOUT parray,const void* PARAM_IN pitem_obj,size_t item_count, pfx_result_t* pstatus);

PFX_INLINE void* base_array_pop_back_n (pfx_base_array_t* PARAM_INOUT parray,size_t item_count,pfx_bool_t bnew_buffer, size_t* npop_count,pfx_result_t* pstatus);

#pragma pack(push)
#pragma pack(1)
typedef struct PFX_DATA_API st_pfx_arraybuffer_block
{
	char*	m_pblock_data;
	size_t	m_pblock_size;
	char		m_char_begins;
}pfx_arraybuffer_block_t;
#pragma pack(pop)

typedef enum PFX_DATA_API enum_aligned_type
{
	ALIGNED_1_BYTE = 0, // 1 << 0
	ALIGNED_2_BYTE, // 1 << 1
	ALIGNED_4_BYTE, // 1 << 2
	ALIGNED_8_BYTE, // 1 << 3
	ALIGNED_16_BYTE,// 1<< 4
	ALIGNED_32_BYTE,// 1<< 5
	ALIGNED_64_BYTE,// 1<< 6
	ALIGNED_128_BYTE,// 1<< 7
	ALIGNED_256_BYTE,// 1<< 8
	ALIGNED_512_BYTE,// 1<< 9
	ALIGNED_1024_BYTE,// 1<< 10
	ALIGNED_TYPE_COUNT
}ALIGNED_TYPE_t;

PFX_DATA_API pfx_arraybuffer_block_t*  init_arraybuffer_block_by_buffer (	char* PARAM_INOUT pbuffer,
	size_t buffer_size, ALIGNED_TYPE_t aligned_type,pfx_result_t* PARAM_INOUT pstatus);

PFX_DATA_API pfx_arraybuffer_block_t*  new_arraybuffer_block (size_t buffer_size,ALIGNED_TYPE_t aligned_type,
																						const IAllocator* PARAM_IN parray_item_allocator,
																						pfx_result_t* PARAM_INOUT pstatus);

PFX_DATA_API pfx_result_t  delete_arraybuffer_block (pfx_arraybuffer_block_t* PARAM_INOUT parray_block,
																const IAllocator* PARAM_IN parray_item_allocator);


typedef struct PFX_DATA_API st_pfx_dynamic_linear_array
{
	size_t						m_item_size;
	size_t						m_buffer_length;
	size_t						m_auto_allocate_step;
	const IAllocator*	m_block_allocator;
	pfx_enum_t			m_aligned_type;

	pfx_base_array_t	m_block_array;
}pfx_dynamic_linear_array_t;

PFX_DATA_API pfx_dynamic_linear_array_t*  init_dynamic_linear_array_by_buffer (size_t item_size,
	size_t allocate_step,
	size_t allocate_block_array_step,
	char* PARAM_INOUT pbuffer,
	size_t buffer_size,
	ALIGNED_TYPE_t aligned_type,
	const IAllocator* PARAM_IN pblock_allocator,
	const IAllocator* PARAM_IN pblock_array_item_allocator,
	pfx_result_t* PARAM_INOUT pstatus);

PFX_DATA_API pfx_dynamic_linear_array_t*  new_dynamic_linear_array (const IAllocator* PARAM_IN parray_allocator,
	size_t item_size,
	size_t default_item_buffer_count,
	size_t allocate_step,
	size_t allocate_block_array_step,
	ALIGNED_TYPE_t aligned_type,
	const IAllocator* PARAM_IN pblock_allocator,
	const IAllocator* PARAM_IN pblock_array_item_allocator,
	pfx_result_t* PARAM_INOUT pstatus);

PFX_DATA_API pfx_result_t  delete_dynamic_linear_array (pfx_dynamic_linear_array_t* pdel_array, 
	const IAllocator* PARAM_IN parray_allocator);

PFX_DATA_API pfx_result_t  resize_dynamic_linear_array (pfx_dynamic_linear_array_t* PARAM_INOUT parray,
	size_t item_count,pfx_bool_t bnew_buffer);

PFX_DATA_API pfx_result_t  config_dynamic_linear_block_array_step (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t step);

PFX_INLINE pfx_arraybuffer_block_t** get_dynamic_linear_array_block_pointer (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t block_index);

PFX_INLINE pfx_arraybuffer_block_t* get_dynamic_linear_array_block (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t block_index);

PFX_INLINE size_t get_dynamic_linear_array_block_count (pfx_dynamic_linear_array_t* PARAM_INOUT parray);

PFX_INLINE pfx_result_t clear_dynamic_linear_array (pfx_dynamic_linear_array_t* PARAM_INOUT parray,pfx_bool_t bnew_buffer);

PFX_INLINE void* get_item_at_dynamic_linear_array_direct (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t block_index,size_t item_index);

PFX_INLINE void* get_item_at_dynamic_linear_array (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t block_index,size_t item_index);

PFX_INLINE void* get_item_at_dynamic_linear_array_linear (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t item_index);

PFX_INLINE size_t set_n_items_at_dynamic_linear_array_block (pfx_dynamic_linear_array_t* PARAM_INOUT parray,
	size_t block_index,size_t item_index,const void* PARAM_IN pitem_buffer,size_t nitem_count);

PFX_INLINE size_t set_n_items_at_dynamic_linear_array_linear (pfx_dynamic_linear_array_t* PARAM_INOUT parray,
	size_t item_index,const void* PARAM_IN pitem_buffer,size_t nitem_count);


// 只用于c语言的，c++涉及对象构造，会出bug
PFX_INLINE void* dynamic_linear_array_push_back (pfx_dynamic_linear_array_t* PARAM_INOUT parray,const void* PARAM_IN pitem_obj,pfx_result_t* pstatus);

PFX_INLINE void* dynamic_linear_array_pop_back (pfx_dynamic_linear_array_t* PARAM_INOUT parray,pfx_bool_t bnew_buffer, pfx_result_t* pstatus);

PFX_INLINE void*dynamic_linear_array_push_back_n (pfx_dynamic_linear_array_t* PARAM_INOUT parray,const void* PARAM_IN pitem_obj,size_t item_count, pfx_result_t* pstatus);

PFX_INLINE void* dynamic_linear_array_pop_back_n (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t item_count,pfx_bool_t bnew_buffer, size_t* npop_count,pfx_result_t* pstatus);






















//////////////////////////////////////////////////////////////////////////
PFX_INLINE pfx_result_t clear_base_array(pfx_base_array_t* PARAM_INOUT parray,pfx_bool_t bnew_buffer,size_t new_resize_step)
{
	return resize_base_array(parray,0,bnew_buffer,new_resize_step);
}

// 只能取一个item，不安全获取，单线程应用在任何会改变array长度的操作后，都应该重新获取，多线程应用必须加锁
PFX_INLINE void* get_item_at_base_array(pfx_base_array_t* PARAM_INOUT parray,size_t item_index)
{
	RETURN_INVALID_RESULT ((null == parray || parray->m_buffer_length <= 0 || parray->m_item_size <= 0 || parray->m_buffer_size <= 0),
		null);
	return (void*)((pfx_long_t)(parray->m_parray_data) + parray->m_item_size * item_index);
}

// 只用于c语言的，c++涉及对象构造，会出bug
PFX_INLINE void* base_array_push_back (pfx_base_array_t* PARAM_INOUT parray,const void* PARAM_IN pitem_obj,pfx_result_t* pstatus)
{
	if (null == parray || null == pitem_obj)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS);
		return null;
	}
	else
	{
		pfx_result_t status;
		void* last_item = null;
		size_t new_index = parray->m_buffer_length;
		status = resize_base_array (parray,parray->m_buffer_length+1,pfx_false,INVALID_VALUE);
		if (PFX_STATUS_OK == status)
		{
			last_item = get_item_at_base_array (parray,new_index);
			if (null != last_item)
			{
				memcpy (last_item,pitem_obj,parray->m_item_size);
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
			}
		}

		SET_POINTER_VALUE (pstatus,status);

		return last_item;
	}
}

PFX_INLINE void* base_array_pop_back (pfx_base_array_t* PARAM_INOUT parray,pfx_bool_t bnew_buffer, pfx_result_t* pstatus)
{
	if (null == parray)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS);
		return null;
	}
	else
	{
		pfx_result_t status = PFX_STATUS_OK;

		size_t new_size = (parray->m_buffer_length > 0) ?  (parray->m_buffer_length-1) : (0);
		void* last_item = (parray->m_buffer_length > 0) ? get_item_at_base_array(parray,new_size) : null;

		if (null != last_item)
		{
			status = resize_base_array (parray,new_size,bnew_buffer,INVALID_VALUE);
			if (PFX_STATUS_OK != status)
			{
				last_item = null;
			}
			if (pfx_true == bnew_buffer)
			{
				last_item = null;
			}
		}

		SET_POINTER_VALUE (pstatus,status);

		return last_item;
	}
}

PFX_INLINE void* base_array_push_back_n (pfx_base_array_t* PARAM_INOUT parray,const void* PARAM_IN pitem_obj,size_t item_count, pfx_result_t* pstatus)
{
	if (null == parray || null == pitem_obj)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS);
		return null;
	}
	else if (item_count <= 0)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_OK);
		return null;
	}
	else
	{
		pfx_result_t status;
		void* last_item = null;
		size_t new_index = parray->m_buffer_length;
		status = resize_base_array (parray,parray->m_buffer_length+item_count,pfx_false,INVALID_VALUE);
		if (PFX_STATUS_OK == status)
		{
			last_item = get_item_at_base_array (parray,new_index);
			if (null != last_item)
			{
				memcpy(last_item,pitem_obj,parray->m_item_size * item_count);
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
			}
		}

		SET_POINTER_VALUE (pstatus,status);

		return last_item;
	}
}

PFX_INLINE void* base_array_pop_back_n(pfx_base_array_t* PARAM_INOUT parray,size_t item_count,pfx_bool_t bnew_buffer, size_t* npop_count,pfx_result_t* pstatus)
{
	if (null == parray)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS);
		return null;
	}
	else
	{
		pfx_result_t status = PFX_STATUS_OK;

		size_t new_size = (parray->m_buffer_length > item_count) ?  (parray->m_buffer_length-item_count) : (0);
		void* last_item = (parray->m_buffer_length > 0) ? get_item_at_base_array (parray,new_size) : null;

		if (npop_count)
		{
			*npop_count = (parray->m_buffer_length > item_count) ? item_count: parray->m_buffer_length;
		}

		if (null != last_item)
		{
			status = resize_base_array (parray,new_size,bnew_buffer,INVALID_VALUE);
			if (PFX_STATUS_OK != status)
			{
				last_item = null;
			}
			if (pfx_true == bnew_buffer)
			{
				last_item = null;
			}
		}

		SET_POINTER_VALUE (pstatus,status);


		return last_item;
	}
}
//////////////////////////////////////////////////////////////////////////
PFX_INLINE pfx_arraybuffer_block_t** get_dynamic_linear_array_block_pointer (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t block_index)
{
	if (null != parray)
	{
		return (pfx_arraybuffer_block_t**)get_item_at_base_array (&parray->m_block_array,block_index);
	}
	else
	{
		return null;
	}
}

PFX_INLINE pfx_arraybuffer_block_t* get_dynamic_linear_array_block (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t block_index)
{
	pfx_arraybuffer_block_t** ppblock = get_dynamic_linear_array_block_pointer (parray,block_index);
	if (ppblock)
	{
		return *ppblock;
	}
	return null;
}

PFX_INLINE size_t get_dynamic_linear_array_block_count (pfx_dynamic_linear_array_t* PARAM_INOUT parray)
{
	if (null != parray)
	{
		return parray->m_block_array.m_buffer_length;
	}
	else
	{
		return 0;
	}
}

PFX_INLINE pfx_result_t clear_dynamic_linear_array (pfx_dynamic_linear_array_t* PARAM_INOUT parray,pfx_bool_t bnew_buffer)
{
	return resize_dynamic_linear_array (parray,0,bnew_buffer);
}

PFX_INLINE void* get_item_at_dynamic_linear_array_direct (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t block_index,size_t item_index)
{
	pfx_arraybuffer_block_t* pblock = get_dynamic_linear_array_block (parray,block_index);
	if (null != pblock)
	{
		size_t offset = item_index * parray->m_item_size;
		if (offset < pblock->m_pblock_size)
		{
			return (pblock->m_pblock_data + offset);
		}
	}
	return null;
}

PFX_INLINE void* get_item_at_dynamic_linear_array (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t block_index,size_t item_index)
{
	if (null != parray)
	{
		if (parray->m_buffer_length < block_index * parray->m_block_array.m_buffer_size + item_index)
		{
			return null;
		}
		else
		{
			return get_item_at_dynamic_linear_array_direct (parray,block_index,item_index);
		}
	}
	return null;
}

PFX_INLINE void* get_item_at_dynamic_linear_array_linear (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t item_index)
{
	if (null != parray)
	{
		if (parray->m_buffer_length < item_index)
		{
			return null;
		}
		else
		{
			size_t block_index = item_index / parray->m_auto_allocate_step;
			item_index = item_index % parray->m_auto_allocate_step;
			return get_item_at_dynamic_linear_array_direct (parray,block_index,item_index);
		}
	}
	return null;
}

PFX_INLINE size_t set_n_items_at_dynamic_linear_array_block (pfx_dynamic_linear_array_t* PARAM_INOUT parray,
	size_t block_index,size_t item_index,const void* PARAM_IN pitem_buffer,size_t nitem_count)
{
	size_t success_size = 0;
	pfx_arraybuffer_block_t* pblock = get_dynamic_linear_array_block (parray,block_index);
	if (null != pblock)
	{	
		if (item_index >= parray->m_auto_allocate_step)
		{
			return 0;
		}
		if (nitem_count > parray->m_auto_allocate_step)
		{
			nitem_count = parray->m_auto_allocate_step;
		}
		success_size = (nitem_count + item_index > parray->m_auto_allocate_step) ? (parray->m_auto_allocate_step - item_index):nitem_count;
		memcpy (pblock->m_pblock_data+item_index*parray->m_item_size,pitem_buffer,success_size * parray->m_item_size);
	}
	return success_size;
}

PFX_INLINE size_t set_n_items_at_dynamic_linear_array_linear (pfx_dynamic_linear_array_t* PARAM_INOUT parray,
	size_t item_index,const void* PARAM_IN pitem_buffer,size_t nitem_count)
{
	size_t success_size = 0;
	if (null != parray)
	{
		if (parray->m_buffer_length >= item_index)
		{
			size_t temp_success_size = 0;
			size_t block_index = item_index  / parray->m_auto_allocate_step;
			item_index = item_index % parray->m_auto_allocate_step;
			temp_success_size = set_n_items_at_dynamic_linear_array_block (parray,block_index,item_index,pitem_buffer,nitem_count);
			nitem_count -= temp_success_size;
			success_size += temp_success_size;
			pitem_buffer = (char*)pitem_buffer +  temp_success_size * parray->m_item_size;
			while (temp_success_size != 0 && 0 != nitem_count)
			{
				++block_index;
				item_index += temp_success_size;
				if (item_index  >= parray->m_auto_allocate_step)
				{
					item_index = 0;
				}
				temp_success_size = set_n_items_at_dynamic_linear_array_block (parray,block_index,item_index,pitem_buffer,nitem_count);
				nitem_count -= temp_success_size;
				success_size += temp_success_size;
				pitem_buffer  = (char*)pitem_buffer +  temp_success_size * parray->m_item_size;
			}
		}
	}
	return success_size;
}


// 只用于c语言的，c++涉及对象构造，会出bug
PFX_INLINE void* dynamic_linear_array_push_back (pfx_dynamic_linear_array_t* PARAM_INOUT parray,const void* PARAM_IN pitem_obj,pfx_result_t* pstatus)
{
	if (null == parray || null == pitem_obj)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS);
		return null;
	}
	else
	{
		pfx_result_t status;
		void* last_item = null;
		size_t new_index = parray->m_buffer_length;
		status = resize_dynamic_linear_array (parray,parray->m_buffer_length+1,pfx_false);
		if (PFX_STATUS_OK == status)
		{
			last_item = get_item_at_dynamic_linear_array_linear (parray,new_index);
			if (null != last_item)
			{
				memcpy (last_item,pitem_obj,parray->m_item_size);
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
			}
		}

		SET_POINTER_VALUE (pstatus,status);

		return last_item;
	}
}

PFX_INLINE void* dynamic_linear_array_pop_back (pfx_dynamic_linear_array_t* PARAM_INOUT parray,pfx_bool_t bnew_buffer, pfx_result_t* pstatus)
{
	if (null == parray)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS);
		return null;
	}
	else
	{
		pfx_result_t status = PFX_STATUS_OK;

		size_t new_size = (parray->m_buffer_length > 0) ?  (parray->m_buffer_length-1) : (0);
		void* last_item = (parray->m_buffer_length > 0) ? get_item_at_dynamic_linear_array_linear (parray,new_size) : null;

		if (null != last_item)
		{
			status = resize_dynamic_linear_array (parray,new_size,bnew_buffer);
			if (PFX_STATUS_OK != status)
			{
				last_item = null;
			}
			if (pfx_true == bnew_buffer)
			{
				last_item = null;
			}
		}

		SET_POINTER_VALUE (pstatus,status);

		return last_item;
	}
}

PFX_INLINE void*dynamic_linear_array_push_back_n (pfx_dynamic_linear_array_t* PARAM_INOUT parray,const void* PARAM_IN pitem_obj,size_t item_count, pfx_result_t* pstatus)
{
	if (null == parray || null == pitem_obj)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS);
		return null;
	}
	else if (item_count <= 0)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_OK);
		return null;
	}
	else
	{
		pfx_result_t status;
		void* last_item = null;
		size_t new_index = parray->m_buffer_length;
		status = resize_dynamic_linear_array (parray,parray->m_buffer_length+item_count,pfx_false);
		if (PFX_STATUS_OK == status)
		{
			size_t success_size = set_n_items_at_dynamic_linear_array_linear (parray,new_index,pitem_obj,item_count);
			if (success_size != item_count)
			{
				status = PFX_STATUS_MEM_ERR;
			}
			else
			{
				last_item = get_item_at_dynamic_linear_array_linear (parray,new_index);
			}

		}

		SET_POINTER_VALUE (pstatus,status);

		return last_item;
	}
}

PFX_INLINE void* dynamic_linear_array_pop_back_n (pfx_dynamic_linear_array_t* PARAM_INOUT parray,size_t item_count,pfx_bool_t bnew_buffer, size_t* npop_count,pfx_result_t* pstatus)
{
	if (null == parray)
	{
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS);
		return null;
	}
	else
	{
		pfx_result_t status = PFX_STATUS_OK;

		size_t new_size = (parray->m_buffer_length > item_count) ?  (parray->m_buffer_length-item_count) : (0);
		void* last_item = (parray->m_buffer_length > 0) ? get_item_at_dynamic_linear_array_linear (parray,new_size) : null;

		if (npop_count)
		{
			*npop_count = (parray->m_buffer_length > item_count) ? item_count: parray->m_buffer_length;
		}

		if (null != last_item)
		{
			status = resize_dynamic_linear_array(parray,new_size,bnew_buffer);
			if (PFX_STATUS_OK != status)
			{
				last_item = null;
			}
			if (pfx_true == bnew_buffer)
			{
				last_item = null;
			}
		}
		SET_POINTER_VALUE (pstatus,status);


		return last_item;
	}
}

PFX_C_EXTERN_END




#endif			//PFX_ARRAY_ALGORITHM_H_
