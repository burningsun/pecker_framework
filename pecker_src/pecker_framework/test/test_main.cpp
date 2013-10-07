/*
 * test_main.cpp
 *
 *  Created on: 2013-9-3
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "../pfx_defines.h"
#include "../data/pfx_math.h"
#include "../native/pfx_log.h"

extern int list_test_main();
extern int array_test_main();
extern int arrayblock_test_main();
extern int dynamic_linear_array_test_main();
extern int string_test_main();
extern int bst_test_main();

extern void stream_test_main();
extern int avl_test_main();
extern int rbtree_test_main();

#include <stdio.h>

typedef int (*INPUTFN)(FILE *, const unsigned char *, _locale_t, va_list);
typedef int (*WINPUTFN)(FILE *, const wchar_t *, _locale_t, va_list);

#ifdef _UNICODE
#define TINPUTFN WINPUTFN
#else  /* _UNICODE */
#define TINPUTFN INPUTFN
#endif  /* _UNICODE */

extern "C" int __cdecl _input_l(_Inout_ FILE * _File, _In_z_ __format_string const unsigned char *, _In_opt_ _locale_t _Locale, va_list _ArgList);
extern "C" int __cdecl vscanf (
	INPUTFN inputfn,
	const char *format,
	_locale_t plocinfo,
	va_list arglist
	);


int myscanf(const pfx_char_t* PARAM_IN str_format,...)
{
	va_list args_ptr;
	va_start(args_ptr,str_format);

	scanf (str_format,args_ptr);
	//vfscanf ((FILE*)hfile->m_hfile,str_format,args_ptr);
	//_IO_vfscanf (stdin, format, arg, NULL); 
	//vscanf(_input_l, str_format, NULL, args_ptr);
	va_end(args_ptr);
	return PFX_STATUS_OK;

}



int test_main()
{
	int status = 0;

	//pfx_u64_t value_ = pfx_pow_N(2,61);
	//PECKER_LOG_("%ld\n",value_);
	//value_ = pfx_pow_N(10,6);
	//PECKER_LOG_("%ld\n",value_);
	//value_ = pfx_pow_N(2,3);
	//PECKER_LOG_("%ld\n",value_);
	//value_ = pfx_pow_N(5,4);
	//PECKER_LOG_("%ld\n",value_);
	//value_ = pfx_pow_N(6,21);
	//PECKER_LOG_("%lld\n",value_);


	//stream_test_main();
	//float test_f = 0.0f;
	//int test_i = 0;
	//int test_i2 = 0;
	//const char* pstr = "1000.123,123,1234567890";
	//const char* pformat = "%f,%d,%d,%d";


	//sscanf(pstr,pformat,&test_f,&status,&test_i,&test_i2);
	//scanf (pformat,&status,&test_f,&test_i,&test_i2);
	//myscanf("%d",&status);

	//status = list_test_main();
	//status = array_test_main();
	//status = arrayblock_test_main();
	//status =  dynamic_linear_array_test_main();
	status = string_test_main();
	//status = bst_test_main();
	//status = avl_test_main();
	//status = rbtree_test_main();
	return status;
}