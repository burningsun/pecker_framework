#ifndef LINUX_THREAD_H_
#define LINUX_THREAD_H_

#include "../pfx_defines.h"
#include "thread_param.h"

PECKER_BEGIN

typedef pthread_attr_t thread_attribute_t;
typedef pthread_t      thread_handle_t;

class linux_thread
{
public:
	typedef Ithread_proxy thread_proxy_interface_t;
private:
	thread_handle_t m_thread_handle;
	int             m_create_thread_status;
protected:
	static void* __on_thread_callback(void* lpParamers)
	{
		thread_proxy_interface_t* proxy_obect_ptr = (thread_proxy_interface_t*)lpParamers;
		if (proxy_obect_ptr)
		{
			long status;
			void* err_pointer;
			status = proxy_obect_ptr->run_proxy();
			err_pointer = (void*)status;
			return err_pointer;
		}
		return null;
	}
public:
	linux_thread ():m_thread_handle(0),m_create_thread_status(-1)
	{
		;
	}
	~linux_thread()
	{
		wait_thread_exit(2000);
	}

	inline thread_handle_t get_handle () const
	{
		return m_thread_handle;
	}

	inline result_t start_thread (
			thread_proxy_interface_t* __proxy_object,
			thread_attribute_t* thread_attr_ptr = 0,
			int wait_last_thread_time = 2000)
	{
		if (!__proxy_object)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		if (!m_create_thread_status)
		{
			wait_thread_exit(wait_last_thread_time);
		}

		m_create_thread_status = pthread_create(&m_thread_handle,
				thread_attr_ptr,
				__on_thread_callback,
				__proxy_object);

		if (m_create_thread_status)
		{
			printf ("pthread_create error = %d/n", m_create_thread_status);
		}
		return m_create_thread_status;
	}

	inline result_t wait_thread_exit (unsigned int timeout = 0xFFFFFFFF)
	{
		result_t status;
		if (0xFFFFFFFF != timeout)
		{
			timespec joinDelay;
			joinDelay.tv_nsec = timeout/1000;
			if (!m_create_thread_status)
			{
				status = pthread_timedjoin_np(m_thread_handle, NULL, &joinDelay); //等待线程结束
			}
			else
			{
				status = PFX_STATUS_OK;
			}
		}
		else
		{
			if (!m_create_thread_status)
			{
				status = pthread_join(m_thread_handle, NULL); //等待线程结束
			}
			else
			{
				status = PFX_STATUS_OK;
			}
		}

		if (PFX_STATUS_OK == status)
		{
			m_thread_handle = null;
			m_create_thread_status = -1;
		}
		else
		{
			status = terminal_thread();
		}
		return status;
	}

	inline result_t terminal_thread()
	{
		result_t status = 0;
		if (!m_create_thread_status)
		{
			status = pthread_cancel(m_thread_handle);
		}
		m_thread_handle = null;
		m_create_thread_status = -1;
		return status;
	}

};
PECKER_END

#endif
