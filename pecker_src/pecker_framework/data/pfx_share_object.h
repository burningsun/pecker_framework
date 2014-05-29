/*
 * pfx_share_object.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHARE_OBJECT_H_
#define		PFX_SHARE_OBJECT_H_

#include "pfx_data_traits.h"
#include "pfx_clist.h"

PECKER_BEGIN

template < class __alloc >
class PFX_DATA_TEMPALE_API cauto_release_object
{
public:
	typedef typename __alloc															allocator_t;
	typedef typename allocator_t::element_t								element_t;
	typedef typename cauto_release_object < allocator_t >	auto_release_obj_t;
private:
	element_t*&	m_obj_ptr;
public:
	cauto_release_object ()
	{
		static element_t* null_element = null;
		m_obj_ptr = null_element;
	}
	explicit cauto_release_object (element_t*& objcet_ptr): m_obj_ptr (objcet_ptr)
	{
		;
	}
	 ~cauto_release_object()
	 {
		 if (m_obj_ptr)
		 {
			 allocator_t::deallocate_object (m_obj_ptr);
			 m_obj_ptr = null;
		 } 
	 }
protected:
	cauto_release_object (const auto_release_obj_t& __other): m_obj_ptr (__other.m_obj_ptr)
	{
		;
	}
};

template < class __alloc >
class PFX_DATA_TEMPALE_API cauto_release_buffer
{
public:
	typedef typename __alloc															allocator_t;
	typedef typename allocator_t::element_t								element_t;
	typedef typename cauto_release_object < allocator_t >	auto_release_obj_t;
private:
	element_t*& m_buffer_ptr;
public:
	cauto_release_buffer ()
	{
		static element_t* null_element = null;
		m_buffer_ptr = null_element;
	}
	explicit cauto_release_buffer (element_t*& buffer_ptr): m_buffer_ptr (buffer_ptr)
	{
		;
	}
	~cauto_release_buffer()
	{
		if (m_buffer_ptr)
		{
			allocator_t::deallocate_objects (m_buffer_ptr);
			m_buffer_ptr = null;
		} 
	}
protected:
	cauto_release_buffer (const auto_release_obj_t& __other): m_obj_ptr (__other.m_obj_ptr)
	{
		;
	}
};

template < class leakable_object >
class PFX_DATA_TEMPALE_API cshare_leakable_object
{
public:
	typedef typename leakable_object								leakable_object_t;
	typedef typename leakable_object_t::allocator_t	allocator_t;
	typedef typename leakable_object_t::element_t		element_t;
	typedef typename leakable_object_t::leak_data_t	leak_data_t;

	typedef typename	cshare_leakable_object < leakable_object_t > cshare_leakable_object_t;
	typedef  typename	cshare_leakable_object_t	clist_node_t;
	typedef typename	clist_base < clist_node_t >	clist_t;

	typedef class clock_object  
	{
	public:
		friend cshare_leakable_object_t;
	private:
		leakable_object_t							m_new_object;
		cshare_leakable_object_t*			m_old_object_ptr;
		boolean_t											m_lock;
		boolean_t											m_locked;
			
	public:
		clock_object ():m_old_object_ptr(null), m_lock (PFX_BOOL_FALSE),
			m_locked(PFX_BOOL_FALSE)
		{;}
		~clock_object()
		{
			unlock_object();
			m_old_object_ptr	= null;
			m_lock						= PFX_BOOL_FALSE;
			m_locked					= PFX_BOOL_FALSE;
		}
	protected:
		clock_object (const clock_object& __other):m_new_object (__other.m_new_object),
			m_old_object_ptr(__other.m_old_object_ptr), m_lock (__other.m_lock),
			m_locked(__other.m_locked)
		{
		}
		PFX_INLINE  result_t  lock_object(boolean_t __clone = PFX_BOOL_FALSE);
		PFX_INLINE result_t unlock_object ();
	public:
		PFX_INLINE const cshare_leakable_object_t& const_lock_object () const
		{
			return *m_old_object_ptr;
		}

		PFX_INLINE leakable_object_t* lock_modify_object(boolean_t __restore = PFX_BOOL_FALSE)
		{			
			RETURN_RESULT (!m_locked, null);

			m_lock = PFX_BOOL_TRUE;

			if (m_old_object_ptr)
			{
				if (m_old_object_ptr->is_shared())
				{
					if (__restore)
					{
						m_old_object_ptr->m_share_obj.deep_copy_to (m_new_object);
					}
					return &m_new_object;
				}
				else
				{
					return  &(m_old_object_ptr->m_share_obj);
				}
			}
			else
			{
				return &m_new_object;
			}

		}


	}lock_object_t;

	friend clist_t; 
private:
	leakable_object_t	m_share_obj;
	clist_node_t*			m_prev_node_ptr;
	clist_node_t*			m_next_node_ptr;
protected:
	PFX_INLINE const clist_node_t*	get_prev_node () const
	{
		return m_prev_node_ptr;
	}
	PFX_INLINE const clist_node_t*	get_next_node () const
	{
		return m_next_node_ptr;
	}
	PFX_INLINE void								set_prev_node (clist_node_t* PARAM_IN node_ptr)
	{
		m_prev_node_ptr = node_ptr;
	}
	PFX_INLINE void								set_next_node  (clist_node_t* PARAM_IN node_ptr)
	{
		m_next_node_ptr = node_ptr;
	}
	PFX_INLINE clist_node_t*				get_prev_node_ref ()
	{
		return m_prev_node_ptr;
	}
	PFX_INLINE clist_node_t*				get_next_node_ref ()
	{
		return m_next_node_ptr;
	}
public:
	cshare_leakable_object () : m_prev_node_ptr(null), m_next_node_ptr(null)
	{
		;
	}
	~cshare_leakable_object()
	{
		release_object();
	}
protected:
	cshare_leakable_object (const cshare_leakable_object_t& __other)
	{
		m_prev_node_ptr = null;
		m_next_node_ptr = null;
		__other.copy_to(*this);
	}
public:
	PFX_INLINE const leakable_object_t& const_reference () const
	{
		return m_share_obj;
	}

	PFX_INLINE result_t release_object ();
	PFX_INLINE result_t share (cshare_leakable_object_t& __other);
	PFX_INLINE boolean_t is_shared () const
	{
		return (boolean_t)(get_prev_node() || get_next_node());
	}

	PFX_INLINE lock_object_t& lock_bits (lock_object_t& __lock, 
		boolean_t __clone = PFX_BOOL_FALSE)
	{
		__lock.m_old_object_ptr = this;
		__lock.lock_object(__clone);
		return __lock;
	}
	PFX_INLINE result_t unlock_bits (lock_object_t& __lock)
	{
		if (__lock.m_old_object_ptr != this)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		else
		{
			return __lock.unlock_object();
		}
	}

};

template < class __alloc >
class PFX_DATA_TEMPALE_API cleakable_object_packet
{
public:
	typedef typename __alloc								allocator_t;
	typedef typename allocator_t::element_t	element_t;

	typedef typename cleakable_object_packet < allocator_t >	cpacket_t;

	typedef typename cpacket_t							cleakable_obj_t;

	typedef class cleak_data
	{
		friend cpacket_t;
	private:
		element_t*	m_packet_ptr;
	}leak_data_t;
	
private:
	element_t* m_packet_ptr;
public:
	cleakable_object_packet ():m_packet_ptr(null)
	{
		;
	}
	~cleakable_object_packet()
	{
		clear();
	}
protected:
	cleakable_object_packet (cpacket_t& __other)
	{
		m_packet_ptr = null;
		__other.copy_to(*this);
	}
public:
	PFX_INLINE leak_data_t& leak_memery_to (leak_data_t& PARAM_OUT __packet)
	{
		__packet.m_packet_ptr = m_packet_ptr;
		this->m_packet_ptr			= null;
		return __packet;
	};

	static PFX_INLINE result_t free_leak_block (leak_data_t& PARAM_INOUT __packet)
	{
		 cpacket_t __freepacket;
		__freepacket.m_packet_ptr	=	__packet.m_packet_ptr;
		__packet.m_packet_ptr			= null;
		return PFX_STATUS_OK;
	}

	PFX_INLINE result_t shallow_copy_to (cpacket_t & PARAM_OUT __packet) const
	{
		result_t status = __packet.clear ();
		if (PFX_STATUS_OK == status)
		{
			__packet.m_packet_ptr = this->m_packet_ptr;
		}
		return status;
	}

	PFX_INLINE result_t deep_copy_to (cpacket_t& PARAM_OUT __packet) const
	{
		return copy_to(__packet);
	}
public:
	PFX_INLINE void swap (cpacket_t& __other)
	{
		if (&__other != this)
		{
			element_t* tmp_ptr		= __other.m_packet_ptr;
			__other.m_packet_ptr	= this->m_packet_ptr;
			this->m_packet_ptr			= tmp_ptr;
		}
	}
	PFX_INLINE result_t init ()
	{
		result_t status;
		if (!m_packet_ptr)
		{
			m_packet_ptr = allocator_t::allocate_object ();
		}

		if (m_packet_ptr)
		{
			status = PFX_STATUS_OK;
		}
		else
		{
			status = PFX_STATUS_MEM_LOW;
		}
		
		return status;
	}
	PFX_INLINE result_t copy_to (cpacket_t& PARAM_OUT __packet) const
	{
		result_t status;
		if (&__packet != this)
		{
			if (this->m_packet_ptr)
			{
				FOR_ONE_LOOP_BEGIN
				
				if (!__packet.m_packet_ptr)
				{
					status = __packet.init ();
					BREAK_LOOP_CONDITION (PFX_STATUS_OK != status)
				}
				__packet.m_packet_ptr[0] = this->m_packet_ptr[0];
				status = PFX_STATUS_OK;

				FOR_ONE_LOOP_END
			}
			else
			{
				status = __packet.clear();
			}
		}
		else
		{
			status = PFX_STATUS_OK;
		}
		return status;
	}
	PFX_INLINE result_t clear ()
	{
		result_t status;
		if (m_packet_ptr)
		{
			 status = allocator_t::deallocate_object (m_packet_ptr);
			 m_packet_ptr = null;
		}
		else
		{
			status = PFX_STATUS_OK;
		}
		return status;
	}
	static PFX_INLINE element_t& error_element ()
	{
		static element_t __error_elem;
		return __error_elem;
	}
	PFX_INLINE element_t&	reference ()
	{
		if (m_packet_ptr)
		{
			return *m_packet_ptr;
		}
		else
		{
			return error_element();
		}
	}
	PFX_INLINE const element_t&	reference () const
	{
		if (m_packet_ptr)
		{
			return *m_packet_ptr;
		}
		else
		{
			return error_element();
		}
	}
};

template < class __alloc >
struct PFX_ShareObject
{
	typedef typename cshare_leakable_object < cleakable_object_packet < __alloc > > cshare_object_t;
};




//////////////////////////////////////////////////////////////////////////
#define CSLEAKABLE_OBJECT_TEMPALTE template < class leakable_object >
#define CSLEAKABLE_OBJECT cshare_leakable_object< leakable_object >
#define CSLEAKABLE_OBJECT_TYPE typename cshare_leakable_object< leakable_object >

CSLEAKABLE_OBJECT_TEMPALTE
PFX_INLINE  result_t  CSLEAKABLE_OBJECT::clock_object::lock_object(boolean_t __clone /*= PFX_BOOL_FALSE*/)
{
	result_t status;
	if (__clone && m_old_object_ptr)
	{
		status = m_old_object_ptr->m_share_obj.deep_copy_to (m_new_object);
	}
	else
	{
		status = PFX_STATUS_OK;
	}

	if (PFX_STATUS_OK == status)
	{
		//m_lock_object_ptr = &m_new_object;
		m_locked = PFX_BOOL_TRUE;
	}
	return status;
}

CSLEAKABLE_OBJECT_TEMPALTE
PFX_INLINE result_t CSLEAKABLE_OBJECT::clock_object ::unlock_object ()
{
	result_t status;
	if (m_lock)
	{
		if (m_old_object_ptr->is_shared())
		{
			FOR_ONE_LOOP_BEGIN
			status = m_old_object_ptr->release_object();
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
			m_old_object_ptr->m_share_obj.swap (m_new_object);
			FOR_ONE_LOOP_END;
		}
		else
		{
			status = PFX_STATUS_OK;
		}
	}
	else
	{
		status = PFX_STATUS_OK;
	}
	//m_lock_object_ptr = null;
	m_lock		= PFX_BOOL_FALSE;
	m_locked	= PFX_BOOL_FALSE;
	return status;
}

CSLEAKABLE_OBJECT_TEMPALTE
PFX_INLINE result_t CSLEAKABLE_OBJECT::release_object ()
{
	
	typedef CSLEAKABLE_OBJECT_TYPE::leak_data_t		leak_data_t;
	typedef CSLEAKABLE_OBJECT_TYPE::clist_node_t	clist_node_t;

	result_t status;
	leak_data_t __tmp_data;
	m_share_obj.leak_memery_to (__tmp_data);

	if (!get_prev_node() && get_prev_node() == get_next_node())
	{
		status = m_share_obj.free_leak_block (__tmp_data);
	}
	else
	{
		clist_node_t* node_ptr = clist_t::remove_list_node_unsafe(this);
		if (node_ptr)
		{
			m_next_node_ptr = null;
			m_prev_node_ptr = null;
			status = PFX_STATUS_OK;
		}
		else
		{
			status = PFX_STATUS_ERROR_;
		}
	}
	return status;
}

CSLEAKABLE_OBJECT_TEMPALTE
PFX_INLINE result_t CSLEAKABLE_OBJECT::share (CSLEAKABLE_OBJECT_TYPE::cshare_leakable_object_t& __other)
{
	typedef CSLEAKABLE_OBJECT_TYPE::clist_node_t	clist_node_t;
	typedef CSLEAKABLE_OBJECT_TYPE::clist_t				clist_t;
	result_t status;

	__other.release_object ();

	const  clist_node_t* node_ptr = 
				clist_t::insert_list_node_back(this, &__other);

	if (node_ptr)
	{
		status = this->m_share_obj.shallow_copy_to (__other.m_share_obj);
	}
	else
	{
		status = PFX_STATUS_ERROR_;
	}

	return status;
}
PECKER_END


#endif			//PFX_SHARE_OBJECT_H_
