/*
 *  pecker_string_adapter.cpp
 *
 *  Created on: 2013-6-25
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */


#include "pecker_string_adapter.h"
PECKER_BEGIN

HResult string_ascii_to_unicode_adapter::convert(const pecker_char_unicode* P_IN pstr_unicode,nSize nunicode_size,pecker_char_ascii* P_OUT pstr_ascii_buffer,nSize nAscii_buffer_size,nSize &nConvered_ascii_string_size)
{
	if (null == pstr_unicode || 0 >= nunicode_size)
	{
		return P_INVALID_VALUE;
	}
	nConvered_ascii_string_size = wcstombs(null,pstr_unicode,0);

	if (nConvered_ascii_string_size < 0)
	{
		return P_FAIL;
	}

	if (null == pstr_ascii_buffer ||  1 >= nAscii_buffer_size)
	{
		return P_OK;
	}

	nConvered_ascii_string_size += 1 ;
	if (nConvered_ascii_string_size > nAscii_buffer_size)
	{
		nConvered_ascii_string_size = nAscii_buffer_size;
	}

	nConvered_ascii_string_size = wcstombs(pstr_ascii_buffer,pstr_unicode,nConvered_ascii_string_size);

	if (nConvered_ascii_string_size < 0)
	{
		return P_FAIL;
	}
	else
	{
		return P_OK;
	}

}

HResult string_ascii_to_unicode_adapter::convert(const pecker_char_ascii* P_IN pstr_ascii,nSize nAscii_size,pecker_char_unicode* P_OUT pstr_unicode_buffer,nSize nunicode_buffer_size,nSize &nConvered_unicode_string_size)
{
	if (null == pstr_ascii || 0 >= nAscii_size)
	{
		return P_INVALID_VALUE;
	}
	nConvered_unicode_string_size = mbstowcs(null,pstr_ascii,0);

	if (nConvered_unicode_string_size < 0)
	{
		return P_FAIL;
	}

	if (null == pstr_unicode_buffer ||  1 >= nunicode_buffer_size)
	{
		return P_OK;
	}

	nConvered_unicode_string_size += 1;
	if (nConvered_unicode_string_size > nunicode_buffer_size)
	{
		nConvered_unicode_string_size = nunicode_buffer_size;
	}

	nConvered_unicode_string_size = mbstowcs(pstr_unicode_buffer,pstr_ascii,nConvered_unicode_string_size);

	if (nConvered_unicode_string_size < 0)
	{
		return P_FAIL;
	}
	else
	{
		return P_OK;
	}
}

HResult string_ascii_to_unicode_adapter::convert(const pecker_string_ascii& str_ascii,pecker_string_unicode& str_unicode)
{
	if (str_ascii.get_string_length() > 0)
	{
		nSize unicode_strlen = mbstowcs(null,str_ascii.get_data(),0);
		if (unicode_strlen < 0)
		{
			return P_FAIL;
		}
		else
		{
			str_unicode.init(unicode_strlen+1);
			unicode_strlen = mbstowcs(str_unicode.get_data_reference(),str_ascii.get_data(),unicode_strlen+1);
			if (unicode_strlen >= 0)
			{
				str_unicode.resize(unicode_strlen);
				return P_OK;
			}
			else
			{
				return P_FAIL;
			}
		}
	}
	else
	{
		return P_INVALID_VALUE;
	}
}

HResult string_ascii_to_unicode_adapter::convert(const pecker_string_unicode& str_unicode,pecker_string_ascii& str_ascii)
{
	if (str_unicode.get_string_length() > 0)
	{
		nSize ascii_strlen = wcstombs(null,str_unicode.get_data(),0);
		if (ascii_strlen < 0)
		{
			return P_FAIL;
		}
		else
		{
			str_ascii.init(ascii_strlen+1);
			ascii_strlen = wcstombs(str_ascii.get_data_reference(),str_unicode.get_data(),ascii_strlen+1);
			if (ascii_strlen >= 0)
			{
				str_ascii.resize(ascii_strlen);
				return P_OK;
			}
			else
			{
				return P_FAIL;
			}
		}
	}
	else
	{
		return P_INVALID_VALUE;
	}
}

HResult string_ascii_to_unicode_adapter::convert(const pecker_char_ascii* P_IN pstr_ascii,nSize nAscii_size,pecker_string_unicode& str_unicode)
{
	if (null != pstr_ascii && nAscii_size > 0)
	{
		nSize unicode_strlen = mbstowcs(null,pstr_ascii,0);
		if (unicode_strlen < 0)
		{
			return P_FAIL;
		}
		else
		{
			str_unicode.init(unicode_strlen+1);
			unicode_strlen = mbstowcs(str_unicode.get_data_reference(),pstr_ascii,unicode_strlen+1);
			if (unicode_strlen >= 0)
			{
				str_unicode.resize(unicode_strlen);
				return P_OK;
			}
			else
			{
				return P_FAIL;
			}
		}
	}
	else
	{
		return P_INVALID_VALUE;
	}
}

HResult string_ascii_to_unicode_adapter::convert(const pecker_char_unicode* P_IN pstr_unicode,nSize nunicode_size,pecker_string_ascii& str_ascii)
{
	if (null == pstr_unicode && nunicode_size > 0)
	{
		nSize ascii_strlen = wcstombs(null,pstr_unicode,0);
		if (ascii_strlen < 0)
		{
			return P_FAIL;
		}
		else
		{
			str_ascii.init(ascii_strlen+1);
			ascii_strlen = wcstombs(str_ascii.get_data_reference(),pstr_unicode,ascii_strlen+1);
			if (ascii_strlen >= 0)
			{
				str_ascii.resize(ascii_strlen);
				return P_OK;
			}
			else
			{
				return P_FAIL;
			}
		}
	}
	else
	{
		return P_INVALID_VALUE;
	}
}

PECKER_END


