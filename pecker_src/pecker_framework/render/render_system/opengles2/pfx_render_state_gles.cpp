/*
 * pfx_render_state_gles.cpp
 *
 *  Created on: 2014-7-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_render_state_gles.h"

PECKER_BEGIN
cnative_render_state_gles2::cnative_render_state_gles2() :
m_texture_unit(-1), m_use_program_ptr(null), m_old_program_ptr(null)
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

PECKER_END


