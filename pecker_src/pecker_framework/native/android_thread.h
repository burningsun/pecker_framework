#ifndef ANDROID_THREAD_H_
#define ANDROID_THREAD_H_

#include "../pfx_defines.h"
#include "thread_param.h"
#include "pfx_log.h"

PECKER_BEGIN

typedef pthread_attr_t thread_attribute_t;
typedef pthread_t      thread_handle_t;

class android_thread
{
public:
	typedef Ithread_proxy thread_proxy_interface_t;
private:
	thread_handle_t m_thread_handle;
	int             m_create_thread_status;

	thread_proxy_interface_t* m_last_thread_proxy_ptr;
protected:
	static void* __on_thread_callback(void* lpParamers)
	{
		thread_proxy_interface_t* proxy_obect_ptr = (thread_proxy_interface_t*)lpParamers;
		volatile long_t& __count = thread_count();
		++__count;
		if (proxy_obect_ptr)
		{
			long status;
			void* err_pointer;
			proxy_obect_ptr->m_bExit_ok = false;
			status = proxy_obect_ptr->run_proxy();
			proxy_obect_ptr->m_bExit_ok = true;
			err_pointer = (void*)status;
			--__count;
			return err_pointer;
		}
		--__count;
		return null;
	}
protected:
	static volatile long_t& thread_count()
	{
		static volatile long_t __count = 0;
		return __count;
	}
public:
	static volatile long_t get_thread_count()
	{
		return thread_count();
	}
public:
	android_thread ():m_thread_handle(0),m_create_thread_status(-1),
	m_last_thread_proxy_ptr(null)
	{
		;
	}
	~android_thread()
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
			PECKER_LOG_ERR ("pthread_create error = %d/n", m_create_thread_status);
		}

		m_last_thread_proxy_ptr = __proxy_object;
		return m_create_thread_status;
	}

	inline result_t wait_thread_exit (unsigned int timeout = 0xFFFFFFFF)
	{
		result_t status;
		if (0xFFFFFFFF != timeout)
		{
//			timespec joinDelay;
//			joinDelay.tv_nsec = timeout/1000;
			if (!m_create_thread_status)
			{
				const long minsleep_clip = 10;
				long remain_time = timeout/1000;
				//status = pthread_timedjoin_np(m_thread_handle, NULL, &joinDelay); //等待线程结束
				status = pthread_detach(m_thread_handle);

				while (remain_time && (m_last_thread_proxy_ptr)
						&&!(m_last_thread_proxy_ptr->m_bExit_ok))
				{
					if (remain_time < minsleep_clip)
					{
						SleepMS(remain_time);
						remain_time = 0;
						break;
					}
					else
					{
						SleepMS(minsleep_clip);
						remain_time -= minsleep_clip;
					}
				}

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
			//status = pthread_cancel(m_thread_handle);
			status = pthread_detach(m_thread_handle);

		}
		m_thread_handle = null;
		m_create_thread_status = -1;
		return status;
	}

};
PECKER_END

#endif //ANDROID_THREAD_H_
