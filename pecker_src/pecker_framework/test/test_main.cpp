/*
 * test_main.cpp
 *
 *  Created on: 2013-9-3
 *      Author: 李镇城 (cut / cutxyz)
 */

extern int list_test_main();
extern int array_test_main();
extern int arrayblock_test_main();
extern int dynamic_linear_array_test_main();
extern int string_test_main();
extern int bst_test_main();
int test_main()
{
	int status;
	//status = list_test_main();
	//status = array_test_main();
	//status = arrayblock_test_main();
	//status =  dynamic_linear_array_test_main();
	//status = string_test_main();
	status = bst_test_main();
	return status;
}