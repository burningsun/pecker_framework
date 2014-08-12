/*
 * pfx_resource_reader_windows.h
 *
 *  Created on: 2014-8-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RESOURCE_READER_WINDOWS_H_
#define		PFX_RESOURCE_READER_WINDOWS_H_

#include "../pfx_defines.h"
#include "pfx_file_io.h"
#if (OS_CONFIG == OS_WINDOWS)

PECKER_BEGIN

class cresource_reader_windows
{
private:

public:
	cresource_reader_windows();
	virtual ~cresource_reader_windows();

};




PECKER_END
#endif	 // #if (OS_CONFIG == OS_WINDOWS)


#endif			//PFX_RESOURCE_READER_WINDOWS_H_
