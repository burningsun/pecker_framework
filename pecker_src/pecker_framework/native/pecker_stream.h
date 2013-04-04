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

#include "../CPeckerObject.h"
#include "pecker_thread.h"

#include <stdio.h>
PECKER_BEGIN

// 流读取数据操作接口
PeckerInterface Ipecker_read_stream
{
	virtual ~Ipecker_read_stream(){;}
	virtual HResult read_integer(int &read_value) = 0;
	virtual HResult read_long(long long &read_value) = 0;
	virtual HResult read_char(char &read_value) = 0;
	virtual HResult read_float(char &read_value) = 0;
	virtual HResult read_double(char &read_value) = 0;
	virtual int read_chars(char* pread_buffer,int read_buffer_size) = 0;
};
// 流写数据操作接口
PeckerInterface Ipecker_write_stream
{
	virtual ~Ipecker_write_stream(){;}
	virtual HResult write_integer(int write_value) = 0;
	virtual HResult write_unsigned_integer(unsigned int write_value) = 0;
	virtual HResult write_long(long long write_value) = 0;
	virtual HResult write_unsigned_long(unsigned long long write_value) = 0;
	virtual HResult write_char(char write_value) = 0;
	virtual HResult write_byte(char write_value) = 0;
	virtual HResult write_float(char write_value) = 0;
	virtual HResult write_double(char write_value) = 0;
	virtual int write_chars(char* pwrite_buffer,int write_buffer_size) = 0;
};

class pecker_read_stream_form_memery : public Ipecker_read_stream
{
typedef const char* CONST_STREAM_BUFFER; 
private:
	CONST_STREAM_BUFFER _M_bind_read_buffer;
	SInt						  _M_bind_read_size;
	pecker_critical_section _M_critical_section;
public:
	pecker_read_stream_form_memery();
	virtual ~pecker_read_stream_form_memery();
	HResult bind_read_buffer(CONST_STREAM_BUFFER pbind_buffer,SInt bind_size);
	HResult read_integer(int &read_value);
	HResult read_long(long long &read_value);
	HResult read_char(char &read_value);
	HResult read_float(char &read_value);
	HResult read_double(char &read_value); 
	int read_chars(char* pread_buffer,int read_buffer_size);
};

//inline HResult pecker_read_stream_form_memery::read_char(char &read_value)
//{
//	if (null == _M_bind_read_buffer || 0 == _M_bind_read_size)
//	{
//		return P_ERR;
//	}
//	pecker_critical_lock cs_lock;
//	cs_lock.lock(&_M_critical_section);
//	int index = sscanf(_M_bind_read_buffer,"%c",&read_value);
//	if (index  > _M_bind_read_size)
//	{
//		_M_bind_read_buffer = null; 
//		_M_bind_read_size = 0;
//		return P_ERR;
//	}
//	else
//	{
//		_M_bind_read_buffer += index;
//		_M_bind_read_size -= index;
//	}
//	return P_OK;
//}
//
//inline int pecker_read_stream_form_memery::read_chars(char* pread_buffer,int read_buffer_size)
//{
//	if (null == _M_bind_read_buffer || 0 == _M_bind_read_size)
//	{
//		return 0;
//	}
//
//	pecker_critical_lock cs_lock;
//	cs_lock.lock(&_M_critical_section);
//
//	char read_char_value = 0;
//	int isubsize = 1;
//	int ireadsize = 0;
//	for (ireadsize=0;ireadsize<read_buffer_size;++ireadsize)
//	{
//		if (P_OK == read_char(read_char_value))
//		{
//			if ( '\n' == read_char_value || 0 == read_char_value)
//			{
//				ireadsize -= isubsize;
//				break;
//			}
//			if ('\r' == read_char_value)
//			{
//				++isubsize;
//				continue;
//			}
//			pread_buffer[ireadsize] = read_char_value;
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	return ireadsize;
//}

class pecker_write_stream_to_memery : public Ipecker_write_stream
{
	typedef char* STREAM_BUFFER; 
private:
	STREAM_BUFFER _M_bind_write_buffer;
	SInt						  _M_bind_write_size;
	pecker_critical_section _M_critical_section;
public:
	pecker_write_stream_to_memery();
	virtual ~pecker_write_stream_to_memery();
	HResult bind_write_buffer(STREAM_BUFFER pbind_buffer,SInt bind_size);
	HResult write_integer(int write_value);
	HResult write_unsigned_integer(unsigned int write_value);
	HResult write_long(long long write_value);
	HResult write_unsigned_long(unsigned long long write_value);
	HResult write_char(char write_value);
	HResult write_byte(char write_value);
	HResult write_float(char write_value);
	HResult write_double(char write_value);
	int write_chars(char* pwrite_buffer,int write_buffer_size);
};


PECKER_END


#endif /* PECKER_STANDER_IOSTREAM_H_ */
