/*
 * pfx_allocator.cpp
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */



#include "pfx_allocator.h"

//PFX_C_EXTERN_BEGIN
const IAllocator gDefualt_allocator = {default_allocator_allocate_obj,default_allocator_deallocate_obj}; 
//PFX_C_EXTERN_END
