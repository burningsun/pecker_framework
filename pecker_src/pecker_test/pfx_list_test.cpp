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
typedef clist_node < sint_t > int_list_node;
typedef pecker_simple_allocator < int_list_node > int_list_allocator;

PFX_INLINE_CODE void print_list_node (const int_list_node* PARAM_IN node_ptr)
{
	if (node_ptr)
	{
		PECKER_LOG_ ("node(%08X) = (item(%d),prev(%08X),next(%08X)\n",node_ptr,node_ptr->get_element(), node_ptr->get_prev_node(),node_ptr->get_next_node());
	}
}

result_t list_test ()
{

	clinked_list < int_list_allocator > * int_list_ptr;
	//int_list_allocator simple_allocator;
	clinked_list < int_list_allocator > ::iterator_t iterator_traval;
	clinked_list < int_list_allocator > int_list ;
	clinked_list < int_list_allocator > ::iterator_t* iterator_traval_ptr;


	int_list_ptr = &int_list;


	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_STR ("test push back\n");

	for (index_t i=0; i<5;++i)
	{
		int_list_node* new_node_ptr = int_list_ptr->new_node();
		new_node_ptr->get_element() = 10 + i;
		int_list_ptr->push_back(new_node_ptr);
	}

	iterator_traval_ptr = int_list_ptr->begin(iterator_traval);
	while (iterator_traval_ptr)
	{
		print_list_node(iterator_traval_ptr->cur_node ());

		iterator_traval_ptr = iterator_traval_ptr->increase ();
	}
	PECKER_LOG_ENDLINE;
	PECKER_LOG_STR ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_STR ("test push front\n");

	for (index_t i=0; i<5;++i)
	{
		int_list_node* new_node_ptr = int_list_ptr->new_node();
		new_node_ptr->get_element() = 10 + i;
		int_list_ptr->push_fornt(new_node_ptr);
	}

	iterator_traval_ptr = int_list_ptr->begin(iterator_traval);
	while (iterator_traval_ptr)
	{
		print_list_node(iterator_traval_ptr->cur_node ());

		iterator_traval_ptr = iterator_traval_ptr->increase ();
	}
	PECKER_LOG_ENDLINE;
	PECKER_LOG_STR (" \n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_STR ("test pop back\n");

	for (index_t i=0; i<3;++i)
	{
		int_list_node* pop_node_ptr = int_list_ptr->pop_back();
		int_list_ptr->release_node(pop_node_ptr);
	}

	iterator_traval_ptr = int_list_ptr->begin(iterator_traval);
	while (iterator_traval_ptr)
	{
		print_list_node(iterator_traval_ptr->cur_node ());

		iterator_traval_ptr = iterator_traval_ptr->increase ();
	}
	PECKER_LOG_ENDLINE;
	PECKER_LOG_STR ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_STR ("test pop front\n");

	for (index_t i=0; i<3;++i)
	{
		int_list_node* pop_node_ptr = int_list_ptr->pop_fornt();
		int_list_ptr->release_node(pop_node_ptr);
	}

	iterator_traval_ptr = int_list_ptr->begin(iterator_traval);
	while (iterator_traval_ptr)
	{
		print_list_node(iterator_traval_ptr->cur_node ());

		iterator_traval_ptr = iterator_traval_ptr->increase ();
	}
	PECKER_LOG_ENDLINE;
	PECKER_LOG_STR ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_STR ("test iterator increase\n");

	clinked_list < int_list_allocator > ::iterator_t iterator_;
	int_list_ptr->begin(iterator_);

	for (index_t i=0; i<2;++i)
	{
		iterator_.increase();
	}

	print_list_node(iterator_.cur_node());

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_STR ("test insert_list_node_back\n");

	int_list_node* new_node_ptr = int_list_ptr->new_node();
	new_node_ptr->get_element() = 100;
	int_list_ptr->insert_back(iterator_, new_node_ptr);

	iterator_traval_ptr = int_list_ptr->begin(iterator_traval);
	while (iterator_traval_ptr)
	{
		print_list_node(iterator_traval_ptr->cur_node ());

		iterator_traval_ptr = iterator_traval_ptr->increase ();
	}
	PECKER_LOG_ENDLINE;
	PECKER_LOG_STR ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_STR ("test insert_list_node_front\n");

	new_node_ptr = int_list_ptr->new_node();
	new_node_ptr->get_element() = 200;
	int_list_ptr->insert_front(iterator_,new_node_ptr);

	iterator_traval_ptr = int_list_ptr->begin(iterator_traval);
	while (iterator_traval_ptr)
	{
		print_list_node(iterator_traval_ptr->cur_node ());

		iterator_traval_ptr = iterator_traval_ptr->increase ();
	}
	PECKER_LOG_ENDLINE;
	PECKER_LOG_STR ("\n");

	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_STR ("test remove_list_node\n");

	int_list_ptr->remove (iterator_);


	iterator_traval_ptr = int_list_ptr->begin(iterator_traval);
	while (iterator_traval_ptr)
	{
		print_list_node(iterator_traval_ptr->cur_node ());

		iterator_traval_ptr = iterator_traval_ptr->increase ();
	}
	PECKER_LOG_ENDLINE;
	PECKER_LOG_STR ("\n");

	return PFX_STATUS_OK;
}
