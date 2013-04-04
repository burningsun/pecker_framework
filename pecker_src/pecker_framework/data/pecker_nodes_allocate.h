/*
 *  pecker_nodes_allocate.h
 *
 *  Created on: 2012-11-3
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_NODES_ALLOCATE_H_
#define PECKER_NODES_ALLOCATE_H_

#include "../CPeckerObject.h"
#include "pecker_array.h"
#include "../native/pecker_allocator.h"

PECKER_BEGIN

typedef int  node_serial_number;
typedef int nodes_pool_size; 

#define  NODES_BOOLEAN_TRUE		true
#define  NODES_BOOLEAN_FLASE	false
typedef bool			nodes_boolean_flag;

template< class _node_t >
struct pecker_serial_node :  public _node_t
{
	node_serial_number	_M_node_ID;
};

template<class _node_t, class allocate_object_t = pecker_simple_allocator<_node_t> >
class pecker_nodes_simple_allocater
{
public:
	 inline _node_t* create_node()
	{
		_node_t* pcreate_node = allocate_object_t::allocate_object();
		return pcreate_node;
	}
	inline void release_node(_node_t* pNode)
	{
		if (null != pNode)
		{
			allocate_object_t::deallocate_object(pNode);
		}
	}
	inline void clear(nodes_boolean_flag bForce_release = NODES_BOOLEAN_FLASE)
	{
	}
	inline nodes_pool_size get_size() const
	{
		return -1;
	}
	inline nodes_boolean_flag Is_pool() const
	{
		return NODES_BOOLEAN_FLASE;
	}
};

template< class _BST_node,class nodes_allocator_t >
class bst_node_allocator
{
private:
	nodes_allocator_t* _M_pAllocator;
	_BST_node* _M_pnode_end;
	nodes_pool_size _M_nodes_count;
public:
	explicit bst_node_allocator(nodes_allocator_t* pallocator = null):_M_pAllocator(pallocator),_M_pnode_end(null),_M_nodes_count(0){;}
	inline nodes_boolean_flag Is_pool() const
	{
		return NODES_BOOLEAN_FLASE;
	}
	inline nodes_pool_size get_size() const
	{
		if ((null == _M_pAllocator) || (NODES_BOOLEAN_FLASE == _M_pAllocator->Is_pool()))
		{
			return _M_nodes_count;
		}
		else
		{
			return (_M_nodes_count + _M_pAllocator->get_size());
		}
	}
	inline _BST_node* create_node()
	{		
		_BST_node* pcreate_node = null;
		if (null == _M_pnode_end)
		{
			if (null != _M_pAllocator)
			{
				pcreate_node = _M_pAllocator->create_node();
			}
		}
		else
		{
			pcreate_node = _M_pnode_end;
			_M_pnode_end = ( _BST_node*)(_M_pnode_end->_M_right);
		}
		return pcreate_node;
	}
	inline void release_node(_BST_node* pNode)
	{
		if (null != pNode)
		{
			if (null == _M_pnode_end)
			{
				_M_pnode_end = pNode;
			}
			else
			{
				_M_pnode_end->_M_right = pNode;
			}
			pNode->_M_right = null;
		}
	}
	inline void clear(nodes_boolean_flag bForce_release = NODES_BOOLEAN_FLASE)
	{
		if (null == _M_pAllocator)
		{
			return;
		}

		if (_M_nodes_count > 0 && NODES_BOOLEAN_TRUE == bForce_release)
		{
			_BST_node* ptemp_node = _M_pnode_end;
			while(null != _M_pnode_end)
			{
				_M_pnode_end = _M_pnode_end->_M_right;
				_M_pAllocator->release_node(ptemp_node);
			}
		}

		_M_pAllocator->clear(bForce_release);


	}
};
//template< class _node_t, class allocate_object_t = pecker_simple_allocator<_node_t> >
//class pecker_nodes_pool_allocater
//{
//	typedef pecker_serial_node< _node_t >  SerialNode;
//private:
//	nodes_pool_size _M_pool_size;
//	pecker_pool_array< SerialNode, allocate_object_t > _M_pool;
//	pecker_pool_array< node_serial_number > _M_recycler_pool;
//public:
//	pecker_nodes_pool_allocater( array_buffer_size_val pool_init_size,
//															array_buffer_size_val recycler_pool_size = ARRAY_DEFAULT_ALLOCATE_STEP,
//															array_buffer_size_val auto_allocate_size = ARRAY_DEFAULT_ALLOCATE_STEP,
//															array_buffer_size_val array_buffer_array_allocate_step = ARRAY_DEFAULT_ALLOCATE_STEP
//		):_M_pool_size(0),
//		_M_pool(auto_allocate_size,array_buffer_array_allocate_step),
//		_M_recycler_pool(auto_allocate_size,array_buffer_array_allocate_step)
//	{
//		_M_pool.init(pool_init_size);
//		_M_recycler_pool.init(pool_init_size);
//	}
//
//	 _node_t* create_node()
//	{
//		 SerialNode* pnew_node = null;
//		 array_buffer_size_val recycler_pool_size = _M_recycler_pool.get_size();
//		 if (recycler_pool_size > 0)
//		 {
//			 array_index_val index = recycler_pool_size-1;
//			 const node_serial_number* pindex = _M_recycler_pool.get_at(index);
//			 if (pindex)
//			 {
//				 pnew_node = _M_pool.get_reference_at(*pindex);
//			 }
//		 }
//		 else
//		 {
//			  array_index_val index = _M_pool.get_size();
//			  if (index >= 0 && P_OK ==  _M_pool.resize(index+1))
//			  {
//				 pnew_node = _M_pool.get_reference_at(index);
//				 pnew_node->_M_node_ID = index;
//			  }
//		 }
//
//		 if (null != pnew_node)
//		 {
//			 ++_M_pool_size;
//		 }
//		 return static_cast< _node_t* >(pnew_node);
//	}
//	void release_node(_node_t* pNode)
//	{
//		if (null != pNode)
//		{
//			SerialNode* pnew_node = (_node_t*)pNode;
//			if (pnew_node == _M_pool.get_at(pnew_node->_M_node_ID))
//			{
//				--_M_pool_size;
//				_M_recycler_pool.push(pnew_node->_M_node_ID);
//			}
//		}
//	}
//	void clear(nodes_boolean_flag bForce_release = NODES_BOOLEAN_FLASE)
//	{
//		_M_recycler_pool.resize(0,-1,-1,bForce_release);
//		_M_pool.resize(0,-1,-1,bForce_release);
//		_M_pool_size = 0;
//	}
//	nodes_pool_size get_size() const
//	{
//		return _M_pool_size;
//	}
//	nodes_boolean_flag Is_pool() const
//	{
//		return NODES_BOOLEAN_TRUE;
//	}
//};






PECKER_END

#endif
