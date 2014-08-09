/*
 * pfx_buffer_object_gles.h
 *
 *  Created on: 2014-7-26
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_BUFFER_OBJECT_GLES_H_
#define		PFX_BUFFER_OBJECT_GLES_H_

#include <GLES2/gl2.h>

#include "../pfx_buffer_object.h"
#include "../../../Include/carray"
#include "../../pfx_render_allocator.h"
#include "../../../pfx_hal_info_gles2.h"


PECKER_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

PFX_INLINE GLenum PFX_RENDER_SYSTEM_API PfxVVT_to_GLVVT(PFX_VEXBUFFER_VALUE_TYPE_t vex_value_type)
{
	static 	 GLenum table[PFX_VEXBUFFER_VALUE_TYPE_COUNT+1] = {
		GL_BYTE,
		GL_UNSIGNED_BYTE,
		GL_SHORT,
		GL_UNSIGNED_SHORT,
		GL_FLOAT,
		GL_FIXED,
#ifdef GL_HALF_FLOAT_OES
		GL_HALF_FLOAT_OES,
#else
		GL_FLOAT,
#endif
		GL_BYTE
	};
	return 	table[vex_value_type];
};

PFX_INLINE usize__t PFX_RENDER_SYSTEM_API PFX_VVT_SIZE(PFX_VEXBUFFER_VALUE_TYPE_t vex_value_type)
{
	static 	 GLenum table[PFX_VEXBUFFER_VALUE_TYPE_COUNT + 1] = {
		1,//GL_BYTE,
		1,//GL_UNSIGNED_BYTE,
		2,//GL_SHORT,
		2,//GL_UNSIGNED_SHORT,
		4,//GL_FLOAT,
		4,//GL_FIXED,
#ifdef GL_HALF_FLOAT_OES
		2,//GL_HALF_FLOAT_OES,
#else
		4,//GL_FLOAT,
#endif
		1//GL_BYTE
	};
	return 	table[vex_value_type];
};


class PFX_RENDER_SYSTEM_API cnative_vertex_cache_buffer
{
private:
	carray < vexbuffer_allocator_t >	m_vertexs;
	cs_t								m_locker;
	enum_int_t						 	m_value_type;
	usize__t							m_vb_struct_size;
public:
	 cnative_vertex_cache_buffer();
	 ~cnative_vertex_cache_buffer();

	result_t  dispose();

	void	 lock_cache_buffer(buffer_bits_t& PARAM_INOUT bits,
		const buffer_rect_t* PARAM_IN lock_rect_ptr = null);

	void	 unlock_cache_buffer();

	result_t  copy_to(cnative_vertex_cache_buffer& PARAM_INOUT __other);
	
	result_t  create_cache_buffer(enum_int_t __value_type,		//PFX_VEXBUFFER_VALUE_TYPE_t
		usize__t vb_struct_size,
		usize__t vb_struct_count);
	
	PFX_INLINE usize__t	get_vb_struct_size () const
	{
		return m_vb_struct_size;
	}

	PFX_INLINE usize__t	vb_struct_attribcount() const
	{
		return (m_vb_struct_size / 
			PFX_VVT_SIZE((PFX_VEXBUFFER_VALUE_TYPE_t)m_value_type));
	}
	
	PFX_INLINE enum_int_t	get_value_type() const
	{
		return m_value_type;
	}

	static u64_t get_version();
};

class PFX_RENDER_SYSTEM_API cvertex_cache_buffer_gles2 : public creference_base< cnative_vertex_cache_buffer >,
	public IPfx_vertex_cache_buffer
{
protected:
	typedef  cnative_vertex_cache_buffer ref_element_t;
	typedef  creference_base< cnative_vertex_cache_buffer > ref_t;
	typedef  new_reference_method< cvertex_cache_buffer_gles2 > new_t;
public:
	static PFX_INLINE cvertex_cache_buffer_gles2* new_vertex_cache()
	{
		return new_t::new_reference();
	}
public:
	PFX_INLINE ref_element_t* get_native_buffer()
	{
		return 	get_reference();
	}
	
	PFX_INLINE result_t	lock_cache_buffer(buffer_bits_t& PARAM_INOUT bits,
		const buffer_rect_t* PARAM_IN lock_rect_ptr = null)
	{	
		ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			ref_ptr->lock_cache_buffer(bits, lock_rect_ptr);
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}
	PFX_INLINE result_t	unlock_cache_buffer()
	{
		ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			ref_ptr->unlock_cache_buffer();
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}

	PFX_INLINE IPfx_vertex_cache_buffer* modify_object()
	{
		if (is_referenced())
		{
			return clone();
		}
		else
		{
			return this;
		}	
	}

	PFX_INLINE result_t	create_cache_buffer(enum_int_t __value_type,
		usize__t vb_struct_size,
		usize__t vb_struct_count)
	{
		release_reference();
		ref_element_t* ref_ptr = create_ref_element();
		if (ref_ptr)
		{
			return ref_ptr->create_cache_buffer(__value_type, vb_struct_size, vb_struct_count);
		}
		else
		{
			return PFX_STATUS_MEM_LOW;
		}
	}

	PFX_INLINE usize__t	vb_struct_attribcount() const
	{
		const ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->vb_struct_attribcount();
		}
		else
		{
			return 0;
		}
	}

	PFX_INLINE usize__t	get_vb_struct_size() const
	{
		const ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->get_vb_struct_size();
		}
		else
		{
			return 0;
		}
	}
	PFX_INLINE enum_int_t	get_value_type() const
	{
		const ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->get_value_type();
		}
		else
		{
			return 0;
		}
	}

	PFX_INLINE IPfx_vertex_cache_buffer* clone() const
	{
		const ref_element_t* ref_ptr = get_reference();

		if (!ref_ptr)
		{
			return null;
		}
		//cvertex_cache_buffer_gles2* new_ptr = (cvertex_cache_buffer_gles2*)ref_t::new_t::new_reference();
		cvertex_cache_buffer_gles2* new_ptr = new_vertex_cache();
		result_t status = PFX_STATUS_ERROR_;
		if (new_ptr)
		{
			ref_element_t* new_elem_ptr = new_ptr->get_reference();
			if (new_elem_ptr)
			{
				status = ((ref_element_t*)ref_ptr)->copy_to(*new_elem_ptr);
			}

			if (PFX_STATUS_OK != status)
			{
				new_ptr->release_reference();
			}
		}

		return (IPfx_vertex_cache_buffer*)(new_ptr);
	}


	PFX_INLINE u64_t get_version() const
	{
		return ref_element_t::get_version();
	}
	PFX_INLINE void	 release_reference()
	{
		ref_t::release_reference();
	}

protected:
	PFX_INLINE ref_element_t* create_element()
	{
		return new ref_element_t;
	}
	PFX_INLINE result_t dispose_element(element_t*& elem_ptr)
	{
		if (elem_ptr)
		{
			delete elem_ptr;
			elem_ptr = null;
		}
		return PFX_STATUS_OK;
	}
};



class cbuffer_object_gles2;
class cnative_render_state_gles2;

class PFX_RENDER_SYSTEM_API cnative_buffer_object_gles2
{
	friend class cbuffer_object_gles2;
	friend class cnative_render_state_gles2;
private:
	GLuint							m_bufferID;
	cvertex_cache_buffer_gles2		m_update_data;
	enum_int_t						m_vbo_type;
	enum_int_t						m_usage_type;

private:
	enum_int_t						m_value_type;
	usize__t						m_vb_struct_size;
	usize__t						m_vb_struct_attribcount;
	usize__t						m_bytes_count;
public:
	PFX_INLINE enum_int_t last_value_type() const
	{
		return m_value_type;
	}
	PFX_INLINE usize__t last_struct_size() const
	{
		return m_vb_struct_size;
	}
	PFX_INLINE usize__t last_struct_attribcount() const
	{
		return m_vb_struct_attribcount;
	}
	PFX_INLINE usize__t last_update_bytes_count() const
	{
		return m_bytes_count;
	}
public:
	cnative_buffer_object_gles2();
	~cnative_buffer_object_gles2();
protected:
	result_t create_buffer_object();
	result_t dispose_buffer_object();
	result_t update_data(buffer_rect_t* PARAM_IN update_rect_ptr = null);
public:
	PFX_INLINE GLuint get_bufferID() const
	{
		return m_bufferID;
	}
public:
	PFX_INLINE result_t set_vbo_buffer(cvertex_cache_buffer_gles2* PARAM_IN buffer_ptr)
	{
		if (buffer_ptr)
		{
			if (buffer_ptr->share_to(&m_update_data))
			{
				return PFX_STATUS_OK;
			}
			else
			{
				return PFX_STATUS_FAIL;
			}
		}
		else
		{
			return PFX_STATUS_INVALID_VALUE;
		}
		
	}
	PFX_INLINE result_t set_vbo_type(enum_int_t vbo_type // PFX_BUFFER_OBJECT_TYPE_t
		)
	{
		if (PFX_VERTEX_BUFFER_OBJECT_TYPE == vbo_type ||
			PFX_INDEX_BUFFER_OBJECT_TYPE == vbo_type)
		{
			m_vbo_type = vbo_type;
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_INVALID_ENUM;
		}
		
	}
	PFX_INLINE result_t set_vbo_usage_type(enum_int_t usage_type //PFX_BUFFER_USAGE_TYPE_t
		)
	{
		if (usage_type < PFX_BUFFER_USAGE_TYPE_COUNT)
		{
			m_usage_type = usage_type;
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_INVALID_ENUM;
		}
	}
	static u64_t get_version();
};


PFX_INLINE GLenum PFXVBT_TO_GLVBT(PFX_BUFFER_OBJECT_TYPE_t vbo_type)
{
	if (PFX_VERTEX_BUFFER_OBJECT_TYPE == vbo_type)
	{
		return GL_ARRAY_BUFFER;
	}
	else if (PFX_INDEX_BUFFER_OBJECT_TYPE == vbo_type)
	{
		return GL_ELEMENT_ARRAY_BUFFER;
	}
	else
	{
		return -1;
	}
}

PFX_INLINE GLenum PFXBUT_TO_GLBUT(PFX_BUFFER_USAGE_TYPE_t usage_type)
{
	static GLenum table[PFX_BUFFER_USAGE_TYPE_COUNT + 1] =
	{ GL_STATIC_DRAW,
	GL_DYNAMIC_DRAW,
	GL_STREAM_DRAW,
	GL_STATIC_DRAW };
	return table[usage_type];
}

class PFX_RENDER_SYSTEM_API cbuffer_object_gles2 : public creference_base< cnative_buffer_object_gles2 >,
	public IPfx_buffer_object
{
protected:
	typedef  cnative_buffer_object_gles2 ref_element_t;
	typedef  creference_base< cnative_buffer_object_gles2 > ref_t;
	typedef  new_reference_method< cbuffer_object_gles2 > new_t;
public:
	static PFX_INLINE cbuffer_object_gles2* new_buffer_object()
	{
		return DYNAMIC_CAST(cbuffer_object_gles2*)(new_t::new_reference());
	}
public:
	PFX_INLINE ref_element_t* get_native_buffer()
	{
		return 	get_reference();
	}

	PFX_INLINE IPfx_buffer_object* diff_cache_object()
	{
		const ref_element_t* ref_ptr = get_reference();
		if (!ref_ptr)
		{
			return null;
		}
		cbuffer_object_gles2* new_ptr = new_buffer_object();//(cbuffer_object_gles2*)ref_t::new_t::new_reference();

		result_t status = PFX_STATUS_ERROR_;
		if (new_ptr)
		{
			ref_element_t* new_elem_ptr = new_ptr->get_reference();
			if (new_elem_ptr)
			{
				new_elem_ptr->m_bufferID = ref_ptr->m_bufferID;
				status = PFX_STATUS_OK;
			}
		}
		return (IPfx_buffer_object*)(new_ptr);
	}

	PFX_INLINE result_t set_vbo_buffer(IPfx_vertex_cache_buffer* PARAM_IN buffer_ptr)
	{
		if (!buffer_ptr || 
			buffer_ptr->get_version() != cnative_vertex_cache_buffer::get_version())
		{
			return PFX_STATUS_INVALID_VALUE;
		}
		ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->set_vbo_buffer(DYNAMIC_CAST(cvertex_cache_buffer_gles2*)(buffer_ptr));
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}
	PFX_INLINE result_t set_vbo_type(enum_int_t vbo_type // PFX_BUFFER_OBJECT_TYPE_t
		)
	{
		ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->set_vbo_type(vbo_type);
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}
	PFX_INLINE result_t set_vbo_usage_type(enum_int_t usage_type //PFX_BUFFER_USAGE_TYPE_t
		)
	{
		ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->set_vbo_usage_type(usage_type);
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}


	PFX_INLINE long_t get_native_location() const
	{
		const ref_element_t* ref_ptr = get_reference();
		if (ref_ptr)
		{
			return ref_ptr->get_bufferID();
		}
		else
		{
			return PFX_STATUS_UNINIT;
		}
	}


	PFX_INLINE u64_t get_version() const
	{
		return ref_element_t::get_version();
	}
	PFX_INLINE void	 release_reference()
	{
		ref_t::release_reference();
	}

protected:
	PFX_INLINE element_t* create_element()
	{
		return new element_t;
	}
	PFX_INLINE result_t dispose_element(element_t*& elem_ptr)
	{
		if (elem_ptr)
		{
			delete elem_ptr;
			elem_ptr = null;
		}
		return PFX_STATUS_OK;
	}
};


#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_BUFFER_OBJECT_GLES_H_
