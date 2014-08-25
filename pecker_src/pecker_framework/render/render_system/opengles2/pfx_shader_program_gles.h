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
#endif

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


class PFX_RENDER_SYSTEM_API native_shader_gles2
{
	DECLARE_FRIEND_CLASS(class shader_gles2);
	DECLARE_FRIEND_CLASS(SHADER_ALLOC_GLES2);

	DEFINE_NATIVE_REF_POOL(SHADER_NODE_ALLOC_GLES2, SHADER_ALLOC_GLES2, m_ref_pool);

protected:
	DECLARE_NATIVE_CREATE_NEW_NODE(shader_gles2, create_shader_node);
	DECLARE_NATIVE_CREATE_SHARE_NODE(shader_gles2, share_shader_node);
	DECLARE_NATIVE_DISPOSE_SHARE_NODE(shader_gles2, dispose_shader_node);
protected:
	typedef cavl_bst_node < shader_param_t > shader_param_node_t;

private:
	GLuint m_shaderID;
	PFX_SHADER_TYPE_t m_shaderTYPE;
	
private:
	native_shader_gles2() :m_shaderID(0),
		m_shaderTYPE(PFXST_UNKOWN_SHADER)
	{
		RPROGRAM_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
public:
	virtual ~native_shader_gles2()
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


class PFX_RENDER_SYSTEM_API shader_gles2;

DECLARE_REF_NODE_CLASS_PROTECTED_BEGIN(shader_gles2,
native_shader_gles2, Ipfx_shader, base_t,
shader_node_alloc_gles2_t,
native_shader_gles2_t)

DECLARE_FRIEND_CLASS(class native_shader_gles2);
DECLARE_FRIEND_CLASS(SHADER_NODE_ALLOC_GLES2);

//
public:
	DECLARE_REF_CREATE_NEW_NODE(shader_gles2, new_shader);
	DECLARE_REF_CREATE_SHARE_NODE(shader_gles2, new_share_shader);
	DECLARE_REF_DISPOSE_SHARE_NODE(shader_gles2, dispose_shader);
private:
	shader_gles2(){ RPROGRAM_LOG_INFO("create...0x%08X", (lpointer_t)this); }
public:
	virtual ~shader_gles2(){ dispose_shader(); RPROGRAM_LOG_INFO("release...0x%08X", (lpointer_t)this); };
	
public:
	static shader_gles2* new_shader(enum_int_t shader_type);
	
	long_t	compile_shader(const char_t* PARAM_IN str_shader_codes,
		usize__t buf_size,
		result_t& status,
		usize__t source_count = 1,
		const void* PARAM_IN param_ptr = null);
	
	long_t	get_native_handle();
	enum_int_t	get_type() const;
	u64_t		get_version() const;

	PFX_INLINE Ipfx_shader* new_share()
	{
		return new_shader();
	}

DECLARE_REF_NODE_CLASS_END

//////////////////////////////////////////////////////////////////////////
STATIC_NATIVE_CREATE_NEW_NODE(native_shader_gles2, shader_gles2, create_shader_node);
NATIVE_CREATE_SHARE_NODE(native_shader_gles2, shader_gles2, share_shader_node, m_ref_pool);
NATIVE_DISPOSE_SHARE_NODE(native_shader_gles2, shader_gles2, dispose_shader_node, m_ref_pool);
//////////////////////////////////////////////////////////////////////////
STATIC_REF_CREATE_NEW_NODE(native_shader_gles2, shader_gles2,
	new_shader, create_shader_node);
REF_CREATE_SHARE_NODE(base_t, shader_gles2, new_share_shader, share_shader_node);
REF_DISPOSE_SHARE_NODE(base_t, shader_gles2, dispose_shader, dispose_shader_node);



#define INVALID_SHADER (-1)
class PFX_RENDER_SYSTEM_API native_shader_program_gles2
{
	DECLARE_FRIEND_CLASS(class shader_program_gles2);
	DECLARE_FRIEND_CLASS(SHADER_PROGRAM_ALLOC_GLES2);
	DEFINE_NATIVE_REF_POOL(SHADER_PROGRAM_NODE_ALLOC_GLES2, SHADER_PROGRAM_ALLOC_GLES2, m_ref_pool);
protected:
	DECLARE_NATIVE_CREATE_NEW_NODE(shader_program_gles2, create_program_node);
	DECLARE_NATIVE_CREATE_SHARE_NODE(shader_program_gles2, share_program_node);
	DECLARE_NATIVE_DISPOSE_SHARE_NODE(shader_program_gles2, dispose_program_node);
private:
	GLuint			m_programID;
	shader_gles2*	m_pixel_shader_ptr;
	shader_gles2*	m_vertex_shader_ptr;
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
private:
	 native_shader_program_gles2();
public:
	 virtual ~native_shader_program_gles2();
public:
	result_t attach_pixel_shader(shader_gles2* PARAM_INOUT shader_ptr);
	result_t attach_vertex_shader(shader_gles2* PARAM_INOUT shader_ptr);
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
			shader_ptr->get_version() == get_hal_instanse_ID().m_version)
		{
			if (PFXST_VERTEXT_SHADER == shader_ptr->get_type())
			{
				return attach_vertex_shader(DYNAMIC_CAST(shader_gles2*)(shader_ptr));
			}
			else if (PFXST_PIXEL_SHADER == shader_ptr->get_type())
			{
				return attach_pixel_shader(DYNAMIC_CAST(shader_gles2*)(shader_ptr));
			}
		}
		return PFX_STATUS_INVALID_PARAMS;
	}
	PFX_INLINE long_t get_native_handle() const
	{
		return 	m_programID;
	}

	u64_t	get_version() const;
};

class PFX_RENDER_SYSTEM_API shader_program_gles2;

DECLARE_REF_NODE_CLASS_PROTECTED_BEGIN(shader_program_gles2,
native_shader_program_gles2, Ipfx_shader_program, base_t,
shader_program_node_gles2_t,
native_shader_program_gles2_t)
//
DECLARE_FRIEND_CLASS(class native_shader_program_gles2);
DECLARE_FRIEND_CLASS(SHADER_PROGRAM_NODE_ALLOC_GLES2);

public:
	DECLARE_REF_CREATE_NEW_NODE(shader_program_gles2, new_program);
	DECLARE_REF_CREATE_SHARE_NODE(shader_program_gles2, new_share_program);
	DECLARE_REF_DISPOSE_SHARE_NODE(shader_program_gles2, dispose_program);
private:
	shader_program_gles2()	{ RPROGRAM_LOG_INFO("create...0x%08X", (lpointer_t)this); }
	
public:
	virtual ~shader_program_gles2() { dispose_program(); RPROGRAM_LOG_INFO("release...0x%08X", (lpointer_t)this); }

public:
	PFX_INLINE result_t compile_program()
	{
		if (this->ref_ptr())
		{
			return this->ref_ptr()->compile_program();
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}

	PFX_INLINE long_t get_location_by_name(const cstring_ascii_t& PARAM_IN
		str_shader_param_name) const
	{
		if (this->ref_ptr())
		{
			return this->ref_ptr()->get_location_by_name(str_shader_param_name);
		}
		else
		{
			return -1;
		}
	}

	PFX_INLINE long_t get_location_by_name
		(const char* PARAM_IN
		str_shader_param_name) const
	{
		if (this->ref_ptr())
		{
			return this->ref_ptr()->get_location_by_name(str_shader_param_name);
		}
		else
		{
			return -1;
		}
	}

	PFX_INLINE result_t attach_shader(Ipfx_shader* PARAM_IN shader_ptr)
	{
		if (this->ref_ptr())
		{
			return this->ref_ptr()->attach_shader(shader_ptr);
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}


	PFX_INLINE const tree_t*  get_shader_param_table() const
	{
		if (this->ref_ptr())
		{
			return &(this->ref_ptr()->get_shader_param_table());
		}
		else
		{
			return null;
		}
	}
	
	PFX_INLINE long_t get_native_handle()
	{
		if (this->ref_ptr())
		{
			return this->ref_ptr()->get_native_handle();
		}
		else
		{
			return 0;
		}
	}
	
	PFX_INLINE u64_t get_version() const
	{
		if (this->ref_ptr())
		{
			return this->ref_ptr()->get_version();
		}
		else
		{
			return 	0;
		}
	}

	PFX_INLINE Ipfx_shader_program* new_share()
	{
		return new_share_program();
	}

	PFX_INLINE result_t use()
	{
		if (this->ref_ptr())
		{
			return this->ref_ptr()->use();
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}


DECLARE_REF_NODE_CLASS_END

//////////////////////////////////////////////////////////////////////////
STATIC_NATIVE_CREATE_NEW_NODE(native_shader_program_gles2, shader_program_gles2, create_program_node);
NATIVE_CREATE_SHARE_NODE(native_shader_program_gles2, shader_program_gles2, share_program_node, m_ref_pool);
NATIVE_DISPOSE_SHARE_NODE(native_shader_program_gles2, shader_program_gles2, dispose_program_node, m_ref_pool);
//////////////////////////////////////////////////////////////////////////
STATIC_REF_CREATE_NEW_NODE(native_shader_program_gles2, shader_program_gles2,
	new_program, create_program_node);
REF_CREATE_SHARE_NODE(base_t, shader_program_gles2, new_share_program, share_program_node);
REF_DISPOSE_SHARE_NODE(base_t, shader_program_gles2, dispose_program, dispose_program_node);



#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_SHADER_PROGRAM_GLES_H_
