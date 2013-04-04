#include "native/pecker_thread.h"
#include "native/pecker_log.h"
USING_PECKER_SDK

static SInt g_add_num = 0;
static pecker_critical_section g_print_cs_lock;
#ifdef WINDOWS_PC

DWORD  WINAPI asyn_test_pecker_thread_proc_callback(__in  LPVOID lpParameter)
{
	SInt thread_num = ((SInt*)lpParameter)[0];
	while(1)
	{
		if (g_add_num > 100)
		{
			break;
		}
		pecker_critical_lock cs_lock;
		cs_lock.lock(&g_print_cs_lock);
		PECKER_LOG_("thread_num:%d, num=%d\n",thread_num,g_add_num);
		cs_lock.unlock();
		++g_add_num;

	}

	return 0;
}

DWORD  WINAPI syn_test_pecker_thread_proc_callback(__in  LPVOID lpParameter)
{
	pecker_critical_lock cs_lock;
	SInt thread_num = ((SInt*)lpParameter)[0];
	while (1)
	{
		cs_lock.lock(&g_print_cs_lock);
		if (g_add_num > 100)
		{
			break;
		}
		PECKER_LOG_("thread_num:%d, num=%d\n",thread_num,g_add_num);
		++g_add_num;

		cs_lock.unlock();
	}

	return 0;
}

#endif

class test_syn_runable : public Ipecker_runable
{
private:
	SInt _M_add_num;
public:
	test_syn_runable():_M_add_num(0)
	{
		;
	}
public:
	void run()
	{
		pecker_critical_lock cs_lock;
		while (1)
		{
			cs_lock.lock(&g_print_cs_lock);
			if (_M_add_num > 100)
			{
				break;
			}
			PECKER_LOG_("thread_id:%d, num=%d\n",pecker_thread_base::get_current_thread_id(),_M_add_num);
			++_M_add_num;

			cs_lock.unlock();
		}
	}
};
class test_asyn_runable : public Ipecker_runable
{
private:
	SInt _M_add_num;
public:
	test_asyn_runable():_M_add_num(0)
	{
		;
	}
public:
	void run()
	{
		pecker_critical_lock cs_lock;
		while (1)
		{
			
			if (_M_add_num > 100)
			{
				break;
			}
			cs_lock.lock(&g_print_cs_lock);
			PECKER_LOG_("thread_id:%d, num=%d\n",pecker_thread_base::get_current_thread_id(),_M_add_num);
			cs_lock.unlock();
			++_M_add_num;

			
		}
	}
};

void test_thread_proc()
{
	pecker_thread_base thread_syn_test_proc1;
	pecker_thread_base thread_syn_test_proc2;
	pecker_thread_base thread_syn_test_proc3;
	pecker_thread_base thread_syn_test_proc4;
	SInt thread_syn_test_proc1_num = 1;
	SInt thread_syn_test_proc2_num = 2;
	SInt thread_syn_test_proc3_num = 3;
	SInt thread_syn_test_proc4_num = 4;
	g_add_num = 0;
	PECKER_LOG_("syn proc thread testing.....\n",0);
	thread_syn_test_proc1.start_thread(syn_test_pecker_thread_proc_callback,&thread_syn_test_proc1_num);
	thread_syn_test_proc2.start_thread(syn_test_pecker_thread_proc_callback,&thread_syn_test_proc2_num);
	thread_syn_test_proc3.start_thread(syn_test_pecker_thread_proc_callback,&thread_syn_test_proc3_num);
	thread_syn_test_proc4.start_thread(syn_test_pecker_thread_proc_callback,&thread_syn_test_proc4_num);
	thread_syn_test_proc1.join_thread(-1);
	thread_syn_test_proc2.join_thread(-1);
	thread_syn_test_proc3.join_thread(-1);
	thread_syn_test_proc4.join_thread(-1);

	pecker_thread_base thread_asyn_test_proc1;
	pecker_thread_base thread_asyn_test_proc2;
	pecker_thread_base thread_asyn_test_proc3;
	pecker_thread_base thread_asyn_test_proc4;
	SInt thread_asyn_test_proc1_num = 1;
	SInt thread_asyn_test_proc2_num = 2;
	SInt thread_asyn_test_proc3_num = 3;
	SInt thread_asyn_test_proc4_num = 4;
	g_add_num = 0;
	PECKER_LOG_("asyn proc thread testing.....\n",0);
	thread_asyn_test_proc1.start_thread(asyn_test_pecker_thread_proc_callback,&thread_asyn_test_proc1_num);
	thread_asyn_test_proc2.start_thread(asyn_test_pecker_thread_proc_callback,&thread_asyn_test_proc2_num);
	thread_asyn_test_proc3.start_thread(asyn_test_pecker_thread_proc_callback,&thread_asyn_test_proc3_num);
	thread_asyn_test_proc4.start_thread(asyn_test_pecker_thread_proc_callback,&thread_asyn_test_proc4_num);
	thread_asyn_test_proc1.join_thread(-1);
	thread_asyn_test_proc2.join_thread(-1);
	thread_asyn_test_proc3.join_thread(-1);
	thread_asyn_test_proc4.join_thread(-1);
}

void test_thread_runable()
{
	test_syn_runable syn_run_target;
	pecker_thread_base thread_syn_test_proc1;
	pecker_thread_base thread_syn_test_proc2;
	pecker_thread_base thread_syn_test_proc3;
	pecker_thread_base thread_syn_test_proc4;

	PECKER_LOG_("syn obj thread testing.....\n",0);

	thread_syn_test_proc1.start_thread(&syn_run_target);
	thread_syn_test_proc2.start_thread(&syn_run_target);
	thread_syn_test_proc3.start_thread(&syn_run_target);
	thread_syn_test_proc4.start_thread(&syn_run_target);

	thread_syn_test_proc1.join_thread(-1);
	thread_syn_test_proc2.join_thread(-1);
	thread_syn_test_proc3.join_thread(-1);
	thread_syn_test_proc4.join_thread(-1);

	test_asyn_runable asyn_run_target;
	pecker_thread_base thread_asyn_test_proc1;
	pecker_thread_base thread_asyn_test_proc2;
	pecker_thread_base thread_asyn_test_proc3;
	pecker_thread_base thread_asyn_test_proc4;

	PECKER_LOG_("asyn obj thread testing.....\n",0);

	thread_asyn_test_proc1.start_thread(&asyn_run_target);
	thread_asyn_test_proc2.start_thread(&asyn_run_target);
	thread_asyn_test_proc3.start_thread(&asyn_run_target);
	thread_asyn_test_proc4.start_thread(&asyn_run_target);

	thread_asyn_test_proc1.join_thread(-1);
	thread_asyn_test_proc2.join_thread(-1);
	thread_asyn_test_proc3.join_thread(-1);
	thread_asyn_test_proc4.join_thread(-1);
}

void test_thread_proc_1()
{
	pecker_thread thread_syn_test_proc1;
	pecker_thread thread_syn_test_proc2;
	pecker_thread thread_syn_test_proc3;
	pecker_thread thread_syn_test_proc4;
	SInt thread_syn_test_proc1_num = 1;
	SInt thread_syn_test_proc2_num = 2;
	SInt thread_syn_test_proc3_num = 3;
	SInt thread_syn_test_proc4_num = 4;
	g_add_num = 0;
	PECKER_LOG_("syn proc thread testing.....\n",0);
	thread_syn_test_proc1.start_thread(syn_test_pecker_thread_proc_callback,&thread_syn_test_proc1_num);
	thread_syn_test_proc2.start_thread(syn_test_pecker_thread_proc_callback,&thread_syn_test_proc2_num);
	thread_syn_test_proc3.start_thread(syn_test_pecker_thread_proc_callback,&thread_syn_test_proc3_num);
	thread_syn_test_proc4.start_thread(syn_test_pecker_thread_proc_callback,&thread_syn_test_proc4_num);
	thread_syn_test_proc1.join_thread(-1);
	thread_syn_test_proc2.join_thread(-1);
	thread_syn_test_proc3.join_thread(-1);
	thread_syn_test_proc4.join_thread(-1);

	pecker_thread thread_asyn_test_proc1;
	pecker_thread thread_asyn_test_proc2;
	pecker_thread thread_asyn_test_proc3;
	pecker_thread thread_asyn_test_proc4;
	SInt thread_asyn_test_proc1_num = 1;
	SInt thread_asyn_test_proc2_num = 2;
	SInt thread_asyn_test_proc3_num = 3;
	SInt thread_asyn_test_proc4_num = 4;
	g_add_num = 0;
	PECKER_LOG_("asyn proc thread testing.....\n",0);
	thread_asyn_test_proc1.start_thread(asyn_test_pecker_thread_proc_callback,&thread_asyn_test_proc1_num);
	thread_asyn_test_proc2.start_thread(asyn_test_pecker_thread_proc_callback,&thread_asyn_test_proc2_num);
	thread_asyn_test_proc3.start_thread(asyn_test_pecker_thread_proc_callback,&thread_asyn_test_proc3_num);
	thread_asyn_test_proc4.start_thread(asyn_test_pecker_thread_proc_callback,&thread_asyn_test_proc4_num);
	thread_asyn_test_proc1.join_thread(-1);
	thread_asyn_test_proc2.join_thread(-1);
	thread_asyn_test_proc3.join_thread(-1);
	thread_asyn_test_proc4.join_thread(-1);
}

void test_thread_runable_1()
{
	test_syn_runable syn_run_target;
	pecker_thread thread_syn_test_proc1;
	pecker_thread thread_syn_test_proc2;
	pecker_thread thread_syn_test_proc3;
	pecker_thread thread_syn_test_proc4;

	PECKER_LOG_("syn obj thread testing.....\n",0);

	thread_syn_test_proc1.start_thread(&syn_run_target);
	thread_syn_test_proc2.start_thread(&syn_run_target);
	thread_syn_test_proc3.start_thread(&syn_run_target);
	thread_syn_test_proc4.start_thread(&syn_run_target);

	thread_syn_test_proc1.join_thread(-1);
	thread_syn_test_proc2.join_thread(-1);
	thread_syn_test_proc3.join_thread(-1);
	thread_syn_test_proc4.join_thread(-1);

	test_asyn_runable asyn_run_target;
	pecker_thread thread_asyn_test_proc1;
	pecker_thread thread_asyn_test_proc2;
	pecker_thread thread_asyn_test_proc3;
	pecker_thread thread_asyn_test_proc4;

	PECKER_LOG_("asyn obj thread testing.....\n",0);

	thread_asyn_test_proc1.start_thread(&asyn_run_target);
	thread_asyn_test_proc2.start_thread(&asyn_run_target);
	thread_asyn_test_proc3.start_thread(&asyn_run_target);
	thread_asyn_test_proc4.start_thread(&asyn_run_target);

	thread_asyn_test_proc1.join_thread(-1);
	thread_asyn_test_proc2.join_thread(-1);
	thread_asyn_test_proc3.join_thread(-1);
	thread_asyn_test_proc4.join_thread(-1);
}