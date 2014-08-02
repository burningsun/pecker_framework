﻿/*
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

template <const GLenum SHADER_TYPE >
class PFX_RENDER_SYSTEM_API cnative_shader_gles2
{
protected:
	typedef cavl_bst_node < shader_param_t > shader_param_node_t;

private:
	GLuint m_shaderID;
public:
	cnative_shader_gles2() :m_shaderID(0){ ; }
	~cnative_shader_gles2()
	{
		dispose();
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
protected:


public:
	PFX_INLINE long_t compile_shader(const char_t* PARAM_IN str_shader_codes,
		usize__t buf_size,
		result_t& status,
		GLsizei source_count = 1)
	{
		if (m_shaderID)
		{
			status = PFX_STATUS_OPENED;
			return m_shaderID;
		}
		m_shaderID = cshader_method_gles2::compile_shader
			(SHADER_TYPE, str_shader_codes, (GLint*)&buf_size, (GLint&)status, source_count);
		return m_shaderID;
	}

	PFX_INLINE long_t get_native_handle()
	{
		return  m_shaderID;
	}

	static PFX_INLINE enum_int_t get_type();
	static PFX_INLINE u64_t		get_version() 
	{
		return cshader_method_gles2::get_version();
	}
};

template <const GLenum SHADER_TYPE >
PFX_INLINE enum_int_t cnative_shader_gles2< SHADER_TYPE >::get_type()  //PFX_SHADER_TYPE_t
{
	return PFXST_UNKOWN_SHADER;
}

template<>
PFX_INLINE enum_int_t cnative_shader_gles2< GL_VERTEX_SHADER >::get_type()
{
	return PFXST_VERTEXT_SHADER;
}
template<>
PFX_INLINE enum_int_t cnative_shader_gles2< GL_FRAGMENT_SHADER >::get_type()
{
	return PFXST_PIXEL_SHADER;
}

typedef cnative_shader_gles2< GL_VERTEX_SHADER >	cnative_vertex_shder_gles2_t;
typedef cnative_shader_gles2< GL_FRAGMENT_SHADER >	cnative_pixel_shder_gles2_t;

template <const GLenum SHADER_TYPE >
class  PFX_RENDER_SYS_TEMPLATE_API cshader_gles2 : public creference_base< cnative_shader_gles2< SHADER_TYPE > >,
					public Ipfx_shader
{
protected:
	typedef  cnative_shader_gles2< SHADER_TYPE > ref_element_t;
	typedef  creference_base< cnative_shader_gles2< SHADER_TYPE > > ref_t;
	typedef typename ref_t::element_t element_t;
public:
	PFX_INLINE ref_element_t* get_native_shader()
	{
		return 	ref_t::get_reference();
	}
	PFX_INLINE long_t	compile_shader(const char_t* PARAM_IN str_shader_codes,
		usize__t buf_size,
		result_t& status,
		usize__t source_count = 1,
		const void* PARAM_IN param_ptr = null)
	{
		release_reference();
		ref_element_t* ref_ptr = ref_t::create_ref_element();
		if (ref_ptr)
		{
			return ref_ptr->compile_shader(str_shader_codes, buf_size, status, source_count);
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}
	PFX_INLINE long_t	get_native_handle()
	{
		ref_element_t* ref_ptr = ref_t::get_reference();
		if (ref_ptr)
		{
			return ref_ptr->get_native_handle();
		}
		else
		{
			return 0;
		}
	}
	PFX_INLINE enum_int_t	get_type() const
	{
		return ref_element_t::get_type();
	}
	PFX_INLINE u64_t get_version() const
	{
		return ref_element_t::get_version();
	}
	PFX_INLINE void	 release_reference()
	{
		ref_t::release_reference();
	}

protected:
	PFX_INLINE ref_element_t* create_element()
	{
		return new ref_element_t;
	}
	PFX_INLINE result_t dispose_element(element_t*& elem_ptr)
	{
		if (elem_ptr)
		{
			delete elem_ptr;
			elem_ptr = null;
		}
		return PFX_STATUS_OK;
	}
};

typedef cshader_gles2< GL_VERTEX_SHADER >	cvertex_shader_gles2_t;
typedef cshader_gles2< GL_FRAGMENT_SHADER >	cpixel_shder_gles2_t;



#define INVALID_SHADER (-1)
class PFX_RENDER_SYSTEM_API cnative_shader_program_gles2
{
private:
	GLuint					m_programID;
	cpixel_shder_gles2_t	m_pixel_shader;
	cvertex_shader_gles2_t	m_vertex_shader;
public:



	typedef cavl_bst_node < shader_param_t >					shader_param_node_t;
	typedef compare_two_node< shader_param_node_t, 
		shader_param_node_t, compare_shader_param_t >			node_cmp_t;
	typedef pfx_binary_search_tree_type < shader_param_node_t,
		node_cmp_t, shader_param_node_allocator_t >
		::avl_binary_search_tree_t								tree_t;
	typedef BST_find_elementx< tree_t,
		cstring_ascii_t, compare_shader_param_ex_t >			find_t;



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
	 ~cnative_shader_program_gles2();
public:
	PFX_INLINE result_t attach_pixel_shader(cpixel_shder_gles2_t* PARAM_INOUT shader_ptr)
	{
		if (!shader_ptr)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		//m_pixel_shader.release_reference();
		shader_ptr->share_to(&m_pixel_shader);
		return PFX_STATUS_OK;
	}
	PFX_INLINE result_t attach_vertex_shader(cvertex_shader_gles2_t* PARAM_INOUT shader_ptr)
	{
		if (!shader_ptr)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		//m_vertex_shader.release_reference();
		shader_ptr->share_to(&m_vertex_shader);
		return PFX_STATUS_OK;
	}
	result_t  compile_program();

	void  dispose();
public:
	PFX_INLINE GLuint get_program_id() const
	{
		return 	m_programID;
	}
	result_t  use();

	long_t  get_location_by_name
		(const cstring_ascii_t& PARAM_IN str_shader_param_name) const;
	
public:
	PFX_INLINE result_t attach_shader(Ipfx_shader* PARAM_IN shader_ptr)
	{
		if (shader_ptr && 
			shader_ptr->get_version() == get_hal_instanse_ID().m_version)
		{
			if (PFXST_VERTEXT_SHADER == shader_ptr->get_type())
			{
				return attach_vertex_shader(DYNAMIC_CAST(cvertex_shader_gles2_t*)(shader_ptr));
			}
			else if (PFXST_PIXEL_SHADER == shader_ptr->get_type())
			{
				return attach_pixel_shader(DYNAMIC_CAST(cpixel_shder_gles2_t*)(shader_ptr));
			}
		}
		return PFX_STATUS_INVALID_PARAMS;
	}
	PFX_INLINE long_t get_native_handle() const
	{
		return 	m_programID;
	}

	static  u64_t	get_version();
};



class  cshader_program_gles2 : public creference_base< cnative_shader_program_gles2 >,
	public Ipfx_shader_program
{
protected:
	typedef  cnative_shader_program_gles2						ref_element_t;
	typedef  creference_base< cnative_shader_program_gles2 >	ref_t;
public:
	PFX_INLINE ref_element_t* get_native_shader_pragram()
	{
		return 	get_reference();
	}
	PFX_INLINE result_t	compile_program()
	{
		ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->compile_program();
		}
		else
		{
			return PFX_STATUS_INVALID_PARAMS;
		}

	}
	PFX_INLINE long_t		get_location_by_name
		(const cstring_ascii_t& PARAM_IN
		str_shader_param_name) const
	{
		const ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->get_location_by_name(str_shader_param_name);
		}
		else
		{
			return 0;
		}
	}
	
	PFX_INLINE result_t	attach_shader(Ipfx_shader* PARAM_IN shader_ptr)
	{
		ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->attach_shader(shader_ptr);
		}
		else
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
	}

	virtual  const tree_t* get_shader_param_table() const
	{
		const ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return &(ref_ptr->get_shader_param_table());
		}
		else
		{
			return null;
		}
	}

	PFX_INLINE long_t	get_native_handle()
	{
		ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->get_native_handle();
		}
		else
		{
			return 0;
		}
	}

	PFX_INLINE u64_t get_version() const
	{
		return ref_element_t::get_version();
	}
	PFX_INLINE void	 release_reference()
	{
		ref_t::release_reference();
	}

protected:
	PFX_INLINE ref_element_t* create_element()
	{
		return new ref_element_t;
	}
	PFX_INLINE result_t dispose_element(element_t*& elem_ptr)
	{
		if (elem_ptr)
		{
			delete elem_ptr;
			elem_ptr = null;
		}
		return PFX_STATUS_OK;
	}
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_SHADER_PROGRAM_GLES_H_
