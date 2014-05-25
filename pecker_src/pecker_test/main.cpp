#include "pfx_defines.h"
#pragma comment (lib,"..\\debug\\pecker_api.lib")

#include "pfx_api_info.h"

extern result_t string_test ();
//extern result_t list_test ();
//extern int bst_test_main();
//extern int avl_bst_test_main();
//extern int rb_bst_test_main();
//extern int array_test_main ();
//extern int bst_stress_test_main ();
extern void matrix_test ();
extern int auto_obj_test ();
extern void test_object_id ();
int main ()
{
	//list_test();
	string_test();
	//bst_test_main();
	//avl_bst_test_main();
	// rb_bst_test_main();
	//array_test_main ();
	//bst_stress_test_main();
	//matrix_test();
	//auto_obj_test();
	//test_object_id();
	return 0;
}