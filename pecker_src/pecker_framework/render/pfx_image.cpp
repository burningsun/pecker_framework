/*
 * pfx_image.h
 *
 *  Created on: 2014-7-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../include/config"
#include "pfx_image.h"

PECKER_BEGIN

cnative_image_base::cnative_image_base() :m_compression_format(PFX_IMG_UNCOMPRESS_FMT), 
m_color_format(PFX_COMPRESS_COLOR_FMT), 
m_color_size(color_format_size<PFX_COMPRESS_COLOR_FMT>::SIZE()), m_image_height(0), m_image_width(0)
{
	InitCriticalSection(&m_locker);
}
cnative_image_base::~cnative_image_base()
{
	dispose();
	DelCriticalSection(&m_locker);
}

result_t cnative_image_base::create_image(usize__t width, usize__t height, usize__t max_bytes_count //= 0
	)
{
	usize__t temp_size = width * height;

	if (max_bytes_count < temp_size)
	{
		max_bytes_count = temp_size * max_color_size();
	}
	critical_section_lock_t __lock;
	__lock.lock(m_locker);
	return m_image_data.resize(max_bytes_count);

}


result_t cnative_image_base::load_image_form_memery(const byte_t* PARAM_IN bits_ptr,
	usize__t bits_count,
	usize__t width, usize__t height, PFX_COLOR_FORMAT_TYPE_t color_format,
	boolean_t to_decompress //= PFX_BOOL_FALSE
	)
{
	if (bits_count > m_image_data.size())
	{
		return PFX_STATUS_OUT_OF_MEMORY;
	}
	m_image_height = height;
	m_image_width = width;
	m_color_format = color_format;
	m_color_size = max_color_size();
	usize__t image_size = height * width * m_color_size;
	critical_section_lock_t __lock;
	__lock.lock(m_locker);
	m_image_data.resize(image_size);
	return m_image_data.set_element_buffers_at(0, bits_ptr, bits_count);
}

result_t cnative_image_base::load_image_form_file(const char_t* PARAM_IN str_image_file_path,
	usize__t file_path_length,
	boolean_t to_decompress //= PFX_BOOL_FALSE
	)
{
	return PFX_STATUS_DENIED;
}

result_t cnative_image_base::copy_to(cnative_image_base* PARAM_INOUT __other_ptr)
{
	if (!__other_ptr)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}

	if (__other_ptr == this)
	{
		return PFX_STATUS_OK;
	}

	__other_ptr->clean_image();
	carray< imgbuffer_allocator_t >::cblock_t* block_ptr = m_image_data.get_block_ptr();
	critical_section_lock_t __lock;
	__lock.lock(m_locker);
	if (!block_ptr || !block_ptr->begin())
	{
		return PFX_STATUS_OK;
	}
	
	__other_ptr->create_image(m_image_width, m_image_height, m_image_data.size());
	return __other_ptr->load_image_form_memery(block_ptr->begin(), m_image_data.size(), 
		m_image_width, m_image_height, m_color_format);
}
result_t cnative_image_base::compress()
{
	return PFX_STATUS_OK;
}
result_t cnative_image_base::dispose()
{
	critical_section_lock_t __lock;
	__lock.lock(m_locker);
	m_image_width = 0;
	m_image_height = 0;
	return m_image_data.dispose();
}

result_t cnative_image_base::clean_image()
{
	critical_section_lock_t __lock;
	__lock.lock(m_locker);
	m_image_width = 0;
	m_image_height = 0;
	return m_image_data.clean();
}

result_t cnative_image_base::lock_bits(image_bits_t& bits,
	buffer_rect_t* PARAM_IN lock_rect_ptr)
{
	LockCriticalSection(&m_locker);
	bits.m_color_format = m_color_format;
	bits.m_colorvalue_size = m_color_size;
	bits.m_compression_format = m_compression_format;
	if (!lock_rect_ptr)
	{
		bits.m_bytes_count = m_image_data.size();
		bits.m_bits_ptr = m_image_data.get_block_ptr()->begin();
	}
	else if (0 == lock_rect_ptr->m_size)
	{
		bits.m_bits_ptr = null;
		bits.m_bytes_count = 0;
	}
	else
	{
		bits.m_bits_ptr = m_image_data.get_block_ptr()->pointer(lock_rect_ptr->m_offset);
		if (bits.m_bits_ptr)
		{
			usize__t remain_size;
			remain_size = m_image_data.size() - lock_rect_ptr->m_offset;
			bits.m_bytes_count = (remain_size > lock_rect_ptr->m_size) ?
				(lock_rect_ptr->m_size) : (remain_size);
		}
		else
		{
			bits.m_bytes_count = 0;
		}
	}
	return 0;
}
result_t cnative_image_base::unlock()
{
	UnlockCriticalSection(&m_locker);
	return PFX_STATUS_OK;
}

PECKER_END


