/*
* pfx_freetypefont.h
*
*  Created on:  2015-2-17
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_FREETYPEFONT_H_
#define		PFX_FREETYPEFONT_H_

#include "pfx_font.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

class cfreetype_font : public IPfx_font
{
private:
	FT_Face       m_face;
	FT_Matrix     m_italic_matrix;
	font_info_t   m_font_info;
protected:
	virtual PFX_INLINE FT_Face& get_face()
	{
		return m_face;
	}
public:
	cfreetype_font();
	virtual ~cfreetype_font();

	virtual result_t init(const font_info_t& PARAM_IN font_info);
	virtual result_t dispose();

	virtual result_t render_char(ulong_t char_code, 
		IPfx_renderchar* PARAM_IN render_char_ptr, 
		coord_t x = -1, coord_t y = -1);

	virtual const font_info_t& get_font_info() const;

};


PECKER_END

#endif			//PFX_FONT_H_
