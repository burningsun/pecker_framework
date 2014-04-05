/*
 * pfx_array.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_ARRAY_H_
#define		PFX_ARRAY_H_

#include "pfx_block.h"
#include "pfx_block_codes.h"

PECKER_BEGIN
#define PFX_DEFUALT_ARRAY_AUTO_STEP DEFUALT_CACHE_BUFFER_SIZE

#define PFX_IARRAY_TEMPLATE_DEFINES template < class element_ >
#define PFX_IARRAY_TEMPLATE_PARAMS  < element_ >

#define PFX_ARRAYBASE_TEMPLATE_DEFINES template < class element_, class dynamic_block, class dynamic_blockptr_collection >
#define PFX_ARRAYBASE_TEMPLATE_PARAMS  < element_, dynamic_block, dynamic_blockptr_collection >

template < class element_ >
PFX_Interface IPfx_array
{
	virtual ~IPfx_array () {;};

	virtual pfx_result_t	init (pfx_usize_t element_count,pfx_usize_t allocate_step_size = 0,
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE) = 0;

	virtual pfx_result_t	resize (pfx_usize_t element_size, pfx_usize_t allocate_step = 0,
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE) = 0;
	virtual pfx_result_t							dispose () = 0;

	virtual  pfx_result_t							copy (const IPfx_array PFX_IARRAY_TEMPLATE_PARAMS * other_ptr) = 0;

	virtual  PFX_BLOCK_STATUS_t			push_back (const element_& elem) = 0;
	virtual  const element_*					pop_back (PFX_BLOCK_STATUS_t& status_) = 0;

	virtual  pfx_usize_t							get_buffer_size () const = 0;
	virtual	 pfx_usize_t							size () const = 0;
	virtual	 const element_*					get_element_at (pfx_uindex_t index_) const = 0;
	virtual pfx_usize_t								set_buffer (pfx_uindex_t index_, const element_* elements_ptr,
																					pfx_usize_t element_size,pfx_result_t& status_) = 0;

	virtual	 pfx_result_t							clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE) = 0;
	virtual	 pfx_boolean_t						is_full () const = 0;
	virtual  pfx_boolean_t						is_empty () const = 0;
};

template < class element_, class dynamic_block, class dynamic_blockptr_collection >
class pfx_carray_base : public IPfx_array PFX_IARRAY_TEMPLATE_PARAMS
{
private:
	dynamic_blockptr_collection			m_element_blocks;
	pfx_usize_t											m_element_buffer_size;
	pfx_usize_t											m_element_count;
	pfx_usize_t											m_auto_step;
	pfx_boolean_t									m_lock_auto_step;
protected:
	PFX_INLINE static element_* get_element_at (dynamic_blockptr_collection& blockptr_collection,
			pfx_uindex_t index_i, pfx_uindex_t index_j, pfx_usize_t step_size, pfx_usize_t block_count);
	PFX_INLINE static element_* get_element_at (dynamic_blockptr_collection& blockptr_collection,
		pfx_uindex_t index, pfx_usize_t step_size, pfx_usize_t block_count);
public:
	virtual dynamic_block*	new_dynamic_block () {return new dynamic_block;};
	virtual pfx_result_t			release_dynamic_block (dynamic_block* PARAM_IN block_ptr) 
	{if (block_ptr) {delete block_ptr;return PFX_STATUS_OK;}return PFX_STATUS_INVALID_PARAMS;};
public:
	void				lock_auto_step ();
	void				unlock_auto_step ();
public:
	pfx_carray_base ();
	pfx_carray_base (const pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS& other_) throw (pfx_result_t);
	virtual ~pfx_carray_base ();
public:
	pfx_result_t	init (pfx_usize_t element_count,pfx_usize_t allocate_step_size = 0,
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE);

	pfx_result_t	resize (pfx_usize_t element_size, pfx_usize_t allocate_step = 0,
		pfx_boolean_t new_buffer = PFX_BOOL_FALSE);
public:
	pfx_result_t								copy (const IPfx_array PFX_IARRAY_TEMPLATE_PARAMS * other_ptr);
	pfx_result_t								dispose ();
	PFX_BLOCK_STATUS_t				push_back (const element_& elem);
	const element_*						pop_back (PFX_BLOCK_STATUS_t& status_);

	PFX_INLINE pfx_usize_t			get_buffer_size () const;
	PFX_INLINE pfx_usize_t			size () const;
	PFX_INLINE const element_*	get_element_at (pfx_uindex_t index_) const;
	PFX_INLINE	pfx_usize_t				set_buffer (pfx_uindex_t index_, const element_* elements_ptr,
																		pfx_usize_t element_size,pfx_result_t& status_);

	pfx_result_t								clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
	PFX_INLINE pfx_boolean_t		is_full () const;
	PFX_INLINE pfx_boolean_t		is_empty () const;    
public:
	PFX_INLINE pfx_result_t			copy (const pfx_carray_base PFX_ARRAYBASE_TEMPLATE_PARAMS &other_);

};

PECKER_END

#endif			//PFX_ARRAY_H_
