/*
 * pfx_array_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_dynamic_array.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"

USING_PECKER_SDK

void print_array (const IPfx_array < int >* PARAM_IN array_ptr)
{
	//class pfx_const_array_iterator : public IPfx_array_iterator < element_ >
	pfx_const_array_iterator < int > itr;
	IPfx_array_iterator < int >* itr_ptr = null;
	itr_ptr = array_ptr->begin (&itr);

	int new_line = 10;
	PECKER_LOG_ ("array element =(size=%d,buffersize=%d) \n<",array_ptr->size(),array_ptr->get_buffer_size());
	while (itr_ptr)
	{
		const int* elem_ptr = itr_ptr->get_current_element();

		if (!elem_ptr)
		{
			PECKER_LOG_ ("null");
		}
		else
		{
			PECKER_LOG_ ("%d",*elem_ptr);
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
int test_array (IPfx_array < int >* PARAM_INOUT array_ptr,
						IPfx_array < int >* PARAM_INOUT array_copy_ptr)
{
	if (!array_ptr || !array_copy_ptr)
	{
		PECKER_LOG_ ("PARAMS ERROR\n");
		return PFX_STATUS_INVALID_PARAMS;
	}
	int temp_buffer [20] = {11,12,13,14,15,16,17,18,19,110,111,112,113,114,115,116,117,118,119,120};
	array_ptr->init (16);
	array_ptr->set_element_buffers_at (0,temp_buffer,16);
	print_array(array_ptr);
	array_ptr->resize (20);
	array_ptr->resize (16);
	for (pfx_uindex_t i=16; i<20; ++i)
	{
		array_ptr->push_back (temp_buffer[i]);
	}
	print_array(array_ptr);
	for (pfx_uindex_t i=0; i<20; ++i)
	{
		array_ptr->pop_back ();
	}
	print_array(array_ptr);
	
	for (pfx_uindex_t i=0; i<20; ++i)
	{
		array_ptr->push_back (temp_buffer[i]);
	}
	print_array(array_ptr);
	array_ptr->set_element_buffers_at (10,array_ptr->get_element_at(0),5);
	print_array(array_ptr);
	array_copy_ptr->copy (array_ptr);
	print_array(array_copy_ptr);
	array_ptr->set_auto_step (20);
	array_ptr->resize (30);
	//array_ptr->set_element_buffers_at (0,array_copy_ptr->get_element_at(0),16);
	//array_ptr->set_element_buffers_at (16,array_copy_ptr->get_element_at(16),4);
	array_ptr->set_element_buffers_at (20,array_ptr->get_element_at(0),10);
	print_array(array_ptr);
	array_ptr->clear (PFX_BOOL_TRUE);
	array_copy_ptr->clear (PFX_BOOL_TRUE);

	return PFX_STATUS_OK;
}

int array_test_main ()
{
	array_type < int >::inconsecutive_array_t		incs_array;
	array_type < int >::inconsecutive_array_t		incs_array_copy;
	array_type < int >::consecutive_array_t			cs_array;
	array_type < int >::consecutive_array_t			cs_array_copy;

	array_type < int >::inconsecutive_share_array_t incss_array;
	array_type < int >::inconsecutive_share_array_t incss_array_copy;
	array_type < int >::consecutive_share_array_t		css_array;
	array_type < int >::consecutive_share_array_t		css_array_copy;

	PECKER_LOG_("======================\n");
	PECKER_LOG_ ("pfx_inconsecutive_array < int > pfx_inconsecutive_array < int >\n");
	test_array (&incs_array,&incs_array_copy);

	PECKER_LOG_("======================\n");
	PECKER_LOG_ ("pfx_consecutive_array < int > pfx_consecutive_array < int >\n");
	test_array (&cs_array,&cs_array_copy);

	PECKER_LOG_("======================\n");
	PECKER_LOG_ ("pfx_inconsecutive_share_array < int > pfx_inconsecutive_share_array < int >\n");
	test_array(&incss_array,&incss_array_copy);

	PECKER_LOG_("======================\n");
	PECKER_LOG_ ("pfx_consecutive_share_array < int > pfx_consecutive_share_array < int >\n");
	test_array(&css_array,&css_array_copy);



 	return 0;
}