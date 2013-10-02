/*
 * pfx_stream.h
 *
 *  Created on: 2013-9-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_STREAM_H_
#define		PFX_STREAM_H_

#include "../pfx_defines.h"
#include <stdio.h>


PFX_C_EXTERN_BEGIN

typedef enum
{
	PFX_NONE_FORMAT = 0,

	PFX_CHAR_FORMAT,
	PFX_CHAR_STRING_FORMAT,

	PFX_WCHAR_FORMAT,
	PFX_WCHAR_STRING_FORMAT,

	PFX_DEC_INT_FORMAT,
	PFX_OCT_INT_FORMAT,
	PFX_HEX_INT_FORMAT,
	
	PFX_FLOAT_FORMAT,


	PFX_STRING_A_FORMAT,
	PFX_STRING_W_FORMAT,

	PFX_PRINT_HEX_0x_INT_FORMAT,
	PFX_PRINTF_FLOAT_E_FORMAT,

	PFX_STREAM_FORMAT_COUNT
}PFX_STREAM_FORMAT_t;


typedef struct st_input_format
{
	PFX_STREAM_FORMAT_t	m_format_type;
	pfx_usize_t							m_minwidth;
	pfx_usize_t							m_maxwidth;
	pfx_index_t						m_begin_index;
	pfx_index_t						m_end_index;

	pfx_bitfield_t						m_mask;								
}pfx_stream_format_t;

#define PFX_PRINTF_CAPS_LOCK (1 << 0)
#define PFX_PRINTF_FLOAT_E (1<<1)


PFX_INLINE pfx_stream_format_t* init_input_format(pfx_stream_format_t PARAM_INOUT* pformat);

PFX_INLINE pfx_stream_format_t* init_input_format_ex(pfx_stream_format_t PARAM_INOUT* pformat,
													PFX_STREAM_FORMAT_t format_type,
													pfx_usize_t minwidth,
													pfx_usize_t maxwidth,
													pfx_bitfield_t	nmask);

 pfx_result_t string_a_parse_int	(const pfx_char_t*						PARAM_IN			pstring_a,
														 const	pfx_stream_format_t*		PARAM_IN			pformat,
														 pfx_sint_t*									PARAM_INOUT	parse_result,
														 pfx_index_t*									PARAM_INOUT	pstring_a_offset);

 pfx_result_t string_a_parse_int64 (const pfx_char_t*						PARAM_IN			pstring_a,
															  const	pfx_stream_format_t*		PARAM_IN			pformat,
															  pfx_s64_t*									PARAM_INOUT	parse_result,
															  pfx_index_t*								PARAM_INOUT	pstring_a_offset);

pfx_result_t string_a_parse_float (const pfx_char_t*						PARAM_IN			pstring_a,
															const pfx_stream_format_t*	PARAM_IN			pformat,
															pfx_float_t*								PARAM_INOUT	parse_result,
															pfx_index_t*								PARAM_INOUT	pstring_a_offset);

pfx_result_t	string_a_parse_double (const pfx_char_t*					PARAM_IN			pstring_a,
																 const pfx_stream_format_t*	PARAM_IN			pformat,
																 pfx_double_t*							PARAM_INOUT	parse_result,
																 pfx_index_t*								PARAM_INOUT	pstring_a_offset);


pfx_usize_t sint_parse_string_a (pfx_sint_t									integer,
														pfx_char_t* PARAM_INOUT		pstring_buffer,
														pfx_usize_t									nstring_buffer_max_size,
														const	pfx_stream_format_t*	PARAM_IN			pformat);

pfx_usize_t uint_parse_string_a (pfx_uint_t									integer,
														pfx_char_t* PARAM_INOUT		pstring_buffer,
														pfx_usize_t									nstring_buffer_max_size,
														const	pfx_stream_format_t*	PARAM_IN			pformat);

pfx_usize_t sint64_parse_string_a (pfx_s64_t								long_integer,
															pfx_char_t* PARAM_INOUT	pstring_buffer,
															pfx_usize_t								nstring_buffer_max_size,
															const	pfx_stream_format_t*	PARAM_IN			pformat);

pfx_usize_t uint64_parse_string_a (pfx_u64_t								long_integer,
															pfx_char_t* PARAM_INOUT	pstring_buffer,
															pfx_usize_t								nstring_buffer_max_size,
															const	pfx_stream_format_t*	PARAM_IN			pformat);

pfx_usize_t float_parse_string_a  (pfx_float_t								single_real,
															pfx_char_t* PARAM_INOUT	pstring_buffer,
															pfx_usize_t								nstring_buffer_max_size,
															const	pfx_stream_format_t*	PARAM_IN			pformat);

pfx_usize_t double_parse_string_a  (pfx_double_t							double_real,
																pfx_char_t* PARAM_INOUT	pstring_buffer,
																pfx_usize_t								nstring_buffer_max_size,
																const	pfx_stream_format_t*	PARAM_IN			pformat);


pfx_index_t get_input_stream_format_a (const pfx_char_t*			PARAM_IN		pstream_buffer,
																	pfx_usize_t													nstream_buffer_size,
																	const	pfx_char_t*		PARAM_IN			pformat,
																	pfx_stream_format_t*	PARAM_INOUT	pformat_result);

pfx_index_t get_output_stream_format_a (const pfx_char_t*			PARAM_IN		pstream_buffer,
																		pfx_usize_t													nstream_buffer_size,
																		const	pfx_char_t*		PARAM_IN			pformat,
																		pfx_stream_format_t*	PARAM_INOUT	pformat_result);

pfx_index_t get_input_stream_format_w (const pfx_wchar_t*			PARAM_IN		pstream_buffer,
																		pfx_usize_t													nstream_buffer_size,
																		const	pfx_char_t*		PARAM_IN			pformat,
																		pfx_stream_format_t*	PARAM_INOUT	pformat_result);

pfx_index_t get_output_stream_format_w (const pfx_wchar_t*			PARAM_IN		pstream_buffer,
																			pfx_usize_t													nstream_buffer_size,
																			const	pfx_char_t*		PARAM_IN			pformat,
																			pfx_stream_format_t*	PARAM_INOUT	pformat_result);

pfx_index_t	pfx_steam_sscanf	(const pfx_char_t*		PARAM_IN		pstream_buffer,
											 pfx_usize_t											nstream_buffer_size,
											 const	pfx_char_t*		PARAM_IN		pformat,
											 va_list	args);

pfx_index_t	pfx_stream_ssprintf	(pfx_char_t*					PARAM_INOUT		pstream_buffer,
												 pfx_usize_t													nstream_buffer_size,
												 const	pfx_char_t*		PARAM_IN				pformat,
												 va_list	args);


//////////////////////////////////////////////////////////////////////////
PFX_INLINE pfx_stream_format_t* init_input_format(pfx_stream_format_t PARAM_INOUT* pformat)
{
	if (null != pformat)
	{
		pformat->m_format_type = PFX_NONE_FORMAT;
		pformat->m_minwidth = 0;
		pformat->m_maxwidth = MAX_UNSIGNED_VALUE;
		pformat->m_begin_index = 0;
		pformat->m_end_index = 0;
	}

	return pformat;
}

PFX_INLINE pfx_stream_format_t* init_input_format_ex(pfx_stream_format_t PARAM_INOUT* pformat,
	PFX_STREAM_FORMAT_t format_type,
	pfx_usize_t minwidth,
	pfx_usize_t maxwidth,
	pfx_bitfield_t	nmask)
{
	if (null != pformat)
	{
		pformat->m_format_type = format_type;
		pformat->m_minwidth = minwidth;
		pformat->m_maxwidth = maxwidth;
		pformat->m_begin_index = 0;
		pformat->m_end_index = 0;
		pformat->m_mask = nmask;
	}
	return pformat;
}
PFX_C_EXTERN_END



#endif			//PFX_STREAM_H_
