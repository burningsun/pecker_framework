/*
 * pfx_gles2_displayview_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_opengles2_def.h"
#include "../../pecker_framework/render/pfx_image_png.h"

#ifndef PFX_HELLO_LENA_H_
#define PFX_HELLO_LENA_H_

extern result_t load_img(const char_t* pfile_name, image_data_t& __img);
extern result_t load_png_img(const char_t* pfile_name, cImage& __img);

class chello_lena_view_gles2 : public 	opengles2_activity_t::IOnRenderView_t
{
	typedef struct pos_clr
	{
		vector4f_t	m_postion;
		vector2f_t	m_img_pos;
	}pos_texpos_t;
private:
	cshader_program_gles2			m_program;
	cvertex_cache_buffer_gles2* 	m_vertexattbi_buffer_ptr;
	cbuffer_object_gles2*			m_vertexbufferobject_ptr;
	image_data_t m_img;
	cImage m_cimg;
	GLuint m_texture2D;
public:
	chello_lena_view_gles2() :m_texture2D(0), m_vertexattbi_buffer_ptr(null), 
		m_vertexbufferobject_ptr(null)
	{
		;
	}
	virtual ~chello_lena_view_gles2()
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
	}

	virtual void on_view(
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state,
		u64_t	__escape_time,
		const viewport_rect_t& view_port,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr)
	{
		static float_t red_channel = 0.7;
		__state.clear_color(red_channel, 0.2f, 0.7f, 1.0f);
		__state.set_clear_mask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		::glEnable(GL_BLEND);
		::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		red_channel += 0.01;
		if (red_channel > 1)
		{
			red_channel = 0;
		}

		
		result_t status;
		cshader_program_gles2* old_program_ptr = __state.select_program(&m_program, status);
		if (PFX_STATUS_OK != status)
		{
			__state.select_program(old_program_ptr,status);
			return;
		}

		const char* chr_name;
		chr_name = "aPosition";
		long_t pos = m_program.get_location_by_name(chr_name);
		
		chr_name = "aTexCoord";
		long_t texcoord = m_program.get_location_by_name(chr_name);
		
		chr_name = "uFixedViewMatrix";
		long_t mat = m_program.get_location_by_name(chr_name);
		
		chr_name = "sTexture";
		long_t tex = m_program.get_location_by_name(chr_name);

		cmatrix4f_t mvp((float_t)view_port.m_height / (float_t)view_port.m_width, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
			);

		__state.set_uniform_attri(mat, mvp.reference());

		if (!m_vertexbufferobject_ptr)
		{
			m_vertexbufferobject_ptr = __state.create_buffer();
			m_vertexbufferobject_ptr->set_vbo_buffer(m_vertexattbi_buffer_ptr);
		}
		__state.set_vertex_attrib_array(pos, m_vertexbufferobject_ptr, 4);
		__state.set_vertex_attrib_array(texcoord, m_vertexbufferobject_ptr, 4, 0, sizeof(vector4f_t));

		//__state.set_vertex_attrib_array(pos, m_vertexattbi_buffer_ptr, 4);
		//__state.set_vertex_attrib_array(texcoord, m_vertexattbi_buffer_ptr, 2, 0, sizeof(vector4f_t));


		glActiveTexture(GL_TEXTURE0);

		if (!m_texture2D)
		{
			//GLubyte pixels[4 * 4] =
			//{
			//	255, 0, 0, 100,// Red
			//	0, 255, 0, 255,// Green
			//	0, 0, 255, 200,// Blue
			//	255, 255, 0, 255, // Yellow
			//};

			glGenTextures(1, &m_texture2D);

#if (OS_CONFIG == OS_WINDOWS)
			const char* lena_path = "test_res\\lena_rgba.png";
#else
			const char* lena_path = "test_res/lena_rgba.png";
#endif //#if (OS_CONFIG == OS_WINDOWS)

			glBindTexture(GL_TEXTURE_2D, m_texture2D);

			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			load_png_img(lena_path, m_cimg);
			const image_data_t& img = m_cimg.get_image_direct();
			glPixelStorei(GL_UNPACK_ALIGNMENT, img.m_pack_size);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.m_img.m_width,
				img.m_img.m_height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, img.m_img.m_bits_ptr);

			//load_img(lena_path, m_img);
			//glPixelStorei(GL_UNPACK_ALIGNMENT, m_img.m_pack_size);

			//

			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_img.m_img.m_width,
			//	m_img.m_img.m_height, 0, GL_RGBA,
			//	GL_UNSIGNED_BYTE, m_img.m_img.m_bits_ptr);



			//// 测试纹理定位用
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2,
			//	2, 0, GL_RGBA,
			//	GL_UNSIGNED_BYTE, pixels);
			// Set the filtering mode
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, m_texture2D);
		}


		
		glUniform1i(tex, 0);

		__state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
		__state.unbind_buffer(pos);
		__state.unbind_buffer(texcoord);


		__state.select_program(old_program_ptr, status);
	}

	virtual void on_load(
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state,
		u64_t	__escape_time,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr)
	{
		PECKER_LOG_INFO("on_load escape time = %lld",__escape_time);

		shader_souce_string_t __sys_shader_source;
		cvertex_shader_gles2_t __vs;
		cpixel_shder_gles2_t   __fs;
		result_t status;

		get_system_defualt_shader_source(__sys_shader_source,
			POSITION_TEXTCOORD_MVP_SHADER_SOURCE,
			SSS_MEDIUEM_FLOAT);

		FOR_ONE_LOOP_BEGIN
			
		BREAK_LOOP_CONDITION_SETS(!__sys_shader_source.m_str_fragment_shader ||
			!__sys_shader_source.m_str_vertext_shader, status, PFX_STATUS_INVALID_VALUE);

		__vs.compile_shader(__sys_shader_source.m_str_vertext_shader->get_string(), 
			__sys_shader_source.m_str_vertext_shader->get_length(), 
			status);

		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);

		__fs.compile_shader(__sys_shader_source.m_str_fragment_shader->get_string(), 
			__sys_shader_source.m_str_fragment_shader->get_length(), 
			status);

		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);

		m_program.create_reference();
		m_program.attach_shader(&__vs);
		m_program.attach_shader(&__fs);
		status = m_program.compile_program();



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
		m_program.release_reference();
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


#endif	//PFX_HELLO_LENA_H_
