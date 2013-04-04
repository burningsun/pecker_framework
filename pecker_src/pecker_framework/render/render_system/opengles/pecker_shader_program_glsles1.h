/*
 * pecker_shader_program_glsles1.h
 *
 *  Created on: 2013-3-6
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_SHADER_PROGRAM_GLSLES1_H_
#define PECKER_SHADER_PROGRAM_GLSLES1_H_

#include "pecker_opengles_object.h"
#include "../../../data/pecker_matrix.h"
PECKER_BEGIN

class pecker_shader_program_glsles1 : public pecker_opengles_v2_object
{
private:
	UInt  _M_program;
	UInt _M_frame_shader;
	UInt _M_vertex_shader;
public:
	pecker_shader_program_glsles1();
	virtual ~pecker_shader_program_glsles1();
	UInt init_shader_program(UInt nvertex_shader, UInt nframe_shader,const pecker_string* P_IN pstr_bind_attributes = null,nSize nAttributes_count = 0,pecker_string* P_OUT pstr_error_info = null);
	UInt init_shader_program(const pecker_string* P_IN pstr_bind_attributes = null,nSize nAttributes_count = 0,pecker_string* P_OUT pstr_error_info = null);

	UInt load_frame_shader_source(const pecker_string& str_source_code,pecker_string* P_OUT pstr_error_info = null);
	UInt load_vertex_shader_source(const pecker_string& str_source_code,pecker_string* P_OUT pstr_error_info = null);

	UInt delete_shader_program();
	UInt delete_frame_shader();
	UInt delete_vertex_shader();

	UInt using_program();
	UInt get_attribute_location(const pecker_string& str_attribute_name) const;
	HResult get_active_attribute(UInt attribute_index,HEnum& attribute_type,nSize &attribute_size, pecker_string& str_attribute_name) const;

	UInt get_uniform_location(const pecker_string& str_uniform_name) const;
	HResult get_active_uniform(UInt uniform_index,HEnum& uniform_type,nSize &uniform_size, pecker_string& str_uniform_name) const;

	HResult get_uniform_float_value(UInt uniform_index,Float* P_INOUT pUniform_value) const;
	HResult get_uniform_int_value(UInt uniform_index,SInt* P_INOUT pUniform_value) const;

	UInt get_program() const;
	UInt get_frame_shader() const;
	UInt get_vertex_shader() const;

public:
	static pecker_shader_program_glsles1* get_using_program();
	static HResult set_uniform_1float(UInt uniform_index,Float x);
	static HResult set_uniform_2float(UInt uniform_index,Float x,Float y);
	static HResult set_uniform_3float(UInt uniform_index,Float x,Float y,Float z);
	static HResult set_uniform_4float(UInt uniform_index,Float x,Float y,Float z,Float w);

	static HResult set_uniform_2float(UInt uniform_index,const pecker_vector2& vector2);
	static HResult set_uniform_3float(UInt uniform_index,const pecker_vector3& vector3);
	static HResult set_uniform_4float(UInt uniform_index,const pecker_vector4& vector4);

	static HResult set_uniform_1int(UInt uniform_index,SInt x);
	static HResult set_uniform_2int(UInt uniform_index,SInt x,SInt y);
	static HResult set_uniform_3int(UInt uniform_index,SInt x,SInt y,SInt z);
	static HResult set_uniform_4int(UInt uniform_index,SInt x,SInt y,SInt z,SInt w);

	static HResult set_uniform_vector1_array(UInt uniform_index,nSize vector_count,const Float* P_IN vector1_array);
	static HResult set_uniform_vector2_array(UInt uniform_index,nSize vector_count,const pecker_vector2* P_IN vector2_array);
	static HResult set_uniform_vector3_array(UInt uniform_index,nSize vector_count,const pecker_vector3* P_IN vector3_array);
	static HResult set_uniform_vector4_array(UInt uniform_index,nSize vector_count,const pecker_vector4* P_IN vector4_array);

	static HResult set_uniform_matrix2_array(UInt uniform_index,nSize matrix_count,const Float* P_IN matrix2_array);
	static HResult set_uniform_matrix3_array(UInt uniform_index,nSize matrix_count,const pecker_matrix3* P_IN matrix3_array);
	static HResult set_uniform_matrix4_array(UInt uniform_index,nSize matrix_count,const pecker_matrix4* P_IN matrix4_array);

	static HResult get_vertex_attribute_float_value(UInt attribute_index,HEnum attribute_type,Float* P_OUT pfloat_value);
	static HResult get_vertex_attribute_int_value(UInt attribute_index,HEnum attribute_type,SInt* P_OUT pint_value);
	static HResult get_vertex_attribute_pointer_value(UInt attribute_index,HEnum attribute_type,PVoid* P_OUT ppointer);

	static HResult set_vertex_attribute_float1_value(UInt attribute_index,Float x);
	static HResult set_vertex_attribute_float2_value(UInt attribute_index,Float x,Float y);
	static HResult set_vertex_attribute_float3_value(UInt attribute_index,Float x,Float y,Float z);
	static HResult set_vertex_attribute_float4_value(UInt attribute_index,Float x,Float y,Float z,Float w);

	static HResult set_vertex_attribute_vector2_value(UInt attribute_index,const pecker_vector2& vector2);
	static HResult set_vertex_attribute_vector3_value(UInt attribute_index,const pecker_vector3& vector3);
	static HResult set_vertex_attribute_vector4_value(UInt attribute_index,const pecker_vector4& vector4);

	//static HResult set_vertex_attribute_float1_array(UInt attribute_index,nSize value_count,const Float* P_IN parray);
	//static HResult set_vertex_attribute_vector2_array(UInt attribute_index,nSize vector_count,const pecker_vector2* P_IN vector2_array);
	//static HResult set_vertex_attribute_vector3_array(UInt attribute_index,nSize vector_count,const pecker_vector3* P_IN vector3_array);
	//static HResult set_vertex_attribute_vector4_array(UInt attribute_index,nSize vector_count,const pecker_vector4* P_IN vector4_array);

	static HResult set_vertex_attribute_pointer_value(UInt attribute_index,nSize attribute_size,HEnum attribute_type,
		HFlag nstride,const PVoid P_IN ppointer,HEnum attribute_data_type ,Bool normalized = false );

	static HResult enable_vertex_attribute_array(UInt attribute_index);
	static HResult disable_vertex_attribute_array(UInt attribute_index);

public:
	virtual UInt get_object_location() const;
};



PECKER_END

#endif //PECKER_SHADER_PROGRAM_GLSLES1_H_