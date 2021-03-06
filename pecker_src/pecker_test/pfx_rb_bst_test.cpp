﻿/*
 * pfx_rb_bst_test.cpp
 *
 *  Created on: 2013-9-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_file_inputdata_cmd.h"
#include "../pecker_framework/data/pfx_binary_search_tree.h"
#include "../pecker_framework/data/pfx_cstring_codes.h"
#include "../pecker_framework/data/pfx_string_cmp_codes.h"

#define	NONE_FLAG_				(-1)
#define	INORDER_FLAG_INC	(0)
#define	INORDER_FLAG_DEC	(1)
#define	PREORDER_FLAG		(2)
#define	POSORDER_FLAG		(3)
#define	REPOSORDER_FLAG	(4)

//static avl_tree_node_t* proot_node = null;
//static pfx_flag_t					gorder_flag = NONE_FLAG_;
//static pfx_index_t				count = 0;
//static avl_tree_node_t* proot_node_2 = null;
USING_PECKER_SDK
	
typedef pecker_simple_allocator< char_t > allc_char_t;
typedef crb_bst_node < cstring < allc_char_t > > bst_string_node_t;
typedef  pfx_binary_search_tree_type < bst_string_node_t, 
	compare_two_node< bst_string_node_t, bst_string_node_t, string_compare < cstring < allc_char_t > > > >::redblack_binary_search_tree_t bst_t;
static bst_t  bst_strings;
static bst_t  bst_copy_strings;
static bst_string_node_t bst_key_node;


PFX_INLINE_CODE void print_rb_bst_node (const bst_string_node_t* PARAM_IN node_ptr)
{
	if (node_ptr)
	{
		const cstring < allc_char_t >& string_ref = node_ptr->get_item();
		const char_t* str_ptr = string_ref.get_string ();
		char_t strformat[200];
		const char_t* str_color = "unknow color";
		if (RED_COLOR_NODE_TYPE == node_ptr->get_color())
		{
			str_color = "red";
		}
		else if (BLACK_COLOR_NODE_TYPE == node_ptr->get_color())
		{
			str_color = "black";
		}

		if (str_ptr)
		{
			sprintf_s (strformat, sizeof (strformat),"THIS(%08X) <%%.%ds> L(%08X) R(%08X) P(%08X) COLOR(%%s)",
				(ulong_t)node_ptr, string_ref.get_length(),
				(ulong_t)node_ptr->get_left_node(),
				(ulong_t)node_ptr->get_right_node(),
				(ulong_t)node_ptr->get_parent_node());

			PECKER_LOG_DIRECT_A (strformat,str_ptr,str_color);
		}
		else
		{
			sprintf_s (strformat,sizeof (strformat),"THIS(%08X) <null> L(%08X) R(%08X) P(%08X) COLOR(%s)",
				(ulong_t)node_ptr, //string_ref.get_length(),
				(ulong_t)node_ptr->get_left_node(),
				(ulong_t)node_ptr->get_right_node(),
				(ulong_t)node_ptr->get_parent_node(),
				str_color);
			PECKER_LOG_DIRECT_A (strformat,str_ptr);
		}
		
	}
	else
	{
		PECKER_LOG_STR	 ("null node");
	}

	PECKER_LOG_STR ("\n");
}

result_t rb_bst_cmd_operate_func(CMD_INOUT_t* cmd_type,const char_t* str_chars_ptr,usize__t nchars_count)
{
	switch (*cmd_type)
	{
	case CMD_ADD:
		{
			if (str_chars_ptr && '8' == str_chars_ptr[0])
			{
				int debug_flag;
				debug_flag = 1;
			}
			nchars_count = nchars_count > 0 ? (nchars_count - 1) : nchars_count;
			bst_string_node_t* new_node_ptr =  bst_strings.new_node();
			new_node_ptr->get_item_ref().init_string(str_chars_ptr,nchars_count);
			result_t status = PFX_STATUS_ERROR_;
			const bst_string_node_t* added_node_ptr = bst_strings.add (new_node_ptr, status);
			print_rb_bst_node(added_node_ptr);
		}
		break;
	case CMD_DEL:
		{
			result_t status = PFX_STATUS_ERROR_;
			nchars_count = nchars_count > 0 ? (nchars_count - 1) : nchars_count;
			bst_key_node.get_item_ref().init_string(str_chars_ptr,nchars_count);
			bst_string_node_t* remove_node_ptr = (bst_string_node_t*)bst_strings.find(&bst_key_node);
			if (remove_node_ptr)
			{
				remove_node_ptr = bst_strings.remove (remove_node_ptr,status);
				if (PFX_STATUS_OK == status && remove_node_ptr)
				{
					print_rb_bst_node(remove_node_ptr);
					status = bst_strings.release_node(remove_node_ptr);
				}
			}

		}
		break;
	case CMD_SEARCH:
		{
			bst_key_node.get_item_ref().init_string(str_chars_ptr,nchars_count);
			const bst_string_node_t* search_node_ptr = bst_strings.find (&bst_key_node);
			print_rb_bst_node(search_node_ptr);
		}
		break;
	case CMD_COPY:
		{
			result_t status = bst_copy_strings.copy(bst_strings.get_root());
		}
		break;
	case CMD_CLR:
		{
			result_t status =bst_copy_strings.clean();
		}
		*cmd_type = CMD_NONE;
		break;
	case CMD_TRAINORDER:
		PECKER_LOG_STR("============\n");
		PECKER_LOG_STR (str_chars_ptr);
		PECKER_LOG_STR("============\n");
		if (0 == strncmp(str_chars_ptr,"inorder",strlen("inorder")))
		{
			bst_t::const_inorder_itr_t bst_iterator;
			bst_t::const_inorder_itr_t* iterator_ptr = bst_strings.begin (bst_iterator);
			while (iterator_ptr)
			{

				print_rb_bst_node(iterator_ptr->cur_node());
				iterator_ptr = iterator_ptr->increase();
			} 
		}
		else 	if (0 == strncmp(str_chars_ptr,"posorder",strlen("posorder")))
		{
			bst_t::const_posorder_itr_t bst_iterator;
			bst_t::const_posorder_itr_t* iterator_ptr = bst_strings.begin (bst_iterator);

			while (iterator_ptr)
			{
				print_rb_bst_node(iterator_ptr->cur_node());
				iterator_ptr = iterator_ptr->increase();
			} 
		}
		else 	if (0 == strncmp(str_chars_ptr,"preorder",strlen("preorder")))
		{
			bst_t::const_preorder_itr_t bst_iterator;
			bst_t::const_preorder_itr_t* iterator_ptr = bst_strings.begin (bst_iterator);

			while (iterator_ptr)
			{
				print_rb_bst_node(iterator_ptr->cur_node());
				iterator_ptr = iterator_ptr->increase();
			} 
		}

		break;
	case CMD_TRACOVORDDER:
		PECKER_LOG_STR("============\n");
		PECKER_LOG_STR (str_chars_ptr);
		PECKER_LOG_STR("============\n");
		if (0 == strncmp(str_chars_ptr,"inorder",strlen("inorder")))
		{
			bst_t::const_inorder_itr_t bst_iterator;
			bst_t::const_inorder_itr_t* iterator_ptr = bst_strings.end (bst_iterator);

			while (iterator_ptr) 
			{
				print_rb_bst_node(iterator_ptr->cur_node());
				iterator_ptr = iterator_ptr->decrease();
			} 
		}
		else 	if (0 == strncmp(str_chars_ptr,"posorder",strlen("posorder")))
		{
			bst_t::const_posorder_itr_t bst_iterator;
			bst_t::const_posorder_itr_t* iterator_ptr = bst_strings.end (bst_iterator);
			iterator_ptr = bst_iterator.to_reverse_begin();

			while (iterator_ptr)
			{
				print_rb_bst_node(iterator_ptr->cur_node());
				iterator_ptr = iterator_ptr->increase();
			} 
		}
		break;
	default:
		*cmd_type = CMD_NONE;
		break;
	}
	return PFX_STATUS_OK;
}




int rb_bst_test_main()
{
	PECKER_LOG_STR ("------------------------------rb test--------------------------------\n");
	PECKER_LOG_STR ("*********test_data\\bst_test_data.txt***********\n");
	bst_strings.clean();
	bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_2.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_2.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_3.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_3.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_4.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_4.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_5.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_5.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_6.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_6.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_7.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_7.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_8.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_8.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_9.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_9.txt",rb_bst_cmd_operate_func);

	 PECKER_LOG_STR ("\n*********test_data\\bst_test_data_10.txt***********\n");
	 bst_strings.clean();
	 bst_copy_strings.clean();
	 file_data_input_for_test_running("test_data\\bst_test_data_10.txt",rb_bst_cmd_operate_func);
	 return 0;
}


