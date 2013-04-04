/*
 * pecker_buffer.cpp
 *
 *  Created on: 2013-3-14
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_buffer.h"
#include "pecker_frame_buffer.h"
PECKER_BEGIN

HEnum Ipecker_vertex_buffer::get_buffer_type() const
{
	return VERTEX_BUFFER_TYPE;
}

HEnum Ipecker_index_buffer::get_buffer_type() const
{
	return INDEX_BUFFER_TYPE;
}
PECKER_END