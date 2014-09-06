/*
 * pfx_image.h
 *
 *  Created on: 2014-7-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../include/config"
#include "pfx_image.h"

PECKER_BEGIN

cImage_reader_base::cImage_reader_base() :m_bNormal(true), m_loader_type(IMG_LOADER_UNKNOWN),
m_src_data_ptr(null), m_src_data_size(0), m_res_reader_ptr(null), m_aset_reader_ptr(null), m_color_format(PFX_RGBA_FMT)
{
	InitCriticalSection(&m_locker);

}
cImage_reader_base::~cImage_reader_base()
{
	if (m_res_reader_ptr)
	{
		m_res_reader_ptr->dispose_object();
		m_res_reader_ptr = null;
	}
	if (m_aset_reader_ptr)
	{
		m_aset_reader_ptr->dispose_object();
		m_aset_reader_ptr = null;
	}
	UnlockCriticalSection(&m_locker);
	DelCriticalSection(&m_locker);
}

void cImage_reader_base::set_normal(bool bNormal //= true
	)
{
	m_bNormal = bNormal;
}

result_t cImage_reader_base::select_load_form_memory(const byte_t* PARAM_IN __src_data_ptr,
	usize__t __src_buffer_size)
{
	if (__src_data_ptr && __src_buffer_size)
	{
		m_src_data_ptr = __src_data_ptr;
		m_src_data_size = __src_buffer_size;
		m_loader_type = IMG_FORM_MEMORY;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

}

result_t  cImage_reader_base::attach_asset_reader(sasset_reader_t* PARAM_INOUT __reader)
{
	RETURN_INVALID_RESULT(null == __reader, PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT(this->m_aset_reader_ptr &&
		__reader->native_ptr() == this->m_aset_reader_ptr->native_ptr(), PFX_STATUS_OK);
	sasset_reader_t* new_ptr = __reader->new_ref();
	if (new_ptr)
	{
		if (m_aset_reader_ptr)
		{
			m_aset_reader_ptr->dispose_object();
		}
		m_aset_reader_ptr = new_ptr;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_MEM_ERR;
	}
}

void cImage_reader_base::detach_asset_reader()
{
	if (m_aset_reader_ptr)
	{
		m_aset_reader_ptr->dispose_object();
		m_aset_reader_ptr = null;
	}
}

result_t cImage_reader_base::attach_resource_reader(sresource_reader_t* PARAM_INOUT __reader)
{
	RETURN_INVALID_RESULT(null == __reader, PFX_STATUS_INVALID_PARAMS);
	RETURN_RESULT(this->m_res_reader_ptr &&
		__reader->native_ptr() == this->m_res_reader_ptr->native_ptr(), PFX_STATUS_OK);
	sresource_reader_t* new_ptr = __reader->new_ref();
	if (new_ptr)
	{
		if (m_res_reader_ptr)
		{
			m_res_reader_ptr->dispose_object();
		}
		m_res_reader_ptr = new_ptr;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_MEM_ERR;
	}
}

void cImage_reader_base::detach_resource_reader()
{
	if (m_res_reader_ptr)
	{
		m_res_reader_ptr->dispose_object();
		m_res_reader_ptr = null;
	}
}



result_t  cImage_reader_base::select_load_form_asset_reader(const char_t* PARAM_IN str_file_name)
{
	if (str_file_name)
	{
		usize__t file_name_size = strlen(str_file_name);
		if (!file_name_size)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		result_t status = m_asset_file_name.init_string(str_file_name, file_name_size + 1);
		if (PFX_STATUS_OK == status)
		{
			status = m_asset_file_name.resize_string(file_name_size);
		}
		if (PFX_STATUS_OK == status)
		{
			m_loader_type = IMG_FORM_ASSET_READER;
		}
		return status;
	}
	else
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
}

result_t cImage_reader_base::select_load_form_resource_reader(const char_t* PARAM_IN str_file_name)
{
	if (str_file_name)
	{
		usize__t file_name_size = strlen(str_file_name);
		if (!file_name_size)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		result_t status = m_resource_file_name.init_string(str_file_name, file_name_size + 1);
		if (PFX_STATUS_OK == status)
		{
			status = m_resource_file_name.resize_string(file_name_size);
		}
		if (PFX_STATUS_OK == status)
		{
			m_loader_type = IMG_FORM_RESOURCE_READER;
		}
		return status;
	}
	else
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
}


result_t  cImage_reader_base::load_image(image_data_t& PARAM_INOUT __imgdata,
image_data_t::img_buffer_t* PARAM_INOUT __cache_buffer //= null
)
{
	return PFX_STATUS_DENIED;
}





#define CIMAGE_PACK_SIZE (8)


result_t cImage::begin_modify_bits(image_bits_t& bits,
	buffer_rect_t* PARAM_IN lock_rect_ptr)
{
	bits.m_color_format = m_image.m_img.m_color_format;
	bits.m_stride = m_image.m_img.m_stride;
	bits.m_compression_format = m_image.m_img.m_compression_format;

	if (!lock_rect_ptr)
	{
		bits.m_bytes_count = m_image.m_img.m_bytes_count;
		bits.m_bits_ptr = m_image.m_img.m_bits_ptr;
	}
	else if (0 == lock_rect_ptr->m_size)
	{
		bits.m_bits_ptr = null;
		bits.m_bytes_count = 0;
	}
	else
	{
		bits.m_bits_ptr = m_image.m_buffer.get_block_ptr()->pointer(lock_rect_ptr->m_offset + 
			m_image.m_imgdata_offset);

		if (bits.m_bits_ptr)
		{
			usize__t remain_size;
			remain_size = m_image.m_img.m_bytes_count - lock_rect_ptr->m_offset;
			bits.m_bytes_count = (remain_size > lock_rect_ptr->m_size) ?
				(lock_rect_ptr->m_size) : (remain_size);
		}
		else
		{
			bits.m_bytes_count = 0;
		}
	}
	return PFX_STATUS_OK;
}

result_t cImage::end_modify_bits()
{
	return PFX_STATUS_OK;
}

result_t cImage::create(
	usize__t   width,
	usize__t   height,
	enum_int_t color_format,		//	 PFX_COLOR_FORMAT_TYPE_t
	usize__t   stride,
	usize__t   color_depth,
	enum_int_t compression_format,
	usize__t   image_buffer_size //= 0
	)
{
	RETURN_INVALID_RESULT((stride << 3) < color_depth, 
		PFX_STATUS_INVALID_PARAMS);

	usize__t temp_img_size;
	temp_img_size = width * height * stride;
	RETURN_INVALID_RESULT((!temp_img_size),
		PFX_STATUS_INVALID_PARAMS);

	
	if (image_buffer_size < (temp_img_size + CIMAGE_PACK_SIZE))
	{
		image_buffer_size = temp_img_size + CIMAGE_PACK_SIZE;
	}

	result_t status;
	status = m_image.m_buffer.init(image_buffer_size);

	RETURN_INVALID_RESULT(PFX_STATUS_OK != status, status);

	lpointer_t buffer_loc = (lpointer_t)m_image.m_buffer.get_block_buffer();
	lpointer_t offset = buffer_loc % CIMAGE_PACK_SIZE;
	if (offset)
	{
		offset = CIMAGE_PACK_SIZE - offset;
	}
	buffer_loc += offset;
	m_image.m_img.m_bits_ptr = (byte_t*)buffer_loc;
	m_image.m_img.m_bytes_count = offset;
	m_image.m_pack_size = CIMAGE_PACK_SIZE;
	m_image.m_imgdata_offset = offset;
	m_image.m_img.m_color_format = color_format;
	m_image.m_img.m_color_depth = color_depth;
	m_image.m_img.m_compression_format = compression_format;
	m_image.m_img.m_stride = stride;
	m_image.m_img.m_stride_extra = 0;
	return PFX_STATUS_OK;

}


result_t cImage::copy_to(cImage& PARAM_OUT __img)
{
	if (&__img == this)
	{
		return PFX_STATUS_OK;
	}
	else
	{
		result_t status;
		status = __img.m_image.m_buffer.init(m_image.m_img.m_bytes_count + CIMAGE_PACK_SIZE);
		RETURN_INVALID_RESULT(PFX_STATUS_OK != status, status);

		lpointer_t buffer_loc = (lpointer_t)__img.m_image.m_buffer.get_block_buffer();
		lpointer_t offset = buffer_loc % CIMAGE_PACK_SIZE;
		if (offset)
		{
			offset = CIMAGE_PACK_SIZE - offset;
		}
		buffer_loc += offset;

		__img.m_image.m_img.m_bits_ptr = (byte_t*)buffer_loc;
		__img.m_image.m_img.m_bytes_count = offset;
		__img.m_image.m_pack_size = CIMAGE_PACK_SIZE;
		__img.m_image.m_imgdata_offset = offset;

		


		__img.m_image.m_img.m_color_format       = m_image.m_img.m_color_format;
		__img.m_image.m_img.m_color_depth        = m_image.m_img.m_color_depth;
		__img.m_image.m_img.m_compression_format = m_image.m_img.m_compression_format;
		__img.m_image.m_img.m_stride = m_image.m_img.m_stride;
		__img.m_image.m_img.m_stride_extra = m_image.m_img.m_stride_extra;
		__img.m_image.m_img.m_width = m_image.m_img.m_width;
		__img.m_image.m_img.m_height = m_image.m_img.m_height;
		__img.m_image.m_str_compress_type.init_string(m_image.m_str_compress_type);


		image_bits_t bits;
		__img.begin_modify_bits(bits);
		memcpy(bits.m_bits_ptr, m_image.m_img.m_bits_ptr, bits.m_bytes_count);
		__img.end_modify_bits();

		return PFX_STATUS_OK;
	}
}

PECKER_END


