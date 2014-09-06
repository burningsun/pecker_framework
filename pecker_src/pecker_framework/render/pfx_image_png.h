/*
 * pfx_image_png.h
 *
 *  Created on: 2014-8-11
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_IMAGE_PNG_H_
#define		PFX_IMAGE_PNG_H_

#include "pfx_image.h"



PECKER_BEGIN

result_t PFX_RENDER_API load_png_image_from_memory(image_data_t& PARAM_INOUT __imgdata,
		const byte_t* PARAM_IN __src_data_ptr, usize__t __src_buffer_size, 
		bool bNormal=true, bool bRGB_color = true);

result_t PFX_RENDER_API load_png_image_from_STDIO(image_data_t& PARAM_INOUT __imgdata,
	pecker_file& hfile, bool bNormal = true, bool bRGB_color = true);

result_t PFX_RENDER_API load_png_image_from_file(image_data_t& PARAM_INOUT __imgdata,
	const char_t* PARAM_IN str_file_name, bool bNormal = true, bool bRGB_color = true);


class PFX_RENDER_API cPng_Image_reader : public cImage_reader_base
{

public:
	result_t  load_image(image_data_t& PARAM_INOUT __imgdata,
		image_data_t::img_buffer_t* PARAM_INOUT __cache_buffer = null);

	static PFX_INLINE result_t  load_image_from_memery(image_data_t& PARAM_INOUT __imgdata,
	const byte_t* PARAM_IN __src_data_ptr,
	usize__t __src_buffer_size,
	bool bNormal = true,
	bool bRGB_color = true)
	{
		return 	load_png_image_from_memory(__imgdata, __src_data_ptr, __src_buffer_size, bNormal, bRGB_color);
	}

	static PFX_INLINE result_t  load_image_from_STDIO(image_data_t& PARAM_INOUT __imgdata,
		pecker_file& hfile, bool bNormal = true,
		bool bRGB_color = true)
	{
		return load_png_image_from_STDIO(__imgdata, hfile, bNormal, bRGB_color);
	}

	static PFX_INLINE result_t  load_image_from_file(image_data_t& PARAM_INOUT __imgdata,
		const char_t* PARAM_IN str_file_name, bool bNormal = true,
		bool bRGB_color = true)
	{
		return load_png_image_from_file(__imgdata, str_file_name, bNormal, bRGB_color);
	}
};

PECKER_END

#endif			//PFX_IMAGE_PNG_H_
