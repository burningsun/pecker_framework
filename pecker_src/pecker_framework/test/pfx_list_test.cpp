/*
 * pfx_list_test.cpp
 *
 *  Created on: 2013-9-3
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../data/pfx_list.h"
#include "../native/pfx_log.h"
#include "../data/pfx_clist.h"
#include "../native/pfx_allocator.h"

USING_PECKER_SDK


PFX_C_EXTERN_BEGIN

	typedef struct st_my_linked_list_node
	{
		int m_item;
		linked_list_node_t m_node;
	}my_linked_list_node;

	const my_linked_list_node* cov_to_my_linked_list_node(const linked_list_node_t* pnode)
	{
		if (pnode)
		{
			pfx_long_t addr = (pfx_long_t) pnode - sizeof(int);
			my_linked_list_node* pnew_node = (my_linked_list_node*)addr;
			return pnew_node;
		}
		return null;
	}
	static int get_list_item(const linked_list_node_t* pnode)
	{
		if (pnode)
		{
			pfx_long_t addr = (pfx_long_t) pnode - sizeof(int);
			my_linked_list_node* pnew_node = (my_linked_list_node*)addr;
			if (pnew_node)
			{
				return pnew_node->m_item;
			}
		}
		return -1;
	}

PFX_C_EXTERN_END

#define CLIST_TEST_NODE pfx_clist_node_base < int >
#define  CLIST_TEST_ALLOC csimple_cpp_allocator < CLIST_TEST_NODE >
#define  CLIST_TEST_LIST pfx_clist < CLIST_TEST_NODE,  CLIST_TEST_ALLOC >

int clist_test_main()
{
	
	CLIST_TEST_ALLOC alloc_sim;
	CLIST_TEST_LIST lstest (&alloc_sim);
	pfx_result_t status;
	for (int i=0;i<256;++i)
	{
		CLIST_TEST_NODE* allc_node = (CLIST_TEST_NODE*)alloc_sim.allocate_obj();
		allc_node->get_item_ref() = i;
		status = lstest.push_back(allc_node);
		if (PFX_STATUS_OK == status)
		{
			PECKER_LOG_("lstest.push_back allc_node->item=%d\n",allc_node->get_item());
		}
		else
		{
			PECKER_LOG_ERR ("lstest.push_back","status = %d\n",status);
		}
	}

	PECKER_LOG_ENDLINE ;
	PECKER_LOG_ENDLINE ;

	CLIST_TEST_NODE* pop_node = lstest.pop_front();
	while (pop_node)
	{


		if (pop_node)
		{
			PECKER_LOG_("lstest.pop_front allc_node->item=%d\n",pop_node->get_item());
		}
		else
		{
			PECKER_LOG_ERR ("lstest.pop_front","pop_node = %d\n",pop_node);
		}
		alloc_sim.dellocate_obj(pop_node);
		pop_node = lstest.pop_front();
	}

	PECKER_LOG_ENDLINE ;
	PECKER_LOG_ENDLINE ;

	for (int i=0;i<256;++i)
	{
		CLIST_TEST_NODE* allc_node = (CLIST_TEST_NODE*)alloc_sim.allocate_obj();
		allc_node->get_item_ref() = i;
		status = lstest.push_front(allc_node);
		if (PFX_STATUS_OK == status)
		{
			PECKER_LOG_("lstest.push_front allc_node->item=%d\n",allc_node->get_item());
		}
		else
		{
			PECKER_LOG_ERR ("lstest.push_front","status = %d\n",status);
		}
	}

	PECKER_LOG_ENDLINE ;
	PECKER_LOG_ENDLINE ;

	pop_node = lstest.pop_back();
	while (pop_node)
	{
		if (pop_node)
		{
			PECKER_LOG_("lstest.pop_back allc_node->item=%d\n",pop_node->get_item());
		}
		else
		{
			PECKER_LOG_ERR ("lstest.pop_back","pop_node = %d\n",pop_node);
		}

		alloc_sim.dellocate_obj(pop_node);
		pop_node = lstest.pop_back();

	}

	return 0;
}


int list_test_main()
{
	my_linked_list_node nodes[256];
	linked_list_node_t* pnode;
	int i;
	for (i=0;i<256;++i)
	{
		my_linked_list_node* ptmpnode = (my_linked_list_node*) cov_to_my_linked_list_node ( init_linked_list_node(&nodes[i].m_node) );
		if (ptmpnode)
		{
			ptmpnode->m_item = i;
		}
	}

	pnode = &nodes[0].m_node;
	for (i=1;i<256;++i)
	{
		pnode = (linked_list_node_t*)insert_linked_list_node_end(pnode,&nodes[i].m_node);
	}

	pnode = &nodes[0].m_node;
	for (i=0;i<256;++i)
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


