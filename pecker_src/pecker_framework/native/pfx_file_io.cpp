﻿/*
 * pfx_file_io.cpp
 *
 *  Created on: 2013-9-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_file_io.h"

//#ifdef _MSC_VER
//#define _stat __stat
//#else
//#define _stat stat
//#endif

// 插，android 居然木有io.h这个文件
#if !defined(__APPLE__) && !defined(__ANDROID__)
 #include <io.h>
#endif //#if !defined(__APPLE__) && !defined(__ANDROID__)
#ifdef __ANDROID__
#include <stdarg.h>
#endif //#ifdef __ANDROID__


#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

#include "../data/pfx_cstring_codes.h"
#include "../data/pecker_value_compare.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif

result_t pfx_check_file_exists (const char_t*  PARAM_IN pstr_path_name)
{
	int status;

	if (null == pstr_path_name)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	status = ::access(pstr_path_name,0);

	switch(status)
	{
	case 0:
		return PFX_STATUS_OK;
	case EACCES:
		return PFX_STATUS_DENIED;
	case ENOENT:
		return PFX_STATUS_NOT_EXISTS;
	case EINVAL:
		return PFX_STATUS_INVALID_VALUE;
	default:
		return PFX_STATUS_ERROR_;
	}

}

result_t pfx_open_file (file_t* PARAM_INOUT	hfile,
										const char_t* PARAM_IN	pstr_path_name,
										const char_t* PARAM_IN pstr_mode)
{
	if (null == hfile || null == pstr_path_name || null == pstr_mode)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	hfile->m_hfile = ::fopen(pstr_path_name,pstr_mode);
	if (null != hfile->m_hfile)
	{
		struct stat _buffer;
		tzset();
		int res = stat(pstr_path_name, &_buffer);
		if (res)
		{
			hfile->m_file_size = pfx_get_file_size(hfile);
		}
		else
		{						 
			hfile->m_file_size = _buffer.st_size;
		}
		hfile->m_create_time = _buffer.st_ctime;
		hfile->m_lastmodify_time = _buffer.st_mtime;
		//
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_FAIL;
	}
	
}

result_t pfx_close_file(file_t* PARAM_INOUT hfile)
{
	int status;
	if (null == hfile)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	status = fclose((FILE*)(hfile->m_hfile));
	hfile->m_hfile = null;
	hfile->m_create_time = 0;
	hfile->m_lastmodify_time = 0;
	hfile->m_file_size = 0;
	if (0 == status)
	{
		return PFX_STATUS_OK;
	}
	else if (EOF == status)
	{
		return PFX_STATUS_ERROR_;
	}
	else
	{
		return PFX_STATUS_FAIL;
	}
}

result_t pfx_seek_file(file_t* PARAM_INOUT hfile,long_t offset,sint_t origin)
{
	result_t status;
	if (null == hfile)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	status = fseek((FILE*)hfile->m_hfile,offset,origin);
	if (0 == status)
	{
		return PFX_STATUS_OK;
	}
	else if (-1 == status)
	{
		return PFX_STATUS_INVALID_VALUE;
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}
}

////extern int vfscanf(FILE *stream, const char *format, va_list param);
//
//pfx_result_t pfx_file_scanf(pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...)
//{
//	va_list args_ptr;
//	va_start(args_ptr,str_format);
//	//fscanf ((FILE*)hfile->m_hfile,str_format,args_ptr);
//	//vfscanf ((FILE*)hfile->m_hfile,str_format,args_ptr);
//	//_IO_vfscanf (stdin, format, arg, NULL); 
//	va_end(args_ptr);
//	return PFX_STATUS_OK;
//
//}

result_t pfx_file_printf(file_t* PARAM_INOUT hfile,const char_t* PARAM_IN str_format,...)
{
	va_list args_ptr;
	va_start(args_ptr,str_format);
	vfprintf((FILE*)hfile->m_hfile,str_format,args_ptr);
	//_IO_vfscanf (stdin, format, arg, NULL); 
	va_end(args_ptr);
	return PFX_STATUS_OK;
}

//pfx_result_t pfx_file_wscanf(pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);
//
//pfx_result_t pfx_file_wprintf(pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);

sint_t	pfx_test_file_eof(file_t* PARAM_INOUT hfile)
{
	RETURN_INVALID_RESULT( (null == hfile),0);
	return feof((FILE*)hfile->m_hfile);
}

size_t pfx_file_read(file_t* PARAM_INOUT hfile,file_data_buffer_t* PARAM_INOUT pbuffer)
{
	RETURN_INVALID_RESULT( (null == hfile || null == hfile->m_hfile || 
		null == pbuffer || null == pbuffer->m_pitems_buffer || 
		0 == pbuffer->m_item_size || 0 == pbuffer->m_items_count),0);

	return fread(pbuffer->m_pitems_buffer,pbuffer->m_item_size,pbuffer->m_items_count,(FILE*)hfile->m_hfile);
}

size_t pfx_file_write(file_t* PARAM_INOUT hfile,file_data_buffer_t* PARAM_INOUT pbuffer)
{
	RETURN_INVALID_RESULT( (null == hfile || null == hfile->m_hfile || 
		null == pbuffer || null == pbuffer->m_pitems_buffer || 
		0 == pbuffer->m_item_size || 0 == pbuffer->m_items_count),0);

	return fwrite(pbuffer->m_pitems_buffer,pbuffer->m_item_size,pbuffer->m_items_count,(FILE*)hfile->m_hfile);
}

sint_t pfx_test_file_error(file_t* PARAM_INOUT hfile)
{
	RETURN_INVALID_RESULT( (null == hfile),0);
	return ferror((FILE*)hfile->m_hfile);
}

size_t pfx_get_file_size(file_t* PARAM_INOUT hfile)
{
	long file_pos_;
	RETURN_INVALID_RESULT( (null == hfile || 0 == hfile->m_hfile),0);
	file_pos_ = ftell((FILE*)hfile->m_hfile);
	fseek((FILE*)hfile->m_hfile,0,SEEK_END);
	hfile->m_file_size = ftell((FILE*)hfile->m_hfile);
	fseek((FILE*)hfile->m_hfile,file_pos_,SEEK_SET);
	return hfile->m_file_size;
}

sint_t pfx_file_flush(file_t* PARAM_INOUT hfile)
{
	RETURN_INVALID_RESULT( (null == hfile || 0 == hfile->m_hfile),EOF);
	return fflush((FILE*)hfile->m_hfile);
}


nsize__t pfx_file_get_string_a (file_t* PARAM_INOUT hfile,
	char_t* PARAM_INOUT pbuffer,
	usize__t nread_buffer_size)
{
	char_t* file_data = null;
	RETURN_INVALID_RESULT((null == hfile || null == hfile->m_hfile || null == pbuffer || 0 == nread_buffer_size),0);
	file_data = fgets(pbuffer,nread_buffer_size,(FILE*)hfile->m_hfile);
	if (null != file_data)
	{
		return strlen(file_data);
	}
	else
	{
		return 0;
	}
}

nsize__t pfx_file_set_string_a (file_t* PARAM_INOUT hfile,
	char_t* PARAM_INOUT pbuffer,
	usize__t nread_buffer_size)
{
	nsize__t write_size = 0;
	nsize__t temp_size = 0;
	char_t	temp_char;
	RETURN_INVALID_RESULT((null == hfile || null == hfile->m_hfile || null == pbuffer || 0 == nread_buffer_size),0);
	temp_size = strlen(pbuffer);
	if (temp_size > write_size)
	{
		temp_char = pbuffer[write_size];
		pbuffer[write_size] = 0;
		write_size = fputs(pbuffer,(FILE*)hfile->m_hfile);
		pbuffer[write_size] = temp_char;
	}
	else
	{
		write_size = fputs(pbuffer,(FILE*)hfile->m_hfile);
	}
	
	return write_size;
}



PECKER_BEGIN

result_t pecker_file::is_file_exists (const char_t* pstr_path)
{
	return pfx_check_file_exists (pstr_path);
}
flag_t pecker_file::get_file_rw_mode (const char_t* pstr_path)
{
	flag_t rw_mode = 0;
	if(0 == ::access(pstr_path,0))
	{
		rw_mode |= PF_FILE_EXISTS;
	}
	if(0 == ::access(pstr_path,2))
	{
		rw_mode |= PF_FILE_READ_ONLY;
	}
	if(0 == ::access(pstr_path,4))
	{
		rw_mode |= PF_FILE_WRITE_ONLY;
	}
	if(0 == ::access(pstr_path,6))
	{
		rw_mode |= PF_FILE_RW;
	}
	return rw_mode;
}


pecker_file::pecker_file()
{
	m_file.m_hfile = null;
	m_file.m_file_size = 0;
}

pecker_file::~pecker_file()
{
	close ();
}

#define APLUS_MASK 	(PFO_OPEN_CREATE | PFO_OPEN_WRITE | PFO_OPEN_READ)
#define A_MASK 	    (PFO_OPEN_CREATE | PFO_OPEN_WRITE)
#define WPLUS_MASK 	(PFO_OPEN_READ | PFO_OPEN_WRITE)
result_t pecker_file::open(const char_t* pstr_path, flag_t nOpenType)
{
	RETURN_INVALID_RESULT (null != m_file.m_hfile,PFX_STATUS_OPENED);

	char str_open_type[20] = "r";
	int string_length = 1;
	if (APLUS_MASK == (nOpenType & APLUS_MASK))
	{
		string_length = sprintf_s(str_open_type, sizeof(str_open_type), "a+");
	}
	else if (A_MASK == (nOpenType & A_MASK))
	{
		string_length = sprintf_s(str_open_type, sizeof(str_open_type), "a");
	}
	else if (WPLUS_MASK == (nOpenType & WPLUS_MASK))
	{
		string_length = sprintf_s(str_open_type, sizeof(str_open_type), "w+");
	}
	else if (PFO_OPEN_WRITE == (nOpenType & PFO_OPEN_WRITE))
	{
		string_length = sprintf_s(str_open_type, sizeof(str_open_type), "w");
		//string_length = 1;
	}

	if(nOpenType & PFO_OPEN_BINARY)
	{
		sprintf_s(str_open_type + string_length, sizeof(str_open_type)-string_length, "b");
	}

	if(nOpenType & PFO_OPEN_TEXT)
	{
		sprintf_s(str_open_type + string_length, sizeof(str_open_type)-string_length, "t");
	}

	result_t result_val;
	result_val = pfx_open_file(&m_file,pstr_path,str_open_type);
	if (PFX_STATUS_OK == result_val)
	{
		pfx_seek_file(&m_file,0,PFX_FILE_SEEK_SET);
	}
	return result_val;
}

result_t pecker_file::close()
{
	RETURN_RESULT (null == m_file.m_hfile || 0 == m_file.m_file_size,PFX_STATUS_OK);
	result_t result_val;
	result_val = pfx_close_file(&m_file);
	//if (PFX_STATUS_OK == result_val)
	//{
	//	m_file.m_hfile = null;
	//	m_file.m_file_size = 0;
	//	m_file.m_lastmodify_time = 0;
	//	m_file.m_create_time = 0;
	//}
	return result_val;
}

result_t pecker_file::read_to_memery (byte_t* PARAM_INOUT memery_buffer_ptr, 
	usize__t& PARAM_INOUT memery_buffer_size)
{
	result_t error_code_s;
	RETURN_INVALID_RESULT (null == memery_buffer_ptr || 0 == memery_buffer_size,PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT (null == m_file.m_file_size || 0 == m_file.m_file_size,PFX_STATUS_CLOSED);
	memery_buffer_size = fread(memery_buffer_ptr, sizeof (byte_t), memery_buffer_size, (FILE*)m_file.m_hfile);
	if (memery_buffer_size > 0)
	{
		error_code_s = PFX_STATUS_OK;
	}
	else
	{
		error_code_s = PFX_STATUS_FIN;
	}
	return error_code_s;

}

usize__t pecker_file::write_to_file (const byte_t* memery_buffer_ptr, usize__t memery_buffer_size,
	result_t& PARAM_INOUT error_code_s)
{
	RETURN_INVALID_RESULT (null == memery_buffer_ptr || 0 == memery_buffer_size,PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT (null == m_file.m_file_size || 0 == m_file.m_file_size,PFX_STATUS_CLOSED);
	memery_buffer_size = fwrite (memery_buffer_ptr,
		sizeof (byte_t),memery_buffer_size/sizeof(byte_t), (FILE*)m_file.m_hfile);
	error_code_s = PFX_STATUS_OK;

	return memery_buffer_size;
}

result_t pecker_file::seek(long_t offset,sint_t origin)
{
	RETURN_INVALID_RESULT (null == m_file.m_file_size || 0 == m_file.m_file_size,PFX_STATUS_CLOSED);
	return pfx_seek_file (&m_file,offset,origin);
}

nsize__t pecker_file::get_file_size()
{
	return pfx_get_file_size(&m_file);
}

sint_t	pecker_file::eof ()
{
	return pfx_test_file_eof(&m_file);
}
sint_t pecker_file::test_error ()
{
	return pfx_test_file_error (&m_file);
}

sint_t pecker_file::fflush()
{
	return pfx_file_flush (&m_file);
}

file_t*	pecker_file::get_handle()
{
	return &m_file;
}

PECKER_END

#ifdef _MSC_VER
#pragma warning(pop)
#endif

