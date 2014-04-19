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
#define PFX_BLOCKHEADER_TEMPLATE_DEFINES template < class element_ >
#define PFX_BLOCKHEADER_TEMPLATE_PARAMS  < element_ >

template < class element_ >
struct pfx_block_header
{
	pfx_usize_t		m_element_buffer_size;
	pfx_usize_t		m_element_count;
	element_*		m_element_ptr;

	pfx_block_header () : m_element_buffer_size (0),m_element_count(0),m_element_ptr(null){;};
};

#define PFX_CSTRING_CODE	(0XFFFF0000)

#define DEFUALT_STRING_CACHE_BUFFER_SIZE DEFUALT_CACHE_BUFFER_SIZE
#define PFX_STRING_TEMPLATE_DEFINES template < class element_ >
#define PFX_STRING_TEMPLATE_PARAMS  < element_ >

#define PFX_CSTRING_TEMPLATE_DEFINES template < class element_,  class elem_compare /*= pecker_value_compare < element_ >*/, const unsigned int CACHE_BUFFER_SIZE /*= DEFUALT_STRING_CACHE_BUFFER_SIZE*/ >
	//template < class element_ , const unsigned int CACHE_BUFFER_SIZE, class element_allocator, typename elem_compare >
#define PFX_CSTRING_TEMPLATE_PARAMS   < element_, elem_compare, CACHE_BUFFER_SIZE  >
	//< element_, CACHE_BUFFER_SIZE, element_allocator, elem_compare >

typedef enum enumGarbageCollectionMODE
{
	GC_DEFUALT_MODE = 0,
	GC_USER_MODE,
	GC_MODE_COUNT
}GarbageCollectionMODE_t;

template < class element_ >
PFX_Interface IPfx_string_header_operate
{
virtual ~IPfx_string_header_operate () {;};
virtual	pfx_result_t				copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
	pfx_boolean_t	bheader_cache_buffer, 
	pfx_boolean_t & PARAM_INOUT is_reference) = 0;
virtual	pfx_result_t				reset_header () = 0;
virtual pfx_result_t				attach_extern_string_buffer (element_* PARAM_IN elem_ptr) = 0;
//virtual void								enable_reference (pfx_boolean_t bEnable) = 0;
};

template < class element_ >
PFX_Interface IPfx_string : public IPfx_string_header_operate < element_ >
{
	virtual ~IPfx_string () {;};
protected:
	virtual	pfx_result_t				copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																			pfx_boolean_t	bheader_cache_buffer, 
																			pfx_boolean_t & PARAM_INOUT is_reference) = 0;
	virtual	pfx_result_t				reset_header () = 0;
	virtual pfx_result_t				attach_extern_string_buffer (element_* PARAM_IN elem_ptr) = 0;
protected:
	//virtual PFX_INLINE	void enable_reference (pfx_boolean_t bEnable){;};
public:
	virtual const IPfx_string PFX_STRING_TEMPLATE_PARAMS* get_prev_node () const {return null;}
	virtual const IPfx_string PFX_STRING_TEMPLATE_PARAMS* get_next_node () const {return null;}

	virtual void set_prev_node (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN node_ptr) {;};
	virtual void set_next_node  (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN node_ptr) {;};
public:
	//virtual	pfx_result_t				swap_string (IPfx_string* PARAM_INOUT other_string_ptr) = 0;
	virtual const element_*		get_string () const = 0;
	virtual pfx_usize_t					get_length () const = 0;
	virtual pfx_usize_t					get_string_buffer_size () const = 0;

	virtual const element_*		get_charbuffer_at (pfx_uindex_t index_) const = 0;
	virtual pfx_usize_t					set_charbuffer_at (pfx_uindex_t index_, const element_* PARAM_IN char_buffer, pfx_usize_t buf_size) = 0;
	
	virtual  const element_*		sub_string_buffer (pfx_uindex_t index_) const = 0;

	virtual  const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	sub_string (pfx_uindex_t index_,
																																IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)  = 0;
	virtual  const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	sub_string (pfx_uindex_t index_,
																																pfx_usize_t		sub_string_size, 
																																IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)  = 0;
	virtual  const IPfx_string PFX_STRING_TEMPLATE_PARAMS *sub_string_const (pfx_uindex_t index_,
																																				IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)  const = 0;
	virtual  const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	sub_string_const (pfx_uindex_t index_,
																																			pfx_usize_t		sub_string_size, 
																																			IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)  const = 0;


	virtual	 pfx_boolean_t			find_first_string (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size,pfx_uindex_t& find_index) const = 0;
	virtual	 pfx_boolean_t			find_first_string (const IPfx_string PFX_STRING_TEMPLATE_PARAMS * PARAM_IN sub_string_ptr,pfx_uindex_t & find_index) const = 0;

	virtual	 pfx_boolean_t			find_string (pfx_uindex_t begin_index, const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size,pfx_uindex_t& find_index) const = 0;
	virtual	 pfx_boolean_t			find_string (pfx_uindex_t begin_index, IPfx_string* PARAM_INOUT sub_string_ptr,pfx_uindex_t& find_index) const = 0;

	virtual	 pfx_boolean_t			find_near_string (pfx_uindex_t begin_index, const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size,pfx_uindex_t& find_index, pfx_usize_t& same_chars_count) const = 0;
	virtual	 pfx_boolean_t			find_near_string (pfx_uindex_t begin_index, IPfx_string* PARAM_INOUT sub_string_ptr,pfx_uindex_t& find_index, pfx_usize_t& same_chars_count) const = 0;

	virtual pfx_result_t				init_string (pfx_usize_t size_) = 0;
	virtual pfx_result_t				init_string (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size) = 0;
	virtual pfx_result_t				init_string (const IPfx_string* PARAM_IN other_ptr) = 0;

	virtual pfx_result_t				resize_string (pfx_usize_t size_) = 0;
	virtual pfx_result_t				garbage_collection (GarbageCollectionMODE_t mode = GC_DEFUALT_MODE,
																						pfx_usize_t new_size = 0) = 0;

	virtual pfx_result_t				append_string (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size) = 0;
	virtual pfx_result_t				append_string (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN append_string_ptr) = 0;

	virtual pfx_result_t				append_front (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size) = 0;
	virtual pfx_result_t				append_front (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN append_string_ptr) = 0;

	virtual pfx_result_t				clip_string_remain_left (pfx_uindex_t clip_index, IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr) = 0;
	virtual pfx_result_t				clip_string_remain_right (pfx_uindex_t clip_index, IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr) = 0;
	virtual	pfx_ulong_t				get_string_type_code () const = 0;
	virtual pfx_usize_t					get_cache_buffer_size () const = 0;
	
	

	//virtual pfx_result_t				copy_string () const = 0;
	virtual int								compare (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* other_ptr) const = 0;


	
};

template < class element_,  class elem_compare = pecker_value_compare < element_ >, const unsigned int CACHE_BUFFER_SIZE = DEFUALT_STRING_CACHE_BUFFER_SIZE >
class pfx_cstring : public IPfx_string < element_ >
{
public:
	typedef element_				item_type_t;
	typedef elem_compare	compare_two_item_t;
protected:
	pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS	m_header;
	element_																						m_cache_buffer [(0 == CACHE_BUFFER_SIZE ? 1: CACHE_BUFFER_SIZE)];
	element_*																						m_extern_string_buffer_ptr;

protected:
	PFX_INLINE pfx_result_t			reset_header ();
	PFX_INLINE element_*				resize_new_stringbuffer (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																									pfx_usize_t elememt_size, 
																									pfx_result_t& PARAM_INOUT status_); 
	pfx_result_t								attach_extern_string_buffer (element_* PARAM_IN elem_ptr);
	PFX_INLINE pfx_result_t			remove_referance ();
	PFX_INLINE pfx_result_t			add_referance (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr);
	virtual PFX_INLINE pfx_boolean_t		is_reference ();

	virtual PFX_INLINE element_*			reallocate_string_buffer (element_* PARAM_INOUT elem_ptr, 
																											pfx_usize_t element_count);
	virtual PFX_INLINE element_*			new_string_buffer (pfx_usize_t element_count);
	virtual PFX_INLINE pfx_result_t		delete_string_buffer (element_* PARAM_IN elem_ptr);
public:
	virtual const IPfx_string PFX_STRING_TEMPLATE_PARAMS* get_prev_node () const {return null;}
	virtual const IPfx_string PFX_STRING_TEMPLATE_PARAMS* get_next_node () const {return null;}
protected:
	virtual void set_prev_node (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN node_ptr) {;};
	virtual void set_next_node  (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN node_ptr) {;};
public:
	pfx_cstring ();
	pfx_cstring (const pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & other_) throw (pfx_result_t);
	virtual ~pfx_cstring ();
public:
	PFX_INLINE pfx_ulong_t		get_string_type_code () const;
	PFX_INLINE pfx_usize_t		get_cache_buffer_size () const;
protected:
	virtual	pfx_result_t				copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																			pfx_boolean_t	bheader_cache_buffer, 
																			pfx_boolean_t & PARAM_INOUT is_reference);
	pfx_result_t							init_string (pfx_usize_t size_,element_*& PARAM_INOUT del_extern_string);
public:
	PFX_INLINE const element_*		get_string () const;
	PFX_INLINE pfx_usize_t				get_length () const;
	PFX_INLINE pfx_usize_t				get_string_buffer_size () const;

	const element_*		get_charbuffer_at (pfx_uindex_t index_) const;
	pfx_usize_t					set_charbuffer_at (pfx_uindex_t index_, const element_* PARAM_IN char_buffer, pfx_usize_t buf_size);

	const element_*		sub_string_buffer (pfx_uindex_t index_) const;

	const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	sub_string (pfx_uindex_t index_, 
																													IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr) ;
	const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	sub_string (pfx_uindex_t index_,
																													pfx_usize_t		sub_string_size, 
																													IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr) ;

	const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	sub_string_const (pfx_uindex_t index_,IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)  const;

	const IPfx_string PFX_STRING_TEMPLATE_PARAMS*	sub_string_const (pfx_uindex_t index_,
																																pfx_usize_t		sub_string_size, 
																																IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_INOUT sub_string_ptr)  const;

	 pfx_boolean_t			find_first_string (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size,pfx_uindex_t& find_index) const;
	 pfx_boolean_t			find_first_string (const IPfx_string PFX_STRING_TEMPLATE_PARAMS * PARAM_IN find_string_ptr,pfx_uindex_t & find_index) const;

	 pfx_boolean_t			find_string (pfx_uindex_t begin_index, const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size,pfx_uindex_t& find_index) const;
	 pfx_boolean_t			find_string (pfx_uindex_t begin_index, IPfx_string PFX_STRING_TEMPLATE_PARAMS * PARAM_INOUT sub_string_ptr,pfx_uindex_t& find_index) const;

	 pfx_boolean_t			find_near_string (pfx_uindex_t begin_index, const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size,pfx_uindex_t& find_index, pfx_usize_t& same_chars_count) const;
	 pfx_boolean_t			find_near_string (pfx_uindex_t begin_index, IPfx_string PFX_STRING_TEMPLATE_PARAMS * PARAM_INOUT sub_string_ptr,pfx_uindex_t& find_index, pfx_usize_t& same_chars_count) const;

	pfx_result_t				init_string (pfx_usize_t size_);
	pfx_result_t				init_string (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size);
	pfx_result_t				init_string (const IPfx_string PFX_STRING_TEMPLATE_PARAMS * PARAM_IN other_ptr);

	pfx_result_t				resize_string (pfx_usize_t size_);
	pfx_result_t				garbage_collection (GarbageCollectionMODE_t mode = GC_DEFUALT_MODE,
																		pfx_usize_t new_size = 0);

	pfx_result_t				append_string (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size);
	pfx_result_t				append_string (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN append_string_ptr);

	pfx_result_t				append_front (const element_* PARAM_IN str_chars_buffer_ptr,pfx_usize_t buffer_size);
	pfx_result_t				append_front (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN append_string_ptr);

	pfx_result_t				clip_string_remain_left (pfx_uindex_t clip_index, IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr);
	pfx_result_t				clip_string_remain_right (pfx_uindex_t clip_index, IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN other_ptr);

	int								compare (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* other_ptr) const;
	int								compare (const pfx_cstring PFX_CSTRING_TEMPLATE_PARAMS & other_) const;

public:
	static PFX_INLINE	pfx_usize_t			cache_buffer_size ();
	
};

template < class element_,  typename elem_compare = pecker_value_compare < element_ >, const unsigned int CACHE_BUFFER_SIZE = DEFUALT_STRING_CACHE_BUFFER_SIZE >
class pfx_cshare_string : public pfx_cstring < element_,  elem_compare, CACHE_BUFFER_SIZE >
{
public:
	typedef element_				item_type_t;
	typedef elem_compare	compare_two_item_t;
protected:
	IPfx_string PFX_STRING_TEMPLATE_PARAMS*	m_prev_string_ptr;
	IPfx_string PFX_STRING_TEMPLATE_PARAMS*	m_next_string_ptr;
protected:
	virtual pfx_result_t	copy_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & PARAM_IN header,
																pfx_boolean_t	bheader_cache_buffer, 
																pfx_boolean_t & PARAM_INOUT is_reference);
public:
	virtual const IPfx_string PFX_STRING_TEMPLATE_PARAMS* get_prev_node () const;
	virtual const IPfx_string PFX_STRING_TEMPLATE_PARAMS* get_next_node () const;
protected:
	virtual void set_prev_node (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN node_ptr);
	virtual void set_next_node  (IPfx_string PFX_STRING_TEMPLATE_PARAMS* PARAM_IN node_ptr);

public:
	pfx_cshare_string ();
	pfx_cshare_string (const pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS & other_) throw (pfx_result_t);
	virtual ~pfx_cshare_string ();
public:
	PFX_INLINE int	compare (const IPfx_string PFX_STRING_TEMPLATE_PARAMS* other_ptr) const;
	PFX_INLINE int	compare (const pfx_cshare_string PFX_CSTRING_TEMPLATE_PARAMS & other_) const;
};
PECKER_END

#endif			//PFX_CSTRING_H_
