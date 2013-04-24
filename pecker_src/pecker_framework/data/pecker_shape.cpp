/*
 *  pecker_shape.cpp
 *
 *  Created on: 2013-4-23
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_shape.h"

PECKER_BEGIN



pecker_dot2d_float::pecker_dot2d_float()
{
	;
}
pecker_dot2d_float::~pecker_dot2d_float()
{
	;
}

Boolean pecker_dot2d_float::intersect(const Ipecker_shape_logic* pshape) const
{
	return true;
}

Boolean pecker_dot2d_float::contains(const Ipecker_shape_logic* pshape) const
{
	if ( SAME_SHAPE == equals(pshape) )
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

HEnum pecker_dot2d_float::equals(const Ipecker_shape_logic* pshape) const
{
	if (pshape && DOT_2D == pshape->get_shape_type())
	{
		const pecker_dot2d_float* pdot = dynamic_cast< const pecker_dot2d_float* > (pshape);
		if (pdot)
		{
			if (pdot->get_point() == get_point())
			{
				return SAME_SHAPE;
			}
			else
			{
				return DIFFERENCE_SHAPE;
			}
		}
		else
		{
			return COMPARE_SHAPE_ERROR;
		}
		
	}
	return DIFFERENCE_SHAPE_TYPE;
}

HEnum pecker_dot2d_float::get_shape_type() const
{
	return DOT_2D;
}


PECKER_END

