/*
 * pfx_cbst.h
 *
 *  Created on: 2013-12-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBST_CODES_H_
#define		PFX_CBST_CODES_H_


#include "pfx_cbst.h"
PECKER_BEGIN

PFX_CBST_TEMPLATE_DEFINES
pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::pfx_cbst(/*Iallocator_cpp* allocator = null*/):
	m_root_ptr (null)
{

}

PFX_CBST_TEMPLATE_DEFINES
pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::pfx_cbst(const pfx_cbst PFX_CBST_TEMPLATE_PARAMS* other_ptr) throw (pfx_result_t) : m_root_ptr (null)
{
	if (this != other_ptr)
	{
		pfx_result_t status_ = copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}

PFX_CBST_TEMPLATE_DEFINES
pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::~pfx_cbst()
{
	clear ();
}

PFX_CBST_TEMPLATE_DEFINES
pfx_result_t pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::copy (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst_ptr)
{
	RETURN_RESULT (other_bst_ptr == this,PFX_STATUS_OK);
	pfx_result_t status_ = clear();
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,PFX_STATUS_ERROR_);
	RETURN_RESULT (null == other_bst_ptr->m_root_ptr,PFX_STATUS_OK);

	node_type_* temp_dec_node_ptr;
	node_type_* temp_src_node_ptr;
	node_type_* new_node_ptr = new_node ();

	RETURN_INVALID_RESULT (null == new_node_ptr,PFX_STATUS_MEM_LOW);

	*new_node_ptr = *other_bst_ptr->m_root_ptr;


	pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (new_node_ptr);
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

				pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (new_node_ptr,null,null,temp_dec_node_ptr);

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

				pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (new_node_ptr,null,null,temp_dec_node_ptr);

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
pfx_result_t pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::copy_by_iterator (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst_ptr)
{
	RETURN_RESULT (other_bst_ptr == this,PFX_STATUS_OK);
	pfx_result_t status_ = clear();
	RETURN_INVALID_RESULT (PFX_STATUS_OK != status_,PFX_STATUS_ERROR_);

	const node_type_* pbegin;
	const node_type_* pend;
	pfx_result_t status = PFX_STATUS_OK;

	RETURN_RESULT (null == m_root_ptr,status);

	pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS iterator_begin;
	pfx_preorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS iterator_end;

	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*  iterator_begin_ptr = begin (&iterator_begin);
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*  iterator_end_ptr = end (&iterator_end);

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
pfx_result_t pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::clear ()
{
	//const node_type_* pbegin;
	//const node_type_* end_ptr;
	pfx_result_t status = PFX_STATUS_OK;

	RETURN_RESULT (null == m_root_ptr,status);

	pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS iterator_begin;
	pfx_posorder_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS iterator_end;

	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*  iterator_begin_ptr =  begin (&iterator_begin);
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS*  iterator_end_ptr =  end (&iterator_end);
	
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

			//node_type_* del_node_parent_ptr = (node_type_*)del_node_ptr->get_parent_node ();

			//if (del_node_parent_ptr->get_left_node () == del_node_ptr)
			//{
			//	 del_node_parent_ptr->set_left_node ((node_type_*)null);
			//}
			//else if (del_node_parent_ptr->get_right_node () == del_node_ptr)
			//{
			//	del_node_parent_ptr->set_left_node ((node_type_*)null);
			//}
			//else
			//{
			//	status = PFX_STATUS_MEM_ERR;
			//}

			status = release_node (del_node_ptr);
			BREAK_LOOP_CONDITION (PFX_STATUS_OK != status);
		}
	} while (1);
	m_root_ptr = null;

	return status;
}

PFX_CBST_TEMPLATE_DEFINES
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::begin (pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_OUT iterator_) const
{
	if (iterator_)
	{
		pfx_result_t status_ = iterator_->init (m_root_ptr,m_root_ptr);
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
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::end (pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * PARAM_OUT iterator_) const
{
	if (iterator_)
	{
		pfx_result_t status_ = iterator_->init (m_root_ptr,m_root_ptr);
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
pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find (pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_OUT iterator_,
		const node_type_* PARAM_IN key_node_ptr) const
{
	if (iterator_)
	{
		const node_type_* find_node_ptr = find (key_node_ptr);
		if (find_node_ptr)
		{
			pfx_result_t status_ = iterator_->init(find_node_ptr,m_root_ptr);
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

//
//public:
PFX_CBST_TEMPLATE_DEFINES
const node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find (const node_type_* PARAM_IN key_node_ptr) const
{
	return pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find_node (key_node_ptr,m_root_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find_reference (const node_type_* PARAM_IN key_node_ptr)
{
	return (node_type_*)pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find_node (key_node_ptr,m_root_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::add (node_type_* PARAM_INOUT add_node_ptr,
	pfx_result_t& PARAM_OUT status_)
{
	node_type_* added_node_ptr = null;
	status_ = pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::add_node (m_root_ptr,add_node_ptr,added_node_ptr);
	return added_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::remove (node_type_* PARAM_INOUT remove_node_ptr,
		pfx_result_t& PARAM_OUT status_)
{
	status_ = pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::remove_node (m_root_ptr,remove_node_ptr);
	if (PFX_STATUS_OK != status_)
	{
		remove_node_ptr = null;
	}
	return remove_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_*  pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::get_root () const
{
	return m_root_ptr;
}
//public:
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE const node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::max_node (const node_type_* root_node_ptr, 
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
PFX_INLINE const node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::min_node (const node_type_* root_node_ptr, 
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
PFX_INLINE pfx_result_t pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
	node_type_* PARAM_IN left_node_ptr /*= null*/,
	node_type_* PARAM_IN right_node_ptr /*= null*/,
	node_type_* PARAM_IN parent_node_ptr /*= null*/)
{
	pfx_result_t status_ = PFX_STATUS_INVALID_PARAMS;
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
const node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find_node (const node_type_* PARAM_IN key_node_ptr,
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
const node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find_near_node  (const node_type_* PARAM_IN key_node_ptr,
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
//
PFX_CBST_TEMPLATE_DEFINES
pfx_result_t pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::add_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT add_node_ptr,
		node_type_*& PARAM_OUT added_node_ptr)
{
	pfx_result_t	status;
	int					cmp_result;
	node_type_*	tmp_root_node_ptr;
	node_type_*	node_to_be_add_ptr;
	node_type_*	parent_node_ptr;

	tmp_root_node_ptr = root_node_ptr;

	// 添加第一个节点
	if (null == tmp_root_node_ptr)
	{
		root_node_ptr = add_node_ptr;
		pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (add_node_ptr);
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
			pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (add_node_ptr,null,null,node_to_be_add_ptr);
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
			pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (add_node_ptr,null,null,node_to_be_add_ptr);
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
pfx_result_t pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::remove_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		const node_type_* PARAM_IN null_node_ptr /*= null*/)
{
	RETURN_INVALID_RESULT (null == remove_node_ptr,PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT (null == root_node_ptr,PFX_STATUS_OK);

	node_type_* sub_romove_ref_node_ptr;
	node_type_* sub_remove_node_ptr;
	pfx_result_t status_ = PFX_STATUS_OK;

	sub_romove_ref_node_ptr = pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find_remove_replace_node 
		(remove_node_ptr,sub_remove_node_ptr,null_node_ptr);

	//remove_node_ptr = 
	status_ =	 pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::remove_node_internal (root_node_ptr,remove_node_ptr,sub_remove_node_ptr,
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
node_type_* pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::find_remove_replace_node (node_type_* PARAM_IN remove_node_ptr,
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
		tmp_sub_remove_node_ptr = pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::min_node (remove_node_ptr->get_right_node(),null_node_ptr);
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
pfx_result_t pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::remove_node_internal (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		node_type_* PARAM_INOUT sub_remove_node_ptr,
		node_type_* PARAM_INOUT sub_remove_node_ref_ptr,
		const node_type_* PARAM_IN null_node_ptr /*= null*/)
{
	node_type_* tmp_root_node_ptr = root_node_ptr;
	node_type_* parant_node_ptr = null;
	pfx_result_t status_ = PFX_STATUS_OK;

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
		pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (remove_node_ptr);
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

		pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (remove_node_ptr);
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

	pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::init_node_leaves (remove_node_ptr);
	BREAK_LOOP (status_,PFX_STATUS_OK);

	FOR_ONE_LOOP_END
	

	return status_;
}


//////////////////////////////////////////////////////////////////////////
///


PFX_CBST_TEMPLATE_DEFINES
pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::pfx_cavl_tree(/*Iallocator_cpp* allocator = null*/)
{
	;
}
PFX_CBST_TEMPLATE_DEFINES
pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::pfx_cavl_tree (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS* PARAM_IN other_) throw (pfx_result_t)
{
	if (this != other_ptr)
	{
		pfx_result_t status_ = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS :: copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}
PFX_CBST_TEMPLATE_DEFINES
pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::pfx_cavl_tree (const pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS* PARAM_IN other_) throw (pfx_result_t)
{
	if (this != other_ptr)
	{
		pfx_result_t status_ = pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}
//public:
PFX_CBST_TEMPLATE_DEFINES
const node_type_* pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::add (node_type_* PARAM_INOUT add_node_ptr,
		pfx_result_t& PARAM_OUT status_)
{
	return pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::add_avl_node (m_root_ptr,add_node_ptr,status_);
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::remove (node_type_* PARAM_INOUT remove_node_ptr,
		pfx_result_t& PARAM_OUT status_)
{
	return remove_avl_node (m_root_ptr,remove_node_ptr,status_);
}

PFX_CBST_TEMPLATE_DEFINES
pfx_result_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::copy (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * 
																													PARAM_IN other_bst_ptr)
{
	return pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: copy_by_iterator (other_bst_ptr);
}
PFX_CBST_TEMPLATE_DEFINES
pfx_result_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::copy (const pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS * 
																													PARAM_IN other_bst_ptr)
{
	return pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: copy (other_bst_ptr);
}
//public:
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS::init_avl_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
	 node_type_* PARAM_IN left_node_ptr /*= null*/,
	 node_type_* PARAM_IN right_node_ptr /*= null*/,
	 node_type_* PARAM_IN parent_node_ptr/* = null*/)
{
	pfx_result_t status_ = PFX_STATUS_INVALID_PARAMS;
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
PFX_INLINE pfx_nsize_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::get_avl_height (const node_type_* PARAM_IN node_ptr)
{
	pfx_nsize_t height_value = -1;
	if (node_ptr)
	{
		height_value = node_ptr->get_height ();
	}
	return height_value;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE pfx_nsize_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::calculate_avl_height (const node_type_* PARAM_IN left_node_ptr,
		const node_type_* PARAM_IN right_node_ptr)
{
	pfx_nsize_t left_height = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS::get_avl_height (left_node_ptr);
	pfx_nsize_t right_height = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS::get_avl_height (right_node_ptr);
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
PFX_INLINE pfx_nsize_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::calculate_avl_height (const node_type_* PARAM_IN node_ptr)
{
	pfx_nsize_t height_value = -1;
	if (node_ptr)
	{
		height_value = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::calculate_avl_height 
																	(node_ptr->get_left_node(),node_ptr->get_right_node ());
	}
	return height_value;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE pfx_nsize_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::calculate_avl_balance_value 
																	(const node_type_* PARAM_IN node_ptr)
{
	pfx_nsize_t balance_value = 0;
	if (node_ptr)
	{
		balance_value = get_avl_height (node_ptr->get_left_node ()) - get_avl_height (node_ptr->get_right_node ());
	}
	return balance_value;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE void pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::update_avl_height (node_type_* PARAM_IN node_ptr)
{
	pfx_nsize_t height_value = calculate_avl_height (node_ptr);
	node_ptr->set_height (height_value);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_rr_rotate (node_type_* PARAM_INOUT node_ptr)
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

	pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::update_avl_height (node_ptr);
	pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::update_avl_height (rotate_node_ptr);

	return rotate_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_ll_rotate (node_type_* PARAM_INOUT node_ptr)
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

	pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::update_avl_height (node_ptr);
	pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::update_avl_height (rotate_node_ptr);

	return rotate_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_lr_rotate (node_type_* PARAM_INOUT node_ptr)
{
	// LR = RR(node_ptr->letf) + LL(node_ptr)
	node_type_* tmp_node_ptr = avl_rr_rotate (node_ptr->get_left_node_ref ());
	node_ptr->set_left_node (tmp_node_ptr); 
	return avl_ll_rotate (node_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE node_type_* pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_rl_rotate (node_type_* PARAM_INOUT node_ptr)
{
	// RL = LL(node_ptr->right)) + RR(node_ptr)
	node_type_* tmp_node_ptr = avl_ll_rotate (node_ptr->get_right_node_ref ());
	node_ptr->set_right_node (tmp_node_ptr); 
	return avl_rr_rotate (node_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE AVLTREE_ROTATE_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_single_rotate (pfx_nsize_t balance_value,
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
		else if (pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::get_avl_height (left_node_ptr->get_left_node ()) >= 
			pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::get_avl_height (left_node_ptr->get_right_node ()))
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

		if ( pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::get_avl_height  (right_node_ptr->get_right_node ()) 
			>= pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::get_avl_height  (right_node_ptr->get_left_node ()))
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
PFX_INLINE pfx_result_t pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_update_rotate (node_type_* & PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT begin_node_ptr)
{
	pfx_result_t			status = PFX_STATUS_OK;
	pfx_nsize_t				height;
	node_type_*			tmp_root_node_ptr;
	node_type_*			parent_node;
	AVLTREE_ROTATE_t rotate_type;

	tmp_root_node_ptr = root_node_ptr;

	// 当起始节点为根节点的处理流程
	if (tmp_root_node_ptr == begin_node_ptr)
	{
		rotate_type = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_single_rotate 
			(pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::calculate_avl_balance_value (tmp_root_node_ptr), tmp_root_node_ptr, root_node_ptr);


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

	pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::update_avl_height (begin_node_ptr);

	do 
	{
		parent_node = begin_node_ptr->get_parent_node_ref ();

		//一般情况下必须达成 null == parent_node的条件，即轮寻翻转到跟节点的时候
		//才退出翻转处理流程
		if (null == parent_node)
		{
			BREAK_LOOP (status,PFX_STATUS_OK);
		}

		// 节点与他的父节点的指针一样，证明内存已经出错
		if (begin_node_ptr == parent_node)
		{
			BREAK_LOOP (status,PFX_STATUS_MEM_ERR);
		}

		height = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::get_avl_height (parent_node);
		pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::update_avl_height (parent_node);

		// 发现更新完的高度跟原来的高度一样，表明上面的节点高度并没有发生变化
		// 退出翻转
		if (pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::get_avl_height (parent_node) == height)
		{
			BREAK_LOOP (status,PFX_STATUS_OK);
		}

		node_type_* parent_parent_node_ptr = parent_node->get_parent_node_ref ();
		begin_node_ptr = parent_node;

			// 注：这利用相关节点的关联引用进行操作，在翻转过程中快速替换被关联节点对应的节点指针
		if (parent_node == tmp_root_node_ptr || null == parent_parent_node_ptr)
		{
			rotate_type = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_single_rotate 
				(pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::calculate_avl_balance_value (parent_node), parent_node, root_node_ptr);
		}
		else
		{
			if (parent_parent_node_ptr->get_left_node () == parent_node)
			{
				node_type_*& temp_node_ptr_ref =  (node_type_*&)(parent_parent_node_ptr->get_left_node_ref ());
				rotate_type = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_single_rotate 
					(pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::calculate_avl_balance_value (parent_node), parent_node, temp_node_ptr_ref);
			}
			else if (parent_parent_node_ptr->get_right_node () == parent_node)
			{
				node_type_*&  temp_node_ptr_ref = (node_type_*&) (parent_parent_node_ptr->get_right_node_ref ());
				rotate_type = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::avl_single_rotate 
					(pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::calculate_avl_balance_value (parent_node), parent_node, temp_node_ptr_ref);
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
			// 进入下一个节点的轮训
			status = PFX_STATUS_OK;
		}

	} while (1);

	return status;
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_* pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::add_avl_node (node_type_*& PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT add_node_ptr,
	pfx_result_t& PARAM_OUT status_)
{
	pfx_result_t			status;
	node_type_*	temp_node_ptr = null;

	RETURN_INVALID_BY_ACT_RESULT ((null == add_node_ptr),
		status_ = PFX_STATUS_INVALID_PARAMS,null);

	status = pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::add_node (root_node_ptr,
		add_node_ptr,temp_node_ptr);

	RETURN_INVALID_BY_ACT_RESULT ((PFX_STATUS_OK != status),
		status_ = status,temp_node_ptr);

	pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS :: update_avl_height (add_node_ptr);

	status = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS :: avl_update_rotate (root_node_ptr,add_node_ptr);

	status_ = status;
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return add_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS ::remove_avl_node (node_type_*& PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT remove_node_ptr,
	pfx_result_t& PARAM_OUT status_)
{
	pfx_result_t			status;
	pfx_s16_t				height;
	node_type_*	temp_node_ptr = null;
	//node_type_*	tmp_root_node_ptr;
	node_type_*	parent_node_ptr;
	node_type_* sub_romove_ref_node_ptr;
	node_type_* sub_remove_node_ptr;

	RETURN_INVALID_BY_ACT_RESULT ((null == remove_node_ptr),
		status_ = PFX_STATUS_INVALID_PARAMS,null);

	height = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS :: get_avl_height (root_node_ptr);

	sub_romove_ref_node_ptr = 
		pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: find_remove_replace_node
		(remove_node_ptr,sub_remove_node_ptr,null);

	status = pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: remove_node_internal
		(root_node_ptr,remove_node_ptr,sub_remove_node_ptr,sub_romove_ref_node_ptr,null);


	status_ = status;
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),remove_node_ptr);

	RETURN_RESULT ((null == root_node_ptr),remove_node_ptr);

	temp_node_ptr = sub_romove_ref_node_ptr;
	if (null == temp_node_ptr)
	{
		if (null != sub_remove_node_ptr)
		{
			parent_node_ptr = sub_remove_node_ptr->get_parent_node_ref();
			if (remove_node_ptr != parent_node_ptr)
			{
				temp_node_ptr = parent_node_ptr;
			}
		}

		if (null == temp_node_ptr)
		{
			temp_node_ptr = root_node_ptr;
		}
	}
		
	root_node_ptr->set_height (height);

	pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS :: update_avl_height (temp_node_ptr);

	parent_node_ptr = (node_type_*)(temp_node_ptr->get_parent_node ());


	status = pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS :: avl_update_rotate (root_node_ptr,temp_node_ptr);

	status_ = status;
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return remove_node_ptr;
}


//template < class node_type_, typename compare_two_node_ >
//class pfx_crb_tree : public virtual pfx_cbst
//{
//public:
PFX_CBST_TEMPLATE_DEFINES
pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::pfx_crb_tree (/*Iallocator_cpp* allocator = null*/)
{
	;
}

PFX_CBST_TEMPLATE_DEFINES
	pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: pfx_crb_tree (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_ptr) throw (pfx_result_t)
{
	if (this != other_ptr)
	{
		pfx_result_t status_ = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}

PFX_CBST_TEMPLATE_DEFINES
pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: pfx_crb_tree (const pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS* PARAM_IN other_ptr) throw (pfx_result_t)
{
	if (this != other_ptr)
	{
		pfx_result_t status_ = pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: copy(other_ptr);
		if (PFX_STATUS_OK != status_)
		{
			throw (status_);
		}
	}
}
//public:
PFX_CBST_TEMPLATE_DEFINES
pfx_result_t pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: copy (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst_ptr)
{
	return pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: copy_by_iterator (other_bst_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
pfx_result_t pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::  copy (const pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst_ptr)
{
	return pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: copy (other_bst_ptr);
}

PFX_CBST_TEMPLATE_DEFINES
const node_type_* pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::add (node_type_* PARAM_INOUT add_node_ptr,
	pfx_result_t& PARAM_OUT status_)
{
	return pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::add_rb_node (m_root_ptr,add_node_ptr,status_);
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::remove (node_type_* PARAM_INOUT remove_node_ptr,
		pfx_result_t& PARAM_OUT status_)
{
	return pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: remove_rb_node (m_root_ptr,remove_node_ptr,status_);
}
//public:
PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::init_rb_node_leaves 
	(node_type_* PARAM_INOUT tree_node_ptr,
	node_type_* PARAM_IN left_node_ptr /*= null*/,
	node_type_* PARAM_IN right_node_ptr /*= null*/,
	node_type_* PARAM_IN parent_node_ptr /*= null*/)
{
	pfx_result_t status_ = PFX_STATUS_INVALID_PARAMS;
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
PFX_INLINE	void  pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::set_rbt_color_red (node_type_* PARAM_INOUT node_ptr)
{
	node_ptr->set_color (RED_COLOR_NODE_TYPE);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE	void  pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::set_rbt_color_black (node_type_* PARAM_INOUT node_ptr)
{
	node_ptr->set_color (BLACK_COLOR_NODE_TYPE);
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE	bool  pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::is_rbt_color_red (node_type_* PARAM_INOUT node_ptr)
{
	return (node_ptr && RED_COLOR_NODE_TYPE == node_ptr->get_color ());
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE	bool  pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::is_rbt_color_black (node_type_* PARAM_INOUT node_ptr)
{
	return (!node_ptr || BLACK_COLOR_NODE_TYPE == node_ptr->get_color ());
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE void pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::copy_tree_color (node_type_* PARAM_INOUT dec_node_ptr,	
	const node_type_* PARAM_IN src_node_ptr)
{
	dec_node_ptr->set_color (src_node_ptr->get_color());
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE  void pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::rbt_left_rotate (node_type_ *& PARAM_INOUT root_node_ptr, 
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
PFX_INLINE void pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::rbt_right_rotate (node_type_ *& PARAM_INOUT	root_node_ptr, 
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
PFX_INLINE pfx_result_t pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_add_rotate_fixup (node_type_ *& PARAM_INOUT root_node_ptr,
	node_type_*  PARAM_INOUT add_node_ptr)
{
	node_type_* temp_node_ptr;
	bool is_red_node = false;

	// 根节点的颜色一定是黑的
	if (add_node_ptr == root_node_ptr)
	{
		pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (add_node_ptr);
		return PFX_STATUS_OK;
	}

	while (add_node_ptr != root_node_ptr) 
	{
		is_red_node = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_red 
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
			is_red_node = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_red (temp_node_ptr);

			//RETURN_INVALID_RESULT ((pfx_invalid == is_color_temp),PFX_STATUS_MEM_ERR);
			if (is_red_node)
			{
				// 叔叔节点红色
				// 将叔叔节点变黑
				// 父节点变黑，（解决新增节点与父节点都是红色的问题）
				// 将爷爷节点变红，当作新增节点，指针上移两代
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (grand_parent_node_ptr);
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
					pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_left_rotate (root_node_ptr,null,add_node_ptr);

					parent_node_ptr = add_node_ptr->get_parent_node_ref ();
					grand_parent_node_ptr = parent_node_ptr->get_parent_node_ref ();
				}

				
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (grand_parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_right_rotate (root_node_ptr,null,grand_parent_node_ptr);
			}

		} 
		// 当爷爷的右孩子节点为父节点的时候
		else if (grand_parent_node_ptr->get_right_node () == parent_node_ptr) 
		{
			temp_node_ptr = grand_parent_node_ptr->get_left_node_ref ();
			is_red_node =  pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_red (temp_node_ptr);

			if (is_red_node)
			{
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (grand_parent_node_ptr);
				add_node_ptr = grand_parent_node_ptr;
			}
			else
			{
				if (parent_node_ptr->get_left_node () == add_node_ptr)
				{
					add_node_ptr = parent_node_ptr;
					pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_right_rotate (root_node_ptr,null,add_node_ptr);

					parent_node_ptr = (node_type_*) add_node_ptr->get_parent_node ();
					grand_parent_node_ptr =  (node_type_*) parent_node_ptr->get_parent_node ();
				}
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (grand_parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_left_rotate (root_node_ptr,null,grand_parent_node_ptr);
			}
		}
		// 父节点既不是爷爷的左孩子也不是右孩子，内存出错
		else
		{
			RETURN_INVALID_RESULT (true,PFX_STATUS_MEM_ERR);
		}
	}

	pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (root_node_ptr);
	return PFX_STATUS_OK;
}

PFX_CBST_TEMPLATE_DEFINES
PFX_INLINE pfx_result_t pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_remove_rotate_fixup (node_type_ *& PARAM_INOUT root_node_ptr,
	node_type_*  PARAM_INOUT ref_node_ptr)
{
	node_type_* temp_node_ptr;
	bool check_color = false;
	bool check_color_ = false;

	RETURN_INVALID_RESULT ((null == ref_node_ptr),PFX_STATUS_OK);

	while (ref_node_ptr != root_node_ptr)
	{
		check_color = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_black (ref_node_ptr);

		if (!check_color)
		{
			break;
		}

		node_type_* parent_node_ptr = ref_node_ptr->get_parent_node_ref ();

		if (parent_node_ptr->get_left_node() == ref_node_ptr)
		{
			temp_node_ptr = parent_node_ptr->get_right_node_ref ();
			check_color = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_red (temp_node_ptr);

			if (check_color)
			{
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_left_rotate (root_node_ptr,null,parent_node_ptr);

				temp_node_ptr = (node_type_*) parent_node_ptr->get_right_node ();
			}

			check_color = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_black 
				((node_type_*) temp_node_ptr->get_left_node ()) ;

			check_color_ = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_black 
				((node_type_*) temp_node_ptr->get_right_node ());

			if (check_color && check_color_)
			{
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (temp_node_ptr);
				ref_node_ptr = parent_node_ptr;
			}
			else
			{
				check_color = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_black 
					((node_type_*) temp_node_ptr->get_right_node ()) ;

				if (check_color)
				{
					node_type_* temp_left_node_ptr = temp_node_ptr->get_left_node_ref ();

					pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_left_node_ptr);
					pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (temp_node_ptr);
					pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_right_rotate (root_node_ptr,null,temp_node_ptr);

					temp_node_ptr = (node_type_*) parent_node_ptr->get_right_node ();
				}

				node_type_* temp_right_node_ptr = temp_node_ptr->get_right_node_ref ();

				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: copy_tree_color (temp_node_ptr,parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_right_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_right_rotate (root_node_ptr,null,parent_node_ptr);

				ref_node_ptr = root_node_ptr;
			}
		}
		else if (parent_node_ptr->get_right_node() == ref_node_ptr)
		{
			temp_node_ptr =  (node_type_*) parent_node_ptr->get_left_node ();
			check_color = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_red (temp_node_ptr);

			if (check_color)
			{
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_right_rotate (root_node_ptr,null,parent_node_ptr);

				temp_node_ptr =  (node_type_*) parent_node_ptr->get_left_node ();
			}

			check_color = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_black 
				((node_type_*) temp_node_ptr->get_left_node ()) ;

			check_color_ = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_black 
				((node_type_*) temp_node_ptr->get_right_node ());

			if (check_color && check_color_)
			{
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_node_ptr);
				ref_node_ptr = parent_node_ptr;
			}
			else
			{
				check_color = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_black 
					((node_type_*) temp_node_ptr->get_left_node ()) ;

				if (check_color)
				{
					node_type_* temp_right_node_ptr = temp_node_ptr->get_right_node_ref ();

					pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_right_node_ptr);
					pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_red (temp_node_ptr);
					pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_left_rotate (root_node_ptr,null,temp_node_ptr);

					temp_node_ptr = (node_type_*) parent_node_ptr->get_left_node ();
				}

				node_type_* temp_left_node_ptr = temp_node_ptr->get_right_node_ref ();

				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: copy_tree_color (temp_node_ptr,parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (parent_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (temp_left_node_ptr);
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_right_rotate (root_node_ptr,null,parent_node_ptr);

				ref_node_ptr = root_node_ptr;
			}
		}
		else
		{
			RETURN_INVALID_RESULT (true,PFX_STATUS_MEM_ERR);
		}
	}

	pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: set_rbt_color_black (ref_node_ptr);
	return PFX_STATUS_OK;
}


PFX_CBST_TEMPLATE_DEFINES
const node_type_* pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::add_rb_node (node_type_*& PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT add_node_ptr,
	pfx_result_t& PARAM_OUT status_)
{
	pfx_result_t			status;
	node_type_*	temp_node_ptr = null;

	RETURN_INVALID_BY_ACT_RESULT (null == add_node_ptr,
		status_ = PFX_STATUS_INVALID_PARAMS,null);

	// 插入的初始节点的颜色为红色
	pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::set_rbt_color_red (add_node_ptr);

	status = pfx_cbst PFX_CBST_TEMPLATE_PARAMS ::add_node (root_node_ptr,
		add_node_ptr,temp_node_ptr);


	RETURN_INVALID_BY_ACT_RESULT ((PFX_STATUS_OK != status),status_ = status,temp_node_ptr);

	// 平衡变换
	status = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::rbt_add_rotate_fixup (root_node_ptr,add_node_ptr);

	status_ = status;
	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return add_node_ptr;
}

PFX_CBST_TEMPLATE_DEFINES
node_type_* pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::remove_rb_node (node_type_*& PARAM_INOUT root_node_ptr,
	node_type_* PARAM_INOUT remove_node_ptr,
	pfx_result_t& PARAM_OUT status_)
{
	pfx_result_t			status;
	bool							is_red_node;

	//_redblack_tree_node_t*	proot_node;
	node_type_* sub_romove_ref_node_ptr;
	node_type_* sub_remove_node_ptr;

	RETURN_INVALID_BY_ACT_RESULT (null == remove_node_ptr,
		status_ = PFX_STATUS_INVALID_PARAMS,null);
	
	sub_romove_ref_node_ptr = 
		pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: find_remove_replace_node
		(remove_node_ptr,sub_remove_node_ptr,null);

	if (sub_remove_node_ptr == root_node_ptr)
	{
		status = pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: remove_node_internal
			(root_node_ptr,remove_node_ptr,sub_remove_node_ptr,sub_romove_ref_node_ptr,null);

		status_ = status;

		if (PFX_STATUS_OK == status)
		{
			if (null != sub_romove_ref_node_ptr)
			{
				pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS ::set_rbt_color_black (sub_romove_ref_node_ptr);
			}

			return remove_node_ptr;
		}
		return null;
	}

	is_red_node = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: is_rbt_color_red (sub_remove_node_ptr);

	status = pfx_cbst PFX_CBST_TEMPLATE_PARAMS :: remove_node_internal
		(root_node_ptr,remove_node_ptr,sub_remove_node_ptr,sub_romove_ref_node_ptr,null);

	if (null != sub_remove_node_ptr && sub_remove_node_ptr != remove_node_ptr)
	{
		pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: copy_tree_color (sub_remove_node_ptr,remove_node_ptr);
	}

	status_ = status;

	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	RETURN_RESULT ((is_red_node || null == root_node_ptr),remove_node_ptr);

	status = pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS :: rbt_remove_rotate_fixup (root_node_ptr,sub_romove_ref_node_ptr);

	status_ = status;

	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),null);

	return remove_node_ptr;
}

PECKER_END

#endif			//PFX_CBST_CODES_H_
