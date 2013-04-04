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

#ifdef ANDROID_OS
#include <unistd.h>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#else
#ifdef WINDOWS_PC
#include <io.h>

#endif
#endif






PECKER_BEGIN

#define MAX_FILE_PATH_LENGTH 512
static Char gstr_install_apkfile_path[MAX_FILE_PATH_LENGTH] = "";
static nSize gn_install_apkfile_path_length = 0;
ConstStringChars gconststr_install_apkfile_path = {gstr_install_apkfile_path,gn_install_apkfile_path_length};

HResult pecker_file_io_base::set_install_apkfile_path(const Char* pstr_path,nSize path_length)
{
	if (path_length > MAX_FILE_PATH_LENGTH)
	{
		return P_FAIL;
	}
	memcpy(gstr_install_apkfile_path,pstr_path,path_length);
	return P_OK;
}

const ConstStringChars& pecker_file_io_base::get_install_apkfile_path()
{
	return gconststr_install_apkfile_path;
}

Handle pecker_file_io_base::get_private_apkfile_manager()
{
	return null;
}

Boolean  pecker_file_io_base::is_file_exists(const Char* pstr_path,nSize path_length)
{
	if( null != pstr_path && 0 == access(pstr_path,0))
	{
		return BOOL_TRUE;
	}
	return BOOL_FALSE;
}

HFlag  pecker_file_io_base::get_file_rw_mode(const Char* pstr_path,nSize path_length)
{
	HFlag retnFlag = 0;
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

HResult pecker_file_io_base::open(const Char* pstr_path,nSize path_length, HFlag nOpenType)
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
			memery_buffer._M_buffer_size =  fread(memery_buffer._M_buffer, sizeof(Char), memery_buffer._M_buffer_size, (FILE*)_M_hFile);
		}
	}
	else
	{
		memery_buffer._M_buffer_size = 0;
	}
	return memery_buffer;
}

nSize pecker_file_io_base::write_to_file(const ConstBytes& memery_buffer,UInt origin /* = FILE_SEEK_SET */,Long offset /* = 0 */)
{
	if (null != _M_hFile && null != memery_buffer._M_buffer && memery_buffer._M_buffer_size > 0)
	{
		if( 0 == fseek((FILE*)_M_hFile, offset , origin))
		{
			 return  fwrite(memery_buffer._M_buffer, sizeof(Char), memery_buffer._M_buffer_size, (FILE*)_M_hFile);
		}
	}
	return (-1);
}

nSize pecker_file_io_base::get_file_size()
{
	if (null == _M_hFile)
	{
		return 0;
	}
	long current_pos = ftell((FILE*)_M_hFile);
	fseek((FILE*)_M_hFile, 0, SEEK_END);
	long end_pos = ftell((FILE*)_M_hFile);
	fseek((FILE*)_M_hFile, current_pos, SEEK_SET);
	return (nSize)end_pos;
}

HResult pecker_file_io_base::close()
{
	if(null == _M_hFile || 0 == fclose((FILE*)_M_hFile))
	{
		_M_hFile = null;
		return P_OK;
	}
	else
	{
		return P_FAIL;
	}
}

PECKER_END
