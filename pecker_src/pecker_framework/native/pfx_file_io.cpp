/*
 * pfx_file_io.cpp
 *
 *  Created on: 2013-9-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_file_io.h"
#include <io.h>
#include <errno.h>
#include <stdio.h>
#include "../data/pfx_cstring_codes.h"
#include "../data/pecker_value_compare.h"


pfx_result_t pfx_check_file_exists (const pfx_char_t*  PARAM_IN pstr_path_name)
{
	int status;

	if (null == pstr_path_name)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	status = access(pstr_path_name,0);

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

pfx_result_t pfx_open_file (pfx_file_t* PARAM_INOUT	hfile,
										const pfx_char_t* PARAM_IN	pstr_path_name,
										const pfx_char_t* PARAM_IN pstr_mode)
{
	if (null == hfile || null == pstr_path_name || null == pstr_mode)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	hfile->m_hfile = fopen(pstr_path_name,pstr_mode);
	if (null != hfile->m_hfile)
	{
		hfile->m_file_size = pfx_get_file_size(hfile);
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_FAIL;
	}
	
}

pfx_result_t pfx_close_file(pfx_file_t* PARAM_INOUT hfile)
{
	int status;
	if (null == hfile)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	status = fclose((FILE*)(hfile->m_hfile));
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

pfx_result_t pfx_seek_file(pfx_file_t* PARAM_INOUT hfile,pfx_long_t offset,pfx_sint_t origin)
{
	pfx_result_t status;
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

pfx_result_t pfx_file_printf(pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...)
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

pfx_sint_t	pfx_test_file_eof(pfx_file_t* PARAM_INOUT hfile)
{
	RETURN_INVALID_RESULT( (null == hfile),0);
	return feof((FILE*)hfile->m_hfile);
}

size_t pfx_file_read(pfx_file_t* PARAM_INOUT hfile,pfx_file_data_buffer_t* PARAM_INOUT pbuffer)
{
	RETURN_INVALID_RESULT( (null == hfile || null == hfile->m_hfile || 
		null == pbuffer || null == pbuffer->m_pitems_buffer || 
		0 == pbuffer->m_item_size || 0 == pbuffer->m_items_count),0);

	return fread(pbuffer->m_pitems_buffer,pbuffer->m_item_size,pbuffer->m_items_count,(FILE*)hfile->m_hfile);
}

size_t pfx_file_write(pfx_file_t* PARAM_INOUT hfile,pfx_file_data_buffer_t* PARAM_INOUT pbuffer)
{
	RETURN_INVALID_RESULT( (null == hfile || null == hfile->m_hfile || 
		null == pbuffer || null == pbuffer->m_pitems_buffer || 
		0 == pbuffer->m_item_size || 0 == pbuffer->m_items_count),0);

	return fwrite(pbuffer->m_pitems_buffer,pbuffer->m_item_size,pbuffer->m_items_count,(FILE*)hfile->m_hfile);
}

pfx_sint_t pfx_test_file_error(pfx_file_t* PARAM_INOUT hfile)
{
	RETURN_INVALID_RESULT( (null == hfile),0);
	return ferror((FILE*)hfile->m_hfile);
}

size_t pfx_get_file_size(pfx_file_t* PARAM_INOUT hfile)
{
	long file_pos_;
	RETURN_INVALID_RESULT( (null == hfile || 0 == hfile->m_hfile),0);
	file_pos_ = ftell((FILE*)hfile->m_hfile);
	fseek((FILE*)hfile->m_hfile,0,SEEK_END);
	hfile->m_file_size = ftell((FILE*)hfile->m_hfile);
	fseek((FILE*)hfile->m_hfile,file_pos_,SEEK_SET);
	return hfile->m_file_size;
}

pfx_sint_t pfx_file_flush(pfx_file_t* PARAM_INOUT hfile)
{
	RETURN_INVALID_RESULT( (null == hfile || 0 == hfile->m_hfile),EOF);
	return fflush((FILE*)hfile->m_hfile);
}


pfx_nsize_t pfx_file_get_string_a (pfx_file_t* PARAM_INOUT hfile,
	pfx_char_t* PARAM_INOUT pbuffer,
	pfx_usize_t nread_buffer_size)
{
	pfx_char_t* file_data = null;
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

pfx_nsize_t pfx_file_set_string_a (pfx_file_t* PARAM_INOUT hfile,
	pfx_char_t* PARAM_INOUT pbuffer,
	pfx_usize_t nread_buffer_size)
{
	pfx_nsize_t write_size = 0;
	pfx_nsize_t temp_size = 0;
	pfx_char_t	temp_char;
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
static pfx_cstring < pfx_char_t, pecker_value_compare < pfx_char_t > > gstr_path;

pfx_result_t	pfx_cfile::set_install_apkfile_path (const pfx_char_t* str_path_ptr,pfx_nsize_t path_length)
{
	pfx_result_t status;
	status = gstr_path.init_string(str_path_ptr,path_length+1);
	if (PFX_STATUS_OK == status)
	{
		pfx_char_t null_char = 0;
		status = gstr_path.set_charbuffer_at (path_length,&null_char,1);
	}
	return status;
}
const pfx_char_t*	pfx_cfile::get_install_apkfile_path (pfx_nsize_t& path_length)
{
	pfx_nsize_t string_len = gstr_path.get_length();
	path_length = (string_len > 0) ? (string_len -1):0;
	return gstr_path.get_string ();
}
pfx_handle_t	pfx_cfile::get_private_apkfile_manager ()
{
	return null;
}
pfx_result_t pfx_cfile::is_file_exists (const pfx_char_t* pstr_path,pfx_nsize_t path_length)
{
	return pfx_check_file_exists (pstr_path);
}
pfx_flag_t pfx_cfile::get_file_rw_mode (const pfx_char_t* pstr_path,pfx_nsize_t path_length)
{
	pfx_flag_t rw_mode = 0;
	if(0 == access(pstr_path,0))
	{
		rw_mode |= PF_FILE_EXISTS;
	}
	if(0 == access(pstr_path,2))
	{
		rw_mode |= PF_FILE_READ_ONLY;
	}
	if(0 == access(pstr_path,4))
	{
		rw_mode |= PF_FILE_WRITE_ONLY;
	}
	if(0 == access(pstr_path,6))
	{
		rw_mode |= PF_FILE_RW;
	}
	return rw_mode;
}


pfx_cfile::pfx_cfile()
{
	m_file.m_hfile = null;
	m_file.m_file_size = 0;
}

pfx_cfile::~pfx_cfile()
{
	close ();
}

pfx_result_t pfx_cfile::open(const pfx_char_t* pstr_path,pfx_nsize_t path_length, pfx_flag_t nOpenType)
{
	RETURN_INVALID_RESULT (null != m_file.m_hfile,PFX_STATUS_OPENED);

	char str_open_type[20] = "r";
	int string_length = 1;
	if(nOpenType & (PFO_OPEN_CREATE | PFO_OPEN_WRITE | PFO_OPEN_READ))
	{
		string_length = sprintf(str_open_type,"a+");
	}
	else if(nOpenType & (PFO_OPEN_CREATE | PFO_OPEN_WRITE))
	{
		string_length = sprintf(str_open_type,"a");
	}
	else if(nOpenType & (PFO_OPEN_READ | PFO_OPEN_WRITE))
	{
		string_length = sprintf(str_open_type,"w+");
	}
	else if(nOpenType & PFO_OPEN_WRITE)
	{
		string_length = sprintf(str_open_type,"w");
		//string_length = 1;
	}

	if(nOpenType | PFO_OPEN_BINARY)
	{
		sprintf(str_open_type+string_length,"b");
	}

	if(nOpenType | PFO_OPEN_TEXT)
	{
		sprintf(str_open_type+string_length,"t");
	}

	pfx_result_t result_val;
	result_val = pfx_open_file(&m_file,pstr_path,str_open_type);
	if (PFX_STATUS_OK == result_val)
	{
		pfx_seek_file(&m_file,0,PFX_FILE_SEEK_SET);
	}
	return result_val;
}

pfx_result_t pfx_cfile::close()
{
	RETURN_RESULT (null == m_file.m_hfile || 0 == m_file.m_file_size,PFX_STATUS_OK);
	pfx_result_t result_val;
	result_val = pfx_close_file(&m_file);
	if (PFX_STATUS_OK == result_val)
	{
		m_file.m_hfile = null;
		m_file.m_file_size = 0;
	}
	return result_val;
}

pfx_result_t pfx_cfile::read_to_memery (pfx_byte_t* PARAM_INOUT memery_buffer_ptr, 
	pfx_usize_t memery_buffer_size, 
	pfx_usize_t& PARAM_INOUT read_buffer_size)
{
	pfx_result_t error_code_s;
	RETURN_INVALID_RESULT (null == memery_buffer_ptr || 0 == memery_buffer_size,PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT (null == m_file.m_file_size || 0 == m_file.m_file_size,PFX_STATUS_CLOSED);
	read_buffer_size = fread (memery_buffer_ptr,sizeof (pfx_byte_t),memery_buffer_size,(FILE*)m_file.m_hfile);
	if (read_buffer_size > 0)
	{
		error_code_s = PFX_STATUS_OK;
	}
	else
	{
		error_code_s = PFX_STATUS_FIN;
	}
	return error_code_s;

}

pfx_usize_t pfx_cfile::write_to_file (const pfx_byte_t* memery_buffer_ptr, pfx_usize_t memery_buffer_size,
	pfx_result_t& PARAM_INOUT error_code_s)
{
	RETURN_INVALID_RESULT (null == memery_buffer_ptr || 0 == memery_buffer_size,PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT (null == m_file.m_file_size || 0 == m_file.m_file_size,PFX_STATUS_CLOSED);
	memery_buffer_size = fwrite (memery_buffer_ptr,
		sizeof (pfx_byte_t),memery_buffer_size/sizeof(pfx_byte_t), (FILE*)m_file.m_hfile);
	error_code_s = PFX_STATUS_OK;

	return memery_buffer_size;
}

pfx_result_t pfx_cfile::seek(pfx_long_t offset,pfx_sint_t origin)
{
	RETURN_INVALID_RESULT (null == m_file.m_file_size || 0 == m_file.m_file_size,PFX_STATUS_CLOSED);
	return pfx_seek_file (&m_file,offset,origin);
}

pfx_nsize_t pfx_cfile::get_file_size()
{
	return pfx_get_file_size(&m_file);
}

pfx_sint_t	pfx_cfile::eof ()
{
	return pfx_test_file_eof(&m_file);
}
pfx_sint_t pfx_cfile::test_error ()
{
	return pfx_test_file_error (&m_file);
}

pfx_sint_t pfx_cfile::fflush()
{
	return pfx_file_flush (&m_file);
}

PECKER_END



