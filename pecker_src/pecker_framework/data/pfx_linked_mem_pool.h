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
	typedef __listnode_allocator				allocator_t;
	typedef typename allocator_t::element_t		list_node_t;
	typedef typename list_node_t::element_t		element_t;
	typedef clinked_list < allocator_t >		list_t;
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

	PFX_INLINE result_t clean_alloc_pool_list()
	{
		list_t deallocate_alloc_list;
		critical_section_lock_t __lock;
		__lock.lock(m_alloc_locked);
		deallocate_alloc_list.swap(m_alloc_ls);
		__lock.unlock();
		return PFX_STATUS_OK;
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



#define DEFUALT_AUTO_RELEASE_POOL_TRIGER (32)


template < class __listnode_allocator >
class clinkedlist_memery_pool
{
public:
	typedef __listnode_allocator				allocator_t;
	typedef typename allocator_t::element_t		list_node_t;
	typedef typename list_node_t::element_t		element_t;
	typedef clinked_list < allocator_t >		list_t;
private:
	cs_t		m_locker;
	list_t		m_pool;
	usize__t	m_release_triger;
public:
	clinkedlist_memery_pool() :m_release_triger(DEFUALT_AUTO_RELEASE_POOL_TRIGER)
	{
		InitCriticalSection(&m_locker);
	}
	~clinkedlist_memery_pool()
	{
		DelCriticalSection(&m_locker);
	}
public:
	PFX_INLINE list_node_t* allocate_node()
	{
		list_node_t* node_ptr;

		if (m_pool.size())
		{
			critical_section_lock_t __lock;
			__lock.lock(m_locker);
			node_ptr = m_pool.pop_back();

		}
		else
		{
			node_ptr = list_t::new_node();
		}

		return node_ptr;
	}
	PFX_INLINE element_t* allocate()
	{
		if (m_pool.size())
		{
			critical_section_lock_t __lock;
			__lock.lock(m_locker);
			list_node_t* node_ptr = m_pool.pop_back();
			return &(node_ptr->get_element());
		}
		else
		{
			list_node_t* node_ptr = list_t::new_node();
			return &(node_ptr->get_element());
		}
	}

	PFX_INLINE result_t dellocate_node(list_node_t*& PARAM_INOUT del_ptr,
			usize__t triger_count = 0)
	{
		result_t status = PFX_STATUS_OK;
		if (del_ptr)
		{
			list_node_t* del_node_ptr = del_ptr;

			critical_section_lock_t __lock;
			__lock.lock(m_locker);
			del_node_ptr = m_pool.push_back(del_node_ptr);
			if (!del_node_ptr)
			{
				status = PFX_STATUS_FAIL;
			}
			else
			{
				del_ptr = null;

				if (!triger_count)
				{
					triger_count = m_release_triger;
				}

				if (triger_count < m_pool.size())
				{
					dispose_node(del_node_ptr);
				}
			}
		}
		else
		{
			auto_release_pool(triger_count);
		}

		return status;
	}

	PFX_INLINE result_t dellocate(element_t*& PARAM_INOUT del_ptr,
			usize__t triger_count = 0)
	{
		result_t status = PFX_STATUS_OK;
		if (del_ptr)
		{
			list_node_t* del_node_ptr = list_node_t::convert_unsafe(del_ptr);
			status = dellocate_node (del_node_ptr);
			if (PFX_STATUS_OK == status)
			{
				del_ptr = null;
			}
		}
		else
		{
			status = auto_release_pool(triger_count);
		}

		return status;
	}

	PFX_INLINE result_t dispose_node(list_node_t*& PARAM_INOUT node_ptr)
	{
		if (node_ptr)
		{
			return list_t::release_node(node_ptr);
		}
		else
		{
			return PFX_STATUS_OK;
		}
	}
	PFX_INLINE void set_triger_count (usize__t triger_count = 0)
	{
		if (triger_count)
		{
			m_release_triger = triger_count;
		}
	}
	PFX_INLINE result_t auto_release_pool(usize__t triger_count = 0)
	{
		if (!triger_count)
		{
			triger_count = m_release_triger;
		}

		critical_section_lock_t __lock;
		__lock.lock(m_locker);
		if (m_pool.size() > triger_count)
		{
			usize__t dispose_count = m_pool.size() - triger_count;
			while (dispose_count)
			{
				list_node_t* node_ptr = m_pool.pop_back();
				dispose_node(node_ptr);
				--dispose_count;
			}
		}
		return PFX_STATUS_OK;
	}

	PFX_INLINE result_t clean_pool()
	{
		list_t clean_pool;
		critical_section_lock_t __lock;
		__lock.lock(m_locker);
		clean_pool.swap(m_pool);
		return PFX_STATUS_OK;
	}



public:
	// 某些编译器对于模板内使用静态成员的时候，编译会出错，改写这种方式
	static clinkedlist_memery_pool& get_reference_pool()
	{
		static 	clinkedlist_memery_pool	pool;
		return pool;
	}
};

PECKER_END
#endif //PFX_LINKED_MEM_POOL_H_
