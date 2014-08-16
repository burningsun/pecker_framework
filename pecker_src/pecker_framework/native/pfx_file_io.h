/*
 * pfx_file_io.h
 *
 *  Created on: 2013-9-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FILE_IO_H_
#define		PFX_FILE_IO_H_

#include "../pfx_defines.h"
#include <time.h>
//#include <stdio.h>

#define  MAX_PATH_NAME 1024

PFX_C_EXTERN_BEGIN

typedef struct st_file
{
	handle_t	m_hfile;
	time_t      m_create_time;
	time_t      m_lastmodify_time;
	size_t		m_file_size;
}file_t;

typedef struct st_file_data_buffer
{
	void*	m_pitems_buffer;
	size_t	m_item_size;
	size_t	m_items_count;
}file_data_buffer_t;

PFX_CORE_API result_t pfx_check_file_exists (const char_t*  PARAM_IN pstr_path_name);

PFX_CORE_API result_t pfx_open_file (file_t* PARAM_INOUT	hfile,
										const char_t* PARAM_IN	pstr_path_name,
										const char_t* PARAM_IN pstr_mode);

PFX_CORE_API result_t pfx_close_file (file_t* PARAM_INOUT hfile);

PFX_CORE_API result_t pfx_seek_file (file_t* PARAM_INOUT hfile,long_t offset,sint_t origin);

//PFX_CORE_API pfx_result_t pfx_file_scanf (pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...);


PFX_CORE_API result_t pfx_file_printf (file_t* PARAM_INOUT hfile,const char_t* PARAM_IN str_format,...);

//PFX_CORE_API pfx_result_t pfx_file_wscanf (pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);

//PFX_CORE_API pfx_result_t pfx_file_wprintf (pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);


PFX_CORE_API sint_t	pfx_test_file_eof (file_t* PARAM_INOUT hfile);

PFX_CORE_API size_t pfx_file_read (file_t* PARAM_INOUT hfile,file_data_buffer_t* PARAM_INOUT pread_buffer);

PFX_CORE_API size_t pfx_file_write (file_t* PARAM_INOUT hfile,file_data_buffer_t* PARAM_INOUT pwrite_buffer);

PFX_CORE_API sint_t pfx_test_file_error (file_t* PARAM_INOUT hfile); 

PFX_CORE_API size_t pfx_get_file_size (file_t* PARAM_INOUT hfile);

PFX_CORE_API sint_t pfx_file_flush (file_t* PARAM_INOUT hfile);

// '\0'结束
PFX_CORE_API nsize__t pfx_file_get_string_a (file_t* PARAM_INOUT hfile,
															char_t* PARAM_INOUT pbuffer,
															usize__t nread_buffer_size);

PFX_CORE_API nsize__t pfx_file_set_string_a (file_t* PARAM_INOUT hfile,
															char_t* PARAM_INOUT pbuffer,
															usize__t nread_buffer_size);

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

class PFX_NATIVE_API pecker_file
{
protected:
	file_t	m_file;  
public:
	static result_t			is_file_exists (const char_t* pstr_path);
	static flag_t			get_file_rw_mode (const char_t* pstr_path);
public:
	pecker_file();
	virtual ~pecker_file();

	result_t			open (const char_t* pstr_path, flag_t nOpenType);
	result_t			close();

	result_t			read_to_memery (byte_t* PARAM_INOUT memery_buffer_ptr,usize__t& PARAM_INOUT memery_buffer_size);

	usize__t			write_to_file(const byte_t*  memery_buffer_ptr, usize__t memery_buffer_size,result_t& PARAM_INOUT error_code_s);

	result_t			seek (long_t offset,sint_t origin);

	nsize__t			get_file_size();
	PFX_INLINE nsize__t	get_readonly_file_size()  const
	{
		return m_file.m_file_size;
	}

	sint_t				test_error ();

	sint_t				fflush ();

	sint_t				eof ();

	file_t*				get_handle ();
	
};

PECKER_END


#endif			//PFX_FILE_IO_H_
