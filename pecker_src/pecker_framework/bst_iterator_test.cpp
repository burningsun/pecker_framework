#include "data/pecker_bst_iterator.h"
#include "data/pecker_balance_tenary_tree.h"
#include "native/pecker_log.h"
#include "native/pecker_file_io.h"
#include "native/pecker_stream.h"
#include "data/pecker_avl_tree.h"
#include "data/pecker_value_compare.h"
USING_PECKER_SDK

typedef pecker_tst_map_node<char,char, pecker_value_compare<char>,pecker_simple_allocator<char>, _AVL_node_base> _TST_node;
typedef pecker_share_string_base_t<char, pecker_value_compare<char>,pecker_simple_allocator<char> > String_base_itrtest;
typedef pecker_nodes_simple_allocater<_TST_node> _TST_node_allocater;
typedef pecker_btst_map_container<char,String_base_itrtest,char,_TST_node,_TST_node_allocater>   BTSTree;
typedef pecker_tst_tree_no_perent_node_inorder_iterator_base<  _TST_node, pecker_simple_allocator< const _TST_node* >,pecker_simple_allocator< const _TST_node** > > _TST_inorder_iterator;

typedef pecker_avl_tree_map_container< String_base_itrtest,int,
	pecker_value_compare_extern< String_base_itrtest >,
	AVL_node_map< String_base_itrtest,int >,
	pecker_nodes_simple_allocater< AVL_node_map< String_base_itrtest,int > > > _AVL_Tree_map;

typedef pecker_bst_tree_no_perent_node_inorder_iterator_base< _AVL_node_base > _AVL_inorder_iterator;

void print_pecker_string(const String_base_itrtest& string_)
{
	if (string_.get_string_length() > 0)
	{
		//if (0 == string_.compare("direct",6))
		//{
		//	int i=0;
		//	i=i;
		//}
		static char logifo[50];
		sprintf(logifo,"%%%d.%ds",string_.get_string_length(),string_.get_string_length());
		PECKER_LOG_(logifo,string_.get_data());
	}
	else
	{
		PECKER_LOG_("null string",0);
	}
}



void init_input_data(pecker_array< String_base_itrtest >& array)
{
	array.clear();
	array.init(1000000,256);
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

	String_base_itrtest strin;

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
}

void init_input_data2(pecker_array< String_base_itrtest >& array)
{
	array.clear();
	array.init(1000000,256);
	pecker_file_io_base myfile;
	myfile.open("input_itr_data.txt",strlen("input_itr_data.txt"),PF_FILE_READ_ONLY);
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

	String_base_itrtest strin;

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
}

void tst_iterator_test_value()
{
	BTSTree tst_map;
	pecker_array< String_base_itrtest > array;
	_TST_inorder_iterator inorder_iterator;

	init_input_data(array);
	pecker_array_iterator< pecker_array<String_base_itrtest> >array_iterator1;
	array.get_iterator(&array_iterator1);
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	while (1)
	{
		const String_base_itrtest* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			HResult res = tst_map.insert(*pvalue,icount);
			if (P_OK != res)
			{
				PECKER_LOG_ERR("tst insert error",0);
			}
		}
		else
		{
			break;
		}
		++icount;
		array_iterator1.increment();
	}

	tst_map.get_iterator(&inorder_iterator);

	inorder_iterator.init(ITERATOR_INIT_MIN);
	icount = 1;

	PECKER_LOG_("\nincrement\n",0);
	while(1)
	{

		if (inorder_iterator.get_current_node() && HAS_VALUE_TST_NODE ==inorder_iterator.get_current_node()->_M_legal_flag)
		{
			PECKER_LOG_("%05d ",icount);
			print_pecker_string(tst_map.get_key(&inorder_iterator));
			++icount;
			PECKER_LOG_("\n",0);
		}


		if (P_OK != inorder_iterator.increment())
		{
			break;
		}

	}

}
void tst_iterator_test_clear()
{
	BTSTree tst_map_og;
	BTSTree tst_map;
	pecker_array< String_base_itrtest > array;
	_TST_inorder_iterator inorder_iterator;

	init_input_data2(array);
	pecker_array_iterator< pecker_array<String_base_itrtest> >array_iterator1;
	array.get_iterator(&array_iterator1);
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	while (1)
	{
		const String_base_itrtest* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			HResult res = tst_map_og.insert(*pvalue,icount);
			if (P_OK != res)
			{
				PECKER_LOG_ERR("tst insert error",0);
			}
		}
		else
		{
			break;
		}
		++icount;
		array_iterator1.increment();
	}

	init_input_data(array);
	array.get_iterator(&array_iterator1);
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	icount = 0;
	while (1)
	{
		const String_base_itrtest* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			HResult res = tst_map.insert(*pvalue,icount);
			if (P_OK != res)
			{
				PECKER_LOG_ERR("tst insert error",0);
			}
		}
		else
		{
			break;
		}
		++icount;
		array_iterator1.increment();
	}

	tst_map.get_iterator(&inorder_iterator);

	inorder_iterator.init(ITERATOR_INIT_MIN);
	icount = 1;

	PECKER_LOG_("\nincrement\n",0);
	while(1)
	{
		PECKER_LOG_("%05d ",icount);
		print_pecker_string(tst_map.get_key(&inorder_iterator));
		++icount;
		PECKER_LOG_("\n",0);

		if (P_OK != inorder_iterator.increment())
		{
			break;
		}

	}

	PECKER_LOG_("\copy testing\n",0);
	tst_map.copy(&tst_map_og);
	tst_map.get_iterator(&inorder_iterator);

	inorder_iterator.init(ITERATOR_INIT_MIN);
	icount = 1;

	PECKER_LOG_("\nincrement\n",0);
	while(1)
	{
		PECKER_LOG_("%05d ",icount);
		print_pecker_string(tst_map.get_key(&inorder_iterator));
		++icount;
		PECKER_LOG_("\n",0);

		if (P_OK != inorder_iterator.increment())
		{
			break;
		}

	}

	PECKER_LOG_("\clear...\n",0);

}
void tst_iterator_test()
{
	BTSTree tst_map;
	pecker_array< String_base_itrtest > array;
	_TST_inorder_iterator inorder_iterator;
	
	init_input_data(array);
	pecker_array_iterator< pecker_array<String_base_itrtest> >array_iterator1;
	array.get_iterator(&array_iterator1);
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	while (1)
	{
		const String_base_itrtest* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			HResult res = tst_map.insert(*pvalue,icount);
			if (P_OK != res)
			{
				PECKER_LOG_ERR("tst insert error",0);
			}
		}
		else
		{
			break;
		}
		++icount;
		array_iterator1.increment();
	}

	tst_map.get_iterator(&inorder_iterator);

	inorder_iterator.init(ITERATOR_INIT_MIN);
	icount = 1;

	PECKER_LOG_("\nincrement\n",0);
	while(1)
	{
		PECKER_LOG_("%05d ",icount);
		print_pecker_string(tst_map.get_key(&inorder_iterator));
		++icount;
		PECKER_LOG_("\n",0);

		if (P_OK != inorder_iterator.increment())
		{
			break;
		}

	}

	inorder_iterator.init(ITERATOR_INIT_MAX);
	icount = 1;

	PECKER_LOG_("\ndecrement\n",0);
	while(1)
	{
		PECKER_LOG_("%05d ",icount);
		print_pecker_string(tst_map.get_key(&inorder_iterator));
		++icount;
		PECKER_LOG_("\n",0);

		if (P_OK != inorder_iterator.decrement())
		{
			break;
		}

	}

	PECKER_LOG_("\ndecrement then increment\n",0);
	inorder_iterator.init(ITERATOR_INIT_MAX);
	icount = 1;
	while(1)
	{
		//if (inorder_iterator.get_current_node() && HAS_VALUE_TST_NODE ==inorder_iterator.get_current_node()->_M_legal_flag)
		//{
			PECKER_LOG_("%05d ",icount);
			print_pecker_string(tst_map.get_key(&inorder_iterator));
			++icount;
			PECKER_LOG_("\n",0);
		//}
			//if (1894 == icount)
			//{
			//	icount = icount;
			//}
			//if (icount < 1000 || icount > 1500)
			//{
			//	if (P_OK != inorder_iterator.increment())
			//	{
			//		break;
			//	}
			//}
			//else
			//{
			//	if (P_OK != inorder_iterator.decrement())
			//	{
			//		break;
			//	}
			//}

			if (icount < 1000 || icount > 1500)
			{
				if (P_OK != inorder_iterator.decrement())
				{
					break;
				}
			}
			else
			{
				if (P_OK != inorder_iterator.increment())
				{
					break;
				}
			}

			//if (P_OK != inorder_iterator.decrement())
			//{
			//	break;
			//}
	}


}
void avlbst_iterator_test()
{
	_AVL_Tree_map avlbst_map;
	pecker_array< String_base_itrtest > array;
	_AVL_inorder_iterator inorder_iterator;

	init_input_data(array);
	pecker_array_iterator< pecker_array<String_base_itrtest> >array_iterator1;
	array.get_iterator(&array_iterator1);
	array_iterator1.init(ITERATOR_INIT_BEGIN_INDEX);
	int icount = 0;
	while (1)
	{
		const String_base_itrtest* pvalue = array.get_at(&array_iterator1);
		if (pvalue)
		{
			HResult res = avlbst_map.insert(*pvalue,icount);
			if (P_OK != res)
			{
				PECKER_LOG_ERR("tst insert error",0);
			}
		}
		else
		{
			break;
		}
		++icount;
		array_iterator1.increment();
	}

	avlbst_map.get_iterator(&inorder_iterator);
	icount = 1;
	while(1)
	{
		if (inorder_iterator.get_current_node())
		{
			PECKER_LOG_("%05d ",icount);
			print_pecker_string(avlbst_map.get_node(&inorder_iterator)->key);
			++icount;
			PECKER_LOG_("\n",0);
		}

		

		if (P_OK != inorder_iterator.increment())
		{
			break;
		}
	}
}