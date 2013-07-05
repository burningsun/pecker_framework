/*
 * pecker_thread.h
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_THREAD_H_
#define PECKER_THREAD_H_

#include "../pecker_reference.h"

PECKER_BEGIN

#ifdef ANDROID_OS

#else
#ifdef WINDOWS_PC
	typedef CRITICAL_SECTION critical_section_data;
#endif
#endif

// 临界区操作类
class pecker_critical_section
{
private:
	critical_section_data _M_critical_section;
	Bool _M_is_enter_critical_section;
public:
	pecker_critical_section();
	~pecker_critical_section();
	HResult enter_critical_section();
	HResult leave_critical_section();
};

// 临界区锁操作
class pecker_critical_lock
{
public: 
	pecker_critical_section* _M_bind_critial_section;
public:
	pecker_critical_lock();
	~pecker_critical_lock();

	HResult lock(pecker_critical_section* pcritical_section);
	HResult unlock();
};

#ifdef WINDOWS_PC
typedef DWORD  (WINAPI *pecker_thread_proc_callback)(__in  LPVOID lpParameter);
typedef SECURITY_ATTRIBUTES thread_attributes;
#else
typedef void* (*pecker_thread_proc_callback)(void* pargs);
typedef pthread_attr_t  thread_attributes;
#endif


// 线程执行体接口
PeckerInterface Ipecker_runable
{
	virtual ~Ipecker_runable(){;}
	virtual void run() = 0;
	//virtual void terminate() = 0;
};

// 线程基本操作类
class pecker_thread_base
{
private:
	Ulong _M_thread_id;
#ifdef WINDOWS_PC
	Handle _M_hthread;
#endif
	
public:
	Ulong get_thread_id() const;

#ifdef WINDOWS_PC
	Handle get_thread_handle() const;
#endif
	
public:
	pecker_thread_base();
	virtual ~pecker_thread_base();
public:
	virtual HResult start_thread(pecker_thread_proc_callback pthread_proc,
		PVoid proc_params,
		thread_attributes* pattribute = null,
		nSize thread_stack_size = 0,
		HFlag thread_creation_flag = 0);

	virtual HResult start_thread(Ipecker_runable* ptarget,
		thread_attributes* pattribute = null,
		nSize thread_stack_size = 0,
		HFlag thread_creation_flag = 0);

	HResult join_thread(Ulong wait_milisec_time = 0);
	HResult terminate_thread(Ulong exit_code);
	HResult pause_thread();
	HResult resume_thread();

	SInt get_thread_priority() const;
	Boolean set_thread_priority(SInt npriority);

	HResult get_thread_exit_code(Ulong &exit_code) const;


	HResult set_thread_affinity_mask(Ulong cpu_mask);

	Boolean is_running() const;
public:
	static void exit_current_thread(Ulong exit_code);
	static void sleep(Ulong wait_milisec_time);
	static Ulong get_current_thread_id();
};	

// 线程过程目标执行体（回调函数转线程执行体）
class pecker_thread_proc_target : public Ipecker_runable
{
private: 
	pecker_thread_proc_callback _M_ptarget_proc;
	PVoid _M_params;
public:
	pecker_thread_proc_target();
	virtual ~pecker_thread_proc_target();
	virtual HResult init(pecker_thread_proc_callback ptarget_proc,PVoid params);
	virtual void run();
	//virtual void terminate();
};

// 线程目标执行体 (适应OOA和OOP两种执行体)
class pecker_thread_target :public Ipecker_runable
{
private:
	pecker_thread_proc_target _M_proc_target;
	Ipecker_runable* _M_ptarget;	
public:
	pecker_thread_target();
	virtual ~pecker_thread_target();

	virtual HResult init(pecker_thread_proc_callback ptarget_proc,PVoid params);
	virtual HResult init(Ipecker_runable* ptarget);
	virtual void run();
	//virtual void terminate();
};

// 线程类
class pecker_thread : public pecker_thread_base
{
private:
	pecker_thread_target _M_thread_target;
	thread_attributes _M_thread_attr;
	thread_attributes* _M_pthread_attr;
	nSize _M_thread_stack_size;
	HFlag _M_thread_creation_flag;
public:
	pecker_thread();
	virtual ~pecker_thread();
	
	virtual HResult init_thread_info(const thread_attributes* pattribute = null,
		nSize thread_stack_size = 0,
		HFlag thread_creation_flag = 0);

	virtual HResult init_thread_target(pecker_thread_proc_callback pthread_proc,
		PVoid proc_params);

	virtual HResult init_thread_target(Ipecker_runable* ptarget);


	virtual HResult init_thread(pecker_thread_proc_callback pthread_proc,
		PVoid proc_params,
		const thread_attributes* pattribute = null,
		nSize thread_stack_size = 0,
		HFlag thread_creation_flag = 0);

	virtual HResult init_thread(Ipecker_runable* ptarget,
		const thread_attributes* pattribute = null,
		nSize thread_stack_size = 0,
		HFlag thread_creation_flag = 0);

	virtual HResult start_thread(pecker_thread_proc_callback pthread_proc,
		PVoid proc_params,
		thread_attributes* pattribute = null,
		nSize thread_stack_size = 0,
		HFlag thread_creation_flag = 0);

	 virtual HResult start_thread(Ipecker_runable* ptarget,
		thread_attributes* pattribute = null,
		nSize thread_stack_size = 0,
		HFlag thread_creation_flag = 0);

	 virtual HResult start_thread();
};

PECKER_END


#endif /* PECKER_THREAD_H_ */
