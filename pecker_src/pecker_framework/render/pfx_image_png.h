/*
 * pfx_image_png.h
 *
 *  Created on: 2014-8-11
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_IMAGE_PNG_H_
#define		PFX_IMAGE_PNG_H_

#include "pfx_image.h"
#include "../native/pfx_file_io.h"


PECKER_BEGIN

result_t PFX_RENDER_API load_png_image_from_memery(image_data_t& PARAM_INOUT __imgdata,
		const byte_t* PARAM_IN __src_data_ptr, usize__t __src_buffer_size, bool bNormal=true);

result_t PFX_RENDER_API load_png_image_from_STDIO(image_data_t& PARAM_INOUT __imgdata,
	pecker_file& hfile, bool bNormal = true);

result_t PFX_RENDER_API load_png_image_from_file(image_data_t& PARAM_INOUT __imgdata,
	const char_t* PARAM_IN str_file_name, bool bNormal = true);

PECKER_END

#endif			//PFX_IMAGE_PNG_H_
