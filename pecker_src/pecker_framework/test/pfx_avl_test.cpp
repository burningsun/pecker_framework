/*
 * pfx_avl_test.cpp
 *
 *  Created on: 2013-10-2
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../data/pfx_bst_iterator.h"
#include "../data/pfx_bst_algorithm.h"
#include "../native/pfx_log.h"
#include "pfx_file_inputdata_cmd.h"
#include "../native/pfx_stream.h"
#include "../data/pfx_bst_iterator.h"
#include "../data/pfx_avl_tree_algorithm.h"

#include <fstream>
#include <string>
#include <iostream>



#define	NONE_FLAG_				(-1)
#define	INORDER_FLAG_INC	(0)
#define	INORDER_FLAG_DEC	(1)
#define	PREORDER_FLAG		(2)
#define	POSORDER_FLAG		(3)
#define	REPOSORDER_FLAG	(4)

static avl_tree_node_t* proot_node = null;
static pfx_flag_t									 gorder_flag = NONE_FLAG_;
static pfx_index_t								 count = 0;
static avl_tree_node_t* proot_node_2 = null;


pfx_result_t avl_cmd_operate_func(CMD_INOUT_t* cmd_type,const pfx_char_t* pstr_chars,pfx_usize_t nchars_count)
{
	pfx_result_t status;
	pfx_stream_format_t stm_format;
	pfx_index_t	offset = 0;
	init_input_format_ex(&stm_format,PFX_DEC_INT_FORMAT,0,MAX_UNSIGNED_VALUE,0);

	switch (*cmd_type)
	{
	case CMD_ADD:
		{
			avl_tree_node_t* pbst_node = new avl_tree_node_t;
			const _avl_tree_node_t* pbst_added_node = null;
			pfx_result_t status = PFX_STATUS_OK;

			status = string_a_parse_int(pstr_chars,&stm_format,(pfx_sint_t*)&(((_avl_tree_node_t*)pbst_node) ->m_key),&offset);
			if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("parse error!!","");
				break;
			}

			init_binary_search_tree_node_nokey_unsafe((binary_search_tree_node_t*)pbst_node,null,null,null);

			
			pbst_added_node =  (_avl_tree_node_t*)add_avl_node_unsafe(&proot_node,pbst_node,cmp_a_and_b_long,&status);
			if (PFX_STATUS_OK == status)
			{
				PECKER_LOG_("add ok! proot_node=%08X,pbst_added_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
					proot_node,
					pbst_added_node->m_key,
					pbst_added_node->m_parent_node,
					pbst_added_node->m_pleft_node,
					pbst_added_node->m_pright_node);
			}
			else if (PFX_STATUS_UNIQUE == status)
			{
				PECKER_LOG_("add UNIQUE! proot_node=%08X, pbst_added_node=%08X,pbst_added_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
					proot_node,
					pbst_added_node,
					pbst_added_node->m_key,
					pbst_added_node->m_parent_node,
					pbst_added_node->m_pleft_node,
					pbst_added_node->m_pright_node);
			}
			else
			{
				PECKER_LOG_("add error = %d\n",status);
			}
		}

		break;
	case CMD_DEL:
		{
			pfx_long_t key = -1;
			const _avl_tree_node_t* pbst_node;
			

			status = string_a_parse_int(pstr_chars,&stm_format,(pfx_sint_t*)&key,&offset);
			if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("parse error!!","");
				break;
			}

			pbst_node = (const _avl_tree_node_t*)find_node_form_binary_search_tree(key,(const binary_search_tree_node_t*)proot_node,cmp_a_and_b_long);
			if (pbst_node)
			{
				binary_search_tree_node_t* pbst_ref = null;
				pfx_result_t status = PFX_STATUS_OK;

				PECKER_LOG_("find ok! proot_node=%08X,pbst_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
					proot_node,pbst_node->m_key,
					pbst_node->m_parent_node,
					pbst_node->m_pleft_node,
					pbst_node->m_pright_node);

				pbst_node = (_avl_tree_node_t*)remove_avl_node_unsafe(&proot_node,(avl_tree_node_t*)pbst_node,cmp_a_and_b_long,&status);
				//status = remove_bst_node_unsafe(&proot_node,(binary_search_tree_node_t*)pbst_node,&pbst_ref,null);
				if (PFX_STATUS_OK == status)
				{
					PECKER_LOG_("remove ok! proot_node=%08X,pbst_node(key,p,l,r) =  (%ld,%08X,%08X,%08X),pbst_ref = %08X\n",
						proot_node,pbst_node->m_key,
						pbst_node->m_parent_node,
						pbst_node->m_pleft_node,
						pbst_node->m_pright_node,
						pbst_ref);
					delete ((binary_search_tree_node_t*)pbst_node);
					pbst_node = null;
				}
				else
				{
					PECKER_LOG_("remove error = %d\n",status);
				}

			}
			else
			{
				PECKER_LOG_("find nothing!\n",0);
			}


		}
		break;
	case CMD_SEARCH:
		{
			pfx_long_t key = -1;
			const binary_search_tree_node_t* pbst_node;

			status = string_a_parse_int(pstr_chars,&stm_format,(pfx_sint_t*)&key,&offset);
			if (PFX_STATUS_OK != status)
			{
				PECKER_LOG_ ("parse error!!","");
				break;
			}

			pbst_node = find_node_form_binary_search_tree(key,(binary_search_tree_node_t*)proot_node,cmp_a_and_b_long);
			if (pbst_node)
			{
				PECKER_LOG_("find ok! proot_node=%08X,pbst_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
					proot_node,pbst_node->m_key,
					pbst_node->m_parent_node,
					pbst_node->m_pleft_node,
					pbst_node->m_pright_node);
			}
			else
			{
				PECKER_LOG_("find nothing!\n",0);
			}
		}
		break;
	case CMD_COPY:
		{
			if (null == proot_node_2)
			{
				status = copy_binary_search_tree_unsafe((binary_search_tree_node_t**)&proot_node_2,(binary_search_tree_node_t*)proot_node,&gDefualt_allocator,new_bst_node_func_default);
				PECKER_LOG_("copy status = %d\n",status);
			}
			else
			{
				status = clear_binary_search_tree_unsafe((binary_search_tree_node_t**)&proot_node_2,&gDefualt_allocator,delete_bst_node_func_default);
				PECKER_LOG_("clear status = %d\n",status);
				status = copy_binary_search_tree_unsafe((binary_search_tree_node_t**)&proot_node_2,(binary_search_tree_node_t*)proot_node,&gDefualt_allocator,new_bst_node_func_default);
				PECKER_LOG_("copy status = %d\n",status);
			}
		}
		break;
	case CMD_CLR:
		{
			if (null == proot_node_2)
			{
				PECKER_LOG_("proot_node_2 = null!\n","");
			}
			else
			{
				status = clear_binary_search_tree_unsafe((binary_search_tree_node_t**)&proot_node_2,&gDefualt_allocator,delete_bst_node_func_default);
				PECKER_LOG_("clear status = %d\n",status);
			}
		}
		*cmd_type = CMD_NONE;
		break;
	case CMD_TRAINORDER:
			if (0 == strncmp(pstr_chars,"inorder",strlen("inorder")))
			{
				const binary_search_tree_base_node_t* pbegin = get_binary_search_tree_inorder_begin_node ((binary_search_tree_base_node_t*)proot_node);
				const binary_search_tree_base_node_t* pend = get_binary_search_tree_inorder_end_node ((binary_search_tree_base_node_t*)proot_node);

				const binary_search_tree_base_node_t* pcur_node = pbegin;

				if (INORDER_FLAG_INC != gorder_flag)
				{
					gorder_flag = INORDER_FLAG_INC;
					PECKER_LOG_("==========inorder inc=============\n","");
					count = 0;
				}
				do
				{
					++count;
					if (null != pcur_node)
					{
						PECKER_LOG_("%08d pcur_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
							count,
							((binary_search_tree_node_t*)pcur_node)->m_key,
							pcur_node->m_parent_node,
							pcur_node->m_pleft_node,
							pcur_node->m_pright_node);
					}
					else
					{
						break;
					}

					if (pcur_node == pend)
					{
						break;
					}

					pcur_node = binary_search_tree_inorder_increase (pcur_node,(binary_search_tree_base_node_t*)proot_node);
				}while(1);


			}
			else 	if (0 == strncmp(pstr_chars,"posorder",strlen("posorder")))
			{
				const binary_search_tree_base_node_t* pbegin = get_binary_search_tree_posorder_begin_node ((binary_search_tree_base_node_t*)proot_node);
				const binary_search_tree_base_node_t* pend = get_binary_search_tree_posorder_end_node ((binary_search_tree_base_node_t*)proot_node);

				const binary_search_tree_base_node_t* pcur_node = pbegin;

				if (POSORDER_FLAG != gorder_flag)
				{
					gorder_flag = POSORDER_FLAG;
					PECKER_LOG_("==========posorder=============\n","");
					count = 0;
				}

				do
				{
					++count;
					if (null != pcur_node)
					{
						PECKER_LOG_("%08d pcur_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
							count,
							((binary_search_tree_node_t*)pcur_node)->m_key,
							pcur_node->m_parent_node,
							pcur_node->m_pleft_node,
							pcur_node->m_pright_node);
					}
					else
					{
						break;
					}

					if (pcur_node == pend)
					{
						break;
					}

					pcur_node = binary_search_tree_posorder_increase (pcur_node,(binary_search_tree_base_node_t*)proot_node);
				}while(1);


			}
			else 	if (0 == strncmp(pstr_chars,"preorder",strlen("preorder")))
			{
				pfx_preorder_iterator_t					 preorder_itr;
				const binary_search_tree_base_node_t* pbegin;
				const binary_search_tree_base_node_t* pend;
				get_binary_search_tree_preorder_begin_iterator ((binary_search_tree_base_node_t*)proot_node,&preorder_itr);
				pbegin = preorder_itr.m_pcurrent_node;
				pend = get_binary_search_tree_preorder_end_node ((binary_search_tree_base_node_t*)proot_node);

				if (PREORDER_FLAG != gorder_flag)
				{
					gorder_flag = PREORDER_FLAG;
					PECKER_LOG_("==========preorder=============\n","");
					count = 0;
				}

				do
				{
					++count;
					if (null != preorder_itr.m_pcurrent_node)
					{
						PECKER_LOG_("%08d pcur_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
							count,
							((binary_search_tree_node_t*)preorder_itr.m_pcurrent_node)->m_key,
							preorder_itr.m_pcurrent_node->m_parent_node,
							preorder_itr.m_pcurrent_node->m_pleft_node,
							preorder_itr.m_pcurrent_node->m_pright_node);
					}
					else
					{
						break;
					}

					if (PFX_STATUS_OK != preorder_itr.m_last_result)
					{
						PECKER_LOG_("error! status = %d\n",preorder_itr.m_last_result);
						break;
					}

					if (PREORDER_FIN == preorder_itr.m_last_result)
					{
						PECKER_LOG_("finish! status = %d\n",preorder_itr.m_last_result);
						break;
					}

					if (null == binary_search_tree_preorder_increase(&preorder_itr,(binary_search_tree_base_node_t*)proot_node))
					{
						PECKER_LOG_("null! status = %d\n",preorder_itr.m_last_result);
						break;
					}
					//pcur_node = binary_search_tree_posorder_increase (pcur_node,proot_node);
				}while(1);
			}

		break;
	case CMD_TRACOVORDDER:
		if (0 == strncmp(pstr_chars,"inorder",strlen("inorder")))
		{
			const binary_search_tree_base_node_t* pbegin = get_binary_search_tree_inorder_begin_node ((binary_search_tree_base_node_t*)proot_node);
			const binary_search_tree_base_node_t* pend = get_binary_search_tree_inorder_end_node ((binary_search_tree_base_node_t*)proot_node);

			const binary_search_tree_base_node_t* pcur_node = pend;

			if (INORDER_FLAG_DEC != gorder_flag)
			{
				gorder_flag = INORDER_FLAG_DEC;
				PECKER_LOG_("==========inorder dec=============\n","");
				count = 0;
			}

			do
			{
				++count;
				if (null != pcur_node)
				{
					PECKER_LOG_("%08d pcur_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
						count,
						((binary_search_tree_node_t*)pcur_node)->m_key,
						pcur_node->m_parent_node,
						pcur_node->m_pleft_node,
						pcur_node->m_pright_node);
				}
				else
				{
					break;
				}

				if (pcur_node == pbegin)
				{
					break;
				}

				pcur_node = binary_search_tree_inorder_decrease (pcur_node,(binary_search_tree_base_node_t*)proot_node);
			}while(1);
		}
		else 	if (0 == strncmp(pstr_chars,"posorder",strlen("posorder")))
		{
			const binary_search_tree_base_node_t* pbegin = get_binary_search_tree_reverse_posorder_begin_node ((binary_search_tree_base_node_t*)proot_node);
			const binary_search_tree_base_node_t* pend = get_binary_search_tree_reverse_posorder_end_node ((binary_search_tree_base_node_t*)proot_node);

			const binary_search_tree_base_node_t* pcur_node = pbegin;

			if (REPOSORDER_FLAG != gorder_flag)
			{
				gorder_flag = REPOSORDER_FLAG;
				PECKER_LOG_("==========reverse posorder=============\n","");
				count = 0;
			}

			do
			{
				++count;
				if (null != pcur_node)
				{
					PECKER_LOG_("%08d pcur_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
						count,
						((binary_search_tree_node_t*)pcur_node)->m_key,
						pcur_node->m_parent_node,
						pcur_node->m_pleft_node,
						pcur_node->m_pright_node);
				}
				else
				{
					break;
				}

				if (pcur_node == pend)
				{
					break;
				}

				pcur_node = binary_search_tree_reverse_posorder_increase (pcur_node,(binary_search_tree_base_node_t*)proot_node);
			}while(1);


		}
		break;
	default:
		*cmd_type = CMD_NONE;
		break;
	}
	return PFX_STATUS_OK;
}




int avl_test_main()
{
	//return file_data_input_for_test_running("test_data\\bst_test_data.txt",avl_cmd_operate_func);
	//return file_data_input_for_test_running("test_data\\bst_test_data_2.txt",avl_cmd_operate_func);
	//return file_data_input_for_test_running("test_data\\bst_test_data_3.txt",avl_cmd_operate_func);
	//return file_data_input_for_test_running("test_data\\bst_test_data_4.txt",avl_cmd_operate_func);
	//return file_data_input_for_test_running("test_data\\bst_test_data_5.txt",avl_cmd_operate_func);
	//return file_data_input_for_test_running("test_data\\bst_test_data_6.txt",avl_cmd_operate_func);
	//return file_data_input_for_test_running("test_data\\bst_test_data_7.txt",avl_cmd_operate_func);
	//return file_data_input_for_test_running("test_data\\bst_test_data_8.txt",avl_cmd_operate_func);
	return file_data_input_for_test_running("test_data\\bst_test_data_9.txt",avl_cmd_operate_func);
	//return file_data_input_for_test_running("test_data\\bst_test_data_10.txt",avl_cmd_operate_func);
}


