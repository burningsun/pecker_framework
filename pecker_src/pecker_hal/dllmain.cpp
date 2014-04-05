// dllmain.cpp : Defines the entry point for the DLL application.
#include "pfx_defines.h"
#include "pfx_api_info.h"
#include "pfx_hal_info.h"
#include <stdio.h>

#define DEBUG_REF_LIB_PATH "../Debug/pecker_api.lib"
#define RELEASE_REF_LIB_PATH "../release/pecker_api.lib"

#ifdef PFX_DEBUG_MODE
#define LIB_PATH DEBUG_REF_LIB_PATH
#else
#define LIB_PATH RELEASE_REF_LIB_PATH
#endif
#pragma  comment (lib,LIB_PATH)


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf ("pecker_hal process attach...\n");
		break;
	case DLL_THREAD_ATTACH:
		printf ("pecker_hal thread attach...\n");
		break;
	case DLL_THREAD_DETACH:
		printf ("pecker_hal thread detach...\n");
		break;
	case DLL_PROCESS_DETACH:
		printf ("pecker_hal process detach...\n");
		break;
	}
	const pfx_version_t& api_ver = get_pecker_api_version();
	printf ("pecker_api version = (%d,%d,%d,%d)\n",
		api_ver.version_code[0],
		api_ver.version_code[1],
		api_ver.version_code[2],
		api_ver.version_code[3]);

	const pfx_version_t& hal_ver = get_pecker_hal_version ();
	printf ("pecker_hal version = (%d,%d,%d,%d)\n\n",
		hal_ver.version_code[0],
		hal_ver.version_code[1],
		hal_ver.version_code[2],
		hal_ver.version_code[3]);


	return TRUE;
}

