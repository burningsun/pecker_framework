/*
 * pfx_renderdevice_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDERDEVICE_OPENGLES2_H_
#define		PFX_RENDERDEVICE_OPENGLES2_H_

#include "../pfx_renderdevice.h"

PFX_C_EXTERN_BEGIN



PFX_C_EXTERN_END

PECKER_BEGIN


class PFX_RENDER_SYSTEM_API CPfx_render_device_opengles2 : public Ipfx_render_device
{
public:
	virtual Ipfx_framebuffer*				new_framebuffer (pfx_result_t&		 PARAM_OUT status_);
	virtual Ipfx_shader*						new_shader_codes (pfx_result_t&		 PARAM_OUT status_);
	virtual Ipfx_shader_program*		new_shader_program (pfx_result_t& PARAM_OUT status_);
	virtual Ipfx_texture*						new_texture (pfx_result_t&					 PARAM_OUT status_);
	virtual Ipfx_gpu_array_buffer*	new_gpu_buffer (pfx_result_t&			 PARAM_OUT status_);

	virtual pfx_result_t release_framebuffer (Ipfx_framebuffer*					PARAM_INOUT release_object);
	virtual pfx_result_t release_shader_codes (Ipfx_shader*						PARAM_INOUT release_object);
	virtual pfx_result_t release_shader_program (Ipfx_shader_program*	PARAM_INOUT release_object);
	virtual pfx_result_t release_texture (Ipfx_texture*									PARAM_INOUT release_object);
	virtual pfx_result_t release_gpu_buffer (Ipfx_gpu_array_buffer*			PARAM_INOUT release_object);

	//////////////////////////////////////////////////////////////////////////

	virtual pfx_result_t init_render_device ();
	virtual pfx_result_t deinit_render_device ();

	virtual pfx_result_t begin_draw (Ipfx_framebuffer_operation* & PARAM_OUT operation_,
		pfx_enum_t mode_ = 0);

	virtual pfx_result_t end_draw (pfx_boolean_t flag = pfx_false);

	virtual pfx_result_t present (const pfx_handle_t PARAM_IN params_ = null);

	virtual pfx_result_t antialiasing_hint (pfx_enum_t target_, PFX_ANTIALIASLING_MODE_t mode_);
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t enable_state ();
	virtual pfx_result_t disable_state ();

	virtual pfx_result_t get_state (pfx_enum_t state_name_,pfx_32_bit_t& PARAM_OUT state_);
	virtual pfx_result_t get_state (pfx_enum_t state_name_,pfx_64bit_t&	PARAM_OUT state_);
	virtual pfx_result_t get_state (pfx_enum_t state_name_,pfx_128bit_t& PARAM_OUT state_);

	virtual PFX_RENDER_DRIVER_INFO_t get_render_driver_info () const;
	//////////////////////////////////////////////////////////////////////////
public:
	CPfx_render_device_opengles2();
	virtual ~CPfx_render_device_opengles2();
};

PECKER_END

#endif			//PFX_RENDERDEVICE_OPENGLES2_H_
