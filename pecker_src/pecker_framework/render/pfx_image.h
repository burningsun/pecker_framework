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
#include "../include/cstring_pfx.h"
#include "../native/pfx_resource_reader.h"
#include "../data/pfx_reference.h"

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

typedef struct PFX_RENDER_API image_bits
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

typedef struct PFX_RENDER_API st_image_data
{
	typedef  carray< imgbuffer_allocator_t > img_buffer_t;

	image_bits   m_img;
	img_buffer_t m_buffer;
	uindex_t	 m_imgdata_offset;
	usize__t     m_pack_size;
	cstring_ascii_t m_str_compress_type;

	result_t dispose()
	{
		m_img.m_bits_ptr = null;
		m_img.m_bytes_count = 0;
		m_img.m_height = 0;
		m_img.m_width = 0;
		return m_buffer.dispose();
	}
	st_image_data() :m_pack_size(0), m_imgdata_offset(0)
	{
		;
	}
	~st_image_data()
	{
		;
	}

}image_data_t;

typedef enum enumIMG_LOAD_TYPE
{
   IMG_LOADER_UNKNOWN = 0,
   IMG_FORM_MEMORY,
   IMG_FORM_ASSET_READER,
   IMG_FORM_RESOURCE_READER,
   IMG_LOAD_TYPE_COUNT
}IMG_LOAD_TYPE_t;

PFX_Interface Image_reader
{
	virtual  ~Image_reader(){ ; }

	virtual void  set_normal(bool bNormal = true) = 0;

	virtual result_t  select_load_form_memory(const byte_t* PARAM_IN __src_data_ptr,
		usize__t __src_buffer_size) = 0;

	virtual result_t  attach_asset_reader(sasset_reader_t& PARAM_INOUT __reader) = 0;
	virtual void  detach_asset_reader() = 0;

	virtual result_t  attach_resource_reader(sresource_reader_t& PARAM_INOUT __reader) = 0;
	virtual void detach_resource_reader() = 0;

	virtual result_t  select_load_form_asset_reader(const char_t* PARAM_IN str_file_name) = 0;

	virtual result_t  select_load_form_resource_reader(const char_t* PARAM_IN str_file_name) = 0;

	virtual result_t  load_image(image_data_t& PARAM_INOUT __imgdata,
		image_data_t::img_buffer_t* PARAM_INOUT __cache_buffer = null) = 0;

};

PFX_Interface Image_adapter
{
	virtual  ~Image_adapter(){ ; }

	virtual result_t convert(const image_data_t& PARAM_IN __img_src,
		image_data_t& PARAM_OUT __img_des,
		usize__t pack_size = 0,
		image_data_t::img_buffer_t* PARAM_INOUT __cache_buffer = null) = 0;

	virtual result_t set_convert_param(const image_bits_t* PARAM_IN __img_des_param = 0) = 0;
};

class PFX_RENDER_API cImage_reader_base : public Image_reader
{
protected:
	IMG_LOAD_TYPE_t m_loader_type;
	bool            m_bNormal;

	const byte_t*   m_src_data_ptr;
	usize__t        m_src_data_size;

	cstring_ascii_t m_asset_file_name;
	cstring_ascii_t m_resource_file_name;

	sresource_reader_t m_res_reader;
	sasset_reader_t    m_aset_reader;

	cs_t m_locker;
public:
	cImage_reader_base();
	virtual ~cImage_reader_base();

	virtual void  set_normal(bool bNormal = true);

	virtual result_t  select_load_form_memory(const byte_t* PARAM_IN __src_data_ptr,
		usize__t __src_buffer_size);

	virtual result_t  attach_asset_reader(sasset_reader_t& PARAM_INOUT __reader);
	virtual void  detach_asset_reader();

	virtual result_t  attach_resource_reader(sresource_reader_t& PARAM_INOUT __reader);
	virtual void detach_resource_reader();

	virtual result_t  select_load_form_asset_reader(const char_t* PARAM_IN str_file_name);

	virtual result_t  select_load_form_resource_reader(const char_t* PARAM_IN str_file_name);

	virtual result_t  load_image(image_data_t& PARAM_INOUT __imgdata,
		image_data_t::img_buffer_t* PARAM_INOUT __cache_buffer = null);
};

class PFX_RENDER_API cImage
{
private:
	image_data_t m_image;
	critical_section_lock_ins_t m_locker;
public:
	
	PFX_INLINE const image_data_t& get_image_direct() const
	{
		return m_image;
	}
	PFX_INLINE result_t load_image(Image_reader* PARAM_IN loader_ptr)
	{
		if (loader_ptr)
		{
			return loader_ptr->load_image(m_image);
		}
		else
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
	}
	PFX_INLINE result_t lock_image()
	{
		return m_locker.lock();
	}
	PFX_INLINE result_t unlock_image()
	{
		return m_locker.unlock();
	}

	result_t begin_modify_bits(image_bits_t& bits,
		buffer_rect_t* PARAM_IN lock_rect_ptr = null);

	result_t end_modify_bits();

	result_t copy_to(cImage& PARAM_OUT __img);

	result_t create(
		usize__t   width,
		usize__t   height,
		enum_int_t color_format,		//	 PFX_COLOR_FORMAT_TYPE_t
		usize__t   stride,
		usize__t   color_depth,
		enum_int_t compression_format,
		usize__t   image_buffer_size = 0);

	PFX_INLINE result_t dispose()
	{
		return m_image.dispose();
	}
};


typedef simple_reference_object< cImage > sImage_t;






PECKER_END

#endif			//PFX_IMAGE_H_
