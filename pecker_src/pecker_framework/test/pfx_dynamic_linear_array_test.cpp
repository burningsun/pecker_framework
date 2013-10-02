/*
 *  pfx_dynamic_linear_array_test.cpp
 *
 *  Created on: 2013-9-20
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../data/pfx_array_algorithm.h"
#include "../native/pfx_allocator.h"
#include "../native/pfx_log.h"

PFX_C_EXTERN_BEGIN



PFX_C_EXTERN_END



int dynamic_linear_array_test_main()
{
	pfx_result_t status;
	pfx_index_t	i;
	pfx_u64_t push_back_n_items[50];
	pfx_dynamic_linear_array_t*  parray = new_dynamic_linear_array(&gDefualt_allocator,
		sizeof(pfx_u64_t),16,16,32,ALIGNED_1_BYTE,&gDefualt_allocator,&gDefualt_allocator,&status);

	if (PFX_STATUS_OK != status)
	{
		PECKER_LOG_("new_base_array status = %d\n",status);
		return 0;
	}

	for (i=0;i<1000;++i)
	{
		pfx_u64_t add_item = i;
		pfx_u64_t* padd_item = (pfx_u64_t*)dynamic_linear_array_push_back(parray,&add_item,&status);
		PECKER_LOG_("base_array_push_back status = %d\n",status);
		if (null == padd_item)
		{
			PECKER_LOG_("base_array_push_back padd_item=%d\n",padd_item);
		}
		else
		{
			PECKER_LOG_("base_array_push_back &add_item=%08X,padd_item=%08X,*padd_item=%ld\n",&add_item,padd_item,*padd_item);
		}
	}

	for (i=0;i<1000;++i)
	{
		pfx_u64_t* pitem = (pfx_u64_t*)get_item_at_dynamic_linear_array_linear(parray,i);
		if (null == pitem)
		{
			PECKER_LOG_("base_array_push_back item=%d\n",pitem);
		}
		else
		{
			PECKER_LOG_("base_array_push_back &item=%08X,*pitem=%ld\n",pitem,*pitem);
		}
	}


	for (i=0;i<1000;++i)
	{
		pfx_u64_t* pop_item = (pfx_u64_t*)dynamic_linear_array_pop_back(parray,pfx_false,&status);
		PECKER_LOG_("base_array_pop_back status = %d\n",status);
		if (null == pop_item)
		{
			PECKER_LOG_("base_array_push_back padd_item=%d\n",pop_item);
		}
		else
		{
			PECKER_LOG_("base_array_push_back,padd_item=%08X,*padd_item=%ld\n",pop_item,*pop_item);
		}
	}

	status = clear_dynamic_linear_array(parray,pfx_true);
	PECKER_LOG_("clear_base_array status = %d\n",status);

	for (i=0;i<(sizeof(push_back_n_items)/sizeof(pfx_u64_t));++i)
	{
		push_back_n_items[i] = i;
	}

	for (i=0;i<20;++i)
	{
		pfx_u64_t* padd_item = (pfx_u64_t*)dynamic_linear_array_push_back_n(parray,push_back_n_items,(sizeof(push_back_n_items)/sizeof(pfx_u64_t)),&status);
		PECKER_LOG_("base_array_push_back status = %d\n",status);
		if (null == padd_item)
		{
			PECKER_LOG_("base_array_push_back_n padd_item=%d\n",padd_item);
		}
		else
		{
			PECKER_LOG_("base_array_push_back_n padd_item=%08X,*padd_item=%ld\n",padd_item,*padd_item);
		}
	}

	for (i=0;i<1000;++i)
	{
		pfx_u64_t* pitem = (pfx_u64_t*)get_item_at_dynamic_linear_array_linear(parray,i);
		if (null == pitem)
		{
			PECKER_LOG_("base_array_push_back item=%d\n",pitem);
		}
		else
		{
			PECKER_LOG_("base_array_push_back &item=%08X,*pitem=%ld\n",pitem,*pitem);
		}
	}

	
	for (i=0;i<20;++i)
	{
		size_t ncount = 0;
		pfx_u64_t* pop_item = (pfx_u64_t*)dynamic_linear_array_pop_back_n(parray,(sizeof(push_back_n_items)/sizeof(pfx_u64_t)),pfx_false,&ncount,&status);
		//PECKER_LOG_("base_array_pop_back status = %d,count = %d\n",status,ncount);
		PECKER_LOG_("base_array_pop_back status = %d",status);
		if (null == pop_item)
		{
			PECKER_LOG_("base_array_push_back padd_item=%d\n",pop_item);
		}
		else
		{
			PECKER_LOG_("base_array_push_back,pop_item=%08X,count = %d\n,*pop_item=%ld\n",pop_item,ncount,*pop_item);
		}
	}

	delete_dynamic_linear_array(parray,&gDefualt_allocator);
	parray = null;

	return 0;
}


