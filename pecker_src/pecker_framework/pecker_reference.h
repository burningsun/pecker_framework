/*
 * pecker_reference.h
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

//
//template<class className>
//struct stringchars
//{
//  className* m_pStrBuf;
//  U32bit m_nStrLen;
//
//  stringchars<className> &operator=(StringChars P_REF pStrChar)
//  {
//    uSize szChar = sizeof(Char);
//    uSize sz = sizeof(className);
//    U32bit len = pStrChar._M_buffer_size * szChar;
//    m_nStrLen = len / sz;
//    if (pStrChar._M_buffer_size % sz > 0)
//    {
//      ++m_nStrLen;
//    }
//    m_pStrBuf = (className*)(pStrChar._M_buffer);
//    return *this;
//  }
//};
//
//template<class className>
//struct stringconstchars
//{
//	const className* m_pStrBuf;
//	U32bit m_nStrLen;
//};
//
//
//typedef struct _st_params
//{
//  PVoid* m_params;
//  U32bit m_nStrLen;
//}ST_PARAMS;



PECKER_END

#endif

#endif /* CPECKEROBJECT_H_ */
