/*
 * pfx_file_io.cpp
 *
 *  Created on: 2013-9-27
 *      Author: 李镇城 (cut / cutxyz)
 */

#include "pfx_file_io.h"
#include <io.h>
#include <errno.h>
#include <stdio.h>

PFX_C_EXTERN_BEGIN

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

//extern int vfscanf(FILE *stream, const char *format, va_list param);

pfx_result_t pfx_file_scanf(pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...)
{
	va_list args_ptr;
	va_start(args_ptr,str_format);
	//fscanf ((FILE*)hfile->m_hfile,str_format,args_ptr);
	//vfscanf ((FILE*)hfile->m_hfile,str_format,args_ptr);
	//_IO_vfscanf (stdin, format, arg, NULL); 
	va_end(args_ptr);
	return PFX_STATUS_OK;

}

pfx_result_t pfx_file_printf(pfx_file_t* PARAM_INOUT hfile,const pfx_char_t* PARAM_IN str_format,...)
{
	va_list args_ptr;
	va_start(args_ptr,str_format);
	vfprintf((FILE*)hfile->m_hfile,str_format,args_ptr);
	//_IO_vfscanf (stdin, format, arg, NULL); 
	va_end(args_ptr);
	return PFX_STATUS_OK;
}

pfx_result_t pfx_file_wscanf(pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);

pfx_result_t pfx_file_wprintf(pfx_file_t* PARAM_INOUT hfile,const pfx_wchar_t* PARAM_IN str_format,...);

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

PFX_C_EXTERN_END
