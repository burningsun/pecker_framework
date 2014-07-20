/*
 * pfx_shader_program_gles.h
 *
 *  Created on: 2014-7-20
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHADER_PROGRAM_GLES_H_
#define		PFX_SHADER_PROGRAM_GLES_H_

#include <gl2.h>
#include "../pfx_shader_program.h"

PECKER_BEGIN

class cpixels_shader_gles2 : public Ipfx_shader
{
private:
	GLuint m_shaderID;
public:
	cpixels_shader_gles2();
	~cpixels_shader_gles2();
public:
	PFX_INLINE GLuint get_shader_id() const
	{
		return m_shaderID;
	}
	void dispose ();
public:
	long_t			compile_shader (const char_t* PARAM_IN str_shader_codes, 
		usize__t buf_size, 
		const void* PARAM_IN param_ptr = null);
	result_t			reloacation (long_t __locate);
	long_t				get_shader_location ();
	enum_int_t	get_type () const; //PFX_SHADER_TYPE_t
	const shader_pps_t* query_shader_info (usize__t& __pps_count) const;
};

class cvertex_shader_gles2 : public Ipfx_shader
{
private:
	GLuint m_shaderID;
public:
	cvertex_shader_gles2();
	~cvertex_shader_gles2();
public:
	PFX_INLINE GLuint shader_id() const
	{
		return m_shaderID;
	}
	void dispose ();
public:
	long_t			compile_shader (const char_t* PARAM_IN str_shader_codes, 
		usize__t buf_size, 
		const void* PARAM_IN param_ptr = null);
	result_t			reloacation (long_t __locate);
	
	PFX_INLINE long_t	get_shader_location ()
	{
		return m_shaderID;
	}
	PFX_INLINE enum_int_t	get_type () const //PFX_SHADER_TYPE_t
	{
		return PFXST_PIXEL_SHADER;
	}
	const shader_pps_t* query_shader_info (usize__t& __pps_count) const;
};



class cshader_program_gles2 : public Ipfx_shader_program
{
private:
	Ipfx_shader*	m_pixels_shader_ptr;
	Ipfx_shader*	m_vertex_shader_ptr;
	GLuint				m_programID;
public:
	PFX_INLINE GLuint glProgramID() const
	{
		return m_programID;
	}
public:
	cshader_program_gles2();
	~cshader_program_gles2();

	result_t init ();
	result_t close ();

	// shader 处理程序
	 result_t link_shader (Ipfx_shader* PARAM_INOUT shader_ptr);
	 result_t link_shader_object ();
	 result_t clean_shader_object ();
	 PFX_INLINE long_t	program_id () const
	 {
		 return m_programID;
	 }

	 result_t draw_array (enum_int_t mode_, //PFX_PRIMITIVE_MODE_t
											uindex_t fist_vertex_index,
											usize__t primitive_count);

	 result_t draw_element (enum_int_t mode_, //PFX_PRIMITIVE_MODE_t
											usize__t indices); //PFX_CONST_GRAM_ELEMENT_INDICES_PARAMS_t

	 result_t	enable_vertex_array_attribute	(long_t tagVertex);
	 result_t	disable_vertex_array_attribute	(long_t tagVertex);

	 result_t	set_vertex_array			(const shader_pps_t& PARAM_IN __param);

	 result_t	set_vertex_attribute	(const shader_pps_t& PARAM_IN __param);
	 result_t	get_attri_location		(shader_pps_t& PARAM_INOUT __result) const;

	 result_t	set_uniform (const shader_pps& PARAM_IN __param) const;
	 result_t	get_uniform_location (shader_pps_t& PARAM_INOUT __result) const;

	 result_t query_program	(shader_pps_t& PARAM_INOUT __result) const;
	 result_t query_uniform		(shader_pps_t& PARAM_INOUT __result) const;
	 result_t query_vertex			(shader_pps_t& PARAM_INOUT __result) const;
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
