/*
 * pecker_texture_gl.h
 *
 *  Created on: 2013-3-20
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_TEXTURE_GL_H_
#define PECKER_TEXTURE_GL_H_


#include "pecker_opengles_object.h"
#include "../pecker_texture.h"

PECKER_BEGIN

class pecker_texture_2d_gles2 : public Ipecker_texture2d,public virtual pecker_opengles_v2_object
{
public:
	static const UInt MAX_TEXTURE_UNIT_COUNT = 32;
	static const UInt MAX_TEXTURE_MIP_LEVEL = 15; // 纹理尺寸 2^15 * 2^15，(powervr sgx 540 2048*2048)
	static const UInt MAX_TEXTURE_SIZE = 32768;
	static const UInt MAX_DEFUALT_TEXTURE_FILTER_COUNT = 16;
private:
	UInt _M_gpu_target;
	UInt _M_mip_level_count;
	nSize _M_defualt_texture_filter_count;
	HEnum _M_render_type;
	UInt _M_active_miplevel;
	pecker_texture_layer_info _M_texture_info;
	pecker_texture_layer_info _M_mip_tmp_info;
	pecker_texture_filter_info _M_defualt_texture_filter[MAX_DEFUALT_TEXTURE_FILTER_COUNT];


public:
	pecker_texture_2d_gles2();
	virtual ~pecker_texture_2d_gles2();

public:
	HResult attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index = 0);//,HEnum face_type = 0,nSize zoffset = 0);
	HResult bind();

public:
	UInt get_mip_level() const;

	HResult set_defualt_texture_filters_info(const pecker_texture_filter_info* filters,nSize filters_count);

	HResult allocate_texture_from_gpu_ram(const pecker_texture_layer_info& top_most_mipinfo) ;
	HResult release_texture_from_gpu_ram();

	HResult use_defualt_texture_filters();
	HResult use_texture_filters(const pecker_texture_filter_info* filters,nSize filters_count);

	HResult bind_texture_to_shader_sample(UInt sample_location,UInt texture_unit);
	const pecker_texture_layer_info& get_texture_info(UInt miplevel = 0);

	HResult update_gpu_buffer(nSize data_size,const PVoid pdata,Bool is_compress = false);
	HResult update_gpu_sub_buffer(nINDEX xoffset,nINDEX yoffset,nSize width,nSize height,  nSize data_size,const PVoid pdata,Bool is_compress = false);

	HResult set_render_type(HEnum attach_type);
	HEnum get_render_type() const;

	HResult set_active_miplevel(UInt miplevel);
	UInt get_active_miplevel() const;
public:
	virtual UInt get_object_location() const;

};

class pecker_texture_cube_gles2 : public Ipecker_texture_cube,public virtual pecker_opengles_v2_object
{
private:
	UInt _M_gpu_target;
	UInt _M_mip_level_count;
	nSize _M_defualt_texture_filter_count;
	HEnum _M_render_type;
	UInt _M_active_miplevel;
	HEnum _M_active_face;
	
	pecker_texture_layer_info _M_texture_info[6];
	pecker_texture_layer_info _M_mip_tmp_info;
	pecker_texture_filter_info _M_defualt_texture_filter[pecker_texture_2d_gles2::MAX_DEFUALT_TEXTURE_FILTER_COUNT];

public:
	pecker_texture_cube_gles2();
	virtual ~pecker_texture_cube_gles2();

public:
	HResult attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index = 0);//,HEnum face_type = 0,nSize zoffset = 0);
	HResult bind();

public:

	HResult set_active_face(HEnum target_type);
	HEnum get_active_face() const;

	HResult allocate_texture_from_gpu_ram(const pecker_texture_layer_info* ptop_most_mipinfo,nSize info_count);

	UInt get_mip_level() const;

	HResult set_defualt_texture_filters_info(const pecker_texture_filter_info* filters,nSize filters_count);

	HResult allocate_texture_from_gpu_ram(const pecker_texture_layer_info& top_most_mipinfo) ;
	HResult release_texture_from_gpu_ram();

	HResult use_defualt_texture_filters();
	HResult use_texture_filters(const pecker_texture_filter_info* filters,nSize filters_count);

	HResult bind_texture_to_shader_sample(UInt sample_location,UInt texture_unit);
	const pecker_texture_layer_info& get_texture_info(UInt miplevel = 0);

	HResult update_gpu_buffer(/*UInt miplevel,*/nSize data_size,const PVoid pdata,Bool is_compress = false);
	HResult update_gpu_sub_buffer(/*UInt miplevel,*/nINDEX xoffset,nINDEX yoffset,nSize width,nSize height,  nSize data_size,const PVoid pdata,Bool is_compress = false);

	HResult set_active_miplevel(UInt miplevel);
	UInt get_active_miplevel() const;

	HResult set_render_type(HEnum attach_type);
	HEnum get_render_type() const;

public:
	virtual UInt get_object_location() const;
};


PECKER_END

#endif // PECKER_TEXTURE_GL_H_


