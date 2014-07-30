/*
 * pfx_render_defs.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_DEFS_H_
#define		PFX_RENDER_DEFS_H_

#include "../pfx_defines.h"
#include "../include/util"
PECKER_BEGIN

typedef enum enumRENDER_SYSTEM_TYPE
{
	PFX_UNKOWN_RENDER_SYSTEM = 0,
	PFX_OPENGL_RENDER_SYSTEM,
	PFX_DIRECTX_RENDER_SYSTEM,
	//........................

	//
	PFX_RENDER_SYSTEM_TYPE_COUNT
}PFX_RENDER_SYSTEM_TYPE_t;

typedef enum enumDIRECTX_SUB_VERSION_TYPE
{
	PFX_DIRECTX9C_SUB_VERSION = 0,
	PFX_DIRECTX10_SUB_VERSION,
	PFX_DIRECTX11_SUB_VERSION,
	//..............................

	//
	DIRECTX_SUB_VERSION_COUNT
}DIRECTX_SUB_VERSION_TYPE_t;

typedef enum enumOPENGL_SUB_VERSION_TYPE
{
	PFX_OPENGLES2_SUB_VERSION = 0,
	PFX_OPENGLES3_SUB_VERSION,
	//..............................

	//
	OPENGL_SUB_VERSION_COUNT
}OPENGL_SUB_VERSION_TYPE_t;

typedef struct buffer_bits
{
	byte_t*				m_bits_ptr;
	usize__t			m_bytes_count;
}buffer_bits_t;

typedef struct  buffer_rect
{
	usize__t m_offset;
	usize__t m_size;
}buffer_rect_t;




PECKER_END

#endif			//PFX_RENDER_DEFS_H_
