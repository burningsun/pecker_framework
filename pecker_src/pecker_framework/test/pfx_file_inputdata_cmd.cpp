/*
 * pfx_file_inputdata_cmd.cpp
 *
 *  Created on: 2013-9-29
 *      Author: 李镇城 (cut / cutxyz)
 */


#include "pfx_file_inputdata_cmd.h"

#include "../native/pfx_file_io.h"

pfx_result_t file_data_input_for_test_running(const pfx_char_t* pfile_name,cmd_operate_func cmd_operate_method)
{
	pfx_file_t hfile;
	pfx_result_t status = PFX_STATUS_OK;
	CMD_INOUT_t cmdType = CMD_NONE;

	RETURN_INVALID_RESULT((null == pfile_name || null == cmd_operate_method),PFX_STATUS_INVALID_PARAMS);

	status = pfx_check_file_exists(pfile_name);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);
	status = pfx_open_file(&hfile,pfile_name,"r");
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

	
	while(1)
	{
		const pfx_usize_t MAX_STRING_SIZE = 256;
		pfx_char_t pstr_buffer[MAX_STRING_SIZE];
		pfx_nsize_t nstr_size = 0;

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