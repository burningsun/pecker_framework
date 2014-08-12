﻿/*
 * pfx_image_png.cpp
 *
 *  Created on: 2014-8-11
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_image_png.h"

#include "../../depends_lib/libpng-1.6.2/png.h"
#include "../../depends_lib/libpng-1.6.2/pngstruct.h"
#include "../../depends_lib/libpng-1.6.2/pnginfo.h"


#include "../native/pfx_log.h"
#include "../native/pecker_stream.h"

PECKER_BEGIN

#define PNG_LOG_ERR   PECKER_LOG_ERR
#define PNG_LOG_INFO  PECKER_LOG_INFO

typedef struct
{
	unsigned char* data;
	int size;
	int offset;
}ImageSource;

static void PngReaderCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	ImageSource* isource = (ImageSource*)png_get_io_ptr(png_ptr);

	if (isource->offset + length <= isource->size)
	{
		memcpy(data, isource->data + isource->offset, length);
		isource->offset += length;
	}
	else
	{
		png_error(png_ptr, "pngReaderCallback failed");
	}
}

#define BUFFER_INIT8 73
result_t load_png_image_from_memery(image_data_t& PARAM_INOUT __imgdata,
	const byte_t* PARAM_IN __src_data_ptr, usize__t __src_buffer_size,
	 bool bNormal )//= true);
{
	RETURN_INVALID_RESULT((null == __src_data_ptr || __src_buffer_size < 8), 
		PFX_STATUS_INVALID_PARAMS);

	if (0 != png_sig_cmp(__src_data_ptr, 0, 8))
	{
		cstring_ascii_t str_log_string;
		bytes_to_hexstring(__src_data_ptr, 8, str_log_string);
		PNG_LOG_ERR("NOT A PNG FILE (%s)", str_log_string.get_string());
		return PFX_STATUS_INVALID_VALUE;
	}

	png_structp png_ptr;
	png_infop info_ptr;
	png_infop end_info_ptr;
	png_uint_32 width, height;
	png_size_t rowBytes;
	png_byte ichannel;
	png_byte color_type;
	png_byte bit_depth;
	png_colorp palette;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		PNG_LOG_ERR("png_create_read_struct FAILED (png_ptr=%d)", 0);
		return PFX_STATUS_FAIL;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		PNG_LOG_ERR("png_create_info_struct FAILED (info_ptr=%d)", 0);
		return PFX_STATUS_FAIL;
	}
	end_info_ptr = png_create_info_struct(png_ptr);
	if (!end_info_ptr)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		PNG_LOG_ERR("png_create_info_struct FAILED (end_info_ptr=%d)", 0);
		return PFX_STATUS_FAIL;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);
		PNG_LOG_ERR("png_create_info_struct FAILED (info_ptr=%08X, end_info_ptr=%08X)", 
			(long_t)info_ptr, (long_t)end_info_ptr);
		return PFX_STATUS_FAIL;
	}

	ImageSource imgsource;
	imgsource.data = (unsigned char*)__src_data_ptr;
	imgsource.size = __src_buffer_size;
	imgsource.offset = 0;
	//define our own callback function for I/O instead of reading from a file
	png_set_read_fn(png_ptr, &imgsource, PngReaderCallback);

	png_read_info(png_ptr, info_ptr);
	width = info_ptr->width;
	height = info_ptr->height;
	color_type = info_ptr->color_type;
	bit_depth = info_ptr->bit_depth;
	rowBytes = info_ptr->rowbytes;
	palette = info_ptr->palette;
	ichannel = info_ptr->channels;
	int pixeldepth = info_ptr->pixel_depth;

	// Convert stuff to appropriate formats!
	if (PNG_COLOR_TYPE_PALETTE == color_type)
	{
		png_set_packing(png_ptr);
		png_set_palette_to_rgb(png_ptr); //Expand data to 24-bit RGB or 32-bit RGBA if alpha available.
	}
	if (PNG_COLOR_TYPE_GRAY == color_type && bit_depth < 8)
	{
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}
	if (PNG_COLOR_TYPE_GRAY_ALPHA == color_type)
	{
		png_set_gray_to_rgb(png_ptr);
	}
	if (16 == bit_depth)
	{
		png_set_strip_16(png_ptr);
	}

	//Expand paletted or RGB images with transparency to full alpha channels so the data will be available as RGBA quartets.
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(png_ptr);
	}

	//png_read_update_info(png_ptr, info_ptr);
	uindex_t pixel_bytes_stride = pixeldepth >> 3;
	if (0 != pixeldepth % 8)
	{
		++pixel_bytes_stride;
	}


	result_t status;
	usize__t img_size;
	img_size = width * height * pixel_bytes_stride;
	status = __imgdata.m_buffer.init(img_size);

	if (status)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);
		return PFX_STATUS_MEM_LOW;
	}


	byte_t* color_bytes_ptr = __imgdata.m_buffer.get_block_ptr()->begin();


	png_bytep * row_pointers = new png_bytep[height];
	usize__t row_stride = width * pixel_bytes_stride;
	uindex_t tmp_height;
	byte_t* tmp_color_bytes_ptr;
	

	
	if (bNormal)
	{
		tmp_color_bytes_ptr = color_bytes_ptr + img_size;
		tmp_height = 0;
		//unlike store the pixel data from top-left corner, store them from bottom-left corner for OGLES Texture drawing...
		while (tmp_color_bytes_ptr && tmp_height < height)
		{
			tmp_color_bytes_ptr -= row_stride;
			row_pointers[tmp_height] = tmp_color_bytes_ptr;
			++tmp_height;
		}
	}
	else
	{
		tmp_color_bytes_ptr = color_bytes_ptr + img_size;
		tmp_height = height;
		while (tmp_color_bytes_ptr && tmp_height)
		{
			tmp_color_bytes_ptr -= row_stride;
			--tmp_height;
			row_pointers[tmp_height] = tmp_color_bytes_ptr;			
		}
	}


	png_read_image(png_ptr, row_pointers);

	if (row_pointers)
	{
		delete[] row_pointers;
		row_pointers = null;
	}

	__imgdata.m_img.m_bits_ptr = color_bytes_ptr;
	__imgdata.m_img.m_bytes_count = img_size;
	__imgdata.m_img.m_stride = pixel_bytes_stride;
	__imgdata.m_img.m_stride_extra = 0;
	__imgdata.m_img.m_width = width;
	__imgdata.m_img.m_height = height;
	__imgdata.m_pack_size = 1;
	__imgdata.m_imgdata_offset = 0;
	__imgdata.m_img.m_compression_format = PFX_IMG_UNCOMPRESS_FMT;
	__imgdata.m_img.m_color_depth = pixeldepth;
	
	switch (pixel_bytes_stride)
	{
	case 2:
		__imgdata.m_img.m_color_format = PFX_RGB_565_FMT;
		break;
	case 3:
		__imgdata.m_img.m_color_format = PFX_RGB8_FMT;
		break;
	case 4:
		__imgdata.m_img.m_color_format = PFX_RGBA8_FMT;
		break;
	case 6:
		__imgdata.m_img.m_color_format = PFX_RGB16_FMT;
		break;
	case 8:
		__imgdata.m_img.m_color_format = PFX_RGBA16_FMT;
		break;
	default:
		__imgdata.m_img.m_color_format = PFX_UNKNOW_COLOR_FMT;
		break;
	} 


	//clean up after the read, and free any memory allocated
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);

	return status;
}

PECKER_END


