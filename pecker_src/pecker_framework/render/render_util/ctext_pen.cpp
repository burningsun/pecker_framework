/*
* ctext_pen.cpp
*
*  Created on: 2015-2-17
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#include "ctext_pen.h"

PECKER_BEGIN

ctext_pen::~ctext_pen()
{
	;
}

IPfx_fontcache* ctext_pen::select_fontcache(IPfx_fontcache* PARAM_INOUT fontcache_ptr)
{
	return null;
}

result_t ctext_pen::set_font(IPfx_font* PARAM_IN font_ptr)
{
	return PFX_STATUS_OK;
}

result_t ctext_pen::textout(
	const cstring_ascii_t& PARAM_IN strText,
	const pointf_t& PARAM_IN view_pos,
	const rect_size_t& PARAM_IN text_box_size)
{
	return PFX_STATUS_OK;
}

result_t ctext_pen::textout(
	const cstring_unicode_t& PARAM_IN strText,
	const pointf_t& PARAM_IN view_pos,
	const rect_size_t& PARAM_IN text_box_size)
{
	return PFX_STATUS_OK;
}

result_t ctext_pen::ascii_textout(
	const char* PARAM_IN strText,
	usize__t strTextLen,
	const pointf_t& PARAM_IN view_pos,
	const rect_size_t& PARAM_IN text_box_size)
{
	return PFX_STATUS_OK;
}
