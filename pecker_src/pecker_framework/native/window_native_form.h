#ifndef PFX_WINDOWS_NATIVE_FORM_H_
#define PFX_WINDOWS_NATIVE_FORM_H_
#include "../pfx_defines.h"

#include "pfx_native_component.h"

#if (OS_CONFIG == OS_WINDOWS)


PECKER_BEGIN

class window_native_form
{
protected:
	static HWND	hwnd_main;
	static LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	result_t	listen_message();
protected:
	LRESULT		on_message(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	result_t 	show();
	result_t	show_dialog();
	
	long_t		get_native_window() const;
	long_t		get_native_display() const;

};



PECKER_END




#endif //PFX_WINDOWS_NATIVE_FORM_H_
