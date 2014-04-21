/*
 * pfx_share_object.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHARE_OBJECT_H_
#define		PFX_SHARE_OBJECT_H_

#include "pfx_data_traits.h"
#include "pfx_clist.h"

PECKER_BEGIN

template < class reference_object_handle >
class pfx_auto_release_object
{
private:
	reference_object_handle* m_reference_object_ptr;
public:
	pfx_auto_release_object ();
	pfx_auto_release_object (reference_object_handle* PARAM_INOUT reference_object_ptr);
	~pfx_auto_release_object ();
};

template < class reference_object_handle >
class pfx_share_object_base 
{
private:
	reference_object_handle m_reference_object_handle;

	pfx_share_object_base < reference_object_handle >* m_prev_object;
	pfx_share_object_base < reference_object_handle >* m_next_object;
private:
	friend pfx_clist_base < pfx_share_object_base < reference_object_handle > >;

	PFX_INLINE const pfx_share_object_base < reference_object_handle >* get_prev_node () const;
	PFX_INLINE const pfx_share_object_base < reference_object_handle >* get_next_node () const;
	PFX_INLINE void set_prev_node (pfx_share_object_base < reference_object_handle >* PARAM_IN node_ptr);
	PFX_INLINE void set_next_node (pfx_share_object_base < reference_object_handle >* PARAM_IN node_ptr);

protected:
	virtual pfx_result_t close_handle (reference_object_handle& handle_);
	virtual pfx_result_t create_handle ();
public:
	pfx_share_object_base ();
	pfx_share_object_base (pfx_share_object_base < reference_object_handle > PARAM_INOUT &other_object);
	~pfx_share_object_base();
public:
	pfx_result_t	bind_object (reference_object_handle PARAM_IN* del_obj);
	pfx_result_t	unbind_object ();
	pfx_bool_t		is_sharing_object ();
public:
	reference_object_handle get_reference_object () const;
	pfx_result_t	init_reference_object (const reference_object_handle& other_ptr);

	pfx_share_object_base < reference_object_handle >* share_object (pfx_share_object_base < reference_object_handle > PARAM_INOUT &other_object); 
};

PECKER_END

#endif			//PFX_SHARE_OBJECT_H_
