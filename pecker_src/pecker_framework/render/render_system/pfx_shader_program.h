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
#include "pfx_vertext_index_buffer.h"
#include "pfx_rendertevent.h"

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

PFX_Interface Ipfx_shader_render_params
{
	Ipfx_shader_render_params ():m_render_event(null),m_event_obejct(null),m_render_program(null){;}
	virtual ~Ipfx_shader_render_params(){clear_all_param();}
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
	Ipfx_render_event* m_render_event;
	Ipfx_shader_program* m_render_program;
	pfx_unknown_event_object_t m_event_obejct;
};


//typedef enum 
PFX_Interface Ipfx_shader_program
{
	virtual ~Ipfx_shader_program(){;}

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

#endif			//PFX_SHADER_PROGRAM_H_
