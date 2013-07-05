/*
 * pecker_buffer_gl.h
 *
 *  Created on: 2013-3-19
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_BUFFER_GL_H_
#define PECKER_BUFFER_GL_H_


#include "pecker_opengles_object.h"
#include "../pecker_buffer.h"

PECKER_BEGIN


union pekcer_cpu_ram_buffer
{
	PVoid		_M_buffer;
	Float*		_M_float_buffer;
	SInt*		_M_int_buffer;
	UShort* _M_ushort_buffer;
	Byte*		_M_bytes;
};

class pecker_vertex_buffer_gles2 : public Ipecker_vertex_buffer, public  virtual pecker_opengles_v2_object
{
public:
	static const UInt MAX_VERTEXT_ATTRIBUTE_COUNT = 8;
protected:
	//union vertex_cpu_ram_buffer
	//{
	//	PVoid	_M_buffer;
	//	Float* _M_float_buffer;
	//	SInt*	_M_int_buffer;
	//	Byte*	_M_bytes;
	//};
	typedef pekcer_cpu_ram_buffer vertex_cpu_ram_buffer;

private:
	vertex_cpu_ram_buffer _M_vertex_buffer;
	nSize	_M_bytes_count;
	UInt		_M_gpu_target;

	nSize _M_vertex_attribute_count;
	vertex_attribute_info   _M_vertex_attribute[MAX_VERTEXT_ATTRIBUTE_COUNT];
	//nINDEX _M_vertex_attribute_table[MAX_VERTEXT_ATTRIBUTE_COUNT];

	update_gpu_ram_info _M_defual_gpu_buffer_setting;

	HEnum _M_vbo_setting;
	Bool _M_first_update_buffer;
	
public:
	pecker_vertex_buffer_gles2();
	virtual ~pecker_vertex_buffer_gles2();

public:
	// cpu ram
	HResult allocate_buffer_from_cpu_ram(nSize number_of_bytes,const PVoid pdata_buffer= null);
	HResult release_buffer_from_cpu_ram();

	nSize get_buffer_size() const;
	const Byte* get_data() const;
	HResult lock_data(Byte* &pdata);
	HResult unlock_data();

	//gpu ram
	HResult allocate_buffer_from_gpu_ram();
	HResult release_buffer_from_gpu_ram();

	HResult set_defualt_gpu_buffer_update_info(const update_gpu_ram_info& pupdate_info);

	HResult update_gpu_buffer();
	HResult update_gpu_buffer(const update_gpu_ram_info& pupdate_info);

	HResult bind_gpu_buffer();
	HResult set_vbo_using_setting(VBO_USING_SETTING setting);
	//
	//HResult set_multi_vertex_attribute_setting(Bool bEnable = false);
	//HResult set_active_single_vertex_attribute_setting(UInt vex_info_index);

	HResult add_defualt_vertex_attribute_setting(const vertex_attribute_info& vertex_attri_info);
	HResult clear_vertex_attribute_setting();

	vertex_attribute_info* get_vertex_attribute_reference(UInt vex_info_index);
	nSize get_vertex_attribute_setting_count() const;

	HResult use_vertex_attrible();
	HResult finish_using_vertex_attrible();

	//HResult set_gpu_buffer_update_info(const update_gpu_ram_info &mapping_info);
	//HResult update_gpu_buffer(const update_gpu_ram_info &mapping_info );
public:
	virtual UInt get_object_location() const;
};

class pecker_index_buffer_gles2 : public Ipecker_index_buffer, public virtual pecker_opengles_v2_object
{
protected:
	//union index_cpu_ram_buffer
	//{
	//	PVoid	_M_buffer;
	//	Float* _M_float_buffer;
	//	SInt*	_M_int_buffer;
	//	UShort* _M_ushort_buffer;
	//	Byte*	_M_bytes;
	//};
	typedef pekcer_cpu_ram_buffer index_cpu_ram_buffer;
private:
	index_cpu_ram_buffer _M_index_buffer;
	nSize	_M_bytes_count;
	UInt		_M_gpu_target;
	update_gpu_ram_info _M_defual_gpu_buffer_setting;

	//HEnum _M_vbo_setting;
	Bool _M_first_update_buffer;

public:
	pecker_index_buffer_gles2();
	virtual ~pecker_index_buffer_gles2();

public:
	// cpu ram
	HResult allocate_buffer_from_cpu_ram(nSize number_of_bytes,const PVoid pdata_buffer= null);
	HResult release_buffer_from_cpu_ram();

	nSize get_buffer_size() const;
	const Byte* get_data() const;
	HResult lock_data(Byte* &pdata);
	HResult unlock_data();

	//gpu ram
	HResult allocate_buffer_from_gpu_ram();
	HResult release_buffer_from_gpu_ram();

	HResult set_defualt_gpu_buffer_update_info(const update_gpu_ram_info& pupdate_info);

	HResult update_gpu_buffer();
	HResult update_gpu_buffer(const update_gpu_ram_info& pupdate_info);

	HResult bind_gpu_buffer();

	//HResult set_vbo_using_setting(HEnum setting);

	//
	//HResult set_gpu_buffer_update_info(const update_gpu_ram_info &mapping_info);
	//HResult update_gpu_buffer(const update_gpu_ram_info &mapping_info );
public:
	virtual UInt get_object_location() const;

};

class pecker_vertex_index_buffer_collection_gles2 : public Ipecker_vertex_index_buffer_collection, public virtual  pecker_opengles_v2_object
{
private:
	Ipecker_vertex_buffer* _M_vertex_buffer[pecker_vertex_buffer_gles2::MAX_VERTEXT_ATTRIBUTE_COUNT];
	Ipecker_index_buffer* _M_index_buffer;
	nSize _M_vertex_buffer_count;
public:
	pecker_vertex_index_buffer_collection_gles2();
	virtual ~pecker_vertex_index_buffer_collection_gles2();

public:
	//HResult allocate_buffers(nSize vertex_buffer_count,Bool has_index_buffer = false);
	//HResult release_buffers();

	Ipecker_vertex_buffer* get_vertex_buffer_reference(UInt buffer_index) ;
	Ipecker_index_buffer* get_index_buffer_reference(UInt buffer_index = 0);

	nSize get_vertex_buffer_count() const;
	nSize get_index_buffer_count() const;

	HResult bind_buffers_and_use_attribute();
	HResult finish_using_buffer_attribute();

	HResult attach_buffer(Ipecker_graphic_buffer* pbuffer);
	HResult dettach_all_buffer();
	HResult bind_buffer_index(Ipecker_graphic_buffer* pbuffer,UInt buffer_index);

};

extern const HEnum gGL_Attribute_data_type_table[ATTRIBUTE_DATA_TYPE_COUNT];
PECKER_END

#endif // PECKER_BUFFER_GL_H_


