/*
 * pfx_render_state.h
 *
 *  Created on: 2014-7-25
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_STATE_H_
#define		PFX_RENDER_STATE_H_


#include "../../include/util"
#include "../../include/cmatrix4.h"
#include "pfx_shader_program.h"
#include "pfx_buffer_object.h"
#include "../pfx_render_defs.h"
#include "../pfx_on_context_view.h"
#include "pfx_texture.h"
#include "pfx_framebuffer_object.h"

PECKER_BEGIN


PFX_Interface IPfx_render_state
{
	virtual ~IPfx_render_state(){ ; }

	virtual void clear_color(float_t red, float_t green, 
		float_t blue, float_t alpha_value) = 0;

	virtual void set_clear_mask(bitfield_t bitmask) = 0;
	
	virtual void set_viewport(const viewport_rect_t& viewport) = 0;

	virtual void draw_arrays(PFX_PRIMITIVE_MODE_t draw_type, uindex_t firstIndex, usize__t draw_count) = 0;

	virtual void gl_draw_arrays(enum_int_t draw_type, uindex_t firstIndex, usize__t draw_count) = 0;

	//////////////////////////////////////////////////////////////////////////
	// shader
	virtual Ipfx_shader* create_shader(enum_int_t shader_type) = 0;
	//////////////////////////////////////////////////////////////////////////
	// program
	virtual Ipfx_shader_program* create_program()  = 0;
	virtual Ipfx_shader_program* working_program() = 0;
	virtual Ipfx_shader_program* last_program()    = 0;

	virtual result_t select_program(Ipfx_shader_program* PARAM_INOUT program_ptr) = 0;
	virtual result_t revert_select_program() = 0;
	virtual result_t reset_state() = 0;
	virtual result_t reset_select_program() = 0;

	//////////////////////////////////////////////////////////////////////////
	// buffer
	virtual result_t bind_buffer(long_t __attribute_location) = 0;

	// vertex direct
	virtual void set_vertex_attrib_array(long_t __attribute_location,
		IPfx_vertex_cache_buffer* PARAM_IN buffer_ptr,
		usize__t attri_count,
		boolean_t bNormalized = PFX_BOOL_FALSE,
		uindex_t offset = 0, usize__t _size = MAX_UNSIGNED_VALUE) = 0;

	// vertex buffer
	virtual void set_vertex_attrib_array(long_t __attribute_location,
		IPfx_buffer_object* PARAM_IN buffer_ptr,
		usize__t attri_count,
		boolean_t bNormalized = PFX_BOOL_FALSE,
		long_t offset = 0) = 0;

	virtual result_t unbind_buffer(long_t __attribute_location) = 0;

	// vbo
	virtual IPfx_buffer_object* create_buffer() = 0;

	virtual result_t set_buffer_object(IPfx_buffer_object* PARAM_IN buffer_ptr,
		buffer_rect_t* PARAM_IN rect_bit = null) = 0;

	//////////////////////////////////////////////////////////////////////////
	// framebuffer
	virtual void use_system_framebuffer() = 0;

	virtual result_t unbind_framebuffer() = 0;

	virtual IPfx_renderbuffer* create_renderbuffer() = 0;
	
	virtual IPfx_framebuffer* create_framebuffer() = 0;

	virtual result_t use_framebuffer(IPfx_framebuffer* PARAM_IN fbuf_ptr) = 0;




	////////////////////////////////////////////////////////////////////////
	// texture
	virtual result_t set_texture(long_t __location,
		IPfx_texture* PARAM_IN texture_ptr,
		enum_int_t unit_number = 0) = 0;

	virtual ctexture_surface* create_texture_surface() = 0;

	virtual IPfx_texture* create_texture2D() = 0;

	//////////////////////////////////////////////////////////////////////////
	// float
	virtual void set_vertex_attri(long_t __location, float_t val) = 0;
	virtual void set_vertex_attri(long_t __location, float_t val1, float_t val2) = 0;
	virtual void set_vertex_attri(long_t __location, float_t val1, float_t val2, float_t val3) = 0;
	virtual void set_vertex_attri(long_t __location, float_t val1, float_t val2, float_t val3, float_t val4) = 0;
	virtual void set_vertex_attri(long_t __location, const vector2f_t& val) = 0;
	virtual void set_vertex_attri(long_t __location, const vector3f_t& val) = 0;
	virtual void set_vertex_attri(long_t __location, const vector4f_t& val) = 0;
	virtual void set_uniform_attri(long_t __location, float_t val) = 0;
	virtual void set_uniform_attri(long_t __location, float_t val1, float_t val2) = 0;
	virtual void set_uniform_attri(long_t __location, float_t val1, float_t val2, float_t val3) = 0;
	virtual void set_uniform_attri(long_t __location, float_t val1, float_t val2, float_t val3, float_t val4) = 0;
	virtual void set_uniform_attri(long_t __location, const vector2f_t& PARAM_INOUT val) = 0;
	virtual void set_uniform_attri(long_t __location, const vector3f_t& PARAM_INOUT val) = 0;
	virtual void set_uniform_attri(long_t __location, const vector4f_t& PARAM_INOUT val) = 0;
	virtual void set_uniform_attri(long_t __location, const float_t* PARAM_INOUT val_ptr, usize__t ncount) = 0;
	virtual void set_uniform_attri(long_t __location, const vector2f_t* PARAM_INOUT val_ptr, usize__t ncount) = 0;
	virtual void set_uniform_attri(long_t __location, const vector3f_t* PARAM_INOUT val_ptr, usize__t ncount) = 0;
	virtual void set_uniform_attri(long_t __location, const vector4f_t* PARAM_INOUT val_ptr, usize__t ncount) = 0;

	virtual void set_uniform_attri(long_t __location, const matrix2f_t& PARAM_INOUT val, bool btransport = false) = 0;
	virtual void set_uniform_attri(long_t __location, const matrix3f_t& PARAM_INOUT val, bool btransport = false) = 0;
	virtual void set_uniform_attri(long_t __location, const matrix4f_t& PARAM_INOUT val, bool btransport = false) = 0;
	virtual void set_uniform_attri(long_t __location, const matrix2f_t* PARAM_INOUT val_ptr, usize__t ncount, bool btransport = false) = 0;
	virtual void set_uniform_attri(long_t __location, const matrix3f_t* PARAM_INOUT val_ptr, usize__t ncount, bool btransport = false) = 0;
	virtual void set_uniform_attri(long_t __location, const matrix4f_t* PARAM_INOUT val_ptr, usize__t ncount, bool btransport = false) = 0;

	//////////////////////////////////////////////////////////////////////////
	// int
	virtual void set_uniform_attri(long_t __location, sint_t val) = 0;
	virtual void set_uniform_attri(long_t __location, sint_t val1, sint_t val2) = 0;
	virtual void set_uniform_attri(long_t __location, sint_t val1, sint_t val2, sint_t val3) = 0;
	virtual void set_uniform_attri(long_t __location, sint_t val1, sint_t val2, sint_t val3, sint_t val4) = 0;
	virtual void set_uniform_attri(long_t __location, const vector2i_t& PARAM_INOUT val) = 0;
	virtual void set_uniform_attri(long_t __location, const vector3i_t& PARAM_INOUT val) = 0;
	virtual void set_uniform_attri(long_t __location, const vector4i_t& PARAM_INOUT val) = 0;
	virtual void set_uniform_attri(long_t __location, const sint_t* PARAM_INOUT val_ptr, usize__t ncount) = 0;
	virtual void set_uniform_attri(long_t __location, const vector2i_t* PARAM_INOUT val_ptr, usize__t ncount) = 0;
	virtual void set_uniform_attri(long_t __location, const vector3i_t* PARAM_INOUT val_ptr, usize__t ncount) = 0;
	virtual void set_uniform_attri(long_t __location, const vector4i_t* PARAM_INOUT val_ptr, usize__t ncount) = 0;
};



PECKER_END

#endif			//PFX_RENDER_STATE_H_
