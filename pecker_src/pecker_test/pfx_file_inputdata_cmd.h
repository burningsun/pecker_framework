/*
 * pfx_file_inputdata_cmd.h
 *
 *  Created on: 2013-9-29
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../pecker_framework/data/pfx_cbst_iterator_codes.h"
#include "../pecker_framework/native/pfx_log.h"



USING_PECKER_SDK

typedef enum 
{
	CMD_NONE = 0,
	CMD_ADD,
	CMD_SEARCH,
	CMD_DEL,
	CMD_CLR,
	CMD_TRAINORDER,
	CMD_TRACOVORDDER,
	CMD_SHOW,
	CMD_COPY,
	CMD_COUNT,
}CMD_INOUT_t;

typedef pfx_result_t	(*cmd_operate_func)(CMD_INOUT_t* cmd_type,const pfx_char_t* pstr_chars,pfx_usize_t nchars_count);

pfx_result_t file_data_input_for_test_running(const pfx_char_t* pfile_name,cmd_operate_func cmd_operate_method);

