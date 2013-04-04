/*
 *  pecker_list.h
 *
 *  Created on: 2012-11-21
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_LIST_H_
#define PECKER_LIST_H_

#include "pecker_nodes_allocate.h"
#include "pecker_list_algorithm.h"
#include "pecker_array_algorithm.h"
#include "pecker_list_iterator.h"

PECKER_BEGIN



template< class item_value_t, 
					class linked_list_node_t = pecker_linked_list_node_t< item_value_t >,
					class nodes_allocator_t = pecker_nodes_simple_allocater< linked_list_node_t > >
class pecker_list
{
	typedef pecker_list_iterator< linked_list_node_t, pecker_list< item_value_t,linked_list_node_t,nodes_allocator_t > > _List_iterator;
	typedef pecker_list< item_value_t,linked_list_node_t,nodes_allocator_t > _List_container;
private:
	nodes_allocator_t _M_allocator;
	list_size					  _M_node_count;

	linked_list_node_t* _M_pbegin_node;
	linked_list_node_t* _M_pend_node;

public:
	pecker_list():_M_pbegin_node(null),_M_pend_node(null),_M_node_count(0)
	{

	}
	pecker_list(const _List_container& other)
	{
		copy(other);
	}
	~pecker_list()
	{
		clear();
	}
public:
	list_result copy(const _List_container& other)
	{
		if (&other == this)
		{
			return P_OK;
		}
		list_size othersize = other.get_size();
		list_size listsize = _M_node_count - othersize;
		list_result return_result = P_OK;
		if (listsize >= 0)
		{
			for (list_size i=0;i<listsize;++i)
			{
				pop();
			}
			linked_list_node_t* ptemp_this_node = _M_pbegin_node;
			const linked_list_node_t* ptemp_other_node = other.begin();
			
			for (list_size i=0;i<othersize;++i)
			{
				ptemp_this_node->value = ptemp_other_node->value;
				ptemp_this_node = ptemp_this_node->_M_next_node;
				ptemp_other_node = ptemp_other_node->_M_next_node;
			}
		}
		else
		{
			linked_list_node_t* ptemp_this_node = _M_pbegin_node;
			const linked_list_node_t* ptemp_other_node = other.begin();

			for (list_size i=0;i<_M_node_count;++i)
			{
				ptemp_this_node->value = ptemp_other_node->value;
				ptemp_this_node = ptemp_this_node->_M_next_node;
				ptemp_other_node = ptemp_other_node->_M_next_node;
			}

			listsize = -listsize;
			
			for (list_size i=0;i<listsize;++i)
			{
				if (null == push(ptemp_other_node->value))
				{
					return_result = P_ERR;
					break;
				}
				ptemp_other_node = ptemp_other_node->_M_next_node;
			}
		}

		return return_result;

	}
	inline list_result swap_list(_List_container& other)
	{
		if (&other != this)
		{
			if (P_OK == _M_allocator.swap(other._M_allocator))
			{
				list_size tmp_size = _M_node_count;
				_M_node_count =  other._M_node_count;
				other._M_node_count = tmp_size;

				linked_list_node_t* ptemp_node = _M_pbegin_node;
				_M_pbegin_node = other._M_pbegin_node;
				other._M_pbegin_node = ptemp_node;

				ptemp_node = _M_pend_node;
				_M_pend_node = other._M_pend_node;
				other._M_pend_node = ptemp_node;
				return P_OK;
			}
			return P_ERR;

		}
		return P_OK;
	}
	list_result clear()
	{
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(true);
			_M_pbegin_node = null;
			_M_pend_node = null;
			_M_node_count = 0;
			return P_OK;
		}
		else
		{
			linked_list_node_t* ptemp_b2e = _M_pbegin_node;
			while (ptemp_b2e != _M_pend_node)
			{
				linked_list_node_t* ptemp_erase = ptemp_b2e;
				ptemp_b2e = ptemp_b2e->_M_next_node;
				_M_allocator.release_node(ptemp_erase);
			}
			_M_pbegin_node = null;
			_M_pend_node = null;
			_M_node_count = 0;

			return P_OK;
		}
	}

	const linked_list_node_t* push(const item_value_t& item_value)
	{
		linked_list_node_t* pnode = _M_allocator.create_node();
		if (P_OK == push_back_list_node< linked_list_node_t >(_M_pend_node,pnode))
		{
			_M_pend_node = pnode;
			pnode->value = item_value;
			if (0 == _M_node_count)
			{
				_M_pbegin_node = _M_pend_node;
			}
			++_M_node_count;
			return pnode;
		}
		else
		{
			_M_allocator.release_node(pnode);
			return null;
		}
	}
	list_result pop()
	{
		linked_list_node_t* ptemp_pre_node = null;
		if (null != _M_pend_node)
		{
			ptemp_pre_node = _M_pend_node->_M_pre_node;
		}
		list_result return_result = remove_list_node< linked_list_node_t >(_M_pend_node);
		if (P_OK == return_result)
		{
			_M_allocator.release_node(_M_pend_node);
			_M_pend_node = ptemp_pre_node;
			if (1 == _M_node_count)
			{
				_M_pbegin_node = null;
			}
			--_M_node_count;
		}
		return return_result;
	}

	const linked_list_node_t* push_front(const item_value_t& item_value)
	{
		linked_list_node_t* pnode = _M_allocator.create_node();
		if (P_OK == push_fornt_list_node< linked_list_node_t >(_M_pbegin_node,pnode))
		{
			_M_pbegin_node = pnode;
			pnode->value = item_value;
			if (0 == _M_node_count)
			{
				_M_pend_node = _M_pbegin_node;
			}
			++_M_node_count;
			return pnode;
		}
		else
		{
			_M_allocator.release_node(pnode);
			return null;
		}
	}
	list_result pop_front()
	{
		linked_list_node_t* ptemp_next_node = null;
		if (null != _M_pbegin_node)
		{
			ptemp_next_node = _M_pbegin_node->_M_next_node;
		}
		list_result return_result = remove_list_node< linked_list_node_t >(_M_pbegin_node);
		if (P_OK == return_result)
		{
			_M_allocator.release_node(_M_pbegin_node);
			_M_pbegin_node = ptemp_next_node;
			if (1 == _M_node_count)
			{
				_M_pend_node = null;
			}
			--_M_node_count;
		}
		return return_result;
	}

	inline const linked_list_node_t* begin() const
	{
		return _M_pbegin_node;
	}
	inline const linked_list_node_t* end() const
	{
		return _M_pend_node;
	}

	inline list_size get_size() const
	{
		return _M_node_count;
	}
	inline _List_iterator* get_iterator(_List_iterator* plist_iterator) const
	{
		if (null != plist_iterator)
		{
			if (P_OK == plist_iterator->reinit(this))
			{
				return plist_iterator;
			}
		}
		return null;
	}
	const linked_list_node_t* get_node(const _List_iterator* plist_iterator) const
	{
		if (null != plist_iterator && plist_iterator->get_container() == this)
		{
			return plist_iterator->get_current_node();
		}
		return null;
	}

	inline list_result swap_value(const _List_iterator* piterator1,const _List_iterator* piterator2)
	{
		linked_list_node_t* pitem_low = (linked_list_node_t*)get_node(piterator1);
		linked_list_node_t* pitem_hight = (linked_list_node_t*)get_node(piterator2);
		return swap_node(pitem_low, pitem_hight);
	}
	inline const linked_list_node_t* insert_next(const _List_iterator* plist_iterator,const item_value_t& _item_value)
	{
		linked_list_node_t* pitem_node = (linked_list_node_t*)get_node(plist_iterator);
		if (null == pitem_node)
		{
			if (null == _M_pbegin_node && null == _M_pend_node)
			{
				return push(_item_value);
			}
			else
			{
				return null;
			}
		}

		if (pitem_node == _M_pend_node)
		{
			return push(_item_value);
		}
		else
		{
			linked_list_node_t* pnode = _M_allocator.create_node();
			if (P_OK == insert_list_node_next< linked_list_node_t >(pitem_node,pnode))
			{
				++_M_node_count;
				return pnode;
			}
			else
			{
				_M_allocator.release_node(pnode);
			}
		}


		return null;
	}
	inline const linked_list_node_t* insert_pre(const _List_iterator* plist_iterator,const item_value_t& _item_value)
	{
		linked_list_node_t* pitem_node = (linked_list_node_t*)get_node(plist_iterator);
		if (null == pitem_node)
		{
			if (null == _M_pbegin_node && null == _M_pend_node)
			{
				return push_front(_item_value);
			}
			else
			{
				return null;
			}
		}

		if (pitem_node == _M_pbegin_node)
		{
			return push_front(_item_value);
		}
		else
		{
			linked_list_node_t* pnode = _M_allocator.create_node();
			if (P_OK == insert_list_node_pre< linked_list_node_t >(pitem_node,pnode))
			{
				++_M_node_count;
				return pnode;
			}
			else
			{
				_M_allocator.release_node(pnode);
			}
		}


		return null;
	}

	inline list_result erase(_List_iterator* plist_iterator)
	{
		linked_list_node_t* pitem_node = (linked_list_node_t*)get_node(plist_iterator);
		if (_M_pbegin_node == pitem_node)
		{
			return pop_front();
		}
		else if (_M_pend_node == pitem_node)
		{
			return pop();
		}
		else
		{
			list_result return_result = remove_list_node< linked_list_node_t >(pitem_node);
			if (P_OK == return_result)
			{
				_M_allocator.release_node(pitem_node);
			}
			return return_result;
		}

	}

	inline list_result erase(_List_iterator* plist_iterator_begin,_List_iterator* plist_iterator_end)
	{
		linked_list_node_t* pitem_node_begin = (linked_list_node_t*)get_node(plist_iterator_begin);
		linked_list_node_t* pitem_node_end = (linked_list_node_t*)get_node(plist_iterator_end);

		linked_list_node_t* pitem_node_begin_to_end = pitem_node_begin;
		linked_list_node_t* pitem_node_end_to_begin = pitem_node_end;

		boolean bcheck_ok = false;

		if (pitem_node_begin == _M_pbegin_node && pitem_node_end == _M_pend_node)
		{
			bcheck_ok = true;
		}
		else
		{
			for (int i=0;i<=_M_node_count;++i)
			{
				if (pitem_node_end == pitem_node_begin_to_end)
				{
					bcheck_ok = true;
					break;
				}
				else if (pitem_node_begin == pitem_node_end_to_begin)
				{
					bcheck_ok = true;
					pitem_node_begin = pitem_node_end;
					pitem_node_end = pitem_node_end_to_begin;
					break;
				}

				if (pitem_node_begin_to_end)
				{
					pitem_node_begin_to_end = pitem_node_begin_to_end->_M_next_node;
				}
				if (pitem_node_end_to_begin)
				{
					pitem_node_end_to_begin = pitem_node_end_to_begin->_M_next_node;
				}
			}
		}


		if (false == bcheck_ok)
		{
			return P_ERR;
		}

		list_result return_result = remove_list_nodes_unsafe< linked_list_node_t >(pitem_node_begin,pitem_node_end);
		if (P_OK != return_result)
		{
			return return_result;
		}

		if (pitem_node_begin == _M_pbegin_node && pitem_node_end == _M_pend_node)
		{
			_M_pbegin_node = null;
			_M_pend_node = null;
		}
		else if (pitem_node_begin == _M_pbegin_node)
		{
			_M_pbegin_node = pitem_node_end->_M_next_node;
		}
		else if (pitem_node_end == _M_pend_node)
		{
			_M_pend_node = pitem_node_begin->_M_pre_node;
		}

		 pitem_node_end->_M_next_node = null;
		 while (pitem_node_begin)
		 {
			 linked_list_node_t* pitem_node_erase = pitem_node_begin;
			 pitem_node_begin = (linked_list_node_t*)(pitem_node_begin->_M_next_node);
			 _M_allocator.release_node(pitem_node_erase);
		 }

		return P_OK;
	}

protected:
	inline list_result swap_node(linked_list_node_t* pfirst_node,linked_list_node_t* psecond_node)
	{
		list_result return_result = swap_list_node< linked_list_node_t >(pfirst_node,psecond_node);
		if (P_OK == return_result)
		{
			if (pfirst_node == _M_pbegin_node && psecond_node == _M_pend_node)
			{
				_M_pbegin_node = psecond_node;
				_M_pend_node = pfirst_node;
			}
			else if (pfirst_node == _M_pend_node && psecond_node == _M_pbegin_node)
			{
				_M_pbegin_node = pfirst_node;
				_M_pend_node = psecond_node;
			}
			else if (pfirst_node == _M_pbegin_node)
			{
				_M_pbegin_node = psecond_node;
			}
			else if (psecond_node == _M_pbegin_node)
			{
				_M_pbegin_node = pfirst_node;
			}
			else if (pfirst_node == _M_pend_node)
			{
				_M_pend_node = psecond_node;
			}
			else if (psecond_node == _M_pend_node)
			{
				_M_pend_node = pfirst_node;
			}


		}

		return return_result;
	}
	
	inline list_result swap_node_with_difference_list( linked_list_node_t* pitem_this_node,
																								_List_container &other_list,
																								linked_list_node_t* pitem_other_node)
	{
		if (null == pitem_this_node || null == pitem_other_node)
		{
			return P_ERR;
		}
		linked_list_node_t* ptransfer_this_node = _M_allocator.transfer_value(other_list._M_allocator,pitem_this_node);
		linked_list_node_t* ptransfer_other_node = other_list._M_allocator.transfer_value(_M_allocator,pitem_other_node);

		if (null != ptransfer_this_node && null != ptransfer_other_node)
		{
			list_result return_result = swap_list_node< linked_list_node_t >(ptransfer_this_node,ptransfer_other_node);
			if (P_OK == return_result)
			{
				if (pitem_this_node == _M_pbegin_node)
				{
					_M_pbegin_node = ptransfer_other_node;
				}
				else if (pitem_this_node == _M_pend_node)
				{
					_M_pend_node == ptransfer_other_node;
				}

				if (pitem_other_node == other_list._M_pbegin_node)
				{
					other_list._M_pbegin_node = ptransfer_this_node;
				}
				else if (pitem_other_node == other_list._M_pend_node)
				{
					other_list._M_pend_node == ptransfer_this_node;
				}
			}
			return return_result;
		}

		
		
		// 出错恢复
		if (null != ptransfer_this_node )
		{
			ptransfer_this_node = other_list._M_allocator.transfer_value(_M_allocator,ptransfer_this_node);

			if (null == ptransfer_this_node)
			{
				return P_ERR;
			}

			if (pitem_this_node == _M_pbegin_node)
			{
				_M_pbegin_node = ptransfer_this_node;
			}
			else if (pitem_this_node == _M_pend_node)
			{
				_M_pend_node == ptransfer_this_node;
			}
		}

		if (null != ptransfer_other_node)
		{
			ptransfer_other_node = _M_allocator.transfer_value(other_list._M_allocator,ptransfer_other_node);

			if (null == ptransfer_other_node)
			{
				return P_ERR;
			}

			if (pitem_other_node == other_list._M_pbegin_node)
			{
				other_list._M_pbegin_node = ptransfer_other_node;
			}
			else if (pitem_other_node == other_list._M_pend_node)
			{
				other_list._M_pend_node == ptransfer_other_node;
			}
		}

		return P_ERR;
	}

};


PECKER_END

#endif // PECKER_LIST_H_