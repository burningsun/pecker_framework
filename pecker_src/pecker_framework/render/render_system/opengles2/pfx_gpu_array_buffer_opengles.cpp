/*
 * pfx_gpu_array_buffer_opengles.cpp
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_gpu_array_buffer_opengles.h"

PECKER_BEGIN

CPfx_gpu_array_buffer_opengles2::~CPfx_gpu_array_buffer_opengles2()
{
	;
}
	// 在显存中申请一块内存用于存放顶点
pfx_long_t CPfx_gpu_array_buffer_opengles2::create_buffer()
{
	return 0;
}
	// 绑定存放顶点的显存，并设置顶点类型
pfx_result_t CPfx_gpu_array_buffer_opengles2::bind_buffer (pfx_long_t tagbuffer,PFX_BUFFER_OBJECT_TYPE_t buffer_type)
{
	return 0;
}

	// 更新显存中的顶点数据
pfx_result_t CPfx_gpu_array_buffer_opengles2::update_buffer (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_)
{
	return 0;
}
	// 更新显存中一部分的顶点数据
pfx_result_t CPfx_gpu_array_buffer_opengles2::update_sub_buffer (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		pfx_index_t offset,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_)
{
	return 0;
}

	// 创建顶点缓冲对象
pfx_long_t CPfx_gpu_array_buffer_opengles2::create_buffer_object (PFX_BUFFER_OBJECT_TYPE_t buffer_type,
		PFX_BUFFER_USAGE_TYPE_t usage_type,
		const PFX_CONST_GRAM_BUFFER_t& PARAM_IN buffer_)
{
	return 0;
}
	
	// 删除顶点缓冲 
pfx_result_t CPfx_gpu_array_buffer_opengles2::delete_buffer(pfx_long_t tagbuffer)
{
	return 0;
}


pfx_result_t CPfx_gpu_array_buffer_opengles2::push_vertex_location (pfx_long_t vertex_loction)
{
	return 0;
}
pfx_result_t CPfx_gpu_array_buffer_opengles2::clear_vertex_location ()
{
	return 0;
}

pfx_result_t CPfx_gpu_array_buffer_opengles2::push_buffer_location (pfx_long_t vertex_loction)
{
	return 0;
}
pfx_result_t CPfx_gpu_array_buffer_opengles2::clear_buffer_location ()
{
	return 0;
}


PECKER_END

