﻿/*
 * pfx_resource_reader_windows.h
 *
 *  Created on: 2014-8-10
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RESOURCE_READER_WINDOWS_H_
#define		PFX_RESOURCE_READER_WINDOWS_H_

#include "../pfx_defines.h"
#include "pfx_file_io.h"
#include "../include/cstring_pfx.h"
#include "../data/pfx_ref_root.h"

#if (OS_CONFIG == OS_ANDROID)

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

PECKER_BEGIN

class cresource_reader_android
{
private:
	cstring_ascii_t m_root_dir_path;
	pecker_file m_hfile;
public:
	static result_t get_application_path(cstring_ascii_t& PARAM_OUT str_app_path);
public:
	cresource_reader_android();
	virtual ~cresource_reader_android();

	result_t set_resource_dir_path(const char_t* PARAM_IN str_dir_path);
	result_t open_resource(const char_t* PARAM_IN str_resource_path);
	result_t seek(long_t offset, sint_t origin);
	result_t read_to_memery(byte_t* PARAM_INOUT memery_buffer_ptr,
			usize__t& PARAM_INOUT memery_buffer_size);
	usize__t get_size() const;
	result_t close();
public:
	PFX_INLINE pecker_file& get_file_handle()
	{
		return m_hfile;
	}

};

class casset_reader_android
{
private:
	struct AAsset* m_assettfile;
protected:
	static struct AAssetManager* get_app_assertsManager ();
public:
	casset_reader_android ();
	virtual ~casset_reader_android();

	result_t open_resource(const char_t* PARAM_IN str_resource_path);
	result_t seek(long_t offset, sint_t origin);
	result_t read_to_memery(byte_t* PARAM_INOUT memery_buffer_ptr,
			usize__t& PARAM_INOUT memery_buffer_size);
	usize__t get_size() const;
	result_t close();
};

//typedef simple_reference< cresource_reader_android >::sref_node sresource_reader_android_t;
//typedef simple_reference< casset_reader_android >::sref_node sasset_reader_android_t;
//typedef simple_reference_object< cresource_reader_android > sresource_reader_android_t;
//typedef simple_reference_object< casset_reader_android >    sasset_reader_android_t;

typedef simple_ref< cresource_reader_android > sresource_reader_android_t;
typedef simple_ref< casset_reader_android > sasset_reader_android_t;


PECKER_END
#endif	 // #if (OS_CONFIG == OS_WINDOWS)

#endif			//PFX_RESOURCE_READER_WINDOWS_H_
