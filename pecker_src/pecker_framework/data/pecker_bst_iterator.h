/*
 *  pecker_bst_iterator.h
 *
 *  Created on: 2012-12-9
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_BST_ITERATOR_H_
#define PECKER_BST_ITERATOR_H_

#include "pecker_iterator.h"
#include "pecker_stack.h"
#include "pecker_bst_algorithm.h"
PECKER_BEGIN


// 二叉树迭代器接口
template< class BST_node_t >
PeckerInterface Ipecker_bst_tree_iterator
{
	virtual ~Ipecker_bst_tree_iterator(){;}
	virtual HResult init() = 0;
	virtual HResult init(TREE_ITERATOR_INIT_TYPE init_type) = 0;
	virtual HResult reinit(const BST_node_t* pBst_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_DEFAULT) = 0;
	virtual const BST_node_t* get_current_node() const = 0;
	virtual const BST_node_t* get_root_node() const = 0;
};

// 二叉树中序遍历迭代器接口
template< class BST_node_t >
PeckerInterface Ipecker_bst_tree_inorder_iterator : public Ipecker_bst_tree_iterator< BST_node_t >
{
	virtual ~Ipecker_bst_tree_inorder_iterator(){;}
	virtual HResult increment() = 0;
	virtual  HResult decrement() = 0;
};

// 二叉树后续遍历迭代器接口
template< class BST_node_t >
PeckerInterface Ipecker_bst_tree_posorder_iterator : public Ipecker_bst_tree_iterator< BST_node_t >
{
	virtual ~Ipecker_bst_tree_posorder_iterator(){;}
	virtual HResult increment_right() = 0;
	virtual  HResult increment_left() = 0;
};

// 无父节点的二叉树节点的中序遍历迭代器
template< class BST_node_t,
				   class allocate_object_t = pecker_system_defualt_allocator( const BST_node_t* ),
				   class pointer_allocate_object_t = pecker_system_defualt_allocator( const BST_node_t** ) >
class pecker_bst_tree_no_perent_node_inorder_iterator_base : public Ipecker_bst_tree_inorder_iterator< BST_node_t >
{
	typedef pecker_stack_pool_array< const BST_node_t*,allocate_object_t,pointer_allocate_object_t  > _Stack_container;
	typedef pecker_bst_tree_no_perent_node_inorder_iterator_base< BST_node_t, allocate_object_t, pointer_allocate_object_t > _Inorder_iterator;
private:
	_Stack_container _M_stack;
	const BST_node_t* _M_pBst_iterator_root;
	const BST_node_t* _M_pBst_current_node;
	bool _M_b_catch_end_flag;
	bool _M_b_catch_begin_flag;
public:
public:
	explicit 	pecker_bst_tree_no_perent_node_inorder_iterator_base(const BST_node_t* pBst_root_node = null):
	    _M_pBst_iterator_root(pBst_root_node),
		_M_b_catch_end_flag(false),
		_M_b_catch_begin_flag(true)
	{
	}
	virtual ~pecker_bst_tree_no_perent_node_inorder_iterator_base()
	{
		_M_pBst_iterator_root = null;
		_M_pBst_current_node = null;
	}	  
protected:
	pecker_bst_tree_no_perent_node_inorder_iterator_base(const _Inorder_iterator& other_iterator)
	{
		copy(&other_iterator);
	}
	pecker_bst_tree_no_perent_node_inorder_iterator_base& operator = (const _Inorder_iterator& other_iterator)
	{
		copy(&other_iterator);
		return *this;
	}
public:
	HResult init()
	{
		return init(ITERATOR_INIT_MIN);
	}

	HResult init(TREE_ITERATOR_INIT_TYPE init_type)
	{
		if (null != _M_pBst_iterator_root)
		{
			const BST_node_t* pBst_tmp_node = _M_pBst_iterator_root;
			_M_stack.clear();

			if (ITERATOR_INIT_MIN == init_type)
			{
				while (null != pBst_tmp_node)
				{
					_M_stack.push(pBst_tmp_node);
					pBst_tmp_node = pBst_tmp_node->_M_left;
				}
				_M_b_catch_begin_flag = true;
				_M_b_catch_end_flag = false;
			}
			else if (ITERATOR_INIT_MAX == init_type)
			{
				while (null != pBst_tmp_node)
				{
					_M_stack.push(pBst_tmp_node);
					pBst_tmp_node = pBst_tmp_node->_M_right;
				}
				_M_b_catch_begin_flag = false;
				_M_b_catch_end_flag = true;
			}
			else
			{
				_M_pBst_current_node = null;
				return PEK_STATUS_ERROR;
			}

			if (_M_stack.get_size() > 0)
			{
				_M_pBst_current_node = *_M_stack.get_end_reference();
				_M_stack.pop();
			}
			else
			{
				_M_pBst_current_node = null;
			}
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	HResult reinit(const BST_node_t* pBst_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_MIN)
	{
		if (null != pBst_root_node)
		{
			_M_stack.clear();
			_M_pBst_iterator_root = pBst_root_node;
			_M_pBst_current_node = null;
			if (ITERATOR_INIT_DEFAULT == init_type)
			{
				init_type = ITERATOR_INIT_MIN;
			}

			return init(init_type);
		}
		return PEK_STATUS_ERROR;
	}

	HResult copy(const _Inorder_iterator* pBst_other_iterator)
	{
		if (this == pBst_other_iterator)
		{
			return PEK_STATUS_OK;
		}
		else if (null != pBst_other_iterator)
		{
			_M_pBst_iterator_root = pBst_other_iterator->_M_pBst_iterator_root;
			_M_pBst_current_node = pBst_other_iterator->_M_pBst_current_node;
			_M_b_catch_end_flag = pBst_other_iterator->_M_b_catch_end_flag;
			_M_b_catch_begin_flag = pBst_other_iterator->_M_b_catch_begin_flag;

			_M_stack = pBst_other_iterator->_M_stack;

			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	HResult increment()
	{
		if (null == _M_pBst_current_node || true == _M_b_catch_end_flag)
		{
			return PEK_STATUS_SUCCESS;
		}

		const BST_node_t* pBst_tmp_node = _M_pBst_current_node;
		if (null == pBst_tmp_node->_M_right)
		{
			nINDEX index = _M_stack.get_size() - 1;
			while (index >= 0)
			{
				const BST_node_t* pBst_top_node = *_M_stack.get_at(index);
				if (pBst_top_node->_M_right == pBst_tmp_node)
				{
					pBst_tmp_node = pBst_top_node;
					--index;
				}
				else if (pBst_top_node->_M_left == pBst_tmp_node)
				{
					pBst_tmp_node = pBst_top_node;
					_M_stack.resize(index);
					break;
				}
				else
				{
					return PEK_STATUS_ERROR;
				}
			}
			if (index < 0)
			{
				_M_b_catch_end_flag = true;
				return PEK_STATUS_SUCCESS;
			}
			else
			{
				if (0 == index)
				{
					const BST_node_t* pBst_top_node = null;
					const BST_node_t* pBst_btn_node = null;
					nSize tmp_size = _M_stack.get_size();
					if ( tmp_size < 2)
					{
						_M_stack.resize(2);
						pBst_top_node = *_M_stack.get_at(1);
						pBst_btn_node = *_M_stack.get_at(0);
						_M_stack.resize(tmp_size);
					}
					else
					{
						pBst_top_node = *_M_stack.get_at(1);
						pBst_btn_node = *_M_stack.get_at(0);
					}
					if (pBst_btn_node->_M_right == pBst_top_node)
					{
						_M_b_catch_end_flag = true;
					}
					else
					{
						_M_b_catch_end_flag = false;
					}
				}
				else
				{
					_M_b_catch_end_flag = false;
				}
		
				_M_pBst_current_node = pBst_tmp_node;
				_M_b_catch_begin_flag = false;
				return PEK_STATUS_OK;
			}
		}
		else
		{
			_M_stack.push(pBst_tmp_node);
			pBst_tmp_node = minimum_bst_node< BST_node_t,_Stack_container >(pBst_tmp_node->_M_right,_M_stack);
			_M_stack.pop();
			_M_pBst_current_node = pBst_tmp_node;
		}
		_M_b_catch_begin_flag = false;
		return PEK_STATUS_OK;
	}

	HResult decrement()
	{
		if (null == _M_pBst_current_node || true == _M_b_catch_begin_flag)
		{
			return PEK_STATUS_SUCCESS;
		}

		const BST_node_t* pBst_tmp_node = _M_pBst_current_node;
		if (null == pBst_tmp_node->_M_left)
		{
			nINDEX index = _M_stack.get_size() - 1;
			while (index >= 0)
			{
				const BST_node_t* pBst_top_node = *_M_stack.get_at(index);
				if (pBst_top_node->_M_left  == pBst_tmp_node)
				{
					pBst_tmp_node = pBst_top_node;
					--index;
				}
				else if (pBst_top_node->_M_right == pBst_tmp_node)
				{
					pBst_tmp_node = pBst_top_node;
					_M_stack.resize(index);
					break;
				}
				else
				{
					return PEK_STATUS_ERROR;
				}
			}
			if (index < 0)
			{
				_M_b_catch_begin_flag = true;
				return PEK_STATUS_SUCCESS;
			}
			else
			{
				if (0 == index)
				{
					const BST_node_t* pBst_top_node = null;
					const BST_node_t* pBst_btn_node = null;
					nSize tmp_size = _M_stack.get_size();
					if ( tmp_size < 2)
					{
						_M_stack.resize(2);
						pBst_top_node = *_M_stack.get_at(1);
						pBst_btn_node = *_M_stack.get_at(0);
						_M_stack.resize(tmp_size);
					}
					else
					{
						pBst_top_node = *_M_stack.get_at(1);
						pBst_btn_node = *_M_stack.get_at(0);
					}
					if (pBst_btn_node->_M_left == pBst_top_node)
					{
						_M_b_catch_begin_flag = true;
					}
					else
					{
						_M_b_catch_begin_flag = false;
					}
				}
				else
				{
					_M_b_catch_begin_flag = false;
				}

				_M_pBst_current_node = pBst_tmp_node;
				_M_b_catch_end_flag = false;
				return PEK_STATUS_OK;
			}
		}
		else
		{
			_M_stack.push(pBst_tmp_node);
			pBst_tmp_node = maximum_bst_node< BST_node_t,_Stack_container >(pBst_tmp_node->_M_left,_M_stack);
			_M_stack.pop();
			_M_pBst_current_node = pBst_tmp_node;
		}
		_M_b_catch_end_flag = false;
		return PEK_STATUS_OK;
	}

	inline const BST_node_t* get_current_node() const
	{
		return _M_pBst_current_node;
	}

	inline const BST_node_t* get_root_node() const
	{
		return _M_pBst_iterator_root;
	}
};

// 无父节点的二叉树节点的后序遍历迭代器
template< class BST_node_t,
					class allocate_object_t = pecker_system_defualt_allocator( const BST_node_t* ),
					class pointer_allocate_object_t = pecker_system_defualt_allocator( const BST_node_t** ) >
class pecker_bst_tree_no_perent_node_posorder_iterator_base : public Ipecker_bst_tree_posorder_iterator< BST_node_t >
{
	typedef pecker_stack_pool_array< const BST_node_t*,allocate_object_t,pointer_allocate_object_t  > _Stack_container;
	typedef pecker_bst_tree_no_perent_node_posorder_iterator_base< BST_node_t, allocate_object_t, pointer_allocate_object_t > _Inorder_iterator;
protected:
	_Stack_container _M_stack;
	const BST_node_t* _M_pBst_iterator_root;
	const BST_node_t* _M_pBst_current_node;
public:
	explicit 	pecker_bst_tree_no_perent_node_posorder_iterator_base(const BST_node_t* pBst_root_node = null):
	_M_pBst_iterator_root(pBst_root_node),
		_M_pBst_current_node(null)
	{
	}
	virtual ~pecker_bst_tree_no_perent_node_posorder_iterator_base()
	{
		_M_pBst_iterator_root = null;
		_M_pBst_current_node = null;
	}	  
	HResult init()
	{
		return init(ITERATOR_INIT_LEFT);
	}

	HResult init(TREE_ITERATOR_INIT_TYPE init_type)
	{
		if (null != _M_pBst_iterator_root)
		{
			const  BST_node_t* pBst_tmp_node = _M_pBst_iterator_root;

			if (ITERATOR_INIT_LEFT == init_type)
			{
				while (null != pBst_tmp_node)
				{
					_M_stack.push(pBst_tmp_node);
					pBst_tmp_node = pBst_tmp_node->_M_left;
				}
				pBst_tmp_node = *_M_stack.get_end_reference();
				while (null != pBst_tmp_node->_M_right)
				{
					pBst_tmp_node = minimum_bst_node< BST_node_t,_Stack_container >(pBst_tmp_node->_M_right,_M_stack);
				}
			}
			else if (ITERATOR_INIT_RIGHT == init_type)
			{
				while (null != pBst_tmp_node)
				{
					_M_stack.push(pBst_tmp_node);
					pBst_tmp_node = pBst_tmp_node->_M_right;
				}
				pBst_tmp_node = *_M_stack.get_end_reference();
				while (null != pBst_tmp_node->_M_left)
				{
					pBst_tmp_node = maximum_bst_node< BST_node_t,_Stack_container >(pBst_tmp_node->_M_left,_M_stack);
				}
			}
			else
			{
				_M_pBst_current_node = null;
				return PEK_STATUS_ERROR;
			}

			if (_M_stack.get_size() > 0)
			{
				_M_pBst_current_node = *_M_stack.get_end_reference();
				_M_stack.pop();
			}
			else
			{
				_M_pBst_current_node = null;
			}
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	HResult reinit(const BST_node_t* pBst_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_LEFT)
	{
		if (null != pBst_root_node)
		{
			_M_pBst_iterator_root = pBst_root_node;
			_M_pBst_current_node = null;
			_M_stack.clear();

			if (ITERATOR_INIT_DEFAULT == init_type)
			{
				init_type = ITERATOR_INIT_LEFT;
			}

			return init(init_type);
		}
		return PEK_STATUS_ERROR;
	}

	HResult copy(const pecker_bst_tree_no_perent_node_posorder_iterator_base* pBst_other_iterator)
	{
		if (this == pBst_other_iterator)
		{
			return PEK_STATUS_OK;
		}
		else if (null != pBst_other_iterator)
		{
			_M_pBst_iterator_root = pBst_other_iterator->_M_pBst_iterator_root;
			_M_pBst_current_node = pBst_other_iterator->_M_pBst_current_node;
			_M_stack = pBst_other_iterator->_M_stack;

			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	HResult increment_right()
	{
		if (null == _M_pBst_current_node || _M_pBst_current_node == _M_pBst_iterator_root)
		{
			return PEK_STATUS_SUCCESS;
		}
			
		const BST_node_t* pBst_tmp_node = _M_pBst_current_node;

		if (_M_stack.get_size() > 0)
		{
			const BST_node_t* pBst_top_node = *_M_stack.get_end_reference();
			if (pBst_top_node->_M_right == pBst_tmp_node)
			{
				_M_pBst_current_node = pBst_top_node;
				_M_stack.pop();
				return PEK_STATUS_OK;
			}
			else if (pBst_top_node->_M_left == pBst_tmp_node)
			{
				pBst_tmp_node = pBst_top_node;
			}
			else
			{
				return PEK_STATUS_ERROR;
			}
		}
		else
		{
			return PEK_STATUS_SUCCESS;
		}

		while (null != pBst_tmp_node->_M_right)
		{
			pBst_tmp_node = minimum_bst_node< BST_node_t,_Stack_container >(pBst_tmp_node->_M_right,_M_stack);
		}
		_M_stack.pop();
		_M_pBst_current_node = pBst_tmp_node;
		return PEK_STATUS_OK;
	}

	HResult increment_left()
	{
		if (null == _M_pBst_current_node || _M_pBst_current_node == _M_pBst_iterator_root)
		{
			return PEK_STATUS_SUCCESS;
		}

		const BST_node_t* pBst_tmp_node = _M_pBst_current_node;

		if (_M_stack.get_size() > 0)
		{
			const BST_node_t* pBst_top_node = *_M_stack.get_end_reference();
			if (pBst_top_node->_M_left == pBst_tmp_node)
			{
				_M_pBst_current_node = pBst_top_node;
				_M_stack.pop();
				return PEK_STATUS_OK;
			}
			else if (pBst_top_node->_M_right == pBst_tmp_node)
			{
				pBst_tmp_node = pBst_top_node;
			}
			else
			{
				return PEK_STATUS_ERROR;
			}
		}
		else
		{
			return PEK_STATUS_SUCCESS;
		}

		while (null != pBst_tmp_node->_M_left)
		{
			pBst_tmp_node = maximum_bst_node< BST_node_t,_Stack_container >(pBst_tmp_node->_M_left,_M_stack);
		}
		_M_stack.pop();
		_M_pBst_current_node = pBst_tmp_node;
		return PEK_STATUS_OK;
	}

	inline const BST_node_t* get_current_node() const
	{
		return _M_pBst_current_node;
	}

	inline const BST_node_t* get_root_node() const
	{
		return _M_pBst_iterator_root;
	}
};


//  无父节点的三叉树节点的中序遍历迭代器
template< class TST_node_t,
class allocate_object_t = pecker_system_defualt_allocator( const TST_node_t* ),
class pointer_allocate_object_t = pecker_system_defualt_allocator( const TST_node_t** ) >
class pecker_tst_tree_no_perent_node_inorder_iterator_base : public Ipecker_bst_tree_inorder_iterator< TST_node_t >
{
	typedef pecker_stack_pool_array< const TST_node_t*,allocate_object_t,pointer_allocate_object_t  > _Stack_container;
	typedef pecker_tst_tree_no_perent_node_inorder_iterator_base< TST_node_t, allocate_object_t, pointer_allocate_object_t > _Inorder_iterator;
private:
	_Stack_container _M_stack;
	const TST_node_t* _M_pTst_iterator_root;
	const TST_node_t* _M_pTst_current_node;
	bool _M_b_catch_end_flag;
	bool _M_b_catch_begin_flag;
public:
	explicit 	pecker_tst_tree_no_perent_node_inorder_iterator_base(const TST_node_t* pTst_root_node = null):
	_M_pTst_iterator_root(pTst_root_node),
	_M_pTst_current_node(null),
		_M_b_catch_end_flag(false),
		_M_b_catch_begin_flag(true)
	{
	}
	virtual ~pecker_tst_tree_no_perent_node_inorder_iterator_base()
	{
		_M_pTst_iterator_root = null;
		_M_pTst_current_node = null;
	}	  
protected:
	pecker_tst_tree_no_perent_node_inorder_iterator_base(const _Inorder_iterator& other_iterator)
	{
		copy(&other_iterator);
	}
	pecker_tst_tree_no_perent_node_inorder_iterator_base& operator = (const _Inorder_iterator& other_iterator)
	{
		copy(&other_iterator);
		return *this;
	}
public:
	HResult init()
	{
		return init(ITERATOR_INIT_MIN);
	}

	HResult init(TREE_ITERATOR_INIT_TYPE init_type)
	{
		if (null != _M_pTst_iterator_root)
		{
			const TST_node_t* pTst_tmp_node = _M_pTst_iterator_root;
			_M_stack.clear();

			if (ITERATOR_INIT_MIN == init_type)
			{
				while (null != pTst_tmp_node)
				{
					_M_stack.push(pTst_tmp_node);
					pTst_tmp_node = (const TST_node_t*)(pTst_tmp_node->_M_left);
				}
				_M_b_catch_begin_flag = true;
				_M_b_catch_end_flag = false;
			}
			else if (ITERATOR_INIT_MAX == init_type)
			{
				pTst_tmp_node = maximum_tst_node(pTst_tmp_node,_M_stack);
				_M_b_catch_begin_flag = false;
				_M_b_catch_end_flag = true;
			}
			else
			{
				_M_pTst_current_node = null;
				return PEK_STATUS_ERROR;
			}

			if (_M_stack.get_size() > 0)
			{
				_M_pTst_current_node = *_M_stack.get_end_reference();
				_M_stack.pop();
			}
			else
			{
				_M_pTst_current_node = null;
			}
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	HResult reinit(const TST_node_t* pTst_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_MIN)
	{
		if (null != pTst_root_node)
		{
			_M_stack.clear();
			_M_pTst_iterator_root = pTst_root_node;
			_M_pTst_current_node = null;
			if (ITERATOR_INIT_DEFAULT == init_type)
			{
				init_type = ITERATOR_INIT_MIN;
			}

			return init(init_type);
		}
		return PEK_STATUS_ERROR;
	}

	HResult copy(const _Inorder_iterator* pTst_other_iterator)
	{
		if (this == pTst_other_iterator)
		{
			return PEK_STATUS_OK;
		}
		else if (null != pTst_other_iterator)
		{
			_M_pTst_iterator_root = pTst_other_iterator->_M_pBst_iterator_root;
			_M_pTst_current_node = pTst_other_iterator->_M_pBst_current_node;
			_M_b_catch_end_flag = pTst_other_iterator->_M_b_catch_end_flag;
			_M_b_catch_begin_flag = pTst_other_iterator->_M_b_catch_begin_flag;

			_M_stack = pTst_other_iterator->_M_stack;

			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	HResult increment()
	{
		//_M_pTst_last_node = _M_pTst_current_node;
		if (null == _M_pTst_current_node || true == _M_b_catch_end_flag)
		{
			return PEK_STATUS_SUCCESS;
		}
		const TST_node_t* pTst_tmp_node = _M_pTst_current_node;
		const TST_node_t* pTst_tmp_node_last = null;

		
		if (null != pTst_tmp_node->_M_middle_node)
		{
			_M_stack.push(pTst_tmp_node);
			_M_pTst_current_node = minimum_bst_node< TST_node_t,_Stack_container >((const TST_node_t*)(pTst_tmp_node->_M_middle_node),_M_stack);
			_M_stack.pop();
			_M_b_catch_begin_flag = false;
			return PEK_STATUS_OK;
		}
		else if (null != pTst_tmp_node->_M_right)
		{
			_M_stack.push(pTst_tmp_node);
			_M_pTst_current_node = minimum_bst_node< TST_node_t,_Stack_container >((const TST_node_t*)(pTst_tmp_node->_M_right),_M_stack);
			_M_stack.pop();

			_M_b_catch_begin_flag = false;
			return PEK_STATUS_OK;
		}

		nINDEX index = _M_stack.get_size() - 1;
		const TST_node_t* pBst_top_node;
		//boolean bis_jump_node = false;

		if (index < 0)
		{
			_M_b_catch_end_flag = true;
			return PEK_STATUS_SUCCESS;
		}

		do 
		{
			pBst_top_node = *_M_stack.get_at(index);
			if (pBst_top_node->_M_left == pTst_tmp_node)
			{
				pTst_tmp_node = pBst_top_node;
				_M_stack.resize(index);
				break;
			}
			if (pBst_top_node->_M_middle_node == pTst_tmp_node)
			{
				--index;
				if (null != pBst_top_node->_M_right && pTst_tmp_node_last != pBst_top_node->_M_right )
				{
					_M_pTst_current_node = minimum_bst_node< TST_node_t,_Stack_container >((const TST_node_t*)(pBst_top_node->_M_right),_M_stack);
					_M_stack.pop();

					_M_b_catch_begin_flag = false;
					return PEK_STATUS_OK;
				}
				pTst_tmp_node_last = pTst_tmp_node;
				pTst_tmp_node = pBst_top_node;
				//bis_jump_node = false;
				continue;
			}

			if (pBst_top_node->_M_right == pTst_tmp_node)
			{
				pTst_tmp_node_last = pTst_tmp_node;
				pTst_tmp_node = pBst_top_node;
				--index;
				//bis_jump_node = false;
				continue;
			}

			--index;
			if (index < 0)
			{
				_M_pTst_current_node = pTst_tmp_node;
				_M_b_catch_end_flag = true;
				return PEK_STATUS_SUCCESS;
			}

			while(pTst_tmp_node != pBst_top_node->_M_right)
			{
				pBst_top_node = *_M_stack.get_at(index);
				--index;
			}
			pTst_tmp_node_last = pTst_tmp_node;
			pTst_tmp_node = pBst_top_node;
			//bis_jump_node = true;
			continue;
		}while(index >= 0);

		_M_pTst_current_node = pTst_tmp_node;
		if (index < 0)
		{
			_M_b_catch_end_flag = true;
			return PEK_STATUS_SUCCESS;
		}
		return PEK_STATUS_OK;
	}

	HResult decrement()
	{
		if (null == _M_pTst_current_node || true == _M_b_catch_begin_flag)
		{
			//_M_pTst_last_node = _M_pTst_current_node;
			return PEK_STATUS_SUCCESS;
		}
		const TST_node_t* pTst_tmp_node = _M_pTst_current_node;
		const TST_node_t* pTst_tmp_node_last = null;

		
		if (null != pTst_tmp_node->_M_left)
		{
			_M_stack.push(pTst_tmp_node);
			_M_pTst_current_node = maximum_tst_node< TST_node_t,_Stack_container >((const TST_node_t*)(pTst_tmp_node->_M_left),_M_stack);
			_M_stack.pop();

			_M_b_catch_end_flag = false;
			//_M_pTst_last_node = _M_pTst_current_node;
			return PEK_STATUS_OK;
		}

		nINDEX index = _M_stack.get_size() - 1;
		const TST_node_t* pBst_top_node;
		//boolean bis_jump_node = false;

		if (index < 0)
		{
			_M_b_catch_begin_flag = true;
			//_M_pTst_last_node = _M_pTst_current_node;
			return PEK_STATUS_SUCCESS;
		}

		do 
		{
			pBst_top_node = *_M_stack.get_at(index);
			if (pBst_top_node->_M_right == pTst_tmp_node)
			{
				_M_stack.resize(index);

				if (null != pBst_top_node->_M_middle_node)
				{
					_M_stack.push(pBst_top_node);
					pTst_tmp_node = maximum_tst_node< TST_node_t,_Stack_container >((const TST_node_t*)(pBst_top_node->_M_middle_node),_M_stack);
					_M_stack.pop();
				}
				else if (null != pBst_top_node->_M_left && pTst_tmp_node_last != pTst_tmp_node->_M_left)
				{
					_M_stack.push(pBst_top_node);
					pTst_tmp_node = maximum_tst_node< TST_node_t,_Stack_container >((const TST_node_t*)(pBst_top_node->_M_left),_M_stack);
					_M_stack.pop();
				}
				else
				{
						pTst_tmp_node = pBst_top_node;
				}				
				break;
			}
			if (pBst_top_node->_M_middle_node == pTst_tmp_node)
			{
				pTst_tmp_node_last = pTst_tmp_node;
				pTst_tmp_node = pBst_top_node;
				_M_stack.resize(index);
				
				break;
			}

			if (pBst_top_node->_M_left == pTst_tmp_node)
			{
				pTst_tmp_node_last = pTst_tmp_node;
				pTst_tmp_node = pBst_top_node;
				--index;
				continue;
			}

			if (index <= 0)
			{
				_M_pTst_current_node = pTst_tmp_node;
				_M_b_catch_begin_flag = true;
				return PEK_STATUS_SUCCESS;
			}

			
			_M_stack.resize(index);
			while (  pBst_top_node->_M_right != pTst_tmp_node)
			{
				--index;
				if (index < 0)
				{
					_M_pTst_current_node = pTst_tmp_node;
					_M_b_catch_begin_flag = true;
					return PEK_STATUS_SUCCESS;
				}
				pBst_top_node = *_M_stack.get_at(index);
			}
			continue;

		}while(index >= 0);

		_M_pTst_current_node = pTst_tmp_node;
		if (index < 0)
		{
			_M_b_catch_begin_flag = true;
			return PEK_STATUS_SUCCESS;
		}
		return PEK_STATUS_OK;
	}

	inline const TST_node_t* get_current_node() const
	{
		return _M_pTst_current_node;
	}

	inline const TST_node_t* get_root_node() const
	{
		return _M_pTst_iterator_root;
	}
};


//// 无父节点的三叉树节点的后序遍历迭代器
//template< class TST_node_t,
//class allocate_object_t = pecker_simple_allocator< const TST_node_t* >,
//class pointer_allocate_object_t = pecker_simple_allocator< const TST_node_t** > >
//class pecker_tst_tree_no_perent_node_posorder_iterator_base : public Ipecker_bst_tree_posorder_iterator< TST_node_t >
//{
//	typedef pecker_stack_pool_array< const TST_node_t*,allocate_object_t,pointer_allocate_object_t  > _Stack_container;
//	typedef pecker_tst_tree_no_perent_node_posorder_iterator_base< TST_node_t, allocate_object_t, pointer_allocate_object_t > _Inorder_iterator;
//protected:
//	_Stack_container _M_stack;
//	const TST_node_t* _M_pTst_iterator_root;
//	const TST_node_t* _M_pTst_current_node;
//public:
//	explicit 	pecker_tst_tree_no_perent_node_posorder_iterator_base(const TST_node_t* pTst_root_node = null):
//	_M_pTst_iterator_root(pTst_root_node),
//		_M_pTst_current_node(null)
//	{
//	}
//	virtual ~pecker_tst_tree_no_perent_node_posorder_iterator_base()
//	{
//		_M_pTst_iterator_root = null;
//		_M_pTst_current_node = null;
//	}	  
//	HResult init()
//	{
//		return init(ITERATOR_INIT_LEFT);
//	}
//
//	HResult init(TREE_ITERATOR_INIT_TYPE init_type)
//	{
//		if (null != _M_pTst_iterator_root)
//		{
//			//const  TST_node_t* pBst_tmp_node = _M_pTst_iterator_root;
//
//			if (ITERATOR_INIT_LEFT == init_type)
//			{
//				_M_pTst_current_node = leftmost_tst_node< TST_node_t,_Stack_container >(_M_pTst_iterator_root,_M_stack);
//				//while (null != pBst_tmp_node)
//				//{
//				//	_M_stack.push(pBst_tmp_node);
//				//	pBst_tmp_node = pBst_tmp_node->_M_left;
//				//}
//				//pBst_tmp_node = *_M_stack.get_end_reference();
//				//while (null != pBst_tmp_node->_M_right)
//				//{
//				//	pBst_tmp_node = minimum_bst_node< TST_node_t,_Stack_container >(pBst_tmp_node->_M_right,_M_stack);
//				//}
//			}
//			else if (ITERATOR_INIT_RIGHT == init_type)
//			{
//				_M_pTst_current_node = maximum_tst_node< TST_node_t,_Stack_container >(_M_pTst_iterator_root,_M_stack);
//				//while (null != pBst_tmp_node)
//				//{
//				//	_M_stack.push(pBst_tmp_node);
//				//	pBst_tmp_node = pBst_tmp_node->_M_right;
//				//}
//				//pBst_tmp_node = *_M_stack.get_end_reference();
//				//while (null != pBst_tmp_node->_M_left)
//				//{
//				//	pBst_tmp_node = maximum_bst_node< TST_node_t,_Stack_container >(pBst_tmp_node->_M_left,_M_stack);
//				//}
//			}
//			else
//			{
//				_M_pTst_current_node = null;
//				return P_ERR;
//			}
//			return P_OK;
//		}
//		return P_ERR;
//	}
//
//	HResult reinit(const TST_node_t* pBst_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_LEFT)
//	{
//		if (null != pBst_root_node)
//		{
//			_M_pTst_iterator_root = pBst_root_node;
//			_M_pTst_current_node = null;
//			_M_stack.clear();
//
//			if (ITERATOR_INIT_DEFAULT == init_type)
//			{
//				init_type = ITERATOR_INIT_LEFT;
//			}
//
//			return init(init_type);
//		}
//		return P_ERR;
//	}
//
//	HResult copy(const pecker_bst_tree_no_perent_node_posorder_iterator_base* pBst_other_iterator)
//	{
//		if (this == pBst_other_iterator)
//		{
//			return P_OK;
//		}
//		else if (null != pBst_other_iterator)
//		{
//			_M_pTst_iterator_root = pBst_other_iterator->_M_pBst_iterator_root;
//			_M_pTst_current_node = pBst_other_iterator->_M_pBst_current_node;
//			_M_stack = pBst_other_iterator->_M_stack;
//
//			return P_OK;
//		}
//		return P_ERR;
//	}
//
//	inline HResult increment_right()
//	{
//		if (null == _M_pTst_current_node || _M_pTst_current_node == _M_pTst_iterator_root)
//		{
//			return P_SUCCESS;
//		}
//
//		const TST_node_t* pBst_tmp_node = _M_pTst_current_node;
//
//		if (_M_stack.get_size() > 0)
//		{
//			const TST_node_t* pBst_top_node = *_M_stack.get_end_reference();
//			if (pBst_top_node->_M_right == pBst_tmp_node)
//			{
//				_M_pTst_current_node = pBst_top_node;
//				_M_stack.pop();
//				return P_OK;
//			}
//			else if (pBst_top_node->_M_left == pBst_tmp_node)
//			{
//				pBst_tmp_node = pBst_top_node;
//			}
//			else
//			{
//				return P_ERR;
//			}
//		}
//		else
//		{
//			return P_SUCCESS;
//		}
//
//		while (null != pBst_tmp_node->_M_right)
//		{
//			pBst_tmp_node = minimum_bst_node< TST_node_t,_Stack_container >(pBst_tmp_node->_M_right,_M_stack);
//		}
//		_M_stack.pop();
//		_M_pTst_current_node = pBst_tmp_node;
//		return P_OK;
//	}
//
//	inline HResult increment_left()
//	{
//		if (null == _M_pTst_current_node || _M_pTst_current_node == _M_pTst_iterator_root)
//		{
//			return P_SUCCESS;
//		}
//
//		const TST_node_t* pBst_tmp_node = _M_pTst_current_node;
//
//		if (_M_stack.get_size() > 0)
//		{
//			const TST_node_t* pBst_top_node = *_M_stack.get_end_reference();
//			if (pBst_top_node->_M_left == pBst_tmp_node)
//			{
//				_M_pTst_current_node = pBst_top_node;
//				_M_stack.pop();
//				return P_OK;
//			}
//			else if (pBst_top_node->_M_right == pBst_tmp_node)
//			{
//				pBst_tmp_node = pBst_top_node;
//			}
//			else
//			{
//				return P_ERR;
//			}
//		}
//		else
//		{
//			return P_SUCCESS;
//		}
//
//		while (null != pBst_tmp_node->_M_left)
//		{
//			pBst_tmp_node = maximum_bst_node< TST_node_t,_Stack_container >(pBst_tmp_node->_M_left,_M_stack);
//		}
//		_M_stack.pop();
//		_M_pTst_current_node = pBst_tmp_node;
//		return P_OK;
//	}
//
//	inline const TST_node_t* get_current_node() const
//	{
//		return _M_pTst_current_node;
//	}
//
//	inline const TST_node_t* get_root_node() const
//	{
//		return _M_pTst_iterator_root;
//	}
//};
PECKER_END

#endif