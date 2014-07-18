#include "syn_lock.h"

PECKER_BEGIN

__critical_section_lock::__critical_section_lock ():m_cs_ptr(NULL)
{

}
__critical_section_lock::~__critical_section_lock ()
{
	unlock();
}

int __critical_section_lock::lock(cs_t& __cs)
{
	if (!m_cs_ptr)
	{
		LockCriticalSection (&__cs);
		m_cs_ptr = &__cs;
		return 0;
	}
	else if (m_cs_ptr == &__cs)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int __critical_section_lock::unlock()
{
	if (m_cs_ptr)
	{
		cs_t* temp_cs_ptr = m_cs_ptr;
		m_cs_ptr = NULL;
		UnlockCriticalSection (temp_cs_ptr);
	}
	return 0;
}

const cs_t* __critical_section_lock::locked_cs () const
{
	return m_cs_ptr;
}

PECKER_END

