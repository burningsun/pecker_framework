/*
 * pfx_string.cpp
 *
 *  Created on: 2013-8-29
 *      Author: 李镇城 (cut / cutxyz)
 */

#include "pfx_string.h"

//PFX_C_EXTERN_BEGIN
pfx_string_t* init_string_by_buffer(size_t char_size,size_t min_buffer_size,char* PARAM_INOUT string_obj_buffer,pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_string_t* preturn_string = (pfx_string_t*)(string_obj_buffer);
	size_t min_charbuffer_size = min_buffer_size - sizeof(pfx_string_t);

	if (min_charbuffer_size < 0||char_size > 0x3FFF||null == string_obj_buffer)
	{
		if (pstatus)
		{
			*pstatus = PFX_STATUS_INVALID_PARAMS;
		}
		return null;
	}
	preturn_string->m_revered = 0;
	preturn_string->m_using_extern_buffer = 0;
	preturn_string->m_char_size = char_size;
	preturn_string->m_defualt_buffer_size = ((min_charbuffer_size > 0x3FFF) ? 0x3FFF:min_charbuffer_size); 
	preturn_string->m_string_buffer_size =  ((min_charbuffer_size > 0x3FFF) ? 0x3FFF:min_charbuffer_size);
	preturn_string->m_string_buffer_length = 0;
	if (preturn_string->m_defualt_buffer_size > 0)
	{
		preturn_string->m_pthis_string_data = (string_obj_buffer + sizeof(pfx_string_t));
	}
	else
	{
		preturn_string->m_pthis_string_data = null;
	}
	

	if (pstatus)
	{
		*pstatus = PFX_STATUS_OK;
	}

	return preturn_string;
}

pfx_string_t* new_string(size_t char_size,size_t min_char_count,const IAllocator* PARAM_IN pAllocator,pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_string_t* preturn_string = null;
	pfx_result_t status = PFX_STATUS_OK;
	size_t allocate_size = char_size * min_char_count;
	char* allocate_buffer = null;

	if (null == pAllocator || allocate_size > 0xFFFF)
	{
		if (pstatus)
		{
			*pstatus = PFX_STATUS_INVALID_PARAMS;
		}
		return preturn_string;
	}

	allocate_size += sizeof(pfx_string_t);
	allocate_buffer = (char*)(pAllocator->allocate_obj((pfx_long_t)pAllocator,allocate_size));

	preturn_string = init_string_by_buffer(char_size,allocate_size,allocate_buffer,&status);

	if (null != pstatus)
	{
		if (null == allocate_buffer)
		{
			*pstatus = PFX_STATUS_MEM_LOW;
		}
		else if (PFX_STATUS_OK != status)
		{
			*pstatus = status;
		}
		else
		{
			*pstatus = PFX_STATUS_OK;
		}
	}
	return preturn_string;
}

pfx_result_t relese_string_extern_buffer(pfx_string_t* PARAM_INOUT pstr,const IAllocator* PARAM_IN pAllocator)
{
	pfx_result_t status = PFX_STATUS_OK;

	if (null == pstr || null == pAllocator)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	if (pstr->m_using_extern_buffer)
	{
		if (null != pstr->m_pthis_string_data)
		{
			pAllocator->dellocate_obj((pfx_long_t)pAllocator,pstr->m_pthis_string_data);
			
			pstr->m_using_extern_buffer = 0;
			pstr->m_string_buffer_size = pstr->m_defualt_buffer_size;

			if (pstr->m_defualt_buffer_size > 0)
			{
				pstr->m_pthis_string_data = (char*)pstr + sizeof(pfx_string_t); 
			}
			else
			{
				pstr->m_pthis_string_data = null;
			}
			pstr->m_string_buffer_length = 0;
		}
		else
		{
			status = PFX_STATUS_INVALID_PARAMS;
		}
	}
	else
	{
		pstr->m_string_buffer_length = 0;
	}

	return status;
}

pfx_result_t init_string(pfx_string_t* PARAM_INOUT pstr,
	size_t string_len,
	const IAllocator* PARAM_IN pchar_allocator)
{
	if (null == pstr || string_len < 0)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	

	if ((string_len < pstr->m_defualt_buffer_size) && (0 == pstr->m_using_extern_buffer))
	{
		//....
		pstr->m_string_buffer_length = 0;
	}
	else if (string_len > pstr->m_string_buffer_size)
	{
		char* allocate_buffer;

		 if (null == pchar_allocator)
		 {
			 return PFX_STATUS_INVALID_PARAMS;
		 }
		// 先申请一块内存
		allocate_buffer = (char*)(pchar_allocator->allocate_obj((pfx_long_t)pchar_allocator,string_len));
		
		if (null != allocate_buffer)
		{
			pstr->m_string_buffer_length = 0;
			// 申请成功后，释放原来的内存，将新内存附加上去
			if (null != pstr->m_pthis_string_data)
			{
				pchar_allocator->dellocate_obj((pfx_long_t)pchar_allocator,pstr->m_pthis_string_data);
			}
			pstr->m_using_extern_buffer = 1;
			pstr->m_pthis_string_data = allocate_buffer;
			pstr->m_string_buffer_size = string_len;
		}
		else
		{
			// 申请内存失败报告缺内存
			return PFX_STATUS_MEM_LOW;
		}
	}
	else 
	{
		pstr->m_string_buffer_length = 0;
	}

	return PFX_STATUS_OK;
}


pfx_result_t init_string_by_charsbuffer(pfx_string_t* PARAM_INOUT pstr,
	const char* PARAM_IN pstr_chars,size_t chars_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = init_string(pstr,chars_buffer_size,pchar_allocator);
	if (PFX_STATUS_OK == status)
	{
		size_t i;
		for (i=0;i<chars_buffer_size;++i)
		{
			pstr->m_pthis_string_data[i] = pstr_chars[i];
		}
		pstr->m_string_buffer_length = chars_buffer_size;
	}
	return status;
}


pfx_result_t copy_string(pfx_string_t* PARAM_INOUT pstr_dec,
	const pfx_string_t* PARAM_IN pstr_src,const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status;
	if (null == pstr_src)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	status =  init_string(pstr_dec,pstr_src->m_string_buffer_size,pchar_allocator);
	if (PFX_STATUS_OK == status)
	{
		size_t copy_size = pstr_src->m_string_buffer_size;
		size_t i;
		for (i=0; i<copy_size; ++i)
		{
			pstr_dec->m_pthis_string_data[i] = pstr_src->m_pthis_string_data[i];
		}
		pstr_dec->m_string_buffer_length = pstr_src->m_string_buffer_length;
	}

	return status;
}


pfx_result_t swap_string(pfx_string_t* PARAM_INOUT pstrA,pfx_string_t* PARAM_INOUT pstrB)
{
	if (null == pstrA || null == pstrB)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	if (pstrB->m_using_extern_buffer && pstrA->m_using_extern_buffer)
	{
		pfx_string_t strC;
		memcpy(&strC,pstrA,sizeof(pfx_string_t));
		memcpy(pstrA,pstrB,sizeof(pfx_string_t));
		memcpy(pstrB,&strC,sizeof(pfx_string_t));
		return PFX_STATUS_OK;
	}
	else if (!(pstrB->m_using_extern_buffer) && !(pstrA->m_using_extern_buffer))
	{
		size_t length; 
		unsigned int temp;
		size_t max_size;
		size_t i;

		if ((pstrA->m_defualt_buffer_size < pstrB->m_string_buffer_length)||
			(pstrB->m_defualt_buffer_size < pstrA->m_string_buffer_length))
		{
			return PFX_STATUS_FAIL;
		}

		max_size = pstrA->m_string_buffer_length;
		if (max_size < pstrB->m_string_buffer_length)
		{
			max_size = pstrB->m_string_buffer_length;
		}
		
		for (i=0;i<max_size;++i)
		{
			char temp_char;
			temp_char = pstrA->m_pthis_string_data[i];
			pstrA->m_pthis_string_data[i] = pstrB->m_pthis_string_data[i];
			pstrB->m_pthis_string_data[i] = temp_char;
		}

		length = pstrA->m_string_buffer_length;
		pstrA->m_string_buffer_length = pstrB->m_string_buffer_length;
		pstrB->m_string_buffer_length = length;


		temp = pstrA->m_revered;
		pstrA->m_revered = pstrB->m_revered;
		pstrB->m_revered = temp;

		temp = pstrA->m_char_size;
		pstrA->m_char_size = pstrB->m_char_size;
		pstrB->m_char_size = temp;

		return PFX_STATUS_OK;
	}
	else if (pstrA->m_using_extern_buffer)
	{
		char* pA_buf; 
		char* pB_buf;
		size_t length; 
		unsigned int temp;

		if (pstrA->m_defualt_buffer_size < pstrB->m_string_buffer_length)
		{
			return PFX_STATUS_FAIL;
		}

		pA_buf = pstrA->m_pthis_string_data;
		pB_buf = pstrB->m_pthis_string_data;

		pstrB->m_pthis_string_data = pA_buf;
		if (pstrA->m_defualt_buffer_size > 0)
		{
			pstrA->m_pthis_string_data = (char*)pstrA + sizeof(pfx_string_t);
		}
		else
		{
			pstrA->m_pthis_string_data = null;
		}

		memcpy(pstrA,pB_buf,pstrB->m_string_buffer_length);

		if (pstrA->m_string_buffer_size > pstrB->m_string_buffer_size)
		{
			pstrB->m_string_buffer_size = pstrA->m_string_buffer_size;
		}


		length = pstrA->m_string_buffer_length;
		pstrA->m_string_buffer_length = pstrB->m_string_buffer_length;
		pstrB->m_string_buffer_length = length;

		pstrA->m_string_buffer_size = pstrA->m_defualt_buffer_size;
		
		temp = pstrA->m_revered;
		pstrA->m_revered = pstrB->m_revered;
		pstrB->m_revered = temp;

		pstrA->m_using_extern_buffer = 0;
		pstrB->m_using_extern_buffer = 1;

		temp = pstrA->m_char_size;
		pstrA->m_char_size = pstrB->m_char_size;
		pstrB->m_char_size = temp;
		
		return PFX_STATUS_OK;
	}
	else  if (pstrB->m_using_extern_buffer)
	{
		char* pB_buf; 
		char* pA_buf;
		size_t length; 
		unsigned int temp;

		if (pstrB->m_defualt_buffer_size < pstrA->m_string_buffer_length)
		{
			return PFX_STATUS_FAIL;
		}

		pB_buf = pstrB->m_pthis_string_data;
		pA_buf = pstrA->m_pthis_string_data;

		pstrA->m_pthis_string_data = pB_buf;
		if (pstrB->m_defualt_buffer_size > 0)
		{
			pstrB->m_pthis_string_data = (char*)pstrB + sizeof(pfx_string_t);
		}
		else
		{
			pstrB->m_pthis_string_data = null;
		}

		memcpy(pstrB,pA_buf,pstrA->m_string_buffer_length);

		if (pstrB->m_string_buffer_size > pstrA->m_string_buffer_size)
		{
			pstrA->m_string_buffer_size = pstrB->m_string_buffer_size;
		}


		length = pstrB->m_string_buffer_length;
		pstrB->m_string_buffer_length = pstrA->m_string_buffer_length;
		pstrA->m_string_buffer_length = length;

		pstrB->m_string_buffer_size = pstrB->m_defualt_buffer_size;

		temp = pstrB->m_revered;
		pstrB->m_revered = pstrA->m_revered;
		pstrA->m_revered = temp;

		pstrB->m_using_extern_buffer = 0;
		pstrA->m_using_extern_buffer = 1;

		temp = pstrB->m_char_size;
		pstrB->m_char_size = pstrA->m_char_size;
		pstrA->m_char_size = temp;

		return PFX_STATUS_OK;
	}

	return PFX_STATUS_FAIL;
}

pfx_result_t swap_string_by_allocator(pfx_string_t* PARAM_INOUT pstrA,pfx_string_t* PARAM_INOUT pstrB,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = swap_string(pstrA,pstrB);
	if (PFX_STATUS_FAIL == status)
	{
		size_t			max_buffer_size;
		pfx_string_t* pstrC;
		
		pstrC = null;
		max_buffer_size = (pstrA->m_string_buffer_length > pstrB->m_string_buffer_length)?pstrA->m_string_buffer_length:pstrB->m_string_buffer_length;
		
		pstrC = new_string(pstrA->m_char_size,(max_buffer_size/pstrA->m_char_size),pchar_allocator,&status);

		if (PFX_STATUS_OK == status)
		{
			status = init_string_by_charsbuffer(pstrC,pstrB->m_pthis_string_data,pstrB->m_string_buffer_length,pchar_allocator);
		}

		if (PFX_STATUS_OK == status)
		{
			status = init_string_by_charsbuffer(pstrB,pstrA->m_pthis_string_data,pstrA->m_string_buffer_length,pchar_allocator);
		}

		if (PFX_STATUS_OK == status)
		{	
			status = init_string_by_charsbuffer(pstrA,pstrC->m_pthis_string_data,pstrC->m_string_buffer_length,pchar_allocator);
		}

		if (PFX_STATUS_OK == status)
		{
			pstrC->m_char_size = pstrB->m_char_size;
			pstrB->m_char_size = pstrA->m_char_size;
			pstrA->m_char_size = pstrC->m_char_size;
		}

		if (null != pstrC)
		{
			delete_string(pstrC,pchar_allocator);
		}
		


	}
	return status;
}

pfx_result_t resize_string(pfx_string_t* PARAM_INOUT pstr,size_t string_len,pfx_bool_t bnew_allocate, const IAllocator* PARAM_IN pchar_allocator)
{
	if (null == pstr || string_len < 0)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}



	if ((string_len < pstr->m_defualt_buffer_size) && (0 == pstr->m_using_extern_buffer))
	{
		// 小于自带内存的时候只要改下字符长度就行
		pstr->m_string_buffer_length = string_len;
	}
	else if (string_len > pstr->m_string_buffer_size)
	{
		char* allocate_buffer;
		if (null == pchar_allocator)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		// 先申请一块内存
		allocate_buffer = (char*)(pchar_allocator->allocate_obj((pfx_long_t)pchar_allocator,string_len));

		if (null != allocate_buffer)
		{
			// 将原来的内存拷贝一份上去
			size_t copy_size = pstr->m_string_buffer_length;
			if (copy_size > string_len)
			{
				copy_size = string_len;
			}
			
			memcpy(allocate_buffer,pstr->m_pthis_string_data,copy_size);

			// 申请成功后，释放原来的内存，将新内存附加上去
			if (null != pstr->m_pthis_string_data)
			{
				pchar_allocator->dellocate_obj((pfx_long_t)pchar_allocator,pstr->m_pthis_string_data);
			}
			pstr->m_using_extern_buffer = 1;
			pstr->m_pthis_string_data = allocate_buffer;
			pstr->m_string_buffer_size = string_len;
		}
		else
		{
			// 申请内存失败报告缺内存
			return PFX_STATUS_MEM_LOW;
		}
	}
	else if (bnew_allocate)
	{
		if (string_len < pstr->m_defualt_buffer_size)
		{
			char* pstr_dec;
			pstr->m_string_buffer_length = string_len;
			pstr_dec = (char*)pstr + sizeof(pfx_string_t);
			memcpy(pstr_dec,pstr->m_pthis_string_data,string_len);
			pstr->m_using_extern_buffer = 0;
		}
		else 
		{
			char* allocate_buffer;
			if (null == pchar_allocator)
			{
				return PFX_STATUS_INVALID_PARAMS;
			}
			// 先申请一块内存
			allocate_buffer = (char*)(pchar_allocator->allocate_obj((pfx_long_t)pchar_allocator,string_len));

			if (null != allocate_buffer)
			{
				// 将原来的内存拷贝一份上去
				size_t copy_size = pstr->m_string_buffer_length;
				if (copy_size > string_len)
				{
					copy_size = string_len;
				}

				memcpy(allocate_buffer,pstr->m_pthis_string_data,copy_size);

				// 申请成功后，释放原来的内存，将新内存附加上去
				if (null != pstr->m_pthis_string_data)
				{
					pchar_allocator->dellocate_obj((pfx_long_t)pchar_allocator,pstr->m_pthis_string_data);
				}
				pstr->m_using_extern_buffer = 1;
				pstr->m_pthis_string_data = allocate_buffer;
				pstr->m_string_buffer_length = string_len;
			}
			else
			{
				// 申请内存失败报告缺内存
				return PFX_STATUS_MEM_LOW;
			}
		}
	}
	else
	{
		pstr->m_string_buffer_length = string_len;
	}

	return PFX_STATUS_OK;
}

pfx_result_t get_sub_string(const pfx_string_t* PARAM_IN porign_string, 
	pfx_string_t* PARAM_INOUT preference_sub_string,size_t ioffset,
	size_t sub_string_length,const IAllocator* PARAM_IN pchar_allocator)
{
	if (null == porign_string || null == preference_sub_string)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	if (ioffset < 0)
	{
		ioffset = 0;
	}

	if (sub_string_length > (porign_string->m_string_buffer_length - ioffset))
	{
		sub_string_length = (porign_string->m_string_buffer_length - ioffset);
	}

	if (sub_string_length < 0)
	{
		sub_string_length = 0;
	}

	return init_string_by_charsbuffer(preference_sub_string,porign_string->m_pthis_string_data+ioffset,sub_string_length,pchar_allocator);

}

pfx_result_t append_string_by_chars(pfx_string_t* PARAM_INOUT pstr,
	const char* PARAM_IN str_chars, size_t chars_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t	status;
	size_t			offset;
	if (null == pstr)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	if (null == str_chars || chars_buffer_size <= 0)
	{
		return PFX_STATUS_OK;
	}

	offset = pstr->m_string_buffer_length;
	status = resize_string(pstr,pstr->m_string_buffer_length+chars_buffer_size,pfx_false,pchar_allocator);
	if (PFX_STATUS_OK == status)
	{
		memcpy(pstr->m_pthis_string_data+offset,str_chars,chars_buffer_size);
	}
	
	return status;

}

PFX_INLINE_CODE pfx_share_buffer_string_t* linked_list_node_cov_to_share_buffer_string_t(linked_list_node_t* pnode)
{
	return (pfx_share_buffer_string_t*)pnode;
}
PFX_INLINE_CODE pfx_share_buffer_string_t* string_t_to_share_buffer_string_t(pfx_string_t* pstr)
{
	if (pstr)
	{
		return (pfx_share_buffer_string_t*)((pfx_long_t)pstr - sizeof(pfx_share_buffer_string_t));
	}
	else
	{
		return null;
	}
}



pfx_result_t get_share_buffer_sub_string(const pfx_share_buffer_string_t* PARAM_INOUT porign_string,
	pfx_share_buffer_string_t* PARAM_INOUT preference_sub_string,
	size_t ioffset,size_t sub_string_length,const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	

	if (null == porign_string || null == preference_sub_string || 
		null == porign_string->m_reference_string || null == preference_sub_string->m_reference_string)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	if (ioffset >= porign_string->m_this_string_length || 0 == sub_string_length)
	{
		preference_sub_string->m_offset = 0;
		preference_sub_string->m_this_string_length = 0;
		return PFX_STATUS_OK;
	}

	if (check_is_linked_list_only_one_node(&(porign_string->m_list_node)))
	{
		pfx_string_t* pnew_string = new_string(porign_string->m_reference_string->m_char_size,
																			  porign_string->m_reference_string->m_defualt_buffer_size/porign_string->m_reference_string->m_char_size,
																			  pchar_allocator,&status);
		if (PFX_STATUS_OK == status && null != pnew_string)
		{
			status = swap_string(pnew_string,porign_string->m_reference_string);
			if (PFX_STATUS_OK == status)
			{
				pfx_share_buffer_string_t* porign_string_modify = (pfx_share_buffer_string_t*)porign_string;
				porign_string_modify->m_reference_string = pnew_string;
				porign_string_modify->m_is_referenced = 1;
				porign_string_modify->m_using_own_buffer = 0;
			}
		}
	}

	if (PFX_STATUS_OK == status && !check_is_linked_list_only_one_node(&preference_sub_string->m_list_node))
	{
		linked_list_node_t* pnode = remove_linked_list_node(&preference_sub_string->m_list_node);
		pnode = init_linked_list_node(pnode);
		if (null == pnode)
		{
			status = PFX_STATUS_MEM_ERR;
		}
	}

	if (PFX_STATUS_OK == status)
	{
		size_t sub_string_length_;
		sub_string_length_ = porign_string->m_this_string_length - ioffset;
		if (sub_string_length_ > sub_string_length)
		{
			sub_string_length_ = sub_string_length;
		}
		preference_sub_string->m_reference_string = porign_string->m_reference_string;
		preference_sub_string->m_offset = ioffset;
		preference_sub_string->m_this_string_length = sub_string_length_;
	}

	return status;
}

pfx_result_t delete_share_string(pfx_share_buffer_string_t* PARAM_INOUT pstr,
	const IAllocator* PARAM_IN pAllocator)
{
	pfx_result_t status = PFX_STATUS_OK;

	if (null == pAllocator)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	if (null == pstr)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	if (check_is_linked_list_only_one_node(&pstr->m_list_node))
	{
		if (pstr->m_using_reference_buffer)
		{
			status = delete_string(pstr->m_reference_string,pAllocator);
		}

		if (PFX_STATUS_OK == status)
		{
			pAllocator->dellocate_obj((pfx_long_t)pAllocator,pstr);
		}
		return status;
	}
	else
	{
		linked_list_node_t* premoved_node = remove_linked_list_node(&pstr->m_list_node);
		if (null != premoved_node)
		{
			premoved_node->m_prev_node = null;
			premoved_node->m_pnext_node = null;
			pstr->m_is_removed = 1;
			pAllocator->dellocate_obj((pfx_long_t)pAllocator,pstr);
			status = PFX_STATUS_OK;
		}
		else
		{
			status = PFX_STATUS_MEM_ERR;
		}
	}

	return status;
}


pfx_result_t append_share_string_by_chars(pfx_share_buffer_string_t* PARAM_INOUT pstr,const char* PARAM_IN str_chars, size_t chars_buffer_size,const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t	status;
	size_t			offset;
	if (null == pstr)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	if (null == str_chars || chars_buffer_size <= 0)
	{
		return PFX_STATUS_OK;
	}

	offset = pstr->m_this_string_length;
	status = resize_share_string(pstr,pstr->m_this_string_length+chars_buffer_size,pfx_false,pchar_allocator);
	if (PFX_STATUS_OK == status)
	{
		memcpy(pstr->m_reference_string->m_pthis_string_data+offset,str_chars,chars_buffer_size);
	}
	return status;
}

pfx_result_t set_share_string_buffer_chars_at(pfx_share_buffer_string_t* PARAM_INOUT pstr,size_t index,const char* PARAM_INOUT set_chars,size_t set_buffer_size,const IAllocator* PARAM_IN pchar_allocator)
{
		pfx_result_t	status;
		if (null == pstr)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		status = resize_share_string(pstr,pstr->m_this_string_length,pfx_false,pchar_allocator);
		if (PFX_STATUS_OK == status)
		{
			status = set_string_buffer_chars_at(pstr->m_reference_string,index,set_chars,set_buffer_size);
		}

		return status;
}

//PFX_C_EXTERN_END
