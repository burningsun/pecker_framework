/*
 * pfx_ref_root.h
 *
 *  Created on: 2014-8-23
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_REF_ROOT_H_
#define		PFX_REF_ROOT_H_

#include "../native/syn_lock.h"
#include "../native/pfx_disposeable.h"
#include "pfx_clist.h"
#include "pfx_linked_mem_pool.h"
#include "../native/pecker_allocator.h"
#include <new>

#ifdef REF_DEBUG
#include "../native/pfx_log.h"
#define REF_LOG_STR PECKER_LOG_STR
#define REF_LOG_INFO PECKER_LOG_INFO
#else
#define REF_LOG_STR(...)
#define REF_LOG_INFO(...)
#endif

PECKER_BEGIN


template< class __ref_obj, class __node_name_ >
struct cref_node
{
	typedef __node_name_ list_node_t;

	cref_node* 	m_prev_ptr;
	cref_node*  m_next_ptr;
	__ref_obj*  m_ref_ptr;

	cref_node() : m_prev_ptr(null), m_next_ptr(null), m_ref_ptr(null)
	{
		;
	}
	virtual ~cref_node()
	{
		m_ref_ptr = null;
		m_prev_ptr = null;
		m_next_ptr = null;

	}
	PFX_INLINE bool is_reference() const
	{
		return (m_next_ptr && m_prev_ptr);
	}

	PFX_INLINE const list_node_t*	get_prev_node() const
	{
		return (const list_node_t*)(m_prev_ptr);
	}
	PFX_INLINE const list_node_t*	get_next_node() const
	{
		return (const list_node_t*)(m_next_ptr);
	}
	PFX_INLINE list_node_t*	get_prev_node()
	{
		return (list_node_t*)(m_prev_ptr);
	}
	PFX_INLINE list_node_t*	get_next_node()
	{
		return (list_node_t*)(m_next_ptr);
	}
	PFX_INLINE void	set_prev_node(list_node_t* PARAM_IN node_ptr)
	{
		m_prev_ptr = (list_node_t*)node_ptr;
	}
	PFX_INLINE void	set_next_node(list_node_t* PARAM_IN node_ptr)
	{
		m_next_ptr = (list_node_t*)node_ptr;
	}
};




template < class __ref_node_allocator, class __ref_allocator >
struct ref_pool_memanger
{
	typedef __ref_node_allocator			 node_alloc_t;
	typedef typename node_alloc_t::element_t ref_node_t;
	typedef csyn_list< node_alloc_t >        list_t;
	

	typedef __ref_allocator ref_alloctor_t;
	typedef typename ref_alloctor_t::element_t ref_t;

	static PFX_INLINE ref_node_t* new_node()
	{
		ref_node_t* new_node_ptr = null;
		new_node_ptr = node_alloc_t::allocate_object();
		if (new_node_ptr)
		{
			new_node_ptr->m_ref_ptr = ref_alloctor_t::allocate_object();
		}
		return new_node_ptr;
	}
	static PFX_INLINE ref_node_t* new_node(list_t& __mem_pool, bool bNew_alloc = true)
	{
		ref_node_t* new_node_ptr = null;

		if (__mem_pool.size())
		{
			__mem_pool.lock();
			new_node_ptr = __mem_pool.pop_back();
			__mem_pool.unlock();
		}
		else
		{
			new_node_ptr = node_alloc_t::allocate_object();
		}

		if (new_node_ptr && bNew_alloc)
		{
			new_node_ptr->m_ref_ptr = ref_alloctor_t::allocate_object();
		}
		return new_node_ptr;
	}

	static PFX_INLINE result_t dispose_node(list_t& __mem_pool,
		list_t& __ref_pool, ref_node_t*& PARAM_INOUT __obj_node_ptr)
	{
		RETURN_INVALID_RESULT((!__obj_node_ptr), PFX_STATUS_INVALID_PARAMS);
		result_t status;
		ref_node_t* gc_ptr;
		usize__t pool_size;
		ref_t* __del_ref = null;
		__ref_pool.lock();

		pool_size = __ref_pool.size();
		if (pool_size)
		{
			gc_ptr = __ref_pool.remove_unsafe(__obj_node_ptr);
			__ref_pool.unlock();

			if (gc_ptr)
			{
				if (1 == pool_size)
				{
					__del_ref = gc_ptr->m_ref_ptr;
				}
				gc_ptr->m_ref_ptr = null;
				gc_ptr->~ref_node_t();				
				status = PFX_STATUS_OK;
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
			}

		}
		else
		{
			__ref_pool.unlock();
			
			gc_ptr = __obj_node_ptr;
			__del_ref = gc_ptr->m_ref_ptr;
			gc_ptr->m_ref_ptr = null;
			gc_ptr->~ref_node_t();
		}

	
		
		if (PFX_STATUS_OK == status)
		{
			if (__del_ref)
			{
				ref_alloctor_t::deallocate_object(__del_ref);
			}
			else if (gc_ptr)
			{
				__mem_pool.lock();
				if (null == __mem_pool.push_back(gc_ptr))
				{
					node_alloc_t::deallocate_object(gc_ptr);
				}
				__mem_pool.unlock();
			}

			__obj_node_ptr = null;

		}

		return status;
		
	}


	static PFX_INLINE ref_node_t* new_share(list_t& __mem_pool, 
		list_t& __ref_pool, ref_node_t* PARAM_INOUT __obj_node_ptr)
	{
		ref_node_t* new_share_ptr = new_node(__mem_pool, false);
		RETURN_INVALID_RESULT((null == new_share_ptr), null);
		__ref_pool.lock();
		if (!__ref_pool.size() && !__obj_node_ptr->is_reference())
		{
			__ref_pool.push_back(__obj_node_ptr);
		}
		new_share_ptr->m_ref_ptr = __obj_node_ptr->m_ref_ptr;
		__ref_pool.push_back(new_share_ptr);
		__ref_pool.unlock();
		return new_share_ptr;
	}
};

#define  DECLARE_REF_NODE_CLASS_BEGIN(THIS_CLASS_NAME,NATIVE_REF,INTERFACE_NAME,BASE_NAME)	\
class THIS_CLASS_NAME : public cref_node< NATIVE_REF, THIS_CLASS_NAME >, \
	public INTERFACE_NAME{ \
protected: typedef cref_node< NATIVE_REF, THIS_CLASS_NAME > BASE_NAME; \

#define DECLARE_REF_NODE_CLASS_END };


// NATIVE
#define DECLARE_FRIEND_CLASS(FRIEND_CLASS)\
	friend FRIEND_CLASS;

#define DECLARE_NATIVE_REF_MEMBER(NODE_ALLOCATOR)\
	csyn_list < NODE_ALLOCATOR > m_mem_list; \
	csyn_list < NODE_ALLOCATOR > m_ref_list;

#define DEFINE_NATIVE_REF_POOL(REF_NODE_ALLOC, REF_ALLOC)\
	typedef ref_pool_memanger< REF_NODE_ALLOC, REF_ALLOC >	 ref_pool_memanger_t;

#define DECLARE_NATIVE_CREATE_NEW_NODE(NODE_NAME,FUNC_NAME)	\
	static PFX_INLINE NODE_NAME * FUNC_NAME();

#define STATIC_NATIVE_CREATE_NEW_NODE(NATIVE_NAME,NODE_NAME,FUNC_NAME) \
	PFX_INLINE NODE_NAME * NATIVE_NAME::FUNC_NAME() \
{ \
	return ref_pool_memanger_t::new_node(); \
}  \

#define DECLARE_NATIVE_CREATE_SHARE_NODE(NODE_NAME,FUNC_NAME)	\
	PFX_INLINE NODE_NAME * FUNC_NAME(NODE_NAME* PARAM_INOUT in_ptr);

#define NATIVE_CREATE_SHARE_NODE(NATIVE_NAME,NODE_NAME,FUNC_NAME)	\
	NODE_NAME* NATIVE_NAME::FUNC_NAME(NODE_NAME* PARAM_INOUT in_ptr) \
{										   \
	return ref_pool_memanger_t::new_share(m_mem_list, m_ref_list, in_ptr); \
}										   \

#define DECLARE_NATIVE_DISPOSE_SHARE_NODE(NODE_NAME,FUNC_NAME)	\
	PFX_INLINE result_t FUNC_NAME(NODE_NAME* PARAM_INOUT in_ptr) \

#define NATIVE_DISPOSE_SHARE_NODE(NATIVE_NAME,NODE_NAME,FUNC_NAME)	\
	result_t NATIVE_NAME::FUNC_NAME(NODE_NAME* PARAM_INOUT in_ptr) \
{										   \
	return ref_pool_memanger_t::dispose_node(m_mem_list, m_ref_list, in_ptr); \
}			 \

// NODE
#define DECLARE_REF_CREATE_NEW_NODE(NODE_NAME,FUNC_NAME)	\
	static PFX_INLINE NODE_NAME * FUNC_NAME();

#define STATIC_REF_CREATE_NEW_NODE(REF_NAME, NODE_NAME,FUNC_NAME,NATIVE_FUNC_NAME) \
	NODE_NAME * NODE_NAME::FUNC_NAME() \
{ \
	return REF_NAME::NATIVE_FUNC_NAME(); \
}  \

#define DECLARE_REF_CREATE_SHARE_NODE(NODE_NAME,FUNC_NAME)	\
	PFX_INLINE NODE_NAME * FUNC_NAME();

#define REF_CREATE_SHARE_NODE(BASE_NAME,NODE_NAME,FUNC_NAME,NATIVE_FUNC_NAME)	\
	 NODE_NAME* NODE_NAME::FUNC_NAME() \
{										   \
if (BASE_NAME::m_ref_ptr)\
  {													\
  return BASE_NAME::m_ref_ptr->NATIVE_FUNC_NAME(this); \
}													\
  else			  \
  {				   \
  return null;	\
}					 \
}										   \

#define DECLARE_REF_DISPOSE_SHARE_NODE(NODE_NAME,FUNC_NAME)	\
	PFX_INLINE result_t FUNC_NAME() \

#define REF_DISPOSE_SHARE_NODE(BASE_NAME,NODE_NAME,FUNC_NAME,NATIVE_FUNC_NAME)	\
	 result_t NODE_NAME::FUNC_NAME() \
{										   \
  if (BASE_NAME::m_ref_ptr)			\
  {		   \
    return BASE_NAME::m_ref_ptr->NATIVE_FUNC_NAME(this);	 \
  }\
  else\
  {	  \
    return PFX_STATUS_OK;\
  }		 \
}\
  




PECKER_END


#endif			//PFX_REF_ROOT_H_
