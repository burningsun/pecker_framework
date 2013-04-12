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

PECKER_BEGIN

PeckerInterface Ipecker_gpu_program
{
	virtual ~Ipecker_gpu_program(){}

	virtual UInt int_shader_program(const pecker_string* P_IN pstr_bind_attributes = null,nSize nAttributes_count = 0,pecker_string* P_OUT pstr_error_info = null) = 0;
	
	virtual UInt load_frame_shader_source(const pecker_string& str_source_code,pecker_string* P_OUT pstr_error_info = null) = 0;
	virtual UInt load_vertex_shader_source(const pecker_string& str_source_code,pecker_string* P_OUT pstr_error_info = null) = 0;

	virtual UInt delete_shader_program() = 0;
	virtual UInt delete_frame_shader() = 0;
	virtual UInt delete_vertex_shader() = 0;

	virtual UInt using_program() = 0;
	//virtual HResult set_shader_value() = 0;
	//virtual HResult get_shader_value() = 0;
};


PECKER_END

#endif //PECKER_GPU_PROGRAM_H_