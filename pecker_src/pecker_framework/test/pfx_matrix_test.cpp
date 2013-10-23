/*
 * pfx_matrix_test.cpp
 *
 *  Created on: 2013-10-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../data/pfx_list.h"
#include "../native/pfx_log.h"
#include "../data/pfx_matrix4.h"

int matrix_test_main()
{
	pfx_vector4_t vec4;
	pfx_marix4_t mat4;
	matrix4_set_column_unsafe (&mat4,0,&vec4);
	matrix4_set_row_unsafe (&mat4,0,&vec4);
	return 0;
}


