/*
 * pfx_math_method.h
 *
 *  Created on: 2013-10-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_MATH_METHOD_H_
#define		PFX_MATH_METHOD_H_


#include "../pfx_defines.h"
#include <math.h>
// andorid abs函数放stdlib.h里面
#include <stdlib.h>

PECKER_BEGIN

//#undef LOW_PRECISION_QUALIFER_VAL
//#undef MID_PRECISION_QUALIFER_VAL
//#undef HIGH_PRECISION_QUALIFER_VAL
//#undef VARY_HIGH_PRECISION_QUALIFER_VAL

#define LOW_PRECISION_QUALIFER_VAL (20)
#define MID_PRECISION_QUALIFER_VAL (10)
#define HIGH_PRECISION_QUALIFER_VAL (5)
#define VARY_HIGH_PRECISION_QUALIFER_VAL (1)

typedef enum enumFLOAT_PRECISION_QUALIFER
{
	LOW_PRECISION_QUALIFER = 0,
	MID_PRECISION_QUALIFER,
	HIGH_PRECISION_QUALIFER,
	VARY_HIGH_PRECISION_QUALIFER,

	PFX_FLOAT_PRECISION_QUALIFER_COUNT
}PFX_FLOAT_PRECISION_QUALIFER_t;

typedef struct st_equals
{
	typedef u32_t delta_t;

	PFX_INLINE bool operator() (char x, char y, delta_t delta = 0) const
	{
		return operate(x, y);
	}
	PFX_INLINE bool operator() (short x, short y, delta_t delta = 0) const
	{
		return operate(x, y);
	}
	PFX_INLINE bool operator() (int x, int y, delta_t delta = 0) const
	{
		return operate(x, y);
	}
	PFX_INLINE bool operator() (long x, long y, delta_t delta = 0) const
	{
		return operate(x, y);
	}
	PFX_INLINE bool operator() (long long x, long long y, delta_t delta = 0) const
	{
		return operate(x, y);
	}
	PFX_INLINE bool operator() (float x, float y, delta_t delta = MID_PRECISION_QUALIFER_VAL) const
	{
		return operate(x, y, delta);
	}
	PFX_INLINE bool operator() (double x, double y, delta_t delta = MID_PRECISION_QUALIFER_VAL) const
	{
		return operate(x, y, delta);
	}


	static PFX_INLINE bool operate(char x, char y, delta_t delta = 0)
	{
		return (x == y);
	}
	static PFX_INLINE bool operate(short x, short y, delta_t delta = 0)
	{
		return (x == y);
	}
	static PFX_INLINE bool operate(int x, int y, delta_t delta = 0)
	{
		return (x == y);
	}
	static PFX_INLINE bool operate(long x, long y, delta_t delta = 0)
	{
		return (x == y);
	}
	static PFX_INLINE bool operate(long long x, long long y, delta_t delta = 0)
	{
		return (x == y);
	}
	static PFX_INLINE bool operate(float fX, float fY, delta_t delta = MID_PRECISION_QUALIFER_VAL)
	{
		bool res;
//#define NOT_IEEE754_FLOAT
#ifndef NOT_IEEE754_FLOAT
		s32_t iX, iY;
		iX = (fX > 0) ? ((s32_t&)fX) : ((s32_t&)fX - 0x80000000);
		iY = (fY > 0) ? ((s32_t&)fY) : ((s32_t&)fY - 0x80000000);
		res = ::abs(iX - iY) < (s32_t)delta;
#else
		RETURN_RESULT(res,res);

		const float delta_abs = ((float)delta) / ((float)4194304);
		res = (::abs(fX - fY) <= delta_abs);

		RETURN_RESULT(!res, res);

		if (fX > fY)
		{
			res = (::abs((fX - fY) / fX) < delta_abs);
		}
		else
		{
			res = (::abs((fX - fY) / fY) < delta_abs);
		}
#endif
		return res;
	}
	static PFX_INLINE bool operate(double fX, double fY, delta_t delta = MID_PRECISION_QUALIFER_VAL)
	{
		bool res;

		res = (fX == fY);
		RETURN_RESULT(res,res);

		const double delta_abs = ((double)delta) / ((double)2251799813685248);
		res = (::abs(fX - fY) <= delta_abs);

		RETURN_RESULT(!res, res);

		if (fX > fY)
		{
			res = (::abs((fX - fY) / fX) < delta_abs);
		}
		else
		{
			res = (::abs((fX - fY) / fY) < delta_abs);
		}

	    return res;
	}
}equals_t;

typedef struct st_abs
{
	PFX_INLINE char operator()(char __val) const
	{
		return operate(__val);
	}
	PFX_INLINE short operator()(short __val) const
	{
		return operate(__val);
	}
	PFX_INLINE int operator()(int __val) const
	{
		return operate(__val);
	}
	PFX_INLINE float operator()(float __val) const
	{
		return operate(__val);
	}
	PFX_INLINE double operator()(double __val) const
	{
		return operate(__val);
	}
	static PFX_INLINE char operate(char __val)
	{
		return ::abs(__val);
	}
	static PFX_INLINE short operate(short __val)
	{
		return ::abs(__val);
	}
	static PFX_INLINE int operate(int __val)
	{
		return ::abs(__val);
	}
	static PFX_INLINE float operate(float __val)
	{
		return ::abs(__val);
	}
	static PFX_INLINE double operate(double __val)
	{
		return ::abs(__val);
	}

}abs_t;

template < class _value >
struct st_add
{
	PFX_INLINE _value operator()(_value a, _value b) const
	{
		return operate(a, b);
	}
	static PFX_INLINE _value operate(_value a, _value b)
	{
		return (a + b);
	}
};

template < class _value >
struct st_add_replace
{
	PFX_INLINE _value operator()(_value a, _value b) const
	{
		return operate(a, b);
	}
	static PFX_INLINE _value& operate(_value& a, _value b)
	{
		a += b;
		return a;
	}
};

template < class _value >
struct st_sub
{
	PFX_INLINE _value operator()(_value a, _value b) const
	{
		return operate(a, b);
	}
	static PFX_INLINE _value operate(_value a, _value b)
	{
		return (a - b);
	}
};

template < class _value >
struct st_sub_replace
{
	PFX_INLINE _value operator()(_value a, _value b) const
	{
		return operate(a, b);
	}
	static PFX_INLINE _value& operate(_value& a, _value b)
	{
		a -= b;
		return a;
	}
};

template < class _value >
struct st_mul
{
	PFX_INLINE _value operator()(_value a, _value b) const
	{
		return operate(a, b);
	}
	static PFX_INLINE _value operate(_value a, _value b)
	{
		return (a * b);
	}
};

template < class _value >
struct st_mul_replace
{
	PFX_INLINE _value operator()(_value a, _value b) const
	{
		return operate(a, b);
	}
	static PFX_INLINE _value& operate(_value& a, _value b)
	{
		a *= b;
		return a;
	}
};

template < class _value >
struct st_div
{
	PFX_INLINE _value operator()(_value a, _value b) const
	{
		return operate(a, b);
	}
	static PFX_INLINE _value operate(_value a, _value b)
	{
		return (a / b);
	}
};

template < class _value >
struct st_div_replace
{
	PFX_INLINE _value operator()(_value a, _value b) const
	{
		return operate(a, b);
	}
	static PFX_INLINE _value& operate(_value& a, _value b)
	{
		a /= b;
		return a;
	}
};

typedef struct st_sin
{
	PFX_INLINE float operator()(float __val) const
	{
		return operate(__val);
	}
	PFX_INLINE double operator()(double __val) const
	{
		return operate(__val);
	}
	static PFX_INLINE float operate(float __val)
	{
		return ::sin(__val);
	}
	static PFX_INLINE double operate(double __val)
	{
		return ::sin(__val);
	}
}sin_t;
typedef struct st_cos
{
	PFX_INLINE float operator()(float __val) const
	{
		return operate(__val);
	}
	PFX_INLINE double operator()(double __val) const
	{
		return operate(__val);
	}
	static PFX_INLINE float operate(float __val)
	{
		return ::cos(__val);
	}
	static PFX_INLINE double operate(double __val)
	{
		return ::cos(__val);
	}
}cos_t;
typedef struct st_tan
{
	PFX_INLINE float operator()(float __val) const
	{
		return operate(__val);
	}
	PFX_INLINE double operator()(double __val) const
	{
		return operate(__val);
	}
	static PFX_INLINE float operate(float __val)
	{
		return ::tan(__val);
	}
	static PFX_INLINE double operate(double __val)
	{
		return ::tan(__val);
	}
}tan_t;
typedef struct st_acos
{
	PFX_INLINE float operator()(float __val) const
	{
		return operate(__val);
	}
	PFX_INLINE double operator()(double __val) const
	{
		return operate(__val);
	}
	static PFX_INLINE float operate(float __val)
	{
		return ::acos(__val);
	}
	static PFX_INLINE double operate(double __val)
	{
		return ::acos(__val);
	}
}acos_t;

typedef struct st_sincos
{
	PFX_INLINE void operator()(float rad,
	float& sin_val, float& cos_val) const
	{
		 operate(rad, sin_val, cos_val);
	}
	PFX_INLINE void operator()(double rad,
		double& sin_val, double& cos_val) const
	{
		 operate(rad, sin_val, cos_val);
	}
	static PFX_INLINE void operate(float rad, 
		float& sin_val, float& cos_val)
	{
		sin_val = ::sin(rad);
		cos_val = ::cos(rad);
	}
	static PFX_INLINE void operate(double rad,
		double& sin_val, double& cos_val)
	{
		sin_val = ::sin(rad);
		cos_val = ::cos(rad);
	}
}sincos_t;


template < class _value >
struct st_sqrt
{
	PFX_INLINE _value operator()(_value a) const
	{
		return operate(a);
	}
	static PFX_INLINE _value operate(_value a)
	{
		return ::sqrt(a);
	}
};



PECKER_END


#endif			//PFX_MATH_METHOD_H_
