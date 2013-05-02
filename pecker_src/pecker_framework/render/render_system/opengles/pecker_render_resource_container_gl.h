/*
 * pecker_render_resource_container_gl.h
 *
 *  Created on: 2013-4-21
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_RENDER_RESOURCE_CONTAINER_GL_H_
#define  PECKER_RENDER_RESOURCE_CONTAINER_GL_H_

#include "../../pecker_render_object.h"
#include "../../../native/pecker_allocator.h"
#include "pecker_shader_program_glsles1.h"
#include "pecker_buffer_gl.h"
#include "pecker_frame_buffer_gl.h"
#include "pecker_texture_gl.h"
#include "pecker_render_buffer_gl.h"

PECKER_BEGIN

typedef pecker_simple_allocator<HEnum> render_system_config_param_allocator_gles2;
typedef pecker_simple_allocator<HEnum*> render_system_config_param_pointer_allocator_gles2;
typedef pecker_simple_allocator<Byte> graphic_buffer_allocator_gles2;
typedef pecker_simple_allocator<Byte> texture_buffer_allocator_gles2;
//typedef pecker_simple_allocator<Byte> render_buffer_allocator;
typedef pecker_simple_allocator<pecker_shader_program_glsles1> gpu_program_allocator_gles2;
typedef pecker_simple_allocator<pecker_vertex_buffer_gles2> vertex_allocator_gles2;
typedef pecker_simple_allocator<pecker_index_buffer_gles2> index_allocator_gles2;
typedef pecker_simple_allocator<pecker_texture_2d_gles2> texture2d_allocator_gles2;
typedef pecker_simple_allocator<pecker_texture_cube_gles2> texture_cube_allocator_gles2;
typedef pecker_simple_allocator<pecker_color_buffer_gles2> colorbuffer_allocator_gles2;
typedef pecker_simple_allocator<pecker_depth_buffer_gles2> depthbuffer_allocator_gles2;
typedef pecker_simple_allocator<pecker_stencil_buffer_gles2> stencilbuffer_allocator_gles2;
typedef pecker_simple_allocator<pecker_frame_buffer_gles2> framebuffer_allocator_gles2;

PECKER_END

#endif //PECKER_RENDER_RESOURCE_CONTAINER_GL_H_