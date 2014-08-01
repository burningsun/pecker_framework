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
#include "syn_lock.h"


#include <stdio.h>
PECKER_BEGIN

// 流读取数据操作接口
PFX_Interface PFX_NATIVE_API Ipecker_read_stream
{
	virtual ~Ipecker_read_stream (){;}
	virtual result_t read_integer (sint_t &read_value) = 0;
	virtual result_t read_long (s64_t &read_value) = 0;
	virtual result_t read_char (char_t &read_value) = 0;
	virtual result_t read_float (float_t &read_value) = 0;
	virtual result_t read_double (double_t &read_value) = 0;
	virtual usize__t read_chars (char_t* read_buffer_ptr,usize__t read_buffer_size) = 0;
};
// 流写数据操作接口
PFX_Interface PFX_NATIVE_API Ipecker_write_stream
{
	virtual ~Ipecker_write_stream (){;}
	virtual result_t write_integer (sint_t write_value) = 0;
	virtual result_t write_unsigned_integer (uint_t write_value) = 0;
	virtual result_t write_long (s64_t write_value) = 0;
	virtual result_t write_unsigned_long (u64_t write_value) = 0;
	virtual result_t write_char (char_t write_value) = 0;
	virtual result_t write_byte (byte_t write_value) = 0;
	virtual result_t write_float (float_t write_value) = 0;
	virtual result_t write_double (double_t write_value) = 0;
	virtual usize__t write_chars (char_t* write_buffer_ptr,usize__t write_buffer_size) = 0;
};

class PFX_NATIVE_API pecker_read_stream_form_memery : public Ipecker_read_stream
{
typedef const char* CONST_STREAM_BUFFER_t; 
private:
	CONST_STREAM_BUFFER_t m_bind_read_buffer_ptr;
	usize__t								m_bind_read_size;
	cs_t										m_critical_section;
public:
	pecker_read_stream_form_memery();
	virtual ~pecker_read_stream_form_memery();
	result_t bind_read_buffer(CONST_STREAM_BUFFER_t bind_buffer_ptr,usize__t bind_size);
	result_t read_integer (sint_t &read_value);
	result_t read_long (s64_t &read_value);
	result_t read_char (char_t &read_value);
	result_t read_float (float_t &read_value);
	result_t read_double (double_t &read_value);
	usize__t	  read_chars (char_t* read_buffer_ptr,usize__t read_buffer_size);
};



class PFX_NATIVE_API pecker_write_stream_to_memery : public Ipecker_write_stream
{
	typedef char* STREAM_BUFFER_t; 
private:
	STREAM_BUFFER_t		m_bind_write_buffer_ptr;
	usize__t							m_bind_write_size;
	cs_t									m_critical_section;
public:
	pecker_write_stream_to_memery();
	virtual ~pecker_write_stream_to_memery();
	result_t bind_write_buffer(STREAM_BUFFER_t bind_buffer_ptr,usize__t bind_size);
	result_t write_integer (sint_t write_value);
	result_t write_unsigned_integer (uint_t write_value);
	result_t write_long (s64_t write_value);
	result_t write_unsigned_long (u64_t write_value);
	result_t write_char (char_t write_value);
	result_t write_byte (byte_t write_value);
	result_t write_float (float_t write_value);
	result_t write_double (double_t write_value);
	usize__t  write_chars (char_t* write_buffer_ptr,usize__t write_buffer_size);
};


PECKER_END


#endif /* PECKER_STANDER_IOSTREAM_H_ */
