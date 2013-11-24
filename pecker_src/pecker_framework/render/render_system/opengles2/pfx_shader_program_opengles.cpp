/*
 * pfx_shader_program_opengles.cpp
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_shader_program_opengles.h"

PECKER_BEGIN



// shader 处理器

CPfx_shader_opengles2::~CPfx_shader_opengles2() 
{
	;
}

pfx_long_t CPfx_shader_opengles2::create_shader (const pfx_string_t* PARAM_IN str_shader_codes,
		const char* str_func_enterpoint /*= "main"*/,
		const char* str_detials /*= null*/)
{
	return 0;
}

pfx_result_t CPfx_shader_opengles2::delete_shader ()
{
	return 0;
}

pfx_long_t CPfx_shader_opengles2::get_shader_location ()
{
	return 0;
}

PFX_SHADER_TYPE_t CPfx_shader_opengles2::get_type () const
{
	return PFXST_SHADER_TYPE_COUNT;
}



CPfx_shader_program_opengles2::~CPfx_shader_program_opengles2()
{
	;
}

	// 配置当前绑定的shader处理器的参数
	// 顶点参数
pfx_long_t CPfx_shader_program_opengles2::get_vertex_attribute_location (//PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		pfx_result_t & PARAM_OUT result_)
{
	return 0;
}

pfx_result_t CPfx_shader_program_opengles2::set_const_vertex_attribute (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_)
{
	return 0;
}

 pfx_result_t CPfx_shader_program_opengles2::set_vertex_pointer (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		const PFX_CONST_GRAM_ARRAY_PARAMS_t& PARAM_IN gram_buffer_)
 {
	 return 0;
 }

pfx_result_t CPfx_shader_program_opengles2::set_const_vertex_attribute (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t attriute_name_location,
		pfx_unknown_shader_param_object_t object_,pfx_usize_t object_size_)
{
	return 0;
}

 pfx_result_t CPfx_shader_program_opengles2::set_vertex_pointer (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t attriute_name_location,
		const PFX_CONST_GRAM_ARRAY_PARAMS_t& PARAM_IN gram_buffer_)
 {
	 return 0;
 }

pfx_result_t CPfx_shader_program_opengles2::enable_vertex_array (pfx_long_t tagVertex)
{
	return 0;
}
pfx_result_t CPfx_shader_program_opengles2::disable_vertex_array (pfx_long_t tagVertex)
{
	return 0;
}

pfx_result_t CPfx_shader_program_opengles2::draw_vertex_array (PFX_PRIMITIVE_MODE_t mode_,
		pfx_index_t fist_vertex_index,
		pfx_usize_t primitive_count)
{
	return 0;
}

pfx_result_t CPfx_shader_program_opengles2::draw_vertex_element_array (PFX_PRIMITIVE_MODE_t mode_,
		const PFX_CONST_GRAM_ELEMENT_INDICES_PARAMS_t& indices)
{
	return 0;
}

	// UNIFORM 绘图常量参数
pfx_long_t CPfx_shader_program_opengles2::get_uniform_location (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN uniform_name,
		pfx_result_t & PARAM_OUT result_)
{
	return 0;
}

pfx_result_t CPfx_shader_program_opengles2::set_uniform (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name, 
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_)
{
	return 0;
}

pfx_result_t CPfx_shader_program_opengles2::set_uniform (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t uniform_name_location,
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_) 
{
	return 0;
}

	// shader 处理程序
pfx_result_t CPfx_shader_program_opengles2::create_program (pfx_handle_t device_)
{
	return 0;
}
pfx_long_t CPfx_shader_program_opengles2::link_program ()
{
	return 0;
}
pfx_result_t CPfx_shader_program_opengles2::delete_program ()
{
	return 0;
}

pfx_result_t CPfx_shader_program_opengles2::attach_shader (Ipfx_shader* PARAM_INOUT shader)
{
	return 0;
}
	
pfx_result_t CPfx_shader_program_opengles2::begin_program ()
{
	return 0;
}

pfx_result_t CPfx_shader_program_opengles2::end_program (pfx_boolean_t flush/* = pfx_true*/)
{
	return 0;
}




PECKER_END


