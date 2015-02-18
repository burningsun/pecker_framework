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

#define REF_DEBUG
#undef REF_LOG_STR
#undef REF_LOG_INFO
#ifdef REF_DEBUG
#include "../native/pfx_log.h"
#define REF_LOG_STR PECKER_LOG_STR
#define REF_LOG_INFO PECKER_LOG_INFO
#else
#define REF_LOG_STR(...)
#define REF_LOG_INFO(...)
#endif

PECKER_BEGIN

class creference_root
{
private:
	usize__t m_reference_count;
public:
	usize__t get_ref_count() const
	{
		return m_reference_count;
	}
protected:
	creference_root():m_reference_count(0){ ; }
	virtual ~creference_root()
	{ 
		m_reference_count = 0;
	}
	virtual result_t real_dispose()
	{
		m_reference_count = 0;
		return PFX_STATUS_OK;
	}
public:
	PFX_INLINE creference_root* share()
	{
		++m_reference_count;
		return this;
	}
	PFX_INLINE result_t dispose()
	{
		if (0 == m_reference_count)
		{
			return real_dispose();
		}
		else 
		{
			--m_reference_count;
			return PFX_STATUS_OK;
		}
	}
	virtual creference_root* new_object() = 0; 
};

//#define DELARE_REF_METHOD(THIS_CLASS_NAME,INTERFACE_NAME,THIS_ALLOCATOR) __NATIVE_DELARE_REF_METHOD(THIS_CLASS_NAME,THIS_ALLOCATOR)

#define DELARE_REF_METHOD(THIS_CLASS_NAME,INTERFACE_NAME,THIS_ALLOCATOR) \
	DELARE_REF_METHOD_S(THIS_CLASS_NAME, INTERFACE_NAME, THIS_ALLOCATOR, native_t)\
	__NATIVE_REF_METHOD


#define DELARE_REF_METHOD_S(THIS_CLASS_NAME,INTERFACE_NAME,THIS_ALLOCATOR, NATIVE_TYPE) 	\
    __DELARE_REF_METHOD(THIS_CLASS_NAME, THIS_ALLOCATOR)\
	__NATIVE_REF_METHOD_X(NATIVE_TYPE)


#define __NATIVE_REF_METHOD_X(native_type)				\
public: \
virtual	PFX_INLINE void get_native_ptr(native_type*& native_ptr)			 \
{										 \
	native_ptr = &m_native;				 \
}										 \
virtual	PFX_INLINE void get_native_ptr(const native_type*& native_ptr) const\
{										 \
	native_ptr = &m_native;				 \
}										 \


#define __NATIVE_REF_METHOD				\
public: \
PFX_INLINE native_t& native()			 \
{										 \
return m_native;					 \
}										 \
PFX_INLINE const native_t& native() const\
{										  \
return m_native;					  \
}										  \
PFX_INLINE native_t* native_ptr()			 \
{										 \
return &m_native;					 \
}										 \
PFX_INLINE const native_t* native_ptr() const\
{										  \
return &m_native;					  \
}										  \

#define __NATIVE_DELARE_REF_METHOD_S(THIS_CLASS_NAME,THIS_ALLOCATOR,NATIVE_TYPE) \
	__DELARE_REF_METHOD(THIS_CLASS_NAME, THIS_ALLOCATOR)\
	__NATIVE_REF_METHOD_X(NATIVE_TYPE)

#define __NATIVE_DELARE_REF_METHOD(THIS_CLASS_NAME,THIS_ALLOCATOR) \
	__DELARE_REF_METHOD(THIS_CLASS_NAME, THIS_ALLOCATOR)\
	__NATIVE_REF_METHOD\
	__NATIVE_REF_METHOD_X(native_t)


#define __DELARE_REF_METHOD(THIS_CLASS_NAME,THIS_ALLOCATOR) \
protected:\
virtual PFX_INLINE result_t __real_dispose()\
{									 \
	THIS_CLASS_NAME* del_ptr = this;  \
	REF_LOG_INFO("__real_dispose (%d)", creference_root::get_ref_count()); \
	return THIS_ALLOCATOR::deallocate_object(del_ptr);\
}  \
public:\
virtual PFX_INLINE THIS_CLASS_NAME* new_ref()  \
{										\
		if (creference_root::share())	 \
		{	\
			REF_LOG_INFO("new_ref (%d)", creference_root::get_ref_count());\
			return this;\
		}	\
        else\
       {\
	      return null;\
	    }\
	}	\
virtual PFX_INLINE THIS_CLASS_NAME * create_object()	\
{													\
	return create_new_object();						 \
}													\
static PFX_INLINE THIS_CLASS_NAME * create_new_object()\
{											\
	return THIS_ALLOCATOR::allocate_object();  \
}											\
virtual PFX_INLINE creference_root* new_object() \
{										 \
	return create_object();				 \
}										 \
virtual PFX_INLINE result_t dispose_object()	  \
{										  \
	result_t status = creference_root::dispose();\
	REF_LOG_INFO("dispose (%d)", creference_root::get_ref_count());\
	return status;	 \
} \

template < class __native_ref >
class simple_ref : public creference_root
{
	typedef simple_ref < __native_ref >	ref_root_t;
	typedef pecker_simple_allocator< ref_root_t > ref_alloc_t;
	typedef __native_ref native_t;
	friend struct pecker_simple_allocator< ref_root_t >;
private:
	native_t m_native;
protected:
	simple_ref()
	{
		REF_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
	virtual ~simple_ref()
	{
		REF_LOG_INFO("release...0x%08X", (lpointer_t)this);
	}
	virtual result_t real_dispose()
	{
		return __real_dispose();
	}
public:
	__NATIVE_DELARE_REF_METHOD(ref_root_t, ref_alloc_t);
};





/////////////////////////////////////////////////////////

template< class __ref_obj, class __node_name_ >
struct cref_node
{
	typedef __node_name_ list_node_t;

protected:
	list_node_t* m_prev_ptr;
	list_node_t* m_next_ptr;
public:
	__ref_obj*   m_ref_ptr;

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
		return m_prev_ptr;
	}
	PFX_INLINE const list_node_t*	get_next_node() const
	{
		return m_next_ptr;
	}
	PFX_INLINE list_node_t*	get_prev_node()
	{
		return m_prev_ptr;
	}
	PFX_INLINE list_node_t*	get_next_node()
	{
		return m_next_ptr;
	}
	PFX_INLINE void	set_prev_node(list_node_t* PARAM_IN node_ptr)
	{
		m_prev_ptr = node_ptr;
	}
	PFX_INLINE void	set_next_node(list_node_t* PARAM_IN node_ptr)
	{
		m_next_ptr = node_ptr;
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
	typedef ref_pool_memanger< __ref_node_allocator, __ref_allocator > ref_pool_memanger_t;

	list_t m_mem_pool;
	list_t m_ref_pool;

	PFX_INLINE result_t  dispose_node(ref_node_t*& PARAM_INOUT __obj_node_ptr)
	{
		return ref_pool_memanger_t::dispose_node(m_mem_pool, m_ref_pool, __obj_node_ptr);
	}
	PFX_INLINE ref_node_t* new_share(ref_node_t* PARAM_INOUT __obj_node_ptr)
	{
		return ref_pool_memanger_t::new_share(m_mem_pool, m_ref_pool, __obj_node_ptr);
	}

	static PFX_INLINE ref_node_t* create_node()
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
			// 后面的dispose_node会调用析构函数，所以导致内存池里面捞出来的对象，虚表缺失
			// 该静态函数主要用于解决构造函数是private的情况下，对现有内存的构造
			ref_node_t::reinit(new_node_ptr);
			
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
			status = PFX_STATUS_OK;
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


// 由于部分编译器，对于模板使用预定义的类型会出现语法错误，所以使用c常用的宏代替
// 这部分的设计，当然为了调试方便，下面的代码都做得很精简，功能性代码都封装起来

// 主要这蛋疼玩意是为了兼容像gcc 4.6以下无法直接friend typedef类型的编译器
#define DECLARE_BE_REF_POOL_MEMANGER_FRIEND(REF_NODE_ALLOC, REF_ALLOC) \
	friend struct ref_pool_memanger< REF_NODE_ALLOC, REF_ALLOC >; \
	friend class  clinked_list < REF_NODE_ALLOC >; \
	friend class  clinked_list_iterator< REF_NODE_ALLOC::element_t >; \
	friend struct linked_list_operation< REF_NODE_ALLOC::element_t >; \

//friend REF_NODE_ALLOC::element_t* ref_pool_memanger< REF_NODE_ALLOC, REF_ALLOC >::create_node(); \

// 公共继承， cref_node内的东西可以随便访问
#define  DECLARE_REF_NODE_CLASS_BEGIN(THIS_CLASS_NAME,NATIVE_REF,INTERFACE_NAME,BASE_NAME)	\
class THIS_CLASS_NAME : public cref_node< NATIVE_REF, THIS_CLASS_NAME >, \
	public INTERFACE_NAME{ \
protected: typedef cref_node< NATIVE_REF, THIS_CLASS_NAME > BASE_NAME; \
public: PFX_INLINE NATIVE_REF* ref_ptr() \
{                                         \
	return BASE_NAME::m_ref_ptr;          \
}										  \
public: PFX_INLINE const NATIVE_REF* ref_ptr() const\
{                                         \
	return BASE_NAME::m_ref_ptr;          \
}\
public: static PFX_INLINE THIS_CLASS_NAME* reinit(THIS_CLASS_NAME* PARAM_INOUT __ptr)\
{								  \
if (__ptr && null == __ptr->ref_ptr())   \
   {								\
      new(__ptr)THIS_CLASS_NAME(); \
   }								\
  return __ptr;						\
}									\

// 保护继承， cref_node内的东西只能自己，派生类，和友元访问
#define  DECLARE_REF_NODE_CLASS_PROTECTED_BEGIN(THIS_CLASS_NAME,NATIVE_REF,INTERFACE_NAME,BASE_NAME,REF_NODE_ALLOC,REF_ALLOC)	\
class THIS_CLASS_NAME : protected cref_node< NATIVE_REF, THIS_CLASS_NAME >, \
	public INTERFACE_NAME{ \
protected: typedef cref_node< NATIVE_REF, THIS_CLASS_NAME > BASE_NAME; \
public:	DECLARE_BE_REF_POOL_MEMANGER_FRIEND(REF_NODE_ALLOC, REF_ALLOC); \
public: PFX_INLINE NATIVE_REF* ref_ptr() \
{                                         \
	return BASE_NAME::m_ref_ptr;          \
}										  \
public: PFX_INLINE const NATIVE_REF* ref_ptr() const\
{                                         \
	return BASE_NAME::m_ref_ptr;          \
}\
public: static PFX_INLINE THIS_CLASS_NAME* reinit(THIS_CLASS_NAME* PARAM_INOUT __ptr)\
{								  \
if (__ptr && null == __ptr->ref_ptr())   \
   {								\
   new(__ptr)THIS_CLASS_NAME(); \
}								\
	return __ptr;						\
}									\


#define DECLARE_REF_NODE_CLASS_END };


// NATIVE
#define DECLARE_FRIEND_CLASS(FRIEND_CLASS)\
	friend FRIEND_CLASS;

#define DEFINE_NATIVE_REF_POOL(REF_NODE_ALLOC, REF_ALLOC, M_POOL_NAME)\
	typedef ref_pool_memanger< REF_NODE_ALLOC, REF_ALLOC >	 ref_pool_memanger_t; \
	protected: ref_pool_memanger_t M_POOL_NAME; \

#define DECLARE_NATIVE_CREATE_NEW_NODE(NODE_NAME,FUNC_NAME)	\
	static PFX_INLINE NODE_NAME * FUNC_NAME();

#define STATIC_NATIVE_CREATE_NEW_NODE(NATIVE_NAME,NODE_NAME,FUNC_NAME) \
	PFX_INLINE NODE_NAME * NATIVE_NAME::FUNC_NAME() \
{ \
	return ref_pool_memanger_t::create_node(); \
}  \

#define DECLARE_NATIVE_CREATE_SHARE_NODE(NODE_NAME,FUNC_NAME)	\
	PFX_INLINE NODE_NAME * FUNC_NAME(NODE_NAME* PARAM_INOUT in_ptr);

#define NATIVE_CREATE_SHARE_NODE(NATIVE_NAME,NODE_NAME,FUNC_NAME,M_POOL_NAME)	\
	NODE_NAME* NATIVE_NAME::FUNC_NAME(NODE_NAME* PARAM_INOUT in_ptr) \
{										   \
	return M_POOL_NAME.new_share(in_ptr); \
}										   \

#define DECLARE_NATIVE_DISPOSE_SHARE_NODE(NODE_NAME,FUNC_NAME)	\
	PFX_INLINE result_t FUNC_NAME(NODE_NAME* PARAM_INOUT in_ptr) \

#define NATIVE_DISPOSE_SHARE_NODE(NATIVE_NAME,NODE_NAME,FUNC_NAME,M_POOL_NAME)	\
	result_t NATIVE_NAME::FUNC_NAME(NODE_NAME* PARAM_INOUT in_ptr) \
{										   \
	return M_POOL_NAME.dispose_node(in_ptr); \
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
  
template < class __share_object >
struct simple_reference
{
	class sref_node;
	class sref_native;

	typedef struct pecker_simple_allocator< sref_native > ref_alloc;
	typedef struct pecker_simple_allocator< sref_node >   node_alloc;
	typedef struct ref_pool_memanger< node_alloc, ref_alloc> ref_pool_t;

	class sref_native
	{
		friend class sref_node;
		friend struct pecker_simple_allocator< sref_native >;
	private:
		__share_object m_native;
		ref_pool_t m_ref_pool;
	public:
		__share_object& native()
		{
			return m_native;
		}

		const __share_object& native() const
		{
			return m_native;
		}

	private:
		sref_native()
		{
			REF_LOG_INFO("create...0x%08X", (lpointer_t)this);;
		}
	public:
		virtual ~sref_native()
		{
			REF_LOG_INFO("release...0x%08X", (lpointer_t)this);;
		}
	protected:
		static sref_node* new_object();
		sref_node* share_object(sref_node* __ptr);
		result_t   dispose_node(sref_node* __ptr);
	};

	class sref_node : public cref_node < sref_native, sref_node >
	{
		friend class sref_native;
		friend struct pecker_simple_allocator< sref_node >;
	protected: 
		typedef cref_node< sref_native, sref_node > base_t; 

	public: 
		PFX_INLINE sref_native* ref_ptr() 
	{                                        
				return base_t::m_ref_ptr;          
	}										 
	public: 
		PFX_INLINE const sref_native* ref_ptr() const
	{                                         
	           return base_t::m_ref_ptr;          
	}
	public: 
		static PFX_INLINE sref_node* reinit(sref_node* PARAM_INOUT __ptr)
	    {								  
			   if (__ptr && null == __ptr->ref_ptr())   
			   {								
				   new(__ptr)sref_node();
			   }							
			   return __ptr;						
	    }									
		PFX_INLINE __share_object* native_ptr()
		{
			if (this->ref_ptr())
			{
				return &(this->ref_ptr()->native());
			}
			else
			{
				return null;
			}
		}
	private:
		sref_node()
		{
			REF_LOG_INFO("create...0x%08X", (lpointer_t)this);;
		}
	public:
		virtual ~sref_node()
		{
			REF_LOG_INFO("release...0x%08X", (lpointer_t)this);
			dispose_node();
		}

		static sref_node* new_object()
		{
			return sref_native::new_object();
		}

		sref_node* new_share()
		{
			if (this->ref_ptr())
			{
				return this->ref_ptr()->share_object(this);
			}
			else
			{
				return null;
			}
		}

		result_t dispose_node()
		{
			if (this->ref_ptr())
			{
				result_t status;
				status = this->ref_ptr()->dispose_node(this);
				return status;
			}

			return PFX_STATUS_OK;

		}
	};


};

template < class __share_object >
typename simple_reference< __share_object >::sref_node* 
simple_reference< __share_object >::sref_native::new_object()
{
	return ref_pool_t::create_node();
}

template < class __share_object >
typename simple_reference< __share_object >::sref_node*
simple_reference< __share_object >::sref_native::share_object
(typename simple_reference< __share_object >::sref_node* __ptr)
{
	return m_ref_pool.new_share(__ptr);
}

template < class __share_object >
result_t simple_reference< __share_object >::sref_native::dispose_node
(typename simple_reference< __share_object >::sref_node* __ptr)
{
	return m_ref_pool.dispose_node(__ptr);
}



PECKER_END


#endif			//PFX_REF_ROOT_H_
