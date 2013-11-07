/*
 * pfx_render_type.cpp
 *
 *  Created on: 2013-11.7
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_render_type.h"


render_reference_object::render_reference_object() : m_pnext_node(null),m_prev_node(null)
{
	m_pobejcet = create_object();
}

render_reference_object::render_reference_object(render_reference_object & PARAM_INOUT other_)
{
	if (this != &other_)
	{
		render_reference_object* temp = null;
		render_reference_object* temp_this = this;
		PFX_INSERT_LIST_NODE_END (&other_,temp_this,temp);
		m_pobejcet = other_.m_pobejcet;
	}
}

render_reference_object::render_reference_object(render_reference_object* PARAM_INOUT other_)
{
	if (null == other_)
	{
		m_pnext_node = null;
		m_prev_node = null;
		m_pobejcet = create_object();
	}
	else if (this != other_)
	{
		render_reference_object* temp = null;
		render_reference_object* temp_this = this;
		PFX_INSERT_LIST_NODE_END (other_,temp_this,temp);
		m_pobejcet = other_->m_pobejcet;
	}
}


render_reference_object::~render_reference_object ()
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
