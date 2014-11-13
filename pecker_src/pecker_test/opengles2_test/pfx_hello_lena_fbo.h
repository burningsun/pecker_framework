/*
 * pfx_hello_lena_fbo.h
 *
 *  Created on: 2014-11-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_opengles2_def.h"
#include "../../pecker_framework/render/pfx_image_png.h"
#include "../../pecker_framework/render/render_system/opengles2/pfx_texture_gles.h"
#include "../../pecker_framework/math/pfx_math.h"

#ifndef PFX_HELLO_LENA_FBO_H_
#define PFX_HELLO_LENA_FBO_H_



extern result_t load_img(const char_t* pfile_name, image_data_t& __img);
extern result_t load_png_img(const char_t* pfile_name, cImage& __img);
extern sImage_t* load_png_img(const char_t* pfile_name);
extern void math_matrix_test();

class chello_lena_fbo_view_gles2 : public 	opengles2_activity_t::IOnRenderView_t
{
	typedef struct pos_clr
	{
		vector4f_t	m_postion;
		vector2f_t	m_img_pos;
	}pos_texpos_t;
private:
	SIMD_MATRIX4F(m_subview_mat_LH);
	SIMD_MATRIX4F(m_subproj_mat_LH);
	SIMD_MATRIX4F(m_subview_mat_RH);
	SIMD_MATRIX4F(m_subproj_mat_RH);

	SIMD_MATRIX4F(m_view_mat_LH);
	SIMD_MATRIX4F(m_proj_mat_LH);
	SIMD_MATRIX4F(m_view_mat_RH);
	SIMD_MATRIX4F(m_proj_mat_RH);


	cshader_program_gles2*			m_program_ptr;
	cvertex_cache_buffer_gles2* 	m_vertexattbi_buffer_ptr;
	cbuffer_object_gles2*			m_vertexbufferobject_ptr;
	image_data_t m_img;
	cImage m_cimg;
	GLuint m_texture2D;
	ctexture_surface* m_tex_surface_ptr;
	ctexture2D_gles2*  m_texture2d_ptr;
	cframebuffer_gles2* m_framebuffer_ptr;
	float_t m_rotateZ;
	

public:
	chello_lena_fbo_view_gles2() :m_texture2D(0), m_vertexattbi_buffer_ptr(null),
		m_vertexbufferobject_ptr(null), m_program_ptr(null), 
		m_tex_surface_ptr(null), m_texture2d_ptr(null), m_rotateZ(0.0),
		m_framebuffer_ptr(null)
	{
		;
	}
	virtual ~chello_lena_fbo_view_gles2()
	{
		if (m_vertexattbi_buffer_ptr)
		{
			m_vertexattbi_buffer_ptr->dispose_vertex();
			m_vertexattbi_buffer_ptr = null;
		}

		if (m_vertexbufferobject_ptr)
		{
			m_vertexbufferobject_ptr->dispose_buffer();
			m_vertexbufferobject_ptr = null;
		}

		if (m_program_ptr)
		{
			m_program_ptr->dispose_program();
			m_program_ptr = null;
		}

		if (m_tex_surface_ptr)
		{
			m_tex_surface_ptr->dispose_object();
			m_tex_surface_ptr = null;
		}

		if (m_texture2d_ptr)
		{
			m_texture2d_ptr->dispose_texture();
			m_texture2d_ptr = null;
		}


	}

	virtual void on_view(
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state,
		u64_t	__escape_time,
		u64_t   __last_frame_render_time,
		const viewport_rect_t& view_port,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr)
	{
		static float_t red_channel = 0.7f;



		red_channel += 0.01f;
		if (red_channel > 1)
		{
			red_channel = 0;
		}

		
		result_t status;
		status = __state.select_program(m_program_ptr);
		if (PFX_STATUS_OK > status)
		{
			__state.revert_select_program();
			return;
		}


		if (null == m_framebuffer_ptr)
		{
			m_framebuffer_ptr = __state.create_framebuffer();
		}

		if (null == m_framebuffer_ptr)
		{
			return;
		}

		status = m_framebuffer_ptr->bind();
		if (PFX_STATUS_OK > status)
		{
			status = m_framebuffer_ptr->create_rendertarget(512, 512);
		}

		if (PFX_STATUS_OK > status)
		{
			return;
		}

		__state.set_viewport(viewport_rect_t(0, 0, 512, 512));

		const char* chr_name;
		chr_name = "aPosition";
		long_t pos = m_program_ptr->get_location_by_name(chr_name);
		
		chr_name = "aTexCoord";
		long_t texcoord = m_program_ptr->get_location_by_name(chr_name);
		
		chr_name = "uFixedViewMatrix";
		long_t mat = m_program_ptr->get_location_by_name(chr_name);
		
		chr_name = "sTexture";
		long_t tex = m_program_ptr->get_location_by_name(chr_name);

		SIMD_MATRIX4F(mvp);
		SIMD_MATRIX4F(mvp_pro);
		SIMD_MATRIX4F(mvp_tmp[4]);
		SIMD_MATRIX4F(mvp__);

		matrix_dot_unsafe_std_t::mul(mvp_pro, m_subproj_mat_LH, m_subview_mat_LH);
		//
		matrix_set_unsafe_std_t::mat4x4_rotateY_col_major(mvp_tmp[2], m_rotateZ);
		matrix_set_unsafe_std_t::mat4x4_rotateZ_col_major(mvp_tmp[2], m_rotateZ);
		matrix_set_unsafe_std_t::mat4x4_translate_col_major(mvp_tmp[1], 0.5, 0.5, 0.0);
		matrix_set_unsafe_std_t::mat4x4_rotateX_col_major(mvp_tmp[0], m_rotateZ);
		matrix_set_unsafe_std_t::mat4x4_rotateZ_col_major(mvp_tmp[0], m_rotateZ);

		m_rotateZ += 0.1f;
		if (m_rotateZ > 6.28f)
		{
			m_rotateZ -= 6.28f;
		}
		matrix_dot_unsafe_std_t::mul(mvp__, mvp_tmp, 2);
		matrix_dot_unsafe_std_t::mul(mvp, mvp__, mvp_pro);

		if (null == m_tex_surface_ptr)
		{
			m_tex_surface_ptr = __state.create_texture_surface();
		}

		if (null == m_tex_surface_ptr)
		{
			return;
		}

		if (null == m_texture2d_ptr)
		{
			m_texture2d_ptr = __state.create_texture2D();
		}

		if (null == m_texture2d_ptr)
		{
			return;
		}


		__state.set_uniform_attri(mat, (matrix4f_t&)mvp);

		if (!m_vertexbufferobject_ptr)
		{
			m_vertexbufferobject_ptr = __state.create_buffer();
			m_vertexbufferobject_ptr->set_vbo_buffer(m_vertexattbi_buffer_ptr);
		}
		__state.set_vertex_attrib_array(pos, m_vertexbufferobject_ptr, 4);
		__state.set_vertex_attrib_array(texcoord, m_vertexbufferobject_ptr, 4, 0, sizeof(vector4f_t));

		if (0 == m_tex_surface_ptr->get_max_miplevel())
		{
#if (OS_CONFIG == OS_WINDOWS)
			const char* lena_path = "test_res\\lena_rgba.png";
#else
			const char* lena_path = "test_res/lena_rgba.png";
#endif //#if (OS_CONFIG == OS_WINDOWS)
			sImage_t* img_ptr = load_png_img(lena_path);
			m_tex_surface_ptr->update_image(img_ptr, PFX_RGBA_FMT);
			img_ptr->dispose_object();

			m_texture2d_ptr->update_surface(m_tex_surface_ptr);
			m_texture2d_ptr->set_texture_filter(PFX_TRN_MIN_FILTER, PFX_TP_NEAREST);
			m_texture2d_ptr->set_texture_filter(PFX_TRN_MAG_FILTER, PFX_TP_NEAREST);
		}

		__state.clear_color(red_channel, 0.2f, 0.7f, 1.0f);
		__state.set_clear_mask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		::glEnable(GL_BLEND);
		::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_texture2d_ptr->bind();
		__state.set_texture(tex, m_texture2d_ptr, 0);
		__state.gl_draw_arrays(GL_TRIANGLE_STRIP, 0, 4);

		matrix_dot_unsafe_std_t::mul(mvp_pro, m_subproj_mat_RH, m_subview_mat_RH);
		matrix_dot_unsafe_std_t::mul(mvp, mvp__, mvp_pro);

		__state.set_uniform_attri(mat, (matrix4f_t&)mvp);
		__state.gl_draw_arrays(GL_TRIANGLE_STRIP, 0, 4);

		__state.unbind_buffer(pos);
		__state.unbind_buffer(texcoord);

		IPfx_texture* tex_ptr = null;
		if (m_framebuffer_ptr)
		{
			tex_ptr = m_framebuffer_ptr->get_texture(PFX_COLOR_BUFFER_FMT, 0);
		}

		__state.use_system_framebuffer();
		__state.set_viewport(view_port);
		__state.clear_color(0.5f, 0.2f, 0.7f, 1.0f);
		__state.set_clear_mask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		::glEnable(GL_BLEND);
		::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		


		
		if (tex_ptr)
		{
			matrix_dot_unsafe_std_t::mul(mvp_pro, m_proj_mat_LH, m_view_mat_LH);
			matrix_dot_unsafe_std_t::mul(mvp, mvp__, mvp_pro);
			__state.set_uniform_attri(mat, (matrix4f_t&)mvp);
			__state.set_vertex_attrib_array(pos, m_vertexbufferobject_ptr, 4);
			__state.set_vertex_attrib_array(texcoord, m_vertexbufferobject_ptr, 4, 0, sizeof(vector4f_t));
			__state.set_texture(tex, tex_ptr, 2);
			__state.gl_draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
			__state.unbind_buffer(pos);
			__state.unbind_buffer(texcoord);
			tex_ptr->dispose();
			tex_ptr = null;
		}

	}

	virtual void on_load(
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state,
		u64_t	__escape_time,
		const viewport_rect_t& view_port,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr)
	{
		PECKER_LOG_INFO("on_load escape time = %lld",__escape_time);

		math_matrix_test();

		shader_souce_string_t __sys_shader_source;
		cshader_gles2* __vs_ptr = __state.create_shader(PFXST_VERTEXT_SHADER);
		cshader_gles2* __fs_ptr = __state.create_shader(PFXST_PIXEL_SHADER);
		result_t status;

		get_system_defualt_shader_source(__sys_shader_source,
			POSITION_TEXTCOORD_MVP_SHADER_SOURCE,
			SSS_MEDIUEM_FLOAT);

		FOR_ONE_LOOP_BEGIN
			
		BREAK_LOOP_CONDITION_SETS(!__sys_shader_source.m_str_fragment_shader ||
			!__sys_shader_source.m_str_vertext_shader, status, PFX_STATUS_INVALID_VALUE);

		__vs_ptr->compile_shader(__sys_shader_source.m_str_vertext_shader->get_string(), 
			__sys_shader_source.m_str_vertext_shader->get_length(), 
			status);

		BREAK_LOOP_CONDITION(PFX_STATUS_OK > status);

		__fs_ptr->compile_shader(__sys_shader_source.m_str_fragment_shader->get_string(), 
			__sys_shader_source.m_str_fragment_shader->get_length(), 
			status);

		BREAK_LOOP_CONDITION(PFX_STATUS_OK > status);

		if (null == m_program_ptr)
		{
			m_program_ptr = __state.create_program();
		}
		m_program_ptr->attach_shader(__vs_ptr);
		m_program_ptr->attach_shader(__fs_ptr);
		status = m_program_ptr->compile_program();

		__vs_ptr->dispose_shader();
		__fs_ptr->dispose_shader();

		__vs_ptr = null;
		__fs_ptr = null;

		VECTOR3F_t vecPos = { 0.0, 0.0, 2.0 };
		VECTOR3F_t vecLookAt = { 0.0, 0.0, 0.0 };
		VECTOR3F_t vecUp = { 0.0, 1.0, 0.0 };
	    matrix_set_unsafe_std_t::mat4x4_LookAtRH_col_major(m_subview_mat_RH, vecPos, vecLookAt, vecUp);
		matrix_set_unsafe_std_t::mat4x4_LookAtLH_col_major(m_subview_mat_LH, vecPos, vecLookAt, vecUp);

		matrix_set_unsafe_std_t::mat4x4_perspectiveRH_opengl(m_subproj_mat_RH,
			1.0, 1.0, 1.0, 100.0);

		matrix_set_unsafe_std_t::mat4x4_perspectiveLH_opengl(m_subproj_mat_LH,
			1.0, 1.0, 1.0, 100.0);

		matrix_set_unsafe_std_t::mat4x4_LookAtRH_col_major(m_view_mat_RH, vecPos, vecLookAt, vecUp);
		matrix_set_unsafe_std_t::mat4x4_LookAtLH_col_major(m_view_mat_LH, vecPos, vecLookAt, vecUp);

		matrix_set_unsafe_std_t::mat4x4_perspectiveRH_opengl(m_proj_mat_RH,
			(float_t)view_port.m_width / (float_t)view_port.m_height, 1.0, 1.0, 100.0);

		matrix_set_unsafe_std_t::mat4x4_perspectiveLH_opengl(m_proj_mat_LH,
			(float_t)view_port.m_width / (float_t)view_port.m_height, 1.0, 1.0, 100.0);


		FOR_ONE_LOOP_END;
	}

	virtual void on_render_complete(
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state,
		result_t status)
	{
		
		;
	}

	virtual void on_closing_render_device(
		u64_t	__escape_time,
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state)
	{
		PECKER_LOG_INFO("on_closing_render_device escape time = %lld",__escape_time);
		if (m_program_ptr)
		{
			m_program_ptr->dispose_program();
			m_program_ptr = null;
		}
		PECKER_LOG_INFO("m_program.release_reference()(%lld)",__escape_time);

		if (m_texture2D)
		{
			glDeleteTextures(1, &m_texture2D);
			m_texture2D = 0;
		}

		if (m_vertexbufferobject_ptr)
		{
			m_vertexbufferobject_ptr->dispose_buffer();
			m_vertexbufferobject_ptr = null;
		}

		if (m_texture2d_ptr)
		{
			m_texture2d_ptr->dispose_render_target();
		}
		
		if (m_framebuffer_ptr)
		{
			m_framebuffer_ptr->dispose_render_target();
		}

		
	}


	
	virtual void on_init(window_contex_t& PARAM_OUT win_context)
	{
		opengles2_activity_t::IOnRenderView_t::on_init(win_context);
		if (null == m_vertexattbi_buffer_ptr)
		{
			m_vertexattbi_buffer_ptr = cvertex_cache_buffer_gles2::create_cache_buffer(PFXVB_FLOAT, sizeof(pos_texpos_t), 4);
		}
		if (null == m_vertexattbi_buffer_ptr)
		{
			PECKER_LOG_ERR("cvertex_cache_buffer_gles2::create_cache_buffer == null,%s", "...");
			return;
		}
		
		buffer_bits_t lock_buffer_bits;
		result_t status;
		status = m_vertexattbi_buffer_ptr->lock_cache_buffer(lock_buffer_bits);
		PECKER_LOG_INFO("m_vertexattbi_buffer.lock_cache_buffer status = %d", status);
		if (PFX_STATUS_OK == status)
		{
			pos_texpos_t* vex_attrib_ptr = (pos_texpos_t*)lock_buffer_bits.m_bits_ptr;
			usize__t vex_count = lock_buffer_bits.m_bytes_count / sizeof(pos_texpos_t);
			if (vex_attrib_ptr && vex_count)
			{
				vex_attrib_ptr[0].m_postion = cvector4f_t(-0.5f, -0.5f, 0.0f, 1.0f).reference(); // pos
				vex_attrib_ptr[0].m_img_pos = cvector2f_t(0.0f, 0.0f).reference(); // rgba

				vex_attrib_ptr[1].m_postion = cvector4f_t(-0.5f, 0.5f, 0.0f, 1.0f).reference(); // pos
				vex_attrib_ptr[1].m_img_pos = cvector2f_t(0.0f, 1.0f).reference(); // rgba

				vex_attrib_ptr[2].m_postion = cvector4f_t(0.5f, -0.5f, 0.0f, 1.0f).reference(); // pos
				vex_attrib_ptr[2].m_img_pos = cvector2f_t(1.0f, 0.0f).reference(); // rgba

				vex_attrib_ptr[3].m_postion = cvector4f_t(0.5f, 0.5f, 0.0f, 1.0f).reference(); // pos
				vex_attrib_ptr[3].m_img_pos = cvector2f_t(1.0f, 1.0f).reference(); // rgba
			}

		}
		m_vertexattbi_buffer_ptr->unlock_cache_buffer();
	}

	virtual void on_log(result_t status, const char_t* str_info_ptr,
		usize__t str_info_length)
	{
		;
	}

	virtual void on_message_box(result_t status, const char_t* str_info_ptr,
		usize__t str_info_length)
	{
#if (OS_CONFIG == OS_WINDOWS)
		::MessageBoxA(NULL, str_info_ptr, "error!", MB_YESNO);
#endif // #if (OS_CONFIG == OS_WINDOWS)
		PECKER_LOG_ERR("on_message_box error %s", "str_info_ptr");
	}

};


#endif	//PFX_HELLO_LENA_FBO_H_
