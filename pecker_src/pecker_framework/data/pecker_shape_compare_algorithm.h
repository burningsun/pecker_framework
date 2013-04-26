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
#include <math.h>

PECKER_BEGIN

enum LINE_DOT_2D_RELATIONSHIP
{
	DOT_IN_LINE = 0,
	LINE_ABOVE_DOT,
	LINE_BELOW_DOT,

	LINE_DOT_2D_RELATIONSHIP_COUNT
};


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
		equal_rectangle2d_size_int(first_shape_h,first_shape_w,second_shape_h,second_shape_w) );
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
// 如何判断点C在向量AB的左侧还是右侧：AC×AB的数值大于0则在右侧，小于0则在左侧

inline HEnum intersect_line_dot_2d_float(const pecker_vector2& line_pointA,const pecker_vector2& line_pointB,const pecker_vector2& pointC)
{
	pecker_vector2 lineAB = line_pointB - line_pointA;
	pecker_vector2 lineAC = pointC - line_pointA;
	Float cross_value = lineAC.cross_value(lineAB);

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
			return DOT_IN_LINE;
		}	
	}
	else if (cross_value > 0)
	{
		return LINE_ABOVE_DOT;
	}
	else
	{
		return LINE_BELOW_DOT;
	}
}
inline HEnum intersect_line_dot_2d_int(SInt line_point_Ax,SInt line_point_Ay,SInt line_point_Bx,SInt line_point_By,SInt pointCx,SInt pointCy)
{
	SInt lineABx = line_point_Bx - line_point_Ax;
	SInt lineABy = line_point_By - line_point_Ay;
	SInt lineACx = pointCx - line_point_Ax;
	SInt lineACy = pointCy - line_point_Ay;
	SInt cross_value = lineABy*lineACx - lineABx*lineACy;

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
		if (pointCx >= min_x && pointCx <= max_x && pointCy >= min_y && pointCy <= max_y)
		{
			return DOT_IN_LINE;
		}	
	}
	else if (0 < cross_value)
	{
		return LINE_ABOVE_DOT;
	}
	else
	{
		return LINE_BELOW_DOT;
	}
}

//////////////////////////////////////////////////////////////////////////
// BitField              bitorder 31~0
//								第13个bit标识第二直线D点在第一直线的下方
//								第12个bit标识第二直线D点在第一直线的上方
//								第11个bit标识第二直线C点在第一直线的下方
//								第10个bit标识第二直线C点在第一直线的上方
//                             第 9个bit标识两直线是否相交(不包含两直线重叠的情况)
//								第8个bit标识两直线是否平衡
//								第0~7个bit标识当前判断结果
//								第14~31个bit保留
#define  BALANCE_LINE  (1 << 8)
#define  INTERSECT_LINE (1 << 9)
#define  C_POINT_ABOVE (1 << 10)
#define  C_POINT_BELOW (1 << 11)
#define  D_POINT_ABOVE (1 << 12)
#define  D_POINT_BELOW (1 << 13)
#define  LINE_INTERSECT_TRUE (1)
#define  LINE_INTERSECT_FALSE (0)
inline BitField intersect_line_line_2d_float(const pecker_vector2& pointA,const pecker_vector2& pointB,const pecker_vector2& pointC,const pecker_vector2& pointD)
{
	BitField return_result = 0;
	pecker_vector2 lineAB = pointB - pointA;
	pecker_vector2 lineCD = pointD - pointC;
	// 点A，C 在直线AB两侧，并且 点C，D在直线CD两侧，则线段AC与线段CD相交 (充分必要条件，两侧包含点在直线上的情况)
	Float cross_AB_CD_value = lineAB.cross_value(lineCD);

	if (EQFLOATZERO(cross_AB_CD_value)) //平衡，重合
	{
		return_result |= BALANCE_LINE;
		Float min_x = pointA.x;
		Float min_y = pointA.y;
		Float max_x = pointB.x;
		Float max_y = pointB.y;

		if (min_x > max_x)
		{
			min_x = pointB.x;
			max_x = pointA.x;
		}
		if (min_y > max_y)
		{
			min_y = pointB.y;
			max_y = pointA.y;
		}

		if ((pointC.x >= min_x && pointC.x <= max_x && pointC.y >= min_y && pointC.y <= max_y) ||
			(pointD.x >= min_x && pointD.x <= max_x && pointD.y >= min_y && pointD.y <= max_y))
		{
			return_result |= LINE_INTERSECT_TRUE;
		}
	}
	else // 不平衡，交叉
	{
		return_result |= INTERSECT_LINE;
		pecker_vector2 lineAC = pointC - pointA;
		pecker_vector2 lineAD = pointD - pointA;
		Float cross_AC_AB_value = lineAC.cross_value(lineAB);
		Float cross_AD_AB_value = lineAD.cross_value(lineAB);
		Float cross = cross_AC_AB_value * cross_AD_AB_value;

		if (cross_AC_AB_value > 0)
		{
			return_result |= C_POINT_ABOVE;
		}
		else if (cross_AC_AB_value < 0)
		{
			return_result |= C_POINT_BELOW;
		}
		if (cross_AD_AB_value > 0)
		{
			return_result |= D_POINT_ABOVE;
		}
		else if (cross_AD_AB_value < 0)
		{
			return_result |= D_POINT_BELOW;
		}
		if ( cross <= 0)
		{
			Float min_x = pointA.x;
			Float min_y = pointA.y;
			Float max_x = pointB.x;
			Float max_y = pointB.y;

			if (min_x > max_x)
			{
				min_x = pointB.x;
				max_x = pointA.x;
			}
			if (min_y > max_y)
			{
				min_y = pointB.y;
				max_y = pointA.y;
			}

			if ((pointC.x >= min_x && pointC.x <= max_x && pointC.y >= min_y && pointC.y <= max_y) ||
				(pointD.x >= min_x && pointD.x <= max_x && pointD.y >= min_y && pointD.y <= max_y))
			{
				return_result |= LINE_INTERSECT_TRUE;
			}
		}
	}

	return return_result;
}

inline BitField intersect_line_line_2d_int(SInt pointAx,SInt pointAy,SInt pointBx,SInt pointBy,
	SInt pointCx,SInt pointCy,SInt pointDx,SInt pointDy)
{
	BitField return_result = 0;
	SInt lineABx = pointBx - pointAx;
	SInt lineABy = pointBy - pointAy;
	SInt lineCDx = pointDx - pointCx;
	SInt lineCDy = pointDy - pointCy;
	// 点A，C 在直线AB两侧，并且 点C，D在直线CD两侧，则线段AC与线段CD相交 (充分必要条件，两侧包含点在直线上的情况)
	SInt cross_AB_CD_value = lineABy*lineCDx - lineABx*lineCDy; 

	if (0 == cross_AB_CD_value) //平衡，重合
	{
		return_result |= BALANCE_LINE;
		Float min_x = pointAx;
		Float min_y = pointAy;
		Float max_x = pointBx;
		Float max_y = pointBy;

		if (min_x > max_x)
		{
			min_x = pointBx;
			max_x = pointAx;
		}
		if (min_y > max_y)
		{
			min_y = pointBy;
			max_y = pointAy;
		}

		if ((pointCx >= min_x && pointCx <= max_x && pointCy >= min_y && pointCy <= max_y) ||
			(pointDx >= min_x && pointDx <= max_x && pointDy >= min_y && pointDy <= max_y))
		{
			return_result |= LINE_INTERSECT_TRUE;
		}
	}
	else // 不平衡，交叉
	{
		return_result |= INTERSECT_LINE;
		
		SInt lineACx = pointCx - pointAx;
		SInt lineACy = pointCy - pointAy;
		SInt lineADx = pointDx - pointAx;
		SInt lineADy = pointDy - pointAy;

		SInt cross_AC_AB_value = lineABy*lineACx - lineABx*lineACy;
		SInt cross_AD_AB_value = lineABy*lineADx - lineABx*lineADy;
		SInt cross = cross_AC_AB_value * cross_AD_AB_value;

		if (cross_AC_AB_value > 0)
		{
			return_result |= C_POINT_ABOVE;
		}
		else if (cross_AC_AB_value < 0)
		{
			return_result |= C_POINT_BELOW;
		}
		if (cross_AD_AB_value > 0)
		{
			return_result |= D_POINT_ABOVE;
		}
		else if (cross_AD_AB_value < 0)
		{
			return_result |= D_POINT_BELOW;
		}
		if ( cross <= 0)
		{
			Float min_x = pointAx;
			Float min_y = pointAy;
			Float max_x = pointBx;
			Float max_y = pointBy;

			if (min_x > max_x)
			{
				min_x = pointBx;
				max_x = pointAx;
			}
			if (min_y > max_y)
			{
				min_y = pointBy;
				max_y = pointAy;
			}

			if ((pointCx >= min_x && pointCx <= max_x && pointCy >= min_y && pointCy <= max_y) ||
				(pointDx >= min_x && pointDx <= max_x && pointDy >= min_y && pointDy <= max_y))
			{
				return_result |= LINE_INTERSECT_TRUE;
			}
		}
	}

	return return_result;
}

//////////////////////////////////////////////////////////////////////////
inline Float euler_distance_dot_2d_float(const pecker_vector2& pointA,const pecker_vector2& pointB)
{
	pecker_vector2 pointBA = pointB - pointA;
	return pointBA.length();
}

inline Float euler_distance_dot_2d_int(SInt pointAx,SInt pointAy,SInt pointBx,SInt pointBy)
{
	SInt pointBAx = pointBx - pointAx;
	SInt pointBAy = pointBy - pointAy;
	return sqrt( (Float)(pointBAx * pointBAx + pointAy * pointAy));
}

inline Float euler_distance_dot_to_line_2d_float(const pecker_vector2& line_pointA,const pecker_vector2& line_pointB,const pecker_vector2& pointC)
{
	pecker_vector2 lineAB = line_pointB - line_pointA;
	pecker_vector2 lineAC = pointC - line_pointA;
	// 方法1：
	// lineAB dot  lineAC = |lineAB| |lineAC| * cos<AB,AC> 
	// normalAB = lineAB/|lineAB|;
	//
	// projAB = normalAB * (|lineAC| * cos<AB,AC>) 
	//              =  normalAB * (lineAB dot  lineAC / |lineAB|) 
	//              = (lineAB/|lineAB|)*(lineAB dot  lineAC / |lineAB|)
	//             =  (lineAB dot  lineAC)  / (|lineAB|*|lineAB|) * lineAB 
	//     
	// d*d + |projAB| * |projAB| = |lineAC| * |lineAC|
	// d = sqrt(|lineAC| * |lineAC| - |projAB| * |projAB|);
	//pecker_vector3 project_AC_to_AB = (lineAC.dot(lineAB)  / lineAB.length_square()) * lineAB;
	//Float sqrt_value = lineAC.length_square() - project_AC_to_AB.length_square();
	Float dotAC_AB = lineAC.dot(lineAB);
	Float sqrt_value = lineAC.length_square() - (dotAC_AB * dotAC_AB / lineAB.length_square());
	if (sqrt_value >= 0)
	{
		return sqrt(sqrt_value);
	}
	else
	{
		return -1.0f;
	}
	
	// 方法2：
	//// 向量AB的法向量为ABNormal
	//// 点C到直线AB的距离 等于 |ABNormal · lineAC | / |ABNormal|·|lineAC|
	//pecker_vector2 lineABNormal = line_pointB - line_pointA;
	//lineABNormal.rotated90();
	//pecker_vector2 lineAC = pointC - line_pointA;
	//Float lineABNormal_length = lineABNormal.length();

	//if (EQFLOATZERO(lineABNormal_length)) // A,B两个点是同一个点，输入错误
	//{
	//	return -1.0f;
	//}
 //   Float lineAC_length =  lineAC.length();
	//if (EQFLOATZERO(lineAC_length)) // C,A两个点是同一个点，则C到AB的距离为0
	//{
	//	return 0.0f;
	//}
	//return (abs(lineAC.dot(lineABNormal)) / (lineABNormal_length * lineAC_length));

}
inline Float euler_distance_dot_to_line_3d_float(const pecker_vector3& line_pointA,const pecker_vector3& line_pointB,const pecker_vector3& pointC)
{
	pecker_vector3 lineAB = line_pointB - line_pointA;
	pecker_vector3 lineAC = pointC - line_pointA;
	// 方法1：
	// lineAB dot  lineAC = |lineAB| |lineAC| * cos<AB,AC> 
	// normalAB = lineAB/|lineAB|;
	//
	// projAB = normalAB * (|lineAC| * cos<AB,AC>) 
	//              =  normalAB * (lineAB dot  lineAC / |lineAB|) 
	//              = (lineAB/|lineAB|)*(lineAB dot  lineAC / |lineAB|)
	//             =  (lineAB dot  lineAC)  / (|lineAB|*|lineAB|) * lineAB 
	//     
	// d*d + |projAB| * |projAB| = |lineAC| * |lineAC|
	// d = sqrt(|lineAC| * |lineAC| - |projAB| * |projAB|);
	//pecker_vector3 project_AC_to_AB = (lineAC.dot(lineAB)  / lineAB.length_square()) * lineAB;
	//Float sqrt_value = lineAC.length_square() - project_AC_to_AB.length_square();
	Float dotAC_AB = lineAC.dot(lineAB);
	Float sqrt_value = lineAC.length_square() - (dotAC_AB * dotAC_AB / lineAB.length_square());
	if (sqrt_value >= 0)
	{
		return sqrt(sqrt_value);
	}
	else
	{
		return -1.0f;
	}

	// 方法2：
	// | lineAB cross lineAC | = |lineAB| * |lineAC| * sin<AB,AC>
	// d = |lineAC| * sin<AB,AC> 
	// | lineAB cross lineAC | = |lineAB| * d
	// d = | lineAB cross lineAC | / |lineAB|
	//return (lineAC.cross(lineAB)).length() / lineAB.length();
} 

PECKER_END

#endif//PECKER_SHAPE_COMPARE_ALGORITHM_H_
