﻿/*
 * pfx_array_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/data/pfx_carray.h"



USING_PECKER_SDK

typedef pecker_simple_allocator< int > alloc_t;

template < class array_type >
void print_carray (const array_type& PARAM_IN __array)
{
	array_type::const_iterator_t itr;
	array_type::const_iterator_t* itr_ptr = __array.begin(itr);

	int new_line = 10;
	PECKER_LOG_ ("array element =(size=%d,buffersize=%d) \n<", __array.size(), __array.get_buffer_size());
	while (itr_ptr)
	{
		const array_type::const_iterator_t::element_t& elem = itr_ptr->reference();

		if (__array.is_error_element(elem))
		{
			PECKER_LOG_ ("null");
		}
		else
		{
			PECKER_LOG_ ("%d",elem);
		}

		itr_ptr = itr_ptr->increase ();

		if (itr_ptr)
		{
			PECKER_LOG_ (", ");
		}

		if (new_line)
		{
			--new_line;
		}
		else
		{
			PECKER_LOG_ ("\n");
			new_line = 10;
		}
	}
	PECKER_LOG_ (">\n");
}

template <class array_typeA, class array_typeB >
int test_array (array_typeA& __arrayA, array_typeB& __arrayB)
{
	int temp_buffer [20] = {11,12,13,14,15,16,17,18,19,110,111,112,113,114,115,116,117,118,119,120};
	__arrayA.init (16);
	__arrayA.resize (16);
	PECKER_LOG_("resize 16\n");
	__arrayA.set_element_buffers_at (0, temp_buffer, 16);
	print_carray< array_typeA >(__arrayA);
	PECKER_LOG_("resize 20\n");
	__arrayA.resize (20);
	PECKER_LOG_("resize 16\n");
	__arrayA.resize (16);
	PECKER_LOG_("push back 4 items\n");
	for (uindex_t i=16; i<20; ++i)
	{
		__arrayA.push_back (temp_buffer[i]);
	}
	print_carray< array_typeA >(__arrayA);
	PECKER_LOG_("pop 20 items\n");
	for (uindex_t i=0; i<20; ++i)
	{
		__arrayA.pop_back ();
	}
	print_carray< array_typeA >(__arrayA);

	PECKER_LOG_("push 20 items\n");
	for (uindex_t i=0; i<20; ++i)
	{
		__arrayA.push_back (temp_buffer[i]);
	}
	print_carray< array_typeA >(__arrayA);

	PECKER_LOG_("set number10 to number14 items\n");
	__arrayA.set_element_buffers_at (10, temp_buffer, 5);
	print_carray< array_typeA >(__arrayA);

	PECKER_LOG_("copy a array\n");
	__arrayA.copy_to (&__arrayB);
	print_carray< array_typeB >(__arrayB);

	PECKER_LOG_("set auto step to 20\n");
	__arrayA.set_auto_step (20);
	PECKER_LOG_("resize 30\n");
	__arrayA.resize (30);

	PECKER_LOG_("set number 0 to number 15 items\n");
	__arrayA.set_element_buffers_at (0, temp_buffer, 16);
	PECKER_LOG_("set number 16 to number 19 items\n");
	__arrayA.set_element_buffers_at (16, temp_buffer, 4);
	PECKER_LOG_("set number 20 to number 29 items\n");
	__arrayA.set_element_buffers_at (20, temp_buffer, 10);
	print_carray< array_typeA >(__arrayA);

	__arrayA.dispose ();
	__arrayB.dispose ();
	return 0;
}

int array_test_main ()
{
	carray < alloc_t >	__array;
	carray < alloc_t >	__copy_array;

	carray_mbs< alloc_t > __array_mbs;
	carray_mbs< alloc_t > __copy_array_mbs;

	PECKER_LOG_("======================\n");
	PECKER_LOG_ ("carray < alloc_t > carray < alloc_t >\n");
	test_array< carray < alloc_t >, carray < alloc_t > > (__array, __copy_array);

	PECKER_LOG_("======================\n");
	PECKER_LOG_ ("carray_mbs < alloc_t > carray_mbs < alloc_t >\n");
	test_array< carray_mbs < alloc_t >, carray_mbs < alloc_t > > (__array_mbs, __copy_array_mbs);
	return 0;
}

//int test_array (IPfx_array < int >* PARAM_INOUT array_ptr,
//						IPfx_array < int >* PARAM_INOUT array_copy_ptr)
//{
//	if (!array_ptr || !array_copy_ptr)
//	{
//		PECKER_LOG_ ("PARAMS ERROR\n");
//		return PFX_STATUS_INVALID_PARAMS;
//	}
//	int temp_buffer [20] = {11,12,13,14,15,16,17,18,19,110,111,112,113,114,115,116,117,118,119,120};
//	array_ptr->init (16);
//	array_ptr->set_element_buffers_at (0,temp_buffer,16);
//	print_array(array_ptr);
//	array_ptr->resize (20);
//	array_ptr->resize (16);
//	for (uindex_t i=16; i<20; ++i)
//	{
//		array_ptr->push_back (temp_buffer[i]);
//	}
//	print_array(array_ptr);
//	for (uindex_t i=0; i<20; ++i)
//	{
//		array_ptr->pop_back ();
//	}
//	print_array(array_ptr);
//	
//	for (uindex_t i=0; i<20; ++i)
//	{
//		array_ptr->push_back (temp_buffer[i]);
//	}
//	print_array(array_ptr);
//	array_ptr->set_element_buffers_at (10,array_ptr->get_element_at(0),5);
//	print_array(array_ptr);
//	array_copy_ptr->copy (array_ptr);
//	print_array(array_copy_ptr);
//	array_ptr->set_auto_step (20);
//	array_ptr->resize (30);
//	//array_ptr->set_element_buffers_at (0,array_copy_ptr->get_element_at(0),16);
//	//array_ptr->set_element_buffers_at (16,array_copy_ptr->get_element_at(16),4);
//	array_ptr->set_element_buffers_at (20,array_ptr->get_element_at(0),10);
//	print_array(array_ptr);
//	array_ptr->clear (PFX_BOOL_TRUE);
//	array_copy_ptr->clear (PFX_BOOL_TRUE);
//
//	return PFX_STATUS_OK;
//}
//
//int array_test_main ()
//{
//	array_type < int >::inconsecutive_array_t		incs_array;
//	array_type < int >::inconsecutive_array_t		incs_array_copy;
//	array_type < int >::consecutive_array_t			cs_array;
//	array_type < int >::consecutive_array_t			cs_array_copy;
//
//	array_type < int >::inconsecutive_share_array_t incss_array;
//	array_type < int >::inconsecutive_share_array_t incss_array_copy;
//	array_type < int >::consecutive_share_array_t		css_array;
//	array_type < int >::consecutive_share_array_t		css_array_copy;
//
//	PECKER_LOG_("======================\n");
//	PECKER_LOG_ ("pfx_inconsecutive_array < int > pfx_inconsecutive_array < int >\n");
//	test_array (&incs_array,&incs_array_copy);
//
//	PECKER_LOG_("======================\n");
//	PECKER_LOG_ ("pfx_consecutive_array < int > pfx_consecutive_array < int >\n");
//	test_array (&cs_array,&cs_array_copy);
//
//	PECKER_LOG_("======================\n");
//	PECKER_LOG_ ("pfx_inconsecutive_share_array < int > pfx_inconsecutive_share_array < int >\n");
//	test_array(&incss_array,&incss_array_copy);
//
//	PECKER_LOG_("======================\n");
//	PECKER_LOG_ ("pfx_consecutive_share_array < int > pfx_consecutive_share_array < int >\n");
//	test_array(&css_array,&css_array_copy);
//
//
//
// 	return 0;
//}