/*
 * pecker_matrix.h
 *
 *  Created on: 2012-7-25
 *      Author: ¿Ó’Ú≥« (cut / cutxyz)
 */

#ifndef PECKER_MATRIX_H_
#define PECKER_MATRIX_H_

#include "pecker_vector.h"

PECKER_BEGIN

struct pecker_matrix3;
struct pecker_matrix4;

typedef enum enumMat3Index
{
  M3_00 = 0,
  M3_01,
  M3_02,
  M3_10,
  M3_11,
  M3_12,
  M3_20,
  M3_21,
  M3_22,

  M3_INDEX_COUNT
}MAT3INDEX;

struct pecker_matrix3
{
public:
  Float m_Mat[9];
public:
  pecker_matrix3();
  pecker_matrix3(Float fVal);
  pecker_matrix3(const Float* fMat3);
  pecker_matrix3(Float fM00,Float fM01,Float fM02,
      Float fM10,Float fM11,Float fM12,
      Float fM20,Float fM21,Float fM22);
  pecker_matrix3(const pecker_matrix3 & other);
  pecker_matrix3(const pecker_matrix4 & Mat4);

  Float & operator()(nINDEX row, nINDEX column);
  Float operator()(nINDEX row, nINDEX column) const;

  pecker_matrix3 operator*(const pecker_matrix3 & Mat3) const;
  pecker_matrix3 operator*(Float fVal) const;

  pecker_matrix3 operator+(const pecker_matrix3 & Mat3) const;
  pecker_matrix3 operator-(const pecker_matrix3 & Mat3) const;

  pecker_matrix3 & operator*=(const pecker_matrix3 & Mat3);
  pecker_matrix3 & operator*=(Float fVal);

  pecker_matrix3 & operator+=(const pecker_matrix3 & Mat3);

  pecker_matrix3 & operator-=(const pecker_matrix3 & Mat3);

  Bool operator==(const pecker_matrix3 & Val) const;
  Bool operator!=(const pecker_matrix3 & Val) const;

  Float* get_data();

  Float determinant() const;
  pecker_matrix3 inverse() const;
  pecker_matrix3 transpose() const;

  static pecker_matrix3 identity_matrix3();
  static pecker_matrix3 rotationX(Float fAngle);
  static pecker_matrix3 rotationY(Float fAngle);
  static pecker_matrix3 rotationZ(Float fAngle);

  static pecker_matrix3 rotation2D(Float fAngle);

  static pecker_matrix3 scale(Float fx,Float fy,Float fz);
  static pecker_matrix3 scale2D(Float fx,Float fy);

  static pecker_matrix3 translation2D(Float fx, Float fy);
};

typedef enum enumMat4Index
{
  M4_00 = 0,
  M4_01,
  M4_02,
  M4_03,
  M4_10,
  M4_11,
  M4_12,
  M4_13,
  M4_20,
  M4_21,
  M4_22,
  M4_23,
  M4_30,
  M4_31,
  M4_32,
  M4_33,

  M4_INDEX_COUNT
}MAT4INDEX;

struct pecker_matrix4
{
public:
  Float m_Mat[16];
public:
  pecker_matrix4();
  pecker_matrix4(Float fVal);
  pecker_matrix4(const Float* fMat4);
  pecker_matrix4(Float fM00,Float fM01,Float fM02,Float fM03,
      Float fM10,Float fM11,Float fM12,Float fM13,
      Float fM20,Float fM21,Float fM22,Float fM23,
      Float fM30,Float fM31,Float fM32,Float fM33);
  pecker_matrix4(const pecker_matrix3 & Mat3);
  pecker_matrix4(const pecker_matrix4 & Mat4);

  Float & operator()(nINDEX row, nINDEX column);
  Float operator()(nINDEX row, nINDEX column) const;

  pecker_matrix4 operator*(const pecker_matrix4 & Mat4) const;
  pecker_vector4 operator*(const pecker_vector4 & vec4) const;
  pecker_matrix4 operator*(Float fVal) const;

  pecker_matrix4 operator+(const pecker_matrix4 & Mat4) const;

  pecker_matrix4 operator-(const pecker_matrix4 & Mat4) const;

  pecker_matrix4 & operator*=(const pecker_matrix4 & Mat4);
  pecker_matrix4 & operator*=(Float fVal);

  pecker_matrix4 & operator+=(const pecker_matrix4 & Mat4);
  pecker_matrix4 & operator-=(const pecker_matrix4 & Mat4);

  Bool operator==(const pecker_matrix4 & Val) const;
  Bool operator!=(const pecker_matrix4 & Val) const;

  Float* get_data();

  pecker_matrix4 inverse() const;
  pecker_matrix4 inverseEx() const;
  pecker_matrix4 transpose() const;

  pecker_matrix4 & post_translate(Float fx, Float fy, Float fz);
  pecker_matrix4 & post_translate(const pecker_vector3 & tvec);

  pecker_matrix4 & pre_translate(Float fx, Float fy, Float fz);
  pecker_matrix4 & pre_translate(const pecker_vector3 & tvec);

  static pecker_matrix4 identity_matrix4();
  static pecker_matrix4 rotationX(Float fAngle);
  static pecker_matrix4 rotationY(Float fAngle);
  static pecker_matrix4 rotationZ(Float fAngle);

  static pecker_matrix4 scale(Float fx,Float fy,Float fz);
  static pecker_matrix4 translation(Float fx, Float fy,Float fz);

  static pecker_matrix4 look_at(const pecker_vector3 & vEye, const pecker_vector3 & vAt, const pecker_vector3 & vUp, bool bRightHanded);

  static pecker_matrix4 look_at_RH(const pecker_vector3 & vEye, const pecker_vector3 & vAt, const pecker_vector3 & vUp);

  static pecker_matrix4 look_at_LH(const pecker_vector3 & vEye, const pecker_vector3 & vAt, const pecker_vector3 & vUp);

  static pecker_matrix4 orthogonal(Float left, Float top, Float right,
      Float bottom, Float nearPlane, Float farPlane, /*const eClipspace cs,*/Bool brotate = false);

  static pecker_matrix4 perspective(
      Float width, Float height,
      Float nearPlane, Float farPlane,
      //const eClipspace cs,
      Bool bRightHanded,
      Bool brotate = false);

  static pecker_matrix4 perspective_float_depth(
      Float width, Float height,
      Float nearPlane,
      //const eClipspace cs,
      Bool bRightHanded,
      Bool brotate = false);
  static pecker_matrix4 perspective_fov(
      Float fovy, Float aspect,
      Float nearPlane, Float farPlane,
      //const eClipspace cs,
      Bool bRightHanded,
      Bool brotate = false);
  static pecker_matrix4 perspective_fov_float_depth(
      Float fovy, Float aspect,
      Float nearPlane,
      //const eClipspace cs,
      Bool bRightHanded,
      Bool brotate = false);
};

PECKER_END

#endif /* PECKER_MATRIX_H_ */
