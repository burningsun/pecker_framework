#ifndef PFX_NATIVE_FORM_H_
#define PFX_NATIVE_FORM_H_
#include "../pfx_defines.h"

//#include "pfx_native_component.h"

#if (OS_CONFIG == OS_WINDOWS)

#define CNative_form		class window_native_form
#define CNative_form_ptr	CNative_form *
#include "window_native_form.h"

PECKER_BEGIN
typedef class window_native_form  native_form_t;
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

