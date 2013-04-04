/*
 * pecker_tick.cpp
 *
 *  Created on: 2012-11-14
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_timetick.h"

PECKER_BEGIN

pecker_tick::pecker_tick():_M_start_tick(-1.0)
{

}
pecker_tick::~pecker_tick()
{
	_M_start_tick = -1.0;
}

#ifdef WINDOWS_PC
static double dfrequency = -1.0;
#endif
HResult pecker_tick::init()
{
	_M_start_tick = -2.0;
#ifdef ANDROID_OS

#else
#ifdef WINDOWS_PC
	if (dfrequency < 0.0)
	{
		QueryPerformanceFrequency(&_M_ticker);
		dfrequency = (Double)_M_ticker.QuadPart;
		dfrequency /= 1000.0f;
	}
#endif
#endif
	return P_OK;
}
HResult pecker_tick::start()
{
	if (_M_start_tick > -1.0)
	{
		return P_ERR;
	}
#ifdef ANDROID_OS
	HResult hresult = clock_gettime(CLOCK_MONOTONIC, &_M_ticker);
	_M_start_tick = (Double)_M_ticker.tv_sec * 1000.0 + (Double)(_M_ticker.tv_nsec) / 1000000.0;
//	res = clock_gettime(CLOCK_MONOTONIC, &m_startTime);
#else
#ifdef WINDOWS_PC
	QueryPerformanceCounter(&_M_ticker);
	_M_start_tick = (Double)(_M_ticker.QuadPart);
#endif
#endif
	return P_OK;
}
Double pecker_tick::get_microsecond()
{
	if (_M_start_tick > 0.0)
	{
#ifdef ANDROID_OS
		HResult hresult = clock_gettime(CLOCK_MONOTONIC, &_M_ticker);
		Double current_tick = (Double)_M_ticker.tv_sec * 1000.0 + (Double)(_M_ticker.tv_nsec) / 1000000.0;
		return (current_tick - _M_start_tick);
#else
#ifdef WINDOWS_PC
		QueryPerformanceCounter(&_M_ticker);
		Double stop_tick = (Double)(_M_ticker.QuadPart);
		return ((stop_tick-_M_start_tick)/dfrequency);
#endif
#endif
	}
	return 0.0;
}

HResult pecker_tick::stop()
{
	if (_M_start_tick > 0.0)
	{
		_M_start_tick = -2.0;
	}

	return P_OK;
}

PECKER_END
