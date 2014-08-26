/*
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

#if (OS_CONFIG == OS_WINDOWS)

PECKER_BEGIN

class PFX_NATIVE_API cresource_reader_windows
{
private:
	cstring_ascii_t m_root_dir_path;
	pecker_file m_hfile;
public:
	static	result_t get_application_path(cstring_ascii_t& PARAM_OUT str_app_path);
public:
	cresource_reader_windows();
	virtual ~cresource_reader_windows();

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

typedef cresource_reader_windows casset_reader_windows;
typedef simple_reference< cresource_reader_windows >::sref_node cresource_share_reader_windows_t;
typedef simple_reference< casset_reader_windows >::sref_node casset_share_reader_windows_t;

PECKER_END
#endif	 // #if (OS_CONFIG == OS_WINDOWS)


#endif			//PFX_RESOURCE_READER_WINDOWS_H_
