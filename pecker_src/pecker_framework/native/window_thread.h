#ifndef WINDOWS_THREAD_H_
#define WINDOWS_THREAD_H_

#include "../pfx_defines.h"
#include "thread_param.h"

PECKER_BEGIN
typedef struct st_thread_attr_t
{
	SECURITY_ATTRIBUTES				m_secure_attr_t;		//in
	size_t												stacksize;					//in
	DWORD											m_thread_id;			//out
}															thread_attribute_t;

typedef HANDLE								thread_handle_t;


class win_thread
{
public:
	typedef Ithread_proxy					thread_proxy_interface_t;
private:
	thread_handle_t								m_thread_handle;
	DWORD										m_threadID;
public:
	inline DWORD get_threadID() const
	{
		return m_threadID;
	}
protected:
static	DWORD	WINAPI	__on_thread_callback(LPVOID  lpParamers)
	{
		thread_proxy_interface_t*	proxy_obect_ptr = (thread_proxy_interface_t*)lpParamers;
		if (proxy_obect_ptr)
		{
			return proxy_obect_ptr->run_proxy();
		}
		return PFX_STATUS_FAIL;
	}
public:
	win_thread() :m_thread_handle(NULL), m_threadID(0)
	{
		;
	}
	~win_thread()
	{
		wait_thread_exit(2000);
	}

	inline thread_handle_t get_handle () const
	{
		return m_thread_handle;
	}

	inline result_t start_thread (
		thread_proxy_interface_t*	__proxy, 
		thread_attribute_t* thread_attr_ptr = NULL,
		int wait_last_thread_time = 2000)
	{
		if (!__proxy)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		result_t status = PFX_STATUS_OK;
		if (m_thread_handle)
		{
			wait_thread_exit(wait_last_thread_time);
		}
		if (thread_attr_ptr)
		{
			m_thread_handle = ::CreateThread(&thread_attr_ptr->m_secure_attr_t,
				thread_attr_ptr->stacksize,
				__on_thread_callback,
				__proxy,
				0,
				&(thread_attr_ptr->m_thread_id));
			m_threadID = thread_attr_ptr->m_thread_id;
		}
		else
		{
			//DWORD thread_id;
			m_thread_handle = 
				::CreateThread(NULL,
				0,
				__on_thread_callback,
				__proxy,
				0,
				&m_threadID);
		}
		
		if (!m_thread_handle)
		{
			status = PFX_STATUS_FAIL;
		}
		return status;
	}

	inline result_t wait_thread_exit (unsigned int timeout = 0xFFFFFFFF)
	{
		if (m_thread_handle)
		{
			int status;
			status = ::WaitForSingleObject(m_thread_handle,timeout);
			::CloseHandle(m_thread_handle);
			m_thread_handle = NULL;
			m_threadID = 0;
		}
		return PFX_STATUS_OK;
	}

	inline result_t terminal_thread()
	{
		if (m_thread_handle)
		{
			result_t status;
			status = ::TerminateThread(m_thread_handle,  DWORD(-1));
			::CloseHandle(m_thread_handle);
			m_thread_handle = NULL;
			m_threadID = 0;
			return status;
		}
		return PFX_STATUS_OK;
	}

};

PECKER_END
#endif //WINDOWS_THREAD_H_
