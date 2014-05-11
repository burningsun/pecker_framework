/*
 * pfx_file_inputdata_cmd.cpp
 *
 *  Created on: 2013-9-29
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */


#include "pfx_file_inputdata_cmd.h"

#include "../pecker_framework/native/pfx_file_io.h"

result_t file_data_input_for_test_running(const char_t* pfile_name,cmd_operate_func cmd_operate_method)
{
	file_t hfile;
	result_t status = PFX_STATUS_OK;
	CMD_INOUT_t cmdType = CMD_NONE;

	RETURN_INVALID_RESULT((null == pfile_name || null == cmd_operate_method),PFX_STATUS_INVALID_PARAMS);

	status = pfx_check_file_exists(pfile_name);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);
	status = pfx_open_file(&hfile,pfile_name,"r");
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

	
	while(1)
	{
		const usize__t MAX_STRING_SIZE = 256;
		char_t pstr_buffer[MAX_STRING_SIZE];
		nsize__t nstr_size = 0;

		if (pfx_test_file_eof(&hfile))
			break;

		nstr_size = pfx_file_get_string_a(&hfile,pstr_buffer,MAX_STRING_SIZE);

		if ( null != strstr(pstr_buffer,"[add]"))
		{
			cmdType = CMD_ADD;
			PECKER_LOG_DIRECT_A("===========add============\n","");
			continue;
		}
		else if (null != strstr(pstr_buffer,"[del]"))
		{
			cmdType = CMD_DEL;
			PECKER_LOG_DIRECT_A("===========del============\n","");
			continue;
		}
		else if (null != strstr(pstr_buffer,"[search]"))
		{
			cmdType = CMD_SEARCH;
			PECKER_LOG_DIRECT_A("===========search============\n","");
			continue;
		}
		else if (null != strstr(pstr_buffer,"[copy]"))
		{
			cmdType = CMD_COPY;
			PECKER_LOG_DIRECT_A("===========copy============\n","");
			continue;
		}
		else if (null != strstr(pstr_buffer,"[clr]"))
		{
			cmdType = CMD_CLR;
			PECKER_LOG_DIRECT_A("===========clr============\n","");
			continue;
		}
		else if (null != strstr(pstr_buffer,"[inc_order]"))
		{
			cmdType = CMD_TRAINORDER;
			PECKER_LOG_DIRECT_A("===========inc_order============\n","");
			continue;
		}
		else if (null != strstr(pstr_buffer,"[dec_order]"))
		{
			cmdType = CMD_TRACOVORDDER;
			PECKER_LOG_DIRECT_A("===========dec_order============\n","");
			continue;
		}
		else if (null != strstr(pstr_buffer,"[show]"))
		{
			cmdType = CMD_SHOW;
			PECKER_LOG_DIRECT_A("===========show============\n","");
			continue;
		}

		status = cmd_operate_method(&cmdType,pstr_buffer,nstr_size);
		if (PFX_STATUS_FIN == status)
		{
			break;
		}
	}

	return status;
}