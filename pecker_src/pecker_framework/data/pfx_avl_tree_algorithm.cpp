/*
 * pfx_avl_tree_algorithm.cpp
 *
 *  Created on: 2013-9-20
 *      Author: 李镇城 (cut / cutxyz)
 */

#include "pfx_avl_tree_algorithm.h"

//RR型旋转
PFX_INLINE_CODE _avl_tree_node_t* avl_rr_rotate (_avl_tree_node_t* PARAM_INOUT pAvl_node)
{
	//avl_tree_node_t* ptmp_parent_node = (avl_tree_node_t*)pAvl_node->m_bst_node.m_parent_node;
	_avl_tree_node_t* pAvl_rt_node = pAvl_node->m_pright_node;

	pAvl_node->m_pright_node = pAvl_rt_node->m_pleft_node;
	pAvl_rt_node->m_pleft_node  = pAvl_node;

	if (pAvl_node->m_pright_node)
	{
		pAvl_node->m_pright_node->m_parent_node =  pAvl_node;
	}
	pAvl_rt_node->m_parent_node = pAvl_node->m_parent_node;
	pAvl_node->m_parent_node =  pAvl_rt_node;



	pAvl_node->m_balance_value.m_balance_value.m_height  = 
		calculate_avl_node_height_by_two_leave (pAvl_node->m_pleft_node,
																					pAvl_node->m_pright_node);

	pAvl_rt_node->m_balance_value.m_balance_value.m_height  = 
		calculate_avl_node_height_by_two_leave (pAvl_rt_node->m_pleft_node,
																					pAvl_rt_node->m_pright_node);
	return pAvl_rt_node;
}
//LL型旋转
PFX_INLINE_CODE _avl_tree_node_t* avl_ll_rotate (_avl_tree_node_t* PARAM_INOUT pAvl_node)
{
	_avl_tree_node_t* pAvl_rt_node = pAvl_node->m_pleft_node; 
	
	pAvl_node->m_pleft_node  = pAvl_rt_node->m_pright_node;
	pAvl_rt_node->m_pright_node = pAvl_node;

	if (pAvl_node->m_pleft_node)
	{
		pAvl_node->m_pleft_node->m_parent_node = pAvl_node;
	}
	pAvl_rt_node->m_parent_node = pAvl_node->m_parent_node;
	pAvl_node->m_parent_node =  pAvl_rt_node;


	pAvl_node->m_balance_value.m_balance_value.m_height  = 
		calculate_avl_node_height_by_two_leave (pAvl_node->m_pleft_node,
																					pAvl_node->m_pright_node);

	pAvl_rt_node->m_balance_value.m_balance_value.m_height = 
		calculate_avl_node_height_by_two_leave (pAvl_rt_node->m_pleft_node,
		pAvl_rt_node->m_pright_node);
	
	return pAvl_rt_node;
}
// LR型旋转
// LR = RR(pRoot->m_iRIndex) + LL(pRoot)
PFX_INLINE_CODE _avl_tree_node_t* avl_lr_rotate (_avl_tree_node_t* PARAM_INOUT pAvl_node)
{ 
	pAvl_node->m_pleft_node =  avl_rr_rotate (pAvl_node->m_pleft_node);
	return avl_ll_rotate (pAvl_node);
}
// RL型旋转
// RL = LL(pRoot->m_iRIndex) + RR(pRoot)
PFX_INLINE_CODE _avl_tree_node_t* avl_rl_rotate (_avl_tree_node_t* PARAM_INOUT pAvl_node)
{
	pAvl_node->m_pright_node = avl_ll_rotate (pAvl_node->m_pright_node);
	return avl_rr_rotate (pAvl_node);
}


//单节点旋转变换
PFX_INLINE_CODE AVLTREE_ROTATE_t AVL_rotate_singlenode (pfx_s16_t ibalance_value,_avl_tree_node_t* PARAM_INOUT pAvl_node,
	_avl_tree_node_t** PARAM_INOUT ppAvl_node_parent_ref)
{
	if (-2 < ibalance_value && ibalance_value > 2)
	{
		return AVLTREE_NONE_ROTATE;
	}

	if (2 == ibalance_value)
	{
		_avl_tree_node_t * pAvl_left_node = (pAvl_node->m_pleft_node);

		if (null == pAvl_left_node)
		{
			return AVLTREE_ROTATE_ERR;
		}
		else if ( get_avl_node_height((pAvl_left_node->m_pleft_node)) >= 
				get_avl_node_height((pAvl_left_node->m_pright_node)))
			{
				*ppAvl_node_parent_ref = avl_ll_rotate(pAvl_node);
				return AVLTREE_LL_ROTATE;
			}
			else
			{
				*ppAvl_node_parent_ref = avl_lr_rotate(pAvl_node);
				return AVLTREE_LR_ROTATE;
			}
	}

	if(-2 == ibalance_value)
	{
		_avl_tree_node_t * pAvl_right_node =(_avl_tree_node_t*)(pAvl_node->m_pright_node);
		if (null == pAvl_right_node)
		{
			return AVLTREE_ROTATE_ERR;
		}

		if ( get_avl_node_height(pAvl_right_node->m_pright_node) 
			>= get_avl_node_height(pAvl_right_node->m_pleft_node))
		{
			*ppAvl_node_parent_ref = avl_rr_rotate(pAvl_node);
			return AVLTREE_RR_ROTATE;
		}
		else
		{
			*ppAvl_node_parent_ref = avl_rl_rotate(pAvl_node);
			return AVLTREE_RL_ROTATE;
		}
	}

	return AVLTREE_NOT_SIMPLE_ROTATE;

}

PFX_INLINE_CODE pfx_result_t AVL_update_rotate (_avl_tree_node_t** PARAM_INOUT ppavl_root_node_ref,
																							_avl_tree_node_t* PARAM_INOUT pbegin_node)
{
	pfx_result_t			status;
	pfx_s16_t				height;
	_avl_tree_node_t*	proot_node;
	_avl_tree_node_t*	parent_node;

	proot_node = *ppavl_root_node_ref;
	pbegin_node->m_balance_value.m_balance_value.m_height = calculate_avl_node_height(pbegin_node);

	do 
	{
		AVLTREE_ROTATE_t rotate_type;
		_avl_tree_node_t** pptemp_node_ref;

		//pbegin_node->m_balance_value.m_balance_value.m_height = calculate_avl_node_height(pbegin_node);
		parent_node = (_avl_tree_node_t*)(pbegin_node->m_parent_node);

		if (null == parent_node)
		{
			break;
		}

		if (pbegin_node == parent_node)
		{
			status = PFX_STATUS_MEM_ERR;
			break;
		}

		if (null != proot_node && 
			proot_node->m_parent_node == parent_node->m_parent_node)
		{
			break;
		}

		height = parent_node->m_balance_value.m_balance_value.m_height;
		parent_node->m_balance_value.m_balance_value.m_height = calculate_avl_node_height(parent_node);

		if ((parent_node->m_balance_value.m_balance_value.m_height) == height)
		{
			break;
		}

		if (parent_node == proot_node || null == parent_node->m_parent_node)
		{
			pptemp_node_ref = ppavl_root_node_ref;
		}
		else
		{
			if (parent_node->m_parent_node->m_pleft_node == parent_node)
			{
				pptemp_node_ref = (_avl_tree_node_t**)&(parent_node->m_parent_node->m_pleft_node);
			}
			else if (parent_node->m_parent_node->m_pright_node == parent_node)
			{
				pptemp_node_ref = (_avl_tree_node_t**)&(parent_node->m_parent_node->m_pright_node);
			}
			else
			{
				status = PFX_STATUS_MEM_ERR;
				break;
			}
		}

		pbegin_node = parent_node;
		rotate_type = AVL_rotate_singlenode(calculate_avl_node_balance_val(parent_node),parent_node,pptemp_node_ref);
		

		if (AVLTREE_ROTATE_ERR == rotate_type ||
			AVLTREE_NOT_SIMPLE_ROTATE || rotate_type)
		{
			status = PFX_STATUS_ERROR_;
			break;
		}
		else
		{
			status = PFX_STATUS_OK;
		}

	} while (1);

	return status;
}

//插入节点
const avl_tree_node_t* add_avl_node_unsafe (avl_tree_node_t** PARAM_INOUT ppavl_root_node_ref,
	avl_tree_node_t* PARAM_INOUT padd_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus)
{
		pfx_result_t			status;
		pfx_s16_t				height;
		avl_tree_node_t*	ptemp_node = null;
		avl_tree_node_t*	proot_node;
		avl_tree_node_t*	padded_parent_node;
		
	
		if (null == ppavl_root_node_ref || null == padd_node || null == cmp_method)
		{
			if (null != pstatus)
			{
				*pstatus = PFX_STATUS_INVALID_PARAMS;
			}
			return null;
		}
		status = add_bst_node_unsafe( (binary_search_tree_node_t**)ppavl_root_node_ref,(binary_search_tree_node_t*)padd_node,(binary_search_tree_node_t**)&ptemp_node,cmp_method);

		if (PFX_STATUS_OK != status)
		{
			if (null != pstatus)
			{
				*pstatus = status;
			}
			return ptemp_node;
		}

		status = AVL_update_rotate((_avl_tree_node_t**)ppavl_root_node_ref,(_avl_tree_node_t*)padd_node);

		if (null != pstatus)
		{
			*pstatus = status;
		}

		if (PFX_STATUS_OK != status)
		{
			return null;
		}
		return padd_node;
}

//移除节点
avl_tree_node_t* remove_avl_node_unsafe(avl_tree_node_t** PARAM_INOUT ppavl_root_node_ref,
																			 avl_tree_node_t* PARAM_INOUT premove_node,
																			 compare_two_value_func cmp_method,
																			 pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_result_t			status;
	pfx_s16_t				height;
	avl_tree_node_t*	ptemp_node = null;
	avl_tree_node_t*	proot_node;
	avl_tree_node_t*	parent_node;

	if (null == ppavl_root_node_ref || null == premove_node || null == cmp_method)
	{
		if (null != pstatus)
		{
			*pstatus = PFX_STATUS_INVALID_PARAMS;
		}
		return null;
	}

	status = remove_bst_node_unsafe((binary_search_tree_node_t**)ppavl_root_node_ref,
																(binary_search_tree_node_t*)premove_node,
																(binary_search_tree_node_t**)&ptemp_node,
																null);

	if (PFX_STATUS_OK != status)
	{
		if (null != pstatus)
		{
			*pstatus = status;
		}
		return premove_node;
	}

	ptemp_node->m_avl_node.m_balance_value.m_balance_value.m_height = calculate_avl_node_height((_avl_tree_node_t*)ptemp_node);
	parent_node = (avl_tree_node_t*)(ptemp_node->m_avl_node.m_parent_node);

	status = AVL_update_rotate((_avl_tree_node_t**)ppavl_root_node_ref,(_avl_tree_node_t*)ptemp_node);

	if (null != pstatus)
	{
		*pstatus = status;
	}

	if (PFX_STATUS_OK != status)
	{
		return null;
	}
	return premove_node;

}



////插入节点
//const avl_tree_node_t* add_avl_node_unsafe (avl_tree_node_t** PARAM_INOUT ppAvl_root_node_ref,
//	avl_tree_node_t* PARAM_INOUT pAdd_node,
//	compare_two_value_func cmp_method,
//	pfx_result_t* PARAM_INOUT pstatus)
//{
//	avl_tree_node_t*	pnode_to_be_add;
//	avl_tree_node_t*	proot_node;
//	int							cmp_result;
//	avl_tree_node_t*	parent_node;
//	avl_tree_node_t*	parent_parent_node;
//	avl_tree_node_t*	proot_parent_node;
//
//	if (null == ppAvl_root_node_ref || null == pAdd_node || null == cmp_method)
//	{
//		if (null != pstatus)
//		{
//			*pstatus = PFX_STATUS_INVALID_PARAMS;
//		}
//		return null;
//	}
//	proot_node = *ppAvl_root_node_ref;
//	
//	// 添加第一个节点
//	if (null == proot_node)
//	{
//		*ppAvl_root_node_ref = pAdd_node;
//		init_binary_search_tree_node_nokey_unsafe ((binary_search_tree_node_t*)pAdd_node,null,null,null);
//		pAdd_node->m_balance_value.m_balance_value.m_height = get_avl_node_height (pAdd_node);
//		return pAdd_node;
//	}
//
//	proot_parent_node = (avl_tree_node_t*)proot_node->m_bst_node.m_parent_node;
//
//	pnode_to_be_add = (avl_tree_node_t*)find_first_near_node_form_binary_search_tree (pAdd_node->m_bst_node.m_key,
//		(binary_search_tree_node_t*)proot_node,cmp_method,
//		&cmp_result);
//
//	if (null != pnode_to_be_add && 0 == cmp_result)
//	{
//		if (null != pstatus)
//		{
//			*pstatus = PFX_STATUS_UNIQUE;
//		}
//		return pnode_to_be_add;
//	}
//
//	parent_node = (avl_tree_node_t*)pnode_to_be_add->m_bst_node.m_parent_node;
//
//	// 插入节点
//	if (0 > cmp_result)
//	{
//		pnode_to_be_add->m_bst_node.m_pleft_node = (binary_search_tree_node_t*)pAdd_node;
//		pAdd_node->m_bst_node.m_parent_node = (binary_search_tree_node_t*)pnode_to_be_add;
//	}
//	else
//	{
//		pnode_to_be_add->m_bst_node.m_pright_node = (binary_search_tree_node_t*)pAdd_node;
//		pAdd_node->m_bst_node.m_parent_node = (binary_search_tree_node_t*)pnode_to_be_add;
//	}
//
//	init_binary_search_tree_node_nokey_unsafe ((binary_search_tree_node_t*)pAdd_node,null,null,null);
//	pAdd_node->m_balance_value.m_balance_value.m_height = get_avl_node_height (pAdd_node);
//	pnode_to_be_add->m_balance_value.m_balance_value.m_height = get_avl_node_height (pnode_to_be_add);
//
//	if (proot_parent_node != parent_node)
//	{
//		parent_parent_node = (avl_tree_node_t*)parent_node->m_bst_node.m_parent_node;
//	}
//	else
//	{
//		return pAdd_node;
//	}
//
//
//	if (null != pstatus)
//	{
//		*pstatus = PFX_STATUS_OK;
//	}
//
//	// 旋转变换
//	do 
//	{
//		AVLTREE_ROTATE_t rotate_type;
//		pfx_s16_t old_height = parent_node->m_balance_value.m_balance_value.m_height;
//		pfx_s16_t balance_val = calculate_avl_node_height (parent_node);
//		avl_tree_node_t** pref_node = null;
//		
//		// 根节点的父节点与当前节点的爷节点相等，表明当前父节点为根节点
//		if (proot_parent_node == parent_parent_node)
//		{
//			rotate_type = AVL_rotate_singlenode (balance_val,parent_node,ppAvl_root_node_ref);
//
//			if (null != pstatus)
//			{
//				if (	AVLTREE_ROTATE_ERR == rotate_type ||
//					AVLTREE_NOT_SIMPLE_ROTATE || rotate_type)
//				{
//					*pstatus = PFX_STATUS_ERROR_;
//				}
//				else
//				{
//					*pstatus = PFX_STATUS_OK;
//				}
//			}
//
//			break;
//		}
//
//		// 推递进行各级旋转变换
//		if (parent_node == (avl_tree_node_t*)parent_parent_node->m_bst_node.m_pleft_node)
//		{
//			pref_node = (avl_tree_node_t**)&(parent_parent_node->m_bst_node.m_pleft_node);
//			
//		}
//		else if (parent_node == (avl_tree_node_t*)parent_parent_node->m_bst_node.m_pright_node)
//		{
//			pref_node = (avl_tree_node_t**)&(parent_parent_node->m_bst_node.m_pright_node);
//		}
//		else // 出错判断，当父节点不是爷节点的左节点或右节点的时候出错
//		{
//			if (null != pstatus)
//			{
//				*pstatus = PFX_STATUS_ERROR_;
//			}
//			pAdd_node = null;
//			break;
//		}
//		
//		rotate_type = AVL_rotate_singlenode (balance_val,parent_node,pref_node);
//		// 旋转出错处理
//		if (AVLTREE_ROTATE_ERR == rotate_type ||
//			AVLTREE_NOT_SIMPLE_ROTATE || rotate_type)
//		{
//			if (null != pstatus)
//			{
//				*pstatus = PFX_STATUS_ERROR_;
//			}
//			break;
//		}
//
//		// 旋转变换后，对应位置节点的高度不变，则不用继续推递下去
//		if (old_height == (*pref_node)->m_balance_value.m_balance_value.m_height)
//		{
//			break;
//		}
//
//		// 更新推递的父节点和爷节点
//		parent_node = parent_parent_node;
//		if (parent_node)
//		{
//			parent_parent_node = (avl_tree_node_t*)parent_node->m_bst_node.m_parent_node;
//			continue;
//		}
//		else
//		{
//			break;
//		}
//		
//	} while (1);
//
//
//	return pAdd_node;
//}
//
////移除节点
//avl_tree_node_t* remove_avl_node_unsafe(avl_tree_node_t** PARAM_INOUT ppAvl_root_node_ref,
//	avl_tree_node_t* PARAM_INOUT premove_node,
//	compare_two_value_func cmp_method,
//	pfx_result_t* PARAM_INOUT pstatus)
//{
//	int cmp_result;
//	pfx_s16_t				balance_val;
//	avl_tree_node_t* proot_node;
//	avl_tree_node_t* preplace_node_parent;
//	avl_tree_node_t* preplace_node;
//
//	// 有效性判断
//	if (null == ppAvl_root_node_ref || null == cmp_method)
//	{
//		if (null != pstatus)
//		{
//			*pstatus = PFX_STATUS_INVALID_PARAMS;
//		}
//		return null;
//	}
//
//	if (null == premove_node)
//	{
//		if (null != pstatus)
//		{
//			*pstatus = PFX_STATUS_OK;
//		}
//		return null;
//	}
//
//	proot_node = *ppAvl_root_node_ref;
//	if (null == proot_node)
//	{
//		if (null != pstatus)
//		{
//			*pstatus = PFX_STATUS_INVALID_PARAMS;
//		}
//		return null;
//	}
//
//
//
//
//	//proot_parent_node = (avl_tree_node_t*)proot_node->m_bst_node.m_parent_node;
//	//parent_node = (avl_tree_node_t*)premove_node->m_bst_node.m_parent_node;
//
//	//if (premove_node == proot_node)
//	//{
//	//	pref_node = ppAvl_root_node_ref;
//	//}
//	//else
//	//{
//	//	parent_parent_node = (avl_tree_node_t*)parent_node->m_bst_node.m_parent_node;
//	//	if (parent_node->m_bst_node.m_pright_node == (binary_search_tree_node_t*)premove_node)
//	//	{
//	//		pref_node = (avl_tree_node_t**)&(parent_node->m_bst_node.m_pright_node);
//	//	}
//	//	else if (parent_node->m_bst_node.m_pleft_node == (binary_search_tree_node_t*)premove_node)
//	//	{
//	//		pref_node = (avl_tree_node_t**)&(parent_node->m_bst_node.m_pleft_node);
//	//	}
//	//	else // 出错判断，当父节点不是爷节点的左节点或右节点的时候出错
//	//	{
//	//		if (null != pstatus)
//	//		{
//	//			*pstatus = PFX_STATUS_ERROR_;
//	//		}
//
//	//		return null;
//	//	}
//	//}
//
//
//
//
//	
//
//	return premove_node;
//}


