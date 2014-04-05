/*
 * pecker_file_io.cpp
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_file_io.h"

#include <stdlib.h>
#include <stdio.h>

#if (OS_CONFIG == OS_ANDROID)
#include <unistd.h>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#else
#if (OS_CONFIG == OS_WINDOWS)
#include <io.h>

#endif
#endif






PECKER_BEGIN

#define MAX_FILE_PATH_LENGTH 512
static pfx_char_t gstr_install_apkfile_path[MAX_FILE_PATH_LENGTH] = "";
static pfx_nsize_t gn_install_apkfile_path_length = 0;
const_string_chars gconststr_install_apkfile_path = {gstr_install_apkfile_path,gn_install_apkfile_path_length};

pfx_result_t pecker_file_io_base::set_install_apkfile_path(const pfx_char_t* pstr_path,pfx_nsize_t path_length)
{
	if (path_length > MAX_FILE_PATH_LENGTH)
	{
		return PEK_STATUS_FAIL;
	}
	memcpy(gstr_install_apkfile_path,pstr_path,path_length);
	return PEK_STATUS_OK;
}

const const_string_chars& pecker_file_io_base::get_install_apkfile_path()
{
	return gconststr_install_apkfile_path;
}

HANDLE pecker_file_io_base::get_private_apkfile_manager()
{
	return null;
}

pfx_boolean_t  pecker_file_io_base::is_file_exists(const pfx_char_t* pstr_path,pfx_nsize_t path_length)
{
	if( null != pstr_path && 0 == access(pstr_path,0))
	{
		return BOOL_TRUE;
	}
	return BOOL_FALSE;
}

pfx_flag_t  pecker_file_io_base::get_file_rw_mode(const pfx_char_t* pstr_path,pfx_nsize_t path_length)
{
	pfx_flag_t retnFlag = 0;
	if(0 == access(pstr_path,0))
	{
		retnFlag |= PF_FILE_EXISTS;
	}
	if(0 == access(pstr_path,1))
	{
		retnFlag |= PF_FILE_READ_ONLY;
	}
	if(0 == access(pstr_path,2))
	{
		retnFlag |= PF_FILE_WRITE_ONLY;
	}
	if(0 == access(pstr_path,4))
	{
		retnFlag |= PF_FILE_RW;
	}
	return retnFlag;
}

pecker_file_io_base::pecker_file_io_base() : _M_hFile(null)
{

}

pecker_file_io_base::~pecker_file_io_base()
{
	if (null != _M_hFile)
	{
		close();
	}
}

pfx_result_t pecker_file_io_base::open(const pfx_char_t* pstr_path,pfx_nsize_t path_length, pfx_flag_t nOpenType)
{
		if(null == pstr_path)
			return PRST_FAIL;
	
		if(null != _M_hFile)
			return PRST_OPENS;
	
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
			string_length = 1;
		}
	
		if(nOpenType | PFO_OPEN_BINARY)
		{
			sprintf(str_open_type+string_length,"b");
		}
	
		if(nOpenType | PFO_OPEN_TEXT)
		{
			sprintf(str_open_type+string_length,"t");
		}
	
		FILE* hFile = fopen(pstr_path,str_open_type);
		if(hFile)
		{
			_M_hFile = hFile;
			fseek(hFile, 0, SEEK_SET);
			return PRST_OK;
		}
		else
		{
			return PRST_OK;
		}
}
Bytes& pecker_file_io_base::read_to_memery(Bytes& memery_buffer,UInt origin /* = 0 */,Long offset /* = 0 */)
{
	if (null != _M_hFile && null != memery_buffer._M_buffer && memery_buffer._M_buffer_size > 0)
	{
		if( 0 == fseek((FILE*)_M_hFile, offset , origin))
		{
			memery_buffer._M_buffer_size =  fread(memery_buffer._M_buffer, sizeof(pfx_char_t), memery_buffer._M_buffer_size, (FILE*)_M_hFile);
		}
	}
	else
	{
		memery_buffer._M_buffer_size = 0;
	}
	return memery_buffer;
}

pfx_nsize_t pecker_file_io_base::write_to_file(const const_bytes& memery_buffer,UInt origin /* = FILE_SEEK_SET */,Long offset /* = 0 */)
{
	if (null != _M_hFile && null != memery_buffer._M_buffer && memery_buffer._M_buffer_size > 0)
	{
		if( 0 == fseek((FILE*)_M_hFile, offset , origin))
		{
			 return  fwrite(memery_buffer._M_buffer, sizeof(pfx_char_t), memery_buffer._M_buffer_size, (FILE*)_M_hFile);
		}
	}
	return (-1);
}

pfx_nsize_t pecker_file_io_base::get_file_size()
{
	if (null == _M_hFile)
	{
		return 0;
	}
	long current_pos = ftell((FILE*)_M_hFile);
	fseek((FILE*)_M_hFile, 0, SEEK_END);
	long end_pos = ftell((FILE*)_M_hFile);
	fseek((FILE*)_M_hFile, current_pos, SEEK_SET);
	return (pfx_nsize_t)end_pos;
}

pfx_result_t pecker_file_io_base::close()
{
	if(null == _M_hFile || 0 == fclose((FILE*)_M_hFile))
	{
		_M_hFile = null;
		return PEK_STATUS_OK;
	}
	else
	{
		return PEK_STATUS_FAIL;
	}
}

PECKER_END
