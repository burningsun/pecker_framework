/*
 * pfx_render_allocator.h
 *
 *  Created on: 2014-7-26
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_ALLOCATOR_H_
#define		PFX_RENDER_ALLOCATOR_H_

#include "../pfx_defines.h"
#include "pfx_render_defs.h"
#include "../Include/native"
#include "../Include/cbst"
#include "../Include/carray"


PECKER_BEGIN

typedef pecker_simple_allocator< cavl_bst_node < struct st_shader_param > > shader_param_node_allocator_t;
typedef pecker_simple_allocator< byte_t > vexbuffer_allocator_t;
typedef pecker_simple_allocator< byte_t > imgbuffer_allocator_t;
typedef pecker_simple_allocator< enum_int_t > configbuffer_allocator_t;



PECKER_END

#endif			//PFX_RENDER_ALLOCATOR_H_
