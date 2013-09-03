﻿/*
 * pfx_list_test.cpp
 *
 *  Created on: 2013-9-3
 *      Author: 李镇城 (cut / cutxyz)
 */

#include "../data/pfx_list.h"
#include "../native/pfx_log.h"

PFX_BEGIN

	struct my_linked_list_node
	{
		int m_item;
		linked_list_node_t m_node;
	};

	const my_linked_list_node* cov_to_my_linked_list_node(const linked_list_node_t* pnode)
	{
		if (pnode)
		{
			Long addr = (Long) pnode - sizeof(int);
			my_linked_list_node* pnew_node = (my_linked_list_node*)addr;
			return pnew_node;
		}
		return null;
	}
	static int get_list_item(const linked_list_node_t* pnode)
	{
		if (pnode)
		{
			Long addr = (Long) pnode - sizeof(int);
			my_linked_list_node* pnew_node = (my_linked_list_node*)addr;
			if (pnew_node)
			{
				return pnew_node->m_item;
			}
		}
		return -1;
	}

PFX_END



int list_test_main()
{
	my_linked_list_node nodes[256];
	for (int i=0;i<256;++i)
	{
		my_linked_list_node* ptmpnode = (my_linked_list_node*) cov_to_my_linked_list_node ( init_linked_list_node(&nodes[i].m_node) );
		if (ptmpnode)
		{
			ptmpnode->m_item = i;
		}
	}

	linked_list_node_t* pnode = &nodes[0].m_node;
	for (int i=1;i<256;++i)
	{
		pnode = (linked_list_node_t*)insert_linked_list_node_end(pnode,&nodes[i].m_node);
	}

	pnode = &nodes[0].m_node;
	for (int i=0;i<256;++i)
	{
		my_linked_list_node* ptmpnode = (my_linked_list_node*) cov_to_my_linked_list_node (pnode);
		if (ptmpnode)
		{
			PECKER_LOG_("NODE ITEM %d, NODE ADDR:%08X,NODE PREV:%08X,NODE NEXT:%08X\n",ptmpnode->m_item,pnode,pnode->m_prev_node,pnode->m_pnext_node);
		}
		else
		{
			PECKER_LOG_ERR("ptmpnode = NULL","pnode ADDR:%08X",pnode);
		}
		pnode = (linked_list_node_t*)get_linked_list_next_node(pnode);
	}

	return 0;
}


