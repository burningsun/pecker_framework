/*
 * cbst.h
 *
 *  Created on: 2013-12-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBST_CODES_H_
#define		PFX_CBST_CODES_H_


#include "pfx_cbst.h"
PECKER_BEGIN

#define TEMPLATE_CBST cbst PFX_CBST_TEMPLATE_PARAMS
#define TYPE_CBST typename cbst PFX_CBST_TEMPLATE_PARAMS

#define TEMPLATE_CAVL_BST cavl_tree PFX_CBST_TEMPLATE_PARAMS
#define TYPE_CAVL_BST typename cavl_tree PFX_CBST_TEMPLATE_PARAMS

#define TEMPLATE_CRB_BST crb_tree PFX_CBST_TEMPLATE_PARAMS
#define TYPE_CRB_BST typename crb_tree PFX_CBST_TEMPLATE_PARAMS

PFX_CBST_TEMPLATE_DEFINES
TEMPLATE_CBST ::cbst(/*Iallocator_cpp* allocator = null*/):
	m_root_ptr (null)
{

}

PFX_CBST_TEMPLATE_DEFINES
TEMPLATE_CBST ::cbst(const TYPE_CBST* other_ptr) throw (result_t) : m_root_ptr (null)
{
	if (this != other_ptr)
	{
		result_t status_ = copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}

PFX_CBST_TEMPLATE_DEFINES
TEMPLATE_CBST ::~cbst()
{
	clear ();
}

PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CBST ::copy (const TYPE_CBST * PARAM_IN other_bst_ptr)
{
	RETURN_RESULT (other_bst_ptr == this,PFX_STATUS_OK);
	result_t status_ = clear();
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,PFX_STATUS_ERROR_);
	RETURN_RESULT (null == other_bst_ptr->m_root_ptr,PFX_STATUS_OK);

	node_type_* temp_dec_node_ptr;
	node_type_* temp_src_node_ptr;
	node_type_* new_node_ptr = new_node ();

	RETURN_INVALID_RESULT (null == new_node_ptr,PFX_STATUS_MEM_LOW);

	*new_node_ptr = *other_bst_ptr->m_root_ptr;


	TEMPLATE_CBST ::init_node_leaves (new_node_ptr);
	m_root_ptr = new_node_ptr;

	temp_dec_node_ptr = new_node_ptr;
	temp_src_node_ptr = other_bst_ptr->m_root_ptr;

	do
	{
		if (null == temp_dec_node_ptr->get_left_node())
		{
			if (null != temp_src_node_ptr->get_left_node())
			{
				new_node_ptr = new_node ();
				*new_node_ptr = *(temp_src_node_ptr->get_left_node());

				TEMPLATE_CBST ::init_node_leaves (new_node_ptr,null,null,temp_dec_node_ptr);

				temp_dec_node_ptr->set_left_node (new_node_ptr);
				temp_dec_node_ptr = new_node_ptr;

				temp_src_node_ptr = temp_src_node_ptr->get_left_node_ref ();
				continue;
			}
		}

		if (null == temp_dec_node_ptr->get_right_node())
		{
			if (null != temp_src_node_ptr->get_right_node())
			{
				new_node_ptr = new_node ();
				*new_node_ptr = *(temp_src_node_ptr->get_right_node());

				TEMPLATE_CBST ::init_node_leaves (new_node_ptr,null,null,temp_dec_node_ptr);

				temp_dec_node_ptr->set_right_node (new_node_ptr);
				temp_dec_node_ptr = new_node_ptr;

				temp_src_node_ptr = temp_src_node_ptr->get_right_node_ref ();
				continue;
			}
		}

		temp_dec_node_ptr = temp_dec_node_ptr->get_parent_node_ref ();
		temp_src_node_ptr = temp_src_node_ptr->get_parent_node_ref ();
	}while(temp_dec_node_ptr);

	return PFX_STATUS_OK;
}

PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CBST ::copy_by_iterator (const TYPE_CBST * PARAM_IN other_bst_ptr)
{
	RETURN_RESULT (other_bst_ptr == this,PFX_STATUS_OK);
	result_t status_ = clear();
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,PFX_STATUS_ERROR_);

	const node_type_* pbegin;
	const node_type_* pend;
	result_t status = PFX_STATUS_OK;

	RETURN_RESULT (null == m_root_ptr,status);

	bst_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS iterator_begin;
	bst_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS iterator_end;

	cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*  iterator_begin_ptr = begin (&iterator_begin);
	cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*  iterator_end_ptr = end (&iterator_end);

	const node_type_* cur_node_ptr;
	cur_node_ptr = iterator_begin_ptr->get_current_node();
	const node_type_* add_node_ptr = null;
	do 
	{
		node_type_* copy_node_ptr = (node_type_*) cur_node_ptr;

		BREAK_LOOP_CONDITION (null == copy_node_ptr);

		if (cur_node_ptr && cur_node_ptr == iterator_end_ptr->get_current_node ())
		{
			node_type_* new_node_ptr = new_node ();
			BREAK_LOOP_CONDITION_SETS (null == new_node_ptr, status_, PFX_STATUS_MEM_LOW);

			*new_node_ptr = *(cur_node_ptr);

			add_node_ptr = add (new_node_ptr,status_);

			if (null == add_node_ptr)
			{
				release_node (new_node_ptr);
			}

			BREAK_LOOP (status_,PFX_STATUS_OK);
		}

		iterator_begin_ptr = iterator_begin_ptr->increase();
		cur_node_ptr = (node_type_*) iterator_begin_ptr->get_current_node();

		if (cur_node_ptr)
		{
			if (cur_node_ptr == iterator_end_ptr->get_current_node ())
			{
				node_type_* new_node_ptr = new_node ();
				BREAK_LOOP_CONDITION_SETS (null == new_node_ptr, status_, PFX_STATUS_MEM_LOW);

				*new_node_ptr = *(cur_node_ptr);
				add_node_ptr = add (new_node_ptr,status_);

				if (null == add_node_ptr)
				{
					release_node (new_node_ptr);
				}

				BREAK_LOOP (status_,PFX_STATUS_OK);
			}
			else
			{
				node_type_* new_node_ptr = new_node ();
				BREAK_LOOP_CONDITION_SETS (null == new_node_ptr, status_, PFX_STATUS_MEM_LOW);

				*new_node_ptr = *(cur_node_ptr);
				add_node_ptr = add (new_node_ptr,status_);

				if (null == add_node_ptr)
				{
					release_node (new_node_ptr);
				}
				continue;
			}
		}

	} while (1);

	return status;
}

PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CBST ::clear ()
{
	result_t status = PFX_STATUS_OK;

	RETURN_RESULT (null == m_root_ptr,status);

	bst_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS iterator_begin;
	bst_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS iterator_end;

	cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*  iterator_begin_ptr =  begin (&iterator_begin);
	cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*  iterator_end_ptr =  end (&iterator_end);
	
	const node_type_* cur_node_ptr;
	cur_node_ptr = iterator_begin_ptr->get_current_node();

	do 
	{
		node_type_* del_node_ptr = (node_type_*) cur_node_ptr;
		
		if (null == del_node_ptr)
		{
			break;
		}

		if (cur_node_ptr == iterator_end_ptr->get_current_node ())
		{
			status = release_node (del_node_ptr);
			break;
		}
			
		iterator_begin_ptr = iterator_begin_ptr->increase();
		cur_node_ptr = (node_type_*) iterator_begin_ptr->get_current_node();

		if (cur_node_ptr)
		{
			if (m_root_ptr == del_node_ptr)
			{
				m_root_ptr = null;
			}
			if (null == del_node_ptr->get_parent_node())
			{
				status = release_node (del_node_ptr);
				break;
			}

			status = release_node (del_node_ptr);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
		}
	} while (1);
	m_root_ptr = null;

	return status;
}

PFX_CBST_TEMPLATE_DEFINES
cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* TEMPLATE_CBST ::begin (cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_OUT iterator_) const
{
	if (iterator_)
	{
		result_t status_ = iterator_->init (m_root_ptr,m_root_ptr);
		if (PFX_STATUS_OK == status_)
		{
			iterator_ = iterator_->begin ();
		}
		else
		{
			iterator_ = null;
		}
	}
	return iterator_;
}

PFX_CBST_TEMPLATE_DEFINES
cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * TEMPLATE_CBST ::end (cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * PARAM_OUT iterator_) const
{
	if (iterator_)
	{
		result_t status_ = iterator_->init (m_root_ptr,m_root_ptr);
		if (PFX_STATUS_OK == status_)
		{
			iterator_ = iterator_->end ();
		}
		else
		{
			iterator_ = null;
		}
	}
	return iterator_;
}

//public:
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* TEMPLATE_CBST ::find (cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_OUT iterator_,
		const node_type_* PARAM_IN key_node_ptr) const
{
	if (iterator_)
	{
		const node_type_* find_node_ptr = find (key_node_ptr);
		if (find_node_ptr)
		{
			result_t status_ = iterator_->init(find_node_ptr,m_root_ptr);
			if (PFX_STATUS_OK != status_)
			{
				iterator_ = null;
			}
		}
		else
		{
			iterator_ = null;
		}
	}
	return iterator_;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE const node_type_* TEMPLATE_CBST ::find_by_item (const typename bst_node_member_reference_type< node_type_ >::item_type_t* PARAM_IN key_ptr) const
{
	return TYPE_CBST::find_node_by_item (key_ptr, m_root_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* find_reference_by_item (const typename bst_node_member_reference_type< node_type_ >::item_type_t* PARAM_IN key_ptr)
{
	return  (node_type_*)TYPE_CBST::find_node_by_item (key_ptr, m_root_ptr);
}
//
//public:
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE const node_type_* TEMPLATE_CBST ::find (const node_type_* PARAM_IN key_node_ptr) const
{
	return TEMPLATE_CBST ::find_node (key_node_ptr, m_root_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* TEMPLATE_CBST ::find_reference (const node_type_* PARAM_IN key_node_ptr)
{
	return (node_type_*)TEMPLATE_CBST ::find_node (key_node_ptr,m_root_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CBST ::add (node_type_* PARAM_INOUT add_node_ptr,
	result_t& PARAM_OUT status_)
{
	node_type_* added_node_ptr = null;
	status_ = TEMPLATE_CBST ::add_node (m_root_ptr,add_node_ptr,added_node_ptr);
	return added_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* TEMPLATE_CBST ::remove (node_type_* PARAM_INOUT remove_node_ptr,
		result_t& PARAM_OUT status_)
{
	status_ = TEMPLATE_CBST ::remove_node (m_root_ptr,remove_node_ptr);
	if (PFX_STATUS_OK != status_)
	{
		remove_node_ptr = null;
	}
	return remove_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_*  TEMPLATE_CBST ::get_root () const
{
	return m_root_ptr;
}
//public:
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE const node_type_* TEMPLATE_CBST ::max_node (const node_type_* root_node_ptr, 
																																const node_type_* null_node_ptr /*= null*/)
{
	if (root_node_ptr)
	{
		const node_type_* right_node_ptr = root_node_ptr->get_right_node();
		if (null_node_ptr)
		{
			while (right_node_ptr && null_node_ptr != right_node_ptr)
			{
				root_node_ptr = right_node_ptr;
				right_node_ptr = root_node_ptr->get_right_node();
			}
		}
		else
		{
			while (right_node_ptr)
			{
				root_node_ptr = right_node_ptr;
				right_node_ptr = root_node_ptr->get_right_node();
			}
		}
	}
	return root_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE const node_type_* TEMPLATE_CBST ::min_node (const node_type_* root_node_ptr, 
																																	const node_type_* null_node_ptr /*= null*/)
{
	if (root_node_ptr)
	{
		const node_type_* left_node_ptr = root_node_ptr->get_left_node();
		if (null_node_ptr)
		{
			while (left_node_ptr && null_node_ptr != left_node_ptr)
			{
				root_node_ptr = left_node_ptr;
				left_node_ptr = root_node_ptr->get_left_node();
			}
		}
		else
		{
			while (left_node_ptr)
			{
				root_node_ptr = left_node_ptr;
				left_node_ptr = root_node_ptr->get_left_node();
			}
		}
	}
	return root_node_ptr;
}
//
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE result_t TEMPLATE_CBST ::init_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
	node_type_* PARAM_IN left_node_ptr /*= null*/,
	node_type_* PARAM_IN right_node_ptr /*= null*/,
	node_type_* PARAM_IN parent_node_ptr /*= null*/)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_left_node ((node_type_*)left_node_ptr);
		tree_node_ptr->set_right_node ((node_type_*)right_node_ptr);
		tree_node_ptr->set_parent_node ((node_type_*)parent_node_ptr);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}
//
PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CBST ::find_node (const node_type_* PARAM_IN key_node_ptr,
		const node_type_* PARAM_IN root_node_ptr)
{
	const node_type_* traval_node_ptr = root_node_ptr;
	while (traval_node_ptr)
	{
		int cmp_result = compare_two_node_ :: compare (key_node_ptr, traval_node_ptr);
		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node ();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node ();
		}
		else
		{
			break;
		}
	}
	return traval_node_ptr;
}
//
PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CBST ::find_near_node  (const node_type_* PARAM_IN key_node_ptr,
	const node_type_* PARAM_IN root_node_ptr,
	int& PARAM_INOUT last_cmp_result)
{
	const node_type_* near_node_ptr = null;
	const node_type_* traval_node_ptr = root_node_ptr;

	int cmp_result = 0;
	while (traval_node_ptr)
	{
		cmp_result = compare_two_node_ :: compare (key_node_ptr,traval_node_ptr);
		near_node_ptr = traval_node_ptr;

		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node ();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node ();
		}
		else
		{
			break;
		}
	}
	last_cmp_result = cmp_result;
	return near_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CBST ::find_node_by_item (const typename bst_node_member_reference_type< node_type_ >::item_type_t* PARAM_IN key_ptr,
	const node_type_* PARAM_IN root_node_ptr)
{
	const node_type_* traval_node_ptr = root_node_ptr;
	while (traval_node_ptr)
	{
		int cmp_result = traval_node_ptr->compare (key_ptr);
		if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node ();
		}
		else if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node ();
		}
		else
		{
			break;
		}
	}
	return traval_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CBST ::find_near_node_by_item  (const typename bst_node_member_reference_type< node_type_ >::item_type_t* PARAM_IN key_ptr,
	const node_type_* PARAM_IN root_node_ptr,
	int& PARAM_INOUT last_cmp_result)
{
	const node_type_* near_node_ptr = null;
	const node_type_* traval_node_ptr = root_node_ptr;

	int cmp_result = 0;
	while (traval_node_ptr)
	{
		cmp_result = traval_node_ptr->compare (key_node_ptr);
		near_node_ptr = traval_node_ptr;

		if (cmp_result < 0)
		{
			traval_node_ptr = traval_node_ptr->get_left_node ();
		}
		else if (cmp_result > 0)
		{
			traval_node_ptr = traval_node_ptr->get_right_node ();
		}
		else
		{
			break;
		}
	}
	last_cmp_result = cmp_result;
	return near_node_ptr;
}

//
PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CBST ::add_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT add_node_ptr,
		node_type_*& PARAM_OUT added_node_ptr)
{
	result_t	status;
	int					cmp_result;
	node_type_*	tmp_root_node_ptr;
	node_type_*	node_to_be_add_ptr;
	node_type_*	parent_node_ptr;

	tmp_root_node_ptr = root_node_ptr;

	// 添加第一个节点
	if (null == tmp_root_node_ptr)
	{
		root_node_ptr = add_node_ptr;
		TEMPLATE_CBST ::init_node_leaves (add_node_ptr);
		added_node_ptr = add_node_ptr;
		return PFX_STATUS_OK;
	}

	FOR_ONE_LOOP_BEGIN
	
	node_to_be_add_ptr	=	(node_type_*) find_near_node(add_node_ptr,tmp_root_node_ptr,cmp_result); 

	// 已经存在一个同样key的节点, added_node_ptr返回的是已有节点的指针
	if (null != node_to_be_add_ptr && 0 == cmp_result)
	{
		added_node_ptr = node_to_be_add_ptr;
		status = PFX_STATUS_UNIQUE;
		break;
	}

	parent_node_ptr = node_to_be_add_ptr->get_parent_node_ref () ;

	if (0 > cmp_result)
	{
		if (null == node_to_be_add_ptr->get_left_node())
		{
			node_to_be_add_ptr->set_left_node (add_node_ptr);
			TEMPLATE_CBST ::init_node_leaves (add_node_ptr,null,null,node_to_be_add_ptr);
		}
		else
		{
			 // 内存数据被损坏
			status = PFX_STATUS_MEM_ERR;
			break;
		}
	}
	else
	{
		if (null == node_to_be_add_ptr->get_right_node())
		{
			TEMPLATE_CBST ::init_node_leaves (add_node_ptr,null,null,node_to_be_add_ptr);
			node_to_be_add_ptr->set_right_node ((node_type_*)add_node_ptr);
		}
		else
		{
			// 内存数据被损坏
			status = PFX_STATUS_MEM_ERR;
			break;
		}
	}

	added_node_ptr = add_node_ptr;
	FOR_ONE_LOOP_END

	status = PFX_STATUS_OK;
	return status;
}
//
PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CBST ::remove_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		const node_type_* PARAM_IN null_node_ptr /*= null*/)
{
	RETURN_INVALID_RESULT (null == remove_node_ptr,PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (null == root_node_ptr,PFX_STATUS_OK);

	node_type_* sub_romove_ref_node_ptr;
	node_type_* sub_remove_node_ptr;
	result_t status_ = PFX_STATUS_OK;

	sub_romove_ref_node_ptr = TEMPLATE_CBST ::find_remove_replace_node 
		(remove_node_ptr,sub_remove_node_ptr,null_node_ptr);

	//remove_node_ptr = 
	status_ =	 TEMPLATE_CBST ::remove_node_internal (root_node_ptr,remove_node_ptr,sub_remove_node_ptr,
		sub_romove_ref_node_ptr,null_node_ptr);

	//if (remove_node_ptr)
	//{
	//	status_ = PFX_STATUS_FAIL;
	//}

	return status_;
}
//
//protected:
PFX_CBST_TEMPLATE_DEFINES
node_type_* TEMPLATE_CBST ::find_remove_replace_node (node_type_* PARAM_IN remove_node_ptr,
	node_type_*& PARAM_OUT sub_remove_node_ptr,
	const node_type_* PARAM_IN null_node_ptr /*= null*/)
{
	const node_type_* sub_remove_ref_node_ptr = null;
	const node_type_* tmp_sub_remove_node_ptr = null;

	if (null_node_ptr == remove_node_ptr->get_left_node ())
	{
		sub_remove_ref_node_ptr = remove_node_ptr->get_right_node ();
		tmp_sub_remove_node_ptr = remove_node_ptr;
	}
	else if (null_node_ptr == remove_node_ptr->get_right_node ())
	{
		sub_remove_ref_node_ptr = remove_node_ptr->get_left_node ();
		tmp_sub_remove_node_ptr = remove_node_ptr;
	}
	else
	{
		tmp_sub_remove_node_ptr = TEMPLATE_CBST ::min_node (remove_node_ptr->get_right_node(),null_node_ptr);
		if (tmp_sub_remove_node_ptr->get_left_node () != null_node_ptr)
		{
			sub_remove_ref_node_ptr = tmp_sub_remove_node_ptr->get_left_node ();
		}
		else 
		{
			sub_remove_ref_node_ptr = tmp_sub_remove_node_ptr->get_right_node ();
		}
	}

	sub_remove_node_ptr = (node_type_*)tmp_sub_remove_node_ptr;
	return  (node_type_*)sub_remove_ref_node_ptr;
}
//
PFX_CBST_TEMPLATE_DEFINES
//node_type_* 
result_t TEMPLATE_CBST ::remove_node_internal (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		node_type_* PARAM_INOUT sub_remove_node_ptr,
		node_type_* PARAM_INOUT sub_remove_node_ref_ptr,
		const node_type_* PARAM_IN null_node_ptr /*= null*/)
{
	node_type_* tmp_root_node_ptr = root_node_ptr;
	node_type_* parant_node_ptr = null;
	result_t status_ = PFX_STATUS_OK;

	FOR_ONE_LOOP_BEGIN
	// 处理替换节点
	if (sub_remove_node_ptr == tmp_root_node_ptr) 
	{                             
		parant_node_ptr = tmp_root_node_ptr->get_parent_node_ref ();
		if (null != parant_node_ptr)
		{
			if (parant_node_ptr->get_left_node() == tmp_root_node_ptr)
			{
				parant_node_ptr->set_left_node (sub_remove_node_ref_ptr);
			}
			else if (parant_node_ptr->get_right_node() == tmp_root_node_ptr)
			{
				parant_node_ptr->set_right_node (sub_remove_node_ref_ptr);
			}
			else
			{
				BREAK_LOOP (status_, PFX_STATUS_MEM_ERR);
			}
		}
		if (sub_remove_node_ref_ptr)
		{
			sub_remove_node_ref_ptr->set_parent_node (parant_node_ptr);
		}

		root_node_ptr = sub_remove_node_ref_ptr;
		TEMPLATE_CBST ::init_node_leaves (remove_node_ptr);
		BREAK_LOOP (status_,PFX_STATUS_OK);
	}

	parant_node_ptr =  sub_remove_node_ptr->get_parent_node_ref ();
	if (sub_remove_node_ptr == parant_node_ptr->get_left_node ())
	{
		parant_node_ptr->set_left_node (sub_remove_node_ref_ptr);
	}
	else
	{
		parant_node_ptr->set_right_node (sub_remove_node_ref_ptr);
	}

	if (sub_remove_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			sub_remove_node_ref_ptr->set_parent_node (parant_node_ptr);
		}

		TEMPLATE_CBST ::init_node_leaves (remove_node_ptr);
		BREAK_LOOP (status_,PFX_STATUS_OK);
	}

	if (parant_node_ptr == remove_node_ptr)
	{
		if (sub_remove_node_ref_ptr)
		{
			sub_remove_node_ref_ptr->set_parent_node (sub_remove_node_ptr);
		}
	}
	else
	{
		if (sub_remove_node_ref_ptr)
		{
			sub_remove_node_ref_ptr->set_parent_node (parant_node_ptr);
		}
	}


	// 将remove node相关的指针复制
	sub_remove_node_ptr->set_left_node		 (remove_node_ptr->get_left_node_ref ());
	sub_remove_node_ptr->set_right_node	 (remove_node_ptr->get_right_node_ref ());
	sub_remove_node_ptr->set_parent_node (remove_node_ptr->get_parent_node_ref ());


	if (remove_node_ptr == tmp_root_node_ptr) // 移除节点是根节点
	{
		root_node_ptr = sub_remove_node_ptr;		// 将根节点替换为psub_node
	}
	else
	{
		parant_node_ptr = remove_node_ptr->get_parent_node_ref ();
		// 替换移除节点父节点的相关指针
		if (remove_node_ptr == parant_node_ptr->get_left_node())
		{
			parant_node_ptr->set_left_node (sub_remove_node_ptr);
		}
		else if (remove_node_ptr == parant_node_ptr->get_right_node())
		{
			parant_node_ptr->set_right_node (sub_remove_node_ptr);
		}
		else
		{
			BREAK_LOOP (status_,PFX_STATUS_MEM_ERR);
		}
	}

	// 更新现在新的左右节点的父节点指针
	node_type_* left_node_ptr = sub_remove_node_ptr->get_left_node_ref ();
	node_type_* right_node_ptr = sub_remove_node_ptr->get_right_node_ref ();

	if (null_node_ptr)
	{
		if (left_node_ptr != null_node_ptr && left_node_ptr)
		{
			left_node_ptr->set_parent_node (sub_remove_node_ptr);
		}

		if (right_node_ptr != null_node_ptr && right_node_ptr)
		{
			right_node_ptr->set_parent_node (sub_remove_node_ptr);
		}
	}
	else
	{
		if (left_node_ptr)
		{
			left_node_ptr->set_parent_node (sub_remove_node_ptr);
		}

		if (right_node_ptr)
		{
			right_node_ptr->set_parent_node (sub_remove_node_ptr);
		}
	}

	TEMPLATE_CBST ::init_node_leaves (remove_node_ptr);
	BREAK_LOOP (status_,PFX_STATUS_OK);

	FOR_ONE_LOOP_END
	

	return status_;
}


//////////////////////////////////////////////////////////////////////////
///


PFX_CBST_TEMPLATE_DEFINES
TEMPLATE_CAVL_BST ::cavl_tree(/*Iallocator_cpp* allocator = null*/)
{
	;
}
PFX_CBST_TEMPLATE_DEFINES
TEMPLATE_CAVL_BST ::cavl_tree (const TYPE_CBST* PARAM_IN other_) throw (result_t)
{
	if (this != other_ptr)
	{
		result_t status_ = TEMPLATE_CAVL_BST :: copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}
PFX_CBST_TEMPLATE_DEFINES
TEMPLATE_CAVL_BST ::cavl_tree (const TYPE_CAVL_BST* PARAM_IN other_) throw (result_t)
{
	if (this != other_ptr)
	{
		result_t status_ = TEMPLATE_CBST :: copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}
//public:
PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CAVL_BST ::add (node_type_* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT status_)
{
	return TEMPLATE_CAVL_BST ::add_avl_node (m_root_ptr,add_node_ptr,status_);
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* TEMPLATE_CAVL_BST ::remove (node_type_* PARAM_INOUT remove_node_ptr,
		result_t& PARAM_OUT status_)
{
	return remove_avl_node (m_root_ptr,remove_node_ptr,status_);
}

PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CAVL_BST ::copy (const TYPE_CBST * 
																													PARAM_IN other_bst_ptr)
{
	return TEMPLATE_CBST :: copy_by_iterator (other_bst_ptr);
}
PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CAVL_BST ::copy (const TYPE_CAVL_BST * 
																													PARAM_IN other_bst_ptr)
{
	return TEMPLATE_CBST :: copy (other_bst_ptr);
}
//public:
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE result_t TYPE_CAVL_BST::init_avl_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
	 node_type_* PARAM_IN left_node_ptr /*= null*/,
	 node_type_* PARAM_IN right_node_ptr /*= null*/,
	 node_type_* PARAM_IN parent_node_ptr/* = null*/)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_left_node ((node_type_*)left_node_ptr);
		tree_node_ptr->set_right_node ((node_type_*)right_node_ptr);
		tree_node_ptr->set_parent_node ((node_type_*)parent_node_ptr);
		tree_node_ptr->set_height (0);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE nsize__t TEMPLATE_CAVL_BST ::get_avl_height (const node_type_* PARAM_IN node_ptr)
{
	nsize__t height_value = -1;
	if (node_ptr)
	{
		height_value = node_ptr->get_height ();
	}
	return height_value;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE nsize__t TEMPLATE_CAVL_BST ::calculate_avl_height (const node_type_* PARAM_IN left_node_ptr,
		const node_type_* PARAM_IN right_node_ptr)
{
	nsize__t left_height = TYPE_CAVL_BST::get_avl_height (left_node_ptr);
	nsize__t right_height = TYPE_CAVL_BST::get_avl_height (right_node_ptr);
	if (left_height > right_height)
	{
		return (left_height+1);
	}
	else
	{
		return (right_height+1);
	}
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE nsize__t TEMPLATE_CAVL_BST ::calculate_avl_height (const node_type_* PARAM_IN node_ptr)
{
	nsize__t height_value = -1;
	if (node_ptr)
	{
		height_value = TEMPLATE_CAVL_BST ::calculate_avl_height 
																	(node_ptr->get_left_node(),node_ptr->get_right_node ());
	}
	return height_value;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE nsize__t TEMPLATE_CAVL_BST ::calculate_avl_balance_value 
																	(const node_type_* PARAM_IN node_ptr)
{
	nsize__t balance_value = 0;
	if (node_ptr)
	{
		balance_value = get_avl_height (node_ptr->get_left_node ()) - get_avl_height (node_ptr->get_right_node ());
	}
	return balance_value;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE void TEMPLATE_CAVL_BST ::update_avl_height (node_type_* PARAM_IN node_ptr)
{
	nsize__t height_value = calculate_avl_height (node_ptr);
	node_ptr->set_height (height_value);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* TEMPLATE_CAVL_BST ::avl_rr_rotate (node_type_* PARAM_INOUT node_ptr)
{
	node_type_* rotate_node_ptr =  node_ptr->get_right_node_ref ();

	node_ptr->set_right_node (rotate_node_ptr->get_left_node_ref ());
	rotate_node_ptr->set_left_node (node_ptr);

	node_type_* tmp_right_node_ptr =  node_ptr->get_right_node_ref ();
	if (tmp_right_node_ptr)
	{
		tmp_right_node_ptr->set_parent_node (node_ptr);
	}
	rotate_node_ptr->set_parent_node (node_ptr->get_parent_node_ref ());
	node_ptr->set_parent_node (rotate_node_ptr);

	TEMPLATE_CAVL_BST ::update_avl_height (node_ptr);
	TEMPLATE_CAVL_BST ::update_avl_height (rotate_node_ptr);

	return rotate_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* TEMPLATE_CAVL_BST ::avl_ll_rotate (node_type_* PARAM_INOUT node_ptr)
{
	node_type_* rotate_node_ptr = node_ptr->get_left_node_ref (); 

	node_ptr->set_left_node (rotate_node_ptr->get_right_node_ref ());
	rotate_node_ptr->set_right_node (node_ptr);

	node_type_* tmp_left_node_ptr = node_ptr->get_left_node_ref ();
	if (tmp_left_node_ptr)
	{
		tmp_left_node_ptr->set_parent_node (node_ptr);
	}
	rotate_node_ptr->set_parent_node (node_ptr->get_parent_node_ref ());
	node_ptr->set_parent_node (rotate_node_ptr);

	TEMPLATE_CAVL_BST ::update_avl_height (node_ptr);
	TEMPLATE_CAVL_BST ::update_avl_height (rotate_node_ptr);

	return rotate_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* TEMPLATE_CAVL_BST ::avl_lr_rotate (node_type_* PARAM_INOUT node_ptr)
{
	// LR = RR(node_ptr->letf) + LL(node_ptr)
	node_type_* tmp_node_ptr = avl_rr_rotate (node_ptr->get_left_node_ref ());
	node_ptr->set_left_node (tmp_node_ptr); 
	return avl_ll_rotate (node_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* TEMPLATE_CAVL_BST ::avl_rl_rotate (node_type_* PARAM_INOUT node_ptr)
{
	// RL = LL(node_ptr->right)) + RR(node_ptr)
	node_type_* tmp_node_ptr = avl_ll_rotate (node_ptr->get_right_node_ref ());
	node_ptr->set_right_node (tmp_node_ptr); 
	return avl_rr_rotate (node_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE AVLTREE_ROTATE_t TEMPLATE_CAVL_BST ::avl_single_rotate (nsize__t balance_value,
	node_type_* PARAM_INOUT node_ptr, node_type_* & PARAM_INOUT parent_ref_node_ptr)
{
	AVLTREE_ROTATE_t rotate_type = AVLTREE_NOT_SIMPLE_ROTATE;

	FOR_ONE_LOOP_BEGIN

	if (-2 < balance_value && balance_value < 2)
	{
		BREAK_LOOP (rotate_type,AVLTREE_NONE_ROTATE);
	}

	if (2 == balance_value)
	{
		node_type_ * left_node_ptr = node_ptr->get_left_node_ref ();

		if (null == left_node_ptr)
		{
			BREAK_LOOP (rotate_type,AVLTREE_ROTATE_ERR);
		}
		else if (TEMPLATE_CAVL_BST ::get_avl_height (left_node_ptr->get_left_node ()) >= 
			TEMPLATE_CAVL_BST ::get_avl_height (left_node_ptr->get_right_node ()))
		{
			parent_ref_node_ptr = avl_ll_rotate (node_ptr);
			BREAK_LOOP (rotate_type,AVLTREE_LL_ROTATE);
		}
		else
		{
			parent_ref_node_ptr = avl_lr_rotate (node_ptr);
			BREAK_LOOP (rotate_type,AVLTREE_LR_ROTATE);
		}
	}

	if(-2 == balance_value)
	{
		node_type_ * right_node_ptr = node_ptr->get_right_node_ref ();
		if (null == right_node_ptr)
		{
			BREAK_LOOP (rotate_type,AVLTREE_ROTATE_ERR);
		}

		if ( TEMPLATE_CAVL_BST ::get_avl_height  (right_node_ptr->get_right_node ()) 
			>= TEMPLATE_CAVL_BST ::get_avl_height  (right_node_ptr->get_left_node ()))
		{
			parent_ref_node_ptr = avl_rr_rotate (node_ptr);
			BREAK_LOOP (rotate_type,AVLTREE_RR_ROTATE);
		}
		else
		{
			parent_ref_node_ptr = avl_rl_rotate (node_ptr);
			BREAK_LOOP (rotate_type,AVLTREE_RL_ROTATE);
		}
	}

	FOR_ONE_LOOP_END
	return rotate_type;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE result_t TEMPLATE_CAVL_BST ::avl_update_insert_rotate (node_type_* & PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT begin_node_ptr)
{
	result_t				status = PFX_STATUS_OK;
	nsize__t					height;
	node_type_*				tmp_root_node_ptr;
	const node_type_*	tmp_root_parent_node_ptr;
	node_type_*				parent_node_ptr;
	AVLTREE_ROTATE_t	rotate_type;

	tmp_root_node_ptr = root_node_ptr;
	tmp_root_parent_node_ptr = root_node_ptr->get_parent_node ();

	// 当起始节点为根节点的处理流程
	if (tmp_root_node_ptr == begin_node_ptr)
	{
		TEMPLATE_CAVL_BST ::update_avl_height (begin_node_ptr);

		rotate_type = TEMPLATE_CAVL_BST ::avl_single_rotate 
			(TEMPLATE_CAVL_BST ::calculate_avl_balance_value (tmp_root_node_ptr), tmp_root_node_ptr, root_node_ptr);


		if (AVLTREE_ROTATE_ERR == rotate_type ||
			AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			status = PFX_STATUS_ERROR_;
		}
		else
		{
			status = PFX_STATUS_OK;
		}
		return status;
	}

	nsize__t balance_value;
	node_type_* parent_parent_node_ptr;

	TEMPLATE_CAVL_BST ::update_avl_height (begin_node_ptr);

	nsize__t same_count = 0;
	// 从第一个节点的跟节点开始翻转
	do 
	{
		parent_node_ptr = begin_node_ptr->get_parent_node_ref ();

		//一般情况下必须达成 null == parent_node的条件，即轮寻翻转到跟节点的时候
		//才退出翻转处理流程
		if (tmp_root_parent_node_ptr == parent_node_ptr)
		{
			BREAK_LOOP (status,PFX_STATUS_OK);
		}

		// 节点与他的父节点的指针一样，证明内存已经出错
		if (begin_node_ptr == parent_node_ptr)
		{
			BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
		}

		height = parent_node_ptr->get_height ();
		TEMPLATE_CAVL_BST ::update_avl_height (parent_node_ptr);
		balance_value = TEMPLATE_CAVL_BST ::calculate_avl_balance_value (parent_node_ptr);

		if (height == parent_node_ptr->get_height ())
		{
			BREAK_LOOP (status,PFX_STATUS_OK);
		}

		parent_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();		
		begin_node_ptr = parent_node_ptr;

		node_type_**	reference_node_ptr_ptr = null;
			// 注：这利用相关节点的关联引用进行操作，在翻转过程中快速替换被关联节点对应的节点指针
		if (parent_node_ptr == tmp_root_node_ptr || tmp_root_parent_node_ptr == parent_parent_node_ptr)
		{
			rotate_type = TEMPLATE_CAVL_BST ::avl_single_rotate 
				(balance_value, parent_node_ptr, root_node_ptr);
		}
		else
		{
			if (parent_parent_node_ptr->get_left_node () == parent_node_ptr)
			{
				reference_node_ptr_ptr = (node_type_**)(&parent_parent_node_ptr->get_left_node_ref ());
				rotate_type = TEMPLATE_CAVL_BST ::avl_single_rotate 
					(balance_value, parent_node_ptr, *reference_node_ptr_ptr);

			}
			else if (parent_parent_node_ptr->get_right_node () == parent_node_ptr)
			{
				reference_node_ptr_ptr = (node_type_**)(&parent_parent_node_ptr->get_right_node_ref ());
				rotate_type = TEMPLATE_CAVL_BST ::avl_single_rotate 
					(balance_value, parent_node_ptr, *reference_node_ptr_ptr);
			}
			else
			{
				BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
			}
		}

		if (AVLTREE_ROTATE_ERR == rotate_type ||
			AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			// 翻转出错，退出流程
			BREAK_LOOP (status,PFX_STATUS_ERROR_);
		}
		else
		{
			status = PFX_STATUS_OK;
		}



	} while (1);


	return status;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE result_t TEMPLATE_CAVL_BST ::avl_update_fixed (node_type_* & PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT begin_node_ptr)
{
	result_t				status = PFX_STATUS_OK;
	nsize__t					height;
	node_type_*				tmp_root_node_ptr;
	const node_type_*	tmp_root_parent_node_ptr;
	node_type_*				parent_node_ptr;
	AVLTREE_ROTATE_t	rotate_type;

	tmp_root_node_ptr = root_node_ptr;
	tmp_root_parent_node_ptr = root_node_ptr->get_parent_node ();

	// 当起始节点为根节点的处理流程
	if (tmp_root_node_ptr == begin_node_ptr)
	{
		TEMPLATE_CAVL_BST ::update_avl_height (begin_node_ptr);

		rotate_type = TEMPLATE_CAVL_BST ::avl_single_rotate 
			(TEMPLATE_CAVL_BST ::calculate_avl_balance_value (tmp_root_node_ptr), tmp_root_node_ptr, root_node_ptr);


		if (AVLTREE_ROTATE_ERR == rotate_type ||
			AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
		{
			status = PFX_STATUS_ERROR_;
		}
		else
		{
			status = PFX_STATUS_OK;
		}
		return status;
	}

	nsize__t balance_value;
	node_type_* parent_parent_node_ptr;

	balance_value = TEMPLATE_CAVL_BST ::calculate_avl_balance_value (begin_node_ptr);

	FOR_ONE_LOOP_BEGIN

		if (2 == balance_value)
		{
			begin_node_ptr = begin_node_ptr->get_left_node_ref ();
		}
		else if (-2 == balance_value)
		{
			begin_node_ptr = begin_node_ptr->get_right_node_ref ();
		}

		TEMPLATE_CAVL_BST ::update_avl_height (begin_node_ptr);

		nsize__t same_count = 0;
		// 从第一个节点的跟节点开始翻转
		do 
		{
			parent_node_ptr = begin_node_ptr->get_parent_node_ref ();

			//一般情况下必须达成 null == parent_node的条件，即轮寻翻转到跟节点的时候
			//才退出翻转处理流程
			if (tmp_root_parent_node_ptr == parent_node_ptr)
			{
				BREAK_LOOP (status,PFX_STATUS_OK);
			}

			// 节点与他的父节点的指针一样，证明内存已经出错
			if (begin_node_ptr == parent_node_ptr)
			{
				BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
			}

			height = parent_node_ptr->get_height ();
			TEMPLATE_CAVL_BST ::update_avl_height (parent_node_ptr);
			balance_value = TEMPLATE_CAVL_BST ::calculate_avl_balance_value (parent_node_ptr);

			// 高度一样，平衡，连续出现2次，则退出
			if (height == parent_node_ptr->get_height () && balance_value > -2 && balance_value <2)
			{
				++same_count; 
				if (same_count > 1)
				{
					BREAK_LOOP (status,PFX_STATUS_OK);
				}
			}
			else
			{
				same_count = 0;
			}

			parent_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();		
			begin_node_ptr = parent_node_ptr;

			node_type_**	reference_node_ptr_ptr = null;
			// 注：这利用相关节点的关联引用进行操作，在翻转过程中快速替换被关联节点对应的节点指针
			if (parent_node_ptr == tmp_root_node_ptr || tmp_root_parent_node_ptr == parent_parent_node_ptr)
			{
				rotate_type = TEMPLATE_CAVL_BST ::avl_single_rotate 
					(balance_value, parent_node_ptr, root_node_ptr);
			}
			else
			{
				if (parent_parent_node_ptr->get_left_node () == parent_node_ptr)
				{
					reference_node_ptr_ptr = (node_type_**)(&parent_parent_node_ptr->get_left_node_ref ());
					rotate_type = TEMPLATE_CAVL_BST ::avl_single_rotate 
						(balance_value, parent_node_ptr, *reference_node_ptr_ptr);

				}
				else if (parent_parent_node_ptr->get_right_node () == parent_node_ptr)
				{
					reference_node_ptr_ptr = (node_type_**)(&parent_parent_node_ptr->get_right_node_ref ());
					rotate_type = TEMPLATE_CAVL_BST ::avl_single_rotate 
						(balance_value, parent_node_ptr, *reference_node_ptr_ptr);
				}
				else
				{
					BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
				}
			}

			if (AVLTREE_ROTATE_ERR == rotate_type ||
				AVLTREE_NOT_SIMPLE_ROTATE == rotate_type)
			{
				// 翻转出错，退出流程
				BREAK_LOOP (status,PFX_STATUS_ERROR_);
			}
			else
			{
				status = PFX_STATUS_OK;
			}



		} while (1);

		FOR_ONE_LOOP_END

			return status;
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CAVL_BST ::add_avl_node (node_type_*& PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT add_node_ptr,
	result_t& PARAM_OUT status_)
{
	result_t	status;
	node_type_*	temp_node_ptr = null;

	RETURN_INVALID_BY_ACT_RESULT ((null == add_node_ptr),
		status_ = PFX_STATUS_INVALID_PARAMS,null);

	status = TEMPLATE_CBST ::add_node (root_node_ptr,
		add_node_ptr,temp_node_ptr);

	RETURN_INVALID_BY_ACT_RESULT ((PFX_STATUS_OK != status),
		status_ = status,temp_node_ptr);

	TEMPLATE_CAVL_BST :: update_avl_height (add_node_ptr);

	status = TEMPLATE_CAVL_BST :: avl_update_insert_rotate (root_node_ptr,add_node_ptr);

	status_ = status;
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return add_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* TEMPLATE_CAVL_BST ::remove_avl_node (node_type_*& PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT remove_node_ptr,
	result_t& PARAM_OUT status_)
{
	result_t			status;
	node_type_*	temp_node_ptr = null;
	node_type_*	parent_node_ptr;
	node_type_* sub_romove_ref_node_ptr;
	node_type_* sub_remove_node_ptr;

	RETURN_INVALID_BY_ACT_RESULT ((null == remove_node_ptr),
		status_ = PFX_STATUS_INVALID_PARAMS,null);

	sub_romove_ref_node_ptr = 
		TEMPLATE_CBST :: find_remove_replace_node
		(remove_node_ptr,sub_remove_node_ptr,null);

	if (sub_remove_node_ptr)
	{
		parent_node_ptr = sub_remove_node_ptr->get_parent_node_ref();
	}
	
	status = TEMPLATE_CBST :: remove_node_internal
		(root_node_ptr,remove_node_ptr,sub_remove_node_ptr,sub_romove_ref_node_ptr,null);

	status_ = status;

	if (PFX_STATUS_OK != status)
	{
		return remove_node_ptr;
	}
	if (sub_remove_node_ptr)
	{
		sub_remove_node_ptr->set_height (remove_node_ptr->get_height ());
	}

	RETURN_RESULT ((null == root_node_ptr),remove_node_ptr);

	temp_node_ptr = sub_romove_ref_node_ptr;
	if (null == temp_node_ptr)
	{
		if (null != sub_remove_node_ptr)
		{
			if (remove_node_ptr != parent_node_ptr)
			{
				temp_node_ptr = parent_node_ptr;
			}
			else
			{
				temp_node_ptr = sub_remove_node_ptr;
			}
		}

		if (null == temp_node_ptr)
		{
			temp_node_ptr = root_node_ptr;
		}
	}
	status = TEMPLATE_CAVL_BST :: avl_update_fixed (root_node_ptr,temp_node_ptr);

	status_ = status;
	if (PFX_STATUS_OK != status)
	{
		return null;
	}

	return remove_node_ptr;
}


//template < class node_type_, typename compare_two_node_ >
//class crb_tree : public virtual cbst
//{
//public:
PFX_CBST_TEMPLATE_DEFINES
TEMPLATE_CRB_BST ::crb_tree (/*Iallocator_cpp* allocator = null*/)
{
	;
}

PFX_CBST_TEMPLATE_DEFINES
	TEMPLATE_CRB_BST :: crb_tree (const TYPE_CBST * PARAM_IN other_ptr) throw (result_t)
{
	if (this != other_ptr)
	{
		result_t status_ = TEMPLATE_CRB_BST :: copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}

PFX_CBST_TEMPLATE_DEFINES
TEMPLATE_CRB_BST :: crb_tree (const TYPE_CRB_BST* PARAM_IN other_ptr) throw (result_t)
{
	if (this != other_ptr)
	{
		result_t status_ = TEMPLATE_CBST :: copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}
//public:
PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CRB_BST :: copy (const TYPE_CBST * PARAM_IN other_bst_ptr)
{
	return TEMPLATE_CBST :: copy_by_iterator (other_bst_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
result_t TEMPLATE_CRB_BST ::  copy (const TYPE_CRB_BST * PARAM_IN other_bst_ptr)
{
	return TEMPLATE_CBST :: copy (other_bst_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CRB_BST ::add (node_type_* PARAM_INOUT add_node_ptr,
	result_t& PARAM_OUT status_)
{
	return TEMPLATE_CRB_BST ::add_rb_node (m_root_ptr,add_node_ptr,status_);
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* TEMPLATE_CRB_BST ::remove (node_type_* PARAM_INOUT remove_node_ptr,
		result_t& PARAM_OUT status_)
{
	return TEMPLATE_CRB_BST :: remove_rb_node (m_root_ptr,remove_node_ptr,status_);
}
//public:
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE result_t TEMPLATE_CRB_BST ::init_rb_node_leaves 
	(node_type_* PARAM_INOUT tree_node_ptr,
	node_type_* PARAM_IN left_node_ptr /*= null*/,
	node_type_* PARAM_IN right_node_ptr /*= null*/,
	node_type_* PARAM_IN parent_node_ptr /*= null*/)
{
	result_t status_ = PFX_STATUS_INVALID_PARAMS;
	if (tree_node_ptr)
	{
		tree_node_ptr->set_left_node ((node_type_*)left_node_ptr);
		tree_node_ptr->set_right_node ((node_type_*)right_node_ptr);
		tree_node_ptr->set_parent_node ((node_type_*)parent_node_ptr);
		tree_node_ptr->set_color (BLACK_COLOR_NODE_TYPE);
		status_ = PFX_STATUS_OK;
	}
	return status_;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE	void  TEMPLATE_CRB_BST ::set_rbt_color_red (node_type_* PARAM_INOUT node_ptr)
{
	node_ptr->set_color (RED_COLOR_NODE_TYPE);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE	void  TEMPLATE_CRB_BST ::set_rbt_color_black (node_type_* PARAM_INOUT node_ptr)
{
	node_ptr->set_color (BLACK_COLOR_NODE_TYPE);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE	bool  TEMPLATE_CRB_BST ::is_rbt_color_red (node_type_* PARAM_INOUT node_ptr)
{
	return (node_ptr && RED_COLOR_NODE_TYPE == node_ptr->get_color ());
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE	bool  TEMPLATE_CRB_BST ::is_rbt_color_black (node_type_* PARAM_INOUT node_ptr)
{
	return (!node_ptr || BLACK_COLOR_NODE_TYPE == node_ptr->get_color ());
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE void TEMPLATE_CRB_BST ::copy_tree_color (node_type_* PARAM_INOUT dec_node_ptr,	
	const node_type_* PARAM_IN src_node_ptr)
{
	dec_node_ptr->set_color (src_node_ptr->get_color());
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE  void TEMPLATE_CRB_BST ::rbt_left_rotate (node_type_ *& PARAM_INOUT root_node_ptr, 
	node_type_ *	PARAM_INOUT sentinel_node_ptr,
	node_type_ *	PARAM_INOUT node_ptr)
{
	node_type_ * temp_node_ptr;
	node_type_ * tmp_letf_node_ptr;

	temp_node_ptr = node_ptr->get_right_node_ref ();
	node_ptr->set_right_node (temp_node_ptr->get_left_node_ref ());

	tmp_letf_node_ptr = temp_node_ptr->get_left_node_ref ();
	if (tmp_letf_node_ptr != sentinel_node_ptr) 
	{
		tmp_letf_node_ptr->set_parent_node (node_ptr);
	}

	temp_node_ptr->set_parent_node (node_ptr->get_parent_node_ref ());

	if (node_ptr == root_node_ptr) 
	{
		root_node_ptr = temp_node_ptr;
	} 
	else
	{
		node_type_ * tmp_parent_node_ptr = node_ptr->get_parent_node_ref ();
		if (node_ptr == tmp_parent_node_ptr->get_left_node ())
		{
			tmp_parent_node_ptr->set_left_node (temp_node_ptr);
		}
		else
		{
			tmp_parent_node_ptr->set_right_node (temp_node_ptr);
		}
	}

	temp_node_ptr->set_left_node (node_ptr);
	node_ptr->set_parent_node (temp_node_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE void TEMPLATE_CRB_BST ::rbt_right_rotate (node_type_ *& PARAM_INOUT	root_node_ptr, 
	node_type_ *	PARAM_INOUT	sentinel_node_ptr,
	node_type_ *	PARAM_INOUT	node_ptr)
{
	node_type_ * temp_node_ptr;
	node_type_* temp_right_node_ptr;

	temp_node_ptr = node_ptr->get_left_node_ref ();
	node_ptr->set_left_node (temp_node_ptr->get_right_node_ref ());

	temp_right_node_ptr = temp_node_ptr->get_right_node_ref ();

	if (temp_right_node_ptr != sentinel_node_ptr) 
	{
		temp_right_node_ptr->set_parent_node (node_ptr);
	}

	temp_node_ptr->set_parent_node (node_ptr->get_parent_node_ref ());

	if (node_ptr == root_node_ptr) 
	{
		root_node_ptr = temp_node_ptr;
	} 
	else
	{
		node_type_ * tmp_parent_node_ptr = node_ptr->get_parent_node_ref ();
		if (tmp_parent_node_ptr->get_right_node () == node_ptr)
		{
			tmp_parent_node_ptr->set_right_node (temp_node_ptr);
		}
		else
		{
			tmp_parent_node_ptr->set_left_node (temp_node_ptr);
		}
	}

	temp_node_ptr->set_right_node (node_ptr);
	node_ptr->set_parent_node (temp_node_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE result_t TEMPLATE_CRB_BST :: rbt_add_rotate_fixup (node_type_ *& PARAM_INOUT root_node_ptr,
	node_type_*  PARAM_INOUT add_node_ptr)
{
	node_type_* temp_node_ptr;
	bool is_red_node = false;

	// 根节点的颜色一定是黑的
	if (add_node_ptr == root_node_ptr)
	{
		TEMPLATE_CRB_BST :: set_rbt_color_black (add_node_ptr);
		return PFX_STATUS_OK;
	}

	while (add_node_ptr != root_node_ptr) 
	{
		is_red_node = TEMPLATE_CRB_BST :: is_rbt_color_red 
			(add_node_ptr->get_parent_node_ref ());
		
		if (!is_red_node)
		{
			break;
		}
		// 新添加的父节点为红色
		
		node_type_* parent_node_ptr = add_node_ptr->get_parent_node_ref ();
		node_type_* grand_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();

		RETURN_INVALID_RESULT (null == grand_parent_node_ptr,PFX_STATUS_MEM_ERR);

		// 当爷爷的左孩子节点为父节点的时候
		if (grand_parent_node_ptr->get_left_node () == parent_node_ptr) 
		{
			temp_node_ptr = grand_parent_node_ptr->get_right_node_ref (); 
			is_red_node = TEMPLATE_CRB_BST :: is_rbt_color_red (temp_node_ptr);

			//RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp),PFX_STATUS_MEM_ERR);
			if (is_red_node)
			{
				// 叔叔节点红色
				// 将叔叔节点变黑
				// 父节点变黑，（解决新增节点与父节点都是红色的问题）
				// 将爷爷节点变红，当作新增节点，指针上移两代
				TEMPLATE_CRB_BST :: set_rbt_color_black (parent_node_ptr);
				TEMPLATE_CRB_BST :: set_rbt_color_black (temp_node_ptr);
				TEMPLATE_CRB_BST :: set_rbt_color_red (grand_parent_node_ptr);
				add_node_ptr = grand_parent_node_ptr;
			}
			else
			{
				// 叔叔节点黑色
				if (parent_node_ptr->get_right_node () == add_node_ptr)
				{
					// 新增节点是父节点的右孩子
					// 左旋操作
					// 然后孩子父亲互换角色
					add_node_ptr = parent_node_ptr;
					TEMPLATE_CRB_BST :: rbt_left_rotate (root_node_ptr,null,add_node_ptr);

					parent_node_ptr = add_node_ptr->get_parent_node_ref ();
					grand_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();
				}

				
				TEMPLATE_CRB_BST :: set_rbt_color_black (parent_node_ptr);
				TEMPLATE_CRB_BST :: set_rbt_color_red (grand_parent_node_ptr);
				TEMPLATE_CRB_BST :: rbt_right_rotate (root_node_ptr,null,grand_parent_node_ptr);
			}

		} 
		// 当爷爷的右孩子节点为父节点的时候
		else if (grand_parent_node_ptr->get_right_node () == parent_node_ptr) 
		{
			temp_node_ptr = grand_parent_node_ptr->get_left_node_ref ();
			is_red_node =  TEMPLATE_CRB_BST :: is_rbt_color_red (temp_node_ptr);

			if (is_red_node)
			{
				TEMPLATE_CRB_BST :: set_rbt_color_black (parent_node_ptr);
				TEMPLATE_CRB_BST :: set_rbt_color_black (temp_node_ptr);
				TEMPLATE_CRB_BST :: set_rbt_color_red (grand_parent_node_ptr);
				add_node_ptr = grand_parent_node_ptr;
			}
			else
			{
				if (parent_node_ptr->get_left_node () == add_node_ptr)
				{
					add_node_ptr = parent_node_ptr;
					TEMPLATE_CRB_BST :: rbt_right_rotate (root_node_ptr,null,add_node_ptr);

					parent_node_ptr = (node_type_*) add_node_ptr->get_parent_node ();
					grand_parent_node_ptr =  (node_type_*) parent_node_ptr->get_parent_node ();
				}
				TEMPLATE_CRB_BST :: set_rbt_color_black (parent_node_ptr);
				TEMPLATE_CRB_BST :: set_rbt_color_red (grand_parent_node_ptr);
				TEMPLATE_CRB_BST :: rbt_left_rotate (root_node_ptr,null,grand_parent_node_ptr);
			}
		}
		// 父节点既不是爷爷的左孩子也不是右孩子，内存出错
		else
		{
			RETURN_INVALID_RESULT (true,PFX_STATUS_MEM_ERR);
		}
	}

	TEMPLATE_CRB_BST :: set_rbt_color_black (root_node_ptr);
	return PFX_STATUS_OK;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE result_t TEMPLATE_CRB_BST :: rbt_remove_rotate_fixup (node_type_ *& PARAM_INOUT root_node_ptr,
	node_type_*  PARAM_INOUT ref_node_ptr)
{
	node_type_* temp_node_ptr;
	bool check_color = false;
	bool check_color_ = false;

	RETURN_INVALID_RESULT ((null == ref_node_ptr),PFX_STATUS_OK);

	while (ref_node_ptr != root_node_ptr)
	{
		check_color = TEMPLATE_CRB_BST :: is_rbt_color_black (ref_node_ptr);

		if (!check_color)
		{
			break;
		}

		node_type_* parent_node_ptr = ref_node_ptr->get_parent_node_ref ();

		if (parent_node_ptr->get_left_node() == ref_node_ptr)
		{
			temp_node_ptr = parent_node_ptr->get_right_node_ref ();
			check_color = TEMPLATE_CRB_BST :: is_rbt_color_red (temp_node_ptr);

			if (check_color)
			{
				if (temp_node_ptr)
				{
					TEMPLATE_CRB_BST :: set_rbt_color_black (temp_node_ptr);
				}
				
				TEMPLATE_CRB_BST :: set_rbt_color_red (parent_node_ptr);
				TEMPLATE_CRB_BST :: rbt_left_rotate (root_node_ptr,null,parent_node_ptr);

				temp_node_ptr = (node_type_*) parent_node_ptr->get_right_node ();
			}

			if (null == temp_node_ptr)
			{
				ref_node_ptr = parent_node_ptr;
				continue;
			}

			check_color = TEMPLATE_CRB_BST :: is_rbt_color_black 
				((node_type_*) temp_node_ptr->get_left_node ()) ;

			check_color_ = TEMPLATE_CRB_BST :: is_rbt_color_black 
				((node_type_*) temp_node_ptr->get_right_node ());


			if (check_color && check_color_)
			{
				TEMPLATE_CRB_BST :: set_rbt_color_red (temp_node_ptr);
				ref_node_ptr = parent_node_ptr;
			}
			else
			{
				check_color = TEMPLATE_CRB_BST :: is_rbt_color_black 
					((node_type_*) temp_node_ptr->get_right_node ()) ;

				if (check_color)
				{
					node_type_* temp_left_node_ptr = temp_node_ptr->get_left_node_ref ();

					if (temp_left_node_ptr)
					{
						TEMPLATE_CRB_BST :: set_rbt_color_black (temp_left_node_ptr);
					}
					
					TEMPLATE_CRB_BST :: set_rbt_color_red (temp_node_ptr);
					TEMPLATE_CRB_BST :: rbt_right_rotate (root_node_ptr,null,temp_node_ptr);

					temp_node_ptr = (node_type_*) parent_node_ptr->get_right_node ();
				}

				node_type_* temp_right_node_ptr = temp_node_ptr->get_right_node_ref ();

				TEMPLATE_CRB_BST :: copy_tree_color (temp_node_ptr,parent_node_ptr);
				TEMPLATE_CRB_BST :: set_rbt_color_black (parent_node_ptr);
				if (temp_right_node_ptr)
				{
					TEMPLATE_CRB_BST :: set_rbt_color_black (temp_right_node_ptr);
				}
				TEMPLATE_CRB_BST :: rbt_right_rotate (root_node_ptr,null,parent_node_ptr);

				ref_node_ptr = root_node_ptr;
			}
		}
		else if (parent_node_ptr->get_right_node() == ref_node_ptr)
		{
			temp_node_ptr =  (node_type_*) parent_node_ptr->get_left_node ();
			check_color = TEMPLATE_CRB_BST :: is_rbt_color_red (temp_node_ptr);

			if (check_color)
			{
				if (temp_node_ptr)
				{
					TEMPLATE_CRB_BST :: set_rbt_color_black (temp_node_ptr);
				}
				TEMPLATE_CRB_BST :: set_rbt_color_red (parent_node_ptr);
				TEMPLATE_CRB_BST :: rbt_right_rotate (root_node_ptr,null,parent_node_ptr);

				temp_node_ptr =  (node_type_*) parent_node_ptr->get_left_node ();
			}

			if (null == temp_node_ptr)
			{
				ref_node_ptr = parent_node_ptr;
				continue;
			}

			check_color = TEMPLATE_CRB_BST :: is_rbt_color_black 
				((node_type_*) temp_node_ptr->get_left_node ()) ;

			check_color_ = TEMPLATE_CRB_BST :: is_rbt_color_black 
				((node_type_*) temp_node_ptr->get_right_node ());

			if (check_color && check_color_)
			{
				TEMPLATE_CRB_BST :: set_rbt_color_black (temp_node_ptr);
				ref_node_ptr = parent_node_ptr;
			}
			else
			{
				check_color = TEMPLATE_CRB_BST :: is_rbt_color_black 
					((node_type_*) temp_node_ptr->get_left_node ()) ;

				if (check_color)
				{
					node_type_* temp_right_node_ptr = temp_node_ptr->get_right_node_ref ();
					if (temp_right_node_ptr)
					{
						TEMPLATE_CRB_BST :: set_rbt_color_black (temp_right_node_ptr);
					}
					TEMPLATE_CRB_BST :: set_rbt_color_red (temp_node_ptr);
					TEMPLATE_CRB_BST :: rbt_left_rotate (root_node_ptr,null,temp_node_ptr);

					temp_node_ptr = (node_type_*) parent_node_ptr->get_left_node ();
				}

				node_type_* temp_left_node_ptr = temp_node_ptr->get_right_node_ref ();

				TEMPLATE_CRB_BST :: copy_tree_color (temp_node_ptr,parent_node_ptr);
				TEMPLATE_CRB_BST :: set_rbt_color_black (parent_node_ptr);
				if (temp_left_node_ptr)
				{
					TEMPLATE_CRB_BST :: set_rbt_color_black (temp_left_node_ptr);
				}
				TEMPLATE_CRB_BST :: rbt_right_rotate (root_node_ptr,null,parent_node_ptr);

				ref_node_ptr = root_node_ptr;
			}
		}
		else
		{
			RETURN_INVALID_RESULT (true,PFX_STATUS_MEM_ERR);
		}
	}

	TEMPLATE_CRB_BST :: set_rbt_color_black (ref_node_ptr);
	return PFX_STATUS_OK;
}


PFX_CBST_TEMPLATE_DEFINES
const node_type_* TEMPLATE_CRB_BST ::add_rb_node (node_type_*& PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT add_node_ptr,
	result_t& PARAM_OUT status_)
{
	result_t			status;
	node_type_*	temp_node_ptr = null;

	RETURN_INVALID_BY_ACT_RESULT (null == add_node_ptr,
		status_ = PFX_STATUS_INVALID_PARAMS,null);

	// 插入的初始节点的颜色为红色
	TEMPLATE_CRB_BST ::set_rbt_color_red (add_node_ptr);

	status = TEMPLATE_CBST ::add_node (root_node_ptr,
		add_node_ptr,temp_node_ptr);


	RETURN_INVALID_BY_ACT_RESULT ((PFX_STATUS_OK != status),status_ = status,temp_node_ptr);

	// 平衡变换
	status = TEMPLATE_CRB_BST ::rbt_add_rotate_fixup (root_node_ptr,add_node_ptr);

	status_ = status;
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return add_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* TEMPLATE_CRB_BST ::remove_rb_node (node_type_*& PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT remove_node_ptr,
	result_t& PARAM_OUT status_)
{
	result_t			status;
	bool							is_red_node;

	//_redblack_tree_node_t*	proot_node;
	node_type_* sub_romove_ref_node_ptr;
	node_type_* sub_remove_node_ptr;

	RETURN_INVALID_BY_ACT_RESULT (null == remove_node_ptr,
		status_ = PFX_STATUS_INVALID_PARAMS,null);
	
	sub_romove_ref_node_ptr = 
		TEMPLATE_CBST :: find_remove_replace_node
		(remove_node_ptr,sub_remove_node_ptr,null);

	if (sub_remove_node_ptr == root_node_ptr)
	{
		status = TEMPLATE_CBST :: remove_node_internal
			(root_node_ptr,remove_node_ptr,sub_remove_node_ptr,sub_romove_ref_node_ptr,null);

		status_ = status;

		if (PFX_STATUS_OK == status)
		{
			if (null != sub_romove_ref_node_ptr)
			{
				TEMPLATE_CRB_BST ::set_rbt_color_black (sub_romove_ref_node_ptr);
			}

			return remove_node_ptr;
		}
		return null;
	}

	is_red_node = TEMPLATE_CRB_BST :: is_rbt_color_red (sub_remove_node_ptr);

	status = TEMPLATE_CBST :: remove_node_internal
		(root_node_ptr,remove_node_ptr,sub_remove_node_ptr,sub_romove_ref_node_ptr,null);

	if (null != sub_remove_node_ptr && sub_remove_node_ptr != remove_node_ptr)
	{
		TEMPLATE_CRB_BST :: copy_tree_color (sub_remove_node_ptr,remove_node_ptr);
	}

	status_ = status;

	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	RETURN_RESULT ((is_red_node || null == root_node_ptr),remove_node_ptr);

	status = TEMPLATE_CRB_BST :: rbt_remove_rotate_fixup (root_node_ptr,sub_romove_ref_node_ptr);

	status_ = status;

	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return remove_node_ptr;
}

PECKER_END

#endif			//PFX_CBST_CODES_H_
