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
#include "../../../Include/native"
#include "../../../pfx_hal_info_gles2.h"
#include "pfx_render_allocator_gles.h"

PECKER_BEGIN

#define RBUFFER_DEBUG
#undef RBUFFER_LOG_STR
#undef RBUFFER_LOG_INFO
#ifdef RBUFFER_DEBUG

#define RBUFFER_LOG_STR PECKER_LOG_STR
#define RBUFFER_LOG_INFO PECKER_LOG_INFO
#else
#define RBUFFER_LOG_STR(...)
#define RBUFFER_LOG_INFO(...)
#endif

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
	DECLARE_FRIEND_CLASS(class cvertex_cache_buffer_gles2);
	DECLARE_FRIEND_CLASS(VERTEXT_CACHE_ALLOC_GLES2);

	DEFINE_NATIVE_REF_POOL(VERTEXT_CACHE_NODE_ALLOC_GLES2, VERTEXT_CACHE_ALLOC_GLES2,m_ref_pool);

protected:
	DECLARE_NATIVE_CREATE_NEW_NODE(cvertex_cache_buffer_gles2, create_vertex_node);
	DECLARE_NATIVE_CREATE_SHARE_NODE(cvertex_cache_buffer_gles2, share_vertex_node);
	DECLARE_NATIVE_DISPOSE_SHARE_NODE(cvertex_cache_buffer_gles2, dispose_vertex_node);
private:
	carray < vexbuffer_allocator_t >	m_vertexs;
	cs_t								m_locker;
	enum_int_t						 	m_value_type;
	usize__t							m_vb_struct_size;

private:
	 cnative_vertex_cache_buffer();
	 cnative_vertex_cache_buffer(const cnative_vertex_cache_buffer& __other);
	 cnative_vertex_cache_buffer& operator=(const cnative_vertex_cache_buffer& __other);
public:
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

class PFX_RENDER_SYSTEM_API cvertex_cache_buffer_gles2;

DECLARE_REF_NODE_CLASS_PROTECTED_BEGIN(cvertex_cache_buffer_gles2, 
cnative_vertex_cache_buffer, IPfx_vertex_cache_buffer, base_t,
vertex_cache_node_alloc_gles2_t,
vertex_cache_alloc_gles2_t)

//friend cnative_vertex_cache_buffer::ref_pool_memanger_t;
//
DECLARE_FRIEND_CLASS(class cnative_vertex_cache_buffer);
DECLARE_FRIEND_CLASS(VERTEXT_CACHE_NODE_ALLOC_GLES2);
//
public:
DECLARE_REF_CREATE_NEW_NODE(cvertex_cache_buffer_gles2, new_vertex_cache);
DECLARE_REF_CREATE_SHARE_NODE(cvertex_cache_buffer_gles2, new_share_vertex);
DECLARE_REF_DISPOSE_SHARE_NODE(cvertex_cache_buffer_gles2, dispose_vertex);

protected:
	typedef  cnative_vertex_cache_buffer ref_element_t;
private:
	cvertex_cache_buffer_gles2(){ RBUFFER_LOG_INFO("create...0x%08X", (lpointer_t)this); }
	
public:
	virtual ~cvertex_cache_buffer_gles2(){ dispose_vertex(); RBUFFER_LOG_INFO("release...0x%08X", (lpointer_t)this); }
public:
	result_t	lock_cache_buffer(buffer_bits_t& PARAM_INOUT bits,
		const buffer_rect_t* PARAM_IN lock_rect_ptr = null);
	
	result_t	unlock_cache_buffer();

	result_t	reset_cache_buffer(enum_int_t __value_type,
		usize__t vb_struct_size,
		usize__t vb_struct_count);

	usize__t	vb_struct_attribcount() const;

	usize__t	get_vb_struct_size() const;

	enum_int_t	get_value_type() const;

	IPfx_vertex_cache_buffer* clone() const;
	
	u64_t get_version() const;

	IPfx_vertex_cache_buffer* new_share();

	static cvertex_cache_buffer_gles2* create_cache_buffer(enum_int_t __value_type,
		usize__t vb_struct_size,
		usize__t vb_struct_count);

DECLARE_REF_NODE_CLASS_END;

//////////////////////////////////////////////////////////////////////////
STATIC_NATIVE_CREATE_NEW_NODE(cnative_vertex_cache_buffer, cvertex_cache_buffer_gles2, create_vertex_node);
NATIVE_CREATE_SHARE_NODE(cnative_vertex_cache_buffer, cvertex_cache_buffer_gles2, share_vertex_node, m_ref_pool);
NATIVE_DISPOSE_SHARE_NODE(cnative_vertex_cache_buffer, cvertex_cache_buffer_gles2, dispose_vertex_node, m_ref_pool);
//////////////////////////////////////////////////////////////////////////
STATIC_REF_CREATE_NEW_NODE(cnative_vertex_cache_buffer, cvertex_cache_buffer_gles2, 
	new_vertex_cache, create_vertex_node);
REF_CREATE_SHARE_NODE(base_t, cvertex_cache_buffer_gles2, new_share_vertex, share_vertex_node);
REF_DISPOSE_SHARE_NODE(base_t, cvertex_cache_buffer_gles2, dispose_vertex, dispose_vertex_node);



class cnative_render_state_gles2;

class PFX_RENDER_SYSTEM_API cnative_buffer_object_gles2
{
	DECLARE_FRIEND_CLASS(class cnative_render_state_gles2);
	DECLARE_FRIEND_CLASS(class cbuffer_object_gles2);
	DECLARE_FRIEND_CLASS(BUFFER_OBJECT_ALLOC_GLES2);
	DEFINE_NATIVE_REF_POOL(BUFFER_OBJECT_NODE_ALLOC_GLES2, BUFFER_OBJECT_ALLOC_GLES2, m_ref_pool);
protected:
	DECLARE_NATIVE_CREATE_NEW_NODE(cbuffer_object_gles2, create_buffer_node);
	DECLARE_NATIVE_CREATE_SHARE_NODE(cbuffer_object_gles2, share_buffer_node);
	DECLARE_NATIVE_DISPOSE_SHARE_NODE(cbuffer_object_gles2, dispose_buffer_node);
private:
	GLuint							m_bufferID;
	cvertex_cache_buffer_gles2*		m_update_data_ptr;
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
	
private:
	cnative_buffer_object_gles2();
public:
	virtual ~cnative_buffer_object_gles2();

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
			// 引用一样，就懒得拷贝了
			if (m_update_data_ptr &&
				(buffer_ptr->ref_ptr() == m_update_data_ptr->ref_ptr()))
			{
				return PFX_STATUS_OK;
			}
			// 创建新的引用，然后将原来的引用去掉
			cvertex_cache_buffer_gles2* share_ptr = buffer_ptr->new_share_vertex();
			if (share_ptr)
			{
				if (m_update_data_ptr)
				{
					m_update_data_ptr->dispose_vertex();
				}
				
				m_update_data_ptr = share_ptr;
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

class PFX_RENDER_SYSTEM_API cbuffer_object_gles2;

DECLARE_REF_NODE_CLASS_PROTECTED_BEGIN(cbuffer_object_gles2,
cnative_buffer_object_gles2, IPfx_buffer_object, base_t,
buffer_object_node_alloc_gles2_t,
buffer_object_alloc_gles2_t)
//
    DECLARE_FRIEND_CLASS(class cnative_buffer_object_gles2);
    DECLARE_FRIEND_CLASS(BUFFER_OBJECT_NODE_ALLOC_GLES2);
	//DECLARE_BE_REF_POOL_MEMANGER_FRIEND(BUFFER_OBJECT_NODE_ALLOC_GLES2, BUFFER_OBJECT_ALLOC_GLES2);
//
public:
	DECLARE_REF_CREATE_NEW_NODE(cbuffer_object_gles2, new_buffer);
	DECLARE_REF_CREATE_SHARE_NODE(cbuffer_object_gles2, new_share_buffer);
	DECLARE_REF_DISPOSE_SHARE_NODE(cbuffer_object_gles2, dispose_buffer);
protected:
	typedef  cnative_buffer_object_gles2 ref_element_t;
	
private:
	cbuffer_object_gles2(){ RBUFFER_LOG_INFO("create...0x%08X", (lpointer_t)this); }
	
public:
	virtual ~cbuffer_object_gles2(){ dispose_buffer(); RBUFFER_LOG_INFO("release...0x%08X", (lpointer_t)this); }

public:
	IPfx_buffer_object* diff_cache_object();

	result_t set_vbo_buffer(IPfx_vertex_cache_buffer* PARAM_IN buffer_ptr);
	result_t set_vbo_type(enum_int_t vbo_type // PFX_BUFFER_OBJECT_TYPE_t
		);
	result_t set_vbo_usage_type(enum_int_t usage_type //PFX_BUFFER_USAGE_TYPE_t
		);


	long_t get_native_location() const;


	u64_t get_version() const;

	PFX_INLINE IPfx_buffer_object* new_share()
	{
		return new_share_buffer();
	}


DECLARE_REF_NODE_CLASS_END;

//////////////////////////////////////////////////////////////////////////
STATIC_NATIVE_CREATE_NEW_NODE(cnative_buffer_object_gles2, cbuffer_object_gles2, create_buffer_node);
NATIVE_CREATE_SHARE_NODE(cnative_buffer_object_gles2, cbuffer_object_gles2, share_buffer_node, m_ref_pool);
NATIVE_DISPOSE_SHARE_NODE(cnative_buffer_object_gles2, cbuffer_object_gles2, dispose_buffer_node, m_ref_pool);
//////////////////////////////////////////////////////////////////////////
STATIC_REF_CREATE_NEW_NODE(cnative_buffer_object_gles2, cbuffer_object_gles2, new_buffer, create_buffer_node);
REF_CREATE_SHARE_NODE(base_t, cbuffer_object_gles2, new_share_buffer, share_buffer_node);
REF_DISPOSE_SHARE_NODE(base_t, cbuffer_object_gles2, dispose_buffer, dispose_buffer_node);


#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_BUFFER_OBJECT_GLES_H_
