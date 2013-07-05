/*  Created on: 2012-12-7
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/
#ifndef PECKER_STACK_H_
#define PECKER_STACK_H_

#include "pecker_array_algorithm.h"
#include "pecker_array.h"


PECKER_BEGIN

template< class value_type,
				   class allocate_object_t = pecker_system_defualt_allocator( value_type ),
				   class pointer_allocate_object_t = pecker_system_defualt_allocator( value_type* ),
					const int INTERNAL_BUFFER_SIZE = 512 >
class pecker_stack_pool_array
{
	typedef pecker_stack_pool_array< value_type,allocate_object_t,pointer_allocate_object_t,INTERNAL_BUFFER_SIZE  > _Stack_container;
	typedef pecker_array_iterator< _Stack_container > _Stack_iterator;
	enum
	{
		_BUFFER_SIZE =  INTERNAL_BUFFER_SIZE / sizeof (value_type) < 1 ? 1
		: INTERNAL_BUFFER_SIZE / sizeof (value_type)
	};

	typedef enum
	{
		STACK_SMALL_BUFFER = 0,
		STACK_LARGE_BUFFER
	}STACK_BUFFER_TYPE;

	typedef struct 
	{
		value_type** _M_ppArray_buffer_array;
		array_buffer_size_val _M_array_buffer_array_buffer_size;
		array_buffer_size_val _M_array_buffer_array_size;
		array_buffer_size_val _M_auto_allocate_step;
		array_buffer_size_val _M_array_buffer_array_allocate_step;
	}st_pool_array;

	typedef union
	{
		value_type			_M_Small_buffer[_BUFFER_SIZE];
		st_pool_array  _M_Large_buffer;
		char					_M_Alias_buffer[_BUFFER_SIZE];	
	}_Stack_value_buffer;
private:
	_Stack_value_buffer	_M_buffer;
	array_buffer_size_val _M_stack_size;
	STACK_BUFFER_TYPE	_M_stack_buffer_type;
private:
	inline value_type* get_large_reference_at(array_index_val index) const
	{
		if (index >=0 && index < _M_stack_size)
		{
			array_index_val tmp_step =  _M_buffer._M_Large_buffer._M_auto_allocate_step;
			array_index_val row_index = index / tmp_step;
			array_index_val column_index = index % tmp_step;
			return &(_M_buffer._M_Large_buffer._M_ppArray_buffer_array[row_index][column_index]);
		}
		else
		{
			return null;
		}
	}
public:
	explicit pecker_stack_pool_array():
																	_M_stack_size(0),
																	_M_stack_buffer_type(STACK_SMALL_BUFFER)
	{
	}
	~pecker_stack_pool_array()
	{
		clear(ARRAY_BOOLEAN_TRUE);
	}

	pecker_stack_pool_array(const _Stack_container& other_array):_M_stack_size(0),
																														 _M_stack_buffer_type(STACK_SMALL_BUFFER)
	{
		copy(other_array);
	}
	_Stack_container& operator = (const _Stack_container& other_array)
	{
		copy(other_array);
		return *this;
	}
public:
	inline array_result swap(_Stack_container& other_array)
	{
		if (&other_array != this)
		{
			STACK_BUFFER_TYPE tmptype = _M_stack_buffer_type;
			_M_stack_buffer_type = other_array._M_stack_buffer_type;
			other_array._M_stack_buffer_type = _M_stack_buffer_type;

			array_buffer_size_val tmpsize = _M_stack_size;
			_M_stack_size = other_array._M_stack_size;
			other_array._M_stack_size = tmpsize;

			_Stack_value_buffer tmpbuffer = _M_buffer;
			_M_buffer = other_array._M_buffer;
			other_array._M_buffer = tmpbuffer;
		}
		return PEK_STATUS_OK;
	}
	inline array_result swap_value(const _Stack_iterator* piterator1,const _Stack_iterator* piterator2)
	{
		value_type* pitem_low = get_reference_at(piterator1);
		value_type* pitem_hight = get_reference_at(piterator2);
		if ( null != pitem_hight && 
			null != pitem_low)
		{
			value_type ptemp_item = *pitem_hight;
			*pitem_hight = *pitem_low;
			*pitem_low = ptemp_item;
			return PEK_STATUS_OK;
		}
		else
		{
			return PEK_STATUS_ERROR;
		}
	}
	inline array_result swap_value(array_index_val index1,array_index_val index2)
	{
		value_type* pitem_low = get_reference_at(index1);
		value_type* pitem_hight = get_reference_at(index2);
		if ( null != pitem_hight && 
			null != pitem_low)
		{
			value_type ptemp_item = *pitem_hight;
			*pitem_hight = *pitem_low;
			*pitem_low = ptemp_item;
			return PEK_STATUS_OK;
		}
		else
		{
			return PEK_STATUS_ERROR;
		}
	}

	array_result resize(array_buffer_size_val resize_size, 
		array_buffer_size_val auto_allocate_size = -1,
		array_buffer_size_val auto_allocate_buffer_array_step = -1,
		array_boolean_flag bForce_release = ARRAY_BOOLEAN_FLASE)
	{
		if (auto_allocate_size <= 0)
		{
			if (STACK_LARGE_BUFFER == _M_stack_buffer_type)
			{
				auto_allocate_size = _M_buffer._M_Large_buffer._M_auto_allocate_step;
			}
			else
			{
				auto_allocate_size = _BUFFER_SIZE;
			}
			
		}
		if (auto_allocate_buffer_array_step <=0 )
		{
			if (STACK_LARGE_BUFFER == _M_stack_buffer_type)
			{
				auto_allocate_buffer_array_step = _M_buffer._M_Large_buffer._M_array_buffer_array_allocate_step;
			}
			else
			{
				auto_allocate_buffer_array_step = ARRAY_DEFAULT_ALLOCATE_STEP;
			}
			
		}

		array_result resize_result;
		if (STACK_LARGE_BUFFER == _M_stack_buffer_type)
		{
			if (resize_size <= _BUFFER_SIZE && ARRAY_BOOLEAN_TRUE == bForce_release)
			{
				_Stack_value_buffer tmp_buffer;

				array_buffer_size_val copy_buffer_size = _M_stack_size;
				if (copy_buffer_size > resize_size)
				{
					copy_buffer_size = resize_size;
				}
				for (array_index_val i = 0; i<copy_buffer_size; ++i)
				{
					tmp_buffer._M_Small_buffer[i] = *get_large_reference_at(i);
				}
				resize_result = resize_array_pool< value_type,pointer_allocate_object_t, allocate_object_t >
					(_M_buffer._M_Large_buffer._M_ppArray_buffer_array,
					_M_stack_size,
					_M_buffer._M_Large_buffer._M_auto_allocate_step,
					_M_buffer._M_Large_buffer._M_array_buffer_array_size,
					_M_buffer._M_Large_buffer._M_array_buffer_array_buffer_size,
					0,
					auto_allocate_size,
					auto_allocate_buffer_array_step,
					ARRAY_BOOLEAN_TRUE,
					ARRAY_BOOLEAN_TRUE);

				if (PEK_STATUS_OK == resize_result)
				{
					_M_stack_size = resize_size;
					_M_buffer = tmp_buffer;
					_M_stack_buffer_type = STACK_SMALL_BUFFER;
				}
			}
			else
			{
				resize_result = resize_array_pool< value_type,pointer_allocate_object_t, allocate_object_t >
					(_M_buffer._M_Large_buffer._M_ppArray_buffer_array,
					_M_stack_size,
					_M_buffer._M_Large_buffer._M_auto_allocate_step,
					_M_buffer._M_Large_buffer._M_array_buffer_array_size,
					_M_buffer._M_Large_buffer._M_array_buffer_array_buffer_size,
					resize_size,
					auto_allocate_size,
					auto_allocate_buffer_array_step,
					bForce_release,
					ARRAY_BOOLEAN_TRUE);

				if (PEK_STATUS_OK == resize_result)
				{
					_M_stack_size = resize_size;
					_M_buffer._M_Large_buffer._M_auto_allocate_step = auto_allocate_size;
					_M_buffer._M_Large_buffer._M_array_buffer_array_allocate_step = auto_allocate_buffer_array_step;
				}
			}

			//return resize_result;
		}
		else if (STACK_SMALL_BUFFER == _M_stack_buffer_type)
		{
			if (resize_size > _BUFFER_SIZE)
			{
				_Stack_value_buffer tmp_buffer = _M_buffer;
				array_buffer_size_val copy_buffer_size = _M_stack_size;
				memset(&_M_buffer,0,sizeof(_M_buffer));
				_M_stack_size = 0;

				resize_result = resize_array_pool< value_type,pointer_allocate_object_t, allocate_object_t >
					(_M_buffer._M_Large_buffer._M_ppArray_buffer_array,
					_M_stack_size,
					_M_buffer._M_Large_buffer._M_auto_allocate_step,
					_M_buffer._M_Large_buffer._M_array_buffer_array_size,
					_M_buffer._M_Large_buffer._M_array_buffer_array_buffer_size,
					resize_size,
					auto_allocate_size,
					auto_allocate_buffer_array_step,
					bForce_release,
					ARRAY_BOOLEAN_TRUE);

				if (PEK_STATUS_OK == resize_result)
				{
					_M_stack_size = resize_size;
					_M_stack_buffer_type = STACK_LARGE_BUFFER;
					_M_buffer._M_Large_buffer._M_auto_allocate_step = auto_allocate_size;
					_M_buffer._M_Large_buffer._M_array_buffer_array_allocate_step = auto_allocate_buffer_array_step;

					for (array_index_val i = 0; i<copy_buffer_size; ++i)
					{
						*get_large_reference_at(i) = tmp_buffer._M_Small_buffer[i];
					}

				}
				else
				{
					_M_buffer = tmp_buffer;
				}
			}
			else
			{
				_M_stack_size = resize_size;
				resize_result = PEK_STATUS_OK;
			}


		}

	

		return resize_result;
	}

	array_result init(array_buffer_size_val resize_size = -1, 
	array_buffer_size_val auto_allocate_size = -1,
	array_buffer_size_val auto_allocate_buffer_array_step = -1)
	{
		if (resize_size < 0)
		{
			resize_size = _BUFFER_SIZE;
		}
		array_result return_result = resize(resize_size,auto_allocate_size,auto_allocate_buffer_array_step,ARRAY_BOOLEAN_FLASE);
		if (PEK_STATUS_OK == return_result)
		{
			_M_stack_size = 0;
		}
		return return_result;
	}

	array_result clear(array_boolean_flag bForce_release = ARRAY_BOOLEAN_FLASE)
	{
		return resize(0,-1,bForce_release);
	}
	array_result copy(const _Stack_container& other_stack)
	{
		if (this != &other_stack)
		{
			array_buffer_size_val other_stack_size = other_stack.get_size();
			array_result resize_result = this->resize(other_stack_size);
			if (PEK_STATUS_OK == resize_result)
			{
				for (array_index_val i=0;i<other_stack_size;++i)
				{
					*get_reference_at(i) = other_stack.get_at(i);
				}
			}
			return resize_result;
		}
		return PEK_STATUS_OK;
	}

	inline array_buffer_size_val get_size() const
	{
		return _M_stack_size;
	}

	inline const value_type* get_at(array_index_val index) const
	{
		if (STACK_SMALL_BUFFER == _M_stack_buffer_type)
		{
			if (index >=0 && index < _M_stack_size)
			{
				return &(_M_buffer._M_Small_buffer[index]);
			}
			else
			{
				return null;
			}
		}
		else
		{
			return get_large_reference_at(index);
		}
	}
	inline value_type* get_reference_at(array_index_val index) const
	{
		if (STACK_SMALL_BUFFER == _M_stack_buffer_type)
		{
			if (index >=0 && index < _M_stack_size)
			{
				return (value_type*)&(_M_buffer._M_Small_buffer[index]);
			}
			else
			{
				return null;
			}
		}
		else
		{
			return get_large_reference_at(index);
		}
	}
	inline array_result set_at(array_index_val index,const value_type& set_item)
	{
		 value_type* pmodify_value = get_reference_at(index);
		 if (null != pmodify_value)
		 {
			 *pmodify_value = set_item;
			 return PEK_STATUS_OK;
		 }
		 return PEK_STATUS_ERROR;
	}

	inline array_result push_new_value()
	{
		array_result resize_result = resize(_M_stack_size+1);
		return resize_result;
	}

	inline array_result push(const value_type& set_item)
	{
		array_result resize_result = resize(_M_stack_size+1);
		if (PEK_STATUS_OK == resize_result)
		{
			*get_reference_at(_M_stack_size-1) = set_item;
		}
		return resize_result;
	}
	inline array_result pop()
	{
		if (_M_stack_size > 0)
		{
			return resize(_M_stack_size-1);
		}
		else
		{
			return PEK_STATUS_SUCCESS;
		}
	}

	inline const value_type* begin() const
	{
		return get_at(0);
	}
	inline const value_type* end() const
	{
		return get_at(_M_stack_size-1);
	}

	inline value_type* get_begin_reference() const
	{
		return get_reference_at(0);
	}
	inline value_type* get_end_reference() const
	{
		return get_reference_at(_M_stack_size-1);
	}

	inline _Stack_iterator* get_iterator(_Stack_iterator* parray_iterator) const
	{
		if (null != parray_iterator)
		{
			if (PEK_STATUS_OK == parray_iterator->reinit(this))
			{
				return parray_iterator;
			}
		}
		return null;
	}
	inline value_type* get_reference_at(const _Stack_iterator* parray_iterator) const
	{
		if (null != parray_iterator)
		{
			return get_reference_at(parray_iterator->get_current_index());
		}

		return null;
	}
	inline const value_type* get_at(const _Stack_iterator* parray_iterator) const
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
