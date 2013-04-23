/*
 *  pecker_shape_compare_algorithm.h
 *
 *  Created on: 2013-4-23
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_SHAPE_COMPARE_ALGORITHM_H_
#define PECKER_SHAPE_COMPARE_ALGORITHM_H_

#include "../CPeckerObject.h"
#include "pecker_vector.h"
#include "pecker_value_compare.h"

PECKER_BEGIN

inline Bool equal_dot2d_float(const pecker_vector2& first_shape,const pecker_vector2& second_shape)
{
	return (first_shape == second_shape);
}

inline Bool equal_dot2d_int(SInt first_shape_x,SInt first_shape_y,SInt second_shape_x,SInt second_shape_y)
{
	return (first_shape_x == second_shape_x && first_shape_y == second_shape_y);
}

inline Bool equal_line_2d_int(SInt first_shape_x,SInt first_shape_y,nSize first_shape_w,nSize first_shape_z,
	SInt second_shape_x,SInt second_shape_y,nSize second_shape_w,nSize second_shape_z)
{
	return (equal_dot2d_int(first_shape_x,first_shape_y,second_shape_x,second_shape_y) &&
		equal_dot2d_int(first_shape_w,first_shape_z,second_shape_w,second_shape_z) );
}

inline Bool equal_line2d_float(const pecker_vector2& first_shape,const pecker_vector2& second_shape)
{
	return (first_shape == second_shape);
}

inline Bool equal_rectangle2d_size_int(nSize first_shape_w,nSize first_shape_h,nSize second_shape_w,nSize second_shape_h)
{
	return (first_shape_w == second_shape_w && first_shape_h == second_shape_h);
}

inline Bool equal_rectangle2d_size_float(const pecker_vector2& first_shape,const pecker_vector2& second_shape)
{
	return (first_shape == second_shape);
}

inline Bool equal_rectangle2d_int(SInt first_shape_x,SInt first_shape_y,nSize first_shape_w,nSize first_shape_h,
	SInt second_shape_x,SInt second_shape_y,nSize second_shape_w,nSize second_shape_h )
{
	return (equal_dot2d_int(first_shape_x,first_shape_y,second_shape_x,second_shape_y) &&
		equal_rectangle2d_size_int(first_shape_h,first_shape_w,second_shape_h,second_shape_w) );
}

inline Bool equal_rectangle2d_float(const pecker_vector2& first_shape_top_point,const pecker_vector2& first_shape_size,
	const pecker_vector2& second_shape_top_point,const pecker_vector2& second_shape_size)
{
	return (equal_dot2d_float(first_shape_top_point,first_shape_top_point) && equal_rectangle2d_size_float(first_shape_size,second_shape_size));
}

inline Bool equal_circular2d_float(const pecker_vector2& first_shape_top_point,Float first_shape_size,
	const pecker_vector2& second_shape_top_point,Float second_shape_size)
{
	return (equal_dot2d_float(first_shape_top_point,first_shape_top_point) && first_shape_size == second_shape_size);
}

inline Bool equal_circular2d_int(SInt first_shape_x,SInt first_shape_y,nSize first_shape_size,
	SInt second_shape_x,SInt second_shape_y,nSize second_shape_size )
{
	return (equal_dot2d_int(first_shape_x,first_shape_y,second_shape_x,second_shape_y) &&
		(first_shape_size == second_shape_size) );
}

inline Bool equal_oval2d_int(SInt first_shape_x,SInt first_shape_y,nSize first_shape_w,nSize first_shape_h,
	SInt second_shape_x,SInt second_shape_y,nSize second_shape_w,nSize second_shape_h )
{
	return (equal_dot2d_int(first_shape_x,first_shape_y,second_shape_x,second_shape_y) &&
		equal_rectangle_size_int(first_shape_h,first_shape_w,second_shape_h,second_shape_w) );
}

inline Bool equal_oval2d_float(const pecker_vector2& first_shape_top_point,const pecker_vector2& first_shape_size,
	const pecker_vector2& second_shape_top_point,const pecker_vector2& second_shape_size)
{
	return (equal_dot2d_float(first_shape_top_point,first_shape_top_point) && equal_rectangle2d_size_float(first_shape_size,second_shape_size));
}

inline Bool equal_triangle2d_float(const pecker_vector2& first_shape_point1,const pecker_vector2& first_shape_point2,const pecker_vector2& first_shape_point3,
	const pecker_vector2& second_shape_point1,const pecker_vector2& second_shape_point2,const pecker_vector2& second_shape_point3)
{
	return (first_shape_point1 == second_shape_point1 && first_shape_point2 == second_shape_point2 && first_shape_point3 == second_shape_point3);
}

inline Bool equal_ploygon2d_float(const pecker_vector2* first_shape_points,nSize first_shape_point_count,
	const pecker_vector2* second_shape_points,nSize second_shape_point_count)
{
	if (null == first_shape_points || null == second_shape_points || first_shape_point_count != second_shape_point_count)
	{
		return false;
	}
	for (nSize i=0;i<first_shape_point_count;++i)
	{
		if (first_shape_points[i] != second_shape_points[i])
		{
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
//点C在线段AB上
//1、向量AB叉乘向量AC，如果叉积等于0，则A B C三点共线             
//2、若C在直线AB上，且C在以AB为对角线的矩形内，则C在线段AB上
inline Bool intersect_line_dot_2d_float(const pecker_vector2& line_pointA,const pecker_vector2& line_pointB,const pecker_vector2& pointC)
{
	pecker_vector2 lineAB = line_pointB - line_pointA;
	pecker_vector2 lineAC = pointC - line_pointA;
	Float cross_value = lineAB.cross_value(lineAC);

	if (EQFLOATZERO(cross_value))
	{
		Float min_x = line_pointA.x;
		Float max_x = line_pointB.x;
		Float min_y = line_pointA.y;
		Float max_y = line_pointB.y;
		if (min_x > max_x)
		{
			min_x = line_pointB.x;
			max_x = line_pointA.x;
		}
		if (min_x > max_y)
		{
			min_y = line_pointB.y;
			max_y = line_pointA.y;
		}
		if (pointC.x >= min_x && pointC.x <= max_x && pointC.y >= min_y && pointC.y <= max_y)
		{
			return true;
		}	
	}
	return false;
}
inline Bool intersect_line_dot_2d_int(SInt line_point_Ax,SInt line_point_Ay,SInt line_point_Bx,SInt line_point_By,SInt dotX,SInt dotY)
{
	SInt cross_value = line_point_Ax*line_point_By- line_point_Ay*line_point_Bx;

	if (0 == cross_value)
	{
		SInt min_x = line_point_Ax;
		SInt max_x = line_point_Bx;
		SInt min_y = line_point_Ay;
		SInt max_y = line_point_By;
		if (min_x > max_x)
		{
			min_x = line_point_Bx;
			max_x = line_point_Ax;
		}
		if (min_x > max_y)
		{
			min_y = line_point_By;
			max_y = line_point_Ay;
		}
		if (pointC.x >= min_x && pointC.x <= max_x && pointC.y >= min_y && pointC.y <= max_y)
		{
			return true;
		}	
	}
	return false;
}

inline Bool intersect_line_line_2d_float(const pecker_vector2& line_pointA,const pecker_vector2& line_pointB,const pecker_vector2& pointC,const pecker_vector2& pointD)
{

	return false;
}

PECKER_END

#endif//PECKER_SHAPE_COMPARE_ALGORITHM_H_
