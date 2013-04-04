/*
 * CPeckerObject.h
 *
 *  Created on: 2012-6-19
 *      Author: 李镇城 (cut / cutxyz)
 */
#include "PeckerDefines.h"

#ifndef CPECKEROBJECT_H_
#define CPECKEROBJECT_H_

#ifdef __cplusplus

//#include <typeinfo>

PECKER_BEGIN

//typedef stringchars<CharStr> StringChars;
typedef struct _st_stringchars
{
  Char* _M_buffer;
  U32bit _M_buffer_size;
}StringChars;
typedef StringChars Bytes;

typedef struct _st_const_stringchars
{
  const Char* _M_buffer;
  U32bit _M_buffer_size;
}ConstStringChars;
typedef ConstStringChars ConstBytes;

template<class className>
struct stringchars
{
  className* m_pStrBuf;
  U32bit m_nStrLen;

  stringchars<className> &operator=(StringChars P_REF pStrChar)
  {
    uSize szChar = sizeof(Char);
    uSize sz = sizeof(className);
    U32bit len = pStrChar._M_buffer_size * szChar;
    m_nStrLen = len / sz;
    if (pStrChar._M_buffer_size % sz > 0)
    {
      ++m_nStrLen;
    }
    m_pStrBuf = (className*)(pStrChar._M_buffer);
    return *this;
  }
};

template<class className>
struct stringconstchars
{
	const className* m_pStrBuf;
	U32bit m_nStrLen;
};


typedef struct _st_params
{
  PVoid* m_params;
  U32bit m_nStrLen;
}ST_PARAMS;

class PeckerObject
{
public:
  virtual ~PeckerObject()
  { ;}
  virtual U64bit ToHashCode();
  virtual StringChars GetObjType(CharStr P_OUT pStrBuf,U32bit nBufLen);
  virtual const StringChars* GetObjType(StringChars P_REF pStrChars);
  virtual HResult InitObject(const ST_PARAMS* P_IN pParams = null);
  virtual HResult ReleaseObject(const ST_PARAMS* P_IN pParams = null);
  virtual const StringChars* ToString(StringChars P_REF pStrChars,const ConstStringChars* strFormat = null);
};

typedef enum
{
  LESSER = -1,
  EQUALS = 0,
  GREATER = 1,
  COMPARE_RESULT_COUNT
}COMPARE_RESULT;

template <class className>
PeckerInterface PeckerCompare : public virtual PeckerObject
{
  virtual ~PeckerCompare()
  { ;}
  virtual COMPARE_RESULT Equals(const className P_REF objectA,const className P_REF objectB)
  {
    if (objectA > objectB)
    {
      return GREATER;
    }
    else if (objectA < objectB)
    {
      return LESSER;
    }
    else
    {
      return EQUALS;
    }
  }

  // vc compiler error C1202: recursive type or function dependency context too complex
  // gcc ok!
  //static PeckerCompare<PeckerCompare> PeckerCompareDefualt;
};

template <class className>
struct PeckerCompareHandleEquals
{

	inline COMPARE_RESULT operator () (const className P_REF objectA,const className P_REF objectB)
	{
		if (objectA > objectB)
		{
			return GREATER;
		}
		else if (objectA < objectB)
		{
			return LESSER;
		}
		else
		{
			return EQUALS;
		}
	}

};

typedef struct _st_isize
{
  U32bit w;
  U32bit h;
}PeckerSize;

typedef struct _st_point
{
  U32bit x;
  U32bit y;
}PeckerPoint;

PECKER_END

#endif

#endif /* CPECKEROBJECT_H_ */
