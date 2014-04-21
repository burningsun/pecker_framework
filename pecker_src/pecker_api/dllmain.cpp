// dllmain.cpp : Defines the entry point for the DLL application.
#include "pfx_defines.h"

#include "data/pfx_cbst_iterator_codes.h"
#include "data/pfx_cbst_codes.h"

#include "render/pfx_color.h"
#include "pfx_api_info.h"
#include <stdio.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf ("pecker_api process attach...\n");
		break;
	case DLL_THREAD_ATTACH:
		printf ("pecker_api thread attach...\n");
		break;
	case DLL_THREAD_DETACH:
		printf ("pecker_api thread detach...\n");
		break;
	case DLL_PROCESS_DETACH:
		printf ("pecker_api process detach...\n");
		break;
	}

	const pfx_version_t& api_ver = get_pecker_api_version();
	printf ("pecker_api version = (%d,%d,%d,%d)\n\n",
		api_ver.version_code[0],
		api_ver.version_code[1],
		api_ver.version_code[2],
		api_ver.version_code[3]);

	return TRUE;
}

