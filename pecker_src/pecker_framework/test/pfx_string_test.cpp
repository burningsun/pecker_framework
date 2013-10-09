/*
 * pfx_list_test.cpp
 *
 *  Created on: 2013-9-3
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../data/pfx_string.h"
#include "../data/pfx_share_string.h"
#include "../native/pfx_log.h"




int string_test_main()
{
	pfx_result_t status;
	pfx_string_t* pcopy_str = null;
	const char* pget_chars = null;
	pfx_string_t* pstr = new_string(sizeof(pfx_char),MIN_STRING_BUFFER_SIZE,&gDefualt_allocator,&status);

	if (null != pstr && PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		status = init_string_by_charsbuffer(pstr,(char*)pfx_char_type("hello world!!"),
			pfx_strlen(pfx_char_type("hello world!!")) * sizeof(pfx_char),&gDefualt_allocator);
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),pstr->m_string_buffer_length / pstr->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,pstr->m_pthis_string_data);

		PECKER_LOG_("init_string_by_charsbuffer status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("new_string status = %d pstr = %08X",status,pstr);
	}

	pcopy_str = new_string(sizeof(pfx_char),MIN_STRING_BUFFER_SIZE,&gDefualt_allocator,&status);
	if (null != pcopy_str && PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		status = copy_string(pcopy_str,pstr,&gDefualt_allocator);
			pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),pcopy_str->m_string_buffer_length / pcopy_str->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,pcopy_str->m_pthis_string_data);
			
		PECKER_LOG_("copy_string status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("new_string status = %d pcopy_str = %08X",status,pstr);
	}

	status = append_string_by_chars(pcopy_str,(const char*)(pfx_char_type("your sister!")),
		sizeof(pfx_char) * pfx_strlen(pfx_char_type("your sister!")),&gDefualt_allocator);

	if (PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			pcopy_str->m_string_buffer_length / pcopy_str->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,pcopy_str->m_pthis_string_data);

		PECKER_LOG_("append_string_by_chars status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("append_string_by_chars status = %d pcopy_str = %08X",status,pstr);
	}

	pget_chars = get_string_buffer_chars_at(pcopy_str,3*pstr->m_char_size);
	if (null != pget_chars)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),3*pstr->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,pget_chars);
	}
	else
	{
		PECKER_LOG_("get_string_buffer_chars_at  = null\n","");
	}

	status = set_string_buffer_chars_at(pcopy_str,3*pstr->m_char_size,(const char*)pfx_char_type("..ooxx.."),
		sizeof(pfx_char)*pfx_strlen(pfx_char_type("..ooxx..")));

	if (PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			pcopy_str->m_string_buffer_length / pcopy_str->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,pcopy_str->m_pthis_string_data);

		PECKER_LOG_("set_string_buffer_chars_at status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("set_string_buffer_chars_at status = %d\n",status);
	}

	status = swap_string(pstr,pcopy_str);
	if (PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		
		pfx_sprintf(print_string_format,pfx_char_type("pstr = %%.%ds\n"),
			pstr->m_string_buffer_length / pstr->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,pstr->m_pthis_string_data);

		pfx_sprintf(print_string_format,pfx_char_type("pcopy_str = %%.%ds\n"),
			pcopy_str->m_string_buffer_length / pcopy_str->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,pcopy_str->m_pthis_string_data);
	}
	PECKER_LOG_("swap_string status = %d\n",status);

	status = swap_string(pstr,pcopy_str);
	if (PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];

		pfx_sprintf(print_string_format,pfx_char_type("pstr = %%.%ds\n"),
			pstr->m_string_buffer_length / pstr->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,pstr->m_pthis_string_data);

		pfx_sprintf(print_string_format,pfx_char_type("pcopy_str = %%.%ds\n"),
			pcopy_str->m_string_buffer_length / pcopy_str->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,pcopy_str->m_pthis_string_data);
	}
	PECKER_LOG_("swap_string status = %d\n",status);

	return 0;
}

int share_string_test_main()
{
	pfx_result_t status;
	pfx_share_string_t* pcopy_str1 = null;
	pfx_share_string_t* pcopy_str2= null;
	pfx_share_string_t* psub_str1 = null;
	pfx_share_string_t* psub_str2 = null;
	pfx_share_string_t* psub_str3 = null;
	pfx_share_string_t* psub_str4 = null;

	const char* pget_chars = null;
	pfx_share_string_t* pstr = new_share_string(sizeof(pfx_char),MIN_STRING_BUFFER_SIZE,&gDefualt_allocator,&status);

	if (null != pstr && PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		status = init_share_string_by_charsbuffer(pstr,(char*)pfx_char_type("hello world!!"),
			pfx_strlen(pfx_char_type("hello world!!")) * sizeof(pfx_char),&gDefualt_allocator);
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),get_share_string_char_buffer_size(pstr) / pstr->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(pstr));

		PECKER_LOG_("init_share_string_by_charsbuffer status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("new_share_string status = %d pstr = %08X",status,pstr);
	}

	pcopy_str1 = new_share_string(sizeof(pfx_char),MIN_STRING_BUFFER_SIZE,&gDefualt_allocator,&status);
	if (null != pcopy_str1 && PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		status = copy_share_string(pcopy_str1,pstr,&gDefualt_allocator);
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),get_share_string_char_buffer_size(pcopy_str1) / pcopy_str1->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(pcopy_str1));

		PECKER_LOG_("copy_share_string status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("new_share_string status = %d pcopy_str = %08X",status,pstr);
	}

	status = append_share_string_by_chars(pcopy_str1,(const char*)(pfx_char_type("your sister!")),
		sizeof(pfx_char) * pfx_strlen(pfx_char_type("your sister!")),&gDefualt_allocator);

	if (PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			get_share_string_char_buffer_size(pcopy_str1) / pcopy_str1->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(pcopy_str1));

		PECKER_LOG_("append_share_string_by_chars status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("append_share_string_by_chars status = %d pcopy_str = %08X",status,pstr);
	}

	pcopy_str2 = new_share_string(sizeof(pfx_char),MIN_STRING_BUFFER_SIZE,&gDefualt_allocator,&status);
	if (null != pcopy_str2 && PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		status = copy_share_string(pcopy_str2,pcopy_str1,&gDefualt_allocator);
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),get_share_string_char_buffer_size(pcopy_str2) / pcopy_str2->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(pcopy_str2));

		PECKER_LOG_("copy_share_string status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("new_share_string status = %d pcopy_str = %08X",status,pstr);
	}


	pget_chars = get_share_string_buffer_chars_at(pcopy_str1,3*pcopy_str1->m_char_size);
	if (null != pget_chars)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),3*pcopy_str1->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,pget_chars);
	}
	else
	{
		PECKER_LOG_("get_share_string_buffer_chars_at  = null\n","");
	}

	status = set_share_string_buffer_chars_at(pcopy_str1,3*pcopy_str1->m_char_size,(const char*)pfx_char_type("..ooxx.."),
		sizeof(pfx_char)*pfx_strlen(pfx_char_type("..ooxx..")),&gDefualt_allocator);

	if (PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			get_share_string_char_buffer_size(pcopy_str1) / pcopy_str1->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(pcopy_str1));

		PECKER_LOG_("set_share_string_buffer_chars_at status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("set_share_string_buffer_chars_at status = %d\n",status);
	}

	psub_str1 = get_share_sub_string(pcopy_str2,sizeof(pfx_char) * 2,sizeof (pfx_char) * 20,pfx_false,&gDefualt_allocator,&status);

	if (PFX_STATUS_OK == status && null != psub_str1)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			get_share_string_char_buffer_size(psub_str1) / psub_str1->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(psub_str1));

		PECKER_LOG_("get_share_sub_string status = %d\n",status);

	}
	else
	{
		PECKER_LOG_("get_share_sub_string status = %d\n",status);
	}

	psub_str2 = get_share_sub_string(psub_str1,sizeof(pfx_char)*2,sizeof(pfx_char) * 15,pfx_false,&gDefualt_allocator,&status);

	if (PFX_STATUS_OK == status && null != psub_str2)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			get_share_string_char_buffer_size(psub_str2) / psub_str2->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(psub_str2));

		PECKER_LOG_("get_share_sub_string status = %d\n",status);

	}
	else
	{
		PECKER_LOG_("get_share_sub_string status = %d\n",status);
	}

	psub_str3 = get_share_sub_string(psub_str2,sizeof(pfx_char)*2,sizeof(pfx_char) * 13,pfx_false,&gDefualt_allocator,&status);

	if (PFX_STATUS_OK == status && null != psub_str3)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			get_share_string_char_buffer_size(psub_str3) / psub_str3->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(psub_str3));

		PECKER_LOG_("get_share_sub_string status = %d\n",status);

	}
	else
	{
		PECKER_LOG_("get_share_sub_string status = %d\n",status);
	}

	psub_str4 = get_share_sub_string(psub_str3,sizeof(pfx_char)*0,sizeof(pfx_char) * 10,pfx_false,&gDefualt_allocator,&status);

	if (PFX_STATUS_OK == status && null != psub_str4)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			get_share_string_char_buffer_size(psub_str4) / psub_str4->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(psub_str4));

		PECKER_LOG_("get_share_sub_string status = %d\n",status);

	}
	else
	{
		PECKER_LOG_("get_share_sub_string status = %d\n",status);
	}


	status = append_share_string_by_chars(pcopy_str1,(const char*)(pfx_char_type("your mother!")),
		sizeof(pfx_char) * pfx_strlen(pfx_char_type("your mother!")),&gDefualt_allocator);

	if (PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			get_share_string_char_buffer_size(pcopy_str1) / pcopy_str1->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(pcopy_str1));

		PECKER_LOG_("append_share_string_by_chars status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("append_share_string_by_chars status = %d pcopy_str = %08X",status,pstr);
	}

	
	pget_chars = get_share_string_buffer_chars_at(psub_str1,3*psub_str1->m_char_size);
	if (null != pget_chars)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),3*psub_str1->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,pget_chars);
	}
	else
	{
		PECKER_LOG_("get_share_string_buffer_chars_at  = null\n","");
	}

	status = set_share_string_buffer_chars_at(psub_str1,3*psub_str1->m_char_size,(const char*)pfx_char_type("111"),
		sizeof(pfx_char)*pfx_strlen(pfx_char_type("111")),&gDefualt_allocator);

	if (PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		pfx_sprintf(print_string_format,pfx_char_type("%%.%ds\n"),
			get_share_string_char_buffer_size(psub_str1) / psub_str1->m_char_size);

		PECKER_LOG_DIRECT(print_string_format,get_share_string_chars_buffer(psub_str1));

		PECKER_LOG_("set_share_string_buffer_chars_at status = %d\n",status);
	}
	else
	{
		PECKER_LOG_("set_share_string_buffer_chars_at status = %d\n",status);
	}
	
	//delete_share_string(pcopy_str1,&gDefualt_allocator);

	//delete_share_string(psub_str1,&gDefualt_allocator);
	delete_share_string(psub_str4,&gDefualt_allocator);
	delete_share_string(psub_str3,&gDefualt_allocator);
	delete_share_string(psub_str2,&gDefualt_allocator);

	delete_share_string(psub_str1,&gDefualt_allocator);

	delete_share_string(pcopy_str1,&gDefualt_allocator);
	delete_share_string(pcopy_str2,&gDefualt_allocator);
	delete_share_string(pstr,&gDefualt_allocator);

	return 0;
}


