/*
 * pfx_string_test.cpp
 *
 *  Created on: 2014-3-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_cstring_codes.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/data/pfx_share_object.h"
//#include "../pecker_framework/native/pecker_allocator.h"
USING_PECKER_SDK

result_t string_test ()
{
	//pfx_share_object_base< pecker_simple_allocator < pfx_sint_t > > obj;

	IPfx_string< char_t >* string_ptr1;
	IPfx_string< char_t >* string_ptr2;
	IPfx_string< char_t >* string_ptr3;

	string_ptr1 = null;
	string_ptr2 = null;

	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("test pfx_cstring\n");

	cstring < char_t > cstring1;
	cstring < char_t > cstring2;
	cstring < char_t > cstring3;
	
	string_ptr1 = &cstring1;
	string_ptr2 = &cstring2;
	string_ptr3 = &cstring3;

	string_ptr1->init_string ("hello",strlen ("hello"));
	string_ptr2->init_string ("world", strlen("world"));
	string_ptr3->init_string (20);
	string_ptr3->resize_string (0);
	string_ptr3->append_string (string_ptr1);
	string_ptr3->append_string (" ",1);
	string_ptr3->append_string (string_ptr2);
	
	const char_t* str = string_ptr3->get_string ();
	char_t strformat[20];
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->append_string (" 1234567890",strlen(" 1234567890"));
	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->resize_string (20);

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->append_string (" 1234567890123456789",strlen(" 1234567890123456789"));
	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->resize_string (20);

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->clip_string_remain_left (11,string_ptr2);

	sprintf (strformat,"%%.%ds|%%.%ds",string_ptr3->get_length(),string_ptr2->get_length ());
	PECKER_LOG_DIRECT_A (strformat,string_ptr3->get_string (),string_ptr2->get_string ());
	PECKER_LOG_ ("\n");

	string_ptr3->clip_string_remain_right (5,string_ptr1);

	sprintf (strformat,"%%.%ds|%%.%ds",string_ptr3->get_length(),string_ptr1->get_length ());
	PECKER_LOG_DIRECT_A (strformat,string_ptr3->get_string (),string_ptr1->get_string ());
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->init_string ("hey!hey!1234567890qwertyuiop",strlen("hey!hey!1234567890qwertyuiop"));
	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	uindex_t find_index = 0;
	boolean_t bfind = PFX_BOOL_FALSE;
	bfind = string_ptr3->find_first_string ("123",3,find_index);
	PECKER_LOG_DIRECT_A ("%d %d",bfind,find_index);
	PECKER_LOG_ ("\n");

	bfind = string_ptr3->find_string (5,"123",3,find_index);
	PECKER_LOG_DIRECT_A ("%d %d",bfind,find_index);
	PECKER_LOG_ ("\n");

	usize__t same_count = 0;
	bfind = string_ptr3->find_near_string (5,"1235",4,find_index,same_count);
	PECKER_LOG_DIRECT_A ("%d %d %d",bfind,find_index,same_count);
	PECKER_LOG_ ("\n");

	string_ptr3->append_front ("987654321",strlen("987654321"));
	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	PECKER_LOG_ENDLINE
	PECKER_LOG_ ("test pfx_cshare_string\n");

	cshare_string < char_t > csstring1;
	cshare_string < char_t > csstring2;
	cshare_string < char_t > csstring3;

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
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->append_string (" 1234567890",strlen(" 1234567890"));
	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->resize_string (20);

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->append_string (" 1234567890123456789",strlen(" 1234567890123456789"));
	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->resize_string (20);

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->clip_string_remain_left (11,string_ptr2);

	sprintf (strformat,"%%.%ds|%%.%ds",string_ptr3->get_length(),string_ptr2->get_length ());
	PECKER_LOG_DIRECT_A (strformat,string_ptr3->get_string (),string_ptr2->get_string ());
	PECKER_LOG_ ("\n");

	string_ptr3->clip_string_remain_right (5,string_ptr1);

	sprintf (strformat,"%%.%ds|%%.%ds",string_ptr3->get_length(),string_ptr1->get_length ());
	PECKER_LOG_DIRECT_A (strformat,string_ptr3->get_string (),string_ptr1->get_string ());
	PECKER_LOG_ ("\n");

	string_ptr3->garbage_collection ();

	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	string_ptr3->init_string ("hey!hey!1234567890qwertyuiop",strlen("hey!hey!1234567890qwertyuiop"));
	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	find_index = 0;
	bfind = PFX_BOOL_FALSE;
	bfind = string_ptr3->find_first_string ("123",3,find_index);
	PECKER_LOG_DIRECT_A ("%d %d",bfind,find_index);
	PECKER_LOG_ ("\n");

	bfind = string_ptr3->find_string (5,"123",3,find_index);
	PECKER_LOG_DIRECT_A ("%d %d",bfind,find_index);
	PECKER_LOG_ ("\n");

	same_count = 0;
	bfind = string_ptr3->find_near_string (5,"1235",4,find_index,same_count);
	PECKER_LOG_DIRECT_A ("%d %d %d",bfind,find_index,same_count);
	PECKER_LOG_ ("\n");

	string_ptr3->append_front ("987654321",strlen("987654321"));
	str = string_ptr3->get_string ();
	sprintf (strformat,"%%.%ds",string_ptr3->get_length());
	PECKER_LOG_DIRECT_A (strformat,str);
	PECKER_LOG_ ("\n");

	return PFX_STATUS_OK;
}