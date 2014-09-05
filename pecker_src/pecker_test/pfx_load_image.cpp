/*
 * pfx_file_inputdata_cmd.cpp
 *
 *  Created on: 2013-9-29
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../pecker_framework/native/pfx_file_io.h"
#include "../pecker_framework/render/pfx_image_png.h"
#include "../pecker_framework/native/pfx_resource_reader.h"
#include "../pecker_framework/native/pfx_log.h"

//#define TEST_ASET_RESOURCE

USING_PECKER_SDK
result_t load_png_img(const char_t* pfile_name, cImage& __img)
{
	cPng_Image_reader __img_reader;
	sasset_reader_t* asset_file_ptr;
	asset_file_ptr = sasset_reader_t::create_new_object();
	

	sresource_reader_t* res_file_ptr;
	res_file_ptr = sresource_reader_t::create_new_object();
	

	casset_reader_t* aset_reader_ptr = asset_file_ptr->native_ptr();
	cresource_reader_t* res_reader_ptr = res_file_ptr->native_ptr();


	if (!aset_reader_ptr || !res_reader_ptr)
	{
		asset_file_ptr->dispose_object();
		res_file_ptr->dispose_object();
		return PFX_STATUS_MEM_ERR;
	}
	
	__img_reader.attach_asset_reader(asset_file_ptr);
	__img_reader.attach_resource_reader(res_file_ptr);
	asset_file_ptr->dispose_object();
	res_file_ptr->dispose_object();

#if defined(TEST_ASET_RESOURCE)
	__img_reader.select_load_form_asset_reader(pfile_name);
#else
	__img_reader.select_load_form_resource_reader(pfile_name);
#endif
	cstring_ascii_t str_app_path;
	cresource_reader_t::get_application_path(str_app_path);
	PECKER_LOG_INFO("%s", str_app_path.get_string());

	//hfile.set_resource_dir_path("..\\PFX_framework\\assets\\");
	//hfile.set_resource_dir_path("C:\\codes\\git\\pecker_framework\\pecker_framework_c\\pecker_src\\PFX_framework\\assets\\");
	//hfile.set_resource_dir_path("C:\\");
	//hfile.set_resource_dir_path("..\\");
#if (OS_CONFIG == OS_WINDOWS)
	aset_reader_ptr->set_resource_dir_path("..\\PFX_framework\\assets\\");
	res_reader_ptr->set_resource_dir_path("..\\PFX_framework\\assets\\");
#endif //#if (OS_CONFIG == OS_WINDOWS)
#if (OS_CONFIG == OS_ANDROID) && !defined(TEST_ASET_RESOURCE)
	res_reader_ptr->set_resource_dir_path("/sdcard/");
#endif // #if (OS_CONFIG == OS_ANDROID)



	return __img.load_image(&__img_reader);

}
result_t load_img(const char_t* pfile_name,image_data_t& __img)
{
//	return load_png_image_from_file(__img, pfile_name);

	//pecker_file hfile;
	result_t status = PFX_STATUS_OK;
#if defined(TEST_ASET_RESOURCE)
	casset_reader_t hfile;
#else
	cresource_reader_t hfile;
#endif
	cstring_ascii_t str_app_path;
	cresource_reader_t::get_application_path(str_app_path);
	PECKER_LOG_INFO("%s", str_app_path.get_string());

	//hfile.set_resource_dir_path("..\\PFX_framework\\assets\\");
	//hfile.set_resource_dir_path("C:\\codes\\git\\pecker_framework\\pecker_framework_c\\pecker_src\\PFX_framework\\assets\\");
	//hfile.set_resource_dir_path("C:\\");
	//hfile.set_resource_dir_path("..\\");
#if (OS_CONFIG == OS_WINDOWS)
	hfile.set_resource_dir_path("..\\PFX_framework\\assets\\");
#endif //#if (OS_CONFIG == OS_WINDOWS)
#if (OS_CONFIG == OS_ANDROID) && !defined(TEST_ASET_RESOURCE)
	hfile.set_resource_dir_path("/sdcard/");
#endif // #if (OS_CONFIG == OS_ANDROID)

	status = hfile.open_resource(pfile_name);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status), status);
	usize__t file_size = hfile.get_size();


	//RETURN_INVALID_RESULT((null == pfile_name),PFX_STATUS_INVALID_PARAMS);

	//status = hfile.is_file_exists(pfile_name);
	//RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);
	//status = hfile.open(pfile_name, PFO_OPEN_READ | PFO_OPEN_BINARY);
	//RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);
	//usize__t file_size = hfile.get_readonly_file_size();//.get_file_size();

	byte_t* read_buffer_ptr = new byte_t[file_size];

	if (!read_buffer_ptr)
	{
		return PFX_STATUS_MEM_LOW;
	}

	//load_png_image_from_STDIO(__img, hfile);

	usize__t read_size = file_size;
	status = hfile.read_to_memery(read_buffer_ptr, read_size);

	if (PFX_STATUS_OK != status)
	{
		return status;
	}

	load_png_image_from_memory(__img, read_buffer_ptr, read_size);

	if (read_buffer_ptr)
	{
		delete[] read_buffer_ptr;
		read_buffer_ptr = null;
	}

	hfile.close();
	return status;
}
