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

pecker_read_stream_form_memery::pecker_read_stream_form_memery():m_bind_read_buffer_ptr(null),
																																	m_bind_read_size(0)
{

}
pecker_read_stream_form_memery::~pecker_read_stream_form_memery()
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	m_bind_read_buffer_ptr = null;
	m_bind_read_size = 0;
}
pfx_result_t pecker_read_stream_form_memery::bind_read_buffer(CONST_STREAM_BUFFER_t bind_buffer_ptr,pfx_usize_t bind_size)
{
	if (null == bind_buffer_ptr || bind_size <= 0)
	{
		return PFX_STATUS_ERROR_;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);

	m_bind_read_buffer_ptr = bind_buffer_ptr;
	m_bind_read_size = bind_size; 
	return PFX_STATUS_OK;
}

pfx_result_t pecker_read_stream_form_memery::read_integer(int &read_value)
{
	if (null == m_bind_read_buffer_ptr || 0 == m_bind_read_size)
	{
		return PFX_STATUS_ERROR_;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	int index = sscanf(m_bind_read_buffer_ptr,"%d",&read_value);
	if (index  > m_bind_read_size)
	{
		m_bind_read_buffer_ptr = null; 
		m_bind_read_size = 0;
		return PFX_STATUS_ERROR_;
	}
	else
	{
		m_bind_read_buffer_ptr += index;
		m_bind_read_size -= index;
	}
	return PFX_STATUS_OK;
}

pfx_result_t pecker_read_stream_form_memery::read_long(long long &read_value)
{
	if (null == m_bind_read_buffer_ptr || 0 == m_bind_read_size)
	{
		return PFX_STATUS_ERROR_;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	int index = sscanf(m_bind_read_buffer_ptr,"%ld",&read_value);
	if (index  > m_bind_read_size)
	{
		m_bind_read_buffer_ptr = null; 
		m_bind_read_size = 0;
		return PFX_STATUS_ERROR_;
	}
	else
	{
		m_bind_read_buffer_ptr += index;
		m_bind_read_size -= index;
	}
	return PFX_STATUS_OK;
}

pfx_result_t pecker_read_stream_form_memery::read_char(char &read_value)
{
	if (null == m_bind_read_buffer_ptr || 0 == m_bind_read_size)
	{
		return PFX_STATUS_ERROR_;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);

	if (m_bind_read_size > 0)
	{
		read_value = m_bind_read_buffer_ptr[0];
		++m_bind_read_buffer_ptr;
		--m_bind_read_size;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}
	//int index = sscanf(m_bind_read_buffer,"%c",&read_value);

	//if (index  > m_bind_read_size)
	//{
	//	m_bind_read_buffer = null; 
	//	m_bind_read_size = 0;
	//	return P_ERR;
	//}
	//else
	//{
	//	m_bind_read_buffer += index;
	//	m_bind_read_size -= index;
	//}
	return PFX_STATUS_OK;
}

pfx_result_t pecker_read_stream_form_memery::read_float(char &read_value)
{
	if (null == m_bind_read_buffer_ptr || 0 == m_bind_read_size)
	{
		return PFX_STATUS_ERROR_;
	}
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	int index = sscanf(m_bind_read_buffer_ptr,"%f",&read_value);
	if (index > m_bind_read_size)
	{
		m_bind_read_buffer_ptr = null; 
		m_bind_read_size = 0;
		return PFX_STATUS_ERROR_;
	}
	else
	{
		m_bind_read_buffer_ptr += index;
		m_bind_read_size -= index;
	}
	return PFX_STATUS_OK;
}

pfx_result_t pecker_read_stream_form_memery::read_double(char &read_value)
{
	if (null == m_bind_read_buffer_ptr || 0 == m_bind_read_size)
	{
		return PFX_STATUS_ERROR_;
	}

	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	int index = sscanf(m_bind_read_buffer_ptr,"%lf",&read_value);
	if (index > m_bind_read_size)
	{
		m_bind_read_buffer_ptr = null; 
		m_bind_read_size = 0;
		return PFX_STATUS_ERROR_;
	}
	else
	{
		m_bind_read_buffer_ptr += index;
		m_bind_read_size -= index;
	}
	return PFX_STATUS_OK;
}

int pecker_read_stream_form_memery::read_chars(char* read_buffer_ptr,int read_buffer_size)
{
	if (null == m_bind_read_buffer_ptr || 0 == m_bind_read_size)
	{
		return 0;
	}

	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	
	char read_char_value = 0;
	int isubsize = 0;
	int ireadsize = 0;
	for (ireadsize=0;ireadsize<read_buffer_size;++ireadsize)
	{
		if (PFX_STATUS_OK == read_char(read_char_value))
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
			read_buffer_ptr[ireadsize] = read_char_value;
		}
		else
		{
			break;
		}
	}

	return ireadsize;
}


pecker_write_stream_to_memery::pecker_write_stream_to_memery():	m_bind_write_buffer_ptr(null),
																																m_bind_write_size (null)
{

}

pecker_write_stream_to_memery::~pecker_write_stream_to_memery()
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);

	m_bind_write_buffer_ptr = null;
	m_bind_write_size = null;
}

pfx_result_t pecker_write_stream_to_memery::bind_write_buffer( STREAM_BUFFER_t bind_buffer_ptr,pfx_usize_t bind_size)
{
	if (null == bind_buffer_ptr || bind_size <= 0)
	{
		return PFX_STATUS_ERROR_;
	}

	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);

	m_bind_write_buffer_ptr = bind_buffer_ptr;
	m_bind_write_size = bind_size;
	
	return PFX_STATUS_OK;
}

pfx_result_t pecker_write_stream_to_memery::write_integer(int write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	
	char tempstring[5];
	int index = sprintf(tempstring,"%d",write_value);
	if (index < m_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			m_bind_write_buffer_ptr[i] = tempstring[i];
		}
		m_bind_write_buffer_ptr[index] = 0;
		m_bind_write_buffer_ptr+=index;
		m_bind_write_size -= index;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

pfx_result_t pecker_write_stream_to_memery::write_unsigned_integer(unsigned int write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);

	char tempstring[5];
	int index = sprintf(tempstring,"%u",write_value);
	if (index < m_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			m_bind_write_buffer_ptr[i] = tempstring[i];
		}
		m_bind_write_buffer_ptr[index] = 0;
		m_bind_write_buffer_ptr+=index;
		m_bind_write_size -= index;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

pfx_result_t pecker_write_stream_to_memery::write_long(long long write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	char tempstring[9];
	int index = sprintf(tempstring,"%ld",write_value);
	if (index < m_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			m_bind_write_buffer_ptr[i] = tempstring[i];
		}
		m_bind_write_buffer_ptr[index] = 0;
		m_bind_write_buffer_ptr+=index;
		m_bind_write_size -= index;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

pfx_result_t pecker_write_stream_to_memery::write_unsigned_long(unsigned long long write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	char tempstring[9];
	int index = sprintf(tempstring,"%ld",write_value);
	if (index < m_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			m_bind_write_buffer_ptr[i] = tempstring[i];
		}
		m_bind_write_buffer_ptr[index] = 0;
		m_bind_write_buffer_ptr+=index;
		m_bind_write_size -= index;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

pfx_result_t pecker_write_stream_to_memery::write_char(char write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);

	char tempstring[5];
	int index = sprintf(tempstring,"%c",write_value);
	if (index < m_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			m_bind_write_buffer_ptr[i] = tempstring[i];
		}
		m_bind_write_buffer_ptr[index] = 0;
		m_bind_write_buffer_ptr+=index;
		m_bind_write_size -= index;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

pfx_result_t pecker_write_stream_to_memery::write_byte(char write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);


	char tempstring[5];
	int index = sprintf(tempstring,"%02x",write_value);
	if (index < m_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			m_bind_write_buffer_ptr[i] = tempstring[i];
		}
		m_bind_write_buffer_ptr[index] = 0;
		m_bind_write_buffer_ptr+=index;
		m_bind_write_size -= index;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

pfx_result_t pecker_write_stream_to_memery::write_float(char write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);

	char tempstring[5];
	int index = sprintf(tempstring,"%f",write_value);
	if (index < m_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			m_bind_write_buffer_ptr[i] = tempstring[i];
		}
		m_bind_write_buffer_ptr[index] = 0;
		m_bind_write_buffer_ptr+=index;
		m_bind_write_size -= index;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

pfx_result_t pecker_write_stream_to_memery::write_double(char write_value)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);
	char tempstring[5];
	int index = sprintf(tempstring,"%f",write_value);
	if (index < m_bind_write_size)
	{
		for (int i=0;i<index;++i)
		{
			m_bind_write_buffer_ptr[i] = tempstring[i];
		}
		m_bind_write_buffer_ptr[index] = 0;
		m_bind_write_buffer_ptr+=index;
		m_bind_write_size -= index;
		return PFX_STATUS_OK;
	}
	return PFX_STATUS_ERROR_;
}

int pecker_write_stream_to_memery::write_chars(char* write_buffer_ptr,int write_buffer_size)
{
	pecker_critical_lock cs_lock;
	cs_lock.lock(&m_critical_section);

	char write_char_value = 0;

	int iwritesize = 0;
	for (iwritesize=0;iwritesize<write_buffer_size;++iwritesize)
	{
		write_char_value = write_buffer_ptr[iwritesize];
		if (0 == write_char_value)
		{
			--iwritesize;
			break;
		}
		if (PFX_STATUS_OK != write_char(write_char_value))
		{
			break;
		}
	}

	return iwritesize;
}


PECKER_END

