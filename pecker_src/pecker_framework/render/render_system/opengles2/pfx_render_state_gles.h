﻿/*
 * pfx_render_state.h
 *
 *  Created on: 2014-7-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_STATE_GLES_H_
#define		PFX_RENDER_STATE_GLES_H_

#include <gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "../../../include/util"
#include "../../../include/cmatrix4"
#include "pfx_shader_program_gles.h"
#include "pfx_buffer_object_gles.h"
#include "../pfx_texture.h"
#include "../../pfx_render_defs.h"
#include "../../pfx_on_context_view.h"

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
		EGL_LUMINANCE_BUFFER,	//PFX_RSYS_LUMINANCE_BUFFER,
		EGL_RGB_BUFFER			//PFX_RSYS_RGB_BUFFER
	};
	return egl_cbt_table[__cbt];
};

PFX_INLINE EGLint PFX_CPLV_TO_EGL_CPLV(PFX_CONTEX_PREPRIORITY_t __priority)
{
	static EGLint egl_cplv_table[PFX_CONTEXT_PREPRIORITY_TYPE_COUNT+1] =
	{
		EGL_CONTEXT_PRIORITY_HIGH_IMG,	//PFX_CONTEXT_DEFAULT_PREPRIORITY,
		EGL_CONTEXT_PRIORITY_LOW_IMG,	//PFX_CONTEXT_LOW_PREPRIORITY,
		EGL_CONTEXT_PRIORITY_MEDIUM_IMG,//PFX_CONTEXT_MEDIUM_PREPRIORITY,
		EGL_CONTEXT_PRIORITY_HIGH_IMG,	//PFX_CONTEXT_HIGH_PREPRIORITY,
		EGL_CONTEXT_PRIORITY_HIGH_IMG,  //PFX_CONTEXT_PREPRIORITY_TYPE_COUNT
	};
	return egl_cplv_table[__priority];
};


class PFX_RENDER_SYSTEM_API cnative_render_state_gles2
{
private:
	enum_int_t				m_texture_unit; //GLenum
	cshader_program_gles2	m_use_program;
public:
	~cnative_render_state_gles2();
protected:
	cnative_render_state_gles2();
public:
	static cnative_render_state_gles2& singletone();
public:
	//
	PFX_INLINE void set_viewport(const viewport_rect_t& viewport)
	{
		::glViewport(viewport.m_x, viewport.m_y, viewport.m_width, viewport.m_height);
	}
	//////////////////////////////////////////////////////////////////////////
	// program
	PFX_INLINE cshader_program_gles2* select_program(cshader_program_gles2* PARAM_INOUT program_ptr, result_t& status)
	{
		if (!program_ptr)
		{
			status = PFX_STATUS_INVALID_PARAMS;
			return null;
		}

		cshader_program_gles2* old_program_ptr = 
			DYNAMIC_CAST(cshader_program_gles2*)(m_use_program.create_reference(false));

		program_ptr->share_to(&m_use_program);

		cnative_shader_program_gles2* native_program_ptr = m_use_program.get_native_shader_pragram();
		if (native_program_ptr)
		{
			status = native_program_ptr->use();
		}
		return old_program_ptr;
	}

	PFX_INLINE result_t reset_selected_program()
	{
		result_t status = PFX_STATUS_OK;
		::glUseProgram(0);
		if (m_use_program.get_native_handle())
		{
			cshader_program_gles2* new_program_ptr =
				DYNAMIC_CAST(cshader_program_gles2*)(cshader_program_gles2::new_reference());
			if (new_program_ptr)
			{
				if (!new_program_ptr->share_to(&m_use_program))
				{
					status = PFX_STATUS_FAIL;
				}
				new_program_ptr->release_reference();
			}
			else
			{
				status = PFX_STATUS_MEM_LOW;
			}
		}
		
		return PFX_STATUS_OK;
	}


	//////////////////////////////////////////////////////////////////////////
	// buffer
	PFX_INLINE result_t bind_buffer(long_t __attribute_location)
	{
		::glEnableVertexAttribArray((GLuint)__attribute_location);
		return PFX_STATUS_OK;
	}

	PFX_INLINE void set_vertex_attrib_array(long_t __attribute_location,
		IPfx_vertex_cache_buffer* PARAM_IN buffer_ptr,
		boolean_t bNormalized = PFX_BOOL_FALSE,  
		uindex_t offset = 0, usize__t _size = MAX_UNSIGNED_VALUE)
	{
		if (buffer_ptr)
		{
			::glEnableVertexAttribArray((GLuint)__attribute_location);
			buffer_bits_t bits;
			buffer_rect_t rect_bit;
			rect_bit.m_offset	= offset;
			rect_bit.m_size		= _size;
			buffer_ptr->lock_cache_buffer(bits, &rect_bit);
			::glVertexAttribPointer((GLuint)__attribute_location,
				buffer_ptr->vb_struct_attribcount(),
				PfxVVT_to_GLVVT((PFX_VEXBUFFER_VALUE_TYPE_t)buffer_ptr->get_value_type()), 
				(GLboolean)bNormalized, 
				(GLsizei)bits.m_bytes_count,
				bits.m_bits_ptr);
			buffer_ptr->unlock_cache_buffer();
		}
	}

	PFX_INLINE void set_vertex_attrib_array(long_t __attribute_location,
		cbuffer_object_gles2* PARAM_IN buffer_ptr,
		boolean_t bNormalized = PFX_BOOL_FALSE,
		long_t offset = 0)
	{
		if (buffer_ptr)
		{
			cnative_buffer_object_gles2* native_buffer_ptr = buffer_ptr->get_native_buffer();
			if (native_buffer_ptr)
			{
				native_buffer_ptr->update_data();
				::glEnableVertexAttribArray((GLuint)__attribute_location);
				::glVertexAttribPointer((GLuint)__attribute_location,
					native_buffer_ptr->m_vb_struct_attribcount,
					PfxVVT_to_GLVVT((PFX_VEXBUFFER_VALUE_TYPE_t)native_buffer_ptr->m_value_type),
					(GLboolean)bNormalized,
					(GLsizei)native_buffer_ptr->m_bytes_count,
					(const char*)offset);
			}

		}
	}

	PFX_INLINE result_t unbind_buffer(long_t __attribute_location)
	{
		::glDisableVertexAttribArray((GLuint)__attribute_location);
		return PFX_STATUS_OK;
	}
	// vbo
	PFX_INLINE cbuffer_object_gles2* create_buffer()
	{
		cbuffer_object_gles2* new_buffer_ptr = 
			(cbuffer_object_gles2*)cbuffer_object_gles2::new_reference();
		cnative_buffer_object_gles2* native_buffer_ptr = null;
		if (new_buffer_ptr)
		{
			native_buffer_ptr = new_buffer_ptr->get_native_buffer();
		}
		if (native_buffer_ptr)
		{
			result_t status;
			status = native_buffer_ptr->create_buffer_object();
			if (PFX_STATUS_OK == status)
			{
				return new_buffer_ptr;
			}
		}
		if (new_buffer_ptr)
		{
			new_buffer_ptr->release_reference();
		}
		return null;
	}

	PFX_INLINE result_t set_buffer_object(cbuffer_object_gles2* PARAM_IN buffer_ptr,
		buffer_rect_t* PARAM_IN rect_bit = null)
	{
		if (buffer_ptr)
		{
			cnative_buffer_object_gles2* native_buffer_ptr = buffer_ptr->get_native_buffer();
			if (native_buffer_ptr)
			{
				return native_buffer_ptr->update_data(rect_bit);
			}
			else
			{
				return PFX_STATUS_UNINIT;
			}
		}
		
		return PFX_STATUS_INVALID_PARAMS;
	}

	//////////////////////////////////////////////////////////////////////////
	// framebuffer
	PFX_INLINE void use_system_framebuffer()
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	//PFX_INLINE result_t bind_framebuffer(framebuffer)
	//{

	//}
	PFX_INLINE result_t unbind_framebuffer()
	{
		use_system_framebuffer();
		return PFX_STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// texture
	//PFX_INLINE result_t set_texture(long_t __location, texture, enum_int_t unit_number = 0)
	//{
	//	if (unit_number != m_texture_unit)
	//	{
	//		::glActiveTexture(unit_number);
	//		m_texture_unit = unit_number;
	//	}
	//}

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
