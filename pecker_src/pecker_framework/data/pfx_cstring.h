/*
 * pfx_cstring.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CSTRING_H_
#define		PFX_CSTRING_H_

#include "../pfx_defines.h"
//#include "pfx_block.h"
#include "pfx_clist.h"
#include "pecker_value_compare.h"
#include "pfx_data_traits.h"

PECKER_BEGIN

#define DEFUALT_CACHE_BUFFER_SIZE (16)
#define PFX_BLOCKHEADER_TEMPLATE_DEFINES template < class element_t >
#define PFX_BLOCKHEADER_TEMPLATE_PARAMS  < element_t >

template < class element_t >
struct PFX_DATA_TEMPALE_API pfx_block_header
{
	usize__t		m_element_buffer_size;
	usize__t		m_element_count;
	element_t*			m_element_ptr;

	pfx_block_header () : m_element_buffer_size (0),m_element_count(0),m_element_ptr(null){;};
};

#define PFX_CSTRING_CODE	(0XFFFF0000)

#define DEFUALT_STRING_CACHE_BUFFER_SIZE DEFUALT_CACHE_BUFFER_SIZE
#define PFX_STRING_TEMPLATE_DEFINES template < class element_t >
#define PFX_STRING_TEMPLATE_PARAMS  < element_t >

#define PFX_CSTRING_TEMPLATE_DEFINES template < class element_t,  class elem_compare /*= pecker_value_compare < element_t >*/, const unsigned int CACHE_BUFFER_SIZE /*= DEFUALT_STRING_CACHE_BUFFER_SIZE*/ >
#define PFX_CSTRING_TEMPLATE_PARAMS   < element_t, elem_compare, CACHE_BUFFER_SIZE  >

#define PFX_CSTRING cstring < element_t, elem_compare, CACHE_BUFFER_SIZE >
#define PFX_CSTRING_TYPE typename cstring < element_t, elem_compare, CACHE_BUFFER_SIZE >

#define PFX_CSSTRING cshare_string < element_t, elem_compare, CACHE_BUFFER_SIZE >
#define PFX_CSSTRING_TYPE typename cshare_string < element_t, elem_compare, CACHE_BUFFER_SIZE >

typedef enum enumGarbageCollectionMODE
{
	GC_DEFUALT_MODE = 0,
	GC_USER_MODE,
	GC_MODE_COUNT
}GarbageCollectionMODE_t;

template < class element_t >
PFX_Interface PFX_DATA_TEMPALE_API IPfx_string_header_operate
{
virtual ~IPfx_string_header_operate () {;};
virtual	result_t				copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
	boolean_t	bheader_cache_buffer, 
	boolean_t & PARAM_INOUT is_reference) = 0;
virtual	result_t				reset_header () = 0;
virtual result_t				attach_extern_string_buffer (element_t* PARAM_IN elem_ptr) = 0;
//virtual void								enable_reference (pfx_boolean_t bEnable) = 0;
};

template < class element_t >
PFX_Interface PFX_DATA_TEMPALE_API IPfx_string : public IPfx_string_header_operate < element_t >
{
public:
	typedef typename IPfx_string PFX_STRING_TEMPLATE_PARAMS IString_t;
	virtual ~IPfx_string () {;};
protected:
	virtual	result_t				copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																			boolean_t	bheader_cache_buffer, 
																			boolean_t & PARAM_INOUT is_reference) = 0;
	virtual	result_t				reset_header () = 0;
	virtual result_t				attach_extern_string_buffer (element_t* PARAM_IN elem_ptr) = 0;
protected:
	//virtual PFX_INLINE	void enable_reference (pfx_boolean_t bEnable){;};
public:
	virtual const IString_t* get_prev_node () const {return null;}
	virtual const IString_t* get_next_node () const {return null;}

	virtual void set_prev_node (IString_t* PARAM_IN node_ptr) {;};
	virtual void set_next_node  (IString_t* PARAM_IN node_ptr) {;};
public:
	//virtual	pfx_result_t				swap_string (IPfx_string* PARAM_INOUT other_string_ptr) = 0;
	virtual const element_t*		get_string () const = 0;
	virtual usize__t				get_length () const = 0;
	virtual usize__t				get_string_buffer_size () const = 0;

	virtual const element_t*		get_charbuffer_at (uindex_t index_) const = 0;
	virtual usize__t				set_charbuffer_at (uindex_t index_, const element_t* PARAM_IN char_buffer, usize__t buf_size) = 0;
	
	virtual  const element_t*		sub_string_buffer (uindex_t index_) const = 0;

	virtual  const IString_t*	sub_string (uindex_t index_,
																																IString_t* PARAM_INOUT sub_string_ptr)  = 0;
	virtual  const IString_t*	sub_string (uindex_t index_,
																																usize__t		sub_string_size, 
																																IString_t* PARAM_INOUT sub_string_ptr)  = 0;
	virtual  const IString_t *sub_string_const (uindex_t index_,
																																				IString_t* PARAM_INOUT sub_string_ptr)  const = 0;
	virtual  const IString_t*	sub_string_const (uindex_t index_,
																																			usize__t		sub_string_size, 
																																			IString_t* PARAM_INOUT sub_string_ptr)  const = 0;


	virtual	 boolean_t			find_first_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size,uindex_t& find_index) const = 0;
	virtual	 boolean_t			find_first_string (const IString_t * PARAM_IN sub_string_ptr,uindex_t & find_index) const = 0;

	virtual	 boolean_t			find_string (uindex_t begin_index, const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size,uindex_t& find_index) const = 0;
	virtual	 boolean_t			find_string (uindex_t begin_index, IPfx_string* PARAM_INOUT sub_string_ptr,uindex_t& find_index) const = 0;

	virtual	 boolean_t			find_near_string (uindex_t begin_index, const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size,uindex_t& find_index, usize__t& same_chars_count) const = 0;
	virtual	 boolean_t			find_near_string (uindex_t begin_index, IPfx_string* PARAM_INOUT sub_string_ptr,uindex_t& find_index, usize__t& same_chars_count) const = 0;

	virtual result_t				init_string (usize__t size_) = 0;
	virtual result_t				init_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size) = 0;
	virtual result_t				init_string (const IPfx_string* PARAM_IN other_ptr) = 0;

	virtual result_t				resize_string (usize__t size_) = 0;
	virtual result_t				garbage_collection (GarbageCollectionMODE_t mode = GC_DEFUALT_MODE,
																						usize__t new_size = 0) = 0;

	virtual result_t				append_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size) = 0;
	virtual result_t				append_string (const IString_t* PARAM_IN append_string_ptr) = 0;

	virtual result_t				append_front (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size) = 0;
	virtual result_t				append_front (const IString_t* PARAM_IN append_string_ptr) = 0;

	virtual result_t				clip_string_remain_left (uindex_t clip_index, IString_t* PARAM_IN other_ptr) = 0;
	virtual result_t				clip_string_remain_right (uindex_t clip_index, IString_t* PARAM_IN other_ptr) = 0;
	virtual	ulong_t				get_string_type_code () const = 0;
	virtual usize__t				get_cache_buffer_size () const = 0;
	
	

	//virtual pfx_result_t				copy_string () const = 0;
	virtual int								compare (const IString_t* other_ptr) const = 0;


	
};

template < class element_t,  
	class elem_compare = pecker_value_compare < element_t >, 
	const unsigned int CACHE_BUFFER_SIZE = DEFUALT_STRING_CACHE_BUFFER_SIZE >
class PFX_DATA_TEMPALE_API cstring : public IPfx_string < element_t >
{
public:
	typedef typename element_t								element_t;
	typedef typename element_t								item_type_t;
	typedef typename elem_compare						compare_two_item_t;
	typedef PFX_CSTRING_TYPE									cstring_t;
	typedef typename IPfx_string < element_t >		IString_t;
protected:
	pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS	m_header;
	element_t																							m_cache_buffer [(0 == CACHE_BUFFER_SIZE ? 1: CACHE_BUFFER_SIZE)];
	element_t*																						m_extern_string_buffer_ptr;

protected:
	PFX_INLINE result_t							reset_header ();
	PFX_INLINE element_t*					resize_new_stringbuffer (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																									usize__t elememt_size, 
																									result_t& PARAM_INOUT status_); 
	result_t												attach_extern_string_buffer (element_t* PARAM_IN elem_ptr);
	PFX_INLINE result_t							remove_referance ();
	PFX_INLINE result_t							add_referance (IString_t* PARAM_IN other_ptr);
	virtual PFX_INLINE boolean_t		is_reference ();

	virtual PFX_INLINE element_t*		reallocate_string_buffer (element_t* PARAM_INOUT elem_ptr, 
																											usize__t element_count);
	virtual PFX_INLINE element_t*		new_string_buffer (usize__t element_count);
	virtual PFX_INLINE result_t			delete_string_buffer (element_t* PARAM_IN elem_ptr);
public:
	virtual const IString_t*					get_prev_node () const {return null;}
	virtual const IString_t*					get_next_node () const {return null;}
protected:
	virtual void set_prev_node			(IString_t* PARAM_IN node_ptr) {;};
	virtual void set_next_node			(IString_t* PARAM_IN node_ptr) {;};
public:
	cstring ();
	cstring (const cstring_t & other_) throw (result_t);
	virtual ~cstring ();
public:
	PFX_INLINE ulong_t						get_string_type_code () const;
	PFX_INLINE usize__t					get_cache_buffer_size () const;
protected:
	virtual	result_t								copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																			boolean_t	bheader_cache_buffer, 
																			boolean_t & PARAM_INOUT is_reference);
	result_t											init_string (usize__t size_,element_t*& PARAM_INOUT del_extern_string);
public:
	PFX_INLINE const element_t*	get_string () const;
	PFX_INLINE usize__t					get_length () const;
	PFX_INLINE usize__t					get_string_buffer_size () const;

	const element_t*							get_charbuffer_at (uindex_t index_) const;
	usize__t											set_charbuffer_at (uindex_t index_, const element_t* PARAM_IN char_buffer, usize__t buf_size);

	const element_t*							sub_string_buffer (uindex_t index_) const;

	const IString_t*							sub_string (uindex_t index_, IString_t* PARAM_INOUT sub_string_ptr) ;
	const IString_t*							sub_string (uindex_t index_, usize__t sub_string_size, IString_t* PARAM_INOUT sub_string_ptr) ;

	const IString_t*							sub_string_const (uindex_t index_,IString_t* PARAM_INOUT sub_string_ptr)  const;

	const IString_t*							sub_string_const (uindex_t index_,
																								usize__t		sub_string_size, 
																								IString_t* PARAM_INOUT sub_string_ptr)  const;

	 boolean_t										find_first_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size,
																							uindex_t& find_index) const;
	 boolean_t										find_first_string (const IString_t * PARAM_IN find_string_ptr,uindex_t & find_index) const;

	 boolean_t										find_string (uindex_t begin_index, const element_t* PARAM_IN str_chars_buffer_ptr,
																					usize__t buffer_size,uindex_t& find_index) const;
	 boolean_t										find_string (uindex_t begin_index, IString_t * PARAM_INOUT sub_string_ptr,
																					uindex_t& find_index) const;

	 boolean_t										find_near_string (uindex_t begin_index, const element_t* PARAM_IN str_chars_buffer_ptr,
																							usize__t buffer_size,uindex_t& find_index, usize__t& same_chars_count) const;
	 boolean_t										find_near_string (uindex_t begin_index, IString_t * PARAM_INOUT sub_string_ptr,
																							uindex_t& find_index, usize__t& same_chars_count) const;

	result_t											init_string (usize__t size_);
	result_t											init_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size);
	result_t											init_string (const IString_t * PARAM_IN other_ptr);

	result_t											resize_string (usize__t size_);
	result_t											garbage_collection (GarbageCollectionMODE_t mode = GC_DEFUALT_MODE,
																									usize__t new_size = 0);

	result_t											append_string (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size);
	result_t											append_string (const IString_t* PARAM_IN append_string_ptr);

	result_t											append_front (const element_t* PARAM_IN str_chars_buffer_ptr,usize__t buffer_size);
	result_t											append_front (const IString_t* PARAM_IN append_string_ptr);

	result_t											clip_string_remain_left (uindex_t clip_index, IString_t* PARAM_IN other_ptr);
	result_t											clip_string_remain_right (uindex_t clip_index, IString_t* PARAM_IN other_ptr);

	int													compare (const IString_t* other_ptr) const;
	int													compare (const cstring_t & other_) const;

public:
	static PFX_INLINE	usize__t			cache_buffer_size ();
	
};

template < class element_t,  
	typename elem_compare = pecker_value_compare < element_t >, 
	const unsigned int CACHE_BUFFER_SIZE = DEFUALT_STRING_CACHE_BUFFER_SIZE >
class PFX_DATA_TEMPALE_API cshare_string : public cstring < element_t,  elem_compare, CACHE_BUFFER_SIZE >
{
public:
	typedef typename	element_t								element_t;
	typedef typename	element_t								item_type_t;
	typedef typename	elem_compare						compare_two_item_t;
	typedef PFX_CSTRING_TYPE									cstring_t;
	typedef typename IPfx_string < element_t >		IString_t;
	typedef PFX_CSSTRING_TYPE								cshare_string_t;
protected:
	IString_t*	m_prev_string_ptr;
	IString_t*	m_next_string_ptr;
protected:
	virtual result_t	copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																boolean_t	bheader_cache_buffer, 
																boolean_t & PARAM_INOUT is_reference);
public:
	virtual const IString_t* get_prev_node () const;
	virtual const IString_t* get_next_node () const;
protected:
	virtual void set_prev_node (IString_t* PARAM_IN node_ptr);
	virtual void set_next_node  (IString_t* PARAM_IN node_ptr);

public:
	cshare_string ();
	cshare_string (const cshare_string_t & other_) throw (result_t);
	virtual ~cshare_string ();
public:
	PFX_INLINE int	compare (const IString_t* other_ptr) const;
	PFX_INLINE int	compare (const cshare_string_t & other_) const;
};
PECKER_END

#endif			//PFX_CSTRING_H_
