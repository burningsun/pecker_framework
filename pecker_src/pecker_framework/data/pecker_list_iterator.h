/*
 *  pecker_list_iterator.h
 *
 *  Created on: 2013-1-7
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_LIST_ITERATOR_H
#define PECKER_LIST_ITERATOR_H

#include "pecker_iterator.h"
#include "pecker_list_algorithm.h"

PECKER_BEGIN
	
template<class  linked_list_node_t, class list_container >
class pecker_list_iterator
{
	typedef pecker_list_iterator< linked_list_node_t,list_container > _List_iterator;
private:
	const list_container* _M_pContainer;
	const linked_list_node_t* _M_pCurrent_node;
public:
	explicit pecker_list_iterator(const list_container* pcontainer = null):_M_pContainer(pcontainer),_M_pCurrent_node(null)
	{
		if (null != _M_pContainer)
		{
			_M_pCurrent_node = _M_pContainer->begin();
		}
	}
	pecker_list_iterator(const _List_iterator& other)
	{
		copy(&other);
	}
	virtual ~pecker_list_iterator()
	{
		_M_pContainer = null;
		_M_pCurrent_node = null;
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
			switch (init_type)
			{
			case ITERATOR_INIT_BEGIN_INDEX:
				_M_pCurrent_node = _M_pContainer->begin();
				break;
			case ITERATOR_INIT_END_INDEX:
				_M_pCurrent_node = _M_pContainer->end();
				break;
			default:
				return P_ERR;
			}
			return P_OK;
		}
		else
		{
			_M_pCurrent_node = null;
			return P_SUCCESS;
		}


	}

	virtual array_result reinit(const list_container* pcontainer,LINEAR_INTERATOR_INIT_TYPE init_type = ITERATOR_INIT_BEGIN_INDEX)
	{
		if (pcontainer != null)
		{
			_M_pContainer = pcontainer;
			return init(init_type);
		}
		return P_ERR;
	}

	virtual array_result copy(const pecker_list_iterator< linked_list_node_t,list_container >* pother_liner_iterator)
	{
		if (this == pother_liner_iterator)
		{
			return P_OK;
		}
		else if (null != pother_liner_iterator)
		{
			_M_pContainer = pother_liner_iterator->_M_pContainer;
			_M_pCurrent_node = pother_liner_iterator->_M_pCurrent_node;
			return P_OK;
		}
		return P_ERR;
	}

	inline virtual array_result increment()
	{
		if (null == _M_pContainer)
		{
			return P_ERR;
		}
		if (null != _M_pCurrent_node->_M_next_node)
		{
			_M_pCurrent_node = _M_pCurrent_node->_M_next_node;
			return P_OK;
		}
		else
		{
			return P_SUCCESS;
		}
		
	}

	inline virtual array_result decrement()
	{
		if (null == _M_pContainer)
		{
			return P_ERR;
		}
		if (null != _M_pCurrent_node->_M_pre_node)
		{
			_M_pCurrent_node = _M_pCurrent_node->_M_pre_node;
			return P_OK;
		}
		else
		{
			return P_SUCCESS;
		}
	}

	inline virtual const linked_list_node_t* get_current_node() const
	{
		return _M_pCurrent_node;
	}

	inline virtual const list_container* get_container() const
	{
		return _M_pContainer;
	}
	// 主要用于快速排序
	static inline int compare(const _List_iterator &iterator1, 
		const _List_iterator &iterator2)
	{
		return ((long)(iterator1._M_pCurrent_node) - (long)(iterator2._M_pCurrent_node));
	}

};


PECKER_END

#endif