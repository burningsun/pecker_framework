/*
 * pfx_list_test.cpp
 *
 *  Created on: 2013-9-25
 *      Author: 李镇城 (cut / cutxyz)
 */

#include "../data/pfx_bst_iterator.h"
#include "../data/pfx_bst_algorithm.h"
#include "../native/pfx_log.h"

#include <fstream>
#include <string>
#include <iostream>

typedef enum 
{
	CMD_NONE = 0,
	CMD_ADD,
	CMD_SEARCH,
	CMD_DEL,
	CMD_CLR,
	CMD_TRAINORDER,
	CMD_TRACOVORDDER,
	//CMD_SHOWALL,
	CMD_COUNT,
}CMD_INOUT;

void bst_file_data_test()
{
	std::ifstream myfile;
	myfile.close();
	myfile.open("test_data\\bst_test_data.txt");

	int i =0;
	CMD_INOUT cmdType = CMD_NONE;
	int index = 0;

	binary_search_tree_node_t* proot_node = null;

	while(1)
	{
		if (myfile.eof())
			break;

		switch (cmdType)
		{
		case CMD_ADD:
			{
				binary_search_tree_node_t* pbst_node = new binary_search_tree_node_t;
				binary_search_tree_node_t* pbst_added_node = null;
				myfile >> pbst_node->m_key;

				init_binary_search_tree_node_nokey_unsafe(pbst_node,null,null,null);

				pfx_result_t status = add_bst_node_unsafe(&proot_node,pbst_node,&pbst_added_node,cmp_a_and_b_long);
				if (PFX_STATUS_OK == status)
				{
					PECKER_LOG_("add ok! proot_node=%08X,pbst_added_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
						proot_node,pbst_added_node->m_key,
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
		case CMD_SEARCH:
			{
				pfx_long_t key = -1;
				const binary_search_tree_node_t* pbst_node;

				myfile >> key;
				pbst_node = find_node_form_binary_search_tree(key,proot_node,cmp_a_and_b_long);
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
		case CMD_DEL:
			{
				pfx_long_t key = -1;
				const binary_search_tree_node_t* pbst_node;

				myfile >> key;
				pbst_node = find_node_form_binary_search_tree(key,proot_node,cmp_a_and_b_long);
				if (pbst_node)
				{
					binary_search_tree_node_t* pbst_ref = null;
					pfx_result_t status;

					PECKER_LOG_("find ok! proot_node=%08X,pbst_node(key,p,l,r) =  (%ld,%08X,%08X,%08X)\n",
						proot_node,pbst_node->m_key,
						pbst_node->m_parent_node,
						pbst_node->m_pleft_node,
						pbst_node->m_pright_node);

					status = remove_bst_node_unsafe(&proot_node,(binary_search_tree_node_t*)pbst_node,&pbst_ref,null);
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
		case CMD_CLR:

			break;
		case CMD_TRAINORDER:
			std::cout << "===============trav inorder============= "<< std::endl;
			break;
		case CMD_TRACOVORDDER:
			std::cout << "=============trav decorder =============="<< std::endl;
			break;
		default:
			break;
		}

		std::string strin;
		myfile >> strin;
		if ("[printfn]"==strin)
		{
			std::cout << "===============node buff=========== "<< std::endl;
			std::cout << "=================================== "<< std::endl;

			continue;
		}
		if ("[printfsn]"==strin)
		{
			std::cout << "===============save node buff=========== "<< std::endl;
			std::cout << "=================================== "<< std::endl;

			continue;
		}
		if ("[show]"==strin)
		{
			std::cout << "===============all tree============= "<< std::endl;
			std::cout << "=================================== "<< std::endl;

			continue;
		}
		if ("[none]"==strin)
		{
			cmdType = CMD_NONE;
			continue;
		}
		if ("[add]"==strin)
		{
			cmdType = CMD_ADD;
			std::cout << "===============add============= "<< std::endl;
			continue;
		}
		else if ("[del]"==strin)
		{
			cmdType = CMD_DEL;
			std::cout << "===============del============= "<< std::endl;
			continue;
		}
		else if("[search]"==strin)
		{
			cmdType = CMD_SEARCH;
			std::cout << "===============search============= "<< std::endl;
			continue;
		}
		else if ("[clr]"==strin)
		{
			cmdType = CMD_CLR;
			std::cout << "===============clr============= "<< std::endl;
			//continue;
		}
		else if ("[incorder]"==strin)
		{
			cmdType = CMD_TRAINORDER;
			std::cout << "===============incorder============= "<< std::endl;
			continue;
		}
		else if ("[decorder]"==strin)
		{
			cmdType = CMD_TRACOVORDDER;
			std::cout << "===============decorder============= "<< std::endl;
			continue;
		}
		else if ("[Visiable]"==strin)
		{
			continue;
		}
		else if ("[Hide]"==strin)
		{
			continue;
		}


	}

	int ibreak;
	std::cin >> ibreak;
}


int bst_test_main()
{

	bst_file_data_test();
	return 0;
}


