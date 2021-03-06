﻿/*
 * pecker_tick.cpp
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_timetick.h"

#if ((OS_CONFIG == OS_ANDROID)||(OS_CONFIG == OS_LINUX))
#include <time.h>
typedef timespec Time_ticker_t;
#else
#if (OS_CONFIG == OS_WINDOWS)
typedef LARGE_INTEGER Time_ticker_t;
#endif
#endif

PECKER_BEGIN

#if (OS_CONFIG == OS_WINDOWS)
	static double dfrequency = -1.0;
#endif

pecker_tick::pecker_tick():m_start_tick(-1.0)
{
#if (OS_CONFIG == OS_ANDROID || OS_CONFIG == OS_LINUX)

#else
#if (OS_CONFIG == OS_WINDOWS)
	if (dfrequency < 0.0)
	{
		LARGE_INTEGER ticker;
		QueryPerformanceFrequency(&ticker);
		dfrequency = (double_t)ticker.QuadPart;
		dfrequency /= 1000.0f;
	}
#endif
#endif
}
pecker_tick::~pecker_tick()
{
	m_start_tick = -1.0;
}


result_t pecker_tick::init()
{
	m_start_tick = 0.0;
	return PFX_STATUS_OK;
}

result_t pecker_tick::start()
{
	//if (m_start_tick > -1.0)
	//{
	//	return PFX_STATUS_ERROR_;
	//}
	Time_ticker_t ticker;
#if (OS_CONFIG == OS_ANDROID || OS_CONFIG == OS_LINUX)
	result_t pfx_result_t = clock_gettime(CLOCK_MONOTONIC, &ticker);
	m_start_tick = (double_t)ticker.tv_sec * 1000.0 + (double_t)(ticker.tv_nsec) / 1000000.0;
//	res = clock_gettime(CLOCK_MONOTONIC, &m_startTime);
#else
#if (OS_CONFIG == OS_WINDOWS)
	//LARGE_INTEGER ticker;
	QueryPerformanceCounter(&ticker);
	m_start_tick = (double_t)(ticker.QuadPart);
#endif
#endif
	return PFX_STATUS_OK;
}
double_t pecker_tick::get_microsecond()
{
	if (m_start_tick > 0.0)
	{
		Time_ticker_t ticker;
#if (OS_CONFIG == OS_ANDROID || OS_CONFIG == OS_LINUX)
		result_t pfx_result_t = clock_gettime(CLOCK_MONOTONIC, &ticker);
		double_t current_tick = (double_t)ticker.tv_sec * 1000.0 + (double_t)(ticker.tv_nsec) / 1000000.0;
		return (current_tick - m_start_tick);
#else
#if (OS_CONFIG == OS_WINDOWS)
		//LARGE_INTEGER ticker;
		QueryPerformanceCounter(&ticker);
		double_t stop_tick = (double_t)(ticker.QuadPart);
		return ((stop_tick-m_start_tick)/dfrequency);
#endif
#endif
	}
	return 0.0;
}

result_t pecker_tick::stop()
{
	m_start_tick = -1.0;
	return PFX_STATUS_OK;
}

PECKER_END
