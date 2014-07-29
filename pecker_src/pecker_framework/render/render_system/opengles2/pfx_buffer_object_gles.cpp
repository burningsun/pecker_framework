/*
 * pfx_buffer_object_gles.cpp
 *
 *  Created on: 2014-7-26
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */


#include "pfx_buffer_object_gles.h"

PECKER_BEGIN

cnative_vertex_cache_buffer::cnative_vertex_cache_buffer() :m_value_type(PFXVB_BYTE), m_vb_struct_size(0)
{
	InitCriticalSection(&m_locker);
}
cnative_vertex_cache_buffer::~cnative_vertex_cache_buffer()
{
	DelCriticalSection(&m_locker);
}

result_t cnative_vertex_cache_buffer::dispose()
{
	result_t status;
	status = m_vertexs.dispose();
	m_value_type = PFXVB_BYTE;
	m_vb_struct_size = 0;
	return status;
}

void cnative_vertex_cache_buffer::lock_cache_buffer(buffer_bits_t& PARAM_INOUT bits,
	const buffer_rect_t* PARAM_IN lock_rect_ptr //= null
	)
{
	LockCriticalSection(&m_locker);
	if (!lock_rect_ptr)
	{
		bits.m_bytes_count = m_vertexs.size();
		bits.m_bits_ptr = m_vertexs.get_block_ptr()->begin();
	}
	else if (0 == lock_rect_ptr->m_size)
	{
		bits.m_bits_ptr = null;
		bits.m_bytes_count = 0;
	}
	else
	{
		bits.m_bits_ptr = m_vertexs.get_block_ptr()->pointer(lock_rect_ptr->m_offset);
		if (bits.m_bits_ptr)
		{
			usize__t remain_size;
			remain_size = m_vertexs.size() - lock_rect_ptr->m_offset;
			bits.m_bytes_count = (remain_size > lock_rect_ptr->m_size) ?
				(lock_rect_ptr->m_size) : (remain_size);
		}
		else
		{
			bits.m_bytes_count = 0;
		}
	}
}
 
void cnative_vertex_cache_buffer::unlock_cache_buffer()
{
	UnlockCriticalSection(&m_locker);
}

result_t cnative_vertex_cache_buffer::copy_to(cnative_vertex_cache_buffer& PARAM_INOUT __other)
{
	if (&__other == this)
	{
		return PFX_STATUS_OK;
	}
	result_t status;
	critical_section_lock_t __lock;
	__lock.lock(m_locker);
	status = this->m_vertexs.copy_to(__other.m_vertexs);
	__lock.unlock();
	return status;
}

result_t cnative_vertex_cache_buffer::create_cache_buffer(enum_int_t __value_type,
	usize__t vb_struct_size,
	usize__t vb_struct_count)
{
	RETURN_INVALID_RESULT((__value_type >= PFX_VEXBUFFER_VALUE_TYPE_COUNT
		|| !vb_struct_size || !vb_struct_count), PFX_STATUS_INVALID_VALUE);

	m_vertexs.clean();

	result_t status;
	status = m_vertexs.resize(vb_struct_size * vb_struct_count);
	if (PFX_STATUS_OK == status)
	{
		m_value_type = __value_type;
		m_vb_struct_size = vb_struct_size;
	}
	else
	{
		m_value_type = PFXVB_BYTE;
		m_vb_struct_size = 0;
	}
	return status;
}

u64_t cnative_vertex_cache_buffer::get_version()
{
	return (get_hal_instanse_ID().m_version);
}

cnative_buffer_object_gles2::cnative_buffer_object_gles2() :m_bufferID(0),
m_vbo_type(PFX_VERTEX_BUFFER_OBJECT_TYPE),
m_usage_type(PFX_BU_STATIC_DRAW),
m_value_type(PFXVB_BYTE), m_vb_struct_size(0),
m_vb_struct_attribcount(0)
{
	;
}
cnative_buffer_object_gles2::~cnative_buffer_object_gles2()
{
	dispose_buffer_object();
}


result_t cnative_buffer_object_gles2::create_buffer_object()
{
	::glGenBuffers(1, &m_bufferID);
	if (m_bufferID)
	{
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_FAIL;
	}
}

result_t cnative_buffer_object_gles2::dispose_buffer_object()
{
	if (m_bufferID)
	{
		::glDeleteBuffers(1, &m_bufferID);
		m_bufferID = 0;
	}
	return PFX_STATUS_OK;
}
	
result_t cnative_buffer_object_gles2::update_data(buffer_rect_t* PARAM_IN update_rect_ptr //= null
	)
{
	if (!m_bufferID)
	{
		return PFX_STATUS_UNINIT;
	}
	GLenum target_type = PFXVBT_TO_GLVBT((PFX_BUFFER_OBJECT_TYPE_t)m_vbo_type);
	if (-1 == target_type)
	{
		return PFX_STATUS_INVALID_ENUM;
	}
	result_t status = PFX_STATUS_OK;
	glBindBuffer(target_type, m_bufferID);
	cnative_vertex_cache_buffer* buffer_ptr = m_update_data.get_native_buffer();
	if (buffer_ptr)
	{
		GLenum usage_type = PFXBUT_TO_GLBUT((PFX_BUFFER_USAGE_TYPE_t)m_usage_type);
		buffer_bits_t bits;
		buffer_ptr->lock_cache_buffer(bits, update_rect_ptr);
		if (bits.m_bits_ptr && bits.m_bytes_count)
		{
			m_bytes_count			= bits.m_bytes_count;
			m_value_type			= buffer_ptr->get_value_type();
			m_vb_struct_size		= buffer_ptr->get_vb_struct_size();
			m_vb_struct_attribcount = buffer_ptr->vb_struct_attribcount();
			if (!update_rect_ptr)
			{
				glBufferData(target_type,
					(GLsizeiptr)&bits.m_bytes_count,
					bits.m_bits_ptr,
					usage_type);
			}
			else
			{
				glBufferSubData(target_type,
					(GLintptr)&update_rect_ptr->m_offset,
					(GLsizeiptr)&update_rect_ptr->m_size,
					bits.m_bits_ptr);
			}
		}
		else
		{
			status = PFX_STATUS_FAIL;
		}

		buffer_ptr->unlock_cache_buffer();
	}
	m_update_data.release_reference();
	return status;
}
u64_t cnative_buffer_object_gles2::get_version()
{
	return (get_hal_instanse_ID().m_version);
}


PECKER_END

