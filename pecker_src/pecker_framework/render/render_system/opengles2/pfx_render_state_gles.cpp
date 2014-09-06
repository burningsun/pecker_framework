/*
 * pfx_render_state_gles.cpp
 *
 *  Created on: 2014-7-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_render_state_gles.h"

PECKER_BEGIN
cnative_render_state_gles2::cnative_render_state_gles2() :
//m_texture_unit(-1), 
m_use_program_ptr(null), m_old_program_ptr(null)
{
	;
}
cnative_render_state_gles2::~cnative_render_state_gles2()
{
	if (m_old_program_ptr)
	{
		m_old_program_ptr->dispose_program();
		m_old_program_ptr = null;
	}

	if (m_use_program_ptr)
	{
		m_use_program_ptr->dispose_program();
		m_use_program_ptr = null;
	}
}
cnative_render_state_gles2& cnative_render_state_gles2::singletone()
{
	static 	cnative_render_state_gles2 render_state;
	return render_state;
}

bool cnative_render_state_gles2::is_egl_externsion_supported(EGLDisplay egl_display, const char* pstr_extension)
{
	const char* pstr_extensions = null;
	const char* pstr_start;
	char* pstr_where;
	char* pstr_terminator;

	pstr_where = (char*)strchr(pstr_extension, ' ');
	if (pstr_where || '\0' == *pstr_extension)
	{
		return false;
	}
	pstr_extensions = ::eglQueryString(egl_display, EGL_EXTENSIONS);
	pstr_start = (char*)pstr_extensions;
	while (1)
	{
		pstr_where = (char*)strstr((const char*)pstr_start, pstr_extension);
		if (null == pstr_where)
		{
			break;
		}
		pstr_terminator = pstr_where + strlen(pstr_extension);
		if (pstr_where == pstr_start || ' ' == *(pstr_where - 1))
		{
			if (' ' == *pstr_terminator || '\0' == *pstr_terminator)
			{
				return true;
			}
		}
		pstr_start = pstr_terminator;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
// shader
cshader_gles2* cnative_render_state_gles2::create_shader(enum_int_t shader_type)
{
	return cshader_gles2::new_shader(shader_type);
}

//////////////////////////////////////////////////////////////////////////
// program
cshader_program_gles2* cnative_render_state_gles2::create_program()
{
	return cshader_program_gles2::create_new_object();
}
cshader_program_gles2* cnative_render_state_gles2::working_program()
{
	if (m_use_program_ptr)
	{
		return m_use_program_ptr->new_ref();
	}
	else
	{
		return null;
	}
}

cshader_program_gles2* cnative_render_state_gles2::last_program()
{
	if (m_old_program_ptr)
	{
		return m_old_program_ptr->new_ref();
	}
	else
	{
		return null;
	}
}

result_t cnative_render_state_gles2::select_program(cshader_program_gles2* PARAM_INOUT program_ptr)
{
	//
	RETURN_INVALID_RESULT((!program_ptr), PFX_STATUS_INVALID_PARAMS);

	// 当前引用与原有引用一样，退出
	if (m_use_program_ptr &&
		m_use_program_ptr->native_ptr() == program_ptr->native_ptr())
	{
		return m_use_program_ptr->use();
	}

	cshader_program_gles2* new_ptr = program_ptr->new_ref();
	// 创建引用失败，退出
	RETURN_INVALID_RESULT((!new_ptr), PFX_STATUS_FAIL);
	if (!(new_ptr->native_ptr()))
	{
		new_ptr->dispose_program();
		return PFX_STATUS_FAIL;
	}

	cshader_program_gles2* working_program_ptr = m_use_program_ptr;
	m_use_program_ptr = new_ptr;
	result_t status = m_use_program_ptr->use();

	// 保存上次使用过的program值
	if (PFX_STATUS_OK == status)
	{
		if (working_program_ptr)
		{
			if (m_old_program_ptr)
			{
				m_old_program_ptr->dispose_program();
			}
			m_old_program_ptr = working_program_ptr;
		}
	}
	else
	{
		working_program_ptr->dispose_program();
	}
	return status;
}

result_t cnative_render_state_gles2::revert_select_program()
{
	//恢复上一次使用的program
	// 如果上次是第一次用，则复位program
	if (!m_old_program_ptr)
	{
		return reset_select_program();
	}

	// 先用上上一次的program，如果成功，则旧变新
	result_t status = m_old_program_ptr->use();

	if (PFX_STATUS_OK == status)
	{
		cshader_program_gles2* tmp_ptr = m_old_program_ptr;
		m_old_program_ptr = m_use_program_ptr;
		m_use_program_ptr = tmp_ptr;
	}
	return status;

}

result_t cnative_render_state_gles2::reset_state()
{
	return reset_select_program();
}

result_t cnative_render_state_gles2::reset_select_program()
{
	result_t status = PFX_STATUS_OK;
	::glUseProgram(0);

	if (m_use_program_ptr)
	{
		m_use_program_ptr->dispose_program();
		m_use_program_ptr = null;
	}
	if (m_old_program_ptr)
	{
		m_old_program_ptr->dispose_program();
		m_old_program_ptr = null;
	}

	return PFX_STATUS_OK;
}

//////////////////////////////////////////////////////////////////////////
// buffer
result_t cnative_render_state_gles2::bind_buffer(long_t __attribute_location)
{
	::glEnableVertexAttribArray((GLuint)__attribute_location);
	return PFX_STATUS_OK;
}

// vertex direct
void cnative_render_state_gles2::set_vertex_attrib_array(long_t __attribute_location,
	IPfx_vertex_cache_buffer* PARAM_IN buffer_ptr,
	usize__t attri_count,
	boolean_t bNormalized ,//= PFX_BOOL_FALSE,
	uindex_t offset ,//= 0, 
	usize__t _size //= MAX_UNSIGNED_VALUE
	)
{
	if (buffer_ptr)
	{
		usize__t  vb_struct_attribcount;
		vb_struct_attribcount = buffer_ptr->vb_struct_attribcount();
		if (attri_count > vb_struct_attribcount)
		{
			attri_count = vb_struct_attribcount;
		}
		::glEnableVertexAttribArray((GLuint)__attribute_location);
		buffer_bits_t bits;
		buffer_rect_t rect_bit;
		rect_bit.m_offset = offset;
		rect_bit.m_size = _size;
		buffer_ptr->lock_cache_buffer(bits, &rect_bit);
		::glVertexAttribPointer((GLuint)__attribute_location,
			attri_count,
			PfxVVT_to_GLVVT((PFX_VEXBUFFER_VALUE_TYPE_t)buffer_ptr->get_value_type()),
			(GLboolean)bNormalized,
			(GLsizei)buffer_ptr->get_vb_struct_size(),
			bits.m_bits_ptr);
		buffer_ptr->unlock_cache_buffer();
	}
}
// vertex buffer
void cnative_render_state_gles2::set_vertex_attrib_array(long_t __attribute_location,
	cbuffer_object_gles2* PARAM_IN buffer_ptr,
	usize__t attri_count,
	boolean_t bNormalized,// = PFX_BOOL_FALSE,
	long_t offset //= 0
	)
{
	if (buffer_ptr)
	{
		cnative_buffer_object_gles2* native_buffer_ptr = buffer_ptr->native_ptr();
		if (native_buffer_ptr && native_buffer_ptr->get_bufferID())
		{
			result_t status = native_buffer_ptr->update_data();
			if (PFX_STATUS_OK != status)
			{
				return;
			}

			usize__t  vb_struct_attribcount;
			vb_struct_attribcount = native_buffer_ptr->last_struct_attribcount();
			if (attri_count > vb_struct_attribcount)
			{
				attri_count = vb_struct_attribcount;
			}

			::glEnableVertexAttribArray((GLuint)__attribute_location);
			::glVertexAttribPointer((GLuint)__attribute_location,
				attri_count,
				PfxVVT_to_GLVVT((PFX_VEXBUFFER_VALUE_TYPE_t)native_buffer_ptr->m_value_type),
				(GLboolean)bNormalized,
				(GLsizei)native_buffer_ptr->last_struct_size(),
				(const char*)offset);
		}

	}
}

result_t cnative_render_state_gles2::unbind_buffer(long_t __attribute_location)
{
	::glDisableVertexAttribArray((GLuint)__attribute_location);
	return PFX_STATUS_OK;
}
// vbo
cbuffer_object_gles2* cnative_render_state_gles2::create_buffer()
{
	cbuffer_object_gles2* new_buffer_ptr = cbuffer_object_gles2::create_new_object();
	if (new_buffer_ptr)
	{
		result_t status;
		status = new_buffer_ptr->native().create_buffer_object();
		if (PFX_STATUS_OK != status)
		{
			new_buffer_ptr->dispose_buffer();
			new_buffer_ptr = null;
		}
	}
	return new_buffer_ptr;
}

result_t cnative_render_state_gles2::set_buffer_object(cbuffer_object_gles2* PARAM_IN buffer_ptr,
	buffer_rect_t* PARAM_IN rect_bit //= null
	)
{
	if (buffer_ptr)
	{
		return buffer_ptr->native().update_data(rect_bit);
	}
	else
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
}

PECKER_END


