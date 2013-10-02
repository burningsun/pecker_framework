/*
 * pfx_stream.cpp
 *
 *  Created on: 2013-9-29
 *      Author: 李镇城 (cut / cutxyz)
 */


#include "../pfx_defines.h"
#include "pfx_stream.h"
#include "../data/pfx_math.h"
#include <math.h>



PFX_C_EXTERN_BEGIN

PFX_INLINE_CODE pfx_bool_t check_is_dec_number_a (pfx_char_t input_char)
{
	if (input_char >= '0' && input_char <= '9')
	{
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}

PFX_INLINE_CODE pfx_bool_t check_is_oct_number_a (pfx_char_t input_char)
{
	if (input_char >= '0' && input_char <= '7')
	{
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}

PFX_INLINE_CODE pfx_bool_t check_is_hex_number_a (pfx_char_t input_char)
{
	if ((input_char >= '0' && input_char <= '9')	|| 
		(input_char >= 'a' && input_char <= 'f')		||
		(input_char >= 'A' && input_char <= 'F'))
	{
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}

PFX_INLINE_CODE pfx_sint_t get_char_dec_oct_number_a(pfx_char_t input_char)
{
	return (pfx_sint_t)input_char - (pfx_sint_t)'0';
}

PFX_INLINE_CODE pfx_sint_t get_char_hex_number_a(pfx_char_t input_char)
{
	if (input_char >= '0' && input_char <= '9')
	{
		return (pfx_sint_t)input_char - (pfx_sint_t)'0';
	}
	else if (input_char >= 'a' && input_char <= 'f')
	{
		return (pfx_sint_t)input_char - (pfx_sint_t)'a';
	}
	else if (input_char >= 'A' && input_char <= 'F')
	{
		return (pfx_sint_t)input_char - (pfx_sint_t)'A';
	}
	else
	{
		return 0;
	}
}

PFX_INLINE_CODE pfx_char_t get_hex_char_a(pfx_sint_t input_hex,bool capslock_on)
{
	if (0 <= input_hex && input_hex <= 9)
	{
		return (pfx_char_t)('0' + input_hex);
	}
	else if (9 < input_hex && input_hex < 16)
	{
		if (capslock_on)
		{
			return (pfx_char_t)(input_hex - 10 + 'A');
		}
		else
		{
			return (pfx_char_t)(input_hex - 10 + 'a');
		}
	}
	else
	{
		return '0';
	}
}

PFX_INLINE_CODE pfx_bool_t check_nagtive_number_a(const pfx_char_t*					PARAM_IN			pstring_a,
																								pfx_usize_t															scanf_size,
																								pfx_index_t*							PARAM_INOUT	pstring_a_offset) 
{
	pfx_usize_t i;
	if (scanf_size < 1)
	{
		*pstring_a_offset = 0;
		return pfx_false;
	}
	if ('-' == pstring_a[0])
	{
		if (scanf_size > 1 && ' ' == pstring_a[1])
		{
			*pstring_a_offset = 2;
		}
		else
		{
			*pstring_a_offset = 1;
		}
		return pfx_true;
	}
	else
	{
		return pfx_false;
	}
}

PFX_INLINE_CODE pfx_result_t string_parse_dec_int64 (const pfx_char_t*					PARAM_IN			pstring_a,
																								pfx_usize_t															scanf_size,
																								pfx_s64_t*								PARAM_INOUT	parse_result,
																								pfx_index_t*							PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status;
	pfx_usize_t i;
	pfx_index_t begin_index = 0;
	pfx_bool_t nagtive_flag = pfx_false;

	*parse_result = 0;
	*pstring_a_offset = 0;

	status = PFX_STATUS_OK;

	//if ('-' == pstring_a[0])
	//{
	//	nagtive_flag = pfx_true;
	//}

	//if ('-' == pstring_a[0] || '+' == pstring_a[0])
	//{
	//	++begin_index;
	//	if (' ' == pstring_a[1])
	//	{
	//		++begin_index;
	//	}
	//}

	nagtive_flag = check_nagtive_number_a(pstring_a,scanf_size,&begin_index);
	

	for (i = begin_index;i<scanf_size;++i)
	{
		if (check_is_dec_number_a(pstring_a[i]))
		{
			if (i > begin_index && (i-begin_index) > 19)
			{
				status = PFX_STATUS_OVERRANGE;
				break;
			}

			*parse_result *= 10;
			*parse_result += get_char_dec_oct_number_a(pstring_a[i]);
		}
		else
		{
			break;
		}
	}


	if (0 == i)
	{
		status = PFX_STATUS_FAIL;
	}

	*pstring_a_offset = i;

	if (PFX_STATUS_OK == status)
	{
		if (nagtive_flag)
		{
			*parse_result =  - *parse_result;
		}
		
	}

	return status;
}

PFX_INLINE_CODE pfx_result_t string_parse_oct_int64 (const pfx_char_t*					PARAM_IN			pstring_a,
																								pfx_usize_t															scanf_size,
																								pfx_s64_t*								PARAM_INOUT	parse_result,
																								pfx_index_t*							PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status;
	pfx_usize_t i;
	pfx_index_t begin_index = 0;
	pfx_bool_t nagtive_flag = pfx_false;

	*parse_result = 0;
	*pstring_a_offset = 0;

	status = PFX_STATUS_OK;

	//if ('-' == pstring_a[0])
	//{
	//	nagtive_flag = pfx_true;
	//}

	//if ('-' == pstring_a[0] || '+' == pstring_a[0])
	//{
	//	++begin_index;
	//	if (' ' == pstring_a[1])
	//	{
	//		++begin_index;
	//	}
	//}
	nagtive_flag = check_nagtive_number_a(pstring_a,scanf_size,&begin_index);

	for (i = begin_index;i<scanf_size;++i)
	{
		if (check_is_oct_number_a(pstring_a[i]))
		{
			if ( i > begin_index && (i - begin_index)>21)
			{
				status = PFX_STATUS_OVERRANGE;
				break;
			}
			*parse_result *= 8;
			*parse_result += get_char_dec_oct_number_a(pstring_a[i]);
		}
		else
		{
			break;
		}
	}
	

	if (0 == i)
	{
		status = PFX_STATUS_FAIL;
	}

	*pstring_a_offset = i;

	if (PFX_STATUS_OK == status)
	{
		if (nagtive_flag)
		{
			*parse_result =  - *parse_result;
		}
		
	}

	return status;
}

PFX_INLINE_CODE pfx_result_t string_parse_hex_int64 (const pfx_char_t*					PARAM_IN			pstring_a,
																								pfx_usize_t															scanf_size,
																								pfx_s64_t*								PARAM_INOUT	parse_result,
																								pfx_index_t*							PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status;
	pfx_usize_t i;

	pfx_index_t begin_index = 0;
	pfx_bool_t nagtive_flag = pfx_false;

	*parse_result = 0;
	*pstring_a_offset = 0;

	status = PFX_STATUS_OK;

	//if ('-' == pstring_a[0])
	//{
	//	nagtive_flag = pfx_true;
	//}

	//if ('-' == pstring_a[begin_index] || '+' == pstring_a[begin_index])
	//{
	//	++begin_index;
	//	if (' ' == pstring_a[begin_index])
	//	{
	//		++begin_index;
	//	}
	//}
	nagtive_flag = check_nagtive_number_a(pstring_a,scanf_size,&begin_index);

	if ('0' == pstring_a[begin_index] && 
		('X' == pstring_a[begin_index+1] || 'x' == pstring_a[begin_index+1]))
	{
		begin_index += 2;
	}



	for (i = begin_index;i<scanf_size;++i)
	{
		if (check_is_hex_number_a(pstring_a[i]))
		{
			if (i > begin_index && (i - begin_index) > 7)
			{
				status = PFX_STATUS_OVERRANGE;
				break;
			}
			*parse_result *= 16;
			*parse_result += get_char_hex_number_a(pstring_a[i]);
		}
		else
		{
			break;
		}
	}

	if (begin_index == i)
	{
		status = PFX_STATUS_FAIL;
	}

	*pstring_a_offset = i;

	if (PFX_STATUS_OK == status)
	{
		if (nagtive_flag)
		{
			*parse_result =  - *parse_result;
		}
		
	}

	return status;
}



PFX_INLINE_CODE pfx_result_t string_parse_float_left(const pfx_char_t*					PARAM_IN			pstring_a,
																								pfx_usize_t															scanf_size,
																								const pfx_usize_t												max_pow_size,
																								const pfx_usize_t												max_num_size,
																								pfx_u64_t*								PARAM_INOUT	parse_result,
																								pfx_sint_t*								PARAM_INOUT	pow_size,
																								pfx_index_t*							PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status;
	pfx_usize_t i;
	pfx_sint_t	npow = 0;
	pfx_u64_t	parse_u64 = 0;
	pfx_sint_t	left_count = 0;

	status = PFX_STATUS_OK;
	for (i=0;i<scanf_size;++i)
	{
		if (check_is_dec_number_a(pstring_a[i]))
		{
			if (i < max_num_size)
			{
				parse_u64 *= 10;
				parse_u64 += get_char_dec_oct_number_a(pstring_a[i]);
				++left_count;
			}
			else
			{
				if (max_num_size == i)
				{
					// 四舍五入
					if (get_char_dec_oct_number_a(pstring_a[i]) > 4)
					{
						++parse_u64;
					}
				}

				if ( (pfx_usize_t)INVALID_VALUE == max_pow_size)
				{
					--i;
					break;
				}
				++npow;
				// double 1.7E+/-308
				if ( (max_pow_size - left_count) == npow)
				{
					status = PFX_STATUS_OVERRANGE;
					break;
				};
			}
		}
		else
		{
			break;
		}
	}

	if (0 == i)
	{
		status = PFX_STATUS_FAIL;
	}

	*pstring_a_offset = i;

	if (PFX_STATUS_OK == status)
	{
		*parse_result =  parse_u64;
		*pow_size = npow;	
	}

	return status;
}

PFX_INLINE_CODE pfx_result_t string_parse_float_right(const pfx_char_t*					PARAM_IN			pstring_a,
																								pfx_usize_t															scanf_size,
																								const pfx_usize_t												max_num_size,
																								pfx_u64_t*								PARAM_INOUT	parse_result,
																								pfx_sint_t*								PARAM_INOUT	parse_right_count,
																								pfx_index_t*							PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status;
	pfx_usize_t i;
	pfx_u64_t	npow = 0;
	pfx_u64_t	parse_u64 = 0;
	pfx_sint_t	right_count = 0;

	status = PFX_STATUS_OK;
	for (i=0;i<scanf_size;++i)
	{
		if (check_is_dec_number_a(pstring_a[i]))
		{
			if (0 == max_num_size)
			{
				continue;
			}
			else if (i < max_num_size)
			{
				parse_u64 *= 10;
				parse_u64 += get_char_dec_oct_number_a(pstring_a[i]);
				++right_count;
			}
			else if (max_num_size == i)
			{
				// 四舍五入
				if (get_char_dec_oct_number_a(pstring_a[i]) > 4)
				{
					++parse_u64;
				}
			}
			else
			{
				continue;
			}
		}
		else
		{
			break;
		}
	}

	if (0 == i)
	{
		status = PFX_STATUS_FAIL;
	}

	*pstring_a_offset = i;

	if (PFX_STATUS_OK == status)
	{
		*parse_result =  parse_u64;
		*parse_right_count = right_count;
	}

	return status;
}

PFX_INLINE_CODE pfx_result_t string_parse_float_extern_pow(const pfx_char_t*					PARAM_IN			pstring_a,
																											 pfx_usize_t															scanf_size,
																											 const pfx_usize_t													max_pow_size,
																											 pfx_sint_t*								PARAM_INOUT	parse_result,
																											 pfx_index_t*								PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status;
	pfx_usize_t i;
	pfx_sint_t	parse_s64 = 0;
	pfx_bool_t nagtive_flag = pfx_false;
	status = PFX_STATUS_OK;


	if ('e' != pstring_a[0] && 'E' != pstring_a[0] && 0 == scanf_size)
	{
		status = PFX_STATUS_FIN;
		return status;
	}

	++pstring_a;
	--scanf_size;

	if ('-' != pstring_a[0] &&  '+' != pstring_a[0] && 0 == scanf_size)
	{
		status = PFX_STATUS_ERROR_;
		return status;
	}

	if ('-' == pstring_a[0])
	{
		nagtive_flag = pfx_true;
	}

	++pstring_a;
	--scanf_size;

	for (i=0;i<scanf_size;++i)
	{
		if (check_is_dec_number_a(pstring_a[i]))
		{
			if (parse_s64<=max_pow_size)
			{
				parse_s64 *= 10;
				parse_s64 += get_char_dec_oct_number_a(pstring_a[i]);
			}
			else
			{
				status = PFX_STATUS_OVERRANGE;
				break;
			}
		}
		else
		{
			break;
		}
	}

	if (0 == i)
	{
		status = PFX_STATUS_FAIL;
	}

	*pstring_a_offset = i;

	if (PFX_STATUS_OK == status)
	{
		if (nagtive_flag)
		{
			parse_s64 = -parse_s64;
		}
		*parse_result =  parse_s64;
	}
	return status;
}

PFX_INLINE_CODE pfx_result_t string_parse_float_e(const pfx_char_t*					PARAM_IN			pstring_a,
																							pfx_usize_t															scanf_size,
																							const pfx_usize_t												MAX_POW_SIZE,
																							const pfx_usize_t												MAX_NUM_SIZE,
																							pfx_bool_t*							PARAM_INOUT	pnagtive_flag,
																							pfx_u64_t*								PARAM_INOUT	parse_left,
																							pfx_u64_t*								PARAM_INOUT	parse_right,
																							pfx_sint_t*								PARAM_INOUT	parse_right_count,
																							pfx_sint_t*								PARAM_INOUT	parse_extern_pow,
																							pfx_index_t*							PARAM_INOUT	pstring_a_offset)
{
	pfx_index_t	number_count = MAX_NUM_SIZE;
	pfx_bool_t		nagtive_flag = pfx_false;
	pfx_index_t	begin_index = 0;
	pfx_index_t	temp_index = 0;
	pfx_result_t	status = PFX_STATUS_OK;
	pfx_sint_t		temp_extern_pow = 0;
	pfx_sint_t		left_pow_size = 0;

	nagtive_flag = check_nagtive_number_a(pstring_a,MAX_UNSIGNED_VALUE,&begin_index);

	status = string_parse_float_left(pstring_a+begin_index,MAX_UNSIGNED_VALUE,INVALID_VALUE,MAX_NUM_SIZE,parse_left,&left_pow_size,&temp_index);
	begin_index += temp_index;
	*pstring_a_offset = begin_index;

	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

	number_count -= (temp_index +1);
	if (number_count < 0)
	{
		number_count = 0;
	}

	if ('.' == pstring_a[begin_index])
	{
		++begin_index;
		status = string_parse_float_right(pstring_a+begin_index,MAX_UNSIGNED_VALUE,(pfx_usize_t)number_count,parse_right,parse_right_count,&temp_index);

		begin_index += temp_index;
		*pstring_a_offset = begin_index;

		RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);
	}
	else if (check_is_dec_number_a(pstring_a[begin_index]))
	{
		status = string_parse_float_right(pstring_a+begin_index,MAX_UNSIGNED_VALUE,(pfx_usize_t)number_count,parse_right,parse_right_count,&temp_index);

		begin_index += temp_index;
		*pstring_a_offset = begin_index;

		RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

		number_count -= (temp_index +1);
		if (number_count < 0)
		{
			number_count = 0;
		}
		temp_extern_pow += temp_index;
		if (temp_extern_pow > 0)
		{
			--temp_extern_pow;
		}
		
		if ('.' == pstring_a[begin_index])
		{
			pfx_u64_t	temp_parse_right = 0;
			pfx_sint_t	temp_parse_right_count = 0;
			pfx_index_t	i;
			++begin_index;
			status = string_parse_float_right(pstring_a+begin_index,MAX_UNSIGNED_VALUE,(pfx_usize_t)number_count,&temp_parse_right,&temp_parse_right_count,&temp_index);

			begin_index += temp_index;
			*pstring_a_offset = begin_index;

			RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);
			
			if (0 != parse_right[0])
			{
				for (i=0;i<temp_extern_pow;++i)
				{
					parse_right[0] *= 10;
				}
			}

			*parse_right += temp_parse_right;
			*parse_right_count = temp_parse_right_count + temp_extern_pow;
		}
	}

	if ('e' == pstring_a[begin_index] || 'E' == pstring_a[begin_index])
	{
		status = string_parse_float_extern_pow(pstring_a+begin_index,MAX_UNSIGNED_VALUE,MAX_POW_SIZE,parse_extern_pow,&temp_index);

		begin_index += temp_index;
		*pstring_a_offset = begin_index;

		RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);

	
	}

	*parse_extern_pow += temp_extern_pow;
	return status;
}

PFX_INLINE_CODE pfx_result_t uint_parse_string_dec(pfx_char_t*	PARAM_INOUT		pstring_buffer,
																							  pfx_usize_t									nstring_buffer_max_size,
																							  pfx_usize_t*	PARAM_INOUT		pstring_buffer_size,
																							  pfx_uint_t										integer,
																							  pfx_usize_t									min_printf_size)
{
	pfx_result_t	status;
	pfx_index_t	i;
	pfx_nsize_t		buffer_size = 0;
	pfx_index_t	count = nstring_buffer_max_size;

	if (min_printf_size > nstring_buffer_max_size)
	{
		return PFX_STATUS_MEM_LOW;
	}

	for (i=0;i<count;++i)
	{
		pfx_uint_t integer_temp = integer / 10;
		pstring_buffer[i] = (pfx_char_t)((integer - integer_temp) & 0xFF) + '0';
		integer = integer_temp;

		if (0 == integer)
		{
			break;
		}
	}

	if (0 != integer)
	{
		return PFX_STATUS_MEM_LOW;
	}

	count = i;
	if (i < min_printf_size && min_printf_size != MAX_UNSIGNED_VALUE)
	{
		pfx_index_t copy_1 = min_printf_size - count;
		pfx_index_t offset_ = min_printf_size-1;

		*pstring_buffer_size = min_printf_size;

		for (i=0;i<copy_1;++i)
		{
			pfx_index_t offset = offset_ - i;
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = '0';
		}

		for (;i<min_printf_size;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}
		
	}
	else
	{
		pfx_index_t offset_ = count - 1;
		*pstring_buffer_size = count;
		for (i=0;i<count;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}
	}

	
	return PFX_STATUS_OK;
}

PFX_INLINE_CODE pfx_result_t uint_parse_string_oct(pfx_char_t*	PARAM_INOUT		pstring_buffer,
	pfx_usize_t									nstring_buffer_max_size,
	pfx_usize_t*	PARAM_INOUT		pstring_buffer_size,
	pfx_uint_t										integer,
	pfx_usize_t									min_printf_size)
{
	pfx_result_t	status;
	pfx_index_t	i;
	pfx_nsize_t		buffer_size = 0;
	pfx_index_t	count = nstring_buffer_max_size;

	if (min_printf_size > nstring_buffer_max_size)
	{
		return PFX_STATUS_MEM_LOW;
	}

	for (i=0;i<count;++i)
	{
		pfx_uint_t integer_temp = integer / 8;
		pstring_buffer[i] = (pfx_char_t)((integer - integer_temp) & 0xFF) + '0';
		integer = integer_temp;

		if (0 == integer)
		{
			break;
		}
	}

	if (0 != integer)
	{
		return PFX_STATUS_MEM_LOW;
	}

	count = i;
	if (i < min_printf_size && min_printf_size != MAX_UNSIGNED_VALUE)
	{
		pfx_index_t copy_1 = min_printf_size - count;
		pfx_index_t offset_ = min_printf_size-1;

		*pstring_buffer_size = min_printf_size;

		for (i=0;i<copy_1;++i)
		{
			pfx_index_t offset = offset_ - i;
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = '0';
		}

		for (;i<min_printf_size;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}

	}
	else
	{
		pfx_index_t offset_ = count - 1;
		*pstring_buffer_size = count;
		for (i=0;i<count;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}
	}


	return PFX_STATUS_OK;
}

PFX_INLINE_CODE pfx_result_t uint_parse_string_hex(pfx_char_t*	PARAM_INOUT		pstring_buffer,
	pfx_usize_t										nstring_buffer_max_size,
	pfx_usize_t*	PARAM_INOUT		pstring_buffer_size,
	pfx_uint_t										integer,
	pfx_usize_t										min_printf_size,
	pfx_bool_t										caps_lock)
{
	pfx_result_t	status;
	pfx_index_t	i;
	pfx_nsize_t		buffer_size = 0;
	pfx_index_t	count = nstring_buffer_max_size;

	if (min_printf_size > nstring_buffer_max_size)
	{
		return PFX_STATUS_MEM_LOW;
	}

	for (i=0;i<count;++i)
	{
		pfx_uint_t integer_temp	= integer / 16;
		pfx_uint_t integer_char	=  integer - integer_temp;
		if (integer_char < 10)
		{
			pstring_buffer[i] = (pfx_char_t)(integer_char & 0xFF) + '0';
		}
		else if (caps_lock)
		{
			pstring_buffer[i] = (pfx_char_t)((integer_char-10) & 0xFF) + 'A';
		}
		else
		{
			pstring_buffer[i] = (pfx_char_t)((integer_char-10) & 0xFF) + 'a';
		}
		
		integer = integer_temp;

		if (0 == integer)
		{
			break;
		}
	}

	if (0 != integer)
	{
		return PFX_STATUS_MEM_LOW;
	}

	count = i;
	if (i < min_printf_size && min_printf_size != MAX_UNSIGNED_VALUE)
	{
		pfx_index_t copy_1 = min_printf_size - count;
		pfx_index_t offset_ = min_printf_size-1;

		*pstring_buffer_size = min_printf_size;

		for (i=0;i<copy_1;++i)
		{
			pfx_index_t offset = offset_ - i;
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = '0';
		}

		for (;i<min_printf_size;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}

	}
	else
	{
		pfx_index_t offset_ = count - 1;
		*pstring_buffer_size = count;
		for (i=0;i<count;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}
	}


	return PFX_STATUS_OK;
}

PFX_INLINE_CODE pfx_result_t uint64_parse_string_dec(pfx_char_t*	PARAM_INOUT		pstring_buffer,
	pfx_usize_t									nstring_buffer_max_size,
	pfx_usize_t*	PARAM_INOUT		pstring_buffer_size,
	pfx_u64_t										integer,
	pfx_usize_t									min_printf_size)
{
	pfx_result_t	status;
	pfx_index_t	i;
	pfx_nsize_t		buffer_size = 0;
	pfx_index_t	count = nstring_buffer_max_size;

	if (min_printf_size > nstring_buffer_max_size)
	{
		return PFX_STATUS_MEM_LOW;
	}

	for (i=0;i<count;++i)
	{
		pfx_u64_t integer_temp = integer / 10;
		pstring_buffer[i] = (pfx_char_t)((integer - integer_temp) & 0xFF) + '0';
		integer = integer_temp;

		if (0 == integer)
		{
			break;
		}
	}

	if (0 != integer)
	{
		return PFX_STATUS_MEM_LOW;
	}

	count = i;
	if (i < min_printf_size && min_printf_size != MAX_UNSIGNED_VALUE)
	{
		pfx_index_t copy_1 = min_printf_size - count;
		pfx_index_t offset_ = min_printf_size-1;

		*pstring_buffer_size = min_printf_size;

		for (i=0;i<copy_1;++i)
		{
			pfx_index_t offset = offset_ - i;
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = '0';
		}

		for (;i<min_printf_size;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}

	}
	else
	{
		pfx_index_t offset_ = count - 1;
		*pstring_buffer_size = count;
		for (i=0;i<count;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}
	}


	return PFX_STATUS_OK;
}

PFX_INLINE_CODE pfx_result_t uint64_parse_string_oct(pfx_char_t*	PARAM_INOUT		pstring_buffer,
	pfx_usize_t									nstring_buffer_max_size,
	pfx_usize_t*	PARAM_INOUT		pstring_buffer_size,
	pfx_u64_t										integer,
	pfx_usize_t									min_printf_size)
{
	pfx_result_t	status;
	pfx_index_t	i;
	pfx_nsize_t		buffer_size = 0;
	pfx_index_t	count = nstring_buffer_max_size;

	if (min_printf_size > nstring_buffer_max_size)
	{
		return PFX_STATUS_MEM_LOW;
	}

	for (i=0;i<count;++i)
	{
		pfx_u64_t integer_temp = integer / 8;
		pstring_buffer[i] = (pfx_char_t)((integer - integer_temp) & 0xFF) + '0';
		integer = integer_temp;

		if (0 == integer)
		{
			break;
		}
	}

	if (0 != integer)
	{
		return PFX_STATUS_MEM_LOW;
	}

	count = i;
	if (i < min_printf_size && min_printf_size != MAX_UNSIGNED_VALUE)
	{
		pfx_index_t copy_1 = min_printf_size - count;
		pfx_index_t offset_ = min_printf_size-1;

		*pstring_buffer_size = min_printf_size;

		for (i=0;i<copy_1;++i)
		{
			pfx_index_t offset = offset_ - i;
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = '0';
		}

		for (;i<min_printf_size;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}

	}
	else
	{
		pfx_index_t offset_ = count - 1;
		*pstring_buffer_size = count;
		for (i=0;i<count;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}
	}


	return PFX_STATUS_OK;
}

PFX_INLINE_CODE pfx_result_t uint64_parse_string_hex(pfx_char_t*	PARAM_INOUT		pstring_buffer,
	pfx_usize_t										nstring_buffer_max_size,
	pfx_usize_t*	PARAM_INOUT		pstring_buffer_size,
	pfx_u64_t										integer,
	pfx_usize_t										min_printf_size,
	pfx_bool_t										caps_lock)
{
	pfx_result_t	status;
	pfx_index_t	i;
	pfx_nsize_t		buffer_size = 0;
	pfx_index_t	count = nstring_buffer_max_size;

	if (min_printf_size > nstring_buffer_max_size)
	{
		return PFX_STATUS_MEM_LOW;
	}

	for (i=0;i<count;++i)
	{
		pfx_u64_t integer_temp	= integer / 16;
		pfx_uint_t integer_char	=  integer - integer_temp;
		if (integer_char < 10)
		{
			pstring_buffer[i] = (pfx_char_t)(integer_char & 0xFF) + '0';
		}
		else if (caps_lock)
		{
			pstring_buffer[i] = (pfx_char_t)((integer_char-10) & 0xFF) + 'A';
		}
		else
		{
			pstring_buffer[i] = (pfx_char_t)((integer_char-10) & 0xFF) + 'a';
		}

		integer = integer_temp;

		if (0 == integer)
		{
			break;
		}
	}

	if (0 != integer)
	{
		return PFX_STATUS_MEM_LOW;
	}

	count = i;
	if (i < min_printf_size && min_printf_size != MAX_UNSIGNED_VALUE)
	{
		pfx_index_t copy_1 = min_printf_size - count;
		pfx_index_t offset_ = min_printf_size-1;

		*pstring_buffer_size = min_printf_size;

		for (i=0;i<copy_1;++i)
		{
			pfx_index_t offset = offset_ - i;
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = '0';
		}

		for (;i<min_printf_size;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}

	}
	else
	{
		pfx_index_t offset_ = count - 1;
		*pstring_buffer_size = count;
		for (i=0;i<count;++i)
		{
			pfx_index_t offset = offset_ - i;
			pfx_char_t temp = pstring_buffer[offset];	
			pstring_buffer[offset] = pstring_buffer[i];
			pstring_buffer[i] = temp;
		}
	}


	return PFX_STATUS_OK;
}

pfx_result_t string_a_parse_int	(const pfx_char_t*						PARAM_IN			pstring_a,
														const	pfx_stream_format_t*		PARAM_IN			pformat,
														pfx_sint_t*										PARAM_INOUT	parse_result,
														pfx_index_t*									PARAM_INOUT	pstring_a_offset)
{
	pfx_s64_t parse_int64 = 0;
	pfx_result_t status = PFX_STATUS_INVALID_PARAMS;

	RETURN_INVALID_RESULT((null == pstring_a || null == pformat || null == parse_result || null == pstring_a_offset),PFX_STATUS_INVALID_PARAMS);

	switch (pformat->m_format_type)
	{
	case PFX_DEC_INT_FORMAT:
		status = string_parse_dec_int64(pstring_a,pformat->m_maxwidth, &parse_int64,pstring_a_offset);
		break;
	case PFX_OCT_INT_FORMAT:
		status = string_parse_oct_int64(pstring_a,pformat->m_maxwidth, &parse_int64,pstring_a_offset);
		break;
	case PFX_HEX_INT_FORMAT:
		status = string_parse_hex_int64(pstring_a,pformat->m_maxwidth, &parse_int64,pstring_a_offset);
		break;
	default:
		status = PFX_STATUS_INVALID_ENUM;
		break;
	}

	if (parse_int64 > (pfx_s64_t)((pfx_u32_t)(MAX_UNSIGNED_VALUE)))
	{
		status = PFX_STATUS_OVERRANGE;
		*pstring_a_offset = 0;
	}

	if (PFX_STATUS_OK == status)
	{
		*parse_result = (pfx_sint_t)(parse_int64 & 0xFFFFFFFF);
	}

	return status;
}


pfx_result_t string_a_parse_int64 (const pfx_char_t*						PARAM_IN			pstring_a,
	const	pfx_stream_format_t*		PARAM_IN			pformat,
	pfx_s64_t*									PARAM_INOUT	parse_int64,
	pfx_index_t*								PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status = PFX_STATUS_INVALID_PARAMS;

	RETURN_INVALID_RESULT((null == pstring_a || null == pformat || null == parse_int64 || null == pstring_a_offset),PFX_STATUS_INVALID_PARAMS);

	switch (pformat->m_format_type)
	{
	case PFX_DEC_INT_FORMAT:
		status = string_parse_dec_int64(pstring_a,pformat->m_maxwidth, parse_int64,pstring_a_offset);
		break;
	case PFX_OCT_INT_FORMAT:
		status = string_parse_oct_int64(pstring_a,pformat->m_maxwidth, parse_int64,pstring_a_offset);
		break;
	case PFX_HEX_INT_FORMAT:
		status = string_parse_hex_int64(pstring_a,pformat->m_maxwidth, parse_int64,pstring_a_offset);
		break;
	default:
		status = PFX_STATUS_INVALID_ENUM;
		break;
	}
	return status;
}


pfx_result_t string_a_parse_float (const pfx_char_t*						PARAM_IN			pstring_a,
	const pfx_stream_format_t*	PARAM_IN			pformat,
	pfx_float_t*								PARAM_INOUT	parse_result,
	pfx_index_t*								PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status = PFX_STATUS_INVALID_PARAMS;
	pfx_index_t	begin_index = 0;
	pfx_index_t	temp_index = 0;
	pfx_bool_t		nagtive_flag = pfx_false;

	pfx_u64_t		left_num = 0;
	pfx_u64_t		right_num = 0;
	pfx_sint_t		right_count = 0;
	pfx_sint_t		extern_pow = 0;

	const pfx_sint_t MAX_POW_SIZE = 38;
	const pfx_sint_t MAX_NUM_SIZE = 7;

	RETURN_INVALID_RESULT((null == pstring_a || null == pformat || null == parse_result || null == pstring_a_offset),PFX_STATUS_INVALID_PARAMS);

	status = string_parse_float_e(pstring_a,
		pformat->m_maxwidth,
		MAX_POW_SIZE,
		MAX_NUM_SIZE,
		&nagtive_flag,
		&left_num,
		&right_num,
		&right_count,
		&extern_pow,
		pstring_a_offset);

	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);


	*parse_result = ( (double)left_num  + (double)right_num * pow(10.0,-right_count) ) * pow(10.0,extern_pow);
	return status;
}

pfx_result_t	string_a_parse_double (const pfx_char_t*					PARAM_IN			pstring_a,
	const pfx_stream_format_t*	PARAM_IN			pformat,
	pfx_double_t*							PARAM_INOUT	parse_result,
	pfx_index_t*								PARAM_INOUT	pstring_a_offset)
{
	pfx_result_t status = PFX_STATUS_INVALID_PARAMS;
	pfx_index_t	begin_index = 0;
	pfx_index_t	temp_index = 0;
	pfx_bool_t		nagtive_flag = pfx_false;
	
	pfx_u64_t		left_num = 0;
	pfx_u64_t		right_num = 0;
	pfx_sint_t		right_count = 0;
	pfx_sint_t		extern_pow = 0;
	
	const pfx_sint_t MAX_POW_SIZE = 308;
	const pfx_sint_t MAX_NUM_SIZE = 16;

	RETURN_INVALID_RESULT((null == pstring_a || null == pformat || null == parse_result || null == pstring_a_offset),PFX_STATUS_INVALID_PARAMS);

	status = string_parse_float_e(pstring_a,
														pformat->m_maxwidth,
														MAX_POW_SIZE,
														MAX_NUM_SIZE,
														&nagtive_flag,
														&left_num,
														&right_num,
														&right_count,
														&extern_pow,
														pstring_a_offset);

	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),status);


	*parse_result = ( (double)left_num  + (double)right_num * pow(10.0,-right_count) ) * pow(10.0,extern_pow);
	return status;
}


pfx_usize_t sint_parse_string_a (pfx_sint_t									integer,
	pfx_char_t* PARAM_INOUT		pstring_buffer,
	pfx_usize_t									nstring_buffer_max_size,
	const	pfx_stream_format_t*	PARAM_IN			pformat)
{
	pfx_usize_t return_size = 0;
	pfx_result_t status = PFX_STATUS_OK;
	pfx_usize_t min_printf_size;
	RETURN_INVALID_RESULT((null == pstring_buffer || 0 == nstring_buffer_max_size || null == pformat),return_size);

	if (integer < 0)
	{
		integer = -integer;
		pstring_buffer[0] = '-';
		--nstring_buffer_max_size;
		++pstring_buffer;

		if (pformat->m_minwidth > 0)
		{
			min_printf_size = pformat->m_minwidth-1;
		}
	}
	else
	{
		min_printf_size = pformat->m_minwidth;
	}

	switch (pformat->m_format_type)
	{
	case PFX_DEC_INT_FORMAT:
		status = uint_parse_string_dec(pstring_buffer,nstring_buffer_max_size,&return_size,integer,min_printf_size);
		break;
	case PFX_OCT_INT_FORMAT:
		status = uint_parse_string_oct(pstring_buffer,pformat->m_maxwidth, &return_size,integer,min_printf_size);
		break;
	case PFX_HEX_INT_FORMAT:
	case PFX_PRINT_HEX_0x_INT_FORMAT:
		{
			pfx_bool_t use_caps_lock = pfx_false;
			if (pformat->m_mask & PFX_PRINTF_CAPS_LOCK)
			{
				use_caps_lock = pfx_true;
			}

			if (PFX_PRINT_HEX_0x_INT_FORMAT == pformat->m_format_type)
			{
				if (nstring_buffer_max_size < 2)
				{
					status = PFX_STATUS_MEM_LOW;
				}
				else
				{
					pstring_buffer[0] = '0';
					pstring_buffer[1] = 'x';
					nstring_buffer_max_size -= 2;
					pstring_buffer += 2;

					if (pformat->m_minwidth >= 2)
					{
						min_printf_size = pformat->m_minwidth- 2;
					}
				}

			}

			if (PFX_STATUS_OK == status)
			{
				status = uint_parse_string_hex(pstring_buffer,pformat->m_maxwidth, &return_size,integer,min_printf_size,use_caps_lock);
			}
			
		}		
		break;
	default:
		status = PFX_STATUS_INVALID_ENUM;
		break;
	}

	if (PFX_STATUS_OK != status)
	{
		return_size = 0;
	}
	else if (integer < 0)
	{
		++return_size;
	}

	return return_size;

}

pfx_usize_t uint_parse_string_a (pfx_uint_t									integer,
	pfx_char_t* PARAM_INOUT		pstring_buffer,
	pfx_usize_t									nstring_buffer_max_size,
	const	pfx_stream_format_t*	PARAM_IN			pformat)
{
	pfx_usize_t return_size = 0;
	pfx_result_t status = PFX_STATUS_OK;
	pfx_usize_t min_printf_size;
	RETURN_INVALID_RESULT((null == pstring_buffer || 0 == nstring_buffer_max_size || null == pformat),return_size);

	min_printf_size = pformat->m_minwidth;

	switch (pformat->m_format_type)
	{
	case PFX_DEC_INT_FORMAT:
		status = uint_parse_string_dec(pstring_buffer,nstring_buffer_max_size,&return_size,integer,min_printf_size);
		break;
	case PFX_OCT_INT_FORMAT:
		status = uint_parse_string_oct(pstring_buffer,pformat->m_maxwidth, &return_size,integer,min_printf_size);
		break;
	case PFX_HEX_INT_FORMAT:
	case PFX_PRINT_HEX_0x_INT_FORMAT:
		{
			pfx_bool_t use_caps_lock = pfx_false;
			if (pformat->m_mask & PFX_PRINTF_CAPS_LOCK)
			{
				use_caps_lock = pfx_true;
			}

			if (PFX_PRINT_HEX_0x_INT_FORMAT == pformat->m_format_type)
			{
				if (nstring_buffer_max_size < 2)
				{
					status = PFX_STATUS_MEM_LOW;
				}
				else
				{
					pstring_buffer[0] = '0';
					pstring_buffer[1] = 'x';
					nstring_buffer_max_size -= 2;
					pstring_buffer += 2;

					if (pformat->m_minwidth >= 2)
					{
						min_printf_size = pformat->m_minwidth- 2;
					}
				}

			}

			if (PFX_STATUS_OK == status)
			{
				status = uint_parse_string_hex(pstring_buffer,pformat->m_maxwidth, &return_size,integer,min_printf_size,use_caps_lock);
			}

		}		
		break;
	default:
		status = PFX_STATUS_INVALID_ENUM;
		break;
	}

	if (PFX_STATUS_OK != status)
	{
		return_size = 0;
	}
	else if (integer < 0)
	{
		++return_size;
	}

	return return_size;

}


pfx_usize_t sint64_parse_string_a (pfx_s64_t								integer,
	pfx_char_t* PARAM_INOUT	pstring_buffer,
	pfx_usize_t								nstring_buffer_max_size,
	const	pfx_stream_format_t*	PARAM_IN			pformat)
{
	pfx_usize_t return_size = 0;
	pfx_result_t status = PFX_STATUS_OK;
	pfx_usize_t min_printf_size;
	RETURN_INVALID_RESULT((null == pstring_buffer || 0 == nstring_buffer_max_size || null == pformat),return_size);

	if (integer < 0)
	{
		integer = -integer;
		pstring_buffer[0] = '-';
		--nstring_buffer_max_size;
		++pstring_buffer;

		if (pformat->m_minwidth > 0)
		{
			min_printf_size = pformat->m_minwidth-1;
		}
	}
	else
	{
		min_printf_size = pformat->m_minwidth;
	}

	switch (pformat->m_format_type)
	{
	case PFX_DEC_INT_FORMAT:
		status = uint64_parse_string_dec(pstring_buffer,nstring_buffer_max_size,&return_size,integer,min_printf_size);
		break;
	case PFX_OCT_INT_FORMAT:
		status = uint64_parse_string_oct(pstring_buffer,pformat->m_maxwidth, &return_size,integer,min_printf_size);
		break;
	case PFX_HEX_INT_FORMAT:
	case PFX_PRINT_HEX_0x_INT_FORMAT:
		{
			pfx_bool_t use_caps_lock = pfx_false;
			if (pformat->m_mask & PFX_PRINTF_CAPS_LOCK)
			{
				use_caps_lock = pfx_true;
			}

			if (PFX_PRINT_HEX_0x_INT_FORMAT == pformat->m_format_type)
			{
				if (nstring_buffer_max_size < 2)
				{
					status = PFX_STATUS_MEM_LOW;
				}
				else
				{
					pstring_buffer[0] = '0';
					pstring_buffer[1] = 'x';
					nstring_buffer_max_size -= 2;
					pstring_buffer += 2;

					if (pformat->m_minwidth >= 2)
					{
						min_printf_size = pformat->m_minwidth- 2;
					}
				}

			}

			if (PFX_STATUS_OK == status)
			{
				status = uint64_parse_string_hex(pstring_buffer,pformat->m_maxwidth, &return_size,integer,min_printf_size,use_caps_lock);
			}

		}		
		break;
	default:
		status = PFX_STATUS_INVALID_ENUM;
		break;
	}

	if (PFX_STATUS_OK != status)
	{
		return_size = 0;
	}
	else if (integer < 0)
	{
		++return_size;
	}

	return return_size;
}

pfx_usize_t uint64_parse_string_a (pfx_u64_t								integer,
	pfx_char_t* PARAM_INOUT	pstring_buffer,
	pfx_usize_t								nstring_buffer_max_size,
	const	pfx_stream_format_t*	PARAM_IN			pformat)
{
	pfx_usize_t return_size = 0;
	pfx_result_t status = PFX_STATUS_OK;
	pfx_usize_t min_printf_size;
	RETURN_INVALID_RESULT((null == pstring_buffer || 0 == nstring_buffer_max_size || null == pformat),return_size);

	min_printf_size = pformat->m_minwidth;

	switch (pformat->m_format_type)
	{
	case PFX_DEC_INT_FORMAT:
		status = uint64_parse_string_dec(pstring_buffer,nstring_buffer_max_size,&return_size,integer,min_printf_size);
		break;
	case PFX_OCT_INT_FORMAT:
		status = uint64_parse_string_oct(pstring_buffer,pformat->m_maxwidth, &return_size,integer,min_printf_size);
		break;
	case PFX_HEX_INT_FORMAT:
	case PFX_PRINT_HEX_0x_INT_FORMAT:
		{
			pfx_bool_t use_caps_lock = pfx_false;
			if (pformat->m_mask & PFX_PRINTF_CAPS_LOCK)
			{
				use_caps_lock = pfx_true;
			}

			if (PFX_PRINT_HEX_0x_INT_FORMAT == pformat->m_format_type)
			{
				if (nstring_buffer_max_size < 2)
				{
					status = PFX_STATUS_MEM_LOW;
				}
				else
				{
					pstring_buffer[0] = '0';
					pstring_buffer[1] = 'x';
					nstring_buffer_max_size -= 2;
					pstring_buffer += 2;

					if (pformat->m_minwidth >= 2)
					{
						min_printf_size = pformat->m_minwidth- 2;
					}
				}

			}

			if (PFX_STATUS_OK == status)
			{
				status = uint64_parse_string_hex(pstring_buffer,pformat->m_maxwidth, &return_size,integer,min_printf_size,use_caps_lock);
			}

		}		
		break;
	default:
		status = PFX_STATUS_INVALID_ENUM;
		break;
	}

	if (PFX_STATUS_OK != status)
	{
		return_size = 0;
	}
	else if (integer < 0)
	{
		++return_size;
	}

	return return_size;

}



pfx_usize_t float_parse_string_a  (pfx_float_t								single_real,
	pfx_char_t* PARAM_INOUT	pstring_buffer,
	pfx_usize_t								nstring_buffer_max_size,
	const	pfx_stream_format_t*	PARAM_IN			pformat);

pfx_usize_t double_parse_string_a  (pfx_double_t							double_real,
	pfx_char_t* PARAM_INOUT	pstring_buffer,
	pfx_usize_t								nstring_buffer_max_size,
	const	pfx_stream_format_t*	PARAM_IN			pformat);



pfx_index_t get_input_stream_format_a (const pfx_char_t*			PARAM_IN		pstream_buffer,
	pfx_usize_t													nstream_buffer_size,
	const	pfx_char_t*		PARAM_IN			pformat,
	pfx_stream_format_t*	PARAM_INOUT	pformat_result)
{
	return 0;
}

pfx_index_t get_output_stream_format_a (const pfx_char_t*			PARAM_IN		pstream_buffer,
	pfx_usize_t													nstream_buffer_size,
	const	pfx_char_t*		PARAM_IN			pformat,
	pfx_stream_format_t*	PARAM_INOUT	pformat_result);

pfx_index_t get_input_stream_format_w (const pfx_wchar_t*			PARAM_IN		pstream_buffer,
	pfx_usize_t													nstream_buffer_size,
	const	pfx_char_t*		PARAM_IN			pformat,
	pfx_stream_format_t*	PARAM_INOUT	pformat_result);

pfx_index_t get_output_stream_format_w (const pfx_wchar_t*			PARAM_IN		pstream_buffer,
	pfx_usize_t													nstream_buffer_size,
	const	pfx_char_t*		PARAM_IN			pformat,
	pfx_stream_format_t*	PARAM_INOUT	pformat_result);

pfx_index_t	pfx_stream_sscanf	(const pfx_char_t*		PARAM_IN		pstream_buffer,
	pfx_usize_t											nstream_buffer_size,
	const	pfx_char_t*		PARAM_IN		pformat,
	va_list	args);

pfx_index_t	pfx_stream_ssprintf	(pfx_char_t*					PARAM_INOUT		pstream_buffer,
	pfx_usize_t													nstream_buffer_size,
	const	pfx_char_t*		PARAM_IN				pformat,
	va_list	args);


PFX_C_EXTERN_END