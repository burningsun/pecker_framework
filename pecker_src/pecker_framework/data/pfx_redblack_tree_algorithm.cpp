/*
 * pfx_redblack_tree_algorithm.cpp
 *
 *  Created on: 2013-10-3
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */


#include "pfx_redblack_tree_algorithm.h"


PFX_INLINE_CODE void rb_tree_left_rotate (_redblack_tree_node_t ** PARAM_INOUT proot_node, 
	_redblack_tree_node_t *	PARAM_INOUT psentinel_node,
	_redblack_tree_node_t *	PARAM_INOUT pnode)
{
	_redblack_tree_node_t  *ptemp_node;

	ptemp_node = pnode->m_pright_node;
	pnode->m_pright_node = ptemp_node->m_pleft_node;

	if (ptemp_node->m_pleft_node != psentinel_node) 
	{
		ptemp_node->m_pleft_node->m_parent_node = pnode;
	}

	ptemp_node->m_parent_node = pnode->m_parent_node;

	if (pnode == *proot_node) 
	{
		*proot_node = ptemp_node;
	} 
	else if (pnode == pnode->m_parent_node->m_pleft_node) 
	{
		pnode->m_parent_node->m_pleft_node = ptemp_node;
	} else 
	{
		pnode->m_parent_node->m_pright_node = ptemp_node;
	}

	ptemp_node->m_pleft_node = pnode;
	pnode->m_parent_node = ptemp_node;
}

PFX_INLINE_CODE void rb_tree_right_rotate (_redblack_tree_node_t **	PARAM_INOUT	proot_node, 
	_redblack_tree_node_t *	PARAM_INOUT	psentinel_node,
	_redblack_tree_node_t *	PARAM_INOUT	pnode)
{
	_redblack_tree_node_t  *ptemp_node;

	ptemp_node = pnode->m_pleft_node;
	pnode->m_pleft_node = ptemp_node->m_pright_node;

	if (ptemp_node->m_pright_node != psentinel_node) 
	{
		ptemp_node->m_pright_node->m_parent_node = pnode;
	}

	ptemp_node->m_parent_node = pnode->m_parent_node;

	if (pnode == *proot_node) 
	{
		*proot_node = ptemp_node;
	} 
	else if (pnode == pnode->m_parent_node->m_pright_node) 
	{
		pnode->m_parent_node->m_pright_node = ptemp_node;
	}
	else 
	{
		pnode->m_parent_node->m_pleft_node = ptemp_node;
	}

	ptemp_node->m_pright_node = pnode;
	pnode->m_parent_node = ptemp_node;
}

PFX_INLINE_CODE pfx_result_t rb_tree_add_rotate_fixup (_redblack_tree_node_t ** PARAM_INOUT proot_node,
	_redblack_tree_node_t*  PARAM_INOUT padd_node)
{
	_redblack_tree_node_t* ptemp_node;
	pfx_bool_t is_color_temp = pfx_false;

	// 根节点的颜色一定是黑的
	if (padd_node == *proot_node)
	{
		set_rb_tree_color_black_unsafe (padd_node);
		return PFX_STATUS_OK;
	}

	while (padd_node != *proot_node && 
		pfx_true == (is_color_temp = check_rb_tree_color_is_red (padd_node->m_parent_node))) 
	{
		RETURN_INVALID_RESULT (null == padd_node->m_parent_node->m_parent_node,PFX_STATUS_MEM_ERR);

		if (padd_node->m_parent_node == padd_node->m_parent_node->m_parent_node->m_pleft_node) 
		{
			ptemp_node = padd_node->m_parent_node->m_parent_node->m_pright_node; 
			is_color_temp = check_rb_tree_color_is_red (ptemp_node);
			RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp),PFX_STATUS_MEM_ERR);
			if (pfx_true == is_color_temp)
			{
				set_rb_tree_color_black_unsafe (padd_node->m_parent_node);
				set_rb_tree_color_black_unsafe (ptemp_node);
				set_rb_tree_color_red_unsafe (padd_node->m_parent_node->m_parent_node);
				padd_node = padd_node->m_parent_node->m_parent_node;
			}
			else
			{
				if (padd_node == padd_node->m_parent_node->m_pright_node)  // lr
				{
					padd_node = padd_node->m_parent_node;
					rb_tree_left_rotate (proot_node,null,padd_node);
				} 
				set_rb_tree_color_black_unsafe (padd_node->m_parent_node); 
				set_rb_tree_color_red_unsafe (padd_node->m_parent_node->m_parent_node);
				rb_tree_right_rotate (proot_node,null,padd_node->m_parent_node->m_parent_node);
			}

		} 
		else 
		{

			ptemp_node = padd_node->m_parent_node->m_parent_node->m_pleft_node;
			is_color_temp = check_rb_tree_color_is_red (ptemp_node);
			RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp),PFX_STATUS_MEM_ERR);
			if (pfx_true == is_color_temp)
			{
				set_rb_tree_color_black_unsafe (padd_node->m_parent_node);
				set_rb_tree_color_black_unsafe (ptemp_node);
				set_rb_tree_color_red_unsafe (padd_node->m_parent_node->m_parent_node);
				padd_node = padd_node->m_parent_node->m_parent_node;
			}
			else
			{
				if (padd_node == padd_node->m_parent_node->m_pleft_node) // rl
				{
					padd_node = padd_node->m_parent_node;
					rb_tree_right_rotate (proot_node,null,padd_node);
				}

				set_rb_tree_color_black_unsafe (padd_node->m_parent_node);
				set_rb_tree_color_red_unsafe (padd_node->m_parent_node->m_parent_node);
				rb_tree_left_rotate (proot_node,null,padd_node->m_parent_node->m_parent_node);

			}
		}
	}

	set_rb_tree_color_black_unsafe (*proot_node);
	return PFX_STATUS_OK;
}

PFX_INLINE_CODE pfx_result_t rb_tree_remove_rotate_fixup (_redblack_tree_node_t ** PARAM_INOUT root,
	_redblack_tree_node_t*  PARAM_INOUT pref_node)
{
	_redblack_tree_node_t* ptemp_node;
	pfx_bool_t is_color_temp1 = pfx_false;
	pfx_bool_t is_color_temp2;

	RETURN_INVALID_RESULT ((null == pref_node),PFX_STATUS_OK);

	while (pref_node != *root && 
		pfx_true == (is_color_temp1 = check_rb_tree_color_is_black (pref_node)) ) 
	{
		RETURN_INVALID_RESULT ((null == pref_node),PFX_STATUS_MEM_ERR);

		if (pref_node == pref_node->m_parent_node->m_pleft_node)
		{
			ptemp_node = pref_node->m_parent_node->m_pright_node;

			is_color_temp1 = check_rb_tree_color_is_red (ptemp_node);

			if (pfx_true == is_color_temp1)
			{
				set_rb_tree_color_black_unsafe (ptemp_node);
				set_rb_tree_color_red_unsafe (pref_node->m_parent_node);
				rb_tree_left_rotate (root,null,pref_node->m_parent_node);
				ptemp_node = pref_node->m_parent_node->m_pright_node;
			}
			else if (pfx_false != is_color_temp1)
			{
				return PFX_STATUS_MEM_ERR;
			}
			
			is_color_temp1 = check_rb_tree_color_is_black (ptemp_node->m_pleft_node) ;
			is_color_temp2 = check_rb_tree_color_is_black (ptemp_node->m_pright_node);

			RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp1 || pfx_invalid == is_color_temp2) , PFX_STATUS_MEM_ERR);

			if (pfx_true == is_color_temp1 && pfx_true == is_color_temp2)
			{
				set_rb_tree_color_red_unsafe (ptemp_node);
				pref_node = pref_node->m_parent_node;
			}
			else
			{
				is_color_temp1 = check_rb_tree_color_is_black (ptemp_node->m_pright_node);
				RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp1),PFX_STATUS_MEM_ERR);

				if (pfx_true == is_color_temp1)
				{
					set_rb_tree_color_black_unsafe (ptemp_node->m_pleft_node);
					set_rb_tree_color_red_unsafe (ptemp_node);
					rb_tree_right_rotate (root,null,ptemp_node);
					ptemp_node = pref_node->m_parent_node->m_pright_node;
				}

				copy_rb_tree_color_unsafe (ptemp_node,pref_node->m_parent_node);
				set_rb_tree_color_black_unsafe (pref_node->m_parent_node);
				set_rb_tree_color_black_unsafe (ptemp_node->m_pright_node);
				rb_tree_left_rotate (root,null,pref_node->m_parent_node);
				pref_node = *root;
			}
		}
		else
		{
			ptemp_node = pref_node->m_parent_node->m_pleft_node;
			is_color_temp1 = check_rb_tree_color_is_red (ptemp_node);

			if (pfx_true == is_color_temp1)
			{
				set_rb_tree_color_black_unsafe (ptemp_node);
				set_rb_tree_color_red_unsafe (pref_node->m_parent_node);
				rb_tree_right_rotate (root,null,pref_node->m_parent_node);
				ptemp_node = pref_node->m_parent_node->m_pleft_node;
			}
			else if (pfx_false != is_color_temp1)
			{
				return is_color_temp1;
			}

			is_color_temp1 = check_rb_tree_color_is_black (ptemp_node->m_pleft_node) ;
			is_color_temp2 = check_rb_tree_color_is_black (ptemp_node->m_pright_node);

			RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp1 || pfx_invalid == is_color_temp2) , PFX_STATUS_MEM_ERR);

			if (pfx_true == is_color_temp1 && pfx_true == is_color_temp2)
			{
				set_rb_tree_color_black_unsafe (ptemp_node);
				pref_node = pref_node->m_parent_node;
			}
			else
			{
				is_color_temp1 = check_rb_tree_color_is_black (ptemp_node->m_pleft_node);
				RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp1),PFX_STATUS_MEM_ERR);

				if (pfx_true == is_color_temp1)
				{
					set_rb_tree_color_black_unsafe (ptemp_node->m_pright_node);
					set_rb_tree_color_red_unsafe (ptemp_node);
					rb_tree_left_rotate (root,null,ptemp_node);
					ptemp_node = pref_node->m_parent_node->m_pleft_node;
				}

				copy_rb_tree_color_unsafe (ptemp_node,pref_node->m_parent_node);
				set_rb_tree_color_black_unsafe (pref_node->m_parent_node);
				set_rb_tree_color_black_unsafe (ptemp_node->m_pleft_node);
				rb_tree_right_rotate (root,null,pref_node->m_parent_node);
				pref_node = *root;
			}
		}
	}

	if (pfx_invalid == is_color_temp1)
	{
		return PFX_STATUS_MEM_ERR;
	}
	set_rb_tree_color_black_unsafe (pref_node);
	return PFX_STATUS_OK;
}

//插入节点
const redblack_tree_node_t* add_redblack_node_unsafe (redblack_tree_node_t** PARAM_INOUT pproot_node_ref,
	redblack_tree_node_t* PARAM_INOUT padd_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_result_t			status;
	pfx_s16_t				height;
	redblack_tree_node_t*	ptemp_node = null;
	redblack_tree_node_t*	proot_node;
	redblack_tree_node_t*	padded_parent_node;

	RETURN_INVALID_BY_ACT_RESULT ((null == pproot_node_ref || null == padd_node || null == cmp_method),
		SET_POINTER_VALUE(pstatus,PFX_STATUS_INVALID_PARAMS),null);

	// 插入的初始节点的颜色为红色
	set_rb_tree_color_red_unsafe ((_redblack_tree_node_t*)padd_node);
	status = add_bst_node_unsafe ((binary_search_tree_node_t**)pproot_node_ref,(binary_search_tree_node_t*)padd_node,(binary_search_tree_node_t**)&ptemp_node,cmp_method);

	RETURN_INVALID_BY_ACT_RESULT ((PFX_STATUS_OK != status),SET_POINTER_VALUE(pstatus,status),ptemp_node);

	// 平衡变换
	status = rb_tree_add_rotate_fixup ((_redblack_tree_node_t**)pproot_node_ref,(_redblack_tree_node_t*)padd_node);

	SET_POINTER_VALUE (pstatus,status);
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return padd_node;
}

//移除节点
redblack_tree_node_t* remove_redblack_node_unsafe(redblack_tree_node_t** PARAM_INOUT pproot_node_ref,
	redblack_tree_node_t* PARAM_INOUT premove_node,
	compare_two_value_func cmp_method,
	pfx_result_t* PARAM_INOUT pstatus)
{
	pfx_result_t			status;
	pfx_bool_t				is_red;
	_redblack_tree_node_t*	ptemp_node = null;
	_redblack_tree_node_t*	proot_node;
	_redblack_tree_node_t* psub_romove_ref_node;
	_redblack_tree_node_t* psub_remove_node;

	RETURN_INVALID_BY_ACT_RESULT ((null == pproot_node_ref || null == premove_node || null == cmp_method),
		SET_POINTER_VALUE (pstatus,PFX_STATUS_INVALID_PARAMS),null);

	proot_node = (_redblack_tree_node_t*)*pproot_node_ref;
	psub_romove_ref_node = 
		(_redblack_tree_node_t*)find_remove_replace_node_form_binary_search_tree_unsafe 
		((binary_search_tree_node_t*)premove_node,(binary_search_tree_node_t**)&psub_remove_node,null);

	if (psub_remove_node == proot_node)
	{
		status = remove_bst_node_unsafe_in ((binary_search_tree_node_t**)pproot_node_ref,
			(binary_search_tree_node_t*)premove_node,
			(binary_search_tree_node_t*)psub_remove_node,
			(binary_search_tree_node_t*)psub_romove_ref_node,
			null);

		SET_POINTER_VALUE (pstatus,status);

		if (PFX_STATUS_OK == status)
		{
			if (null != psub_romove_ref_node)
			{
				set_rb_tree_color_black_unsafe (psub_romove_ref_node);
			}
			
			return premove_node;
		}
		return null;
	}

	is_red = check_rb_tree_color_is_red (psub_remove_node);

	status = 	remove_bst_node_unsafe_in ((binary_search_tree_node_t**)pproot_node_ref,
		(binary_search_tree_node_t*)premove_node,
		(binary_search_tree_node_t*)psub_remove_node,
		(binary_search_tree_node_t*)psub_romove_ref_node,null);

	if (null != psub_remove_node && psub_remove_node != (_redblack_tree_node_t*)premove_node)
	{
		copy_rb_tree_color_unsafe (psub_remove_node,(_redblack_tree_node_t*)premove_node);
	}

	SET_POINTER_VALUE (pstatus,status);

	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	RETURN_RESULT ((pfx_true == is_red),premove_node);

	proot_node = (_redblack_tree_node_t*)*pproot_node_ref;

	SET_POINTER_VALUE (pstatus,status);

	RETURN_RESULT ((null == proot_node),premove_node);

	status = rb_tree_remove_rotate_fixup ((_redblack_tree_node_t**)pproot_node_ref,(_redblack_tree_node_t*)psub_romove_ref_node);

	SET_POINTER_VALUE (pstatus,status);

	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return premove_node;

}


















