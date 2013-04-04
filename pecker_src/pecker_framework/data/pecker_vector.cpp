/*
 * PeckerVector.cpp
 *
 *  Created on: 2012-7-25
 *      Author: 李镇城 (cut / cutxyz)
 */
#include "pecker_vector.h"
#include <math.h>

#define FIXEDVAL 65535.0f

PECKER_BEGIN

pecker_vector2::pecker_vector2():x(0.0f),y(0.0f)
{ ;}
pecker_vector2::pecker_vector2(Float val):x(val),y(val)
{ ;}
pecker_vector2::pecker_vector2(Float x,Float y):x(x),y(y)
{ ;}
pecker_vector2::pecker_vector2(const Float* P_IN vec2):x(vec2[0]),y(vec2[1])
{ ;}
pecker_vector2::pecker_vector2(const pecker_vector2 & other):x(other.x),y(other.y)
{ ;}
pecker_vector2::pecker_vector2(const pecker_vector3 & vec3):x(vec3.x),y(vec3.y)
{ ;}

pecker_vector2 & pecker_vector2::operator+=(const pecker_vector2 & Val)
{
  x += Val.x;
  y += Val.y;
  return *this;
}


pecker_vector2 & pecker_vector2::operator-=(const pecker_vector2 & Val)
{
  x -= Val.x;
  y -= Val.y;
  return *this;
}


pecker_vector2 & pecker_vector2::operator*=(const pecker_vector2 & Val)
{
  x *= Val.x;
  y *= Val.y;
  return *this;
}

pecker_vector2 & pecker_vector2::operator*=(Float Val)
{
  x *= Val;
  y *= Val;
  return *this;
}

pecker_vector2 & pecker_vector2::operator/=(const pecker_vector2 & Val)
{
  x /= Val.x;
  y /= Val.y;
  return *this;
}

pecker_vector2 & pecker_vector2::operator/=(Float Val)
{
  x /= Val;
  y /= Val;
  return *this;
}

pecker_vector2 pecker_vector2::operator+(const pecker_vector2 & Val) const
{
  pecker_vector2 res(*this);
  return (res += Val);
}


pecker_vector2 pecker_vector2::operator-(const pecker_vector2 & Val) const
{
  pecker_vector2 res(*this);
  return (res -= Val);
}


pecker_vector2 pecker_vector2::operator*(const pecker_vector2 & Val) const
{
  pecker_vector2 res(*this);
  return (res *= Val);
}

pecker_vector2 pecker_vector2::operator*(Float Val) const
{
  pecker_vector2 res(*this);
  return (res *= Val);
}

pecker_vector2 pecker_vector2::operator/(const pecker_vector2 & Val) const
{
  pecker_vector2 res(*this);
  return (res /= Val);
}

pecker_vector2 pecker_vector2::operator/(Float Val) const
{
  pecker_vector2 res(*this);
  return (res /= Val);
}

Bool pecker_vector2::operator==(const pecker_vector2 & Val) const
{
  return (EQFLOATZERO( x - Val.x )&&EQFLOATZERO( y - Val.y ));
}

Bool pecker_vector2::operator!=(const pecker_vector2 & Val) const
{
  return ((!EQFLOATZERO( x - Val.x))||(!EQFLOATZERO( y - Val.y )));
}


Float pecker_vector2::length_square() const
{
  return (x*x+y*y);
}

Float pecker_vector2::length() const
{
  Double dx = x;
  Double dy = y;
  return (Float)(sqrt(dx*dx + dy*dy));
}

pecker_vector2 pecker_vector2::normalize()
{
  return (*this/=length());
}

pecker_vector2 pecker_vector2::normalized() const
{
  return pecker_vector2(*this);
}

pecker_vector2 pecker_vector2::rotated90()
{
  Float temp = -y;
  y = x;
  x = temp;
  return *this;
}

pecker_vector2 pecker_vector2::rotated90ed() const
{
  return pecker_vector2(-y,x);
}

Float pecker_vector2::dot(const pecker_vector2 & other)
{
  return (x*other.x + y*other.y);
}


Float* pecker_vector2::get_data()
{
  return (Float*)this;
}

pecker_vector3::pecker_vector3():x(0.0f),y(0.0f),z(0.0f)
{ ;}
pecker_vector3::pecker_vector3(Float val):x(val),y(val),z(val)
{ ;}
pecker_vector3::pecker_vector3(const Float* P_IN vec3):x(vec3[0]),y(vec3[1]),z(vec3[2])
{ ;}
pecker_vector3::pecker_vector3(Float x,Float y,Float z):x(x),y(y),z(z)
{ ;}
pecker_vector3::pecker_vector3(const pecker_vector3 & other):x(other.x),y(other.y),z(other.z)
{ ;}
pecker_vector3::pecker_vector3(const pecker_vector4 & vec4):x(vec4.x),y(vec4.y),z(vec4.z)
{ ;}

pecker_vector3 & pecker_vector3::operator+=(const pecker_vector3 & Val)
{
  x +=Val.x;
  y +=Val.y;
  z +=Val.z;
  return *this;
}

pecker_vector3 & pecker_vector3::operator-=(const pecker_vector3 & Val)
{
  x -=Val.x;
  y -=Val.y;
  z -=Val.z;
  return *this;
}

pecker_vector3 & pecker_vector3::operator*=(const pecker_vector3 & Val)
{
  x *=Val.x;
  y *=Val.y;
  z *=Val.z;
  return *this;
}

pecker_vector3 & pecker_vector3::operator*=(Float Val)
{
  x *=Val;
  y *=Val;
  z *=Val;
  return *this;
}

pecker_vector3 & pecker_vector3::operator/=(const pecker_vector3 & Val)
{
  x /=Val.x;
  y /=Val.y;
  z /=Val.z;
  return *this;
}

pecker_vector3 & pecker_vector3::operator/=(Float Val)
{
  x /=Val;
  y /=Val;
  z /=Val;
  return *this;
}

pecker_vector3 pecker_vector3::operator+(const pecker_vector3 & Val) const
{
  pecker_vector3 res(*this);
  return (res += Val);
}


pecker_vector3 pecker_vector3::operator-(const pecker_vector3 & Val) const
{
  pecker_vector3 res(*this);
  return (res -= Val);
}

pecker_vector3 pecker_vector3::operator*(const pecker_vector3 & Val) const
{
  pecker_vector3 res(*this);
  return (res *= Val);
}

pecker_vector3 pecker_vector3::operator*(Float Val) const
{
  pecker_vector3 res(*this);
  return (res *= Val);
}

pecker_vector3 pecker_vector3::operator/(const pecker_vector3 & Val) const
{
  pecker_vector3 res(*this);
  return (res /= Val);
}

pecker_vector3 pecker_vector3::operator/(Float Val) const
{
  pecker_vector3 res(*this);
  return (res /= Val);
}

Bool pecker_vector3::operator==(const pecker_vector3 & Val) const
{
  return (EQFLOATZERO( x - Val.x ) && EQFLOATZERO( y - Val.y) && EQFLOATZERO( z - Val.z ));
}

Bool pecker_vector3::operator!=(const pecker_vector3 & Val) const
{
  return ((!(EQFLOATZERO( x - Val.x ))) || (!(EQFLOATZERO( y - Val.y ))) || (!(EQFLOATZERO( z - Val.z ))));
}

Float pecker_vector3::length_square() const
{
  return (x*x+y*y+z*z);
}
Float pecker_vector3::length() const
{
  Double dx = x;
  Double dy = y;
  Double dz = z;
  return (Float)(sqrt(dx*dx+dy*dy+dz*dz));
}
pecker_vector3 pecker_vector3::normalize()
{
  return (*this /= length());
}

pecker_vector3 pecker_vector3::normalized() const
{
  pecker_vector3 res(*this);
  return (res /= length());
}

Float pecker_vector3::dot(const pecker_vector3 & other)
{
  return (x*other.x + y*other.y + z*other.z);
}


pecker_vector3 pecker_vector3::cross(const pecker_vector3 & other) const
{
  pecker_vector3 res;
  res.x = y*other.z - z*other.y;
  res.y = z*other.x - x*other.z;
  res.z = x*other.y - y*other.x;
  return res;
}

Float* pecker_vector3::get_data()
{
  return (Float*)this;
}

pecker_vector4::pecker_vector4():x(0.0f),y(0.0f),z(0.0f),w(0.0f)
{ ;}
pecker_vector4::pecker_vector4(Float val):x(val),y(val),z(val),w(val)
{ ;}
pecker_vector4::pecker_vector4(const Float* vec4):x(vec4[0]),y(vec4[1]),z(vec4[2]),w(vec4[3])
{ ;}
pecker_vector4::pecker_vector4(Float x,Float y,Float z,Float w):x(x),y(y),z(z),w(w)
{ ;}
pecker_vector4::pecker_vector4(const pecker_vector4 & other):x(other.x),y(other.y),z(other.z),w(other.w)
{ ;}
pecker_vector4::pecker_vector4(const pecker_vector3 & vec3,Float w):x(vec3.x),y(vec3.y),z(vec3.z),w(w)
{ ;}
pecker_vector4::pecker_vector4(Float x,const pecker_vector3 & vec3):x(x),y(vec3.x),z(vec3.y),w(vec3.z)
{ ;}

pecker_vector4 & pecker_vector4::operator+=(const pecker_vector4 & Val)
{
  x += Val.x;
  y += Val.y;
  z += Val.z;
  w += Val.w;
  return *this;
}


pecker_vector4 & pecker_vector4::operator-=(const pecker_vector4 & Val)
{
  x -= Val.x;
  y -= Val.y;
  z -= Val.z;
  w -= Val.w;
  return *this;
}

pecker_vector4 & pecker_vector4::operator*=(const pecker_vector4 & Val)
{
  x *= Val.x;
  y *= Val.y;
  z *= Val.z;
  w *= Val.w;
  return *this;
}

pecker_vector4 & pecker_vector4::operator*=(Float Val)
{
  x *= Val;
  y *= Val;
  z *= Val;
  w *= Val;
  return *this;
}

pecker_vector4 & pecker_vector4::operator/=(const pecker_vector4 & Val)
{
  x /= Val.x;
  y /= Val.y;
  z /= Val.z;
  w /= Val.w;
  return *this;
}

pecker_vector4 & pecker_vector4::operator/=(Float Val)
{
  x /= Val;
  y /= Val;
  z /= Val;
  w /= Val;
  return *this;
}

pecker_vector4 pecker_vector4::operator+(const pecker_vector4 & Val) const
{
  pecker_vector4 res(*this);
  return (res += Val);
}

pecker_vector4 pecker_vector4::operator-(const pecker_vector4 & Val) const
{
  pecker_vector4 res(*this);
  return (res -= Val);
}

pecker_vector4 pecker_vector4::operator*(const pecker_vector4 & Val) const
{
  pecker_vector4 res(*this);
  return (res *= Val);
}

pecker_vector4 pecker_vector4::operator*(Float Val) const
{
  pecker_vector4 res(*this);
  return (res *= Val);
}

pecker_vector4 pecker_vector4::operator/(const pecker_vector4 & Val) const
{
  pecker_vector4 res(*this);
  return (res /= Val);
}


pecker_vector4 pecker_vector4::operator/(Float Val) const
{
  pecker_vector4 res(*this);
  return (res /= Val);
}

Bool pecker_vector4::operator==(const pecker_vector4 & Val) const
{
  return (EQFLOATZERO( x - Val.x ) && EQFLOATZERO( y - Val.y) && EQFLOATZERO( z - Val.z ) && EQFLOATZERO( w - Val.w ));
}

Bool pecker_vector4::operator!=(const pecker_vector4 & Val) const
{
  return ((!(EQFLOATZERO( x - Val.x ))) || (!(EQFLOATZERO( y - Val.y ))) || (!(EQFLOATZERO( z - Val.z ))) || (!EQFLOATZERO( w - Val.w )));
}

Float pecker_vector4::length_square() const
{
  return (x*x+y*y+z*z+w*w);
}

Float pecker_vector4::length() const
{
  Double dx = x;
  Double dy = y;
  Double dz = z;
  Double dw = w;
  return (Float)(sqrt(x*x+y*y+z*z+w*w));
}

pecker_vector4 pecker_vector4::normalize()
{
  return (*this /= length());
}

pecker_vector4 pecker_vector4::normalized() const
{
  pecker_vector4 res(*this);
  return (res /= length());
}

Float pecker_vector4::dot(const pecker_vector4 & other)
{
  return (x*other.x + y*other.y + z*other.z + w*other.w);
}

Float* pecker_vector4::get_data()
{
  return (Float*)this;
}

PECKER_END

