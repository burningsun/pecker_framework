/*
 * pecker_font.h
 *
 *  Created on: 2013-5-28
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_FONT_H_
#define PECKER_FONT_H_

#include "../CPeckerObject.h"
#include "../data/pecker_string.h"
#include "../render/render_system/pecker_texture.h"
#include "../render/render_system/pecker_render_device.h"
#include "pecker_thread.h"
#include <ft2build.h>
#include FT_FREETYPE_H

PECKER_BEGIN

struct font_text_info_node
{
	const pecker_char*				_M_text;
	nSize										_M_text_node;
	font_text_info_node*			_M_pNext_info_node;

	//
	//...........................
	nSize										_M_text_metrix_size[2];
	Float										_M_text_region[4];
	Ipecker_texture*					_M_ptexture;
};
	
enum FONT_CREATE_BUFFER_MODE
{
	FONT_CREATE_BUFFER_DEFUALT_MODE = 0,

	FONT_CREATE_BUFFER_MODE_COUNT
};

class pecker_font
{
private:
	pecker_critical_section _M_critical_section;
public:
	pecker_font();
	~pecker_font();
	HResult create_font_buffer(HEnum create_mode = FONT_CREATE_BUFFER_DEFUALT_MODE);
	HResult release_font_buffer();
	HResult init_font(const char* font_name,nSize font_name_size,nSize nfont_width,nSize nfont_hegiht);
	
	const font_text_info_node* text(const pecker_char* pstrtext,nSize text_length,Bool newtext = false);
	
	HResult lock(pecker_critical_lock* plock);
	HResult unlock();
};

PECKER_END


#endif /* PECKER_FONT_H_ */
