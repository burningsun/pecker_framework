/*
* pfx_text_pen.h
*
*  Created on: 2015-2-17
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_TEXT_PEN_H_
#define		PFX_TEXT_PEN_H_

#include "pfx_pen.h"
#include "pfx_fontcache.h"


PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN



PFX_Interface IPfx_text_pen : public IPfx_pen
{
	virtual ~IPfx_text_pen(){ ; }

	virtual IPfx_fontcache* select_fontcache(IPfx_fontcache* PARAM_INOUT fontcache_ptr) = 0;

	virtual result_t set_font(IPfx_font* PARAM_IN font_ptr) = 0;

	virtual result_t textout(
		const cstring_ascii_t& PARAM_IN strText,
		const pointf_t& PARAM_IN view_pos,
		const rect_size_t& PARAM_IN text_box_size) = 0;

	virtual result_t textout(
		const cstring_unicode_t& PARAM_IN strText,			
		const pointf_t& PARAM_IN view_pos,
		const rect_size_t& PARAM_IN text_box_size) = 0;

	virtual result_t ascii_textout(
		const char* PARAM_IN strText,
		usize__t strTextLen,
		const pointf_t& PARAM_IN view_pos,
		const rect_size_t& PARAM_IN text_box_size) = 0;
};


PECKER_END

#endif			//PFX_TEXT_PEN_H_
