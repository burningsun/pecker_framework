﻿/*
 * pfx_resource_reader_windows.cpp
 *
 *  Created on: 2014-8-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_resource_reader_android.h"
#include "pfx_log.h"
#if (OS_CONFIG == OS_ANDROID)
#include "android_native_form.h"
PECKER_BEGIN

cresource_reader_android::cresource_reader_android()
{
}

cresource_reader_android::~cresource_reader_android()
{
	close ();
}


result_t cresource_reader_android::get_application_path(cstring_ascii_t& PARAM_OUT str_app_path)
{
	str_app_path.init_string(1024);

	const cstring_ascii_t& str_path = android_native_form::get_app_path();

	str_app_path.init_string(str_path.get_length()+1);
	str_app_path.resize_string(0);
	str_app_path.append_string(str_path);

	if (str_app_path.get_length() > 0)
	{
		str_app_path.append_string("\0",1);
		str_app_path.resize_string(str_path.get_length());
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_FAIL;
	}
}


result_t cresource_reader_android::set_resource_dir_path(const char_t* PARAM_IN str_dir_path)
{
	result_t status;
	status = PFX_STATUS_OK;
	// 默认情况下取程序路径
	if (null == str_dir_path)
	{
		status = get_application_path(m_root_dir_path);
		if (status)
		{
			m_root_dir_path.clean();
			return status;
		}
	}

	usize__t str_dir_path_len = strlen(str_dir_path);
	const usize__t dir_str_len = strlen("../");
	const usize__t root_str_len = strlen("/");
	const usize__t dir_str_len2 = strlen("/");

	int cmp1 = 0;
	int cmp2 = 0;
	int cmp3 = 0;

	cmp1 = memcmp((str_dir_path + str_dir_path_len - dir_str_len2),
		"/",
		dir_str_len2);
	cmp2 = memcmp("../", str_dir_path, dir_str_len);

	if (str_dir_path_len >= dir_str_len2 &&
		0 == cmp1 &&
		(!(0 == cmp2 &&
		str_dir_path_len <= dir_str_len)  //&& //不能是首个相对路径的"\\"
		)

		)
		//去掉最后一个"\\"
	{
		str_dir_path_len -= dir_str_len2;
	}

	if (str_dir_path_len >= root_str_len &&
		0 == memcmp(str_dir_path, "/", strlen("/"))	// 绝对路径处理
		)
	{
		m_root_dir_path.init_string(str_dir_path, str_dir_path_len+1);
		m_root_dir_path.resize_string(str_dir_path_len);
	}
	else // 相对路径处理
	{
		status = get_application_path(m_root_dir_path);
		if (status)
		{
			m_root_dir_path.clean();
			return status;
		}

		//bool bresize = false;
		while (str_dir_path_len >= dir_str_len &&
			0 == memcmp("../", str_dir_path, dir_str_len))
		{
			char_t* chr_app_path_ptr = m_root_dir_path.get_string();
			usize__t str_len = strlen(chr_app_path_ptr);
			for (int i = str_len; i > 0; --i)
			{
				if ('/' == chr_app_path_ptr[i])
				{
					chr_app_path_ptr[i] = 0;
					m_root_dir_path.resize_string(i);
					//bresize = true;
					break;
				}
			}
			str_dir_path += dir_str_len;
			str_dir_path_len -= dir_str_len;

		};

		if (str_dir_path_len)
		{
			m_root_dir_path.append_string("/", strlen("/"));
			m_root_dir_path.append_string(str_dir_path, str_dir_path_len);
			m_root_dir_path.append_string("\0", 1);
			m_root_dir_path.resize_string(m_root_dir_path.get_length() - 1);
		}

	}


	return status;
}
result_t cresource_reader_android::open_resource(const char_t* PARAM_IN str_resource_path)
{
	RETURN_INVALID_RESULT(!str_resource_path, PFX_STATUS_INVALID_PARAMS);

	result_t status;
	status = PFX_STATUS_OK;
	usize__t str_res_path_size;


	const usize__t dir_str_len = strlen("../");
	const usize__t root_str_len = strlen("/");
	const usize__t dir_str_len2 = strlen("/");
	str_res_path_size = strlen(str_resource_path);

	RETURN_INVALID_RESULT(!str_res_path_size, PFX_STATUS_INVALID_PARAMS);

	if (m_hfile.get_handle()->m_hfile)
	{
		close ();
	}

	if (str_res_path_size >= root_str_len &&
		0 == memcmp(str_resource_path, "/", strlen("/"))	// 绝对路径处理
		)
	{
		status = m_hfile.open(str_resource_path, PFO_OPEN_READ | PFO_OPEN_BINARY);
	}
	else
	{
		if (0 == m_root_dir_path.get_length())
		{
			status = get_application_path(m_root_dir_path);
			if (status)
			{
				return status;
			}
		}
		cstring_ascii_t str_file_path;
		str_file_path.init_string(m_root_dir_path.get_length() + dir_str_len2 + str_res_path_size + 1);
		str_file_path.resize_string(0);
		str_file_path.append_string(m_root_dir_path);
		str_file_path.resize_string(m_root_dir_path.get_length());
		str_file_path.append_string("/", dir_str_len2);
		str_file_path.append_string(str_resource_path, str_res_path_size);
		str_file_path.append_string("\0", 1);
		status = m_hfile.open(str_file_path.get_string(), PFO_OPEN_READ | PFO_OPEN_BINARY);
	}


	return status;
}
result_t cresource_reader_android::seek(long_t offset, sint_t origin)
{
	result_t status;
	status = m_hfile.seek(offset, origin);
	return status;
}
result_t cresource_reader_android::read_to_memery(byte_t* PARAM_INOUT memery_buffer_ptr,
	usize__t& PARAM_INOUT memery_buffer_size)
{
	result_t status;
	status = m_hfile.read_to_memery(memery_buffer_ptr, memery_buffer_size);
	return status;
}
usize__t cresource_reader_android::get_size() const
{
	return m_hfile.get_readonly_file_size();
}
result_t cresource_reader_android::close()
{
	result_t status;
	status = m_hfile.close();
	return status;
}



struct AAssetManager* casset_reader_android::get_app_assertsManager ()
{
	return android_native_form::get_app_assertManager();
}

casset_reader_android::casset_reader_android ():m_assettfile(null)
{
	;
}

casset_reader_android::~casset_reader_android()
{
	close ();
}

result_t casset_reader_android::open_resource(const char_t* PARAM_IN str_resource_path)
{
	if (m_assettfile)
	{
		close();
	}
	m_assettfile = AAssetManager_open(get_app_assertsManager(),str_resource_path,AASSET_MODE_BUFFER);
	if (m_assettfile)
	{
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_FAIL;
	}
}

result_t casset_reader_android::seek(long_t offset, sint_t origin)
{
	RETURN_INVALID_RESULT((!m_assettfile), PFX_STATUS_UNINIT);
	off_t pos = AAsset_seek(m_assettfile,offset,origin);
	if (pos < 0)
	{
		return PFX_STATUS_FAIL;
	}
	else
	{
		return PFX_STATUS_OK;
	}
}

result_t casset_reader_android::read_to_memery(byte_t* PARAM_INOUT memery_buffer_ptr,
		usize__t& PARAM_INOUT memery_buffer_size)
{
	RETURN_INVALID_RESULT((!m_assettfile), PFX_STATUS_UNINIT);

	int read_size = AAsset_read(m_assettfile, memery_buffer_ptr, memery_buffer_size);
	if (read_size < 0)
	{
		memery_buffer_size = 0;
		return PFX_STATUS_FAIL;
	}
	else
	{
		memery_buffer_size = read_size;
		return PFX_STATUS_OK;
	}
}

usize__t casset_reader_android::get_size() const
{
	RETURN_INVALID_RESULT((!m_assettfile), 0);
	return AAsset_getLength(m_assettfile);
}

result_t casset_reader_android::close()
{
	RETURN_RESULT((!m_assettfile), PFX_STATUS_OK);
	AAsset_close(m_assettfile);
	m_assettfile = null;
	return PFX_STATUS_OK;
}

PECKER_END

#endif // #if (OS_CONFIG == OS_WINDOWS)

