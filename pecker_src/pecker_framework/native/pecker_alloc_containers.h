/*
 * pecker_alloc_containers.h
 *
 *  Created on: 2012-6-19
 *      Author: 李镇城 (cut / cutxyz)
 */
//#pragma once
#ifndef PECKER_ALLOC_CONTAINERS_H_
#define PECKER_ALLOC_CONTAINERS_H_

#include "pecker_allocator.h"

PECKER_BEGIN

typedef pecker_simple_allocator< char > pecker_acsii_string_alloc;
typedef pecker_simple_allocator< wchar_t > pecker_utf_string_alloc;


PECKER_END

#endif // PECKER_ALLOC_CONTAINERS_H_
