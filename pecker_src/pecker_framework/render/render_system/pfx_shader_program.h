/*
 * pfx_shader_program.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHADER_PROGRAM_H_
#define		PFX_SHADER_PROGRAM_H_

#include "../../include/config"

PECKER_BEGIN

typedef enum enumSHADER_PARAM_TYPE
{
	PFXSPT_UNKNOWN_SHADER_PARAM_TYPE = 0,

	PFXSPT_FLOAT1,
	PFXSPT_FLOAT2,
	PFXSPT_FLOAT3,
	PFXSPT_FLOAT4,
	PFXSPT_INT1,
	PFXSPT_INT2,
	PFXSPT_INT3,
	PFXSPT_INT4,

	PFXSPT_MATRIX_2X2,
	PFXSPT_MATRIX_2X3,
	PFXSPT_MATRIX_2X4,
	PFXSPT_MATRIX_3X2,
	PFXSPT_MATRIX_3X3,
	PFXSPT_MATRIX_3X4,
	PFXSPT_MATRIX_4X2,
	PFXSPT_MATRIX_4X3,
	PFXSPT_MATRIX_4X4,

	PFXSPT_SAMPLER1D,
	PFXSPT_SAMPLER2D,
	PFXSPT_SAMPLER3D,
	PFXSPT_SAMPLERCUBE,
	PFXSPT_SAMPLER1DSHADOW,
	PFXSPT_SAMPLER2DSHADOW,
	PFXSPT_SAMPLER2DARRAY,

	PFXSPT_SHADER_PARAM_TYPE_COUNT
}PFX_SHADER_PARAM_TYPE_t;

//typedef void* pfx_unknown_shader_param_object_t;

typedef enum enumSHADER_TYPE
{
	PFXST_VERTEXT_SHADER = 0,
	PFXST_PIXEL_SHADER,
	PFXST_SHADER_TYPE_COUNT
}PFX_SHADER_TYPE_t;

typedef enum enumPrimitiveMode
{
	PFX_PRI_POINTS = 0,
	PFX_PRI_LINES,
	PFX_PRI_LINE_STRIP,
	PFX_PRI_LINE_LOOP,
	PFX_PRI_TRIANGLES,
	PFX_PRI_TRIANGLE_STRIP,
	PFX_PRI_TRIANGLE_FAN,

	PFX_PRIMITIVE_MODE_COUNT
}PFX_PRIMITIVE_MODE_t;

struct shader_pps //program param structure
{
	enum_int_t	m_type;
	void *				m_name;
	usize__t			m_name_len;

	void*				m_variables;
	enum_int_t	m_var_type;

	index_t			m_index;
	bool_t				m_modify;

	shader_pps () : m_name(null), m_name_len(0),
		m_variables(null), m_var_type(0), m_index (INVALID_VALUE),
		m_modify (PFX_BOOL_FALSE)
	{
		;
	}
};


// shader 处理器
PFX_Interface Ipfx_shader
{
	virtual long_t			compile_shader (const char_t* PARAM_IN str_shader_codes, 
																		usize__t buf_size, 
																		const void* PARAM_IN param_ptr = null) = 0;
	virtual result_t			reloacation (long_t __locate) = 0;
	virtual long_t			get_shader_location () = 0;
	virtual enum_int_t	get_type () const = 0; //PFX_SHADER_TYPE_t
	virtual const shader_pps*query_shader_info (usize__t& __pps_count) const = 0;
};

PFX_Interface Ipfx_shader_program
{
	virtual ~Ipfx_shader_program(){;}

	// shader 处理程序
	virtual result_t link_shader (Ipfx_shader* PARAM_INOUT shader_ptr) = 0;
	virtual result_t link_shader_object () = 0;
	virtual result_t clean_shader_object () = 0;
	//virtual result_t begin_program () = 0;
	//virtual result_t end_program () = 0;
	virtual	long_t		program_id () const = 0;

	virtual result_t draw_array (enum_int_t mode_, //PFX_PRIMITIVE_MODE_t
														uindex_t fist_vertex_index,
														usize__t primitive_count) = 0;

	virtual result_t draw_element (enum_int_t mode_, //PFX_PRIMITIVE_MODE_t
														usize__t indices) = 0; //PFX_CONST_GRAM_ELEMENT_INDICES_PARAMS_t

	virtual result_t	enable_vertex_array_attribute	(long_t tagVertex) = 0;
	virtual result_t	disable_vertex_array_attribute	(long_t tagVertex) = 0;

	virtual result_t	set_vertex_array			(const shader_pps& PARAM_IN __param) = 0;

	virtual result_t	set_vertex_attribute	(const shader_pps& PARAM_IN __param) = 0;
	virtual result_t	get_attri_location		(shader_pps& PARAM_INOUT __result) const = 0;

	virtual result_t	set_uniform (const shader_pps& PARAM_IN __param) const = 0;
	virtual result_t	get_uniform_location (const shader_pps& PARAM_IN __param) const = 0;

	virtual result_t query_program	(shader_pps& PARAM_INOUT __result) const = 0;
	virtual result_t query_uniform		(shader_pps& PARAM_INOUT __result) const = 0;
	virtual result_t query_vertex			(shader_pps& PARAM_INOUT __result) const = 0;
};

template < class shader_type >
struct PFX_Shader_traits
{
	typedef typename shader_type				shader_t;
	
	typedef typename shader_t::string_t		string_t;
	typedef typename shader_t::handle_t	handle_t;
	typedef typename shader_t::param_t	param_t;	

	typedef typename shader_t::render_device_t render_device_t;

	static PFX_INLINE shader_t	create_shader (render_device_t&  render_device)
	{
		return shader_t::create_shader (render_device);
	}
	static PFX_INLINE result_t		delete_shader (shader_t&  __shader)
	{
		return shader_t::delete_shader (__shader);
	}
	static PFX_INLINE shader_t& compile_shader (shader_t& __shader, string_t __shader_code, 
																						const param_t* PARAM_IN param_ptr = null)
	{
		__shader.compile_shader (__shader_code, param_ptr);
		return __shader;
	}
};

template < class shader_program_type, class param_type >
struct PFX_ShaderProgram_set_operate_traits
{
	typedef typename shader_program_type					shader_program_t;
	typedef typename param_type									param_t;
	typedef typename shader_program_t::name_t		name_t;
	typedef typename shader_program_t::location_t	location_t;
	static PFX_INLINE result_t set_variables (shader_program_t& __program, 
		location_t __loc, const param_t& __param)
	{
		return __program.set_variables (__loc, __param);
	}
	static PFX_INLINE location_t set_variables (shader_program_t& __program, 
		const name_t& param_name, const param_t& __param)
	{
		return __program.set_variables (param_name, __param);
	}
};

template < class shader_program_type >
struct PFX_ShaderProgram_get_operate_traits
{
	typedef typename shader_program_type					shader_program_t;
	typedef typename shader_program_t::name_t		name_t;
	typedef typename shader_program_t::location_t	location_t;
	static PFX_INLINE location_t get_variables_location (shader_program_t& __program, 
																									const name_t& __name)
	{
		return __program.get_variables_location (__loc, __name);
	}
	static PFX_INLINE result_t bind_variables_location (shader_program_t& __program, 
		const name_t& __name, location_t __loc)
	{
		return __program.bind_variables_location (__name, __loc);
	}
};


template < class shader_program_type >
struct PFX_ShaderVertex_params_traits
{
	typedef typename shader_program_type							shader_program_t;

	// param
	typedef typename shader_program_t::vex1f_t				vex1f_t;
	typedef typename shader_program_t::vex2f_t				vex2f_t;
	typedef typename shader_program_t::vex3f_t				vex3f_t;
	typedef typename shader_program_t::vex4f_t				vex4f_t;

	typedef typename shader_program_t::vex1fv_t				vex1fv_t;
	typedef typename shader_program_t::vex2fv_t				vex2fv_t;
	typedef typename shader_program_t::vex3fv_t				vex3fv_t;
	typedef typename shader_program_t::vex4fv_t				vex4fv_t;

	typedef typename shader_program_t::vex_array_t		vex_array_t;
	// result
	typedef typename shader_program_t::vex_location_t	vex_location_t;
};

template < class shader_program_type >
struct PFX_ShaderUniform_params_traits
{
	typedef typename shader_program_type									shader_program_t;

	// param
	typedef typename shader_program_t::uniform1i_t				uniform1i_t	;
	typedef typename shader_program_t::uniform2i_t				uniform2i_t	;
	typedef typename shader_program_t::uniform3i_t				uniform3i_t	;
	typedef typename shader_program_t::uniform4i_t				uniform4i_t	;
	
	typedef typename shader_program_t::uniform1f_t				uniform1f_t	;
	typedef typename shader_program_t::uniform2f_t				uniform2f_t	;
	typedef typename shader_program_t::uniform3f_t				uniform3f_t	;
	typedef typename shader_program_t::uniform4f_t				uniform4f_t	;

	typedef typename shader_program_t::mat2f_t						mat2f_t	;
	typedef typename shader_program_t::mat3f_t						mat3f_t	;
	typedef typename shader_program_t::mat4f_t						mat4f_t	;

	typedef typename shader_program_t::uniform1iv_t				uniform1iv_t	;
	typedef typename shader_program_t::uniform2iv_t				uniform2iv_t	;
	typedef typename shader_program_t::uniform3iv_t				uniform3iv_t	;
	typedef typename shader_program_t::uniform4iv_t				uniform4iv_t	;

	typedef typename shader_program_t::uniform1fv_t				uniform1fv_t	;
	typedef typename shader_program_t::uniform2fv_t				uniform2fv_t	;
	typedef typename shader_program_t::uniform3fv_t				uniform3fv_t	;
	typedef typename shader_program_t::uniform4fv_t				uniform4fv_t	;

	typedef typename shader_program_t::mat2fv_t						mat2fv_t	;
	typedef typename shader_program_t::mat3fv_t						mat3fv_t	;
	typedef typename shader_program_t::mat4fv_t						mat4fv_t	;

	//result
	typedef typename shader_program_t::unform_location_t	unform_location_t; 

};
template < class shader_program_type >
struct PFX_ShaderProgram_traits
{
	typedef typename shader_program_type									shader_program_t;
	typedef typename shader_program_t::render_device_t		render_device_t;

	// return old shader program
	static PFX_INLINE shader_program_t&	use_shader_program (render_device_t&  render_device, 
		shader_program_t& __program)
	{
		return render_device.use_shader_program (__program);
	}
	static PFX_INLINE shader_program_t	create_shader_program (render_device_t&  render_device)
	{
		return shader_program_t::create_shader_program (render_device);
	}
	static PFX_INLINE result_t		delete_shader_program (shader_program_t&  __shader_program)
	{
		return shader_program_t::delete_shader (__shader_program);
	}


	typedef typename PFX_ShaderVertex_params_traits< shader_program_t >					vertex_param_t;
	typedef typename PFX_ShaderUniform_params_traits< shader_program_t >				uniform_param_t;
	typedef typename PFX_ShaderProgram_get_operate_traits< shader_program_t >	loction_gets_t;
	// param
	typedef typename vertex_param_t::vex1f_t				vex1f_t;
	typedef typename vertex_param_t::vex2f_t				vex2f_t;
	typedef typename vertex_param_t::vex3f_t				vex3f_t;
	typedef typename vertex_param_t::vex4f_t				vex4f_t;
	typedef typename vertex_param_t::vex1fv_t			vex1fv_t;
	typedef typename vertex_param_t::vex2fv_t			vex2fv_t;
	typedef typename vertex_param_t::vex3fv_t			vex3fv_t;
	typedef typename vertex_param_t::vex4fv_t			vex4fv_t;
	typedef typename vertex_param_t::vex_array_t		vex_array_t;
	// result
	typedef typename vertex_param_t::vex_location_t	vex_location_t;

	// param
	typedef typename uniform_param_t::uniform1i_t		uniform1i_t	;
	typedef typename uniform_param_t::uniform2i_t		uniform2i_t	;
	typedef typename uniform_param_t::uniform3i_t		uniform3i_t	;
	typedef typename uniform_param_t::uniform4i_t		uniform4i_t	;
	typedef typename uniform_param_t::uniform1f_t		uniform1f_t	;
	typedef typename uniform_param_t::uniform2f_t		uniform2f_t	;
	typedef typename uniform_param_t::uniform3f_t		uniform3f_t	;
	typedef typename uniform_param_t::uniform4f_t		uniform4f_t	;
	typedef typename uniform_param_t::uniform1iv_t	uniform1iv_t	;
	typedef typename uniform_param_t::uniform2iv_t	uniform2iv_t	;
	typedef typename uniform_param_t::uniform3iv_t	uniform3iv_t	;
	typedef typename uniform_param_t::uniform4iv_t	uniform4iv_t	;
	typedef typename uniform_param_t::uniform1fv_t	uniform1fv_t;
	typedef typename uniform_param_t::uniform2fv_t	uniform2fv_t;
	typedef typename uniform_param_t::uniform3fv_t	uniform3fv_t;
	typedef typename uniform_param_t::uniform4fv_t	uniform4fv_t;
	//result
	typedef typename shader_program_t::unform_location_t	unform_location_t; 

	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex_array_t > set_vexarr_t;

	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex1f_t >			set_vex1f_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex2f_t >			set_vex2f_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex3f_t >			set_vex3f_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex4f_t >			set_vex4f_t;

	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex1fv_t >		set_vex1fv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex2fv_t >		set_vex2fv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex3fv_t >		set_vex3fv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, vex4fv_t >		set_vex4fv_t;
																																											   
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform1i_t  >		set_ufm1i_t  ;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform2i_t  >		set_ufm2i_t  ;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform3i_t  >		set_ufm3i_t  ;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform4i_t  >		set_ufm4i_t  ;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform1f_t  >		set_ufm1f_t  ;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform2f_t  >		set_ufm2f_t  ;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform3f_t  >		set_ufm3f_t  ;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform4f_t  >		set_ufm4f_t  ;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform1iv_t >		set_ufm1iv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform2iv_t >		set_ufm2iv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform3iv_t >		set_ufm3iv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform4iv_t >		set_ufm4iv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform1fv_t >		set_ufm1fv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform2fv_t >		set_ufm2fv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform3fv_t >		set_ufm3fv_t;
	typedef typename PFX_ShaderProgram_set_operate_traits< shader_program_t, uniform4fv_t >		set_ufm4fv_t;


};


PECKER_END

#endif			//PFX_SHADER_PROGRAM_H_
