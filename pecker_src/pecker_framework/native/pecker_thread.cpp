/*
 * pecker_thread.cpp
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_thread.h"

PECKER_BEGIN

pecker_critical_section::pecker_critical_section():m_is_enter_critical_section(PFX_BOOL_FALSE)
{
#if (OS_CONFIG == OS_ANDROID)

#else
#if (OS_CONFIG == OS_WINDOWS)
	::InitializeCriticalSection(&m_critical_section);
#endif
#endif
}
	
pecker_critical_section::~pecker_critical_section()
{
#if (OS_CONFIG == OS_ANDROID)

#else
#if (OS_CONFIG == OS_WINDOWS)
	leave_critical_section();
	::DeleteCriticalSection(&m_critical_section);
#endif
#endif
}

result_t pecker_critical_section::enter_critical_section()
{
#if (OS_CONFIG == OS_ANDROID)

#else
#if (OS_CONFIG == OS_WINDOWS)
	::EnterCriticalSection(&m_critical_section);
	m_is_enter_critical_section = PFX_BOOL_TRUE;
#endif
#endif
	return PFX_STATUS_OK;
}
result_t pecker_critical_section::leave_critical_section()
{
#if (OS_CONFIG == OS_ANDROID)

#else
#if (OS_CONFIG == OS_WINDOWS)
	if (PFX_BOOL_TRUE == m_is_enter_critical_section)
	{
		m_is_enter_critical_section = PFX_BOOL_FALSE;
		::LeaveCriticalSection(&m_critical_section);
	}

#endif
#endif
	return PFX_STATUS_OK;
}
//
//
//class pecker_critical_lock
//{
//public: 
//	pecker_critical_section* m_bind_critial_section;
//public:
pecker_critical_lock::pecker_critical_lock():m_bind_critial_section_ptr(null)
{

}
pecker_critical_lock::~pecker_critical_lock()
{
	unlock();
}

result_t pecker_critical_lock::lock(pecker_critical_section* pcritical_section)
{
	if (null != pcritical_section)
	{
		result_t pfx_result_t = pcritical_section->enter_critical_section();
		m_bind_critial_section_ptr = pcritical_section;
	}
	return PFX_STATUS_ERROR_;
}

result_t pecker_critical_lock::unlock()
{
	if (null != m_bind_critial_section_ptr)
	{
		pecker_critical_section* ptemp_critial_section_pointer = m_bind_critial_section_ptr;
		m_bind_critial_section_ptr = null;
		return ptemp_critial_section_pointer->leave_critical_section();
	}
	return PFX_STATUS_ERROR_;
}
//};


pecker_thread_base::pecker_thread_base():m_thread_id(0)
#if (OS_CONFIG == OS_WINDOWS)
	,m_hthread(null)
#endif
{

}

pecker_thread_base::~pecker_thread_base()
{
	result_t join_result = this->join_thread(1000);
	if (PFX_STATUS_OK != join_result)
	{
		ulong_t exit_code;
		if (PFX_STATUS_OK == get_thread_exit_code(exit_code))
		{
			terminate_thread(exit_code);
		}
	}
}


void pecker_thread_base::exit_current_thread(ulong_t exit_code)
{
#if (OS_CONFIG == OS_WINDOWS)
	::ExitThread(exit_code);
#endif
}

void pecker_thread_base::sleep(ulong_t wait_milisec_time)
{
#if (OS_CONFIG == OS_WINDOWS)
	::Sleep(wait_milisec_time);
#endif
}

ulong_t pecker_thread_base::get_current_thread_id()
{
#if (OS_CONFIG == OS_WINDOWS)
	return ::GetCurrentThreadId();
#endif
	return 0;
}

result_t pecker_thread_base::start_thread(pecker_thread_proc_callback thread_proc_ptr, pvoid_t proc_params_ptr,  thread_attributes* attribute_ptr /* = null */, nsize__t thread_stack_size /* = 0 */, flag_t thread_creation_flag /* = 0 */)
{
	result_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	if (NULL == m_hthread)
	{
		m_hthread = ::CreateThread(attribute_ptr,thread_stack_size,thread_proc_ptr,proc_params_ptr,thread_creation_flag,&m_thread_id);
		if (NULL != m_hthread)
		{
			result_value = PFX_STATUS_OK;
		}
		else
		{
			result_value = PFX_STATUS_FAIL;
		}
	}
	else
	{
		result_value = PFX_STATUS_WAITRESULT;
	}

#endif
	return result_value;
}

#if (OS_CONFIG == OS_WINDOWS)
DWORD WINAPI pecker_runable_thread_function( LPVOID lpParam )
{
	Ipecker_runable* pthread_target = (Ipecker_runable*)lpParam;
	if (pthread_target)
	{
		pthread_target->run();
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_FAIL;
}
#endif

result_t pecker_thread_base::start_thread(Ipecker_runable* target_ptr,  thread_attributes* attribute_ptr /* = null */, nsize__t thread_stack_size /* = 0 */, flag_t thread_creation_flag /* = 0 */)
{
	result_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	if (NULL == m_hthread)
	{
		m_hthread = ::CreateThread(attribute_ptr,thread_stack_size,pecker_runable_thread_function,target_ptr,thread_creation_flag,&m_thread_id);
		if (NULL != m_hthread)
		{
			result_value = PFX_STATUS_OK;
		}
		else
		{
			result_value = PFX_STATUS_FAIL;
		}
	}
	else
	{
		result_value = PFX_STATUS_WAITRESULT;
	}

#endif
	return result_value;
}

result_t pecker_thread_base::join_thread(ulong_t wait_milisec_time /* = 0 */)
{
	result_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	DWORD wait_result = ::WaitForSingleObject(m_hthread,wait_milisec_time);
	switch(wait_result)
	{
	case WAIT_OBJECT_0:
		if ( !::CloseHandle(m_hthread))
		{
			result_value = PFX_STATUS_ERROR_;
		}
		else
		{
			result_value = PFX_STATUS_OK;
			m_thread_id = 0;
			m_hthread = NULL;
		}
		break;
	case  WAIT_ABANDONED:
		result_value = PFX_STATUS_WAITRESULT;
		break;
	case WAIT_TIMEOUT:
		result_value = PFX_STATUS_TIMEOUT;
		break;
	case WAIT_FAILED:
		result_value = PFX_STATUS_FAIL;
		break;

	}
#endif
	
	return result_value;
}

result_t pecker_thread_base::terminate_thread(ulong_t exit_code)
{
	result_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	if (::TerminateThread(m_hthread,exit_code))
	{
		result_value = PFX_STATUS_OK;
		::CloseHandle(m_hthread);
		m_thread_id = 0;
		m_hthread = NULL;
	}
	else
	{
		result_value = PFX_STATUS_FAIL;
	}
#endif
	return result_value;
}

result_t pecker_thread_base::pause_thread()
{
	result_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	if (-1 != ::SuspendThread(m_hthread))
	{
		result_value = PFX_STATUS_OK;
	}
	else
	{
		result_value = PFX_STATUS_FAIL;
	}
#endif
	return result_value;
}

result_t pecker_thread_base::resume_thread()
{
	result_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	if (-1 != ::ResumeThread(m_hthread))
	{
		result_value = PFX_STATUS_OK;
	}
	else
	{
		result_value = PFX_STATUS_FAIL;
	}
#endif
	return result_value;
}

sint_t pecker_thread_base::get_thread_priority() const
{
	sint_t priority_value;
#if (OS_CONFIG == OS_WINDOWS)
	priority_value = ::GetThreadPriority(m_hthread);
#endif
	return priority_value;
}

boolean_t pecker_thread_base::set_thread_priority(sint_t npriority)
{
	boolean_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	result_value = ::SetThreadPriority(m_hthread,npriority);
#endif
	return result_value;
}

boolean_t pecker_thread_base::is_running() const
{
	boolean_t return_value = PFX_BOOL_FALSE;
#if (OS_CONFIG == OS_WINDOWS)
	DWORD exit_code;
	if (::GetExitCodeThread(m_hthread,&exit_code))
	{
		if (STILL_ACTIVE == exit_code)
		{
			return_value = PFX_BOOL_TRUE;
		}
	}
	else
	{
		return_value = PFX_BOOL_INVALID;
	}
#endif
	return return_value;
}
result_t pecker_thread_base::get_thread_exit_code(ulong_t &exit_code) const
{
	result_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	if (::GetExitCodeThread(m_hthread,&exit_code))
	{
		result_value = PFX_STATUS_OK;
	}
	else
	{
		result_value = PFX_STATUS_FAIL;
	}
#endif
	return result_value;
}

result_t pecker_thread_base::set_thread_affinity_mask(ulong_t cpu_mask)
{
	result_t result_value;
#if (OS_CONFIG == OS_WINDOWS)
	if (0 != ::SetThreadAffinityMask(m_hthread,cpu_mask))
	{
		result_value = PFX_STATUS_OK;
	}
	else
	{
		result_value = PFX_STATUS_FAIL;
	}
#endif
	return result_value;
}

ulong_t pecker_thread_base::get_thread_id() const
{
	return m_thread_id;
}

#if (OS_CONFIG == OS_WINDOWS)
HANDLE pecker_thread_base::get_thread_handle() const
{
	return m_hthread;
}
#endif

pecker_thread_proc_target::pecker_thread_proc_target():m_target_proc_ptr(null),m_params_ptr(null)
{

}
pecker_thread_proc_target::~pecker_thread_proc_target()
{
	m_target_proc_ptr = null;
	m_params_ptr = null;
}

result_t pecker_thread_proc_target::init(pecker_thread_proc_callback target_proc_ptr,pvoid_t params_ptr)
{
	if (null != target_proc_ptr)
	{
		m_target_proc_ptr = target_proc_ptr;
		m_params_ptr = params_ptr;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

void pecker_thread_proc_target::run()
{
	if (null != m_target_proc_ptr)
	{
		m_target_proc_ptr(m_params_ptr);
	}
}

pecker_thread_target::pecker_thread_target() : m_target_ptr(null){}

pecker_thread_target::~pecker_thread_target()
{
	m_target_ptr = null;
}

result_t pecker_thread_target::init(pecker_thread_proc_callback target_proc_ptr,pvoid_t params_ptr)
{
	result_t init_result =  m_proc_target.init(target_proc_ptr,params_ptr);
	if (PFX_STATUS_OK == init_result)
	{
		m_target_ptr = &m_proc_target;
	}
	return init_result; 
}

result_t pecker_thread_target::init(Ipecker_runable* target_ptr)
{
	if (null != target_ptr)
	{
		m_target_ptr = target_ptr;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

void pecker_thread_target::run()
{
	if (null != m_target_ptr)
	{
		m_target_ptr->run();
	}
}

pecker_thread::pecker_thread():m_thread_attr_ptr(null),m_thread_stack_size(0),m_thread_creation_flag(0)
{

}

pecker_thread::~pecker_thread()
{
	m_thread_attr_ptr = null;
	m_thread_stack_size = 0;
	m_thread_creation_flag = 0;
}

result_t pecker_thread::init_thread_info(const thread_attributes* attribute_ptr /* = null */, nsize__t thread_stack_size /* = 0 */, flag_t thread_creation_flag /* = 0 */)
{
	if (null != attribute_ptr)
	{
		m_thread_attr = *attribute_ptr;
		m_thread_attr_ptr = &m_thread_attr;
	}
	else
	{
		m_thread_attr_ptr = null;
	}
	m_thread_stack_size = thread_stack_size;
	m_thread_creation_flag = thread_creation_flag;

	return PFX_STATUS_OK;
}

result_t pecker_thread::init_thread_target(pecker_thread_proc_callback thread_proc_ptr,
	pvoid_t proc_params_ptr)
{
	return m_thread_target.init(thread_proc_ptr,proc_params_ptr);
}

result_t pecker_thread::init_thread_target(Ipecker_runable* target_ptr)
{
	return m_thread_target.init(target_ptr);
}

result_t pecker_thread::init_thread(Ipecker_runable* target_ptr,const thread_attributes* attribute_ptr /* = null */, nsize__t thread_stack_size /* = 0 */, flag_t thread_creation_flag /* = 0 */)
{
	result_t init_result = m_thread_target.init(target_ptr);
	if (PFX_STATUS_OK == init_result)
	{
		 if (null != attribute_ptr)
		 {
			 m_thread_attr = *attribute_ptr;
			 m_thread_attr_ptr = &m_thread_attr;
		 }
		 else
		 {
			 m_thread_attr_ptr = null;
		 }
		m_thread_stack_size = thread_stack_size;
		m_thread_creation_flag = thread_creation_flag;
	}
	return init_result;
}

result_t pecker_thread::init_thread(pecker_thread_proc_callback thread_proc_ptr, pvoid_t proc_params_ptr, const thread_attributes* attribute_ptr /* = null */, nsize__t thread_stack_size /* = 0 */, flag_t thread_creation_flag /* = 0 */)
{
	result_t init_result = m_thread_target.init(thread_proc_ptr,proc_params_ptr);
	if (PFX_STATUS_OK == init_result)
	{
		if (null != attribute_ptr)
		{
			m_thread_attr = *attribute_ptr;
			m_thread_attr_ptr = &m_thread_attr;
		}
		else
		{
			m_thread_attr_ptr = null;
		}
		m_thread_stack_size = thread_stack_size;
		m_thread_creation_flag = thread_creation_flag;
	}
	return init_result;
}

result_t pecker_thread::start_thread(pecker_thread_proc_callback thread_proc_ptr, pvoid_t proc_params_ptr, thread_attributes* attribute_ptr /* = null */, nsize__t thread_stack_size /* = 0 */, flag_t thread_creation_flag /* = 0 */)
{
	if (PFX_STATUS_OK == init_thread(thread_proc_ptr,proc_params_ptr,attribute_ptr,thread_stack_size,thread_creation_flag))
	{
		return pecker_thread_base::start_thread(&m_thread_target,m_thread_attr_ptr,m_thread_stack_size,m_thread_creation_flag);
	}
	return PFX_STATUS_ERROR_;
}

result_t pecker_thread::start_thread(Ipecker_runable* target_ptr,thread_attributes* attribute_ptr /*= null*/,
	nsize__t thread_stack_size /*= 0*/,
	flag_t thread_creation_flag /*= 0*/)
{
	if (PFX_STATUS_OK == init_thread(target_ptr,attribute_ptr,thread_stack_size,thread_creation_flag))
	{
		return pecker_thread_base::start_thread(&m_thread_target,m_thread_attr_ptr,m_thread_stack_size,m_thread_creation_flag);
	}
	return PFX_STATUS_ERROR_;
}

result_t pecker_thread::start_thread()
{
	return pecker_thread_base::start_thread(&m_thread_target,m_thread_attr_ptr,m_thread_stack_size,m_thread_creation_flag); 
}


PECKER_END

