/*
 * pfx_renderdevice_opengles.cpp
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_renderdevice_opengles.h"

PFX_C_EXTERN_BEGIN



PFX_C_EXTERN_END

PECKER_BEGIN


CPfx_render_device_opengles2::CPfx_render_device_opengles2()
{
	;
}

CPfx_render_device_opengles2::~CPfx_render_device_opengles2()
{
	;
}

Ipfx_framebuffer*				CPfx_render_device_opengles2::new_framebuffer (pfx_result_t&		 PARAM_OUT status_)
{
	return null;
}
Ipfx_shader*						CPfx_render_device_opengles2::new_shader_codes (pfx_result_t&		 PARAM_OUT status_)
{
	return null;
}
Ipfx_shader_program*		CPfx_render_device_opengles2::new_shader_program (pfx_result_t& PARAM_OUT status_)
{
	return null;
}
Ipfx_texture*						CPfx_render_device_opengles2::new_texture (pfx_result_t&				 PARAM_OUT status_)
{
	return null;
}
Ipfx_gpu_array_buffer*	CPfx_render_device_opengles2::new_gpu_buffer (pfx_result_t&			 PARAM_OUT status_)
{
	return null;
}

pfx_result_t CPfx_render_device_opengles2::release_framebuffer (Ipfx_framebuffer*					PARAM_INOUT release_object)
{
	return 0;
}
pfx_result_t CPfx_render_device_opengles2::release_shader_codes (Ipfx_shader*						PARAM_INOUT release_object)
{
	return 0;
}
pfx_result_t CPfx_render_device_opengles2::release_shader_program (Ipfx_shader_program*	PARAM_INOUT release_object)
{
	return 0;
}
pfx_result_t CPfx_render_device_opengles2::release_texture (Ipfx_texture*									PARAM_INOUT release_object)
{
	return 0;
}
pfx_result_t CPfx_render_device_opengles2::release_gpu_buffer (Ipfx_gpu_array_buffer*			PARAM_INOUT release_object)
{
	return 0;
}

	//////////////////////////////////////////////////////////////////////////

pfx_result_t CPfx_render_device_opengles2::init_render_device ()
{
	return 0;
}
pfx_result_t CPfx_render_device_opengles2::deinit_render_device ()
{
	return 0;
}

pfx_result_t CPfx_render_device_opengles2::begin_draw (Ipfx_framebuffer_operation* & PARAM_OUT operation_,
		pfx_enum_t mode_/* = 0*/)
{
	return 0;
}

pfx_result_t CPfx_render_device_opengles2::end_draw (pfx_boolean_t flag /*= pfx_false*/)
{
	return 0;
}

pfx_result_t CPfx_render_device_opengles2::present (const pfx_handle_t PARAM_IN params_ /* = null */)
{
	return 0;
}

pfx_result_t CPfx_render_device_opengles2::antialiasing_hint (pfx_enum_t target_, PFX_ANTIALIASLING_MODE_t mode_)
{
	return 0;
}
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_render_device_opengles2::enable_state ()
{
	return 0;
}
pfx_result_t CPfx_render_device_opengles2::disable_state ()
{
	return 0;
}

pfx_result_t CPfx_render_device_opengles2::get_state (pfx_enum_t state_name_,pfx_32_bit_t& PARAM_OUT state_)
{
	return 0;
}
pfx_result_t CPfx_render_device_opengles2::get_state (pfx_enum_t state_name_,pfx_64bit_t&	PARAM_OUT state_)
{
	return 0;
}
pfx_result_t CPfx_render_device_opengles2::get_state (pfx_enum_t state_name_,pfx_128bit_t& PARAM_OUT state_)
{
	return 0;
}

PFX_RENDER_DRIVER_INFO_t CPfx_render_device_opengles2::get_render_driver_info () const
{
	 PFX_RENDER_DRIVER_INFO_t info_;
	 return info_;
};

PECKER_END


