
#include "native/pfx_log.h"
#include "native/pfx_timetick.h"

extern int test_main();

#include <locale.h>



int main()
{
	setlocale(LC_ALL,"chs"); 
	//// test log
	//PECKER_LOG_("111=%d\n",1);
	//PECKER_LOG_INFO("123","456=%d",8);
	//PECKER_LOG_ERR("123","456=%d",8);
	//PECKER_LOG_ENDLINE;

	//// test tick
	//st_tick_instance_t tick;
	//init_timetick(&tick);
	//PECKER_LOG_("开始计时\n");
	//start_timetick(&tick);
	//::Sleep(1);
	//Double millisecond = get_millisecond(&tick);
	//PECKER_LOG_INFO("获取当前时间","time=%lf ms",millisecond);
	//stop_timetick(&tick);

	 test_main();

	return 0;
}