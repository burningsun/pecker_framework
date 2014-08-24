/*
 * pfx_hello_triangle_vbo.h
 *
 *  Created on: 2014-8-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_opengles2_def.h"

#ifndef PFX_HELLO_TRIANGLE_VBO_H_
#define PFX_HELLO_TRIANGLE_VBO_H_


class chello_triangle_vbo_render_view_gles2 : public 	opengles2_activity_t::IOnRenderView_t
{
	typedef struct pos_clr
	{
		vector4f_t	m_postion;
		vector4f_t	m_color;
	}pos_clr_t;
private:
	cshader_program_gles2			m_program;
	cvertex_cache_buffer_gles2* 	m_vertexattbi_buffer_ptr;
	cbuffer_object_gles2*			m_vertexbufferobject_ptr;
public:
	chello_triangle_vbo_render_view_gles2() : m_vertexbufferobject_ptr(null), m_vertexattbi_buffer_ptr(null)
	{
		;
	}
	virtual ~chello_triangle_vbo_render_view_gles2()
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


		//SleepMS(100);
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
		
		chr_name = "aColor";
		long_t clr = m_program.get_location_by_name(chr_name);
		
		chr_name = "uFixedViewMatrix";
		long_t mat = m_program.get_location_by_name(chr_name);
		
		cmatrix4f_t mvp(1.0,0.0,0.0,0.0,
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
		__state.set_vertex_attrib_array(clr, m_vertexbufferobject_ptr, 4, 0, sizeof(vector4f_t));


		__state.draw_arrays(GL_TRIANGLES, 0, 3);
		__state.unbind_buffer(pos);
		__state.unbind_buffer(clr);

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

		get_system_defualt_shader_source(__sys_shader_source, //HELLO_SHADER_SOURCE,
			POSITION_COLOR_MVP_SHADER_SOURCE, 
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
		if (m_vertexbufferobject_ptr)
		{
			PECKER_LOG_INFO("m_vertexbufferobject_ptr = %08X",(long_t)m_vertexbufferobject_ptr);
			m_vertexbufferobject_ptr->dispose_buffer();
			m_vertexbufferobject_ptr = null;
			PECKER_LOG_INFO("m_vertexbufferobject_ptr->release_reference()(%lld)",__escape_time);
		}

		m_program.release_reference();
		PECKER_LOG_INFO("m_program.release_reference()(%lld)",__escape_time);
	}


	
	virtual void on_init(window_contex_t& PARAM_OUT win_context)
	{
		opengles2_activity_t::IOnRenderView_t::on_init(win_context);
		if (null == m_vertexattbi_buffer_ptr)
		{
			m_vertexattbi_buffer_ptr = cvertex_cache_buffer_gles2::create_cache_buffer(PFXVB_FLOAT, sizeof(pos_clr_t), 3);
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
			pos_clr_t* vex_attrib_ptr = (pos_clr_t*)lock_buffer_bits.m_bits_ptr;
			usize__t vex_count = lock_buffer_bits.m_bytes_count / sizeof(pos_clr_t);
			if (vex_attrib_ptr && vex_count)
			{
				vex_attrib_ptr[0].m_postion = cvector4f_t(0.0, 0.5, 0.0, 1.0).reference(); // pos
				vex_attrib_ptr[0].m_color = cvector4f_t(1.0, 0.0, 0.0, 1).reference(); // rgba

				vex_attrib_ptr[1].m_postion = cvector4f_t(-0.5, -0.5, 0.0, 1.0).reference(); // pos
				vex_attrib_ptr[1].m_color = cvector4f_t(0.0, 1.0, 0.0, 0.5).reference(); // rgba

				vex_attrib_ptr[2].m_postion = cvector4f_t(0.5, -0.5, 0.0, 1.0).reference(); // pos
				vex_attrib_ptr[2].m_color = cvector4f_t(0.0, 0.0, 1.0, 0).reference(); // rgba
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

#endif //PFX_HELLO_TRIANGLE_VBO_H_


