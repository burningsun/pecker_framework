#include "data/pecker_array.h"
#include "data/pecker_avl_tree.h"
#include "data/pecker_balance_tst_algorithm.h"
#include "native/pecker_file_io.h"
#include "native/pecker_stream.h"
#include "data/pecker_value_compare.h"

USING_PECKER_SDK
//int pecker_value_compare<char>::tst_char_cmp_count = 0;

typedef pecker_tst_set_node<char, pecker_value_compare<char>,
		pecker_simple_allocator<char>, _AVL_node_base> _TST_node;
typedef pecker_share_string_base_t<char, pecker_value_compare<char>,
		pecker_simple_allocator<char> > String_base;
typedef pecker_nodes_simple_allocater<_TST_node> _TST_node_allocater;


int btst_test_main()
{

	//    int cmp111 = 0;
	//	int retn = testapp2< int,_TST_node_set >(ptst_root_node,cmp111);

	_TST_node_allocater node_alloc;
	_TST_node* ptst_root_node = null;
	_TST_node* ptst_temp_node = null;
	String_base string_test;
	avl_result myresult = 0;
	tst_node_count_val tst_node_count = 0;
	string_test.init("12345678", 8);

	ptst_temp_node = avl_tst_tree_insert<char,
			_TST_node_allocater, String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			(tst_buffer_size) (string_test.get_string_length()), node_alloc,
			myresult,tst_node_count);

	string_test.init("123456", 6);

	ptst_temp_node = avl_tst_tree_insert<char,
			_TST_node_allocater, String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc, myresult,tst_node_count);

	string_test.init("1234567890", 10);

	ptst_temp_node = avl_tst_tree_insert<char,
			_TST_node_allocater,String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc, myresult,tst_node_count);

	string_test.init("1234568907", 10);

	ptst_temp_node = avl_tst_tree_insert<char,
			_TST_node_allocater, String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc, myresult,tst_node_count);

	string_test.init("1231234567", 10);

	ptst_temp_node = avl_tst_tree_insert<char,
			_TST_node_allocater, String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc, myresult,tst_node_count);

	string_test.init("234567890", 9);
	ptst_temp_node = avl_tst_tree_insert<char, 
			_TST_node_allocater, String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc, myresult,tst_node_count);

	string_test.init("34567890", 8);
	ptst_temp_node = avl_tst_tree_insert<char, 
			_TST_node_allocater,String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc, myresult,tst_node_count);

	string_test.init("4567890", 7);
	ptst_temp_node = avl_tst_tree_insert<char,
			_TST_node_allocater,String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc, myresult,tst_node_count);

	ptst_temp_node = avl_tst_tree_find_referance<char,_TST_node>(ptst_root_node,
			string_test.get_data(), string_test.get_string_length());

	string_test.init("34567890", 8);
	ptst_temp_node = avl_tst_tree_find_referance<char, _TST_node>(ptst_root_node,
			string_test.get_data(), string_test.get_string_length());

	string_test.init("234567890", 9);
	ptst_temp_node = avl_tst_tree_find_referance<char, _TST_node>(ptst_root_node,
			string_test.get_data(), string_test.get_string_length());

	string_test.init("1231234567", 10);
	ptst_temp_node = avl_tst_tree_find_referance<char, _TST_node>(ptst_root_node,
			string_test.get_data(), string_test.get_string_length());

	string_test.init("1234568907", 10);
	ptst_temp_node = avl_tst_tree_find_referance<char, _TST_node>(ptst_root_node,
			string_test.get_data(), string_test.get_string_length());

	string_test.init("1234567890", 10);
	ptst_temp_node = avl_tst_tree_find_referance<char, _TST_node>(ptst_root_node,
			string_test.get_data(), string_test.get_string_length());

	string_test.init("1231234567", 10);
	myresult = avl_tst_tree_erase<char, //pecker_value_compare<char>,
			_TST_node_allocater, String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc,tst_node_count);

	string_test.init("1234568907", 10);
	myresult = avl_tst_tree_erase<char, //pecker_value_compare<char>,
			_TST_node_allocater, String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc,tst_node_count);

	string_test.init("123456", 6);
	myresult = avl_tst_tree_erase<char, //pecker_value_compare<char>,
			_TST_node_allocater,String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc,tst_node_count);

	string_test.init("12345678", 8);
	myresult = avl_tst_tree_erase<char, //pecker_value_compare<char>,
			_TST_node_allocater,String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc,tst_node_count);
	string_test.init("1234567890", 10);
	myresult = avl_tst_tree_erase<char, //pecker_value_compare<char>,
			_TST_node_allocater,String_base, _TST_node>(
			ptst_root_node, string_test.get_data(),
			string_test.get_string_length(), node_alloc,tst_node_count);

	return 0;
}



typedef int tst_map_value;
//typedef pecker_tst_set_node<char,pecker_value_compare<char>,pecker_simple_allocator< char >,_AVL_node_base> _TST_set_node;
typedef pecker_tst_map_node<char,tst_map_value,pecker_value_compare<char>,pecker_simple_allocator< char >,_AVL_node_base> _TST_map_node;
//typedef pecker_share_string_base_t< char,pecker_simple_allocator< char >,pecker_simple_allocator< char > >  String_base;
//typedef pecker_nodes_simple_allocater< _TST_node > _TST_node_allocater;
typedef pecker_nodes_simple_allocater<_TST_map_node > _TST_map_node_allocater;

//#ifdef WINDOWS_PC
//#include <Windows.h>
//#include <iostream>
//#include <fstream>
//#include <string>
//#endif
//

#include "native/pecker_timetick.h"
#include "native/pecker_log.h"
#include <stdio.h>
#include <string.h>
static char string_log_buf[1024];
int tst_stress_time(pecker_array< String_base >& array)
{
	_TST_map_node_allocater node_alloc;
	_TST_map_node* ptst_root_node = null;
	_TST_map_node* ptst_temp_node = null;
	tst_node_count_val tst_node_count = 0;
	String_base string_test;
	avl_result myresult = 0;
	pecker_tick escape_time;
	pecker_array_iterator< pecker_array<String_base> >array_iterator1;
	array.get_iterator(&array_iterator1);
	escape_time.init();

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	int itestcount = -1;
    Double dfEscapeTime;

    PECKER_LOG_INFO("tst_stress_time",".......");

	escape_time.start();
	while (1)
	{
		const String_base* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			ptst_temp_node = avl_tst_tree_insert< char,_TST_map_node_allocater,String_base,_TST_map_node>(ptst_root_node,
				pvalue->get_data(),
				pvalue->get_string_length(),
				node_alloc,myresult,tst_node_count);


			if (ptst_temp_node)
			{
				ptst_temp_node->value = icount++;
			}
			else
			{
				sprintf(string_log_buf,"string = %%%d.%ds result=%%d",pvalue->get_string_length(),pvalue->get_string_length());
				PECKER_LOG_ERR("tst insert null",string_log_buf,pvalue->get_data(),myresult);
				//std::cout << "insert null" << myresult << std::endl;
			}

		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("tst map insert","dfEscapeTime = %f ms",dfEscapeTime);

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	icount = 0;
	escape_time.start();
	while (1)
	{
		const String_base* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			const _TST_map_node* pctst_temp_node = avl_tst_tree_find<char,_TST_map_node>(ptst_root_node,
				pvalue->get_data(),pvalue->get_string_length());
			if (null == pctst_temp_node)
			{
				//std::cout << *pvalue << std::endl;
				sprintf(string_log_buf,"string = %%%d.%ds",pvalue->get_string_length(),pvalue->get_string_length());
				PECKER_LOG_ERR("tst find null",string_log_buf,pvalue->get_data());
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("tst map find","dfEscapeTime = %f ms",dfEscapeTime);

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	icount = 0;
	escape_time.start();
	while (1)
	{
		const String_base* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			myresult = avl_tst_tree_erase<char,_TST_map_node_allocater,String_base,_TST_map_node>
				(ptst_root_node,
				pvalue->get_data(),
				pvalue->get_string_length(),
				node_alloc,
				tst_node_count);
			if (myresult != PEK_STATUS_OK)
			{
				sprintf(string_log_buf,"string = %%%d.%ds result = %%d",pvalue->get_string_length(),pvalue->get_string_length());
				PECKER_LOG_ERR("tst erase error",string_log_buf,pvalue->get_data(),myresult);
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("tst map erase","dfEscapeTime = %f ms",dfEscapeTime);
	return 0;
}



int avl_char_cmp_count__ = 0;
struct pecker_value_compare__
{
	inline int operator () (const char &char1,const char &char2)  const
	{
		return (char1 - char2);
	}
	static  inline int compare(const char &char1,const char &char2)
	{
		//++avl_char_cmp_count__;
		return (char1 - char2);
	}
};
struct stringcmp_t_
{
	inline int operator () (const String_base & str1,const String_base & str2) const
	{
		//return str1.compare(str2.get_data(),str2.get_string_length());
		//return str1.compare(str2);

		int ilen1 = str1.get_string_length();
		int ilen2 =  str2.get_string_length();
		const char* pstrchar1 = str1.get_data();
		const char* pstrchar2 = str2.get_data();

		int imin = ilen1;
		if (imin > ilen2)
			imin = ilen2;
		for (int i=0;i<imin;++i)
		{
			int iretn = pecker_value_compare__::compare( *(pstrchar1+i) , *(pstrchar2+i));
			if (0 != iretn)
			{
				return iretn;
			}
		}
		return (ilen1 - ilen2);
	}
};

typedef pecker_avl_tree_map_container< String_base,int,stringcmp_t_,AVL_node_map< String_base,int >,pecker_nodes_simple_allocater< AVL_node_map< String_base,int > > > _AVL_Tree_map;
_TST_map_node* tst_stress_insert_time(pecker_array< String_base >& array)
{
	_TST_map_node_allocater node_alloc;
	_TST_map_node* ptst_root_node = null;
	_TST_map_node* ptst_temp_node = null;
	tst_node_count_val tst_node_count = 0;
	String_base string_test;
	avl_result myresult = 0;
	pecker_array_iterator< pecker_array<String_base> >array_iterator1;
	array.get_iterator(&array_iterator1);

	pecker_tick escape_time;
	escape_time.init();

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	int itestcount = -1;
	Double dfEscapeTime;

	PECKER_LOG_INFO("tst_stress_insert_time","begin.......");

	escape_time.start();
	while (1)
	{
		const String_base* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			ptst_temp_node = avl_tst_tree_insert< char,_TST_map_node_allocater,String_base,_TST_map_node>(ptst_root_node,
				pvalue->get_data(),
				pvalue->get_string_length(),
				node_alloc,myresult,tst_node_count);


			if (ptst_temp_node)
			{
				ptst_temp_node->value = icount++;
			}
			else
			{
				//std::cout << "insert null" << myresult << std::endl;

				PECKER_LOG_ERR("tst insert null","result = %d",myresult);
			}


		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("tst map insert","dfEscapeTime = %f ms",dfEscapeTime);

	return ptst_root_node;
}
int tst_stress_find_time(pecker_array< String_base >& array,_TST_map_node* ptst_root_node)
{
	_TST_node_allocater node_alloc;
	const _TST_map_node* pctst_temp_node = null;
	String_base string_test;
	avl_result myresult = 0;
	pecker_tick escape_time;
	pecker_array_iterator< pecker_array<String_base> >array_iterator1;
	array.get_iterator(&array_iterator1);
	escape_time.init();

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	int itestcount = -1;
    Double dfEscapeTime;
	PECKER_LOG_ENDLINE
    PECKER_LOG_INFO("tst_stress_find_time","begin.......");

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	icount = 0;
	escape_time.start();
	while (1)
	{
		const String_base* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			pctst_temp_node = avl_tst_tree_find<char,_TST_map_node>(ptst_root_node,
				pvalue->get_data(),pvalue->get_string_length());
			if (null == pctst_temp_node)
			{
				//std::cout << *pvalue << std::endl;
				sprintf(string_log_buf,"string = %%%d.%ds",pvalue->get_string_length(),pvalue->get_string_length());
				PECKER_LOG_ERR("tst insert null",string_log_buf,pvalue->get_data());
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("tst map find","dfEscapeTime = %f ms",dfEscapeTime);
	PECKER_LOG_ENDLINE
	return 0;
}

int  avl_stress_insert_time(pecker_array< String_base >& array ,_AVL_Tree_map& avl_tree_strings_map)
{
	pecker_array_iterator< pecker_array<String_base> >array_iterator1;
	pecker_tick escape_time;
	array.get_iterator(&array_iterator1);
	escape_time.init();
	Double dfEscapeTime;
	PECKER_LOG_ENDLINE
	PECKER_LOG_INFO("avl_stress_insert_time","begin.......");


	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	int res = 0;

	escape_time.start();
	while (1)
	{
		const String_base* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			res = avl_tree_strings_map.insert(*pvalue,icount);
			if (PEK_STATUS_OK != res)
			{
				sprintf(string_log_buf,"string = %%%d.%ds result=%%d icount = %%d",pvalue->get_string_length(),pvalue->get_string_length());
				PECKER_LOG_ERR("tst insert error",string_log_buf,pvalue->get_data(),res,icount);
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		icount++;
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("avl map insert","dfEscapeTime = %f ms",dfEscapeTime);
	PECKER_LOG_ENDLINE
	return 0;
}

int  avl_stress_find_time(pecker_array< String_base >& array ,_AVL_Tree_map& avl_tree_strings_map)
{
	pecker_array_iterator< pecker_array<String_base> >array_iterator1;
	pecker_tick escape_time;
	array.get_iterator(&array_iterator1);
	escape_time.init();
	Double dfEscapeTime;

	PECKER_LOG_ENDLINE
	PECKER_LOG_INFO("avl_stress_find_time","begin.......");

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;

	escape_time.start();
	while (1)
	{
		const String_base* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			if (null == avl_tree_strings_map.find(*pvalue))
			{
				sprintf(string_log_buf,"string = %%%d.%ds",pvalue->get_string_length(),pvalue->get_string_length());
				PECKER_LOG_ERR("avl find null",string_log_buf,pvalue->get_data());
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("avl map find","dfEscapeTime = %f ms",dfEscapeTime);

	PECKER_LOG_ENDLINE
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
int _2_map_cmp(int itime = 1)
{
	pecker_array< String_base > array;
	array.init(1000000,256);
	pecker_tick escape_time;
	Double dfEscapeTime;
	escape_time.init();

	//std::ifstream myfile;
	pecker_file_io_base myfile;
	myfile.open("inputaddsearch.txt",strlen("inputaddsearch.txt"),PF_FILE_READ_ONLY);
	Char* pFILE_BUFF = null;
	pecker_read_stream_form_memery read_stream;
	Bytes read_buffer = {null,0};
	if (myfile.get_file_size() > 0)
	{
		pFILE_BUFF = new Char[myfile.get_file_size()];
		read_buffer._M_buffer = pFILE_BUFF;
		read_buffer._M_buffer_size = myfile.get_file_size();
		myfile.read_to_memery(read_buffer);
		read_stream.bind_read_buffer(read_buffer._M_buffer,read_buffer._M_buffer_size);

	}

	
	
	static Char string_buff[4096];
	//myfile.close();
	//myfile.open("inputaddsearch.txt");

	
	String_base strin;
	//strin.init(256);

	//std::ifstream mystdfile;
	//std::string stdstrin;
	//mystdfile.open("inputaddsearch.txt");

	escape_time.start();
	while(1)
	{
		int iread = read_stream.read_chars(string_buff,4096);
		if (0 == iread)
		{
			break;
		}
		strin.init(string_buff,iread);
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("read file time","dfEscapeTime = %f ms",dfEscapeTime);

//	myfile.close();
//	myfile.open("inputaddsearch.txt");


	read_stream.bind_read_buffer(read_buffer._M_buffer,read_buffer._M_buffer_size);
	escape_time.start();
	//while(1)
	//{
	//	if (myfile.eof())
	//		break;

	//	String_base strin;
	//	myfile >> strin;

	//	array.push(strin);
	//}
	while(1)
	{
		int iread = read_stream.read_chars(string_buff,4096);
		if (0 == iread)
		{
			break;
		}
		strin.init(string_buff,iread);
		array.push(strin);
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();

	PECKER_LOG_INFO("load file to mem","dfEscapeTime = %f ms",dfEscapeTime);

	_AVL_Tree_map avl_tree_strings_map;
	avl_stress_insert_time(array,avl_tree_strings_map);
	_TST_map_node* ptstroot = tst_stress_insert_time(array);
	
	
	//pecker_value_compare<char>::tst_char_cmp_count = 0;
	avl_char_cmp_count__ = 0;

	for (int i=0;i<itime;++i)
	{
//		std::cout << "......." << i << "......"<< std::endl;
		avl_stress_find_time(array,avl_tree_strings_map);
		tst_stress_find_time(array,ptstroot);
		 
//		std::cout << "......." << std::endl;
	}

	PECKER_LOG_INFO("avl cmp totle times","count = %d",avl_char_cmp_count__);
	//PECKER_LOG_INFO("tst cmp totle times","count = %d",pecker_value_compare<char>::tst_char_cmp_count);
	return 0;
}

struct stringcmp_t_std
{
	inline int operator () (const std::string & str1,const  std::string & str2) const
	{
		//return str1.compare(str2);
		int ilen1 = str1.length();
		int ilen2 =  str2.length();
		const char* pstrchar1 = str1.data();
		const char* pstrchar2 = str2.data();

		int imin = ilen1;
		if (imin > ilen2)
			imin = ilen2;
		for (int i=0;i<imin;++i)
		{
			int iretn = pecker_value_compare__::compare( *(pstrchar1+i) , *(pstrchar2+i));
			if (0 != iretn)
			{
				return iretn;
			}
		}
		return (ilen1 - ilen2);
	}
};
typedef pecker_avl_tree_map_container< std::string,int,stringcmp_t_std,AVL_node_map< std::string,int >,pecker_nodes_simple_allocater<  AVL_node_map< std::string,int > > > _AVL_Tree_map_stdstr;
int  avl_std_string_stress_insert_time(pecker_array< std::string >& array ,_AVL_Tree_map_stdstr& avl_tree_strings_map)
{
	pecker_array_iterator< pecker_array< std::string > >array_iterator1;
	pecker_tick escape_time;
	array.get_iterator(&array_iterator1);
	escape_time.init();
	Double dfEscapeTime;
	PECKER_LOG_ENDLINE
	PECKER_LOG_INFO("avl_stress_insert_time","begin.......");


	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	int res = 0;

	escape_time.start();
	while (1)
	{
		const std::string* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			res = avl_tree_strings_map.insert(*pvalue,icount);
			if (PEK_STATUS_OK != res)
			{
				sprintf(string_log_buf,"string = %%%d.%ds result=%%d icount = %%d",pvalue->length(),pvalue->length());
				PECKER_LOG_ERR("tst insert error",string_log_buf,pvalue->data(),res,icount);
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		icount++;
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("avl std string map insert","dfEscapeTime = %f ms",dfEscapeTime);
	PECKER_LOG_ENDLINE
	return 0;
}

int  avl_std_string_stress_find_time(pecker_array< std::string >& array ,_AVL_Tree_map_stdstr& avl_tree_strings_map)
{
	pecker_array_iterator< pecker_array< std::string > >array_iterator1;
	pecker_tick escape_time;
	array.get_iterator(&array_iterator1);
	escape_time.init();
	Double dfEscapeTime;

	PECKER_LOG_ENDLINE
	PECKER_LOG_INFO("avl_std_string_stress_find_time",".......");

	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;

	escape_time.start();
	while (1)
	{
		const std::string* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			if (null == avl_tree_strings_map.find(*pvalue))
			{
				sprintf(string_log_buf,"string = %%%d.%ds",pvalue->length(),pvalue->length());
				PECKER_LOG_ERR("avl  find null",string_log_buf,pvalue->data());
			}
		}
		else
		{
			//std::cout << "null" << std::endl;
			break;
		}
		array_iterator1.increment();
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("avl std string map find","dfEscapeTime = %f ms",dfEscapeTime);
	PECKER_LOG_ENDLINE
	return 0;
}

int _2_avl_key_map_cmp(int itime = 1)
{
	pecker_array< String_base > array;
	pecker_array< std::string > arraystd;
	//pecker_array< std::string > arraystd_find;
	array.init(1000000,256);
	arraystd.init(1000000,256);
	//arraystd_find.init(1000000,256);
	pecker_tick escape_time;
	Double dfEscapeTime;
	escape_time.init();

	pecker_file_io_base myfile;
	myfile.open("inputaddsearch.txt",strlen("inputaddsearch.txt"),PF_FILE_READ_ONLY);
	Char* pFILE_BUFF = null;
	pecker_read_stream_form_memery read_stream;
	Bytes read_buffer = {null,0};
	if (myfile.get_file_size() > 0)
	{
		pFILE_BUFF = new Char[myfile.get_file_size()];
		read_buffer._M_buffer = pFILE_BUFF;
		read_buffer._M_buffer_size = myfile.get_file_size();
		myfile.read_to_memery(read_buffer);
		read_stream.bind_read_buffer(read_buffer._M_buffer,read_buffer._M_buffer_size);

	}


	static Char string_buff[4096];
	


	String_base strin;
	//strin.init(256);
	escape_time.start();

	while(1)
	{
		int iread = read_stream.read_chars(string_buff,4096);

		if (0 == iread)
		{
			break;
		}
		strin.init(string_buff,iread);
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("pecker read file time","dfEscapeTime = %f ms",dfEscapeTime);

	std::ifstream mystdfile;
	std::string stdstrin;
	mystdfile.open("inputaddsearch.txt");

	escape_time.start();
	while(1)
	{
		if (mystdfile.eof())
			break;

		mystdfile >> stdstrin;
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("std read file time","dfEscapeTime = %f ms",dfEscapeTime);

	//	myfile.close();
	//	myfile.open("inputaddsearch.txt");


	read_stream.bind_read_buffer(read_buffer._M_buffer,read_buffer._M_buffer_size);
	escape_time.start();
	//while(1)
	//{
	//	if (myfile.eof())
	//		break;

	//	String_base strin;
	//	myfile >> strin;

	//	array.push(strin);
	//}
	while(1)
	{
		int iread = read_stream.read_chars(string_buff,4096);
		if (0 == iread)
		{
			break;
		}
		strin.init(string_buff,iread);
		array.push(strin);
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("pecker load file to mem","dfEscapeTime = %f ms",dfEscapeTime);

	mystdfile.close();
	mystdfile.open("inputaddsearch.txt");

	escape_time.start();
	while(1)
	{
		if (mystdfile.eof())
			break;

		mystdfile >> stdstrin;
		arraystd.push(stdstrin);
	}
	dfEscapeTime = escape_time.get_microsecond();
	escape_time.stop();
	PECKER_LOG_INFO("std load file to mem","dfEscapeTime = %f ms",dfEscapeTime);

	arraystd.pop();

	//mystdfile.close();
	//mystdfile.open("inputaddsearch.txt");

	//while(1)
	//{
	//	if (mystdfile.eof())
	//		break;

	//	mystdfile >> stdstrin;
	//	arraystd_find.push(stdstrin);
	//}
	//arraystd_find.pop();

	//_TST_map_node* ptstroot = tst_stress_insert_time(array);
	_AVL_Tree_map avl_tree_strings_map;
	avl_stress_insert_time(array,avl_tree_strings_map);

	_AVL_Tree_map_stdstr avl_tree_stdstrings_map;
	avl_std_string_stress_insert_time(arraystd,avl_tree_stdstrings_map);


	//pecker_value_compare<char>::tst_char_cmp_count = 0;
	avl_char_cmp_count__ = 0;

	for (int i=0;i<itime;++i)
	{
		//		std::cout << "......." << i << "......"<< std::endl;
		//tst_stress_find_time(array,ptstroot);
		avl_stress_find_time(array,avl_tree_strings_map);
		avl_std_string_stress_find_time(arraystd,avl_tree_stdstrings_map);
		//		std::cout << "......." << std::endl;
	}

	return 0;
}