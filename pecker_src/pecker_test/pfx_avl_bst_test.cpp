/*
 * pfx_avl_bst_test.cpp
 *
 *  Created on: 2013-9-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_file_inputdata_cmd.h"
#include "../pecker_framework/data/pfx_binary_search_tree.h"
#include "../pecker_framework/data/pfx_cstring_codes.h"

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
	
typedef pfx_cavl_bst_node < pfx_cstring < pfx_char_t >, pecker_value_compare_extern < pfx_cstring < pfx_char_t > > > bst_string_node_t;
static pfx_binary_search_tree_type < bst_string_node_t >::avl_binary_search_tree_t  bst_strings;
static pfx_binary_search_tree_type < bst_string_node_t >::avl_binary_search_tree_t  bst_copy_strings;
static bst_string_node_t bst_key_node;

PFX_INLINE_CODE void print_avl_bst_node (const bst_string_node_t* PARAM_IN node_ptr)
{
	if (node_ptr)
	{
		const pfx_cstring < pfx_char_t >& string_ref = node_ptr->get_item();
		const pfx_char_t* str_ptr = string_ref.get_string ();
		pfx_char_t strformat[200];
		if (str_ptr)
		{
			sprintf (strformat,"THIS(%08X) <%%.%ds> L(%08X) R(%08X) P(%08X) HEIGHT(%d) BALANCE(%d)",
				(pfx_ulong_t)node_ptr, string_ref.get_length(),
				(pfx_ulong_t)node_ptr->get_left_node(),
				(pfx_ulong_t)node_ptr->get_right_node(),
				(pfx_ulong_t)node_ptr->get_parent_node(),
				(pfx_ulong_t)node_ptr->get_height(),
				pfx_cavl_tree < bst_string_node_t > ::calculate_avl_balance_value(node_ptr));

			PECKER_LOG_DIRECT_A (strformat,str_ptr);
		}
		else
		{
			sprintf (strformat,"THIS(%08X) <null> L(%08X) R(%08X) P(%08X)  HEIGHT(%d) BALANCE(%d)",
				(pfx_ulong_t)node_ptr, string_ref.get_length(),
				(pfx_ulong_t)node_ptr->get_left_node(),
				(pfx_ulong_t)node_ptr->get_right_node(),
				(pfx_ulong_t)node_ptr->get_parent_node(),
				(pfx_ulong_t)node_ptr->get_height(),
				pfx_cavl_tree < bst_string_node_t > ::calculate_avl_balance_value(node_ptr));
			PECKER_LOG_DIRECT_A (strformat);
		}
		
	}
	else
	{
		PECKER_LOG_ ("null node");
	}

	PECKER_LOG_ ("\n");
}

pfx_result_t avl_bst_cmd_operate_func(CMD_INOUT_t* cmd_type,const pfx_char_t* str_chars_ptr,pfx_usize_t nchars_count)
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
			pfx_result_t status = PFX_STATUS_ERROR_;
			const bst_string_node_t* added_node_ptr = bst_strings.add (new_node_ptr,status);
			print_avl_bst_node(added_node_ptr);
		}
		break;
	case CMD_DEL:
		{
			pfx_result_t status = PFX_STATUS_ERROR_;
			nchars_count = nchars_count > 0 ? (nchars_count - 1) : nchars_count;
			bst_key_node.get_item_ref().init_string(str_chars_ptr,nchars_count);
			bst_string_node_t* remove_node_ptr = bst_strings.find_reference(&bst_key_node);
			if (remove_node_ptr)
			{
				remove_node_ptr = bst_strings.remove (remove_node_ptr,status);
				if (PFX_STATUS_OK == status && remove_node_ptr)
				{
					print_avl_bst_node(remove_node_ptr);
					status = bst_strings.release_node(remove_node_ptr);
				}
			}

		}
		break;
	case CMD_SEARCH:
		{
			bst_key_node.get_item_ref().init_string(str_chars_ptr,nchars_count);
			const bst_string_node_t* search_node_ptr = bst_strings.find (&bst_key_node);
			print_avl_bst_node(search_node_ptr);
		}
		break;
	case CMD_COPY:
		{
			pfx_result_t status = bst_copy_strings.copy(&bst_strings);
		}
		break;
	case CMD_CLR:
		{
			pfx_result_t status =bst_copy_strings.clear();
		}
		*cmd_type = CMD_NONE;
		break;
	case CMD_TRAINORDER:
			PECKER_LOG_("============\n");
			PECKER_LOG_DIRECT_A (str_chars_ptr);
			PECKER_LOG_("============\n");
			if (0 == strncmp(str_chars_ptr,"inorder",strlen("inorder")))
			{
				pfx_inorder_iterator < bst_string_node_t > bst_iterator;
				pfx_cbst_iterator < bst_string_node_t >* iterator_ptr = bst_strings.begin (&bst_iterator);
				while (iterator_ptr)
				{

					print_avl_bst_node(iterator_ptr->get_current_node ());
					iterator_ptr = iterator_ptr->increase();
					
				} 
			}
			else 	if (0 == strncmp(str_chars_ptr,"posorder",strlen("posorder")))
			{
				pfx_posorder_iterator < bst_string_node_t > bst_iterator;
				pfx_cbst_iterator < bst_string_node_t >* iterator_ptr = bst_strings.begin (&bst_iterator);

				while (iterator_ptr)
				{
					print_avl_bst_node(iterator_ptr->get_current_node ());
					iterator_ptr = iterator_ptr->increase();
				} 
			}
			else 	if (0 == strncmp(str_chars_ptr,"preorder",strlen("preorder")))
			{
				pfx_preorder_iterator < bst_string_node_t > bst_iterator;
				pfx_cbst_iterator < bst_string_node_t >* iterator_ptr = bst_strings.begin (&bst_iterator);

				while (iterator_ptr)
				{
					print_avl_bst_node(iterator_ptr->get_current_node ());
					iterator_ptr = iterator_ptr->increase();
				} 
			}

		break;
	case CMD_TRACOVORDDER:
		PECKER_LOG_("============\n");
		PECKER_LOG_DIRECT_A (str_chars_ptr);
		PECKER_LOG_("============\n");
		if (0 == strncmp(str_chars_ptr,"inorder",strlen("inorder")))
		{
			pfx_cbst_iterator < bst_string_node_t > bst_iterator;
			pfx_cbst_iterator < bst_string_node_t >* iterator_ptr = bst_strings.end (&bst_iterator);

			while (iterator_ptr) 
			{
				print_avl_bst_node(iterator_ptr->get_current_node ());
				iterator_ptr = iterator_ptr->decrease();
			} 
		}
		else 	if (0 == strncmp(str_chars_ptr,"posorder",strlen("posorder")))
		{
			pfx_posorder_iterator < bst_string_node_t > bst_iterator;
			pfx_cbst_iterator < bst_string_node_t >* iterator_ptr = bst_strings.end (&bst_iterator);
			iterator_ptr = bst_iterator.reverse_begin ();

			while (iterator_ptr)
			{
				print_avl_bst_node(iterator_ptr->get_current_node ());
				iterator_ptr = iterator_ptr->decrease();
			} 
		}
		break;
	default:
		*cmd_type = CMD_NONE;
		break;
	}
	return PFX_STATUS_OK;
}




int avl_bst_test_main()
{
	PECKER_LOG_ ("------------------------------avl test--------------------------------\n");
	PECKER_LOG_ ("*********test_data\\bst_test_data.txt***********\n");
	bst_strings.clear();
	bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_2.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_2.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_3.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_3.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_4.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_4.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_5.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_5.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_6.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_6.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_7.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_7.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_8.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_8.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_9.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_9.txt",avl_bst_cmd_operate_func);

	 PECKER_LOG_ ("\n*********test_data\\bst_test_data_10.txt***********\n");
	 bst_strings.clear();
	 bst_copy_strings.clear();
	 file_data_input_for_test_running("test_data\\bst_test_data_10.txt",avl_bst_cmd_operate_func);
	 return 0;
}


