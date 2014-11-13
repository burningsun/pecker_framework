/*
 * pfx_buffer_object.h
 *
 *  Created on: 2013-11-13
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BUFFER_OBJECT_H_
#define		PFX_BUFFER_OBJECT_H_

#include "../../include/config"
#include "../../include/cshare_object.h"
#include "../pfx_render_defs.h"


PECKER_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#endif

typedef enum enumBufferObjectType
{
	PFX_COMM_BUFFER_OBJECT_TYPE = 0,
	PFX_VERTEX_BUFFER_OBJECT_TYPE,
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

typedef enum  enumVexValueType
{
	PFXVB_BYTE = 0,
	PFXVB_UNSIGNED_BYTE,
	PFXVB_SHORT,
	PFXVB_UNSIGNED_SHORT,
	PFXVB_FLOAT,
	PFXVB_FIXED,
	PFXVB_HALF_FLOAT,
	PFX_VEXBUFFER_VALUE_TYPE_COUNT
}PFX_VEXBUFFER_VALUE_TYPE_t;




//GL_BYTE
//GL_UNSIGNED_BYTE
//GL_SHORT
//GL_UNSIGNED_SHORT
//GL_FLOAT
//GL_FIXED
//GL_HALF_FLOAT_OES*



PFX_Interface IPfx_vertex_cache_buffer : public creference_root
{
	virtual ~IPfx_vertex_cache_buffer(){ ; }

	virtual result_t	lock_cache_buffer(buffer_bits_t& PARAM_INOUT bits, 
											const buffer_rect_t* PARAM_IN lock_rect_ptr = null) = 0;
	virtual result_t	unlock_cache_buffer () = 0;
	
	virtual result_t reset_cache_buffer
		(enum_int_t __value_type, usize__t vb_struct_size, 
		usize__t vb_struct_count) = 0;
	
	virtual usize__t	vb_struct_attribcount() const = 0;
	virtual usize__t	get_vb_struct_size() const = 0;
	virtual enum_int_t	get_value_type() const = 0;//PFX_VEXBUFFER_VALUE_TYPE_t

	virtual IPfx_vertex_cache_buffer* clone() const = 0;

	virtual u64_t get_version() const = 0;

	virtual IPfx_vertex_cache_buffer* new_share() = 0;
	virtual result_t dispose_vertex() = 0;
};




PFX_Interface PFX_RENDER_SYSTEM_API IPfx_buffer_object : public creference_root
{
	virtual ~IPfx_buffer_object(){ ; }
	//virtual IPfx_buffer_object* diff_cache_object() = 0;

	virtual result_t bind() = 0;

	virtual result_t set_vbo_buffer(IPfx_vertex_cache_buffer* PARAM_IN buffer_ptr) = 0;
	virtual result_t set_vbo_type(enum_int_t vbo_type // PFX_BUFFER_OBJECT_TYPE_t
		) = 0;
	virtual result_t set_vbo_usage_type(enum_int_t usage_type //PFX_BUFFER_USAGE_TYPE_t
		) = 0;
	virtual long_t get_native_location() const = 0;

	virtual IPfx_buffer_object* new_share() = 0;
	virtual result_t dispose_buffer() = 0;

	virtual result_t dispose_render_target() = 0;

};

#ifdef _MSC_VER
#pragma warning(pop)
#endif


PECKER_END

#endif			//PFX_BUFFER_OBJECT_H_
