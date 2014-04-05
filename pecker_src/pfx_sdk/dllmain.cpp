// dllmain.cpp : Defines the entry point for the DLL application.
#include "pfx_defines.h"

HMODULE g_pfx_api_module_handle = NULL;
long long g_ref_count = 0;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if (!g_pfx_api_module_handle)
	{
		g_pfx_api_module_handle = ::LoadLibraryA ("pecker_api.dll");
	}
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		++g_ref_count;
		break;
	case DLL_THREAD_ATTACH:
		++g_ref_count;
		break;
	case DLL_THREAD_DETACH:
		--g_ref_count;
		break;
	case DLL_PROCESS_DETACH:
		--g_ref_count;
		break;
	}

	if (0 >= g_ref_count)
	{
		BOOL result_ = ::FreeLibrary (g_pfx_api_module_handle);
		if (result_)
		{
			g_pfx_api_module_handle = NULL;
		}
	}
	return TRUE;
}

