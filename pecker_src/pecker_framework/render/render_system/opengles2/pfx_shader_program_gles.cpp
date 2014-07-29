/*
 * pfx_shader_program_gles.cpp
 *
 *  Created on: 2014-7-23
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_shader_program_gles.h"
#include "../../../native/pfx_log.h"

PECKER_BEGIN

GLuint cshader_method_gles2::compile_shader(GLenum __shader_type,
									const GLchar* PARAM_IN str_shader_codes,
									const GLint* PARAM_IN source_size,
									GLint& compiled_status,
									GLsizei source_count //=1
									)
{
	// 创建着色器
	GLuint shader = glCreateShader(__shader_type);
	if (shader)
	{
		//编译着色源代码
		const GLchar* pSource = (GLchar*)(str_shader_codes);
		::glShaderSource(shader, source_count, &pSource, source_size);
		::glCompileShader(shader);
		compiled_status = 0;
		//获取编译结果
		::glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled_status);
		if (!compiled_status)
		{
			::glDeleteShader(shader);
			shader = 0;
		}
	}
	else
	{
		compiled_status = -1;
	}
	return shader;
}

void cshader_method_gles2::dispose_shader(GLuint& __shader_addr)
{
	if (__shader_addr)
	{
		::glDeleteShader(__shader_addr);
		__shader_addr = 0;
	}
}

usize__t cshader_method_gles2::get_shader_info_lengh(GLuint __shader_addr)
{
	GLint info_length = 0;
	::glGetShaderiv(__shader_addr, GL_INFO_LOG_LENGTH, &info_length);
	return info_length;
}

usize__t cshader_method_gles2::get_shader_info_log(GLuint __shader_addr,
	char_t* log_info_buff_ptr,
	usize__t log_buff_size)
{
	if (!log_info_buff_ptr || !log_buff_size)
	{
		return 0;
	}
	usize__t info_length = get_shader_info_lengh(__shader_addr);
	::glGetShaderInfoLog(__shader_addr, info_length,
		(GLsizei*)&log_buff_size, log_info_buff_ptr);
	return log_buff_size;
}

u64_t cshader_method_gles2::get_version()
{
	return (get_hal_instanse_ID().m_version);
}

PFX_INLINE_CODE enum_int_t glspt_to_pfxspt(GLenum __type)
{
	enum_int_t __pfx_type;
	switch (__type)
	{
	case GL_FLOAT:
		__pfx_type = PFXSPT_FLOAT1;
		break;
	case GL_FLOAT_VEC2:
		__pfx_type = PFXSPT_FLOAT2;
		break;
	case GL_FLOAT_VEC3:
		__pfx_type = PFXSPT_FLOAT3;
		break;
	case GL_FLOAT_VEC4:
		__pfx_type = PFXSPT_FLOAT4;
		break;
	case GL_INT:
		__pfx_type = PFXSPT_INT1;
		break; 
	case GL_INT_VEC2:
		__pfx_type = PFXSPT_INT2;
		break;
	case GL_INT_VEC3:
		__pfx_type = PFXSPT_INT3;
		break;
	case GL_INT_VEC4:
		__pfx_type = PFXSPT_INT4;
		break;
	case GL_BOOL:
		__pfx_type = PFXSPT_BOOL1;
		break;
	case GL_BOOL_VEC2:
		__pfx_type = PFXSPT_BOOL2;
		break;
	case GL_BOOL_VEC3:
		__pfx_type = PFXSPT_BOOL3;
		break;
	case GL_BOOL_VEC4:
		__pfx_type = PFXSPT_BOOL4;
		break;
	case GL_FLOAT_MAT2:
		__pfx_type = PFXSPT_MATRIX_2X2;
		break;
	case GL_FLOAT_MAT3:
		__pfx_type = PFXSPT_MATRIX_3X3;
		break;
	case GL_FLOAT_MAT4:
		__pfx_type = PFXSPT_MATRIX_4X4;
		break;
	case GL_SAMPLER_2D:
		__pfx_type = PFXSPT_SAMPLER2D;
		break;
	case GL_SAMPLER_CUBE:
		__pfx_type = PFXSPT_SAMPLERCUBE;
		break;


	default:
		__pfx_type = PFXSPT_UNKNOWN_SHADER_PARAM_TYPE;
		break;
	}
	return __pfx_type;
}

cnative_shader_program_gles2::cnative_shader_program_gles2() :m_programID(0)
{
	;
}
cnative_shader_program_gles2::~cnative_shader_program_gles2()
{
	dispose();
}

result_t cnative_shader_program_gles2::parse_shader_param_table()
{
	tree_t temp_tree;
	result_t status;
	// Query and store uniforms from the program.
	GLint activeUniforms;
	cstring_ascii_t str_name;

	FOR_ONE_LOOP_BEGIN

	if (!m_programID)
	{
		status = PFX_STATUS_OK;
		break;
	}
	str_name.init_string(16);

	// uniform
	glGetProgramiv(m_programID, GL_ACTIVE_UNIFORMS, &activeUniforms);
	if (activeUniforms > 0)
	{
		GLint length;
		glGetProgramiv(m_programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
		if (length > 0)
		{
			for (int i = 0; i < activeUniforms; ++i)
			{
				tree_t::node_t* node_ptr = tree_t::new_node();
				if (!node_ptr)
				{
					status = PFX_STATUS_MEM_LOW;
					break;
				}

				node_ptr->get_item_ref().m_name.init_string(length + 1);

				// Query uniform info.
				GLsizei uniform_size = 0;
				GLenum value_type = 0;
				glGetActiveUniform(m_programID, i, length, nullptr, &uniform_size, 
					&value_type,
					(GLchar*)(node_ptr->get_item_ref().m_name.get_string()));
				if (uniform_size)
				{
					node_ptr->get_item_ref().m_value_type = glspt_to_pfxspt(value_type);
					node_ptr->get_item_ref().m_name.resize_string(uniform_size);
					node_ptr->get_item_ref().m_name.reference(uniform_size - 1) = '\0';
				}

				node_ptr->get_item_ref().m_type = PFX_UNIFORM_VALUE;
				

				// Only add uniforms that are not built-in.
				// The ones that start with 'CC_' are built-ins
				const char_t* str_ptr = node_ptr->get_item().m_name.get_string();
				if (strncmp("CC_", str_ptr, 3) != 0) 
				{

					// remove possible array '[]' from uniform name
					if (node_ptr->get_item().m_name.get_length() > 1 && length > 3)
					{
						char* c = (char*)strrchr(str_ptr, '[');
						if (c)
						{
							*c = '\0';
						}
					}
	
					node_ptr->get_item_ref().m_location = glGetUniformLocation(m_programID, str_ptr);
					GLenum __gl_error_code = glGetError();
					if (__gl_error_code != GL_NO_ERROR)
					{
						PECKER_LOG_("error: 0x%x", (int)__gl_error_code);
						tree_t::release_node(node_ptr);
						break;
					}

					temp_tree.add(node_ptr, status);
					if (PFX_STATUS_OK != status)
					{
						tree_t::release_node(node_ptr);
						break;
					}
				}
				else
				{
					tree_t::release_node(node_ptr);
					break;
				}
			}
		}
	}

	BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);

	// Query and store vertex attribute meta-data from the program.
	GLint activeAttributes;
	GLint length;
	glGetProgramiv(m_programID, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
	if (activeAttributes > 0)
	{
		glGetProgramiv(m_programID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
		if (length > 0)
		{
			for (int i = 0; i < activeAttributes; ++i)
			{
				tree_t::node_t* node_ptr = tree_t::new_node();
				if (!node_ptr)
				{
					status = PFX_STATUS_MEM_LOW;
					break;
				}

				node_ptr->get_item_ref().m_name.init_string(length + 1);

				// Query attribute info.
				GLsizei attribute_size = 0;
				GLenum value_type = 0;
				glGetActiveAttrib(m_programID, i, length, nullptr, &attribute_size, 
					&value_type, 
					(GLchar*)(node_ptr->get_item_ref().m_name.get_string()));
				if (attribute_size)
				{
					node_ptr->get_item_ref().m_value_type = glspt_to_pfxspt(value_type);
					node_ptr->get_item_ref().m_name.resize_string(attribute_size);
					node_ptr->get_item_ref().m_name.reference(attribute_size - 1) = '\0';
				}

				node_ptr->get_item_ref().m_type = PFX_VERTEX_VALUE;

				// Query the pre-assigned attribute location
				node_ptr->get_item_ref().m_location = glGetAttribLocation(m_programID, 
					node_ptr->get_item_ref().m_name.get_string());

				GLenum __gl_error_code = glGetError();
				if (__gl_error_code != GL_NO_ERROR)
				{
					PECKER_LOG_("error: 0x%x", (int)__gl_error_code);
					tree_t::release_node(node_ptr);
					break;
				}
				
				temp_tree.add(node_ptr, status);

				if (PFX_STATUS_OK != status)
				{
					tree_t::release_node(node_ptr);
					break;
				}
			}

		}
	}

	FOR_ONE_LOOP_END
	if (PFX_STATUS_OK == status)
	{
		temp_tree.swap(m_shader_param_table);
	}
	
	return status;
}
result_t cnative_shader_program_gles2::modify_shader_param_table
(enum_int_t param_type,
enum_int_t param_value_type,
const cstring_ascii_t& str_name,
long_t new_location)
{
	tree_t::const_inorder_itr_t __itr;
	tree_t::const_inorder_itr_t* __itr_ptr;
	result_t status;
	__itr_ptr = m_shader_param_table.root(__itr);

	status = PFX_STATUS_FAIL;
	FOR_ONE_LOOP_BEGIN
	if (__itr_ptr)
	{
		__itr_ptr = find_t::find_node(str_name, __itr);
		find_t::node_t* node_ptr = null;
		if (__itr_ptr)
		{
			node_ptr = (find_t::node_t*)__itr_ptr->cur_node();
		}
		if (node_ptr)
		{
			if (node_ptr->get_item().m_type != param_type || 
				node_ptr->get_item().m_value_type != param_value_type)
			{
				status = PFX_STATUS_INVALID_PARAMS;
				break;
			}
			node_ptr->get_item_ref().m_location = new_location;
			status = PFX_STATUS_OK;
			break;
		}
	}

	tree_t::node_t* new_node_ptr = tree_t::new_node();
	if (new_node_ptr)
	{
		str_name.copy_to(new_node_ptr->get_item_ref().m_name);
		new_node_ptr->get_item_ref().m_location = new_location;
		new_node_ptr->get_item_ref().m_type = param_type;
		new_node_ptr->get_item_ref().m_value_type = param_value_type;
		m_shader_param_table.add(new_node_ptr, status);
		if (PFX_STATUS_OK != status)
		{
			tree_t::release_node(new_node_ptr);
		}
		break;
	}
	else
	{
		status = PFX_STATUS_MEM_LOW;
		break;
	}
	FOR_ONE_LOOP_END

	return status;
}


usize__t PFX_RENDER_SYSTEM_API cnative_shader_program_gles2::get_program_info_lengh(GLuint __program_id)
{
	GLsizei infoLen = 0;
	glGetProgramiv(__program_id, GL_INFO_LOG_LENGTH, &infoLen);
	return infoLen;
}

usize__t PFX_RENDER_SYSTEM_API cnative_shader_program_gles2::get_program_info_log(GLuint __program_ID,
	char_t* log_info_buff_ptr,
	usize__t log_buff_size)
{
	if (!log_info_buff_ptr || !log_buff_size)
	{
		return 0;
	}

	GLsizei infoLen = get_program_info_lengh(__program_ID);
	::glGetProgramInfoLog(__program_ID, infoLen, (GLsizei*)&log_buff_size, (GLchar*)log_info_buff_ptr);
	return log_buff_size;
}

result_t cnative_shader_program_gles2::compile_program()
{
	if (m_programID)
	{
		return 0;
	}
	else
	{
		m_programID = glCreateProgram();
	}

	cnative_vertex_shder_gles2_t* vertex_shader_ptr = m_vertex_shader.get_native_shader();
	cnative_pixel_shder_gles2_t* pixel_shader_ptr = m_pixel_shader.get_native_shader();

	if (m_programID &&
		vertex_shader_ptr &&
		vertex_shader_ptr->get_shader_id() &&
		pixel_shader_ptr &&
		pixel_shader_ptr->get_shader_id())
	{
		glAttachShader(m_programID, pixel_shader_ptr->get_shader_id());
		glAttachShader(m_programID, pixel_shader_ptr->get_shader_id());
		glLinkProgram(m_programID);
		GLint linked = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			glDeleteProgram(m_programID);
			m_programID = 0;
		}
		else
		{
			parse_shader_param_table();
		}
		return linked;
	}

	return -1;
}
void cnative_shader_program_gles2::dispose()
{
	glDeleteProgram(m_programID);
	m_programID = 0;
	m_pixel_shader.release_reference();
	m_vertex_shader.release_reference();
}

result_t  cnative_shader_program_gles2::use()
{
	glUseProgram(m_programID);
	if (m_programID)
	{
		return PFX_STATUS_OK;
	}
	return PFK_STATUS_SUCCESS;
}

long_t cnative_shader_program_gles2:: get_location_by_name
(const cstring_ascii_t& PARAM_IN str_shader_param_name) const
{
	tree_t::const_inorder_itr_t __itr;
	tree_t::const_inorder_itr_t* __itr_ptr;
	//result_t status;
	__itr_ptr = m_shader_param_table.root(__itr);
	if (__itr_ptr && __itr_ptr->cur_node())
	{
		__itr_ptr = find_t::find_node(str_shader_param_name, __itr);
		if (__itr_ptr && __itr_ptr->cur_node())
		{
			return __itr_ptr->cur_node()->get_item().m_location;
		}
	}
	return INVALID_SHADER;
}

u64_t cnative_shader_program_gles2::get_version()
{
	return (get_hal_instanse_ID().m_version);
}

PECKER_END


