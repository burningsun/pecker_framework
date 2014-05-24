/*
 * pfx_buffer_object.h
 *
 *  Created on: 2013-11-13
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BUFFER_OBJECT_H_
#define		PFX_BUFFER_OBJECT_H_

#include "../../include/config"


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
	byte_t*					m_bits_ptr;
	usize__t					m_bytes_count;
	enum_int_t			m_usage; //PFX_BUFFER_USAGE_TYPE_t
}buffer_bits_t;

PFX_Interface Ipfx_update_buffer_usermode
{
	virtual result_t update_buffer (buffer_bits_t* PARAM_INOUT lock_bits_ptr) = 0;
};

PFX_Interface IPfx_buffer_object
{
	virtual result_t			lock_buffer (buffer_bits_t* & PARAM_INOUT bits_ptr) = 0;
	virtual result_t			unlock_buffer () = 0;
	virtual result_t			update_buffer (Ipfx_update_buffer_usermode* PARAM_IN usermode_ptr) = 0;
	virtual enum_int_t	get_buffer_type () const = 0; //PFX_BUFFER_OBJECT_TYPE_t
};

template < typename buffer_object_type >
struct PFX_Buffer_Object_traits
{
	typedef typename buffer_object_type			BO_t;
	typedef typename BO_t::render_device_t		render_device_t;
	typedef typename BO_t::update_mode_t		update_mode_t;

	static PFX_INLINE BO_t*	create_buffer (render_device_t& render_device)
	{
		return BO_t::create_buffer (render_device);
	}
	static PFX_INLINE result_t	delete_buffer (BO_t* PARAM_INOUT object_ptr)
	{
		return BO_t::delete_buffer (object_ptr);
	}
};

template < typename vertex_struct_type >
struct PFX_vertex_struct_traits
{
	typedef typename vertex_struct_type vertex_struct_t;
	static PFX_INLINE usize__t				sub_struct_size (const vertex_struct_t& __vs, uindex_t i)
	{
		return __vs.sub_struct_size (i);
	}
	static PFX_INLINE usize__t				sub_struct_count (const vertex_struct_t& __vs)
	{
		return __vs.sub_struct_count ();
	}
	static PFX_INLINE uindex_t			sub_struct_offset (const vertex_struct_t& __vs, uindex_t i)
	{
		return __vs.sub_struct_offset(i);
	}
	static PFX_INLINE const byte_t*	sub_struct_ptr (const vertex_struct_t& __vs, uindex_t i)
	{
		return __vs.sub_struct_ptr(i);
	}
};

template < typename vertex_struct_type, class shader_program, const bool_t using_vbo = PFX_BOOL_FALSE >
struct PFX_vertex_struct_format
{
	typedef PFX_vertex_struct_traits< vertex_struct_type > vertex_struct_t;
	typedef typename shader_program									 shader_program_t;

	// 使用一个vertex_attributes_buffer保存所有结构体数据，实现Array of Structures
	static PFX_INLINE result_t update_vertex_with_AOS (shader_program_t& __shader_program, 
		vertex_struct_t* PARAM_IN __vs_ptr, usize__t __vs_count)
	{
		return 0;
	}

	// 使用一个vertex_attributes_buffer只保存一个结构体数据，实现Structure of Arrays 
	static PFX_INLINE result_t update_vertex_with_SOA (shader_program_t& __shader_program, 
		const byte_t* PARAM_IN __vs_array_ptr, usize__t __vs_buf_size)
	{
		return 0;
	}
};


PECKER_END

#endif			//PFX_BUFFER_OBJECT_H_
