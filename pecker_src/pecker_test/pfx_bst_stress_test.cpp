/*
 * pfx_array_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_dynamic_array.h"
#include "../pecker_framework/data/pfx_binary_search_tree.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/native/pecker_timetick.h"
#include "../pecker_framework/native/pfx_file_io.h"
#include "../pecker_framework/native/pecker_stream.h"

USING_PECKER_SDK

typedef pfx_cbalance_bst_node < pfx_cstring < pfx_char_t >, pecker_value_compare_extern < pfx_cstring < pfx_char_t > > > bst_string_node_t;
//static pfx_binary_search_tree < bst_string_node_t >  bst_strings;
//static pfx_binary_search_tree < bst_string_node_t >  bst_copy_strings;
//static bst_string_node_t bst_key_node;
PFX_INLINE_CODE void print_bbst_node (const bst_string_node_t* PARAM_IN node_ptr)
{
	if (node_ptr)
	{
		const pfx_cstring < pfx_char_t >& string_ref = node_ptr->get_item();
		const pfx_char_t* str_ptr = string_ref.get_string ();
		pfx_char_t strformat[200];
		if (str_ptr)
		{
			sprintf (strformat,"THIS(%08X) <%%.%ds> L(%08X) R(%08X) P(%08X) BVAL(%d)",
				(pfx_ulong_t)node_ptr, string_ref.get_length(),
				(pfx_ulong_t)node_ptr->get_left_node(),
				(pfx_ulong_t)node_ptr->get_right_node(),
				(pfx_ulong_t)node_ptr->get_parent_node(),
				(pfx_ulong_t)node_ptr->get_height());
			PECKER_LOG_DIRECT_A (strformat,str_ptr);
		}
		else
		{
			sprintf (strformat,"THIS(%08X) <null> L(%08X) R(%08X) P(%08X) BVAL(%d)",
				(pfx_ulong_t)node_ptr, string_ref.get_length(),
				(pfx_ulong_t)node_ptr->get_left_node(),
				(pfx_ulong_t)node_ptr->get_right_node(),
				(pfx_ulong_t)node_ptr->get_parent_node(),
				(pfx_ulong_t)node_ptr->get_height());
			PECKER_LOG_DIRECT_A (strformat);
		}

	}
	else
	{
		PECKER_LOG_ ("null node");
	}

	PECKER_LOG_ ("\n");
}

void stress_test_bst (const IPfx_array < pfx_cstring < pfx_char_t > >* PARAM_IN array_ptr, 
									pfx_cbst < bst_string_node_t >* PARAM_INOUT bst_ptr, pfx_boolean_t bshow)
{
	bst_string_node_t bst_key_node;
	pfx_const_array_iterator < pfx_cstring < pfx_char_t > > itr;
	pecker_tick tick_count;
	IPfx_array_iterator < pfx_cstring < pfx_char_t > >* itr_ptr = null;
	
	tick_count.init();

	// add
	itr_ptr = array_ptr->begin (&itr);
	tick_count.start();
	while (itr_ptr)
	{
		const pfx_cstring < pfx_char_t >* elem_ptr;

		elem_ptr = itr_ptr->get_current_element();
		if (elem_ptr)
		{
			bst_string_node_t* bst_node;
			pfx_result_t status;
			const bst_string_node_t* const_bst_node;
			status = PFX_STATUS_OK;
			bst_node = bst_ptr->new_node();
			status = bst_node->get_item_ref().init_string(elem_ptr);
			if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("init string in node error = %d\n",status);
			}
			const_bst_node = bst_ptr->add(bst_node,status);
			if (null == const_bst_node)
			{
				PECKER_LOG_ ("add node null error= %d\n",status);
			}
			else if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("add node error= %d\n",status);
			}
		}
		else
		{
			PECKER_LOG_ ("null element in array!\n");
		}
		itr_ptr = itr_ptr->increase ();
	}
	PECKER_LOG_ ("add node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	// search
	itr_ptr = array_ptr->begin (&itr);
	tick_count.start();
	while (itr_ptr)
	{
		const pfx_cstring < pfx_char_t >* elem_ptr;

		elem_ptr = itr_ptr->get_current_element();
		if (elem_ptr)
		{
			const bst_string_node_t* const_bst_node;
			pfx_result_t status = PFX_STATUS_OK;

			status = bst_key_node.get_item_ref().init_string(elem_ptr);
			if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("bst_key_node init string in node error = %d\n",status);
			}

			const_bst_node = bst_ptr->find(&bst_key_node);
			if (null == const_bst_node)
			{
				PECKER_LOG_ ("not find the node\n");
			}
		}
		else
		{
			PECKER_LOG_ ("null element in array!\n");
		}
		itr_ptr = itr_ptr->increase ();
	}
	PECKER_LOG_ ("search node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	// inorder traval
	pfx_inorder_iterator < bst_string_node_t > bst_inorder_iterator;
	pfx_cbst_iterator < bst_string_node_t >* iterator_ptr = bst_ptr->begin (&bst_inorder_iterator);

	tick_count.start();
	while (iterator_ptr)
	{
		if (bshow)
		{
			print_bbst_node(iterator_ptr->get_current_node ());
		}
		iterator_ptr = iterator_ptr->increase();
	} 
	PECKER_LOG_ ("inorder traval time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	//rev inorder traval
	pfx_inorder_iterator < bst_string_node_t > bst_rinorder_iterator;
	iterator_ptr = bst_ptr->end (&bst_rinorder_iterator);

	tick_count.start();
	while (iterator_ptr)
	{
		if (bshow)
		{
			print_bbst_node(iterator_ptr->get_current_node ());
		}
		iterator_ptr = iterator_ptr->decrease();
	} 
	PECKER_LOG_ ("rev inorder traval time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	// preorder traval
	pfx_preorder_iterator < bst_string_node_t > bst_preorder_iterator;
	iterator_ptr = bst_ptr->begin (&bst_preorder_iterator);

	tick_count.start();
	while (iterator_ptr)
	{
		if (bshow)
		{
			print_bbst_node(iterator_ptr->get_current_node ());
		}
		iterator_ptr = iterator_ptr->increase();
	} 
	PECKER_LOG_ ("inorder traval time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	// posorder traval
	pfx_preorder_iterator < bst_string_node_t > bst_posorder_iterator;
	iterator_ptr = bst_ptr->begin (&bst_posorder_iterator);

	tick_count.start();
	while (iterator_ptr)
	{
		if (bshow)
		{
			print_bbst_node(iterator_ptr->get_current_node ());
		}
		iterator_ptr = iterator_ptr->increase();
	} 
	PECKER_LOG_ ("inorder traval time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	// remove
	itr_ptr = array_ptr->begin (&itr);
	tick_count.start();
	while (itr_ptr)
	{
		const pfx_cstring < pfx_char_t >* elem_ptr;

		elem_ptr = itr_ptr->get_current_element();
		if (elem_ptr)
		{
			bst_string_node_t* bst_node;
			pfx_result_t status = PFX_STATUS_OK;

			status = bst_key_node.get_item_ref().init_string(elem_ptr);
			if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("bst_key_node init string in node error = %d\n",status);
			}
						
			bst_string_node_t* remove_node_ptr = bst_ptr->find_reference(&bst_key_node);
			if (null == remove_node_ptr)
			{
				PECKER_LOG_ ("not find the remove_node_ptr\n");
				itr_ptr = itr_ptr->increase ();
				continue;
			}
			bst_node = bst_ptr->remove(remove_node_ptr,status);
			if (null == bst_node)
			{
				PECKER_LOG_ ("not find the node\n");
			}
			else
			{
				//print_bbst_node(bst_node);

				status = bst_ptr->release_node(bst_node);
				if (PFX_STATUS_OK != status)
				{
					PECKER_LOG_ ("release_node error %d\n",status);
				}
			}
		}
		else
		{
			PECKER_LOG_ ("null element in array!\n");
		}
		itr_ptr = itr_ptr->increase ();
	}
	PECKER_LOG_ ("remove node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	// add
	itr_ptr = array_ptr->begin (&itr);
	tick_count.start();
	while (itr_ptr)
	{
		const pfx_cstring < pfx_char_t >* elem_ptr;

		elem_ptr = itr_ptr->get_current_element();
		if (elem_ptr)
		{
			bst_string_node_t* bst_node;
			pfx_result_t status;
			const bst_string_node_t* const_bst_node;
			status = PFX_STATUS_OK;
			bst_node = bst_ptr->new_node();
			status = bst_node->get_item_ref().init_string(elem_ptr);
			if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("init string in node error = %d\n",status);
			}
			const_bst_node = bst_ptr->add(bst_node,status);
			if (null == const_bst_node)
			{
				PECKER_LOG_ ("add node null error= %d\n",status);
			}
			else if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("add node error= %d\n",status);
			}
		}
		else
		{
			PECKER_LOG_ ("null element in array!\n");
		}
		itr_ptr = itr_ptr->increase ();
	}
	PECKER_LOG_ ("add node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	tick_count.start();
	pfx_result_t status = bst_ptr->clear();
	if (PFX_STATUS_OK != status)
	{
		PECKER_LOG_ ("clear node error= %d\n",status);
	}
	PECKER_LOG_ ("clear node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

}

pfx_result_t load_file_to_array (const pfx_char_t* PARAM_IN str_path_ptr, pfx_nsize_t path_len,
											IPfx_array < pfx_cstring < pfx_char_t > >* PARAM_INOUT array_ptr)
{
	pfx_cfile file;
	pfx_result_t status;
	pecker_read_stream_form_memery read_stream;
	pfx_char_t* file_buffer_ptr;
	pecker_tick tick_count;

	array_ptr->clear ();
	status = pfx_cfile::is_file_exists (str_path_ptr, path_len);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

	status = file.open(str_path_ptr,path_len,PFO_OPEN_READ);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

	tick_count.init();
	tick_count.start();
	if (file.get_file_size() > 0)
	{
		pfx_usize_t read_size = 0;
		file_buffer_ptr = new pfx_char_t [file.get_file_size()];
		file.read_to_memery((pfx_byte_t*)file_buffer_ptr,file.get_file_size(),read_size);
		read_stream.bind_read_buffer(file_buffer_ptr,read_size);
	}
	PECKER_LOG_ ("load file tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	tick_count.start();

	pfx_char_t string_buffer[4096];
	while (1)
	{

		pfx_usize_t read_size = read_stream.read_chars (string_buffer,sizeof (string_buffer));
		if (0 == read_size)
		{
			break;
		}

		pfx_cstring < pfx_char_t > * strtemp_ptr;
		pfx_usize_t old_array_size = array_ptr->size ();
		//if (old_array_size == 16)
		//{
		//	old_array_size = 16;
		//}
		status = array_ptr->resize (old_array_size + 1);
		if (PFX_STATUS_OK != status)
		{
			PECKER_LOG_ ("array resize error = %d/n",status);
			break;
		}
		

		strtemp_ptr = array_ptr->get_element_reference_at (old_array_size);

		if (null == strtemp_ptr)
		{
			PECKER_LOG_ ("array resize error, strtemp_ptr =null/n");
			break;
		}

		strtemp_ptr->init_string(string_buffer,read_size);
		//int test_;
		//test_ = 1;
	}
	PECKER_LOG_ ("load string tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
	return PFX_STATUS_OK;
}

int bst_stress_test_main ()
{
	pfx_inconsecutive_array < pfx_cstring < pfx_char_t >, pecker_value_compare_extern < pfx_cstring < pfx_char_t > >, 2000 > incs_array;
	incs_array.init(100000);

	PECKER_LOG_ ("====================");
	PECKER_LOG_ ("load file\n");
	load_file_to_array ("test_data\\tst_test_data1.txt",strlen("test_data\\tst_test_data1.txt"),&incs_array);

	PECKER_LOG_ ("====================");
	PECKER_LOG_ ("test bst\n");
	pfx_binary_search_tree < bst_string_node_t >  bst_;
	stress_test_bst (&incs_array,&bst_,PFX_BOOL_FALSE);

	PECKER_LOG_ ("====================");
	PECKER_LOG_ ("test avl-bst\n");
	pfx_avl_binary_search_tree < bst_string_node_t >  avl_bst_;
	stress_test_bst (&incs_array,&avl_bst_,PFX_BOOL_FALSE);

	PECKER_LOG_ ("====================");
	PECKER_LOG_ ("test rb-bst\n");
	pfx_redblack_binary_search_tree < bst_string_node_t >  rb_bst_;
	stress_test_bst (&incs_array,&rb_bst_,PFX_BOOL_FALSE);

 	return 0;
}