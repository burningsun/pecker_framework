﻿/*
 * pecker_timetick.h
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_TIMETICK_H_
#define PECKER_TIMETICK_H_

#include "../pfx_defines.h"
#if (OS_CONFIG == OS_ANDROID)
#include <time.h>
typedef timespec Time_ticker;
#else
#if (OS_CONFIG == OS_WINDOWS)
typedef LARGE_INTEGER Time_ticker;
#endif
#endif

PECKER_BEGIN
// 计时器，时间单位是毫秒，浮点数。
class pecker_tick
{
private:
	//Time_ticker		m_ticker;
	pfx_double_t	m_start_tick;
public:
	pecker_tick();
	~pecker_tick();
	pfx_result_t init();
	pfx_result_t start();
	pfx_double_t get_microsecond();
	pfx_result_t stop();
};
PECKER_END

#endif /* PECKER_TIMETICK_H_ */
