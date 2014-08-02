/*
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

PECKER_BEGIN
// 计时器，时间单位是毫秒，浮点数。
class PFX_NATIVE_API pecker_tick
{
private:
	double_t m_start_tick;
public:
	pecker_tick();
	~pecker_tick();
	result_t init();
	result_t start();
	double_t get_microsecond();
	result_t stop();
};
PECKER_END

#endif /* PECKER_TIMETICK_H_ */
