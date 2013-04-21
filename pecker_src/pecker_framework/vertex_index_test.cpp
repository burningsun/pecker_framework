#include "render/render_system/opengles/pecker_buffer_gl.h"
#include "render/render_system/opengles/pecker_shader_program_glsles1.h"
#include "render/render_system/opengles/pecker_texture_gl.h"
USING_PECKER_SDK

void vertex_test()
{
	pecker_vertex_buffer_gles2 vex_buf_gl;
	Ipecker_vertex_buffer* vex_buffer = &vex_buf_gl;
	pecker_opengles_v2_object* vex_buff_obj = &vex_buf_gl;


	pecker_index_buffer_gles2 index_buf_gl;
	Ipecker_index_buffer* index_buffer = &index_buf_gl;
	pecker_opengles_v2_object* index_buf_obj = &index_buf_gl;

	pecker_gpu_program_param_gles2 shader_program_params;
	pecker_shader_program_glsles1 shader_program;

	pecker_texture_2d_gles2 tex;

}