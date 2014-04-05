/*
 * pecker_tick.cpp
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_timetick.h"

PECKER_BEGIN

#if (OS_CONFIG == OS_WINDOWS)
	static double dfrequency = -1.0;
#endif

pecker_tick::pecker_tick():m_start_tick(-1.0)
{
#if (OS_CONFIG == OS_ANDROID)

#else
#if (OS_CONFIG == OS_WINDOWS)
	if (dfrequency < 0.0)
	{
		LARGE_INTEGER ticker;
		QueryPerformanceFrequency(&ticker);
		dfrequency = (pfx_double_t)ticker.QuadPart;
		dfrequency /= 1000.0f;
	}
#endif
#endif
}
pecker_tick::~pecker_tick()
{
	m_start_tick = -1.0;
}


pfx_result_t pecker_tick::init()
{
	m_start_tick = 0.0;
	return PFX_STATUS_OK;
}

pfx_result_t pecker_tick::start()
{
	//if (m_start_tick > -1.0)
	//{
	//	return PFX_STATUS_ERROR_;
	//}
#if (OS_CONFIG == OS_ANDROID)
	pfx_result_t pfx_result_t = clock_gettime(CLOCK_MONOTONIC, &m_ticker);
	m_start_tick = (pfx_double_t)m_ticker.tv_sec * 1000.0 + (pfx_double_t)(m_ticker.tv_nsec) / 1000000.0;
//	res = clock_gettime(CLOCK_MONOTONIC, &m_startTime);
#else
#if (OS_CONFIG == OS_WINDOWS)
	LARGE_INTEGER ticker;
	QueryPerformanceCounter(&ticker);
	m_start_tick = (pfx_double_t)(ticker.QuadPart);
#endif
#endif
	return PFX_STATUS_OK;
}
pfx_double_t pecker_tick::get_microsecond()
{
	if (m_start_tick > 0.0)
	{
#if (OS_CONFIG == OS_ANDROID)
		pfx_result_t pfx_result_t = clock_gettime(CLOCK_MONOTONIC, &m_ticker);
		pfx_double_t current_tick = (pfx_double_t)m_ticker.tv_sec * 1000.0 + (pfx_double_t)(m_ticker.tv_nsec) / 1000000.0;
		return (current_tick - m_start_tick);
#else
#if (OS_CONFIG == OS_WINDOWS)
		LARGE_INTEGER ticker;
		QueryPerformanceCounter(&ticker);
		pfx_double_t stop_tick = (pfx_double_t)(ticker.QuadPart);
		return ((stop_tick-m_start_tick)/dfrequency);
#endif
#endif
	}
	return 0.0;
}

pfx_result_t pecker_tick::stop()
{
	m_start_tick = -1.0;
	return PFX_STATUS_OK;
}

PECKER_END
