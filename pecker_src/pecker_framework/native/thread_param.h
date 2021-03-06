#ifndef THREAD_PARAM_H_
#define THREAD_PARAM_H_
#include "syn_lock.h"

PECKER_BEGIN

typedef struct st_proxy_status
{
	volatile int		m_status;
	void*				m_reverd_object_ptr;
	cs_t				m_lock;
	st_proxy_status ():m_status(0), m_reverd_object_ptr(NULL)
	{
		InitCriticalSection(&m_lock);
	}
	~st_proxy_status()
	{
		DelCriticalSection(&m_lock);
	}
}proxy_status_t;


struct Ithread_proxy
{
#ifdef __ANDROID__
	friend class android_thread;
private:
	volatile bool m_bExit_ok;
public:
#endif
	virtual ~Ithread_proxy(){;}
	virtual long run_proxy () = 0;
};

template < class __proxy_object, class __on_proxy_callback >
struct thread_proxy : public Ithread_proxy
{
	typedef __proxy_object			proxy_object_t;
	typedef __on_proxy_callback		proxy_callback_t;
	typedef thread_proxy < __proxy_object, __on_proxy_callback > thread_proxy_t;


	proxy_object_t*		m_object_ptr;
	proxy_callback_t	m_callback;
	proxy_status_t*		m_proxy_status;

	thread_proxy ():m_object_ptr(NULL),m_callback(NULL),m_bclone_obj(false)
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


	virtual Ithread_proxy* clone ()
	{
		thread_proxy_t* return_proxy_ptr = new thread_proxy_t;
		if (return_proxy_ptr)
		{
			*return_proxy_ptr = *this;
			return_proxy_ptr->m_bclone_obj = true;
		}
		return return_proxy_ptr;
	}
	virtual void release ()
	{
		if (m_bclone_obj)
		{
			delete this;
		}
	}
private:
	bool m_bclone_obj;
};

template < class __proxy_object, class __on_proxy_callback >
struct thread_proxy_proc : public Ithread_proxy
{
	typedef __proxy_object			proxy_object_t;
	typedef __on_proxy_callback		proxy_callback_t;
	typedef thread_proxy < __proxy_object, __on_proxy_callback > thread_proxy_t;


	proxy_object_t	*	m_object_ptr;
	proxy_callback_t	m_callback;
	proxy_status_t		m_proxy_status;

	thread_proxy_proc ():m_object_ptr(NULL),m_callback(NULL),m_bclone_obj(false)
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

	virtual Ithread_proxy* clone ()
	{
		thread_proxy_t* return_proxy_ptr = new thread_proxy_t;
		if (return_proxy_ptr)
		{
			*return_proxy_ptr = *this;
			return_proxy_ptr->m_bclone_obj = true;
		}
		return return_proxy_ptr;
	}
	virtual void release ()
	{
		if (m_bclone_obj)
		{
			delete this;
		}
	}
private:
	bool m_bclone_obj;
};

PECKER_END

#endif //THREAD_PARAM_H_
