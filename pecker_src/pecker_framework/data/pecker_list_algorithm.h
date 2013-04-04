/*
 *  pecker_list_algorithm.h
 *
 *  Created on: 2012-11-21
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_LIST_ALGORITHM_H_
#define PECKER_LIST_ALGORITHM_H_

#include "../CPeckerObject.h"
PECKER_BEGIN

typedef HResult	 list_result;
typedef nSize			 list_size;

struct pecker_linked_list_node_base
{
	pecker_linked_list_node_base* _M_pre_node;
	pecker_linked_list_node_base* _M_next_node;
};

template < class node_item_t >
struct pecker_linked_list_node : public pecker_linked_list_node_base
{
	node_item_t value;
};

template < class node_item_t >
struct pecker_linked_list_node_t
{
	pecker_linked_list_node_t* _M_pre_node;
	pecker_linked_list_node_t* _M_next_node;

	node_item_t value;
};

template < class linked_list_node_t >
inline list_result push_back_list_node(linked_list_node_t*& pbegin_node,linked_list_node_t* padd_node)
{
	if (null != padd_node)
	{
		
		if (null == pbegin_node)
		{
			pbegin_node = padd_node;
			padd_node->_M_pre_node = null;
			padd_node->_M_next_node = null;
		}
		else
		{
			linked_list_node_t* plast_node = pbegin_node;
			while (plast_node->_M_next_node)
			{
				plast_node = (linked_list_node_t*)(plast_node->_M_next_node);
			}
			plast_node->_M_next_node = padd_node;
			padd_node->_M_pre_node = plast_node;
			padd_node->_M_next_node = null;
		}

		return P_OK;
	}
	
	return P_ERR;
}

template < class linked_list_node_t >
inline list_result push_fornt_list_node(linked_list_node_t*& pend_node,linked_list_node_t* padd_node)
{
	if (null != padd_node)
	{

		if (null == pend_node)
		{
			pend_node = padd_node;
			padd_node->_M_pre_node = null;
			padd_node->_M_next_node = null;
		}
		else
		{
			linked_list_node_t* plast_node = pend_node;
			while (plast_node->_M_pre_node)
			{
				plast_node = (linked_list_node_t*)(plast_node->_M_pre_node);
			}
			plast_node->_M_pre_node = padd_node;
			padd_node->_M_next_node = plast_node;
			padd_node->_M_pre_node = null;
		}

		return P_OK;
	}

	return P_ERR;
}

template < class linked_list_node_t >
inline list_result swap_list_node(linked_list_node_t* pfirst_node,linked_list_node_t* psecond_node)
{
	if (pfirst_node == psecond_node)
	{
		return P_SUCCESS;
	}
	else if (null == pfirst_node || null == psecond_node)
	{
		return P_ERR;
	}

	linked_list_node_t* pfirst_node_pre = pfirst_node->_M_pre_node;
	linked_list_node_t* pfirst_node_next = pfirst_node->_M_next_node;
	linked_list_node_t* psecond_node_pre = psecond_node->_M_pre_node;
	linked_list_node_t* psecond_node_next = psecond_node->_M_next_node;

	if (pfirst_node_pre == psecond_node_next)// second node <---> node <---> first node
	{
		pfirst_node_pre->_M_pre_node = pfirst_node;
		pfirst_node_pre->_M_next_node = psecond_node;
	}
	else if (pfirst_node_next == psecond_node_pre)// first node <---> node <---> second node
	{
		pfirst_node_next->_M_pre_node = psecond_node;
		pfirst_node_next->_M_next_node = pfirst_node;
	}
	else if (pfirst_node_pre != psecond_node && pfirst_node_next != psecond_node)// 非相邻结点
	{
		if (psecond_node_next == pfirst_node || psecond_node_pre == pfirst_node)
		{
			return P_ERR;
		}
		pfirst_node_pre->_M_next_node = psecond_node;
		pfirst_node_next->_M_pre_node = psecond_node;
		psecond_node_pre->_M_next_node = pfirst_node;
		psecond_node_next->_M_pre_node = pfirst_node;
	}

	pfirst_node->_M_pre_node = psecond_node_pre;
	pfirst_node->_M_next_node = psecond_node_next;
	psecond_node->_M_pre_node = pfirst_node_pre;
	psecond_node->_M_next_node = pfirst_node_next;

	return P_OK;
}

template < class linked_list_node_t >
inline list_result remove_list_node(linked_list_node_t* premove_node)
{
	if (null == premove_node)
	{
		return P_SUCCESS;
	}
	else
	{
		linked_list_node_t* ptmp_next_node = (linked_list_node_t*)(premove_node->_M_next_node);
		linked_list_node_t* ptmp_pre_node = (linked_list_node_t*)(premove_node->_M_pre_node);
		
		if (null != ptmp_next_node)
		{
			ptmp_next_node->_M_pre_node = ptmp_pre_node;
		}

		if (null != ptmp_pre_node)
		{
			ptmp_pre_node->_M_next_node = ptmp_next_node;
		}

		return P_OK;
	}

}

template < class linked_list_node_t >
inline list_result remove_list_nodes_unsafe(linked_list_node_t* pbegin_node,linked_list_node_t* pend_node)
{
	if (pbegin_node == pend_node)
	{
		return remove_list_node< linked_list_node_t >(pbegin_node);
	}
	else if (null == pbegin_node)
	{
		return remove_list_node< linked_list_node_t >(pend_node);
	}
	else if (null == pend_node)
	{
		return remove_list_node< linked_list_node_t >(pbegin_node);
	}

	linked_list_node_t* ptmp_next_node = (linked_list_node_t*)(pend_node->_M_next_node);
	linked_list_node_t* ptmp_pre_node = (linked_list_node_t*)(pbegin_node->_M_pre_node);

	ptmp_pre_node->_M_next_node = ptmp_next_node;
	ptmp_next_node->_M_pre_node = ptmp_pre_node;
	return P_OK;
}

template < class linked_list_node_t >
inline list_result insert_list_node_next(linked_list_node_t*& pnode_to_be_add,linked_list_node_t* padd_node)
{
	if (null != padd_node)
	{

		if (null == pnode_to_be_add)
		{
			pnode_to_be_add = padd_node;
			padd_node->_M_pre_node = null;
			padd_node->_M_next_node = null;
		}
		else
		{
			linked_list_node_t* pnext_node = (linked_list_node_t*)(pnode_to_be_add->_M_next_node);
			if (null != pnext_node)
			{
				pnext_node->_M_pre_node = padd_node;
			}
			pnode_to_be_add->_M_next_node = padd_node;
			padd_node->_M_pre_node = pnode_to_be_add;
			padd_node->_M_next_node = pnext_node;
		}

		return P_OK;
	}

	return P_ERR;
}

template < class linked_list_node_t >
inline list_result insert_list_node_pre(linked_list_node_t*& pnode_to_be_add,linked_list_node_t* padd_node)
{
	if (null != padd_node)
	{

		if (null == pnode_to_be_add)
		{
			pnode_to_be_add = padd_node;
			padd_node->_M_pre_node = null;
			padd_node->_M_next_node = null;
		}
		else
		{
			linked_list_node_t* pre_node = (linked_list_node_t*)(pnode_to_be_add->_M_pre_node);
			if (null != pre_node)
			{
				pre_node->_M_next_node = padd_node;
			}
			pnode_to_be_add->_M_pre_node = padd_node;
			padd_node->_M_next_node = pnode_to_be_add;
			padd_node->pre_node = pre_node;
		}

		return P_OK;
	}

	return P_ERR;
}

PECKER_END

#endif // PECKER_LIST_ALGORITHM_H_