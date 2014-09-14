#include "../pecker_framework/pfx_defines.h"
#include "../pecker_framework/pfx_app_init.h"

#ifdef __ANDROID__
#else
#ifdef _DEBUG
#pragma comment (lib,"..\\debug\\pecker_api.lib")
#pragma comment (lib,"..\\debug\\pecker_hal.lib")
#else
#pragma comment (lib,"..\\release\\pecker_api.lib")
#pragma comment (lib,"..\\release\\pecker_hal.lib")
#endif
#endif

#include "../pecker_framework/pfx_api_info.h"

//extern int array_test_main ();
extern result_t string_test ();
extern result_t list_test ();
extern int bst_test_main();
extern int avl_bst_test_main();
extern int rb_bst_test_main();
extern int array_test_main ();
extern int bst_stress_test_main (bool bshow = false);
extern void matrix_test ();
extern int auto_obj_test ();
extern void test_object_id ();
extern void symbiont_object();



#if (defined(__ANDROID__)|| defined(__APP_MAIN_SHOW__))
int test_main ()
{
#else

extern void form_test();
extern void gles2_displayview_test();

int main ()
{
	//gles2_displayview_test();
	//form_test();
#endif

	//symbiont_object();

	//list_test();
	//string_test();
	//bst_test_main();
	//avl_bst_test_main();
	//rb_bst_test_main();
	//array_test_main ();
	//bst_stress_test_main();
	//matrix_test();
	//auto_obj_test();
	//test_object_id();

//	abs_float32_neon(xxx,ddd,3);
	return 0;
}
