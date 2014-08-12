/*
 * pfx_file_inputdata_cmd.cpp
 *
 *  Created on: 2013-9-29
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../pecker_framework/native/pfx_file_io.h"
#include "../pecker_framework/render/pfx_image_png.h"

USING_PECKER_SDK

result_t load_img(const char_t* pfile_name,image_data_t& __img)
{
	pecker_file hfile;
	result_t status = PFX_STATUS_OK;


	RETURN_INVALID_RESULT((null == pfile_name),PFX_STATUS_INVALID_PARAMS);

	status = hfile.is_file_exists(pfile_name, strlen(pfile_name));
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);
	status = hfile.open(pfile_name, strlen(pfile_name), PFO_OPEN_READ | PFO_OPEN_BINARY);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);
	usize__t file_size = hfile.get_file_size();

	byte_t* read_buffer_ptr = new byte_t[file_size];

	if (!read_buffer_ptr)
	{
		return PFX_STATUS_MEM_LOW;
	}

	usize__t read_size = 0;
	status = hfile.read_to_memery(read_buffer_ptr, file_size, read_size);

	if (PFX_STATUS_OK != status)
	{
		return status;
	}

	load_png_image_from_memery(__img, read_buffer_ptr, read_size);

	if (read_buffer_ptr)
	{
		delete[] read_buffer_ptr;
		read_buffer_ptr = null;
	}

	return status;
}