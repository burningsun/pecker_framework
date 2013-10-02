/*
 * pfx_stream_test.cpp
 *
 *  Created on: 2013-10-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "../native/pfx_log.h"
#include "../native/pfx_stream.h"

const char test_string[100][100] = { {"0123456789"},
{"0x12345678"},
{"1234567890"},
{"1234567890.123456"},
{"1234567890123456789012345.123456"},
{"12345678.123e+3"},
{"12345678.123e-3"},
{"1234567890123456789012345.123456e+6"},
{"1234567890123456789012345.123456e-5"}};


void stream_test_main()
{
	pfx_stream_format_t stm_format;
	pfx_sint_t		parse_ints[3];
	pfx_s64_t		parse_int64s[3];
	pfx_double_t parse_doubles[6];
	pfx_float_t		parse_floats[6];
	pfx_result_t	status;
	pfx_index_t	index_;
	pfx_index_t	i;

	init_input_format_ex(&stm_format,PFX_DEC_INT_FORMAT,0,MAX_UNSIGNED_VALUE,0);
	status = string_a_parse_int(test_string[0],&stm_format,&parse_ints[0],&index_);
	PECKER_LOG_DIRECT_A("status=%d,index=%d,parse=%d\n",status,index_,parse_ints[0]);

	status = string_a_parse_int64(test_string[0],&stm_format,&parse_int64s[0],&index_);
	PECKER_LOG_DIRECT_A("status=%d,index=%d,parse=%ld\n",status,index_,parse_int64s[0]);

	init_input_format_ex(&stm_format,PFX_HEX_INT_FORMAT,0,MAX_UNSIGNED_VALUE,0);
	status = string_a_parse_int(test_string[1],&stm_format,&parse_ints[1],&index_);
	PECKER_LOG_DIRECT_A("status=%d,index=%d,parse=%X\n",status,index_,parse_ints[1]);

	status = string_a_parse_int64(test_string[1],&stm_format,&parse_int64s[1],&index_);
	PECKER_LOG_DIRECT_A("status=%d,index=%d,parse=%lX\n",status,index_,parse_int64s[1]);

	init_input_format_ex(&stm_format,PFX_OCT_INT_FORMAT,0,MAX_UNSIGNED_VALUE,0);
	status = string_a_parse_int(test_string[2],&stm_format,&parse_ints[2],&index_);
	PECKER_LOG_DIRECT_A("status=%d,index=%d,parse=%o\n",status,index_,parse_ints[2]);

	status = string_a_parse_int64(test_string[2],&stm_format,&parse_int64s[2],&index_);
	PECKER_LOG_DIRECT_A("status=%d,index=%d,parse=%lo\n",status,index_,parse_int64s[2]);

	for (i=3;i<9;++i)
	{
		status = string_a_parse_float(test_string[i],&stm_format,&parse_floats[i-3],&index_);
		PECKER_LOG_DIRECT_A("status=%d,index=%d,parse=%f\n",status,index_,parse_floats[i-3]);

		status = string_a_parse_double(test_string[i],&stm_format,&parse_doubles[i-3],&index_);
		PECKER_LOG_DIRECT_A("status=%d,index=%d,parse=%lf\n",status,index_,parse_doubles[i-3]);
	}
	

}
