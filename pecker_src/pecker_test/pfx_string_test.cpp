/*
 * pfx_string_test.cpp
 *
 *  Created on: 2014-3-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_cstring_codes.h"
#include "../pecker_framework/data/pfx_cshare_string_codes.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/data/pfx_share_object.h"
#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/data/pfx_string_cmp_codes.h"
USING_PECKER_SDK

typedef pecker_simple_allocator < char_t > alloc_char_t;


void string_cmp_test (const cstring < alloc_char_t >& str1, const cstring< alloc_char_t >& str2)
{
	typedef find_cstrstring_operate < cstring < alloc_char_t > > find_str1_t;
	typedef find_string_operate < char_t > find_str2_t;
	char_t strformat[256];
	int find_res;
	usize__t same_count;
	PECKER_LOG_ ("find_str1_t::same_string(str1, str2)\n");
	find_res = find_str1_t::same_string(str1, str2);
	sprintf_s(strformat, sizeof(strformat), "str=%%.%ds, find=%%.%ds, res = %d",
		str1.get_length(),
		str2.get_length(),
		find_res);
	PECKER_LOG_DIRECT_A (strformat, str1.get_string(), str2.get_string());
	PECKER_LOG_ ("\n");
	find_res = find_str2_t::same_string(str1.get_string(),str1.get_length(),str2.get_string(),str2.get_length());
	PECKER_LOG_ ("res = %d\n",find_res);

	PECKER_LOG_ ("find_str1_t::same_string(str1, str2, same_count)\n");
	find_res = find_str1_t::same_string(str1, str2, same_count);
	sprintf_s(strformat, sizeof(strformat), "str=%%.%ds, find=%%.%ds, res = %d, same_count = %d",
		str1.get_length(),
		str2.get_length(),
		find_res,
		same_count);
	PECKER_LOG_DIRECT_A (strformat, str1.get_string(), str2.get_string());
	PECKER_LOG_ ("\n");
	find_res = find_str2_t::same_string(str1.get_string(),str1.get_length(),str2.get_string(),str2.get_length(),same_count);
	PECKER_LOG_ ("res = %d, same_count=%d\n", find_res, same_count);


	uindex_t index;

	PECKER_LOG_ ("find_str1_t::find_first_string(str1, str2)\n");
	index = find_str1_t::find_first_string(str1, str2);
	sprintf_s(strformat, sizeof(strformat), "str=%%.%ds, find=%%.%ds, index = %d",
		str1.get_length(),
		str2.get_length(),
		index);
	PECKER_LOG_DIRECT_A (strformat, str1.get_string(), str2.get_string());
	PECKER_LOG_ ("\n");
	index = find_str2_t::find_first_string(str1.get_string(),str1.get_length(),str2.get_string(),str2.get_length());
	PECKER_LOG_ ("index = %d\n", index);

	PECKER_LOG_ ("find_str1_t::find_near_string(str1, str2, same_count)\n");
	index = find_str1_t::find_near_string(str1, str2, same_count);
	sprintf_s(strformat, sizeof(strformat), "str=%%.%ds, find=%%.%ds, index = %d, same_count = %d",
		str1.get_length(),
		str2.get_length(),
		index,
		same_count);
	PECKER_LOG_DIRECT_A (strformat, str1.get_string(), str2.get_string());
	PECKER_LOG_ ("\n");
	index = find_str2_t::find_near_string(str1.get_string(),str1.get_length(),str2.get_string(),str2.get_length(),same_count);
	PECKER_LOG_ ("index = %d, same_count=%d\n", index, same_count);
	PECKER_LOG_ ("\n\n\n");
}

result_t string_test ()
{
	//pfx_share_object_base< pecker_simple_allocator < pfx_sint_t > > obj;


	IPfx_string< char_t >* string_ptr1;
	IPfx_string< char_t >* string_ptr2;
	IPfx_string< char_t >* string_ptr3;
	char_t strformat[256];
	string_ptr1 = null;
	string_ptr2 = null;
	const char_t* str;

	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("test pfx_cstring\n");

	cstring < alloc_char_t > cstring1;
	cstring < alloc_char_t > cstring2;
	cstring < alloc_char_t > cstring3;
	cstring < alloc_char_t > cstring_find;
	//
	//string_ptr1 = &cstring1;
	//string_ptr2 = &cstring2;
	//string_ptr3 = &cstring3;

	//string_ptr1->init_string ("hello",strlen ("hello"));
	//string_ptr2->init_string ("world", strlen("world"));
	//string_ptr3->init_string (20);
	//string_ptr3->resize_string (0);
	//string_ptr3->append_string (string_ptr1);
	//string_ptr3->append_string (" ",1);
	//string_ptr3->append_string (string_ptr2);

	//cstring_find.init_string("hello",strlen("hello"));

	//
	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_cmp_test (cstring1, cstring2);
	//string_cmp_test (cstring1, cstring_find);
	//string_cmp_test(cstring3,cstring1);
	//string_cmp_test(cstring3,cstring2);
	//string_cmp_test(cstring3,cstring_find);

	//string_ptr3->garbage_collection ();

	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_ptr3->append_string (" 1234567890",strlen(" 1234567890"));
	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_ptr3->resize_string (20);

	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_ptr3->garbage_collection ();

	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_ptr3->append_string (" 1234567890123456789",strlen(" 1234567890123456789"));
	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_ptr3->resize_string (20);

	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_ptr3->garbage_collection ();

	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_ptr3->clip_string_remain_left (11,string_ptr2);

	//sprintf (strformat,"%%.%ds|%%.%ds",string_ptr3->get_length(),string_ptr2->get_length ());
	//PECKER_LOG_DIRECT_A (strformat,string_ptr3->get_string (),string_ptr2->get_string ());
	//PECKER_LOG_ ("\n");

	//string_ptr3->clip_string_remain_right (5,string_ptr1);

	//sprintf (strformat,"%%.%ds|%%.%ds",string_ptr3->get_length(),string_ptr1->get_length ());
	//PECKER_LOG_DIRECT_A (strformat,string_ptr3->get_string (),string_ptr1->get_string ());
	//PECKER_LOG_ ("\n");

	//string_ptr3->garbage_collection ();

	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//string_ptr3->init_string ("hey!hey!1234567890qwertyuiop",strlen("hey!hey!1234567890qwertyuiop"));
	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	////uindex_t find_index = 0;
	////boolean_t bfind = PFX_BOOL_FALSE;
	////bfind = string_ptr3->find_first_string ("123",3,find_index);
	////PECKER_LOG_DIRECT_A ("%d %d",bfind,find_index);
	////PECKER_LOG_ ("\n");

	////bfind = string_ptr3->find_string (5,"123",3,find_index);
	////PECKER_LOG_DIRECT_A ("%d %d",bfind,find_index);
	////PECKER_LOG_ ("\n");

	////usize__t same_count = 0;
	////bfind = string_ptr3->find_near_string (5,"1235",4,find_index,same_count);
	////PECKER_LOG_DIRECT_A ("%d %d %d",bfind,find_index,same_count);
	////PECKER_LOG_ ("\n");

	//string_ptr3->append_front ("987654321",strlen("987654321"));
	//str = string_ptr3->get_string ();
	//sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	//PECKER_LOG_DIRECT_A (strformat,str);
	//PECKER_LOG_ ("\n");

	//PECKER_LOG_ENDLINE
	//PECKER_LOG_ ("test pfx_cshare_string\n");

	cshare_string < alloc_char_t > csstring1;
	cshare_string < alloc_char_t > csstring2;
	cshare_string < alloc_char_t > csstring3;

	string_ptr1 = &csstring1;
	string_ptr2 = &csstring2;
	string_ptr3 = &csstring3;

	string_ptr1->init_string ("hello",strlen ("hello"));
	string_ptr2->init_string ("world", strlen("world"));
	string_ptr3->init_string (20);
	string_ptr3->resize_string (0);
	string_ptr3->append_string (string_ptr1);
	string_ptr3->append_string (" ",1);
	string_ptr3->append_string (string_ptr2);

	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->append_string (" 1234567890",strlen(" 1234567890"));
	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->resize_string (20);

	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->append_string (" 1234567890123456789",strlen(" 1234567890123456789"));
	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->resize_string (20);

	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->clip_string_remain_left (11,string_ptr2);

	sprintf_s(strformat, sizeof(strformat), "%%.%ds|%%.%ds", string_ptr3->get_length(), string_ptr2->get_length());
	PECKER_LOG_DIRECT_A (strformat,string_ptr3->get_string (),string_ptr2->get_string ());
	PECKER_LOG_ ("\n");

	string_ptr3->clip_string_remain_right (5,string_ptr1);

	sprintf_s(strformat, sizeof(strformat), "%%.%ds|%%.%ds", string_ptr3->get_length(), string_ptr1->get_length());
	PECKER_LOG_DIRECT_A (strformat,string_ptr3->get_string (),string_ptr1->get_string ());
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->init_string ("hey!hey!1234567890qwertyuiop",strlen("hey!hey!1234567890qwertyuiop"));
	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	//find_index = 0;
	//bfind = PFX_BOOL_FALSE;
	//bfind = string_ptr3->find_first_string ("123",3,find_index);
	//PECKER_LOG_DIRECT_A ("%d %d",bfind,find_index);
	//PECKER_LOG_ ("\n");

	//bfind = string_ptr3->find_string (5,"123",3,find_index);
	//PECKER_LOG_DIRECT_A ("%d %d",bfind,find_index);
	//PECKER_LOG_ ("\n");

	//same_count = 0;
	//bfind = string_ptr3->find_near_string (5,"1235",4,find_index,same_count);
	//PECKER_LOG_DIRECT_A ("%d %d %d",bfind,find_index,same_count);
	//PECKER_LOG_ ("\n");

	string_ptr3->append_front ("987654321",strlen("987654321"));
	str = string_ptr3->get_string ();
	sprintf_s(strformat, sizeof(strformat), "%%.%ds", string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	return PFX_STATUS_OK;
}