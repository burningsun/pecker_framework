/*
 * pfx_list_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_clist.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"

USING_PECKER_SDK
typedef pfx_clist_node < pfx_sint_t > int_list_node;
typedef pecker_simple_allocator < int_list_node > int_list_allocator;

PFX_INLINE_CODE void print_list_node (const int_list_node* PARAM_IN node_ptr)
{
	if (node_ptr)
	{
		PECKER_LOG_ ("node(%08X) = (item(%d),prev(%08X),next(%08X)\n",node_ptr,node_ptr->get_item(), node_ptr->get_prev_node(),node_ptr->get_next_node());
	}
}

pfx_result_t list_test ()
{

	pfx_clist_base < int_list_node > * int_list_ptr;
	int_list_allocator simple_allocator;
	pfx_list_iterator_base < int_list_node > iterator_traval;
	pfx_clist < int_list_node, int_list_allocator > int_list (&simple_allocator);
	int_list_ptr = &int_list;

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("test push back\n");

	for (pfx_index_t i=0; i<5;++i)
	{
		int_list_node* new_node_ptr = int_list_ptr->new_node();
		new_node_ptr->get_item_ref() = 10 + i;
		int_list_ptr->push_back(new_node_ptr);
	}
	int_list_ptr->begin(&iterator_traval);
	
	while (iterator_traval.get_item())
	{
		print_list_node(iterator_traval.get_item());
		pfx_result_t status = iterator_traval.increase();
		if (PFX_STATUS_FIN == status)
		{
			break;
		}
	}
	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("test push front\n");

	for (pfx_index_t i=0; i<5;++i)
	{
		int_list_node* new_node_ptr = int_list_ptr->new_node();
		new_node_ptr->get_item_ref() = 10 + i;
		int_list_ptr->push_front(new_node_ptr);
	}

	int_list_ptr->begin(&iterator_traval);

	while (iterator_traval.get_item())
	{
		print_list_node(iterator_traval.get_item());
		pfx_result_t status = iterator_traval.increase();
		if (PFX_STATUS_FIN == status)
		{
			break;
		}
	}
	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("test pop back\n");

	for (pfx_index_t i=0; i<3;++i)
	{
		int_list_node* pop_node_ptr = int_list_ptr->pop_back();
		int_list_ptr->release_node(pop_node_ptr);
	}

	int_list_ptr->begin(&iterator_traval);

	while (iterator_traval.get_item())
	{
		print_list_node(iterator_traval.get_item());
		pfx_result_t status = iterator_traval.increase();
		if (PFX_STATUS_FIN == status)
		{
			break;
		}
	}
	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("test pop front\n");

	for (pfx_index_t i=0; i<3;++i)
	{
		int_list_node* pop_node_ptr = int_list_ptr->pop_front();
		int_list_ptr->release_node(pop_node_ptr);
	}

	int_list_ptr->begin(&iterator_traval);

	while (iterator_traval.get_item())
	{
		print_list_node(iterator_traval.get_item());
		pfx_result_t status = iterator_traval.increase();
		if (PFX_STATUS_FIN == status)
		{
			break;
		}
	}
	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("test iterator increase\n");

	pfx_list_iterator_base < int_list_node > iterator_;
	int_list_ptr->begin(&iterator_);

	for (pfx_index_t i=0; i<2;++i)
	{
		iterator_.increase();
	}

	print_list_node(iterator_.get_item());

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("test insert_list_node_back\n");

	int_list_node* new_node_ptr = int_list_ptr->new_node();
	new_node_ptr->get_item_ref() = 100;
	int_list_ptr->insert_list_node_back(&iterator_,new_node_ptr);

	int_list_ptr->begin(&iterator_traval);

	while (iterator_traval.get_item())
	{
		print_list_node(iterator_traval.get_item());
		pfx_result_t status = iterator_traval.increase();
		if (PFX_STATUS_FIN == status)
		{
			break;
		}
	}
	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("test insert_list_node_front\n");

	new_node_ptr = int_list_ptr->new_node();
	new_node_ptr->get_item_ref() = 200;
	int_list_ptr->insert_list_node_front(&iterator_,new_node_ptr);

	int_list_ptr->begin(&iterator_traval);

	while (iterator_traval.get_item())
	{
		print_list_node(iterator_traval.get_item());
		pfx_result_t status = iterator_traval.increase();
		if (PFX_STATUS_FIN == status)
		{
			break;
		}
	}
	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("test remove_list_node\n");

	int_list_ptr->remove_list_node(&iterator_);

	int_list_ptr->begin(&iterator_traval);

	while (iterator_traval.get_item())
	{
		print_list_node(iterator_traval.get_item());
		pfx_result_t status = iterator_traval.increase();
		if (PFX_STATUS_FIN == status)
		{
			break;
		}
	}
	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("\n");

	return PFX_STATUS_OK;
}