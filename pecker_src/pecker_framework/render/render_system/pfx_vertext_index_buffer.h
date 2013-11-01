/*
 * pfx_vertex_index_buffer.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VERTEX_INDEX_BUFFER_H_
#define		PFX_VERTEX_INDEX_BUFFER_H_

#include "../../pfx_defines.h"

PFX_C_EXTERN_BEGIN

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
}GRAM_DATA_FORMAT_t;

typedef struct st_GRAM_ARRAY_BUFFER
{
	pfx_bool_t		m_is_normalized;
	pfx_enum_t	m_data_format; //GRAM_DATA_FORMAT_t
	pfx_usize_t		m_vertex_item_size;
	pfx_usize_t		m_buffer_size;
	pfx_byte_t*	m_vertex_buffer;

}GRAM_ARRAY_BUFFER_t;



PFX_C_EXTERN_END

#endif			//PFX_VERTEX_INDEX_BUFFER_H_
