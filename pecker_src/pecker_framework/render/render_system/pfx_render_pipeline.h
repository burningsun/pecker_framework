/*
 * pfx_render_pipeline.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_PIPELINE_H_
#define		PFX_RENDER_PIPELINE_H_

#include "../../pfx_defines.h"

PECKER_BEGIN

PFX_Interface Ipfx_shader_program;
PFX_Interface Ipfx_shader_render_params;


PFX_Interface Ipfx_render_frame
{

};

PFX_Interface Ipfx_render_frame_list
{

};

typedef pfx_result_t (*delete_shader_params_callback) (Ipfx_shader_render_params* PARAM_INOUT params);



pfx_result_t insert_shader_program_to_pipeline (Ipfx_shader_render_params* PARAM_INOUT params,delete_shader_params_callback del_callback);

pfx_result_t run_pipeline ();

PECKER_END

#endif			//PFX_UTIL_H_
