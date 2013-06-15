/*
 * pecker_font.cpp
 *
 *  Created on: 2013-6-13
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_font.h"
PECKER_BEGIN
	
pecker_font::pecker_font():_M_pref_render_device(null),_M_mode(FONT_CREATE_BUFFER_DEFUALT_MODE)
{

}

pecker_font::~pecker_font()
{
	pecker_font::release_font_buffer();
}

HResult pecker_font::new_font_buffer()
{
	if (_M_pref_render_device)
	{
		Ipecker_frame_buffer_object* pobject = _M_pref_render_device->create_frame_buffer_object(TEXTURE_BUFFER_TYPE,TEXTURE_2D_TYPE);
		Ipecker_texture2d* ptexture = dynamic_cast< Ipecker_texture2d* >(pobject);
		return _M_textures.push(ptexture);
	}
	else
	{
		return P_UNINIT;
	}
}

HResult pecker_font::delete_font_buffer()
{
	if (null != _M_pref_render_device && _M_textures.get_size() > 0)
	{
		Ipecker_texture2d** pptexture = _M_textures.get_end_reference();
		if (null != pptexture)
		{
			Ipecker_frame_buffer_object* pobject = dynamic_cast< Ipecker_frame_buffer_object* >(*pptexture);
			HResult result_value = _M_textures.pop();
			if (P_OK == result_value || P_SUCCESS == result_value)
			{
				result_value = _M_pref_render_device->release_frame_buffer_object(pobject);
			}
			return result_value;
		}
		else
		{
			return P_FAIL;
		}
	}
	else
	{
		return P_UNINIT;
	}
}

HResult pecker_font::create_font_buffer(Ipecker_render_device* pDevice, HEnum create_mode /* = FONT_CREATE_BUFFER_DEFUALT_MODE */)
{
	if (null == pDevice)
	{
		return P_INVALID_VALUE;
	}

	if (null != _M_pref_render_device && pDevice != _M_pref_render_device)
	{
		release_font_buffer();
	}

	_M_pref_render_device = pDevice;


	_M_mode = FONT_CREATE_BUFFER_DEFUALT_MODE;

	return new_font_buffer();
}

HResult pecker_font::release_font_buffer()
{
	nSize stacksize = _M_textures.get_size();
	if (null != _M_pref_render_device)
	{
		HResult result_value = P_OK;
		for (nINDEX i = 0; i<stacksize; ++i)
		{
			result_value = delete_font_buffer();
			if (P_OK != result_value)
			{
				break;
			}
		}
		return result_value;
	}
	else
	{
		_M_textures.clear();
		return P_UNINIT;
	}	
}

HResult pecker_font::init_font(const char* font_name,nSize font_name_size,nSize nfont_width,nSize nfont_hegiht)
{
	return P_OK;
}

const font_text_info_node* pecker_font::text(const pecker_char* pstrtext,nSize text_length,Bool newtext /* = false */)
{
	return P_OK;
}

HResult pecker_font::lock(pecker_critical_lock* plock)
{
	if (plock)
	{
		return plock->lock(&_M_critical_section);
	}
	else
	{
		return P_ERR;
	}
}

HResult pecker_font::unlock()
{
	return _M_critical_section.leave_critical_section();
}

PECKER_END
