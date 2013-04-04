#include "pool_alloc.h"
#include <iostream>
using namespace std;

//HASH_ITEM_INIT(hashint,int,int) 
//POOL_ALLOCATE_INIT(hashint,hash_item_hashint_,256) 
HASH_TABLE_INIT(hashint,int,int,2,4,hash_fun_,cmp_fun_);
int pool_alloc_main()
{
	hash_hashint_table table_;
	hash_hashint_table_init(&table_);

	for (int i=0;i<20;++i)
	{
		int ires = hash_hashint_table_insert(&table_,i,20-i);
		if (ires)
		{
			cout << "insert error " << ires << endl;
		}
		else
		{
			cout<<"insert ok" << 20-i << endl;
		}
	}
	
	for (int i=0;i<20;++i)
	{
		int* ires = hash_hashint_table_find(&table_,i);
		if (ires)
		{
			cout << "find " << *ires << endl;
		}
		else
		{
			cout << "find null" <<endl;
		}
	}
	
		pool_hashint_item* pooltem = table_._M_allocator._M_allocate;
		cout << "iterator" << endl;
		while(1)
		{
			hash_item_hashint_* itrval = pool_hashint_mem_iterator_inc(pooltem,&pooltem);
			if (itrval)
			{
				cout << itrval->_M_value << endl;
				hash_hashint_table_erase_node(itrval);
			}
			else
			{
				break;
			}
		}
	
	for (int i=0;i<20;++i)
	{
		int* ires = hash_hashint_table_find(&table_,i);
		if (ires)
		{
			int delres = hash_hashint_table_erase_value(ires);
			if (delres)
			{
				cout << "del err " <<delres <<endl;
			}
			else
			{
				cout << "del ok" << endl;
			}
		}
		else
		{
			cout << "find null" <<endl;
		}
	}
	return 0;
}
//int pool_alloc_main()
//{
//	hash_table table_;
//	hash_table_init(&table_);
//
//	for (int i=0;i<20;++i)
//	{
//		int ires = hash_table_insert(&table_,i,20-i);
//		if (ires)
//		{
//			cout << "insert error " << ires << endl;
//		}
//	}
//
//	for (int i=0;i<20;++i)
//	{
//		int* ires = hash_table_find(&table_,i);
//		if (ires)
//		{
//			cout << "find " << *ires << endl;
//		}
//		else
//		{
//			cout << "find null" <<endl;
//		}
//	}
//
//		pool_item* pooltem = table_._M_allocator._M_allocate;
//		cout << "iterator" << endl;
//		while(1)
//		{
//			hash_item* itrval = pool_mem_iterator_inc(pooltem,&pooltem);
//			if (itrval)
//			{
//				cout << itrval->_M_value << endl;
//			}
//			else
//			{
//				break;
//			}
//		}
//
//	for (int i=0;i<20;++i)
//	{
//		int* ires = hash_table_find(&table_,i);
//		if (ires)
//		{
//			int delres = hash_table_erase_value(ires);
//			if (delres)
//			{
//				cout << "del err " <<delres <<endl;
//			}
//			else
//			{
//				cout << "del ok" << endl;
//			}
//		}
//		else
//		{
//			cout << "find null" <<endl;
//		}
//	}
//	return 0;
//}
//int pool_alloc_main()
//{
//	pool_mem pool_;
//	pool_mem_init(&pool_);
//	value_t* allocitem[POOL_MAX_SIZE];
//	for (int i=0;i<POOL_MAX_SIZE;++i)
//	{
//		allocitem[i] = 0;
//	}
//	for (int i=0;i<20;++i)
//	{
//		allocitem[i] = pool_mem_allocate(&pool_);
//		if (0 == allocitem[i])
//		{
//			cout << "allocate null" << endl;
//			break;
//		}
//		else
//		{
//			*(allocitem[i]) = i;
//		}
//	}
//
//	pool_item* pooltem = pool_._M_allocate;
//	cout << "iterator" << endl;
//	while(1)
//	{
//		value_t* itrval = pool_mem_iterator_inc(pooltem,&pooltem);
//		if (itrval)
//		{
//			cout << *itrval << endl;
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	for (int i=0;i<21;++i)
//	{
//		int  res = pool_mem_deallocate(&pool_,allocitem[i]);
//		if (0 != res)
//		{
//			cout << "deallocate error = " << res << endl;
//		}
//	}
//
//
//	return 0;
//}