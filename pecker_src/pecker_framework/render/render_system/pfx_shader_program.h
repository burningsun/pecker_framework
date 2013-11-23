/*
 * pfx_shader_program.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SHADER_PROGRAM_H_
#define		PFX_SHADER_PROGRAM_H_

#include "../../pfx_defines.h"
#include "../../data/pfx_matrix4.h"
#include "../../data/pfx_string.h"
#include "pfx_gram_array_params.h"
#include "pfx_rendertevent.h"
#include "../pfx_render_type.h"

PECKER_BEGIN
//typedef void* pfx_unknown_shader_param_object_t;
//PFX_Interface Ipfx_shader_params_menager
//{
//	virtual ~Ipfx_shader_params_menager(){;}
//	virtual pfx_result_t dispose_a_frame (pfx_index_t frame_number) = 0;
//	virtual pfx_result_t dispose_all_frame() = 0;
//
//	virtual pfx_unknown_shader_param_object_t* get_frame_params (pfx_index_t frame_number) = 0;
//	virtual pfx_result_t bind_shader_params (pfx_result_t frame_number,pfx_unknown_shader_param_object_t shader_params) = 0;
//};

// shader 渲染参数
// 主要用于渲染流水线的调用，和逻辑渲染与实际渲染分离用
PFX_Interface Ipfx_shader_render_params
{
	Ipfx_shader_render_params ():m_render_event(null),m_event_obejct(null),m_render_program(null){;}
	virtual ~Ipfx_shader_render_params(){clear_all_param();}

	// 串行实际渲染操作
	virtual pfx_result_t lock() = 0;
	virtual pfx_result_t unlock() = 0;

public:
	PFX_INLINE pfx_result_t bind_render_params (Ipfx_shader_program* PARAM_INOUT use_render_program_,
		Ipfx_render_event* PARAM_INOUT event_,
		pfx_unknown_event_object_t  PARAM_IN event_obejct_);

	PFX_INLINE void clear_all_param ();
	PFX_INLINE Ipfx_render_event* get_render_event() ;
	PFX_INLINE pfx_result_t bind_render_event (Ipfx_render_event* PARAM_INOUT event_);
	PFX_INLINE void clear_render_event ();
	PFX_INLINE pfx_unknown_event_object_t get_reference_event_object () const;
	PFX_INLINE pfx_result_t bind_event_object (pfx_unknown_event_object_t  PARAM_IN event_obejct_);
	PFX_INLINE pfx_result_t bind_render_program (Ipfx_shader_program* PARAM_INOUT use_render_program_);
	PFX_INLINE void clear_render_program ();
protected:
	// 渲染事件，主要作用是处理实际渲染事件
	Ipfx_render_event* m_render_event;
	// shader处理程序，主要作用是使用某个shader处理程序作为该次渲染事件的主要shader处理程序
	Ipfx_shader_program* m_render_program;
	// 事件对象，主要作用是绑定该次渲染的参数，如MVP矩阵、镜头等，自由度高，
	// 该参数作用主要用户逻辑渲染与实际渲染分离用
	pfx_unknown_event_object_t m_event_obejct;
};


typedef enum enumSHADER_PARAM_TYPE
{
	PFXSPT_UNKNOWN_SHADER_PARAM_TYPE = 0,
	
	PFXSPT_FLOAT1,
	PFXSPT_FLOAT2,
	PFXSPT_FLOAT3,
	PFXSPT_FLOAT4,
	PFXSPT_INT1,
	PFXSPT_INT2,
	PFXSPT_INT3,
	PFXSPT_INT4,

	PFXSPT_MATRIX_2X2,
	PFXSPT_MATRIX_2X3,
	PFXSPT_MATRIX_2X4,
	PFXSPT_MATRIX_3X2,
	PFXSPT_MATRIX_3X3,
	PFXSPT_MATRIX_3X4,
	PFXSPT_MATRIX_4X2,
	PFXSPT_MATRIX_4X3,
	PFXSPT_MATRIX_4X4,

	PFXSPT_SAMPLER1D,
	PFXSPT_SAMPLER2D,
	PFXSPT_SAMPLER3D,
	PFXSPT_SAMPLERCUBE,
	PFXSPT_SAMPLER1DSHADOW,
	PFXSPT_SAMPLER2DSHADOW,
	PFXSPT_SAMPLER2DARRAY,

	PFXSPT_SHADER_PARAM_TYPE_COUNT
}PFX_SHADER_PARAM_TYPE_t;

typedef void* pfx_unknown_shader_param_object_t;

typedef enum enumSHADER_TYPE
{
	PFXST_VERTEXT_SHADER = 0,
	PFXST_PIXEL_SHADER,
	PFXST_SHADER_TYPE_COUNT
}PFX_SHADER_TYPE_t;

typedef enum enumPrimitiveMode
{
	PFX_PRI_POINTS = 0,
	PFX_PRI_LINES,
	PFX_PRI_LINE_STRIP,
	PFX_PRI_LINE_LOOP,
	PFX_PRI_TRIANGLES,
	PFX_PRI_TRIANGLE_STRIP,
	PFX_PRI_TRIANGLE_FAN,

	PFX_PRIMITIVE_MODE_COUNT
}PFX_PRIMITIVE_MODE_t;


// shader 处理器
PFX_Interface Ipfx_shader
{
	virtual ~Ipfx_shader() {;}

	virtual pfx_long_t create_shader (const pfx_string_t* PARAM_IN str_shader_codes,
		const char* str_func_enterpoint = "main",
		const char* str_detials = null) = 0;

	virtual pfx_result_t delete_shader () = 0;

	virtual pfx_long_t get_shader_location () = 0;

	virtual PFX_SHADER_TYPE_t get_type () const = 0;
};

PFX_Interface Ipfx_shader_program
{
	virtual ~Ipfx_shader_program(){;}

	// 配置当前绑定的shader处理器的参数
	// 顶点参数
	virtual pfx_long_t get_vertex_attribute_location (//PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		pfx_result_t & PARAM_OUT result_) = 0;

	virtual pfx_result_t set_const_vertex_attribute (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_) = 0;

	virtual  pfx_result_t set_vertex_pointer (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name,
		const PFX_CONST_GRAM_ARRAY_PARAMS_t& PARAM_IN gram_buffer_) = 0;

	virtual pfx_result_t set_const_vertex_attribute (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t attriute_name_location,
		pfx_unknown_shader_param_object_t object_,pfx_usize_t object_size_) = 0;

	virtual  pfx_result_t set_vertex_pointer (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t attriute_name_location,
		const PFX_CONST_GRAM_ARRAY_PARAMS_t& PARAM_IN gram_buffer_) = 0;

	virtual pfx_result_t enable_vertex_array (pfx_long_t tagVertex) = 0;
	virtual pfx_result_t disable_vertex_array (pfx_long_t tagVertex) = 0;

	virtual pfx_result_t draw_vertex_array (PFX_PRIMITIVE_MODE_t mode_,
		pfx_index_t fist_vertex_index,
		pfx_usize_t primitive_count) = 0;

	virtual pfx_result_t draw_vertex_element_array (PFX_PRIMITIVE_MODE_t mode_,
		const PFX_CONST_GRAM_ELEMENT_INDICES_PARAMS_t& indices) = 0;

	// UNIFORM 绘图常量参数
	virtual pfx_long_t get_uniform_location (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN uniform_name,
		pfx_result_t & PARAM_OUT result_) = 0;

	virtual pfx_result_t set_uniform (PFX_SHADER_PARAM_TYPE_t type_,
		const pfx_string_t* PARAM_IN attriute_name, 
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_) = 0;

	virtual pfx_result_t set_uniform (PFX_SHADER_PARAM_TYPE_t type_,
		pfx_long_t uniform_name_location,
		pfx_unknown_shader_param_object_t object_,
		pfx_usize_t object_size_) = 0;

	// shader 处理程序
	virtual pfx_result_t create_program (pfx_handle_t device_) = 0;
	virtual pfx_long_t link_program () = 0;
	virtual pfx_result_t delete_program () = 0;

	virtual pfx_result_t attach_shader (Ipfx_shader* PARAM_INOUT shader) = 0;
	
	
	//virtual pfx_result_t use_program () = 0;
	virtual pfx_result_t begin_program () = 0;
	virtual pfx_result_t end_program (pfx_boolean_t flush = pfx_true) = 0;

	

	//virtual pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, pfx_sint_t X) = 0;
	//virtual pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector2i_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector3i_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector4i_t& PARAM_IN vec) = 0;

	//virtual pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, pfx_float_t X) = 0;
	//virtual pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector2f_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector3f_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector4f_t& PARAM_IN vec) = 0;

	//virtual pfx_result_t set_vertex_attribute (pfx_long_t attriute_name_location, pfx_sint_t X) = 0;
	//virtual pfx_result_t set_vertex_attribute (pfx_long_t attriute_name_location, const pfx_vector2i_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_vertex_attribute (pfx_long_t attriute_name_location, const pfx_vector3i_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_vertex_attribute (pfx_long_t attriute_name_location, const pfx_vector4i_t& PARAM_IN vec) = 0;

	//virtual pfx_result_t set_vertex_attribute (pfx_long_t attriute_name_location, pfx_float_t X) = 0;
	//virtual pfx_result_t set_vertex_attribute (pfx_long_t attriute_name_location, const pfx_vector2f_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_vertex_attribute (pfx_long_t attriute_name_location, const pfx_vector3f_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_vertex_attribute (pfx_long_t attriute_name_location, const pfx_vector4f_t& PARAM_IN vec) = 0;

	//virtual pfx_long_t get_vertex_attribute_1i (const pfx_string_t* PARAM_IN attriute_name, pfx_sint_t& PARAM_OUT X) = 0;
	//virtual pfx_long_t get_vertex_attribute_2i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_vertex_attribute_3i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_vertex_attribute_4i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;

	//virtual pfx_long_t get_vertex_attribute_1f (const pfx_string_t* PARAM_IN attriute_name, pfx_float_t& PARAM_OUT X) = 0;
	//virtual pfx_long_t get_vertex_attribute_2f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_vertex_attribute_3f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_vertex_attribute_4f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;

	//virtual pfx_result_t set_gpu_ram_buffer (const pfx_string_t* PARAM_IN attriute_name, const GRAM_ARRAY_BUFFER_t& PARAM_IN gram_buffer_) = 0; 
	//virtual GRAM_ARRAY_BUFFER_t* get_gpu_ram_buffer (const pfx_string_t* PARAM_IN attriute_name) = 0;

	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, pfx_sint_t X) = 0;
	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector2i_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector3i_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector4i_t& PARAM_IN vec) = 0;

	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, pfx_float_t X) = 0;
	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector2f_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector3f_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector4f_t& PARAM_IN vec) = 0;

	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_marix2_t& PARAM_IN mat) = 0;
	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_marix3_t& PARAM_IN mat) = 0;
	//virtual pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_marix4_t& PARAM_IN mat) = 0;

	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, pfx_sint_t X) = 0;
	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_vector2i_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_vector3i_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_vector4i_t& PARAM_IN vec) = 0;

	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, pfx_float_t X) = 0;
	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_vector2f_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_vector3f_t& PARAM_IN vec) = 0;
	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_vector4f_t& PARAM_IN vec) = 0;

	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_marix2_t& PARAM_IN mat) = 0;
	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_marix3_t& PARAM_IN mat) = 0;
	//virtual pfx_result_t set_uniform (pfx_long_t attriute_name_location, const pfx_marix4_t& PARAM_IN mat) = 0;

	//virtual pfx_long_t	get_uniform_1i (const pfx_string_t* PARAM_IN attriute_name, pfx_sint_t& PARAM_OUT X) = 0;
	//virtual pfx_long_t get_uniform_2i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_uniform_3i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_uniform_4i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;

	//virtual pfx_long_t get_uniform_1f (const pfx_string_t* PARAM_IN attriute_name, pfx_float_t& PARAM_OUT X) = 0;
	//virtual pfx_long_t get_uniform_2f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_uniform_3f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_uniform_4f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;

	//virtual pfx_long_t get_uniform_mat2f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_uniform_mat3f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
	//virtual pfx_long_t get_uniform_mat4f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_) = 0;
};

//////////////////////////////////////////////////////////////////////////

PFX_INLINE pfx_result_t Ipfx_shader_render_params::bind_render_params (Ipfx_shader_program* PARAM_INOUT use_render_program_,
	Ipfx_render_event* PARAM_INOUT event_,
	pfx_unknown_event_object_t  PARAM_IN event_obejct_)
{
	RETURN_INVALID_RESULT ((null == event_)||(null == event_obejct_)||(null == use_render_program_),PFX_STATUS_INVALID_PARAMS);
	lock();
	m_render_event = event_;
	m_event_obejct = event_obejct_;
	m_render_program = use_render_program_;
	unlock();
	return PFX_STATUS_OK;
}

PFX_INLINE void Ipfx_shader_render_params::clear_all_param ()
{
	lock();
	m_render_event = null;
	m_event_obejct = null;
	m_render_program = null;
	unlock();
}


PFX_INLINE Ipfx_render_event* Ipfx_shader_render_params::get_render_event() 
{
	return m_render_event;
}
PFX_INLINE pfx_result_t Ipfx_shader_render_params::bind_render_event (Ipfx_render_event* PARAM_INOUT event_)
{
	RETURN_INVALID_RESULT (null == event_,PFX_STATUS_INVALID_PARAMS);
	lock();
	m_render_event = event_;
	unlock();
	return PFX_STATUS_OK;
}
PFX_INLINE void Ipfx_shader_render_params::clear_render_event ()
{
	lock();
	m_render_event = null;
	unlock();
}

PFX_INLINE pfx_unknown_event_object_t Ipfx_shader_render_params::get_reference_event_object () const
{
	return m_event_obejct;
}

PFX_INLINE pfx_result_t Ipfx_shader_render_params::bind_event_object (pfx_unknown_event_object_t  PARAM_IN event_obejct_)
{
	RETURN_INVALID_RESULT (null == event_obejct_,PFX_STATUS_INVALID_PARAMS);
	lock();
	m_event_obejct = event_obejct_;
	unlock();
	return PFX_STATUS_OK;
}

PFX_INLINE pfx_result_t Ipfx_shader_render_params::bind_render_program (Ipfx_shader_program* PARAM_INOUT use_render_program_) 
{
	RETURN_INVALID_RESULT (null == use_render_program_,PFX_STATUS_INVALID_PARAMS);
	lock();
	m_render_program = use_render_program_;
	unlock();
	return PFX_STATUS_OK;
}

PFX_INLINE void Ipfx_shader_render_params::clear_render_program ()
{
	lock();
	m_render_program = null;
	unlock();
}

PECKER_END

#endif			//PFX_SHADER_PROGRAM_H_
