/*
 * pure_ndk_template.cpp
 *
 *  Created on: 2015-2-19
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#ifndef PURE_NATIVE_CODE
#define PURE_NATIVE_CODE
#endif //PURE_NATIVE_CODE

#include "pfx_app_init.h"

extern "C"
{
int pecker_program(void* form)
{
	return PFX_main((pecker_sdk::native_form_t*)form);
}
}




