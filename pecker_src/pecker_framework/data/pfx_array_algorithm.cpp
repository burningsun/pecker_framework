/*
 * pfx_array_algorithm.cpp
 *
 *  Created on: 2013-9-12
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_array_algorithm.h"

//PFX_C_EXTERN_BEGIN



pfx_base_array_t* init_base_array_by_buffer(size_t item_size,
																				size_t allocate_step,
																				char* PARAM_INOUT pbuffer,
																				size_t buffer_size,
																				const IAllocator* PARAM_IN pitem_allocator,
																				pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_base_array_t* preturn_array = null;
	//if (null == pbuffer || buffer_size < sizeof(pfx_base_array_t) || null == pitem_allocator
	//	|| 0 >= allocate_step || 0 >= item_size )
	//{
	//	if (null != pstatus)
	//	{
	//		*pstatus = PFX_STATUS_INVALID_PARAMS;
	//	}
	//	return null;
	//}
	RETURN_INVALID_BY_ACT_RESULT ((null == pbuffer || buffer_size < sizeof(pfx_base_array_t) || null == pitem_allocator
		|| 0 >= allocate_step || 0 >= item_size) ,SET_POINTER_VALUE(pstatus,PFX_STATUS_INVALID_PARAMS),null);

	preturn_array = (pfx_base_array_t*)pbuffer;
	preturn_array->m_buffer_length = 0;
	preturn_array->m_item_size = item_size;
	preturn_array->m_auto_allocate_step = allocate_step;
	preturn_array->m_defualt_array_size = (buffer_size - sizeof(pfx_base_array_t))/item_size;
	preturn_array->m_using_extern_buffer = 0;
	preturn_array->m_buffer_size = preturn_array->m_defualt_array_size;
	preturn_array->m_pitem_allocator = pitem_allocator;
	preturn_array->m_parray_data = (preturn_array->m_defualt_array_size > 0) ? ((void*)((pfx_long_t)pbuffer + sizeof(pfx_base_array_t))) : null; 
	
	//if (null != pstatus)
	//{
	//	*pstatus = PFX_STATUS_OK;
	//}
	SET_POINTER_VALUE(pstatus,PFX_STATUS_OK);

	return preturn_array;
}
pfx_base_array_t* new_base_array(const IAllocator* PARAM_IN parray_allocator,
										size_t item_size,
										size_t default_item_count,
										size_t allocate_step,
										const IAllocator* PARAM_IN parray_item_allocator,
										pfx_result_t* PARAM_INOUT pstatus)
{
	size_t allocate_size = 0;
	char* allocate_buffer = null;
	pfx_base_array_t* preturn_array = null;

	//if (null == parray_allocator || 
	//	null == parray_item_allocator ||
	//	0 >= allocate_step || 0 >= item_size)
	//{
	//	if (null != pstatus)
	//	{
	//		*pstatus = PFX_STATUS_INVALID_PARAMS;
	//	}
	//	return null;
	//}
	RETURN_INVALID_BY_ACT_RESULT ((null == parray_allocator || 
		null == parray_item_allocator ||
		0 >= allocate_step || 0 >= item_size),SET_POINTER_VALUE(pstatus,PFX_STATUS_INVALID_PARAMS),null);

	allocate_size = sizeof(pfx_base_array_t) + item_size*default_item_count;
	allocate_buffer = (char*)parray_allocator->allocate_obj((pfx_long_t)parray_allocator,allocate_size);
	//if (null == allocate_buffer)
	//{
	//	if (null != pstatus)
	//	{
	//		*pstatus = PFX_STATUS_MEM_LOW;
	//	}
	//	return null;
	//}
	RETURN_INVALID_BY_ACT_RESULT ((null == allocate_buffer),SET_POINTER_VALUE(pstatus,PFX_STATUS_MEM_LOW),null);

	preturn_array = init_base_array_by_buffer(item_size,allocate_step,allocate_buffer,allocate_size,parray_item_allocator,pstatus);
	if (null == preturn_array)
	{
		parray_allocator->dellocate_obj((pfx_long_t)parray_allocator,allocate_buffer);
	}
	return preturn_array;
}

pfx_result_t delete_base_array(pfx_base_array_t* pdel_array, const IAllocator* PARAM_IN parray_allocator)
{
	//if (null == pdel_array || null == parray_allocator)
	//{
	//	return PFX_STATUS_INVALID_PARAMS;
	//}
	RETURN_INVALID_RESULT ((null == pdel_array || null == parray_allocator),PFX_STATUS_INVALID_PARAMS);

	if (pdel_array->m_using_extern_buffer)
	{
		//if (null == pdel_array->m_pitem_allocator)
		//{
		//	return PFX_STATUS_MEM_ERR;
		//}
		RETURN_INVALID_RESULT ((null == pdel_array->m_pitem_allocator),PFX_STATUS_MEM_ERR);

		if (null != pdel_array->m_parray_data)
		{
			pdel_array->m_pitem_allocator->dellocate_obj((pfx_long_t)(pdel_array->m_pitem_allocator),pdel_array->m_parray_data);
		}
	}

	parray_allocator->dellocate_obj((pfx_long_t)parray_allocator,pdel_array);

	return PFX_STATUS_OK;
}

PFX_INLINE_CODE size_t get_resize_array_buffer_size(pfx_base_array_t* PARAM_INOUT parray,size_t item_count)
{
	size_t new_buffer_size;
	new_buffer_size = item_count / parray->m_auto_allocate_step;
	if (0 == new_buffer_size)
	{
		new_buffer_size = parray->m_auto_allocate_step;
	}
	else if (item_count % parray->m_auto_allocate_step == 0)
	{
		new_buffer_size = item_count;
	}
	else
	{
		new_buffer_size =  parray->m_auto_allocate_step * (new_buffer_size + 1);
	}
	return new_buffer_size;
}

PFX_INLINE_CODE pfx_result_t resize_null_array_buffer(pfx_base_array_t* PARAM_INOUT parray,size_t item_count)
{
	size_t new_buffer_size;
	//if (0 == item_count)
	//{
	//	return PFX_STATUS_OK;
	//}
	RETURN_RESULT ((0 == item_count),PFX_STATUS_OK);

	//if (null == parray->m_pitem_allocator)
	//{
	//	return PFX_STATUS_MEM_ERR;
	//}
	RETURN_INVALID_RESULT ((null == parray->m_pitem_allocator),PFX_STATUS_MEM_ERR);

	new_buffer_size = get_resize_array_buffer_size(parray,item_count);
	parray->m_parray_data = parray->m_pitem_allocator->allocate_obj((pfx_long_t)(parray->m_pitem_allocator),parray->m_item_size * new_buffer_size);
	if (null != parray->m_parray_data)
	{
		parray->m_using_extern_buffer = 1;
		parray->m_buffer_length = item_count;
		parray->m_buffer_size = new_buffer_size;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_MEM_LOW;
	}
}

PFX_INLINE_CODE pfx_result_t resize_internal_array_buffer(pfx_base_array_t* PARAM_INOUT parray,size_t item_count)
{
	size_t new_buffer_size;
	char* new_array_items = null;
	if (item_count <= parray->m_defualt_array_size)
	{
		parray->m_buffer_length = item_count;
		parray->m_buffer_size = parray->m_defualt_array_size;
		parray->m_using_extern_buffer = 0;
		return PFX_STATUS_OK;
	}

	//if (0 == item_count)
	//{
	//	return PFX_STATUS_OK;
	//}
	RETURN_RESULT ((0 == item_count),PFX_STATUS_OK);

	//if (null == parray->m_pitem_allocator || 
	//	(null == parray->m_parray_data && 0 != parray->m_defualt_array_size) )
	//{
	//	return PFX_STATUS_MEM_ERR;
	//}
	RETURN_INVALID_RESULT (null == parray->m_pitem_allocator || 
		(null == parray->m_parray_data && 0 != parray->m_defualt_array_size),PFX_STATUS_MEM_ERR);

	new_buffer_size = get_resize_array_buffer_size(parray,item_count);
	new_array_items = (char*)parray->m_pitem_allocator->allocate_obj((pfx_long_t)(parray->m_pitem_allocator),parray->m_item_size * new_buffer_size);
	if (null != new_array_items)
	{
		size_t min_copy_size = ((parray->m_buffer_length > item_count)?item_count:parray->m_buffer_length)*parray->m_item_size;
		memcpy(new_array_items,parray->m_parray_data,min_copy_size);
		parray->m_using_extern_buffer = 1;
		parray->m_buffer_length = item_count;
		parray->m_buffer_size = new_buffer_size;
		parray->m_parray_data = new_array_items;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_MEM_LOW;
	}
}

PFX_INLINE_CODE pfx_result_t resize_external_array_buffer(pfx_base_array_t* PARAM_INOUT parray,size_t item_count,pfx_bool_t bnew_buffer)
{
	size_t new_buffer_size;
	char* new_array_items = null;

	//if (null == parray->m_pitem_allocator || null == parray->m_parray_data)
	//{
	//	return PFX_STATUS_MEM_ERR;
	//}
	RETURN_INVALID_RESULT ((null == parray->m_pitem_allocator || null == parray->m_parray_data),
		PFX_STATUS_MEM_ERR);

	if (item_count <= parray->m_defualt_array_size)
	{
		parray->m_buffer_length = item_count;
		if (bnew_buffer)
		{
			memcpy( ((void*)((pfx_long_t)parray + sizeof(pfx_base_array_t))),parray->m_parray_data,item_count*parray->m_item_size);

			parray->m_pitem_allocator->dellocate_obj((pfx_long_t)parray->m_pitem_allocator,parray->m_parray_data);
			parray->m_parray_data = (parray->m_defualt_array_size > 0) ? ((void*)((pfx_long_t)parray + sizeof(pfx_base_array_t))):(null);
			parray->m_buffer_size = parray->m_defualt_array_size;
			parray->m_using_extern_buffer = 0;

			return PFX_STATUS_OK;
				
		}
	    else
		{
			return PFX_STATUS_OK;
		}
		
	}

	if (item_count <= parray->m_buffer_size)
	{
		parray->m_buffer_length = item_count;
		//if (!bnew_buffer)
		//{
		//	return PFX_STATUS_OK;
		//}
		RETURN_RESULT ((!bnew_buffer),PFX_STATUS_OK);
	}

	new_buffer_size = get_resize_array_buffer_size(parray,item_count);
	new_array_items = (char*)parray->m_pitem_allocator->allocate_obj((pfx_long_t)(parray->m_pitem_allocator),parray->m_item_size * new_buffer_size);
	if (null != new_array_items)
	{
		size_t min_copy_size = ((parray->m_buffer_length > item_count)?item_count:parray->m_buffer_length)*parray->m_item_size;
		memcpy(new_array_items,parray->m_parray_data,min_copy_size);
		parray->m_using_extern_buffer = 1;
		parray->m_buffer_length = item_count;
		parray->m_buffer_size = new_buffer_size;
		parray->m_pitem_allocator->dellocate_obj((pfx_long_t)(parray->m_pitem_allocator),parray->m_parray_data);
		parray->m_parray_data = new_array_items;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_MEM_LOW;
	}
}

pfx_result_t resize_base_array(pfx_base_array_t* PARAM_INOUT parray,size_t item_count,pfx_bool_t bnew_buffer,size_t new_resize_step)
{
	pfx_result_t status = PFX_STATUS_OK;
	size_t		  back_up_step;
	//if (null == parray || parray->m_auto_allocate_step <= 0)
	//{
	//	return PFX_STATUS_INVALID_PARAMS;
	//}
	RETURN_INVALID_RESULT ((null == parray || parray->m_auto_allocate_step <= 0),
		PFX_STATUS_INVALID_PARAMS);

	if (0 == new_resize_step)
	{
		new_resize_step = 1;
	}
	else if (INVALID_VALUE == new_resize_step)
	{
		new_resize_step = parray->m_auto_allocate_step;
	}

	back_up_step = parray->m_auto_allocate_step;
	parray->m_auto_allocate_step = new_resize_step;

	if (parray->m_using_extern_buffer)
	{
		status = resize_external_array_buffer(parray,item_count,bnew_buffer);
	}
	else
	{
		status = resize_internal_array_buffer(parray,item_count);
	}

	if (PFX_STATUS_OK != status)
	{
		parray->m_auto_allocate_step = back_up_step;
	}

	return status;
}

pfx_arraybuffer_block_t* init_arraybuffer_block_by_buffer(	char* PARAM_INOUT pbuffer,
	size_t buffer_size, ALIGNED_TYPE_t aligned_type,pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_arraybuffer_block_t* preturn_block = null;
	unsigned long bitmask = (1 << aligned_type) - 1;
	pfx_index_t aligned_offset = 0;
	//if (buffer_size < sizeof(pfx_arraybuffer_block_t))
	//{
	//	if (pstatus)
	//	{
	//		*pstatus = PFX_STATUS_MEM_ERR;
	//	}
	//	return null;
	//}
	RETURN_INVALID_BY_ACT_RESULT ((buffer_size < sizeof(pfx_arraybuffer_block_t)),
		SET_POINTER_VALUE(pstatus,PFX_STATUS_MEM_ERR),null);

	preturn_block = (pfx_arraybuffer_block_t*)pbuffer;
	preturn_block->m_pblock_data = (char*)(((pfx_ulong_t)&preturn_block->m_char_begins + bitmask) & (~bitmask)) ;
	aligned_offset = preturn_block->m_pblock_data - &(preturn_block->m_char_begins);

	//if (buffer_size < (sizeof(pfx_arraybuffer_block_t) + aligned_offset))
	//{
	//	if (pstatus)
	//	{
	//		*pstatus = PFX_STATUS_MEM_ERR;
	//	}
	//	return null;
	//}
	RETURN_INVALID_BY_ACT_RESULT ((buffer_size < (sizeof(pfx_arraybuffer_block_t) + aligned_offset)),
		SET_POINTER_VALUE(pstatus,PFX_STATUS_MEM_ERR),null);

	preturn_block->m_pblock_size = buffer_size - (sizeof(pfx_arraybuffer_block_t)-1 + aligned_offset);
	//if (pstatus)
	//{
	//	*pstatus = PFX_STATUS_OK;
	//}
	SET_POINTER_VALUE (pstatus,PFX_STATUS_OK);

	return preturn_block;
}

pfx_arraybuffer_block_t* new_arraybuffer_block(size_t buffer_size,ALIGNED_TYPE_t aligned_type,
	const IAllocator* PARAM_IN parray_item_allocator,
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_arraybuffer_block_t* preturn_block;
	size_t allocate_size; 
	char* pbuffer; 

	if (0 == buffer_size)
	{
		buffer_size = 1;
	}

	allocate_size = sizeof(pfx_arraybuffer_block_t) + ((1 << aligned_type) - 1) + buffer_size - 1;
	pbuffer = (char*)parray_item_allocator->allocate_obj((pfx_long_t)parray_item_allocator,allocate_size);
	if (null != pbuffer)
	{
		preturn_block = init_arraybuffer_block_by_buffer(pbuffer,allocate_size,aligned_type,pstatus);
	}
	else
	{
		//if (null != pstatus)
		//{
		//	*pstatus = PFX_STATUS_MEM_LOW;
		//}
		SET_POINTER_VALUE (pstatus,PFX_STATUS_MEM_LOW);
	}
	return preturn_block;
}

pfx_result_t delete_arraybuffer_block(pfx_arraybuffer_block_t* PARAM_INOUT parray_block,
	const IAllocator* PARAM_IN parray_item_allocator)
{
	//if (null == parray_block || null == parray_item_allocator)
	//{
	//	return PFX_STATUS_INVALID_PARAMS;
	//}
	RETURN_INVALID_RESULT ((null == parray_block || null == parray_item_allocator),
		PFX_STATUS_INVALID_PARAMS);

	parray_item_allocator->dellocate_obj((pfx_long_t)(parray_item_allocator),parray_block);
	return PFX_STATUS_OK;
}


pfx_dynamic_linear_array_t* init_dynamic_linear_array_by_buffer(size_t item_size,
	size_t allocate_step,
	size_t allocate_block_array_step,
	char* PARAM_INOUT pbuffer,
	size_t buffer_size,
	ALIGNED_TYPE_t aligned_type,
	const IAllocator* PARAM_IN pblock_allocator,
	const IAllocator* PARAM_IN pblock_array_item_allocator,
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_dynamic_linear_array_t*  preturn_array = null;
	pfx_base_array_t* pblock_array = null;
	//if (null == pbuffer || sizeof(pfx_dynamic_linear_array_t) > buffer_size ||
	//	null == pblock_allocator || null == pblock_array_item_allocator || 
	//	allocate_step <= 0 || allocate_block_array_step <= 0 || item_size <= 0 ||
	//	aligned_type >= ALIGNED_TYPE_COUNT) 
	//{
	//	if (null != pstatus)
	//	{
	//		*pstatus = PFX_STATUS_INVALID_PARAMS;
	//	}
	//	return null;
	//}
	RETURN_INVALID_BY_ACT_RESULT ((null == pbuffer || sizeof(pfx_dynamic_linear_array_t) > buffer_size ||
			null == pblock_allocator || null == pblock_array_item_allocator || 
			allocate_step <= 0 || allocate_block_array_step <= 0 || item_size <= 0 ||
			aligned_type >= ALIGNED_TYPE_COUNT),
			SET_POINTER_VALUE(pstatus,PFX_STATUS_INVALID_PARAMS),null);

	preturn_array = (pfx_dynamic_linear_array_t*)(pbuffer);

	pblock_array = init_base_array_by_buffer(sizeof(pfx_arraybuffer_block_t*),allocate_block_array_step,
		(char*)&preturn_array->m_block_array,sizeof(preturn_array->m_block_array),pblock_array_item_allocator,pstatus);

	//if (null == pblock_array)
	//{
	//	return null;
	//}
	RETURN_INVALID_RESULT ((null == pblock_array),null);


	preturn_array->m_aligned_type = aligned_type;
	preturn_array = (pfx_dynamic_linear_array_t*)pbuffer;
	preturn_array->m_item_size = item_size;
	preturn_array->m_buffer_length = 0;
	preturn_array->m_auto_allocate_step = allocate_step;
	preturn_array->m_block_allocator = pblock_allocator;
	
	//if (null != pstatus)
	//{
	//	*pstatus = PFX_STATUS_OK;
	//}
	SET_POINTER_VALUE (pstatus,PFX_STATUS_OK);

	return preturn_array;
}


// 代码文件内联函数（某些编译器不支持，这里通过PFX_INLINE_CODE宏兼容，这几个函数紧当前文件可用）

// 通过元素的数量，计算block的数量
PFX_INLINE_CODE size_t calculate_dynamic_linear_array_block_count(pfx_dynamic_linear_array_t* parray,size_t new_item_count)
{
	if (new_item_count % parray->m_auto_allocate_step == 0) 
	{
		return (new_item_count / parray->m_auto_allocate_step) ;
	}
	else
	{
		return (new_item_count / parray->m_auto_allocate_step + 1);
	}
}

// 按block数组索引释放指定范围的block
PFX_INLINE_CODE pfx_result_t release_array_block_buffer_by_index(pfx_dynamic_linear_array_t* parray,
	size_t begin_index,size_t end_index,pfx_bool_t resize_block_array_flag)
{
	size_t i;
	size_t block_count = 
		(parray->m_block_array.m_buffer_length > end_index+1)?(end_index+1):(parray->m_block_array.m_buffer_length);
	
	//if (begin_index > block_count)
	//{
	//	return PFX_STATUS_OK;
	//}
	RETURN_RESULT ((begin_index > block_count),PFX_STATUS_OK);

	for (i=begin_index;i<block_count;++i)
	{
		pfx_arraybuffer_block_t** ppblock = get_dynamic_linear_array_block_pointer(parray,i);
		if (ppblock && *ppblock)
		{
			delete_arraybuffer_block(*ppblock,parray->m_block_allocator);
			*ppblock = null;
		}
	}

	return resize_base_array(&parray->m_block_array,begin_index,resize_block_array_flag,INVALID_VALUE);
}

// 释放数组所有block
PFX_INLINE_CODE pfx_result_t release_array_block_buffer(pfx_dynamic_linear_array_t* parray)
{
	size_t block_count = parray->m_block_array.m_buffer_length;
	size_t i;
	for (i=0;i<block_count;++i)
	{
		pfx_arraybuffer_block_t** ppblock = get_dynamic_linear_array_block_pointer(parray,i);
		if (ppblock && *ppblock)
		{
			delete_arraybuffer_block(*ppblock,parray->m_block_allocator);
			*ppblock = null;
		}
	}
	return resize_base_array(&parray->m_block_array,0,pfx_true,INVALID_VALUE);
}




pfx_dynamic_linear_array_t* new_dynamic_linear_array(const IAllocator* PARAM_IN parray_allocator,
	size_t item_size,
	size_t default_item_buffer_count,
	size_t allocate_step,
	size_t allocate_block_array_step,
	ALIGNED_TYPE_t aligned_type,
	const IAllocator* PARAM_IN pblock_allocator,
	const IAllocator* PARAM_IN pblock_array_item_allocator,
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_dynamic_linear_array_t*  preturn_array = null;
	char* pbuffer = null;
	//if (null == parray_allocator || null == pblock_allocator || null == pblock_array_item_allocator || 
	//	allocate_step <= 0 || allocate_block_array_step <= 0 || item_size <= 0 || aligned_type >=ALIGNED_TYPE_COUNT) 
	//{
	//	if (null != pstatus)
	//	{
	//		*pstatus = PFX_STATUS_INVALID_PARAMS;
	//	}
	//	return null;
	//}
	RETURN_INVALID_BY_ACT_RESULT ((null == parray_allocator || null == pblock_allocator || null == pblock_array_item_allocator || 
			allocate_step <= 0 || allocate_block_array_step <= 0 || item_size <= 0 || aligned_type >=ALIGNED_TYPE_COUNT),
			SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS),null);

	pbuffer = (char*)parray_allocator->allocate_obj((pfx_long_t)parray_allocator,sizeof(pfx_dynamic_linear_array_t));
	//if (null == pbuffer)
	//{
	//	if (null != pstatus)
	//	{
	//		*pstatus = PFX_STATUS_MEM_LOW;
	//	}
	//	return null;
	//}
	RETURN_INVALID_BY_ACT_RESULT (null == pbuffer,
		SET_POINTER_VALUE(pstatus,PFX_STATUS_MEM_LOW),null);

	preturn_array = init_dynamic_linear_array_by_buffer(item_size,
		allocate_step,allocate_block_array_step,pbuffer,
		sizeof(pfx_dynamic_linear_array_t),aligned_type,pblock_allocator,pblock_array_item_allocator,pstatus);

	if (null == preturn_array)
	{
		parray_allocator->dellocate_obj((pfx_long_t)parray_allocator,pbuffer);
	}
	else
	{
		size_t i;
		// 计算获得需要的block数量
		size_t default_block_count = calculate_dynamic_linear_array_block_count(preturn_array,default_item_buffer_count);
		// 将block数组重新设置大小
		pfx_result_t status = resize_base_array(&preturn_array->m_block_array,default_block_count,pfx_false,INVALID_VALUE);
		
		// 设置数组大小成功，则清理可用数组可用元素，而不清理内存
		if (PFX_STATUS_OK == status)
		{
			status = clear_base_array(&preturn_array->m_block_array,pfx_false,INVALID_VALUE);
		}

		// 设置数组大小成功，则清理可用数组可用元素，且清理内存
		if (PFX_STATUS_OK != status)
		{
			clear_base_array(&preturn_array->m_block_array,pfx_true,INVALID_VALUE);
			parray_allocator->dellocate_obj((pfx_long_t)parray_allocator,pbuffer);

			//if (pstatus)
			//{
			//	*pstatus = status;
			//}
			SET_POINTER_VALUE (pstatus,status);

			return null;
		}

		// 申请各个block的内存，并加入block索引数组，如果存在一个申请失败的，
		// 则清理所有已经申请block的内存，并且清理索引索引数组的内存
		for (i=0; i<default_block_count; ++i)
		{
			pfx_arraybuffer_block_t* pblock;
			pfx_arraybuffer_block_t** ppblock;
			
			// 申请一个block内存
			pblock = new_arraybuffer_block(preturn_array->m_auto_allocate_step * preturn_array->m_item_size,
				(ALIGNED_TYPE_t)(preturn_array->m_aligned_type),preturn_array->m_block_allocator,&status);
			// 申请失败，释放所有block的内存和数组内存
			if (null == pblock || PFX_STATUS_OK != status)
			{
				release_array_block_buffer(preturn_array);
				break;
				
			}
			// 将block加入数组索引
			ppblock = (pfx_arraybuffer_block_t**)base_array_push_back(&preturn_array->m_block_array,&pblock,&status);
			// 加入失败，释放所有block的内存和数组内存
			if (null == ppblock || PFX_STATUS_OK != status)
			{
				release_array_block_buffer(preturn_array);
				break;
			}
		}

		if (pstatus)
		{
			*pstatus = status;
		}

		if (PFX_STATUS_OK != status)
		{
			parray_allocator->dellocate_obj((pfx_long_t)parray_allocator,pbuffer);
			preturn_array = null;
		}

	}

	return preturn_array;
}

pfx_result_t delete_dynamic_linear_array(pfx_dynamic_linear_array_t* pdel_array, 
	const IAllocator* PARAM_IN parray_allocator)
{
	//if (null == pdel_array || null == parray_allocator)
	//{
	//	return PFX_STATUS_INVALID_PARAMS;
	//}
	RETURN_INVALID_RESULT ((null == pdel_array || null == parray_allocator),
		PFX_STATUS_INVALID_PARAMS);

	release_array_block_buffer(pdel_array);
	parray_allocator->dellocate_obj((pfx_long_t)parray_allocator,pdel_array);
	
	return PFX_STATUS_OK;
}

pfx_result_t resize_dynamic_linear_array(pfx_dynamic_linear_array_t* PARAM_INOUT parray,
	size_t item_count,pfx_bool_t bnew_buffer)
{
	pfx_result_t status = PFX_STATUS_OK;
	size_t i;
	size_t old_block_count = parray->m_block_array.m_buffer_length;
	// 计算获得需要的block数量
	size_t new_block_count = calculate_dynamic_linear_array_block_count(parray,item_count);

	//if (null == parray) 
	//{
	//	return PFX_STATUS_INVALID_PARAMS;
	//}
	RETURN_INVALID_RESULT ((null == parray),PFX_STATUS_INVALID_PARAMS);

	// 新block与旧block数量相等
	if (old_block_count == new_block_count)
	{
		if (0 == old_block_count)
		{
			return PFX_STATUS_OK;
		}
		else
		{
			pfx_arraybuffer_block_t* pblock = get_dynamic_linear_array_block(parray,new_block_count-1);
			//if (null == pblock)
			//{
			//	return PFX_STATUS_MEM_ERR;
			//}
			RETURN_INVALID_RESULT (null == pblock,PFX_STATUS_MEM_ERR);

			parray->m_buffer_length = item_count;
			return PFX_STATUS_OK;
		}
	}
	else if (old_block_count > new_block_count) // 新block数量小于旧block数量
	{
		//pfx_arraybuffer_block_t* pblock;
		if (0 == old_block_count)
		{
			return PFX_STATUS_MEM_ERR;
		}
		else if (pfx_true == bnew_buffer)
		{
			status = release_array_block_buffer_by_index(parray,new_block_count,old_block_count-1,bnew_buffer);
			if (PFX_STATUS_OK == status)
			{
				parray->m_buffer_length = item_count;
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
			}
			return status;
		}
	}
	// 新block数量大于旧block数量

	// 将block数组重新设置大小
	status = resize_base_array(&parray->m_block_array,new_block_count,pfx_false,INVALID_VALUE);

	// 设置数组大小成功，则清理数组新增元素，而不清理内存
	if (PFX_STATUS_OK == status)
	{
		status = resize_base_array(&parray->m_block_array,old_block_count,pfx_false,INVALID_VALUE);
	}

	//if (PFX_STATUS_OK != status)
	//{
	//	return status;
	//}
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),status);

	// 申请各个block的内存，并加入block索引数组，如果存在一个申请失败的，
	// 则清理所有已经申请block的内存，并且清理索引索引数组的内存
	for (i=old_block_count; i<new_block_count; ++i)
	{
		pfx_arraybuffer_block_t* pblock;
		pfx_arraybuffer_block_t** ppblock;

		// 申请一个block内存
		pblock = new_arraybuffer_block(parray->m_auto_allocate_step * parray->m_item_size,
			(ALIGNED_TYPE_t)(parray->m_aligned_type),parray->m_block_allocator,&status);
		// 申请失败，释放所有block的内存和数组内存
		if (null == pblock || PFX_STATUS_OK != status)
		{
			release_array_block_buffer_by_index(parray,old_block_count,new_block_count-1,pfx_false);
			status = PFX_STATUS_FAIL;
			break;

		}
		// 将block加入数组索引
		ppblock = (pfx_arraybuffer_block_t**)base_array_push_back(&parray->m_block_array,&pblock,&status);
		// 加入失败，释放所有block的内存和数组内存
		if (null == ppblock || PFX_STATUS_OK != status)
		{
			release_array_block_buffer_by_index(parray,old_block_count,new_block_count-1,pfx_false);
			status = PFX_STATUS_FAIL;
			break;
		}
	}

	if (PFX_STATUS_OK == status)
	{
		parray->m_buffer_length = item_count;
	}
	return status;
}

//PFX_C_EXTERN_END





