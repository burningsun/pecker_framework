/*
 * pfx_image_png.h
 *
 *  Created on: 2014-8-11
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_IMAGE_PNG_H_
#define		PFX_IMAGE_PNG_H_

#include "pfx_image.h"

// 插，android 居然木有io.h这个文件
#if !defined(__APPLE__) && !defined(__ANDROID__)
#include <io.h>
#endif //#if !defined(__APPLE__) && !defined(__ANDROID__)
#ifdef __ANDROID__
#include <stdarg.h>
#endif //#ifdef __ANDROID__
#include <errno.h>
#include <stdio.h>

PECKER_BEGIN

#define PNG_FORMAT_NO_CHANGE 0x80000000 /* additional flag */
#define PNG_FORMAT_COUNT 64
#define PNG_FORMAT_MASK 0x3f

extern const char_t * PNG_format_names[PNG_FORMAT_COUNT];

result_t PFX_RENDER_API load_png_image_from_memery(image_data_t& PARAM_INOUT __imgdata,
		const byte_t* PARAM_IN __src_data_ptr, usize__t __src_buffer_size, bool bNormal=true);

//result_t PFX_RENDER_API load_png_image_from_STDIO(image_data_t& PARAM_INOUT __imgdata,
//	FILE* hfile, const RBG8_color* PARAM_IN background_color_ptr);
//
//result_t PFX_RENDER_API load_png_image_from_file(image_data_t& PARAM_INOUT __imgdata,
//	const char_t* PARAM_IN str_file_name, const RBG8_color* PARAM_IN background_color_ptr);

PECKER_END

#endif			//PFX_IMAGE_PNG_H_
