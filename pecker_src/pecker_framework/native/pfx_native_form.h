#ifndef PFX_NATIVE_FORM_H_
#define PFX_NATIVE_FORM_H_
#include "../pfx_defines.h"

#include "pfx_native_component.h"

#if (OS_CONFIG == OS_WINDOWS)
#include "window_native_form.h"

PECKER_BEGIN
typedef window_native_form  native_form_t;
PECKER_END

#else 
#if (OS_CONFIG == OS_ANDROID)
//#include "android_native_form.h"
//
//PECKER_BEGIN
//typedef android_native_form native_form_t;
//PECKER_END

#endif 	// #if ((OS_CONFIG == OS_ANDROID))
#endif	// #if (OS_CONFIG == OS_WINDOWS)



#endif //PFX_NATIVE_FORM_H_
