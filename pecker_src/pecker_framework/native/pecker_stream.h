/*
 * pecker_stream.h
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_STREAM_H_
#define PECKER_STREAM_H_

#include "../pfx_defines.h"
#include "pecker_thread.h"

#include <stdio.h>
PECKER_BEGIN

// 流读取数据操作接口
PFX_Interface PFX_NATIVE_API Ipecker_read_stream
{
	virtual ~Ipecker_read_stream (){;}
	virtual pfx_result_t read_integer (pfx_sint_t &read_value) = 0;
	virtual pfx_result_t read_long (pfx_s64_t &read_value) = 0;
	virtual pfx_result_t read_char (pfx_char_t &read_value) = 0;
	virtual pfx_result_t read_float (pfx_float_t &read_value) = 0;
	virtual pfx_result_t read_double (pfx_double_t &read_value) = 0;
	virtual pfx_usize_t read_chars (pfx_char_t* read_buffer_ptr,pfx_usize_t read_buffer_size) = 0;
};
// 流写数据操作接口
PFX_Interface PFX_NATIVE_API Ipecker_write_stream
{
	virtual ~Ipecker_write_stream (){;}
	virtual pfx_result_t write_integer (pfx_sint_t write_value) = 0;
	virtual pfx_result_t write_unsigned_integer (pfx_uint_t write_value) = 0;
	virtual pfx_result_t write_long (pfx_s64_t write_value) = 0;
	virtual pfx_result_t write_unsigned_long (pfx_u64_t write_value) = 0;
	virtual pfx_result_t write_char (pfx_char_t write_value) = 0;
	virtual pfx_result_t write_byte (pfx_byte_t write_value) = 0;
	virtual pfx_result_t write_float (pfx_float_t write_value) = 0;
	virtual pfx_result_t write_double (pfx_double_t write_value) = 0;
	virtual pfx_usize_t write_chars (pfx_char_t* write_buffer_ptr,pfx_usize_t write_buffer_size) = 0;
};

class PFX_NATIVE_API pecker_read_stream_form_memery : public Ipecker_read_stream
{
typedef const char* CONST_STREAM_BUFFER_t; 
private:
	CONST_STREAM_BUFFER_t m_bind_read_buffer_ptr;
	pfx_usize_t								m_bind_read_size;
	pecker_critical_section			m_critical_section;
public:
	pecker_read_stream_form_memery();
	virtual ~pecker_read_stream_form_memery();
	pfx_result_t bind_read_buffer(CONST_STREAM_BUFFER_t bind_buffer_ptr,pfx_usize_t bind_size);
	pfx_result_t read_integer (pfx_sint_t &read_value);
	pfx_result_t read_long (pfx_s64_t &read_value);
	pfx_result_t read_char (pfx_char_t &read_value);
	pfx_result_t read_float (pfx_float_t &read_value);
	pfx_result_t read_double (pfx_double_t &read_value);
	pfx_usize_t	  read_chars (pfx_char_t* read_buffer_ptr,pfx_usize_t read_buffer_size);
};



class PFX_NATIVE_API pecker_write_stream_to_memery : public Ipecker_write_stream
{
	typedef char* STREAM_BUFFER_t; 
private:
	STREAM_BUFFER_t			m_bind_write_buffer_ptr;
	pfx_usize_t							m_bind_write_size;
	pecker_critical_section		m_critical_section;
public:
	pecker_write_stream_to_memery();
	virtual ~pecker_write_stream_to_memery();
	pfx_result_t bind_write_buffer(STREAM_BUFFER_t bind_buffer_ptr,pfx_usize_t bind_size);
	pfx_result_t write_integer (pfx_sint_t write_value);
	pfx_result_t write_unsigned_integer (pfx_uint_t write_value);
	pfx_result_t write_long (pfx_s64_t write_value);
	pfx_result_t write_unsigned_long (pfx_u64_t write_value);
	pfx_result_t write_char (pfx_char_t write_value);
	pfx_result_t write_byte (pfx_byte_t write_value);
	pfx_result_t write_float (pfx_float_t write_value);
	pfx_result_t write_double (pfx_double_t write_value);
	pfx_usize_t  write_chars (pfx_char_t* write_buffer_ptr,pfx_usize_t write_buffer_size);
};


PECKER_END


#endif /* PECKER_STANDER_IOSTREAM_H_ */
