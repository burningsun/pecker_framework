/*
 * pfx_gram_array_params.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_GRAM_ARRAY_PARAMS_H_
#define		PFX_GRAM_ARRAY_PARAMS_H_

#include "../../pfx_defines.h"

PECKER_BEGIN

typedef enum enumGRAM_DATA_FORMAT
{
	PFX_BYTE_FMT = 0,
	PFX_UNSIGNED_BYTE_FMT,
	PFX_SHORT_FMT,
	PFX_UNSIGNED_SHORT_FMT,
	PFX_FLOAT_FMT,
	PFX_FIXED_FMT,

	PFX_EXTERN_FMT,
	VEX_DATA_FORMAT_COUNT
}PFX_GRAM_DATA_FORMAT_t;

typedef struct st_GRAM_BUFFER
{
	pfx_usize_t		m_size;
	void*				m_buffer;	
}PFX_GRAM_BUFFER_t;

typedef struct st_CONST_GRAM_BUFFER
{
	pfx_usize_t		m_size;
	const	void*	m_buffer;	
}PFX_CONST_GRAM_BUFFER_t;

typedef struct st_GRAM_ARRAY_PARAMS
{
	pfx_bool_t					m_is_normalized;
	pfx_enum_t				m_data_format; //GRAM_DATA_FORMAT_t
	pfx_usize_t					m_vertex_item_size;
	PFX_GRAM_BUFFER_t m_vertex_buffer;
}PFX_GRAM_ARRAY_PARAMS_t;

typedef struct st_CONST_GRAM_ARRAY_PARAMS
{
	pfx_bool_t									m_is_normalized;
	pfx_enum_t								m_data_format; //GRAM_DATA_FORMAT_t
	pfx_usize_t									m_vertex_item_size;
	PFX_CONST_GRAM_BUFFER_t	m_vertex_buffer;
}PFX_CONST_GRAM_ARRAY_PARAMS_t;

typedef struct st_GRAM_ELEMENT_INDICES_PARAMS
{
	pfx_enum_t				m_data_format; //GRAM_DATA_FORMAT_t
	PFX_GRAM_BUFFER_t m_vertex_buffer;
}PFX_GRAM_ELEMENT_INDICES_PARAMS_t;

typedef struct st_CONST_GRAM_ELEMENT_INDICES_PARAMS
{
	pfx_enum_t								m_data_format; //GRAM_DATA_FORMAT_t
	PFX_CONST_GRAM_BUFFER_t	m_vertex_buffer;
}PFX_CONST_GRAM_ELEMENT_INDICES_PARAMS_t;

PECKER_END

#endif			//PFX_GRAM_ARRAY_PARAMS_H_
