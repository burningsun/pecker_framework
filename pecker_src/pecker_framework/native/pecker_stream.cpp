/*
 * pecker_stream.cpp
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_stream.h"

PECKER_BEGIN

pecker_read_stream_form_memery::pecker_read_stream_form_memery():_M_bind_read_buffer(null),
																																	_M_bind_read_size(0)
{

}
pecker_read_stream_form_memery::~pecker_read_stream_form_memery()
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	_M_bind_read_buffer = null;
	_M_bind_read_size = 0;
}
HResult pecker_read_stream_form_memery::bind_read_buffer(CONST_STREAM_BUFFER pbind_buffer,SInt bind_size)
{
	if (null == pbind_buffer || bind_size <= 0)
	{
		return P_ERR;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);

	_M_bind_read_buffer = pbind_buffer;
	_M_bind_read_size = bind_size; 
	return P_OK;
}

HResult pecker_read_stream_form_memery::read_integer(int &read_value)
{
	if (null == _M_bind_read_buffer || 0 == _M_bind_read_size)
	{
		return P_ERR;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	int index = sscanf(_M_bind_read_buffer,"%d",&read_value);
	if (index  > _M_bind_read_size)
	{
		_M_bind_read_buffer = null; 
		_M_bind_read_size = 0;
		return P_ERR;
	}
	else
	{
		_M_bind_read_buffer += index;
		_M_bind_read_size -= index;
	}
	return P_OK;
}

HResult pecker_read_stream_form_memery::read_long(long long &read_value)
{
	if (null == _M_bind_read_buffer || 0 == _M_bind_read_size)
	{
		return P_ERR;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	int index = sscanf(_M_bind_read_buffer,"%ld",&read_value);
	if (index  > _M_bind_read_size)
	{
		_M_bind_read_buffer = null; 
		_M_bind_read_size = 0;
		return P_ERR;
	}
	else
	{
		_M_bind_read_buffer += index;
		_M_bind_read_size -= index;
	}
	return P_OK;
}

HResult pecker_read_stream_form_memery::read_char(char &read_value)
{
	if (null == _M_bind_read_buffer || 0 == _M_bind_read_size)
	{
		return P_ERR;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);

	if (_M_bind_read_size > 0)
	{
		read_value = _M_bind_read_buffer[0];
		++_M_bind_read_buffer;
		--_M_bind_read_size;
		return P_OK;
	}
	else
	{
		return P_ERR;
	}
	//int index = sscanf(_M_bind_read_buffer,"%c",&read_value);

	//if (index  > _M_bind_read_size)
	//{
	//	_M_bind_read_buffer = null; 
	//	_M_bind_read_size = 0;
	//	return P_ERR;
	//}
	//else
	//{
	//	_M_bind_read_buffer += index;
	//	_M_bind_read_size -= index;
	//}
	return P_OK;
}

HResult pecker_read_stream_form_memery::read_float(char &read_value)
{
	if (null == _M_bind_read_buffer || 0 == _M_bind_read_size)
	{
		return P_ERR;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	int index = sscanf(_M_bind_read_buffer,"%f",&read_value);
	if (index > _M_bind_read_size)
	{
		_M_bind_read_buffer = null; 
		_M_bind_read_size = 0;
		return P_ERR;
	}
	else
	{
		_M_bind_read_buffer += index;
		_M_bind_read_size -= index;
	}
	return P_OK;
}

HResult pecker_read_stream_form_memery::read_double(char &read_value)
{
	if (null == _M_bind_read_buffer || 0 == _M_bind_read_size)
	{
		return P_ERR;
	}

	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	int index = sscanf(_M_bind_read_buffer,"%lf",&read_value);
	if (index > _M_bind_read_size)
	{
		_M_bind_read_buffer = null; 
		_M_bind_read_size = 0;
		return P_ERR;
	}
	else
	{
		_M_bind_read_buffer += index;
		_M_bind_read_size -= index;
	}
	return P_OK;
}

int pecker_read_stream_form_memery::read_chars(char* pread_buffer,int read_buffer_size)
{
	if (null == _M_bind_read_buffer || 0 == _M_bind_read_size)
	{
		return 0;
	}

	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	
	char read_char_value = 0;
	int isubsize = 0;
	int ireadsize = 0;
	for (ireadsize=0;ireadsize<read_buffer_size;++ireadsize)
	{
		if (P_OK == read_char(read_char_value))
		{
			if ( '\n' == read_char_value || 0 == read_char_value)
			{
				ireadsize -= isubsize;
				break;
			}
			if ('\r' == read_char_value)
			{
				++isubsize;
				continue;
			}
			pread_buffer[ireadsize] = read_char_value;
		}
		else
		{
			break;
		}
	}

	return ireadsize;
}


pecker_write_stream_to_memery::pecker_write_stream_to_memery():	_M_bind_write_buffer(null),
																																_M_bind_write_size (null)
{

}

pecker_write_stream_to_memery::~pecker_write_stream_to_memery()
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);

	_M_bind_write_buffer = null;
	_M_bind_write_size = null;
}

HResult pecker_write_stream_to_memery::bind_write_buffer( STREAM_BUFFER pbind_buffer,SInt bind_size)
{
	if (null == pbind_buffer || bind_size <= 0)
	{
		return P_ERR;
	}

	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);

	_M_bind_write_buffer = pbind_buffer;
	_M_bind_write_size = bind_size;
	
	return P_OK;
}

HResult pecker_write_stream_to_memery::write_integer(int write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	
	char tempstring[5];
	int index = sprintf(tempstring,"%d",write_value);
	if (index < _M_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			_M_bind_write_buffer[i] = tempstring[i];
		}
		_M_bind_write_buffer[index] = 0;
		_M_bind_write_buffer+=index;
		_M_bind_write_size -= index;
		return P_OK;
	}
	return P_ERR;
}

HResult pecker_write_stream_to_memery::write_unsigned_integer(unsigned int write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);

	char tempstring[5];
	int index = sprintf(tempstring,"%u",write_value);
	if (index < _M_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			_M_bind_write_buffer[i] = tempstring[i];
		}
		_M_bind_write_buffer[index] = 0;
		_M_bind_write_buffer+=index;
		_M_bind_write_size -= index;
		return P_OK;
	}
	return P_ERR;
}

HResult pecker_write_stream_to_memery::write_long(long long write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	char tempstring[9];
	int index = sprintf(tempstring,"%ld",write_value);
	if (index < _M_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			_M_bind_write_buffer[i] = tempstring[i];
		}
		_M_bind_write_buffer[index] = 0;
		_M_bind_write_buffer+=index;
		_M_bind_write_size -= index;
		return P_OK;
	}
	return P_ERR;
}

HResult pecker_write_stream_to_memery::write_unsigned_long(unsigned long long write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	char tempstring[9];
	int index = sprintf(tempstring,"%ld",write_value);
	if (index < _M_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			_M_bind_write_buffer[i] = tempstring[i];
		}
		_M_bind_write_buffer[index] = 0;
		_M_bind_write_buffer+=index;
		_M_bind_write_size -= index;
		return P_OK;
	}
	return P_ERR;
}

HResult pecker_write_stream_to_memery::write_char(char write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);

	char tempstring[5];
	int index = sprintf(tempstring,"%c",write_value);
	if (index < _M_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			_M_bind_write_buffer[i] = tempstring[i];
		}
		_M_bind_write_buffer[index] = 0;
		_M_bind_write_buffer+=index;
		_M_bind_write_size -= index;
		return P_OK;
	}
	return P_ERR;
}

HResult pecker_write_stream_to_memery::write_byte(char write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);


	char tempstring[5];
	int index = sprintf(tempstring,"%02x",write_value);
	if (index < _M_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			_M_bind_write_buffer[i] = tempstring[i];
		}
		_M_bind_write_buffer[index] = 0;
		_M_bind_write_buffer+=index;
		_M_bind_write_size -= index;
		return P_OK;
	}
	return P_ERR;
}

HResult pecker_write_stream_to_memery::write_float(char write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);

	char tempstring[5];
	int index = sprintf(tempstring,"%f",write_value);
	if (index < _M_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			_M_bind_write_buffer[i] = tempstring[i];
		}
		_M_bind_write_buffer[index] = 0;
		_M_bind_write_buffer+=index;
		_M_bind_write_size -= index;
		return P_OK;
	}
	return P_ERR;
}

HResult pecker_write_stream_to_memery::write_double(char write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);
	char tempstring[5];
	int index = sprintf(tempstring,"%f",write_value);
	if (index < _M_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			_M_bind_write_buffer[i] = tempstring[i];
		}
		_M_bind_write_buffer[index] = 0;
		_M_bind_write_buffer+=index;
		_M_bind_write_size -= index;
		return P_OK;
	}
	return P_ERR;
}

int pecker_write_stream_to_memery::write_chars(char* pwrite_buffer,int write_buffer_size)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&_M_critical_section);

	char write_char_value = 0;

	int iwritesize = 0;
	for (iwritesize=0;iwritesize<write_buffer_size;++iwritesize)
	{
		write_char_value = pwrite_buffer[iwritesize];
		if (0 == write_char_value)
		{
			--iwritesize;
			break;
		}
		if (P_OK != write_char(write_char_value))
		{
			break;
		}
	}

	return iwritesize;
}


PECKER_END

