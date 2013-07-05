/*
 *  pecker_array_iterator.h
 *
 *  Created on: 2012-11-1
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_ARRAY_ITERATOR_H
#define PECKER_ARRAY_ITERATOR_H

#include "pecker_iterator.h"
#include "pecker_array_algorithm.h"

PECKER_BEGIN
	
template<class array_container >
class pecker_array_iterator
{
	typedef pecker_array_iterator< array_container > _Array_iterator;
private:
	const array_container* _M_pContainer;
	array_index_val _M_current_index;
public:
	explicit pecker_array_iterator(const array_container* pcontainer = null):_M_pContainer(pcontainer)
	{
		if (null != _M_pContainer && _M_pContainer->get_size() > 0)
		{
			_M_current_index = 0;
		}
		_M_current_index = -1;
	}
	pecker_array_iterator(const _Array_iterator& other)
	{
		copy(&other);
	}
	virtual ~pecker_array_iterator()
	{
		_M_pContainer = null;
	}

public:
	virtual array_result init()
	{
		return init(ITERATOR_INIT_BEGIN_INDEX);
	}

	virtual array_result init(LINEAR_INTERATOR_INIT_TYPE init_type = ITERATOR_INIT_BEGIN_INDEX)
	{
		if (null != _M_pContainer)
		{
			array_buffer_size_val size = _M_pContainer->get_size();
			if (0 >= size)
			{
				_M_current_index = -1;
				return PEK_STATUS_OK;
			}

			if (ITERATOR_INIT_BEGIN_INDEX == init_type)
			{
				_M_current_index = 0;
			}
			else if (ITERATOR_INIT_END_INDEX == init_type)
			{
				_M_current_index = size - 1;
			}
			else
			{
				_M_current_index = -1;
				return PEK_STATUS_ERROR;
			}
			return PEK_STATUS_OK;
		}
		else
		{
			_M_current_index = -1;
			return PEK_STATUS_SUCCESS;
		}


	}

	virtual array_result reinit(const array_container* pcontainer,LINEAR_INTERATOR_INIT_TYPE init_type = ITERATOR_INIT_BEGIN_INDEX)
	{
		if (pcontainer != null)
		{
			_M_pContainer = pcontainer;
			return init(init_type);
		}
		return PEK_STATUS_ERROR;
	}

	virtual array_result copy(const pecker_array_iterator< array_container >* pother_liner_iterator)
	{
		if (this == pother_liner_iterator)
		{
			return PEK_STATUS_OK;
		}
		else if (null != pother_liner_iterator)
		{
			_M_pContainer = pother_liner_iterator->_M_pContainer;
			_M_current_index = pother_liner_iterator->_M_current_index;
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	inline virtual array_result increment()
	{
		if (null == _M_pContainer)
		{
			return PEK_STATUS_ERROR;
		}
		++_M_current_index;
		//if (_M_current_index < (_M_pContainer->get_size() - 1))
		//{
		//	++_M_current_index;
		//}
		return PEK_STATUS_OK;
	}

	inline virtual array_result decrement()
	{
		if (null == _M_pContainer)
		{
			return PEK_STATUS_ERROR;
		}

		--_M_current_index;
		//if (0 < _M_current_index)
		//{
		//	--_M_current_index;
		//}
		return PEK_STATUS_OK;
	}

	inline virtual array_index_val get_current_index() const
	{
		return _M_current_index;
	}

	inline virtual array_result set_current_index(array_index_val set_index)
	{
		if (null != _M_pContainer && set_index >=0 && set_index < _M_pContainer->get_size())
		{
			_M_current_index = set_index;
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}


	static inline int compare(const _Array_iterator &iterator1, 
		const _Array_iterator &iterator2)
	{
		return (iterator1._M_current_index - iterator2._M_current_index);
	}

};


PECKER_END

#endif