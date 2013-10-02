/*
 * pfx_bst_algorithm.cpp
 *
 *  Created on: 2013-10-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_bst_algorithm.h"
#include "pfx_bst_iterator.h"
#include "../native/pfx_log.h"

#define BST_ALLOCATE_NODE_DEBUG

// 默认
// 分配新的二叉树节点的内存
binary_search_tree_node_t* new_bst_node_func_default(const IAllocator* PARAM_IN pallocator,const binary_search_tree_node_t* PARAM_IN pother_node)
{
	binary_search_tree_node_t* pnode = (binary_search_tree_node_t*)(pallocator->allocate_obj((pfx_long_t)pallocator,sizeof(binary_search_tree_node_t)));
	if (null != pnode)
	{
		pnode->m_key = pother_node->m_key;
		pnode->m_mask.m_mask_bits = pother_node->m_mask.m_mask_bits;

#ifdef BST_ALLOCATE_NODE_DEBUG
		PECKER_LOG_("copy.....other node(key,mask,p,l,r) = (%d,%08X,%08X,%08X,%08X)\n",
			pother_node->m_key,pother_node->m_mask,pother_node->m_parent_node,pother_node->m_pleft_node,pother_node->m_pright_node);
#endif
	}
#ifdef BST_ALLOCATE_NODE_DEBUG
	else
	{
			PECKER_LOG_("allocate fail!!...... ","");
	}
#endif
	return pnode;
}

// 默认
// 删除二叉树节点所占的内存
pfx_result_t delete_bst_node_func_default(const IAllocator* PARAM_IN pallocator,binary_search_tree_node_t* PARAM_IN pdel_node)
{
	if (null != pdel_node)
	{
#ifdef BST_ALLOCATE_NODE_DEBUG
		PECKER_LOG_("delete.....del node(key,mask,p,l,r) = (%d,%08X,%08X,%08X,%08X)\n",
			pdel_node->m_key,pdel_node->m_mask,pdel_node->m_parent_node,pdel_node->m_pleft_node,pdel_node->m_pright_node);
#endif
		pallocator->dellocate_obj((pfx_long_t)pallocator,pdel_node);
		return PFX_STATUS_OK;
	}
	else
	{
#ifdef BST_ALLOCATE_NODE_DEBUG
		PECKER_LOG_("delete node is null.....!!","");
#endif
		return PFX_STATUS_INVALID_OPERATION;
	}
}

pfx_result_t copy_binary_search_tree_unsafe (binary_search_tree_node_t** PARAM_INOUT ppdec_root_node,const binary_search_tree_node_t* PARAM_IN psrc_root_node,
	const IAllocator* PARAM_IN pallocator,new_bst_node_func new_node_method)
{
	binary_search_tree_node_t* ptemp_dec_node;
	binary_search_tree_node_t* ptemp_src_node;
	binary_search_tree_node_t* pnew_node = new_node_method(pallocator,psrc_root_node);

	if (null == pnew_node)
	{
		return PFX_STATUS_MEM_LOW;
	}
	init_binary_search_tree_node_nokey_unsafe(pnew_node,null,null,null);
	*ppdec_root_node = pnew_node;
	ptemp_dec_node = pnew_node;
	ptemp_src_node = (binary_search_tree_node_t*)psrc_root_node;

	do
	{
		if (null == ptemp_dec_node->m_pleft_node)
		{
			if (null != ptemp_src_node->m_pleft_node)
			{
				pnew_node = new_node_method(pallocator,ptemp_src_node->m_pleft_node);
				init_binary_search_tree_node_nokey_unsafe(pnew_node,null,null,ptemp_dec_node);
				ptemp_dec_node->m_pleft_node = pnew_node;
				ptemp_dec_node = pnew_node;

				ptemp_src_node = ptemp_src_node->m_pleft_node;
				continue;
			}

			//if (ptemp_dec_node->m_parent_node)
			//{
			//	ptemp_dec_node = ptemp_dec_node->m_parent_node;
			//}
			//else
			//{
			//	break;
			//}
		}

		if (null == ptemp_dec_node->m_pright_node)
		{
			if (null != ptemp_src_node->m_pright_node)
			{
				pnew_node = new_node_method(pallocator,ptemp_src_node->m_pright_node);
				init_binary_search_tree_node_nokey_unsafe(pnew_node,null,null,ptemp_dec_node);
				ptemp_dec_node->m_pright_node = pnew_node;
				ptemp_dec_node = pnew_node;

				ptemp_src_node = ptemp_src_node->m_pright_node;
				continue;
			}
		}

		ptemp_dec_node = ptemp_dec_node->m_parent_node;
		ptemp_src_node = ptemp_src_node->m_parent_node;
	}while(ptemp_dec_node);
	


	return PFX_STATUS_OK;
}

pfx_result_t clear_binary_search_tree_unsafe (binary_search_tree_node_t** PARAM_INOUT ppdec_root_node,const IAllocator* PARAM_IN pallocator,delete_bst_node_func delete_node_method)
{
	const binary_search_tree_node_t* pbegin;
	const binary_search_tree_node_t* pend;
	pfx_result_t status = PFX_STATUS_OK;

	binary_search_tree_node_t* pdec_root_node;
	RETURN_INVALID_RESULT( (null == ppdec_root_node || null == pallocator || null == delete_node_method ),PFX_STATUS_INVALID_PARAMS);
	pdec_root_node = *ppdec_root_node;

	pbegin = get_binary_search_tree_posorder_begin_node (pdec_root_node);
	pend = get_binary_search_tree_posorder_end_node (pdec_root_node);
	const binary_search_tree_node_t* pcur_node = pbegin;

	*ppdec_root_node = null;
	do
	{
		binary_search_tree_node_t* pdel_node;
		if (null != pcur_node)
		{
			pdel_node = (binary_search_tree_node_t*)pcur_node;
		}
		else
		{
			break;
		}

		if (pcur_node == pend)
		{
			status = delete_node_method(pallocator,pdel_node);
			break;
		}

		pcur_node = binary_search_tree_posorder_increase (pcur_node,pdec_root_node);

		if (null != pcur_node)
		{
			if ( null == pdel_node->m_parent_node)
			{
				status = delete_node_method(pallocator,pdel_node);
				break;
			}

			if (pdel_node->m_parent_node->m_pleft_node == pdel_node)
			{
				pdel_node->m_parent_node->m_pleft_node = null;
			}
			else if (pdel_node->m_parent_node->m_pright_node == pdel_node)
			{
				pdel_node->m_parent_node->m_pright_node = null;
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
				break;
			}
			status = delete_node_method(pallocator,pdel_node);
			if (PFX_STATUS_OK != status)
			{
				return status;
			}

		}
		else
		{
			break;
		}


	}while(1);

	return status;
}


