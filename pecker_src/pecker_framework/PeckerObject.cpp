/*
 * PeckerObject.cpp
 *
 *  Created on: 2012-6-19
 *      Author: 李镇城 (cut / cutxyz)
 */
#include "CPeckerObject.h"
//#include <typeinfo>

PECKER_BEGIN

static U64bit gu64Hashbase = 0x11223344;
U64bit PeckerObject::ToHashCode()
{
  return (gu64Hashbase + (U64bit)this);
}

StringChars PeckerObject::GetObjType(CharStr P_OUT pStrBuf,U32bit nBufLen)
{
  StringChars nRetnVal =
  { pStrBuf,nBufLen};
  this->GetObjType(nRetnVal);
  return nRetnVal;
}

const StringChars* PeckerObject::GetObjType(StringChars P_REF pStrChars)
{
  const char* pchar = 0;//typeid(*this).name();

  for(U32bit i=0;i<pStrChars._M_buffer_size;++i)
  {
    if(0 != pchar[i])
    {
      pStrChars._M_buffer[i] = pchar[i];
    }
    else
    {
      pStrChars._M_buffer_size = i;
      break;
    }
  }
  pStrChars._M_buffer[pStrChars._M_buffer_size] = 0;

  return &pStrChars;
}

HResult PeckerObject::InitObject(const ST_PARAMS* P_IN pParams /*= null*/)
{
  return 0;
}

HResult PeckerObject::ReleaseObject(const ST_PARAMS* P_IN pParams /*= null*/)
{
  return 0;
}

const StringChars* PeckerObject::ToString(StringChars P_REF pStrChars,const ConstStringChars* strFormat /*= null*/)
{
  return GetObjType(pStrChars);
}

PECKER_END
