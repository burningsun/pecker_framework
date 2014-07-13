/*
 * pfx_array_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
//#include "../pecker_framework/data/pfx_dynamic_array.h"
#include "../pecker_framework/data/pfx_carray_codes.h"
#include "../pecker_framework/data/pfx_binary_search_tree.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/native/pecker_timetick.h"
#include "../pecker_framework/native/pfx_file_io.h"
#include "../pecker_framework/native/pecker_stream.h"
#include "../pecker_framework/data/pfx_string_cmp_codes.h"

USING_PECKER_SDK

#define NODE_ARRAY


typedef pecker_simple_allocator< char_t > allc_char_t;
typedef crb_bst_node < cstring < allc_char_t > > bst_string_node_t;

//static pfx_binary_search_tree < bst_string_node_t >  bst_strings;
//static pfx_binary_search_tree < bst_string_node_t >  bst_copy_strings;
//static bst_string_node_t bst_key_node;

#ifdef NODE_ARRAY
#define  GET_ELEM_CONST(X) (&((X)->get_item()))
#define GET_ELEM(X) (&((X)->get_item_ref()))
typedef bst_string_node_t ELEM_t;
#else
#define  GET_ELEM_CONST(X) (X)
#define GET_ELEM(X) (X)
typedef  cstring < char_t > ELEM_t;
#endif

PFX_INLINE_CODE void print_bbst_node (const bst_string_node_t* PARAM_IN node_ptr)
{
	if (node_ptr)
	{
		const cstring < allc_char_t >& string_ref = node_ptr->get_item();
		const char_t* str_ptr = string_ref.get_string ();
		char_t strformat[200];
		if (str_ptr)
		{
			sprintf (strformat,"THIS(%08X) <%%.%ds> L(%08X) R(%08X) P(%08X) BVAL(%d)",
				(ulong_t)node_ptr, string_ref.get_length(),
				(ulong_t)node_ptr->get_left_node(),
				(ulong_t)node_ptr->get_right_node(),
				(ulong_t)node_ptr->get_parent_node(),
				(ulong_t)node_ptr->get_height());
			PECKER_LOG_DIRECT_A (strformat,str_ptr);
		}
		else
		{
			sprintf (strformat,"THIS(%08X) <null> L(%08X) R(%08X) P(%08X) BVAL(%d)",
				(ulong_t)node_ptr, string_ref.get_length(),
				(ulong_t)node_ptr->get_left_node(),
				(ulong_t)node_ptr->get_right_node(),
				(ulong_t)node_ptr->get_parent_node(),
				(ulong_t)node_ptr->get_height());
			PECKER_LOG_DIRECT_A (strformat);
		}

	}
	else
	{
		PECKER_LOG_ ("null node");
	}

	PECKER_LOG_ ("\n");
}


void stress_test_bst (const IPfx_array < ELEM_t >* PARAM_IN array_ptr, 
									cbst < bst_string_node_t >* PARAM_INOUT bst_ptr, boolean_t bshow)
{
	bst_string_node_t bst_key_node;
	const_array_iterator < ELEM_t > itr;
	pecker_tick tick_count;
	IPfx_array_iterator < ELEM_t >* itr_ptr = null;
	
	tick_count.init();
	//PECKER_LOG_ ("pfx_cstring < pfx_char_t > size %d\n",sizeof (pfx_cstring < pfx_char_t >));
	// add
	itr_ptr = array_ptr->begin (&itr);
	tick_count.start();
	while (itr_ptr)
	{
		const ELEM_t* elem_ptr;

		elem_ptr = itr_ptr->get_current_element();
		if (elem_ptr)
		{
			bst_string_node_t* bst_node;
			result_t status;
			const bst_string_node_t* const_bst_node;
			status = PFX_STATUS_OK;
			bst_node = bst_ptr->new_node();
			status = bst_node->get_item_ref().init_string(GET_ELEM_CONST(elem_ptr));
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
	for (int i=0;i<5;++i)
	{
	itr_ptr = array_ptr->begin (&itr);
	tick_count.start();
	while (itr_ptr)
	{
		const ELEM_t* elem_ptr;

		elem_ptr = itr_ptr->get_current_element();
		if (elem_ptr)
		{
			const bst_string_node_t* const_bst_node;
			result_t status = PFX_STATUS_OK;



#ifdef NODE_ARRAY
			const_bst_node = bst_ptr->find(elem_ptr);
#else
			status = bst_key_node.get_item_ref().init_string(GET_ELEM_CONST(elem_ptr));
			if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("bst_key_node init string in node error = %d\n",status);
			}
			const_bst_node = bst_ptr->find(&bst_key_node);
#endif
			
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
	}
	// inorder traval
	bst_inorder_iterator < bst_string_node_t > bst_inorder_itr;
	cbst_iterator < bst_string_node_t >* iterator_ptr = bst_ptr->begin (&bst_inorder_itr);

	tick_count.start();
	while (iterator_ptr)
	{
		if (bshow)
		{
			print_bbst_node(iterator_ptr->get_current_node ());
		}
		//pfx_nsize_t bval = pfx_cavl_tree < bst_string_node_t > ::calculate_avl_balance_value(iterator_ptr->get_current_node()) ;
		//if (bval >= 2 || bval <=-2)
		//{
		//	PECKER_LOG_ ("bval error!\n");
		//}
		iterator_ptr = iterator_ptr->increase();
	} 
	PECKER_LOG_ ("inorder traval time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
	result_t status;

	//rev inorder traval
	bst_inorder_iterator < bst_string_node_t > bst_rinorder_iterator;
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
	bst_preorder_iterator < bst_string_node_t > bst_preorder_itr;
	iterator_ptr = bst_ptr->begin (&bst_preorder_itr);

	tick_count.start();
	while (iterator_ptr)
	{
		if (bshow)
		{
			print_bbst_node(iterator_ptr->get_current_node ());
		}
		iterator_ptr = iterator_ptr->increase();
	} 
	PECKER_LOG_ ("preorder traval time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	// posorder traval
	bst_preorder_iterator < bst_string_node_t > bst_posorder_itr;
	iterator_ptr = bst_ptr->begin (&bst_posorder_itr);

	tick_count.start();
	while (iterator_ptr)
	{
		if (bshow)
		{
			print_bbst_node(iterator_ptr->get_current_node ());
		}
		iterator_ptr = iterator_ptr->increase();
	} 
	PECKER_LOG_ ("posorder traval time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	// remove
	itr_ptr = array_ptr->begin (&itr);
	tick_count.start();
	while (itr_ptr)
	{

		const ELEM_t* elem_ptr;

		elem_ptr = itr_ptr->get_current_element();
		if (elem_ptr)
		{
			bst_string_node_t* bst_node;
			result_t status = PFX_STATUS_OK;


#ifdef NODE_ARRAY
			bst_string_node_t* remove_node_ptr = bst_ptr->find_reference(elem_ptr);
			//print_bbst_node(remove_node_ptr);
			if (null == remove_node_ptr)
			{
				PECKER_LOG_ ("not find the remove_node_ptr\n");
				itr_ptr = itr_ptr->increase ();
				continue;
			}
#else
			status = bst_key_node.get_item_ref().init_string(GET_ELEM_CONST(elem_ptr));
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
#endif

			//pfx_uindex_t sindex = 0;
			//pfx_usize_t same_count = 0;
			//if (GET_ELEM_CONST(elem_ptr)->find_near_string (0,"act4",4,sindex,same_count) && 0 == sindex && 4 == same_count)
			//{
			//	elem_ptr = elem_ptr;
			//}

			bst_node = bst_ptr->remove(remove_node_ptr,status);

			iterator_ptr = bst_ptr->begin (&bst_inorder_itr);

			//tick_count.start();
			//while (iterator_ptr)
			//{
			//	if (bshow)
			//	{
			//		print_bbst_node(iterator_ptr->get_current_node ());
			//	}
			//	pfx_nsize_t bval = pfx_cavl_tree < bst_string_node_t > ::calculate_avl_balance_value(iterator_ptr->get_current_node()) ;
			//	if (bval >= 2 || bval <=-2)
			//	{
			//		PECKER_LOG_ ("bval error!\n");
			//		break;
			//	}
			//	iterator_ptr = iterator_ptr->increase();
			//} 
			//PECKER_LOG_ ("inorder traval time tick = %lf ms\n",tick_count.get_microsecond());
			//tick_count.stop();

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
		const ELEM_t* elem_ptr;

		elem_ptr = itr_ptr->get_current_element();
		if (elem_ptr)
		{
			bst_string_node_t* bst_node;
			result_t status;
			const bst_string_node_t* const_bst_node;
			status = PFX_STATUS_OK;
			bst_node = bst_ptr->new_node();
			status = bst_node->get_item_ref().init_string(GET_ELEM_CONST(elem_ptr));
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
	status = bst_ptr->clear();
	if (PFX_STATUS_OK != status)
	{
		PECKER_LOG_ ("clear node error= %d\n",status);
	}
	PECKER_LOG_ ("clear node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

}

result_t load_file_to_array (const char_t* PARAM_IN str_path_ptr, nsize__t path_len,
											IPfx_array < ELEM_t >* PARAM_INOUT array_ptr)
{
	pecker_file file;
	result_t status;
	pecker_read_stream_form_memery read_stream;
	char_t* file_buffer_ptr;
	pecker_tick tick_count;

	array_ptr->clear ();
	status = pecker_file::is_file_exists (str_path_ptr, path_len);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

	status = file.open(str_path_ptr,path_len,PFO_OPEN_READ);
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

	tick_count.init();
	tick_count.start();
	if (file.get_file_size() > 0)
	{
		usize__t read_size = 0;
		file_buffer_ptr = new char_t [file.get_file_size()];
		file.read_to_memery((byte_t*)file_buffer_ptr,file.get_file_size(),read_size);
		read_stream.bind_read_buffer(file_buffer_ptr,read_size);
	}
	PECKER_LOG_ ("load file tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();

	tick_count.start();

	char_t string_buffer[4096];
	while (1)
	{

		usize__t read_size = read_stream.read_chars (string_buffer,sizeof (string_buffer));
		if (0 == read_size)
		{
			break;
		}

		ELEM_t * strtemp_ptr;
		usize__t old_array_size = array_ptr->size ();
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

		GET_ELEM(strtemp_ptr)->init_string(string_buffer,read_size);
		//.init_string(string_buffer,read_size);
		//int test_;
		//test_ = 1;
	}
	PECKER_LOG_ ("load string tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
	return PFX_STATUS_OK;
}

int bst_stress_test_main ()
{

	array_type < ELEM_t, pecker_value_compare_extern < ELEM_t >, 2000 >::inconsecutive_array_t incs_array;
	//pfx_consecutive_array < ELEM_t, pecker_value_compare_extern < ELEM_t > > incs_array;
	incs_array.init(300000);

	PECKER_LOG_ ("====================");
	PECKER_LOG_ ("load file\n");
	load_file_to_array ("test_data\\tst_test_data1.txt",strlen("test_data\\tst_test_data1.txt"),&incs_array);
	//load_file_to_array ("test_data\\tst_test_data2.txt",strlen("test_data\\tst_test_data2.txt"),&incs_array);

	PECKER_LOG_ ("====================");
	PECKER_LOG_ ("test bst\n");
	pfx_binary_search_tree_type< bst_string_node_t > ::binary_search_tree_t   bst_;
	stress_test_bst (&incs_array,&bst_,PFX_BOOL_FALSE);

	PECKER_LOG_ ("====================");
	PECKER_LOG_ ("test avl-bst\n");
	pfx_binary_search_tree_type< bst_string_node_t >::avl_binary_search_tree_t   avl_bst_;
	stress_test_bst (&incs_array,&avl_bst_,PFX_BOOL_FALSE);
	//stress_test_bst (&incs_array,&avl_bst_,PFX_BOOL_FALSE);
	//stress_test_bst (&incs_array,&avl_bst_,PFX_BOOL_FALSE);
	//stress_test_bst (&incs_array,&avl_bst_,PFX_BOOL_FALSE);
	//stress_test_bst (&incs_array,&avl_bst_,PFX_BOOL_FALSE);

	PECKER_LOG_ ("====================");
	PECKER_LOG_ ("test rb-bst\n");
	pfx_binary_search_tree_type< bst_string_node_t >::redblack_binary_search_tree_t rb_bst_;
	stress_test_bst (&incs_array,&rb_bst_,PFX_BOOL_FALSE);

 	return 0;
}