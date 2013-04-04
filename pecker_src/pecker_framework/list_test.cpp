#include "data/pecker_list.h"
#include "native/pecker_log.h"
USING_PECKER_SDK

int list_test()
{
	typedef pecker_list_iterator< pecker_linked_list_node_t< int >, pecker_list< int > > _List_iterator_;

	pecker_list< int > lstest1;
	pecker_list< int > lstest2;
	_List_iterator_ lsiterator1;
	_List_iterator_ lsiterator2;
	_List_iterator_ lsiterator3;

	for (int i=0;i<10;++i)
	{
		lstest1.push(i);
	}

	lstest1.get_iterator(&lsiterator1);
	lsiterator1.init(ITERATOR_INIT_BEGIN_INDEX);

	PECKER_LOG_("iterator inc\n",0);
	while(lsiterator1.get_current_node())
	{
		PECKER_LOG_("node value = %d \n",lsiterator1.get_current_node()->value);
		if (P_OK != lsiterator1.increment())
		{
			break;
		}
	}

	PECKER_LOG_("\niterator dec\n",0);
	while(lsiterator1.get_current_node())
	{
		PECKER_LOG_("node value = %d \n",lsiterator1.get_current_node()->value);
		if (P_OK != lsiterator1.decrement())
		{
			break;
		}
	}

	PECKER_LOG_("\niterator inc and dec\n",0);
	for (int i=0;i<5;++i)
	{
		if (lsiterator1.get_current_node())
		{
			PECKER_LOG_("node value = %d \n",lsiterator1.get_current_node()->value);
		}
		
		if (P_OK != lsiterator1.increment())
		{
			break;
		}
	}
	for (int i=0;i<5;++i)
	{
		if (lsiterator1.get_current_node())
		{
			PECKER_LOG_("node value = %d \n",lsiterator1.get_current_node()->value);
		}

		if (P_OK != lsiterator1.decrement())
		{
			break;
		}
	}

	lstest2.copy(lstest1);
	lsiterator2.copy(&lsiterator1);
	if (P_OK != lsiterator2.increment())
	{
		lsiterator2.decrement();
	}
	lstest1.erase(&lsiterator1);
	lsiterator1.copy(&lsiterator2);

	PECKER_LOG_("\nerase next.....\n",0);
	if (lsiterator1.get_current_node())
	{
		PECKER_LOG_("node value = %d \n",lsiterator1.get_current_node()->value);
	}
	else
	{
		PECKER_LOG_("node value = null",0);
	}

	lstest1.get_iterator(&lsiterator2);

	PECKER_LOG_("\nerase\n",0);
	for (int i=0;i<lstest1.get_size();++i)
	{
		if (lsiterator2.get_current_node())
		{
			PECKER_LOG_("node value = %d \n",lsiterator2.get_current_node()->value);
		}
		if (P_OK != lsiterator2.increment())
		{
			break;
		}
	}

	lstest1.get_iterator(&lsiterator1);
	lstest1.get_iterator(&lsiterator2);

	for (int i=0;i<4;++i)
	{
		lsiterator1.increment();
	}
	for (int i=0;i<7;++i)
	{
		lsiterator2.increment();
	}
	lstest1.erase(&lsiterator1,&lsiterator2);

	lstest1.get_iterator(&lsiterator2);

	PECKER_LOG_("\nerases\n",0);
	for (int i=0;i<lstest1.get_size();++i)
	{
		if (lsiterator2.get_current_node())
		{
			PECKER_LOG_("node value = %d \n",lsiterator2.get_current_node()->value);
		}
		if (P_OK != lsiterator2.increment())
		{
			break;
		}
	}
	lstest1.clear();

	return 0;
}