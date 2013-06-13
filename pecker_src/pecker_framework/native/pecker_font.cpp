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
	
pecker_font::pecker_font()
{

}

pecker_font::~pecker_font()
{

}

HResult pecker_font::create_font_buffer(HEnum create_mode /* = FONT_CREATE_BUFFER_DEFUALT_MODE */)
{
	return P_OK;
}

HResult pecker_font::release_font_buffer()
{
	return P_OK;
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
