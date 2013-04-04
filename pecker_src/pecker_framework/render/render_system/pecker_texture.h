/*
 * pecker_texture.h
 *
 *  Created on: 2013-3-14
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_TEXTURE_H_
#define  PECKER_TEXTURE_H_

#include "../pecker_render_object.h"

PECKER_BEGIN

enum TEXTURE_TYPE
{
	UNKOWN_TEXTURE_TYPE = 0,
	TEXTURE_2D_TYPE,
	TEXTURE_CUBE_TYPE,
	TEXTURE_3D_TYPE,
	//TEXTURE_VOLUME_TYPE,

	TEXTURE_TYPE_COUNT
};
struct pecker_texture_filter_info
{
	HEnum				_M_filter_name;
	INT_FLOAT_SHARE_MEM_VAL	_M_filter_param;
};

struct pecker_texture_layer_info
{
	HEnum	_M_target_type;
	HEnum	_M_internal_format;
	HEnum	_M_bit_format;
	HEnum	_M_data_type;
	UInt			_M_miplevel;
	HEnum	_M_usage;
	nSize		_M_border;
	nSize		_M_width;
	nSize		_M_height;
	nSize		_M_bit_row_size;
};

PeckerInterface Ipecker_texture : public Ipecker_frame_buffer_object//: public Ipecker_graphic_buffer
{
	virtual ~Ipecker_texture(){;}

	HEnum get_frame_buffer_object_type() const;

	virtual UInt get_mip_level() const = 0;

	virtual HResult set_defualt_texture_filters_info(const pecker_texture_filter_info* filters) = 0;


	virtual HResult allocate_texture_from_gpu_ram(const pecker_texture_layer_info& top_most_mipinfo) = 0;
	virtual HResult release_texture_from_gpu_ram() = 0;

	virtual HResult use_defualt_texture_filters() = 0;
	virtual HResult use_texture_filters(const pecker_texture_filter_info* filters,nSize filters_count) = 0;
	virtual HResult bind_texture_to_shader_sample(UInt sample_location,UInt texture_unit) = 0;
	virtual const pecker_texture_layer_info& get_texture_info(UInt miplevel = 0)=0;

	
	virtual HResult update_gpu_buffer(nSize data_size,const PVoid pdata,Bool is_compress = false) = 0;
	virtual HResult update_gpu_sub_buffer(nINDEX xoffset,nINDEX yoffset,nSize width,nSize height,  nSize data_size,const PVoid pdata,Bool is_compress = false) = 0;

	virtual HEnum get_texture_type() const = 0;

	virtual HResult set_active_miplevel(UInt miplevel) = 0;
	virtual UInt	get_active_miplevel() const= 0;

	virtual HResult set_render_type(HEnum attach_type) = 0;
	virtual HEnum get_render_type() const = 0;
};

PeckerInterface Ipecker_texture2d : public Ipecker_texture
{
	virtual ~Ipecker_texture2d(){;}
	HEnum get_texture_type() const;
};

enum TEXTURE_CUBE_MAP_TYPE
{
	 TEXTURE_CUBE_MAP_POSX = 0,
	 TEXTURE_CUBE_MAP_NEGX,

	 TEXTURE_CUBE_MAP_POSY,
	  TEXTURE_CUBE_MAP_NEGY,

	 TEXTURE_CUBE_MAP_POSZ,
	 TEXTURE_CUBE_MAP_NEGZ,

	 TEXTURE_CUBE_MAP_COUNT
};

PeckerInterface Ipecker_texture_cube : public Ipecker_texture
{
	virtual ~Ipecker_texture_cube(){;}
	virtual HResult set_active_face(HEnum target_type) = 0;
	virtual HEnum get_active_face() const= 0;
	virtual HResult allocate_texture_from_gpu_ram(const pecker_texture_layer_info* ptop_most_mipinfo,nSize info_count) = 0;
	HEnum get_texture_type() const;
};

PECKER_END

#endif //PECKER_TEXTURE_H_