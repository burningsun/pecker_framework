#ifndef SYN_LOCK_H_
#define 	SYN_LOCK_H_
#include "../pfx_defines.h"

PECKER_BEGIN
typedef CriticalSection	cs_t;

typedef class PFX_NATIVE_API __critical_section_lock
{
private:
	cs_t* m_cs_ptr;
public:
	__critical_section_lock ();
	~__critical_section_lock();
	const cs_t* locked_cs () const;
	int lock (cs_t& __cs);
	int unlock ();
}critical_section_lock_t;

PECKER_END

#endif //SYN_LOCK_H_
