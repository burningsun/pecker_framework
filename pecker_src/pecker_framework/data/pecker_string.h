/*
 *  pecker_string.h
 *
 *  Created on: 2012-11-7
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_STRING_H_
#define PECKER_STRING_H_

#include "../native/pecker_allocator.h"
#include "pecker_iterator.h"
#include "../native/pecker_log.h"
#include "../data/pecker_value_compare.h"
PECKER_BEGIN

#define STRING_BOOLEAN_TRUE true
#define  STRING_BOOLEAN_FALSE false

typedef nINDEX string_char_index;
typedef HResult string_result;
typedef bool string_boolean_flag;
typedef int string_size_t;
typedef int string_offerset_t;

template< class char_value_t,class __cmp_t >
inline string_char_index find_first_string_index_(const char_value_t* pstring_chars,string_size_t string_length,
		const char_value_t* pfind_string_chars,string_size_t cmp_string_length)
{
	if (cmp_string_length > string_length || null == pstring_chars || 0 >= string_length || null == pfind_string_chars || 0 >= cmp_string_length)
	{
		return -1;
	}
	string_size_t same_chars_count = 0;
	string_char_index index=0;
	for (;index<string_length;++index)
	{
		int icmp_result = __cmp_t::compare(*(pstring_chars+index),*(pfind_string_chars+same_chars_count));
		if (0 == icmp_result)
		{
			string_char_index itemp_index = index + 1;
			++same_chars_count;
			for (;itemp_index<string_length;++itemp_index)
			{
				icmp_result = __cmp_t::compare(*(pstring_chars+itemp_index),*(pfind_string_chars+same_chars_count));

				if (0 != icmp_result || same_chars_count == cmp_string_length)
				{
					break;
				}
				else
				{
					++same_chars_count;
				}
			}
			if (same_chars_count == cmp_string_length)
			{
				break;
			}
			else
			{
				index = itemp_index;
				same_chars_count = 0;
			}
		}
	}

	if (0 == same_chars_count)
	{
		return -1;
	}
	else
	{
		return index;
	}
}

template< class char_value_t,class __cmp_t>
inline string_size_t find_begin_same_string_size_(const char_value_t* pstring_chars,string_size_t string_length,
		const char_value_t* pcmp_string_chars,string_size_t cmp_string_length)
{
	if (null == pstring_chars || 0 >= string_length || null == pcmp_string_chars || 0 >= cmp_string_length)
	{
		return 0;
	}
	if (string_length > cmp_string_length)
	{
		string_length = cmp_string_length;
	}
	string_char_index index = 0;
	for (; index<string_length;++index)
	{
		int cmp_result = __cmp_t::compare(*(pstring_chars+index),*(pcmp_string_chars+index));
		if (0 != cmp_result)
		{
			break;
		}
		//++nsame_char_count;
	}
	return index; //nsame_char_count;
}

template< class char_value_t,class __cmp_t>
inline int compare_string_(const char_value_t* pstring_chars,string_size_t string_length,
		const char_value_t* pcmp_string_chars,string_size_t cmp_string_length)
{
	
	int ireturn_value;
	int iminlen = string_length;
	if (iminlen > cmp_string_length)
	{
		iminlen = cmp_string_length;
	}
	for (string_char_index index=0;index<iminlen;++index)
	{
		ireturn_value = __cmp_t::compare(*(pstring_chars+index),*(pcmp_string_chars+index));
		if (0 != ireturn_value)
		{
			return ireturn_value;
		}
	}
	return (string_length - cmp_string_length);
}

template< class _string_chars_ >
void print_pecker_string_chars(const _string_chars_& string_)
{
	if (string_.get_string_length() > 0)
	{
		static char logifo[50];
		sprintf(logifo,"%%%d.%ds",string_.get_string_length(),string_.get_string_length());
		PECKER_LOG_(logifo,string_.get_data());
	}
	else
	{
		PECKER_LOG_("null string",0);
	}
}

// 字符串，可共享字符，带小cache加速短字符串的空间分配，默认字符空间16字节
template< class char_value_t,class __cmp_t,class allocate_object_t = pecker_simple_allocator< char_value_t >,const int INTERNAL_BUFFER_SIZE = 16 >
class pecker_share_string_base_t
{
	typedef pecker_share_string_base_t< char_value_t,__cmp_t,allocate_object_t,INTERNAL_BUFFER_SIZE> String_base;

	enum
	{
		_BUFFER_SIZE =  INTERNAL_BUFFER_SIZE / sizeof (char_value_t) < 1 ? 1
		: INTERNAL_BUFFER_SIZE / sizeof (char_value_t)
	};

	typedef union
	{	
		char_value_t _Small_buffer[_BUFFER_SIZE];
		char_value_t *_Large_buffer;
		char _Alias_buffer[_BUFFER_SIZE];	
	} _String_value_buffer;


private:
	_String_value_buffer _M_pstring_data_header;
	char_value_t* _M_pthis_string_data;
	string_size_t _M_string_buffer_size;
	string_size_t _M_string_length;
	String_base* _M_shared_buffer_pre_string;
	String_base* _M_shared_buffer_next_string;
	 
public:
	pecker_share_string_base_t():
	_M_string_buffer_size(_BUFFER_SIZE),
	_M_string_length(0),
	_M_pthis_string_data(_M_pstring_data_header._Small_buffer),
	_M_shared_buffer_pre_string(null),
	_M_shared_buffer_next_string(null)
	{
		_M_pstring_data_header._Large_buffer = null;
	}
	pecker_share_string_base_t(const String_base& other_string):
	_M_string_buffer_size(_BUFFER_SIZE),
	_M_string_length(0),
	_M_pthis_string_data(_M_pstring_data_header._Small_buffer),
	_M_shared_buffer_pre_string(null),
	_M_shared_buffer_next_string(null)
	{
		_M_pstring_data_header._Large_buffer = null;
		copy(other_string);
	}
	pecker_share_string_base_t& operator = (const String_base& other_string)
	{
		copy(other_string);
		return *this;
	}
	~pecker_share_string_base_t()
	{
		clear();
	}
public:
	string_result clear()
	{
		if (_M_string_buffer_size > _BUFFER_SIZE)
		{
			if (null == _M_shared_buffer_next_string && null == _M_shared_buffer_pre_string)
			{
				allocate_object_t::deallocate_objects(_M_pstring_data_header._Large_buffer);
			}

			if (null != _M_shared_buffer_pre_string)
			{
				_M_shared_buffer_pre_string->_M_shared_buffer_next_string = _M_shared_buffer_next_string;
				_M_shared_buffer_pre_string = null;
			}

			if (null != _M_shared_buffer_next_string)
			{
				_M_shared_buffer_next_string->_M_shared_buffer_pre_string = _M_shared_buffer_pre_string;
				_M_shared_buffer_next_string = null;
			}

			_M_string_buffer_size = _BUFFER_SIZE;	
		}

		_M_pthis_string_data = _M_pstring_data_header._Small_buffer;
		_M_string_length = 0;

		return P_OK;

	}
	string_result swap(String_base &other_string)
	{
		if (this == &other_string)
		{
			return P_OK;
		}

		char_value_t* ptmp_header = null;
		
		if (_M_string_buffer_size > _BUFFER_SIZE && other_string._M_string_buffer_size > _BUFFER_SIZE)
		{
			ptmp_header = _M_pstring_data_header._Large_buffer;
			if (ptmp_header != other_string._M_pstring_data_header._Large_buffer)
			{
				_M_pstring_data_header._Large_buffer = other_string._M_pstring_data_header._Large_buffer;
				other_string._M_pstring_data_header._Large_buffer = ptmp_header;
			}

			ptmp_header = _M_pthis_string_data;
			_M_pthis_string_data = other_string._M_pthis_string_data;
			other_string._M_pthis_string_data = ptmp_header;
		}
		else if (_M_string_buffer_size > _BUFFER_SIZE)
		{
			ptmp_header = _M_pstring_data_header._Large_buffer;
			for (string_char_index index =0;index<other_string._M_string_length;++index)
			{
				_M_pstring_data_header._Small_buffer[index] = other_string._M_pthis_string_data[index];
			}
			other_string._M_pstring_data_header._Large_buffer = ptmp_header;
		}
		else if (other_string._M_string_buffer_size > _BUFFER_SIZE)
		{
			ptmp_header = other_string._M_pstring_data_header._Large_buffer;
			for (string_char_index index =0;index< _M_string_length; ++index)
			{
				other_string._M_pstring_data_header._Small_buffer[index] = _M_pthis_string_data[index];
			}
			_M_pstring_data_header._Large_buffer = ptmp_header;
		}
		else
		{
			if (other_string._M_string_length > _M_string_length)
			{
				for (string_char_index index=0; index<_M_string_length; ++index)
				{
					char_value_t tmp_swap_value = _M_pthis_string_data[index];
					_M_pthis_string_data[index] = other_string._M_pthis_string_data[index];
					other_string._M_pthis_string_data[index] = tmp_swap_value;
				}

				for (string_char_index index = _M_string_length;index<other_string._M_string_length;++index)
				{
					_M_pthis_string_data[index] = other_string._M_pthis_string_data[index];
				}
			}
			else
			{
				for (string_char_index index=0; index< other_string._M_string_length; ++index)
				{
					char_value_t tmp_swap_value = _M_pthis_string_data[index];
					_M_pthis_string_data[index] = other_string._M_pthis_string_data[index];
					other_string._M_pthis_string_data[index] = tmp_swap_value;
				}

				for (string_char_index index = other_string._M_string_length;index<_M_string_length;++index)
				{
					 other_string._M_pthis_string_data[index] = _M_pthis_string_data[index];
				}
			}


		}
		
		string_size_t tmp_size = _M_string_buffer_size;
		_M_string_buffer_size = other_string._M_string_buffer_size;
		other_string._M_string_buffer_size = tmp_size;

		tmp_size = _M_string_length;
		_M_string_length = other_string._M_string_length;
		other_string._M_string_length = tmp_size;

		if (_M_string_buffer_size > _BUFFER_SIZE || other_string._M_string_buffer_size > _BUFFER_SIZE)
		{
			if (_M_shared_buffer_next_string == &other_string)
			{
				_M_shared_buffer_next_string = other_string._M_shared_buffer_next_string;
				other_string._M_shared_buffer_next_string = this;
				other_string._M_shared_buffer_pre_string = _M_shared_buffer_pre_string;
				_M_shared_buffer_pre_string = &other_string;
			}
			else if (_M_shared_buffer_pre_string == &other_string)
			{
				_M_shared_buffer_pre_string = other_string._M_shared_buffer_pre_string;
				other_string._M_shared_buffer_pre_string = this;
				other_string._M_shared_buffer_next_string = _M_shared_buffer_next_string;
				_M_shared_buffer_next_string = &other_string;
			}
			else
			{
				String_base* tmp_string = _M_shared_buffer_pre_string;
				_M_shared_buffer_pre_string = other_string._M_shared_buffer_pre_string;
				other_string._M_shared_buffer_pre_string = tmp_string;

				tmp_string = _M_shared_buffer_next_string;
				_M_shared_buffer_next_string = other_string._M_shared_buffer_next_string;
				other_string._M_shared_buffer_next_string = tmp_string;
			}

			if (null != _M_shared_buffer_pre_string)
			{
				_M_shared_buffer_pre_string->_M_shared_buffer_next_string = this;
			}
			if (null != _M_shared_buffer_next_string)
			{
				_M_shared_buffer_next_string->_M_shared_buffer_pre_string = this;
			}
			if (null != other_string._M_shared_buffer_pre_string)
			{
				other_string._M_shared_buffer_pre_string->_M_shared_buffer_next_string = &other_string;
			}
			if (null != other_string._M_shared_buffer_next_string)
			{
				other_string._M_shared_buffer_next_string->_M_shared_buffer_pre_string = &other_string;
			}
		}


		return P_OK;
	}

	string_result init(string_size_t string_length,string_boolean_flag bnew_buffer = STRING_BOOLEAN_FALSE)
	{
		if ( (0 >= string_length) )
		{
			return P_ERR;
		}

		char_value_t* pheaderpointer = null;
		bool bis_release_buffer = (null == _M_shared_buffer_pre_string && null == _M_shared_buffer_next_string);

		if (string_length <= _BUFFER_SIZE)
		{
			if (_M_string_buffer_size > _BUFFER_SIZE)
			{
				if (STRING_BOOLEAN_FALSE == bnew_buffer)
				{
					if (bis_release_buffer)
					{
						pheaderpointer = _M_pstring_data_header._Large_buffer;
					}
					else
					{
						pheaderpointer = _M_pstring_data_header._Small_buffer;
						_M_string_buffer_size = _BUFFER_SIZE;
					}
				}
				else
				{
					if (bis_release_buffer)
					{
						allocate_object_t::deallocate_objects(_M_pstring_data_header._Large_buffer);
					}
					pheaderpointer = _M_pstring_data_header._Small_buffer;
					_M_string_buffer_size = _BUFFER_SIZE;
				}
			}
			else
			{
				pheaderpointer = _M_pstring_data_header._Small_buffer;
				_M_string_buffer_size = _BUFFER_SIZE;
			}
		}
		else
		{
			if ((string_length > _M_string_buffer_size) ||  
				 false == bis_release_buffer || 
				bnew_buffer)
			{
				pheaderpointer = allocate_object_t::allocate_objects(string_length);
				if (null != pheaderpointer)
				{
						if ( bis_release_buffer && _M_string_buffer_size > _BUFFER_SIZE )
						{
							allocate_object_t::deallocate_objects(_M_pstring_data_header._Large_buffer);
						}
						_M_pstring_data_header._Large_buffer = pheaderpointer;
						_M_string_buffer_size = string_length;
				}
			}
			else
			{
				pheaderpointer = _M_pstring_data_header._Large_buffer;
			}
		}
	
		if (null == pheaderpointer)
		{
			return P_ERR;
		}

		if (null != _M_shared_buffer_pre_string)
		{
			_M_shared_buffer_pre_string->_M_shared_buffer_next_string = _M_shared_buffer_next_string;
			_M_shared_buffer_pre_string = null;
		}

		if (null != _M_shared_buffer_next_string)
		{
			_M_shared_buffer_next_string->_M_shared_buffer_pre_string = _M_shared_buffer_pre_string;
			_M_shared_buffer_next_string = null;
		}

		_M_pthis_string_data = pheaderpointer;
		_M_string_length = 0;//string_length;

		return P_OK;
	}

	string_result init(const char_value_t* pstring_chars, string_size_t string_length,string_boolean_flag bnew_buffer = STRING_BOOLEAN_FALSE)
	{
		if ( (null == pstring_chars && 0 >= string_length) )
		{
			return P_ERR;
		}

		string_result init_result = init(string_length,bnew_buffer);
		if (P_OK != init_result)
		{
			return init_result;
		}

		_M_string_length = string_length;
		for (string_char_index index = 0; index < string_length; ++index)
		{
			*(_M_pthis_string_data+index) = *(pstring_chars + index);
		}

		return P_OK;
	}
	string_result copy(const String_base& other)
	{
		if (this != &other)
		{
			return init(other.get_data(),other.get_string_length(),STRING_BOOLEAN_FALSE);
		}
		return P_OK;
	}
	string_result get_share_buffer_sub_string(String_base& reference_sub_string,string_offerset_t ioffset,string_size_t sub_string_length = -1)
	{
		if ( (ioffset >= _M_string_length) || (ioffset < 0) || (this == &reference_sub_string) )
		{
			return P_FAIL;
		}
		
		if (ioffset < 0)
		{
			ioffset = 0;
		}

		if ((sub_string_length < 0) || (sub_string_length + ioffset > _M_string_length))
		{
			sub_string_length = _M_string_length - ioffset;
		}

		if (_M_string_buffer_size > _BUFFER_SIZE)
		{
			reference_sub_string.clear();
			reference_sub_string._M_pstring_data_header._Large_buffer = _M_pstring_data_header._Large_buffer;
			reference_sub_string._M_string_buffer_size = _M_string_buffer_size;
			reference_sub_string._M_pthis_string_data = ioffset + _M_pthis_string_data;
			reference_sub_string._M_string_length = sub_string_length;
			reference_sub_string._M_shared_buffer_pre_string = this;
			reference_sub_string._M_shared_buffer_next_string = _M_shared_buffer_next_string;

			if (null != _M_shared_buffer_next_string)
			{
				_M_shared_buffer_next_string->_M_shared_buffer_pre_string = &reference_sub_string;
			}
			_M_shared_buffer_next_string = &reference_sub_string;

			return P_OK;
		}
		else
		{
			return reference_sub_string.init(ioffset + _M_pthis_string_data,sub_string_length,STRING_BOOLEAN_FALSE);
		}
	

		
	}
	string_result get_sub_string(String_base& sub_string,string_offerset_t ioffset,string_size_t sub_string_length = -1)
	{
		if (ioffset >= _M_string_length || ioffset < 0 || this == &sub_string)
		{
			return P_FAIL;
		}
		if (ioffset < 0)
		{
			ioffset = 0;
		}
		if ((sub_string_length < 0) || (sub_string_length + ioffset > _M_string_length))
		{
			sub_string_length = _M_string_length - ioffset;
		}
		return sub_string.init((_M_pthis_string_data+ioffset),sub_string_length,STRING_BOOLEAN_FALSE);
	}
	inline string_result set_at(string_char_index index, const char_value_t& char_value, string_boolean_flag bforce_set_all_reference = STRING_BOOLEAN_FALSE)
	{
		if (index >= _M_string_length)
		{
			return P_ERR;
		}

		if ((null == _M_shared_buffer_next_string && null == _M_shared_buffer_pre_string)||
			(bforce_set_all_reference && _M_string_buffer_size > _BUFFER_SIZE))
		{
			_M_pthis_string_data[index] = char_value;
			return P_OK;
		}
		else
		{
			if (index < _M_string_length)
			{
				_M_pthis_string_data[index] = char_value;
				return P_OK;
			}
			else
			{
				return P_ERR;
			}
		}
	}
	inline const char_value_t* get_at(string_char_index index) const
	{
		if (index >= 0 && index < _M_string_length)
		{
			return (_M_pthis_string_data + index);
		}
		return null;
	}
	string_result append_string(const char_value_t* pstring_chars, string_size_t string_length)
	{
		if ( (null == pstring_chars && 0 >= string_length) )
		{
			return P_OK;
		}

		string_size_t new_string_length = string_length + _M_string_length;
		char_value_t* pheaderpointer = null;
		bool bis_release_buffer = (null == _M_shared_buffer_pre_string && null == _M_shared_buffer_next_string);

		if (new_string_length <= _BUFFER_SIZE)
		{
			if (_M_string_buffer_size > _BUFFER_SIZE)
			{
					if (!bis_release_buffer)
					{
						for (string_char_index index = 0;index<_M_string_length;++index)
						{
							_M_pstring_data_header._Small_buffer[index] = *(_M_pthis_string_data + index);
						}
						_M_pthis_string_data =  _M_pstring_data_header._Small_buffer;
						_M_string_buffer_size = _BUFFER_SIZE;
					}
			}
			else
			{
				if (_M_pthis_string_data - _M_pstring_data_header._Small_buffer + new_string_length > _BUFFER_SIZE)
				{
					for (string_char_index index = 0;index<_M_string_length;++index)
					{
						_M_pstring_data_header._Small_buffer[index] = *(_M_pthis_string_data + index);
					}
					_M_pthis_string_data =  _M_pstring_data_header._Small_buffer;
					_M_string_buffer_size = _BUFFER_SIZE;
				}
			}
		}
		else
		{
			if ((new_string_length > _M_string_buffer_size) ||  
				false == bis_release_buffer )
			{
				pheaderpointer = allocate_object_t::allocate_objects(new_string_length);
				if (null != pheaderpointer)
				{
					for (string_char_index index = 0;index<_M_string_length;++index)
					{
						*(pheaderpointer + index) = *(_M_pthis_string_data + index);
					}

					if ( bis_release_buffer && _M_string_buffer_size > _BUFFER_SIZE )
					{
						allocate_object_t::deallocate_objects(_M_pstring_data_header._Large_buffer);
					}

					_M_pstring_data_header._Large_buffer = pheaderpointer;
					_M_string_buffer_size = new_string_length;
				}
				else
				{
					return P_ERR;
				}
			}
		}


		if (null != _M_shared_buffer_pre_string)
		{
			_M_shared_buffer_pre_string->_M_shared_buffer_next_string = _M_shared_buffer_next_string;
			_M_shared_buffer_pre_string = null;
		}

		if (null != _M_shared_buffer_next_string)
		{
			_M_shared_buffer_next_string->_M_shared_buffer_pre_string = _M_shared_buffer_pre_string;
			_M_shared_buffer_next_string = null;
		}

		pheaderpointer = _M_pthis_string_data +  _M_string_length;

		for (string_char_index index = 0 ;index<string_length; ++index)
		{
			*(pheaderpointer + index) = *(pstring_chars + index);
		}
		_M_string_length = new_string_length;

		return P_OK;


	}
	string_result append_string(const String_base& otherstring)
	{
		return append_string(otherstring.get_data(),otherstring.get_string_length());
	}
	string_char_index find_first_string_index(const char_value_t* pstring_chars, string_size_t string_length) const
	{
		if ( (string_length > _M_string_length) ||
				(null == pstring_chars) ||
				(0 >= string_length))
		{
			return -1;
		}

		return find_first_string_index_<char_value_t,__cmp_t>(_M_pthis_string_data,_M_string_length,pstring_chars,string_length);

	}
	string_char_index find_first_string_index(const String_base& sub_string) const
	{
		if (this == &sub_string)
		{
			return 0;
		}
		else
		{
			return find_first_string_index_<char_value_t,__cmp_t>( _M_pthis_string_data, _M_string_length,sub_string.get_data(),sub_string.get_string_length());
		}
	}
	string_size_t find_begin_same_string_size(const char_value_t* pstring_chars, string_size_t string_length,string_char_index string_cmp_index = 0) const
	{
		if (string_cmp_index >= _M_string_length)
		{
			return -1;
		}
		return  find_begin_same_string_size_<char_value_t,__cmp_t>((_M_pthis_string_data+string_cmp_index),(_M_string_length-string_cmp_index),pstring_chars,string_length);
	}
	string_size_t find_begin_same_string_size(const String_base& sub_string,string_char_index string_cmp_index = 0) const
	{
		if (string_cmp_index >= _M_string_length)
		{
			return -1;
		}
		return  find_begin_same_string_size_<char_value_t,__cmp_t>((_M_pthis_string_data+string_cmp_index),(_M_string_length-string_cmp_index),sub_string.get_data(),sub_string.get_string_length());
	}
	string_result clip_string_in_share_buffer_left_part(String_base& new_string,string_char_index nclip_index)
	{
		if (nclip_index >= _M_string_length)
		{
			return P_ERR;
		}
		string_result sub_string_reslut = get_share_buffer_sub_string(new_string,nclip_index);
		if (P_OK == sub_string_reslut)
		{
			_M_string_length = nclip_index;
		}

		return sub_string_reslut;

	}

	string_result clip_string_in_share_buffer_right_part(String_base& new_string,string_char_index nclip_index)
	{
		if (nclip_index >= _M_string_length)
		{
			return P_ERR;
		}
		string_result sub_string_reslut = get_share_buffer_sub_string(new_string,0,nclip_index);
		if (P_OK == sub_string_reslut)
		{
			_M_string_length -= nclip_index;
			_M_pthis_string_data += nclip_index;
		}

		return sub_string_reslut;

	}

	string_result clip_string_left_part(String_base& new_string,string_char_index nclip_index)
	{
		if (nclip_index >= _M_string_length)
		{
			return P_ERR;
		}
		string_result sub_string_reslut = get_sub_string(new_string,nclip_index);
		if (P_OK == sub_string_reslut)
		{
			_M_string_length = nclip_index;
		}

		return sub_string_reslut;

	}
	string_result clip_string_right_part(String_base& new_string,string_char_index nclip_index)
	{
		if (nclip_index >= _M_string_length)
		{
			return P_ERR;
		}
		string_result sub_string_reslut = get_sub_string(new_string,0,nclip_index);
		if (P_OK == sub_string_reslut)
		{
			_M_string_length -= nclip_index;
			_M_pthis_string_data += nclip_index;
		}

		return sub_string_reslut;

	}

	inline const char_value_t* get_buffer() const
	{
		return _M_pstring_data_header;
	}
	inline string_size_t get_buffer_size() const
	{
		return _M_string_buffer_size;
	}
	inline const char_value_t* get_data() const
	{
		return _M_pthis_string_data;
	}
	inline string_size_t get_string_length() const
	{
		return _M_string_length;
	}
	inline int compare(const char_value_t* pstring_chars,string_size_t string_length) const
	{
		return  compare_string_< char_value_t , __cmp_t >(_M_pthis_string_data,_M_string_length,pstring_chars,string_length);
	}
	inline int compare(const String_base& other) const
	{
		if (this == &other)
		{
			return 0;
		}
		return compare_string_< char_value_t , __cmp_t >(_M_pthis_string_data,_M_string_length,other.get_data(),other.get_string_length());
	}

	inline int compare_same_chars(const String_base& other,string_size_t & begin_same_char_count) const
	{
		if (this == &other)
		{
			begin_same_char_count = _M_string_length;
			return 0;
		}
		const char_value_t* pstring_chars = _M_pthis_string_data;
		const char_value_t* pcmp_string_chars = other.get_data();
		string_size_t string_min = other.get_string_length();
		int cmp_result = _M_string_length - string_min;
		if (string_min > _M_string_length)
		{
			string_min = _M_string_length;
		}
		string_char_index index = 0;
		for (; index<string_min;++index)
		{
			cmp_result = __cmp_t::compare(*(pstring_chars+index),*(pcmp_string_chars+index));
			if (0 != cmp_result)
			{
				break;
			}
		}
		begin_same_char_count = index;
		return cmp_result;
	}

	inline int compare_same_chars(const char_value_t* pcmp_string_chars,
			string_size_t string_length,string_size_t & begin_same_char_count) const
	{
		const char_value_t* pstring_chars = _M_pthis_string_data;
		int cmp_result = _M_string_length - string_length;
		int index = 0;

		if (cmp_result < 0)
		{
			string_length = _M_string_length;
		}

		for (; index<string_length;++index)
		{
			cmp_result = __cmp_t::compare(*(pstring_chars+index),*(pcmp_string_chars+index));
			if (0 != cmp_result)
			{
				break;
			}
		}

		begin_same_char_count = index;
		return cmp_result;
	}

	static inline string_result merge_neighbour_sub_string(String_base& sub_string1,String_base& sub_string2,String_base& new_string)
	{

		if ( 
			(sub_string1._M_string_buffer_size <= _BUFFER_SIZE || sub_string2._M_string_buffer_size <= _BUFFER_SIZE) ||
			(sub_string1._M_pstring_data_header._Large_buffer != sub_string2._M_pstring_data_header._Large_buffer) ||
			(( (sub_string1._M_pthis_string_data+sub_string1._M_string_length) != sub_string2._M_pthis_string_data) &&
			( (sub_string2._M_pthis_string_data+sub_string2._M_string_length) != sub_string1._M_pthis_string_data)) ||
			(null == sub_string1._M_shared_buffer_pre_string && null == sub_string1._M_shared_buffer_next_string) ||
			(null == sub_string2._M_shared_buffer_pre_string && null == sub_string2._M_shared_buffer_next_string) )
		{
			string_result str_result = P_ERR;

			if (&sub_string1 == &new_string)
			{
				str_result = new_string.append_string(sub_string2);
			}
			else if (&sub_string2 == &new_string)
			{
				string_size_t str_size = sub_string2._M_string_length;
				str_result = new_string.append_string(sub_string1);
				if (P_OK == str_result)
				{
					char_value_t* pheader = new_string._M_pthis_string_data + sub_string1._M_string_length;
					for (string_char_index index = 0;index<str_size; ++index)
					{
						pheader[index] = new_string._M_pthis_string_data[index];
					}
					for (string_char_index index =0; index < sub_string1._M_string_length; ++index)
					{
						new_string._M_pthis_string_data[index] = sub_string1._M_pthis_string_data[index];
					}
				}
			}
			else
			{
				str_result = new_string.init(sub_string1.get_string_length() + sub_string2.get_string_length());
				if (P_OK == str_result)
				{
					char_value_t* pheader = new_string._M_pthis_string_data;
					for (string_char_index index = 0;index<sub_string1._M_string_length; ++index)
					{
						pheader[index] = sub_string1._M_pthis_string_data[index];
					}
					pheader += sub_string1._M_string_length;
					for (string_char_index index = 0; index <sub_string2._M_string_length;++index)
					{
						pheader[index] = sub_string2._M_pthis_string_data[index];
					}
				}
			}
			return str_result;
		}
		new_string._M_pstring_data_header._Large_buffer = sub_string1._M_pstring_data_header._Large_buffer;
		new_string._M_string_length = sub_string1._M_string_length + sub_string2._M_string_length;
		new_string._M_string_buffer_size = sub_string1._M_string_buffer_size;

		String_base* psub_string1 = (String_base*)(&sub_string1);
		String_base* psub_string1_next = psub_string1->_M_shared_buffer_next_string;

		new_string._M_shared_buffer_pre_string = psub_string1;
		new_string._M_shared_buffer_next_string = psub_string1->_M_shared_buffer_next_string;
		psub_string1->_M_shared_buffer_next_string = &new_string;
		if (psub_string1_next)
		{
			psub_string1_next->_M_shared_buffer_pre_string = &new_string;
		}

		if (sub_string1._M_pthis_string_data < sub_string2._M_pthis_string_data)
		{
			new_string._M_pthis_string_data = sub_string1._M_pthis_string_data;
		}
		else
		{
			new_string._M_pthis_string_data = sub_string2._M_pthis_string_data;
		}

		return P_OK;
	}

};

//
typedef pecker_share_string_base_t< char,pecker_value_compare< char > > pecker_string;

PECKER_END

#endif
