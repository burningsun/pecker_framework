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
void print_carray(const array_type& PARAM_IN __array)
{
	typename array_type::const_iterator_t itr;
	typename array_type::const_iterator_t* itr_ptr = __array.begin (itr);

	int new_line = 10;
	PECKER_LOG_("array element =(size=%d,buffersize=%d) \n<", __array.size(), __array.get_buffer_size());
	while (itr_ptr)
	{
		const typename array_type::const_iterator_t::element_t& elem = itr_ptr->reference ();

		if (__array.is_error_element (elem))
		{
			PECKER_LOG_STR("null");
		}
		else
		{
			PECKER_LOG_("%d", elem);
		}

		itr_ptr = itr_ptr->increase ();

		if (itr_ptr)
		{
			PECKER_LOG_STR(", ");
		}

		if (new_line)
		{
			--new_line;
		}
		else
		{
			PECKER_LOG_STR("\n");
			new_line = 10;
		}
	}
	PECKER_LOG_STR(">\n");
}

template < class array_typeA, class array_typeB >
int test_array(array_typeA& __arrayA,
		array_typeB& __arrayB)
{
	int temp_buffer[20] =
	{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120 };
	__arrayA.init (16);
	__arrayA.resize (16);
	PECKER_LOG_STR("resize 16\n");
	__arrayA.set_element_buffers_at (0, temp_buffer, 16);
	print_carray< array_typeA > (__arrayA);
	PECKER_LOG_STR("resize 20\n");
	__arrayA.resize (20);
	PECKER_LOG_STR("resize 16\n");
	__arrayA.resize (16);
	PECKER_LOG_STR("push back 4 items\n");
	for (uindex_t i = 16; i < 20; ++i)
	{
		__arrayA.push_back (temp_buffer[i]);
	}
	print_carray< array_typeA > (__arrayA);
	PECKER_LOG_STR("pop 20 items\n");
	for (uindex_t i = 0; i < 20; ++i)
	{
		__arrayA.pop_back ();
	}
	print_carray< array_typeA > (__arrayA);

	PECKER_LOG_STR("push 20 items\n");
	for (uindex_t i = 0; i < 20; ++i)
	{
		__arrayA.push_back (temp_buffer[i]);
	}
	print_carray< array_typeA > (__arrayA);

	PECKER_LOG_STR("set number10 to number14 items\n");
	__arrayA.set_element_buffers_at (10, temp_buffer, 5);
	print_carray< array_typeA > (__arrayA);

	PECKER_LOG_STR("copy a array\n");
	__arrayA.copy_to (&__arrayB);
	print_carray< array_typeB > (__arrayB);

	PECKER_LOG_STR("set auto step to 20\n");
	__arrayA.set_auto_step (20);
	PECKER_LOG_STR("resize 30\n");
	__arrayA.resize (30);

	PECKER_LOG_STR("set number 0 to number 15 items\n");
	__arrayA.set_element_buffers_at (0, temp_buffer, 16);
	PECKER_LOG_STR("set number 16 to number 19 items\n");
	__arrayA.set_element_buffers_at (16, temp_buffer, 4);
	PECKER_LOG_STR("set number 20 to number 29 items\n");
	__arrayA.set_element_buffers_at (20, temp_buffer, 10);
	print_carray< array_typeA > (__arrayA);

	__arrayA.dispose ();
	__arrayB.dispose ();
	return 0;
}
int array_test_main()
{
	carray< alloc_t > __array;
	carray< alloc_t > __copy_array;

	carray_mbs< alloc_t > __array_mbs;
	carray_mbs< alloc_t > __copy_array_mbs;

	PECKER_LOG_STR("======================\n");
	PECKER_LOG_STR("carray < alloc_t > carray < alloc_t >\n");
	test_array< carray< alloc_t >, carray< alloc_t > > (__array, __copy_array);

	PECKER_LOG_STR("======================\n");
	PECKER_LOG_STR("carray_mbs < alloc_t > carray_mbs < alloc_t >\n");
	test_array< carray_mbs< alloc_t >, carray_mbs< alloc_t > > (__array_mbs, __copy_array_mbs);

	PECKER_LOG_STR("======================\n");
	PECKER_LOG_STR("carray < alloc_t > carray_mbs < alloc_t >\n");
	test_array< carray< alloc_t >, carray_mbs< alloc_t > > (__array, __copy_array_mbs);

	PECKER_LOG_STR("======================\n");
	PECKER_LOG_STR("carray_mbs < alloc_t > carray < alloc_t >\n");
	test_array< carray_mbs< alloc_t >, carray< alloc_t > > (__array_mbs, __copy_array);

	return 0;
}

