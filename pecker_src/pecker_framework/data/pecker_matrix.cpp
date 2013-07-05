/*
 * PeckerMatrix.cpp
 *
 *  Created on: 2012-7-25
 *      Author: 李镇城 (cut / cutxyz)
 */
#include "pecker_matrix.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../native/pecker_log.h"

PECKER_BEGIN

pecker_matrix3::pecker_matrix3()
{
//  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
//  {
//    m_Mat[i] = 0.0f;
//  }
}
pecker_matrix3::pecker_matrix3(Float fVal)
{
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    m_Mat[i] = fVal;
  }
}
pecker_matrix3::pecker_matrix3(const Float* fMat3)
{
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    m_Mat[i] = fMat3[i];
  }
}
pecker_matrix3::pecker_matrix3(Float fM00,Float fM01,Float fM02,
    Float fM10,Float fM11,Float fM12,
    Float fM20,Float fM21,Float fM22)
{
  m_Mat[M3_00] = fM00; m_Mat[M3_01] = fM01; m_Mat[M3_02] = fM02;
  m_Mat[M3_10] = fM10; m_Mat[M3_11] = fM11; m_Mat[M3_12] = fM12;
  m_Mat[M3_20] = fM20; m_Mat[M3_21] = fM21; m_Mat[M3_22] = fM22;
}

pecker_matrix3::pecker_matrix3(const pecker_matrix3 & other)
{
  if (&other != this)
  for (nINDEX i=0; i<M3_INDEX_COUNT; ++i)
  {
    m_Mat[i] = other.m_Mat[i];
  }
}

pecker_matrix3::pecker_matrix3(const pecker_matrix4 & Mat4)
{
  for(nINDEX i=0;i<3;++i)
  {
    m_Mat[i] = Mat4.m_Mat[i];
    m_Mat[i+3] = Mat4.m_Mat[i+4];
    m_Mat[i+6] = Mat4.m_Mat[i+8];
  }
}

Float & pecker_matrix3::operator()(nINDEX row, nINDEX column)
{
  return (m_Mat[row+column*3]);
}

Float pecker_matrix3::operator()(nINDEX row, nINDEX column) const
{
  return (m_Mat[row+column*3]);
}

pecker_matrix3 pecker_matrix3::operator*(const pecker_matrix3 & Mat3) const
{
  pecker_matrix3 res;

  // col 1
  res.m_Mat[M3_00] = m_Mat[M3_00]*Mat3.m_Mat[M3_00] + m_Mat[M3_10]*Mat3.m_Mat[M3_01] + m_Mat[M3_20]*Mat3.m_Mat[M3_02];
  res.m_Mat[M3_01] = m_Mat[M3_01]*Mat3.m_Mat[M3_00] + m_Mat[M3_11]*Mat3.m_Mat[M3_01] + m_Mat[M3_21]*Mat3.m_Mat[M3_02];
  res.m_Mat[M3_02] = m_Mat[M3_02]*Mat3.m_Mat[M3_00] + m_Mat[M3_12]*Mat3.m_Mat[M3_01] + m_Mat[M3_22]*Mat3.m_Mat[M3_02];

  // col 2
  res.m_Mat[M3_10] = m_Mat[M3_00]*Mat3.m_Mat[M3_10] + m_Mat[M3_10]*Mat3.m_Mat[M3_11] + m_Mat[M3_20]*Mat3.m_Mat[M3_12];
  res.m_Mat[M3_11] = m_Mat[M3_01]*Mat3.m_Mat[M3_10] + m_Mat[M3_11]*Mat3.m_Mat[M3_11] + m_Mat[M3_21]*Mat3.m_Mat[M3_12];
  res.m_Mat[M3_12] = m_Mat[M3_02]*Mat3.m_Mat[M3_10] + m_Mat[M3_12]*Mat3.m_Mat[M3_11] + m_Mat[M3_22]*Mat3.m_Mat[M3_12];

  // col3
  res.m_Mat[M3_20] = m_Mat[M3_00]*Mat3.m_Mat[M3_20] + m_Mat[M3_10]*Mat3.m_Mat[M3_21] + m_Mat[M3_20]*Mat3.m_Mat[M3_22];
  res.m_Mat[M3_21] = m_Mat[M3_01]*Mat3.m_Mat[M3_20] + m_Mat[M3_11]*Mat3.m_Mat[M3_21] + m_Mat[M3_21]*Mat3.m_Mat[M3_22];
  res.m_Mat[M3_22] = m_Mat[M3_02]*Mat3.m_Mat[M3_20] + m_Mat[M3_12]*Mat3.m_Mat[M3_21] + m_Mat[M3_22]*Mat3.m_Mat[M3_22];

  return res;
}

pecker_matrix3 pecker_matrix3::operator*(Float fVal) const
{
  pecker_matrix3 res;
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    res.m_Mat[i] = m_Mat[i] * fVal;
  }
  return res;
}

pecker_matrix3 pecker_matrix3::operator+(const pecker_matrix3 & Mat3) const
{
  pecker_matrix3 res;
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    res.m_Mat[i] = m_Mat[i] + Mat3.m_Mat[i];
  }
  return res;
}

pecker_matrix3 pecker_matrix3::operator-(const pecker_matrix3 & Mat3) const
{
  pecker_matrix3 res;
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    res.m_Mat[i] = m_Mat[i] - Mat3.m_Mat[i];
  }
  return res;
}

pecker_matrix3 & pecker_matrix3::operator*=(const pecker_matrix3 & Mat3)
{
  pecker_matrix3 tmpMat(*this);
  *this = tmpMat * Mat3;
  return *this;
}


pecker_matrix3 & pecker_matrix3::operator*=(Float fVal)
{
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    m_Mat[i] *= fVal;
  }
  return *this;
}

pecker_matrix3 & pecker_matrix3::operator+=(const pecker_matrix3 & Mat3)
{
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    m_Mat[i] += Mat3.m_Mat[i];
  }
  return *this;
}

pecker_matrix3 & pecker_matrix3::operator-=(const pecker_matrix3 & Mat3)
{
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    m_Mat[i] -= Mat3.m_Mat[i];
  }
  return *this;
}


Bool pecker_matrix3::operator==(const pecker_matrix3 & Val) const
{
  Bool res = true;
  for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
  {
    if(!EQFLOATZERO(m_Mat[i]-Val.m_Mat[i]))
    {
      res = false;
      break;
    }
  }
  return res;
}

Bool pecker_matrix3::operator!=(const pecker_matrix3 & Val) const
{
  return !(*this == Val);
}

Float* pecker_matrix3::get_data()
{
  return (Float*)this;
}

Float pecker_matrix3::determinant() const
{

  return ( m_Mat[M3_00]*(m_Mat[M3_11]*m_Mat[M3_22]-m_Mat[M3_21]*m_Mat[M3_12])
      - m_Mat[M3_10]*(m_Mat[M3_01]*m_Mat[M3_22]-m_Mat[M3_21]*m_Mat[M3_02])
      + m_Mat[M3_20]*(m_Mat[M3_01]*m_Mat[M3_12]-m_Mat[M3_11]*m_Mat[M3_02]) );
}

pecker_matrix3 pecker_matrix3::inverse() const
{
  pecker_matrix3 res;
  Float fDet = determinant();
  // 0 == fDet
  if (EQFLOATZERO(fDet))
  {
    for (nINDEX i=0;i<M3_INDEX_COUNT;++i)
    {
      res.m_Mat[i] = 0.0f;
    }

    //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix3::inverse","determinant == 0.0f");
	PECKER_LOG_ERR("CMatrix3::inverse","determinant == 0.0f",0);
    return res;
  }

  fDet = 1.0f/fDet;

  res.m_Mat[M3_00] = m_Mat[M3_11]*m_Mat[M3_22] - m_Mat[M3_12]*m_Mat[M3_21];
  res.m_Mat[M3_01] = m_Mat[M3_02]*m_Mat[M3_21] - m_Mat[M3_01]*m_Mat[M3_22];
  res.m_Mat[M3_02] = m_Mat[M3_01]*m_Mat[M3_12] - m_Mat[M3_02]*m_Mat[M3_11];

  res.m_Mat[M3_10] = m_Mat[M3_12]*m_Mat[M3_20] - m_Mat[M3_10]*m_Mat[M3_22];
  res.m_Mat[M3_11] = m_Mat[M3_00]*m_Mat[M3_22] - m_Mat[M3_02]*m_Mat[M3_20];
  res.m_Mat[M3_12] = m_Mat[M3_02]*m_Mat[M3_10] - m_Mat[M3_00]*m_Mat[M3_12];

  res.m_Mat[M3_20] = m_Mat[M3_10]*m_Mat[M3_21] - m_Mat[M3_11]*m_Mat[M3_20];
  res.m_Mat[M3_21] = m_Mat[M3_01]*m_Mat[M3_20] - m_Mat[M3_00]*m_Mat[M3_21];
  res.m_Mat[M3_22] = m_Mat[M3_00]*m_Mat[M3_11] - m_Mat[M3_01]*m_Mat[M3_10];

  return (res *= fDet);
}

pecker_matrix3 pecker_matrix3::transpose() const
{
  pecker_matrix3 res;
  res.m_Mat[M3_00] = m_Mat[M3_00]; res.m_Mat[M3_10] = m_Mat[M3_01]; res.m_Mat[M3_20] = m_Mat[M3_02];
  res.m_Mat[M3_01] = m_Mat[M3_10]; res.m_Mat[M3_11] = m_Mat[M3_11]; res.m_Mat[M3_21] = m_Mat[M3_12];
  res.m_Mat[M3_02] = m_Mat[M3_20]; res.m_Mat[M3_12] = m_Mat[M3_21]; res.m_Mat[M3_22] = m_Mat[M3_22];
  return res;
}

pecker_matrix3 pecker_matrix3::identity_matrix3()
{
  pecker_matrix3 res;
  res.m_Mat[M3_00] = 1.0f; res.m_Mat[M3_10] = 0.0f; res.m_Mat[M3_20] = 0.0f;
  res.m_Mat[M3_01] = 0.0f; res.m_Mat[M3_11] = 1.0f; res.m_Mat[M3_21] = 0.0f;
  res.m_Mat[M3_02] = 0.0f; res.m_Mat[M3_12] = 0.0f; res.m_Mat[M3_22] = 1.0f;
  return res;
}

pecker_matrix3 pecker_matrix3::rotationX(Float fAngle)
{
  pecker_matrix3 res;
  Float fCosine, fSine;

  /* Precompute cos and sin */
#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
  fCosine = (Float)cos((Double)(-fAngle));
  fSine = (Float)sin((Double)(-fAngle));
#else
  fCosine = (Float)cos((Double)(fAngle));
  fSine = (Float)sin((Double)(fAngle));
#endif

  /* Create the trigonometric matrix corresponding to X rotation */
  res.m_Mat[M3_00]=1.0f; res.m_Mat[M3_10]=0.0f;    res.m_Mat[M3_20]=0.0f;
  res.m_Mat[M3_01]=0.0f; res.m_Mat[M3_11]=fCosine; res.m_Mat[M3_21]=fSine;
  res.m_Mat[M3_02]=0.0f; res.m_Mat[M3_12]=-fSine;  res.m_Mat[M3_22]=fCosine;

  return res;
}

pecker_matrix3 pecker_matrix3::rotationY(Float fAngle)
{
  pecker_matrix3 res;
  Float fCosine, fSine;

  /* Precompute cos and sin */
#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
  fCosine = (Float)cos((Double)(-fAngle));
  fSine = (Float)sin((Double)(-fAngle));
#else
  fCosine = (Float)cos((Double)(fAngle));
  fSine = (Float)sin((Double)(fAngle));
#endif

  /* Create the trigonometric matrix corresponding to Y rotation */
  res.m_Mat[M3_00]=fCosine; res.m_Mat[M3_10]=0.0f; res.m_Mat[M3_20]=-fSine;
  res.m_Mat[M3_01]=0.0f;    res.m_Mat[M3_11]=1.0f; res.m_Mat[M3_21]=0.0f;
  res.m_Mat[M3_02]=fSine;   res.m_Mat[M3_12]=0.0f; res.m_Mat[M3_22]=fCosine;

  return res;
}

pecker_matrix3 pecker_matrix3::rotationZ(Float fAngle)
{
  pecker_matrix3 res;
  Float fCosine, fSine;

  /* Precompute cos and sin */
#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
  fCosine = (Float)cos((Double)(-fAngle));
  fSine = (Float)sin((Double)(-fAngle));
#else
  fCosine = (Float)cos((Double)(fAngle));
  fSine = (Float)sin((Double)(fAngle));
#endif
  /* Create the trigonometric matrix corresponding to Z rotation */
  res.m_Mat[M3_00]=fCosine; res.m_Mat[M3_10]=fSine;   res.m_Mat[M3_20]=0.0f;
  res.m_Mat[M3_01]=-fSine;  res.m_Mat[M3_11]=fCosine; res.m_Mat[M3_21]=0.0f;
  res.m_Mat[M3_02]=0.0f;    res.m_Mat[M3_12]=0.0f;    res.m_Mat[M3_22]=1.0f;

  return res;
}

pecker_matrix3 pecker_matrix3::rotation2D(Float fAngle)
{
  pecker_matrix3 res;
  Float fCosine, fSine;

  /* Precompute cos and sin */
#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
  fCosine = (Float)cos((Double)(-fAngle));
  fSine = (Float)sin((Double)(-fAngle));
#else
  fCosine = (Float)cos((Double)(fAngle));
  fSine = (Float)sin((Double)(fAngle));
#endif
  /* Create the trigonometric matrix corresponding to Z rotation */
  res.m_Mat[M3_00]=fCosine; res.m_Mat[M3_10]=fSine;   res.m_Mat[M3_20]=0.0f;
  res.m_Mat[M3_01]=-fSine;  res.m_Mat[M3_11]=fCosine; res.m_Mat[M3_21]=0.0f;
  res.m_Mat[M3_02]=0.0f;    res.m_Mat[M3_12]=0.0f;    res.m_Mat[M3_22]=1.0f;

  return res;
}

pecker_matrix3 pecker_matrix3::scale(Float fx,Float fy,Float fz)
{
  return pecker_matrix3( fx ,0.0f,0.0f,
                  0.0f, fy ,0.0f,
                  0.0f,0.0f, fz );
}
pecker_matrix3 pecker_matrix3::scale2D(Float fx,Float fy)
{
  return pecker_matrix3( fx ,0.0f,0.0f,
                  0.0f, fy ,0.0f,
                  0.0f,0.0f,1.0f );
}

pecker_matrix3 pecker_matrix3::translation2D(Float fx, Float fy)
{
  return pecker_matrix3( 1.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                    fx , fy , 1.0f);
//    return CMatrix3( 1.0f, 0.0f, fx,
//                     0.0f, 1.0f, fy,
//                     0.0f, 0.0f, 1.0f);
}


pecker_matrix4::pecker_matrix4()
{ ;}
pecker_matrix4::pecker_matrix4(Float fVal)
{ ;}
pecker_matrix4::pecker_matrix4(const Float* fMat4)
{
  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    m_Mat[i] = fMat4[i];
  }
}
pecker_matrix4::pecker_matrix4(Float fM00,Float fM01,Float fM02,Float fM03,
    Float fM10,Float fM11,Float fM12,Float fM13,
    Float fM20,Float fM21,Float fM22,Float fM23,
    Float fM30,Float fM31,Float fM32,Float fM33)
{
  m_Mat[M4_00] = fM00; m_Mat[M4_01] = fM01; m_Mat[M4_02] = fM02; m_Mat[M4_03] = fM03;
  m_Mat[M4_10] = fM10; m_Mat[M4_11] = fM11; m_Mat[M4_12] = fM12; m_Mat[M4_13] = fM13;
  m_Mat[M4_20] = fM20; m_Mat[M4_21] = fM21; m_Mat[M4_22] = fM22; m_Mat[M4_23] = fM23;
  m_Mat[M4_30] = fM30; m_Mat[M4_31] = fM31; m_Mat[M4_32] = fM32; m_Mat[M4_33] = fM33;
}

pecker_matrix4::pecker_matrix4(const pecker_matrix3 & Mat3)
{
  for (nINDEX i=0;i<3;++i)
  {
    m_Mat[i]   = Mat3.m_Mat[i];
    m_Mat[i+4] = Mat3.m_Mat[i+3];
    m_Mat[i+8] = Mat3.m_Mat[i+6];
  }

  m_Mat[M4_03] = 0.0f;
  m_Mat[M4_13] = 0.0f;
  m_Mat[M4_23] = 0.0f;

  m_Mat[M4_30] = 0.0f;
  m_Mat[M4_31] = 0.0f;
  m_Mat[M4_32] = 0.0f;

  m_Mat[M4_33] = 1.0f;
}


pecker_matrix4::pecker_matrix4(const pecker_matrix4 & Mat4)
{
  if (&Mat4 != this)
  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    m_Mat[i] = Mat4.m_Mat[i];
  }
}

Float & pecker_matrix4::operator()(nINDEX row, nINDEX column)
{
  return (m_Mat[row + column*4]);
}
Float pecker_matrix4::operator()(nINDEX row, nINDEX column) const
{
  return (m_Mat[row + column*4]);
}

pecker_matrix4 pecker_matrix4::operator*(const pecker_matrix4 & Mat4) const
{
  pecker_matrix4 res;

  // col 0
  res.m_Mat[M4_00] =  m_Mat[M4_00]*Mat4.m_Mat[M4_00] +  m_Mat[M4_10]*Mat4.m_Mat[M4_01] + m_Mat[M4_20]*Mat4.m_Mat[M4_02] + m_Mat[M4_30]*Mat4.m_Mat[M4_03];
  res.m_Mat[M4_01] =  m_Mat[M4_01]*Mat4.m_Mat[M4_00] +  m_Mat[M4_11]*Mat4.m_Mat[M4_01] + m_Mat[M4_21]*Mat4.m_Mat[M4_02] + m_Mat[M4_31]*Mat4.m_Mat[M4_03];
  res.m_Mat[M4_02] =  m_Mat[M4_02]*Mat4.m_Mat[M4_00] +  m_Mat[M4_12]*Mat4.m_Mat[M4_01] + m_Mat[M4_22]*Mat4.m_Mat[M4_02] + m_Mat[M4_32]*Mat4.m_Mat[M4_03];
  res.m_Mat[M4_03] =  m_Mat[M4_03]*Mat4.m_Mat[M4_00] +  m_Mat[M4_13]*Mat4.m_Mat[M4_01] + m_Mat[M4_23]*Mat4.m_Mat[M4_02] + m_Mat[M4_33]*Mat4.m_Mat[M4_03];
  // col 1
  res.m_Mat[M4_10] =  m_Mat[M4_00]*Mat4.m_Mat[M4_10] +  m_Mat[M4_10]*Mat4.m_Mat[M4_11] + m_Mat[M4_20]*Mat4.m_Mat[M4_12] + m_Mat[M4_30]*Mat4.m_Mat[M4_13];
  res.m_Mat[M4_11] =  m_Mat[M4_01]*Mat4.m_Mat[M4_10] +  m_Mat[M4_11]*Mat4.m_Mat[M4_11] + m_Mat[M4_21]*Mat4.m_Mat[M4_12] + m_Mat[M4_31]*Mat4.m_Mat[M4_13];
  res.m_Mat[M4_12] =  m_Mat[M4_02]*Mat4.m_Mat[M4_10] +  m_Mat[M4_12]*Mat4.m_Mat[M4_11] + m_Mat[M4_22]*Mat4.m_Mat[M4_12] + m_Mat[M4_32]*Mat4.m_Mat[M4_13];
  res.m_Mat[M4_13] =  m_Mat[M4_03]*Mat4.m_Mat[M4_10] +  m_Mat[M4_13]*Mat4.m_Mat[M4_10] + m_Mat[M4_23]*Mat4.m_Mat[M4_12] + m_Mat[M4_33]*Mat4.m_Mat[M4_13];

  // col 2
  res.m_Mat[M4_20] =  m_Mat[M4_00]*Mat4.m_Mat[M4_20] +  m_Mat[M4_10]*Mat4.m_Mat[M4_21] + m_Mat[M4_20]*Mat4.m_Mat[M4_22] + m_Mat[M4_30]*Mat4.m_Mat[M4_23];
  res.m_Mat[M4_21] =  m_Mat[M4_01]*Mat4.m_Mat[M4_20] +  m_Mat[M4_11]*Mat4.m_Mat[M4_21] + m_Mat[M4_21]*Mat4.m_Mat[M4_22] + m_Mat[M4_31]*Mat4.m_Mat[M4_23];
  res.m_Mat[M4_22] = m_Mat[M4_02]*Mat4.m_Mat[M4_20] +  m_Mat[M4_12]*Mat4.m_Mat[M4_21] + m_Mat[M4_22]*Mat4.m_Mat[M4_22] + m_Mat[M4_32]*Mat4.m_Mat[M4_23];
  res.m_Mat[M4_23] = m_Mat[M4_03]*Mat4.m_Mat[M4_20] +  m_Mat[M4_13]*Mat4.m_Mat[M4_21] + m_Mat[M4_23]*Mat4.m_Mat[M4_22] + m_Mat[M4_33]*Mat4.m_Mat[M4_23];

  // col 3
  res.m_Mat[M4_30] =  m_Mat[M4_00]*Mat4.m_Mat[M4_30] +  m_Mat[M4_10]*Mat4.m_Mat[M4_31] + m_Mat[M4_20]*Mat4.m_Mat[M4_32] + m_Mat[M4_30]*Mat4.m_Mat[M4_33];
  res.m_Mat[M4_31] =  m_Mat[M4_01]*Mat4.m_Mat[M4_30] +  m_Mat[M4_11]*Mat4.m_Mat[M4_31] + m_Mat[M4_21]*Mat4.m_Mat[M4_32] + m_Mat[M4_31]*Mat4.m_Mat[M4_33];
  res.m_Mat[M4_32] =  m_Mat[M4_02]*Mat4.m_Mat[M4_30] +  m_Mat[M4_12]*Mat4.m_Mat[M4_31] + m_Mat[M4_22]*Mat4.m_Mat[M4_32] + m_Mat[M4_32]*Mat4.m_Mat[M4_33];
  res.m_Mat[M4_33] =  m_Mat[M4_03]*Mat4.m_Mat[M4_30] +  m_Mat[M4_13]*Mat4.m_Mat[M4_31] + m_Mat[M4_23]*Mat4.m_Mat[M4_32] + m_Mat[M4_33]*Mat4.m_Mat[M4_33];


  return res;
}

pecker_vector4 pecker_matrix4::operator*(const pecker_vector4 & vec4) const
{
  return pecker_vector4(vec4.x*m_Mat[M4_00] + vec4.y*m_Mat[M4_10] + vec4.z*m_Mat[M4_20] + vec4.w*m_Mat[M4_30],
                  vec4.x*m_Mat[M4_01] + vec4.y*m_Mat[M4_11] + vec4.z*m_Mat[M4_21] + vec4.w*m_Mat[M4_31],
                  vec4.x*m_Mat[M4_02] + vec4.y*m_Mat[M4_12] + vec4.z*m_Mat[M4_22] + vec4.w*m_Mat[M4_32],
                  vec4.x*m_Mat[M4_03] + vec4.y*m_Mat[M4_13] + vec4.z*m_Mat[M4_23] + vec4.w*m_Mat[M4_33]);
}

pecker_matrix4 pecker_matrix4::operator*(Float fVal) const
{
  pecker_matrix4 res;

  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    res.m_Mat[i] = m_Mat[i] * fVal;
  }

  return res;
}

pecker_matrix4 pecker_matrix4::operator+(const pecker_matrix4 & Mat4) const
{
  pecker_matrix4 res;

  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    res.m_Mat[i] = m_Mat[i] + Mat4.m_Mat[i];
  }

  return res;
}

pecker_matrix4 pecker_matrix4::operator-(const pecker_matrix4 & Mat4) const
{
  pecker_matrix4 res;

  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    res.m_Mat[i] = m_Mat[i] - Mat4.m_Mat[i];
  }

  return res;
}


pecker_matrix4 & pecker_matrix4::operator*=(const pecker_matrix4 & Mat4)
{
  pecker_matrix4 tmpMat4(*this);
  *this = tmpMat4 * Mat4;
  return *this;
}


pecker_matrix4 & pecker_matrix4::operator*=(Float fVal)
{
  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    m_Mat[i] *= fVal;
  }
  return *this;
}

pecker_matrix4 & pecker_matrix4::operator+=(const pecker_matrix4 & Mat4)
{
  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    m_Mat[i] += Mat4.m_Mat[i];
  }
  return *this;
}

pecker_matrix4 & pecker_matrix4::operator-=(const pecker_matrix4 & Mat4)
{
  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    m_Mat[i] -= Mat4.m_Mat[i];
  }
  return *this;
}


Bool pecker_matrix4::operator==(const pecker_matrix4 & Val) const
{
  Bool res = true;
  for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
  {
    if(!EQFLOATZERO(m_Mat[i]-Val.m_Mat[i]))
    {
      res = false;
      break;
    }
  }
  return res;
}

Bool pecker_matrix4::operator!=(const pecker_matrix4 & Val) const
{
  return !(*this == Val);
}


Float* pecker_matrix4::get_data()
{
  return (Float*)this;
}

pecker_matrix4 pecker_matrix4::inverse() const
{
//    matrix A 0 3X3
//    matrix C 1 3X1
//
//    ┌     (matrix A)            │             ┐
//    │   M00     M01     M02     │     M03     │
//    │   M10     M12     M13     │     M14     │
//    │   M20     M21     M22     │     M23     │
//    ├───────────────────────────┤             │
//    │   M30     M31     M32     │     M33     │
//    └ (matrix C)                │             ┘
  Float fMatADet = ( m_Mat[M4_00]*(m_Mat[M4_11]*m_Mat[M4_22]-m_Mat[M4_21]*m_Mat[M4_12])
        - m_Mat[M4_10]*(m_Mat[M4_01]*m_Mat[M4_22]-m_Mat[M4_21]*m_Mat[M4_02])
        + m_Mat[M4_20]*(m_Mat[M4_01]*m_Mat[M4_12]-m_Mat[M4_11]*m_Mat[M4_02]) );

  pecker_matrix4 res;
  // matrix A 行列式值为0,退出计算
  if (EQFLOATZERO(fMatADet))
   {
     for (nINDEX i=0;i<M4_INDEX_COUNT;++i)
     {
       res.m_Mat[i] = 0.0f;
     }

     //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix4::inverse","matrix A determinant == 0.0f");
	 PECKER_LOG_ERR("CMatrix4::inverse","matrix A determinant == 0.0f",0);

     return res;
   }

  fMatADet = 1.0f/fMatADet;
  //　inverse(matrix A)
  res.m_Mat[M4_00] = (m_Mat[M4_11]*m_Mat[M4_22] - m_Mat[M4_12]*m_Mat[M4_21]) * fMatADet;
  res.m_Mat[M4_01] = (m_Mat[M4_02]*m_Mat[M4_21] - m_Mat[M4_01]*m_Mat[M4_22]) * fMatADet;
  res.m_Mat[M4_02] = (m_Mat[M4_01]*m_Mat[M4_12] - m_Mat[M4_02]*m_Mat[M4_11]) * fMatADet;

  res.m_Mat[M4_10] = (m_Mat[M4_12]*m_Mat[M4_20] - m_Mat[M4_10]*m_Mat[M4_22]) * fMatADet;
  res.m_Mat[M4_11] = (m_Mat[M4_00]*m_Mat[M4_22] - m_Mat[M4_02]*m_Mat[M4_20]) * fMatADet;
  res.m_Mat[M4_12] = (m_Mat[M4_02]*m_Mat[M4_10] - m_Mat[M4_00]*m_Mat[M4_12]) * fMatADet;

  res.m_Mat[M4_20] = (m_Mat[M4_10]*m_Mat[M4_21] - m_Mat[M4_11]*m_Mat[M4_20]) * fMatADet;
  res.m_Mat[M4_21] = (m_Mat[M4_01]*m_Mat[M4_20] - m_Mat[M4_00]*m_Mat[M4_21]) * fMatADet;
  res.m_Mat[M4_22] = (m_Mat[M4_00]*m_Mat[M4_11] - m_Mat[M4_01]*m_Mat[M4_10]) * fMatADet;

  // - matrix C * inverse(matrix A)
  res.m_Mat[M4_30] = - ( m_Mat[M4_30]*res.m_Mat[M4_00] + m_Mat[M4_31]*res.m_Mat[M4_10] + m_Mat[M4_32]*res.m_Mat[M4_20] );
  res.m_Mat[M4_31] = - ( m_Mat[M4_30]*res.m_Mat[M4_01] + m_Mat[M4_31]*res.m_Mat[M4_11] + m_Mat[M4_32]*res.m_Mat[M4_21] );
  res.m_Mat[M4_32] = - ( m_Mat[M4_30]*res.m_Mat[M4_02] + m_Mat[M4_31]*res.m_Mat[M4_12] + m_Mat[M4_32]*res.m_Mat[M4_22] );

  //
  res.m_Mat[M4_03] = 0.0f;
  res.m_Mat[M4_13] = 0.0f;
  res.m_Mat[M4_23] = 0.0f;
  res.m_Mat[M4_33] = 1.0f;

  return res;
}



HResult LinearEqSolve(Float* PARAM_INOUT pRes, Float ** PARAM_INOUT pSrc,nSize nCnt)
{
  if (null == pRes || null == pSrc)
  {
    return PEK_STATUS_FAIL;
  }

  if (1 == nCnt)
  {
    if (0 == pSrc[ 0 ][ 1 ])
    {
      return PEK_STATUS_FAIL;
    }
    pRes[ 0 ] = pSrc[ 0 ][ 0 ]/pSrc[ 0 ][ 1 ];
    return PEK_STATUS_OK;
  }

  Float ftempVal;
  // Loop backwards in an attempt avoid the need to swap rows
  for (nINDEX i=nCnt-1;i>=0;--i)
  {
    if (EQFLOATZERO( pSrc[i][nCnt]) )
    {
      for (nINDEX j=0;j<=nCnt;++j)
      {
        // Swap the two values
        ftempVal = pSrc[nCnt-1][j];
        pSrc[nCnt-1][j] = pSrc[i][j];
        pSrc[i][j] = ftempVal;
      }

      // Now zero the last columns of the top rows
      nSize ntmpCnt = nCnt-1;

      if (EQFLOATZERO(pSrc[ntmpCnt][nCnt]))
      {
        return PEK_STATUS_FAIL;
      }
      for (nINDEX j=0;j<ntmpCnt;++j)
      {
        ftempVal = pSrc[j][nCnt] / pSrc[ntmpCnt][nCnt];
        for (nINDEX k=0;k<nCnt;++k)
        {
          pSrc[j][k] -= ftempVal*pSrc[ntmpCnt][k];
        }
      }

      break;
    }

    HResult res = LinearEqSolve(pRes, pSrc, nCnt-1);
    if (PEK_STATUS_OK != res)
    {
      return res;
    }
  }

  // Now calc the solution for the bottom row
  ftempVal = pSrc[nCnt-1][M4_00];
  for (nINDEX k = 1; k < nCnt; ++k)
  {
    ftempVal -= pSrc[nCnt-1][k]*pRes[k-1];
  }

  if (EQFLOATZERO(pSrc[nCnt-1][nCnt]))
  {
    return PEK_STATUS_FAIL;
  }

  ftempVal = ftempVal / pSrc[nCnt-1][nCnt];
  pRes[nCnt-1] = ftempVal;

  return PEK_STATUS_OK;
}

// M.M^-1=I.
pecker_matrix4 pecker_matrix4::inverseEx() const
{
  pecker_matrix4 resMat;
  Float arrMat[20];
  Float arrRes[M4_10];
  Float* arrpArrMat[M4_10];
  const pecker_matrix4 idMat4 = pecker_matrix4::identity_matrix4();

  arrpArrMat[M4_00] = &arrMat[M4_00];
  arrpArrMat[M4_01] = &arrMat[M4_11];
  arrpArrMat[M4_02] = &arrMat[M4_22];
  arrpArrMat[M4_03] = &arrMat[M4_33];

  HResult res =  PEK_STATUS_OK;

  for (nINDEX i=0; i<4; ++i)
  {
    for (nINDEX j=0;j<4;++j)
    {
      arrpArrMat[j][M4_00] = idMat4.m_Mat[i + 4*j];
      memcpy(&arrpArrMat[j][M4_01],&m_Mat[4*j],4*sizeof(Float));
    }
    res = LinearEqSolve(arrRes, (Float**)arrpArrMat, 4);
    if (PEK_STATUS_OK != res)
    {
      //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix4::inverseEx","LinearEqSolve errors!");
		PECKER_LOG_ERR("CMatrix4::inverseEx","LinearEqSolve errors!",0);
      break;
    }
    for (nINDEX j=0; j<4; ++j)
    {
      resMat.m_Mat[i + 4 * j] = arrRes[j];
    }

  }

  return resMat;
}
pecker_matrix4 pecker_matrix4::transpose() const
{
  pecker_matrix4 res;
  res.m_Mat[M4_00] = m_Mat[M4_00];                res.m_Mat[M4_01] = m_Mat[M4_10];                res.m_Mat[M4_02] = m_Mat[M4_20];                res.m_Mat[M4_03] = m_Mat[ M4_30];
  res.m_Mat[M4_10] = m_Mat[M4_01];                res.m_Mat[M4_11] = m_Mat[M4_11];                res.m_Mat[M4_12] = m_Mat[M4_21];                res.m_Mat[M4_13] = m_Mat[M4_31];
  res.m_Mat[M4_20] = m_Mat[M4_02];                res.m_Mat[M4_21] = m_Mat[M4_12];                res.m_Mat[M4_22] = m_Mat[M4_22];              res.m_Mat[M4_23] = m_Mat[M4_32];
  res.m_Mat[ M4_30] = m_Mat[M4_03];               res.m_Mat[M4_31] = m_Mat[M4_13];               res.m_Mat[M4_32] = m_Mat[M4_23];              res.m_Mat[M4_33] = m_Mat[M4_33];
  return res;
}

pecker_matrix4 & pecker_matrix4::post_translate(Float fx, Float fy, Float fz)
{
  // col(3) += fx * col(0) + fy * col(1) + fz * col(2);
  m_Mat[ M4_30] += (fx*m_Mat[M4_00] + fy*m_Mat[M4_10] + fz*m_Mat[M4_20]);
  m_Mat[M4_31] += (fx*m_Mat[M4_01] + fy*m_Mat[M4_11] + fz*m_Mat[M4_21]);
  m_Mat[M4_32] += (fx*m_Mat[M4_02] + fy*m_Mat[M4_12] + fz*m_Mat[M4_22]);
  m_Mat[M4_33] += (fx*m_Mat[M4_03] + fy*m_Mat[M4_13] + fz*m_Mat[M4_23]);

  return *this;
}

pecker_matrix4 & pecker_matrix4::post_translate(const pecker_vector3 & vec)
{
  return post_translate(vec.x,vec.y,vec.z);
}


pecker_matrix4 & pecker_matrix4::pre_translate(Float fx, Float fy, Float fz)
{
  //  row(0) += fx * row(3);
  //  row(1) += fy * row(3);
  //  row(2) += fz * row(3);
  m_Mat[M4_00] += m_Mat[M4_03] * fx;    m_Mat[M4_10] += m_Mat[M4_13]*fx;        m_Mat[M4_20] += m_Mat[M4_23]*fx;       m_Mat[ M4_30] += m_Mat[M4_33]*fx;
  m_Mat[M4_01] += m_Mat[M4_03] * fy;    m_Mat[M4_10] += m_Mat[M4_13]*fy;        m_Mat[M4_20] += m_Mat[M4_23]*fy;       m_Mat[ M4_30] += m_Mat[M4_33]*fy;
  m_Mat[M4_02] += m_Mat[M4_03] * fz;    m_Mat[M4_10] += m_Mat[M4_13]*fz;        m_Mat[M4_20] += m_Mat[M4_23]*fz;       m_Mat[ M4_30] += m_Mat[M4_33]*fz;

  return *this;
}

pecker_matrix4 & pecker_matrix4::pre_translate(const pecker_vector3 & vec)
{
  return pre_translate(vec.x,vec.y,vec.z);
}


pecker_matrix4 pecker_matrix4::identity_matrix4()
{
  return pecker_matrix4(1.0f,0.0f,0.0f,0.0f,
                  0.0f,1.0f,0.0f,0.0f,
                  0.0f,0.0f,1.0f,0.0f,
                  0.0f,0.0f,0.0f,1.0f);
}

pecker_matrix4 pecker_matrix4::rotationX(Float fAngle)
{
  pecker_matrix4 res;
  Float fCosine, fSine;

  /* Precompute cos and sin */
#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
  fCosine = (Float)cos((Double)(-fAngle));
  fSine = (Float)sin((Double)(-fAngle));
#else
  fCosine = (Float)cos((Double)(fAngle));
  fSine = (Float)sin((Double)(fAngle));
#endif

  /* Create the trigonometric matrix corresponding to X rotation */
  res.m_Mat[M4_00]=1.0f; res.m_Mat[M4_10]=0.0f;    res.m_Mat[M4_20]=0.0f;     res.m_Mat[M4_30]=0.0f;
  res.m_Mat[M4_01]=0.0f; res.m_Mat[M4_11]=fCosine; res.m_Mat[M4_21]=fSine;    res.m_Mat[M4_31]=0.0f;
  res.m_Mat[M4_02]=0.0f; res.m_Mat[M4_12]=-fSine;  res.m_Mat[M4_22]=fCosine;  res.m_Mat[M4_32]=0.0f;
  res.m_Mat[M4_03]=0.0f; res.m_Mat[M4_13]=0.0f;    res.m_Mat[M4_23]=0.0f;     res.m_Mat[M4_33]=1.0f;
  return res;
}
pecker_matrix4 pecker_matrix4::rotationY(Float fAngle)
{
  pecker_matrix4 res;
  Float fCosine, fSine;

  /* Precompute cos and sin */
#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
  fCosine = (Float)cos((Double)(-fAngle));
  fSine = (Float)sin((Double)(-fAngle));
#else
  fCosine = (Float)cos((Double)(fAngle));
  fSine = (Float)sin((Double)(fAngle));
#endif

  /* Create the trigonometric matrix corresponding to Y rotation */
  res.m_Mat[M4_00]=fCosine; res.m_Mat[M4_10]=0.0f; res.m_Mat[M4_20]=-fSine;     res.m_Mat[M4_30]=0.0f;
  res.m_Mat[M4_01]=0.0f;    res.m_Mat[M4_11]=1.0f; res.m_Mat[M4_21]=0.0f;       res.m_Mat[M4_31]=0.0f;
  res.m_Mat[M4_02]=fSine;   res.m_Mat[M4_12]=0.0f; res.m_Mat[M4_22]=fCosine;    res.m_Mat[M4_32]=0.0f;
  res.m_Mat[M4_03]=0.0f;    res.m_Mat[M4_13]=0.0f; res.m_Mat[M4_23]=0.0f;       res.m_Mat[M4_33]=1.0f;
  return res;
}
pecker_matrix4 pecker_matrix4::rotationZ(Float fAngle)
{
  pecker_matrix4 res;
  Float fCosine, fSine;

  /* Precompute cos and sin */
#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
  fCosine = (Float)cos((Double)(-fAngle));
  fSine = (Float)sin((Double)(-fAngle));
#else
  fCosine = (Float)cos((Double)(fAngle));
  fSine = (Float)sin((Double)(fAngle));
#endif
  /* Create the trigonometric matrix corresponding to Z rotation */
  res.m_Mat[M4_00]=fCosine; res.m_Mat[M4_10]=fSine;   res.m_Mat[M4_20]=0.0f; res.m_Mat[M4_30]=0.0f;
  res.m_Mat[M4_01]=-fSine;  res.m_Mat[M4_11]=fCosine; res.m_Mat[M4_21]=0.0f; res.m_Mat[M4_31]=0.0f;
  res.m_Mat[M4_02]=0.0f;    res.m_Mat[M4_12]=0.0f;    res.m_Mat[M4_22]=1.0f; res.m_Mat[M4_31]=0.0f;
  res.m_Mat[M4_03]=0.0f;    res.m_Mat[M4_13]=0.0f;    res.m_Mat[M4_23]=0.0f; res.m_Mat[M4_33]=1.0f;

  return res;
}

pecker_matrix4 pecker_matrix4::scale(Float fx,Float fy,Float fz)
{
  return pecker_matrix4( fx ,0.0f,0.0f,0.0f,
                  0.0f, fy ,0.0f,0.0f,
                  0.0f,0.0f, fz ,0.0f,
                  0.0f,0.0f,0.0f,1.0f);
}
pecker_matrix4 pecker_matrix4::translation(Float fx, Float fy,Float fz)
{
//  return CMatrix4(1.0f,0.0f,0.0f, fx ,
//                  0.0f,1.0f,0.0f, fy ,
//                  0.0f,0.0f,1.0f, fz ,
//                  0.0f,0.0f,0.0f,1.0f);
    return pecker_matrix4(1.0f,0.0f,0.0f,0.0f,
                    0.0f,1.0f,0.0f,0.0f,
                    0.0f,0.0f,1.0f,0.0f ,
                     fx , fy , fz ,1.0f);
}

pecker_matrix4 pecker_matrix4::look_at(const pecker_vector3 & vEye, const pecker_vector3 & vAt, const pecker_vector3 & vUp, bool bRightHanded)
{
  pecker_matrix4 result;

  pecker_vector3 vForward = ( (bRightHanded) ? (vEye - vAt) : (vAt - vEye) );
  vForward.normalize();

  pecker_vector3 vUpNorm = vUp.normalized();
  pecker_vector3 vSide   = vUpNorm.cross(vForward);
  vUpNorm = vForward.cross(vSide);

  result.m_Mat[M4_00]=vSide.x;    result.m_Mat[M4_10]=vSide.y;    result.m_Mat[M4_20]=vSide.z;            result.m_Mat[ M4_30]=0.0f;
  result.m_Mat[M4_01]=vUpNorm.x;  result.m_Mat[M4_11]=vUpNorm.y;  result.m_Mat[M4_21]=vUpNorm.z;          result.m_Mat[M4_31]=0.0f;
  result.m_Mat[M4_02]=vForward.x; result.m_Mat[M4_12]=vForward.y; result.m_Mat[M4_22]=vForward.z;        result.m_Mat[M4_32]=0.0f;
  result.m_Mat[M4_03]=0.0f;       result.m_Mat[M4_13]=0.0f;       result.m_Mat[M4_23]=0.0f;              result.m_Mat[M4_33]=1.0f;

  result.post_translate(-vEye);
  return result;
}



pecker_matrix4 pecker_matrix4::look_at_RH(const pecker_vector3 & vEye, const pecker_vector3 & vAt, const pecker_vector3 & vUp)
{
  return  look_at(vEye,vAt,vUp,true);
}


pecker_matrix4 pecker_matrix4::look_at_LH(const pecker_vector3 & vEye, const pecker_vector3 & vAt, const pecker_vector3 & vUp)
{
  return  look_at(vEye,vAt,vUp,false);
}



pecker_matrix4 pecker_matrix4::orthogonal(Float left, Float top, Float right,
    Float bottom, Float nearPlane, Float farPlane, Bool brotate /*= false*/)
{

  Float rcplmr = left - right;
  Float rcpbmt = bottom - top;
  Float rcpnmf = nearPlane - farPlane;

  if ( EQFLOATZERO(rcplmr) || EQFLOATZERO(rcpbmt) || EQFLOATZERO(rcpnmf))
  {
    //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix4::orthogonal",
    //    "params invail! left - right or bottom - top or nearPlane - farPlane == 0");
	  PECKER_LOG_ERR("CMatrix4::orthogonal",
		     "params invail! left - right or bottom - top or nearPlane - farPlane == 0",0);
    return pecker_matrix4(0.0f);
  }

  rcplmr = 1.0f/rcplmr;
  rcpbmt = 1.0f/rcpbmt;
  rcpnmf = 1.0f/rcpnmf;

  pecker_matrix4 result;

    if (brotate)
    {
        result.m_Mat[M4_00]= 0.0f;          result.m_Mat[M4_10]= 2.0f*rcplmr;   result.m_Mat[M4_20]=0.0f;  result.m_Mat[ M4_30]=-(right+left)*rcplmr;
        result.m_Mat[M4_01]= -2.0f*rcpbmt;  result.m_Mat[M4_11]= 0.0f;          result.m_Mat[M4_21]=0.0f;  result.m_Mat[M4_31]= (top+bottom)*rcpbmt;
    }
    else
    {
        result.m_Mat[M4_00]= -2.0f*rcplmr;  result.m_Mat[M4_10]= 0.0f;          result.m_Mat[M4_20]=0.0f;  result.m_Mat[ M4_30]= (right+left)*rcplmr;
        result.m_Mat[M4_01]= 0.0f;          result.m_Mat[M4_11]= -2.0f*rcpbmt;  result.m_Mat[M4_21]=0.0f;  result.m_Mat[M4_31]= (top+bottom)*rcpbmt;
    }

#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
       result.m_Mat[M4_02]= 0.0f;  result.m_Mat[M4_12]= 0.0f;  result.m_Mat[M4_22]= -rcpnmf;   result.m_Mat[M4_32]= nearPlane*rcpnmf;
#else
       result.m_Mat[M4_02]= 0.0f;  result.m_Mat[M4_12]= 0.0f;  result.m_Mat[M4_22]= -2*rcpnmf; result.m_Mat[M4_32]= (nearPlane+farPlane)*rcpnmf;
#endif

    result.m_Mat[M4_03]=0;  result.m_Mat[M4_13]=0;  result.m_Mat[M4_23]=0; result.m_Mat[M4_33]=1;

    return result;
}

pecker_matrix4 pecker_matrix4::perspective(
    Float width, Float height,
    Float nearPlane, Float farPlane,
    Bool bRightHanded,
    Bool brotate /*= false*/)
{
  Float rcpnmf = (nearPlane - farPlane);
  if (EQFLOATZERO(width) || EQFLOATZERO(height) || EQFLOATZERO(rcpnmf))
  {
    //char ErrInfo[256];
    //sprintf(ErrInfo,"params invail! width=%f height=%f  nearPlane - farPlane=%f",width,height,rcpnmf);
    //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix4::perspective",ErrInfo);
	PECKER_LOG_ERR("CMatrix4::perspective","params invail! width=%f height=%f  nearPlane - farPlane=%f",width,height,rcpnmf);
//    CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix4::perspective",
//        "params invail! width or height or nearPlane - farPlane == 0");
    return pecker_matrix4(0.0f);
  }

  Float n2 = 2.0f * nearPlane;
  rcpnmf = 1.0f/rcpnmf;
  pecker_matrix4 result;
  if (brotate)
  {
    result.m_Mat[M4_00] = 0.0f;        result.m_Mat[M4_10]= -n2/width;    result.m_Mat[M4_20]= 0.0f;   result.m_Mat[ M4_30]= 0.0f;
    result.m_Mat[M4_01] = n2/height;   result.m_Mat[M4_11]= 0.0f;         result.m_Mat[M4_21]= 0.0f;   result.m_Mat[M4_31]= 0.0f;
  }
  else
  {
    result.m_Mat[M4_00] = n2/width;    result.m_Mat[M4_10]= 0.0f;         result.m_Mat[M4_20]= 0.0f;   result.m_Mat[ M4_30]= 0.0f;
    result.m_Mat[M4_01] = 0.0f;        result.m_Mat[M4_11]= n2/height;    result.m_Mat[M4_21]= 0.0f;   result.m_Mat[M4_31]= 0.0f;
  }

#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
    result.m_Mat[M4_02] = 0.0f;   result.m_Mat[M4_12]= 0.0f;   result.m_Mat[M4_22]= farPlane*rcpnmf;    result.m_Mat[M4_32]= (farPlane*rcpnmf)*nearPlane;
#else
    result.m_Mat[M4_02] = 0.0f;   result.m_Mat[M4_12]= 0.0f;   result.m_Mat[M4_22]= farPlane+nearPlane*rcpnmf;    result.m_Mat[M4_32]= (farPlane*rcpnmf)*n2;
#endif

  result.m_Mat[M4_03] = 0.0f;        result.m_Mat[M4_13]= 0.0f;  result.m_Mat[M4_23]= -1.0f;  result.m_Mat[M4_33]= 0.0f;

  if (!bRightHanded)
  {
          result.m_Mat[M4_22] = result.m_Mat[M4_22]*(-1.0f);
          result.m_Mat[M4_23] = 1.0f;
  }

  return result;
}

pecker_matrix4 pecker_matrix4::perspective_float_depth(
    Float width, Float height,
    Float nearPlane,
    Bool bRightHanded,
    Bool brotate /*= false*/)
{
  if (EQFLOATZERO(width) || EQFLOATZERO(height))
   {
    //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix4::perspective_float_depth",
    //    "params invail! width or height  == 0");
	   PECKER_LOG_ERR("CMatrix4::perspective_float_depth",
		       "params invail! width or height  == 0",0);
     return pecker_matrix4(0.0f);
   }

  Float n2 = 2.0f*nearPlane;

  pecker_matrix4 result;
  if (brotate)
  {
     result.m_Mat[M4_00] = 0.0f;        result.m_Mat[M4_10] = -n2/width;     result.m_Mat[M4_20] = 0.0f;  result.m_Mat[ M4_30] = 0.0f;
     result.m_Mat[M4_01] = n2/height;   result.m_Mat[M4_11] = 0.0f;          result.m_Mat[M4_21] = 0.0f;  result.m_Mat[M4_31] = 0.0f;
  }
  else
  {
     result.m_Mat[M4_00] = n2/width;    result.m_Mat[M4_10] = 0.0f;          result.m_Mat[M4_20] = 0.0f;  result.m_Mat[ M4_30] = 0.0f;
     result.m_Mat[M4_01] = 0.0f;        result.m_Mat[M4_11] = n2/height;     result.m_Mat[M4_21] = 0.0f;  result.m_Mat[M4_31] = 0.0f;
  }
#if defined(GRAPHIC_DEVICE_DX9) || defined(GRAPHIC_DEVICE_DX10) || defined(GRAPHIC_DEVICE_DX11) || defined(GRAPHIC_DEVICE_DX12)
     result.m_Mat[M4_02] = 0.0f;        result.m_Mat[M4_12] = 0.0f;          result.m_Mat[M4_22]= 0.0f;  result.m_Mat[M4_32] = nearPlane;
#else
     result.m_Mat[M4_02] = 0.0f;        result.m_Mat[M4_12] = 0.0f;          result.m_Mat[M4_22]= ( (bRightHanded) ? (1.0f) : (-1.0f) );   result.m_Mat[M4_32] = n2;
#endif
     result.m_Mat[M4_03] = 0.0f;        result.m_Mat[M4_13] = 0.0f;          result.m_Mat[M4_23]= ( (bRightHanded) ? (-1.0f) : (1.0f) );   result.m_Mat[M4_33] = 0.0f;

  return result;
}

pecker_matrix4 pecker_matrix4::perspective_fov(
    Float fovy, Float aspect,
    Float nearPlane, Float farPlane,
    Bool bRightHanded,
    Bool brotate /*= false*/)
{
  if (EQFLOATZERO(aspect))
  {
    //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix4::perspective_fov",
    //    "params invail! aspect == 0");
	  PECKER_LOG_ERR("CMatrix4::perspective_fov",
		  "params invail! aspect == 0",0);
    return pecker_matrix4(0.0f);
  }
  //char ErrInfo[256];
  //sprintf(ErrInfo,"fovy=%f,aspect=%f,nearPlane=%f,farPlane=%f",fovy,aspect,nearPlane,farPlane);
  //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_INFO,"CMatrix4::perspective_fov",ErrInfo);

  Float height = ((2.0f*nearPlane) * (Float)tan(fovy*0.5f));

  //sprintf(ErrInfo,"height=%f ,fovy*0.5f=%f, tan(fovy*0.5f)=%f",height,(fovy*0.5f), (Float)tan(fovy*0.5f));
  //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_INFO,"CMatrix4::perspective_fov",ErrInfo);

  if (brotate)
  {
    return perspective(height, height/aspect, nearPlane, farPlane, bRightHanded, brotate);
  }
  return perspective(height/aspect, height, nearPlane, farPlane, bRightHanded, brotate);
}

pecker_matrix4 pecker_matrix4::perspective_fov_float_depth(
    Float fovy, Float aspect,
    Float nearPlane,
    Bool bRightHanded,
    Bool brotate /*= false*/)
{
  if (EQFLOATZERO(aspect))
  {
    //CPeckerLogger::GetSignleton()->LogOut(LOGINFO_ERROR,"CMatrix4::perspective_fov_float_depth",
    //  "params invail! aspect == 0");
	  PECKER_LOG_ERR("CMatrix4::perspective_fov_float_depth",
		    "params invail! aspect == 0",0);
    return pecker_matrix4(0.0f);
  }

  Float height = ( (2.0f*nearPlane) * (Float)tan(fovy*0.5) );
  if (brotate)
  {
    return perspective_float_depth(height, (height/aspect), nearPlane,bRightHanded, brotate);
  }
  else
  {
    return perspective_float_depth((height/aspect), height, nearPlane,bRightHanded, brotate);
  }
}

PECKER_END

