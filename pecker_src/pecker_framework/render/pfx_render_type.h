/*
 * pfx_render_type.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_TYPE_H_
#define		PFX_RENDER_TYPE_H_

#include "../pfx_defines.h"
#include "../data/pfx_list.h"

PFX_C_EXTERN_BEGIN

typedef struct st_pfx_color pfx_color_t;

struct st_pfx_color
{
	pfx_float_t m_red;
	pfx_float_t m_green;
	pfx_float_t m_blue;
};

class render_reference_object
{
protected:
	pfx_handle_t m_pobejcet;
	render_reference_object* m_prev_node;
	render_reference_object* m_pnext_node;
protected:
	virtual pfx_handle_t create_object () {return null;};
	virtual void delete_object() {;};
public:
	render_reference_object ();
	render_reference_object (render_reference_object & PARAM_INOUT other_);
	render_reference_object (render_reference_object* PARAM_INOUT other_);

	virtual ~render_reference_object ();

	PFX_INLINE void copy_refernce (render_reference_object* PARAM_INOUT other_);
	PFX_INLINE void dispose();

	PFX_INLINE pfx_handle_t get_object() const;
	PFX_INLINE pfx_bool_t		is_reference () const;
	PFX_INLINE pfx_result_t	new_instance ();
};

PFX_INLINE pfx_handle_t render_reference_object ::get_object() const
{
	return m_pobejcet;
}
PFX_INLINE void render_reference_object::copy_refernce (render_reference_object* PARAM_INOUT other_)
{
	if (null == other_)
	{
		return;
	}
	else if (this != other_)
	{
		 dispose();
		render_reference_object* temp = null;
		render_reference_object* temp_this = this;
		PFX_INSERT_LIST_NODE_END (other_,temp_this,temp);
		m_pobejcet = other_->m_pobejcet;
	}
}
PFX_INLINE void render_reference_object::dispose()
{
	if (null == m_pnext_node && null == m_prev_node)
	{
		if (null != m_pobejcet)
		{
			delete_object();
		}
		m_pobejcet = null;
	}
	else
	{
		render_reference_object* tempbegin = null;
		render_reference_object* tempend = null;
		render_reference_object* temp_this = this;
		PFX_REMOVE_LIST_NODE (temp_this,tempbegin,tempend);
		m_pobejcet = null;
		m_pnext_node = null;
		m_prev_node = null;
	}
}
PFX_INLINE pfx_bool_t	render_reference_object::is_reference () const
{
	return (pfx_bool_t)(m_prev_node && m_pnext_node);
}
PFX_INLINE pfx_result_t	render_reference_object::new_instance ()
{
	dispose();
	m_pobejcet =  create_object ();
	if (null != m_pobejcet)
	{
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_MEM_LOW;
	}
}

//PFX_INLINE 

PFX_C_EXTERN_END

#endif			//PFX_RENDER_TYPE_H_
