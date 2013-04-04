/*
 * pecker_vector.h
 *
 *  Created on: 2012-7-25
 *      Author: ÀîÕò³Ç (cut / cutxyz)
 */

#ifndef PECKER_VECTOR_H_
#define PECKER_VECTOR_H_

#include "../CPeckerObject.h"

PECKER_BEGIN

#define FLOAT_PRECISION 0.000001f
#define EQFLOATZERO(x) ((Bool)( (FLOAT_PRECISION) >= (x) && (-FLOAT_PRECISION) <= (x)))

struct pecker_vector2;
struct pecker_vector3;
struct pecker_vector4;

struct pecker_vector2
{
  Float x,y;
  pecker_vector2();
  pecker_vector2(Float val);
  pecker_vector2(Float x,Float y);
  pecker_vector2(const Float* P_IN vec2);
  pecker_vector2(const pecker_vector2 &other);
  pecker_vector2(const pecker_vector3 &vec3);

  pecker_vector2 & operator+=(const pecker_vector2 & Val);

  pecker_vector2 & operator-=(const pecker_vector2 & Val);

  pecker_vector2 & operator*=(const pecker_vector2 & Val);
  pecker_vector2 & operator*=(Float Val);

  pecker_vector2 & operator/=(const pecker_vector2 & Val);
  pecker_vector2 & operator/=(Float Val);

  pecker_vector2 operator+(const pecker_vector2 & Val) const;

  pecker_vector2 operator-(const pecker_vector2 & Val) const;

  pecker_vector2 operator*(const pecker_vector2 & Val) const;
  pecker_vector2 operator*(Float Val) const;

  pecker_vector2 operator/(const pecker_vector2 & Val) const;
  pecker_vector2 operator/(Float Val) const;

  Bool operator==(const pecker_vector2 & Val) const;
  Bool operator!=(const pecker_vector2 & Val) const;


  friend pecker_vector2 operator- (const pecker_vector2& rhs){ return pecker_vector2(-rhs.x, -rhs.y);}
  friend pecker_vector2 operator*(Float lhs, const pecker_vector2&  rhs){ pecker_vector2 res(lhs);return res *= rhs;}
  friend pecker_vector2 operator/(Float lhs, const pecker_vector2&  rhs){ pecker_vector2 res(lhs);return res /= rhs;}

  Float length_square() const;
  Float length() const;
  pecker_vector2 normalize();
  pecker_vector2 normalized() const;
  pecker_vector2 rotated90();
  pecker_vector2 rotated90ed() const;
  Float dot(const pecker_vector2 & other);

  Float* get_data();
};

struct pecker_vector3
{
  Float x,y,z;
  pecker_vector3();
  pecker_vector3(Float val);
  pecker_vector3(const Float* P_IN vec3);
  pecker_vector3(Float x,Float y,Float z);
  pecker_vector3(const pecker_vector3 & other);
  pecker_vector3(const pecker_vector4 & vec4);

  pecker_vector3 & operator+=(const pecker_vector3 & Val);

  pecker_vector3 & operator-=(const pecker_vector3 & Val);

  pecker_vector3 & operator*=(const pecker_vector3 & Val);
  pecker_vector3 & operator*=(Float Val);

  pecker_vector3 & operator/=(const pecker_vector3 & Val);
  pecker_vector3 & operator/=(Float Val);

  pecker_vector3 operator+(const pecker_vector3 & Val) const;

  pecker_vector3 operator-(const pecker_vector3 & Val) const;

  pecker_vector3 operator*(const pecker_vector3 & Val) const;
  pecker_vector3 operator*(Float Val) const;

  pecker_vector3 operator/(const pecker_vector3 & Val) const;
  pecker_vector3 operator/(Float Val) const;

  Bool operator==(const pecker_vector3 & Val) const;
  Bool operator!=(const pecker_vector3 & Val) const;

  friend pecker_vector3 operator- (const pecker_vector3& rhs){ return pecker_vector3(-rhs.x, -rhs.y, -rhs.z);}
  friend pecker_vector3 operator*(Float lhs, const pecker_vector3&  rhs){ pecker_vector3 res(lhs);return res *= rhs;}
  friend pecker_vector3 operator/(Float lhs, const pecker_vector3&  rhs){ pecker_vector3 res(lhs);return res /= rhs;}

  Float length_square() const;
  Float length() const;
  pecker_vector3 normalize();
  pecker_vector3 normalized() const;

  Float dot(const pecker_vector3 & other);

  pecker_vector3 cross(const pecker_vector3 & other) const;

  Float* get_data();
};

struct pecker_vector4
{
  Float x,y,z,w;
  pecker_vector4();
  pecker_vector4(Float val);
  pecker_vector4(const Float* vec4);
  pecker_vector4(Float x,Float y,Float z,Float w);
  pecker_vector4(const pecker_vector4 & other);

  pecker_vector4(const pecker_vector3 & vec3,Float w);
  pecker_vector4(Float x,const pecker_vector3 & vec3);

  pecker_vector4 & operator+=(const pecker_vector4 & Val);

  pecker_vector4 & operator-=(const pecker_vector4 & Val);

  pecker_vector4 & operator*=(const pecker_vector4 & Val);
  pecker_vector4 & operator*=(Float Val);

  pecker_vector4 & operator/=(const pecker_vector4 & Val);
  pecker_vector4 & operator/=(Float Val);

  pecker_vector4 operator+(const pecker_vector4 & Val) const;

  pecker_vector4 operator-(const pecker_vector4 & Val) const;

  pecker_vector4 operator*(const pecker_vector4 & Val) const;
  pecker_vector4 operator*(Float Val) const;

  pecker_vector4 operator/(const pecker_vector4 & Val) const;
  pecker_vector4 operator/(Float Val) const;

  Bool operator==(const pecker_vector4 & Val) const;
  Bool operator!=(const pecker_vector4 & Val) const;

  friend pecker_vector4 operator- (const pecker_vector4& rhs){ return pecker_vector4(-rhs.x, -rhs.y, -rhs.z, -rhs.w);}
  friend pecker_vector4 operator*(Float lhs, const pecker_vector4&  rhs){ pecker_vector4 res(lhs);return res *= rhs;}
  friend pecker_vector4 operator/(Float lhs, const pecker_vector4&  rhs){ pecker_vector4 res(lhs);return res /= rhs;}

  Float length_square() const;
  Float length() const;
  pecker_vector4 normalize();
  pecker_vector4 normalized() const;
  Float dot(const pecker_vector4 & other);

  Float* get_data();
};

PECKER_END

#endif /* PECKER_VECTOR_H_ */
