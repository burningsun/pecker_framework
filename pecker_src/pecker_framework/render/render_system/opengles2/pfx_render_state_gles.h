﻿/*
 * pfx_render_state.h
 *
 *  Created on: 2014-7-25
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_STATE_GLES_H_
#define		PFX_RENDER_STATE_GLES_H_

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "../pfx_render_state.h"
#include "pfx_shader_program_gles.h"
#include "pfx_buffer_object_gles.h"
#include "pfx_texture_gles.h"
#include "pfx_framebuffer_object_gles.h"

PECKER_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

PFX_INLINE EGLint PFX_RSYSCBT_TO_EGL_RSYSCBT(PFX_RSYS_PARAM_COLOR_BUFFER_TYPE_t __cbt)
{
	static EGLint egl_cbt_table[PFX_RENDER_SYS_PARAM_COLOR_BUFFER_TYPE_COUNT + 1] =
	{
		EGL_RGB_BUFFER,			//PFX_RSYS_RGB_BUFFER,
		EGL_LUMINANCE_BUFFER,//PFX_RSYS_LUMINANCE_BUFFER,
		EGL_RGB_BUFFER//PFX_RSYS_RGB_BUFFER
	};
	return egl_cbt_table[__cbt];
};

PFX_INLINE EGLint PFX_CPLV_TO_EGL_CPLV(PFX_CONTEX_PREPRIORITY_t __priority)
{
	static EGLint egl_cplv_table[PFX_CONTEXT_PREPRIORITY_TYPE_COUNT+1] =
	{
		EGL_CONTEXT_PRIORITY_HIGH_IMG,	//PFX_CONTEXT_DEFAULT_PREPRIORITY,
		EGL_CONTEXT_PRIORITY_LOW_IMG,//PFX_CONTEXT_LOW_PREPRIORITY,
		EGL_CONTEXT_PRIORITY_MEDIUM_IMG,//PFX_CONTEXT_MEDIUM_PREPRIORITY,
		EGL_CONTEXT_PRIORITY_HIGH_IMG,//PFX_CONTEXT_HIGH_PREPRIORITY,
		EGL_CONTEXT_PRIORITY_HIGH_IMG,//PFX_CONTEXT_PREPRIORITY_TYPE_COUNT
	};
	return egl_cplv_table[__priority];
};

class PFX_RENDER_SYSTEM_API cnative_render_state_gles2 : public IPfx_render_state
{
private:
	//enum_int_t m_texture_unit; //GLenum
	cshader_program_gles2* m_use_program_ptr;
	cshader_program_gles2* m_old_program_ptr;
public:
	virtual ~cnative_render_state_gles2();
protected:
	cnative_render_state_gles2();
public:
	static cnative_render_state_gles2& singletone();
public:
	PFX_INLINE void clear_color(float_t red, float_t green, float_t blue, float_t alpha_value)
	{
		::glClearColor(red, green, blue, alpha_value);
	}
	PFX_INLINE void set_clear_mask(bitfield_t bitmask)
	{
		::glClear(bitmask);
	}
	//
	PFX_INLINE void set_viewport(const viewport_rect_t& viewport)
	{
		::glViewport(viewport.m_x, viewport.m_y, viewport.m_width, viewport.m_height);
	}
	PFX_INLINE void draw_arrays(PFX_PRIMITIVE_MODE_t draw_type, uindex_t firstIndex, usize__t draw_count)
	{
		::glDrawArrays(PFX_PRIMODE_2_GLES2_PRIMODE(draw_type), firstIndex, draw_count);
	}
	PFX_INLINE void gl_draw_arrays(enum_int_t draw_type, uindex_t firstIndex, usize__t draw_count)
	{
		::glDrawArrays(draw_type, firstIndex, draw_count);
	}
	//////////////////////////////////////////////////////////////////////////
	// shader
	cshader_gles2* create_shader_gles(enum_int_t shader_type);
	PFX_INLINE Ipfx_shader* create_shader(enum_int_t shader_type)
	{
		return create_shader_gles(shader_type);
	}
	//////////////////////////////////////////////////////////////////////////
	// program
	cshader_program_gles2* create_program_gles();
	cshader_program_gles2* working_program_gles();
	cshader_program_gles2* last_program_gles();

	PFX_INLINE Ipfx_shader_program* create_program()
	{
		return create_program_gles();
	}
	PFX_INLINE Ipfx_shader_program* working_program()
	{
		return working_program_gles();
	}
	PFX_INLINE Ipfx_shader_program* last_program()
	{
		return last_program_gles();
	}



	result_t select_program(cshader_program_gles2* PARAM_INOUT program_ptr);
	result_t revert_select_program();
	result_t reset_state();
	result_t reset_select_program();

	PFX_INLINE result_t select_program(Ipfx_shader_program* PARAM_INOUT program_ptr)
	{
		if (program_ptr && 
			program_ptr->get_version() == cnative_shader_program_gles2::get_version())
		{
			cshader_program_gles2* program_gles_ptr = DYNAMIC_CAST(cshader_program_gles2*)(program_ptr);
			return select_program(program_gles_ptr);
		}
		else
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// buffer
	result_t bind_buffer(long_t __attribute_location);

	// vertex direct
	void set_vertex_attrib_array(long_t __attribute_location,
		IPfx_vertex_cache_buffer* PARAM_IN buffer_ptr,
		usize__t attri_count,
		boolean_t bNormalized = PFX_BOOL_FALSE,
		uindex_t offset = 0, usize__t _size = MAX_UNSIGNED_VALUE);

	// vertex buffer
	void set_vertex_attrib_array(long_t __attribute_location,
		cbuffer_object_gles2* PARAM_IN buffer_ptr,
		usize__t attri_count,
		boolean_t bNormalized = PFX_BOOL_FALSE,
		long_t offset = 0);

	PFX_INLINE void set_vertex_attrib_array(long_t __attribute_location,
		IPfx_buffer_object* PARAM_IN buffer_ptr,
		usize__t attri_count,
		boolean_t bNormalized = PFX_BOOL_FALSE,
		long_t offset = 0)
	{
		if (buffer_ptr &&
			buffer_ptr->get_version() == cnative_buffer_object_gles2::get_version())
		{
			cbuffer_object_gles2* buffer_gles_ptr = DYNAMIC_CAST(cbuffer_object_gles2*)(buffer_ptr);
			set_vertex_attrib_array(__attribute_location,
				buffer_gles_ptr,
				attri_count,
				bNormalized,
				offset);
		}
	}

	

	result_t unbind_buffer(long_t __attribute_location);

	// vbo
	cbuffer_object_gles2* create_buffer_gles();

	result_t set_buffer_object(cbuffer_object_gles2* PARAM_IN buffer_ptr,
		buffer_rect_t* PARAM_IN rect_bit = null);

	PFX_INLINE IPfx_buffer_object* create_buffer()
	{
		return create_buffer_gles();
	}

	PFX_INLINE result_t set_buffer_object(IPfx_buffer_object* PARAM_IN buffer_ptr,
		buffer_rect_t* PARAM_IN rect_bit = null)
	{
		if (buffer_ptr &&
			buffer_ptr->get_version() == cnative_buffer_object_gles2::get_version())
		{
			cbuffer_object_gles2* buffer_gles_ptr = DYNAMIC_CAST(cbuffer_object_gles2*)(buffer_ptr);
			return set_buffer_object(buffer_gles_ptr, rect_bit);
		}
		else
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
	}


	//////////////////////////////////////////////////////////////////////////
	// framebuffer
	PFX_INLINE void use_system_framebuffer()
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	PFX_INLINE result_t unbind_framebuffer()
	{
		use_system_framebuffer();
		return PFX_STATUS_OK;
	}

	PFX_INLINE crenderbuffer_gles2* create_renderbuffer_gles()
	{
		return crenderbuffer_gles2::create_new_object();
	}
	
	PFX_INLINE cframebuffer_gles2* create_framebuffer_gles()
	{
		return cframebuffer_gles2::create_new_object();
	}

	PFX_INLINE result_t use_framebuffer_gles(cframebuffer_gles2* PARAM_IN fbuf_ptr)
	{
		RETURN_INVALID_RESULT(!fbuf_ptr, PFX_STATUS_INVALID_PARAMS);
		return fbuf_ptr->bind();
	}

	PFX_INLINE IPfx_renderbuffer* create_renderbuffer()
	{
		return create_renderbuffer_gles();
	}

	PFX_INLINE IPfx_framebuffer* create_framebuffer()
	{
		return create_framebuffer_gles();
	}

	PFX_INLINE result_t use_framebuffer(IPfx_framebuffer* PARAM_IN fbuf_ptr)
	{
		if (fbuf_ptr &&
			fbuf_ptr->get_version() == cnative_framebuffer_gles2::get_version())
		{
			cframebuffer_gles2* fbuf_gles_ptr = DYNAMIC_CAST(cframebuffer_gles2*)(fbuf_ptr);
			return use_framebuffer_gles(fbuf_gles_ptr);
		}
		else
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
	}






	////////////////////////////////////////////////////////////////////////
	// texture
	PFX_INLINE result_t set_texture(long_t __location,
		IPfx_texture* PARAM_IN texture_ptr, 
		enum_int_t unit_number = 0)
	{
		if (null == texture_ptr || texture_ptr->get_version() != cnative_texture2D_gles2::get_version()
			|| unit_number > 31 || unit_number < 0)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}

		result_t status;
		::glActiveTexture(unit_number + GL_TEXTURE0);
		status = texture_ptr->bind_texture();
		::glUniform1i(__location, unit_number);
		return status;
	}

	PFX_INLINE ctexture_surface* create_texture_surface()
	{
		return ctexture_surface::create_new_object();
	}

	PFX_INLINE ctexture2D_gles2* create_texture2D_gles()
	{
		return ctexture2D_gles2::create_new_object();
	}

	PFX_INLINE IPfx_texture* create_texture2D()
	{
		return create_texture2D_gles();
	}

	//////////////////////////////////////////////////////////////////////////
	// float
	PFX_INLINE void set_vertex_attri(long_t __location, float_t val)
	{
		::glVertexAttrib1f((GLuint)__location, val);
	}
	PFX_INLINE void set_vertex_attri(long_t __location, float_t val1, float_t val2)
	{
		::glVertexAttrib2f((GLuint)__location, val1, val2);
	}
	PFX_INLINE void set_vertex_attri(long_t __location, float_t val1, float_t val2, float_t val3)
	{
		::glVertexAttrib3f((GLuint)__location, val1, val2, val3);
	}
	PFX_INLINE void set_vertex_attri(long_t __location, float_t val1, float_t val2, float_t val3, float_t val4)
	{
		::glVertexAttrib4f((GLuint)__location, val1, val2, val3, val4);
	}
	PFX_INLINE void set_vertex_attri(long_t __location, const vector2f_t& val)
	{
		::glVertexAttrib2fv((GLuint)__location, (const GLfloat*)&val);
	}
	PFX_INLINE void set_vertex_attri(long_t __location, const vector3f_t& val)
	{
		::glVertexAttrib3fv((GLuint)__location, (const GLfloat*)&val);
	}
	PFX_INLINE void set_vertex_attri(long_t __location, const vector4f_t& val)
	{
		::glVertexAttrib4fv((GLuint)__location, (const GLfloat*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, float_t val)
	{
		::glUniform1f((GLint)__location, val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, float_t val1, float_t val2)
	{
		::glUniform2f((GLint)__location, val1, val2);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, float_t val1, float_t val2, float_t val3)
	{
		::glUniform3f((GLint)__location, val1, val2, val3);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, float_t val1, float_t val2, float_t val3, float_t val4)
	{
		::glUniform4f((GLint)__location, val1, val2, val3, val4);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector2f_t& PARAM_INOUT val)
	{
		::glUniform2fv((GLint)__location, 1, (const GLfloat*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector3f_t& PARAM_INOUT val)
	{
		::glUniform3fv((GLint)__location, 1, (const GLfloat*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector4f_t& PARAM_INOUT val)
	{
		::glUniform4fv((GLint)__location, 1, (const GLfloat*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const float_t* PARAM_INOUT val_ptr, usize__t ncount)
	{
		::glUniform1fv((GLint)__location, ncount, (const GLfloat*)val_ptr);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector2f_t* PARAM_INOUT val_ptr, usize__t ncount)
	{
		::glUniform2fv((GLint)__location, ncount, (const GLfloat*)val_ptr);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector3f_t* PARAM_INOUT val_ptr, usize__t ncount)
	{
		::glUniform3fv((GLint)__location, ncount, (const GLfloat*)val_ptr);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector4f_t* PARAM_INOUT val_ptr, usize__t ncount)
	{
		::glUniform4fv((GLint)__location, ncount, (const GLfloat*)val_ptr);
	}

	PFX_INLINE void set_uniform_attri(long_t __location, const matrix2f_t& PARAM_INOUT val, bool btransport = false)
	{
		::glUniformMatrix2fv((GLint)__location, 1, btransport, (const GLfloat*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const matrix3f_t& PARAM_INOUT val, bool btransport = false)
	{
		::glUniformMatrix3fv((GLint)__location, 1, btransport, (const GLfloat*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const matrix4f_t& PARAM_INOUT val, bool btransport = false)
	{
		::glUniformMatrix4fv((GLint)__location, 1, btransport, (const GLfloat*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const matrix2f_t* PARAM_INOUT val_ptr, usize__t ncount, bool btransport = false)
	{
		::glUniformMatrix2fv((GLint)__location, ncount, btransport, (const GLfloat*)val_ptr);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const matrix3f_t* PARAM_INOUT val_ptr, usize__t ncount, bool btransport = false)
	{
		::glUniformMatrix3fv((GLint)__location, ncount, btransport, (const GLfloat*)val_ptr);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const matrix4f_t* PARAM_INOUT val_ptr, usize__t ncount, bool btransport = false)
	{
		::glUniformMatrix4fv((GLint)__location, ncount, btransport, (const GLfloat*)val_ptr);
	}

	//////////////////////////////////////////////////////////////////////////
	// int
	PFX_INLINE void set_uniform_attri(long_t __location, sint_t val)
	{
		::glUniform1i((GLint)__location, val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, sint_t val1, sint_t val2)
	{
		::glUniform2i((GLint)__location, val1, val2);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, sint_t val1, sint_t val2, sint_t val3)
	{
		::glUniform3i((GLint)__location, val1, val2, val3);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, sint_t val1, sint_t val2, sint_t val3, sint_t val4)
	{
		::glUniform4i((GLint)__location, val1, val2, val3, val4);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector2i_t& PARAM_INOUT val)
	{
		::glUniform2iv((GLint)__location, 1, (const GLint*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector3i_t& PARAM_INOUT val)
	{
		::glUniform3iv((GLint)__location, 1, (const GLint*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector4i_t& PARAM_INOUT val)
	{
		::glUniform4iv((GLint)__location, 1, (const GLint*)&val);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const sint_t* PARAM_INOUT val_ptr, usize__t ncount)
	{
		::glUniform1iv((GLint)__location, ncount, (const GLint*)val_ptr);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector2i_t* PARAM_INOUT val_ptr, usize__t ncount)
	{
		::glUniform2iv((GLint)__location, ncount, (const GLint*)val_ptr);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector3i_t* PARAM_INOUT val_ptr, usize__t ncount)
	{
		::glUniform3iv((GLint)__location, ncount, (const GLint*)val_ptr);
	}
	PFX_INLINE void set_uniform_attri(long_t __location, const vector4i_t* PARAM_INOUT val_ptr, usize__t ncount)
	{
		::glUniform4iv((GLint)__location, ncount, (const GLint*)val_ptr);
	}

	static bool is_egl_externsion_supported(EGLDisplay egl_display, const char* pstr_extension);
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_RENDER_STATE_GLES_H_
