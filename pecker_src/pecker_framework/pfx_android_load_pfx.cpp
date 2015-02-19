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
result_t candroid_application::init (ANativeActivity* activity)
{
	cstring_ascii_t str_value;
	android_native_form::get_meta_data_value (activity,
					"working_lib_in_apk",
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
									"working_lib_name",
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
									"working_lib_name",
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
	m_handle = dlopen(dl_name, flag);

	PECKER_LOG_INFO("dlopen - %sn", dlerror());
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
android_native_form::PFX_main_callback candroid_application::enter_point()
{
	android_native_form::PFX_main_callback main_fuc = null;
	if (m_working_lib_name.get_length() && m_handle)
	{
		main_fuc = (android_native_form::PFX_main_callback)
				dlsym(m_handle, "PFX_main");

		PECKER_LOG_INFO("main_fuc - %p", main_fuc);
	}
	return main_fuc;

}

const char* candroid_application::get_working_lib_path () const
{
	return m_working_lib_name.get_string();
}

PECKER_END

#if defined(SLAVE_LIB)

#else
//extern int PFX_main(pecker_sdk::android_native_form* PARAM_INOUT main_form);
static pecker_sdk::candroid_application gandorid_app;
void ANativeActivity_onCreate(ANativeActivity* activity,
	void* savedState, size_t savedStateSize)
{
	__android_log_print(ANDROID_LOG_INFO,
						__func__,
						"%p, %p, %d",
						activity,
						savedState,
						savedStateSize);

//	pecker_sdk::cstring_ascii_t str_value;
//	pecker_sdk::android_native_form::get_meta_data_value (activity,
//				"working_lib_name",
//				str_value);
//	pecker_sdk::android_native_form::get_app_path (activity,
//					str_value);
//	pecker_sdk::android_native_form::get_user_package_name (activity,
//						str_value);
	gandorid_app.init(activity);
	gandorid_app.load_working_lib(gandorid_app.get_working_lib_path(),RTLD_NOW);

	pecker_sdk::android_native_form::PFX_main_callback main_fuc = gandorid_app.enter_point();
	//pecker_sdk::android_native_form::PFX_main_callback main_fuc = PFX_main;
	if (main_fuc)
	{
		pecker_sdk::android_native_form::app_main(main_fuc, activity, savedState, savedStateSize);
	}

}
#endif





