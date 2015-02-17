/*
 * pfx_graphics_test.cpp
 *
 *  Created on: 2013-9-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "../pecker_framework/data/pfx_cgraphics.h"

USING_PECKER_SDK

struct st_region_test
{
	typedef point_locate< ushort_t >  element_t;
	typedef nsize__t  length_t;
	typedef nsize__t   angle_t;
	typedef point_locate< ushort_t >     pos_t;

	element_t* m_data_ptr;
	nsize__t   m_size;
	pos_t      m_center;
};

typedef graphic_node_data< st_region_test >	 gnd_test;
typedef region_cmp_angle< gnd_test > rcg_test;
typedef graphic_node< gnd_test, rcg_test > gn;


void test_graphic()
{
	
}
