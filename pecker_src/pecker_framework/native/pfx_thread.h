#ifndef PFX_THREAD_H_
#define PFX_THREAD_H_
#include "../pfx_defines.h"

#include "thread_param.h"

#if (OS_CONFIG == OS_WINDOWS)
#include "window_thread.h"

PECKER_BEGIN
typedef win_thread  thread_t;
PECKER_END

#else 
#if ((OS_CONFIG == OS_LINUX) || (OS_CONFIG == OS_ANDROID))
#include "linux_thread.h"

PECKER_BEGIN
typedef linux_thread thread_t;
PECKER_END

#endif 
#endif



#endif //PFX_THREAD_H_
