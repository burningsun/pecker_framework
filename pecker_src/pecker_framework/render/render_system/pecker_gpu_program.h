/*
 * pecker_gpu_program.h
 *
 *  Created on: 2013-4-6
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_GPU_PROGRAM_H_
#define PECKER_GPU_PROGRAM_H_

#include "../pecker_render_object.h"
#include "../../data/pecker_string.h"
#include "../../data/pecker_matrix.h"

PECKER_BEGIN

#define GPU_LOCATION_HANDLE long

PeckerInterface Ipecker_gpu_program_param
{
	virtual ~Ipecker_gpu_program_param(){;}

	virtual HResult set_uniform_int(GPU_LOCATION_HANDLE uniform_location,SInt x) = 0;
	virtual HResult set_uniform_int(GPU_LOCATION_HANDLE uniform_location,SInt x,SInt y) = 0;
	virtual HResult set_uniform_int(GPU_LOCATION_HANDLE uniform_location,SInt x,SInt y,SInt z) = 0;
	virtual HResult set_uniform_int(GPU_LOCATION_HANDLE uniform_location,SInt x,SInt y,SInt z,SInt w) = 0;

	virtual HResult set_uniform_float(GPU_LOCATION_HANDLE uniform_location,Float x) = 0;
	virtual HResult set_uniform_float(GPU_LOCATION_HANDLE uniform_location,Float x,Float y) = 0;
	virtual HResult set_uniform_float(GPU_LOCATION_HANDLE uniform_location,Float x,Float y,Float z) = 0;
	virtual HResult set_uniform_float(GPU_LOCATION_HANDLE uniform_location,Float x,Float y,Float z,Float w) = 0;

	virtual HResult set_uniform_vector(GPU_LOCATION_HANDLE uniform_location,const pecker_vector2& vector2) = 0;
	virtual HResult set_uniform_vector(GPU_LOCATION_HANDLE uniform_location,const pecker_vector3& vector3) = 0;
	virtual HResult set_uniform_vector(GPU_LOCATION_HANDLE uniform_location,const pecker_vector4& vector4) = 0;

	virtual HResult set_uniform_int_array(GPU_LOCATION_HANDLE uniform_location,nSize array_size,const SInt* pint_array) = 0;

	virtual HResult set_uniform_float_array(GPU_LOCATION_HANDLE uniform_location,nSize array_size,const Float* pfloat_array) = 0;
	virtual HResult set_uniform_vector_array(GPU_LOCATION_HANDLE uniform_location,nSize array_size,const pecker_vector2* pvector_array) = 0;
	virtual HResult set_uniform_vector_array(GPU_LOCATION_HANDLE uniform_location,nSize array_size,const pecker_vector3* pvector_array) = 0;
	virtual HResult set_uniform_vector_array(GPU_LOCATION_HANDLE uniform_location,nSize array_size,const pecker_vector4* pvector_array) = 0;

	virtual HResult set_uniform_matrix_array(GPU_LOCATION_HANDLE uniform_location,nSize array_size,const pecker_matrix3* pmaxtrix_array) = 0;
	virtual HResult set_uniform_matrix_array(GPU_LOCATION_HANDLE uniform_location,nSize array_size,const pecker_matrix4* pmaxtrix_array) = 0;

	virtual HResult get_attribute_value(GPU_LOCATION_HANDLE attribute_location,HEnum attribute_type,Float* P_OUT pvalue) = 0;
	virtual HResult get_attribute_value(GPU_LOCATION_HANDLE attribute_location,HEnum attribute_type,SInt* P_OUT pvalue) = 0;
	virtual HResult get_attribute_value(GPU_LOCATION_HANDLE attribute_location,HEnum attribute_type,PVoid* P_OUT pvalue) = 0;

	virtual HResult set_attribute_float(GPU_LOCATION_HANDLE attribute_location,Float x) = 0;
	virtual HResult set_attribute_float(GPU_LOCATION_HANDLE attribute_location,Float x,Float y) = 0;
	virtual HResult set_attribute_float(GPU_LOCATION_HANDLE attribute_location,Float x,Float y,Float z) = 0;
	virtual HResult set_attribute_float(GPU_LOCATION_HANDLE attribute_location,Float x,Float y,Float z,Float w) = 0;

	virtual HResult set_attribute_vector(GPU_LOCATION_HANDLE attribute_location,const pecker_vector2& vector2) = 0;
	virtual HResult set_attribute_vector(GPU_LOCATION_HANDLE attribute_location,const pecker_vector3& vector3) = 0;
	virtual HResult set_attribute_vector(GPU_LOCATION_HANDLE attribute_location,const pecker_vector4& vector4) = 0;
	
	virtual HResult set_attribute_float_array(GPU_LOCATION_HANDLE attribute_location,nSize array_size,const Float* pfloat_array) = 0;
	virtual HResult set_attribute_vector_array(GPU_LOCATION_HANDLE attribute_location,nSize array_size,const pecker_vector2* pvector_array) = 0;
	virtual HResult set_attribute_vector_array(GPU_LOCATION_HANDLE attribute_location,nSize array_size,const pecker_vector3* pvector_array) = 0;
	virtual HResult set_attribute_vector_array(GPU_LOCATION_HANDLE attribute_location,nSize array_size,const pecker_vector4* pvector_array) = 0;

	virtual GPU_LOCATION_HANDLE get_uniform_location_by_name(const pecker_string& str_attribute_name) = 0;
	virtual GPU_LOCATION_HANDLE get_attribute_location_by_name(const pecker_string& str_attribute_name) = 0;
};

PeckerInterface Ipecker_gpu_program
{
	virtual ~Ipecker_gpu_program(){}

	virtual GPU_LOCATION_HANDLE int_shader_program(const pecker_string* P_IN pstr_bind_attributes = null,nSize nAttributes_count = 0,pecker_string* P_OUT pstr_error_info = null) = 0;
	
	virtual GPU_LOCATION_HANDLE load_frame_shader_source(const pecker_string& str_source_code,pecker_string* P_OUT pstr_error_info = null) = 0;
	virtual GPU_LOCATION_HANDLE load_vertex_shader_source(const pecker_string& str_source_code,pecker_string* P_OUT pstr_error_info = null) = 0;

	virtual HResult delete_shader_program() = 0;
	virtual HResult delete_frame_shader() = 0;
	virtual HResult delete_vertex_shader() = 0;

	virtual GPU_LOCATION_HANDLE using_program() = 0;

	virtual Ipecker_gpu_program_param* get_program_param() = 0;
	//virtual HResult set_shader_value() = 0;
	//virtual HResult get_shader_value() = 0;
};


PECKER_END

#endif //PECKER_GPU_PROGRAM_H_