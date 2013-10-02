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
	pfx_string_t* pstr = new_string(sizeof(pfx_char),MIN_STRING_BUFFER_SIZE,&gDefualt_allocator,&status);

	if (null != pstr && PFX_STATUS_OK == status)
	{
		pfx_char print_string_format[256];
		status = init_string_by_charsbuffer(pstr,(char*)pfx_char_type("hello world!!"),
			pfx_strlen(pfx_char_type("hello world!!")) * sizeof(pfx_char),&gDefualt_allocator);
		pfx_sprintf(print_string_format,pfx_char_type("code = %%.%ds\n"),pstr->m_string_buffer_length / pstr->m_char_size);
		PECKER_LOG_DIRECT(print_string_format,pstr->m_pthis_string_data);
	}
	else
	{
		PECKER_LOG_("new_string status = %d pstr = %08X",status,pstr);
	}

	if (PFX_STATUS_OK == status)
	{

	}

	return 0;
}


