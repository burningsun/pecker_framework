/*
 * pfx_shader_program_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHADER_PROGRAM_OPENGLES2_H_
#define		PFX_SHADER_PROGRAM_OPENGLES2_H_

#include "../pfx_shader_program.h"

PECKER_BEGIN

// shader 处理器
class PFX_RENDER_SYSTEM_API CPfx_shader_opengles2 : public  Ipfx_shader
{
public:
	virtual ~CPfx_shader_opengles2();

	virtual pfx_long_t create_shader (const pfx_string_t* PARAM_IN str_shader_codes,
		const char* str_func_enterpoint = "main",
		const char* str_detials = null);

	virtual pfx_result_t delete_shader ();

	virtual pfx_long_t get_shader_location ();

	virtual PFX_SHADER_TYPE_t get_type () const;
};

class PFX_RENDER_SYSTEM_API CPfx_shader_program_opengles2 : public Ipfx_shader_program
{
public:
	virtual ~CPfx_shader_program_opengles2();

	// 配置当前绑定的shader处理器的参数
	// 顶点参数
	virtual pfx_long_t get_vertex_attribute_location (//PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		pfx_result_t & PARAM_OUT result_);

	virtual pfx_result_t set_const_vertex_attribute (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_);

	virtual  pfx_result_t set_vertex_pointer (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		const PFX_CONST_GRAM_ARRAY_PARAMS_t& PARAM_IN gram_buffer_);

	virtual pfx_result_t set_const_vertex_attribute (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t attriute_name_location,
		pfx_unknown_shader_param_object_t object_,pfx_usize_t object_size_);

	virtual  pfx_result_t set_vertex_pointer (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t attriute_name_location,
		const PFX_CONST_GRAM_ARRAY_PARAMS_t& PARAM_IN gram_buffer_);

	virtual pfx_result_t enable_vertex_array (pfx_long_t tagVertex);
	virtual pfx_result_t disable_vertex_array (pfx_long_t tagVertex);

	virtual pfx_result_t draw_vertex_array (PFX_PRIMITIVE_MODE_t mode_,
		pfx_index_t fist_vertex_index,
		pfx_usize_t primitive_count);

	virtual pfx_result_t draw_vertex_element_array (PFX_PRIMITIVE_MODE_t mode_,
		const PFX_CONST_GRAM_ELEMENT_INDICES_PARAMS_t& indices);

	// UNIFORM 绘图常量参数
	virtual pfx_long_t get_uniform_location (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN uniform_name,
		pfx_result_t & PARAM_OUT result_);

	virtual pfx_result_t set_uniform (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name, 
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_);

	virtual pfx_result_t set_uniform (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t uniform_name_location,
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_);

	// shader 处理程序
	virtual pfx_result_t create_program (pfx_handle_t device_);
	virtual pfx_long_t link_program ();
	virtual pfx_result_t delete_program ();

	virtual pfx_result_t attach_shader (Ipfx_shader* PARAM_INOUT shader);
	
	
	virtual pfx_result_t begin_program ();
	virtual pfx_result_t end_program (pfx_boolean_t flush = pfx_true);
};



PECKER_END

#endif			//PFX_SHADER_PROGRAM_OPENGLES2_H_
