/*
* pfx_freetypefont.cpp
*
*  Created on: 2015-2-17
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#include "pfx_freetypefont.h"
#include "../../native/pfx_log.h"

#ifdef CONFIG_LOG_FONT
#define FONT_LOG_INFO PECKER_LOG_INFO
#define FONT_LOG_ERR PECKER_LOG_ERR
#else
#define FONT_LOG_INFO(X,...)
#define FONT_LOG_ERR(X,...)
#endif

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

struct cfreetype_lib
{
	FT_Library m_lib;
	FT_Error   m_error;
	cfreetype_lib()
	{
		m_lib = null;
		m_error = FT_Init_FreeType(&m_lib);
	}
	~cfreetype_lib()
	{
		if (m_lib && !m_error)
		{
			FT_Done_FreeType(m_lib);
			m_lib = null;
		}

	}
};

static cfreetype_lib gFreeType_lib;


cfreetype_font::cfreetype_font() :m_face(null)
{
	const float_t lean = 0.0;
	m_italic_matrix.xx = 0x10000L;
	m_italic_matrix.xy = lean * 0x10000L;
	m_italic_matrix.yx = 0;
	m_italic_matrix.yy = 0x10000L;

	m_font_info.m_sizex = 0;
	m_font_info.m_sizey = 0;
	m_font_info.m_ptx_count = 0;
	m_font_info.m_pty_count = 0;
	m_font_info.m_render_dpix = 0;
	m_font_info.m_render_dpiy = 0;
	m_font_info.m_style.m_border_size = 0;
	m_font_info.m_style.m_angle_degree = 0;
	m_font_info.m_font_name.init_string("null", strlen("null"));
}

cfreetype_font::~cfreetype_font()
{
	dispose();
}

result_t cfreetype_font::init(const font_info_t& PARAM_IN font_info)
{
	RETURN_INVALID_BY_ACT_RESULT(gFreeType_lib.m_error || null == gFreeType_lib.m_lib,
		FONT_LOG_ERR("load freetype lib error, error code=%d", gFreeType_lib.m_error),
		PFX_STATUS_ERROR_);

	if (font_info_compare::compare(font_info, m_font_info))
	{
		FT_Face face = null;
		FT_Error error = FT_New_Face(gFreeType_lib.m_lib,
			font_info.m_font_name.get_string(), 0, &face);
		FT_Face old_face = m_face;

		RETURN_INVALID_BY_ACT_RESULT(error || null == face,
			FONT_LOG_ERR("FT_New_Face error, error code=%d", error),
			PFX_STATUS_ERROR_);

		error = FT_Set_Char_Size(face, 
			m_font_info.m_sizex * m_font_info.m_ptx_count,
			m_font_info.m_sizey * m_font_info.m_pty_count,
			m_font_info.m_render_dpix, 
			m_font_info.m_render_dpiy);

		if (error)
		{
			FONT_LOG_ERR("FT_Set_Char_Size(face, %d, %d, %d, %d) error, error code=%d",
				m_font_info.m_sizex * m_font_info.m_ptx_count,
				m_font_info.m_sizey * m_font_info.m_pty_count,
				m_font_info.m_render_dpix,
				m_font_info.m_render_dpiy,
				error);
			FT_Done_Face(face);
			return PFX_STATUS_ERROR_;
		}

		const float_t lean = DEGREE_TO_RAD(m_font_info.m_style.m_angle_degree);
		m_italic_matrix.xx = 0x10000L;
		m_italic_matrix.xy = lean * 0x10000L;
		m_italic_matrix.yx = 0;
		m_italic_matrix.yy = 0x10000L;
		FT_Set_Transform(face, &m_italic_matrix, 0);

		FT_GlyphSlot slot = face->glyph;
		if (slot && slot->format == FT_GLYPH_FORMAT_OUTLINE)
		{
			if (m_font_info.m_style.m_border_size > 0)
			{
				error = FT_Outline_Embolden(&slot->outline, m_font_info.m_style.m_border_size);
				if (error)
				{
					FONT_LOG_ERR("FT_Outline_Embolden error, error code=%d", error);
				}	
			}
			else
			{
				FONT_LOG_INFO("using defualt border size (%d)", m_font_info.m_style.m_border_size);
			}
		}
		else
		{
			FONT_LOG_INFO("FT_GlyphSlot format is not FT_GLYPH_FORMAT_OUTLINE (%d)", 
				slot->format);
		}
		
		
		m_face = face;
		if (old_face)
		{
			FT_Done_Face(old_face);
			old_face = null;
		}
	}

	return PFX_STATUS_OK;
}
result_t cfreetype_font::dispose()
{
	if (m_face)
	{
		FT_Done_Face(m_face);
		m_face = null;
	}
	return PFX_STATUS_OK;	
}

result_t cfreetype_font::render_char(ulong_t char_code,
	IPfx_renderchar* PARAM_IN render_char_ptr,
	coord_t x /*= -1*/, coord_t y /*= -1*/)
{
	RETURN_INVALID_RESULT(null == m_face,
		PFX_STATUS_UNINIT);

	RETURN_INVALID_RESULT(null == render_char_ptr,
		PFX_STATUS_INVALID_PARAMS);

	FT_GlyphSlot slot = m_face->glyph;
	RETURN_INVALID_RESULT(null == m_face,
		PFX_STATUS_ERROR_);

	FT_Error error = FT_Load_Char(m_face, char_code, FT_LOAD_RENDER);
	if (error)
	{
		FONT_LOG_ERR("FT_Load_Char error, error code=%d", error);
		return PFX_STATUS_ERROR_;
	}
	else 
	{
		image_bits img_bits;

		img_bits.m_width = slot->bitmap.width;
		img_bits.m_height = slot->bitmap.rows;
		img_bits.m_color_format = PFX_LUMINANCE_FMT;
		img_bits.m_stride = color_format_size<PFX_LUMINANCE_FMT>::SIZE();
		img_bits.m_bits_ptr = slot->bitmap.buffer;
		img_bits.m_bytes_count = img_bits.m_width *	img_bits.m_height;
		if (x < 0)
		{
			x = slot->bitmap_left;
		}
		if (y < 0)
		{
			y = slot->bitmap_top;
		}
		return render_char_ptr->draw_char(&img_bits, x, y);
	}
}

const font_info_t& cfreetype_font::get_font_info() const
{
	return m_font_info;
}




PECKER_END


