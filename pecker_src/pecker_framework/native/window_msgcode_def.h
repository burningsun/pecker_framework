/*
* window_msgcode_def.h
*
*  Created on: 2014-7-31
*      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PFX_WINDOWS_MSGCODE_DEF_H_
#define PFX_WINDOWS_MSGCODE_DEF_H_
#include "../pfx_defines.h"

#if (OS_CONFIG == OS_WINDOWS)

typedef enum enumPFX_WINDOWS_MSG_OFFSET
{
   ACTIVE_RESUME = 0,
   ACTIVE_PARSE,
   ACTIVE_RESTART,

   MAX_PFX_MSG_OFFSET = 512
}PFX_WINDOWS_MSG_OFFSET_t;

#define WM_SHOW_RESUM (WM_USER + ACTIVE_RESUME)
#define WM_SHOW_PARSE (WM_USER + ACTIVE_PARSE)
#define WM_SHOW_RESTART (WM_USER + ACTIVE_RESTART)
#define WM_PFX_MAX_USERCODE (WM_USER + MAX_PFX_MSG_OFFSET)



#endif//	(OS_CONFIG == OS_WINDOWS)


#endif //PFX_WINDOWS_MSGCODE_DEF_H_
