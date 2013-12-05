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


PECKER_BEGIN

typedef struct st_pfx_color pfx_color_t;

struct st_pfx_color
{
	pfx_float_t m_red;
	pfx_float_t m_green;
	pfx_float_t m_blue;
	pfx_float_t m_alpha;
};

#define PFX_RGBA_BITS(R,G,B,A) ((((R)&0xFF)<<24)|(((G)&0xFF)<<16)|(((B)&0xFF)<<8)|((A)&0xFF))
PFX_INLINE pfx_color_t GET_COLOR_T (pfx_bitfield_t RGBA_)
{
	pfx_color_t COLOR_;
	COLOR_.m_red = (pfx_float_t) ( (RGBA_ & 0xFF000000) >> 24) / (pfx_float_t) (0xFF);
	COLOR_.m_green = (pfx_float_t) ( (RGBA_ & 0x00FF0000) >> 16) / (pfx_float_t) (0xFF);
	COLOR_.m_blue = (pfx_float_t) ( (RGBA_ & 0x0000FF00) >> 8) / (pfx_float_t) (0xFF);
	COLOR_.m_alpha = (pfx_float_t)  (RGBA_ & 0x000000FF)  / (pfx_float_t) (0xFF);
	return	 COLOR_;
}

typedef struct st_PIXEL_COLOR_FORMAT
{
	pfx_u8_t m_red_size;
	pfx_u8_t m_green_size;
	pfx_u8_t m_blue_size;
	pfx_u8_t m_alpha_size;
}PFX_PIXEL_COLOR_FORMAT_t;

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

PECKER_END

#endif			//PFX_RENDER_TYPE_H_
