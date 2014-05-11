/*
 * pfx_cbst.h
 *
 *  Created on: 2013-12-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CBST_H_
#define		PFX_CBST_H_

#include "pfx_iterator.h"
#include "pecker_value_compare.h"
#include "pfx_data_traits.h"


PECKER_BEGIN

#define PFX_CBST_ITERATOR_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_CBST_ITERATOR_TEMPLATE_PARAMS  < node_type_ >
#define PFX_CBST_TEMPLATE_DEFINES template < class node_type_, class compare_two_node_ >
#define PFX_CBST_TEMPLATE_PARAMS  < node_type_, compare_two_node_ >

typedef enum PFX_DATA_API enum_preorder_iterator_next_node_type
{
	PREORDER_NEXT_SUB_ROOT_RIGHT = 0,
	PREORDER_NEXT_SUB_ROOT_LEFT,
	PREORDER_NEXT_LEFT,
	PREORDER_NEXT_RIGHT,
	PREORDER_NEXT_BEGIN,
	PREORDER_NEXT_END,
	PREORDER_FIN,

	enum_preorder_iterator_next_node_type_COUNT
}pfx_preorder_iterator_next_node_type_t;


//AVL旋转类型
typedef enum PFX_DATA_API enumAVLTREE_ROTATE_TYPE
{
	AVLTREE_NONE_ROTATE = 0,
	AVLTREE_ROTATE_ERR,
	AVLTREE_NOT_SIMPLE_ROTATE,
	AVLTREE_LL_ROTATE,
	AVLTREE_RR_ROTATE,
	AVLTREE_RL_ROTATE,
	AVLTREE_LR_ROTATE,
	AVLTREE_ROTATE_TYPE_COUNT
}AVLTREE_ROTATE_t;

#define RED_COLOR_NODE_TYPE		(1)
#define BLACK_COLOR_NODE_TYPE	(0)



template < class node_type_ >
class PFX_DATA_TEMPALE_API cbst_iterator : public IPfx_increase_iterator < node_type_ >
{
public:
	typedef cbst_iterator < node_type_ >			iterator_t;
	typedef node_type_										element_t;
	typedef node_type_	&									reference_t;
	typedef node_type_&										pointer_t;
	typedef typename cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS bst_interator_t;
protected:
	const node_type_*	m_current_node_ptr;
	const node_type_*   m_root_node_ptr;
public:
	cbst_iterator ();
	~cbst_iterator();
public:
	const node_type_* get_current_node () const;
	const node_type_* get_root_node () const;

	virtual result_t init (const node_type_*	current_node_ptr,
								const node_type_*   root_node_ptr);

public:
	virtual bst_interator_t* begin 
		(bst_interator_t* PARAM_INOUT 
		set_begin_iterator_ptr) const;
	virtual bst_interator_t* end 		
		(bst_interator_t* PARAM_INOUT 
		set_end_iterator_ptr) const;

	virtual bst_interator_t* begin (){return null;}
	virtual bst_interator_t* end (){return null;}

	virtual bst_interator_t* increase () {return null;}
	virtual bst_interator_t* decrease () {return null;}
public:
	virtual PFX_INLINE IPfx_increase_iterator < node_type_ >*	increase_iterator () { return increase(); }
	virtual	PFX_INLINE const node_type_*										get_current_element () const { return get_current_node(); }
//public:
//	static const node_type_* get_inorder_begin_node (const node_type_* root_node_ptr);
//	static const node_type_* get_inorder_end_node (const node_type_* root_node_ptr);
};

// 搜索二叉树中序遍历
template < class node_type_ >
class PFX_DATA_TEMPALE_API bst_inorder_iterator :
		public virtual cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS,
		public IPfx_decrease_iterator < node_type_ >
{
public:
	typedef bst_inorder_iterator < node_type_ > iterator_t;
	typedef typename cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS bst_interator_t;
public:
	bst_interator_t* begin ();
	bst_interator_t* end ();

	bst_interator_t* increase ();
	bst_interator_t* decrease ();
public:
	IPfx_decrease_iterator < node_type_ >*	decrease_iterator ();
	const node_type_*									get_current_element () const;
public:
	static const node_type_* get_inorder_begin_node (const node_type_* root_node_ptr);
	static const node_type_* get_inorder_end_node (const node_type_* root_node_ptr);
};

// 搜索二叉树前序遍历
template < class node_type_ >
class PFX_DATA_TEMPALE_API bst_preorder_iterator : 
	public virtual cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS
{
public:
	typedef bst_preorder_iterator < node_type_ > iterator_t;
	typedef typename cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS bst_interator_t;
protected:
	enum_t				m_next_node_type;
	result_t				m_last_result;
public:
	result_t init (const node_type_*	current_node_ptr,
		const node_type_*   root_node_ptr);
public:
	bst_interator_t* begin ();
	bst_interator_t* end ();

	bst_interator_t* increase ();
	bst_interator_t* decrease ();
public:
	static const node_type_* get_preorder_begin_node (const node_type_* root_node_ptr);
	static const node_type_* get_preorder_end_node (const node_type_* root_node_ptr);
};

// 搜索二叉树后序遍历
template < class node_type_ >
class PFX_DATA_TEMPALE_API bst_posorder_iterator :
	public virtual cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS
{
public:
	typedef bst_posorder_iterator < node_type_ > iterator_t;
	typedef typename cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS bst_interator_t;
public:
	bst_interator_t*					begin ();
	bst_interator_t*					reverse_begin ();
	bst_interator_t*					end ();

	bst_interator_t*					increase ();
	bst_interator_t*					decrease ();
public:
	static const node_type_*	get_posorder_begin_node (const node_type_* root_node_ptr);
	static const node_type_*	get_posorder_end_node (const node_type_* root_node_ptr);
	static const node_type_*	get_reverse_posorder_begin_node (const node_type_* root_node_ptr);
};

// 普通的搜索二叉树
template < class node_type_, class compare_two_node_ = pecker_value_compare_extern< node_type_ > >
class PFX_DATA_TEMPALE_API cbst
{
public:
	typedef node_type_					node_type_t;
	typedef node_type_*					node_type_ptr_t;
	typedef const node_type_*		const_node_type_ptr_t;
	typedef compare_two_node_	compare_two_node_t;
	typedef typename cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS bst_interator_t;
	typedef typename cbst PFX_CBST_TEMPLATE_PARAMS		cbst_t;
protected:
	node_type_* m_root_ptr;
public:
	cbst ();
	cbst (const cbst< node_type_, compare_two_node_ >* other_ptr) throw (result_t);
	virtual ~cbst();
public:
	virtual result_t			copy (const cbst_t* PARAM_IN other_bst);
	virtual result_t			copy_by_iterator (const cbst_t* PARAM_IN other_bst);
	virtual result_t			clear ();

	virtual PFX_INLINE node_type_*	new_node () {return new node_type_;};
	virtual	PFX_INLINE result_t				release_node (node_type_* PARAM_IN node_ptr) 
	{if (node_ptr) {delete node_ptr;return PFX_STATUS_OK;}return PFX_STATUS_INVALID_PARAMS;};

public:
	virtual bst_interator_t *					begin (bst_interator_t* PARAM_OUT iterator_) const;
	virtual bst_interator_t *					end (bst_interator_t * PARAM_OUT iterator_) const;
public:
	virtual bst_interator_t *					find (bst_interator_t * PARAM_OUT iterator_,
																			const node_type_* PARAM_IN key_node_ptr) const;

public:
	PFX_INLINE const node_type_*	find_by_item (const typename bst_node_member_reference_type< node_type_ >::item_type_t* PARAM_IN key_ptr) const;
	PFX_INLINE node_type_*				find_reference_by_item (const typename bst_node_member_reference_type< node_type_ >::item_type_t* PARAM_IN key_ptr);

	PFX_INLINE const node_type_*	find (const node_type_* PARAM_IN key_node_ptr) const;
	PFX_INLINE node_type_*				find_reference (const node_type_* PARAM_IN key_node_ptr);

	virtual const node_type_*				add (node_type_* PARAM_INOUT add_node_ptr,
																		result_t& PARAM_OUT status_);
	virtual node_type_*						remove (node_type_* PARAM_INOUT remove_node_ptr,
																		result_t& PARAM_OUT status_);
	const node_type_*							get_root () const;
public:
	static PFX_INLINE const node_type_* max_node (const node_type_* root_node_ptr, const node_type_* null_node_ptr = null);
	static PFX_INLINE const node_type_* min_node (const node_type_* root_node_ptr, const node_type_* null_node_ptr = null);

	static PFX_INLINE result_t init_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
		node_type_* PARAM_IN left_node_ptr = null,
		node_type_* PARAM_IN right_node_ptr = null,
		node_type_* PARAM_IN parent_node_ptr = null);

	static const node_type_* find_node (const node_type_* PARAM_IN key_node_ptr,
		const node_type_* PARAM_IN root_node_ptr);

	static const node_type_* find_near_node  (const node_type_* PARAM_IN key_node_ptr,
		const node_type_* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result);

	static const node_type_* find_node_by_item (const typename bst_node_member_reference_type< node_type_ >::item_type_t* PARAM_IN key_ptr,
		const node_type_* PARAM_IN root_node_ptr);

	static const node_type_* find_near_node_by_item  (const typename bst_node_member_reference_type< node_type_ >::item_type_t* PARAM_IN key_ptr,
		const node_type_* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result);

	static result_t add_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT add_node_ptr,
		node_type_*& PARAM_OUT added_node_ptr);

	static result_t remove_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		const node_type_* PARAM_IN null_node_ptr = null);


protected:
	static  node_type_* find_remove_replace_node (node_type_* PARAM_IN remove_node_ptr,
		node_type_*& PARAM_OUT sub_remove_node_ptr,
		const node_type_* PARAM_IN null_node_ptr = null);

	static result_t	remove_node_internal (node_type_*& PARAM_INOUT root_node_ptrptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		node_type_* PARAM_INOUT sub_remove_node_ptr,
		node_type_* PARAM_INOUT sub_remove_node_ref_ptr,
		const node_type_* PARAM_IN null_node_ptr = null);
	
};

// AVL树
template < class node_type_, class compare_two_node_ = pecker_value_compare_extern< node_type_ > >
class PFX_DATA_TEMPALE_API cavl_tree : public virtual cbst < node_type_,  compare_two_node_ >
{
public:
	typedef typename cavl_tree PFX_CBST_TEMPLATE_PARAMS cavl_bst_t;
public:
	cavl_tree (/*Iallocator_cpp* allocator = null*/);
	cavl_tree (const cbst_t* PARAM_IN other_ptr) throw (result_t);
	cavl_tree (const cavl_bst_t* PARAM_IN other_ptr) throw (result_t);
public:
	virtual const node_type_* add (node_type_* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT status_);
	virtual node_type_* remove (node_type_* PARAM_INOUT remove_node_ptr,
		result_t& PARAM_OUT status_);
	virtual result_t copy (const cbst_t* PARAM_IN other_bst_ptr);
	result_t copy (const cavl_bst_t * PARAM_IN other_bst_ptr);
public:
	static PFX_INLINE result_t init_avl_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
		node_type_* PARAM_IN left_node_ptr = null,
		node_type_* PARAM_IN right_node_ptr = null,
		node_type_* PARAM_IN parent_node_ptr = null);

	static PFX_INLINE nsize__t get_avl_height (const node_type_* PARAM_IN node_ptr);
	static PFX_INLINE nsize__t calculate_avl_height (const node_type_* PARAM_IN left_node_ptr,
		const node_type_* PARAM_IN right_node_ptr);
	static PFX_INLINE nsize__t calculate_avl_height (const node_type_* PARAM_IN node_ptr);
	static PFX_INLINE nsize__t calculate_avl_balance_value (const node_type_* PARAM_IN node_ptr);

	static const node_type_* add_avl_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT status_);

	static node_type_* remove_avl_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		result_t& PARAM_OUT status_);


protected:	
	static PFX_INLINE void update_avl_height (node_type_* PARAM_IN node_ptr);
	
	static PFX_INLINE node_type_* avl_rr_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_ll_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_lr_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_rl_rotate (node_type_* PARAM_INOUT node_ptr);

	static PFX_INLINE AVLTREE_ROTATE_t avl_single_rotate (nsize__t balance_value,
		node_type_* PARAM_INOUT node_ptr, node_type_* & PARAM_INOUT parent_ref_node_ptr);
	static PFX_INLINE result_t avl_update_insert_rotate (node_type_* & PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT begin_node_ptr);
	static PFX_INLINE result_t avl_update_fixed (node_type_* & PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT begin_node_ptr);

};


//黑红树
template < class node_type_, class compare_two_node_ = pecker_value_compare_extern< node_type_ > >
class PFX_DATA_TEMPALE_API crb_tree : public virtual cbst < node_type_,  compare_two_node_ >
{
public:
	typedef typename crb_tree PFX_CBST_TEMPLATE_PARAMS crb_bst_t;
public:
	crb_tree ();
	crb_tree (const cbst_t* PARAM_IN other_ptr) throw (result_t);
	crb_tree (const crb_bst_t* PARAM_IN other_ptr) throw (result_t);
public:
	virtual result_t copy (const cbst_t* PARAM_IN other_bst_ptr);
	result_t copy (const crb_bst_t * PARAM_IN other_bst_ptr);

	virtual const node_type_* add (node_type_* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT status_);
	virtual node_type_* remove (node_type_* PARAM_INOUT remove_node_ptr,
		result_t& PARAM_OUT status_);



public:
	static PFX_INLINE result_t init_rb_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
		node_type_* PARAM_IN left_node_ptr = null,
		node_type_* PARAM_IN right_node_ptr = null,
		node_type_* PARAM_IN parent_node_ptr = null);

	static const node_type_* add_rb_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT add_node_ptr,
		result_t& PARAM_OUT status_);

	static node_type_* remove_rb_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		result_t& PARAM_OUT status_);
protected:
	static PFX_INLINE	void  set_rbt_color_red (node_type_* PARAM_INOUT pnode);
	static PFX_INLINE	void  set_rbt_color_black (node_type_* PARAM_INOUT pnode);
	static PFX_INLINE	bool  is_rbt_color_red (node_type_* PARAM_INOUT pnode);
	static PFX_INLINE	bool  is_rbt_color_black (node_type_* PARAM_INOUT pnode);
	static PFX_INLINE void copy_tree_color (node_type_* PARAM_INOUT pdec_node,
		const node_type_* PARAM_IN psrc_node);

	static PFX_INLINE  void rbt_left_rotate (node_type_ *& PARAM_INOUT root_node_ptr, 
		node_type_ *	PARAM_INOUT sentinel_node_ptr,
		node_type_ *	PARAM_INOUT node_ptr);

	static PFX_INLINE void rbt_right_rotate (node_type_ *& PARAM_INOUT	root_node_ptr, 
		node_type_ *	PARAM_INOUT	sentinel_node_ptr,
		node_type_ *	PARAM_INOUT	node_ptr);

	static PFX_INLINE result_t rbt_add_rotate_fixup (node_type_ *& PARAM_INOUT root_node_ptr,
		node_type_*  PARAM_INOUT add_node_ptr);

	static PFX_INLINE result_t rbt_remove_rotate_fixup (node_type_ *& PARAM_INOUT root_ptr,
		node_type_*  PARAM_INOUT ref_node_ptr);


};
PECKER_END

#endif			//PFX_CBST_H_
