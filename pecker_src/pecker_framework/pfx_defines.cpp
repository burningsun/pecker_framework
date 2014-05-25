/*
 * pfx_defines.cpp
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_defines.h"

PECKER_BEGIN

uint_t&	__type_id::ID ()
{
	static uint_t static_id = 0;
	return static_id;
}

uint_t __type_id::NEW_ID ()
{
	++ID();
	return ID();
}

boolean_t __type_id::__IS_type (const object_id_t& type_a, const object_id_t& test_type)
{
	boolean_t retn_res = PFX_BOOL_FALSE;
	const object_id_t* list_ptr = & type_a;
	usize__t __testID = test_type.final_type_id();

	do 
	{
		uint_t __base_id = list_ptr->final_type_id();
		if (__testID != __base_id)
		{
			retn_res = list_ptr->check_id (__testID);
			if (PFX_BOOL_TRUE == retn_res)
			{
				break;
			}
		}
		list_ptr = list_ptr->next;
	} while (list_ptr);

	return retn_res;
}

PECKER_END
