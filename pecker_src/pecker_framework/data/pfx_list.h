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

PFX_INLINE linked_list_node_t* init_linked_list_node (linked_list_node_t* PARAM_INOUT pnode);

PFX_INLINE const linked_list_node_t* find_linked_list_first_node (const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE const linked_list_node_t* find_linked_list_last_node (const linked_list_node_t*	PARAM_IN	pnode);

PFX_INLINE const linked_list_node_t* insert_linked_list_node_end (linked_list_node_t* PARAM_INOUT pnode,linked_list_node_t* PARAM_INOUT pnode_add);

PFX_INLINE const linked_list_node_t* insert_linked_list_node_begin (linked_list_node_t* PARAM_INOUT pnode,linked_list_node_t* PARAM_INOUT pnode_add);

PFX_INLINE linked_list_node_t* remove_linked_list_node (linked_list_node_t* PARAM_INOUT pnode);

PFX_INLINE pfx_bool_t check_is_linked_list_first_node (const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE pfx_bool_t check_is_linked_list_last_node (const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE pfx_bool_t check_is_linked_list_only_one_node (const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE const linked_list_node_t* get_linked_list_next_node (const linked_list_node_t* PARAM_IN	pnode);

PFX_INLINE const linked_list_node_t* get_linked_list_prev_node (const linked_list_node_t* PARAM_IN	pnode);

#define PFX_GET_LIST_PREV(NODE) ((NODE)->m_prev_node)
#define PFX_GET_LIST_NEXT(NODE) ((NODE)->m_pnext_node)

#define PFX_INIT_LIST_NODE(NODE) \
	do	\
	{	\
		if (null == (NODE))							\
		{														\
			break;											\
		};														\
	PFX_GET_LIST_PREV(NODE) = null;				\
	PFX_GET_LIST_NEXT(NODE) = null;				\
}while(0);

#define PFX_INSERT_LIST_NODE_END(pnode,pnode_add,pnode_next) \
	do	\
	{	\
		if (null == (pnode) || null == (pnode_add))		\
		{																				\
			(pnode_add)=null;												\
			break;																	\
		}																				\
	(pnode_next) = PFX_GET_LIST_NEXT(pnode);						\
	PFX_GET_LIST_NEXT(pnode) = (pnode_add);						\
	PFX_GET_LIST_PREV(pnode_add) = (pnode);						\
	PFX_GET_LIST_NEXT(pnode_add) = (pnode_next);			\
	if ((pnode_next))													\
	{																				\
		PFX_GET_LIST_PREV(pnode_next) = (pnode_add);		\
	}																				\
}while(0);

#define PFX_INSERT_LIST_NODE_BEGIN(pnode,pnode_add,pnode_pre) \
	do	\
	{																					\
		if (null == (pnode) || null == (pnode_add))		\
		{																				\
			(pnode_add)=null;												\
			break;																	\
		}																				\
		(pnode_pre) = PFX_GET_LIST_PREV(pnode);						\
		PFX_GET_LIST_PREV(pnode) = (pnode_add);						\
		PFX_GET_LIST_NEXT(pnode_add) = (pnode);						\
		PFX_GET_LIST_PREV(pnode_add) = (pnode_pre);				\
		if ((pnode_pre))														\
		{																				\
			PFX_GET_LIST_NEXT(pnode_pre) = (pnode_add);			\
		}																				\
}while(0);

#define PFX_REMOVE_LIST_NODE(pnode,pnode_pre,pnode_next) \
	do	\
	{																					\
		if (null == (pnode))													\
		{																				\
			break;																	\
		}																				\
		(pnode_next) = PFX_GET_LIST_NEXT(pnode);						\
		(pnode_pre) = PFX_GET_LIST_PREV(pnode);						\
		if ((pnode_next))													\
		{																				\
			PFX_GET_LIST_PREV(pnode_next) = (pnode_pre);			\
		}																				\
		if ((pnode_pre))														\
		{																				\
			PFX_GET_LIST_NEXT(pnode_pre) = (pnode_next);			\
		}																				\
}while(0);

#define PFX_INSERT_NODE_TO_LIST_NODE_END(type_name,pnode,pnode_add,pbengin_node,pend_node) \
	do	\
{																					\
	type_name pnode_next;										\
	if (null == (pnode) || null == (pnode_add))		\
	{																				\
		break;																	\
	}																				\
	if ((pend_node) == (pnode))										\
	{																				\
		(pend_node) = (pnode_add);								\
	}																				\
	if (null == (pbengin_node))									\
	{																				\
		(pbengin_node) = (pnode_add);						\
	}																				\
	PFX_INSERT_LIST_NODE_END(pnode,pnode_add,pnode_next);\
}while(0);

#define PFX_INSERT_NODE_TO_LIST_NODE_BEGIN(type_name,pnode,pnode_add,pbengin_node,pend_node) \
	do	\
{																					\
	type_name pnode_pre;										\
	if (null == (pnode) || null == (pnode_add))		\
	{																				\
		break;																	\
	}																				\
	if ((pbengin_node) == (pnode))							\
	{																				\
		(pbengin_node) = (pnode_add);						\
	}																				\
	if (null == (pend_node))										\
	{																				\
		(pend_node) = (pnode_add);								\
	}																				\
	PFX_INSERT_LIST_NODE_BEGIN(pnode,pnode_add,pnode_pre);\
}while(0);

#define PFX_REMOVE_LIST_NODE_IN_LIST(type_name,pnode,pbengin_node,pend_node) \
	do	\
{																					\
	type_name pnode_pre;										\
	type_name pnode_next;										\
	if (null == (pnode) || null == (pbengin_node)	\
		|| null == (pend_node))									\
	{																				\
		break;																	\
	}																				\
	if ((pbengin_node) == (pnode))							\
	{																				\
		(pbengin_node) = PFX_GET_LIST_PREV(pnode);				\
	};																				\
	if ((pend_node) == (pnode))									\
	{																				\
		(pend_node) = PFX_GET_LIST_NEXT(pnode);					\
	};																				\
	PFX_REMOVE_LIST_NODE(pnode,pnode_pre,pnode_next);\
}while(0);

#define PFX_CHECK_LIST_IS_EMPTY(LIST_) ((LIST_)?(((LIST_)->m_first) && ((LIST_)->m_last)):1)

//////////////////////////////////////////////////////////////////////////
PFX_INLINE linked_list_node_t* init_linked_list_node(linked_list_node_t* PARAM_INOUT pnode)
{
	memset(pnode,0,sizeof(linked_list_node_t));
	return pnode;
}
PFX_INLINE const linked_list_node_t* find_linked_list_first_node (const linked_list_node_t* PARAM_IN	pnode)
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
PFX_INLINE const linked_list_node_t* find_linked_list_last_node (const linked_list_node_t*	PARAM_IN	pnode)
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
PFX_INLINE const linked_list_node_t* insert_linked_list_node_end (linked_list_node_t* PARAM_INOUT pnode,linked_list_node_t* PARAM_INOUT pnode_add)
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
PFX_INLINE const linked_list_node_t* insert_linked_list_node_begin (linked_list_node_t* PARAM_INOUT pnode,linked_list_node_t* PARAM_INOUT pnode_add)
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
PFX_INLINE linked_list_node_t* remove_linked_list_node (linked_list_node_t* PARAM_INOUT pnode)
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

PFX_INLINE pfx_bool_t check_is_linked_list_first_node (const linked_list_node_t* PARAM_IN	pnode)
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

PFX_INLINE pfx_bool_t check_is_linked_list_last_node (const linked_list_node_t* PARAM_IN	pnode)
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

PFX_INLINE pfx_bool_t check_is_linked_list_only_one_node (const linked_list_node_t* PARAM_IN	pnode)
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

PFX_INLINE const linked_list_node_t* get_linked_list_next_node (const linked_list_node_t* PARAM_IN	pnode)
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

PFX_INLINE const linked_list_node_t* get_linked_list_prev_node (const linked_list_node_t* PARAM_IN	pnode)
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
