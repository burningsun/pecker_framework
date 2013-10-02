/*
 * pfx_file_io.h
 *
 *  Created on: 2013-9-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FILE_IO_H_
#define		PFX_FILE_IO_H_

#include "../pfx_defines.h"
#include <stdio.h>

#define  MAX_PATH_NAME 1024

PFX_C_EXTERN_BEGIN

typedef struct st_pfx_file
{
	pfx_handle_t	m_hfile;
	size_t				m_file_size;
}pfx_file_t;

typedef struct st_pfx_file_data_buffer
{
	void*	m_pitems_buffer;
	size_t	m_item_size;
	size_t	m_items_count;
}pfx_file_data_buffer_t;

pfx_result_t pfx_check_file_exists (const pfx_char_t*  PARAM_IN pstr_path_name);

pfx_result_t pfx_open_file (pfx_file_t* PARAM_INOUT	hfile,
										const pfx_char_t* PARAM_IN	pstr_path_name,
										const pfx_char_t* PARAM_IN pstr_mode);

pfx_result_t pfx_close_file (pfx_file_t* PARAM_INOUT hfile);

pfx_result_t pfx_seek_file (pfx_file_t* PARAM_INOUT hfile,pfx_long_t offset,pfx_sint_t origin);

pfx_result_t pfx_file_scanf (pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...);


pfx_result_t pfx_file_printf (pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...);

pfx_result_t pfx_file_wscanf (pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);

pfx_result_t pfx_file_wprintf (pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);


pfx_sint_t	pfx_test_file_eof (pfx_file_t* PARAM_INOUT hfile);

size_t pfx_file_read (pfx_file_t* PARAM_INOUT hfile,pfx_file_data_buffer_t* PARAM_INOUT pread_buffer);

size_t pfx_file_write (pfx_file_t* PARAM_INOUT hfile,pfx_file_data_buffer_t* PARAM_INOUT pwrite_buffer);

pfx_sint_t pfx_test_file_error (pfx_file_t* PARAM_INOUT hfile); 

size_t pfx_get_file_size (pfx_file_t* PARAM_INOUT hfile);

pfx_sint_t pfx_file_flush (pfx_file_t* PARAM_INOUT hfile);

// '\0'结束
pfx_nsize_t pfx_file_get_string_a (pfx_file_t* PARAM_INOUT hfile,
															pfx_char_t* PARAM_INOUT pbuffer,
															pfx_usize_t nread_buffer_size);

pfx_nsize_t pfx_file_set_string_a (pfx_file_t* PARAM_INOUT hfile,
															pfx_char_t* PARAM_INOUT pbuffer,
															pfx_usize_t nread_buffer_size);

PFX_C_EXTERN_END



#endif			//PFX_FILE_IO_H_
