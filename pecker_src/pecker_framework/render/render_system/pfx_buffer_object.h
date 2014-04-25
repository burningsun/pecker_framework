/*
 * pfx_buffer_object.h
 *
 *  Created on: 2013-11-13
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BUFFER_OBJECT_H_
#define		PFX_BUFFER_OBJECT_H_

#include "../../pfx_defines.h"


PECKER_BEGIN

typedef enum enumBufferObjectType
{
	PFX_VERTEX_BUFFER_OBJECT_TYPE = 0,
	PFX_INDEX_BUFFER_OBJECT_TYPE,
	PFX_MAP_BUFFER_OBJECT_TYPE,

	PFX_BUFFER_OBJECT_TYPE_COUNT
}PFX_BUFFER_OBJECT_TYPE_t;

typedef enum enumBufferUsageType
{
	PFX_BU_STATIC_DRAW = 0,
	PFX_BU_DYNAMIC_DRAW,
	PFX_BU_STREAM_DRAW,

	PFX_BUFFER_USAGE_TYPE_COUNT
}PFX_BUFFER_USAGE_TYPE_t;

typedef struct buffer_bits
{
	pfx_byte_t*										m_bits_ptr;
	pfx_usize_t										m_bytes_count;
	PFX_BUFFER_USAGE_TYPE_t			m_usage;
}buffer_bits_t;

PFX_Interface Ipfx_update_buffer_usermode
{
	virtual pfx_result_t update_buffer (buffer_bits_t* PARAM_INOUT lock_bits_ptr) = 0;
};

PFX_Interface IPfx_buffer_object
{
	virtual pfx_result_t lock_buffer (buffer_bits_t* & PARAM_INOUT bits_ptr) = 0;
	virtual pfx_result_t unlock_buffer () = 0;
	virtual pfx_result_t update_buffer (Ipfx_update_buffer_usermode* PARAM_IN usermode_ptr) = 0;
	virtual PFX_BUFFER_OBJECT_TYPE_t get_buffer_type () const = 0;
};

template < typename buffer_object_type >
struct PFX_Buffer_Object
{
	typedef typename buffer_object_type::render_device_t		render_device_t;
	typedef typename buffer_object_type::buffer_object_t			buffer_object_t;

	static PFX_INLINE buffer_object_t*	create_buffer (render_device_t render_device)
	{
		return null;
	}
	static PFX_INLINE pfx_result_t			delete_buffer (buffer_object_t* PARAM_INOUT render_object_ptr)
	{
		return PFX_STATUS_DENIED;
	}
};


PFX_Interface IPfx_vertex_array
{
	virtual pfx_result_t push_struct_info ( pfx_enum_int_t element_type_, 
																			pfx_usize_t element_count, 
																			pfx_boolean_t bNormalisze) = 0;

	virtual pfx_result_t clear_struct_info () = 0;
	
	virtual pfx_usize_t	get_struct_count () const = 0;

	// 使用一个vertex_attributes_buffer保存所有结构体数据，实现Array of Structures
	virtual pfx_result_t update_vertex_attributes (PFX_Interface Ipfx_shader_program* PARAM_IN shader_program_ptr,
																								const pfx_byte_t* PARAM_IN vertex_attributes_buffer, pfx_usize_t bytes_count) = 0;

	// 使用一个vertex_attributes_buffer只保存一个结构体数据，实现Structure of Arrays 
	virtual pfx_result_t update_one_vertex_attributes (PFX_Interface Ipfx_shader_program* PARAM_IN shader_program_ptr,
																								pfx_uindex_t	struct_index,
																								const pfx_byte_t* PARAM_IN vertex_attributes_buffer, pfx_usize_t bytes_count) = 0;
};

template < typename vertex_array_type >
struct PFX_Vertex_Array
{
	typedef typename vertex_array_t::vertex_array_t			vertex_array_t;

	static PFX_INLINE vertex_array_t*	create_vertex_array ()
	{
		return null;
	}
	static PFX_INLINE pfx_result_t			delete_vertex_array (vertex_array_t* PARAM_INOUT array_ptr)
	{
		return PFX_STATUS_DENIED;
	}
};

PECKER_END

#endif			//PFX_BUFFER_OBJECT_H_
