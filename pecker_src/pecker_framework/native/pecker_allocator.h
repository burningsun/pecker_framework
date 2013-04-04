/*
 * PeckerAllocator.h
 *
 *  Created on: 2012-6-19
 *      Author: 李镇城 (cut / cutxyz)
 */
//#pragma once
#ifndef PECKER_ALLOCATOR_H_
#define PECKER_ALLOCATOR_H_

#include "../CPeckerObject.h"
#include <new>

PECKER_BEGIN

template<class className>
class pecker_simple_allocator
{
public: 
	HResult swap(pecker_simple_allocator<className> &other)
	{
		return P_OK;
	}

	className* transfer_value(pecker_simple_allocator<className> &other,className* p_value_t)
	{
		return p_value_t;
	}
public:
	static inline className* allocate_object()
	{
			return new className;
	}
public: 
	static inline void deallocate_object(className*  pDelObject)
	{
		if(null != pDelObject)
		{
			delete  pDelObject;
		}
	}

public: 
	static inline className* allocate_objects(nSize nSize)
		{
			if(nSize > 0)
			{
				return new className[nSize];
			}
			return null;
		}
public: 
	static inline void deallocate_objects(className*  pDelObject)
		{
			if(null != pDelObject)
			{
				delete [] pDelObject;
			}
		}
};

//typedef enum enumALIGNEDPACK
//{
//  DEFUALT_PACK = 0,
//  PACK2,
//  PACK4,
//  PACK8,
//  PACK16,
//  PACK32,
//  PACK64,
//  ALIGNEDPACK_COUNT
//}ALIGNEDPACK;
//
//extern "C"
//{
//  Bytes NewAlignedMemory(nSize nallocate_objectSize,ALIGNEDPACK nAlignedPackType);
//  void DeleteAlignedMemory(Bytes P_REF pAlignedMemory);
//}

PECKER_END

#endif
