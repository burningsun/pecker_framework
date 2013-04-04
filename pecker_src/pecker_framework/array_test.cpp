#include "data/pecker_array.h"
#include "data/pecker_stack.h"
#include "native/pecker_log.h"
#include "native/pecker_stream.h"
#include "data/pecker_string.h"
#include "data/pecker_value_compare.h"
//#include <iostream>
USING_PECKER_SDK

#define MAX_LOG_STRING_INFO 4096
static char gstr_log_info[MAX_LOG_STRING_INFO];
void array_test_main()
{
	pecker_write_stream_to_memery output_stream;
	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	pecker_array<int> array;
	array.init();
	for (int i=0;i<20;++i)
	{
		array.push(i);
	}
	pecker_array_iterator< pecker_array<int> > array_iterator1;
	array.get_iterator(&array_iterator1);
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	//std::cout << "inc ....." << std::endl;
	PECKER_LOG_INFO("array_test_main","inc.......");
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			//std::cout << *pvalue << ",";
		}
		else
		{
			output_stream.write_chars("null\n",6);
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}

	//output_stream.write_char('\0');
	PECKER_LOG_INFO("begin to end","%s",gstr_log_info);


	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "dec ....." << std::endl;
	PECKER_LOG_INFO("array_test_main","dec.......");
	array_iterator1.init(ITERATOR_INIT_END_INDEX);
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.decrement();
	}
	//output_stream.write_char('\0');
	PECKER_LOG_INFO("end to begin","%s",gstr_log_info);

	for (int i=0;i<5;++i)
	{
		array.pop();
	}

	for (int i=0;i<20;++i)
	{
		array.push(i);
	}

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	//std::cout << "inc ....." << std::endl;
	PECKER_LOG_INFO("array_test_main","inc.......");
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.increment();
	}

	PECKER_LOG_INFO("push pop begin to end","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "dec ....." << std::endl;
	PECKER_LOG_INFO("array_test_main","dec.......");
	array_iterator1.init(ITERATOR_INIT_END_INDEX);
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.decrement();
	}
	PECKER_LOG_INFO("push pop end to begin","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "resize,get set" << std::endl;
	PECKER_LOG_INFO("array_test_main","resize,get set");
	array.resize(100,20);
	for (int i=0;i<100;++i)
	{
		array.set_at(i,100-i);
	}
	for (int i=0;i<100;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	//std::cout << std::endl;
	PECKER_LOG_INFO("resize,get set begin to end","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	//std::cout << "resize,true,get set" << std::endl;
	PECKER_LOG_INFO("array_test_main","resize,true,get set");
	array.resize(50,20,true);
	for (int i=0;i<50;++i)
	{
		array.set_at(i,i);
	}
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	//std::cout << std::endl;
	PECKER_LOG_INFO("resize,true,get set begin to end","%s",gstr_log_info);

	

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	pecker_array_iterator< pecker_array<int> > array_iterator2;
	array.get_iterator(&array_iterator2);
	array_iterator2.init(ITERATOR_INIT_END_INDEX);

	int isetval = 100;
	array.set_at(1,isetval);
	array.set_at(6,isetval);
	array.set_at(11,isetval);
	array.set_at(16,isetval);
	array.set_at(21,isetval);
	array.set_at(26,isetval);
	array.set_at(31,isetval);
	array.set_at(36,isetval);
	array.set_at(41,isetval);
	array.set_at(46,isetval);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
		}
		else
		{
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	PECKER_LOG_INFO("array to be sort","%s",gstr_log_info);
	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	
	quick_sort_increment< int,pecker_value_compare<int>,pecker_array<int>,pecker_array_iterator< pecker_array<int> > >
		(array,array_iterator1,array_iterator2);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
		}
		else
		{
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	PECKER_LOG_INFO("array  sorted","%s",gstr_log_info);
	

	array.clear(true);

	//int ibreak;
	//std::cin >> ibreak;

}

void array_pool_test_main()
{
	pecker_write_stream_to_memery output_stream;
	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	pecker_pool_array<int> array;
	array.init();
	for (int i=0;i<20;++i)
	{
		array.push(i);
	}
	pecker_array_iterator< pecker_pool_array<int> > array_iterator1;

	array.get_iterator(&array_iterator1);
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	//std::cout << "inc ....." << std::endl;
	PECKER_LOG_INFO("array_pool_test_main","inc.......");
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			//std::cout << *pvalue << ",";
		}
		else
		{
			output_stream.write_chars("null\n",6);
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}

	//output_stream.write_char('\0');
	PECKER_LOG_INFO("begin to end","%s",gstr_log_info);


	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "dec ....." << std::endl;
	PECKER_LOG_INFO("array_test_main","dec.......");
	array_iterator1.init(ITERATOR_INIT_END_INDEX);
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.decrement();
	}
	//output_stream.write_char('\0');
	PECKER_LOG_INFO("end to begin","%s",gstr_log_info);

	for (int i=0;i<5;++i)
	{
		array.pop();
	}

	for (int i=0;i<20;++i)
	{
		array.push(i);
	}

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	//std::cout << "inc ....." << std::endl;
	PECKER_LOG_INFO("array_pool_test_main","inc.......");
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
			//PECKER_LOG_INFO("array_pool_test_main","%d",*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_pool_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.increment();
	}

	PECKER_LOG_INFO("push pop begin to end","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "dec ....." << std::endl;
	PECKER_LOG_INFO("array_pool_test_main","dec.......");
	array_iterator1.init(ITERATOR_INIT_END_INDEX);
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_pool_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_pool_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.decrement();
	}
	PECKER_LOG_INFO("push pop end to begin","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "resize,get set" << std::endl;
	PECKER_LOG_INFO("array_pool_test_main","resize,get set");
	array.resize(100,20);
	for (int i=0;i<100;++i)
	{
		array.set_at(i,100-i);
	}
	for (int i=0;i<100;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_pool_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_pool_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	//std::cout << std::endl;
	PECKER_LOG_INFO("resize,get set begin to end","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	//std::cout << "resize,true,get set" << std::endl;
	PECKER_LOG_INFO("array_pool_test_main","resize,true,get set");
	array.resize(50,20,true);
	for (int i=0;i<50;++i)
	{
		array.set_at(i,i);
	}
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_pool_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_pool_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	//std::cout << std::endl;
	PECKER_LOG_INFO("resize,true,get set begin to end","%s",gstr_log_info);



	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	pecker_array_iterator< pecker_pool_array<int> > array_iterator2;
	array.get_iterator(&array_iterator2);
	array_iterator2.init(ITERATOR_INIT_END_INDEX);

	int isetval = 100;
	array.set_at(1,isetval);
	array.set_at(6,isetval);
	array.set_at(11,isetval);
	array.set_at(16,isetval);
	array.set_at(21,isetval);
	array.set_at(26,isetval);
	array.set_at(31,isetval);
	array.set_at(36,isetval);
	array.set_at(41,isetval);
	array.set_at(46,isetval);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
		}
		else
		{
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	PECKER_LOG_INFO("array to be sort","%s",gstr_log_info);
	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	quick_sort_increment< int,pecker_value_compare<int>,pecker_pool_array<int>,pecker_array_iterator< pecker_pool_array<int> > >
		(array,array_iterator1,array_iterator2);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
		}
		else
		{
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	PECKER_LOG_INFO("array  sorted","%s",gstr_log_info);


	array.clear(true);

	//int ibreak;
	//std::cin >> ibreak;

}

void array_stack_pool_test_main()
{
	pecker_write_stream_to_memery output_stream;
	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	pecker_stack_pool_array<int> array;
	array.init();
	for (int i=0;i<20;++i)
	{
		array.push(i);
	}
	pecker_array_iterator< pecker_stack_pool_array<int> > array_iterator1;

	array.get_iterator(&array_iterator1);
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	//std::cout << "inc ....." << std::endl;
	PECKER_LOG_INFO("array_stack_pool_test_main","inc.......");
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			//std::cout << *pvalue << ",";
		}
		else
		{
			output_stream.write_chars("null\n",6);
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}

	//output_stream.write_char('\0');
	PECKER_LOG_INFO("begin to end","%s",gstr_log_info);


	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "dec ....." << std::endl;
	PECKER_LOG_INFO("array_test_main","dec.......");
	array_iterator1.init(ITERATOR_INIT_END_INDEX);
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.decrement();
	}
	//output_stream.write_char('\0');
	PECKER_LOG_INFO("end to begin","%s",gstr_log_info);

	for (int i=0;i<5;++i)
	{
		array.pop();
	}

	for (int i=0;i<20;++i)
	{
		array.push(i);
	}

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	//std::cout << "inc ....." << std::endl;
	PECKER_LOG_INFO("array_stack_pool_test_main","inc.......");
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
			//PECKER_LOG_INFO("array_stack_pool_test_main","%d",*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_stack_pool_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.increment();
	}

	PECKER_LOG_INFO("push pop begin to end","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "dec ....." << std::endl;
	PECKER_LOG_INFO("array_stack_pool_test_main","dec.......");
	array_iterator1.init(ITERATOR_INIT_END_INDEX);
	while (1)
	{
		const int* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_stack_pool_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
			output_stream.write_char(',');
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_stack_pool_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		array_iterator1.decrement();
	}
	PECKER_LOG_INFO("push pop end to begin","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	//std::cout << "resize,get set" << std::endl;
	PECKER_LOG_INFO("array_stack_pool_test_main","resize,get set");
	array.resize(100,20);
	for (int i=0;i<100;++i)
	{
		array.set_at(i,100-i);
	}
	for (int i=0;i<100;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_stack_pool_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_stack_pool_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	//std::cout << std::endl;
	PECKER_LOG_INFO("resize,get set begin to end","%s",gstr_log_info);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	//std::cout << "resize,true,get set" << std::endl;
	PECKER_LOG_INFO("array_stack_pool_test_main","resize,true,get set");
	array.resize(50,20,true);
	for (int i=0;i<50;++i)
	{
		array.set_at(i,i);
	}
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//PECKER_LOG_INFO("array_stack_pool_test_main","%d",*pvalue);
			output_stream.write_integer(*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			//PECKER_LOG_ERR("array_stack_pool_test_main","%d(null)",pvalue);
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	//std::cout << std::endl;
	PECKER_LOG_INFO("resize,true,get set begin to end","%s",gstr_log_info);



	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	pecker_array_iterator< pecker_stack_pool_array<int> > array_iterator2;
	array.get_iterator(&array_iterator2);
	array_iterator2.init(ITERATOR_INIT_END_INDEX);

	int isetval = 100;
	array.set_at(1,isetval);
	array.set_at(6,isetval);
	array.set_at(11,isetval);
	array.set_at(16,isetval);
	array.set_at(21,isetval);
	array.set_at(26,isetval);
	array.set_at(31,isetval);
	array.set_at(36,isetval);
	array.set_at(41,isetval);
	array.set_at(46,isetval);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
		}
		else
		{
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	PECKER_LOG_INFO("array to be sort","%s",gstr_log_info);
	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);

	quick_sort_increment< int,pecker_value_compare<int>,pecker_stack_pool_array<int>,pecker_array_iterator< pecker_stack_pool_array<int> > >
		(array,array_iterator1,array_iterator2);

	output_stream.bind_write_buffer(gstr_log_info,MAX_LOG_STRING_INFO);
	for (int i=0;i<50;++i)
	{
		const int* pvalue = array.get_at(i);
		if (pvalue)
		{
			output_stream.write_integer(*pvalue);
		}
		else
		{
			output_stream.write_chars("null\n",6);
			break;
		}
		output_stream.write_char(',');
	}
	PECKER_LOG_INFO("array  sorted","%s",gstr_log_info);


	array.clear(true);

	//int ibreak;
	//std::cin >> ibreak;

}