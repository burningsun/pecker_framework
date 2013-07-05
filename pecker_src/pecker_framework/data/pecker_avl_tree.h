/*
 *  pecker_avl_tree.h
 *
 *  Created on: 2012-11-3
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_AVL_TREE_H_
#define PECKER_AVL_TREE_H_

//#ifndef AVL_DEBUG_CODE
//#define  AVL_DEBUG_CODE
//#endif

#include "../pecker_reference.h"
#include "pecker_iterator.h"
#include "pecker_bst_iterator.h"
#include "pecker_avl_tree_algorithm.h"
#include "pecker_nodes_allocate.h"


//#ifdef AVL_DEBUG_CODE
//#include <iostream>
//#endif

PECKER_BEGIN

typedef bool Avl_tree_boolean_flag;
#define  AVL_TREE_BOOLEAN_TRUE	true
#define  AVL_TREE_BOOLEAN_FLASE	false

//PeckerInterface Ipecker_avl_tree_iterator
//{
//	virtual ~Ipecker_avl_tree_iterator(){;}
//	virtual avl_result init() = 0;
//	virtual avl_result init(TREE_ITERATOR_INIT_TYPE init_type) = 0;
//	virtual avl_result reinit(const _AVL_node_base* pAvl_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_DEFAULT) = 0;
//	virtual const _AVL_node_base* get_current_node() const = 0;
//	virtual const _AVL_node_base* get_root_node() const = 0;
//};
typedef Ipecker_bst_tree_iterator< _AVL_node_base > Ipecker_avl_tree_iterator;

// AVL树中序遍历迭代器，（数据从小到大）
class pecker_avl_tree_inorder_iterator_base : public Ipecker_bst_tree_inorder_iterator< _AVL_node_base >
{
protected:
	const _AVL_node_base* _M_Avl_node_stack[AVL_MAX_HEIGHT];
	_Avl_height		_M_Avl_node_stack_size;
	const _AVL_node_base* _M_pAvl_iterator_root;
	const _AVL_node_base* _M_pAvl_current_node;
	Avl_tree_boolean_flag _M_b_catch_end_flag;
	Avl_tree_boolean_flag _M_b_catch_begin_flag;
public:
explicit 	pecker_avl_tree_inorder_iterator_base(const _AVL_node_base* pAvl_root_node = null):
	  _M_pAvl_iterator_root(pAvl_root_node),
	  _M_b_catch_end_flag(AVL_TREE_BOOLEAN_FLASE),
	  _M_b_catch_begin_flag(AVL_TREE_BOOLEAN_TRUE),
	  _M_pAvl_current_node(null),
	  _M_Avl_node_stack_size(0)
	{
	}
	 virtual ~pecker_avl_tree_inorder_iterator_base()
	  {
		  _M_Avl_node_stack_size = 0;
		  _M_pAvl_iterator_root = 0;
		  _M_pAvl_current_node = 0;
	  }	  
protected:
	pecker_avl_tree_inorder_iterator_base(const pecker_avl_tree_inorder_iterator_base& other_iterator)
	{
		copy(&other_iterator);
	}
	pecker_avl_tree_inorder_iterator_base& operator = (const pecker_avl_tree_inorder_iterator_base& other_iterator)
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
		if (null != _M_pAvl_iterator_root)
		{
			_M_Avl_node_stack_size = 0;
			const _AVL_node_base* pAvl_tmp_node = _M_pAvl_iterator_root;

			if (ITERATOR_INIT_MIN == init_type)
			{
				while (null != pAvl_tmp_node)
				{
					_M_Avl_node_stack[_M_Avl_node_stack_size++] = pAvl_tmp_node;
					pAvl_tmp_node = pAvl_tmp_node->_M_left;
				}
				_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_TRUE;
				_M_b_catch_end_flag = AVL_TREE_BOOLEAN_FLASE;
			}
			else if (ITERATOR_INIT_MAX == init_type)
			{
				while (null != pAvl_tmp_node)
				{
					_M_Avl_node_stack[_M_Avl_node_stack_size++] = pAvl_tmp_node;
					pAvl_tmp_node = pAvl_tmp_node->_M_right;
				}
				_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_FLASE;
				_M_b_catch_end_flag = AVL_TREE_BOOLEAN_TRUE;
			}
			else
			{
				_M_pAvl_current_node = null;
				return PEK_STATUS_ERROR;
			}

			if (_M_Avl_node_stack_size > 0)
			{
				_M_pAvl_current_node = _M_Avl_node_stack[--_M_Avl_node_stack_size]; 
			}
			else
			{
				_M_pAvl_current_node = null;
			}
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	HResult reinit(const _AVL_node_base* pAvl_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_MIN)
	{
		if (null != pAvl_root_node)
		{
			_M_pAvl_iterator_root = pAvl_root_node;
			_M_pAvl_current_node = null;
			_M_Avl_node_stack_size = 0;
			if (ITERATOR_INIT_DEFAULT == init_type)
			{
				init_type = ITERATOR_INIT_MIN;
			}

			return init(init_type);
		}
		return PEK_STATUS_ERROR;
	}

	HResult copy(const pecker_avl_tree_inorder_iterator_base* pAvl_other_iterator)
	{
		if (this == pAvl_other_iterator)
		{
			return PEK_STATUS_OK;
		}
		else if (null != pAvl_other_iterator)
		{
			_M_pAvl_iterator_root = pAvl_other_iterator->_M_pAvl_iterator_root;
			_M_pAvl_current_node = pAvl_other_iterator->_M_pAvl_current_node;
			_M_Avl_node_stack_size = pAvl_other_iterator->_M_Avl_node_stack_size;
			_M_b_catch_end_flag = pAvl_other_iterator->_M_b_catch_end_flag;
			_M_b_catch_begin_flag = pAvl_other_iterator->_M_b_catch_begin_flag;

			for (avl_array_index_val index = 0; index < _M_Avl_node_stack_size; ++index)
			{
				_M_Avl_node_stack[index] = pAvl_other_iterator->_M_Avl_node_stack[index];
			}

			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	inline HResult increment()
	{
		if (null == _M_pAvl_current_node || AVL_TREE_BOOLEAN_TRUE == _M_b_catch_end_flag)
		{
			return PEK_STATUS_SUCCESS;
		}

		const _AVL_node_base* pAvl_tmp_node = _M_pAvl_current_node;
		if (null == pAvl_tmp_node->_M_right)
		{
			avl_array_index_val index = _M_Avl_node_stack_size - 1;
			while(index >=0)
			{
				if (_M_Avl_node_stack[index]->_M_right == pAvl_tmp_node)
				{
					pAvl_tmp_node = _M_Avl_node_stack[index--];
				}
				else if (_M_Avl_node_stack[index]->_M_left == pAvl_tmp_node)
				{
					_M_Avl_node_stack_size = index;
					pAvl_tmp_node = _M_Avl_node_stack[index];
					break;
				}
				else
				{
					return PEK_STATUS_ERROR;
				}
			}
			if (index < 0)
			{
				_M_b_catch_end_flag = AVL_TREE_BOOLEAN_TRUE;
				return PEK_STATUS_SUCCESS;
			}
			else
			{
				if (0 == index && _M_Avl_node_stack[0]->_M_right == _M_Avl_node_stack[1])
				{
					_M_b_catch_end_flag = AVL_TREE_BOOLEAN_TRUE;
				}
				else
				{
					_M_b_catch_end_flag = AVL_TREE_BOOLEAN_FLASE;
				}
				_M_pAvl_current_node = pAvl_tmp_node;
				_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_FLASE;
				return PEK_STATUS_OK;
			}
		}
		else
		{
			_M_Avl_node_stack[_M_Avl_node_stack_size++] = pAvl_tmp_node;
			pAvl_tmp_node = minimum_bst_node(pAvl_tmp_node->_M_right,_M_Avl_node_stack,_M_Avl_node_stack_size);
			--_M_Avl_node_stack_size;
			_M_pAvl_current_node = pAvl_tmp_node;
		}
		_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_FLASE;
		return PEK_STATUS_OK;
	}

	inline HResult decrement()
	{
		if (null == _M_pAvl_current_node || AVL_TREE_BOOLEAN_TRUE == _M_b_catch_begin_flag)
		{
			return PEK_STATUS_SUCCESS;
		}

		const _AVL_node_base* pAvl_tmp_node = _M_pAvl_current_node;
		if (null == pAvl_tmp_node->_M_left)
		{
			avl_array_index_val index = _M_Avl_node_stack_size - 1;
			while(index >=0)
			{
				if (_M_Avl_node_stack[index]->_M_left == pAvl_tmp_node)
				{
					pAvl_tmp_node = _M_Avl_node_stack[index--];
				}
				else if (_M_Avl_node_stack[index]->_M_right == pAvl_tmp_node)
				{
					_M_Avl_node_stack_size = index;
					pAvl_tmp_node = _M_Avl_node_stack[index];
					break;
				}
				else
				{
					return PEK_STATUS_ERROR;
				}
			}
			if (index < 0)
			{
				_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_TRUE;
				return PEK_STATUS_SUCCESS;
			}
			else
			{
				if (0 == index && _M_Avl_node_stack[0]->_M_left == _M_Avl_node_stack[1])
				{
					_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_TRUE;
				}
				else
				{
					_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_FLASE;
				}
				_M_pAvl_current_node = pAvl_tmp_node;
				_M_b_catch_end_flag = AVL_TREE_BOOLEAN_FLASE;
				return PEK_STATUS_OK;
			}
		}
		else
		{
			_M_Avl_node_stack[_M_Avl_node_stack_size++] = pAvl_tmp_node;
			pAvl_tmp_node = maximum_bst_node(pAvl_tmp_node->_M_left,_M_Avl_node_stack,_M_Avl_node_stack_size);
			--_M_Avl_node_stack_size;
			_M_pAvl_current_node = pAvl_tmp_node;
		}
		_M_b_catch_end_flag = AVL_TREE_BOOLEAN_FLASE;
		return PEK_STATUS_OK;
	}

	inline const _AVL_node_base* get_current_node() const
	{
		return _M_pAvl_current_node;
	}

	inline const _AVL_node_base* get_root_node() const
	{
		return _M_pAvl_iterator_root;
	}
};

// 
template<class key_t, class cmp_t, class __AVL_node_t>
class pecker_avl_tree_inorder_iterator : public  pecker_avl_tree_inorder_iterator_base
{
private:
	cmp_t _M_compare;
public:
	HResult _M_add_error_code;
public:
	explicit 	pecker_avl_tree_inorder_iterator(const __AVL_node_t* pAvl_root_node = null):
	         pecker_avl_tree_inorder_iterator_base(pAvl_root_node)
	{
	}
	virtual ~pecker_avl_tree_inorder_iterator()
	{
	}
	HResult set_current_node(const __AVL_node_t* pAvl_current_node)
	{
		if (null  != pAvl_current_node && bst_tree_find< key_t, __AVL_node_t, cmp_t > (_M_pAvl_iterator_root,pAvl_current_node->key, _M_compare))
		{
			_M_Avl_node_stack_size = 0;
			const __AVL_node_t* pAvl_tmp_node = _M_pAvl_iterator_root;
			
			while (null != pAvl_tmp_node)
			{
				int cmp_result = _M_compare(pAvl_current_node->key,pAvl_tmp_node->key);
				if (cmp_result < 0)
				{
					_M_Avl_node_stack[_M_Avl_node_stack_size++] = pAvl_tmp_node;
					pAvl_tmp_node = (const __AVL_node_t*)(pAvl_tmp_node->_M_left);
				}
				else if (cmp_result > 0)
				{
					_M_Avl_node_stack[_M_Avl_node_stack_size++] = pAvl_tmp_node;
					pAvl_tmp_node = (const __AVL_node_t*)(pAvl_tmp_node->_M_right);
				}
				else
				{
					_M_pAvl_current_node = pAvl_tmp_node;
					break;
				}
			}
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}
};

// AVL树后序遍历,(左右中)
class pecker_avl_tree_posorder_iterator_base  : public Ipecker_bst_tree_posorder_iterator< _AVL_node_base >
{
protected:
	const _AVL_node_base* _M_Avl_node_stack[AVL_MAX_HEIGHT];
	_Avl_height		_M_Avl_node_stack_size;
	const _AVL_node_base* _M_pAvl_iterator_root;
	const _AVL_node_base* _M_pAvl_current_node;
	//Avl_tree_boolean_flag _M_b_catch_end_flag;
	//Avl_tree_boolean_flag _M_b_catch_begin_flag;
public:
	explicit 	pecker_avl_tree_posorder_iterator_base(const _AVL_node_base* pAvl_root_node = null):
	_M_pAvl_iterator_root(pAvl_root_node),
		//_M_b_catch_end_flag(AVL_TREE_BOOLEAN_FLASE),
		//_M_b_catch_begin_flag(AVL_TREE_BOOLEAN_TRUE),
		_M_pAvl_current_node(null),
		_M_Avl_node_stack_size(0)
	{
	}
	virtual ~pecker_avl_tree_posorder_iterator_base()
	{
		_M_Avl_node_stack_size = 0;
		_M_pAvl_iterator_root = 0;
		_M_pAvl_current_node = 0;
	}	  
	HResult init()
	{
		return init(ITERATOR_INIT_LEFT);
	}

	HResult init(TREE_ITERATOR_INIT_TYPE init_type)
	{
		if (null != _M_pAvl_iterator_root)
		{
			_M_Avl_node_stack_size = 0;
			const _AVL_node_base* pAvl_tmp_node = _M_pAvl_iterator_root;

			if (ITERATOR_INIT_LEFT == init_type)
			{
				while (null != pAvl_tmp_node)
				{
					_M_Avl_node_stack[_M_Avl_node_stack_size++] = pAvl_tmp_node;
					pAvl_tmp_node = pAvl_tmp_node->_M_left;
				}
				pAvl_tmp_node = _M_Avl_node_stack[_M_Avl_node_stack_size-1]; 
				while (null != pAvl_tmp_node->_M_right)
				{
					pAvl_tmp_node = minimum_bst_node(pAvl_tmp_node->_M_right,_M_Avl_node_stack,_M_Avl_node_stack_size);
				}
				//_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_TRUE;
				//_M_b_catch_end_flag = AVL_TREE_BOOLEAN_FLASE;
			}
			else if (ITERATOR_INIT_RIGHT == init_type)
			{
				while (null != pAvl_tmp_node)
				{
					_M_Avl_node_stack[_M_Avl_node_stack_size++] = pAvl_tmp_node;
					pAvl_tmp_node = pAvl_tmp_node->_M_right;
				}
				pAvl_tmp_node = _M_Avl_node_stack[_M_Avl_node_stack_size-1]; 
				while (null != pAvl_tmp_node->_M_left)
				{
					pAvl_tmp_node = maximum_bst_node(pAvl_tmp_node->_M_left,_M_Avl_node_stack,_M_Avl_node_stack_size);
				}
				//_M_b_catch_begin_flag = AVL_TREE_BOOLEAN_TRUE;
				//_M_b_catch_end_flag = AVL_TREE_BOOLEAN_FLASE;
			}
			else
			{
				_M_pAvl_current_node = null;
				return PEK_STATUS_ERROR;
			}

			if (_M_Avl_node_stack_size > 0)
			{
				_M_pAvl_current_node = _M_Avl_node_stack[--_M_Avl_node_stack_size]; 
			}
			else
			{
				_M_pAvl_current_node = null;
			}
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	HResult reinit(const _AVL_node_base* pAvl_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_LEFT)
	{
		if (null != pAvl_root_node)
		{
			_M_pAvl_iterator_root = pAvl_root_node;
			_M_pAvl_current_node = null;
			_M_Avl_node_stack_size = 0;

			if (ITERATOR_INIT_DEFAULT == init_type)
			{
				init_type = ITERATOR_INIT_LEFT;
			}

			return init(init_type);
		}
		return PEK_STATUS_ERROR;
	}

	HResult copy(const pecker_avl_tree_posorder_iterator_base* pAvl_other_iterator)
	{
		if (this == pAvl_other_iterator)
		{
			return PEK_STATUS_OK;
		}
		else if (null != pAvl_other_iterator)
		{
			_M_pAvl_iterator_root = pAvl_other_iterator->_M_pAvl_iterator_root;
			_M_pAvl_current_node = pAvl_other_iterator->_M_pAvl_current_node;
			_M_Avl_node_stack_size = pAvl_other_iterator->_M_Avl_node_stack_size;
			//_M_b_catch_end_flag = pAvl_other_iterator->_M_b_catch_end_flag;
			//_M_b_catch_begin_flag = pAvl_other_iterator->_M_b_catch_begin_flag;

			for (avl_array_index_val index = 0; index < _M_Avl_node_stack_size; ++index)
			{
				_M_Avl_node_stack[index] = pAvl_other_iterator->_M_Avl_node_stack[index];
			}

			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	inline HResult increment_right()
	{
		if (null == _M_pAvl_current_node || _M_pAvl_current_node == _M_pAvl_iterator_root)
		{
			return PEK_STATUS_SUCCESS;
		}
		avl_array_index_val index = _M_Avl_node_stack_size - 1;
		const _AVL_node_base* pAvl_tmp_node = _M_pAvl_current_node;

		if (index >= 0)
		{
			if (_M_Avl_node_stack[index]->_M_right == pAvl_tmp_node)
			{
				_M_pAvl_current_node = _M_Avl_node_stack[index];
				--_M_Avl_node_stack_size;
				return PEK_STATUS_OK;
			}
			else if (_M_Avl_node_stack[index]->_M_left == pAvl_tmp_node)
			{
				pAvl_tmp_node = _M_Avl_node_stack[index];
				//--_M_Avl_node_stack_size;
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

		//while (null != pAvl_tmp_node->_M_left)
		//{
		//	pAvl_tmp_node = maximum_bst_node(pAvl_tmp_node->_M_left,_M_Avl_node_stack,_M_Avl_node_stack_size);
		//}

		while (null != pAvl_tmp_node->_M_right)
		{
			pAvl_tmp_node = minimum_bst_node(pAvl_tmp_node->_M_right,_M_Avl_node_stack,_M_Avl_node_stack_size);
		}
		--_M_Avl_node_stack_size;
		_M_pAvl_current_node = pAvl_tmp_node;
		return PEK_STATUS_OK;
	}

	inline HResult increment_left()
	{
		if (null == _M_pAvl_current_node || _M_pAvl_current_node == _M_pAvl_iterator_root)
		{
			return PEK_STATUS_SUCCESS;
		}
		avl_array_index_val index = _M_Avl_node_stack_size - 1;
		const _AVL_node_base* pAvl_tmp_node = _M_pAvl_current_node;

		if (index >= 0)
		{
			if (_M_Avl_node_stack[index]->_M_left == pAvl_tmp_node)
			{
				_M_pAvl_current_node = _M_Avl_node_stack[index];
				--_M_Avl_node_stack_size;
				return PEK_STATUS_OK;
			}
			else if (_M_Avl_node_stack[index]->_M_right == pAvl_tmp_node)
			{
				pAvl_tmp_node = _M_Avl_node_stack[index];
				//--_M_Avl_node_stack_size;
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

		//while (null != pAvl_tmp_node->_M_left)
		//{
		//	pAvl_tmp_node = maximum_bst_node(pAvl_tmp_node->_M_left,_M_Avl_node_stack,_M_Avl_node_stack_size);
		//}

		while (null != pAvl_tmp_node->_M_left)
		{
			pAvl_tmp_node = maximum_bst_node(pAvl_tmp_node->_M_left,_M_Avl_node_stack,_M_Avl_node_stack_size);
		}
		--_M_Avl_node_stack_size;
		_M_pAvl_current_node = pAvl_tmp_node;
		return PEK_STATUS_OK;
	}

	inline const _AVL_node_base* get_current_node() const
	{
		return _M_pAvl_current_node;
	}

	inline const _AVL_node_base* get_root_node() const
	{
		return _M_pAvl_iterator_root;
	}
};


template<class key_t, class cmp_t, class __AVL_node_t,class nodes_allocator_t>
class pecker_avl_tree_set_container
{
	typedef pecker_avl_tree_set_container<key_t, cmp_t, __AVL_node_t,nodes_allocator_t> _AVL_set_container;
	typedef pecker_avl_tree_inorder_iterator_base		_Tree_inoder_iterator;
	typedef pecker_avl_tree_posorder_iterator_base	_Tree_posoder_iterator;
	typedef Ipecker_avl_tree_iterator _Tree_iterator;
private:
	__AVL_node_t* _M_root_node;
	nodes_allocator_t	_M_allocator;
	cmp_t _M_compare;
	avl_node_count_val _M_node_count;
public:
	pecker_avl_tree_set_container():_M_root_node(null),_M_node_count(0)
	{
	}
	pecker_avl_tree_set_container(const _AVL_set_container& other)
	{
		if (&other != this)
		{
			_M_root_node = null;
			this->copy(other);
		}
	}

	_AVL_set_container& operator = (const _AVL_set_container& other)
	{
		if (&other != this)
		{
			this->copy(other);
		}
		return *this;
	}
	~pecker_avl_tree_set_container()
	{
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(AVL_TREE_BOOLEAN_TRUE);
			_M_root_node = null;
			_M_node_count = 0;
		}
		else
		{
			erase_all_nodes();
		}
	}
protected:
	avl_result erase_all_nodes()
	{
		_Tree_posoder_iterator this_iterator(_M_root_node);
		_M_root_node = null;
		_M_node_count = 0;

		this_iterator.init();
		//this_iterator.init(ITERATOR_INIT_RIGHT);

		while(1)
		{
			__AVL_node_t* perase_node = (__AVL_node_t*)(this_iterator.get_current_node());
			avl_result result_ = this_iterator.increment_right();
			//avl_result result_ = this_iterator.increment_left();
			if (PEK_STATUS_OK == result_)
			{
//#ifdef AVL_DEBUG_CODE
//				std::cout << "release node = "<<perase_node->key<<std::endl;
//#endif
				_M_allocator.release_node(perase_node);
			}
			else  if (PEK_STATUS_SUCCESS == result_)
			{
//#ifdef AVL_DEBUG_CODE
//				std::cout << "release node = "<<perase_node->key<<std::endl;
//#endif
				_M_allocator.release_node(perase_node);
				break;
			}
			else
			{
//#ifdef AVL_DEBUG_CODE
//				std::cout << "release errors =  error"<<std::endl;
//#endif
				break;
			}
			
		}
		return PEK_STATUS_OK;
	}
	nodes_allocator_t &get_nodes_allocater() 
	{
		return _M_allocator;
	}
public:
	avl_result copy(const _AVL_set_container* other)
	{
		if (null == other)
		{
			return PEK_STATUS_ERROR;
		}
		if (other == this)
		{
			return PEK_STATUS_OK;
		}
		//clear(AVL_TREE_BOOLEAN_TRUE);
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(AVL_TREE_BOOLEAN_FLASE);
			_M_root_node = null;
			_M_node_count = 0;
		}
		typedef bst_node_allocator< __AVL_node_t,nodes_allocator_t > _Pool_allocator;
		_Pool_allocator fast_allocator(&_M_allocator);

		_Tree_posoder_iterator this_iterator(_M_root_node);
		avl_node_count_val icount = 0;
		_M_root_node = null;
		_M_node_count = 0;

		this_iterator.init();
		while(icount < other->get_node_count())
		{
			__AVL_node_t* perase_node = (__AVL_node_t*)(this_iterator.get_current_node());
			avl_result result_ = this_iterator.increment_right();

			++icount;
			if (PEK_STATUS_OK == result_)
			{
				fast_allocator.release_node(perase_node);
			}
			else  if (PEK_STATUS_SUCCESS == result_)
			{
				fast_allocator.release_node(perase_node);
				break;
			}
			else
			{
				break;
			}

		}

		const _AVL_node_base* pAvl_node_stack[AVL_MAX_HEIGHT];
		__AVL_node_t** pAvl_copy_node_ref_stack[AVL_MAX_HEIGHT];

		_Avl_height		nAvl_node_stack_size = 0;
		const _AVL_node_base* ptemp_node = other->_M_root_node;
		
		__AVL_node_t** ptemp_copy_node = &_M_root_node;

		while (ptemp_node)
		{
			__AVL_node_t* pcopy_node = fast_allocator.create_node();
			
			if (null != pcopy_node)
			{
				*pcopy_node = *((__AVL_node_t*)ptemp_node);
				//pcopy_node->key = ((__AVL_node_t*)ptemp_node)->key;
				//pcopy_node->_M_height = ptemp_node->_M_height;
				pcopy_node->_M_left = null;
				pcopy_node->_M_right = null;
				

#ifdef AVL_DEBUG_CODE
				pcopy_node->teststr = ptemp_node->teststr;
#endif
			}
			else
			{
				clear(AVL_TREE_BOOLEAN_TRUE);

				while(1)
				{
					__AVL_node_t* perase_node = (__AVL_node_t*)(this_iterator.get_current_node());
					avl_result result_ = this_iterator.increment_right();

					++icount;
					if (PEK_STATUS_OK == result_)
					{
						_M_allocator.release_node(perase_node);
					}
					else  if (PEK_STATUS_SUCCESS == result_)
					{
						_M_allocator.release_node(perase_node);
						break;
					}
					else
					{
						break;
					}

				}

				return PEK_STATUS_ERROR;
			}

			*ptemp_copy_node = pcopy_node;


			if (ptemp_node->_M_right)
			{
				pAvl_copy_node_ref_stack[nAvl_node_stack_size] = (__AVL_node_t**)&(pcopy_node->_M_right);
				pAvl_node_stack[nAvl_node_stack_size++] = ptemp_node->_M_right;
				
			}
			if (ptemp_node->_M_left)
			{
				ptemp_node = ptemp_node->_M_left;
				ptemp_copy_node =  (__AVL_node_t**)&(pcopy_node->_M_left);
			}
			else
			{
				if (nAvl_node_stack_size <= 0)
				{
					break;
				}
				else
				{
					ptemp_node = pAvl_node_stack[--nAvl_node_stack_size];
					ptemp_copy_node = pAvl_copy_node_ref_stack[nAvl_node_stack_size];
				}
			}
		}
		_M_node_count = other->_M_node_count;

		while(1)
		{
			__AVL_node_t* perase_node = (__AVL_node_t*)(this_iterator.get_current_node());
			avl_result result_ = this_iterator.increment_right();

			++icount;
			if (PEK_STATUS_OK == result_)
			{
				_M_allocator.release_node(perase_node);
			}
			else  if (PEK_STATUS_SUCCESS == result_)
			{
				_M_allocator.release_node(perase_node);
				break;
			}
			else
			{
				break;
			}

		}
		return PEK_STATUS_OK;
	}
	avl_result clear(Avl_tree_boolean_flag bForce_release = AVL_TREE_BOOLEAN_FLASE)
	{
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(bForce_release);
			_M_root_node = null;
			_M_node_count = 0;
		}
		else
		{
			_AVL_set_container swap_for_release_tree;
			swap_for_release_tree._M_root_node = this->_M_root_node;
			swap_for_release_tree._M_node_count = this->_M_node_count;
			this->_M_root_node = 0;
			this->_M_node_count = 0;
		}

		return PEK_STATUS_OK;
	}	

	inline const __AVL_node_t* get_root() const
	{
		return _M_root_node;
	}

	inline avl_node_count_val get_node_count() const
	{
		return _M_node_count;
	}

	avl_result insert(const key_t& key)
	{
		__AVL_node_t* newnode = _M_allocator.create_node();
		if (null != newnode)
		{
			newnode->key = key;

//#ifdef AVL_DEBUG_CODE
//			newnode->teststr = key;
//#endif
		}
		avl_result add_error_code;
		avl_tree_add<key_t,cmp_t,__AVL_node_t>(_M_root_node,newnode,_M_compare,add_error_code);
		if (PEK_STATUS_OK == add_error_code)
		{
			++_M_node_count;
		}
		return add_error_code;
	}

	const __AVL_node_t* findnode(const key_t & key) const
	{
		return bst_tree_find<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare);
	}

	const key_t* find(const key_t &key) const
	{
		const __AVL_node_t* pfind_node = bst_tree_find<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare);
		if (null != pfind_node)
		{
			return &(pfind_node->key);
		}
		return null;
	}

	avl_result erase(const key_t key)
	{
		avl_result remove_error_code;
		__AVL_node_t* erase_node = avl_tree_remove<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare,remove_error_code);
		if (erase_node)
		{
			--_M_node_count;
			_M_allocator.release_node(erase_node);
			erase_node = null;
		}
		return remove_error_code;
	}

	avl_result replace(const key_t key,const key_t newkey)
	{
		avl_result remove_error_code;
		__AVL_node_t* erase_node = avl_tree_remove<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare,remove_error_code);
		if (erase_node)
		{
			avl_result add_error_code;
			erase_node->key = key;
			avl_tree_add<key_t,cmp_t,__AVL_node_t>(_M_root_node,erase_node,_M_compare,add_error_code);
			if (PEK_STATUS_OK != add_error_code)
			{
				--_M_node_count;
			}
			return add_error_code;
		}
		else
		{
			return remove_error_code;
		}
		
	}

	inline _Tree_iterator* get_iterator(_Tree_iterator* PARAM_INOUT pIterator) const
	{
		if (pIterator)
		{
			pIterator->reinit(static_cast< _AVL_node_base* >(_M_root_node));
		}
		return pIterator;
	}

	inline const key_t* get_at(const _Tree_iterator* PARAM_IN pIterator) const
	{
		if (pIterator && _M_root_node == pIterator->get_root_node())
		{
			const __AVL_node_t* pnode = (const __AVL_node_t*)(pIterator->get_current_node());
			if (pnode)
			{
				return &(pnode->key);
			}
		}

		return null;
	}

	inline const __AVL_node_t* get_node(const _Tree_iterator* PARAM_IN pIterator) const
	{
		if (pIterator && _M_root_node == pIterator->get_root_node())
		{
			return  (const __AVL_node_t*)(pIterator->get_current_node());
		}
		return null;
	}
};

template< class key_t, class value_t, class cmp_t, class __AVL_node_t,class nodes_allocator_t >
class pecker_avl_tree_map_container
{
	typedef pecker_avl_tree_map_container< key_t, value_t,cmp_t, __AVL_node_t,nodes_allocator_t > _AVL_map_container;
	typedef pecker_avl_tree_inorder_iterator_base		_Tree_inoder_iterator;
	typedef pecker_avl_tree_posorder_iterator_base	_Tree_posoder_iterator;
	typedef Ipecker_avl_tree_iterator _Tree_iterator;
private:
	__AVL_node_t* _M_root_node;
	nodes_allocator_t	_M_allocator;
	cmp_t _M_compare;
	avl_node_count_val _M_node_count;
public:
	pecker_avl_tree_map_container():_M_root_node(null),_M_node_count(0)
	{
	}
	pecker_avl_tree_map_container(const _AVL_map_container& other)
	{
		if (&other != this)
		{
			_M_root_node = null;
			this->copy(other);
		}
	}

	_AVL_map_container& operator = (const _AVL_map_container& other)
	{
		if (&other != this)
		{
			this->copy(other);
		}
		return *this;
	}
	~pecker_avl_tree_map_container()
	{
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(AVL_TREE_BOOLEAN_TRUE);
			_M_root_node = null;
			_M_node_count = 0;
		}
		else
		{
			erase_all_nodes();
		}
	}
protected:
	avl_result erase_all_nodes()
	{
		_Tree_posoder_iterator this_iterator(_M_root_node);
		_M_root_node = null;
		_M_node_count = 0;

		this_iterator.init();
		while(1)
		{
			__AVL_node_t* perase_node = (__AVL_node_t*)(this_iterator.get_current_node());
			avl_result result_ = this_iterator.increment_right();

			if (PEK_STATUS_OK == result_)
			{
				_M_allocator.release_node(perase_node);
			}
			else  if (PEK_STATUS_SUCCESS == result_)
			{
				_M_allocator.release_node(perase_node);
				break;
			}
			else
			{
				break;
			}

		}
		return PEK_STATUS_OK;
	}
	inline nodes_allocator_t &get_nodes_allocater() const
	{
		return _M_allocator;
	}
public:
	avl_result copy(const _AVL_map_container* other)
	{
		if (null == other)
		{
			return PEK_STATUS_ERROR;
		}
		if (other == this)
		{
			return PEK_STATUS_OK;
		}
		//clear(AVL_TREE_BOOLEAN_TRUE);
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(AVL_TREE_BOOLEAN_FLASE);
			_M_root_node = null;
			_M_node_count = 0;
		}

		typedef bst_node_allocator< __AVL_node_t,nodes_allocator_t > _Pool_allocator;
		_Pool_allocator fast_allocator(&_M_allocator);

		_Tree_posoder_iterator this_iterator(_M_root_node);
		avl_node_count_val icount = 0;
		_M_root_node = null;
		_M_node_count = 0;

		this_iterator.init();
		while(icount < other->get_node_count())
		{
			__AVL_node_t* perase_node = (__AVL_node_t*)(this_iterator.get_current_node());
			avl_result result_ = this_iterator.increment_right();

			++icount;
			if (PEK_STATUS_OK == result_)
			{
				fast_allocator.release_node(perase_node);
			}
			else  if (PEK_STATUS_SUCCESS == result_)
			{
				fast_allocator.release_node(perase_node);
				break;
			}
			else
			{
				break;
			}

		}

		const _AVL_node_base* pAvl_node_stack[AVL_MAX_HEIGHT];
		__AVL_node_t** pAvl_copy_node_ref_stack[AVL_MAX_HEIGHT];

		_Avl_height		nAvl_node_stack_size = 0;
		const _AVL_node_base* ptemp_node = other->_M_root_node;

		__AVL_node_t** ptemp_copy_node = &_M_root_node;

		while (ptemp_node)
		{
			__AVL_node_t* pcopy_node = fast_allocator.create_node();

			if (null != pcopy_node)
			{
				*pcopy_node = *((__AVL_node_t*)ptemp_node);
				pcopy_node->_M_left = null;
				pcopy_node->_M_right = null;

//#ifdef AVL_DEBUG_CODE
//				pcopy_node->pkey = ptemp_node->pkey;
//#endif
			}
			else
			{
				clear(AVL_TREE_BOOLEAN_TRUE);
				while(1)
				{
					__AVL_node_t* perase_node = (__AVL_node_t*)(this_iterator.get_current_node());
					avl_result result_ = this_iterator.increment_right();

					if (PEK_STATUS_OK == result_)
					{
						_M_allocator.release_node(perase_node);
					}
					else  if (PEK_STATUS_SUCCESS == result_)
					{
						_M_allocator.release_node(perase_node);
						break;
					}
					else
					{
						break;
					}

				}
				return PEK_STATUS_ERROR;
			}

			*ptemp_copy_node = pcopy_node;


			if (ptemp_node->_M_right)
			{
				pAvl_copy_node_ref_stack[nAvl_node_stack_size] = (__AVL_node_t**)&(pcopy_node->_M_right);
				pAvl_node_stack[nAvl_node_stack_size++] = ptemp_node->_M_right;

			}
			if (ptemp_node->_M_left)
			{
				ptemp_node = ptemp_node->_M_left;
				ptemp_copy_node =  (__AVL_node_t**)&(pcopy_node->_M_left);
			}
			else
			{
				if (nAvl_node_stack_size <= 0)
				{
					break;
				}
				else
				{
					ptemp_node = pAvl_node_stack[--nAvl_node_stack_size];
					ptemp_copy_node = pAvl_copy_node_ref_stack[nAvl_node_stack_size];
				}
			}
		}
		_M_node_count = other->_M_node_count;

		while(1)
		{
			__AVL_node_t* perase_node = (__AVL_node_t*)(this_iterator.get_current_node());
			avl_result result_ = this_iterator.increment_right();

			if (PEK_STATUS_OK == result_)
			{
				_M_allocator.release_node(perase_node);
			}
			else  if (PEK_STATUS_SUCCESS == result_)
			{
				_M_allocator.release_node(perase_node);
				break;
			}
			else
			{
				break;
			}

		}

		return PEK_STATUS_OK;
	}
	avl_result clear(Avl_tree_boolean_flag bForce_release = AVL_TREE_BOOLEAN_FLASE)
	{
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(bForce_release);
			_M_root_node = null;
			_M_node_count = 0;
		}
		else
		{
			_AVL_map_container swap_for_release_tree;
			swap_for_release_tree._M_root_node = this->_M_root_node;
			swap_for_release_tree._M_node_count = this->_M_node_count;
			this->_M_root_node = 0;
			this->_M_node_count = 0;
		}

		return PEK_STATUS_OK;
	}	

	inline const __AVL_node_t* get_root() const
	{
		return _M_root_node;
	}

	inline avl_node_count_val get_node_count() const
	{
		return _M_node_count;
	}

	avl_result insert(const key_t& key,value_t value)
	{
		__AVL_node_t* newnode = _M_allocator.create_node();
		if (null != newnode)
		{
			newnode->key = key;
			newnode->value = value;

//#ifdef AVL_DEBUG_CODE
//			newnode->teststr = key;
//#endif
		}
		avl_result add_error_code;
		avl_tree_add<key_t,cmp_t,__AVL_node_t>(_M_root_node,newnode,_M_compare,add_error_code);
		if (PEK_STATUS_OK == add_error_code)
		{
			++_M_node_count;
		}
		return add_error_code;
	}

	const __AVL_node_t* findnode(const key_t & key) const
	{
		return bst_tree_find<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare);
	}

	const value_t* find(const key_t &key) const
	{
		const __AVL_node_t* pfind_node = bst_tree_find<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare);
		if (null != pfind_node)
		{
			return &(pfind_node->value);
		}
		return null;
	}

	avl_result erase(const key_t key)
	{
		avl_result remove_error_code;
		__AVL_node_t* erase_node = avl_tree_remove<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare,remove_error_code);
		if (erase_node)
		{
			--_M_node_count;
			_M_allocator.release_node(erase_node);
			erase_node = null;
		}
		return remove_error_code;
	}

	avl_result replace(const key_t key,const key_t newkey)
	{
		avl_result remove_error_code;
		__AVL_node_t* erase_node = avl_tree_remove<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare,remove_error_code);
		if (erase_node)
		{
			avl_result add_error_code;
			erase_node->key = key;
			avl_tree_add<key_t,cmp_t,__AVL_node_t>(_M_root_node,erase_node,_M_compare,add_error_code);
			if (PEK_STATUS_OK != add_error_code)
			{
				--_M_node_count;
			}
			return add_error_code;
		}
		else
		{
			return remove_error_code;
		}

	}
	avl_result replace(const key_t key,const key_t newkey,const value_t newvalue)
	{
		avl_result remove_error_code;
		__AVL_node_t* erase_node = avl_tree_remove<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare,remove_error_code);
		if (erase_node)
		{
			avl_result add_error_code;
			erase_node->key = key;
			erase_node->value = newvalue;
			avl_tree_add<key_t,cmp_t,__AVL_node_t>(_M_root_node,erase_node,_M_compare,add_error_code);
			if (PEK_STATUS_OK != add_error_code)
			{
				--_M_node_count;
			}
			return add_error_code;
		}
		else
		{
			return remove_error_code;
		}

	}
	avl_result replace(const key_t key,const value_t newvalue)
	{
		__AVL_node_t* pfind_node = bst_tree_find_referance<key_t,cmp_t,__AVL_node_t>(_M_root_node,key,_M_compare);
		if (null != pfind_node)
		{
			pfind_node->value = newvalue;
			return PEK_STATUS_OK;
		}
		return PEK_STATUS_ERROR;
	}

	inline _Tree_iterator* get_iterator(_Tree_iterator* PARAM_INOUT pIterator) const
	{
		if (pIterator)
		{
			pIterator->reinit(static_cast< _AVL_node_base* >(_M_root_node));
		}
		return pIterator;
	}

	inline const value_t* get_at(const _Tree_iterator* PARAM_IN pIterator) const
	{
		if (pIterator && _M_root_node == pIterator->get_root_node())
		{
			const __AVL_node_t* pnode = (const __AVL_node_t*)(pIterator->get_current_node());
			if (pnode)
			{
				return &(pnode->value);
			}
		}

		return null;
	}

	inline const __AVL_node_t* get_node(const _Tree_iterator* PARAM_IN pIterator) const
	{
		if (pIterator && _M_root_node == pIterator->get_root_node())
		{
			return  (const __AVL_node_t*)(pIterator->get_current_node());
		}
		return null;
	}
};


PECKER_END

#endif
