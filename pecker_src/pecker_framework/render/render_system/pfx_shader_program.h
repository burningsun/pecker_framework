/*
 * pfx_shader_program.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHADER_PROGRAM_H_
#define		PFX_SHADER_PROGRAM_H_

#include "../../include/config"
#include "../../include/cshare_object"
#include "../../Include/cstring"
#include "../pfx_render_allocator.h"

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

	PFXSPT_BOOL1,
	PFXSPT_BOOL2,
	PFXSPT_BOOL3,
	PFXSPT_BOOL4,

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
	PFXST_UNKOWN_SHADER = 0,
	PFXST_VERTEXT_SHADER,
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

typedef enum enumShaderParamValueType
{
	PFX_CONST_VALUE = 0,
	PFX_UNIFORM_VALUE,
	PFX_VERTEX_VALUE,
	PFX_SHADER_PARAM_VALUE_COUNT,
}PFX_SHADER_PARAM_VALUE_t;

typedef struct  st_shader_param
{
	enum_int_t		m_type; // PFX_SHADER_PARAM_VALUE_t
	enum_int_t		m_value_type; 
	long_t			m_location;
	cstring_ascii_t	m_name;
}shader_param_t;

typedef struct  st_compare_shader_param
{
	PFX_INLINE int operator () (const shader_param_t& value1,
	const shader_param_t& value2) const
	{
		return cascii_string_compare_t::compare(value1.m_name, value2.m_name);
	}
	static PFX_INLINE int compare(const shader_param_t& value1,
		const shader_param_t& value2)
	{
		return cascii_string_compare_t::compare(value1.m_name, value2.m_name);
	}
}compare_shader_param_t;

typedef struct  st_compare_shader_param_by_name
{
	PFX_INLINE int operator () (const shader_param_t& value1,
	const cstring_ascii_t& value2) const
	{
		return cascii_string_compare_t::compare(value1.m_name, value2);
	}
	static PFX_INLINE int compare(const shader_param_t& value1,
		const cstring_ascii_t& value2)
	{
		return cascii_string_compare_t::compare(value1.m_name, value2);
	}
}compare_shader_param_ex_t;

typedef struct  st_compare_shader_param_by_chrname
{
	PFX_INLINE int operator () (const shader_param_t& value1,
	const char_t* value2) const
	{
		return ascii_string_compare_withchars_t::compare(value1.m_name, value2);
	}
	static PFX_INLINE int compare(const shader_param_t& value1,
		const char_t* value2)
	{
		return ascii_string_compare_withchars_t::compare(value1.m_name, value2);
	}
}compare_shader_param_exchr_t;


PFX_Interface  PFX_RENDER_SYSTEM_API Ipfx_shader
{
	virtual ~Ipfx_shader(){ ; }
	virtual long_t	compile_shader(const char_t* PARAM_IN str_shader_codes,
		usize__t buf_size,
		result_t& status,
		usize__t source_count = 1,
		const void* PARAM_IN param_ptr = null)	= 0;
	virtual long_t		get_native_handle() = 0;
	virtual enum_int_t	get_type() const = 0;
	virtual u64_t		get_version() const = 0;
	virtual void		release_reference() = 0;
};

PFX_Interface Ipfx_shader_program
{
	typedef cavl_bst_node < shader_param_t >					shader_param_node_t;
	typedef compare_two_node< shader_param_node_t,
		shader_param_node_t, compare_shader_param_t >			node_cmp_t;
	typedef pfx_binary_search_tree_type < shader_param_node_t,
		node_cmp_t, shader_param_node_allocator_t >
		::avl_binary_search_tree_t								tree_t;
	typedef BST_find_elementx< tree_t,
		cstring_ascii_t, compare_shader_param_ex_t >			find_t;

	virtual ~Ipfx_shader_program(){ ; }

	virtual result_t	compile_program() = 0;
	virtual long_t		get_location_by_name
		(const cstring_ascii_t& PARAM_IN
		str_shader_param_name) const = 0;
	virtual long_t		get_location_by_name
		(const char* PARAM_IN
		str_shader_param_name) const = 0;

	virtual result_t	attach_shader(Ipfx_shader* PARAM_IN shader_ptr) = 0;


	virtual  const tree_t* get_shader_param_table() const = 0;
	virtual long_t		get_native_handle() = 0;
	virtual u64_t		get_version() const = 0;
	virtual void		release_reference() = 0;

};





PECKER_END

#endif			//PFX_SHADER_PROGRAM_H_
