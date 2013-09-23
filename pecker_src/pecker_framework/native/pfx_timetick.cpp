/*
 * pfx_timetick.cpp
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城 (cut / cutxyz)
 */
#include "pfx_timetick.h"

USING_PECKER_SDK

#define STOP_TICK_FLAG 0X10101010
#define RUN_TICK_FLAG 0X01010101

//PFX_C_EXTERN_BEGIN
#if (OS_CONFIG == OS_WINDOWS)
	static double dfrequency = -1.0;
#endif

pfx_result_t	init_timetick(st_tick_instance_t* PARAM_INOUT ptick)
{
#if (OS_CONFIG == OS_WINDOWS)
	if (dfrequency < 0)
	{
		Time_ticker ticker;
		QueryPerformanceFrequency(&ticker);
		dfrequency = (pfx_double_t)ticker.QuadPart;
		dfrequency /= 1000.0;
	}
#endif
	if (NULL != ptick)
	{
		ptick->m_start_tick = 0.0;
		ptick->m_flags = STOP_TICK_FLAG;
		return PFX_STATUS_OK;
	}

	return PFX_STATUS_INVALID_PARAMS;
}


PFX_INLINE pfx_result_t inline_start_timetick(st_tick_instance_t* PARAM_INOUT ptick)
{
	if (STOP_TICK_FLAG == ptick->m_flags)
	{
#if (OS_CONFIG == OS_ANDROID)
		pfx_result_t hresult = clock_gettime(CLOCK_MONOTONIC, &(ptick->m_ticker));
		ptick->m_start_tick = (pfx_double_t)ptick->m_ticker.tv_sec * 1000.0 + (pfx_double_t)(ptick->m_ticker.tv_nsec) / 1000000.0;
#else
#if (OS_CONFIG == OS_WINDOWS)
		QueryPerformanceCounter(&(ptick->m_ticker));
		ptick->m_start_tick  = (pfx_double_t)(ptick->m_ticker .QuadPart);
#endif
#endif
		ptick->m_flags = RUN_TICK_FLAG;

		return PFX_STATUS_OK;
	}
	else if (RUN_TICK_FLAG == ptick->m_flags)
	{
		return PFX_STATUS_OPENED;
	}
	else 
	{
		return PFX_STATUS_UNINIT;
	}
	
}



pfx_result_t	inline_stop_timetick(st_tick_instance_t* PARAM_INOUT ptick)
{
	if (RUN_TICK_FLAG == ptick->m_flags)
	{
		ptick->m_flags = STOP_TICK_FLAG;
		return PFX_STATUS_OK;
	}
	else if (STOP_TICK_FLAG == ptick->m_flags)
	{
		return PFX_STATUS_CLOSED;
	}
	else
	{
		return PFX_STATUS_UNINIT;
	}
}

pfx_double_t	inline_get_millisecond(st_tick_instance_t* PARAM_INOUT ptick)
{
	if (RUN_TICK_FLAG == ptick->m_flags)
	{
#if (OS_CONFIG == OS_ANDROID)
		pfx_result_t hresult = clock_gettime(CLOCK_MONOTONIC, &(ptick->m_ticker));
		pfx_double_t current_tick = (pfx_double_t)ptick->m_ticker.tv_sec * 1000.0 + (pfx_double_t)(ptick->m_ticker.tv_nsec) / 1000000.0;
		return (current_tick - _M_start_tick);
#else
#if (OS_CONFIG == OS_WINDOWS)
		pfx_double_t stop_tick;
		QueryPerformanceCounter(&ptick->m_ticker);
		stop_tick = (pfx_double_t)(ptick->m_ticker.QuadPart);
		return ((stop_tick- ptick->m_start_tick)/dfrequency);
#endif
#endif
	}
	return 0.0;
}

pfx_result_t	start_timetick(st_tick_instance_t* PARAM_INOUT ptick)
{
	if (NULL == ptick)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	else
	{
		return inline_start_timetick(ptick);
	}
}

pfx_result_t	stop_timetick(st_tick_instance_t* PARAM_INOUT ptick)
{
	if (NULL == ptick)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	else
	{
		return inline_stop_timetick(ptick);
	}
}

pfx_double_t	get_millisecond(st_tick_instance_t* PARAM_INOUT ptick)
{
	if (NULL == ptick)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	return inline_get_millisecond(ptick);
}
//PFX_C_EXTERN_END

#ifdef __cplusplus

pecker_tick::pecker_tick()
{
	init_timetick(&m_tick);
}

pecker_tick::~pecker_tick()
{
	init_timetick(&m_tick);
}

pfx_result_t pecker_tick::start()
{
	return inline_start_timetick(&m_tick);
}

pfx_result_t pecker_tick::stop()
{
	return inline_stop_timetick(&m_tick);
}

pfx_double_t pecker_tick::get_millisecond()
{
	return inline_get_millisecond(&m_tick);
}

#endif
