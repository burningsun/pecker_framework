/*
 * pfx_rendertarget.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDERTARGET_H_
#define		PFX_RENDERTARGET_H_

#include "../../pfx_defines.h"
#include "../pfx_render_type.h"
#include "pfx_render_pipeline.h"
PFX_C_EXTERN_BEGIN

struct pfx_render_target
{
protected:
	pfx_usize_t		m_width;
	pfx_usize_t		m_height;
	pfx_long_t		m_target;
public:
	pfx_render_target(pfx_usize_t width, pfx_usize_t height):m_width(width),m_height(height){;} 
	virtual ~pfx_render_target(){;}

	inline pfx_usize_t	get_width () const
	{
		return m_width;
	}
	inline pfx_usize_t	get_height () const
	{
		return m_height;
	}
	inline pfx_long_t	get_target () const
	{
		return m_target;
	}

	inline pfx_result_t using_render_params (
		Ipfx_shader_render_params* PARAM_INOUT program_params_,
		delete_shader_params_callback del_call_back = null)
	{
		RETURN_INVALID_RESULT ((null == program_params_),PFX_STATUS_INVALID_PARAMS);
		return insert_shader_program_to_pipeline_unsafe (program_params_,del_call_back);
	}

	//inline pfx_result_t using_shader_program (Ipfx_shader_program* PARAM_INOUT program_,
	//	Ipfx_shader_render_params* PARAM_INOUT program_params_,
	//	delete_shader_params_callback del_call_back = null)
	//{
	//	pfx_result_t status;
	//	RETURN_INVALID_RESULT ((null == program_params_),PFX_STATUS_INVALID_PARAMS);
	//	status = program_params_->bind_render_program(program_);
	//	RETURN_INVALID_RESULT ((PFX_STATUS_OK != status),PFX_STATUS_FAIL);
	//	return insert_shader_program_to_pipeline_unsafe (program_params_,del_call_back);
	//}
	virtual pfx_result_t bind_render_target () = 0;
	virtual pfx_result_t unbind_render_target () = 0;
}
//typedef struct 	st_pfx_render_target pfx_render_target_t;
//
//struct st_pfx_render_target
//{
//	pfx_usize_t		m_width;
//	pfx_usize_t		m_height;
//	pfx_long_t		m_target;
//
//	pfx_result_t	(*use_render_program) (pfx_render_target_t* target,pfx_long_t program_id);
//	pfx_result_t	(*clear_frame) (pfx_render_target_t* target,pfx_bitfield_t clear_mask, 
//		pfx_color_t color,pfx_float_t depth_value,pfx_bitfield_t stencil_mask);
//};
//
//PFX_C_EXTERN_END

#endif			//PFX_UTIL_H_
