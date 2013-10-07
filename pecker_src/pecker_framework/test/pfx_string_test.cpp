/*
 * pfx_list_test.cpp
 *
 *  Created on: 2013-9-3
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../data/pfx_string.h"
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

	return 0;
}


