/*
 * pecker_thread.cpp
 *
 *  Created on: 2012-11-14
 *      Author: ÀîÕò³Ç  £¨ cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_thread.h"

PECKER_BEGIN

pecker_critical_section::pecker_critical_section():_M_is_enter_critical_section(BOOL_FALSE)
{
#ifdef ANDROID_OS

#else
#ifdef WINDOWS_PC
	::InitializeCriticalSection(&_M_critical_section);
#endif
#endif
}
	
pecker_critical_section::~pecker_critical_section()
{
#ifdef ANDROID_OS

#else
#ifdef WINDOWS_PC
	leave_critical_section();
	::DeleteCriticalSection(&_M_critical_section);
#endif
#endif
}

HResult pecker_critical_section::enter_critical_section()
{
#ifdef ANDROID_OS

#else
#ifdef WINDOWS_PC
	::EnterCriticalSection(&_M_critical_section);
	_M_is_enter_critical_section = BOOL_TRUE;
#endif
#endif
	return P_OK;
}
HResult pecker_critical_section::leave_critical_section()
{
#ifdef ANDROID_OS

#else
#ifdef WINDOWS_PC
	if (BOOL_TRUE == _M_is_enter_critical_section)
	{
		_M_is_enter_critical_section = BOOL_FALSE;
		::LeaveCriticalSection(&_M_critical_section);
	}

#endif
#endif
	return P_OK;
}
//
//
//class pecker_critical_lock
//{
//public: 
//	pecker_critical_section* _M_bind_critial_section;
//public:
pecker_critical_lock::pecker_critical_lock():_M_bind_critial_section(null)
{

}
pecker_critical_lock::~pecker_critical_lock()
{
	unlock();
}

HResult pecker_critical_lock::lock(pecker_critical_section* pcritical_section)
{
	if (null != pcritical_section)
	{
		HResult hresult = pcritical_section->enter_critical_section();
		_M_bind_critial_section = pcritical_section;
	}
	return P_ERR;
}

HResult pecker_critical_lock::unlock()
{
	if (null != _M_bind_critial_section)
	{
		pecker_critical_section* ptemp_critial_section_pointer = _M_bind_critial_section;
		_M_bind_critial_section = null;
		return ptemp_critial_section_pointer->leave_critical_section();
	}
	return P_ERR;
}
//};


pecker_thread_base::pecker_thread_base():_M_thread_id(0)
#ifdef WINDOWS_PC
	,_M_hthread(null)
#endif
{

}

pecker_thread_base::~pecker_thread_base()
{
	HResult join_result = this->join_thread(1000);
	if (P_OK != join_result)
	{
		Ulong exit_code;
		if (P_OK == get_thread_exit_code(exit_code))
		{
			terminate_thread(exit_code);
		}
	}
}


void pecker_thread_base::exit_current_thread(Ulong exit_code)
{
#ifdef WINDOWS_PC
	::ExitThread(exit_code);
#endif
}

void pecker_thread_base::sleep(Ulong wait_milisec_time)
{
#ifdef WINDOWS_PC
	::Sleep(wait_milisec_time);
#endif
}

Ulong pecker_thread_base::get_current_thread_id()
{
#ifdef WINDOWS_PC
	return ::GetCurrentThreadId();
#endif
	return 0;
}

HResult pecker_thread_base::start_thread(pecker_thread_proc_callback pthread_proc, PVoid proc_params,  thread_attributes* pattribute /* = null */, nSize thread_stack_size /* = 0 */, HFlag thread_creation_flag /* = 0 */)
{
	HResult result_value;
#ifdef WINDOWS_PC
	if (NULL == _M_hthread)
	{
		_M_hthread = ::CreateThread(pattribute,thread_stack_size,pthread_proc,proc_params,thread_creation_flag,&_M_thread_id);
		if (NULL != _M_hthread)
		{
			result_value = P_OK;
		}
		else
		{
			result_value = P_FAIL;
		}
	}
	else
	{
		result_value = P_RUNNING_WAIT;
	}

#endif
	return result_value;
}

#ifdef WINDOWS_PC
DWORD WINAPI pecker_runable_thread_function( LPVOID lpParam )
{
	Ipecker_runable* pthread_target = (Ipecker_runable*)lpParam;
	if (pthread_target)
	{
		pthread_target->run();
		return P_OK;
	}
	return P_FAIL;
}
#endif

HResult pecker_thread_base::start_thread(Ipecker_runable* ptarget,  thread_attributes* pattribute /* = null */, nSize thread_stack_size /* = 0 */, HFlag thread_creation_flag /* = 0 */)
{
	HResult result_value;
#ifdef WINDOWS_PC
	if (NULL == _M_hthread)
	{
		_M_hthread = ::CreateThread(pattribute,thread_stack_size,pecker_runable_thread_function,ptarget,thread_creation_flag,&_M_thread_id);
		if (NULL != _M_hthread)
		{
			result_value = P_OK;
		}
		else
		{
			result_value = P_FAIL;
		}
	}
	else
	{
		result_value = P_RUNNING_WAIT;
	}

#endif
	return result_value;
}

HResult pecker_thread_base::join_thread(Ulong wait_milisec_time /* = 0 */)
{
	HResult result_value;
#ifdef WINDOWS_PC
	DWORD wait_result = ::WaitForSingleObject(_M_hthread,wait_milisec_time);
	switch(wait_result)
	{
	case WAIT_OBJECT_0:
		
		if ( !::CloseHandle(_M_hthread))
		{
			result_value = P_ERR;
		}
		else
		{
			result_value = P_OK;
			_M_thread_id = 0;
			_M_hthread = NULL;
		}
		break;
	case  WAIT_ABANDONED:
		result_value = P_WAITRESULT;
		break;
	case WAIT_TIMEOUT:
		result_value = P_TIMEOUT;
		break;
	case WAIT_FAILED:
		result_value = P_FAIL;
		break;

	}
#endif
	
	return result_value;
}

HResult pecker_thread_base::terminate_thread(Ulong exit_code)
{
	HResult result_value;
#ifdef WINDOWS_PC
	if (::TerminateThread(_M_hthread,exit_code))
	{
		result_value = P_OK;
		::CloseHandle(_M_hthread);
		_M_thread_id = 0;
		_M_hthread = NULL;
	}
	else
	{
		result_value = P_FAIL;
	}
#endif
	return result_value;
}

HResult pecker_thread_base::pause_thread()
{
	HResult result_value;
#ifdef WINDOWS_PC
	if (-1 != ::SuspendThread(_M_hthread))
	{
		result_value = P_OK;
	}
	else
	{
		result_value = P_FAIL;
	}
#endif
	return result_value;
}

HResult pecker_thread_base::resume_thread()
{
	HResult result_value;
#ifdef WINDOWS_PC
	if (-1 != ::ResumeThread(_M_hthread))
	{
		result_value = P_OK;
	}
	else
	{
		result_value = P_FAIL;
	}
#endif
	return result_value;
}

SInt pecker_thread_base::get_thread_priority() const
{
	SInt priority_value;
#ifdef WINDOWS_PC
	priority_value = ::GetThreadPriority(_M_hthread);
#endif
	return priority_value;
}

Boolean pecker_thread_base::set_thread_priority(SInt npriority)
{
	Boolean result_value;
#ifdef WINDOWS_PC
	result_value = ::SetThreadPriority(_M_hthread,npriority);
#endif
	return result_value;
}

HResult pecker_thread_base::get_thread_exit_code(Ulong &exit_code) const
{
	HResult result_value;
#ifdef WINDOWS_PC
	if (::GetExitCodeThread(_M_hthread,&exit_code))
	{
		result_value = P_OK;
	}
	else
	{
		result_value = P_FAIL;
	}
#endif
	return result_value;
}

HResult pecker_thread_base::set_thread_affinity_mask(Ulong cpu_mask)
{
	HResult result_value;
#ifdef WINDOWS_PC
	if (0 != ::SetThreadAffinityMask(_M_hthread,cpu_mask))
	{
		result_value = P_OK;
	}
	else
	{
		result_value = P_FAIL;
	}
#endif
	return result_value;
}

Ulong pecker_thread_base::get_thread_id() const
{
	return _M_thread_id;
}

#ifdef WINDOWS_PC
Handle pecker_thread_base::get_thread_handle() const
{
	return _M_hthread;
}
#endif

pecker_thread_proc_target::pecker_thread_proc_target():_M_ptarget_proc(null),_M_params(null)
{

}
pecker_thread_proc_target::~pecker_thread_proc_target()
{
	_M_ptarget_proc = null;
	_M_params = null;
}

HResult pecker_thread_proc_target::init(pecker_thread_proc_callback ptarget_proc,PVoid params)
{
	if (null != ptarget_proc)
	{
		_M_ptarget_proc = ptarget_proc;
		_M_params = params;
		return P_OK;
	}
	return P_ERR;
}

void pecker_thread_proc_target::run()
{
	if (null != _M_ptarget_proc)
	{
		_M_ptarget_proc(_M_params);
	}
}

pecker_thread_target::pecker_thread_target() : _M_ptarget(null){}

pecker_thread_target::~pecker_thread_target()
{
	_M_ptarget = null;
}

HResult pecker_thread_target::init(pecker_thread_proc_callback ptarget_proc,PVoid params)
{
	HResult init_result =  _M_proc_target.init(ptarget_proc,params);
	if (P_OK == init_result)
	{
		_M_ptarget = &_M_proc_target;
	}
	return init_result; 
}

HResult pecker_thread_target::init(Ipecker_runable* ptarget)
{
	if (null != ptarget)
	{
		_M_ptarget = ptarget;
		return P_OK;
	}
	return P_ERR;
}

void pecker_thread_target::run()
{
	if (null != _M_ptarget)
	{
		_M_ptarget->run();
	}
}

pecker_thread::pecker_thread():_M_pthread_attr(null),_M_thread_stack_size(0),_M_thread_creation_flag(0)
{

}

pecker_thread::~pecker_thread()
{
	_M_pthread_attr = null;
	_M_thread_stack_size = 0;
	_M_thread_creation_flag = 0;
}

HResult pecker_thread::init_thread_info(const thread_attributes* pattribute /* = null */, nSize thread_stack_size /* = 0 */, HFlag thread_creation_flag /* = 0 */)
{
	if (null != pattribute)
	{
		_M_thread_attr = *pattribute;
		_M_pthread_attr = &_M_thread_attr;
	}
	else
	{
		_M_pthread_attr = null;
	}
	_M_thread_stack_size = thread_stack_size;
	_M_thread_creation_flag = thread_creation_flag;

	return P_OK;
}

HResult pecker_thread::init_thread_target(pecker_thread_proc_callback pthread_proc,
	PVoid proc_params)
{
	return _M_thread_target.init(pthread_proc,proc_params);
}

HResult pecker_thread::init_thread_target(Ipecker_runable* ptarget)
{
	return _M_thread_target.init(ptarget);
}

HResult pecker_thread::init_thread(Ipecker_runable* ptarget,const thread_attributes* pattribute /* = null */, nSize thread_stack_size /* = 0 */, HFlag thread_creation_flag /* = 0 */)
{
	HResult init_result = _M_thread_target.init(ptarget);
	if (P_OK == init_result)
	{
		 if (null != pattribute)
		 {
			 _M_thread_attr = *pattribute;
			 _M_pthread_attr = &_M_thread_attr;
		 }
		 else
		 {
			 _M_pthread_attr = null;
		 }
		_M_thread_stack_size = thread_stack_size;
		_M_thread_creation_flag = thread_creation_flag;
	}
	return init_result;
}

HResult pecker_thread::init_thread(pecker_thread_proc_callback pthread_proc, PVoid proc_params, const thread_attributes* pattribute /* = null */, nSize thread_stack_size /* = 0 */, HFlag thread_creation_flag /* = 0 */)
{
	HResult init_result = _M_thread_target.init(pthread_proc,proc_params);
	if (P_OK == init_result)
	{
		if (null != pattribute)
		{
			_M_thread_attr = *pattribute;
			_M_pthread_attr = &_M_thread_attr;
		}
		else
		{
			_M_pthread_attr = null;
		}
		_M_thread_stack_size = thread_stack_size;
		_M_thread_creation_flag = thread_creation_flag;
	}
	return init_result;
}

HResult pecker_thread::start_thread(pecker_thread_proc_callback pthread_proc, PVoid proc_params, thread_attributes* pattribute /* = null */, nSize thread_stack_size /* = 0 */, HFlag thread_creation_flag /* = 0 */)
{
	if (P_OK == init_thread(pthread_proc,proc_params,pattribute,thread_stack_size,thread_creation_flag))
	{
		return pecker_thread_base::start_thread(&_M_thread_target,_M_pthread_attr,_M_thread_stack_size,_M_thread_creation_flag);
	}
	return P_ERR;
}

HResult pecker_thread::start_thread(Ipecker_runable* ptarget,thread_attributes* pattribute /*= null*/,
	nSize thread_stack_size /*= 0*/,
	HFlag thread_creation_flag /*= 0*/)
{
	if (P_OK == init_thread(ptarget,pattribute,thread_stack_size,thread_creation_flag))
	{
		return pecker_thread_base::start_thread(&_M_thread_target,_M_pthread_attr,_M_thread_stack_size,_M_thread_creation_flag);
	}
	return P_ERR;
}

HResult pecker_thread::start_thread()
{
	return pecker_thread_base::start_thread(&_M_thread_target,_M_pthread_attr,_M_thread_stack_size,_M_thread_creation_flag); 
}


PECKER_END

