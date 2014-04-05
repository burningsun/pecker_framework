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

#include "../pfx_defines.h"

PECKER_BEGIN

#if (OS_CONFIG == OS_ANDROID)

#else
#if (OS_CONFIG == OS_WINDOWS)
	typedef CRITICAL_SECTION critical_section_data;
#endif
#endif

// 临界区操作类
class pecker_critical_section
{
private:
	critical_section_data m_critical_section;
	pfx_boolean_t			m_is_enter_critical_section;
public:
	pecker_critical_section();
	~pecker_critical_section();
	pfx_result_t enter_critical_section();
	pfx_result_t leave_critical_section();
};

// 临界区锁操作
class pecker_critical_lock
{
public: 
	pecker_critical_section* m_bind_critial_section_ptr;
public:
	pecker_critical_lock();
	~pecker_critical_lock();

	pfx_result_t lock(pecker_critical_section* pcritical_section);
	pfx_result_t unlock();
};

#if (OS_CONFIG == OS_WINDOWS)
typedef DWORD  (WINAPI *pecker_thread_proc_callback)(__in  LPVOID lpParameter);
typedef SECURITY_ATTRIBUTES thread_attributes;
#else
typedef void* (*pecker_thread_proc_callback)(void* pargs);
typedef pthread_attr_t  thread_attributes;
#endif


// 线程执行体接口
PFX_Interface Ipecker_runable
{
	virtual ~Ipecker_runable(){;}
	virtual void run() = 0;
	//virtual void terminate() = 0;
};

// 线程基本操作类
class pecker_thread_base
{
private:
	pfx_ulong_t m_thread_id;
#if (OS_CONFIG == OS_WINDOWS)
	HANDLE m_hthread;
#endif
	
public:
	pfx_ulong_t get_thread_id() const;

#if (OS_CONFIG == OS_WINDOWS)
	HANDLE get_thread_handle() const;
#endif
	
public:
	pecker_thread_base();
	virtual ~pecker_thread_base();
public:
	virtual pfx_result_t start_thread(pecker_thread_proc_callback thread_proc_ptr,
		pfx_pvoid_t proc_params_ptr,
		thread_attributes* attribute_ptr = null,
		pfx_nsize_t thread_stack_size = 0,
		pfx_flag_t thread_creation_flag = 0);

	virtual pfx_result_t start_thread(Ipecker_runable* target_ptr,
		thread_attributes* attribute_ptr = null,
		pfx_nsize_t thread_stack_size = 0,
		pfx_flag_t thread_creation_flag = 0);

	pfx_result_t join_thread(pfx_ulong_t wait_milisec_time = 0);
	pfx_result_t terminate_thread(pfx_ulong_t exit_code);
	pfx_result_t pause_thread();
	pfx_result_t resume_thread();

	pfx_sint_t get_thread_priority() const;
	pfx_boolean_t set_thread_priority(pfx_sint_t npriority);

	pfx_result_t get_thread_exit_code(pfx_ulong_t &exit_code) const;


	pfx_result_t set_thread_affinity_mask(pfx_ulong_t cpu_mask);

	pfx_boolean_t is_running() const;
public:
	static void exit_current_thread(pfx_ulong_t exit_code);
	static void sleep(pfx_ulong_t wait_milisec_time);
	static pfx_ulong_t get_current_thread_id();
};	

// 线程过程目标执行体（回调函数转线程执行体）
class pecker_thread_proc_target : public Ipecker_runable
{
private: 
	pecker_thread_proc_callback	m_target_proc_ptr;
	pfx_pvoid_t								m_params_ptr;
public:
	pecker_thread_proc_target();
	virtual ~pecker_thread_proc_target();
	virtual pfx_result_t init(pecker_thread_proc_callback target_proc_ptr,pfx_pvoid_t params_ptr);
	virtual void run();
	//virtual void terminate();
};

// 线程目标执行体 (适应OOA和OOP两种执行体)
class pecker_thread_target :public Ipecker_runable
{
private:
	pecker_thread_proc_target m_proc_target;
	Ipecker_runable*					m_target_ptr;	
public:
	pecker_thread_target();
	virtual ~pecker_thread_target();

	virtual pfx_result_t init(pecker_thread_proc_callback target_proc_ptr,pfx_pvoid_t params_ptr);
	virtual pfx_result_t init(Ipecker_runable* target_ptr);
	virtual void run();
	//virtual void terminate();
};

// 线程类
class pecker_thread : public pecker_thread_base
{
private:
	pecker_thread_target	m_thread_target;
	thread_attributes			m_thread_attr;
	thread_attributes*		m_thread_attr_ptr;
	pfx_nsize_t						m_thread_stack_size;
	pfx_flag_t						m_thread_creation_flag;
public:
	pecker_thread();
	virtual ~pecker_thread();
	
	virtual pfx_result_t init_thread_info(const thread_attributes* attribute_ptr = null,
		pfx_nsize_t thread_stack_size = 0,
		pfx_flag_t thread_creation_flag = 0);

	virtual pfx_result_t init_thread_target(pecker_thread_proc_callback thread_proc_ptr,
		pfx_pvoid_t proc_params_ptr);

	virtual pfx_result_t init_thread_target(Ipecker_runable* target_ptr);


	virtual pfx_result_t init_thread(pecker_thread_proc_callback thread_proc_ptr,
		pfx_pvoid_t proc_params_ptr,
		const thread_attributes* attribute_ptr = null,
		pfx_nsize_t thread_stack_size = 0,
		pfx_flag_t thread_creation_flag = 0);

	virtual pfx_result_t init_thread(Ipecker_runable* target_ptr,
		const thread_attributes* attribute_ptr = null,
		pfx_nsize_t thread_stack_size = 0,
		pfx_flag_t thread_creation_flag = 0);

	virtual pfx_result_t start_thread(pecker_thread_proc_callback thread_proc_ptr,
		pfx_pvoid_t proc_params_ptr,
		thread_attributes* attribute_ptr = null,
		pfx_nsize_t thread_stack_size = 0,
		pfx_flag_t thread_creation_flag = 0);

	 virtual pfx_result_t start_thread(Ipecker_runable* target_ptr,
		thread_attributes* attribute_ptr = null,
		pfx_nsize_t thread_stack_size = 0,
		pfx_flag_t thread_creation_flag = 0);

	 virtual pfx_result_t start_thread();
};

PECKER_END


#endif /* PECKER_THREAD_H_ */
