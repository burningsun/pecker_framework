﻿/*
 * pfx_timetick.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城 (cut / cutxyz)
 */

#ifndef		PFX_TIMETICK_H_
#define		PFX_TIMETICK_H_

#include "../pfx_defines.h"



#if (OS_CONFIG == OS_ANDROID)
#include <time.h>
typedef timespec Time_ticker;
#else
#if (OS_CONFIG == OS_WINDOWS)
typedef LARGE_INTEGER Time_ticker;
#endif
#endif

PFX_C_EXTERN_BEGIN
	// 计时器，时间单位是毫秒，浮点数。
	typedef struct st_tick_instance
	{
		Time_ticker		m_ticker;
		Double			m_start_tick;
		BitField			m_flags;
	}st_tick_instance_t;

	pfx_result	init_timetick(st_tick_instance_t* PARAM_INOUT ptick);
	pfx_result	start_timetick(st_tick_instance_t* PARAM_INOUT ptick);
	pfx_result	stop_timetick(st_tick_instance_t* PARAM_INOUT ptick);
	Double	get_millisecond(st_tick_instance_t* PARAM_INOUT ptick);
PFX_C_EXTERN_END

#ifdef __cplusplus
PECKER_BEGIN

class PFX_API pecker_tick
{
private:
	st_tick_instance_t m_tick;
public:
	pecker_tick();
	~pecker_tick();
	pfx_result start();
	Double get_millisecond();
	pfx_result stop();
};

PECKER_END
#endif

#endif			//PFX_TIMETICK_H_
