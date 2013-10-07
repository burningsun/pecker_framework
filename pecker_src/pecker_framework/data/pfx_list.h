/*
 * pfx_list.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_LIST_H_
#define		PFX_LIST_H_

#include "../pfx_defines.h"

PFX_C_EXTERN_BEGIN

typedef	struct st_linked_list_node linked_list_node_t;
struct st_linked_list_node
{
	linked_list_node_t* m_prev_node;
	linked_list_node_t* m_pnext_node;
};

PFX_INLINE linked_list_node_t* init_linked_list_node(linked_list_node_t* PARAM_INOUT pnode);

PFX_INLINE const linked_list_node_t* find_linked_list_first_node(const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE const linked_list_node_t* find_linked_list_last_node(const linked_list_node_t*	PARAM_IN	pnode);

PFX_INLINE const linked_list_node_t* insert_linked_list_node_end(linked_list_node_t* PARAM_INOUT pnode,linked_list_node_t* PARAM_INOUT pnode_add);

PFX_INLINE const linked_list_node_t* insert_linked_list_node_begin(linked_list_node_t* PARAM_INOUT pnode,linked_list_node_t* PARAM_INOUT pnode_add);

PFX_INLINE linked_list_node_t* remove_linked_list_node(linked_list_node_t* PARAM_INOUT pnode);

PFX_INLINE pfx_bool_t check_is_linked_list_first_node(const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE pfx_bool_t check_is_linked_list_last_node(const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE pfx_bool_t check_is_linked_list_only_one_node(const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE const linked_list_node_t* get_linked_list_next_node(const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE const linked_list_node_t* get_linked_list_prev_node(const linked_list_node_t* PARAM_IN	pnode);

//////////////////////////////////////////////////////////////////////////
PFX_INLINE linked_list_node_t* init_linked_list_node(linked_list_node_t* PARAM_INOUT pnode)
{
	memset(pnode,0,sizeof(linked_list_node_t));
	return pnode;
}
PFX_INLINE const linked_list_node_t* find_linked_list_first_node(const linked_list_node_t* PARAM_IN	pnode)
{
	const linked_list_node_t* pnode_bk = pnode;
	if (null == pnode)
	{
		return pnode;
	}
	while (null != pnode->m_prev_node || pnode_bk == pnode->m_prev_node)
	{
		pnode = pnode->m_prev_node;
	}
	return pnode;
}
PFX_INLINE const linked_list_node_t* find_linked_list_last_node(const linked_list_node_t*	PARAM_IN	pnode)
{
	const linked_list_node_t* pnode_bk = pnode;
	if (null == pnode)
	{
		return pnode;
	}
	while (null != pnode->m_pnext_node || pnode_bk == pnode->m_pnext_node)
	{
		pnode = pnode->m_pnext_node;
	}
	return pnode;
}
PFX_INLINE const linked_list_node_t* insert_linked_list_node_end(linked_list_node_t* PARAM_INOUT pnode,linked_list_node_t* PARAM_INOUT pnode_add)
{
	linked_list_node_t* pnode_next;

	if (null == pnode || null == pnode_add)
	{
		return null;
	}
	// 保护需插入节点的下一个节点
	pnode_next = pnode->m_pnext_node;
	
	// 插入节点
	pnode->m_pnext_node = pnode_add;
	pnode_add->m_prev_node = pnode;
	pnode_add->m_pnext_node = pnode_next;

	if (pnode_next)
	{
		pnode_next->m_prev_node = pnode_add;
	}

	return pnode_add;
}
PFX_INLINE const linked_list_node_t* insert_linked_list_node_begin(linked_list_node_t* PARAM_INOUT pnode,linked_list_node_t* PARAM_INOUT pnode_add)
{
	linked_list_node_t* pnode_pre;

	if (null == pnode || null == pnode_add)
	{
		return null;
	}
	// 保护需插入节点的前一个节点
	pnode_pre = pnode->m_prev_node;

	// 插入节点
	pnode->m_prev_node = pnode_add;
	pnode_add->m_pnext_node = pnode;
	pnode_add->m_prev_node = pnode_pre;

	if (pnode_pre)
	{
		pnode_pre->m_pnext_node = pnode_add;
	}

	return pnode_add;
}
PFX_INLINE linked_list_node_t* remove_linked_list_node(linked_list_node_t* PARAM_INOUT pnode)
{
	linked_list_node_t* pnode_next;
	linked_list_node_t* pnode_pre;

	if (null == pnode)
	{
		return null;
	}

	pnode_next = pnode->m_pnext_node;
	pnode_pre = pnode->m_prev_node;
	
	if (pnode_next)
	{
		pnode_next->m_prev_node = pnode_pre;
	}

	if (pnode_pre)
	{
		pnode_pre->m_pnext_node = pnode_next;
	}
	

	return pnode;

}

PFX_INLINE pfx_bool_t check_is_linked_list_first_node(const linked_list_node_t* PARAM_IN	pnode)
{
	if (pnode && (null == pnode->m_prev_node))
	{
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}

PFX_INLINE pfx_bool_t check_is_linked_list_last_node(const linked_list_node_t* PARAM_IN	pnode)
{
	if (pnode && (null == pnode->m_pnext_node))
	{
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}

PFX_INLINE pfx_bool_t check_is_linked_list_only_one_node(const linked_list_node_t* PARAM_IN	pnode)
{
	if (null == pnode)
	{
		return pfx_invalid;
	}
	else if ((null == pnode->m_prev_node) && (null == pnode->m_pnext_node))
	{
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}

PFX_INLINE const linked_list_node_t* get_linked_list_next_node(const linked_list_node_t* PARAM_IN	pnode)
{
	if (pnode)
	{
		return pnode->m_pnext_node;
	}
	else
	{
		return pnode;
	}
}

PFX_INLINE const linked_list_node_t* get_linked_list_prev_node(const linked_list_node_t* PARAM_IN	pnode)
{
	if (pnode)
	{
		return pnode->m_prev_node;
	}
	else
	{
		return pnode;
	}
}

PFX_C_EXTERN_END

#endif			//PFX_LIST_H_
