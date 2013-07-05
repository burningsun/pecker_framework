/*
 *  pecker_string_adapter.h
 *
 *  Created on: 2013-6-25
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_STRING_ADAPTER_H_
#define PECKER_STRING_ADAPTER_H_

#include "pecker_string.h"
PECKER_BEGIN

class string_ascii_to_unicode_adapter
{
public:
	static HResult convert(const pecker_string_ascii& str_ascii,pecker_string_unicode& str_unicode);
	static HResult convert(const pecker_string_unicode& str_unicode,pecker_string_ascii& str_ascii);
	static HResult convert(const pecker_char_ascii* PARAM_IN pstr_ascii,nSize nAscii_size,pecker_char_unicode* PARAM_OUT pstr_unicode_buffer,nSize nunicode_buffer_size,nSize &nConvered_unicode_string_size);
	static HResult convert(const pecker_char_unicode* PARAM_IN pstr_unicode,nSize nunicode_size,pecker_char_ascii* PARAM_OUT pstr_ascii_buffer,nSize nAscii_buffer_size,nSize &nConvered_ascii_string_size);

	static HResult convert(const pecker_char_unicode* PARAM_IN pstr_unicode,nSize nunicode_size,pecker_string_ascii& str_ascii);
	static HResult convert(const pecker_char_ascii* PARAM_IN pstr_ascii,nSize nAscii_size,pecker_string_unicode& str_unicode);
};

PECKER_END

#endif
