﻿/*
 * pfx_array_test.cpp
 *
 *  Created on: 2014-3-28
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>

#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/data/pfx_carray.h"
#include "../pecker_framework/data/pfx_binary_search_tree.h"
#include "../pecker_framework/data/pfx_cstring_codes.h"
#include "../pecker_framework/data/pfx_string_cmp_codes.h"
#include "../pecker_framework/native/pecker_timetick.h"
#include "../pecker_framework/native/pfx_file_io.h"
#include "../pecker_framework/native/pecker_stream.h"

USING_PECKER_SDK

typedef pecker_simple_allocator< char_t > alloc_char_t;

typedef cstring< alloc_char_t > string_t;

typedef pecker_simple_allocator< string_t > alloc_t;

typedef carray< alloc_t > array_t;
//typedef carray_mbs< alloc_t >							array_t;

typedef cbalance_bst_node< string_t > bst_node_t;

//typedef string_compare < string_t >				string_cmp_t;
typedef ascii_string_compare< string_t > string_cmp_t;

typedef compare_two_node< bst_node_t, bst_node_t, string_cmp_t > node_cmp_t;

typedef pfx_binary_search_tree_type< bst_node_t, node_cmp_t >::binary_search_tree_t bst_t;

typedef pfx_binary_search_tree_type< bst_node_t, node_cmp_t >::avl_binary_search_tree_t avl_bst_t;

typedef pfx_binary_search_tree_type< bst_node_t, node_cmp_t >::redblack_binary_search_tree_t rb_bst_t;

typedef pecker_simple_allocator< bst_node_t > bst_set_node_t;

typedef cbst_set< BST_operate< bst_set_node_t, node_cmp_t > > bst_set_t;
typedef cbst_set< AVL_BST_operate< bst_set_node_t, node_cmp_t > > avl_bst_set_t;
typedef cbst_set< RB_BST_operate< bst_set_node_t, node_cmp_t > > rb_bst_set_t;

PFX_INLINE_CODE void print_bbst_node(const bst_node_t* PARAM_IN node_ptr,
		int __type = 0)
{
	if (node_ptr)
	{
		const string_t& string_ref = node_ptr->get_item ();
		const char_t* str_ptr = string_ref.get_string ();
		char_t strformat[200];
		usize__t print_size = (str_ptr) ? string_ref.get_length () : 4;

		switch (__type)
		{
		case BINARY_SEARCH_TREE_TYPE:
			sprintf_s (strformat, sizeof(strformat), "THIS(%%08X) <%%.%ds> L(%%08X) R(%%08X) P(%%08X)", print_size);
			break;
		case AVL_BINARY_SEARCH_TREE_TYPE:
			sprintf_s (strformat, sizeof(strformat), "THIS(%%08X) <%%.%ds> L(%%08X) R(%%08X) P(%%08X) HEIGHT(%d) BALANCE(%d)", print_size, (ulong_t) node_ptr->get_height (),
					AVL_BST_node_init< bst_node_t >::calculate_avl_balance_value (node_ptr));
			break;
		case RB_BINARY_SEARCH_TREE_TYPE:
			sprintf_s (strformat, sizeof(strformat), "THIS(%%08X) <%%.%ds> L(%%08X) R(%%08X) P(%%08X) COLOR(%s)", print_size, (((ulong_t) node_ptr->get_color ()) ? "red" : "black"));
			break;
		default:
			sprintf_s (strformat, sizeof(strformat), "THIS(%%08X) <%%.%ds> L(%%08X) R(%%08X) P(%%08X)", print_size);
			break;
		}

		if (str_ptr)
		{
			PECKER_LOG_DIRECT_A (strformat,
					(ulong_t)node_ptr,
					str_ptr,
					(ulong_t)node_ptr->get_left_node(),
					(ulong_t)node_ptr->get_right_node(),
					(ulong_t)node_ptr->get_parent_node());
		}
		else
		{
			PECKER_LOG_DIRECT_A (strformat,
					(ulong_t)node_ptr,
					"null",
					(ulong_t)node_ptr->get_left_node(),
					(ulong_t)node_ptr->get_right_node(),
					(ulong_t)node_ptr->get_parent_node());
		}

	}
	else
	{
		PECKER_LOG_STR("null node");
	}

	PECKER_LOG_STR("\n");
}

//template < class __array_type, class __bst_type >
template < class __array_type, class __bst_type, const int __print_type >
void bst_add_node_stress_test_by_node(const __array_type& PARAM_IN __array,
__bst_type& PARAM_OUT __bst,
boolean_t bshow = true)
{
	typename __array_type::const_iterator_t __arr_itr;
	pecker_tick tick_count;

	typename __array_type::const_iterator_t* arr_itr_ptr = null;

	// 
	PECKER_LOG_STR ("begin add ......\n");
	tick_count.init();
	arr_itr_ptr = __array.begin(__arr_itr);
	tick_count.start();
	while (arr_itr_ptr)
	{
		const typename __array_type::element_t& elem = arr_itr_ptr->reference();
		if (&elem == &(__array_type::error_element()))
		{
			PECKER_LOG_STR ("null element in array!\n");
			arr_itr_ptr = arr_itr_ptr->increase();
			continue;
		}

		typename __bst_type::node_t* bst_node_ptr;
		result_t status;
		const typename __bst_type::node_t* const_node_ptr;

		status = PFX_STATUS_OK;
		bst_node_ptr = __bst.new_node();
		status = bst_node_ptr->get_item_ref().init_string (elem);
		if (PFX_STATUS_OK > status)
		{
			PECKER_LOG_ ("init string in node error = %d\n",status);
			arr_itr_ptr = arr_itr_ptr->increase();
			__bst.release_node(bst_node_ptr);
			continue;
		}

		const_node_ptr = __bst.add(bst_node_ptr, status);
		if (null == const_node_ptr)
		{
			PECKER_LOG_ ("add node null error= %d\n",status);
		}
		else if (PFX_STATUS_OK > status)
		{
			PECKER_LOG_ ("add node error= %d\n",status);
		}
		else if (bshow)
		{
			print_bbst_node(const_node_ptr, __print_type);
		}
		arr_itr_ptr = arr_itr_ptr->increase();
		continue;
	}
	PECKER_LOG_ ("add node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
}

template < class __array_type, class __bst_type, const int __print_type >
void bst_find_node_stress_test_by_node(const __array_type& PARAM_IN __array,
__bst_type& PARAM_OUT __bst,
boolean_t bshow = true)
{
	typename __bst_type::node_t key_node;
	typename __array_type::const_iterator_t __arr_itr;
	pecker_tick tick_count;

	typename __array_type::const_iterator_t* arr_itr_ptr = null;

	// 
	PECKER_LOG_STR ("begin find ......\n");
	tick_count.init();
	arr_itr_ptr = __array.begin(__arr_itr);
	tick_count.start();
	while (arr_itr_ptr)
	{
		const typename __array_type::element_t& elem = arr_itr_ptr->reference();
		if (&elem == &(__array_type::error_element()))
		{
			PECKER_LOG_STR ("null element in array!\n");
			arr_itr_ptr = arr_itr_ptr->increase();
			continue;
		}

		//__bst_type::node_t*				bst_node_ptr;
		result_t status;
		const typename __bst_type::node_t* const_node_ptr;

		status = PFX_STATUS_OK;

		status = key_node.get_item_ref().init_string (elem);
		if (PFX_STATUS_OK > status)
		{
			PECKER_LOG_ ("init string in node error = %d\n",status);
		}
		const_node_ptr = __bst.find(&key_node);
		if (null == const_node_ptr)
		{
			PECKER_LOG_STR ("not find\n");
		}
		else
		{
			//if (__bst_type::cmp_t::compare_two_elemen_t::compare(const_node_ptr->get_item(), elem))
			//{
			//	PECKER_LOG_("not  same!\n");
			//}
			if (bshow)
			{
				print_bbst_node(const_node_ptr, __print_type);
			}

		}
		arr_itr_ptr = arr_itr_ptr->increase();
		continue;
	}
	PECKER_LOG_ ("find node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
}

//#define __bst_type bst_set_t
template < class __array_type, class __bst_type, const int __print_type >
void bst_erase_node_stress_test_by_node(const __array_type& PARAM_IN __array,
__bst_type& PARAM_OUT __bst,
boolean_t bshow = true)
{
	typename __bst_type::node_t key_node;
	typename __array_type::const_iterator_t __arr_itr;
	pecker_tick tick_count;

	typename __array_type::const_iterator_t* arr_itr_ptr = null;

	// 
	PECKER_LOG_STR ("begin erase ......\n");
	tick_count.init();
	arr_itr_ptr = __array.begin(__arr_itr);
	tick_count.start();
	while (arr_itr_ptr)
	{
		const typename __array_type::element_t& elem = arr_itr_ptr->reference();
		if (&elem == &(__array_type::error_element()))
		{
			PECKER_LOG_STR ("null element in array!\n");
			arr_itr_ptr = arr_itr_ptr->increase();
			continue;
		}

		typename __bst_type::node_t* bst_node_ptr;
		result_t status;
		const typename __bst_type::node_t* const_node_ptr;
		typename __bst_type::node_t* removed_node_ptr = null;

		status = PFX_STATUS_OK;

		status = key_node.get_item_ref().init_string (elem);
		if (PFX_STATUS_OK > status)
		{
			PECKER_LOG_ ("init string in node error = %d\n",status);
		}
		const_node_ptr = __bst.find(&key_node);
		if (null == const_node_ptr)
		{
			PECKER_LOG_STR ("not find node\n");
		}
		else
		{

			removed_node_ptr = (typename __bst_type::node_t*)const_node_ptr;
			removed_node_ptr = __bst.remove(removed_node_ptr, status);
		}

		if (removed_node_ptr)
		{
			if (bshow)
			{
				print_bbst_node(const_node_ptr, __print_type);
			}

			status = __bst.release_node(removed_node_ptr);
			if (PFX_STATUS_OK > status)
			{
				PECKER_LOG_("release node error = %d\n", status);
			}
		}

		arr_itr_ptr = arr_itr_ptr->increase();
		continue;
	}
	PECKER_LOG_ ("erase node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
}

template < class __array_type, class __bst_type, const int __print_type >
void bst_find_node_stress_test_by_elem(const __array_type& PARAM_IN __array,
__bst_type& PARAM_OUT __bst,
boolean_t bshow = true)
{
	typename __bst_type::node_t key_node;
	typename __array_type::const_iterator_t __arr_itr;
	pecker_tick tick_count;

	typename __array_type::const_iterator_t* arr_itr_ptr = null;

	// 
	PECKER_LOG_STR ("begin find element......\n");
	tick_count.init();
	arr_itr_ptr = __array.begin(__arr_itr);
	tick_count.start();
	while (arr_itr_ptr)
	{
		const typename __array_type::element_t& elem = arr_itr_ptr->reference();
		if (&elem == &(__array_type::error_element()))
		{
			PECKER_LOG_STR ("null element in array!\n");
			arr_itr_ptr = arr_itr_ptr->increase();
			continue;
		}
		typename __bst_type::const_iterator_t __bst_itr;
		typename __bst_type::const_iterator_t* __itr_ptr = __bst.find_node(elem, __bst_itr);
		if (null == __itr_ptr)
		{
			PECKER_LOG_STR ("not find\n");
		}
		else
		{
			//if (__bst_type::cmp_t::compare_two_elemen_t::compare(__itr_ptr->cur_node()->get_item(), elem))
			//{
			//	PECKER_LOG_("not  same!\n");
			//}
			if (bshow)
			{
				print_bbst_node(__itr_ptr->cur_node(), __print_type);
			}
		}
		arr_itr_ptr = arr_itr_ptr->increase();
		continue;
	}
	PECKER_LOG_ ("find node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
}

//#define __array_type array_t
//#define __bst_type bst_set_t
template < class __array_type, class __bst_type, const int __print_type >
void bst_erase_node_stress_test_by_elem(const __array_type& PARAM_IN __array,
__bst_type& PARAM_OUT __bst,
boolean_t bshow = true)
{
	typename __bst_type::node_t key_node;
	typename __array_type::const_iterator_t __arr_itr;
	pecker_tick tick_count;

	typename __array_type::const_iterator_t* arr_itr_ptr = null;

	// 
	PECKER_LOG_STR ("begin erase ......\n");
	tick_count.init();
	arr_itr_ptr = __array.begin(__arr_itr);
	tick_count.start();
	while (arr_itr_ptr)
	{
		const typename __array_type::element_t& elem = arr_itr_ptr->reference();
		if (&elem == &(__array_type::error_element()))
		{
			PECKER_LOG_STR ("null element in array!\n");
			arr_itr_ptr = arr_itr_ptr->increase();
			continue;
		}

		typename __bst_type::const_iterator_t __bst_itr;
		result_t status;
		typename __bst_type::node_t* removed_node_ptr = null;

		status = PFX_STATUS_OK;

		typename __bst_type::const_iterator_t* __itr_ptr = __bst.find_node(elem, __bst_itr);
		if (null == __itr_ptr)
		{
			PECKER_LOG_STR ("not find\n");
			continue;
		}

		removed_node_ptr = __bst.remove(__bst_itr, status);

		if (removed_node_ptr && PFX_STATUS_OK == status)
		{
			if (bshow)
			{
				print_bbst_node(removed_node_ptr, __print_type);
			}

			status = __bst.release_node(removed_node_ptr);
			if (PFX_STATUS_OK > status)
			{
				PECKER_LOG_("release node error = %d\n", status);
			}
		}

		arr_itr_ptr = arr_itr_ptr->increase();
		continue;
	}
	PECKER_LOG_ ("erase node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
}

template < class __bst_type, const int __print_type >
void bst_enum_node_stress_test_by_node(__bst_type& PARAM_OUT __bst,
boolean_t bIncrease = true,
boolean_t bshow = true)
{

	pecker_tick tick_count;
	typename __bst_type::const_iterator_t __itr;
	typename __bst_type::const_iterator_t* itr_ptr = null;

	// 
	PECKER_LOG_STR ("begin enum ......\n");
	tick_count.init();
	if (bIncrease)
	{
		itr_ptr = __bst.begin(__itr);
	}
	else
	{
		itr_ptr = __bst.end(__itr);
	}

	tick_count.start();
	while (itr_ptr)
	{
		const typename __bst_type::node_t* node_ptr;
		node_ptr = itr_ptr->cur_node ();
		if (bshow)
		{
			print_bbst_node(node_ptr, __print_type);
		}
		if (bIncrease)
		{
			itr_ptr = itr_ptr->increase ();
		}
		else
		{
			itr_ptr = itr_ptr->decrease ();
		}
	}
	PECKER_LOG_ ("enum node time tick = %lf ms\n",tick_count.get_microsecond());
	tick_count.stop();
}

template < class __array_type >
result_t load_file_to_array(const char_t* PARAM_IN str_path_ptr,
		nsize__t path_len,
		__array_type* PARAM_INOUT array_ptr)
		{
			pecker_file file;
			result_t status;
			pecker_read_stream_form_memery read_stream;
			char_t* file_buffer_ptr;
			pecker_tick tick_count;

			array_ptr->clean ();
			status = pecker_file::is_file_exists (str_path_ptr);
			RETURN_INVALID_RESULT((PFX_STATUS_OK > status),status);

			status = file.open(str_path_ptr,PFO_OPEN_READ);
			RETURN_INVALID_RESULT((PFX_STATUS_OK > status),status);

			tick_count.init();
			tick_count.start();
			if (file.get_file_size() > 0)
			{
				usize__t read_size = file.get_file_size();
				file_buffer_ptr = new char_t [file.get_file_size()];
				file.read_to_memery((byte_t*)file_buffer_ptr,read_size);
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

				usize__t old_array_size = array_ptr->size ();
				status = array_ptr->resize (old_array_size + 1);
				if (PFX_STATUS_OK > status)
				{
					PECKER_LOG_ ("array resize error = %d/n",status);
					break;
				}

				typename __array_type::element_t& elem = array_ptr->get_element_at(old_array_size);

				if (array_ptr->is_error_element(elem))
				{
					PECKER_LOG_STR ("array resize error, strtemp_ptr =null/n");
					break;
				}

				elem.init_string(string_buffer, read_size);
			}
			PECKER_LOG_ ("load string tick = %lf ms\n",tick_count.get_microsecond());
			tick_count.stop();
			return PFX_STATUS_OK;
		}

int bst_stress_test_main(bool bshow = false)
{

	array_t incs_array;

	//pfx_consecutive_array < ELEM_t, pecker_value_compare_extern < ELEM_t > > incs_array;
	incs_array.init (300000);

	PECKER_LOG_STR("====================");
	PECKER_LOG_STR("load file\n");
	//load_file_to_array< array_t > ("test_data\\tst_test_data1.txt",
	//	strlen("test_data\\tst_test_data1.txt"),
	//	&incs_array);

	load_file_to_array< array_t > ("test_data\\tst_test_data2.txt", strlen ("test_data\\tst_test_data2.txt"), &incs_array);
	//load_file_to_array ("test_data\\tst_test_data2.txt",strlen("test_data\\tst_test_data2.txt"),&incs_array);

	for (int i = 0; i < 1; ++i)
	{

		PECKER_LOG_STR("====================");
		PECKER_LOG_STR("test bst\n");

		bst_set_t _binst;
		bst_add_node_stress_test_by_node< array_t, bst_set_t, BINARY_SEARCH_TREE_TYPE > (incs_array, _binst, bshow);
		bst_find_node_stress_test_by_elem< array_t, bst_set_t, BINARY_SEARCH_TREE_TYPE > (incs_array, _binst, bshow);
		bst_find_node_stress_test_by_node< array_t, bst_set_t, BINARY_SEARCH_TREE_TYPE > (incs_array, _binst, bshow);
		bst_enum_node_stress_test_by_node< bst_set_t, BINARY_SEARCH_TREE_TYPE > (_binst, PFX_BOOL_TRUE, bshow);
		bst_enum_node_stress_test_by_node< bst_set_t, BINARY_SEARCH_TREE_TYPE > (_binst, PFX_BOOL_FALSE, bshow);
		bst_erase_node_stress_test_by_elem< array_t, bst_set_t, BINARY_SEARCH_TREE_TYPE > (incs_array, _binst, bshow);
		//bst_erase_node_stress_test_by_node< array_t, bst_set_t, BINARY_SEARCH_TREE_TYPE >(incs_array, _binst, bshow);

		SleepMS(2000);

		PECKER_LOG_STR("====================");
		PECKER_LOG_STR("test avl-bst\n");
		avl_bst_set_t _avlbinst;
		bst_add_node_stress_test_by_node< array_t, avl_bst_set_t, AVL_BINARY_SEARCH_TREE_TYPE > (incs_array, _avlbinst, bshow);
		bst_find_node_stress_test_by_elem< array_t, avl_bst_set_t, AVL_BINARY_SEARCH_TREE_TYPE > (incs_array, _avlbinst, bshow);
		bst_find_node_stress_test_by_node< array_t, avl_bst_set_t, AVL_BINARY_SEARCH_TREE_TYPE > (incs_array, _avlbinst, bshow);
		bst_enum_node_stress_test_by_node< avl_bst_set_t, AVL_BINARY_SEARCH_TREE_TYPE > (_avlbinst, PFX_BOOL_TRUE, bshow);
		bst_enum_node_stress_test_by_node< avl_bst_set_t, AVL_BINARY_SEARCH_TREE_TYPE > (_avlbinst, PFX_BOOL_FALSE, bshow);
		bst_erase_node_stress_test_by_elem< array_t, avl_bst_set_t, AVL_BINARY_SEARCH_TREE_TYPE > (incs_array, _avlbinst, bshow);
		//bst_erase_node_stress_test_by_node< array_t, avl_bst_set_t, AVL_BINARY_SEARCH_TREE_TYPE >(incs_array, _avlbinst, bshow);

		SleepMS(2000);

		PECKER_LOG_STR("====================");
		PECKER_LOG_STR("test rb-bst\n");
		rb_bst_set_t _rbbinst;
		bst_add_node_stress_test_by_node< array_t, rb_bst_set_t, RB_BINARY_SEARCH_TREE_TYPE > (incs_array, _rbbinst, bshow);
		bst_find_node_stress_test_by_elem< array_t, rb_bst_set_t, RB_BINARY_SEARCH_TREE_TYPE > (incs_array, _rbbinst, bshow);
		bst_find_node_stress_test_by_node< array_t, rb_bst_set_t, RB_BINARY_SEARCH_TREE_TYPE > (incs_array, _rbbinst, bshow);
		bst_enum_node_stress_test_by_node< rb_bst_set_t, RB_BINARY_SEARCH_TREE_TYPE > (_rbbinst, PFX_BOOL_TRUE, bshow);
		bst_enum_node_stress_test_by_node< rb_bst_set_t, RB_BINARY_SEARCH_TREE_TYPE > (_rbbinst, PFX_BOOL_FALSE, bshow);
		bst_erase_node_stress_test_by_elem< array_t, rb_bst_set_t, RB_BINARY_SEARCH_TREE_TYPE > (incs_array, _rbbinst, bshow);
		//bst_erase_node_stress_test_by_node< array_t, avl_bst_set_t, RB_BINARY_SEARCH_TREE_TYPE >(incs_array, _rbbinst, bshow);
	}

	return 0;
}
