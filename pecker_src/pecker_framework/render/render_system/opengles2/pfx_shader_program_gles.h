/*
 * pfx_shader_program_gles.h
 *
 *  Created on: 2014-7-20
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHADER_PROGRAM_GLES_H_
#define		PFX_SHADER_PROGRAM_GLES_H_

#include <GLES2/gl2.h>
#include "../pfx_shader_program.h"
#include "../../../pfx_hal_info_gles2.h"
#include "../../../Include/native"
#include "pfx_render_allocator_gles.h"

#define RPROGRAM_DEBUG
#undef  RPROGRAM_LOG_STR
#undef  RPROGRAM_LOG_INFO
#ifdef  RPROGRAM_DEBUG

#define RPROGRAM_LOG_STR PECKER_LOG_STR
#define RPROGRAM_LOG_INFO PECKER_LOG_INFO
#else
#define RPROGRAM_LOG_STR(...)
#define RPROGRAM_LOG_INFO(...)
#endif


PECKER_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#endif



PFX_INLINE GLenum PFX_PRIMODE_2_GLES2_PRIMODE(PFX_PRIMITIVE_MODE_t MODE)
{
	static GLenum glmode[] =
	{
		GL_POINTS,
		GL_LINES,
		GL_LINE_STRIP,
		GL_LINE_LOOP,
		GL_TRIANGLES,
		GL_TRIANGLE_STRIP,
		GL_TRIANGLE_FAN,
		GL_LINES
	};

	return glmode[MODE];
};

class PFX_RENDER_SYSTEM_API cshader_method_gles2
{
public:
	static GLuint compile_shader(
		GLenum __shader_type,
		const GLchar* PARAM_IN str_shader_codes,
		const GLint* PARAM_IN source_size,
		GLint& compiled_status,
		GLsizei source_count =1);

	static void dispose_shader(GLuint& __shader_addr);

	static usize__t get_shader_info_lengh(GLuint __shader_addr);

	static usize__t get_shader_info_log(GLuint __shader_addr,
		char_t* log_info_buff_ptr,
		usize__t log_buff_size);

	static u64_t get_version();
};


class PFX_RENDER_SYSTEM_API cnative_shader_gles2
{
	DECLARE_FRIEND_CLASS(class cshader_gles2);
protected:
	typedef cavl_bst_node < shader_param_t > shader_param_node_t;

private:
	GLuint m_shaderID;
	PFX_SHADER_TYPE_t m_shaderTYPE;	
public:
	cnative_shader_gles2() :m_shaderID(0),
		m_shaderTYPE(PFXST_UNKOWN_SHADER)
	{
		RPROGRAM_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
public:
	virtual ~cnative_shader_gles2()
	{
		dispose();
		RPROGRAM_LOG_INFO("release...0x%08X", (lpointer_t)this);
	}
public:
	PFX_INLINE GLuint get_shader_id() const
	{
		return m_shaderID;
	}
	PFX_INLINE void dispose()
	{
		cshader_method_gles2::dispose_shader(m_shaderID);
	}
public:
	static PFX_INLINE bool check_shader_type(enum_int_t shader_type)
	{
		return (PFXST_VERTEXT_SHADER == shader_type || PFXST_PIXEL_SHADER == shader_type);
	}
	PFX_INLINE result_t set_shader_type(enum_int_t shader_type)
	{
		RETURN_INVALID_RESULT(m_shaderID, PFX_STATUS_DENIED);

		result_t status = PFX_STATUS_INVALID_PARAMS;
		if (!m_shaderID &&
			check_shader_type(shader_type))
		{
			m_shaderTYPE = (PFX_SHADER_TYPE_t)shader_type;
			status = PFX_STATUS_OK;
		}
		return status;
	}
	
	PFX_INLINE long_t compile_shader(
		const char_t* PARAM_IN str_shader_codes,
		usize__t buf_size,
		result_t& status,
		GLsizei source_count = 1)
	{
		if (m_shaderID)
		{
			status = PFX_STATUS_OPENED;
			return m_shaderID;
		}

		GLenum shader_type;
		switch (m_shaderTYPE)
		{
		case PFXST_VERTEXT_SHADER:
			shader_type = GL_VERTEX_SHADER;
			break;
		case PFXST_PIXEL_SHADER:
			shader_type = GL_FRAGMENT_SHADER;
			break;
		default:
			status = PFX_STATUS_UNINIT;
			return 0;
		}

		m_shaderID = cshader_method_gles2::compile_shader
			(shader_type, str_shader_codes, (GLint*)&buf_size, (GLint&)status, source_count);
		return m_shaderID;
	}

	PFX_INLINE long_t get_native_handle()
	{
		return  m_shaderID;
	}

	PFX_INLINE enum_int_t get_type() const
	{
		return m_shaderTYPE;
	}
	static PFX_INLINE u64_t		get_version()
	{
		return cshader_method_gles2::get_version();
	}
};


class PFX_RENDER_SYSTEM_API cshader_gles2 : public Ipfx_shader
{
	typedef   cnative_shader_gles2 native_t;
	DECLARE_FRIEND_CLASS(SHADER_NODE_ALLOC_GLES2);
private:
	native_t m_native;
public:
	DELARE_REF_METHOD(cshader_gles2, Ipfx_shader, shader_node_alloc_gles2_t);
protected:
	cshader_gles2()
	{ 
		RPROGRAM_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
	virtual ~cshader_gles2()
	{
		RPROGRAM_LOG_INFO("release...0x%08X", (lpointer_t)this);
	}
	virtual PFX_INLINE result_t real_dispose()
	{
		return __real_dispose();
	}
public:
	PFX_INLINE static cshader_gles2* new_shader(enum_int_t shader_type)
	{
		cshader_gles2*  new_obj_ptr = create_new_object();
		if (new_obj_ptr)
		{
			result_t status;
			status = new_obj_ptr->native().set_shader_type(shader_type);
			if (PFX_STATUS_OK > status)
			{
				new_obj_ptr->dispose_object();
				new_obj_ptr = null;
			}
		}
		return new_obj_ptr;
	}
	
	PFX_INLINE long_t	compile_shader(const char_t* PARAM_IN str_shader_codes,
		usize__t buf_size,
		result_t& status,
		usize__t source_count = 1,
		const void* PARAM_IN param_ptr = null)
	{
		return this->native().compile_shader(str_shader_codes, buf_size, status, source_count);
	}
	PFX_INLINE long_t	get_native_handle()
	{
		return this->native().get_native_handle();
	}

	PFX_INLINE enum_int_t	get_type() const
	{
		return this->native().get_type();
	}
	PFX_INLINE u64_t get_version() const
	{
		return native_t::get_version();
	}
	PFX_INLINE Ipfx_shader* new_share()
	{
		return new_ref();
	}
	PFX_INLINE result_t dispose_shader()
	{
		return dispose_object();
	}
};





#define INVALID_SHADER (-1)
class PFX_RENDER_SYSTEM_API cnative_shader_program_gles2
{
	DECLARE_FRIEND_CLASS(class cshader_program_gles2);
private:
	GLuint			m_programID;
	cshader_gles2*	m_pixel_shader_ptr;
	cshader_gles2*	m_vertex_shader_ptr;
public:
	typedef cavl_bst_node < shader_param_t >					shader_param_node_t;
	typedef compare_two_node< shader_param_node_t, 
		shader_param_node_t, compare_shader_param_t >			node_cmp_t;
	typedef pfx_binary_search_tree_type < shader_param_node_t,
		node_cmp_t, shader_param_node_allocator_t >
		::avl_binary_search_tree_t								tree_t;
	typedef BST_find_elementx< tree_t,
		cstring_ascii_t, compare_shader_param_ex_t >			find_t;

	typedef BST_find_elementx< tree_t,
		const char_t*,
		compare_shader_param_exchr_t >							find_chr_t;
public:
	static  usize__t  get_program_info_lengh(GLuint __program_id);

	static usize__t  get_program_info_log(GLuint __program_ID,
		char_t* log_info_buff_ptr,
		usize__t log_buff_size);
protected:
	tree_t	m_shader_param_table;
	result_t  parse_shader_param_table();
	result_t  modify_shader_param_table
		(enum_int_t param_type,
		enum_int_t param_value_type,
		const cstring_ascii_t& str_name,
		long_t new_location);
public:
	PFX_INLINE const tree_t& get_shader_param_table() const
	{
		return m_shader_param_table;
	}
	
public:
	 cnative_shader_program_gles2();
public:
	 virtual ~cnative_shader_program_gles2();
public:
	result_t attach_pixel_shader(cshader_gles2* PARAM_INOUT shader_ptr);
	result_t attach_vertex_shader(cshader_gles2* PARAM_INOUT shader_ptr);
	result_t compile_program();

	void  dispose();
public:
	PFX_INLINE GLuint get_program_id() const
	{
		return 	m_programID;
	}
	result_t  use();

	long_t  get_location_by_name
		(const cstring_ascii_t& PARAM_IN str_shader_param_name) const;
	
	long_t	get_location_by_name
		(const char* PARAM_IN str_shader_param_name) const;
	
public:
	PFX_INLINE result_t attach_shader(Ipfx_shader* PARAM_IN shader_ptr)
	{
		if (shader_ptr && 
			shader_ptr->get_version() == get_hal_instanse_ID_gles2().m_version)
		{
			if (PFXST_VERTEXT_SHADER == shader_ptr->get_type())
			{
				return attach_vertex_shader(DYNAMIC_CAST(cshader_gles2*)(shader_ptr));
			}
			else if (PFXST_PIXEL_SHADER == shader_ptr->get_type())
			{
				return attach_pixel_shader(DYNAMIC_CAST(cshader_gles2*)(shader_ptr));
			}
		}
		return PFX_STATUS_INVALID_PARAMS;
	}
	PFX_INLINE long_t get_native_handle() const
	{
		return 	m_programID;
	}

	static u64_t	get_version();
};

class PFX_RENDER_SYSTEM_API cshader_program_gles2 : public Ipfx_shader_program
{
	DECLARE_FRIEND_CLASS(SHADER_PROGRAM_NODE_ALLOC_GLES2);
	typedef cnative_shader_program_gles2 native_t;
private:
	native_t m_native;
protected:
	cshader_program_gles2()	
	{ 
		RPROGRAM_LOG_INFO("create...0x%08X", (lpointer_t)this); 
	}
	virtual ~cshader_program_gles2() 
	{ 
		RPROGRAM_LOG_INFO("release...0x%08X", (lpointer_t)this); 
	}
	virtual PFX_INLINE result_t real_dispose()
	{
		return __real_dispose();
	}
public:
	DELARE_REF_METHOD(cshader_program_gles2, 
		Ipfx_shader_program, 
		shader_program_node_gles2_t);
public:

	PFX_INLINE result_t compile_program()
	{
		return this->native().compile_program();
	}

	PFX_INLINE long_t get_location_by_name(const cstring_ascii_t& PARAM_IN
		str_shader_param_name) const
	{
		return this->native().get_location_by_name(str_shader_param_name);
	}

	PFX_INLINE long_t get_location_by_name
		(const char* PARAM_IN
		str_shader_param_name) const
	{
		return this->native().get_location_by_name(str_shader_param_name);
	}

	PFX_INLINE result_t attach_shader(Ipfx_shader* PARAM_IN shader_ptr)
	{
		return this->native().attach_shader(shader_ptr);
	}


	PFX_INLINE const tree_t*  get_shader_param_table() const
	{
		return 	&(this->native().get_shader_param_table());
	}

	PFX_INLINE long_t get_native_handle()
	{
		return this->native().get_native_handle();
	}

	PFX_INLINE u64_t get_version() const
	{
		return native_t::get_version();
	}

	PFX_INLINE Ipfx_shader_program* new_share()
	{
		return new_ref();
	}

	PFX_INLINE result_t dispose_program()
	{
		return dispose_object();
	}

	PFX_INLINE result_t use()
	{
		return this->native().use();
	}
};



#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_SHADER_PROGRAM_GLES_H_
