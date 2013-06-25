/*
 * pecker_font.cpp
 *
 *  Created on: 2013-6-13
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_font.h"
#include "../../native/pecker_window_context.h"
#include "../../data/pecker_string_adapter.h"
PECKER_BEGIN
	
static pecker_critical_section g_LoadFT_cs;
static FT_Library  gFT_library = null;
pecker_font::pecker_font():_M_pref_render_device(null),_M_mode(FONT_CREATE_BUFFER_DEFUALT_MODE),_M_face(null)
{
	pecker_critical_lock lock_cs;
	lock_cs.lock(&g_LoadFT_cs);
	if (null == gFT_library)
	{
		FT_Init_FreeType( &gFT_library );
	}
	lock_cs.unlock();
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

HResult pecker_font::init_font(const char* font_name,nSize font_name_size,nSize nfont_width,nSize nfont_hegiht /* = 0 */,nSize npixel_width /* = 0 */,nSize npixel_height /* = 0 */)
{
	if (null == gFT_library)
	{
		pecker_critical_lock lock_cs;
		lock_cs.lock(&g_LoadFT_cs);
		if (null == gFT_library)
		{
			FT_Init_FreeType( &gFT_library );
		}
		lock_cs.unlock();
	}

	if (null == gFT_library)
	{
		return P_FAIL;
	}

	const FT_Byte* pfont_memery = null;
	FT_Long nfont_memery_size = 0;
	FT_Error ft_error = FT_New_Memory_Face(gFT_library,pfont_memery,nfont_memery_size,0,&_M_face);

	if (ft_error)
	{
		if (FT_Err_Unknown_File_Format == ft_error)
		{
			PECKER_LOG_ERR("pecker_font::init_font","FT_New_Memory_Face error! the font file could be opened and read,%s","...");
		}

		PECKER_LOG_ERR("pecker_font::init_font","FT_New_Memory_Face error! error code = %d",ft_error);
		return P_ERR;
	}

	pekcer_size dpi_size = pecker_program_apps::get_device_dpi();
	ft_error = FT_Set_Char_Size(
		_M_face,    /* handle to face object           */
		nfont_width*64,       /* char_width in 1/64th of points  */
		nfont_hegiht*64,   /* char_height in 1/64th of points */
		dpi_size.w,     /* horizontal device resolution    */
		dpi_size.h );   /* vertical device resolution      */
	

	if (ft_error)
	{

		PECKER_LOG_ERR("pecker_font::init_font","FT_Set_Char_Size error! error code = %d，(dpi w=%d，dpi h=%d)",ft_error,dpi_size.w,dpi_size.h);
		return P_ERR;
	}

	if (npixel_width > 0 || npixel_height > 0)
	{
		ft_error = FT_Set_Pixel_Sizes(
			_M_face,   /* handle to face object */
			npixel_width,      /* pixel_width           */
			npixel_height );   /* pixel_height          */

		if (ft_error)
		{
			PECKER_LOG_ERR("pecker_font::init_font","FT_Set_Pixel_Sizes error! error code = %d",ft_error);
			return P_ERR;
		}

		 //FT_ENCODING_GB2312
	}


	return P_OK;
}

HResult pecker_font::draw_bitmap(FT_Bitmap*  bitmap,FT_Int  x,FT_Int  y)
{
	return P_OK;
}

HResult pecker_font::draw_to_texture(font_text_info_node& nodeInfo)
{
	return P_OK;
}

Ulong pecker_font::get_char_code(const pecker_char_ascii* pstrtext,nSize text_length,HEnum hCharEncode,int &offset)
{
	return 0;
}

const font_text_info_node* pecker_font::text(const pecker_char_unicode* pstrtext,nSize text_length,Bool newtext /* = false */)
{
	const pecker_avltst_map_node(pecker_char_unicode,font_text_info_node)* pnode = _M_font_info_index.findnode(pstrtext,text_length);
	if (null != pnode)
	{
		return &(pnode->value);
	}


	FT_Error ft_error;
	ft_error = FT_Select_Charmap(_M_face, FT_ENCODING_UNICODE);

	if (ft_error)
	{
		PECKER_LOG_ERR("pecker_font::text","FT_Select_Charmap FT_ENCODING_UNICODE error! error code = %d",ft_error);
		return null;
	}

	font_text_info_node node_info;
	int pen_x = 0;
	int pen_y = 0;
	FT_GlyphSlot slot = _M_face->glyph;
	for (nINDEX i=0;i<text_length;++i)
	{
		/* load glyph image into the slot (erase previous one) */
		ft_error = FT_Load_Char( _M_face, pstrtext[i], FT_LOAD_RENDER );
		if ( ft_error )
		{
			PECKER_LOG_ERR("pecker_font::text","FT_Load_Char error! char = %X, error code = %d",((int)(pstrtext[i])&0xFFFF),ft_error);
			continue;
		}
		draw_bitmap(&(slot->bitmap),pen_x + slot->bitmap_left,pen_y-slot->bitmap_top);
		pen_x += slot->advance.x >> 6;
	}
	if (P_OK != draw_to_texture(node_info))
	{
		return null;
	}

	pecker_avltst_map_node(pecker_char_unicode,font_text_info_node)* pinsert_node = null;
	_M_font_info_index.insert(pstrtext,text_length,node_info,pinsert_node);

	if (pinsert_node)
	{
		return &(pinsert_node->value);
	}
	else
	{
		return null;
	}
}

const font_text_info_node* pecker_font::text(const pecker_char_ascii* pstrtext_a,HEnum hCharEncode, nSize buffer_length,Bool newtext /* = false */)
{
	const pecker_char_unicode* pstrtext = null;
	nSize text_length = 0;

	// 转unicode 字符
	pecker_string_unicode convert_str;
	HResult result_val = string_ascii_to_unicode_adapter::convert(pstrtext_a,buffer_length,convert_str);
	if (P_OK == result_val)
	{
		pstrtext = convert_str.get_data();
		text_length = convert_str.get_string_length();
	}
	else
	{
		return null;
	}


	const pecker_avltst_map_node(pecker_char_unicode,font_text_info_node)* pnode = _M_font_info_index.findnode(pstrtext,text_length);
	if (null != pnode)
	{
		return &(pnode->value);
	}


	FT_Error ft_error;
	ft_error = FT_Select_Charmap(_M_face, FT_ENCODING_UNICODE);

	font_text_info_node node_info;
	int pen_x = 0;
	int pen_y = 0;
	FT_GlyphSlot slot = _M_face->glyph;

	if (!ft_error)
	{
		int ioffset = 0;
		for (nINDEX i=0;i<text_length;++i)
		{
			Ulong charCode = get_char_code((pstrtext_a+ioffset),buffer_length-ioffset,hCharEncode,ioffset);
			/* load glyph image into the slot (erase previous one) */
			ft_error = FT_Load_Char( _M_face, charCode, FT_LOAD_RENDER );
			if ( ft_error )
			{
				PECKER_LOG_ERR("pecker_font::text","FT_Load_Char error! char = %X, error code = %d",((int)(pstrtext[i])&0xFFFF),ft_error);
				continue;
			}
			draw_bitmap(&(slot->bitmap),pen_x + slot->bitmap_left,pen_y-slot->bitmap_top);
			pen_x += slot->advance.x >> 6;
		}
	}
	else
	{
		ft_error = FT_Select_Charmap(_M_face, (FT_Encoding)hCharEncode);
		if (ft_error)
		{
			PECKER_LOG_ERR("pecker_font::text","FT_Select_Charmap FT_ENCODING_UNICODE error! error code = %d",ft_error);
			return null;
		}

		int ioffset = 0;
		for (nINDEX i=0;i<text_length;++i)
		{
			if (ioffset >= buffer_length)
			{
				break;
			}
			FT_ULong code_char = get_char_code(pstrtext_a+ioffset,buffer_length-ioffset,hCharEncode,ioffset);
			/* load glyph image into the slot (erase previous one) */
			ft_error = FT_Load_Char( _M_face, code_char , FT_LOAD_RENDER );
			if ( ft_error )
			{
				PECKER_LOG_ERR("pecker_font::text","FT_Load_Char error! char = %X, error code = %d",((int)(pstrtext[i])&0xFFFF),ft_error);
				continue;
			}
			draw_bitmap(&(slot->bitmap),pen_x + slot->bitmap_left,pen_y-slot->bitmap_top);
			pen_x += slot->advance.x >> 6;
		}
	}
	
	if (P_OK != draw_to_texture(node_info))
	{
		return null;
	}

	pecker_avltst_map_node(pecker_char_unicode,font_text_info_node)* pinsert_node = null;
	_M_font_info_index.insert(pstrtext,text_length,node_info,pinsert_node);

	if (pinsert_node)
	{
		return &(pinsert_node->value);
	}
	else
	{
		return null;
	}
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
