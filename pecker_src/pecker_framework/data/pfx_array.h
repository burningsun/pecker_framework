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
#define PFX_CON_ARRAY consecutive_array_base  < cstring_  >
#define PFX_CON_ARRAY_TYPE typename consecutive_array_base  < cstring_  >

#define consecutive_array_element typename string_member_reference_type < cstring_ >::item_type_t

#define PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_DEFINES	template < class  consecutive_array_array >
#define PFX_INCONSECUTIVE_ARRAY_BASE_TEMPLATE_PARAMS	<consecutive_array_array >
#define PFX_INCON_ARRAY inconsecutive_array_base < consecutive_array_array  >
#define PFX_INCON_ARRAY_TYPE typename inconsecutive_array_base  < consecutive_array_array  >
	
#define inconsecutive_array_block			typename  object_reference_type< typename array_member_reference_type < consecutive_array_array >::item_type_t >::obj_type_t
#define inconsecutive_array_element	typename  array_member_reference_type< typename array_member_reference_type < consecutive_array_array >::item_type_t > ::item_type_t

#define PFX_CONSECUTIVE_ARRAY_CODE (0XFFFE0000)
#define PFX_INCONSECUTIVE_ARRAY_CODE (0XFFFE7FFF)

template < class element_ >
PFX_Interface IPfx_array;

template < class element_ >
PFX_Interface PFX_DATA_TEMPALE_API IPfx_array_iterator : public IPfx_increase_iterator < element_ >, 
											public IPfx_decrease_iterator< element_ >
{
	typedef typename	element_													element_t;
	typedef typename	element_													item_type_t;
	typedef typename	IPfx_array < item_type_t >					IArray_t;
	typedef typename	IPfx_array_iterator < element_t >		IArray_itr;
	typedef typename	IPfx_increase_iterator < element_t >	Inc_itr;
	typedef typename	IPfx_decrease_iterator< element_t >	Dec_itr;


	virtual ~IPfx_array_iterator < element_t > () {;}

	virtual result_t init (const IArray_t* attach_array_ptr, uindex_t current_index) = 0;

	virtual IArray_itr*			increase () = 0;
	virtual IArray_itr*			decrease () = 0;

	virtual Inc_itr*					increase_iterator () = 0;
	virtual Dec_itr*					decrease_iterator () = 0;
	virtual	const element_*	get_current_element () const = 0;
};


template < class element_ >
class PFX_DATA_TEMPALE_API const_array_iterator : public IPfx_array_iterator < element_ >
{

public:
	typedef typename	element_													element_t;
	typedef typename	element_													item_type_t;
	typedef typename	IPfx_array < item_type_t >					IArray_t;
	typedef typename	IPfx_array_iterator < element_t >		IArray_itr;
	typedef typename	IPfx_increase_iterator < element_t >	Inc_itr;
	typedef typename	IPfx_decrease_iterator< element_t >	Dec_itr;
private:
	const IArray_t*	m_attach_array_ptr;
	uindex_t			m_index;
public:
	const_array_iterator ();
	virtual ~const_array_iterator ();

	virtual result_t init (const IArray_t* attach_array_ptr, uindex_t current_index);

	virtual IArray_itr*			increase ();
	virtual IArray_itr*			decrease ();

	virtual Inc_itr*					increase_iterator ();
	virtual Dec_itr*					decrease_iterator ();
	virtual	const element_*	get_current_element () const;
};

template < class element_ >
class PFX_DATA_TEMPALE_API array_iterator : public IPfx_array_iterator < element_ >
{
public:
	typedef typename	element_													element_t;
	typedef typename	element_													item_type_t;
	typedef typename	IPfx_array < item_type_t >					IArray_t;
	typedef typename	IPfx_array_iterator < element_t >		IArray_itr;
	typedef typename	IPfx_increase_iterator < element_t >	Inc_itr;
	typedef typename	IPfx_decrease_iterator< element_t >	Dec_itr;
private:
	IArray_t*	m_attach_array_ptr;
	uindex_t	m_index;
public:
	array_iterator ();
	virtual ~array_iterator ();

	virtual result_t init (const IArray_t* attach_array_ptr, uindex_t current_index);

	virtual IArray_itr*			increase ();
	virtual IArray_itr*			decrease ();

	virtual Inc_itr*					increase_iterator ();
	virtual Dec_itr*					decrease_iterator ();

	virtual	const element_*	get_current_element () const;
	virtual element_*			get_current_element_reference ();
};

template < class element_ >
PFX_Interface PFX_DATA_TEMPALE_API IPfx_array
{
	typedef typename	element_															element_t;
	typedef typename	element_															item_type_t;
	typedef typename	IPfx_array < item_type_t >							IArray_t;
	typedef typename	const_array_iterator < item_type_t >			const_array_itr_t;
	typedef typename	array_iterator < item_type_t >						array_itr_t;

	virtual ~IPfx_array () {;};


	virtual result_t						init (usize__t element_count, usize__t allocate_step_size = 0, 
																		boolean_t release_buffer = PFX_BOOL_FALSE) = 0;

	virtual result_t						resize (usize__t element_size, boolean_t release_buffer = PFX_BOOL_FALSE) = 0;
	virtual result_t						set_max_elements_count (usize__t max_count = 0) = 0;
	virtual result_t						set_auto_step (usize__t auto_step = 0) = 0;
	virtual usize__t						get_max_elements_count () const = 0;
	virtual usize__t						get_auto_step () const = 0;

	virtual result_t						copy (const IArray_t * PARAM_IN other_ptr) = 0;

	virtual result_t						push_back (const element_t& elem) = 0;
	virtual result_t						pop_back () = 0;

	virtual usize__t						get_buffer_size () const = 0;
	virtual	usize__t						size () const = 0;

	virtual const element_t*	get_element_at (uindex_t index_) const = 0;
	virtual element_t*				get_element_reference_at (uindex_t index_) = 0;
	virtual usize__t						set_element_buffers_at (uindex_t index_, const element_t* PARAM_IN elements_ptr,
																				usize__t element_size) = 0;

	virtual	result_t						clear (boolean_t release_buffer = PFX_BOOL_FALSE) = 0;

	virtual	boolean_t					is_full () const = 0;
	virtual boolean_t					is_empty () const = 0;

	virtual ulong_t						get_array_type_code () const = 0;	

protected:
	virtual const element_t*	get_buffer () const = 0;
	
public:
	virtual const_array_itr_t*	begin (const_array_itr_t* PARAM_INOUT iterator_ptr) const = 0;
	virtual const_array_itr_t*	end (const_array_itr_t* PARAM_INOUT iterator_ptr) const = 0;

	virtual array_itr_t*				begin (array_itr_t* PARAM_INOUT iterator_ptr) = 0;
	virtual array_itr_t*				end (array_itr_t* PARAM_INOUT iterator_ptr) = 0;


};

template < class  cstring_ >
class PFX_DATA_TEMPALE_API consecutive_array_base : public cstring_,
	public IPfx_array < consecutive_array_element >
{
public:
	typedef consecutive_array_element												item_type_t;
	typedef typename	IPfx_array < item_type_t >							IArray_t;
	typedef typename	consecutive_array_base < cstring_ >			conarray_t;
	typedef typename	cstring_																cstring_t;
	typedef typename	const_array_iterator < item_type_t >			const_array_itr_t;
	typedef typename	array_iterator < item_type_t >						array_itr_t;
private:
	usize__t		m_auto_size_step;
	usize__t		m_max_elements_count;
protected:
	PFX_INLINE		usize__t			get_new_buffer_size (usize__t new_size, usize__t auto_size_step, usize__t max_size); 
public:
	consecutive_array_base ();
	consecutive_array_base (const conarray_t &other_) throw (result_t);
	virtual ~consecutive_array_base();
public:
	PFX_INLINE result_t							init (usize__t element_count, usize__t allocate_step_size = 0, 
																				boolean_t release_buffer = PFX_BOOL_FALSE);
	
	PFX_INLINE result_t							resize (usize__t element_size, boolean_t release_buffer = PFX_BOOL_FALSE);
	PFX_INLINE result_t							set_max_elements_count (usize__t max_count = 0);
	PFX_INLINE result_t							set_auto_step (usize__t auto_step = 0);
	PFX_INLINE usize__t						get_max_elements_count () const;
	PFX_INLINE usize__t						get_auto_step () const;
	
	PFX_INLINE result_t							copy (const IArray_t * PARAM_IN other_ptr);
	PFX_INLINE result_t							copy (conarray_t * PARAM_INOUT other_ptr);

	PFX_INLINE result_t							push_back (const item_type_t& elem);
	PFX_INLINE result_t							pop_back ();
	
	PFX_INLINE usize__t						get_buffer_size () const;
	PFX_INLINE usize__t						size () const;
	
	PFX_INLINE const item_type_t*	get_element_at (uindex_t index_) const;
	PFX_INLINE item_type_t*				get_element_reference_at (uindex_t index_);

	PFX_INLINE usize__t						set_element_buffers_at (uindex_t index_, const item_type_t* PARAM_IN elements_ptr, usize__t element_size);
	
	PFX_INLINE result_t							clear (boolean_t release_buffer = PFX_BOOL_FALSE);
	
	PFX_INLINE boolean_t					is_full () const;
	PFX_INLINE boolean_t					is_empty () const;

	PFX_INLINE ulong_t							get_array_type_code () const;	
	PFX_INLINE const item_type_t*	get_buffer () const;

static	PFX_INLINE usize__t				cache_buffer_size ();

public:
	const_array_itr_t*							begin (const_array_itr_t* PARAM_INOUT iterator_ptr) const;
	const_array_itr_t*							end (const_array_itr_t* PARAM_INOUT iterator_ptr) const;

	array_itr_t*										begin (array_itr_t* PARAM_INOUT iterator_ptr);
	array_itr_t*										end (array_itr_t* PARAM_INOUT iterator_ptr);

};

template < class  consecutive_array_array >
class PFX_DATA_TEMPALE_API inconsecutive_array_base : public IPfx_array < inconsecutive_array_element >
{
public:
	typedef inconsecutive_array_element																	item_type_t;
	typedef inconsecutive_array_block																			block_t;
	typedef typename	IPfx_array < item_type_t >													IArray_t;
	typedef typename	consecutive_array_array														conarr_array_t;
	typedef typename	const_array_iterator < item_type_t >									const_array_itr_t;
	typedef typename	array_iterator < item_type_t >												array_itr_t;
	typedef typename	inconsecutive_array_base< consecutive_array_array > inarray_t;
private:
	consecutive_array_array m_array_array;
	usize__t		m_elements_count;
	usize__t		m_auto_size_step;
	usize__t		m_max_elements_count;
public:
	inconsecutive_array_base ();
	inconsecutive_array_base (const inarray_t&other_) throw (result_t);
	virtual ~inconsecutive_array_base();	
private:
	PFX_INLINE item_type_t*				get_element_reference_at (uindex_t index_, usize__t step_size);
public:
	virtual	PFX_INLINE usize__t			get_step_cache_size () const;									
	PFX_INLINE usize__t						get_current_auto_step () const;
protected:
	virtual PFX_INLINE block_t*			new_array_block ();
	virtual PFX_INLINE result_t			delete_array_block (block_t* PARAM_INOUT array_ptr);
public:
	PFX_INLINE result_t							init_remian_element (usize__t element_count, usize__t allocate_step_size = 0, 
																				boolean_t release_buffer = PFX_BOOL_FALSE);
public:
	PFX_INLINE result_t							init (usize__t element_count, usize__t allocate_step_size = 0, 
																			boolean_t release_buffer = PFX_BOOL_FALSE);
	


	PFX_INLINE result_t							resize (usize__t element_size, boolean_t release_buffer = PFX_BOOL_FALSE);
	PFX_INLINE result_t							set_max_elements_count (usize__t max_count = 0);
	PFX_INLINE result_t							set_auto_step (usize__t auto_step = 0);
	PFX_INLINE usize__t						get_max_elements_count () const;
	PFX_INLINE usize__t						get_auto_step () const;

	PFX_INLINE result_t							copy (const IArray_t * PARAM_IN other_ptr);
	PFX_INLINE result_t							copy (inarray_t* PARAM_INOUT other_ptr);

	PFX_INLINE result_t							push_back (const item_type_t& elem);
	PFX_INLINE result_t							pop_back ();

	PFX_INLINE usize__t						get_buffer_size () const;
	PFX_INLINE usize__t						size () const;

	PFX_INLINE const item_type_t*	get_element_at (uindex_t index_) const;
	PFX_INLINE item_type_t*				get_element_reference_at (uindex_t index_);

	PFX_INLINE usize__t						set_element_buffers_at (uindex_t index_, const item_type_t* PARAM_IN elements_ptr, usize__t element_size);

	PFX_INLINE result_t							clear (boolean_t release_buffer = PFX_BOOL_FALSE);

	PFX_INLINE boolean_t					is_full () const;
	PFX_INLINE boolean_t					is_empty () const;

	PFX_INLINE ulong_t							get_array_type_code () const;	

protected:
	virtual const item_type_t*				get_buffer () const {return null;};

public:
	static	PFX_INLINE usize__t			cache_buffer_size ();
	static	PFX_INLINE usize__t			step_buffer_size ();

public:
	const_array_itr_t*							begin (const_array_itr_t* PARAM_INOUT iterator_ptr) const;
	const_array_itr_t*							end (const_array_itr_t* PARAM_INOUT iterator_ptr) const;

	array_itr_t*										begin (array_itr_t* PARAM_INOUT iterator_ptr);
	array_itr_t*										end (array_itr_t* PARAM_INOUT iterator_ptr);

};


template < class element_, 
	class elem_compare = pecker_value_compare < element_ >, 
	const unsigned int CACHE_BUFFER_SIZE = PFX_DEFUALT_ARRAY_SIZE >
struct PFX_DATA_TEMPALE_API consecutive_array_type
{
	typedef  consecutive_array_base < cstring < element_, elem_compare, CACHE_BUFFER_SIZE > >				consecutive_array_t;
	typedef  consecutive_array_base < cshare_string < element_, elem_compare, CACHE_BUFFER_SIZE > >	consecutive_share_array_t;
};

template < class _consecutive_array_t, 
	const unsigned int CACHE_BUFFER_SIZE = PFX_DEFUALT_ARRAY_SIZE >
struct PFX_DATA_TEMPALE_API consecutive_array_array_type
{
	typedef typename consecutive_array_type<_consecutive_array_t*, 
		pecker_value_compare_extern < _consecutive_array_t >,
		CACHE_BUFFER_SIZE >::consecutive_array_t															consecutive_array_array_t;
};


template < class element_,  
	class elem_compare = pecker_value_compare < element_ >,
	const unsigned int FIRST_CACHE_BUFFER_SIZE		= PFX_DEFUALT_ARRAY_SIZE,
	const unsigned int SECOND_CACHE_BUFFER_SIZE	= PFX_DEFUALT_ARRAY_SIZE >
struct PFX_DATA_TEMPALE_API array_type
{
	typedef typename consecutive_array_type< element_,  
		elem_compare, 
		FIRST_CACHE_BUFFER_SIZE >::consecutive_array_t														consecutive_array_t;
	typedef typename consecutive_array_type< element_, 
		elem_compare, 
		FIRST_CACHE_BUFFER_SIZE >::consecutive_share_array_t											consecutive_share_array_t;

	typedef typename consecutive_array_type< element_, 
		elem_compare, 
		SECOND_CACHE_BUFFER_SIZE >::consecutive_array_t													_consecutive_array_t;

	typedef typename consecutive_array_type< element_, 
		elem_compare, 
		SECOND_CACHE_BUFFER_SIZE>::consecutive_share_array_t										_consecutive_share_array_t;

	typedef typename consecutive_array_array_type< _consecutive_array_t,  
		FIRST_CACHE_BUFFER_SIZE >::consecutive_array_array_t											consecutive_array_array_t;

	typedef typename consecutive_array_array_type< _consecutive_share_array_t, 
		FIRST_CACHE_BUFFER_SIZE >::consecutive_array_array_t											consecutive_share_array_array_t;


	typedef inconsecutive_array_base< consecutive_array_array_t >									inconsecutive_array_t;

	typedef inconsecutive_array_base < consecutive_share_array_array_t >						inconsecutive_share_array_t;
};

PECKER_END

#endif			//PFX_ARRAY_H_
