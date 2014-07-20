/*
 * pfx_disposeable.h
 *
 *  Created on: 2014-7-20
 *      Author: 李镇城 (cut / cutxyz)
 */
//#pragma once
#ifndef PFX_DISPOSEABLE_H_
#define PFX_DISPOSEABLE_H_

#include "../pfx_defines.h"
PECKER_BEGIN

PFX_Interface IDisposeAble
{
	virtual ~IDisposeAble(){;}
	virtual result_t dispose () = 0;
};

PECKER_END

#endif
