/*
 *  pecker_array.h
 *
 *  Created on: 2012-11-1
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_ARRAY_H_
#define PECKER_ARRAY_H_

#include "../native/pecker_allocator.h"
#include "pecker_array_algorithm.h"
#include "pecker_array_iterator.h"
PECKER_BEGIN

template< class class_type,class allocate_object_t = pecker_simple_allocator< class_type > >
class pecker_array
{
	typedef pecker_array_iterator< pecker_array< class_type,allocate_object_t > > _Array_iterator;
	typedef pecker_array< class_type,allocate_object_t > _Array_container;
private:
	class_type* _M_parray_buffer;
	array_buffer_size_val _M_array_size;
	array_buffer_size_val _M_array_buffer_size;
	array_buffer_size_val _M_auto_allocate_step;
public:
	explicit pecker_array(array_buffer_size_val auto_allocate_size = ARRAY_DEFAULT_ALLOCATE_STEP):_M_parray_buffer(null),
		_M_array_buffer_size(0),
		_M_array_size(0),
		_M_auto_allocate_step(auto_allocate_size)
	{
		if (_M_auto_allocate_step <= 0)
		{
			_M_auto_allocate_step = ARRAY_DEFAULT_ALLOCATE_STEP;
		}
	}
	pecker_array(const _Array_container& other_array)
	{
		_M_parray_buffer = null;
		_M_array_buffer_size = 0,
		_M_array_size = 0,
		_M_auto_allocate_step = ARRAY_DEFAULT_ALLOCATE_STEP;
		copy(other_array);
	}
	pecker_array& operator = (const _Array_container& other_array)
	{
		copy(other_array);
		return *this;
	}

	virtual ~pecker_array()
	{
		clear(ARRAY_BOOLEAN_TRUE);
	}
public:
	inline array_result swap(_Array_container& other_array)
	{
		if (&other_array != this)
		{
			array_buffer_size_val temp_size;
			class_type* temp_type_pointer = _M_parray_buffer;
			_M_parray_buffer = other_array._M_parray_buffer;
			other_array._M_parray_buffer = temp_type_pointer;

			temp_size = _M_array_size;
			_M_array_size = other_array._M_array_size;
			other_array._M_array_size = temp_size;

			temp_size = _M_array_buffer_size;
			_M_array_buffer_size = other_array._M_array_buffer_size;
			other_array._M_array_buffer_size = temp_size;

			temp_size = _M_auto_allocate_step;
			_M_auto_allocate_step = other_array._M_auto_allocate_step;
			other_array._M_auto_allocate_step = temp_size;
		}
		return P_OK;
	}
	inline array_result swap_value(const _Array_iterator* piterator1,const _Array_iterator* piterator2)
	{
		class_type* pitem_low = get_reference_at(piterator1);
		class_type* pitem_hight = get_reference_at(piterator2);
		if ( null != pitem_hight && 
				null != pitem_low)
		{
			class_type ptemp_item = *pitem_hight;
			*pitem_hight = *pitem_low;
			*pitem_low = ptemp_item;
			return P_OK;
		}
		else
		{
			return P_ERR;
		}
	}
	inline array_result swap_value(array_index_val index1,array_index_val index2)
	{
		class_type* pitem_low = get_reference_at(index1);
		class_type* pitem_hight = get_reference_at(index2);
		if ( null != pitem_hight && 
			null != pitem_low)
		{
			class_type ptemp_item = *pitem_hight;
			*pitem_hight = *pitem_low;
			*pitem_low = ptemp_item;
			return P_OK;
		}
		else
		{
			return P_ERR;
		}
	}

	array_result init(array_buffer_size_val init_size = 1, array_buffer_size_val auto_allocate_size = -1)
	{
		if (init_size <= 0)
		{
			init_size = 1;
		}
		array_result resize_result = resize(init_size,auto_allocate_size);
		if (P_OK == resize_result)
		{
			_M_array_size = 0;
		}
		return resize_result;
	}
	array_result copy(const _Array_container& other_array)
	{
		if (&other_array != this)
		{
			array_result resize_result = 
				resize_array< class_type, allocate_object_t >(_M_parray_buffer,_M_array_size,
				&_M_array_buffer_size,
				other_array._M_array_size,
				other_array._M_auto_allocate_step,
				ARRAY_BOOLEAN_FLASE,
				ARRAY_BOOLEAN_TRUE);
			if (P_OK == resize_result)
			{
				_M_array_size = other_array._M_array_size;
				_M_auto_allocate_step = other_array._M_auto_allocate_step;

				for (array_index_val index =0;index < _M_array_size; ++index)
				{
					_M_parray_buffer[index] = other_array._M_parray_buffer[index];
				}
			}
			return resize_result;
		}
		return P_OK;
	}

	inline const class_type* get_at(array_index_val index) const
	{
		if (index >=0 && index < _M_array_size)
		{
			return &_M_parray_buffer[index];
		}
		else
		{
			return null;
		}
	}
	inline class_type* get_reference_at(array_index_val index) const
	{
		if (index >=0 && index < _M_array_size)
		{
			return &_M_parray_buffer[index];
		}
		else
		{
			return null;
		}
	}
	inline array_result set_at(array_index_val index,const class_type& set_item)
	{
		if (index >=0 && index < _M_array_size)
		{
			_M_parray_buffer[index] = set_item;
			return P_OK;
		}
		else
		{
			return P_ERR;
		}
	}
	
	array_result resize(array_buffer_size_val resize_size, 
		array_buffer_size_val auto_allocate_size = -1,
		array_boolean_flag bForce_release = ARRAY_BOOLEAN_FLASE)
	{
		if (auto_allocate_size <= 0)
		{
			auto_allocate_size = _M_auto_allocate_step;
		}
		array_result resize_result = resize_array< class_type, allocate_object_t >(_M_parray_buffer,_M_array_size,
			_M_array_buffer_size,
			resize_size,
			auto_allocate_size,
			bForce_release,
			ARRAY_BOOLEAN_FLASE);

		if (P_OK == resize_result)
		{
			_M_array_size = resize_size;
			_M_auto_allocate_step = auto_allocate_size;
		}

		return resize_result;
	}
	array_result clear(array_boolean_flag bForce_release = ARRAY_BOOLEAN_FLASE)
	{
		return resize(0,-1,bForce_release);
	}

	inline array_result push_new_value()
	{
		array_result resize_result = resize(_M_array_size+1);
		return resize_result;
	}
	inline array_result push(const class_type& set_item)
	{
		array_result resize_result = resize(_M_array_size+1);
		if (P_OK == resize_result)
		{
			_M_parray_buffer[_M_array_size-1] = set_item;
		}
		return resize_result;
	}
	inline array_result pop()
	{
		if (_M_array_size > 0)
		{
			return resize(_M_array_size-1);
		}
		else
		{
			return P_SUCCESS;
		}
	}

	inline const class_type* begin() const
	{
		return get_at(0);
	}
	inline const class_type* end() const
	{
		return get_at(_M_array_size-1);
	}

	inline class_type* get_begin_reference() const
	{
		return get_reference_at(0);
	}
	inline class_type* get_end_reference() const
	{
		return get_reference_at(_M_array_size-1);
	}


	inline array_buffer_size_val get_size() const
	{
		return _M_array_size;
	}

	inline _Array_iterator* get_iterator(_Array_iterator* parray_iterator) const
	{
		if (null != parray_iterator)
		{
			if (P_OK == parray_iterator->reinit(this))
			{
				return parray_iterator;
			}
		}
		return null;
	}
	inline class_type* get_reference_at(const _Array_iterator* parray_iterator) const
	{
		if (null != parray_iterator)
		{
			return get_reference_at(parray_iterator->get_current_index());
		}

		return null;
	}
	inline const class_type* get_at(const _Array_iterator* parray_iterator) const
	{
		if (null != parray_iterator)
		{
			return get_at(parray_iterator->get_current_index());
		}

		return null;
	}
};

template<class class_type,
class allocate_object_t = pecker_simple_allocator< class_type >,
class pointer_allocate_object_t = pecker_simple_allocator< class_type* > >
class pecker_pool_array
{
	typedef pecker_array_iterator< pecker_pool_array< class_type,allocate_object_t > > _Array_iterator;
	typedef pecker_pool_array< class_type,allocate_object_t > _Array_container;
private:
	class_type** _M_ppArray_buffer_array;
	array_buffer_size_val _M_pool_size;
	array_buffer_size_val _M_auto_allocate_step;
	array_buffer_size_val _M_array_buffer_array_size;
	array_buffer_size_val _M_array_buffer_array_buffer_size;
	array_buffer_size_val _M_array_buffer_array_allocate_step;
public:
	explicit pecker_pool_array(array_buffer_size_val auto_allocate_size = ARRAY_DEFAULT_ALLOCATE_STEP,
		                                    array_buffer_size_val array_buffer_array_allocate_step = ARRAY_DEFAULT_ALLOCATE_STEP):
	    _M_ppArray_buffer_array(null),
		_M_pool_size(0),
		_M_array_buffer_array_size(0),
		_M_array_buffer_array_buffer_size(0),
		_M_auto_allocate_step(auto_allocate_size),
		_M_array_buffer_array_allocate_step(array_buffer_array_allocate_step)

	{
		if (_M_auto_allocate_step <= 0)
		{
			_M_auto_allocate_step = ARRAY_DEFAULT_ALLOCATE_STEP;
		}

		if (_M_array_buffer_array_allocate_step <= 0)
		{
			_M_array_buffer_array_allocate_step = ARRAY_DEFAULT_ALLOCATE_STEP;
		}
	}
	pecker_pool_array(const _Array_container& other_array)
	{
		_M_ppArray_buffer_array = null;
		_M_pool_size = 0;
		_M_array_buffer_array_size = 0;
		_M_array_buffer_array_buffer_size = 0;
		_M_auto_allocate_step = ARRAY_DEFAULT_ALLOCATE_STEP;
		_M_array_buffer_array_allocate_step = ARRAY_DEFAULT_ALLOCATE_STEP;
		copy(other_array);
	}
	_Array_container& operator = (const _Array_container& other_array)
	{
		copy(other_array);
		return *this;
	}

	virtual ~pecker_pool_array()
	{
		clear(ARRAY_BOOLEAN_TRUE);
	}
public:
	inline array_result swap(_Array_container& other_array)
	{
		if (&other_array != this)
		{
			array_buffer_size_val temp_size;
			class_type** temp_type_pointer = _M_ppArray_buffer_array;
			_M_ppArray_buffer_array = other_array._M_ppArray_buffer_array;
			other_array._M_ppArray_buffer_array = temp_type_pointer;

			temp_size = _M_pool_size;
			_M_pool_size = other_array._M_pool_size;
			other_array._M_pool_size = temp_size;

			temp_size = _M_array_buffer_array_size;
			_M_array_buffer_array_size = other_array._M_array_buffer_array_size;
			other_array._M_array_buffer_array_size = temp_size;

			temp_size = _M_auto_allocate_step;
			_M_auto_allocate_step = other_array._M_auto_allocate_step;
			other_array._M_auto_allocate_step = temp_size;

			temp_size = _M_array_buffer_array_buffer_size;
			_M_array_buffer_array_buffer_size = other_array._M_array_buffer_array_buffer_size;
			other_array._M_array_buffer_array_buffer_size = temp_size;

			temp_size = _M_array_buffer_array_allocate_step;
			_M_array_buffer_array_allocate_step = other_array._M_array_buffer_array_allocate_step;
			other_array._M_array_buffer_array_allocate_step = temp_size;
		}
		return P_OK;
	}
	inline array_result swap_value(const _Array_iterator* piterator1,const _Array_iterator* piterator2)
	{
		class_type* pitem_low = get_reference_at(piterator1);
		class_type* pitem_hight = get_reference_at(piterator2);
		if ( null != pitem_hight && 
			null != pitem_low)
		{
			class_type ptemp_item = *pitem_hight;
			*pitem_hight = *pitem_low;
			*pitem_low = ptemp_item;
			return P_OK;
		}
		else
		{
			return P_ERR;
		}
	}
	inline array_result swap_value(array_index_val index1,array_index_val index2)
	{
		class_type* pitem_low = get_reference_at(index1);
		class_type* pitem_hight = get_reference_at(index2);
		if ( null != pitem_hight && 
			null != pitem_low)
		{
			class_type ptemp_item = *pitem_hight;
			*pitem_hight = *pitem_low;
			*pitem_low = ptemp_item;
			return P_OK;
		}
		else
		{
			return P_ERR;
		}
	}

	array_result init(array_buffer_size_val init_buffer_size = 1, 
		array_buffer_size_val auto_allocate_size = -1,
		array_buffer_size_val auto_allocate_buffer_array_step = -1)
	{
		if (init_buffer_size <= 0)
		{
			init_buffer_size = 1;
		}
		array_result resize_result = resize(init_buffer_size,auto_allocate_size,auto_allocate_buffer_array_step);
		if (P_OK == resize_result)
		{
			_M_pool_size = 0;
		}
		return resize_result;
	}
	array_result copy(const _Array_container& other_array)
	{
		if (&other_array != this)
		{
			array_result resize_result = resize_array_pool< class_type,pointer_allocate_object_t, allocate_object_t >
				(_M_ppArray_buffer_array,
				_M_pool_size,
				_M_auto_allocate_step,
				_M_array_buffer_array_size,
				_M_array_buffer_array_buffer_size,
				other_array._M_pool_size,
				other_array._M_auto_allocate_step,
				other_array._M_array_buffer_array_allocate_step,
				ARRAY_BOOLEAN_FLASE,
				ARRAY_BOOLEAN_TRUE);

			if (P_OK == resize_result)
			{
				_M_pool_size = other_array._M_pool_size;
				_M_auto_allocate_step = other_array._M_auto_allocate_step;
				_M_array_buffer_array_allocate_step = other_array._M_array_buffer_array_allocate_step;
			  
				array_index_val index =0;
				array_index_val row_size = _M_array_buffer_array_buffer_size -1;
				array_index_val last_column_size = _M_pool_size % _M_auto_allocate_step;
				for (;index < row_size; ++index)
				{
					for (array_index_val index_column = 0;index_column<_M_auto_allocate_step;++index_column)
					{
						_M_ppArray_buffer_array[index][index_column] = other_array._M_ppArray_buffer_array[index][index_column];
					}
				}

				for (array_index_val index_column = 0;index_column<last_column_size;++index_column)
				{
					_M_ppArray_buffer_array[index][index_column] = other_array._M_ppArray_buffer_array[index][index_column];
				}	
			}
			return resize_result;
		}
		return P_OK;
	}
	
	inline const class_type* get_at(array_index_val index) const
	{
		if (index >=0 && index < _M_pool_size)
		{
			array_index_val row_index = index / _M_auto_allocate_step;
			array_index_val column_index = index % _M_auto_allocate_step;
			return &(_M_ppArray_buffer_array[row_index][column_index]);
		}
		else
		{
			return null;
		}
	}
	inline class_type* get_reference_at(array_index_val index) const
	{
		if (index >=0 && index < _M_pool_size)
		{
			array_index_val row_index = index / _M_auto_allocate_step;
			array_index_val column_index = index % _M_auto_allocate_step;
			return &(_M_ppArray_buffer_array[row_index][column_index]);
		}
		else
		{
			return null;
		}
	}
	inline array_result set_at(array_index_val index,const class_type& set_item)
	{
		if (index >=0 && index < _M_pool_size)
		{
			array_index_val row_index = index / _M_auto_allocate_step;
			array_index_val column_index = index % _M_auto_allocate_step;
			_M_ppArray_buffer_array[row_index][column_index] = set_item;
			return P_OK;
		}
		else
		{
			return P_FAIL;
		}
	}

	array_result resize(array_buffer_size_val resize_size, 
		array_buffer_size_val auto_allocate_size = -1,
		array_buffer_size_val auto_allocate_buffer_array_step = -1,
		array_boolean_flag bForce_release = ARRAY_BOOLEAN_FLASE)
	{
		if (auto_allocate_size <= 0)
		{
			auto_allocate_size = _M_auto_allocate_step;
		}
		if (auto_allocate_buffer_array_step <=0)
		{
			auto_allocate_buffer_array_step = _M_array_buffer_array_allocate_step;
		}

		array_result resize_result = resize_array_pool< class_type,pointer_allocate_object_t, allocate_object_t >
			(_M_ppArray_buffer_array,
			_M_pool_size,
			_M_auto_allocate_step,
			_M_array_buffer_array_size,
			_M_array_buffer_array_buffer_size,
			resize_size,
			auto_allocate_size,
			auto_allocate_buffer_array_step,
			bForce_release,
			ARRAY_BOOLEAN_FLASE);

		if (P_OK == resize_result)
		{
			_M_pool_size = resize_size;
			_M_auto_allocate_step = auto_allocate_size;
			_M_array_buffer_array_allocate_step = auto_allocate_buffer_array_step;
		}

		return resize_result;
	}
	array_result clear(array_boolean_flag bForce_release = ARRAY_BOOLEAN_FLASE)
	{
		return resize(0,-1,-1,bForce_release);
	}

	inline array_result push_new_value()
	{
		array_result resize_result = resize(_M_pool_size+1);
		return resize_result;
	}

	inline array_result push(const class_type& set_item)
	{
		array_result resize_result = resize(_M_pool_size+1);
		if (P_OK == resize_result)
		{
			*get_reference_at(_M_pool_size-1) = set_item;
		}
		return resize_result;
	}
	inline array_result pop()
	{
		if (_M_pool_size > 0)
		{
			return resize(_M_pool_size-1);
		}
		else
		{
			return P_SUCCESS;
		}
	}

	inline const class_type* begin() const
	{
		return get_at(0);
	}
	inline const class_type* end() const
	{
		return get_at(_M_pool_size-1);
	}

	inline class_type* get_begin_reference() const
	{
		return get_reference_at(0);
	}
	inline class_type* get_end_reference() const
	{
		return get_reference_at(_M_pool_size-1);
	}


	inline array_buffer_size_val get_size() const
	{
		return _M_pool_size;
	}

	inline _Array_iterator* get_iterator(_Array_iterator* parray_iterator) const
	{
		if (null != parray_iterator)
		{
			if (P_OK == parray_iterator->reinit(this))
			{
				return parray_iterator;
			}
		}
		return null;
	}
	inline class_type* get_reference_at(const _Array_iterator* parray_iterator) const
	{
		if (null != parray_iterator)
		{
			return get_reference_at(parray_iterator->get_current_index());
		}

		return null;
	}
	inline const class_type* get_at(const _Array_iterator* parray_iterator) const
	{
		if (null != parray_iterator)
		{
			return get_at(parray_iterator->get_current_index());
		}

		return null;
	}

};


PECKER_END

#endif