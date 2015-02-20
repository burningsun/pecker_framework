/*
 * pfx_android_load_pfx.cpp
 *
 *  Created on: 2015-2-19
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_android_load_pfx.h"



PECKER_BEGIN
candroid_application::candroid_application():m_handle(null)
{
	;
}
candroid_application::~candroid_application()
{
	close_working_lib ();
}
result_t candroid_application::init (ANativeActivity* activity,
		const char* str_check_flag_name,
		const char* str_lib_name)
{
	cstring_ascii_t str_value;
	android_native_form::get_meta_data_value (activity,
			        str_check_flag_name,//"working_lib_in_apk",
					str_value);
	bool _lib_in_apk = false;
	if (0 == str_value.get_length() ||
		0 == ascii_string_compare_withchars_t::compare(str_value,"yes"))
	{
		_lib_in_apk = true;
	}

	if (_lib_in_apk)
	{
		cstring_ascii_t str_value;
		cstring_ascii_t str_package_name;
		android_native_form::get_meta_data_value (activity,
									str_lib_name,//"working_lib_name",
									str_value);
		android_native_form::get_user_package_name (activity,
				                    str_package_name);
		const char* chrfront_ptr = "/data/data/";
		const char* chrmid_ptr = "/lib/lib";
		const char* chrlast_ptr = ".so";

		m_working_lib_name.init_string(
				strlen(chrfront_ptr)+str_package_name.get_length()+
				strlen(chrmid_ptr)+str_value.get_length()+
				strlen(chrlast_ptr)+1);

		m_working_lib_name.resize_string(0);
		m_working_lib_name.append_string(chrfront_ptr, strlen(chrfront_ptr));
		m_working_lib_name.append_string(str_package_name);
		m_working_lib_name.append_string(chrmid_ptr, strlen(chrmid_ptr));
		m_working_lib_name.append_string(str_value);
		m_working_lib_name.append_string(chrlast_ptr, strlen(chrlast_ptr));
		m_working_lib_name.append_string("\0", 1);

	}
	else
	{
		android_native_form::get_meta_data_value (activity,
				                    str_lib_name,//"working_lib_name",
									m_working_lib_name);
	}

	if (m_working_lib_name.get_length())
	{
		PECKER_LOG_STR(m_working_lib_name.get_string());
		return PFX_STATUS_OK;
	}
	else
	{
		PECKER_LOG_STR("null lib name");
		return PFX_STATUS_FAIL;
	}

}
result_t candroid_application::load_working_lib (const char* dl_name, int flag)
{
	if (m_handle)
	{
		close_working_lib ();
	}

	PECKER_LOG_STR(dl_name);
	PECKER_LOG_INFO("before dlopen %p (%s)", m_handle, dlerror());

	m_handle = dlopen(dl_name, flag);

	PECKER_LOG_INFO("after dlopen %p (%s)", m_handle, dlerror());
	if (m_handle)
	{
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}

}
result_t candroid_application::close_working_lib ()
{
	if (m_handle)
	{
		dlclose(m_handle);
		m_handle = null;
	}
	return PFX_STATUS_OK;
}
void* candroid_application::func_addr(const char* str_name)
{
	void* func = null;
	if (m_working_lib_name.get_length() && m_handle)
	{
		func = dlsym(m_handle, str_name);
		PECKER_LOG_INFO("%s - %p",str_name, func);
	}
	return func;

}

const char* candroid_application::get_working_lib_path () const
{
	return m_working_lib_name.get_string();
}

void* candroid_application::handle ()
{
	return m_handle;
}

PECKER_END

#if !defined(PURE_NATIVE_CODE)

#else
// 纯NDK，是附加任何JAR
//extern int PFX_main(pecker_sdk::android_native_form* PARAM_INOUT main_form);
static pecker_sdk::candroid_application gandorid_app;

static int(*gmain_func)(void*) = 0;
static int __PFX_main(pecker_sdk::android_native_form* PARAM_INOUT main_form)
{
	if (gmain_func)
	{
		return gmain_func(main_form);
	}
	else
	{
		return PFX_STATUS_NOT_EXISTS;
	}
}

void ANativeActivity_onCreate(ANativeActivity* activity,
	void* savedState, size_t savedStateSize)
{
	__android_log_print(ANDROID_LOG_INFO,
						__func__,
						"%p, %p, %d",
						activity,
						savedState,
						savedStateSize);

	gandorid_app.init(activity);

	//加载运行的库
	if (null == gandorid_app.handle())
	{
		gandorid_app.load_working_lib(gandorid_app.get_working_lib_path(),RTLD_GLOBAL);
	}

	//获取代码入口
	gmain_func = (int(*)(void*))gandorid_app.func_addr("pecker_program");

	//运行代码
	if (gmain_func)
	{
		pecker_sdk::android_native_form::app_main(__PFX_main, activity, savedState, savedStateSize);
	}
	else
	{
		PECKER_LOG_ERR("get pecker_program() failed (handle = %p)",
				gandorid_app.handle());
	}

}
#endif





