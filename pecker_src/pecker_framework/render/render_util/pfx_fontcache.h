/*
* pfx_fontcache.h
*
*  Created on: 2015-2-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_FONTCACHE_H_
#define		PFX_FONTCACHE_H_

#include "pfx_font.h"
#include "../render_system/pfx_texture.h"
#include "../../data/pfx_carray.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

typedef struct st_fontcache_rect
{
	rect_sizef_t       m_font_rect;
	nsize__t           m_rank;
	double_t           m_last_tick;
	font_info_t        m_font_info;
	cstring_unicode_t  m_font_text;
}fontcache_rect_t;

typedef enum enumFONTCACHEMODE
{
   FONTCACHE_APPEND	= 0,
   FONTCACHE_LINE,

   FONT_CACHE_MODE_COUNT
}FONT_CACHE_MODE_t;

PFX_Interface IPfx_fontcache : public creference_root
{
	virtual ~IPfx_fontcache(){ ; }
	virtual result_t init(IPfx_texture* PARAM_INOUT cache_texture_ptr) = 0;
	virtual IPfx_texture* get_cache_texture() = 0;

	virtual result_t get_text_cache_pos(IPfx_array< fontcache_rect_t >* PARAM_OUT rect_ptr,
		const font_info_t& PARAM_IN font_info,
		const cstring_ascii_t& PARAM_IN strText) = 0;

	virtual result_t get_text_cache_pos(IPfx_array< fontcache_rect_t >* PARAM_OUT rect_ptr,
		const font_info_t& PARAM_IN font_info,
		const cstring_unicode_t& PARAM_IN strText) = 0;

	virtual result_t set_cache_font(IPfx_font* PARAM_IN font_ptr) = 0;
	virtual result_t clean_cache_font() = 0;
	virtual IPfx_font* get_cache_font(uindex_t idx = 0) = 0;
	virtual const IPfx_font* get_cache_font(uindex_t idx = 0) const = 0;

	// mode =  FONT_CACHE_MODE_t
	virtual result_t set_cache_mode(enum_int_t mode) = 0;
	virtual result_t save_cache_mode() = 0;
	virtual result_t restore_cache_mode() = 0;

	virtual result_t set_text_cache(const cstring_ascii_t& PARAM_IN strText) = 0;
	
	virtual result_t set_text_cache(const cstring_unicode_t& PARAM_IN strText) = 0;

	virtual result_t clean_text_cache(const fontcache_rect_t& PARAM_IN rect) = 0;
	virtual result_t clean() = 0;

	virtual IPfx_fontcache* new_share() = 0;

};

PECKER_END

#endif			//PFX_FONTCACHE_H_
