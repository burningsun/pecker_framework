/*
 * pfx_carray.h
 *
 *  Created on: 2013-12-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CARRAY_H_
#define		PFX_CARRAY_H_

#include "pfx_cstring.h"

PECKER_BEGIN

#define PFX_CARRAY_TEMPLATE_DEFINES template < class item_type_,  const int array_defualt_size_ >
#define PFX_CARRAY_TEMPLATE_PARAMS  < item_type_, array_defualt_size_ >
#define ARRAY_DEFUALT_SIZE STRING_DEFUALT_SIZE

template < class item_type_,  
const int array_defualt_size_ = ARRAY_DEFUALT_SIZE >
class pfx_carray_linear : public pfx_cstring < item_type_, array_defualt_size_ > 
{

};

PECKER_END

#endif			//PFX_CARRAY_H_
