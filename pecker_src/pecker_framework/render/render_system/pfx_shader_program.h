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


PFX_Interface Ipfx_shader_program_params
{
	Ipfx_shader_program_params ():m_render_event(null),m_event_obejct(null){;}
	virtual ~Ipfx_shader_program_params(){;}

	inline Ipfx_render_event* get_render_event() 
	{
		return m_render_event;
	}
	inline pfx_result_t bind_render_event (Ipfx_render_event* PARAM_INOUT event_)
	{
		RETURN_INVALID_RESULT (null == event_,PFX_STATUS_INVALID_PARAMS);
		m_render_event = event_;
		return PFX_STATUS_OK;
	}
	inline void clear_render_event ()
	{
		m_render_event = null;
	}

	inline pfx_unknown_event_object_t get_reference_event_object () const
	{
		return m_event_obejct;
	}

	inline pfx_result_t bind_event_object (pfx_unknown_event_object_t  PARAM_IN event_obejct_)
	{
		RETURN_INVALID_RESULT (null == event_obejct_,PFX_STATUS_INVALID_PARAMS);
		m_event_obejct = event_obejct_;
		return PFX_STATUS_OK;
	}

	//pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, pfx_sint_t X);
	//pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector2i_t& PARAM_IN vec);
	//pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector3i_t& PARAM_IN vec);
	//pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector4i_t& PARAM_IN vec);

	//pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, pfx_float_t X);
	//pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector2f_t& PARAM_IN vec);
	//pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector3f_t& PARAM_IN vec);
	//pfx_result_t set_vertex_attribute (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector4f_t& PARAM_IN vec);

	//pfx_result_t get_vertex_attribute_1i (const pfx_string_t* PARAM_IN attriute_name, pfx_sint_t& PARAM_OUT X);
	//pfx_vector2i_t* get_vertex_attribute_2i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_vector3i_t* get_vertex_attribute_3i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_vector4i_t* get_vertex_attribute_4i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);

	//pfx_result_t get_vertex_attribute_1f (const pfx_string_t* PARAM_IN attriute_name, pfx_float_t& PARAM_OUT X);
	//pfx_vector2f_t* get_vertex_attribute_2f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_vector3f_t* get_vertex_attribute_3f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_vector4f_t* get_vertex_attribute_4f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);

	//pfx_result_t set_gpu_ram_buffer (const pfx_string_t* PARAM_IN attriute_name, const GRAM_ARRAY_BUFFER_t& PARAM_IN gram_buffer_); // 浅拷贝!
	//GRAM_ARRAY_BUFFER_t* get_gpu_ram_buffer (const pfx_string_t* PARAM_IN attriute_name);


	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, pfx_sint_t X);
	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector2i_t& PARAM_IN vec);
	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector3i_t& PARAM_IN vec);
	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector4i_t& PARAM_IN vec);

	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, pfx_float_t X);
	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector2f_t& PARAM_IN vec);
	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector3f_t& PARAM_IN vec);
	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_vector4f_t& PARAM_IN vec);

	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_marix2_t& PARAM_IN mat);
	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_marix3_t& PARAM_IN mat);
	//pfx_result_t set_uniform (const pfx_string_t* PARAM_IN attriute_name, const pfx_marix4_t& PARAM_IN mat);


	//pfx_result_t		get_uniform_1i (const pfx_string_t* PARAM_IN attriute_name, pfx_sint_t& PARAM_OUT X);
	//pfx_vector2i_t* get_uniform_2i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_vector3i_t* get_uniform_3i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_vector4i_t* get_uniform_4i (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);

	//pfx_result_t		get_uniform_1f (const pfx_string_t* PARAM_IN attriute_name, pfx_float_t& PARAM_OUT X);
	//pfx_vector2f_t* get_uniform_2f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_vector3f_t* get_uniform_3f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_vector4f_t* get_uniform_4f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);

	//pfx_marix2_t* get_uniform_mat2f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_marix3_t* get_uniform_mat3f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);
	//pfx_marix4_t* get_uniform_mat4f (const pfx_string_t* PARAM_IN attriute_name,pfx_result_t & PARAM_OUT result_);

	//pfx_result_t set_uniform_array (const pfx_string_t* PARAM_IN attriute_name,pfx_usize_t item_float_count,pfx_usize_t item_count,
	//	const pfx_float_t* PARAM_IN array_); // 浅拷贝!
	//pfx_result_t set_uniform_array (const pfx_string_t* PARAM_IN attriute_name,pfx_usize_t item_int_count,pfx_usize_t item_count,
	//	const pfx_sint_t* PARAM_IN array_); // 浅拷贝!

	//pfx_result_t get_uniform_array (const pfx_string_t* PARAM_IN attriute_name,pfx_usize_t item_float_count,pfx_usize_t &item_count,
	//	const pfx_float_t*& PARAM_OUT array_); 
	//pfx_result_t get_uniform_array (const pfx_string_t* PARAM_IN attriute_name,pfx_usize_t item_int_count,pfx_usize_t item_count,
	//	const pfx_sint_t*& PARAM_OUT array_); 

	//virtual pfx_result_t set_uniform (pfx_index_t index_,)

protected:
	Ipfx_render_event* m_render_event;
	pfx_unknown_event_object_t m_event_obejct;
};

PFX_Interface Ipfx_shader_program
{
	virtual ~Ipfx_shader_program(){;}
};


#endif			//PFX_SHADER_PROGRAM_H_
