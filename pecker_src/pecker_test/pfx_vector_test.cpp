/*
 * pfx_list_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_vector_codes.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"

USING_PECKER_SDK

void vector_test ()
{
	pfx_vector < dimension_value_operations < float >, 4 > vec4,vec4_;
	vec4.reference(DIMENSION_W) = 1;
	vec4.reference(DIMENSION_Z) = 1;
	vec4.reference(DIMENSION_Y) = 1;
	vec4.reference(DIMENSION_X) = 1;
	vec4_ = vec4;
	vec4.cross_replace(vec4_.m_dim);
}