/*
 * pfx_block.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BLOCK_H_
#define		PFX_BLOCK_H_

#include "pfx_defines.h"

PECKER_BEGIN

#define DEFUALT_CACHE_BUFFER_SIZE (16)
#define PFX_BLOCKHEADER_TEMPLATE_DEFINES template < class element_ >
#define PFX_BLOCKHEADER_TEMPLATE_PARAMS  < element_ >

#define PFX_BLOCK_TEMPLATE_DEFINES template < class element_ >
#define PFX_BLOCK_TEMPLATE_PARAMS  < element_ >

#define PFX_STATIC_BLOCK_TEMPLATE_DEFINES template < class element_ , const unsigned int CACHE_BUFFER_SIZE >
#define PFX_STATIC_BLOCK_TEMPLATE_PARAMS  < element_, CACHE_BUFFER_SIZE >

#define PFX_DYNAMIC_BLOCK_TEMPLATE_DEFINES template < class element_ , const unsigned int CACHE_BUFFER_SIZE, class element_allocator >
#define PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS  < element_, CACHE_BUFFER_SIZE, element_allocator >

#define PFX_SHARE_BLOCK_TEMPLATE_DEFINES		template < class element_, class elements_block >
#define PFX_SHARE_BLOCK_TEMPLATE_PARAMS	< element_, elements_block >

template < class element_ >
struct pfx_block_header
{
	pfx_usize_t		m_element_buffer_size;
	pfx_usize_t		m_element_count;
	element_*		m_element_ptr;

	pfx_block_header () : m_element_buffer_size (0),m_element_count(0),m_element_ptr(null){;};
};

typedef enum enumBLOCK_STATUS
{
	PFX_BLOCK_NORMAL = 0,
	PFX_BLOCK_EMPTY,
	PFX_BLOCK_FULL,
	PFX_BLOCK_ERROR,
	PFX_BLOCK_MEM_LOW,

	PFX_BLOCK_STATUS_COUNT
}PFX_BLOCK_STATUS_t;

PFX_BLOCK_TEMPLATE_DEFINES
PFX_Interface IPfx_block
{
	virtual ~IPfx_block () {;};

	virtual pfx_result_t init (pfx_usize_t element_size, pfx_usize_t allocate_step = 0, 
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE) = 0;

	virtual pfx_result_t resize (pfx_usize_t element_size, pfx_usize_t allocate_step = 0,
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE) = 0;

	virtual  unsigned int							get_cache_size () const = 0;
	virtual  pfx_result_t							dispose () = 0;
	virtual  pfx_result_t							copy (const IPfx_block PFX_BLOCK_TEMPLATE_PARAMS * other_ptr) = 0;
	virtual  PFX_BLOCK_STATUS_t			push_back (const element_& elem) = 0;
	virtual  element_*								pop_back (PFX_BLOCK_STATUS_t& status_) = 0;
	virtual  PFX_BLOCK_STATUS_t			push_front (const element_& elem) = 0;
	virtual  element_*								pop_front (PFX_BLOCK_STATUS_t& status_) = 0;
	virtual  pfx_usize_t							get_buffer_size () const = 0;
	virtual	 pfx_usize_t							size () const = 0;
	virtual	 const element_*					get_buffer (pfx_uindex_t index_ = 0) const = 0;
	virtual pfx_usize_t								set_buffer (pfx_uindex_t index_, const element_* elements_ptr,
																pfx_usize_t element_size,pfx_result_t& status_) = 0;
	
	virtual	 pfx_result_t							clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE) = 0;
	virtual	 pfx_boolean_t						is_full () const = 0;
	virtual pfx_boolean_t						is_empty () const = 0;

protected:
	virtual	 element_*								get_buffer_reference (pfx_uindex_t index_ = 0) = 0;
};

template < class element_,const unsigned int CACHE_BUFFER_SIZE = DEFUALT_CACHE_BUFFER_SIZE >
class pfx_static_block : public IPfx_block PFX_BLOCK_TEMPLATE_PARAMS
{
private:
	pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS m_header;
	element_				m_cache_buffer [DEFUALT_CACHE_BUFFER_SIZE];
protected:
	pfx_result_t reset_header ();
	pfx_result_t bind_block_header (const pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS & block_header);
public:
	pfx_static_block ();
	pfx_static_block (const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS & other_) throw (pfx_result_t);
	pfx_static_block (const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS * other_ptr) throw (pfx_result_t);
	virtual ~pfx_static_block ();
public:
	pfx_result_t init (pfx_usize_t element_size, pfx_usize_t allocate_step = 0, 
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE);

	pfx_result_t resize (pfx_usize_t element_size, pfx_usize_t allocate_step = 0,
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE);
public:
	PFX_INLINE  unsigned int							get_cache_size () const
	{
		return CACHE_BUFFER_SIZE;
	}
public:
	virtual pfx_result_t									dispose ();
	pfx_result_t												copy (const IPfx_block PFX_BLOCK_TEMPLATE_PARAMS * other_ptr);
	pfx_result_t												copy (const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS * other_ptr);
	PFX_INLINE PFX_BLOCK_STATUS_t			push_back (const element_& elem);
	PFX_INLINE element_*								pop_back (PFX_BLOCK_STATUS_t& status_);
	PFX_INLINE PFX_BLOCK_STATUS_t			push_front (const element_& elem);
	PFX_INLINE element_*								pop_front (PFX_BLOCK_STATUS_t& status_);
	PFX_INLINE pfx_usize_t							get_buffer_size () const;
	PFX_INLINE	 pfx_usize_t							size () const;
	PFX_INLINE	 const element_*					get_buffer (pfx_uindex_t index_ = 0) const;
	PFX_INLINE pfx_usize_t							set_buffer (pfx_uindex_t index_, const element_* elements_ptr,pfx_usize_t element_size,pfx_result_t& status_);
	PFX_INLINE element_*								get_buffer_reference (pfx_uindex_t index_ = 0);
	PFX_INLINE pfx_usize_t							move_data (pfx_uindex_t first_element_index,pfx_usize_t move_size,pfx_uindex_t move_to_index);
	PFX_INLINE	 pfx_result_t							clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
	PFX_INLINE	 pfx_boolean_t						is_full () const;
	PFX_INLINE pfx_boolean_t						is_empty () const;
};

template < class element_, const unsigned int CACHE_BUFFER_SIZE, class element_allocator >
class pfx_dynamic_block : public virtual pfx_static_block < element_, CACHE_BUFFER_SIZE >
{
private:
	pfx_boolean_t	m_lock_dynamic_resize;
	pfx_usize_t			m_resize_step;
public:
	pfx_dynamic_block ();
	pfx_dynamic_block (const pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS & other_) throw (pfx_result_t);
	pfx_dynamic_block (const pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS * other_ptr) throw (pfx_result_t);
	virtual ~pfx_dynamic_block ();
//public:
//	virtual element_* allocate_elements (pfx_usize_t element_size) {return new element_[element_size];};
//	virtual element_* reallocate_elements (element_* PARAM_IN element_ptr, pfx_usize_t element_size) {return null;};
//	virtual pfx_result_t deallocate_elements (element_* PARAM_IN element_ptr) 
//	{if (element_ptr) {delete [] element_ptr; return PFX_STATUS_OK;}return PFX_STATUS_INVALID_PARAMS;};
public:
static pfx_result_t block_init (pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS &header, 
													pfx_usize_t element_size,pfx_boolean_t new_buffer = PFX_BOOL_FALSE);

static pfx_result_t block_resize (pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS &header,
														pfx_usize_t element_size,pfx_boolean_t new_buffer = PFX_BOOL_FALSE);
public:
	void				lock_resize ();
	void				unlock_resize ();
public:
	pfx_result_t init (pfx_usize_t element_size, pfx_usize_t allocate_step = 0, 
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE);
	
	pfx_result_t resize (pfx_usize_t element_size, pfx_usize_t allocate_step = 0,
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE);

public:
//	virtual pfx_result_t									dispose ();
	pfx_result_t												copy (const IPfx_block PFX_BLOCK_TEMPLATE_PARAMS * other_ptr);
	pfx_result_t												copy (const pfx_static_block PFX_STATIC_BLOCK_TEMPLATE_PARAMS * other_ptr);
	pfx_result_t												copy (const pfx_dynamic_block PFX_DYNAMIC_BLOCK_TEMPLATE_PARAMS * other_ptr);
	PFX_INLINE PFX_BLOCK_STATUS_t			push_back (const element_& elem);
	//PFX_INLINE const element_*					pop_back (PFX_BLOCK_STATUS_t& status_);
	PFX_INLINE PFX_BLOCK_STATUS_t			push_front (const element_& elem);
	//PFX_INLINE PFX_BLOCK_STATUS_t			pop_front (PFX_BLOCK_STATUS_t& status_);
	PFX_INLINE	 pfx_result_t							clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
};

template < class element_, class elements_block >
class pfx_share_block_base : public IPfx_block PFX_BLOCK_TEMPLATE_PARAMS
{
private:
	pfx_block_header PFX_BLOCKHEADER_TEMPLATE_PARAMS	m_header;
	elements_block*																			m_block_ptr;
private:
	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS*	m_prev_block_ptr;
	pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS*	m_next_block_ptr;
public:
	PFX_INLINE const pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* get_prev_node () const
	{
		return m_prev_block_ptr;
	}
	PFX_INLINE const pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* get_next_node () const
	{
		return m_next_block_ptr;
	}
	PFX_INLINE void set_prev_node (pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* PARAM_IN node_ptr)
	{
		m_prev_block_ptr = node_ptr;
	}
	PFX_INLINE void set_next_node  (pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* PARAM_IN node_ptr)
	{
		m_next_block_ptr = node_ptr;
	}

public:
	pfx_share_block_base ();
	pfx_share_block_base (const pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS & other_) throw (pfx_result_t);
	pfx_share_block_base (const pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS * other_ptr) throw (pfx_result_t);
	virtual ~pfx_share_block_base ();
protected:
	virtual elements_block*							new_block () {return new elements_block;};
	virtual pfx_result_t									release_block (elements_block* PARAM_IN release_block_ptr)
	{if (release_block_ptr) {delete release_block_ptr;return PFX_STATUS_OK;}return PFX_STATUS_INVALID_PARAMS;};
public:
	virtual pfx_result_t									dispose ();
	pfx_result_t												copy (const IPfx_block PFX_BLOCK_TEMPLATE_PARAMS * other_ptr);
public:
	PFX_INLINE pfx_boolean_t						is_reference () const;
public:
	PFX_INLINE pfx_result_t							swap (pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS & other_);
//protected:
//	PFX_INLINE pfx_result_t							remove_reference ();
public:
	pfx_result_t init (pfx_usize_t element_size, pfx_usize_t allocate_step = 0, 
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE);

	pfx_result_t resize (pfx_usize_t element_size, pfx_usize_t allocate_step = 0,
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE);

	pfx_result_t sub_share_block (pfx_share_block_base PFX_SHARE_BLOCK_TEMPLATE_PARAMS* PARAM_INOUT sub_share_block_ptr,
		pfx_uindex_t first_index,pfx_usize_t sub_size);
public:
	PFX_INLINE  unsigned int							get_cache_size () const
	{
		return 0;
	}
protected:
	PFX_INLINE	 element_*								get_buffer_reference (pfx_uindex_t index_ = 0);
public:
	PFX_INLINE PFX_BLOCK_STATUS_t			push_back (const element_& elem);
	PFX_INLINE const element_*					pop_back (PFX_BLOCK_STATUS_t& status_);
	PFX_INLINE PFX_BLOCK_STATUS_t			push_front (const element_& elem);
	PFX_INLINE PFX_BLOCK_STATUS_t			pop_front (PFX_BLOCK_STATUS_t& status_);

	PFX_INLINE pfx_usize_t							get_buffer_size () const;
	PFX_INLINE	 pfx_usize_t							size () const;
	PFX_INLINE	 const element_*					get_buffer (pfx_uindex_t index_ = 0) const;
	PFX_INLINE pfx_usize_t							set_buffer (pfx_uindex_t index_, 
																		const element_* elements_ptr,pfx_usize_t element_size,pfx_result_t& status_);
	PFX_INLINE	 pfx_result_t							clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
	PFX_INLINE	 pfx_boolean_t						is_full () const;
	PFX_INLINE pfx_boolean_t						is_empty () const;
};

PECKER_END

#endif			//PFX_BLOCK_H_
