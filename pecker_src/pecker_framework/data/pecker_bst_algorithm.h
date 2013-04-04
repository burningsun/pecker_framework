/*
 *  pecker_bst_iterator.h
 *
 *  Created on: 2012-12-20
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_BST_ALGORITHM_H_
#define PECKER_BST_ALGORITHM_H_

#include "pecker_stack.h"

PECKER_BEGIN

template< class BST_node_t >
inline  const BST_node_t* minimum_bst_node(const BST_node_t* pbst_node)
{
	while (null != pbst_node->_M_left )
	{
		pbst_node = (const BST_node_t*)(pbst_node->_M_left);
	}
	return pbst_node;
}

template< class BST_node_t >
inline  const BST_node_t* maximum_bst_node(const BST_node_t* pbst_node)
{
	while (null != pbst_node->_M_right) 
	{
		pbst_node =  (const BST_node_t*)(pbst_node->_M_right);
	}
	return pbst_node;
}

template< class BST_node_t ,class Nodes_stack >
inline  const BST_node_t* minimum_bst_node(const BST_node_t* pbst_node,Nodes_stack &node_paths)
{
	if (null == pbst_node)
	{
		return null;
	}
	node_paths.push(pbst_node);
	while(null != pbst_node->_M_left)
	{
		pbst_node = ( const BST_node_t*)(pbst_node->_M_left);
		node_paths.push(pbst_node);
	}
	return pbst_node;
}

template< class BST_node_t ,class Nodes_stack >
inline  const BST_node_t* maximum_bst_node(const BST_node_t* pbst_node,Nodes_stack &node_paths)
{
	if (null == pbst_node)
	{
		return null;
	}
	node_paths.push(pbst_node);
	while(null != pbst_node->_M_right)
	{
		pbst_node =  (const BST_node_t*)(pbst_node->_M_right);
		node_paths.push(pbst_node);
	}
	return pbst_node;
}

template< class BST_node_t ,class Nodes_stack >
inline  const BST_node_t* leftmost_tst_node(const BST_node_t* pbst_node,Nodes_stack &node_paths)
{
	if (null == pbst_node)
	{
		return null;
	}

	node_paths.push(pbst_node);
	do
	{
		while (null != pbst_node->_M_left )
		{
			pbst_node =  (const BST_node_t*)(pbst_node->_M_left);
			node_paths.push(pbst_node);
		}

		if (null != pbst_node->_M_middle_node)
		{
			pbst_node =  (const BST_node_t*)(pbst_node->_M_middle_node);
			node_paths.push(pbst_node);
		}
	}while(null != pbst_node->_M_left || null != pbst_node->_M_middle_node);


	return pbst_node;//*node_paths.get_end_reference();
}


template< class BST_node_t ,class Nodes_stack >
inline  const BST_node_t* maximum_tst_node(const BST_node_t* pbst_node,Nodes_stack &node_paths)
{
	if (null == pbst_node)
	{
		return null;
	}

	node_paths.push(pbst_node);
	do
	{
		while (null != pbst_node->_M_right )
		{
			pbst_node =  (const BST_node_t*)(pbst_node->_M_right);
			node_paths.push(pbst_node);
		}

		if (null != pbst_node->_M_middle_node)
		{
			pbst_node =  (const BST_node_t*)(pbst_node->_M_middle_node);
			node_paths.push(pbst_node);
		}
	}while(null != pbst_node->_M_right || null != pbst_node->_M_middle_node);


	return pbst_node;//*node_paths.get_end_reference();
}

template< class BST_node_t ,class nodes_allocator_t, class _BSTree_posoder_iterator  >
inline HResult clear_bst_tree(BST_node_t* &bst_root_node,
													  nodes_allocator_t &Node_allocator)
{
	_BSTree_posoder_iterator this_iterator(bst_root_node);
	_M_root_node = null;
	_M_node_count = 0;

	this_iterator.init();
	//this_iterator.init(ITERATOR_INIT_RIGHT);

	while(1)
	{
		BST_node_t* perase_node = (BST_node_t*)(this_iterator.get_current_node());
		HResult result_ = this_iterator.increment_right();
		if (P_OK == result_)
		{
			Node_allocator.release_node(perase_node);
		}
		else  if (P_SUCCESS == result_)
		{
			Node_allocator.release_node(perase_node);
			break;
		}
		else if (P_ERR == result_)
		{
			return P_ERR;
		}
		else
		{
			break;
		}

	}

	return P_OK;
}

template<class key_t, class cmp_t, class BST_node_t>
inline BST_node_t* bst_tree_find_referance(BST_node_t* pBST_root_node, const key_t &key,cmp_t &_compare)
{
	while (null != pBST_root_node)
	{
		int cmp_result = _compare(key,pBST_root_node->key);
		if (cmp_result < 0)
		{
			pBST_root_node = (BST_node_t*)(pBST_root_node->_M_left);
		}
		else if (cmp_result > 0)
		{
			pBST_root_node = (BST_node_t*)(pBST_root_node->_M_right);
		}
		else
		{
			return pBST_root_node;
		}
	}
	return null;
}

template<class key_t, class cmp_t, class BST_node_t>
inline const BST_node_t* bst_tree_find(const BST_node_t* pBST_root_node, const key_t &key,const cmp_t &_compare)
{
	while (null != pBST_root_node)
	{
		int cmp_result = _compare(key,pBST_root_node->key);
		if (cmp_result < 0)
		{
			pBST_root_node = (BST_node_t*)(pBST_root_node->_M_left);
		}
		else if (cmp_result > 0)
		{
			pBST_root_node = (BST_node_t*)(pBST_root_node->_M_right);
		}
		else
		{
			return pBST_root_node;
		}
	}
	return null;
}

template< class key_t, class cmp_t, class BST_node_t  >
BST_node_t* add_bst_node(BST_node_t* &pBST_root_node,BST_node_t* pAdd_node,const cmp_t& _compare,HResult &error_code )
{
	BST_node_t* pnode_to_be_add = null;
	int cmp_result;
	error_code = P_OK;
	while (null != pBST_root_node)
	{
		cmp_result = _compare(pAdd_node->key,pBST_root_node->key);
		pnode_to_be_add = pBST_root_node;
		if (cmp_result < 0)
		{
			pBST_root_node = (BST_node_t*)(pBST_root_node->_M_left);
		}
		else if (cmp_result > 0)
		{
			pBST_root_node = (BST_node_t*)(pBST_root_node->_M_right);
		}
		else
		{
			error_code = P_UNIQUE_ERR;
			return null;
		}
	}

	if (null != pnode_to_be_add)
	{
		cmp_result = _compare(pAdd_node->key,pnode_to_be_add->key);
		pnode_to_be_add = pBST_root_node;
		if (cmp_result < 0)
		{
			pnode_to_be_add->_M_left = pAdd_node;
		}
		else if (cmp_result > 0)
		{
			pnode_to_be_add->_M_right = pAdd_node;
		}
		else
		{
			error_code = P_UNIQUE_ERR;
			return null;
		}
	}
	pAdd_node->_M_left = null;
	pAdd_node->_M_right = null;
	return pAdd_node;
}


template< class BST_node_t ,class nodes_allocator_t, class Nodes_stack, class Nodes_ref_stack  >
inline HResult copy_bst_tree(const BST_node_t* psrc_bst_root_node,BST_node_t* &pdec_bst_root_node,
	nodes_allocator_t &Node_allocator,Nodes_stack &node_paths,Nodes_ref_stack &node_ref_paths)
{
	const BST_node_t* ptemp_node = psrc_bst_root_node;
	BST_node_t** ptemp_copy_node = &pdec_bst_root_node;

	while (ptemp_node)
	{
		BST_node_t* pcopy_node = Node_allocator.create_node();

		if (null != pcopy_node)
		{
			*pcopy_node = *((BST_node_t*)ptemp_node);
			pcopy_node->_M_left = null;
			pcopy_node->_M_right = null;
		}
		else
		{
			return P_ERR;
		}

		*ptemp_copy_node = pcopy_node;


		if (ptemp_node->_M_right)
		{
			//pBST_copy_node_ref_stack[nBST_node_stack_size] = (BST_node_t**)&(pcopy_node->_M_right);
			//pBST_node_stack[nBST_node_stack_size++] = ptemp_node->_M_right;
			node_ref_paths.push( (BST_node_t**)&(pcopy_node->_M_right) );
			node_paths.push( (BST_node_t*)(ptemp_node->_M_right) );
		}
		if (ptemp_node->_M_left)
		{
			ptemp_node = ptemp_node->_M_left;
			ptemp_copy_node =  (BST_node_t**)&(pcopy_node->_M_left);
		}
		else
		{
			//if (nBST_node_stack_size <= 0)
			if (node_paths.get_size() <= 0)
			{
				break;
			}
			else
			{
				//ptemp_node = pBST_node_stack[--nBST_node_stack_size];
				//ptemp_copy_node = pBST_copy_node_ref_stack[nBST_node_stack_size];
				ptemp_node = *(node_paths.end());
				ptemp_copy_node = *(node_ref_paths.end());
				node_paths.pop();
				node_ref_paths.pop();
			}
		}
	}
	return P_OK;
}




PECKER_END
#endif