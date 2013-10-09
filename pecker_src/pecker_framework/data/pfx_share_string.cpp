/*
 * pfx_share_string.cpp
 *
 *  Created on: 2013-10-7
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_share_string.h"


// 强制转换一个buffer成为字符串
pfx_share_string_t* init_share_string_by_buffer(size_t char_size,size_t min_buffer_size,
	pfx_char_t* PARAM_INOUT string_obj_buffer,
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_share_string_t* preturn_string = (pfx_share_string_t*)(string_obj_buffer);
	pfx_sint_t min_charbuffer_size = (pfx_sint_t)min_buffer_size - sizeof(pfx_share_string_extern_t);
	pfx_result_t status = PFX_STATUS_OK;

	RETURN_INVALID_BY_ACT_RESULT((min_buffer_size < sizeof(pfx_share_string_t) || char_size > 0x3FFF || null == string_obj_buffer),
		SET_POINTER_VALUE(pstatus,PFX_STATUS_INVALID_VALUE),null);

	RETURN_INVALID_BY_ACT_RESULT ( (null == init_linked_list_node(&preturn_string->m_list_node)),
		SET_POINTER_VALUE(pstatus,PFX_STATUS_MEM_ERR),null);


	preturn_string->m_char_buffer_offset = 0;
	preturn_string->m_char_size = char_size;
	if (min_charbuffer_size <= 0)
	{
		preturn_string->m_using_internal_buffer = pfx_false;
		preturn_string->m_interbuffer_defualt_buffer_size = 0;
		preturn_string->m_char_buffer_size = 0;
		preturn_string->m_reference_string = null;
	}
	else
	{
		preturn_string->m_using_internal_buffer = pfx_true;
		preturn_string->m_interbuffer_defualt_buffer_size =  ((min_charbuffer_size > 0x3FFF) ? 0x3FFF:min_charbuffer_size); ;
		preturn_string->m_char_buffer_size = 0;
		preturn_string->m_reference_string = init_string_by_buffer(char_size,sizeof(pfx_share_string_t) + preturn_string->m_interbuffer_defualt_buffer_size ,//min_buffer_size-sizeof(pfx_share_string_t),
			string_obj_buffer+sizeof(pfx_share_string_t),&status);
	};

	SET_POINTER_VALUE (pstatus,status);
	RETURN_INVALID_RESULT( (PFX_STATUS_OK != status), null);
	return preturn_string;
}

// 从内存分配器中新建一个字符串
pfx_share_string_t* new_share_string(size_t char_size,size_t min_char_buffer_size,
	const IAllocator* PARAM_IN pAllocator,
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_share_string_t* preturn_string = null;
	size_t	allocate_size = sizeof (pfx_share_string_t); 
	pfx_char_t* pallocate_chars = null;
	RETURN_INVALID_BY_ACT_RESULT ((null == pAllocator),SET_POINTER_VALUE(pstatus,PFX_STATUS_INVALID_PARAMS),null);

	if (min_char_buffer_size > 0)
	{
		allocate_size = sizeof (pfx_share_string_extern_t) + min_char_buffer_size;
	}

	pallocate_chars = (pfx_char_t*)pAllocator->allocate_obj((pfx_long_t)pAllocator,allocate_size);

	RETURN_INVALID_BY_ACT_RESULT ((null == pallocate_chars),
		SET_POINTER_VALUE(pstatus,PFX_STATUS_MEM_LOW),null);

	preturn_string = init_share_string_by_buffer(char_size,allocate_size,pallocate_chars,pstatus);
	return preturn_string;
}

// 初始化字符串
pfx_result_t init_share_string(pfx_share_string_t* PARAM_INOUT pstr,
	size_t string_len,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	pfx_bool_t	check_result = pfx_false;

	RETURN_INVALID_RESULT ((null == pstr || null == pchar_allocator),PFX_STATUS_INVALID_PARAMS);
	
	check_result = check_is_linked_list_only_one_node(&pstr->m_list_node);

	RETURN_INVALID_RESULT ((pfx_invalid == check_result),PFX_STATUS_ERROR_);

	if (pfx_true == check_result)
	{
		if (null == pstr->m_reference_string)
		{
			pstr->m_reference_string = new_string(pstr->m_char_size,pstr->m_interbuffer_defualt_buffer_size,pchar_allocator,&status);

			RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),status);
		}
	}
	else
	{
		RETURN_INVALID_RESULT ((null == pstr->m_reference_string),PFX_STATUS_MEM_ERR);
		status = relese_share_string_extern_buffer(pstr,pchar_allocator);

		RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),status);

		if (null == pstr->m_reference_string)
		{
			pstr->m_reference_string = new_string(pstr->m_char_size,pstr->m_interbuffer_defualt_buffer_size,pchar_allocator,&status);

			RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),status);
		}
	}

	status = init_string(pstr->m_reference_string,string_len,pchar_allocator);

	if (PFX_STATUS_OK == status)
	{
		pstr->m_char_buffer_offset = 0;
		pstr->m_char_buffer_size = pstr->m_reference_string->m_string_buffer_length;
	}


	return status;
}

// 使用现有buffer初始化字符串结构体，同时原有buffer转化为字符结构体
pfx_result_t init_share_string_by_charsbuffer(pfx_share_string_t* PARAM_INOUT pstr,
	const pfx_char_t* PARAM_IN pstr_chars,size_t chars_buffer_size,
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	RETURN_INVALID_RESULT (null == pstr || null == pstr_chars || 0 >= chars_buffer_size|| null == pchar_allocator,
		PFX_STATUS_INVALID_PARAMS);

	if (pstr_chars == get_string_chars_buffer(pstr->m_reference_string))
	{
		return PFX_STATUS_OK;
	}

	if (pstr_chars > get_string_chars_buffer(pstr->m_reference_string) && 
		pstr_chars < (get_string_chars_buffer(pstr->m_reference_string) + get_string_chars_length(pstr->m_reference_string)))
	{
		size_t offset = pstr_chars - get_string_chars_buffer(pstr->m_reference_string);
		status = resize_share_string(pstr,chars_buffer_size,pfx_true,pfx_false,pchar_allocator);
		pstr_chars = get_string_chars_buffer(pstr->m_reference_string) + offset;
	}
	else
	{
		status = init_share_string(pstr,chars_buffer_size,pchar_allocator);
	}

	

	if (PFX_STATUS_OK == status)
	{
		RETURN_RESULT ((0 == chars_buffer_size),status);
		RETURN_INVALID_RESULT ((null == pstr->m_reference_string),PFX_STATUS_MEM_ERR);

		status = init_string_by_charsbuffer(pstr->m_reference_string,pstr_chars,chars_buffer_size,pchar_allocator);
		pstr->m_char_buffer_size = get_string_chars_length(pstr->m_reference_string);//pstr->m_reference_string->m_string_buffer_length;
	}
	return status;
}

// 释放一个字符串占有的额外的内存资源
pfx_result_t relese_share_string_extern_buffer(pfx_share_string_t* PARAM_INOUT pstr,
	const IAllocator* PARAM_IN pAllocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	pfx_bool_t check_result = pfx_false;
	RETURN_INVALID_RESULT ((null == pstr || null == pAllocator),PFX_STATUS_INVALID_PARAMS);

	check_result = check_is_linked_list_only_one_node(&pstr->m_list_node);
	RETURN_INVALID_RESULT ((pfx_invalid==check_result),PFX_STATUS_ERROR_);

	if (pfx_true == check_result)
	{
		pstr->m_char_buffer_size = 0;
		pstr->m_char_buffer_offset = 0;
		if (null != pstr->m_reference_string)
		{
			status = relese_string_extern_buffer(pstr->m_reference_string,pAllocator);

			if (PFX_STATUS_OK == status && 
				pstr->m_reference_string != (&((pfx_share_string_extern_t*)pstr)->m_string_instance))
			{
				pAllocator->dellocate_obj((pfx_long_t)pAllocator,pstr->m_reference_string);
				pstr->m_reference_string = null;
			}
		}
	}
	else
	{
		linked_list_node_t* premove = remove_linked_list_node(&pstr->m_list_node);
		RETURN_INVALID_RESULT (null == premove,PFX_STATUS_ERROR_);
		premove = init_linked_list_node(premove);
		RETURN_INVALID_RESULT (null == premove,PFX_STATUS_ERROR_);
		pstr->m_char_buffer_size = 0;
		pstr->m_char_buffer_offset = 0;
	}
	return status;
}

// 字符串拷贝
pfx_result_t copy_share_string(pfx_share_string_t* PARAM_INOUT pstr_dec,
	const pfx_share_string_t* PARAM_IN pstr_src,const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	pfx_bool_t check_result = pfx_false;

	RETURN_INVALID_RESULT (((null == pstr_dec)||(null == pstr_src)||(null == pchar_allocator)),
		PFX_STATUS_INVALID_PARAMS);
	
	RETURN_RESULT (pstr_dec == pstr_src,PFX_STATUS_OK);

	if (pstr_dec->m_reference_string == pstr_src->m_reference_string)
	{
		pstr_dec->m_char_buffer_offset = pstr_src->m_char_buffer_offset;
		pstr_dec->m_char_buffer_size = pstr_src->m_char_buffer_size;
		return PFX_STATUS_OK;
	}

	if (null == pstr_src->m_reference_string || 0 == pstr_src->m_char_buffer_size)
	{
		RETURN_INVALID_RESULT ((pstr_src->m_char_buffer_offset + pstr_src->m_char_buffer_size) > 
			pstr_src->m_reference_string->m_string_buffer_length,PFX_STATUS_MEM_ERR);

		return relese_share_string_extern_buffer(pstr_dec,pchar_allocator);
	}

	check_result = check_is_linked_list_only_one_node(&pstr_dec->m_list_node);
	RETURN_INVALID_RESULT ((pfx_invalid==check_result),PFX_STATUS_ERROR_);

	if (pfx_false == check_result)
	{
		linked_list_node_t* premove = remove_linked_list_node(&pstr_dec->m_list_node);
		RETURN_INVALID_RESULT (null == premove,PFX_STATUS_ERROR_);
		premove = init_linked_list_node(premove);
		RETURN_INVALID_RESULT (null == premove,PFX_STATUS_ERROR_);

		if (pstr_dec->m_using_internal_buffer)
		{
			pstr_dec->m_reference_string = &((pfx_share_string_extern_t*)pstr_dec)->m_string_instance;
		}
		else
		{
			pstr_dec->m_reference_string = null;
		}
	}

	if (null == pstr_dec->m_reference_string)
	{
		pstr_dec->m_reference_string = new_string(pstr_src->m_reference_string->m_char_size,
			pstr_src->m_reference_string->m_defualt_buffer_size,pchar_allocator,&status);
	}

	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),PFX_STATUS_ERROR_);

	status = init_string_by_charsbuffer(pstr_dec->m_reference_string,
		get_share_string_chars_buffer(pstr_src),
		get_share_string_char_buffer_size(pstr_src),
		pchar_allocator);

	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),PFX_STATUS_ERROR_);

	pstr_dec->m_char_buffer_offset = 0;
	pstr_dec->m_char_buffer_size = pstr_src->m_char_buffer_size;
	return status;
}


pfx_share_string_t* get_share_sub_string	(pfx_share_string_t* PARAM_INOUT porign_string,
	size_t ioffset,size_t sub_string_length,
	pfx_bool_t	bnew_buffer,
	const IAllocator* PARAM_IN pchar_allocator,
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_result_t status = PFX_STATUS_OK;
	pfx_bool_t	check_result = pfx_false; 
	pfx_share_string_t* preturn_string = null;
	const linked_list_node_t* pshare_node = null;

	RETURN_INVALID_BY_ACT_RESULT ((null == porign_string || null == pchar_allocator),
		SET_POINTER_VALUE(pstatus,PFX_STATUS_INVALID_PARAMS),
		null);

	if (null == porign_string->m_reference_string)
	{
		SET_POINTER_VALUE(pstatus,PFX_STATUS_OK);
		return null;
	}

	if (ioffset > porign_string->m_char_buffer_size)
	{
		SET_POINTER_VALUE(pstatus,PFX_STATUS_OK);
		return null;
	}

	if (ioffset + sub_string_length > porign_string->m_char_buffer_size)
	{
		sub_string_length = porign_string->m_char_buffer_size - ioffset;
	}

	if (0 >= sub_string_length)
	{
		SET_POINTER_VALUE(pstatus,PFX_STATUS_OK);
		return null;
	}

	if (pfx_true == bnew_buffer)
	{
		preturn_string = new_share_string(porign_string->m_char_size,
			porign_string->m_using_internal_buffer,pchar_allocator,&status);

		RETURN_INVALID_BY_ACT_RESULT(PFX_STATUS_OK != status,SET_POINTER_VALUE(pstatus,status),null);
		
		status = init_share_string_by_charsbuffer(preturn_string,
			get_share_string_chars_buffer(porign_string),
			get_share_string_char_buffer_size(porign_string),pchar_allocator);

		RETURN_INVALID_BY_ACT_RESULT(PFX_STATUS_OK != status,SET_POINTER_VALUE(pstatus,status),null);
	}


	preturn_string = new_share_string(porign_string->m_char_size,0,pchar_allocator,&status);

	RETURN_INVALID_BY_ACT_RESULT(PFX_STATUS_OK != status,SET_POINTER_VALUE(pstatus,status),null);

	if (porign_string->m_reference_string == &(((pfx_share_string_extern_t*)porign_string)->m_string_instance) &&
		porign_string->m_using_internal_buffer)
	{
		pfx_string_t* pdec_string;
		pdec_string = new_string(porign_string->m_reference_string->m_char_size,
			porign_string->m_reference_string->m_defualt_buffer_size,pchar_allocator,&status);

		RETURN_INVALID_BY_ACT_RESULT(PFX_STATUS_OK != status,SET_POINTER_VALUE(pstatus,status),null);

		memcpy(pdec_string,
			porign_string->m_reference_string,
			sizeof (pfx_string_t) + porign_string->m_reference_string->m_defualt_buffer_size);

		if (porign_string->m_reference_string->m_defualt_buffer_size > 0)
		{
			porign_string->m_reference_string->m_pthis_string_data = 
				((pfx_char_t*)porign_string+sizeof(pfx_string_t));
		}
		else
		{
			porign_string->m_reference_string->m_pthis_string_data = null;
		}

		porign_string->m_reference_string->m_using_extern_buffer = 0;
		porign_string->m_reference_string->m_string_buffer_length = 0;
		porign_string->m_reference_string->m_string_buffer_size = 
			porign_string->m_reference_string->m_defualt_buffer_size;

		porign_string->m_reference_string = pdec_string;
	}

	pshare_node = insert_linked_list_node_end(&porign_string->m_list_node,&preturn_string->m_list_node);

	RETURN_INVALID_BY_ACT_RESULT(null == pshare_node,SET_POINTER_VALUE(pstatus,PFX_STATUS_ERROR_),null);

	preturn_string->m_reference_string = porign_string->m_reference_string;
	preturn_string->m_char_buffer_offset = porign_string->m_char_buffer_offset + ioffset;
	preturn_string->m_char_buffer_size = sub_string_length;

	return preturn_string;
}

// 重新定义共享字符串大小
pfx_result_t resize_share_string (pfx_share_string_t* PARAM_INOUT pstr,
	size_t string_len,pfx_bool_t busing_internal_buffer, pfx_bool_t bnew_allocate, 
	const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	pfx_bool_t check_result = pfx_false;
	size_t string_len_ = 0;
	size_t string_default_len = MIN_STRING_BUFFER_SIZE;
	pfx_string_t* pog_string = null;
	
	RETURN_INVALID_RESULT ((null == pstr || null == pchar_allocator),PFX_STATUS_INVALID_PARAMS);

	if (0 == string_len && pfx_true == bnew_allocate)
	{
		return relese_share_string_extern_buffer(pstr,pchar_allocator);
	}

	check_result = check_is_linked_list_only_one_node(&pstr->m_list_node);
	RETURN_INVALID_RESULT ((pfx_invalid == check_result), PFX_STATUS_MEM_ERR);

	if (null != pstr->m_reference_string)
	{
		RETURN_INVALID_RESULT ((pstr->m_char_size != pstr->m_reference_string->m_char_size),
			PFX_STATUS_MEM_ERR);
		string_len_ = pstr->m_reference_string->m_string_buffer_length;
		string_default_len = pstr->m_reference_string->m_defualt_buffer_size;
		pog_string = pstr->m_reference_string;
	}

	if (pfx_false == check_result)
	{
		linked_list_node_t* premove = remove_linked_list_node(&pstr->m_list_node);
		RETURN_INVALID_RESULT (null == premove,PFX_STATUS_ERROR_);
		premove = init_linked_list_node(premove);
		RETURN_INVALID_RESULT (null == premove,PFX_STATUS_ERROR_);

		if (pstr->m_using_internal_buffer && pfx_true == busing_internal_buffer)
		{
			pstr->m_reference_string = &((pfx_share_string_extern_t*)pstr)->m_string_instance;
		}
		else
		{
			pstr->m_reference_string = null;
		}

	}

	if (null == pstr->m_reference_string)
	{
		if (string_len > 0)
		{
			pstr->m_reference_string = new_string(pstr->m_char_size,string_default_len,pchar_allocator,&status);

			RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

			if (null != pog_string)
			{
				status = copy_string(pstr->m_reference_string,pog_string,pchar_allocator);
			}
		}
	}
	else
	{
		status = resize_string(pstr->m_reference_string,string_len,bnew_allocate,pchar_allocator);
	}

	if (PFX_STATUS_OK == status)
	{
		pstr->m_char_buffer_offset = 0;
		pstr->m_char_buffer_size = get_string_chars_length(pstr->m_reference_string);
		//if (pstr->m_reference_string)
		//{
		//	pstr->m_char_buffer_size = pstr->m_reference_string->m_string_buffer_length;
		//}
		//else
		//{
		//	pstr->m_char_buffer_size = 0;
		//}
	}


	return status;
}


// 给字符串后面加入新的字符串
pfx_result_t append_share_string_by_chars (pfx_share_string_t* PARAM_INOUT pstr,
	const char* PARAM_IN str_chars, size_t chars_buffer_size,const IAllocator* PARAM_IN pchar_allocator)
{
	pfx_result_t status = PFX_STATUS_OK;
	pfx_bool_t	check_result = pfx_false;
	//size_t	new_offset;
	//pfx_char_t*	pchar_ = null;

	RETURN_INVALID_RESULT ((null == pstr || (null == str_chars && chars_buffer_size > 0)||null == pchar_allocator),PFX_STATUS_INVALID_PARAMS);

	RETURN_RESULT (null == str_chars,PFX_STATUS_OK);

	
	if (str_chars >= get_string_chars_buffer(pstr->m_reference_string) && 
		str_chars < (get_string_chars_buffer(pstr->m_reference_string)+get_string_chars_length(pstr->m_reference_string))  )
	{
		// 使用字符串自身字符进行添加
		size_t offset = str_chars - get_string_chars_buffer(pstr->m_reference_string);
		status = resize_share_string(pstr,pstr->m_char_buffer_size + chars_buffer_size,pfx_true,pfx_false,pchar_allocator);
		RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);
		str_chars = get_string_chars_buffer(pstr->m_reference_string) + offset;
	}
	else
	{
		status = resize_share_string(pstr,pstr->m_char_buffer_size + chars_buffer_size,pfx_true,pfx_false,pchar_allocator);
	}
	//new_offset = pstr->m_char_buffer_size;
	

	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	//pchar_ =  (pfx_char_t*)get_share_string_chars_buffer(pstr);
	//pchar_ += new_offset;

	//memcpy (pchar_,str_chars,chars_buffer_size);

	status = append_string_by_chars(pstr->m_reference_string,str_chars,chars_buffer_size,pchar_allocator);

	RETURN_INVALID_RESULT (PFX_STATUS_OK != status,status);

	pstr->m_char_buffer_size = get_string_chars_length(pstr->m_reference_string);

	return status;
}


