/*
 * pfx_clist.h
 *
 *  Created on: 2013-12-17
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CLIST_H_
#define		PFX_CLIST_H_

#include "../pfx_defines.h"

PECKER_BEGIN

#define PFX_CLIST_TEMPLATE_DEFINES template < class node_type_ >
#define PFX_CLIST_TEMPLATE_PARAMS  < item_type_ >

template < class node_type_ >
class pfx_clist_base
{
protected:
	node_type_* m_first_node_ptr;
	node_type_* m_last_node_ptr;
public:
	pfx_clist_base ();
	virtual ~pfx_clist_base();

	virtual node_type_* new_node () = 0;
	virtual	pfx_result_t release_node (node_type_* PARAM_IN node_ptr) = 0;
public:
	pfx_result_t push_back (node_type_* PARAM_INOUT node_ptr);
	node_type_* pop_back ();

	pfx_result_t push_front (node_type_* PARAM_INOUT node_ptr);
	node_type_* pop_front ();

	const node_type_* begin_node () const;
	const node_type_* end_node () const;

	pfx_result_t dispose_list ();
	pfx_result_t clear_list ();

public:
	static pfx_result_t init_list_node (node_type_* PARAM_INOUT node_ptr);
	static const node_type_* insert_list_node_back (node_type_* PARAM_INOUT node_ptr,
		node_type_* PARAM_INOUT insert_node_ptr);
	static const node_type_* insert_list_node_front (node_type_* PARAM_INOUT node_ptr,
		node_type_* PARAM_INOUT insert_node_ptr);
	static const node_type_* remove_list_node (node_type_* PARAM_INOUT node_ptr);
	static const node_type_* get_first_list_node (const node_type_* PARAM_INOUT node_ptr);
	static const node_type_* get_last_list_node (const node_type_* PARAM_INOUT node_ptr);
	static pfx_bool_t is_first_list_node (const node_type_* PARAM_INOUT node_ptr);
	static pfx_bool_t is_last_list_node (const node_type_* PARAM_INOUT node_ptr);
};

template < class node_type_, typename node_allocator_ >
class pfx_clist : public virtual pfx_clist_base PFX_CLIST_TEMPLATE_PARAMS
{
private:
	node_allocator_* m_allocator;
public:
	pfx_clist (node_allocator_* PARAM_INOUT alloator = null);
public:
	virtual node_type_* new_node ();
	virtual	pfx_result_t release_node (node_type_* PARAM_IN node_ptr);
};

PECKER_END

#endif			//PFX_CLIST_H_
