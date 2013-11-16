/*
 * pfx_image.h
 *
 *  Created on: 2013-11-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_IMAGE_H_
#define		PFX_IMAGE_H_

#include "../../pfx_defines.h"

PECKER_BEGIN

typedef enum enumIMAGE_STORAGE_FORMAT
{
	PFX_IMG_FMT_RGBA = 0,
	PFX_IMG_FMT_RGB,
	PFX_IMG_FMT_LUMINANCE_ALPHA,
	PFX_IMG_FMT_LUMINANCE,
	PFX_IMG_FMT_ALPHA,

	PFX_IMAGE_STORAGE_FORMAT_COUNT
}PFX_IMAGE_STORAGE_FORMAT_t;

typedef enum enumIMAGE_PIXEL_FORMAT
{
	PFX_IMG_PXL_FMT_8888 = 0,
	PFX_IMG_PXL_FMT_4444,
	PFX_IMG_PXL_FMT_5551,
	PFX_IMG_PXL_FMT_5650,

	PFX_IMAGE_PIXEL_FORMAT_COUNT
}PFX_IMAGE_PIXEL_FORMAT_t;

typedef struct st_image_
{
	PFX_IMAGE_STORAGE_FORMAT_t m_strorage_format;
	PFX_IMAGE_PIXEL_FORMAT_t		m_pixel_format;
	pfx_usize_t											m_width;
	pfx_usize_t											m_height;
	pfx_usize_t											m_image_size;
	void*													m_pixel_data;												
}PFX_IMAGE_t;

typedef struct st_const_image_
{
	PFX_IMAGE_STORAGE_FORMAT_t m_strorage_format;
	PFX_IMAGE_PIXEL_FORMAT_t		m_pixel_format;
	pfx_usize_t											m_width;
	pfx_usize_t											m_height;
	pfx_usize_t											m_image_size;
	const void*										m_pixel_data;												
}PFX_CONST_IMAGE_t;

typedef struct st_compressed_image_
{
	pfx_flag_t			m_image_compress_type;	
	PFX_IMAGE_t	m_image_data;
}PFX_COMPRESSED_IMAGE_t;

typedef struct st_const_compressed_image_
{
	pfx_flag_t						m_image_compress_type;	
	PFX_CONST_IMAGE_t	m_image_data;
}PFX_CONST_COMPRESSED_IMAGE_t;

PECKER_END

#endif			//PFX_IMAGE_H_
