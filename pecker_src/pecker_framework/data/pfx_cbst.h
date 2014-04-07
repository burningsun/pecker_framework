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
class PFX_DATA_TEMPALE_API pfx_cbst_iterator : public pfx_increase_iterator < node_type_ >
{
protected:
	const node_type_*	m_current_node_ptr;
	const node_type_*   m_root_node_ptr;
public:
	pfx_cbst_iterator ();
	~pfx_cbst_iterator();
public:
	const node_type_* get_current_node () const;
	const node_type_* get_root_node () const;

	virtual pfx_result_t init (const node_type_*	current_node_ptr,
								const node_type_*   root_node_ptr);

public:
	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* begin 
		(pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_INOUT 
		set_begin_iterator_ptr) const;
	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* end 		
		(pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* PARAM_INOUT 
		set_end_iterator_ptr) const;

	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* begin (){return null;}
	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* end (){return null;}

	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* increase () {return null;}
	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* decrease () {return null;}
public:
	virtual PFX_INLINE pfx_increase_iterator < node_type_ >*	increase_iterator () { return increase(); }
	virtual	PFX_INLINE const node_type_*									get_current_element () const { return get_current_node(); }
//public:
//	static const node_type_* get_inorder_begin_node (const node_type_* root_node_ptr);
//	static const node_type_* get_inorder_end_node (const node_type_* root_node_ptr);
};

// 搜索二叉树中序遍历
template < class node_type_ >
class PFX_DATA_TEMPALE_API pfx_inorder_iterator :
		public virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS,
		public pfx_decrease_iterator < node_type_ >
{
public:
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* begin ();
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* end ();

	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* increase ();
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* decrease ();
public:
	pfx_decrease_iterator < node_type_ >*	decrease_iterator ();
	const node_type_*									get_current_element () const;
public:
	static const node_type_* get_inorder_begin_node (const node_type_* root_node_ptr);
	static const node_type_* get_inorder_end_node (const node_type_* root_node_ptr);
};

// 搜索二叉树前序遍历
template < class node_type_ >
class PFX_DATA_TEMPALE_API pfx_preorder_iterator : 
	public virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS
{
protected:
	pfx_enum_t				m_next_node_type;
	pfx_result_t				m_last_result;
public:
	pfx_result_t init (const node_type_*	current_node_ptr,
		const node_type_*   root_node_ptr);
public:
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* begin ();
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* end ();

	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* increase ();
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* decrease ();
public:
	static const node_type_* get_preorder_begin_node (const node_type_* root_node_ptr);
	static const node_type_* get_preorder_end_node (const node_type_* root_node_ptr);
};

// 搜索二叉树后序遍历
template < class node_type_ >
class PFX_DATA_TEMPALE_API pfx_posorder_iterator :
	public virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS
{
public:
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* begin ();
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* reverse_begin ();
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* end ();

	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* increase ();
	pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS* decrease ();
public:
	static const node_type_* get_posorder_begin_node (const node_type_* root_node_ptr);
	static const node_type_* get_posorder_end_node (const node_type_* root_node_ptr);
	static const node_type_* get_reverse_posorder_begin_node (const node_type_* root_node_ptr);
};

template < class node_type_, class compare_two_node_ = pecker_value_compare_extern< node_type_ > >
class PFX_DATA_TEMPALE_API pfx_cbst
{
protected:
	node_type_* m_root_ptr;
	//Iallocator_cpp* m_allocator;
public:
	pfx_cbst (/*Iallocator_cpp* allocator = null*/);
	pfx_cbst (const pfx_cbst< node_type_, compare_two_node_ >* other_ptr) throw (pfx_result_t);
	virtual ~pfx_cbst();
public:
	virtual pfx_result_t copy (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst);
	virtual pfx_result_t copy_by_iterator (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst);
	virtual pfx_result_t clear ();

	virtual node_type_* new_node () {return new node_type_;};
	virtual	pfx_result_t release_node (node_type_* PARAM_IN node_ptr) 
	{if (node_ptr) {delete node_ptr;return PFX_STATUS_OK;}return PFX_STATUS_INVALID_PARAMS;};

public:
	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * begin (pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * PARAM_OUT iterator_) const;
	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * end (pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * PARAM_OUT iterator_) const;
public:
	virtual pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * find (pfx_cbst_iterator PFX_CBST_ITERATOR_TEMPLATE_PARAMS * PARAM_OUT iterator_,
		const node_type_* PARAM_IN key_node_ptr) const;

public:
	virtual const node_type_* find (const node_type_* PARAM_IN key_node_ptr) const;
	virtual node_type_* find_reference (const node_type_* PARAM_IN key_node_ptr);

	virtual const node_type_* add (node_type_* PARAM_INOUT add_node_ptr,
		pfx_result_t& PARAM_OUT status_);
	virtual node_type_* remove (node_type_* PARAM_INOUT remove_node_ptr,
		pfx_result_t& PARAM_OUT status_);
	const node_type_* get_root () const;
public:
	static PFX_INLINE const node_type_* max_node (const node_type_* root_node_ptr, const node_type_* null_node_ptr = null);
	static PFX_INLINE const node_type_* min_node (const node_type_* root_node_ptr, const node_type_* null_node_ptr = null);

	static PFX_INLINE pfx_result_t init_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
		node_type_* PARAM_IN left_node_ptr = null,
		node_type_* PARAM_IN right_node_ptr = null,
		node_type_* PARAM_IN parent_node_ptr = null);

	static const node_type_* find_node (const node_type_* PARAM_IN key_node_ptr,
		const node_type_* PARAM_IN root_node_ptr);

	static const node_type_* find_near_node  (const node_type_* PARAM_IN key_node_ptr,
		const node_type_* PARAM_IN root_node_ptr,
		int& PARAM_INOUT last_cmp_result);

	static pfx_result_t add_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT add_node_ptr,
		node_type_*& PARAM_OUT added_node_ptr);

	static pfx_result_t remove_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		const node_type_* PARAM_IN null_node_ptr = null);

protected:
	static  node_type_* find_remove_replace_node (node_type_* PARAM_IN remove_node_ptr,
		node_type_*& PARAM_OUT sub_remove_node_ptr,
		const node_type_* PARAM_IN null_node_ptr = null);

	//static  node_type_*
	static pfx_result_t	remove_node_internal (node_type_*& PARAM_INOUT root_node_ptrptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		node_type_* PARAM_INOUT sub_remove_node_ptr,
		node_type_* PARAM_INOUT sub_remove_node_ref_ptr,
		const node_type_* PARAM_IN null_node_ptr = null);
	
};

template < class node_type_, class compare_two_node_ = pecker_value_compare_extern< node_type_ > >
class PFX_DATA_TEMPALE_API pfx_cavl_tree : public virtual pfx_cbst < node_type_,  compare_two_node_ >
{
public:
	pfx_cavl_tree (/*Iallocator_cpp* allocator = null*/);
	pfx_cavl_tree (const pfx_cbst< node_type_,  compare_two_node_ >* PARAM_IN other_ptr) throw (pfx_result_t);
	pfx_cavl_tree (const pfx_cavl_tree < node_type_,  compare_two_node_ >* PARAM_IN other_ptr) throw (pfx_result_t);
public:
	const node_type_* add (node_type_* PARAM_INOUT add_node_ptr,
		pfx_result_t& PARAM_OUT status_);
	node_type_* remove (node_type_* PARAM_INOUT remove_node_ptr,
		pfx_result_t& PARAM_OUT status_);
	pfx_result_t copy (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst_ptr);
	pfx_result_t copy (const pfx_cavl_tree PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst_ptr);
public:
	static PFX_INLINE pfx_result_t init_avl_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
		node_type_* PARAM_IN left_node_ptr = null,
		node_type_* PARAM_IN right_node_ptr = null,
		node_type_* PARAM_IN parent_node_ptr = null);

	static PFX_INLINE pfx_nsize_t get_avl_height (const node_type_* PARAM_IN node_ptr);
	static PFX_INLINE pfx_nsize_t calculate_avl_height (const node_type_* PARAM_IN left_node_ptr,
		const node_type_* PARAM_IN right_node_ptr);
	static PFX_INLINE pfx_nsize_t calculate_avl_height (const node_type_* PARAM_IN node_ptr);
	static PFX_INLINE pfx_nsize_t calculate_avl_balance_value (const node_type_* PARAM_IN node_ptr);

	static const node_type_* add_avl_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT add_node_ptr,
		pfx_result_t& PARAM_OUT status_);

	static node_type_* remove_avl_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		pfx_result_t& PARAM_OUT status_);
protected:	
	static PFX_INLINE void update_avl_height (node_type_* PARAM_IN node_ptr);
	
	static PFX_INLINE node_type_* avl_rr_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_ll_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_lr_rotate (node_type_* PARAM_INOUT node_ptr);
	static PFX_INLINE node_type_* avl_rl_rotate (node_type_* PARAM_INOUT node_ptr);

	static PFX_INLINE AVLTREE_ROTATE_t avl_single_rotate (pfx_nsize_t balance_value,
		node_type_* PARAM_INOUT node_ptr, node_type_* & PARAM_INOUT parent_ref_node_ptr);
	
	static PFX_INLINE pfx_result_t avl_update_rotate (node_type_* & PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT begin_node_ptr);

};



template < class node_type_, class compare_two_node_ = pecker_value_compare_extern< node_type_ > >
class PFX_DATA_TEMPALE_API pfx_crb_tree : public virtual pfx_cbst < node_type_,  compare_two_node_ >
{
public:
	pfx_crb_tree (/*Iallocator_cpp* allocator = null*/);
	pfx_crb_tree (const pfx_cbst< node_type_,  compare_two_node_ >* PARAM_IN other_ptr) throw (pfx_result_t);
	pfx_crb_tree (const pfx_crb_tree< node_type_,  compare_two_node_ >* PARAM_IN other_ptr) throw (pfx_result_t);
public:
	pfx_result_t copy (const pfx_cbst PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst_ptr);
	pfx_result_t copy (const pfx_crb_tree PFX_CBST_TEMPLATE_PARAMS * PARAM_IN other_bst_ptr);

	const node_type_* add (node_type_* PARAM_INOUT add_node_ptr,
		pfx_result_t& PARAM_OUT status_);
	node_type_* remove (node_type_* PARAM_INOUT remove_node_ptr,
		pfx_result_t& PARAM_OUT status_);



public:
	static PFX_INLINE pfx_result_t init_rb_node_leaves (node_type_* PARAM_INOUT tree_node_ptr,
		node_type_* PARAM_IN left_node_ptr = null,
		node_type_* PARAM_IN right_node_ptr = null,
		node_type_* PARAM_IN parent_node_ptr = null);

	static const node_type_* add_rb_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT add_node_ptr,
		pfx_result_t& PARAM_OUT status_);

	static node_type_* remove_rb_node (node_type_*& PARAM_INOUT root_node_ptr,
		node_type_* PARAM_INOUT remove_node_ptr,
		pfx_result_t& PARAM_OUT status_);
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

	static PFX_INLINE pfx_result_t rbt_add_rotate_fixup (node_type_ *& PARAM_INOUT root_node_ptr,
		node_type_*  PARAM_INOUT add_node_ptr);

	static PFX_INLINE pfx_result_t rbt_remove_rotate_fixup (node_type_ *& PARAM_INOUT root_ptr,
		node_type_*  PARAM_INOUT ref_node_ptr);


};
PECKER_END

#endif			//PFX_CBST_H_
