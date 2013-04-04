//#define AVL_DEBUG_CODE
#include "data/pecker_avl_tree.h"
#include "data/pecker_array.h"
#include "data/pecker_string.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <Windows.h>
USING_PECKER_SDK

int avl_char_cmp_count = 0;
struct string_char_compare_
{
	 int operator () (const char &char1,const char &char2)  const
	{
		return (char1 - char2);
	}
	static  inline int compare(const char &char1,const char &char2) 
	{
		++avl_char_cmp_count;
		return (char1 - char2);
	}
};

struct stringcmp_t
{
	int operator () (const std::string & str1,const std::string & str2) const
	{
		//return str1.compare(str2);

		int ilen1 = str1.length();
		int ilen2 =  str2.length();
		int imin = ilen1;
		const char* pstrchar1 = str1.data();
		const char* pstrchar2 = str2.data();
		if (imin > ilen2)
			imin = ilen2;
		for (int i=0;i<imin;++i)
		{
			//int iretn = *(pstrchar1+i) - *(pstrchar2+i);
			int iretn = string_char_compare_::compare( *(pstrchar1+i) , *(pstrchar2+i));
			if (0 != iretn)
			{
				return iretn;
			}
		}
		return (ilen1 - ilen2);
	}
};
int avl_tree_container_test_main()
{
	pecker_avl_tree_set_container< std::string,stringcmp_t,AVL_node_set< std::string >,pecker_nodes_simple_allocater< AVL_node_set< std::string> > > avl_tree_strings;
	pecker_avl_tree_set_container< std::string,stringcmp_t,AVL_node_set< std::string >,pecker_nodes_simple_allocater< AVL_node_set< std::string> > > avl_tree_strings_copy;
	
	pecker_array< std::string > array_strings;
	array_strings.init(100000,256);
	std::ifstream myfile;
	myfile.close();
	myfile.open("inputaddsearch.txt");
	while(1)
	{
		if (myfile.eof())
			break;

		std::string strin;
		myfile >> strin;
		array_strings.push(strin);
	}

	pecker_array_iterator< pecker_array< std::string > > array_iterator_strings;
	array_strings.get_iterator(&array_iterator_strings);
	array_iterator_strings.init(ITERATOR_INIT_BEGIN_INDEX);
	std::cout << "inc ....." << std::endl;
	while (1)
	{
		const std::string* pvalue = array_strings.get_at(&array_iterator_strings);
		if (pvalue)
		{
			avl_result res = avl_tree_strings.insert(*pvalue);
			if (P_OK != res)
			{
				std::cout << "insert error" << std::endl;
			}
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		array_iterator_strings.increment();
	}

	array_iterator_strings.init(ITERATOR_INIT_BEGIN_INDEX);
	std::cout << "inc ....." << std::endl;
	while (1)
	{
		const std::string* pvalue = array_strings.get_at(&array_iterator_strings);
		if (pvalue)
		{
			const std::string* pfind_value= avl_tree_strings.find(*pvalue);
			if (null == pfind_value)
			{
				std::cout << "find null" << std::endl;
			}
			else
			{
				std::cout << *pfind_value << std::endl;
			}
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		array_iterator_strings.increment();
	}

	array_iterator_strings.init(ITERATOR_INIT_BEGIN_INDEX);
	std::cout << "inc ....." << std::endl;
	while (1)
	{
		const std::string* pvalue = array_strings.get_at(&array_iterator_strings);
		if (pvalue)
		{
			avl_result res = avl_tree_strings.erase(*pvalue);
			if (P_OK != res)
			{
				std::cout << "erase error" << std::endl;
			}
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		array_iterator_strings.increment();
	}

	array_iterator_strings.init(ITERATOR_INIT_BEGIN_INDEX);
	std::cout << "inc ....." << std::endl;
	while (1)
	{
		const std::string* pvalue = array_strings.get_at(&array_iterator_strings);
		if (pvalue)
		{
			avl_result res = avl_tree_strings.insert(*pvalue);
			if (P_OK != res)
			{
				std::cout << "insert error" << std::endl;
			}
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		array_iterator_strings.increment();
	}

	//pecker_avl_tree_inorder_iterator< std::string,stringcmp_t,AVL_node_set< std::string > > tree_iterator_strings(avl_tree_strings.get_root());
	pecker_bst_tree_no_perent_node_inorder_iterator_base< _AVL_node_base > tree_iterator_strings;
	avl_tree_strings.get_iterator(&tree_iterator_strings);

	tree_iterator_strings.init();
	std::cout << "tree iterator inc ....." << std::endl;
	while (1)
	{
		const std::string* pvalue = avl_tree_strings.get_at(&tree_iterator_strings);
		if (pvalue)
		{
			std::cout << *pvalue << std::endl;
			if ( "yard" == *pvalue)
			{
				pvalue = pvalue;
			}
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}

		
		if ( P_OK != tree_iterator_strings.increment())
		{
			break;
		}
	}

	std::cout << std::endl << std::endl << "tree iterator dec ....." << std::endl;
	while (1)
	{
		const std::string* pvalue = avl_tree_strings.get_at(&tree_iterator_strings);
		if (pvalue)
		{
			std::cout << *pvalue << std::endl;
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		if ( P_OK != tree_iterator_strings.decrement())
		{
			break;
		}
	}

	std::cout << "tree iterator inc  && dec....." << std::endl;
	for (int i=0;i<100;++i)
	{
		const std::string* pvalue = avl_tree_strings.get_at(&tree_iterator_strings);
		if (pvalue)
		{
			std::cout << i << " = " << *pvalue << std::endl;
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		if ( P_OK != tree_iterator_strings.increment())
		{
			break;
		}
	}
	for (int i = 0;i<50;++i)
	{
		const std::string* pvalue = avl_tree_strings.get_at(&tree_iterator_strings);
		if (pvalue)
		{
			std::cout << i << " = " << *pvalue << std::endl;
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		if ( P_OK != tree_iterator_strings.decrement())
		{
			break;
		}
	}

	//pecker_avl_tree_posorder_iterator_base tree_pos_iterator(avl_tree_strings.get_root());
	//tree_pos_iterator.init();
	pecker_bst_tree_no_perent_node_posorder_iterator_base< _AVL_node_base > tree_pos_iterator;
	avl_tree_strings.get_iterator(&tree_pos_iterator);
	std::cout << "tree pos iterator inc  && dec....." << std::endl;
	for (int i=0;i<50;++i)
	{
		const std::string* pvalue = avl_tree_strings.get_at(&tree_pos_iterator);
		if (pvalue)
		{
			std::cout << i << " = " << *pvalue << std::endl;
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		if ( P_OK != tree_pos_iterator.increment_right())
		{
			break;
		}
	}

	for (int i=0;i<20;++i)
	{
		const std::string* pvalue = avl_tree_strings.get_at(&tree_pos_iterator);
		if (pvalue)
		{
			std::cout << i << " = " << *pvalue << std::endl;
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		if ( P_OK != tree_pos_iterator.increment_left())
		{
			break;
		}
	}


	avl_tree_strings_copy.copy(&avl_tree_strings);
	avl_tree_strings.clear();

	tree_iterator_strings.reinit(avl_tree_strings_copy.get_root());
	std::cout  << std::endl << std::endl << std::endl << std::endl<< "copy tree iterator inc ....." << std::endl;

	while (1)
	{
		const std::string* pvalue = avl_tree_strings_copy.get_at(&tree_iterator_strings);
		if (pvalue)
		{
			std::cout <<*pvalue << std::endl;
		}
		else
		{
			std::cout << "null" << std::endl;
			break;
		}
		if ( P_OK != tree_iterator_strings.increment())
		{
			break;
		}
	}

	avl_tree_strings_copy.clear();

	return 0;
}

int avl_map_time(pecker_array< std::string >& array );
int stl_map_time(pecker_array< std::string >& array);

int avl_stl_map_cmp(int itime = 1)
{
	pecker_array< std::string > array;
	array.init(100000,256);
	LARGE_INTEGER litmp; 
	LONGLONG QPartStartTick,QPartStopTick;
	double dfMinus, dfFreq, dfEscapeTime;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;   // 获得计数器的时钟频率
	std::ifstream myfile;

	myfile.close();
	myfile.open("inputaddsearch.txt");

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;               // 获得初始值
	while(1)
	{
		if (myfile.eof())
			break;

		std::string strin;
		myfile >> strin;
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfEscapeTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒

	std::cout << "read file time = " << dfEscapeTime << std::endl;

	myfile.close();
	myfile.open("inputaddsearch.txt");

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	while(1)
	{
		if (myfile.eof())
			break;

		std::string strin;
		myfile >> strin;

		array.push(strin);
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfEscapeTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "load file to mem "<< dfEscapeTime << std::endl;
	std::cout << "......." << std::endl;

	for (int i=0;i<itime;++i)
	{
		std::cout << "......." << i << "......"<< std::endl;
		stl_map_time(array);
		avl_map_time(array);
		std::cout << "......." << std::endl;
	}
	return 0;
}
int avl_map_time(pecker_array< std::string >& array )
{
	pecker_array_iterator< pecker_array<std::string> >array_iterator1;
	array.get_iterator(&array_iterator1);

	pecker_avl_tree_map_container< std::string,int,stringcmp_t,AVL_node_map< std::string,int >,pecker_nodes_simple_allocater< AVL_node_map< std::string,int > > > avl_tree_strings_map;

	std::cout << "......." << std::endl;

	LARGE_INTEGER litmp; 
	LONGLONG QPartStartTick,QPartStopTick;
	double dfMinus, dfFreq, dfEscapeTime;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;   // 获得计数器的时钟频率
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	while (1)
	{
		const std::string* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			if (P_OK != avl_tree_strings_map.insert(*pvalue,icount))
			{
				std::cout << "avl insert error" << std::endl;
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfEscapeTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "avl insert "<< dfEscapeTime << std::endl;

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	while (1)
	{
		const std::string* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			//avl_tree_strings_map.find(*pvalue); // release会直接和谐,所以要加点东西
			if (null == avl_tree_strings_map.find(*pvalue))
			{
				std::cout << "find null" << std::endl;
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfEscapeTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "avl find "<< dfEscapeTime << std::endl;

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	while (1)
	{
		const std::string* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			if (P_OK != avl_tree_strings_map.erase(*pvalue))
			{
				std::cout << "erase error" << std::endl;
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfEscapeTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "avl erase "<< dfEscapeTime << std::endl;
	return 0;
}

int stl_map_time(pecker_array< std::string >& array)
{
	pecker_array_iterator< pecker_array<std::string> >array_iterator1;
	array.get_iterator(&array_iterator1);
	std::map<std::string,int> stl_string_map;

	LARGE_INTEGER litmp; 
	LONGLONG QPartStartTick,QPartStopTick;
	double dfMinus, dfFreq, dfEscapeTime;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;   // 获得计数器的时钟频率
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;

	std::cout << "......." << std::endl;
	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	while (1)
	{
		const std::string* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			stl_string_map.insert(std::map<std::string , int >::value_type( *pvalue,icount));
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfEscapeTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "stl map insert "<< dfEscapeTime << std::endl;

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);


	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	while (1)
	{
		const std::string* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			stl_string_map.find(*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfEscapeTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "stl map find "<< dfEscapeTime << std::endl;

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	while (1)
	{
		const std::string* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			//std::cout << *pvalue << ",";
			stl_string_map.erase(*pvalue);
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfEscapeTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "stl map erase "<< dfEscapeTime << std::endl;
	return 0;
}