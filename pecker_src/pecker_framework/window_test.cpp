#include "native/pecker_window.h"
USING_PECKER_SDK

void show_simple_window()
{
	pecker_window_form<HDC> simple_form;
	pecker_string strparams;
	pecker_program_apps::init_apps();
	pecker_program_apps::execute_program(&simple_form,strparams);
}