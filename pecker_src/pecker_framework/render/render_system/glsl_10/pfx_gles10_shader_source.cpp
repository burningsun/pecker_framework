﻿/*
* pfx_gles10_shader_source.cpp
*
*  Created on: 2014-8-8
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#include "pfx_gles10_shader_source.h"

PECKER_BEGIN
// hello
static const char_t* chr_hello_VS =
ASCII_STRING(
attribute vec4 aPosition;
void main()
{
	gl_Position =  aPosition;
}
);

static const char_t* chr_hello_FS =
ASCII_STRING(
precision mediump float;
void main()
{
	gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}
);

// position color	mvp
static const char_t* chr_position_Color_MVP_VS =
ASCII_STRING(
	attribute vec4 aPosition;
	attribute vec4 aColor;
	uniform  mat4 uFixedViewMatrix;
	varying vec4 vColor;
	void main() 
	{
		gl_Position = uFixedViewMatrix * aPosition;
		vColor = aColor;
	}
);

static const char_t* chr_Color_HIGH_FS =
ASCII_STRING(
	precision highp float;
	varying vec4 vColor;
	void main() 
	{
		gl_FragColor = vColor;
	}
);

static const char_t* chr_Color_MEDIUM_FS =
ASCII_STRING(
	precision mediump float;
	varying vec4 vColor;
	void main() 
	{
		gl_FragColor = vColor;
	}
);

static const char_t* chr_Color_LOW_FS =
ASCII_STRING(
	precision lowp float;
	varying vec4 vColor;
	void main() 
	{
		gl_FragColor = vColor;
	}
);
//

// position, texture position, mvp
static const char_t* chr_position_TexCoord_MVP_VS = 
ASCII_STRING(
	attribute vec4 aPosition;
	attribute vec2 aTexCoord;
	uniform  mat4 uFixedViewMatrix;
	varying vec2 vTexCoord;
	void main() 
	{
		gl_Position =  uFixedViewMatrix * aPosition;
		vTexCoord = aTexCoord;
	} 
);

static const char_t* chr_textcode_sample_HIGH_FS =
ASCII_STRING(
	precision highp float;
	varying vec2 vTexCoord;
	uniform sampler2D sTexture;
	void main()
	{
		gl_FragColor = texture2D(sTexture, vTexCoord);
	} 
);

static const char_t* chr_textcode_sample_MEDIUM_FS = 
ASCII_STRING(
	precision mediump float;
	varying vec2 vTexCoord;
	uniform sampler2D sTexture;
	void main()
	{
	  gl_FragColor = texture2D(sTexture, vTexCoord);
	}
);

static const char_t* chr_textcode_sample_LOW_FS = 
ASCII_STRING(
	precision lowp float;
	varying vec2 vTexCoord;
	uniform sampler2D sTexture;
	void main()
	{
		gl_FragColor = texture2D(sTexture, vTexCoord);
	} 
);


// position, texture1 position, texture2 position, mvp
static const char_t* chr_position_Two_TexCoord_MVP_VS = 
ASCII_STRING(
	attribute vec4 aPosition;
	attribute vec2 aTexCoord1;
	attribute vec2 aTexCoord2;
	uniform  mat4 uFixedViewMatrix;
	varying vec2 vTexCoord1;
	varying vec2 vTexCoord2;
	void main() 
	{
		gl_Position =  uFixedViewMatrix * aPosition;
		vTexCoord1 = aTexCoord1;
		vTexCoord2 = aTexCoord2;
	}
);

static const char_t* chr_textcode_two_sample_HIGH_FS = 
ASCII_STRING(
	precision highp float;
	varying vec2 vTexCoord1;
	varying vec2 vTexCoord2;
	uniform sampler2D sTextureBase;
	uniform sampler2D sTextureLight;
	uniform vec2      vMergeFactor;
	void main()
	{
		vec4 vBaseColor = texture2D(sTextureBase, vTexCoord1);
		vec4 vLightColor = texture2D(sTextureLight, vTexCoord2);
		gl_FragColor = (vBaseColor + vMergeFactor.x) * (sTextureLight + vMergeFactor.y);
	}
);

static const char_t* chr_textcode_two_sample_MEDIUM_FS = 
ASCII_STRING(
	precision mediump float;
	varying vec2 vTexCoord1;
	varying vec2 vTexCoord2;
	uniform sampler2D sTextureBase;
	uniform sampler2D sTextureLight;
	uniform vec2      vMergeFactor;
	void main()
	{
		vec4 vBaseColor = texture2D(sTextureBase,vTexCoord1);
		vec4 vLightColor = texture2D(sTextureLight,vTexCoord2);
		gl_FragColor = (vBaseColor + vMergeFactor.x) * (sTextureLight + vMergeFactor.y);
	} 
);

static const char_t* chr_textcode_two_sample_LOW_FS = 
ASCII_STRING(
	precision lowp float;
	varying vec2 vTexCoord1;
	varying vec2 vTexCoord2;
	uniform sampler2D sTextureBase;
	uniform sampler2D sTextureLight;
	uniform vec2      vMergeFactor;
	void main()
	{
		vec4 vBaseColor = texture2D(sTextureBase,vTexCoord1);
		vec4 vLightColor = texture2D(sTextureLight,vTexCoord2);
		gl_FragColor = (vBaseColor + vMergeFactor.x) * (sTextureLight + vMergeFactor.y);
	}
);

static cstring_ascii_t str_hello_VS,
str_hello_FS,
str_position_Color_MVP_VS,
str_position_TexCoord_MVP_VS,
str_position_Two_TexCoord_MVP_VS,
str_Color_HIGH_FS,
str_textcode_sample_HIGH_FS,
str_textcode_two_sample_HIGH_FS,
str_Color_MEDIUM_FS,
str_textcode_sample_MEDIUM_FS,
str_textcode_two_sample_MEDIUM_FS,
str_Color_LOW_FS,
str_textcode_sample_LOW_FS,
str_textcode_two_sample_LOW_FS;

static PFX_INLINE_CODE bool init_shader_source_table()
{
	str_hello_VS.init_string(chr_hello_VS, strlen(chr_hello_VS));
	str_hello_FS.init_string(chr_hello_FS, strlen(chr_hello_FS));

	str_position_Color_MVP_VS.init_string(chr_position_Color_MVP_VS, strlen(chr_position_Color_MVP_VS) + 1);
	str_position_TexCoord_MVP_VS.init_string(chr_position_TexCoord_MVP_VS, strlen(chr_position_TexCoord_MVP_VS) + 1);
	str_position_Two_TexCoord_MVP_VS.init_string(chr_position_Two_TexCoord_MVP_VS, strlen(chr_position_Two_TexCoord_MVP_VS) + 1);

	str_Color_HIGH_FS.init_string(chr_Color_HIGH_FS, strlen(chr_Color_HIGH_FS));
	str_textcode_sample_HIGH_FS.init_string(chr_textcode_sample_HIGH_FS, strlen(chr_textcode_sample_HIGH_FS));
	str_textcode_two_sample_HIGH_FS.init_string(chr_textcode_two_sample_HIGH_FS, strlen(chr_textcode_two_sample_HIGH_FS));

	str_Color_MEDIUM_FS.init_string(chr_Color_MEDIUM_FS, strlen(chr_Color_MEDIUM_FS));
	str_textcode_sample_MEDIUM_FS.init_string(chr_textcode_sample_MEDIUM_FS, strlen(chr_textcode_sample_MEDIUM_FS));
	str_textcode_two_sample_MEDIUM_FS.init_string(chr_textcode_two_sample_MEDIUM_FS, strlen(chr_textcode_two_sample_MEDIUM_FS));

	str_Color_LOW_FS.init_string(chr_Color_LOW_FS, strlen(chr_Color_LOW_FS));
	str_textcode_sample_LOW_FS.init_string(chr_textcode_sample_LOW_FS, strlen(chr_textcode_sample_LOW_FS));
	str_textcode_two_sample_LOW_FS.init_string(chr_textcode_two_sample_LOW_FS, strlen(chr_textcode_two_sample_LOW_FS));

	return 	true;
}


//static const char_t* str_vs[SYSTEM_DEFUAL_GLES10_SHADER_SOURCE_COUNT + 1] =
//{ chr_position_Color_MVP_VS, chr_position_TexCoord_MVP_VS, chr_position_Two_TexCoord_MVP_VS, chr_position_Color_MVP_VS };
//
//static const char_t* str_h_fs[SYSTEM_DEFUAL_GLES10_SHADER_FLAOT_PRECISION_COUNT + 1] =
//{ chr_Color_HIGH_FS, chr_textcode_sample_HIGH_FS, chr_textcode_two_sample_HIGH_FS };
//
//static const char_t* str_m_fs[SYSTEM_DEFUAL_GLES10_SHADER_FLAOT_PRECISION_COUNT + 1] =
//{ chr_Color_MEDIUM_FS, chr_textcode_sample_MEDIUM_FS, chr_textcode_two_sample_MEDIUM_FS };
//
//static const char_t* str_l_fs[SYSTEM_DEFUAL_GLES10_SHADER_FLAOT_PRECISION_COUNT + 1] =
//{ chr_Color_LOW_FS, chr_textcode_sample_LOW_FS, chr_textcode_two_sample_LOW_FS };

//static const char_t** str_preci_f_table[SYSTEM_DEFUAL_GLES10_SHADER_FLAOT_PRECISION_COUNT + 1]
//= { str_h_fs, str_m_fs, str_l_fs };

//////////////////////////////////////////////////////////////////////////
static const cstring_ascii_t* str_vs[SYSTEM_DEFUAL_GLES10_SHADER_SOURCE_COUNT + 1] =
{ &str_hello_VS, &str_position_Color_MVP_VS, &str_position_TexCoord_MVP_VS, &str_position_Two_TexCoord_MVP_VS, &str_position_Color_MVP_VS };

static const cstring_ascii_t* str_h_fs[SYSTEM_DEFUAL_GLES10_SHADER_SOURCE_COUNT + 1] =
{ &str_hello_FS, &str_Color_HIGH_FS, &str_textcode_sample_HIGH_FS, &str_textcode_two_sample_HIGH_FS, &str_Color_HIGH_FS };

static const cstring_ascii_t* str_m_fs[SYSTEM_DEFUAL_GLES10_SHADER_SOURCE_COUNT + 1] =
{ &str_hello_FS, &str_Color_MEDIUM_FS, &str_textcode_sample_MEDIUM_FS, &str_textcode_two_sample_MEDIUM_FS, &str_Color_MEDIUM_FS };

static const cstring_ascii_t* str_l_fs[SYSTEM_DEFUAL_GLES10_SHADER_SOURCE_COUNT + 1] =
{ &str_hello_FS, &str_Color_LOW_FS, &str_textcode_sample_LOW_FS, &str_textcode_two_sample_LOW_FS, &str_Color_LOW_FS };

static const cstring_ascii_t** str_preci_f_table[SYSTEM_DEFUAL_GLES10_SHADER_FLAOT_PRECISION_COUNT + 1]
= { str_h_fs, str_m_fs, str_l_fs, str_h_fs };

const  shader_souce_string_t* get_system_defualt_shader_source(
	shader_souce_string_t& shader_source_code,
	SYSTEM_DEFUALT_GLES10_SHADER_SOURCE_t __source_type,
	SYSTEM_DEFUALT_GLES10_SHADER_FLAOT_PRECISION_t __precision_float //= SSS_MEDIUEM_FLOAT
	)
{
	static bool binit_table = init_shader_source_table();
	if (!binit_table)
	{
		binit_table = init_shader_source_table();
	}
	shader_source_code.m_str_vertext_shader = str_vs[__source_type];
	shader_source_code.m_str_fragment_shader = str_preci_f_table[__precision_float][__source_type];
	return 	&shader_source_code;
}


PECKER_END
