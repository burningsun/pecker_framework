/*  Created on: 2012-12-1
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/
#ifndef PECKER_BALANCE_TENARY_TREE_H_
#define PECKER_BALANCE_TENARY_TREE_H_

#include "pecker_string.h"
#include "pecker_balance_tst_algorithm.h"
#include "pecker_stack.h"
#include "pecker_bst_iterator.h"
#include "pecker_bst_algorithm.h"
PECKER_BEGIN

typedef bool Tst_tree_boolean_flag;
#define  TST_TREE_BOOLEAN_TRUE	true
#define  TST_TREE_BOOLEAN_FLASE	false

//template < class _BTST_Node >
//PeckerInterface Ipecker_bts_tree_iterator
//{
//	virtual ~Ipecker_bts_tree_iterator(){;}
//	virtual tst_result init() = 0;
//	virtual tst_result init(TREE_ITERATOR_INIT_TYPE init_type) = 0;
//	virtual tst_result reinit(const _BTST_Node* pAvl_root_node,TREE_ITERATOR_INIT_TYPE init_type = ITERATOR_INIT_DEFAULT) = 0;
//	virtual const _BTST_Node* get_current_node() const = 0;
//	virtual const _BTST_Node* get_root_node() const = 0;
//};
//
//template < class _BTST_Node >
//class pecker_btst_tree_inorder_iterator_base : public Ipecker_bts_tree_iterator< _BTST_Node >
//{
//
//};



template<class key_value_t, class String_key_t, class _BTST_Node,class nodes_allocator_t>
class pecker_btst_set_container 
{
	typedef pecker_btst_set_container< key_value_t, String_key_t ,_BTST_Node, nodes_allocator_t > _btst_set_container;
	typedef  Ipecker_bst_tree_iterator< _BTST_Node >  _Tree_iterator;
private:
	_BTST_Node* _M_root_node;
	nodes_allocator_t	_M_allocator;
	tst_node_count_val _M_nodes_count;
	tst_node_count_val _M_value_count;
public:
	pecker_btst_set_container():_M_root_node(null),_M_nodes_count(0),_M_value_count(0)
	{
		;
	}
	~pecker_btst_set_container()
	{
		erase_all_nodes();
	}
public:
	tst_result copy(const _btst_set_container* other)
	{
		//typedef pecker_stack_pool_array< const _BTST_Node* > _Stack_;
		//typedef pecker_stack_pool_array< _BTST_Node** > _Stack_ref;

		//if (null == other)
		//{
		//	return P_ERR;
		//}
		//if (other == this)
		//{
		//	return P_OK;
		//}
		//clear(TST_TREE_BOOLEAN_TRUE);
		////.....
		//
		//_Stack_ node_path_stack;
		//_Stack_ref node_ref_path_stack;
		//tst_result return_result = copy_tst_tree< _BTST_Node,nodes_allocator_t,_Stack_,_Stack_ref >(other->get_root(),_M_root_node,_M_allocator,node_path_stack,node_ref_path_stack );
		//if (P_OK == return_result)
		//{
		//	_M_nodes_count = other->_M_nodes_count;
		//	_M_value_count = other->_M_value_count;
		//}
		//return return_result;

		typedef pecker_stack_pool_array< const _BTST_Node* > _Stack_cst;
		typedef pecker_stack_pool_array< _BTST_Node* > _Stack_;
		typedef pecker_stack_pool_array< _BTST_Node** > _Stack_ref;
		typedef bst_node_allocator< _BTST_Node,nodes_allocator_t > _Pool_allocator;
		if (null == other)
		{
			return P_ERR;
		}
		if (other == this)
		{
			return P_OK;
		}
		//clear(TST_TREE_BOOLEAN_TRUE);
		_Pool_allocator fast_allocate(&_M_allocator);
		_Stack_cst clr_path;
		_BTST_Node* ptemp_root_node = _M_root_node;
		clear_tst_tree< String_key_t,_BTST_Node,_Pool_allocator,_Stack_cst >(ptemp_root_node,fast_allocate,clr_path,other->get_node_count());
		_M_root_node = null;
		_M_value_count = 0;
		_M_nodes_count = 0;
		//.....
		_Stack_ node_path_stack;
		//_Stack_ mid_nodes;
		_Stack_ref node_ref_path_stack;
		//tst_result return_result = copy_tst_tree< _BTST_Node,nodes_allocator_t,_Stack_,_Stack_ref >(other->get_root(),_M_root_node,_M_allocator,node_path_stack,node_ref_path_stack);//,mid_nodes );
		tst_result return_result = copy_tst_tree< _BTST_Node,_Pool_allocator,_Stack_,_Stack_ref >(other->get_root(),_M_root_node,fast_allocate,node_path_stack,node_ref_path_stack);
		clr_path.clear();
		clear_tst_tree< String_key_t,_BTST_Node,nodes_allocator_t,_Stack_cst >(ptemp_root_node,_M_allocator,clr_path);
		if (P_OK == return_result)
		{
			_M_nodes_count = other->_M_nodes_count;
			_M_value_count = other->_M_value_count;
		}
		return return_result;
		//return P_OK;
	}
	tst_result clear(Tst_tree_boolean_flag bForce_release = TST_TREE_BOOLEAN_FLASE)
	{
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(bForce_release);
			_M_root_node = null;
			_M_nodes_count = 0;
		}
		else
		{
			_btst_set_container swap_for_release_tree;
			swap_for_release_tree._M_root_node = this->_M_root_node;
			swap_for_release_tree._M_nodes_count = this->_M_nodes_count;
			swap_for_release_tree._M_value_count = this->_M_value_count;
			this->_M_root_node = null;
			this->_M_value_count = 0;
			this->_M_nodes_count = 0;
		}

		return P_OK;
	}	
public:
	const _BTST_Node* findnode(const key_value_t* pstring_key,string_size_t string_size) const
	{
		return avl_tst_tree_find< key_value_t,_BTST_Node >(_M_root_node,pstring_key,string_size);
	}
	tst_result  insert(const key_value_t* pstring_key,string_size_t string_size)
	{
		tst_result return_value;
		_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,nodes_allocator_t,String_key_t,_BTST_Node>
			(_M_root_node,pstring_key,string_size,_M_allocator,return_value,_M_nodes_count);
		if (null != pInsert_node && P_OK == return_value)
		{
			++_M_value_count;
		}
		return return_value;
	}
	tst_result erase(const key_value_t* pstring_key,string_size_t string_size)
	{
		tst_result return_value = avl_tst_tree_erase<key_value_t,nodes_allocator_t,String_key_t,_BTST_Node>(_M_root_node,pstring_key,string_size,_M_allocator,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;
		}
		return return_value;
	}
	tst_result replace(const key_value_t* pstring_key,string_size_t string_size,const key_value_t* pnew_string_key,string_size_t new_string_size)
	{
		typedef bst_node_allocator< _BTST_Node,nodes_allocator_t > _Pool_allocator;
		_Pool_allocator fast_allocate(&_M_allocator);

		tst_result return_value = avl_tst_tree_erase<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>(_M_root_node,pstring_key,string_size,fast_allocate,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;
			
			_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>
				(_M_root_node,pstring_key,string_size,fast_allocate,return_value,_M_nodes_count);
			if (null != pInsert_node && P_OK == return_value)
			{
				++_M_value_count;
			}
		}

		return return_value;
	}

	const _BTST_Node* find_node_with_string_begin(const key_value_t* pstring_key,string_size_t string_size) const
	{
		return avl_tst_tree_find_start_string_node< key_value_t,_BTST_Node >(_M_root_node,pstring_key,string_size);
	}

	const _BTST_Node* findnode(const String_key_t& string_key) const
	{
		return avl_tst_tree_find< key_value_t,_BTST_Node >(_M_root_node,string_key.get_data(),string_key.get_string_length());
	}
	tst_result  insert(const String_key_t& string_key)
	{
		tst_result return_value;
		_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,nodes_allocator_t,String_key_t,_BTST_Node>(_M_root_node,string_key.get_data(),string_key.get_string_length(),_M_allocator,return_value);
		if (null != pInsert_node && P_OK == return_value)
		{
			++_M_value_count;
		}
		return return_value;
	}
	tst_result erase(const String_key_t& string_key)
	{
		tst_result return_value = avl_tst_tree_erase<key_value_t,nodes_allocator_t,String_key_t,_BTST_Node>(_M_root_node,string_key.get_data(),string_key.get_string_length(),_M_allocator,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;
		}
		return return_value;
	}
	tst_result replace(const String_key_t& string_key,const String_key_t& new_string_key)
	{
		typedef bst_node_allocator< _BTST_Node,nodes_allocator_t > _Pool_allocator;
		_Pool_allocator fast_allocate(&_M_allocator);

		tst_result return_value = avl_tst_tree_erase<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>(_M_root_node,string_key.get_data(),string_key.get_string_length(),fast_allocate,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;

			_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>
				(_M_root_node,new_string_key.get_data(),new_string_key.get_string_length(),fast_allocate,return_value,_M_nodes_count);
			if (null != pInsert_node && P_OK == return_value)
			{
				++_M_value_count;
			}
		}

		return return_value;
	}
	const _BTST_Node* find_node_with_string_begin(const String_key_t& string_key) const
	{
		return avl_tst_tree_find_start_string_node< key_value_t,_BTST_Node >(_M_root_node,string_key.get_data(),string_key.get_string_length());
	}

	inline tst_node_count_val get_node_count() const
	{
		return _M_nodes_count;
	}
	inline tst_node_count_val get_value_count() const
	{
		return _M_value_count;
	}
	inline const _BTST_Node* get_root() const
	{
		return _M_root_node;
	}

	inline _Tree_iterator* get_iterator(_Tree_iterator* P_INOUT pIterator) const
	{
		if (pIterator)
		{
			pIterator->reinit(static_cast< _BTST_Node* >(_M_root_node));
		}
		return pIterator;
	}

	inline String_key_t get_key(const _Tree_iterator* P_IN pIterator) const
	{

		if (pIterator && _M_root_node == pIterator->get_root_node())
		{
			const _BTST_Node* pnode = (const _BTST_Node*)(pIterator->get_current_node());
			return get_tst_key_string<  String_key_t,  _BTST_Node >(pnode);
		}
		
		String_key_t string_return;
		return string_return;
	}

protected:
	inline nodes_allocator_t &get_nodes_allocater() const
	{
		return _M_allocator;
	}
	inline tst_result erase_all_nodes()
	{
		typedef pecker_stack_pool_array< const _BTST_Node* > _Stack_;
		_Stack_ path;
		tst_result return_result;

		return_result = clear_tst_tree< String_key_t,_BTST_Node,nodes_allocator_t,_Stack_>(_M_root_node,//_M_nodes_count,
			_M_allocator,path);

		_M_nodes_count = 0;
		_M_value_count = 0;
		return return_result;
	}
};

template<class key_value_t, class String_key_t, class value_t, class _BTST_Node,class nodes_allocator_t>
class pecker_btst_map_container 
{
	typedef pecker_btst_map_container< key_value_t, String_key_t ,value_t,_BTST_Node, nodes_allocator_t > _btst_map_container;
	typedef  Ipecker_bst_tree_iterator< _BTST_Node >  _Tree_iterator;
private:
	_BTST_Node* _M_root_node;
	nodes_allocator_t	_M_allocator;
	tst_node_count_val _M_nodes_count;
	tst_node_count_val _M_value_count;
public:
	pecker_btst_map_container():_M_root_node(null),_M_nodes_count(0),_M_value_count(0)
	{

	}
	~pecker_btst_map_container()
	{
		erase_all_nodes();
	}
public:
	tst_result copy(const _btst_map_container* other)
	{
		typedef pecker_stack_pool_array< const _BTST_Node* > _Stack_cst;
		typedef pecker_stack_pool_array< _BTST_Node* > _Stack_;
		typedef pecker_stack_pool_array< _BTST_Node** > _Stack_ref;
		typedef bst_node_allocator< _BTST_Node,nodes_allocator_t > _Pool_allocator;
		if (null == other)
		{
			return P_ERR;
		}
		if (other == this)
		{
			return P_OK;
		}
		//clear(TST_TREE_BOOLEAN_TRUE);
		_Pool_allocator fast_allocate(&_M_allocator);
		_Stack_cst clr_path;
		_BTST_Node* ptemp_root_node = _M_root_node;
		clear_tst_tree< String_key_t,_BTST_Node,_Pool_allocator,_Stack_cst >(ptemp_root_node,fast_allocate,clr_path,other->get_node_count());
		_M_root_node = null;
		_M_value_count = 0;
		_M_nodes_count = 0;
		//.....
		_Stack_ node_path_stack;
		//_Stack_ mid_nodes;
		_Stack_ref node_ref_path_stack;
		//tst_result return_result = copy_tst_tree< _BTST_Node,nodes_allocator_t,_Stack_,_Stack_ref >(other->get_root(),_M_root_node,_M_allocator,node_path_stack,node_ref_path_stack);//,mid_nodes );
		tst_result return_result = copy_tst_tree< _BTST_Node,_Pool_allocator,_Stack_,_Stack_ref >(other->get_root(),_M_root_node,fast_allocate,node_path_stack,node_ref_path_stack);
		clr_path.clear();
		clear_tst_tree< String_key_t,_BTST_Node,nodes_allocator_t,_Stack_cst >(ptemp_root_node,_M_allocator,clr_path);
		if (P_OK == return_result)
		{
			_M_nodes_count = other->_M_nodes_count;
			_M_value_count = other->_M_value_count;
		}
		return return_result;
		//return P_OK;
	}
	tst_result clear(Tst_tree_boolean_flag bForce_release = TST_TREE_BOOLEAN_FLASE)
	{
		if (_M_allocator.Is_pool())
		{
			_M_allocator.clear(bForce_release);
			_M_root_node = null;
			_M_nodes_count = 0;
		}
		else
		{
			_btst_map_container swap_for_release_tree;
			swap_for_release_tree._M_root_node = this->_M_root_node;
			swap_for_release_tree._M_nodes_count = this->_M_nodes_count;
			swap_for_release_tree._M_value_count = this->_M_value_count;
			this->_M_root_node = null;
			this->_M_value_count = 0;
			this->_M_nodes_count = 0;
		}

		return P_OK;
	}	
public:
	const _BTST_Node* findnode(const key_value_t* pstring_key,string_size_t string_size) const
	{
		return avl_tst_tree_find< key_value_t,_BTST_Node >(_M_root_node,pstring_key,string_size);
	}
	const _BTST_Node* find_node_with_string_begin(const key_value_t* pstring_key,string_size_t string_size) const
	{
		return avl_tst_tree_find_start_string_node< key_value_t,_BTST_Node >(_M_root_node,pstring_key,string_size);
	}

	tst_result  insert(const key_value_t* pstring_key,string_size_t string_size,const value_t& insert_value)
	{
		tst_result return_value;
		_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,nodes_allocator_t,String_key_t,_BTST_Node>
			(_M_root_node,pstring_key,string_size,_M_allocator,return_value,_M_nodes_count);
		if (null != pInsert_node && P_OK == return_value)
		{
			pInsert_node->value = insert_value;
			++_M_value_count;
		}
		return return_value;
	}
	tst_result erase(const key_value_t* pstring_key,string_size_t string_size)
	{
		tst_result return_value = avl_tst_tree_erase<key_value_t,nodes_allocator_t,String_key_t,_BTST_Node>(_M_root_node,pstring_key,string_size,_M_allocator,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;
		}
		return return_value;
	}
	tst_result replace(const key_value_t* pstring_key,string_size_t string_size,const key_value_t* pnew_string_key,string_size_t new_string_size)
	{
		typedef bst_node_allocator< _BTST_Node,nodes_allocator_t > _Pool_allocator;
		_Pool_allocator fast_allocate(&_M_allocator);

		tst_result return_value = avl_tst_tree_erase<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>(_M_root_node,pstring_key,string_size,fast_allocate,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;

			_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>
				(_M_root_node,pnew_string_key,new_string_size,fast_allocate,return_value,_M_nodes_count);
			if (null != pInsert_node && P_OK == return_value)
			{
				++_M_value_count;
			}
		}

		return return_value;
	}
	tst_result replace(const key_value_t* pstring_key,string_size_t string_size,const key_value_t* pnew_string_key,string_size_t new_string_size,const value_t& replace_value)
	{
		typedef bst_node_allocator< _BTST_Node,nodes_allocator_t > _Pool_allocator;
		_Pool_allocator fast_allocate(&_M_allocator);

		tst_result return_value = avl_tst_tree_erase<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>(_M_root_node,pstring_key,string_size,fast_allocate,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;

			_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>
				(_M_root_node,pnew_string_key,new_string_size,fast_allocate,return_value,_M_nodes_count);
			if (null != pInsert_node && P_OK == return_value)
			{
				pInsert_node->value = replace_value;
				++_M_value_count;
			}
		}

		return return_value;
	}
	tst_result replace(const key_value_t* pstring_key,string_size_t string_size,const value_t& replace_value)
	{
		_BTST_Node* pfind_node = avl_tst_tree_find_referance< key_value_t,_BTST_Node >(_M_root_node,pstring_key,string_size);
		if (pfind_node)
		{
			pfind_node->value = replace_value;
			return P_OK;
		}
		return P_ERR;
	}

	const _BTST_Node* findnode(const String_key_t& string_key) const
	{
		return avl_tst_tree_find< key_value_t,_BTST_Node >(_M_root_node,string_key.get_data(),string_key.get_string_length());
	}
	tst_result  insert(const String_key_t& string_key,const value_t& insert_value)
	{
		tst_result return_value;
		_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,nodes_allocator_t,String_key_t,_BTST_Node>
			(_M_root_node,string_key.get_data(),string_key.get_string_length(),_M_allocator,return_value,_M_nodes_count);
		if (null != pInsert_node && P_OK == return_value)
		{
			pInsert_node->value = insert_value;
			++_M_value_count;
		}
		return return_value;
	}
	tst_result erase(const String_key_t& string_key)
	{
		tst_result return_value = avl_tst_tree_erase<key_value_t,nodes_allocator_t,String_key_t,_BTST_Node>(_M_root_node,string_key.get_data(),string_key.get_string_length(),_M_allocator,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;
		}
		return return_value;
	}
	tst_result replace(const String_key_t& string_key,const String_key_t& new_string_key)
	{
		typedef bst_node_allocator< _BTST_Node,nodes_allocator_t > _Pool_allocator;
		_Pool_allocator fast_allocate(&_M_allocator);

		tst_result return_value = avl_tst_tree_erase<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>(_M_root_node,string_key.get_data(),string_key.get_string_length(),fast_allocate,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;

			_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>
				(_M_root_node,new_string_key.get_data(),new_string_key.get_string_length(),fast_allocate,return_value,_M_nodes_count);
			if (null != pInsert_node && P_OK == return_value)
			{
				++_M_value_count;
			}
		}

		return return_value;
	}
	tst_result replace(const String_key_t& string_key,const String_key_t& new_string_key,const value_t& replace_value)
	{
		typedef bst_node_allocator< _BTST_Node,nodes_allocator_t > _Pool_allocator;
		_Pool_allocator fast_allocate(&_M_allocator);

		tst_result return_value = avl_tst_tree_erase<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>(_M_root_node,string_key.get_data(),string_key.get_string_length(),fast_allocate,_M_nodes_count);
		if (P_OK == return_value && _M_value_count > 0)
		{
			--_M_value_count;

			_BTST_Node* pInsert_node = avl_tst_tree_insert<key_value_t,_Pool_allocator,String_key_t,_BTST_Node>
				(_M_root_node,new_string_key.get_data(),new_string_key.get_string_length(),fast_allocate,return_value,_M_nodes_count);
			if (null != pInsert_node && P_OK == return_value)
			{
				pInsert_node->value = replace_value;
				++_M_value_count;
			}
		}

		return return_value;
	}
	tst_result replace(const String_key_t& string_key,const value_t& replace_value)
	{
		_BTST_Node* pfind_node = avl_tst_tree_find_referance< key_value_t,_BTST_Node >(_M_root_node,string_key.get_data(),string_key.get_string_length());
		if (pfind_node)
		{
			pfind_node->value = replace_value;
			return P_OK;
		}
		return P_ERR;
	}
	const _BTST_Node* find_node_with_string_begin(const String_key_t& string_key) const
	{
		return avl_tst_tree_find_start_string_node< key_value_t,_BTST_Node >(_M_root_node,string_key.get_data(),string_key.get_string_length());
	}

	inline tst_node_count_val get_node_count() const
	{
		return _M_nodes_count;
	}
	inline tst_node_count_val get_value_count() const
	{
		return _M_value_count;
	}
	inline const _BTST_Node* get_root() const
	{
		return _M_root_node;
	}

	inline _Tree_iterator* get_iterator(_Tree_iterator* P_INOUT pIterator) const
	{
		if (pIterator)
		{
			pIterator->reinit(static_cast< _BTST_Node* >(_M_root_node));
		}
		return pIterator;
	}

	inline String_key_t get_key(const _Tree_iterator* P_IN pIterator) const
	{

		if (pIterator && _M_root_node == pIterator->get_root_node())
		{
			const _BTST_Node* pnode = (const _BTST_Node*)(pIterator->get_current_node());
			return get_tst_key_string<  String_key_t,  _BTST_Node >(pnode);
		}

		String_key_t string_return;
		return string_return;
	}

	inline const value_t* get_value(const _Tree_iterator* P_IN pIterator) const
	{
		if (pIterator && _M_root_node == pIterator->get_root_node())
		{
			const _BTST_Node* pnode = (const _BTST_Node*)(pIterator->get_current_node());
			if (pnode)
			{
				return &(pnode->value);
			}
		}

		return null;
	}

protected:
	inline nodes_allocator_t &get_nodes_allocater() const
	{
		return _M_allocator;
	}
	inline tst_result erase_all_nodes()
	{
		typedef pecker_stack_pool_array< const _BTST_Node* > _Stack_;
		_Stack_ path;
		tst_result return_result;

		return_result = clear_tst_tree< String_key_t,_BTST_Node,nodes_allocator_t,_Stack_>(_M_root_node,//_M_nodes_count,
			_M_allocator,path);

		_M_nodes_count = 0;
		_M_value_count = 0;
		return return_result;
	}
};


PECKER_END

#endif 
