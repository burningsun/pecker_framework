/*
 * pecker_timetick.h
 *
 *  Created on: 2012-11-14
 *      Author: �����  �� cut / cutxyz��
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_TIMETICK_H_
#define PECKER_TIMETICK_H_

#include "../CPeckerObject.h"
#ifdef ANDROID_OS
#include <time.h>
typedef timespec Time_ticker;
#else
#ifdef WINDOWS_PC
typedef LARGE_INTEGER Time_ticker;
#endif
#endif

PECKER_BEGIN
// ��ʱ����ʱ�䵥λ�Ǻ��룬��������
class pecker_tick
{
private:
	Time_ticker _M_ticker;
	Double _M_start_tick;
public:
	pecker_tick();
	~pecker_tick();
	HResult init();
	HResult start();
	Double get_microsecond();
	HResult stop();
};
PECKER_END

#endif /* PECKER_TIMETICK_H_ */
