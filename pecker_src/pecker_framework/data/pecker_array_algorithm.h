/*
 *  pecker_array_algorithm.h
 *
 *  Created on: 2012-11-1
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_ARRAY_ALGORITHM_H_
#define PECKER_ARRAY_ALGORITHM_H_

#include "../CPeckerObject.h"
PECKER_BEGIN

#define  ARRAY_DEFAULT_ALLOCATE_STEP 16
#define  ARRAY_BOOLEAN_TRUE		true
#define  ARRAY_BOOLEAN_FLASE	false

typedef HResult	 array_result;
typedef nINDEX		 array_index_val;
typedef nSize			 array_buffer_size_val;
typedef bool			 array_boolean_flag;

// resize
template<class class_type,class allocate_object_t>
inline array_result resize_array(class_type* & pArray_buffer,
															array_buffer_size_val current_array_size,
															array_buffer_size_val &current_array_buffer_size,
	                                                        array_buffer_size_val new_array_size,
															array_buffer_size_val new_allocate_object_step,
															array_boolean_flag		 bForce_release,
															array_boolean_flag		 bNew_allocate)
{
	array_buffer_size_val new_array_buffer_size = 0;

#ifdef ARRAY_BEBUG_CODE
	if (new_allocate_object_step <= 0)
	{
		new_allocate_object_step = ARRAY_DEFAULT_ALLOCATE_STEP;
	}
	
	if(new_array_size < 0)
		new_array_size = 0;
#endif
	
	if (ARRAY_BOOLEAN_TRUE == bForce_release)
	{
		if (0 >= new_array_size)
		{
			if (null != pArray_buffer)
			{
				allocate_object_t::deallocate_objects(pArray_buffer);
				pArray_buffer = null;
			}
			current_array_buffer_size = 0;
			return P_OK;
		}
		

		array_buffer_size_val tmp_mod_result = new_array_size % new_allocate_object_step;
		if (0 == tmp_mod_result)
		{
			new_array_buffer_size = new_array_size;
		}
		else
		{
			new_array_buffer_size = new_array_size - tmp_mod_result + new_allocate_object_step;
		}

		if (new_array_buffer_size == current_array_buffer_size)
		{
			return P_OK;
		}
	}
	else
	{
		if (new_array_size <= current_array_size)
		{
			return P_OK;
		}

		array_buffer_size_val tmp_mod_result = new_array_size % new_allocate_object_step;
		if (0 == tmp_mod_result)
		{
			new_array_buffer_size = new_array_size;
		}
		else
		{
			new_array_buffer_size = new_array_size - tmp_mod_result + new_allocate_object_step;
		}

		if (new_array_buffer_size <= current_array_buffer_size)
		{
			return P_OK;
		}
	}

	class_type* ptemp_new_allocate_object_buffer = allocate_object_t::allocate_objects(new_array_buffer_size);
	
	if (null != ptemp_new_allocate_object_buffer)
	{
		if (ARRAY_BOOLEAN_FLASE == bNew_allocate)
		{
			if (new_array_size > current_array_size)
			{
				new_array_size = current_array_size;
			}
			for (array_index_val index=0; index < new_array_size;++index)
			{
				ptemp_new_allocate_object_buffer[index] = pArray_buffer[index];
			}
		}
		allocate_object_t::deallocate_objects(pArray_buffer);
		pArray_buffer = ptemp_new_allocate_object_buffer;
		current_array_buffer_size = new_array_buffer_size;
		return P_OK;
	}
	else
	{
		return P_ERR;
	}

	return P_OK;
}

template< class class_type,class pointer_allocate_object_t,class allocate_object_t >
inline array_result resize_array_pool(class_type** & ppArray_buffer_pointer,
	array_buffer_size_val current_array_size,
	array_buffer_size_val current_array_allocate_object_step,
	array_buffer_size_val &current_array_buffer_pointer_size,
	array_buffer_size_val &current_array_buffer_pointer_buffer_size,
	array_buffer_size_val new_array_size,
	array_buffer_size_val new_allocate_object_step,
	array_buffer_size_val new_array_buffer_pointer_allocate_object_step,
	array_boolean_flag		 bForce_release,
	array_boolean_flag		 bNew_allocate)
{
	array_buffer_size_val tmp_mod_result = new_array_size % new_allocate_object_step;
	array_buffer_size_val new_buffer_pointer_size = new_array_size / new_allocate_object_step;
	if (tmp_mod_result > 0)
	{
		++new_buffer_pointer_size;
	}

	if (ARRAY_BOOLEAN_TRUE == bForce_release && 0 == new_array_size)
	{
		for (array_index_val index = new_buffer_pointer_size; index < current_array_buffer_pointer_size; ++index)
		{
			allocate_object_t::deallocate_objects(ppArray_buffer_pointer[index]);
			ppArray_buffer_pointer[index] = null;
		}
		pointer_allocate_object_t::deallocate_objects(ppArray_buffer_pointer);
		ppArray_buffer_pointer = null;
		current_array_buffer_pointer_size = 0;
		current_array_buffer_pointer_buffer_size = 0;
		return P_OK;
	}

	array_result resize_result = resize_array<class_type*, pointer_allocate_object_t>(ppArray_buffer_pointer,
		current_array_buffer_pointer_size,
		current_array_buffer_pointer_buffer_size,
		new_buffer_pointer_size,
		new_array_buffer_pointer_allocate_object_step,
		ARRAY_BOOLEAN_FLASE,
		ARRAY_BOOLEAN_FLASE);
	
	if (P_OK != resize_result)
	{
		return resize_result;
	}

	bool bis_allocate_object_fail = false;

	if (new_allocate_object_step != current_array_allocate_object_step)
	{
		class_type** ptemp_new_allocate_object_pointer_buffer = pointer_allocate_object_t::allocate_objects(new_buffer_pointer_size);
		if (null == ptemp_new_allocate_object_pointer_buffer)
		{
			return P_ERR;
		}

		array_index_val index = 0;
		for (; index < new_buffer_pointer_size; ++index)
		{
			ptemp_new_allocate_object_pointer_buffer[index] = allocate_object_t::allocate_objects(new_allocate_object_step);
			if (null == ptemp_new_allocate_object_pointer_buffer[index])
			{
				bis_allocate_object_fail = true;
				break;
			}
		}
		if (bis_allocate_object_fail)
		{
			for (; index >=0; --index)
			{
				allocate_object_t::deallocate_objects(ptemp_new_allocate_object_pointer_buffer[index]);
				ptemp_new_allocate_object_pointer_buffer[index] = null;
			}

			pointer_allocate_object_t::deallocate_objects(ptemp_new_allocate_object_pointer_buffer);
			return P_ERR;
		}
		else
		{
			if (new_array_size > current_array_size)
			{
				new_array_size = current_array_size;
			}

			array_index_val index_old_row = 0;
			array_index_val index_old_column = 0;
			array_index_val index_new_row = 0;
			array_index_val index_new_column = 0;

			if (ARRAY_BOOLEAN_FLASE == bNew_allocate)
			{
				for (index = 0;index<new_array_size;++index)
				{
					ptemp_new_allocate_object_pointer_buffer[index_new_row][index_new_column] = ppArray_buffer_pointer[index_old_row][index_old_column];
					++index_new_column;
					++index_old_column;
					if (current_array_allocate_object_step == index_old_column)
					{
						index_old_column = 0;
						++index_old_row;
					}
					if (new_allocate_object_step == index_new_column)
					{
						index_new_column = 0;
						++index_new_row;
					}
				}
			}


			for (index = 0;index<new_buffer_pointer_size;++index)
			{
				ppArray_buffer_pointer[index] = ptemp_new_allocate_object_pointer_buffer[index];
			}

			pointer_allocate_object_t::deallocate_objects(ptemp_new_allocate_object_pointer_buffer);
		}

		current_array_buffer_pointer_size = new_buffer_pointer_size;
		return P_OK;
	}



	if (new_buffer_pointer_size == current_array_buffer_pointer_size)
	{
		return P_OK;
	}
	else if (new_buffer_pointer_size < current_array_buffer_pointer_size)
	{
		if (ARRAY_BOOLEAN_TRUE == bForce_release)
		{
			for (array_index_val index = new_buffer_pointer_size; index < current_array_buffer_pointer_size; ++index)
			{
				allocate_object_t::deallocate_objects(ppArray_buffer_pointer[index]);
				ppArray_buffer_pointer[index] = null;
			}

		}
		
			
		current_array_buffer_pointer_size = new_buffer_pointer_size;
		return P_OK;
	}
	else if (new_buffer_pointer_size > current_array_buffer_pointer_size)
	{
		array_index_val tmp_allocate_size = new_buffer_pointer_size -  current_array_buffer_pointer_size;
		class_type** ptemp_new_allocate_object_pointer_buffer = pointer_allocate_object_t::allocate_objects(tmp_allocate_size);
		array_index_val index = 0;
		for (; index < tmp_allocate_size; ++index)
		{
			ptemp_new_allocate_object_pointer_buffer[index] = allocate_object_t::allocate_objects(new_allocate_object_step);
			if (null == ptemp_new_allocate_object_pointer_buffer[index])
			{
				bis_allocate_object_fail = true;
				break;
			}
		}
		if (bis_allocate_object_fail)
		{
			for (; index >=0; --index)
			{
				allocate_object_t::deallocate_objects(ptemp_new_allocate_object_pointer_buffer[index]);
				ptemp_new_allocate_object_pointer_buffer[index] = null;
			}

			pointer_allocate_object_t::deallocate_objects(ptemp_new_allocate_object_pointer_buffer);
			ptemp_new_allocate_object_pointer_buffer = null;
			return P_ERR;
		}
		else
		{
			index = current_array_buffer_pointer_size;
			for (; index < new_buffer_pointer_size; ++index)
			{
				ppArray_buffer_pointer[index] = ptemp_new_allocate_object_pointer_buffer[index-current_array_buffer_pointer_size];
			}
		}
		pointer_allocate_object_t::deallocate_objects(ptemp_new_allocate_object_pointer_buffer);
		ptemp_new_allocate_object_pointer_buffer = null;
	}

	current_array_buffer_pointer_size = new_buffer_pointer_size;
	return P_OK;
}


// sort

// 升序排列
template < class item_type, class compare_t,class _Array_container, class _Array_iterator>
array_result increment_order_partition(_Array_container& array,_Array_iterator& iterator_low,_Array_iterator& iterator_high,_Array_iterator& iterator_out)
{
	const item_type* pitem_high = null;
	const item_type* pitem_low = null;
	const item_type* pitem = array.get_at(&iterator_low);
	if (null == pitem)
	{
		return P_ERR;
	}
	item_type clip_item = *pitem;

	pitem_high =  array.get_at(&iterator_high);
	if (null == pitem_high)
	{
		return P_ERR;
	}

	pitem_low =  array.get_at(&iterator_low);
	if (null == pitem_low)
	{
		return P_ERR;
	}

	while (0 != _Array_iterator::compare(iterator_low,iterator_high) )
	{
		while (0 != _Array_iterator::compare(iterator_low,iterator_high) && compare_t::compare(*pitem_high,clip_item) >= 0)
		{
			iterator_high.decrement();
			pitem_high =  array.get_at(&iterator_high);
			if (null == pitem_high)
			{
				return P_ERR;
			}
		}

		//if (P_OK != swap< item_type,_Array_container , _Array_iterator >(array,iterator_low,iterator_high))
		if (P_OK != array.swap_value(&iterator_low,&iterator_high))
		{
			return P_ERR;
		}

		while (0 != _Array_iterator::compare(iterator_low,iterator_high) && compare_t::compare(*pitem_low,clip_item) <= 0)
		{
			iterator_low.increment();
			pitem_low =  array.get_at(&iterator_low);
			if (null == pitem_high)
			{
				return P_ERR;
			}
		}

		//if (P_OK != swap< item_type,_Array_container , _Array_iterator >(array,iterator_low,iterator_high))
		if (P_OK != array.swap_value(&iterator_low,&iterator_high))
		{
			return P_ERR;
		}

	}
	iterator_out.copy(&iterator_low);
	return P_OK;
}

// 降序排列
template < class item_type, class compare_t,class _Array_container, class _Array_iterator>
array_result decrement_order_partition(_Array_container& array,_Array_iterator& iterator_low,_Array_iterator& iterator_high,_Array_iterator& iterator_out)
{
	const item_type* pitem_high = null;
	const item_type* pitem_low = null;
	const item_type* pitem = array.get_at(&iterator_low);
	if (null == pitem)
	{
		return P_ERR;
	}
	item_type clip_item = *pitem;

	pitem_high =  array.get_at(&iterator_high);
	if (null == pitem_high)
	{
		return P_ERR;
	}

	pitem_low =  array.get_at(&iterator_low);
	if (null == pitem_low)
	{
		return P_ERR;
	}

	while (0 != _Array_iterator::compare(iterator_low,iterator_high) )
	{
		while (0 != _Array_iterator::compare(iterator_low,iterator_high) && compare_t::compare(*pitem_high,clip_item) <= 0)
		{
			iterator_high.decrement();
			pitem_high =  array.get_at(&iterator_high);
			if (null == pitem_high)
			{
				return P_ERR;
			}
		}

		//if (P_OK != swap< item_type,_Array_container , _Array_iterator >(array,iterator_low,iterator_high))
		if (P_OK != array.swap_value(&iterator_low,&iterator_high))
		{
			return P_ERR;
		}

		while (0 != _Array_iterator::compare(iterator_low,iterator_high) && compare_t::compare(*pitem_low,clip_item) >= 0)
		{
			iterator_low.increment();
			pitem_low =  array.get_at(&iterator_low);
			if (null == pitem_high)
			{
				return P_ERR;
			}
		}

		//if (P_OK != swap< item_type,_Array_container , _Array_iterator >(array,iterator_low,iterator_high))
		if (P_OK != array.swap_value(&iterator_low,&iterator_high))
		{
			return P_ERR;
		}

	}
	iterator_out.copy(&iterator_low);
	return P_OK;
}


template < class item_type, class compare_t,class _Array_container, class _Array_iterator >
array_result quick_sort_increment(_Array_container& array,const _Array_iterator& iterator_low_, const _Array_iterator& iterator_high_)
{
	_Array_iterator iterator_low(iterator_low_);
	_Array_iterator iterator_high(iterator_high_);
	_Array_iterator iterator_clip;
	
	if (P_OK != increment_order_partition< item_type, compare_t, _Array_container, _Array_iterator >(array,iterator_low,iterator_high,iterator_clip))
	{
		return P_ERR;
	}

	iterator_low.copy(&iterator_low_);
	iterator_high.copy(&iterator_high_);

	if (0 != _Array_iterator::compare(iterator_clip,iterator_low))
	{
		_Array_iterator itmp_pre(iterator_clip);
		itmp_pre.decrement();
		if (P_OK != quick_sort_increment< item_type, compare_t, _Array_container, _Array_iterator >(array,iterator_low,itmp_pre))
		{
			return P_ERR;
		}
	}

	if (0 != _Array_iterator::compare(iterator_clip,iterator_high))
	{
		_Array_iterator itmp_next(iterator_clip);
		itmp_next.increment();
		if (P_OK != quick_sort_increment< item_type, compare_t, _Array_container, _Array_iterator >(array,itmp_next,iterator_high))
		{
			return P_ERR;
		}
	}

	return P_OK;
}

template < class item_type, class compare_t,class _Array_container, class _Array_iterator >
array_result quick_sort_decrement(_Array_container& array,const _Array_iterator& iterator_low_, const _Array_iterator& iterator_high_)
{
	_Array_iterator iterator_low(iterator_low_);
	_Array_iterator iterator_high(iterator_high_);
	_Array_iterator iterator_clip;

	if (P_OK != decrement_order_partition< item_type, compare_t, _Array_container, _Array_iterator >(array,iterator_low,iterator_high,iterator_clip))
	{
		return P_ERR;
	}

	iterator_low.copy(&iterator_low_);
	iterator_high.copy(&iterator_high_);

	if (0 != _Array_iterator::compare(iterator_clip,iterator_low))
	{
		_Array_iterator itmp_pre(iterator_clip);
		itmp_pre.decrement();
		if (P_OK != quick_sort_decrement< item_type, compare_t, _Array_container, _Array_iterator >(array,iterator_low,itmp_pre))
		{
			return P_ERR;
		}
	}

	if (0 != _Array_iterator::compare(iterator_clip,iterator_high))
	{
		_Array_iterator itmp_next(iterator_clip);
		itmp_next.increment();
		if (P_OK != quick_sort_decrement< item_type, compare_t, _Array_container, _Array_iterator >(array,itmp_next,iterator_high))
		{
			return P_ERR;
		}
	}

	return P_OK;
}



PECKER_END

#endif
