/*
 * pfx_bst_iterator.cpp
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */




#include "pfx_bst_iterator.h"


const binary_search_tree_node_t* get_binary_search_tree_inorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null != proot_node)
	{
		return min_binary_search_tree_node_unsafe (proot_node);
	}
	else
	{
		return null;
	}
}

const binary_search_tree_node_t* get_binary_search_tree_inorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null != proot_node)
	{
		return max_binary_search_tree_node_unsafe (proot_node);
	}
	else
	{
		return null;
	}
}

const binary_search_tree_node_t* binary_search_tree_inorder_increase (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
																																	const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null == pcurrent_node || null == proot_node)
	{
		return null;
	}

	if (pcurrent_node == proot_node)
	{
		if (null != pcurrent_node->m_pright_node)
		{
			return min_binary_search_tree_node_unsafe (pcurrent_node->m_pright_node);
		}
		else
		{
			return null;
		}
	}

	if (null != pcurrent_node->m_pright_node)
	{
		return min_binary_search_tree_node_unsafe (pcurrent_node->m_pright_node);
	}


	if (pcurrent_node->m_parent_node->m_pleft_node == pcurrent_node)
	{
		return pcurrent_node->m_parent_node;
	}

	if (pcurrent_node == pcurrent_node->m_parent_node)
	{
		return null;
	}

	pcurrent_node =  pcurrent_node->m_parent_node;
	while (null != pcurrent_node->m_parent_node)
	{
		if (pcurrent_node->m_parent_node->m_pright_node == pcurrent_node)
		{
			pcurrent_node = pcurrent_node->m_parent_node;
			continue;
		}
		if (pcurrent_node->m_parent_node->m_pleft_node == pcurrent_node)
		{
			pcurrent_node = pcurrent_node->m_parent_node;
			break;
		}

	}
	return pcurrent_node;
}
const binary_search_tree_node_t* binary_search_tree_inorder_decrease (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
																																	const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null == pcurrent_node || null == proot_node)
	{
		return null;
	}

	if (pcurrent_node == proot_node)
	{
		if (null != pcurrent_node->m_pleft_node)
		{
			return max_binary_search_tree_node_unsafe (pcurrent_node->m_pleft_node);
		}
		else
		{
			return null;
		}
	}

	if (null != pcurrent_node->m_pleft_node)
	{
		return max_binary_search_tree_node_unsafe (pcurrent_node->m_pleft_node);
	}

	if (pcurrent_node->m_parent_node->m_pright_node == pcurrent_node)
	{
		return pcurrent_node->m_parent_node;
	}

	if (pcurrent_node == pcurrent_node->m_parent_node)
	{
		return null;
	}

	pcurrent_node =  pcurrent_node->m_parent_node;
	while (null != pcurrent_node->m_parent_node)
	{
		if (pcurrent_node->m_parent_node->m_pleft_node == pcurrent_node)
		{
			pcurrent_node = pcurrent_node->m_parent_node;
			continue;
		}
		if (pcurrent_node->m_parent_node->m_pright_node == pcurrent_node)
		{
			pcurrent_node = pcurrent_node->m_parent_node;
			break;
		}

	}
	return pcurrent_node;
		
}




const binary_search_tree_node_t* get_binary_search_tree_posorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null != proot_node)
	{
		const binary_search_tree_node_t* ptemp_node = null;
		
		while (null != proot_node)
		{
			ptemp_node = proot_node;
			if (null != proot_node->m_pleft_node)
			{
				proot_node = proot_node->m_pleft_node;
				continue;
			}
			else 	if (null != proot_node->m_pright_node)
			{
				proot_node = proot_node->m_pright_node;
				continue;
			}
			else
			{
				break;
			}

		}
		return ptemp_node;
		
	}
	else
	{
		return null;
	}
}

const binary_search_tree_node_t* get_binary_search_tree_posorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	return proot_node;
}

const binary_search_tree_node_t* binary_search_tree_posorder_increase (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
	const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (pcurrent_node == proot_node)
	{
		return null;
	}

	if (null == pcurrent_node->m_parent_node)
	{
		return null;
	}

	if (pcurrent_node->m_parent_node->m_pright_node == pcurrent_node)
	{
		return pcurrent_node->m_parent_node;
	}

	if (pcurrent_node->m_parent_node->m_pleft_node == pcurrent_node)
	{
		const binary_search_tree_node_t* ptemp_node;
		const binary_search_tree_node_t* ptemp_node_retn;
		ptemp_node = pcurrent_node->m_parent_node->m_pright_node;
		ptemp_node_retn = pcurrent_node->m_parent_node;

		while (null != ptemp_node)
		{
			ptemp_node_retn = ptemp_node;
			if (null != ptemp_node->m_pleft_node)
			{
				ptemp_node = ptemp_node->m_pleft_node;
				continue;
			}
			else if (null != ptemp_node->m_pright_node)
			{
				ptemp_node = ptemp_node->m_pright_node;
				continue;
			}
			else
			{
				break;
			}

		}
		
		return ptemp_node_retn;
	}

	return null;
}

//////////////////////////////////////////////////////////////////////////

const binary_search_tree_node_t* get_binary_search_tree_reverse_posorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null != proot_node)
	{
		const binary_search_tree_node_t* ptemp_node = null;

		while (null != proot_node)
		{
			ptemp_node = proot_node;
			if (null != proot_node->m_pright_node)
			{
				proot_node = proot_node->m_pright_node;
				continue;
			}
			else if (null != proot_node->m_pleft_node)
			{
				proot_node = proot_node->m_pleft_node;
				continue;
			}
			else
			{
				break;
			}

		}
		return ptemp_node;

	}
	else
	{
		return null;
	}
}

const binary_search_tree_node_t* get_binary_search_tree_reverse_posorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	return proot_node;
}

const binary_search_tree_node_t* binary_search_tree_reverse_posorder_increase (const binary_search_tree_node_t* PARAM_IN pcurrent_node,
	const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (pcurrent_node == proot_node)
	{
		return null;
	}

	if (null == pcurrent_node->m_parent_node)
	{
		return null;
	}

	if (pcurrent_node->m_parent_node->m_pleft_node == pcurrent_node)
	{
		return pcurrent_node->m_parent_node;
	}

	if (pcurrent_node->m_parent_node->m_pright_node == pcurrent_node)
	{
		const binary_search_tree_node_t* ptemp_node;
		const binary_search_tree_node_t* ptemp_node_retn;
		ptemp_node = pcurrent_node->m_parent_node->m_pleft_node;
		ptemp_node_retn = pcurrent_node->m_parent_node;

		while (null != ptemp_node)
		{
			ptemp_node_retn = ptemp_node;

			if (null != ptemp_node->m_pright_node)
			{
				ptemp_node = ptemp_node->m_pright_node;
				continue;
			}
			else if (null != ptemp_node->m_pleft_node)
			{
				ptemp_node = ptemp_node->m_pleft_node;
				continue;
			}
			else
			{
				break;
			}

		}

		return ptemp_node_retn;
	}

	return null;
}

//////////////////////////////////////////////////////////////////////////

const binary_search_tree_node_t* get_binary_search_tree_preorder_begin_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	return proot_node;
}

const binary_search_tree_node_t* get_binary_search_tree_preorder_end_node (const binary_search_tree_node_t* PARAM_IN proot_node)
{
	if (null != proot_node)
	{
		const binary_search_tree_node_t* ptemp_node = null;

		while (null != proot_node)
		{
			ptemp_node = proot_node;
			if (null != proot_node->m_pright_node)
			{
				proot_node = proot_node->m_pright_node;
				continue;
			}
			else if (null != proot_node->m_pleft_node)
			{
				proot_node = proot_node->m_pleft_node;
				continue;
			}
			else
			{
				break;
			}

		}
		return ptemp_node;

	}
	else
	{
		return null;
	}

}

const pfx_preorder_iterator_t* get_binary_search_tree_preorder_begin_iterator (const binary_search_tree_node_t* PARAM_IN proot_node,pfx_preorder_iterator_t* PARAM_INOUT piterator)
{
	RETURN_INVALID_RESULT((null == piterator),null);
	piterator->m_pcurrent_node = get_binary_search_tree_preorder_begin_node (proot_node);
	piterator->m_last_result = PFX_STATUS_OK;
	if (null != piterator->m_pcurrent_node)
	{
		if (null != piterator->m_pcurrent_node->m_pleft_node)
		{
			piterator->m_next_node_type = PREORDER_NEXT_LEFT;
		}
		else if (null != piterator->m_pcurrent_node->m_pright_node)
		{
			piterator->m_next_node_type = PREORDER_NEXT_RIGHT;
		}
		else
		{
			piterator->m_next_node_type = PREORDER_FIN;
		}
	}
	return piterator;
}

const pfx_preorder_iterator_t* get_binary_search_tree_preorder_end_iterator(const binary_search_tree_node_t* PARAM_IN proot_node,pfx_preorder_iterator_t* PARAM_INOUT piterator)
{
	RETURN_INVALID_RESULT ((null == piterator),null);
	piterator->m_pcurrent_node = get_binary_search_tree_preorder_end_node (proot_node);
	piterator->m_next_node_type = PREORDER_NEXT_END;

	return piterator;
}

const pfx_preorder_iterator_t* binary_search_tree_preorder_increase (pfx_preorder_iterator_t* PARAM_INOUT piterator,const binary_search_tree_node_t* PARAM_IN proot_node)
{
	pfx_enum_t back_up_next_type;
	pfx_enum_t next_type;
	const binary_search_tree_node_t* pnext_node;
	pfx_result_t	status = PFX_STATUS_OK;

	RETURN_INVALID_RESULT ((null == piterator || null == proot_node || 
		null == piterator->m_pcurrent_node || enum_preorder_iterator_next_node_type_COUNT <= piterator->m_next_node_type||
		PFX_STATUS_OK != piterator->m_last_result), null);

	back_up_next_type = piterator->m_next_node_type;

	switch (back_up_next_type)
	{
	case PREORDER_NEXT_SUB_ROOT_RIGHT:
		{
			const binary_search_tree_node_t* pcur_node =  piterator->m_pcurrent_node;
			do 
			{
				pnext_node = pcur_node->m_parent_node;
				if (pcur_node == proot_node)
				{
					status = PFX_STATUS_OK;
					next_type = PREORDER_FIN;
					break;
				}
				else if (null == pnext_node)
				{
					status = PFX_STATUS_OK;
					next_type = PREORDER_FIN;
					break;
				}
				else if (pnext_node->m_pright_node == pcur_node)
				{
					pcur_node = pnext_node;
					continue;
				}
				else if (pnext_node->m_pleft_node == pcur_node)
				{
					if (null == pnext_node->m_pright_node)
					{
						pcur_node = pnext_node;
						continue;
					}
					pnext_node = pnext_node->m_pright_node;
					status = PFX_STATUS_OK;

					if (null != pnext_node->m_pleft_node)
					{
						next_type = PREORDER_NEXT_LEFT;
						break;
					}
					else if (null != pnext_node->m_pright_node)
					{
						next_type = PREORDER_NEXT_RIGHT;
						break;
					}
					else
					{
						next_type = PREORDER_NEXT_SUB_ROOT_RIGHT;
						break;
					}

				}
				else
				{
					status = PFX_STATUS_MEM_ERR;
					next_type = PREORDER_FIN;
					pnext_node = null;
				}
			} while (1);
			piterator->m_pcurrent_node = pnext_node;
			piterator->m_next_node_type = next_type;
			piterator->m_last_result = status;
		}
		break;
	case PREORDER_NEXT_LEFT:
		{
			pnext_node = piterator->m_pcurrent_node->m_pleft_node;
			if (null == pnext_node)
			{
				status = PFX_STATUS_MEM_ERR;
				next_type = PREORDER_FIN;
			}
			else if (null != pnext_node->m_pleft_node)
			{
				next_type = PREORDER_NEXT_LEFT;
			}
			else if (null != pnext_node->m_pright_node)
			{
				next_type = PREORDER_NEXT_RIGHT;
			}
			else
			{
				next_type = PREORDER_NEXT_SUB_ROOT_RIGHT;
			}
			piterator->m_pcurrent_node = pnext_node;
			piterator->m_next_node_type = next_type;
			piterator->m_last_result = status;
		}
		break;
	case PREORDER_NEXT_RIGHT:
		{
			pnext_node = piterator->m_pcurrent_node->m_pright_node;
			if (null == pnext_node)
			{
				status = PFX_STATUS_MEM_ERR;
				next_type = PREORDER_FIN;
			}
			else if (null != pnext_node->m_pleft_node)
			{
				next_type = PREORDER_NEXT_LEFT;
			}
			else if (null != pnext_node->m_pright_node)
			{
				next_type = PREORDER_NEXT_RIGHT;
			}
			else
			{
				next_type = PREORDER_NEXT_SUB_ROOT_RIGHT;
			}
			piterator->m_pcurrent_node = pnext_node;
			piterator->m_next_node_type = next_type;
			piterator->m_last_result = PFX_STATUS_OK;
		}
		break;
	case PREORDER_NEXT_BEGIN:
		{
			 get_binary_search_tree_preorder_begin_iterator (proot_node,piterator);
		}
		break;
	case PREORDER_NEXT_END:
		{
			piterator->m_pcurrent_node = null;
			piterator->m_next_node_type = PREORDER_FIN;
			piterator->m_last_result = PFX_STATUS_OK;
		}
		break;
	default:
		{
			piterator->m_pcurrent_node = null;
			piterator->m_next_node_type = PREORDER_FIN;
			piterator->m_last_result = PFX_STATUS_INVALID_OPERATION;
		}
		break;
	}

	return piterator;
}

