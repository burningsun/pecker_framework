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

PECKER_BEGIN

typedef enum enumPFX_IMG_COMPRESSION_FORAMT
{
	PFX_IMG_UNCOMPRESS_FMT = 0,
	PFX_IMG_PVR_FMT,
	PFX_IMG_DDS_FMT,
	PFX_IMG_PNG_FMT,
	PFX_IMG_JPG_FMT,
	PFX_IMG_UNKOWN_FMT,
	PFX_PFX_IMG_CPS_FMT_COUNT
}PFX_IMG_COMPRESSION_FORAMT_t;

typedef struct image_bits
{
	byte_t*										m_bits_ptr;
	usize__t										m_bytes_count;
	PFX_COLOR_FORMAT_TYPE_t		m_color_format;
	enum_int_t								m_compression_format;
}image_bits_t;

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
