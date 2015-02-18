/*
 * pfx_android_load_pfx.cpp
 *
 *  Created on: 2014-1-31
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <dlfcn.h>
#include <android/log.h>

class pfx_dl_load
{
private:
	void* handle;
public:
	pfx_dl_load()
	{
		handle = dlopen("libPFX_CORE_GLES.so", RTLD_NOW);
		__android_log_print(ANDROID_LOG_INFO,__func__,"dlopen - %sn", dlerror());
	}
	~pfx_dl_load()
	{
	    if (handle)
	    {
	    	dlclose(handle);
	    }
	}


};

static pfx_dl_load gpfx_dl_load;



