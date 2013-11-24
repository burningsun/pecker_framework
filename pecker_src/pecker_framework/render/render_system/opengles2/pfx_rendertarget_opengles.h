/*
 * pfx_rendertarget_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDERTARGET_OPENGLES2_H_
#define		PFX_RENDERTARGET_OPENGLES2_H_

#include "../pfx_rendertarget.h"

PECKER_BEGIN

class  CPfx_render_target_opengles2 : public pfx_render_target
{
public:
	CPfx_render_target_opengles2();
	CPfx_render_target_opengles2(pfx_usize_t width, pfx_usize_t height);
	virtual ~CPfx_render_target_opengles2();
};


PECKER_END

#endif			//PFX_RENDERTARGET_OPENGLES2_H_
