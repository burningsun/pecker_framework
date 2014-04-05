/*
 * pfx_file_io.h
 *
 *  Created on: 2013-9-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FILE_IO_H_
#define		PFX_FILE_IO_H_

#include "../pfx_defines.h"
//#include <stdio.h>

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

PFX_CORE_API pfx_result_t pfx_check_file_exists (const pfx_char_t*  PARAM_IN pstr_path_name);

PFX_CORE_API pfx_result_t pfx_open_file (pfx_file_t* PARAM_INOUT	hfile,
										const pfx_char_t* PARAM_IN	pstr_path_name,
										const pfx_char_t* PARAM_IN pstr_mode);

PFX_CORE_API pfx_result_t pfx_close_file (pfx_file_t* PARAM_INOUT hfile);

PFX_CORE_API pfx_result_t pfx_seek_file (pfx_file_t* PARAM_INOUT hfile,pfx_long_t offset,pfx_sint_t origin);

//PFX_CORE_API pfx_result_t pfx_file_scanf (pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...);


PFX_CORE_API pfx_result_t pfx_file_printf (pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...);

//PFX_CORE_API pfx_result_t pfx_file_wscanf (pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);

//PFX_CORE_API pfx_result_t pfx_file_wprintf (pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);


PFX_CORE_API pfx_sint_t	pfx_test_file_eof (pfx_file_t* PARAM_INOUT hfile);

PFX_CORE_API size_t pfx_file_read (pfx_file_t* PARAM_INOUT hfile,pfx_file_data_buffer_t* PARAM_INOUT pread_buffer);

PFX_CORE_API size_t pfx_file_write (pfx_file_t* PARAM_INOUT hfile,pfx_file_data_buffer_t* PARAM_INOUT pwrite_buffer);

PFX_CORE_API pfx_sint_t pfx_test_file_error (pfx_file_t* PARAM_INOUT hfile); 

PFX_CORE_API size_t pfx_get_file_size (pfx_file_t* PARAM_INOUT hfile);

PFX_CORE_API pfx_sint_t pfx_file_flush (pfx_file_t* PARAM_INOUT hfile);

// '\0'结束
PFX_CORE_API pfx_nsize_t pfx_file_get_string_a (pfx_file_t* PARAM_INOUT hfile,
															pfx_char_t* PARAM_INOUT pbuffer,
															pfx_usize_t nread_buffer_size);

PFX_CORE_API pfx_nsize_t pfx_file_set_string_a (pfx_file_t* PARAM_INOUT hfile,
															pfx_char_t* PARAM_INOUT pbuffer,
															pfx_usize_t nread_buffer_size);

PFX_C_EXTERN_END

PECKER_BEGIN

typedef enum enumFILE_ORIGIN
{
	PFX_FILE_SEEK_SET  =  0,
	PFX_FILE_SEEK_CUR = 1,
	PFX_FILE_SEEK_END = 2
}FILE_ORIGIN_t;

//file rw mode
#define PF_FILE_NO_EXISTS			(0)
#define PF_FILE_EXISTS				(1<<0)
#define PF_FILE_READ_ONLY		(1<<1)
#define PF_FILE_WRITE_ONLY		(1<<2)
#define PF_FILE_RW						(1<<3)

//file open mode
#define PFO_OPEN_NONE			(0)
#define PFO_OPEN_EXISTS			(1<<0)
#define PFO_OPEN_CREATE			(1<<1)
#define PFO_OPEN_READ				(1<<2)
#define PFO_OPEN_WRITE			(1<<3)
#define PFO_OPEN_APPEND		(1<<4)
#define PFO_OPEN_BINARY			(1<<5)
#define PFO_OPEN_TEXT				(1<<6)
#define PFO_OPEN_EX_BIT			(1<<7)

class pfx_cfile
{
protected:
	pfx_file_t	m_file;
public:
	static pfx_result_t				set_install_apkfile_path (const pfx_char_t* str_path_ptr,pfx_nsize_t path_length);
	static const pfx_char_t*	get_install_apkfile_path (pfx_nsize_t& path_length);
	static pfx_handle_t			get_private_apkfile_manager ();
	static pfx_result_t				is_file_exists (const pfx_char_t* pstr_path,pfx_nsize_t path_length);
	static pfx_flag_t					get_file_rw_mode (const pfx_char_t* pstr_path,pfx_nsize_t path_length);
public:
	pfx_cfile();
	virtual ~pfx_cfile();

	pfx_result_t			open (const pfx_char_t* pstr_path,pfx_nsize_t path_length, pfx_flag_t nOpenType);
	pfx_result_t			close();

	pfx_result_t			read_to_memery (pfx_byte_t* PARAM_INOUT memery_buffer_ptr,pfx_usize_t memery_buffer_size,
												pfx_usize_t& PARAM_INOUT read_buffer_size);

	pfx_usize_t				write_to_file(const pfx_byte_t*  memery_buffer_ptr, pfx_usize_t memery_buffer_size,pfx_result_t& PARAM_INOUT error_code_s);

	pfx_result_t			seek (pfx_long_t offset,pfx_sint_t origin);

	pfx_nsize_t				get_file_size();

	pfx_sint_t				test_error ();

	pfx_sint_t				fflush ();

	pfx_file_t*				get_handle () const;
	
};

PECKER_END


#endif			//PFX_FILE_IO_H_
