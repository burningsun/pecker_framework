/*
 * pecker_render_buffer_gl.cpp
 *
 *  Created on: 2013-4-2
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_render_buffer_gl.h"
#include "../pecker_frame_buffer.h"
#include "pecker_render_resource_container_gl.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
PECKER_BEGIN
	


// OPENGL ES 2颜色缓存常量对应表
static const UInt COLOR_BUFFER_FORMAT_TABLE_GLES2[COLOR_BUFFER_FORMAT_COUNT] 
= {GL_RGB565,GL_RGBA4,GL_RGB5_A1,GL_RGB8_OES,GL_RGBA8_OES};
// OPENGL ES 2深度缓存常量对应表
static const UInt DEPTH_BUFFER_FORMAT_TABLE_GLES2[DEPTH_BUFFER_FORMAT_COUNT]
= {GL_DEPTH_COMPONENT16,GL_DEPTH_COMPONENT24_OES,GL_DEPTH_COMPONENT32_OES,
GL_DEPTH24_STENCIL8_OES};
// OPENGL ES 2模板缓存常量对应表
static const UInt STENCIL_BUFFER_FORMAT_TABLE_GLES2[STENCIL_BUFFER_FORMAT_COUNT]
= {GL_STENCIL_INDEX8,GL_STENCIL_INDEX1_OES,GL_STENCIL_INDEX4_OES,GL_DEPTH24_STENCIL8_OES};




pecker_color_buffer_gles2::pecker_color_buffer_gles2():_M_gpu_target(0)
{

}

pecker_color_buffer_gles2::~pecker_color_buffer_gles2()
{
	release_buffer_from_gpu_ram();
}

HResult pecker_color_buffer_gles2::attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index /* = 0 */)
{
	if (null != pframe_buffer)
	{
		return pframe_buffer->attach_render_buffer(this,attach_index);
	}
	return P_INVALID_VALUE;
}

HResult pecker_color_buffer_gles2::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_color_buffer_gles2::allocate_buffer_from_gpu_ram()
{
	if (0 == _M_gpu_target)
	{
		glGenRenderbuffers(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	else
	{
		return P_UNIQUE_ERR;
	}
}

HResult pecker_color_buffer_gles2::release_buffer_from_gpu_ram()
{
	if (0 != _M_gpu_target)
	{
		glDeleteRenderbuffers(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	else
	{
		return P_OK;
	}
	
}

HResult pecker_color_buffer_gles2::use_render_buffer_info()
{
	if (0 != _M_gpu_target)
	{
		UInt internal_format = _M_render_buffer_info._M_internal_format;
		if (_M_render_buffer_info._M_internal_format < COLOR_BUFFER_FORMAT_COUNT)
		{
			internal_format = COLOR_BUFFER_FORMAT_TABLE_GLES2[_M_render_buffer_info._M_internal_format];
		}

		glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
		glRenderbufferStorage(GL_RENDERBUFFER,_M_render_buffer_info._M_internal_format,
			_M_render_buffer_info._M_width,_M_render_buffer_info._M_heigth);

		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	return P_FAIL;
}

HResult pecker_color_buffer_gles2::use_render_buffer_info(const pecker_render_buffer_info& buf_info)
{
	if (0 != _M_gpu_target)
	{
		UInt internal_format = buf_info._M_internal_format;
		if (buf_info._M_internal_format < COLOR_BUFFER_FORMAT_COUNT)
		{
			internal_format = COLOR_BUFFER_FORMAT_TABLE_GLES2[buf_info._M_internal_format];
		}
		glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
		glRenderbufferStorage(GL_RENDERBUFFER,internal_format,
			buf_info._M_width,buf_info._M_heigth);

		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == result_)
		{
			_M_render_buffer_info = buf_info;
		}
		return result_;
	}
	return P_FAIL;
}

const pecker_render_buffer_info& pecker_color_buffer_gles2::get_render_buffer_info() const
{
	return _M_render_buffer_info;
}

UInt pecker_color_buffer_gles2::get_object_location() const
{
	return _M_gpu_target;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

pecker_depth_buffer_gles2::pecker_depth_buffer_gles2():_M_gpu_target(0)
{

}

pecker_depth_buffer_gles2::~pecker_depth_buffer_gles2()
{
	release_buffer_from_gpu_ram();
}

HResult pecker_depth_buffer_gles2::attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index /* = 0 */)
{
	if (null != pframe_buffer)
	{
		return pframe_buffer->attach_render_buffer(this,attach_index);
	}

	return P_INVALID_VALUE;
}

HResult pecker_depth_buffer_gles2::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_depth_buffer_gles2::allocate_buffer_from_gpu_ram()
{
	if (0 == _M_gpu_target)
	{
		glGenRenderbuffers(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	else
	{
		return P_UNIQUE_ERR;
	}
}

HResult pecker_depth_buffer_gles2::release_buffer_from_gpu_ram()
{
	if (0 != _M_gpu_target)
	{
		glDeleteRenderbuffers(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	else
	{
		return P_OK;
	}
}

//HResult pecker_depth_buffer_gles2::set_default_render_buffer_info(const pecker_render_buffer_info& buf_info)
//{
//	return P_OK;
//}

HResult pecker_depth_buffer_gles2::use_render_buffer_info()
{
	if (0 != _M_gpu_target)
	{
		UInt internal_format = _M_render_buffer_info._M_internal_format;
		if (_M_render_buffer_info._M_internal_format < DEPTH_BUFFER_FORMAT_COUNT)
		{
			internal_format = DEPTH_BUFFER_FORMAT_TABLE_GLES2[_M_render_buffer_info._M_internal_format];
		}

		glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
		glRenderbufferStorage(GL_RENDERBUFFER,_M_render_buffer_info._M_internal_format,
			_M_render_buffer_info._M_width,_M_render_buffer_info._M_heigth);

		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	return P_FAIL;
}

HResult pecker_depth_buffer_gles2::use_render_buffer_info(const pecker_render_buffer_info& buf_info)
{
	if (0 != _M_gpu_target)
	{
		UInt internal_format = buf_info._M_internal_format;
		if (buf_info._M_internal_format < DEPTH_BUFFER_FORMAT_COUNT)
		{
			internal_format = DEPTH_BUFFER_FORMAT_TABLE_GLES2[buf_info._M_internal_format];
		}
		glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
		glRenderbufferStorage(GL_RENDERBUFFER,internal_format,
			buf_info._M_width,buf_info._M_heigth);

		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == result_)
		{
			_M_render_buffer_info = buf_info;
		}
		return result_;
	}
	return P_FAIL;
}

const pecker_render_buffer_info& pecker_depth_buffer_gles2::get_render_buffer_info() const
{
	return _M_render_buffer_info;
}

UInt pecker_depth_buffer_gles2::get_object_location() const
{
	return _M_gpu_target;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

pecker_stencil_buffer_gles2::pecker_stencil_buffer_gles2():_M_gpu_target(0)
{

}

pecker_stencil_buffer_gles2::~pecker_stencil_buffer_gles2()
{
	release_buffer_from_gpu_ram();
}

HResult pecker_stencil_buffer_gles2::attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index /* = 0 */)
{
	if (null != pframe_buffer)
	{
		return pframe_buffer->attach_render_buffer(this,attach_index);
	}
	return P_FAIL;
}

HResult pecker_stencil_buffer_gles2::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_stencil_buffer_gles2::allocate_buffer_from_gpu_ram()
{
	if (0 == _M_gpu_target)
	{
		glGenRenderbuffers(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	else
	{
		return P_UNIQUE_ERR;
	}
}

HResult pecker_stencil_buffer_gles2::release_buffer_from_gpu_ram()
{
	if (0 != _M_gpu_target)
	{
		glDeleteRenderbuffers(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	else
	{
		return P_OK;
	}
}

//HResult pecker_stencil_buffer_gles2::set_default_render_buffer_info(const pecker_render_buffer_info& buf_info)
//{
//	return P_OK;
//}

HResult pecker_stencil_buffer_gles2::use_render_buffer_info()
{
	if (0 != _M_gpu_target)
	{
		UInt internal_format = _M_render_buffer_info._M_internal_format;
		if (_M_render_buffer_info._M_internal_format < STENCIL_BUFFER_FORMAT_COUNT)
		{
			internal_format = STENCIL_BUFFER_FORMAT_TABLE_GLES2[_M_render_buffer_info._M_internal_format];
		}

		glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
		glRenderbufferStorage(GL_RENDERBUFFER,_M_render_buffer_info._M_internal_format,
			_M_render_buffer_info._M_width,_M_render_buffer_info._M_heigth);

		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	return P_FAIL;
}

HResult pecker_stencil_buffer_gles2::use_render_buffer_info(const pecker_render_buffer_info& buf_info)
{
	if (0 != _M_gpu_target)
	{
		UInt internal_format = buf_info._M_internal_format;
		if (buf_info._M_internal_format < DEPTH_BUFFER_FORMAT_COUNT)
		{
			internal_format = DEPTH_BUFFER_FORMAT_TABLE_GLES2[buf_info._M_internal_format];
		}
		glBindRenderbuffer(GL_RENDERBUFFER,_M_gpu_target);
		glRenderbufferStorage(GL_RENDERBUFFER,internal_format,
			buf_info._M_width,buf_info._M_heigth);

		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == result_)
		{
			_M_render_buffer_info = buf_info;
		}
		return result_;
	}
	return P_FAIL;
}

const pecker_render_buffer_info& pecker_stencil_buffer_gles2::get_render_buffer_info() const
{
	return _M_render_buffer_info;
}

UInt pecker_stencil_buffer_gles2::get_object_location() const
{
	return _M_gpu_target;
}


PECKER_END

