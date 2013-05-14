#include "native/pecker_log.h"
extern int avl_cmp_stress_main();
extern void avl_alg_func_main();
extern void array_test_main();
extern void array_pool_test_main();
extern int avl_tree_container_test_main();
extern int avl_stl_map_cmp(int itime);
extern int pool_alloc_main();
extern int string_share_test();
extern int btst_test_main();
extern int _3_map_cmp(int itime);
extern int _2_map_cmp(int itime);
//extern int test_io();
extern int _2_avl_key_map_cmp(int itime);
//extern void out_pn9_sn();
//extern int test_pn9_sn();
extern void array_stack_pool_test_main();
extern void tst_iterator_test();
extern void tst_iterator_test_value();
extern void avlbst_iterator_test();
extern int list_test();
//extern void test_stream_main();
extern void tst_iterator_test_clear();
extern void test_thread_proc();
extern void test_thread_runable();
extern void test_thread_proc_1();
extern void test_thread_runable_1();
extern void show_simple_window();
extern void shape_logic_test();
#include <iostream>

#include "data/pecker_shape.h"
//#include "data/test.h"
int main()
{

	
	//shape_logic_test();
	//unsigned int temp_value = 65535;
	//unsigned int mip = temp_value;
	//unsigned long long temp64 = 0xFF;
	//temp64 *= 0x10000000;

	//temp_value = temp64 & 0xFFFFFFFF;
	//temp_value = (temp_value&0x55555555) + ((temp_value>>1)&0x55555555);     
	//temp_value = (temp_value&0x33333333) + ((temp_value>>2)&0x33333333);
	//temp_value = (temp_value&0x0f0f0f0f) + ((temp_value>>4)&0x0f0f0f0f);     
	//temp_value = (temp_value&0x00ff00ff) + ((temp_value>>8)&0x00ff00ff);     
	//temp_value = (temp_value&0x0000ffff) + ((temp_value>>16)&0x0000ffff); 
	//mip = temp_value;
	//temp_value = (temp64 >> 32) & 0xFFFFFFFF;
	//temp_value = (temp_value&0x55555555) + ((temp_value>>1)&0x55555555);     
	//temp_value = (temp_value&0x33333333) + ((temp_value>>2)&0x33333333);
	//temp_value = (temp_value&0x0f0f0f0f) + ((temp_value>>4)&0x0f0f0f0f);     
	//temp_value = (temp_value&0x00ff00ff) + ((temp_value>>8)&0x00ff00ff);     
	//temp_value = (temp_value&0x0000ffff) + ((temp_value>>16)&0x0000ffff); 
	//mip += temp_value;
	//PECKER_LOG_INFO("1 count","temp_value=%d,count 1 = %d",mip,temp_value);

	// temp_value = 65535;
	////temp_value = (temp_value&0x55555555) + ((temp_value>>1)&0x55555555);     
	////temp_value = (temp_value&0x33333333) + ((temp_value>>2)&0x33333333);
	////temp_value = (temp_value&0x0f0f0f0f) + ((temp_value>>4)&0x0f0f0f0f);     
	////temp_value = (temp_value&0x00ff00ff) + ((temp_value>>8)&0x00ff00ff);     
	////temp_value = (temp_value&0x0000ffff) + ((temp_value>>16)&0x0000ffff); 
	//temp_value = (temp_value&0x5555) + ((temp_value>>1)&0x5555);     
	//temp_value = (temp_value&0x3333) + ((temp_value>>2)&0x3333);
	//temp_value = (temp_value&0x0f0f) + ((temp_value>>4)&0x0f0f);     
	//temp_value = (temp_value&0x00ff) + ((temp_value>>8)&0x00ff);     
	//PECKER_LOG_INFO("1 count","temp_value=%d,count 1 = %d",mip,temp_value);

	//temp_value = mip;
	////mip = 1;
	////if ((temp_value >> 16) == 0) {mip = mip +16; temp_value = temp_value <<16;}
	////if ((temp_value >> 24) == 0) {mip = mip + 8; temp_value = temp_value << 8;}
	////if ((temp_value >> 28) == 0) {mip = mip + 4; temp_value = temp_value << 4;}
	////if ((temp_value >> 30) == 0) {mip = mip + 2; temp_value = temp_value << 2;}
	////mip = 32 - (mip - (temp_value >> 31));

	//mip = 1;
	//if ((temp_value >> 8) == 0) {mip = mip +8; temp_value = temp_value <<8;}
	//if ((temp_value >> 12) == 0) {mip = mip + 4; temp_value = temp_value << 4;}
	//if ((temp_value >> 14) == 0) {mip = mip + 2; temp_value = temp_value << 2;}
	//mip = 16 - (mip - (temp_value >> 15));

	//PECKER_LOG_INFO("first 1 num","first 1 num = %d",mip);

	show_simple_window();
	//test_thread_runable_1();
	//test_thread_proc_1();
	//test_thread_runable();
	 //test_thread_proc();
	//tst_iterator_test_clear();
	//test_stream_main();
	 //list_test();
	//tst_iterator_test_value();
	 //tst_iterator_test();
	 //avlbst_iterator_test();
	//array_stack_pool_test_main();
	//test_pn9_sn();
	//out_pn9_sn();
	//test_io();
	//_2_avl_key_map_cmp(20);
	//_2_map_cmp(20);
	//_3_map_cmp(5);
	//btst_test_main();
	
	// string_share_test();
	//pool_alloc_main();
	//avl_tree_container_test_main();
	//avl_stl_map_cmp(10);
	 //avl_tree_container_test_main();
	//for (int i=0;i<20;++i)
	//{
	//	std :: cout << "test time "<<i<<std::endl<<std::endl;
	//	//avl_cmp_stress_main();
	//	avl_stl_map_cmp();
	//	std :: cout << std::endl;
	//}
	//array_test_main();
	//array_pool_test_main();

	//PECKER_LOG_ENDLINE;
	//PECKER_LOG_INFO("breaking","........");
	int ibreak;
	std::cin >> ibreak;
	return 0;
}