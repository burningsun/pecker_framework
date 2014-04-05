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
PFX_Interface Ipecker_read_stream
{
	virtual ~Ipecker_read_stream (){;}
	virtual pfx_result_t read_integer (int &read_value) = 0;
	virtual pfx_result_t read_long (long long &read_value) = 0;
	virtual pfx_result_t read_char (char &read_value) = 0;
	virtual pfx_result_t read_float (char &read_value) = 0;
	virtual pfx_result_t read_double (char &read_value) = 0;
	virtual int read_chars (char* read_buffer_ptr,int read_buffer_size) = 0;
};
// 流写数据操作接口
PFX_Interface Ipecker_write_stream
{
	virtual ~Ipecker_write_stream (){;}
	virtual pfx_result_t write_integer (int write_value) = 0;
	virtual pfx_result_t write_unsigned_integer (unsigned int write_value) = 0;
	virtual pfx_result_t write_long (long long write_value) = 0;
	virtual pfx_result_t write_unsigned_long (unsigned long long write_value) = 0;
	virtual pfx_result_t write_char (char write_value) = 0;
	virtual pfx_result_t write_byte (char write_value) = 0;
	virtual pfx_result_t write_float (char write_value) = 0;
	virtual pfx_result_t write_double (char write_value) = 0;
	virtual int write_chars (char* write_buffer_ptr,int write_buffer_size) = 0;
};

class pecker_read_stream_form_memery : public Ipecker_read_stream
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
	pfx_result_t read_integer(int &read_value);
	pfx_result_t read_long(long long &read_value);
	pfx_result_t read_char(char &read_value);
	pfx_result_t read_float(char &read_value);
	pfx_result_t read_double(char &read_value); 
	int read_chars(char* read_buffer_ptr,int read_buffer_size);
};



class pecker_write_stream_to_memery : public Ipecker_write_stream
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
	pfx_result_t write_integer(int write_value);
	pfx_result_t write_unsigned_integer(unsigned int write_value);
	pfx_result_t write_long(long long write_value);
	pfx_result_t write_unsigned_long(unsigned long long write_value);
	pfx_result_t write_char(char write_value);
	pfx_result_t write_byte(char write_value);
	pfx_result_t write_float(char write_value);
	pfx_result_t write_double(char write_value);
	int write_chars(char* write_buffer_ptr,int write_buffer_size);
};


PECKER_END


#endif /* PECKER_STANDER_IOSTREAM_H_ */
