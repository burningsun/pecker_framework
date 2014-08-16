/*
 * pfx_gles10_shader_source.h
 *
 *  Created on: 2014-8-8
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_GLES10_SHADER_SOURCE_H_
#define		PFX_GLES10_SHADER_SOURCE_H_

#include <GLES2/gl2.h>

#include "../../../pfx_defines.h"
#include "../../../include/cstring_pfx.h"

PECKER_BEGIN

typedef struct PFX_RENDER_SYSTEM_API st_shader_souce_string
{
	const cstring_ascii_t* m_str_vertext_shader;
	const cstring_ascii_t* m_str_fragment_shader;
	st_shader_souce_string() :m_str_vertext_shader(null),
		m_str_fragment_shader(null)
	{
		;
	}
	~st_shader_souce_string()
	{
		;
	}

}shader_souce_string_t;

typedef enum enumSYSTEM_DEFUALT_GLES10_SHADER_SOURCE
{
	HELLO_SHADER_SOURCE = 0,
	POSITION_COLOR_MVP_SHADER_SOURCE,
	POSITION_TEXTCOORD_MVP_SHADER_SOURCE,
	POSITION_2TEXTCOORD_MVP_SHADER_SOURCE,

	SYSTEM_DEFUAL_GLES10_SHADER_SOURCE_COUNT
}SYSTEM_DEFUALT_GLES10_SHADER_SOURCE_t;

typedef enum enumSYSTEM_DEFUALT_GLES10_SHADER_FLAOT_PRECISION
{
	SSS_HIGH_FLOAT = 0,
	SSS_MEDIUEM_FLOAT,
	SSS_LOW_FLOAT,

	SYSTEM_DEFUAL_GLES10_SHADER_FLAOT_PRECISION_COUNT
}SYSTEM_DEFUALT_GLES10_SHADER_FLAOT_PRECISION_t;

PFX_RENDER_SYSTEM_API const  shader_souce_string_t*  get_system_defualt_shader_source(
shader_souce_string_t& shader_source_code,
SYSTEM_DEFUALT_GLES10_SHADER_SOURCE_t __source_type, 
SYSTEM_DEFUALT_GLES10_SHADER_FLAOT_PRECISION_t __precision_float = SSS_MEDIUEM_FLOAT);

PECKER_END

#endif			//PFX_GLES10_SHADER_SOURCE_H_
