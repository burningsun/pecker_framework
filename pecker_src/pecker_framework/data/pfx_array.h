/*
 * pfx_array.h
 *
 *  Created on: 2014-2-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_ARRAY_H_
#define		PFX_ARRAY_H_

#include "pfx_cstring_codes.h"
#include "pfx_iterator.h"
#include "pfx_data_traits.h"

PECKER_BEGIN

#define PFX_DEFUALT_ARRAY_AUTO_STEP	DEFUALT_CACHE_BUFFER_SIZE
#define PFX_DEFUALT_ARRAY_SIZE					DEFUALT_CACHE_BUFFER_SIZE

#define PFX_IARRAY_TEMPLATE_DEFINES template < class element_ >
#define PFX_IARRAY_TEMPLATE_PARAMS  < element_ >

#define PFX_IARRAY_ITERATOR_TEMPLATE_DEFINES template < class element_ >
#define PFX_IARRAY_ITERATOR_TEMPLATE_PARAMS  < element_ >

#define PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES template < class cstring_ >
#define PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS   < cstring_  >
#define consecutive_array_element typename string_member_reference_type < cstring_ >::item_type_t

#define PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES	template < class  consecutive_array, class  consecutive_array_array >
#define PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS	< consecutive_array, consecutive_array_array >
#define inconsecutive_array_element typename array_member_reference_type < consecutive_array >::item_type_t

#define PFX_CONSECUTIVE_ARRAY_CODE (0XFFFE0000)
#define PFX_INCONSECUTIVE_ARRAY_CODE (0XFFFE7FFF)

template < class element_ >
PFX_Interface IPfx_array;

template < class element_ >
PFX_Interface IPfx_array_iterator : public pfx_increase_iterator < element_ >, 
											public pfx_decrease_iterator < element_ >
{
	virtual ~IPfx_array_iterator < element_ > () {;}

	virtual pfx_result_t init (const IPfx_array < element_ >* attach_array_ptr, pfx_uindex_t current_index) = 0;

	virtual IPfx_array_iterator < element_ >*		increase () = 0;
	virtual IPfx_array_iterator < element_ >*		decrease () = 0;

	virtual pfx_increase_iterator < element_ >*	increase_iterator () = 0;
	virtual pfx_decrease_iterator < element_ >*	decrease_iterator () = 0;
	virtual	const element_*									get_current_element () const = 0;
};


template < class element_ >
class pfx_const_array_iterator : public IPfx_array_iterator < element_ >
{
private:
	const IPfx_array < element_ >*	m_attach_array_ptr;
	pfx_uindex_t									m_index;
public:
	pfx_const_array_iterator ();
	virtual ~pfx_const_array_iterator ();

	virtual pfx_result_t init (const IPfx_array < element_ >* attach_array_ptr, pfx_uindex_t current_index);

	virtual IPfx_array_iterator < element_ >*		increase ();
	virtual IPfx_array_iterator < element_ >*		decrease ();

	virtual pfx_increase_iterator < element_ >*	increase_iterator ();
	virtual pfx_decrease_iterator < element_ >*	decrease_iterator ();
	virtual	const element_*									get_current_element () const;
};

template < class element_ >
class pfx_array_iterator : public IPfx_array_iterator < element_ >
{
private:
	IPfx_array < element_ >*	m_attach_array_ptr;
	pfx_uindex_t						m_index;
public:
	pfx_array_iterator ();
	virtual ~pfx_array_iterator ();

	virtual pfx_result_t init (const IPfx_array < element_ >* attach_array_ptr, pfx_uindex_t current_index);

	virtual IPfx_array_iterator < element_ >*		increase ();
	virtual IPfx_array_iterator < element_ >*		decrease ();

	virtual pfx_increase_iterator < element_ >* increase_iterator ();
	virtual pfx_decrease_iterator < element_ >* decrease_iterator ();

	virtual	const element_*									get_current_element () const;
	virtual element_*												get_current_element_reference ();
};

template < class element_ >
PFX_Interface IPfx_array
{

	virtual ~IPfx_array () {;};


	virtual pfx_result_t						init (pfx_usize_t element_count, pfx_usize_t allocate_step_size = 0, 
																		pfx_boolean_t release_buffer = PFX_BOOL_FALSE) = 0;

	virtual pfx_result_t						resize (pfx_usize_t element_size, pfx_boolean_t release_buffer = PFX_BOOL_FALSE) = 0;
	virtual pfx_result_t						set_max_elements_count (pfx_usize_t max_count = 0) = 0;
	virtual pfx_result_t						set_auto_step (pfx_usize_t auto_step = 0) = 0;
	virtual pfx_usize_t							get_max_elements_count () const = 0;
	virtual pfx_usize_t							get_auto_step () const = 0;

	virtual pfx_result_t						copy (const IPfx_array PFX_IARRAY_TEMPLATE_PARAMS * PARAM_IN other_ptr) = 0;

	virtual pfx_result_t						push_back (const element_& elem) = 0;
	virtual pfx_result_t						pop_back () = 0;

	virtual pfx_usize_t							get_buffer_size () const = 0;
	virtual	pfx_usize_t							size () const = 0;

	virtual const element_*				get_element_at (pfx_uindex_t index_) const = 0;
	virtual element_*							get_element_reference_at (pfx_uindex_t index_) = 0;
	virtual pfx_usize_t							set_element_buffers_at (pfx_uindex_t index_, const element_* PARAM_IN elements_ptr,
																					pfx_usize_t element_size) = 0;

	virtual	pfx_result_t						clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE) = 0;

	virtual	pfx_boolean_t					is_full () const = 0;
	virtual pfx_boolean_t					is_empty () const = 0;

	virtual pfx_ulong_t						get_array_type_code () const = 0;	

protected:
	virtual const element_*				get_buffer () const = 0;
	
public:
	virtual pfx_const_array_iterator < element_ >*	begin (pfx_const_array_iterator < element_ >* PARAM_INOUT iterator_ptr) const = 0;
	virtual pfx_const_array_iterator < element_ >*	end (pfx_const_array_iterator < element_ >* PARAM_INOUT iterator_ptr) const = 0;

	virtual pfx_array_iterator < element_ >*				begin (pfx_array_iterator < element_ >* PARAM_INOUT iterator_ptr) = 0;
	virtual pfx_array_iterator < element_ >*				end (pfx_array_iterator < element_ >* PARAM_INOUT iterator_ptr) = 0;


};

template < class  cstring_ >
class pfx_consecutive_array_base : public cstring_,
	public IPfx_array < consecutive_array_element >
{
public:
	typedef consecutive_array_element item_type_t;
private:
	pfx_usize_t		m_auto_size_step;
	pfx_usize_t		m_max_elements_count;
protected:
	PFX_INLINE		pfx_usize_t			get_new_buffer_size (pfx_usize_t new_size, pfx_usize_t auto_size_step, pfx_usize_t max_size); 
public:
	pfx_consecutive_array_base ();
	pfx_consecutive_array_base (const pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS &other_) throw (pfx_result_t);
	virtual ~pfx_consecutive_array_base();
public:
	PFX_INLINE pfx_result_t			init (pfx_usize_t element_count, pfx_usize_t allocate_step_size = 0, 
																pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
	
	PFX_INLINE pfx_result_t			resize (pfx_usize_t element_size, pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
	PFX_INLINE pfx_result_t			set_max_elements_count (pfx_usize_t max_count = 0);
	PFX_INLINE pfx_result_t			set_auto_step (pfx_usize_t auto_step = 0);
	PFX_INLINE pfx_usize_t			get_max_elements_count () const;
	PFX_INLINE pfx_usize_t			get_auto_step () const;
	
	PFX_INLINE pfx_result_t			copy (const IPfx_array < consecutive_array_element > * PARAM_IN other_ptr);
	PFX_INLINE pfx_result_t			copy (pfx_consecutive_array_base PFX_CONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS * PARAM_INOUT other_ptr);

	PFX_INLINE pfx_result_t			push_back (const consecutive_array_element& elem);
	PFX_INLINE pfx_result_t			pop_back ();
	
	PFX_INLINE pfx_usize_t			get_buffer_size () const;
	PFX_INLINE pfx_usize_t			size () const;
	
	PFX_INLINE const consecutive_array_element*	get_element_at (pfx_uindex_t index_) const;
	PFX_INLINE consecutive_array_element*				get_element_reference_at (pfx_uindex_t index_);

	PFX_INLINE pfx_usize_t			set_element_buffers_at (pfx_uindex_t index_, const consecutive_array_element* PARAM_IN elements_ptr, pfx_usize_t element_size);
	
	PFX_INLINE pfx_result_t			clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
	
	PFX_INLINE pfx_boolean_t		is_full () const;
	PFX_INLINE pfx_boolean_t		is_empty () const;

	PFX_INLINE pfx_ulong_t			get_array_type_code () const;	
	PFX_INLINE const consecutive_array_element*	get_buffer () const;

static	PFX_INLINE pfx_usize_t	cache_buffer_size ();

public:
	pfx_const_array_iterator < consecutive_array_element >*	begin (pfx_const_array_iterator < consecutive_array_element >* PARAM_INOUT iterator_ptr) const;
	pfx_const_array_iterator < consecutive_array_element >*	end (pfx_const_array_iterator < consecutive_array_element >* PARAM_INOUT iterator_ptr) const;

	pfx_array_iterator < consecutive_array_element >*			begin (pfx_array_iterator < consecutive_array_element >* PARAM_INOUT iterator_ptr);
	pfx_array_iterator < consecutive_array_element >*			end (pfx_array_iterator < consecutive_array_element >* PARAM_INOUT iterator_ptr);

};

template < class  consecutive_array, class  consecutive_array_array >
class pfx_inconsecutive_array_base : public IPfx_array < inconsecutive_array_element >
{
public:
	typedef inconsecutive_array_element item_type_t;
private:
	consecutive_array_array m_array_array;
	pfx_usize_t		m_elements_count;
	pfx_usize_t		m_auto_size_step;
	pfx_usize_t		m_max_elements_count;
public:
	pfx_inconsecutive_array_base ();
	pfx_inconsecutive_array_base (const pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS &other_) throw (pfx_result_t);
	virtual ~pfx_inconsecutive_array_base();	
private:
	PFX_INLINE inconsecutive_array_element*	get_element_reference_at (pfx_uindex_t index_, pfx_usize_t step_size);
public:
	virtual	PFX_INLINE pfx_usize_t				get_step_cache_size () const;									
	PFX_INLINE pfx_usize_t							get_current_auto_step () const;
protected:
	virtual PFX_INLINE consecutive_array* new_array_block ();
	virtual PFX_INLINE pfx_result_t				delete_array_block (consecutive_array* PARAM_INOUT array_ptr);
public:
	PFX_INLINE pfx_result_t			init_remian_element (pfx_usize_t element_count, pfx_usize_t allocate_step_size = 0, 
		pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
public:
	PFX_INLINE pfx_result_t			init (pfx_usize_t element_count, pfx_usize_t allocate_step_size = 0, 
		pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
	


	PFX_INLINE pfx_result_t			resize (pfx_usize_t element_size, pfx_boolean_t release_buffer = PFX_BOOL_FALSE);
	PFX_INLINE pfx_result_t			set_max_elements_count (pfx_usize_t max_count = 0);
	PFX_INLINE pfx_result_t			set_auto_step (pfx_usize_t auto_step = 0);
	PFX_INLINE pfx_usize_t			get_max_elements_count () const;
	PFX_INLINE pfx_usize_t			get_auto_step () const;

	PFX_INLINE pfx_result_t			copy (const IPfx_array < inconsecutive_array_element > * PARAM_IN other_ptr);
	PFX_INLINE pfx_result_t			copy (pfx_inconsecutive_array_base PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS * PARAM_INOUT other_ptr);

	PFX_INLINE pfx_result_t			push_back (const inconsecutive_array_element& elem);
	PFX_INLINE pfx_result_t			pop_back ();

	PFX_INLINE pfx_usize_t			get_buffer_size () const;
	PFX_INLINE pfx_usize_t			size () const;

	PFX_INLINE const inconsecutive_array_element*	get_element_at (pfx_uindex_t index_) const;
	PFX_INLINE inconsecutive_array_element*				get_element_reference_at (pfx_uindex_t index_);

	PFX_INLINE pfx_usize_t			set_element_buffers_at (pfx_uindex_t index_, const inconsecutive_array_element* PARAM_IN elements_ptr, pfx_usize_t element_size);

	PFX_INLINE pfx_result_t			clear (pfx_boolean_t release_buffer = PFX_BOOL_FALSE);

	PFX_INLINE pfx_boolean_t		is_full () const;
	PFX_INLINE pfx_boolean_t		is_empty () const;

	PFX_INLINE pfx_ulong_t			get_array_type_code () const;	

protected:
	virtual const inconsecutive_array_element*					get_buffer () const {return null;};

public:
	static	PFX_INLINE pfx_usize_t		cache_buffer_size ();
	static	PFX_INLINE pfx_usize_t		step_buffer_size ();

public:
	pfx_const_array_iterator < inconsecutive_array_element >*	begin (pfx_const_array_iterator < inconsecutive_array_element >* PARAM_INOUT iterator_ptr) const;
	pfx_const_array_iterator < inconsecutive_array_element >*	end (pfx_const_array_iterator < inconsecutive_array_element >* PARAM_INOUT iterator_ptr) const;

	pfx_array_iterator < inconsecutive_array_element >*				begin (pfx_array_iterator < inconsecutive_array_element >* PARAM_INOUT iterator_ptr);
	pfx_array_iterator < inconsecutive_array_element >*				end (pfx_array_iterator < inconsecutive_array_element >* PARAM_INOUT iterator_ptr);

};


template < class element_, 
	class elem_compare = pecker_value_compare < element_ >, 
	const unsigned int CACHE_BUFFER_SIZE = PFX_DEFUALT_ARRAY_SIZE >
struct consecutive_array_type
{
	typedef  pfx_consecutive_array_base < pfx_cstring < element_, elem_compare, CACHE_BUFFER_SIZE > >				consecutive_array_t;
	typedef  pfx_consecutive_array_base < pfx_cshare_string < element_, elem_compare, CACHE_BUFFER_SIZE > > consecutive_share_array_t;
};

template < class _consecutive_array_t, 
	const unsigned int CACHE_BUFFER_SIZE = PFX_DEFUALT_ARRAY_SIZE >
struct consecutive_array_array_type
{
	typedef typename consecutive_array_type<_consecutive_array_t*, 
		pecker_value_compare_extern < _consecutive_array_t >,
		CACHE_BUFFER_SIZE >::consecutive_array_t															consecutive_array_array_t;
};


template < class element_,  
	class elem_compare = pecker_value_compare < element_ >,
	const unsigned int FIRST_CACHE_BUFFER_SIZE		= PFX_DEFUALT_ARRAY_SIZE,
	const unsigned int SECOND_CACHE_BUFFER_SIZE	= PFX_DEFUALT_ARRAY_SIZE >
struct array_type
{
	typedef typename consecutive_array_type< element_,  
		elem_compare, 
		FIRST_CACHE_BUFFER_SIZE >::consecutive_array_t														consecutive_array_t;
	typedef typename consecutive_array_type< element_, 
		elem_compare, 
		FIRST_CACHE_BUFFER_SIZE >::consecutive_share_array_t											consecutive_share_array_t;

	typedef typename consecutive_array_type< element_, 
		elem_compare, 
		SECOND_CACHE_BUFFER_SIZE >::consecutive_array_t												_consecutive_array_t;

	typedef typename consecutive_array_type< element_, 
		elem_compare, 
		SECOND_CACHE_BUFFER_SIZE>::consecutive_share_array_t										_consecutive_share_array_t;

	typedef typename consecutive_array_array_type< _consecutive_array_t,  
		FIRST_CACHE_BUFFER_SIZE >::consecutive_array_array_t											consecutive_array_array_t;

	typedef typename consecutive_array_array_type< _consecutive_share_array_t, 
		FIRST_CACHE_BUFFER_SIZE >::consecutive_array_array_t											consecutive_share_array_array_t;


	typedef pfx_inconsecutive_array_base< _consecutive_array_t, 
		consecutive_array_array_t >																							inconsecutive_array_t;

	typedef pfx_inconsecutive_array_base < _consecutive_share_array_t, 
		consecutive_share_array_array_t >																				inconsecutive_share_array_t;
};

PECKER_END

#endif			//PFX_ARRAY_H_
