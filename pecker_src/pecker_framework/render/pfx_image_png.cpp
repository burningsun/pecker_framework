/*
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

#define PNG_DECODE_PACK (8)

typedef struct
{
	unsigned char* data;
	int size;
	int offset;
}ImageSource;

static void PngReaderCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	ImageSource* isource = (ImageSource*)png_get_io_ptr(png_ptr);

	if (isource->offset + (nsize__t)length <= isource->size)
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
result_t load_png_image_from_memory(image_data_t& PARAM_INOUT __imgdata,
	const byte_t* PARAM_IN __src_data_ptr, usize__t __src_buffer_size,
	 bool bNormal, //= true
	 bool bRGB_color// = true
	 )
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

	if (!bRGB_color)
	{
		png_set_bgr(png_ptr);
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
	status = __imgdata.m_buffer.init(img_size + PNG_DECODE_PACK);

	if (status)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);
		return PFX_STATUS_MEM_LOW;
	}

	lpointer_t buffer_loc = (lpointer_t)__imgdata.m_buffer.get_block_buffer();
	lpointer_t offset = buffer_loc % PNG_DECODE_PACK;
	if (offset)
	{
		offset = PNG_DECODE_PACK - offset;
	}
	buffer_loc += offset;
	

	byte_t* color_bytes_ptr;

	color_bytes_ptr = (byte_t*)buffer_loc;


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
	__imgdata.m_pack_size = PNG_DECODE_PACK;
	__imgdata.m_imgdata_offset = offset;
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


result_t  load_png_image_from_STDIO(image_data_t& PARAM_INOUT __imgdata,
	pecker_file& hfile, 
	bool bNormal, //= true
	bool bRGB_color// = true
	)
{
	RETURN_INVALID_RESULT(!hfile.get_handle(), PFX_STATUS_INVALID_PARAMS);

	png_byte png_header[8];
	usize__t read_header_size = sizeof(png_header);
	hfile.read_to_memery(png_header, read_header_size);

	if (0 != png_sig_cmp(png_header, 0, 8) || read_header_size != sizeof(png_header))
	{
		cstring_ascii_t str_log_string;
		bytes_to_hexstring(png_header, 8, str_log_string);
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

	//I/O initialisation methods
	png_init_io(png_ptr, (png_FILE_p)hfile.get_handle()->m_hfile);
	png_set_sig_bytes(png_ptr, 8); //Required!!!

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

	if (!bRGB_color)
	{
		png_set_bgr(png_ptr);
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
	status = __imgdata.m_buffer.init(img_size + PNG_DECODE_PACK);

	if (status)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);
		return PFX_STATUS_MEM_LOW;
	}

	lpointer_t buffer_loc = (lpointer_t)__imgdata.m_buffer.get_block_buffer();
	lpointer_t offset = buffer_loc % PNG_DECODE_PACK;
	if (offset)
	{
		offset = PNG_DECODE_PACK - offset;
	}
	buffer_loc += offset;


	byte_t* color_bytes_ptr;

	color_bytes_ptr = (byte_t*)buffer_loc;


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
	__imgdata.m_pack_size = PNG_DECODE_PACK;
	__imgdata.m_imgdata_offset = offset;
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


result_t PFX_RENDER_API load_png_image_from_file(image_data_t& PARAM_INOUT __imgdata,
	const char_t* PARAM_IN str_file_name, 
	bool bNormal, //= true
	bool bRGB_color// = true
	)
{
	RETURN_INVALID_RESULT(!str_file_name, PFX_STATUS_INVALID_PARAMS);
	
	pecker_file hfile;
	result_t status = PFX_STATUS_OK;

	status = hfile.is_file_exists(str_file_name);
	RETURN_INVALID_RESULT((PFX_STATUS_OK > status), status);
		  
	status = hfile.open(str_file_name,  PFO_OPEN_READ | PFO_OPEN_BINARY);
	RETURN_INVALID_RESULT((PFX_STATUS_OK > status), status);

	usize__t file_size = hfile.get_file_size();

	status = load_png_image_from_STDIO(__imgdata, hfile, bNormal,bRGB_color);

	hfile.close();

	return status;
	
}

result_t cPng_Image_reader::load_image(image_data_t& PARAM_INOUT __imgdata,
	image_data_t::img_buffer_t* PARAM_INOUT __cache_buffer //= null
	)
{
	bool bRGA_color = true;
	if (PFX_BGR_FMT == cImage_reader_base::get_color_format() ||
		PFX_BGRA_FMT == cImage_reader_base::get_color_format())
	{
		bRGA_color = false;
	}
	result_t status;
	switch (m_loader_type)
	{
	case IMG_FORM_MEMORY:
		status = load_png_image_from_memory(__imgdata, m_src_data_ptr, 
			m_src_data_size, m_bNormal, bRGA_color);
		m_src_data_ptr = null;
		m_src_data_size = 0;
		m_loader_type = IMG_LOADER_UNKNOWN;
		break;
	case IMG_FORM_ASSET_READER:
		{
		  if (null == m_aset_reader_ptr)
		  {
			  status = PFX_STATUS_UNINIT;
			  break;
		  }
		  casset_reader_t* reader_ptr = m_aset_reader_ptr->native_ptr();
		  if (!reader_ptr)
		  {
			  status = PFX_STATUS_UNINIT;
			  break;
		  }
		  status = reader_ptr->open_resource(m_asset_file_name.get_string());
		  if (status)
		  {
			  break;
		  }

#if (OS_CONFIG == OS_ANDROID)
		  if (__cache_buffer)
		  {
			  usize__t read_size;
			  read_size = reader_ptr->get_size();
			  status = __cache_buffer->resize(read_size);
			  if (status)
			  {
				  reader_ptr->close();
				  break;
			  }
			  status = reader_ptr->read_to_memery(__cache_buffer->get_block_buffer(), read_size);
			  if (status)
			  {
				  reader_ptr->close();
				  break;
			  }
			  status = load_png_image_from_memory(__imgdata, __cache_buffer->get_block_buffer(), 
				  read_size, bRGA_color);
		  }
		  else
		  {
			  usize__t read_size;
			  image_data_t::img_buffer_t _cache_buffer;
			  read_size = reader_ptr->get_size();
			  status = _cache_buffer.init(read_size);
			  if (status)
			  {
				  reader_ptr->close();
				  break;
			  }
			  status = reader_ptr->read_to_memery(_cache_buffer.get_block_buffer(), read_size);
			  if (status)
			  {
				  reader_ptr->close();
				  break;
			  }
			  status = load_png_image_from_memory(__imgdata, _cache_buffer.get_block_buffer(), 
				  read_size, bRGA_color);
		  }
#else	// #if (OS_CONFIG == OS_ANDROID)

#if (OS_CONFIG == OS_WINDOWS)
		  status = load_png_image_from_STDIO(__imgdata, reader_ptr->get_file_handle(),
			  m_bNormal, bRGA_color);
#else	// #if (OS_CONFIG == OS_WINDOWS)
		  status = load_png_image_from_STDIO(__imgdata, reader_ptr->get_file_handle(), 
			  m_bNormal, bRGA_color);
#endif	// #if (OS_CONFIG == OS_WINDOWS)
#endif // #if (OS_CONFIG == OS_ANDROID)

		  reader_ptr->close();
		}

		break;
	case  IMG_FORM_RESOURCE_READER:
	   {
			if (null == m_res_reader_ptr)
		    {
		      status = PFX_STATUS_UNINIT;
		      break;
		    }
			cresource_reader_t* reader_ptr = m_res_reader_ptr->native_ptr();
			if (!reader_ptr)
			{
				status = PFX_STATUS_UNINIT;
				break;
			}
			status = reader_ptr->open_resource(m_resource_file_name.get_string());
			if (status)
			{
				break;
			}
			status = load_png_image_from_STDIO(__imgdata, reader_ptr->get_file_handle(), m_bNormal, 
				bRGA_color);
			reader_ptr->close();
	   }
		break;
	default:
		status = PFX_STATUS_UNINIT;
		break;
	}
	return status;
}

PECKER_END


