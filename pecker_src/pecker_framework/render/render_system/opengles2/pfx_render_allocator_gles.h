/*
 * pfx_render_allocator_gles.h
 *
 *  Created on: 2014-8-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_ALLOCATOR_GLES_H_
#define		PFX_RENDER_ALLOCATOR_GLES_H_
#include "../../pfx_render_allocator.h"

PECKER_BEGIN

class  cnative_vertex_cache_buffer;
class  cvertex_cache_buffer_gles2;
#define VERTEXT_CACHE_ALLOC_GLES2_NAME 	pecker_simple_allocator< cnative_vertex_cache_buffer >
#define VERTEXT_CACHE_ALLOC_GLES2 class VERTEXT_CACHE_ALLOC_GLES2_NAME 	 
typedef VERTEXT_CACHE_ALLOC_GLES2 vertex_cache_alloc_gles2_t;

#define VERTEXT_CACHE_NODE_ALLOC_GLES2_NAME pecker_simple_allocator< cvertex_cache_buffer_gles2 >
#define VERTEXT_CACHE_NODE_ALLOC_GLES2 class VERTEXT_CACHE_NODE_ALLOC_GLES2_NAME
typedef VERTEXT_CACHE_NODE_ALLOC_GLES2 vertex_cache_node_alloc_gles2_t;

class cbuffer_object_gles2;
class cnative_buffer_object_gles2;

#define BUFFER_OBJECT_ALLOC_GLES2 class pecker_simple_allocator< cnative_buffer_object_gles2 > 	 
typedef BUFFER_OBJECT_ALLOC_GLES2 buffer_object_alloc_gles2_t;
#define BUFFER_OBJECT_NODE_ALLOC_GLES2 class pecker_simple_allocator< cbuffer_object_gles2 >
typedef BUFFER_OBJECT_NODE_ALLOC_GLES2 buffer_object_node_alloc_gles2_t;


class  cnative_shader_gles2;
class  cshader_gles2;

#define SHADER_ALLOC_GLES2      class pecker_simple_allocator< cnative_shader_gles2 > 	 
typedef SHADER_ALLOC_GLES2 		native_shader_gles2_t;

#define SHADER_NODE_ALLOC_GLES2 class pecker_simple_allocator< cshader_gles2 >
typedef SHADER_NODE_ALLOC_GLES2 shader_node_alloc_gles2_t;


class cnative_shader_program_gles2;
class cshader_program_gles2;

#define SHADER_PROGRAM_ALLOC_GLES2      class pecker_simple_allocator< cnative_shader_program_gles2 > 	 
typedef SHADER_PROGRAM_ALLOC_GLES2 		native_shader_program_gles2_t;
			  
#define SHADER_PROGRAM_NODE_ALLOC_GLES2 class pecker_simple_allocator< cshader_program_gles2 >
typedef SHADER_PROGRAM_NODE_ALLOC_GLES2 shader_program_node_gles2_t;

class ctexture2D_gles;
#define  TEXTURE_2D_NODE_ALLOC_GLES2 class pecker_simple_allocator< ctexture2D_gles >
typedef TEXTURE_2D_NODE_ALLOC_GLES2  ctexture2D_gles_allocator_t;






PECKER_END

#endif			//PFX_RENDER_ALLOCATOR_GLES_H_
