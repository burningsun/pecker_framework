/*
 * pecker_shader_program_glsles1.cpp
 *
 *  Created on: 2013-3-6
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_shader_program_glsles1.h"
#include <GLES2/gl2.h>
PECKER_BEGIN

pecker_shader_program_glsles1::pecker_shader_program_glsles1():
_M_program(0),_M_frame_shader(0),_M_vertex_shader(0)
{
	;
}

static pecker_shader_program_glsles1* g_pusing_shader_program = null;
pecker_shader_program_glsles1::~pecker_shader_program_glsles1()
{
	delete_shader_program();
	delete_frame_shader();
	delete_vertex_shader();

	if (this == g_pusing_shader_program)
	{
		g_pusing_shader_program = null;
	}
}
UInt pecker_shader_program_glsles1::init_shader_program(UInt nvertex_shader, UInt nframe_shader,const pecker_string* P_IN pstr_bind_attributes /* = null */,
	nSize nAttributes_count /* = 0 */,pecker_string* P_OUT pstr_error_info /* = null */)	
{
	if (0 != _M_program)
	{
		return 0;
	}

	return _M_program;
}
UInt pecker_shader_program_glsles1::init_shader_program(const pecker_string* P_IN pstr_bind_attributes /* = null */,nSize nAttributes_count /* = 0 */,pecker_string* P_OUT pstr_error_info /* = null */)
{
	if (0 != _M_program)
	{
		return 0;
	}

	return _M_program;
}

UInt pecker_shader_program_glsles1::load_frame_shader_source(const pecker_string& str_source_code,pecker_string* P_OUT pstr_error_info /* = null */)
{
	if (0 != _M_frame_shader)
	{
		return 0;
	}
	if (str_source_code.get_string_length() <= 0)
	{
		return 0;
	}
	// 创建着色器
	GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
	if (shader)
	{
		//编译着色源代码
		const GLchar* pSource = (GLchar*)(str_source_code.get_data());
		::glShaderSource(shader, 1, &pSource, null);
		::glCompileShader(shader);
		GLint compiled = 0;
		//获取编译结果
		::glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			if(pstr_error_info)
			{
				GLint info_length = 0;
				::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
				if (info_length)
				{
					pstr_error_info->init(info_length);
					GLchar* print_err_buf = (GLchar*) pstr_error_info->get_data();
					GLsizei print_error_length = info_length;
					::glGetShaderInfoLog(shader, info_length, &print_error_length, print_err_buf);

					PECKER_LOG_ERR("pecker_shader_program_glsles1::load_frame_shader_source","error info = %s",print_err_buf);
				}
			}
			::glDeleteShader(shader);
			shader = 0;
		}
		_M_frame_shader = shader;
	}
	return (UInt)shader;
}
UInt pecker_shader_program_glsles1::load_vertex_shader_source(const pecker_string& str_source_code,pecker_string* P_OUT pstr_error_info /* = null */)
{
	if (0 != _M_vertex_shader)
	{
		return 0;
	}
	if (str_source_code.get_string_length() <= 0)
	{
		return 0;
	}
	// 创建着色器
	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	if (shader)
	{
		//编译着色源代码
		const GLchar* pSource = (GLchar*)(str_source_code.get_data());
		::glShaderSource(shader, 1, &pSource, null);
		::glCompileShader(shader);
		GLint compiled = 0;
		//获取编译结果
		::glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			if(pstr_error_info)
			{
				GLint info_length = 0;
				::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
				if (info_length)
				{
					pstr_error_info->init(info_length);
					GLchar* print_err_buf = (GLchar*) pstr_error_info->get_data();
					GLsizei print_error_length = info_length;
					::glGetShaderInfoLog(shader, info_length, &print_error_length, print_err_buf);

					PECKER_LOG_ERR("pecker_shader_program_glsles1::load_frame_shader_source","error info = %s",print_err_buf);
				}
			}
			::glDeleteShader(shader);
			shader = 0;
		}
		_M_vertex_shader = shader;
	}
	return (UInt)shader;
}

UInt pecker_shader_program_glsles1::delete_shader_program()
{
	if (0 != _M_program)
	{
		::glDeleteProgram(_M_program);
		UInt uerror_code = pecker_opengles_v2_object::get_last_error_code();
		if (GL_NO_ERROR == uerror_code)
		{
			_M_program = 0;
		}
		return uerror_code;

	}
	return P_OK;
}
UInt pecker_shader_program_glsles1::delete_frame_shader()
{
	if (0 != _M_frame_shader)
	{
		::glDeleteShader(_M_frame_shader);
		UInt uerror_code = pecker_opengles_v2_object::get_last_error_code();
		if (GL_NO_ERROR == uerror_code)
		{
			_M_frame_shader = 0;
		}

		return uerror_code;
		
	}
	return P_OK;
}
UInt pecker_shader_program_glsles1::delete_vertex_shader()
{
	if (0 != _M_vertex_shader)
	{
		::glDeleteShader(_M_vertex_shader);
		UInt uerror_code = pecker_opengles_v2_object::get_last_error_code();
		if (GL_NO_ERROR == uerror_code)
		{
			_M_vertex_shader = 0;
		}
		return uerror_code;
	}
	return P_OK;
}

UInt pecker_shader_program_glsles1::using_program()
{
	if (0 != _M_program)
	{
		::glUseProgram(_M_program);
		UInt uerror_code = pecker_opengles_v2_object::get_last_error_code();
		if (GL_NO_ERROR == uerror_code)
		{
			g_pusing_shader_program = this;
			return _M_program;
		}
	}
	return 0;
}
	
UInt pecker_shader_program_glsles1::get_attribute_location(const pecker_string& str_attribute_name) const
{
	UInt return_index = (UInt)(-1);
	if (0 != _M_program && str_attribute_name.get_string_length() > 0)
	{
		return_index = ::glGetAttribLocation(_M_program,str_attribute_name.get_data());
		//if (GL_NO_ERROR != ::glGetError())
		//{
		//	return_index = (UInt)(-1);
		//}
	}
	return return_index;
}
	
HResult  pecker_shader_program_glsles1::get_active_attribute
	(UInt attribute_index,HEnum& attribute_type,nSize &attribute_size, pecker_string& str_attribute_name) const
{
	GLsizei strlength = 0;
	::glGetActiveAttrib(_M_program,attribute_index,strlength,&strlength,&attribute_size,(GLenum*)(&attribute_type),null);
	UInt uerror_code = pecker_opengles_v2_object::get_last_error_code();
	if (GL_NO_ERROR == uerror_code)
	{
		str_attribute_name.init(strlength);
		GLchar* pstr_name = (GLchar*)str_attribute_name.get_data();
		::glGetActiveAttrib(_M_program,attribute_index,strlength,&strlength,&attribute_size,(GLenum*)(&attribute_type),pstr_name);
		uerror_code = pecker_opengles_v2_object::get_last_error_code();
	}
		
	return uerror_code;
}

	
UInt  pecker_shader_program_glsles1::get_uniform_location
	(const pecker_string& str_uniform_name) const
{
	UInt return_index = (UInt)(-1);
	if (0 != _M_program && str_uniform_name.get_string_length() > 0)
	{
		return_index = ::glGetUniformLocation(_M_program,str_uniform_name.get_data());
	}
	return return_index;
}
	
HResult  pecker_shader_program_glsles1::get_active_uniform
	(UInt uniform_index,HEnum& uniform_type,nSize &uniform_size, pecker_string& str_uniform_name) const
{

	GLsizei strlength = 0;
	::glGetActiveAttrib(_M_program,uniform_index,strlength,&strlength,&uniform_size,(GLenum*)(&uniform_type),null);
	UInt uerror_code = pecker_opengles_v2_object::get_last_error_code();
	if (GL_NO_ERROR == uerror_code)
	{
		str_uniform_name.init(strlength);
		GLchar* pstr_name = (GLchar*)str_uniform_name.get_data();
		::glGetActiveAttrib(_M_program,uniform_index,strlength,&strlength,&uniform_size,(GLenum*)(&uniform_type),pstr_name);
		uerror_code = pecker_opengles_v2_object::get_last_error_code();
	}
	return uerror_code;

}

HResult  pecker_shader_program_glsles1::get_uniform_float_value
	(UInt uniform_index,Float* P_INOUT pUniform_value) const
{
	::glGetUniformfv(_M_program,uniform_index,pUniform_value);
	return pecker_opengles_v2_object::get_last_error_code();
}
	
HResult pecker_shader_program_glsles1::get_uniform_int_value(UInt uniform_index,SInt* P_INOUT pUniform_value) const
{
	if (0 != _M_program)
	{
		::glGetUniformiv(_M_program,uniform_index,pUniform_value);
		return pecker_opengles_v2_object::get_last_error_code();
	}
	return P_OK;
}

UInt  pecker_shader_program_glsles1::get_program() const
{
	return _M_program;
}
	
UInt  pecker_shader_program_glsles1::get_frame_shader() const
{
	return _M_frame_shader;
}
	
UInt  pecker_shader_program_glsles1::get_vertex_shader() const
{
	return _M_vertex_shader;
}


pecker_shader_program_glsles1*  pecker_shader_program_glsles1::get_using_program()
{
	return g_pusing_shader_program;
}
HResult pecker_shader_program_glsles1::set_uniform_1float(UInt uniform_index,Float x)
{
	::glUniform1f(uniform_index,x);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_2float(UInt uniform_index,Float x,Float y)
{
	::glUniform2f(uniform_index,x,y);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_3float(UInt uniform_index,Float x,Float y,Float z)
{
	::glUniform3f(uniform_index,x,y,z);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_4float(UInt uniform_index,Float x,Float y,Float z,Float w)
{
	::glUniform4f(uniform_index,x,y,z,w);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_shader_program_glsles1::set_uniform_2float(UInt uniform_index,const pecker_vector2& vector2)
{
	::glUniform2f(uniform_index,vector2.x,vector2.y);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_3float(UInt uniform_index,const pecker_vector3& vector3)
{
	::glUniform3f(uniform_index,vector3.x,vector3.y,vector3.z);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_4float(UInt uniform_index,const pecker_vector4& vector4)
{
	::glUniform4f(uniform_index,vector4.x,vector4.y,vector4.z,vector4.w);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_shader_program_glsles1::set_uniform_1int(UInt uniform_index,SInt x)
{
	::glUniform1i(uniform_index,x);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_2int(UInt uniform_index,SInt x,SInt y)
{
	::glUniform2i(uniform_index,x,y);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_3int(UInt uniform_index,SInt x,SInt y,SInt z)
{
	::glUniform3i(uniform_index,x,y,z);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_4int(UInt uniform_index,SInt x,SInt y,SInt z,SInt w)
{
	::glUniform4i(uniform_index,x,y,z,w);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_shader_program_glsles1::set_uniform_vector1_array(UInt uniform_index,nSize vector_count,const Float* P_IN vector1_array)
{
	::glUniform1fv(uniform_index,vector_count,vector1_array);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_vector2_array(UInt uniform_index,nSize vector_count,const pecker_vector2* P_IN vector2_array)
{
	::glUniform2fv(uniform_index,vector_count,(const GLfloat*)vector2_array);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_vector3_array(UInt uniform_index,nSize vector_count,const pecker_vector3* P_IN vector3_array)
{
	::glUniform3fv(uniform_index,vector_count,(const GLfloat*)vector3_array);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_vector4_array(UInt uniform_index,nSize vector_count,const pecker_vector4* P_IN vector4_array)
{
	::glUniform4fv(uniform_index,vector_count,(const GLfloat*)vector4_array);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_shader_program_glsles1::set_uniform_matrix2_array(UInt uniform_index,nSize matrix_count,const Float* P_IN matrix2_array)
{
	::glUniformMatrix2fv(uniform_index,matrix_count,GL_FALSE,matrix2_array);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_matrix3_array(UInt uniform_index,nSize matrix_count,const pecker_matrix3* P_IN matrix3_array)
{
	::glUniformMatrix3fv(uniform_index,matrix_count,GL_FALSE,(const GLfloat*)matrix3_array);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_uniform_matrix4_array(UInt uniform_index,nSize matrix_count,const pecker_matrix4* P_IN matrix4_array)
{
	::glUniformMatrix4fv(uniform_index,matrix_count,GL_FALSE,(const GLfloat*)matrix4_array);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_shader_program_glsles1::get_vertex_attribute_float_value(UInt attribute_index,HEnum attribute_type,Float* P_OUT pfloat_value)
{
	::glGetVertexAttribfv(attribute_index,attribute_type,pfloat_value);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::get_vertex_attribute_int_value(UInt attribute_index,HEnum attribute_type,SInt* P_OUT pint_value)
{
	::glGetVertexAttribiv(attribute_index,attribute_type,pint_value);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::get_vertex_attribute_pointer_value(UInt attribute_index,HEnum attribute_type,PVoid* P_OUT ppointer)
{
	::glGetVertexAttribPointerv(attribute_index,attribute_type,ppointer);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_shader_program_glsles1::set_vertex_attribute_float1_value(UInt attribute_index,Float x)
{
	::glVertexAttrib1f(attribute_index,x);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_vertex_attribute_float2_value(UInt attribute_index,Float x,Float y)
{
	::glVertexAttrib2f(attribute_index,x,y);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_vertex_attribute_float3_value(UInt attribute_index,Float x,Float y,Float z)
{
	::glVertexAttrib3f(attribute_index,x,y,z);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_vertex_attribute_float4_value(UInt attribute_index,Float x,Float y,Float z,Float w)
{
	::glVertexAttrib4f(attribute_index,x,y,z,w);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_shader_program_glsles1::set_vertex_attribute_vector2_value(UInt attribute_index,const pecker_vector2& vector2)
{
	::glVertexAttrib2f(attribute_index,vector2.x,vector2.y);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_vertex_attribute_vector3_value(UInt attribute_index,const pecker_vector3& vector3)
{
	::glVertexAttrib3f(attribute_index,vector3.x,vector3.y,vector3.z);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::set_vertex_attribute_vector4_value(UInt attribute_index,const pecker_vector4& vector4)
{
	::glVertexAttrib4f(attribute_index,vector4.x,vector4.y,vector4.z,vector4.w);
	return pecker_opengles_v2_object::get_last_error_code();
}

//HResult pecker_shader_program_glsles1::set_vertex_attribute_float1_array(UInt attribute_index,nSize value_count,const Float* P_IN parray)
//{
//	return P_OK;
//}
//HResult pecker_shader_program_glsles1::set_vertex_attribute_vector2_array(UInt attribute_index,nSize vector_count,const pecker_vector2* P_IN vector2_array)
//{
//	return P_OK;
//}
//HResult pecker_shader_program_glsles1::set_vertex_attribute_vector3_array(UInt attribute_index,nSize vector_count,const pecker_vector3* P_IN vector3_array)
//{
//	return P_OK;
//}
//HResult pecker_shader_program_glsles1::set_vertex_attribute_vector4_array(UInt attribute_index,nSize vector_count,const pecker_vector4* P_IN vector4_array)
//{
//	return P_OK;
//}

HResult pecker_shader_program_glsles1::set_vertex_attribute_pointer_value(UInt attribute_index,nSize attribute_size,HEnum attribute_type,
		HFlag nstride,const PVoid P_IN ppointer,HEnum attribute_data_type ,Bool normalized /*= false*/ )
{
	::glVertexAttribPointer(attribute_index,attribute_size,attribute_type,normalized,nstride,ppointer);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_shader_program_glsles1::enable_vertex_attribute_array(UInt attribute_index)
{
	::glEnableVertexAttribArray(attribute_index);
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_shader_program_glsles1::disable_vertex_attribute_array(UInt attribute_index)
{
	::glDisableVertexAttribArray(attribute_index);
	return pecker_opengles_v2_object::get_last_error_code();
}

UInt pecker_shader_program_glsles1::get_object_location() const
{
	return _M_program;
}


PECKER_END
