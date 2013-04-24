/*
 *  pecker_shape.h
 *
 *  Created on: 2013-4-22
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_SHAPE_H_
#define PECKER_SHAPE_H_

#include "../CPeckerObject.h"
#include "pecker_vector.h"

PECKER_BEGIN

enum SHAPE_TYPE
{
	DOT_2D = 0,
	LINE_2D,
	RECTANGLE_2D,
	SQURE_2D,
	TRIANGLE_2D,
	CIRCULAR_2D,
	OVAL_2D,
	POLYGON_2D,

	DOT_3D = 0,
	LINE_3D,
	RECTANGLE_3D,
	SQURE_3D,
	TRIANGLE_3D,
	CIRCULAR_3D,
	OVAL_3D,
	POLYGON_3D,

	SHAPE_TYPE_COUNT
};

enum SHAPE_EQUALS_RESULT
{
	SAME_SHAPE = 0,
	DIFFERENCE_SHAPE,
	DIFFERENCE_SHAPE_TYPE,
	COMPARE_SHAPE_ERROR,

	SHAPE_EQUALS_RESULT_TYPE
};

PeckerInterface Ipecker_shape_logic
{
	virtual ~Ipecker_shape_logic(){;}
	virtual Boolean intersect(const Ipecker_shape_logic* pshape) const = 0;
	virtual Boolean contains(const Ipecker_shape_logic* pshape) const = 0; 
	virtual HEnum equals(const Ipecker_shape_logic* pshape) const = 0;
	virtual HEnum get_shape_type() const = 0;
};

class pecker_dot2d_float : public virtual Ipecker_shape_logic
{
private:
	pecker_vector2 _M_dot;
public:
	inline Float getX() const
	{
		return _M_dot.x;
	}
	inline Float getY() const
	{
		return _M_dot.y;
	}
	inline const pecker_vector2& get_point() const
	{
		return _M_dot;
	}
	inline void setX(Float x)
	{
		_M_dot.x = x;
	}
	inline void setY(Float y)
	{
		_M_dot.y = y;
	}

public:
	pecker_dot2d_float();
	~pecker_dot2d_float();

	virtual Boolean intersect(const Ipecker_shape_logic* pshape) const;
	virtual Boolean contains(const Ipecker_shape_logic* pshape) const; 
	virtual HEnum equals(const Ipecker_shape_logic* pshape) const;
	virtual HEnum get_shape_type() const;

};


PECKER_END

#endif//PECKER_SHAPE_H_
