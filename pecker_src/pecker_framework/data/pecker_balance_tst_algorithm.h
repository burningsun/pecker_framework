/*
 *  pecker_balance_tst_algorithm.h
 *
 *  Created on: 2012-11-8
 *      Author: �����  �� cut / cutxyz��
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
//
//		����ƽ��������(�ַ����ڴ湲���Ż���AVLƽ�����(�ȴ����AVL�����뷭ת������)) �������Ĳ��룬ɾ��������
//
#ifndef PECKER_BALANCE_TST_ALGORITHM_H_
#define PECKER_BALANCE_TST_ALGORITHM_H_

#include "../CPeckerObject.h"
#include "pecker_value_compare.h"
#include "pecker_avl_tree_algorithm.h"
#include "pecker_nodes_allocate.h"
#include "pecker_string.h"
#include "../native/pecker_log.h"

PECKER_BEGIN

//#define  TST_DEBUG_

#ifdef TST_DEBUG_
#define	PRINT_TST_NODE_STRING(string_) 	{ \
																					if (string_.get_string_length() > 0) \
																					{ \
																						static char logifo[50]; \
																						sprintf(logifo,"%%%d.%ds",string_.get_string_length(),string_.get_string_length()); \
																						PECKER_LOG_(logifo,string_.get_data()); \
																					}\
																					else \
																					{ \
																						PECKER_LOG_("null string",0);\
																					}\
																					PECKER_LOG_("\n",0);\
																				}
#endif

typedef int					Ternarytree_legal_node_flag;
typedef int					tst_node_id;
typedef nINDEX			tst_array_index_val;
typedef nSize				tst_node_count_val;
typedef nSize				tst_buffer_size;
typedef HResult		tst_result;

// �������ڵ�ֵ��Ч����
typedef enum enumTERNARYTREE_LEGAL_NODE_FLAG_TYPE
{
	INVALID_TST_NODE = 0,  //��Ч�ڵ���Чֵ
	NO_VALUE_TST_NODE,    //��Ч�ڵ���Чֵ
	HAS_VALUE_TST_NODE,   //��Ч�ڵ���Чֵ

	TERNARYTREE_LEGAL_NODE_FLAG_TYPE_COUNT
}TERNARYTREE_LEGAL_NODE_FLAG_TYPE;

// �������ڵ�����
template< class key_char_value_t,
class __cmp_t,
class allocate_object_t = pecker_simple_allocator< key_char_value_t >,
class bst_base_node_t = _AVL_node_base>
struct pecker_tst_set_node : public bst_base_node_t
{
	pecker_share_string_base_t<key_char_value_t,__cmp_t,allocate_object_t> key;
	pecker_tst_set_node* _M_middle_root_node;
	pecker_tst_set_node* _M_middle_node;
	Ternarytree_legal_node_flag _M_legal_flag;
};

template< class key_char_value_t,
class value_t,
class __cmp_t,
class allocate_object_t = pecker_simple_allocator< key_char_value_t >,
class bst_base_node_t = _AVL_node_base>
struct pecker_tst_map_node_extern : public pecker_tst_set_node<key_char_value_t,__cmp_t,allocate_object_t,bst_base_node_t>
{
	value_t value;
};

template< class key_char_value_t,
class value_t,
class __cmp_t,
class allocate_object_t = pecker_simple_allocator< key_char_value_t >,
class bst_base_node_t = _AVL_node_base>
struct pecker_tst_map_node : public bst_base_node_t
{
	pecker_share_string_base_t<key_char_value_t,__cmp_t,allocate_object_t> key;

	pecker_tst_map_node* _M_middle_root_node;
	pecker_tst_map_node* _M_middle_node;
	Ternarytree_legal_node_flag _M_legal_flag;

	value_t value;
};

template< class String_key_t,class bst_base_node_t = _AVL_node_base >
struct pecker_tst_set_node_ : public bst_base_node_t
{
	String_key_t key;

	pecker_tst_set_node_* _M_middle_root_node;
	pecker_tst_set_node_* _M_middle_node;
	Ternarytree_legal_node_flag _M_legal_flag;
};

template< class String_key_t, class value_t, class bst_base_node_t = _AVL_node_base >
struct pecker_tst_map_node_ : public bst_base_node_t
{
	String_key_t key;
	pecker_tst_map_node_* _M_middle_root_node;
	pecker_tst_map_node_* _M_middle_node;
	Ternarytree_legal_node_flag _M_legal_flag;

	value_t value;
};

template< class String_key_t, class _BTST_Node >
inline String_key_t get_tst_key_string(const _BTST_Node* pNode)
{
	String_key_t str_return;
	if (null == pNode)
	{
		return str_return;
	}
	pecker_stack_pool_array< const _BTST_Node* > node_path_stack;
	string_size_t string_size = 0;
	while(null != pNode)
	{
		node_path_stack.push(pNode);
		string_size += pNode->key.get_string_length();
		pNode = pNode->_M_middle_root_node;
	}
	str_return.init(string_size+1);
	while(node_path_stack.get_size() > 0)
	{
		const _BTST_Node* ptop_node = *node_path_stack.end();
		str_return.append_string(ptop_node->key);
		node_path_stack.pop();
	}
	return str_return;
}



// ����������
template< class key_char_value_t,
class _TST_node >
inline const _TST_node* avl_tst_tree_find(const _TST_node* pTst_root_node,
		const key_char_value_t* pkey_string,
		string_size_t key_string_size)
{
	if (null == pTst_root_node || null == pkey_string || 0 >= key_string_size)
	{
		return null;
	}

	const _TST_node* ptemp_find_node = pTst_root_node;
	string_size_t nbegin_same_char_size = 0;
	tst_array_index_val index = 0;
	int last_cmp_result;

	while (ptemp_find_node)
	{
		last_cmp_result = ptemp_find_node->key.compare_same_chars(pkey_string + index,key_string_size - index,nbegin_same_char_size);

		if (last_cmp_result < 0)
		{
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_right);
		}
		else if (last_cmp_result > 0)
		{
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_left);
		}
		else
		{
			index += nbegin_same_char_size;
			if (index >= key_string_size)
			{
				if (nbegin_same_char_size == ptemp_find_node->key.get_string_length())
				{
					return ptemp_find_node;
				}
				break;
			}
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_middle_node);
		}
	}
	return null;
}

// ����������,���ؿ��޸ĵĽ��ָ��
template< class key_char_value_t,
class _TST_node >
inline _TST_node* avl_tst_tree_find_referance(_TST_node* pTst_root_node,
		const key_char_value_t* pkey_string,
		string_size_t key_string_size)
{
	if (null == pTst_root_node || null == pkey_string || 0 >= key_string_size)
	{
		return null;
	}

	_TST_node* ptemp_find_node = pTst_root_node;
	string_size_t nbegin_same_char_size = 0;
	tst_array_index_val index = 0;
	int last_cmp_result;

	while (ptemp_find_node)
	{
		last_cmp_result = ptemp_find_node->key.compare_same_chars(pkey_string + index,key_string_size - index,nbegin_same_char_size);

		if (last_cmp_result < 0)
		{
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_right);
		}
		else if (last_cmp_result > 0)
		{
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_left);
		}
		else
		{
			index += nbegin_same_char_size;
			if (index >= key_string_size)
			{
				if (nbegin_same_char_size == ptemp_find_node->key.get_string_length())
				{
					return ptemp_find_node;
				}
				break;
			}
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_middle_node);
		}
	}
	return null;

}

//������������ĳ�ַ�����ͷ���׸����
template< class key_char_value_t,
class _TST_node >
	inline const _TST_node* avl_tst_tree_find_start_string_node(const _TST_node* pTst_root_node,
	const key_char_value_t* pkey_string,
	string_size_t key_string_size)
{
	if (null == pTst_root_node || null == pkey_string || 0 >= key_string_size)
	{
		return null;
	}

	const _TST_node* ptemp_find_node = pTst_root_node;
	string_size_t nbegin_same_char_size = 0;
	tst_array_index_val index = 0;
	int last_cmp_result;

	while (ptemp_find_node)
	{
		last_cmp_result = ptemp_find_node->key.compare_same_chars(pkey_string + index,key_string_size - index,nbegin_same_char_size);

		if (last_cmp_result < 0)
		{
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_right);
		}
		else if (last_cmp_result > 0)
		{
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_left);
		}
		else
		{
			index += nbegin_same_char_size;
			if (index >= key_string_size)
			{
				return ptemp_find_node;
				//if (nbegin_same_char_size == ptemp_find_node->key.get_string_length())
				//{
				//	return ptemp_find_node;
				//}
				//break;
			}
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_middle_node);
		}
	}
	return null;
}

// ���������Ҳ��������
typedef enum enumTST_FIND_ADD_TYPE
{
	ADD_ERR = 0,							// ����
	NODE_EXSIT,							// �ڵ㲻����
	BST_NEW_NODE_ADD,		// ��Ҫ�½��ڵ㣬�������������뷽ʽ����Ľ��
	TST_NEW_NODE_ADD,			// ��Ҫ�½��ڵ㣬�������������뷽ʽ����Ľ��
	CLIP_AND_ADD_NODE,		// ��ֽڵ㣬������һ������ڵ�
	CLIP_NODE							// ��ֽڵ�

}TST_FIND_ADD_TYPE;


// ���������������
template< class key_char_value_t,
class _TST_node >
inline _TST_node* avl_tst_tree_find_add_node(_TST_node* pTst_root_node,
		_TST_node**& pTst_last_reference_node,
		const key_char_value_t* pkey_string,
		string_size_t key_string_size,
		TST_FIND_ADD_TYPE & add_type,
		string_size_t & nbegin_same_char_size,
		string_size_t & travel_string_index)
{
	_TST_node* ptemp_find_node = pTst_root_node;
	_TST_node** pptmp_last_reference_node = null;
	_TST_node* last_root_node = ptemp_find_node;
	int last_cmp_result;

	add_type = ADD_ERR;
	pTst_last_reference_node = null;
	nbegin_same_char_size = 0;

	while(1)
	{
		pptmp_last_reference_node = null;

		while(1)
		{
			pTst_last_reference_node = pptmp_last_reference_node;
			last_cmp_result = ptemp_find_node->key.compare_same_chars( pkey_string + travel_string_index, key_string_size - travel_string_index,nbegin_same_char_size);

			if (nbegin_same_char_size > 0)
			{
				break;
			}
			if (last_cmp_result < 0)
			{
				pptmp_last_reference_node = (_TST_node**)(&(ptemp_find_node->_M_right));
				ptemp_find_node = *pptmp_last_reference_node;
			}
			else if (last_cmp_result > 0)
			{
				pptmp_last_reference_node = (_TST_node**)(&(ptemp_find_node->_M_left));
				ptemp_find_node = *pptmp_last_reference_node;
			}
			else
			{
				break;
			}

			if (null == ptemp_find_node)
			{
				break;
			}
		}

		travel_string_index += nbegin_same_char_size;

		if (0 == nbegin_same_char_size)
		{
			ptemp_find_node = last_root_node;
			if (travel_string_index > 0)
			{
				add_type = TST_NEW_NODE_ADD;
			}
			else
			{
				add_type = BST_NEW_NODE_ADD;
			}

			break;
		}
		else if (null == ptemp_find_node)
		{
			if (pTst_last_reference_node)
			{
				ptemp_find_node = *pTst_last_reference_node;
			}
			else
			{
				ptemp_find_node = last_root_node;
			}

			if (travel_string_index >= key_string_size)
			{
				add_type = CLIP_NODE;
			}
			else
			{
				add_type = CLIP_AND_ADD_NODE;
			}
			break;
		}
		else
		{
			string_size_t find_key_string_size = ptemp_find_node->key.get_string_length();
			if (travel_string_index >= key_string_size)
			{
				if (find_key_string_size == nbegin_same_char_size)
				{
					add_type = NODE_EXSIT;
				}
				else
				{
					add_type = CLIP_NODE;
				}
				break;
			}

			if (find_key_string_size > nbegin_same_char_size)
			{
				add_type = CLIP_AND_ADD_NODE;
				break;
			}

			last_root_node = ptemp_find_node;
			ptemp_find_node = (_TST_node*)(ptemp_find_node->_M_middle_node);

			if (null == ptemp_find_node)
			{
				ptemp_find_node = last_root_node;
				find_key_string_size = last_root_node->key.get_string_length();

				if (0 == last_cmp_result)
				{
					add_type = TST_NEW_NODE_ADD;
				}
				else
				{
					add_type = BST_NEW_NODE_ADD;
				}

				break;
			}

		}
	}
	return ptemp_find_node;

}

// ����������������
template< class key_char_value_t,
class nodes_allocator_t,
class String_base,
class _TST_node_t >
inline _TST_node_t* avl_tst_tree_insert(_TST_node_t* & pTst_root_node,
		const key_char_value_t* pkey_string,
		tst_buffer_size key_string_size,
		nodes_allocator_t& node_allocator,
		avl_result & add_result,
		tst_node_count_val& node_count)
{
	//typedef pecker_share_string_base_t< key_char_value_t,__cmp_t,char_allocater_t> String_base;
	typedef pecker_value_compare_extern< String_base > string_cmp_;

	if (null == pkey_string || 0 >= key_string_size)
	{
		add_result = P_ERR;
		return null;
	}

	if (null == pTst_root_node) // ���ڵ�Ϊ�գ��½�һ���������ڵ���Ϊ���ڵ�
	{
		_TST_node_t* newnode = node_allocator.create_node();
		newnode->_M_left = null;
		newnode->_M_right = null;
		newnode->_M_height = 0;
		newnode->_M_legal_flag = HAS_VALUE_TST_NODE;
		newnode->_M_middle_node = null;
		newnode->_M_middle_root_node = null;
		newnode->key.init(pkey_string,key_string_size);
		pTst_root_node = newnode;
		++node_count;
		add_result = P_OK;
		return newnode;
	}
	string_size_t nsame_begin_char_count = 0;
	string_size_t ntravl_string_size = 0;

	_TST_node_t** pLast_reference_node = null;
	TST_FIND_ADD_TYPE add_type;
	_TST_node_t* pfind_add_node = avl_tst_tree_find_add_node< key_char_value_t,_TST_node_t >
	(pTst_root_node,pLast_reference_node,pkey_string,key_string_size,add_type,
			nsame_begin_char_count,
			ntravl_string_size);// ���Ҳ������ݽڵ�
	_TST_node_t* pNew_add_node = null;
	_TST_node_t* pmid_root_node = null;
	add_result = P_OK;

	switch(add_type)
	{
		case NODE_EXSIT:
		if (HAS_VALUE_TST_NODE != pfind_add_node->_M_legal_flag)
		{
			pfind_add_node->_M_legal_flag = HAS_VALUE_TST_NODE;
		}
		else
		{
			add_result = P_UNIQUE_ERR;
		}
		pNew_add_node = pfind_add_node;
		break;

		case BST_NEW_NODE_ADD:
		{
			string_cmp_ string_cmp_type;
			_TST_node_t* newnode = node_allocator.create_node();

			if (null == newnode)
			{
				add_result = P_ERR;
				break;
			}
			++node_count;

			newnode->key.init( (pkey_string+ntravl_string_size),(key_string_size - ntravl_string_size));
			pmid_root_node = (_TST_node_t*)(pfind_add_node->_M_middle_root_node);
			newnode->_M_legal_flag = HAS_VALUE_TST_NODE;
			newnode->_M_middle_node = null;
			newnode->_M_middle_root_node = pmid_root_node;

			if (null != pmid_root_node)
			{
				pNew_add_node = avl_tree_add< String_base,string_cmp_,_TST_node_t >((_TST_node_t*&)(pmid_root_node->_M_middle_node),newnode,string_cmp_type,add_result);
			}
			else
			{
				pNew_add_node = avl_tree_add<String_base,string_cmp_,_TST_node_t>(pTst_root_node,newnode,string_cmp_type,add_result);
			}
		}
		break;

		case TST_NEW_NODE_ADD:
		{
			_TST_node_t* newnode = node_allocator.create_node();

			if (null == newnode)
			{
				add_result = P_ERR;
				break;
			}
			++node_count;

			newnode->key.init( (pkey_string+ntravl_string_size),(key_string_size - ntravl_string_size));
			pmid_root_node = pfind_add_node;
			newnode->_M_legal_flag = HAS_VALUE_TST_NODE;
			newnode->_M_middle_node = null;
			newnode->_M_middle_root_node = pfind_add_node;
			if (null == pfind_add_node->_M_middle_node) // ���м���Ϊ�յ�ʱ��ֱ�ӽ������ڵ���Ϊ�м���
			{
				pfind_add_node->_M_middle_node = newnode;
				newnode->_M_left = null;
				newnode->_M_right = null;
				newnode->_M_height = 0;
				pNew_add_node = newnode;
			}
			else // ���м���ǿյ�ʱ�򣬽�pfind_add_node�м�����Ϊ�����ĸ���㣬������㰴AVL���Ĳ��뷽ʽ��������
			{
				string_cmp_ string_cmp_type;
				pNew_add_node = avl_tree_add< String_base,string_cmp_,_TST_node_t >((_TST_node_t*&)(pfind_add_node->_M_middle_node),newnode,string_cmp_type,add_result);
			}
		}
		break;

		case CLIP_NODE:
		{
			_TST_node_t* newnode = node_allocator.create_node();
			if (null == newnode)
			{
				add_result = P_ERR;
				break;
			}
			++node_count;

			pmid_root_node = (_TST_node_t*)(pfind_add_node->_M_middle_root_node);
			newnode->_M_legal_flag = HAS_VALUE_TST_NODE;
			pfind_add_node->key.clip_string_in_share_buffer_right_part(newnode->key,nsame_begin_char_count);

			newnode->_M_height = pfind_add_node->_M_height;
			newnode->_M_right = pfind_add_node->_M_right;
			newnode->_M_left = pfind_add_node->_M_left;
			newnode->_M_middle_node = pfind_add_node;

			newnode->_M_middle_root_node = pmid_root_node;

			if (pfind_add_node == pTst_root_node)
			{
				pTst_root_node = newnode;
			}
			else if (pmid_root_node && pmid_root_node->_M_middle_node == pfind_add_node)
			{
				pmid_root_node->_M_middle_node = newnode;
			}
			else if (null != pLast_reference_node)
			{
				*pLast_reference_node = newnode;
			}

			pfind_add_node->_M_middle_root_node = newnode;
			pfind_add_node->_M_height = 0;
			pfind_add_node->_M_right = null;
			pfind_add_node->_M_left = null;
			pNew_add_node = newnode;
		}
		break;

		case CLIP_AND_ADD_NODE:
		{
			_TST_node_t* newnode = node_allocator.create_node();
			if (null == newnode)
			{
				add_result = P_ERR;
				break;
			}

			_TST_node_t* newnode2 = node_allocator.create_node();
			if (null == newnode2)
			{
				add_result = P_ERR;
				break;
			}
			node_count += 2;

			pmid_root_node = (_TST_node_t*)(pfind_add_node->_M_middle_root_node);
			newnode->_M_legal_flag = NO_VALUE_TST_NODE;
			pfind_add_node->key.clip_string_in_share_buffer_right_part(newnode->key,nsame_begin_char_count);
			newnode->_M_height = pfind_add_node->_M_height;
			newnode->_M_right = pfind_add_node->_M_right;
			newnode->_M_left = pfind_add_node->_M_left;
			newnode->_M_middle_node = pfind_add_node;
			newnode->_M_middle_root_node = pmid_root_node;

			if (pfind_add_node == pTst_root_node)
			{
				pTst_root_node = newnode;
			}
			else if (pmid_root_node && pmid_root_node->_M_middle_node == pfind_add_node)
			{
				pmid_root_node->_M_middle_node = newnode;
			}
			else if (null != pLast_reference_node)
			{
				*pLast_reference_node = newnode;
			}

			pfind_add_node->_M_middle_root_node = newnode;
			pfind_add_node->_M_height = 1;



			newnode2->key.init( (pkey_string+ntravl_string_size),(key_string_size - ntravl_string_size));
			newnode2->_M_legal_flag = HAS_VALUE_TST_NODE;
			newnode2->_M_middle_root_node = newnode;
			newnode2->_M_middle_node = null;

			newnode2->_M_height = 0;
			newnode2->_M_right = null;
			newnode2->_M_left = null;

			pmid_root_node = newnode;

			int cmp_result = newnode2->key.compare(pfind_add_node->key);
			if (cmp_result > 0)
			{
				pfind_add_node->_M_right = newnode2;
				pfind_add_node->_M_left = null;
			}
			else
			{
				pfind_add_node->_M_right = null;
				pfind_add_node->_M_left = newnode2;
			}
			pNew_add_node = newnode2;
		}
		break;

		case ADD_ERR:
		add_result = P_ERR;
		break;
		default:
		add_result = P_FAIL;
		break;
	}

	return pNew_add_node;
}

template< class key_char_value_t, 
class nodes_allocator_t,
class String_base,
class _TST_node >
inline avl_result avl_tst_tree_erase
(_TST_node* &pTst_root_node,
		const key_char_value_t* pkey_string,
		tst_buffer_size key_string_size,
		nodes_allocator_t& node_allocator,
		tst_node_count_val& node_count)
{
	//typedef pecker_share_string_base_t< key_char_value_t,__cmp_t,char_allocater_t> String_base;
	typedef pecker_value_compare_extern< String_base > string_cmp_;

	if (null == pkey_string || 0 >= key_string_size)
	{
		return P_ERR;
	}

	if (null == pTst_root_node)
	{
		return P_OK;
	}

	_TST_node* pfind_remove_node = avl_tst_tree_find_referance<key_char_value_t,_TST_node>
	(pTst_root_node,pkey_string,key_string_size);  // ���ұ�ɾ���
	if (null == pfind_remove_node)
	{															// �����ڱ�ɾ���
		return P_SUCCESS;
	}

	if (null != pfind_remove_node->_M_middle_node) // ����ɾ���ڵ㣬��ɾ���ڵ�����м��㣬�򽫽��Ϸ���ʶ���ó� NO_VALUE_TST_NODE
	{
		pfind_remove_node->_M_legal_flag = NO_VALUE_TST_NODE;
		return P_OK;
	}

	string_cmp_ string_cmp_type;
	avl_result remove_result;
	_TST_node* premoved_node = null;
	_TST_node* premoved_middle_root_node = (_TST_node*)(pfind_remove_node->_M_middle_root_node);

	// ɾ���ڵ�
	if (premoved_middle_root_node == null)
	{
		premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
		(pTst_root_node,pfind_remove_node->key,string_cmp_type,remove_result);
	}
	else
	{
		premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
		( (_TST_node*&)(premoved_middle_root_node->_M_middle_node),pfind_remove_node->key,string_cmp_type,remove_result);
	}

	if (null == premoved_node)
	{
		return P_ERR;
	}
	else if (P_OK != remove_result)
	{
		return remove_result;
	}

	premoved_node->_M_legal_flag = INVALID_TST_NODE; // ���ó���Ч�ڵ���Чֵ����Ҫ��ʹ���ڴ��ֱ��ö��ʱ����
	node_allocator.release_node(premoved_node);
	--node_count;

	while (premoved_middle_root_node) // ɾ���ڵ��������㣬������ɾ�������Ϊ�м���Ϊnull���Ϸ���ʶ������HAS_VALUE_TST_NODE
	{
		premoved_node = premoved_middle_root_node;
		premoved_middle_root_node = (_TST_node*)(premoved_node->_M_middle_root_node);

		if (null == premoved_node->_M_middle_node && HAS_VALUE_TST_NODE != premoved_node->_M_legal_flag)
		{
			if (premoved_middle_root_node == null)
			{
				premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
				(pTst_root_node,premoved_node->key,string_cmp_type,remove_result);
			}
			else
			{
				premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
				( (_TST_node*&)(premoved_middle_root_node->_M_middle_node),premoved_node->key,string_cmp_type,remove_result);
			}
			if (null == premoved_node)
			{
				return P_ERR;
			}
			else if (P_OK != remove_result)
			{
				return remove_result;
			}
			premoved_node->_M_legal_flag = INVALID_TST_NODE; // ���ó���Ч�ڵ���Чֵ����Ҫ��ʹ���ڴ��ֱ��ö��ʱ����
			node_allocator.release_node(premoved_node);
			--node_count;
		}
		else
		{
			break;
		}

	}
	return P_OK;
}

template< class key_char_value_t,
class nodes_allocator_t,
class String_base,
class _TST_node >
inline avl_result avl_tst_tree_erase
(_TST_node* &pTst_root_node,
		_TST_node* pTst_del_node,
		nodes_allocator_t& node_allocator,
		tst_node_count_val& node_count)
{
	//typedef pecker_share_string_base_t< key_char_value_t,__cmp_t,char_allocater_t> String_base;
	typedef pecker_value_compare_extern< String_base > string_cmp_;

	if (null == pTst_root_node && null != pTst_del_node)
	{
		return P_ERR;
	}

	_TST_node* pfind_remove_node = pTst_del_node;
	if (null == pfind_remove_node) // �����ڱ�ɾ���
	{
		return P_SUCCESS;
	}

	if (null != pfind_remove_node->_M_middle_node) // ����ɾ���ڵ㣬��ɾ���ڵ�����м��㣬�򽫽��Ϸ���ʶ���ó� NO_VALUE_TST_NODE
	{
		pfind_remove_node->_M_legal_flag = NO_VALUE_TST_NODE;
		return P_OK;
	}

	string_cmp_ string_cmp_type;
	avl_result remove_result;
	_TST_node* premoved_node = null;
	_TST_node* premoved_middle_root_node = (_TST_node*)(pfind_remove_node->_M_middle_root_node);

	// ɾ���ڵ�
	if (premoved_middle_root_node == null)
	{
		premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
		(pTst_root_node,pfind_remove_node->key,string_cmp_type,remove_result);
	}
	else
	{
		premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
		( (_TST_node*&)(premoved_middle_root_node->_M_middle_node),pfind_remove_node->key,string_cmp_type,remove_result);
	}

	if (null == premoved_node)
	{
		return P_ERR;
	}
	else if (P_OK != remove_result)
	{
		return remove_result;
	}

	premoved_node->_M_legal_flag = INVALID_TST_NODE;
	node_allocator.release_node(premoved_node);
	--node_count;

	while (premoved_middle_root_node) // ɾ���ڵ��������㣬������ɾ�������Ϊ�м���Ϊnull���Ϸ���ʶ������HAS_VALUE_TST_NODE
	{
		premoved_node = premoved_middle_root_node;
		premoved_middle_root_node = (_TST_node*)(premoved_node->_M_middle_root_node);

		if (null == premoved_node->_M_middle_node && HAS_VALUE_TST_NODE != premoved_node->_M_legal_flag)
		{
			if (premoved_middle_root_node == null)
			{
				premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
				(pTst_root_node,premoved_node->key,string_cmp_type,remove_result);
			}
			else
			{
				premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
				( (_TST_node*&)(premoved_middle_root_node->_M_middle_node),premoved_node->key,string_cmp_type,remove_result);
			}
			if (null == premoved_node)
			{
				return P_ERR;
			}
			else if (P_OK != remove_result)
			{
				return remove_result;
			}
			premoved_node->_M_legal_flag = INVALID_TST_NODE;
			node_allocator.release_node(premoved_node);
			--node_count;
		}
		else
		{
			break;
		}

	}
	return P_OK;
}

template< class key_char_value_t, 
class String_base,
class _TST_node >
inline avl_result avl_tst_tree_remove
(_TST_node* &pTst_root_node,
		_TST_node* pTst_remove_node,
		_TST_node* &pTst_remove_node_list,
		_TST_node* &pTst_remove_set_no_value_node,
		tst_node_count_val& node_count)
{
	//typedef pecker_share_string_base_t< key_char_value_t,__cmp_t,char_allocater_t> String_base;
	typedef pecker_value_compare_extern< String_base > string_cmp_;
	pTst_remove_node_list = null;
	if (null == pTst_root_node && null != pTst_remove_node)
	{
		return P_ERR;
	}

	_TST_node* pfind_remove_node = pTst_remove_node;
	if (null == pfind_remove_node) // �����ڱ�ɾ���
	{
		return P_SUCCESS;
	}

	if (null != pfind_remove_node->_M_middle_node) // ����ɾ���ڵ㣬��ɾ���ڵ�����м��㣬�򽫽��Ϸ���ʶ���ó� NO_VALUE_TST_NODE
	{
		pfind_remove_node->_M_legal_flag = NO_VALUE_TST_NODE;
		pTst_remove_set_no_value_node = pfind_remove_node;
		return P_OK;
	}

	string_cmp_ string_cmp_type;
	avl_result remove_result;
	_TST_node* premoved_node = null;
	_TST_node* premoved_middle_root_node = (_TST_node*)(pfind_remove_node->_M_middle_root_node);
	_TST_node* premove_node_list = null;
	pfind_remove_node = null;
	// ɾ���ڵ�
	if (premoved_middle_root_node == null)
	{
		premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
		(pTst_root_node,pfind_remove_node->key,string_cmp_type,remove_result);
	}
	else
	{
		premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
		( (_TST_node*&)(premoved_middle_root_node->_M_middle_node),pfind_remove_node->key,string_cmp_type,remove_result);
	}

	if (null == premoved_node)
	{
		return P_ERR;
	}
	else if (P_OK != remove_result)
	{
		return remove_result;
	}

	premoved_node->_M_legal_flag = INVALID_TST_NODE;
	--node_count;

	premoved_node->_M_right = null;
	pTst_remove_node_list = premoved_node;
	premove_node_list = pTst_remove_node_list;

	while (premoved_middle_root_node) // ɾ���ڵ��������㣬������ɾ�������Ϊ�м���Ϊnull���Ϸ���ʶ������HAS_VALUE_TST_NODE
	{
		premoved_node = premoved_middle_root_node;
		premoved_middle_root_node = (_TST_node*)(premoved_node->_M_middle_root_node);

		if (null == premoved_node->_M_middle_node && HAS_VALUE_TST_NODE != premoved_node->_M_legal_flag)
		{
			if (premoved_middle_root_node == null)
			{
				premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
				(pTst_root_node,premoved_node->key,string_cmp_type,remove_result);
			}
			else
			{
				premoved_node = avl_tree_remove<String_base,string_cmp_,_TST_node>
				( (_TST_node*&)(premoved_middle_root_node->_M_middle_node),premoved_node->key,string_cmp_type,remove_result);
			}
			if (null == premoved_node)
			{
				premove_node_list->_M_right = null;
				return P_ERR;
			}
			else if (P_OK != remove_result)
			{
				premove_node_list->_M_right = null;
				return remove_result;
			}
			premoved_node->_M_legal_flag = INVALID_TST_NODE;
			--node_count;

			premove_node_list->_M_right = premoved_node;
			premove_node_list = premoved_node;
		}
		else
		{
			break;
		}

	}

	premove_node_list->_M_right = null;
	return P_OK;
}

template< class key_char_value_t,
class String_base,
class _TST_node >
inline avl_result avl_tst_tree_remove
(_TST_node* &pTst_root_node,
		const key_char_value_t* pkey_string,
		string_size_t key_string_size,
		_TST_node* &pTst_remove_node_list,
		_TST_node* &pTst_remove_set_no_value_node,
		tst_node_count_val& node_count)
{
	//typedef pecker_share_string_base_t< key_char_value_t,__cmp_t,char_allocater_t> String_base;
	if (null == pkey_string || 0 >= key_string_size)
	{
		return P_ERR;
	}

	if (null == pTst_root_node)
	{
		return P_OK;
	}

	_TST_node* pfind_remove_node = avl_tst_tree_find_referance<key_char_value_t,_TST_node > // ���ұ�ɾ���
	(pTst_root_node,pkey_string,key_string_size);
	return avl_tst_tree_remove< key_char_value_t,// __cmp_t,
		//char_allocater_t,
		String_base, _TST_node >(pTst_root_node,pfind_remove_node,pTst_remove_node_list,pTst_remove_set_no_value_node,node_count);
}

template< class _TST_node ,class nodes_allocator_t, class Nodes_stack, class Nodes_ref_stack  >
inline HResult copy_tst_tree(const _TST_node* psrc_bst_root_node,_TST_node* &pdec_bst_root_node,
	nodes_allocator_t &Node_allocator,Nodes_stack &node_paths,Nodes_ref_stack &node_ref_paths)//,Nodes_stack &mid_nodes)
{
	const _TST_node* ptemp_node = psrc_bst_root_node;
	_TST_node** ptemp_copy_node = &pdec_bst_root_node;
	//mid_nodes.push(null);
	_TST_node* ptemp_mid_root = null;
	while (ptemp_node)
	{
		
		_TST_node* pcopy_node = Node_allocator.create_node();

		if (null != pcopy_node)
		{
			*pcopy_node = *((_TST_node*)ptemp_node);
			pcopy_node->_M_left = null;
			pcopy_node->_M_right = null;
			pcopy_node->_M_middle_node = null;
			pcopy_node->_M_middle_root_node = ptemp_mid_root;

#ifdef TST_DEBUG_
			print_pecker_string_chars< pecker_share_string_base_t<char, pecker_value_compare<char>,pecker_simple_allocator<char> > >(pcopy_node->key);
#endif
		}
		else
		{
			return P_ERR;
		}

		*ptemp_copy_node = pcopy_node;
		

		if (ptemp_node->_M_right)
		{
			node_ref_paths.push( (_TST_node**)&(pcopy_node->_M_right) );
			node_paths.push( (_TST_node*)(ptemp_node->_M_right) );
		}

		if (ptemp_node->_M_middle_node)
		{
			node_ref_paths.push( (_TST_node**)&(pcopy_node->_M_middle_node) );
			node_paths.push( (_TST_node*)(ptemp_node->_M_middle_node) );
		}


		if (ptemp_node->_M_left)
		{
			ptemp_mid_root = ptemp_node->_M_middle_root_node;
			ptemp_node = (_TST_node*)(ptemp_node->_M_left);
			ptemp_copy_node =  (_TST_node**)&(pcopy_node->_M_left);
		}
		else
		{
			if (node_paths.get_size() <= 0)
			{
				break;
			}
			else
			{
				ptemp_node = *(node_paths.end());
				ptemp_mid_root = ptemp_node->_M_middle_root_node;
				ptemp_copy_node = (_TST_node**)*(node_ref_paths.end());
				node_paths.pop();
				node_ref_paths.pop();
			}
		}
		
	}
	return P_OK;
}

template< class String_key_t, class _TST_node ,class nodes_allocator_t, class Nodes_stack  >
inline HResult clear_tst_tree(_TST_node* &bst_root_node,//tst_node_count_val &node_count,
	nodes_allocator_t &Node_allocator,Nodes_stack& nodes_path )
{
	if (null == bst_root_node)
	{
		return P_SUCCESS;
	}
	
	_TST_node* ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >(bst_root_node,nodes_path);
	_TST_node* plast_temp_node = null;
	nodes_path.pop();
	_TST_node** pptmp_top_node = (_TST_node**)nodes_path.get_end_reference();
	_TST_node* ptmp_top_node = null;

	while( null != pptmp_top_node && null != *pptmp_top_node)
	{
		ptmp_top_node = *pptmp_top_node;
		
		if (ptemp_node->_M_right)
		{
			nodes_path.push(ptemp_node);
			ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >( (_TST_node*)(ptemp_node->_M_right),nodes_path);
			nodes_path.pop();
			pptmp_top_node = (_TST_node**)nodes_path.get_end_reference();
			continue;
		}

		plast_temp_node = ptemp_node;

		if (ptemp_node == ptmp_top_node->_M_left)
		{
			ptmp_top_node->_M_left = null;
			
			if (ptmp_top_node->_M_middle_node)
			{
				ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >( (_TST_node*)(ptmp_top_node->_M_middle_node),nodes_path);
			}
			else if (ptmp_top_node->_M_right)
			{
				ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >( (_TST_node*)(ptmp_top_node->_M_right),nodes_path);
			}
			else
			{
				ptemp_node = ptmp_top_node;
			}
		}
		else if (ptemp_node == ptmp_top_node->_M_middle_node)
		{
			ptmp_top_node->_M_middle_node = null;
			
			if (ptmp_top_node->_M_right)
			{
				ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >( (_TST_node*)(ptmp_top_node->_M_right),nodes_path);
			}
			else
			{
				ptemp_node = ptmp_top_node;
			}
		}
		else if (ptemp_node == ptmp_top_node->_M_right)
		{
			ptmp_top_node->_M_right = null;
			ptemp_node = ptmp_top_node;
		}

		nodes_path.pop();
		pptmp_top_node = (_TST_node**)nodes_path.get_end_reference();

		//if (plast_temp_node->_M_left || plast_temp_node->_M_right || plast_temp_node->_M_middle_node)
		//{
		//	plast_temp_node = plast_temp_node;
		//}

#ifdef TST_DEBUG_
		String_key_t print_string = get_tst_key_string< String_key_t,_TST_node >(plast_temp_node);
		PRINT_TST_NODE_STRING(print_string);
#endif

		//--node_count;
		//if (bst_root_node == plast_temp_node)
		//{
		//	Node_allocator.release_node(plast_temp_node);
		//	break;
		//}
		//else
		//{
		//	Node_allocator.release_node(plast_temp_node);
		//}
		Node_allocator.release_node(plast_temp_node);
	}

#ifdef TST_DEBUG_
	String_key_t print_string = get_tst_key_string< String_key_t,_TST_node >(bst_root_node);
	PRINT_TST_NODE_STRING(print_string);
#endif
	Node_allocator.release_node(bst_root_node);
	bst_root_node = null;

	return P_OK;
}

template< class String_key_t, class _TST_node ,class nodes_allocator_t, class Nodes_stack  >
inline HResult clear_tst_tree(_TST_node* &bst_root_node,//tst_node_count_val &node_count,
	nodes_allocator_t &Node_allocator,Nodes_stack& nodes_path,tst_node_count_val release_count )
	{
		if (null == bst_root_node || release_count <= 0)
		{
			return P_SUCCESS;
		}

		_TST_node* ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >(bst_root_node,nodes_path);
		_TST_node* plast_temp_node = null;
		nodes_path.pop();
		_TST_node** pptmp_top_node = (_TST_node**)nodes_path.get_end_reference();
		_TST_node* ptmp_top_node = null;
		tst_node_count_val icount = 0;

		while( null != pptmp_top_node && null != *pptmp_top_node)
		{
			ptmp_top_node = *pptmp_top_node;

			if (ptemp_node->_M_right)
			{
				nodes_path.push(ptemp_node);
				ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >( (_TST_node*)(ptemp_node->_M_right),nodes_path);
				nodes_path.pop();
				pptmp_top_node = (_TST_node**)nodes_path.get_end_reference();
				continue;
			}

			plast_temp_node = ptemp_node;

			if (ptemp_node == ptmp_top_node->_M_left)
			{
				ptmp_top_node->_M_left = null;

				if (ptmp_top_node->_M_middle_node)
				{
					ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >( (_TST_node*)(ptmp_top_node->_M_middle_node),nodes_path);
				}
				else if (ptmp_top_node->_M_right)
				{
					ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >( (_TST_node*)(ptmp_top_node->_M_right),nodes_path);
				}
				else
				{
					ptemp_node = ptmp_top_node;
				}
			}
			else if (ptemp_node == ptmp_top_node->_M_middle_node)
			{
				ptmp_top_node->_M_middle_node = null;

				if (ptmp_top_node->_M_right)
				{
					ptemp_node = (_TST_node*)leftmost_tst_node< _TST_node, Nodes_stack >( (_TST_node*)(ptmp_top_node->_M_right),nodes_path);
				}
				else
				{
					ptemp_node = ptmp_top_node;
				}
			}
			else if (ptemp_node == ptmp_top_node->_M_right)
			{
				ptmp_top_node->_M_right = null;
				ptemp_node = ptmp_top_node;
			}

			nodes_path.pop();
			pptmp_top_node = (_TST_node**)nodes_path.get_end_reference();

			//if (plast_temp_node->_M_left || plast_temp_node->_M_right || plast_temp_node->_M_middle_node)
			//{
			//	plast_temp_node = plast_temp_node;
			//}

#ifdef TST_DEBUG_
			String_key_t print_string = get_tst_key_string< String_key_t,_TST_node >(plast_temp_node);
			PRINT_TST_NODE_STRING(print_string);
#endif

			//--node_count;
			//if (bst_root_node == plast_temp_node)
			//{
			//	Node_allocator.release_node(plast_temp_node);
			//	break;
			//}
			//else
			//{
			//	Node_allocator.release_node(plast_temp_node);
			//}
			Node_allocator.release_node(plast_temp_node);
			++icount;
			if (icount >= release_count)
			{
				return P_OK;
			}
		}

#ifdef TST_DEBUG_
		String_key_t print_string = get_tst_key_string< String_key_t,_TST_node >(bst_root_node);
		PRINT_TST_NODE_STRING(print_string);
#endif
		Node_allocator.release_node(bst_root_node);
		bst_root_node = null;

		return P_OK;
	}
PECKER_END

#endif
