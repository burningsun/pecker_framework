﻿/*
 * pfx_cblock.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBLOCK_H_
#define		PFX_CBLOCK_H_

#include "../pfx_defines.h"

PECKER_BEGIN


template < class __alloc >
class PFX_DATA_TEMPLATE_API cblock
{
public:
	typedef __alloc							allocator_t;
	typedef typename allocator_t::element_t	element_t;
	typedef cblock < allocator_t >			cblock_t;

	typedef cblock_t						cleakable_obj_t;
public:
	typedef class cleak_data
	{
		friend class cblock< allocator_t >;
		// gcc 4.6不支持这样的写法，尼玛
		//friend cblock_t;
	private:
		element_t*	m_block_ptr;
		usize__t	m_size;
	}leak_data_t;

private:
	element_t*	m_block_ptr;
	usize__t			m_size;
public:
	cblock () : m_block_ptr(null), m_size(0)
	{
		;
	}
	cblock (const cblock_t& __other)
	{
		if (this != &__other)
		{
			m_block_ptr = null; 
			m_size = 0;
			__other.copy_to(*this);
		}
	}
	~cblock()
	{
		clean();
	}
public:
	PFX_INLINE leak_data_t& leak_memery_to (leak_data_t& PARAM_OUT __block);

	static PFX_INLINE result_t free_leak_block (leak_data_t& PARAM_INOUT __block);

	PFX_INLINE result_t shallow_copy_to (cblock_t & PARAM_OUT __block) const;

	PFX_INLINE result_t deep_copy_to (cblock_t& PARAM_OUT __block) const;
public:
	static PFX_INLINE element_t& error_element ()
	{
		static element_t __error_elem;
		return __error_elem;
	}
	PFX_INLINE boolean_t is_error_element (const element_t& __elem) const
	{
		return (&error_element() == &__elem);
	}
	PFX_INLINE element_t&	reference (uindex_t i)
	{
		if (i < size())
		{
			return reference_unsafe(i);
		}
		else
		{
			return error_element();
		}
	}
	PFX_INLINE const element_t&	reference (uindex_t i) const
	{
		if (i < size())
		{
			return reference_unsafe(i);
		}
		else
		{
			return error_element();
		}
	}

	PFX_INLINE element_t*	pointer (uindex_t i)
	{
		if (i < size())
		{
			return pointer_unsafe(i);
		}
		else
		{
			return null;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	PFX_INLINE element_t&	reference_unsafe (uindex_t i)
	{
		return m_block_ptr[i];
	}
	PFX_INLINE element_t*	pointer_unsafe (uindex_t i)
	{
		return (m_block_ptr + i);
	}
	PFX_INLINE element_t* begin ()
	{
		return m_block_ptr;
	}
	PFX_INLINE element_t* end()
	{
		return ((0 == m_size)?(m_block_ptr):(m_block_ptr + m_size - 1));
	}
	//////////////////////////////////////////////////////////////////////////
	PFX_INLINE element_t const&	reference_unsafe (uindex_t i) const
	{
		return m_block_ptr[i];
	}
	PFX_INLINE const element_t*	pointer_unsafe (uindex_t i) const
	{
		return (m_block_ptr + i);
	}
	PFX_INLINE const element_t* begin () const
	{
		return m_block_ptr;
	} 
	PFX_INLINE const element_t* end() const
	{
		return ((0 == m_size)?(m_block_ptr):(m_block_ptr + m_size - 1));
	}

	//////////////////////////////////////////////////////////////////////////
	PFX_INLINE usize__t size () const
	{
		return m_size;
	}
	//////////////////////////////////////////////////////////////////////////
	PFX_INLINE void swap (cblock_t& __other);
	
	PFX_INLINE result_t init_buffer (usize__t __size);
	PFX_INLINE result_t init_buffer (const element_t* buf_ptr, usize__t __size);
	PFX_INLINE result_t resize(usize__t __size);
	PFX_INLINE result_t insert (uindex_t __offset, const element_t* buf_ptr, usize__t __size);

	PFX_INLINE usize__t set_buffer_direct (const element_t* buf_ptr, usize__t __size);
	PFX_INLINE usize__t set_buffer_direct_down (const element_t* buf_ptr, 
		uindex_t __offset, usize__t __size);
	PFX_INLINE usize__t set_buffer_direct_up (const element_t* buf_ptr, 
		uindex_t __offset, usize__t __size);
	PFX_INLINE usize__t set_buffer (const element_t* buf_ptr, usize__t __size, uindex_t __offset = 0);

	PFX_INLINE usize__t move_buffer (uindex_t __offset, usize__t __size, uindex_t __new_offset);

	//////////////////////////////////////////////////////////////////////////
	PFX_INLINE result_t copy_to(cblock_t&  PARAM_OUT __block) const;

	PFX_INLINE result_t clean ();

	PFX_INLINE result_t dispose ()
	{
		return clean();
	}
	PFX_INLINE void force_clean ()
	{
		cblock_t tmp_block;
		this->swap(tmp_block);
	}
};

template < class element_type >
struct block_operate
{
	typedef element_type	element_t;
	typedef block_operate	block_op_t;

	static PFX_INLINE boolean_t is_same_buffer (element_t* buffer_ptr, usize__t buffer_size, 
		const element_t* buf_ptr)
	{
		const element_t* begin_ptr	= buffer_ptr;
		const element_t* end_ptr		= buffer_ptr + buffer_size - 1;

		if (buf_ptr >= begin_ptr && buf_ptr <= end_ptr) 
		{
			return PFX_BOOL_TRUE;
		}
		else
		{
			return PFX_BOOL_FALSE;
		}
	}

	static PFX_INLINE usize__t set_buffer_direct_down  (element_t* buffer_ptr, usize__t buffer_size, 
		const element_t* buf_ptr, 
		uindex_t __offset, usize__t __size)
	{
		RETURN_RESULT (__offset >= buffer_size || !buffer_ptr, 0);
		if (__size+__offset > buffer_size)
		{
			__size = buffer_size - __offset;
		}
		RETURN_RESULT (0 == __size, 0);

		usize__t succeed_size = __size;
		while (__size)
		{
			--__size;
			buffer_ptr[__offset + __size] = buf_ptr[__size];
		}

		return succeed_size;
	}

	static PFX_INLINE usize__t set_buffer_direct_up (element_t* buffer_ptr, usize__t buffer_size, 
		const element_t* buf_ptr, 
		uindex_t __offset, usize__t __size)
	{
		RETURN_RESULT (__offset >= buffer_size || !buffer_ptr, 0);
		if (__size+__offset > buffer_size)
		{
			__size = buffer_size - __offset;
		}
		for (uindex_t i=0; i<__size;++i)
		{
			buffer_ptr[__offset + i] = buf_ptr[i];
		}
		return __size;
	}

	static PFX_INLINE usize__t move_buffer (element_t* buffer_ptr, usize__t buffer_size,
		uindex_t __offset, usize__t __size, uindex_t __new_offset)
	{
		usize__t succeed_size;
		RETURN_RESULT ((__offset >= buffer_size || 
			__new_offset >= buffer_size), 0);
		RETURN_RESULT (__offset == __new_offset, __size);

		if (__offset > __new_offset)
		{
			succeed_size = set_buffer_direct_up(buffer_ptr, buffer_size,
				(buffer_ptr + __offset), __new_offset, __size);
		}
		else
		{
			succeed_size = set_buffer_direct_down(buffer_ptr, buffer_size, 
				(buffer_ptr + __offset), __new_offset, __size);
		}
		return succeed_size;
	}

	static PFX_INLINE usize__t set_buffer (element_t* buffer_ptr, usize__t buffer_size,
		const element_t* buf_ptr, 
		usize__t __size, 
		uindex_t	__offset = 0)
	{
		usize__t succeed_size;
		RETURN_RESULT (!buffer_ptr || !buffer_size, 0);
		RETURN_RESULT ((null == buf_ptr || 0 == __size), __size);

		const element_t* begin_ptr	= buffer_ptr;
		const element_t* end_ptr		= buffer_ptr + buffer_size - 1;

		if (buf_ptr >= begin_ptr && buf_ptr <= end_ptr) 
		{
			succeed_size = move_buffer (buffer_ptr, buffer_size, (uindex_t)(buf_ptr - begin_ptr) , __size, __offset);
		}
		else
		{
			succeed_size = set_buffer_direct_down(buffer_ptr, buffer_size, buf_ptr, __offset, __size);
		}

		return succeed_size;
	} 
};

template < class __allocA, class __allcB >
PFX_INLINE result_t  block_to_block (const cblock< __allocA >& __blockA, 
											cblock< __allcB >& __blockB)
{
	result_t status;
	if (&__blockA != &__blockB)
	{
		FOR_ONE_LOOP_BEGIN
		status = __blockB.init_buffer(__blockA.size());

		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		
		status = __blockB.set_buffer_direct(__blockA.begin(), __blockA.size());
		FOR_ONE_LOOP_END
	}
	else
	{
		status = PFX_STATUS_OK;
	}

	return status;
};

template < class __cblockA, class __cblockB>
PFX_INLINE result_t  block_to_block_direct (const __cblockA& __blockA, 
	__cblockB& __blockB)
{
	result_t status;
	if (&__blockA != &__blockB)
	{
		FOR_ONE_LOOP_BEGIN
		status = __blockB.init_buffer(__blockA.size());

		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);

		status = __blockB.set_buffer_direct(__blockA.begin(), __blockA.size());
		FOR_ONE_LOOP_END
	}
	else
	{
		status = PFX_STATUS_OK;
	}

	return status;
};

//////////////////////////////////////////////////////////////////////////
#define PFX_CBLOCK_TEMPLATE_DEFINES template < class __alloc >
#define PFX_CBLOCK cblock< __alloc >
#define PFX_CBLOCK_TYPE typename  cblock< __alloc >

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE PFX_CBLOCK_TYPE::leak_data_t& PFX_CBLOCK::leak_memery_to 
(PFX_CBLOCK_TYPE::leak_data_t& PARAM_OUT __block)
{
	typedef PFX_CBLOCK_TYPE::leak_data_t leak_data_t;

	__block.m_block_ptr	=	this->m_block_ptr;
	__block.m_size				=	this->m_size;
	this->m_block_ptr		= null;
	this->m_size					= null;

	return __block;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::free_leak_block 
(PFX_CBLOCK_TYPE::leak_data_t& PARAM_INOUT __block)
{
	PFX_CBLOCK_TYPE::cblock_t __freeblock;
	__freeblock.m_block_ptr	=	__block.m_block_ptr;
	__freeblock.m_size				=	__block.m_size;
	__block.m_block_ptr			= null;
	__block.m_size						= 0;
	return PFX_STATUS_OK;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::shallow_copy_to (PFX_CBLOCK_TYPE::cblock_t & PARAM_OUT __block) const
{
	result_t status;
	status = __block.clean ();
	if (PFX_STATUS_OK == status)
	{
		__block.m_block_ptr = this->m_block_ptr;
		__block.m_size				= this->m_size;
	}
	return status;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::deep_copy_to (PFX_CBLOCK_TYPE::cblock_t& PARAM_OUT __block) const
{
	return copy_to(__block);
}


PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::copy_to(PFX_CBLOCK_TYPE::cblock_t&  PARAM_OUT __block) const
{
	typedef PFX_CBLOCK_TYPE::cblock_t cblock_t;
	 return block_to_block_direct<  cblock_t,  cblock_t > (*this, __block);
}

//////////////////////////////////////////////////////////////////////////
PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE void PFX_CBLOCK::swap (PFX_CBLOCK_TYPE::cblock_t& __other)
{
	typedef PFX_CBLOCK_TYPE::element_t element_t;
	 
	if (&__other != this)
	{
		element_t*	tmp_block_ptr;
		usize__t			tmp_size;
		tmp_block_ptr				= __other.m_block_ptr;
		__other.m_block_ptr	= this->m_block_ptr;
		this->m_block_ptr		= tmp_block_ptr;

		tmp_size				=	__other.m_size;
		__other.m_size	= this->m_size;
		this->m_size			= tmp_size;
	}

}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::init_buffer (usize__t __size)
{
	typedef PFX_CBLOCK_TYPE::element_t element_t;
	typedef PFX_CBLOCK_TYPE::allocator_t allocator_t;

	result_t status;
	
	if (!__size)
	{
		status = clean();
	}
	else if (__size != m_size)
	{
		FOR_ONE_LOOP_BEGIN
		element_t* new_buffer;
		cblock_t tmp_block;
		if (m_block_ptr)
		{
			new_buffer = allocator_t::reallocate_objects (m_block_ptr, __size);
			if (new_buffer)
			{
				m_size = __size;
				BREAK_LOOP (status, PFX_STATUS_OK);
			}
		}
		new_buffer = allocator_t::allocate_objects (__size);
		if (!new_buffer)
		{
			BREAK_LOOP (status, PFX_STATUS_MEM_LOW);
		}

		this->swap(tmp_block);
		m_block_ptr = new_buffer;
		m_size = __size;
		BREAK_LOOP (status, PFX_STATUS_OK);
		FOR_ONE_LOOP_END
	}
	else 
	{
		status = PFX_STATUS_OK;
	}
	return status;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::init_buffer (const PFX_CBLOCK_TYPE::element_t* buf_ptr, usize__t __size)
{
	result_t status;
	FOR_ONE_LOOP_BEGIN
	
	status = init_buffer(__size);
	BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
	usize__t succeed_size;
	succeed_size = set_buffer(buf_ptr, __size);
	if (__size != succeed_size)
	{
		status = PFX_STATUS_OK;
	}
	FOR_ONE_LOOP_END
	return status;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::resize(usize__t __size)
{
	typedef PFX_CBLOCK_TYPE::cblock_t cblock_t;

	result_t status;
	if (0 == __size)
	{
		status = clean();
	}
	else if (__size != m_size)
	{
		cblock_t tmp_block;
		FOR_ONE_LOOP_BEGIN
		status = tmp_block.init_buffer(__size);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		tmp_block.set_buffer_direct(m_block_ptr,m_size);
		this->swap(tmp_block);
		FOR_ONE_LOOP_END
	}
	else
	{
		status = PFX_STATUS_OK;
	}
	return status;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::insert (uindex_t __offset, 
		const PFX_CBLOCK_TYPE::element_t* buf_ptr, usize__t __size)
{
	typedef PFX_CBLOCK_TYPE::cblock_t cblock_t;
	result_t status;

	RETURN_RESULT (0 == __size || __offset > size(), PFX_STATUS_OK);
	RETURN_INVALID_RESULT (null == buf_ptr, PFX_STATUS_INVALID_PARAMS);

	FOR_ONE_LOOP_BEGIN
	cblock_t tmp_block;
	usize__t succeed_size;
	
	tmp_block.init_buffer (size() + __size);
	
	succeed_size = tmp_block.set_buffer_direct_down (this->begin(), 0, __offset);
	BREAK_LOOP_CONDITION_SETS(succeed_size != __offset, status, PFX_STATUS_FAIL);

	succeed_size = tmp_block.set_buffer_direct_down (buf_ptr, __offset, __size);
	BREAK_LOOP_CONDITION_SETS(succeed_size != __size, status, PFX_STATUS_FAIL);

	succeed_size = tmp_block.set_buffer_direct_down (this->pointer_unsafe(__offset), 
		(__offset + __size), 
		(size() - __offset));
	BREAK_LOOP_CONDITION_SETS(succeed_size != (size() - __offset), status, PFX_STATUS_FAIL);

	this->swap(tmp_block);
	FOR_ONE_LOOP_END

	return status;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE usize__t PFX_CBLOCK::set_buffer_direct 
	(const PFX_CBLOCK_TYPE::element_t* buf_ptr, usize__t __size)
{
	usize__t succeed_size;
	if (__size > size())
	{
		__size = size();
	}
	succeed_size = __size;
		
	while (__size)
	{
		--__size;
		reference_unsafe(__size) = buf_ptr[__size];
	}
	return succeed_size;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE usize__t PFX_CBLOCK::set_buffer_direct_down (const PFX_CBLOCK_TYPE::element_t* buf_ptr, 
	uindex_t __offset, usize__t __size)
{
	RETURN_RESULT (__offset >= size(), 0);
	if (__size+__offset > size())
	{
		__size = size() - __offset;
	}
	RETURN_RESULT (0 == __size, 0);

	usize__t succeed_size = __size;
	while (__size)
	{
		--__size;
		reference_unsafe(__offset + __size) = buf_ptr[__size];
	}
		
	return succeed_size;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE usize__t PFX_CBLOCK::set_buffer_direct_up (const PFX_CBLOCK_TYPE::element_t* buf_ptr, 
	uindex_t __offset, usize__t __size)
{
	RETURN_RESULT (__offset >= size(), 0);
	if (__size+__offset > size())
	{
		__size = size() - __offset;
	}
	for (uindex_t i=0; i<__size;++i)
	{
		reference_unsafe(__offset + i) = buf_ptr[i];
	}
	return __size;
}

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE usize__t PFX_CBLOCK::move_buffer (uindex_t __offset, usize__t __size, uindex_t __new_offset)
{
	usize__t succeed_size;
	RETURN_RESULT (__offset >= size() || 
		__new_offset >= size(), 0);
	RETURN_RESULT (__offset == __new_offset, __size);

	if (__offset > __new_offset)
	{
		succeed_size = set_buffer_direct_up(pointer_unsafe(__offset), __new_offset, __size);
	}
	else
	{
		succeed_size = set_buffer_direct_down(pointer_unsafe(__offset), __new_offset, __size);
	}
	return succeed_size;
}

PFX_CBLOCK_TEMPLATE_DEFINES
	PFX_INLINE usize__t PFX_CBLOCK::set_buffer (const PFX_CBLOCK_TYPE::element_t* buf_ptr, 
	usize__t __size, 
	uindex_t	__offset)
{
	usize__t succeed_size;
	RETURN_RESULT (!this->m_block_ptr||!this->m_size,0);
	RETURN_RESULT ((null == buf_ptr || 0 == __size), __size);
	if (buf_ptr >= begin() && buf_ptr <= end()) 
	{
		succeed_size = move_buffer ((uindex_t)(buf_ptr - begin()) , __size, __offset);
	}
	else
	{
		succeed_size = set_buffer_direct_down(buf_ptr, __offset, __size);
	}

	return succeed_size;
} 

PFX_CBLOCK_TEMPLATE_DEFINES
PFX_INLINE result_t PFX_CBLOCK::clean ()
{
	typedef PFX_CBLOCK_TYPE::allocator_t allocator_t;

	result_t status;
	//FOR_ONE_LOOP_BEGIN
	if (m_block_ptr)
	{
		status	= allocator_t::deallocate_objects (m_block_ptr);
	}
	else
	{
		status = PFX_STATUS_OK;
	}
	
	m_block_ptr = null;
	m_size			= 0;
	//FOR_ONE_LOOP_END
	return status;
}

PECKER_END

#endif			//PFX_CBLOCK_H_
