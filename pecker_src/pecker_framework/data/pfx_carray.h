﻿/*
 * pfx_carray.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CARRAY_H_
#define		PFX_CARRAY_H_

#include "pfx_cblock.h"
#include "pfx_data_traits.h"

PECKER_BEGIN

#define PFX_ARRAY_AUTO_STEP_SIZE (16)
#define PFX_ARRAY_SIZE MAX_UNSIGNED_VALUE
template < class element_ >
PFX_Interface PFX_DATA_TEMPLATE_API IPfx_array
{
	typedef element_															element_t;
	typedef element_															item_type_t;
	typedef IPfx_array < item_type_t >							IArray_t;

	virtual ~IPfx_array () {;};


	virtual result_t						init (usize__t element_count, usize__t allocate_step_size = 0) = 0;

	virtual result_t						resize (usize__t element_size) = 0;

	virtual result_t						garbage_collection (usize__t new_size = 0) = 0;
	
	virtual result_t						set_max_elements_count (usize__t max_count = 0) = 0;
	virtual result_t						set_auto_step (usize__t auto_step = 0) = 0;

	virtual usize__t						get_max_elements_count () const = 0;
	virtual usize__t						get_auto_step () const = 0;

	virtual result_t						copy_to (IArray_t * PARAM_IN other_ptr) const = 0;

	virtual result_t						push_back (const element_t& elem) = 0;
	virtual result_t						pop_back () = 0;

	virtual usize__t						get_buffer_size () const = 0;
	virtual	usize__t						size () const = 0;

	virtual const element_t&	get_element_at (uindex_t index_) const = 0;
	virtual element_t&				get_element_at (uindex_t index_) = 0;

	virtual usize__t						set_element_buffers_at (uindex_t index_, const element_t* PARAM_IN elements_ptr,
																				usize__t element_size) = 0;

	virtual	result_t						clean () = 0;
	virtual result_t						dispose () = 0;

	virtual	boolean_t					is_full () const = 0;
	virtual boolean_t					is_empty () const = 0;

	virtual boolean_t					is_error_element (const element_t& __elem) const = 0;
//protected:
//	virtual const element_t*	get_buffer () const = 0;
public:
	static const object_id_t& final_type ()
	{
		static object_id_t obj_id;
		return cobject_id < IArray_t >::to_object_id(obj_id);
	}
	PFX_INLINE virtual const object_id_t& type_id () const
	{
		return final_type();
	}
};

template < class  __alloc >
class PFX_DATA_TEMPLATE_API carray : 
	public IPfx_array < typename __alloc::element_t >
{
public:
	typedef  __alloc										allocator_t;
	typedef typename allocator_t::element_t			element_t;
	typedef  element_t								item_type_t;
	typedef  IPfx_array < element_t >		IArray_t;
	typedef  cblock< allocator_t >				cblock_t;
	typedef  carray< allocator_t >				carray_t;


protected:
	cblock_t		m_block;
	usize__t		m_size;
private:
	usize__t		m_auto_size_step;
	usize__t		m_max_elements_count;


public:
	carray () : m_size (0), m_auto_size_step (PFX_ARRAY_AUTO_STEP_SIZE), 
		m_max_elements_count((usize__t)PFX_ARRAY_SIZE)
	{
		;
	}
	carray (const carray_t &__other) throw (result_t)
	{
		if (&__other != this)
		{
			carray ();
			result_t status = __other.copy_to(this);
			if (PFX_STATUS_OK > status)
			{
				throw (status);
			}
		}
	}
	virtual ~carray()
	{
		dispose ();
	}
public:
	static const object_id_t& final_type ()
	{
		static object_id_t obj_id;
		return cobject_id < carray_t, IArray_t >::to_object_id(obj_id);
	}
	PFX_INLINE virtual const object_id_t& type_id () const
	{
		return final_type();
	}
public:
	typedef class carray_const_iterator
	{
		//friend carray_t;
		friend class carray< __alloc >;
	public:
		typedef typename carray_t::element_t			element_t;
		typedef carray_const_iterator		iterator_t;
	private:
		const element_t*	 m_cur_ptr;
		const element_t* m_begin_ptr;
		const element_t* m_end_ptr;
	public:
		carray_const_iterator():m_cur_ptr(null), m_begin_ptr(null), m_end_ptr(null)
		{
			;
		}
		~carray_const_iterator()
		{
			m_cur_ptr		= null; 
			m_begin_ptr	=null; 
			m_end_ptr	= null;
		}
	public:
		PFX_INLINE usize__t size() const
		{
			if (m_end_ptr >= m_begin_ptr)
			{
				return (uindex_t)(m_end_ptr - m_begin_ptr) + 1;
			}
			else
			{
				return 0;
			}

		}
		PFX_INLINE void to_begin ()
		{
			m_cur_ptr = m_begin_ptr;
		}
		PFX_INLINE void to_end ()
		{
			m_cur_ptr = m_end_ptr;
		}
		PFX_INLINE const element_t& reference() const
		{
			return *m_cur_ptr;
		}
		PFX_INLINE iterator_t*	cur_ptr()
		{
			if (m_cur_ptr)
			{
				return this;
			}
			else
			{
				return null;
			}
		}
		PFX_INLINE iterator_t*	increase ()
		{
			if (m_cur_ptr != m_end_ptr)
			{
				++m_cur_ptr;
				return this;
			}
			else
			{
				return null;
			}

		}
		PFX_INLINE iterator_t*	decrease ()
		{
			if (m_cur_ptr != m_begin_ptr)
			{
				--m_cur_ptr;
				return this;
			}
			else
			{
				return null;
			}

		}
	}const_iterator_t;
public:
	PFX_INLINE const_iterator_t*	begin (const_iterator_t& PARAM_OUT itr) const
	{
		RETURN_RESULT (0 == size(), null);
		itr.m_begin_ptr = this->m_block.begin();
		itr.m_cur_ptr = itr.m_begin_ptr;
		itr.m_end_ptr = this->m_block.begin() + size() - 1;
		return &itr;
	}
	PFX_INLINE const_iterator_t*	end (const_iterator_t& PARAM_OUT itr) const
	{
		RETURN_RESULT (0 == size(), null);
		itr.m_end_ptr = this->m_block.begin() + size() - 1;
		itr.m_cur_ptr = itr.m_end_ptr;
		itr.m_begin_ptr = this->m_block.begin();
		return &itr;
	}
	PFX_INLINE result_t						set_at (const_iterator_t& PARAM_INOUT itr, 
		const element_t& __char, boolean_t __autofixed = PFX_BOOL_FALSE)
	{
		if (itr.m_begin_ptr == this->m_block.begin())
		{
			if (itr.m_cur_ptr)
			{
				*itr.m_cur_ptr = __char;
				return PFX_STATUS_OK;
			}
			else
			{
				return PFX_STATUS_OVERRANGE;
			}

		}
		else if (__autofixed)
		{
			uindex_t offset = itr.m_cur_ptr - itr.m_begin_ptr;
			if (offset < size())
			{
				begin(itr);
				itr.m_cur_ptr += offset;
				*itr.m_cur_ptr = __char;
				return PFX_STATUS_OK;
			}
			else
			{
				end(itr);
				return PFX_STATUS_OVERRANGE;
			}
		}
		else 
		{
			return PFX_STATUS_DENIED;
		}
	}

	PFX_INLINE const cblock_t* get_block_ptr() const
	{
		return &m_block;
	}
	PFX_INLINE cblock_t* get_block_ptr() 
	{
		return &m_block;
	}
	PFX_INLINE const element_t* get_block_buffer() const
	{
		return m_block.begin();
	}
	PFX_INLINE element_t* get_block_buffer() 
	{
		return m_block.begin();
	}
	PFX_INLINE element_t* get_element_ptr_at(uindex_t index_)
	{
		return m_block.pointer(index_);
	}
public:
	void swap (carray_t& __other)
	{
		if (&__other != this)
		{
			this->m_block.swap(__other.m_block);

			usize__t __tmp		= this->m_size;
			this->m_size			= __other.m_size;
			__other.m_size	= __tmp;

			__tmp											= this->m_auto_size_step;
			this->m_auto_size_step			= __other.m_auto_size_step;
			__other.m_auto_size_step	= __tmp;

			__tmp														= this->m_max_elements_count;
			this->m_max_elements_count			= __other.m_max_elements_count;
			__other.m_max_elements_count	= __tmp;
		}
	}
	const cblock_t& get_block () const
	{
		return m_block;
	}
	
public:
	virtual result_t						init (usize__t element_count, usize__t allocate_step_size = 0)
	{
		usize__t __size;
		result_t status;
		if (!allocate_step_size)
		{
			allocate_step_size = m_auto_size_step;
		}
		if (!allocate_step_size)
		{
			__size = element_count;
		}
		else
		{
			usize__t remain_size = element_count % allocate_step_size;
			__size = element_count  + ((remain_size)?(allocate_step_size - remain_size):(0));
		}
		
		status = m_block.init_buffer(__size);
		if (PFX_STATUS_OK == status)
		{
			m_auto_size_step	= allocate_step_size;
			m_size						= element_count;
		}
		return status;
	}

	virtual result_t						resize (usize__t element_size)
	{
		result_t status;

		if (element_size > m_block.size())
		{
			usize__t __size;

			if (!m_auto_size_step)
			{
				__size = element_size;
			}
			else
			{
				usize__t remain_size = element_size % m_auto_size_step;
				__size = element_size  + ((remain_size)?(m_auto_size_step - remain_size):(0));
			}

			status = m_block.resize(__size);
		}
		else
		{
			status = PFX_STATUS_OK;
		}

		if (PFX_STATUS_OK == status)
		{
			m_size = element_size;
		}
		return status;
	}

	virtual result_t						garbage_collection (usize__t new_size = 0)
	{
		result_t status;
		
		usize__t __size;

		if (new_size < m_size)
		{
			new_size = m_size;
		}

		if (!m_auto_size_step)
		{
			__size = new_size;
		}
		else
		{
			usize__t remain_size = new_size % m_auto_size_step;
			__size = new_size  + ((remain_size)?(m_auto_size_step - remain_size):(0));
		}
		
		if (__size < m_block.size())
		{
			status = m_block.resize(__size);
		}
		else
		{
			status = PFX_STATUS_OK;
		}
		return status;
	}

	virtual result_t						set_max_elements_count (usize__t max_count = 0)
	{
		if (!max_count)
		{
			m_max_elements_count = max_count;
		}
		else
		{
			m_max_elements_count = (usize__t)PFX_ARRAY_SIZE;
		}
		return PFX_STATUS_OK;
	}
	virtual result_t						set_auto_step (usize__t auto_step = 0)
	{
		if (auto_step)
		{
			m_auto_size_step = auto_step;
		}
		else if (!m_auto_size_step)
		{
			m_auto_size_step = PFX_ARRAY_AUTO_STEP_SIZE;
		}
		return PFX_STATUS_OK;
	}

	virtual PFX_INLINE usize__t	get_max_elements_count () const
	{
		return m_max_elements_count;
	}
	virtual PFX_INLINE usize__t	get_auto_step () const
	{
		return m_auto_size_step;
	}

	virtual result_t						copy_to (carray_t& __other) const
	{
		result_t status;
		if (&__other != this)
		{
			FOR_ONE_LOOP_BEGIN
			if (__other.m_block.size() < m_size)
			{
				cblock_t new_block;
				__other.m_block.swap(new_block);
				status = __other.init(m_size);

				if (PFX_STATUS_OK > status)
				{
					__other.m_block.swap(new_block);
					break;
				}
				__other.resize(m_size);
			}
			status = __other.m_block.set_buffer_direct(this->m_block.begin(), m_size);
			FOR_ONE_LOOP_END
		}
		else
		{
			status = PFX_STATUS_OK;
		}
		return status;
	}
	virtual result_t						copy_to (IArray_t * PARAM_IN other_ptr) const
	{
		RETURN_INVALID_RESULT (!other_ptr, PFX_STATUS_INVALID_PARAMS);
		RETURN_INVALID_RESULT(other_ptr == this, PFX_STATUS_OK);

		if (__type_id::__IS_type(final_type(), other_ptr->type_id()))
		{
			return copy_to((carray_t&)(*other_ptr));
		}
		result_t status;
		FOR_ONE_LOOP_BEGIN
		if (other_ptr->get_buffer_size () < m_size)
		{
			status = other_ptr->init (m_size);
		}
		else
		{
			status = other_ptr->resize (m_size);
		}
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		status = other_ptr->set_element_buffers_at(0, this->m_block.begin(), m_size);
		FOR_ONE_LOOP_END
		return status;
	}

	virtual result_t						push_back (const element_t& elem)
	{
		result_t status;
		RETURN_INVALID_RESULT (m_size == m_max_elements_count, PFX_STATUS_FULL);
		uindex_t i = m_size;
		FOR_ONE_LOOP_BEGIN
		status = resize(m_size+1);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		m_block.reference_unsafe(i) = elem;
		FOR_ONE_LOOP_END
		return status;
	}
	virtual result_t						pop_back ()
	{
		result_t status;
		if (m_size)
		{
			status = resize(m_size-1);
		}
		else
		{
			status = PFX_STATUS_EMPTY;
		}
		return status;
	}

	virtual PFX_INLINE usize__t	get_buffer_size () const
	{
		return m_block.size();
	}
	virtual	PFX_INLINE usize__t	size () const
	{
		return m_size;
	}

	virtual PFX_INLINE const element_t&	get_element_at (uindex_t index_) const
	{
		return m_block.reference(index_);
	}
	virtual PFX_INLINE element_t&			get_element_at (uindex_t index_)
	{
		return m_block.reference(index_);
	}

	static PFX_INLINE element_t& error_element ()
	{
		return cblock_t::error_element();
	}

	virtual PFX_INLINE boolean_t is_error_element (const element_t& __elem) const
	{
		return m_block.is_error_element (__elem);
	}

	virtual PFX_INLINE usize__t				set_element_buffers_at (uindex_t index_, const element_t* PARAM_IN elements_ptr,
		usize__t element_size)
	{
		RETURN_RESULT (index_ > size(), 0);
		usize__t temp_size = size() - index_;
		element_size = (temp_size < element_size)?temp_size:element_size;
		return m_block.set_buffer(elements_ptr, element_size, index_);
	}

	virtual	PFX_INLINE result_t					clean ()
	{
		m_size = 0;
		return PFX_STATUS_OK;
	}
	virtual PFX_INLINE result_t				dispose ()
	{
		m_size = 0;
		return m_block.dispose();
	}

	virtual	 PFX_INLINE boolean_t			is_full () const
	{
		return (boolean_t)(m_size == m_max_elements_count);
	}
	virtual PFX_INLINE boolean_t			is_empty () const
	{
		return (boolean_t)(!m_size);
	}
};

template < class  __alloc, 
					class __alloc_block = pecker_simple_allocator < cblock< __alloc > > >
class PFX_DATA_TEMPLATE_API carray_mbs : 
	public IPfx_array < typename __alloc::element_t >
{
public:
	typedef  __alloc										allocator_t;
	typedef  __alloc_block							block_allocator_t;
	typedef typename allocator_t::element_t			element_t;
	typedef  element_t								item_type_t;
	typedef  IPfx_array < element_t >		IArray_t;
	typedef  cblock< allocator_t >				cblock_t;
	typedef  carray< block_allocator_t >	block_array_t;

	typedef  carray_mbs < allocator_t, block_allocator_t > carray_t;
protected:
	block_array_t	m_blocks;
	usize__t				m_size;
private:
	usize__t		m_auto_size_step;
	usize__t		m_max_elements_count;
public:
	carray_mbs () : m_size (0), m_auto_size_step (PFX_ARRAY_AUTO_STEP_SIZE), 
		m_max_elements_count((usize__t)PFX_ARRAY_SIZE)
	{
		;
	}
	carray_mbs (const carray_t &__other) throw (result_t)
	{
		if (&__other != this)
		{
			carray_mbs ();
			result_t status = __other.copy_to(this);
			if (PFX_STATUS_OK > status)
			{
				throw (status);
			}
		}
	}
	virtual ~carray_mbs()
	{
		dispose ();
	}
public:
	static const object_id_t& final_type ()
	{
		static object_id_t obj_id;
		return cobject_id < carray_t, IArray_t >::to_object_id(obj_id);
	}
	PFX_INLINE virtual const object_id_t& type_id () const
	{
		return final_type();
	}
public:
	///////////////////////////////////////////////////////
	typedef class carray_const_iterator
	{
		friend class carray_mbs < __alloc, __alloc_block >;
		//friend carray_t;
	public:
		typedef typename carray_t::element_t			element_t;
		typedef carray_const_iterator		iterator_t;
	private:
		const carray_t*	m_array;
		uindex_t				m_index;
	public:
		carray_const_iterator():m_array(null),m_index(0)
		{
			;
		}
		~carray_const_iterator()
		{
			m_array = null;
			m_index = 0;
		}
	public:
		PFX_INLINE uindex_t index () const
		{
			return m_index;
		}

		PFX_INLINE usize__t size() const
		{
			if (m_array)
			{
				return m_array->size();
			}
			else
			{
				return 0;
			}
		}
		PFX_INLINE void to_begin ()
		{
			m_index = 0;
		}
		PFX_INLINE void to_end ()
		{
			if (m_array && m_array->size())
			{
				m_index = m_array->size() - 1;
			}
			else
			{
				m_index = 0;
			}
		}
		PFX_INLINE const element_t& reference() const
		{
			if (m_array)
			{
				return m_array->get_element_at (m_index);
			}
			else
			{
				return carray_t::error_element ();
			}
		}
		PFX_INLINE iterator_t*	cur_ptr()
		{
			if (m_array && m_index < m_array->size())
			{
				return this;
			}
			else
			{
				return null;
			}
		}
		PFX_INLINE iterator_t*	increase ()
		{
			if (m_array && m_index < m_array->size())
			{
				if (m_index == m_array->size () - 1)
				{
					return null;
				}
				++m_index;
				return this;
			}
			else
			{
				return null;
			}

		}
		PFX_INLINE iterator_t*	decrease ()
		{
			if (m_index && m_array && m_array->size ())
			{
				--m_index;
				return this;
			}
			else
			{
				return null;
			}

		}
	}const_iterator_t;
public:
	PFX_INLINE const_iterator_t*	begin (const_iterator_t& PARAM_OUT itr) const
	{
		RETURN_RESULT (0 == size(), null);
		itr.m_array = this;
		itr.m_index = 0;
		return &itr;
	}
	PFX_INLINE const_iterator_t*	end (const_iterator_t& PARAM_OUT itr) const
	{
		RETURN_RESULT (0 == size(), null);
		itr.m_array = this;
		itr.m_index = size() - 1;
		return &itr;
	}
	PFX_INLINE result_t						set_at (const_iterator_t& PARAM_INOUT itr, 
		const element_t& __char)
	{
		if (itr.m_array == this)
		{
			this->get_element_at(itr.m_index) = __char;
		}
	}
public:
	void swap (carray_t& __other)
	{
		if (&__other != this)
		{
			this->m_blocks.swap(__other.m_blocks);

			usize__t __tmp		= this->m_size;
			this->m_size			= __other.m_size;
			__other.m_size	= __tmp;

			__tmp											= this->m_auto_size_step;
			this->m_auto_size_step			= __other.m_auto_size_step;
			__other.m_auto_size_step	= __tmp;

			__tmp														= this->m_max_elements_count;
			this->m_max_elements_count			= __other.m_max_elements_count;
			__other.m_max_elements_count	= __tmp;
		}
	}
////////////////////////////////////////////////////////////////////////////
public:
	virtual result_t						init (usize__t element_count, usize__t allocate_step_size = 0)
	{
		if (!element_count)
		{
			return clean();
		}
		if (element_count > m_max_elements_count)
		{
			return PFX_STATUS_FULL;
		}
		if (element_count <= m_size)
		{
			m_size = element_count;
			return PFX_STATUS_OK;
		}

		//usize__t __size;
		result_t status;
		if (!allocate_step_size)
		{
			allocate_step_size = m_auto_size_step;
		}
		if (!allocate_step_size)
		{
			allocate_step_size = element_count;
		}

		usize__t new_block_size = 
			element_count / allocate_step_size + ((element_count % allocate_step_size > 0)?1:0); 



		FOR_ONE_LOOP_BEGIN

		usize__t old_size = m_blocks.size ();
		status = m_blocks.resize (new_block_size);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK !=status);

		if (allocate_step_size == m_auto_size_step)
		{
			for (uindex_t i=old_size; i<new_block_size; ++i)
			{
				cblock_t& __block =  m_blocks.get_element_at(i);
				status = __block.init_buffer(allocate_step_size);
				BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
			}
		}
		else
		{
			uindex_t i = new_block_size;
			while (i)
			{
				--i;
				cblock_t& __block =  m_blocks.get_element_at(i);
				status = __block.init_buffer(allocate_step_size);
				BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
			}
		}
		FOR_ONE_LOOP_END
		if (PFX_STATUS_OK == status)
		{
			m_auto_size_step	= allocate_step_size;
			m_size						= element_count;
		}
		return status;
	}

	virtual result_t						resize (usize__t element_count)
	{
		if (!element_count)
		{
			return clean();
		}
		if (element_count < m_size)
		{
			m_size = element_count;
			return PFX_STATUS_OK;
		}
		if (element_count == m_size)
		{
			return PFX_STATUS_OK;
		}
		if (element_count > m_max_elements_count)
		{
			return PFX_STATUS_FULL;
		}

		//usize__t __size;
		result_t status;
		usize__t	allocate_step_size = m_auto_size_step;

		if (!allocate_step_size)
		{
			allocate_step_size = element_count;
		}

		usize__t new_block_size = 
			element_count / allocate_step_size + ((element_count % allocate_step_size > 0)?1:0); 

		FOR_ONE_LOOP_BEGIN

		usize__t old_size = m_blocks.size ();
		status = m_blocks.resize (new_block_size);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK !=status);
		for (uindex_t i=old_size; i<new_block_size; ++i)
		{
			cblock_t& __block =  m_blocks.get_element_at(i);
			status = __block.resize(allocate_step_size);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		}
		FOR_ONE_LOOP_END
		if (PFX_STATUS_OK == status)
		{
			m_auto_size_step	= allocate_step_size;
			m_size						= element_count;
		}
		return status;
	}

	virtual result_t						garbage_collection (usize__t new_size = 0)
	{
		result_t status;
		//usize__t __size;

		usize__t	allocate_step_size = m_auto_size_step;

		if (!allocate_step_size)
		{
			m_blocks.dispose ();
			m_auto_size_step = ((0 == PFX_ARRAY_AUTO_STEP_SIZE)?0:16);
			return PFX_STATUS_MEM_ERR;
		}

		usize__t new_block_size = 
			m_size / allocate_step_size + ((m_size % allocate_step_size > 0)?0:1); 

		//usize__t cur_block_count = m_blocks.size ();
		FOR_ONE_LOOP_BEGIN
		status = m_blocks.resize (m_blocks.get_buffer_size());
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		for (uindex_t i=new_block_size; i<m_blocks.size(); ++i)
		{
			cblock_t& __block =  m_blocks.get_element_at(i);
			if (__block.size())
			{
				__block.dispose();
			}
			else
			{
				break;
			}
		}
		m_blocks.resize (new_block_size);
		FOR_ONE_LOOP_END
		return status;
	}

	virtual result_t						set_max_elements_count (usize__t max_count = 0)
	{
		if (!max_count)
		{
			m_max_elements_count = max_count;
		}
		else
		{
			m_max_elements_count = (usize__t)PFX_ARRAY_SIZE;
		}
		return PFX_STATUS_OK;
	}
	virtual result_t						set_auto_step (usize__t auto_step = 0)
	{
		usize__t new_step = 0;
		if (auto_step && auto_step != m_auto_size_step)
		{
			new_step = auto_step;
			//if (m_size > m_auto_size_step)
			//{
			//	new_step = auto_step;
			//}
			//else
			//{
			//	m_auto_size_step = auto_step;
			//}
		}
		else if (!m_auto_size_step)
		{
			new_step = PFX_ARRAY_AUTO_STEP_SIZE;
		}
		if (new_step)
		{
			carray_mbs new_array;
			usize__t _block_count;
			result_t status;

			_block_count = m_size / new_step + ((m_size % new_step)?1:0);
			FOR_ONE_LOOP_BEGIN
			status = new_array.m_blocks.set_auto_step(this->m_blocks.get_auto_step());
			BREAK_LOOP_CONDITION(PFX_STATUS_OK > status);
			status = new_array.init(m_size, new_step);
			BREAK_LOOP_CONDITION(PFX_STATUS_OK > status);
			uindex_t i = m_size;
			while (i)
			{
				--i;
				new_array.get_element_at(i) = this->get_element_at(i);
			}
			swap(new_array);
			FOR_ONE_LOOP_END
		}
		return PFX_STATUS_OK;
	}
	PFX_INLINE result_t					set_blocks_step (usize__t step = 0)
	{
		return this->m_blocks.set_auto_step(step);
	}
	PFX_INLINE usize__t				get_blocks_step () const
	{
		return this->m_blocks.get_auto_step();
	}

	virtual PFX_INLINE usize__t	get_max_elements_count () const
	{
		return m_max_elements_count;
	}
	virtual PFX_INLINE usize__t	get_auto_step () const
	{
		return m_auto_size_step;
	}

	virtual result_t						copy_to (carray_t& __other, boolean_t new_buffer = PFX_BOOL_TRUE) const
	{
		result_t status;
		RETURN_RESULT (&__other == this, PFX_STATUS_OK);

		carray_mbs new_array;
		if (new_buffer)
		{
			new_array.set_max_elements_count(this->get_max_elements_count());
			//usize__t _block_count = m_size / new_step + ((m_size % new_step)?1:0);

			FOR_ONE_LOOP_BEGIN
			status = new_array.m_blocks.set_auto_step(this->m_blocks.get_auto_step());
			BREAK_LOOP_CONDITION(PFX_STATUS_OK > status);
			status = new_array.init(m_size);
			BREAK_LOOP_CONDITION(PFX_STATUS_OK > status);
			uindex_t i = m_size;
			while (i)
			{
				--i;
				new_array.get_element_at(i) = this->get_element_at(i);
			}
			__other.swap(new_array);
			FOR_ONE_LOOP_END
		}
		else
		{
			__other.set_max_elements_count(this->get_max_elements_count());
			FOR_ONE_LOOP_BEGIN
			status = __other.m_blocks.set_auto_step(this->m_blocks.get_auto_step());
			BREAK_LOOP_CONDITION(PFX_STATUS_OK > status);
			status = __other.init(m_size, this->get_auto_step());
			BREAK_LOOP_CONDITION(PFX_STATUS_OK > status);
			uindex_t i = m_size;
			while (i)
			{
				--i;
				new_array.get_element_at(i) = this->get_element_at(i);
			}
			FOR_ONE_LOOP_END
		}
		return status;
	}
	virtual result_t						copy_to (IArray_t * PARAM_IN other_ptr) const
	{
		RETURN_INVALID_RESULT (!other_ptr, PFX_STATUS_INVALID_PARAMS);
		RETURN_INVALID_RESULT(other_ptr == this, PFX_STATUS_OK);

		if (__type_id::__IS_type(final_type(), other_ptr->type_id()))
		{
			return copy_to((carray_t&)(*other_ptr));
		}
		result_t status;
		FOR_ONE_LOOP_BEGIN
		other_ptr->set_max_elements_count (this->get_max_elements_count());
		if (other_ptr->get_buffer_size () < m_size)
		{
			status = other_ptr->init (m_size);
		}
		else
		{
			status = other_ptr->resize (m_size);
		}
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		status = other_ptr->set_element_buffers_at(0, this->m_blocks.get_block().begin()->begin(), m_size);
		FOR_ONE_LOOP_END
		return status;
	}

	virtual result_t						push_back (const element_t& elem)
	{
		result_t status;
		RETURN_INVALID_RESULT (m_size == m_max_elements_count, PFX_STATUS_FULL);
		uindex_t i = m_size;
		FOR_ONE_LOOP_BEGIN
		status = resize(m_size+1);
		BREAK_LOOP_CONDITION (PFX_STATUS_OK > status);
		get_element_at(i) = elem;
		FOR_ONE_LOOP_END
		return status;
	}
	virtual result_t						pop_back ()
	{
		result_t status;
		if (m_size)
		{
			status = resize(m_size-1);
		}
		else
		{
			status = PFX_STATUS_EMPTY;
		}
		return status;
	}

	virtual PFX_INLINE usize__t	get_buffer_size () const
	{
		return (this->m_blocks.size() * m_auto_size_step);
	}
	virtual	PFX_INLINE usize__t	size () const
	{
		return m_size;
	}

	static PFX_INLINE element_t& error_element ()
	{
		static element_t __error_elem;
		return __error_elem;
	}
	virtual PFX_INLINE boolean_t is_error_element (const element_t& __elem) const
	{
		return (&error_element() == &__elem);
	}
	virtual PFX_INLINE const element_t&	get_element_at (uindex_t __index) const
	{ 
		uindex_t block_index;
		if (!m_auto_size_step || __index >= m_size)
		{
			return error_element();
		}
		block_index = __index / m_auto_size_step;
		return m_blocks.get_element_at(block_index).reference_unsafe(__index % m_auto_size_step);
	}
	virtual PFX_INLINE element_t&			get_element_at (uindex_t __index)
	{
		uindex_t block_index;
		if (!m_auto_size_step || __index >= m_size)
		{
			return error_element();
		}
		block_index = __index / m_auto_size_step;
		return m_blocks.get_element_at(block_index).reference_unsafe(__index % m_auto_size_step);
	}

	virtual PFX_INLINE usize__t				set_element_buffers_at (uindex_t __index, const element_t* PARAM_IN elements_ptr,
		usize__t element_size)
	{
		if (__index >= m_size || !m_auto_size_step)
		{
			return 0;
		}

		usize__t succeeded_size = 0;
		uindex_t block_index;
		if ((element_size + __index) > m_size)
		{
			element_size = m_size - __index;
		}
		block_index	= __index / m_auto_size_step;
		__index			= __index % m_auto_size_step;
		usize__t temp_size = m_auto_size_step - __index;
		if (temp_size > element_size)
		{
			temp_size = element_size;
		}
		FOR_ONE_LOOP_BEGIN
		usize__t temp_ssize = m_blocks.get_element_at(block_index).set_buffer(elements_ptr, temp_size, __index);
		succeeded_size += temp_size;
		BREAK_LOOP_CONDITION (temp_size != temp_ssize);
		element_size	-= temp_ssize;
		temp_size			=	m_auto_size_step;
		elements_ptr	+= temp_ssize;
		++block_index;
		while (element_size)
		{
			temp_ssize = m_blocks.get_element_at(block_index).set_buffer(elements_ptr, temp_size, __index);
			succeeded_size += temp_size;
			BREAK_LOOP_CONDITION (temp_size != temp_ssize);
			element_size	-= temp_ssize;
			temp_size			=	m_auto_size_step;
			elements_ptr	+= temp_ssize;
			++block_index;
		}

		FOR_ONE_LOOP_END
		return succeeded_size;
	}

	virtual	PFX_INLINE result_t					clean ()
	{
		m_size = 0;
		return PFX_STATUS_OK;
	}
	virtual PFX_INLINE result_t				dispose ()
	{
		m_size = 0;
		return m_blocks.dispose();
	}

	virtual	 PFX_INLINE boolean_t			is_full () const
	{
		return (boolean_t)(m_size == m_max_elements_count);
	}
	virtual PFX_INLINE boolean_t			is_empty () const
	{
		return (boolean_t)(!m_size);
	}
};





PECKER_END

#endif			//PFX_ARRAY_H_
