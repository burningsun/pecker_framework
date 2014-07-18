#ifndef THREAD_PARAM_H_
#define THREAD_PARAM_H_
#include "syn_lock.h"

PECKER_BEGIN

typedef struct st_proxy_status
{
	volatile int		m_status;
	void*				m_reverd_object_ptr;
	cs_t					m_lock;
	st_proxy_status ():m_status(0), m_reverd_object_ptr(NULL)
	{
		InitCriticalSection(&m_lock);
	}
}proxy_status_t;


struct Ithread_proxy
{
	virtual ~Ithread_proxy(){;}
	virtual long run_proxy () = 0;
};

template < class __proxy_object, class __on_proxy_callback >
struct thread_proxy : public Ithread_proxy
{
	typedef __proxy_object			proxy_object_t;
	typedef __on_proxy_callback		proxy_callback_t;



	proxy_object_t	*	m_object_ptr;
	proxy_callback_t	m_callback;
	proxy_status_t*	m_proxy_status;

	thread_proxy ():m_object_ptr(NULL),m_callback(NULL)
	{
		;
	}
	~thread_proxy()
	{
		;
	}

	PFX_INLINE long run_proxy ()
	{
		if (m_object_ptr)
		{
			return (m_object_ptr->*m_callback) (m_proxy_status);
		}
		return 0;
	}
};

template < class __proxy_object, class __on_proxy_callback >
struct thread_proxy_proc : public Ithread_proxy
{
	typedef __proxy_object					proxy_object_t;
	typedef __on_proxy_callback		proxy_callback_t;



	proxy_object_t	*	m_object_ptr;
	proxy_callback_t	m_callback;
	proxy_status_t		m_proxy_status;

	thread_proxy_proc ():m_object_ptr(NULL),m_callback(NULL)
	{
		;
	}
	~thread_proxy_proc()
	{
		;
	}

	PFX_INLINE long run_proxy ()
	{
		if (m_callback)
		{
			return m_callback(m_object_ptr, &m_proxy_status);
		}
		return 0;
	}
};

PECKER_END

#endif //THREAD_PARAM_H_
