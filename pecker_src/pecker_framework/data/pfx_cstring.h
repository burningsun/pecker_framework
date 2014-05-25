/*
 * pfx_cstring.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CSTRING_H_
#define		PFX_CSTRING_H_

#include "../pfx_defines.h"
#include "pfx_cblock.h"
#include "pfx_share_object.h"
//#include "pfx_clist.h"
#include "pecker_value_compare.h"
#include "pfx_data_traits.h"

PECKER_BEGIN

#define DEFUALT_CACHE_BUFFER_SIZE (16)

#define DEFUALT_STRING_CACHE_BUFFER_SIZE DEFUALT_CACHE_BUFFER_SIZE

typedef enum enumGarbageCollectionMODE
{
	GC_DEFUALT_MODE = 0,
	GC_USER_MODE,
	GC_MODE_COUNT
}GarbageCollectionMODE_t;

template < class element_t >
PFX_Interface PFX_DATA_TEMPALE_API IPfx_string
{
public:
	typedef typename element_t							element_t;
	typedef typename IPfx_string< element_t > IString_t;
	virtual ~IPfx_string () {;};
public:
	static const object_id_t& final_type ()
	{
		static object_id_t obj_id;
		return cobject_id < IString_t >::to_object_id(obj_id);
	}
	PFX_INLINE virtual const object_id_t& type_id () const
	{
		return final_type();
	}
public:
	virtual result_t						init_string (usize__t __size) = 0;
	virtual result_t						init_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size) = 0;
	virtual result_t						init_string (const IString_t* PARAM_IN other_ptr) = 0;

	virtual result_t						resize_string (usize__t __size) = 0;
	virtual result_t						garbage_collection (GarbageCollectionMODE_t mode = GC_DEFUALT_MODE, 
																						usize__t new_size = 0) = 0;

	virtual result_t						append_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size) = 0;
	virtual result_t						append_string (const IString_t* PARAM_IN append_string_ptr) = 0;

	virtual result_t						append_front (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size) = 0;
	virtual result_t						append_front (const IString_t* PARAM_IN append_string_ptr) = 0;

	virtual result_t						insert_string (uindex_t __offset, const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size) = 0;
	virtual result_t						insert_string (uindex_t __offset, const IString_t* PARAM_IN insert_string_ptr) = 0;

	virtual result_t						clip_string_remain_left (uindex_t clip_index, IString_t* PARAM_OUT other_ptr) = 0;
	virtual result_t						clip_string_remain_right (uindex_t clip_index, IString_t* PARAM_OUT other_ptr) = 0;

	virtual usize__t						get_cache_buffer_size () const = 0;

	virtual const element_t*	get_string () const = 0;
	virtual usize__t						get_length () const = 0;
	virtual usize__t						get_string_buffer_size () const = 0;

	virtual const element_t*	get_charbuffer_at (uindex_t index_) const = 0;
	virtual usize__t						set_charbuffer_at (uindex_t index_, 
																						const element_t* PARAM_IN char_buffer, 
																						usize__t buf_size) = 0;
	virtual element_t&				reference (uindex_t __index) = 0; 
	virtual const element_t&	reference (uindex_t __index) const = 0; 
	
	virtual  const element_t*	sub_string_buffer (uindex_t index_) const = 0;

	virtual  const IString_t *		sub_string (uindex_t index_,
																		IString_t* PARAM_OUT sub_string_ptr)  const = 0;

	virtual  const IString_t*		sub_string (uindex_t index_,
																		usize__t		sub_string_size, 
																		IString_t* PARAM_OUT sub_string_ptr)  const = 0;

	virtual result_t						sub_string (uindex_t __index, usize__t __size) = 0;

	virtual result_t						to_same_string (IString_t* PARAM_OUT same_string_ptr) = 0;
	virtual result_t						copy_to (IString_t* PARAM_OUT to_string_ptr)  const = 0;
	virtual result_t						dispose () = 0;
	virtual result_t						clean () = 0;


	//
	//virtual int								compare (const IString_t* other_ptr) const = 0;
};

template < class __alloc,  
	const unsigned int CACHE_BUFFER_SIZE = DEFUALT_STRING_CACHE_BUFFER_SIZE >
class PFX_DATA_TEMPALE_API cstring : 
	public IPfx_string < typename __alloc::element_t >
{
public:
	typedef typename __alloc										allocator_t;
	typedef typename allocator_t::element_t			element_t;
	typedef typename element_t								item_type_t;
	typedef typename IPfx_string < element_t >		IString_t;
	typedef typename cblock< allocator_t >				cblock_t;

	typedef typename cstring< allocator_t, CACHE_BUFFER_SIZE >	cstring_t;
protected:
	element_t											m_cache_buffer [(0 == CACHE_BUFFER_SIZE ? 1: CACHE_BUFFER_SIZE)];
	cblock_t												m_block;
	element_t*										m_this_string_ptr;
	usize__t												m_size;
public:
	cstring ():m_size(0), m_this_string_ptr(m_cache_buffer)
	{
		;
	}
	cstring (const cstring_t & other_) throw (result_t)
	{
		m_size = 0;
		m_this_string_ptr = m_cache_buffer;
		result_t status = other_.copy_to(*this);
		if (PFX_STATUS_OK != status)
		{
			throw (status);
		}
	}
	virtual ~cstring ()
	{
		dispose ();
	}
public:
	typedef class cstring_const_iterator
	{
		friend cstring_t;
	public:
		typedef element_t							element_t;
		typedef cstring_const_iterator		iterator_t;
	private:
		const element_t*	 m_cur_ptr;
		const element_t* m_begin_ptr;
		const element_t* m_end_ptr;
	public:
		cstring_const_iterator():m_cur_ptr(null), m_begin_ptr(null), m_end_ptr(null)
		{
			;
		}
		~cstring_const_iterator()
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
	typedef class cstring_iterator
	{
		friend cstring_t;
	public:
		typedef element_t				element_t;
		typedef cstring_iterator		iterator_t;
	private:
		element_t*			m_cur_ptr;
		const element_t* m_begin_ptr;
		const element_t* m_end_ptr;
	public:
		cstring_iterator():m_cur_ptr(null), m_begin_ptr(null), m_end_ptr(null)
		{
			;
		}
		~cstring_iterator()
		{
			m_cur_ptr		= null; 
			m_begin_ptr	=null; 
			m_end_ptr	= null;
		}
	public:
		PFX_INLINE usize__t size() const
		{
			if (m_begin_ptr >=  m_end_ptr)
			{
				return (uindex_t)(m_end_ptr - m_begin_ptr)+1;
			}
			else
			{
				return 0;
			}
			
		}
		PFX_INLINE void to_begin ()
		{
			m_cur_ptr = (element_t*)m_begin_ptr;
		}
		PFX_INLINE void to_end ()
		{
			m_cur_ptr = (element_t*)m_end_ptr;
		}
		PFX_INLINE element_t& reference()
		{
			return *m_cur_ptr;
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
	}iterator_t;
public:
	PFX_INLINE const_iterator_t* begin (const_iterator_t& PARAM_OUT itr) const
	{
		RETURN_RESULT (0 == get_length(), null);
		itr.m_begin_ptr = this->m_this_string_ptr;
		itr.m_cur_ptr = itr.m_begin_ptr;
		itr.m_end_ptr = this->m_this_string_ptr + get_length() - 1;
		return &itr;
	}
	PFX_INLINE const_iterator_t* end (const_iterator_t& PARAM_OUT itr) const
	{
		RETURN_RESULT (0 == get_length(), null);
		itr.m_end_ptr = this->m_this_string_ptr + get_length() - 1;
		itr.m_cur_ptr = itr.m_end_ptr;
		itr.m_begin_ptr = this->m_this_string_ptr;
		return &itr;
	}
	PFX_INLINE iterator_t* begin (iterator_t& PARAM_OUT itr)
	{
		RETURN_RESULT (0 == get_length(), null);
		itr.m_cur_ptr = this->m_this_string_ptr;
		itr.m_begin_ptr = itr.m_cur_ptr;
		itr.m_end_ptr = this->m_this_string_ptr + get_length() - 1;
		return &itr;
	}
	PFX_INLINE iterator_t* end (iterator_t& PARAM_OUT itr)
	{
		RETURN_RESULT (0 == get_length(), null);
		itr.m_cur_ptr = this->m_this_string_ptr + get_length() - 1;
		itr.m_end_ptr = itr.m_cur_ptr;
		itr.m_begin_ptr = this->m_this_string_ptr;
		return &itr;
	}

	PFX_INLINE usize__t	size() const
	{
		return m_size;
	}
public:
	static PFX_INLINE	usize__t							cache_buffer_size ()
	{
		return CACHE_BUFFER_SIZE;//(0 == CACHE_BUFFER_SIZE ? 1: CACHE_BUFFER_SIZE);
	}
	static const object_id_t&							final_type ()
	{
		static object_id_t obj_id;
		return cobject_id < cstring_t, IString_t >::to_object_id(obj_id);
	}
	PFX_INLINE virtual const object_id_t&	type_id () const
	{
		return final_type();
	}
public:
	result_t									init_string(const cstring_t& __otherstr);
	virtual result_t						init_string (usize__t __size);
	virtual result_t						init_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size);
	virtual result_t						init_string (const IString_t* PARAM_IN other_ptr);
	
	virtual result_t						resize_string (usize__t __size);
	virtual result_t						garbage_collection (GarbageCollectionMODE_t mode = GC_DEFUALT_MODE, 
																						usize__t new_size = 0);

	virtual result_t						append_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size);
	virtual result_t						append_string (const IString_t* PARAM_IN append_string_ptr);
	virtual result_t						append_string (const cstring_t& PARAM_IN __append_str);

	virtual result_t						append_front (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size);
	virtual result_t						append_front (const IString_t* PARAM_IN append_string_ptr);
	virtual result_t						append_front (const cstring_t& PARAM_IN __append_str);

	virtual result_t						insert_string (uindex_t __offset, const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size);
	virtual result_t						insert_string (uindex_t __offset, const IString_t* PARAM_IN insert_string_ptr);
	virtual result_t						insert_string (uindex_t __offset, const cstring_t& PARAM_IN __append_str);

	virtual result_t						clip_string_remain_left (uindex_t clip_index, IString_t* PARAM_OUT other_ptr);
	virtual result_t						clip_string_remain_left (uindex_t clip_index, cstring_t& PARAM_OUT __other);

	virtual result_t						clip_string_remain_right (uindex_t clip_index, IString_t* PARAM_OUT other_ptr);
	virtual result_t						clip_string_remain_right (uindex_t clip_index, cstring_t& PARAM_OUT __other);
	
	virtual usize__t						get_cache_buffer_size () const;

	virtual const element_t*	get_string () const;
	virtual usize__t						get_length () const;
	virtual usize__t						get_string_buffer_size () const;

	virtual element_t&				reference (uindex_t __index); 
	virtual const element_t&	reference (uindex_t __index) const; 

	virtual const element_t*	get_charbuffer_at (uindex_t index_) const;
	virtual usize__t						set_charbuffer_at (uindex_t index_, 
																						const element_t* PARAM_IN char_buffer, 
																						usize__t buf_size);

	virtual  const element_t*	sub_string_buffer (uindex_t index_) const;

	virtual  const IString_t *		sub_string (uindex_t index_,
																			IString_t* PARAM_OUT sub_string_ptr)  const;
	virtual  const IString_t*		sub_string (uindex_t	index_,
																		usize__t		sub_string_size, 
																		IString_t* PARAM_OUT sub_string_ptr)  const;

	virtual  const cstring_t *		sub_string (uindex_t index_,cstring_t& PARAM_OUT __sub_string)  const;
	virtual  const cstring_t*		sub_string (uindex_t index_,
																		usize__t		sub_string_size, 
																		cstring_t& PARAM_OUT __sub_string)  const;

	virtual result_t						sub_string (uindex_t __index, usize__t __size);

	virtual result_t						to_same_string (IString_t* PARAM_OUT same_string_ptr);
	virtual result_t						to_same_string (cstring_t& PARAM_OUT __same_string);

	virtual result_t						copy_to (IString_t* PARAM_OUT to_string_ptr)  const;
	virtual result_t						copy_to (cstring_t& PARAM_OUT __to_string)  const;
	virtual result_t						dispose ();
	virtual result_t						clean ();
};


//template < class element_t,  
//	typename elem_compare = pecker_value_compare < element_t >, 
//	const unsigned int CACHE_BUFFER_SIZE = DEFUALT_STRING_CACHE_BUFFER_SIZE >
//class PFX_DATA_TEMPALE_API cshare_string : public cstring < element_t,  elem_compare, CACHE_BUFFER_SIZE >
//{
//public:
//	typedef typename	element_t								element_t;
//	typedef typename	element_t								item_type_t;
//	typedef typename	elem_compare						compare_two_item_t;
//	typedef PFX_CSTRING_TYPE									cstring_t;
//	typedef typename IPfx_string < element_t >		IString_t;
//	typedef PFX_CSSTRING_TYPE								cshare_string_t;
//protected:
//	IString_t*	m_prev_string_ptr;
//	IString_t*	m_next_string_ptr;
//protected:
//	virtual result_t	copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
//																boolean_t	bheader_cache_buffer, 
//																boolean_t & PARAM_INOUT is_reference);
//public:
//	virtual const IString_t* get_prev_node () const;
//	virtual const IString_t* get_next_node () const;
//protected:
//	virtual void set_prev_node (IString_t* PARAM_IN node_ptr);
//	virtual void set_next_node  (IString_t* PARAM_IN node_ptr);
//
//public:
//	cshare_string ();
//	cshare_string (const cshare_string_t & other_) throw (result_t);
//	virtual ~cshare_string ();
//public:
//	PFX_INLINE int	compare (const IString_t* other_ptr) const;
//	PFX_INLINE int	compare (const cshare_string_t & other_) const;
//};
PECKER_END

#endif			//PFX_CSTRING_H_
