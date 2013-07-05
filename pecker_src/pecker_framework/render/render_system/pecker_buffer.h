/*
 * pecker_buffer.h
 *
 *  Created on: 2013-3-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_BUFFER_H_
#define  PECKER_BUFFER_H_

#include "../pecker_render_object.h"

PECKER_BEGIN

//const UInt MAX_GPU_ATTRIBUTE_COUNT 32

struct update_gpu_ram_info
{
	HEnum _M_usage_type;
	nINDEX _M_offset;
	nSize	  _M_update_size;
	//Bool	 _M_update_sub_buffer;

	update_gpu_ram_info(
											HEnum usage_type = 0,
											nINDEX offset = -1,
											nSize	  update_size = 0/*,
											Bool	  update_sub_buffer = 0*/):
																					_M_usage_type(usage_type),
																					_M_offset(offset),
																					_M_update_size(update_size)/*,
																					_M_update_sub_buffer(update_sub_buffer)*/
																					{
																						;
																					}
};

enum BUFFER_TYPE
{
	UNKOWN_BUFFER_TYPE = 0,
	VERTEX_BUFFER_TYPE,
	INDEX_BUFFER_TYPE,
	//TEXTURE_BUFFER_TYPE,
	//RENDER_BUFFER_TYPE,
	//FRAME_BUFFER_TYPE,

	BUFFER_TYPE_COUNT
};

enum VBO_USING_SETTING
{
	ALL_ENABLE_VBO = 0,
	ALL_DISABLE_VBO,
	DEFUALT_VBO,

	VBO_USING_SETTING_COUNT
};
// store vertex or index
PeckerInterface Ipecker_graphic_buffer
{
	virtual ~Ipecker_graphic_buffer(){;}
	// cpu ram
	virtual HResult allocate_buffer_from_cpu_ram(nSize number_of_bytes,const PVoid pdata_buffer= null) = 0;
	virtual HResult release_buffer_from_cpu_ram() = 0;

	virtual nSize get_buffer_size() const = 0;
	virtual const Byte* get_data() const = 0;
	virtual HResult lock_data(Byte* &pdata) = 0;
	virtual HResult unlock_data() = 0;
	
	//gpu ram
	virtual HResult allocate_buffer_from_gpu_ram() = 0;
	virtual HResult release_buffer_from_gpu_ram() = 0;

	virtual HResult update_gpu_buffer() = 0;
	virtual HResult update_gpu_buffer(const update_gpu_ram_info& pupdate_info) = 0;
	
	virtual HResult set_defualt_gpu_buffer_update_info(const update_gpu_ram_info& pupdate_info) = 0;
	//virtual HResult clear_defualt_setting() = 0;

	virtual HResult bind_gpu_buffer() = 0;

	
	 
	virtual HEnum get_buffer_type() const = 0;


};

enum ATTRIBUTE_DATA_TYPE
{
	DATA_TYPE_BYTE								= 0,              
	DATA_TYPE_UNSIGNED_BYTE,    
	DATA_TYPE_SHORT,                     
	DATA_TYPE_UNSIGNED_SHORT,
	DATA_TYPE_INT,                           
	DATA_TYPE_UNSIGNED_INT,       
	DATA_TYPE_FLOAT,                      
	DATA_TYPE_FIXED,
	ATTRIBUTE_DATA_TYPE_COUNT
};
struct vertex_attribute_info
{
	nINDEX _M_attribute_index;
	nSize _M_attribute_size;
	HFlag _M_stride;
	ATTRIBUTE_DATA_TYPE _M_attribute_data_type;
	UInt _M_offset;
	Bool _M_normalized;
	Bool _M_use_vbo;

	vertex_attribute_info(	
											nINDEX attribute_index = -1,
											nSize attribute_size = 0,
											HFlag stride = 0,
											ATTRIBUTE_DATA_TYPE attribute_data_type = DATA_TYPE_BYTE,
											UInt offset = 0,
											Bool normalized = false,
											Bool use_vbo = false):
											_M_attribute_index(attribute_index),
											_M_attribute_size(attribute_size),
											_M_stride(stride),
											_M_attribute_data_type(attribute_data_type),
											_M_offset(offset),
											_M_normalized(normalized),
											_M_use_vbo(use_vbo)
											{
												;
											}
};

PeckerInterface Ipecker_vertex_buffer : public Ipecker_graphic_buffer
{
	virtual ~Ipecker_vertex_buffer(){;}
	HEnum get_buffer_type() const;

	//virtual HResult set_multi_vertex_attribute_setting(Bool bEnable = false) = 0;
	//virtual HResult set_active_single_vertex_attribute_setting(UInt vex_info_index) = 0;
	
	virtual HResult add_defualt_vertex_attribute_setting(const vertex_attribute_info& vertex_attri_info) = 0;
	virtual HResult clear_vertex_attribute_setting() = 0;

	virtual vertex_attribute_info* get_vertex_attribute_reference(UInt vex_info_index) = 0;
	virtual nSize get_vertex_attribute_setting_count() const = 0;

	virtual HResult set_vbo_using_setting(VBO_USING_SETTING setting) = 0;
	virtual HResult use_vertex_attrible() = 0;
	virtual HResult finish_using_vertex_attrible() = 0;

	//virtual HResult set_gpu_buffer_update_info(const update_gpu_ram_info &mapping_info) = 0;
	//virtual HResult update_gpu_buffer(const update_gpu_ram_info &mapping_info ) = 0;
	//virtual HResult update_gpu_buffer(HEnum usage_type) = 0;
	//virtual HResult update_gpu_sub_buffer(nINDEX offset, nSize update_size,HEnum usage_type) = 0;
};

PeckerInterface Ipecker_index_buffer : public Ipecker_graphic_buffer
{
	virtual ~Ipecker_index_buffer(){;}
	HEnum get_buffer_type() const;

	//virtual HResult use_index_buffer() = 0;
	//virtual HResult set_gpu_buffer_update_info(const update_gpu_ram_info &mapping_info) = 0;
	//virtual HResult update_gpu_buffer(const update_gpu_ram_info &mapping_info ) = 0;
	//virtual HResult update_gpu_buffer(HEnum usage_type) = 0;
	//virtual HResult update_gpu_sub_buffer(nINDEX offset, nSize update_size,HEnum usage_type) = 0;
};

PeckerInterface Ipecker_vertex_index_buffer_collection
{
	virtual ~Ipecker_vertex_index_buffer_collection(){;}

	//virtual HResult allocate_buffers(nSize vertex_buffer_count,Bool has_index_buffer = false) = 0;
	//virtual HResult release_buffers() = 0;

	virtual Ipecker_vertex_buffer* get_vertex_buffer_reference(UInt buffer_index) = 0;
	virtual Ipecker_index_buffer* get_index_buffer_reference(UInt buffer_index = 0) = 0;

	virtual nSize get_vertex_buffer_count() const = 0;
	virtual nSize get_index_buffer_count() const = 0;
	
	virtual HResult bind_buffers_and_use_attribute() = 0;
	virtual HResult finish_using_buffer_attribute() = 0;

	virtual HResult attach_buffer(Ipecker_graphic_buffer* pbuffer) = 0;
	virtual HResult dettach_all_buffer() = 0;
	virtual HResult bind_buffer_index(Ipecker_graphic_buffer* pbuffer,UInt buffer_index) = 0;

};
PECKER_END

#endif //PECKER_BUFFER_H_