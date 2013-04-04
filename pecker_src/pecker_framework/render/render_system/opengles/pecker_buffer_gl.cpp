/*
 * pecker_buffer_gl.cpp
 *
 *  Created on: 2013-3-19
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#include "pecker_buffer_gl.h"
#include "../../../native/pecker_allocator.h"
#include <GLES2/gl2.h>



PECKER_BEGIN
typedef pecker_simple_allocator<Byte> render_buffer_allocator;

pecker_vertex_buffer_gles2::pecker_vertex_buffer_gles2():
_M_bytes_count(0),_M_gpu_target(0),_M_vertex_attribute_count(0),_M_first_update_buffer(false),_M_vbo_setting(DEFUALT_VBO)
{
	_M_vertex_buffer._M_buffer = null;
}

pecker_vertex_buffer_gles2::~pecker_vertex_buffer_gles2()
{
	release_buffer_from_cpu_ram();
	release_buffer_from_gpu_ram();
	
	_M_bytes_count = 0;
	_M_gpu_target = 0;
	_M_vertex_attribute_count = 0;
	_M_vertex_buffer._M_buffer = null;
}

HResult pecker_vertex_buffer_gles2::allocate_buffer_from_cpu_ram(nSize number_of_bytes,const PVoid pdata_buffer/* = null */)
{
	if (null != _M_vertex_buffer._M_bytes)
	{
		return P_UNIQUE_ERR;
	}

	_M_vertex_buffer._M_bytes = render_buffer_allocator::allocate_objects(number_of_bytes);
	if (null != _M_vertex_buffer._M_bytes)
	{
		_M_bytes_count = number_of_bytes;
	}
	else
	{
		return P_FAIL;
	}
	Byte* pbyte_data_buffer = static_cast<Byte*>(pdata_buffer);
	if (null != pbyte_data_buffer)
	{
		for (nINDEX i = 0;i<number_of_bytes;++i)
		{
			_M_vertex_buffer._M_bytes[i] = pbyte_data_buffer[i];
		}
	}

	return P_OK;
}

HResult pecker_vertex_buffer_gles2::release_buffer_from_cpu_ram()
{
	if (null != _M_vertex_buffer._M_bytes)
	{
		render_buffer_allocator::deallocate_objects(_M_vertex_buffer._M_bytes);
		_M_vertex_buffer._M_bytes = null;
		
	}
	_M_bytes_count = 0;

	return P_OK;
}

nSize pecker_vertex_buffer_gles2::get_buffer_size() const
{
	return _M_bytes_count;
}

const Byte* pecker_vertex_buffer_gles2::get_data() const
{
	return _M_vertex_buffer._M_bytes;
}

HResult pecker_vertex_buffer_gles2::lock_data(Byte* &pdata)
{
	if (null == _M_vertex_buffer._M_bytes)
	{
		return P_ERR;
	}
	else
	{
		pdata = _M_vertex_buffer._M_bytes;
		return P_OK;
	}
}

HResult pecker_vertex_buffer_gles2::unlock_data()
{
	return P_OK;
}

HResult pecker_vertex_buffer_gles2::allocate_buffer_from_gpu_ram()
{
	if (0 == _M_gpu_target)
	{
		glGenBuffers(1,&_M_gpu_target);
		_M_first_update_buffer = true;
		return pecker_opengles_v2_object::get_last_error_code();
	}
	return P_UNIQUE_ERR;
}

HResult pecker_vertex_buffer_gles2::release_buffer_from_gpu_ram()
{
	glDeleteBuffers(1,&_M_gpu_target);
	_M_first_update_buffer = true;
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_vertex_buffer_gles2::set_defualt_gpu_buffer_update_info(const update_gpu_ram_info& pupdate_info)
{
	_M_defual_gpu_buffer_setting = pupdate_info;
	return P_OK;
}

HResult pecker_vertex_buffer_gles2::update_gpu_buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER,_M_gpu_target);
	HResult error_code;
	if (!_M_first_update_buffer && (_M_defual_gpu_buffer_setting._M_offset != 0 || 
		_M_defual_gpu_buffer_setting._M_update_size != _M_bytes_count))
	{
		glBufferSubData(_M_gpu_target,
			_M_defual_gpu_buffer_setting._M_offset,
			_M_defual_gpu_buffer_setting._M_update_size,
			_M_vertex_buffer._M_bytes + _M_defual_gpu_buffer_setting._M_offset);
		error_code = pecker_opengles_v2_object::get_last_error_code();
	}
	else
	{
		glBufferData(_M_gpu_target,
			_M_bytes_count,
			_M_vertex_buffer._M_bytes,
			_M_defual_gpu_buffer_setting._M_usage_type);

		error_code = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == error_code)
		{
			_M_first_update_buffer = false;
		}
	}
	return error_code;
}

HResult pecker_vertex_buffer_gles2::update_gpu_buffer(const update_gpu_ram_info& pupdate_info)
{
	glBindBuffer(GL_ARRAY_BUFFER,_M_gpu_target);
	HResult error_code;
	if (!_M_first_update_buffer &&(pupdate_info._M_offset != 0 || 
		pupdate_info._M_update_size != _M_bytes_count))
	{
		glBufferSubData(_M_gpu_target,
			pupdate_info._M_offset,
			pupdate_info._M_update_size,
			_M_vertex_buffer._M_bytes + pupdate_info._M_offset);
		error_code = pecker_opengles_v2_object::get_last_error_code();
	}
	else
	{
		glBufferData(_M_gpu_target,
			_M_bytes_count,
			_M_vertex_buffer._M_bytes,
			pupdate_info._M_usage_type);

		error_code = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == error_code)
		{
			_M_first_update_buffer = false;
		}
	}
	return error_code;
}

HResult pecker_vertex_buffer_gles2::bind_gpu_buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER,_M_gpu_target);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_vertex_buffer_gles2::add_defualt_vertex_attribute_setting(const vertex_attribute_info& vertex_attri_info)
{
	if (vertex_attri_info._M_attribute_index < MAX_VERTEXT_ATTRIBUTE_COUNT &&
		vertex_attri_info._M_attribute_index >= 0)
	{
		if (_M_vertex_attribute[vertex_attri_info._M_attribute_index]._M_attribute_index < 0)
		{
			++_M_vertex_attribute_count;
		}
		_M_vertex_attribute[vertex_attri_info._M_attribute_index] = vertex_attri_info;
		return P_OK;
	}
	else
	{
		return P_INVALID_VALUE;
	}
}

HResult pecker_vertex_buffer_gles2::clear_vertex_attribute_setting()
{
	for (nINDEX i=0;i<MAX_VERTEXT_ATTRIBUTE_COUNT;++i)
	{
		if (_M_vertex_attribute[i]._M_attribute_index >= 0)
		{
			_M_vertex_attribute[i]._M_attribute_index = -1;
			--_M_vertex_attribute_count;
		}
		if (_M_vertex_attribute_count <= 0)
		{
			break;
		}
	}
	return P_OK;
}

vertex_attribute_info* pecker_vertex_buffer_gles2::get_vertex_attribute_reference(UInt vex_info_index)
{
	if (vex_info_index < MAX_VERTEXT_ATTRIBUTE_COUNT && vex_info_index >= 0)
	{
		return &_M_vertex_attribute[vex_info_index];
	}
	else
	{
		return null;
	}
}

nSize pecker_vertex_buffer_gles2::get_vertex_attribute_setting_count() const
{
	return _M_vertex_attribute_count;
}

HResult pecker_vertex_buffer_gles2::use_vertex_attrible()
{
	glBindBuffer(GL_ARRAY_BUFFER,_M_gpu_target);
	nSize set_count = 0;
	for (nINDEX i=0;i<MAX_VERTEXT_ATTRIBUTE_COUNT;++i)
	{
		if (_M_vertex_attribute[i]._M_attribute_index >= 0)
		{
			Byte* pIndata;
			switch(_M_vbo_setting)
			{
			case ALL_ENABLE_VBO:
				pIndata = null;
				break;
			case ALL_DISABLE_VBO:
				pIndata = _M_vertex_buffer._M_bytes;
				break;
			case DEFUALT_VBO:
			default:
				if (_M_vertex_attribute[i]._M_use_vbo)
				{
					pIndata = null;
				}
				else
				{
					pIndata = _M_vertex_buffer._M_bytes;
				}
				break;
			}
			glEnableVertexAttribArray(_M_vertex_attribute[i]._M_attribute_index);
			glVertexAttribPointer(_M_vertex_attribute[i]._M_attribute_index,
				_M_vertex_attribute[i]._M_attribute_size,
				_M_vertex_attribute[i]._M_attribute_data_type,
				_M_vertex_attribute[i]._M_normalized,
				_M_vertex_attribute[i]._M_stride,
				_M_vertex_attribute[i]._M_offset + pIndata);
			++set_count;
		}

		if (set_count >= _M_vertex_attribute_count)
		{
			break;
		}
	}
	return pecker_vertex_buffer_gles2::get_last_error_code();
}

HResult pecker_vertex_buffer_gles2::finish_using_vertex_attrible()
{
	glBindBuffer(GL_ARRAY_BUFFER,_M_gpu_target);
	nSize set_count = 0;
	for (nINDEX i=0;i<MAX_VERTEXT_ATTRIBUTE_COUNT;++i)
	{
		if (_M_vertex_attribute[i]._M_attribute_index >= 0)
		{
			glDisableVertexAttribArray(_M_vertex_attribute[i]._M_attribute_index);
			++set_count;
		}

		if (set_count >= _M_vertex_attribute_count)
		{
			break;
		}
	}
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_vertex_buffer_gles2::set_vbo_using_setting(HEnum setting)
{
	if (setting < VBO_USING_SETTING_COUNT)
	{
		_M_vbo_setting = setting;
		return P_OK;
	}
	return P_INVALID_VALUE;
}

UInt pecker_vertex_buffer_gles2::get_object_location() const
{
	return _M_gpu_target;
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

pecker_index_buffer_gles2::pecker_index_buffer_gles2() : _M_bytes_count(0),_M_gpu_target(0),_M_first_update_buffer(true)//,_M_vbo_setting(DEFUALT_VBO)
{
	_M_index_buffer._M_buffer = null;
}

pecker_index_buffer_gles2::~pecker_index_buffer_gles2()
{
	release_buffer_from_cpu_ram();
	release_buffer_from_gpu_ram();
	_M_bytes_count = 0;

	_M_first_update_buffer = true;
	_M_gpu_target = 0;
	_M_index_buffer._M_buffer = null;
}


HResult pecker_index_buffer_gles2::allocate_buffer_from_cpu_ram(nSize number_of_bytes,const PVoid pdata_buffer/* = null */)
{
	if (null != _M_index_buffer._M_bytes)
	{
		return P_UNIQUE_ERR;
	}

	_M_index_buffer._M_bytes = render_buffer_allocator::allocate_objects(number_of_bytes);
	if (null != _M_index_buffer._M_bytes)
	{
		_M_bytes_count = number_of_bytes;
	}
	else
	{
		return P_FAIL;
	}
	Byte* pbyte_data_buffer = static_cast<Byte*>(pdata_buffer);
	if (null != pbyte_data_buffer)
	{
		for (nINDEX i = 0;i<number_of_bytes;++i)
		{
			_M_index_buffer._M_bytes[i] = pbyte_data_buffer[i];
		}
	}

	return P_OK;
}

HResult pecker_index_buffer_gles2::release_buffer_from_cpu_ram()
{
	if (null != _M_index_buffer._M_bytes)
	{
		render_buffer_allocator::deallocate_objects(_M_index_buffer._M_bytes);
		_M_index_buffer._M_bytes = null;

	}
	_M_bytes_count = 0;

	return P_OK;
}

nSize pecker_index_buffer_gles2::get_buffer_size() const
{
	return _M_bytes_count;
}

const Byte* pecker_index_buffer_gles2::get_data() const
{
	return _M_index_buffer._M_bytes;
}

HResult pecker_index_buffer_gles2::lock_data(Byte* &pdata)
{
	if (null == _M_index_buffer._M_bytes)
	{
		return P_ERR;
	}
	else
	{
		pdata = _M_index_buffer._M_bytes;
		return P_OK;
	}
}

HResult pecker_index_buffer_gles2::unlock_data()
{
	return P_OK;
}

HResult pecker_index_buffer_gles2::allocate_buffer_from_gpu_ram()
{
	if (0 == _M_gpu_target)
	{
		glGenBuffers(1,&_M_gpu_target);
		_M_first_update_buffer = true;
		return pecker_opengles_v2_object::get_last_error_code();
	}
	return P_UNIQUE_ERR;
}

HResult pecker_index_buffer_gles2::release_buffer_from_gpu_ram()
{
	glDeleteBuffers(1,&_M_gpu_target);
	_M_first_update_buffer = true;
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_index_buffer_gles2::set_defualt_gpu_buffer_update_info(const update_gpu_ram_info& pupdate_info)
{
	_M_defual_gpu_buffer_setting = pupdate_info;
	return P_OK;
}

HResult pecker_index_buffer_gles2::update_gpu_buffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_M_gpu_target);
	HResult error_code;
	if (!_M_first_update_buffer && (_M_defual_gpu_buffer_setting._M_offset != 0 || 
		_M_defual_gpu_buffer_setting._M_update_size != _M_bytes_count))
	{
		glBufferSubData(_M_gpu_target,
			_M_defual_gpu_buffer_setting._M_offset,
			_M_defual_gpu_buffer_setting._M_update_size,
			_M_index_buffer._M_bytes + _M_defual_gpu_buffer_setting._M_offset);
		error_code = pecker_opengles_v2_object::get_last_error_code();
	}
	else
	{
		glBufferData(_M_gpu_target,
			_M_bytes_count,
			_M_index_buffer._M_bytes,
			_M_defual_gpu_buffer_setting._M_usage_type);

		error_code = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == error_code)
		{
			_M_first_update_buffer = false;
		}
	}
	return error_code;
}

HResult pecker_index_buffer_gles2::update_gpu_buffer(const update_gpu_ram_info& pupdate_info)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_M_gpu_target);
	HResult error_code;
	if (!_M_first_update_buffer &&(pupdate_info._M_offset != 0 || 
		pupdate_info._M_update_size != _M_bytes_count))
	{
		glBufferSubData(_M_gpu_target,
			pupdate_info._M_offset,
			pupdate_info._M_update_size,
			_M_index_buffer._M_bytes + pupdate_info._M_offset);
		error_code = pecker_opengles_v2_object::get_last_error_code();
	}
	else
	{
		glBufferData(_M_gpu_target,
			_M_bytes_count,
			_M_index_buffer._M_bytes,
			pupdate_info._M_usage_type);

		error_code = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == error_code)
		{
			_M_first_update_buffer = false;
		}
	}
	return error_code;
}

HResult pecker_index_buffer_gles2::bind_gpu_buffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_M_gpu_target);
	return pecker_opengles_v2_object::get_last_error_code();
}

UInt pecker_index_buffer_gles2::get_object_location() const
{
	return _M_gpu_target;
}

//HResult pecker_index_buffer_gles2::set_vbo_using_setting(HEnum setting)
//{
//	if (setting < VBO_USING_SETTING_COUNT)
//	{
//		_M_vbo_setting = setting;
//		return P_OK;
//	}
//	return P_INVALID_VALUE;
//}

//////////////////////////////////////////////////////////////////////////
//

pecker_vertex_index_buffer_collection_gles2::pecker_vertex_index_buffer_collection_gles2()
{

}

pecker_vertex_index_buffer_collection_gles2::~pecker_vertex_index_buffer_collection_gles2()
{

}

Ipecker_vertex_buffer* pecker_vertex_index_buffer_collection_gles2::get_vertex_buffer_reference(UInt buffer_index)
{
	if (buffer_index < pecker_vertex_buffer_gles2::MAX_VERTEXT_ATTRIBUTE_COUNT)
	{
		return _M_vertex_buffer[buffer_index];
	}
	else
	{
		return null;
	}
}

Ipecker_index_buffer* pecker_vertex_index_buffer_collection_gles2::get_index_buffer_reference(UInt buffer_index /* = 0 */)
{
	if (buffer_index > 0)
	{
		return null;
	}
	else
	{
		return _M_index_buffer;
	}
}

nSize pecker_vertex_index_buffer_collection_gles2::get_vertex_buffer_count() const
{
	return _M_vertex_buffer_count;
}

nSize pecker_vertex_index_buffer_collection_gles2::get_index_buffer_count() const
{
	if (null != _M_index_buffer)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

HResult pecker_vertex_index_buffer_collection_gles2::bind_buffers_and_use_attribute()
{
	HResult error_code = P_INVALID_VALUE;
	nSize vex_buf_count = _M_vertex_buffer_count;
	for (nINDEX i=0; i<pecker_vertex_buffer_gles2::MAX_VERTEXT_ATTRIBUTE_COUNT;++i)
	{
		if (null == _M_vertex_buffer[i])
		{
			error_code = _M_vertex_buffer[i]->use_vertex_attrible();
			--vex_buf_count;
		}
		if (P_OK != error_code)
		{
			return error_code;
		}
		if (0 == vex_buf_count)
		{
			break;
		}
		
	}

	if (null != _M_index_buffer)
	{
		error_code = _M_index_buffer->bind_gpu_buffer();
	}

	return error_code;
}

HResult pecker_vertex_index_buffer_collection_gles2::finish_using_buffer_attribute()
{
	HResult error_code = P_INVALID_VALUE;
	nSize vex_buf_count = _M_vertex_buffer_count;
	for (nINDEX i=0; i<pecker_vertex_buffer_gles2::MAX_VERTEXT_ATTRIBUTE_COUNT;++i)
	{
		if (null == _M_vertex_buffer[i])
		{
			error_code = _M_vertex_buffer[i]->finish_using_vertex_attrible();
			--vex_buf_count;
		}
		if (P_OK != error_code)
		{
			return error_code;
		}
		if (0 == vex_buf_count)
		{
			break;
		}

	}

	return error_code;
}

HResult pecker_vertex_index_buffer_collection_gles2::attach_buffer(Ipecker_graphic_buffer* pbuffer)
{
	if (null == pbuffer)
	{
		return P_INVALID_VALUE;
	}
	if (_M_vertex_buffer_count == pecker_vertex_buffer_gles2::MAX_VERTEXT_ATTRIBUTE_COUNT)
	{
		return P_OUT_OF_MEMORY;
	}
	HEnum buffer_type = pbuffer->get_buffer_type();
	HResult error_code = P_OK;
	switch(buffer_type)
	{
	case VERTEX_BUFFER_TYPE:
		_M_vertex_buffer[_M_vertex_buffer_count] = dynamic_cast< Ipecker_vertex_buffer* >(pbuffer);
		if (null != _M_vertex_buffer[_M_vertex_buffer_count])
		{
			++_M_vertex_buffer_count;
		}
		else
		{
			error_code = P_INVALID_VALUE;
		}
		break;
	case INDEX_BUFFER_TYPE:
		_M_index_buffer = dynamic_cast< Ipecker_index_buffer* >(pbuffer);
		if (null == _M_index_buffer)
		{
			error_code = P_INVALID_VALUE;
		}
		break;
	default:
		error_code = P_INVALID_VALUE;
		break;
	}

	return error_code;
}

HResult pecker_vertex_index_buffer_collection_gles2::dettach_all_buffer()
{
	for (nINDEX i=0;i<pecker_vertex_buffer_gles2::MAX_VERTEXT_ATTRIBUTE_COUNT;++i)
	{
		_M_vertex_buffer[i] = null;
	}
	_M_index_buffer = null;
	return P_OK;
}

HResult pecker_vertex_index_buffer_collection_gles2::bind_buffer_index(Ipecker_graphic_buffer* pbuffer,UInt buffer_index)
{
	if (null == pbuffer || buffer_index >= pecker_vertex_buffer_gles2::MAX_VERTEXT_ATTRIBUTE_COUNT)
	{
		return P_INVALID_VALUE;
	}
	if (_M_vertex_buffer_count == pecker_vertex_buffer_gles2::MAX_VERTEXT_ATTRIBUTE_COUNT)
	{
		return P_OUT_OF_MEMORY;
	}
	HEnum buffer_type = pbuffer->get_buffer_type();
	HResult error_code = P_OK;
	switch(buffer_type)
	{
	case VERTEX_BUFFER_TYPE:
		{
			Ipecker_vertex_buffer* ptest_buffer = dynamic_cast< Ipecker_vertex_buffer* >(pbuffer);
			if (null == _M_vertex_buffer[buffer_index] && null != ptest_buffer)
			{
				_M_vertex_buffer[buffer_index] = ptest_buffer;
				++_M_vertex_buffer_count;
			}
			else if (null != ptest_buffer)
			{
				_M_vertex_buffer[buffer_index] = ptest_buffer;
			}
			else
			{
				error_code = P_INVALID_VALUE;
			}
		}

		break;
	case INDEX_BUFFER_TYPE:
		{
			Ipecker_index_buffer* ptest_buffer = dynamic_cast< Ipecker_index_buffer* >(pbuffer);
			if (null != ptest_buffer)
			{
				_M_index_buffer = ptest_buffer;
			}
			else
			{
				error_code = P_INVALID_VALUE;
			}
		}

		break;
	default:
		error_code = P_INVALID_VALUE;
		break;
	}

	return error_code;
}

PECKER_END
