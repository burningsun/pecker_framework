/*
 * pecker_texture_gl.cpp
 *
 *  Created on: 2013-3-20
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */


#include "pecker_texture_gl.h"
#include "../pecker_frame_buffer.h"
#include "../../../native/pecker_allocator.h"
#include <GLES2/gl2.h>
PECKER_BEGIN

typedef pecker_simple_allocator<Byte> texture_buffer_allocator;

pecker_texture_2d_gles2::pecker_texture_2d_gles2():
							_M_gpu_target(0),
								_M_mip_level_count(0),
								_M_defualt_texture_filter_count(0),
								_M_render_type(COLOR_BUFFER_TYPE),
								_M_active_miplevel(0)//,
								//_M_texture_buffer(null)
{

}

pecker_texture_2d_gles2::~pecker_texture_2d_gles2()
{
	release_texture_from_gpu_ram();
	_M_gpu_target = 0;
	_M_mip_level_count = 0;
	_M_defualt_texture_filter_count = 0;
}

HResult pecker_texture_2d_gles2::attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index /* = 0 */)//,HEnum face_type /* = 0 */,nSize zoffset /* = 0 */)
{
	if (null == pframe_buffer)
	{
		return P_INVALID_VALUE;
	}
	return pframe_buffer->attach_texture(this,attach_index);//,face_type,zoffset);
}

HResult pecker_texture_2d_gles2::bind()
{
	glBindTexture(GL_TEXTURE_2D,_M_gpu_target);
	return pecker_opengles_v2_object::get_last_error_code();
}

UInt pecker_texture_2d_gles2::get_mip_level() const
{
	return _M_mip_level_count;
}

HResult pecker_texture_2d_gles2::set_defualt_texture_filters_info(const pecker_texture_filter_info* filters,nSize filters_count)
{
	if (filters_count <= 0 || null == filters)
		return P_INVALID_VALUE;

	_M_defualt_texture_filter_count = filters_count;
	for (nINDEX i=0;i<filters_count;++i)
	{
		_M_defualt_texture_filter[i] = filters[i];
	}
	return P_OK;
}

HResult pecker_texture_2d_gles2::allocate_texture_from_gpu_ram(const pecker_texture_layer_info& top_most_mipinfo) 
{

	if (top_most_mipinfo._M_height < 1 || top_most_mipinfo._M_height > MAX_TEXTURE_SIZE || top_most_mipinfo._M_width < 1 || top_most_mipinfo._M_width > MAX_TEXTURE_SIZE)
	{
		return P_INVALID_VALUE;
	}

	if (0 == _M_gpu_target)
	{
		glGenTextures(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == result_)
		{
			UInt temp_value = top_most_mipinfo._M_height;
			UInt temp_miplevel = 0;
			UInt temp_max_miplevel = 0;
			_M_texture_info = top_most_mipinfo;
			_M_active_miplevel = 0;
			
			// 计算16位整数转换成2进制后1的个数
			temp_value = (temp_value&0x5555) + ((temp_value>>1)&0x5555);     
			temp_value = (temp_value&0x3333) + ((temp_value>>2)&0x3333);
			temp_value = (temp_value&0x0f0f) + ((temp_value>>4)&0x0f0f);     
			temp_value = (temp_value&0x00ff) + ((temp_value>>8)&0x00ff);     

			// 计算16位整数转换成2进制后第1个1的位置
			temp_value = top_most_mipinfo._M_height;
			temp_miplevel = 1;
			if ((temp_value >> 8) == 0) {temp_miplevel = temp_miplevel +8; temp_value = temp_value <<8;}
			if ((temp_value >> 12) == 0) {temp_miplevel = temp_miplevel + 4; temp_value = temp_value << 4;}
			if ((temp_value >> 14) == 0) {temp_miplevel = temp_miplevel + 2; temp_value = temp_value << 2;}
			temp_miplevel = 16 - (temp_miplevel - (temp_value >> 15));
			temp_max_miplevel = temp_miplevel;

			// 2的N次方换算成2进制，只存在1个1，对于不满足条件的进行修正
			if ( 1 < temp_value)
			{
				_M_texture_info._M_height = 1 << temp_miplevel;
			}
			
			temp_value = top_most_mipinfo._M_width;
			// 计算16位整数转换成2进制后1的个数
			temp_value = (temp_value&0x5555) + ((temp_value>>1)&0x5555);     
			temp_value = (temp_value&0x3333) + ((temp_value>>2)&0x3333);
			temp_value = (temp_value&0x0f0f) + ((temp_value>>4)&0x0f0f);     
			temp_value = (temp_value&0x00ff) + ((temp_value>>8)&0x00ff);     

			// 计算16位整数转换成2进制后第1个1的位置
			temp_value = top_most_mipinfo._M_width;
			temp_miplevel = 1;
			if ((temp_value >> 8) == 0) {temp_miplevel = temp_miplevel +8; temp_value = temp_value <<8;}
			if ((temp_value >> 12) == 0) {temp_miplevel = temp_miplevel + 4; temp_value = temp_value << 4;}
			if ((temp_value >> 14) == 0) {temp_miplevel = temp_miplevel + 2; temp_value = temp_value << 2;}
			temp_miplevel = 16 - (temp_miplevel - (temp_value >> 15));
			
			if (temp_miplevel >  temp_max_miplevel)
			{
				temp_max_miplevel = temp_miplevel;
			}
			
			// 2的N次方换算成2进制，只存在1个1，对于不满足条件的进行修正
			if ( 1 < temp_value)
			{
				_M_texture_info._M_width = 1 << temp_miplevel;
			}

			_M_mip_level_count = temp_max_miplevel;
			_M_mip_tmp_info = _M_texture_info;
			
		}
		return result_;
	}
	else
	{
		return P_UNIQUE_ERR;
	}
	
}

HResult pecker_texture_2d_gles2::release_texture_from_gpu_ram()
{
	if (0 != _M_gpu_target)
	{
		glDeleteTextures(1,&_M_gpu_target);
		return pecker_opengles_v2_object::get_last_error_code();
	}
	else
	{
		return P_OK;
	}
	
}

HResult pecker_texture_2d_gles2::use_defualt_texture_filters()
{
	return use_texture_filters(_M_defualt_texture_filter,_M_defualt_texture_filter_count);
}

HResult pecker_texture_2d_gles2::use_texture_filters(const pecker_texture_filter_info* filters,nSize filters_count)
{
	if (0 != _M_gpu_target)
	{
		glBindTexture(GL_TEXTURE_2D,_M_gpu_target);
		for (nINDEX i=0;i<_M_defualt_texture_filter_count;++i)
		{
			glTexParameteri(GL_TEXTURE_2D,_M_defualt_texture_filter[i]._M_filter_name,_M_defualt_texture_filter[i]._M_filter_param._M_uinteger);
		}
		return P_OK;
	}
	else
	{
		return P_FAIL;
	}

}

HResult pecker_texture_2d_gles2::bind_texture_to_shader_sample(UInt sample_location,UInt texture_unit)
{
	if (0 != _M_gpu_target)
	{
		if (texture_unit < MAX_TEXTURE_UNIT_COUNT)
		{
			glActiveTexture(GL_TEXTURE0 + texture_unit);
			glBindTexture(GL_TEXTURE_2D,_M_gpu_target);
			glUniform1i(sample_location,texture_unit);
			return pecker_texture_2d_gles2::get_last_error_code();
		}
		return P_INVALID_VALUE;
	}
	else
	{
		return P_FAIL;
	}

}

const pecker_texture_layer_info& pecker_texture_2d_gles2::get_texture_info(UInt miplevel)
{
		_M_mip_tmp_info._M_height = _M_texture_info._M_height >> miplevel;
		_M_mip_tmp_info._M_width = _M_texture_info._M_width >> miplevel;

	return _M_mip_tmp_info;
}

HResult pecker_texture_2d_gles2::update_gpu_buffer(/*UInt miplevel,*/nSize data_size,const PVoid pdata,Bool is_compress /*= false*/)
{
	if (0 != _M_gpu_target)
	{
		const pecker_texture_layer_info& tex_info =  get_texture_info(_M_active_miplevel);
		glBindTexture(GL_TEXTURE_2D,_M_gpu_target);
		if (false == is_compress)
		{
			glTexImage2D(GL_TEXTURE_2D,
				_M_active_miplevel,
				tex_info._M_internal_format,
				tex_info._M_width,
				tex_info._M_height,
				tex_info._M_border,
				tex_info._M_bit_format,
				tex_info._M_data_type,
				pdata);
		}
		else
		{
			glCompressedTexImage2D(GL_TEXTURE_2D,
				_M_active_miplevel,
				tex_info._M_internal_format,
				tex_info._M_width,
				tex_info._M_height,
				tex_info._M_border,
				data_size,
				pdata);
		}

		UInt result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	return P_FAIL;
}
HResult pecker_texture_2d_gles2::update_gpu_sub_buffer(/*UInt miplevel,*/nINDEX xoffset,nINDEX yoffset,nSize width,nSize height,  nSize data_size,const PVoid pdata,Bool is_compress/* = false*/)
{
	if (0 != _M_gpu_target)
	{
		glBindTexture(GL_TEXTURE_2D,_M_gpu_target);
		if (!is_compress)
		{
			glTexSubImage2D(GL_TEXTURE_2D,
				_M_active_miplevel,
				xoffset,
				yoffset,
				width,
				height,
				_M_texture_info._M_bit_format,
				_M_texture_info._M_data_type,
				pdata);
		}
		else
		{
			glCompressedTexSubImage2D(GL_TEXTURE_2D,
				_M_active_miplevel,
				xoffset,
				yoffset,
				width,
				height,
				_M_texture_info._M_bit_format,
				data_size,
				pdata);
		}

		UInt result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	return P_FAIL;
}

HResult pecker_texture_2d_gles2::set_render_type(HEnum attach_type)
{
	if (attach_type >= 0 && attach_type < STENCIL_BUFFER_TYPE)
	{
		_M_render_type = attach_type;
		return P_OK;
	}
	else
	{
		return P_INVALID_VALUE;
	}

}

HResult pecker_texture_2d_gles2::set_active_miplevel(UInt miplevel)
{
	if (miplevel < _M_mip_level_count)
	{
		_M_active_miplevel = miplevel;
		return P_OK;
	}
	return P_INVALID_VALUE;
}

UInt pecker_texture_2d_gles2::get_active_miplevel() const
{
	return _M_active_miplevel;
}

HEnum pecker_texture_2d_gles2::get_render_type() const
{
	return _M_render_type;
}

UInt pecker_texture_2d_gles2::get_object_location() const
{
	return _M_gpu_target;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

pecker_texture_cube_gles2::pecker_texture_cube_gles2():
	_M_gpu_target(0),
	_M_mip_level_count(0),
	_M_defualt_texture_filter_count(0),
	_M_active_face(TEXTURE_CUBE_MAP_POSX),
	_M_render_type(COLOR_BUFFER_TYPE),
	_M_active_miplevel(0)//,
	//_M_texture_buffer(null)
{

}

pecker_texture_cube_gles2::~pecker_texture_cube_gles2()
{
	release_texture_from_gpu_ram();
	_M_gpu_target = 0;
	_M_mip_level_count = 0;
	_M_defualt_texture_filter_count = 0;
	_M_active_face = TEXTURE_CUBE_MAP_POSX;
}

HResult pecker_texture_cube_gles2::attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index /* = 0 */)//,HEnum face_type /* = 0 */,nSize zoffset /* = 0 */)
{
	if (null == pframe_buffer)
	{
		return P_INVALID_VALUE;
	}
	return pframe_buffer->attach_texture(this,attach_index);//,face_type,zoffset);
}

HResult pecker_texture_cube_gles2::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP,_M_gpu_target);
	return pecker_opengles_v2_object::get_last_error_code();
}

UInt pecker_texture_cube_gles2::get_mip_level() const
{
	return _M_mip_level_count;
}

HResult pecker_texture_cube_gles2::set_defualt_texture_filters_info(const pecker_texture_filter_info* filters,nSize filters_count)
{
	if (filters_count <= 0 || null == filters)
		return P_INVALID_VALUE;

	_M_defualt_texture_filter_count = filters_count;
	for (nINDEX i=0;i<filters_count;++i)
	{
		_M_defualt_texture_filter[i] = filters[i];
	}
	return P_OK;
}

HResult pecker_texture_cube_gles2::allocate_texture_from_gpu_ram(const pecker_texture_layer_info& top_most_mipinfo) 
{

	if (top_most_mipinfo._M_height < 1 || top_most_mipinfo._M_height > pecker_texture_2d_gles2::MAX_TEXTURE_SIZE ||
		top_most_mipinfo._M_width < 1 || top_most_mipinfo._M_width > pecker_texture_2d_gles2::MAX_TEXTURE_SIZE)
	{
		return P_INVALID_VALUE;
	}

	if (0 == _M_gpu_target)
	{
		glGenTextures(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == result_)
		{
			UInt temp_value = top_most_mipinfo._M_height;
			UInt temp_miplevel = 0;
			UInt temp_max_miplevel = 0;
			_M_active_miplevel = 0;
			_M_texture_info[0] = top_most_mipinfo;
			_M_texture_info[1] = top_most_mipinfo;
			_M_texture_info[2] = top_most_mipinfo;
			_M_texture_info[3] = top_most_mipinfo;
			_M_texture_info[4] = top_most_mipinfo;
			_M_texture_info[5] = top_most_mipinfo;

			// 计算16位整数转换成2进制后1的个数
			temp_value = (temp_value&0x5555) + ((temp_value>>1)&0x5555);     
			temp_value = (temp_value&0x3333) + ((temp_value>>2)&0x3333);
			temp_value = (temp_value&0x0f0f) + ((temp_value>>4)&0x0f0f);     
			temp_value = (temp_value&0x00ff) + ((temp_value>>8)&0x00ff);     

			// 计算16位整数转换成2进制后第1个1的位置
			temp_value = top_most_mipinfo._M_height;
			temp_miplevel = 1;
			if ((temp_value >> 8) == 0) {temp_miplevel = temp_miplevel +8; temp_value = temp_value <<8;}
			if ((temp_value >> 12) == 0) {temp_miplevel = temp_miplevel + 4; temp_value = temp_value << 4;}
			if ((temp_value >> 14) == 0) {temp_miplevel = temp_miplevel + 2; temp_value = temp_value << 2;}
			temp_miplevel = 16 - (temp_miplevel - (temp_value >> 15));
			temp_max_miplevel = temp_miplevel;

			// 2的N次方换算成2进制，只存在1个1，对于不满足条件的进行修正
			if ( 1 < temp_value)
			{
				_M_texture_info[0]._M_height = 1 << temp_miplevel;
				_M_texture_info[1]._M_height = _M_texture_info[0]._M_height ;
				_M_texture_info[2]._M_height = _M_texture_info[0]._M_height ;
				_M_texture_info[3]._M_height = _M_texture_info[0]._M_height ;
				_M_texture_info[4]._M_height = _M_texture_info[0]._M_height ;
				_M_texture_info[5]._M_height = _M_texture_info[0]._M_height ;
			}

			temp_value = top_most_mipinfo._M_width;
			// 计算16位整数转换成2进制后1的个数
			temp_value = (temp_value&0x5555) + ((temp_value>>1)&0x5555);     
			temp_value = (temp_value&0x3333) + ((temp_value>>2)&0x3333);
			temp_value = (temp_value&0x0f0f) + ((temp_value>>4)&0x0f0f);     
			temp_value = (temp_value&0x00ff) + ((temp_value>>8)&0x00ff);     

			// 计算16位整数转换成2进制后第1个1的位置
			temp_value = top_most_mipinfo._M_width;
			temp_miplevel = 1;
			if ((temp_value >> 8) == 0) {temp_miplevel = temp_miplevel +8; temp_value = temp_value <<8;}
			if ((temp_value >> 12) == 0) {temp_miplevel = temp_miplevel + 4; temp_value = temp_value << 4;}
			if ((temp_value >> 14) == 0) {temp_miplevel = temp_miplevel + 2; temp_value = temp_value << 2;}
			temp_miplevel = 16 - (temp_miplevel - (temp_value >> 15));

			if (temp_miplevel >  temp_max_miplevel)
			{
				temp_max_miplevel = temp_miplevel;
			}

			// 2的N次方换算成2进制，只存在1个1，对于不满足条件的进行修正
			if ( 1 < temp_value)
			{
				_M_texture_info[0]._M_width = 1 << temp_miplevel;
				_M_texture_info[1]._M_width = _M_texture_info[0]._M_width;
				_M_texture_info[2]._M_width = _M_texture_info[0]._M_width;
				_M_texture_info[3]._M_width = _M_texture_info[0]._M_width;
				_M_texture_info[4]._M_width = _M_texture_info[0]._M_width;
				_M_texture_info[5]._M_width = _M_texture_info[0]._M_width;
			}

			_M_mip_level_count = temp_max_miplevel;
			_M_mip_tmp_info = _M_texture_info[0];

		}
		return result_;
	}
	else
	{
		return P_UNIQUE_ERR;
	}

}

HResult pecker_texture_cube_gles2::release_texture_from_gpu_ram()
{
	if (0 != _M_gpu_target)
	{
		glDeleteTextures(1,&_M_gpu_target);
		return pecker_opengles_v2_object::get_last_error_code();
	}
	else
	{
		return P_OK;
	}

}

HResult pecker_texture_cube_gles2::use_defualt_texture_filters()
{
	return use_texture_filters(_M_defualt_texture_filter,_M_defualt_texture_filter_count);
}

HResult pecker_texture_cube_gles2::use_texture_filters(const pecker_texture_filter_info* filters,nSize filters_count)
{
	if (0 != _M_gpu_target)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP,_M_gpu_target);
		for (nINDEX i=0;i<_M_defualt_texture_filter_count;++i)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP,_M_defualt_texture_filter[i]._M_filter_name,_M_defualt_texture_filter[i]._M_filter_param._M_uinteger);
		}
		return P_OK;
	}
	else
	{
		return P_FAIL;
	}
}

HResult pecker_texture_cube_gles2::bind_texture_to_shader_sample(UInt sample_location,UInt texture_unit)
{
	if (0 != _M_gpu_target)
	{
		if (texture_unit < pecker_texture_2d_gles2::MAX_TEXTURE_UNIT_COUNT)
		{
			glActiveTexture(GL_TEXTURE0 + texture_unit);
			glBindTexture(GL_TEXTURE_CUBE_MAP,_M_gpu_target);
			glUniform1i(sample_location,texture_unit);
			return pecker_texture_cube_gles2::get_last_error_code();
		}
		return P_INVALID_VALUE;
	}
	else
	{
		return P_FAIL;
	}

}

const pecker_texture_layer_info& pecker_texture_cube_gles2::get_texture_info(UInt miplevel)
{
	_M_mip_tmp_info._M_height = _M_texture_info[_M_active_face]._M_height >> miplevel;
	_M_mip_tmp_info._M_width = _M_texture_info[_M_active_face]._M_width >> miplevel;

	return _M_mip_tmp_info;
}

HResult pecker_texture_cube_gles2::update_gpu_buffer(/*UInt miplevel,*/nSize data_size,const PVoid pdata,Bool is_compress/* = false*/)
{
	//if (miplevel < _M_mip_level_count)
	if (0 != _M_gpu_target)
	{
		const pecker_texture_layer_info& tex_info =  get_texture_info(_M_active_miplevel);
		glBindTexture(GL_TEXTURE_CUBE_MAP,_M_gpu_target);

		if (is_compress)
		{
			glTexImage2D(_M_active_face+GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				_M_active_miplevel,
				tex_info._M_internal_format,
				tex_info._M_width,
				tex_info._M_height,
				tex_info._M_border,
				tex_info._M_bit_format,
				tex_info._M_data_type,
				pdata);
		}
		else
		{
			glCompressedTexImage2D(_M_active_face+GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				_M_active_miplevel,
				tex_info._M_internal_format,
				tex_info._M_width,
				tex_info._M_height,
				tex_info._M_border,
				data_size,
				pdata);
		}

		UInt result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	return P_FAIL;
}
HResult pecker_texture_cube_gles2::update_gpu_sub_buffer(/*UInt miplevel,*/nINDEX xoffset,nINDEX yoffset,nSize width,nSize height,  nSize data_size,const PVoid pdata,Bool is_compress/* = false*/)
{
	//if (miplevel < _M_mip_level_count)
	if (0 != _M_gpu_target)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP,_M_gpu_target);
		if (!is_compress)
		{
			glTexSubImage2D(_M_active_face+GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				_M_active_miplevel,
				xoffset,
				yoffset,
				width,
				height,
				_M_texture_info[_M_active_face]._M_bit_format,
				_M_texture_info[_M_active_face]._M_data_type,
				pdata);
		}
		else
		{
			glCompressedTexSubImage2D(_M_active_face+GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				_M_active_miplevel,
				xoffset,
				yoffset,
				width,
				height,
				_M_texture_info[_M_active_face]._M_bit_format,
				data_size,
				pdata);
		}

		UInt result_ = pecker_opengles_v2_object::get_last_error_code();
		return result_;
	}
	return P_FAIL;
}

HResult pecker_texture_cube_gles2::set_active_face(HEnum target_type)
{
	if (target_type < TEXTURE_CUBE_MAP_COUNT && target_type >= 0)
	{
		_M_active_face = target_type;
		return P_OK;
	}
	return P_INVALID_VALUE;
}
HEnum pecker_texture_cube_gles2::get_active_face() const
{
	return _M_active_face;
}

HResult pecker_texture_cube_gles2::allocate_texture_from_gpu_ram(const pecker_texture_layer_info* ptop_most_mipinfo,nSize info_count)
{
	if (null == ptop_most_mipinfo)
	{
		return P_INVALID_VALUE;
	}
	for (nINDEX i=0; i<info_count; ++i)
	{
		const pecker_texture_layer_info& top_most_mipinfo = ptop_most_mipinfo[i];
		if (top_most_mipinfo._M_height < 1 || top_most_mipinfo._M_height > pecker_texture_2d_gles2::MAX_TEXTURE_SIZE ||
			top_most_mipinfo._M_width < 1 || top_most_mipinfo._M_width > pecker_texture_2d_gles2::MAX_TEXTURE_SIZE)
		{
			return P_INVALID_VALUE;
		}
	}


	if (0 == _M_gpu_target)
	{
		glGenTextures(1,&_M_gpu_target);
		HResult result_ = pecker_opengles_v2_object::get_last_error_code();
		if (P_OK == result_)
		{
			_M_active_miplevel = 0;
			for (nINDEX i=0;i<info_count;++i)
			{
				const pecker_texture_layer_info& top_most_mipinfo = ptop_most_mipinfo[i];
				UInt temp_value = top_most_mipinfo._M_height;
				UInt temp_miplevel = 0;
				UInt temp_max_miplevel = 0;
				_M_texture_info[0] = top_most_mipinfo;
				_M_texture_info[1] = top_most_mipinfo;
				_M_texture_info[2] = top_most_mipinfo;
				_M_texture_info[3] = top_most_mipinfo;
				_M_texture_info[4] = top_most_mipinfo;
				_M_texture_info[5] = top_most_mipinfo;

				// 计算16位整数转换成2进制后1的个数
				temp_value = (temp_value&0x5555) + ((temp_value>>1)&0x5555);     
				temp_value = (temp_value&0x3333) + ((temp_value>>2)&0x3333);
				temp_value = (temp_value&0x0f0f) + ((temp_value>>4)&0x0f0f);     
				temp_value = (temp_value&0x00ff) + ((temp_value>>8)&0x00ff);     

				// 计算16位整数转换成2进制后第1个1的位置
				temp_value = top_most_mipinfo._M_height;
				temp_miplevel = 1;
				if ((temp_value >> 8) == 0) {temp_miplevel = temp_miplevel +8; temp_value = temp_value <<8;}
				if ((temp_value >> 12) == 0) {temp_miplevel = temp_miplevel + 4; temp_value = temp_value << 4;}
				if ((temp_value >> 14) == 0) {temp_miplevel = temp_miplevel + 2; temp_value = temp_value << 2;}
				temp_miplevel = 16 - (temp_miplevel - (temp_value >> 15));
				temp_max_miplevel = temp_miplevel;

				// 2的N次方换算成2进制，只存在1个1，对于不满足条件的进行修正
				if ( 1 < temp_value)
				{
					_M_texture_info[i]._M_height = 1 << temp_miplevel;
				}

				temp_value = top_most_mipinfo._M_width;
				// 计算16位整数转换成2进制后1的个数
				temp_value = (temp_value&0x5555) + ((temp_value>>1)&0x5555);     
				temp_value = (temp_value&0x3333) + ((temp_value>>2)&0x3333);
				temp_value = (temp_value&0x0f0f) + ((temp_value>>4)&0x0f0f);     
				temp_value = (temp_value&0x00ff) + ((temp_value>>8)&0x00ff);     

				// 计算16位整数转换成2进制后第1个1的位置
				temp_value = top_most_mipinfo._M_width;
				temp_miplevel = 1;
				if ((temp_value >> 8) == 0) {temp_miplevel = temp_miplevel +8; temp_value = temp_value <<8;}
				if ((temp_value >> 12) == 0) {temp_miplevel = temp_miplevel + 4; temp_value = temp_value << 4;}
				if ((temp_value >> 14) == 0) {temp_miplevel = temp_miplevel + 2; temp_value = temp_value << 2;}
				temp_miplevel = 16 - (temp_miplevel - (temp_value >> 15));

				if (temp_miplevel >  temp_max_miplevel)
				{
					temp_max_miplevel = temp_miplevel;
				}

				// 2的N次方换算成2进制，只存在1个1，对于不满足条件的进行修正
				if ( 1 < temp_value)
				{
					_M_texture_info[i]._M_width = 1 << temp_miplevel;
				}

				if (temp_max_miplevel > _M_mip_level_count)
				{
					_M_mip_level_count = temp_max_miplevel;
				}
				
			}
	
			_M_mip_tmp_info = _M_texture_info[0];
		}
		return result_;
	}
	else
	{
		return P_UNIQUE_ERR;
	}
}

HResult pecker_texture_cube_gles2::set_active_miplevel(UInt miplevel)
{
	if (miplevel < _M_mip_level_count)
	{
		_M_active_miplevel = miplevel;
		return P_OK;
	}
	return P_INVALID_VALUE;
}

UInt pecker_texture_cube_gles2::get_active_miplevel() const
{
	return _M_active_miplevel;
}

HResult pecker_texture_cube_gles2::set_render_type(HEnum attach_type)
{
	if (attach_type >= 0 && attach_type < STENCIL_BUFFER_TYPE)
	{
		_M_render_type = attach_type;
		return P_OK;
	}
	else
	{
		return P_INVALID_VALUE;
	}

}
HEnum pecker_texture_cube_gles2::get_render_type() const
{
	return _M_render_type;
}

UInt pecker_texture_cube_gles2::get_object_location() const
{
	return _M_gpu_target;
}

PECKER_END




