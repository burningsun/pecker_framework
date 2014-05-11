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
result_t pecker_read_stream_form_memery::bind_read_buffer(CONST_STREAM_BUFFER_t bind_buffer_ptr,usize__t bind_size)
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

result_t pecker_read_stream_form_memery::read_integer (sint_t &read_value)
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

result_t pecker_read_stream_form_memery::read_long (s64_t &read_value)
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

result_t pecker_read_stream_form_memery::read_char (char_t &read_value)
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

result_t pecker_read_stream_form_memery::read_float (float_t &read_value)
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

result_t pecker_read_stream_form_memery::read_double (double_t &read_value)
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

usize__t pecker_read_stream_form_memery::read_chars (char_t* read_buffer_ptr,usize__t read_buffer_size)
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

result_t pecker_write_stream_to_memery::bind_write_buffer( STREAM_BUFFER_t bind_buffer_ptr,usize__t bind_size)
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

result_t pecker_write_stream_to_memery::write_integer (sint_t write_value)
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

result_t pecker_write_stream_to_memery::write_unsigned_integer (uint_t write_value)
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

result_t pecker_write_stream_to_memery::write_long (s64_t write_value)
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

result_t pecker_write_stream_to_memery::write_unsigned_long (u64_t write_value)
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

result_t pecker_write_stream_to_memery::write_char (char_t write_value)
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

result_t pecker_write_stream_to_memery::write_byte (byte_t write_value)
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

result_t pecker_write_stream_to_memery::write_float (float_t write_value)
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

result_t pecker_write_stream_to_memery::write_double (double_t write_value)
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

usize__t pecker_write_stream_to_memery::write_chars (char_t* write_buffer_ptr,usize__t write_buffer_size)
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

