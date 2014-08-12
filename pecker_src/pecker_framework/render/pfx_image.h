/*
 * pfx_image.h
 *
 *  Created on: 2013-11-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_IMAGE_H_
#define		PFX_IMAGE_H_

#include "../include/config"
#include "pfx_color.h"
#include "pfx_render_allocator.h"
#include "../include/carray"
#include "../include/native"
#include "../include/cstring"

PECKER_BEGIN

typedef enum enumPFX_IMG_COMPRESSION_FORAMT
{
	PFX_IMG_UNCOMPRESS_FMT = 0,
	PFX_IMG_AUTO_DETECT_FMT,
	PFX_IMG_PVR_FMT,
	PFX_IMG_DDS_FMT,
	PFX_IMG_PNG_FMT,
	PFX_IMG_JPG_FMT,
	PFX_IMG_UNKOWN_FMT,
	PFX_PFX_IMG_CPS_FMT_COUNT
}PFX_IMG_COMPRESSION_FORAMT_t;

typedef struct image_bits
{
	byte_t*		 m_bits_ptr;
	usize__t	 m_bytes_count;
	
	usize__t     m_width;
	usize__t     m_height;

	enum_int_t   m_color_format;		//	 PFX_COLOR_FORMAT_TYPE_t
	usize__t     m_stride;	//
	usize__t	 m_stride_extra;//
	usize__t	 m_color_depth;

	enum_int_t	 m_compression_format;

	image_bits() :m_width(0), m_height(0),
		m_color_format(PFX_RGBA8_FMT),
		m_stride(color_format_size<PFX_RGBA8_FMT>::SIZE()),
		m_compression_format(PFX_IMG_UNCOMPRESS_FMT),
		m_stride_extra(0),
		m_color_depth(0)
	{
		
	}

	~image_bits()
	{
		;
	}

}image_bits_t;

typedef struct st_image_data
{
	typedef  carray< imgbuffer_allocator_t > img_buffer_t;

	image_bits   m_img;
	img_buffer_t m_buffer;
	uindex_t	 m_imgdata_offset;
	usize__t     m_pack_size;
	cstring_ascii_t m_str_compress_type;

	st_image_data() :m_pack_size(0), m_imgdata_offset(0)
	{
		;
	}
	~st_image_data()
	{
		;
	}

}image_data_t;












class PFX_RENDER_TEMPLATE_API cnative_image_base
{
protected:
	PFX_COLOR_FORMAT_TYPE_t			m_color_format;
	enum_int_t						m_compression_format;
	carray< imgbuffer_allocator_t > m_image_data;
	cs_t							m_locker;
	usize__t						m_image_width;
	usize__t						m_image_height;
	usize__t						m_color_size;
public:
	cnative_image_base();
	virtual ~cnative_image_base();

	result_t create_image(usize__t width, usize__t height, usize__t max_bytes_count = 0);


	virtual result_t load_image_form_memery(const byte_t* PARAM_IN bits_ptr,
		usize__t bits_count,
		usize__t width, usize__t height, PFX_COLOR_FORMAT_TYPE_t color_format, 
		boolean_t to_decompress = PFX_BOOL_FALSE);

	virtual result_t load_image_form_file(const char_t* PARAM_IN str_image_file_path,
		usize__t file_path_length,
		boolean_t to_decompress = PFX_BOOL_FALSE);

	virtual result_t copy_to(cnative_image_base* PARAM_INOUT __other_ptr);
	virtual result_t compress();
	virtual result_t dispose();
	result_t clean_image();

	result_t lock_bits(image_bits_t& bits,
		buffer_rect_t* PARAM_IN bits_rect_ptr);
	result_t unlock();
};

template < enum_int_t image_compression_format >
struct PFX_Image
{
	static PFX_INLINE result_t load_image_form_memery (byte_t* PARAM_IN bits_ptr,
		image_bits_t& PARAM_INOUT image_bits_, boolean_t to_decompress)
	{
		return PFX_STATUS_DENIED;
	}
	static PFX_INLINE result_t load_image_form_resource_table (const char_t* PARAM_IN str_image_name,
		usize__t image_name_length,image_bits_t& PARAM_INOUT image_bits_, 
		boolean_t to_decompress)
	{
		return PFX_STATUS_DENIED; 
	}
	static PFX_INLINE result_t load_image_form_file (const char_t* PARAM_IN str_image_file_path,
		usize__t file_path_length,image_bits_t& PARAM_INOUT image_bits_, 
		boolean_t to_decompress)
	{
		return PFX_STATUS_DENIED; 
	}
	static PFX_INLINE result_t release_image (image_bits_t& PARAM_INOUT image_bits_)
	{
		return PFX_STATUS_DENIED; 
	}
};

PECKER_END

#endif			//PFX_IMAGE_H_
