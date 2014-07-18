#ifndef PFX_LINKED_MEM_POOL_H_
#define PFX_LINKED_MEM_POOL_H_
#include "../pfx_defines.h"
#include "../native/syn_lock.h"
#include "pfx_clist.h"
#include "../native/pecker_allocator.h"

PECKER_BEGIN

template < class __listnode_allocator >
class clinked_mem_pool
{
public:
	typedef __listnode_allocator							allocator_t;
	typedef typename allocator_t::element_t		list_node_t;
	typedef typename list_node_t::element_t		element_t;
	typedef clinked_list < allocator_t >	list_t;
private:
	cs_t	m_alloc_locked;
	cs_t	m_active_locked;
	list_t	m_alloc_ls;
	list_t	m_active_ls;
public:
	clinked_mem_pool()
	{
		InitCriticalSection(&m_active_locked);
		InitCriticalSection(&m_alloc_locked);
	}
	~clinked_mem_pool()
	{										
		dispose();
		DelCriticalSection(&m_active_locked);
		DelCriticalSection(&m_alloc_locked);
	}

	PFX_INLINE usize__t active_size() const
	{
		return m_active_ls.size();
	}
	PFX_INLINE usize__t alloc_pool_size() const
	{
		return m_alloc_ls.size();
	}

	PFX_INLINE list_node_t* allocate()
	{
		if (m_alloc_ls.is_empty())
		{
			return list_t::new_node();
		}
		else
		{
			critical_section_lock_t __lock;
			__lock.lock(m_alloc_locked);
			if (m_alloc_ls.is_empty())
			{
				return list_t::new_node();
			}
			else
			{
				return m_alloc_ls.pop_fornt();
			}
			__lock.unlock();
		}
	}

	PFX_INLINE result_t deallocate(list_node_t*& delnode)
	{
		critical_section_lock_t __lock;
		__lock.lock(m_alloc_locked);
		m_alloc_ls.push_back(delnode);
		delnode = null;
		__lock.unlock();
		return PFX_STATUS_OK;
	}
	PFX_INLINE result_t despose_node(list_node_t*& delnode)
	{
		return list_t::release_node(delnode);
	}
	
	PFX_INLINE list_node_t* fetch_active()
	{
		critical_section_lock_t __lock;
		__lock.lock(m_active_locked);
		return m_active_ls.pop_fornt();
	}
	PFX_INLINE list_node_t* push_active(list_node_t* active_ptr)
	{
		critical_section_lock_t __lock;
		__lock.lock(m_active_locked);
		return m_active_ls.push_back(active_ptr);
	}

	PFX_INLINE result_t clean_active_list(bool bRelease = false)
	{
		list_t deallocate_list;
		critical_section_lock_t __lock;
		__lock.lock(m_active_locked);
		deallocate_list.swap(m_active_ls);
		__lock.unlock();
		if (!bRelease)
		{
			critical_section_lock_t _lock;
			list_node_t* node_ptr = deallocate_list.pop_fornt();
			_lock.lock(m_alloc_locked);
			while (node_ptr)
			{
				m_alloc_ls.push_back(node_ptr);
				node_ptr = deallocate_list.pop_fornt();
			}
			_lock.unlock();
		}
	}

	PFX_INLINE result_t dispose()
	{
		list_t deallocate_alloc_list;
		list_t deallocate_active_list;

		critical_section_lock_t __lock;
		__lock.lock(m_alloc_locked);
		deallocate_alloc_list.swap(m_alloc_ls);
		__lock.unlock();

		critical_section_lock_t _lock;
		_lock.lock(m_active_locked);
		deallocate_active_list.swap(m_active_ls);
		__lock.unlock();

		return PFX_STATUS_OK;
	}

};

template < class __elem  >
class linked_mem_pool : public clinked_mem_pool < pecker_simple_allocator< clist_node< __elem > > >
{
	;
};

PECKER_END
#endif //PFX_LINKED_MEM_POOL_H_
