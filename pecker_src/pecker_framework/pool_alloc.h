#ifndef POOL_ALLOC_H_
#define POOL_ALLOC_H_

inline int hash_fun_(int val,int imax_table_dx_size)
{
	if (0 == val && imax_table_dx_size <= 0)
	{
		return -1;
	}
	return (val % imax_table_dx_size);
}
inline int cmp_fun_(int val1, int val2)
{
	return (val1 - val2);
}



//typedef int hs_value_t;
//typedef int hs_key_t;


//struct st_pool_mem;

#define HASH_ITEM_INIT(hashname,hs_value_t,hs_key_t) \
typedef struct st_##hashname##_hash_item		\
{														\
	hs_value_t _M_value;				\
	hs_key_t		_M_key;					\
	void* p_pre_item;					\
	void* p_next_item;					\
	void* p_allocator;					\
	void** p_header;						\
}hash_item_##hashname##_;	



#define POOL_ALLOCATE_INIT(poolname,value_t,POOL_MAX_SIZE)		\
typedef struct st_pool_##poolname##_item								\
{																				\
	value_t _M_value;											\
	void* p_pre_item;											\
	void* p_next_item;											\
}pool_##poolname##_item;							     \
																				\
typedef struct st_pool_##poolname##_mem								\
{																				\
	pool_##poolname##_item _M_pool[POOL_MAX_SIZE];		\
	pool_##poolname##_item* _M_allocate;								\
	pool_##poolname##_item* _M_release;								   \
}pool_##poolname##_mem;															\
																					\
inline int pool_##poolname##_mem_init(pool_##poolname##_mem* pool)		\
{																					\
	if (0 == pool)															\
	{																				\
		return -1;															\
	}																				\
	pool->_M_allocate = 0;										\
	pool->_M_release = &(pool->_M_pool[0]);	\
	pool_##poolname##_item* ptemp_pool_item = &(pool->_M_pool[0]);			\
	ptemp_pool_item->p_pre_item = 0;												\
	for (int i=1;i<POOL_MAX_SIZE;++i)												\
	{																											\
		pool_##poolname##_item* ptemp_old_pool_item = ptemp_pool_item;		\
		ptemp_pool_item->p_next_item = &(pool->_M_pool[i]);		\
		ptemp_pool_item = &(pool->_M_pool[i]);								\
		ptemp_pool_item->p_pre_item = ptemp_old_pool_item;	\
	}																											\
	ptemp_pool_item->p_next_item = 0;											\
}																												\
																												\
inline value_t* pool_##poolname##_mem_allocate(pool_##poolname##_mem* pool)				\
{																												\
	if (0 == pool || 0 == pool->_M_release)									 \
	{																											\
		return 0;																							\
	}																											\
	pool_##poolname##_item* pold_allocate= pool->_M_allocate;						\
	pool->_M_allocate = pool->_M_release;										\
	pool->_M_release = (pool_##poolname##_item*)(pool->_M_release->p_next_item);	\
																																\
	pool->_M_allocate->p_pre_item = 0;															\
	pool->_M_allocate->p_next_item = pold_allocate;									\
																																\
	if (pold_allocate)																								\
	{																															\
		pold_allocate->p_pre_item = pool->_M_allocate;								\
	}																															\
	if (pool->_M_release)																						\
	{																															\
		pool->_M_release->p_pre_item = 0;															\
	}																															\
																																\
	return &(pool->_M_allocate->_M_value);													\
}																																\
																																\
inline int  pool_##poolname##_mem_deallocate(pool_##poolname##_mem* pool,value_t* delvalue)	\
{																																\
	if (0 == delvalue)																								\
	{																															\
		return -1;																										\
	}																															\
	pool_##poolname##_item* pdel_item = (pool_##poolname##_item*)delvalue;											\
	pool_##poolname##_item* pnext_item = (pool_##poolname##_item*)(pdel_item->p_next_item);			\
	pool_##poolname##_item* pre_item = (pool_##poolname##_item*)(pdel_item->p_pre_item);				\
	unsigned int bool_flag_1 = (0 == pnext_item && 0 == pre_item && pool->_M_allocate == pdel_item);					\
	unsigned int bool_flag_2 = ( (0 != pre_item) && (((pool_##poolname##_item*)(pre_item->p_next_item)) == pdel_item));			\
	unsigned int bool_flag_3 = ( (0 != pnext_item) && (((pool_##poolname##_item*)(pnext_item->p_pre_item)) == pdel_item));		\
																																																		\
	if (bool_flag_1)																																											\
	{																																																	\
		pool->_M_allocate = 0;																																						\
	}																																																	\
	else if (bool_flag_2 && bool_flag_3)																																	\
	{																																																	\
		pnext_item->p_pre_item = pre_item;																																\
		pre_item->p_next_item = pnext_item;																																\
	}																																																	\
	else if (bool_flag_2 && 0 == pnext_item)																															\
	{																																																	\
		pre_item->p_next_item = pnext_item;																																\
	}																																																   \
	else if (bool_flag_3 && 0 == pre_item)																																\
	{																																																	\
		pnext_item->p_pre_item = pre_item;																																\
	}																																																	\
	else																																																\
	{																																																	\
		return -1;																																												\
	}																																																	\
																																																		\
	pdel_item->p_pre_item = 0;											\
	pdel_item->p_next_item = pool->_M_release;			\
	if (pool->_M_release)														\
	{																							\
		pool->_M_release->p_pre_item = pdel_item;			\
	}																							\
	pool->_M_release = pdel_item;										\
																								\
	return 0;																				\
}																								\
																								\
inline value_t* pool_##poolname##_mem_iterator_inc(pool_##poolname##_item* pool_item_,pool_##poolname##_item** pool_item_next)								\
{																																																	\
	if (0 == pool_item_)																																								\
	{																																															    \
		return 0;																																												\
	}																																																\
	value_t* pvalue = &(pool_item_->_M_value);																												\
	if (0 != pool_item_next)																																						\
	{																																																\
		*pool_item_next = (pool_##poolname##_item*)(pool_item_->p_next_item);																					\
	}																																																\
	return pvalue;																																										\
}																																																	\
																																																	\
inline value_t* pool_##poolname##_mem_iterator_dec(pool_##poolname##_item* pool_item_,pool_##poolname##_item** pool_item_pre)								\
{																																																	\
	if (0 == pool_item_)																																								\
	{																																															    \
		return 0;																																												\
	}																																																\
	value_t* pvalue = &(pool_item_->_M_value);																												\
	if (0 != pool_item_pre)																																						\
	{																																																\
		*pool_item_pre = (pool_##poolname##_item*)(pool_item_->p_pre_item);																						\
	}																																																\
	return pvalue;																																										\
}																																																



#define HASH_TABLE_INIT(hashname,hs_value_t,hs_key_t,HASH_TABLE_SIZE,POOL_MAX_SIZE,hash_fun,cmp_fun) \
HASH_ITEM_INIT(hashname,hs_value_t,hs_key_t) \
POOL_ALLOCATE_INIT(hashname,hash_item_##hashname##_,POOL_MAX_SIZE)	\
typedef struct																																\
{																																						\
	hash_item_##hashname##_* _M_table[HASH_TABLE_SIZE];											\
	pool_##hashname##_mem _M_allocator;																			\
}hash_##hashname##_table;																										\
																																						\
inline int hash_##hashname##_table_init(hash_##hashname##_table* table)				\
{																																						\
	if (0 == table)																															\
	{																																					\
		return -1;																																\
	}																																					\
	for (int i=0;i<HASH_TABLE_SIZE;++i)																						\
	{																																					\
		table->_M_table[i] = 0;																										\
	}																																					\
	return pool_##hashname##_mem_init(&(table->_M_allocator));								   \
}																																																	\
inline hs_value_t* hash_##hashname##_table_find(hash_##hashname##_table* table,hs_key_t key)				\
{																																																	\
	if (0 == table)																																										\
	{																																																\
		return 0;																																												\
	}																																																\
	int index = hash_fun(key,HASH_TABLE_SIZE);																													\
	if (index < 0)																																											\
	{																																																\
		return 0;																																												\
	}																																																\
	hash_item_##hashname##_* ptmp = table->_M_table[index];																					\
	while (ptmp)																																											\
	{																																																\
		hs_key_t* pval = &(ptmp->_M_key);																																\
		if (pval)																																												\
		{																																															\
			if (0 == cmp_fun(key, *pval))																																		\
			{																																														\
				return &(ptmp->_M_value);																																	\
			}																																														\
		}																																															\
		ptmp = (hash_item_##hashname##_*)(ptmp->p_next_item);																					\
	}																																																\
																																																	\
	return 0;																																													\
}																																																	\
inline int hash_##hashname##_table_insert(hash_##hashname##_table* table,hs_key_t key,hs_value_t value_)		\
{																																																				\
	if (0 == table)																																													\
	{																																				\
		return -1;																															\
	}																																				\
																																					\
	int index = hash_fun(key,HASH_TABLE_SIZE);																	\
	if (index < 0)																															\
	{																																				\
		return -1;																															\
	}																																				\
																																					\
	hash_item_##hashname##_* ptmp = table->_M_table[index];									\
	while (ptmp)																															\
	{																																				\
		hs_key_t* pval = &(ptmp->_M_key);																				\
		if (pval)																																\
		{																																			\
			if (0 == cmp_fun(key, *pval))																						\
			{																																		\
				return 1;																														\
			}																																		\
		}																																			\
		ptmp = (hash_item_##hashname##_*)(ptmp->p_next_item);									\
	}																																				\
																																					\
	hash_item_##hashname##_* pnew_item = pool_##hashname##_mem_allocate(&(table->_M_allocator));			\
	if (pnew_item)																														\
	{																																				\
		pnew_item->_M_key = key;																								\
		pnew_item->_M_value = value_;																					\
		pnew_item->p_allocator = &(table->_M_allocator);												\
		pnew_item->p_header = (void**)(&(table->_M_table[index]));								\
	}																																				\
	else																																			\
   {																																				\
	   return -1;																															\
   }																																				\
	hash_item_##hashname##_* pold_item = table->_M_table[index];						   \
	table->_M_table[index] = pnew_item;																				\
	if (pold_item)																														\
	{																																				\
		pnew_item->p_pre_item = pold_item->p_pre_item;													\
		pold_item->p_pre_item = pnew_item;																			\
	}																																				\
	else																																			\
	{																																				\
		pnew_item->p_pre_item = 0;																							\
	}																																				\
	pnew_item->p_next_item = pold_item;																			\
																																					\
	return 0;																																	\
}																																					\
inline int hash_##hashname##_table_erase_node(hash_item_##hashname##_* pitem)			\
{																																					\
	if (0 == pitem)																														\
	{																																				\
		return -1;																															\
	}																																				\
	hash_item_##hashname##_* preitem = (hash_item_##hashname##_*)(pitem->p_pre_item);			\
	hash_item_##hashname##_* pnextitem = (hash_item_##hashname##_*)(pitem->p_next_item);	\
	pool_##hashname##_mem* pallocator = (pool_##hashname##_mem*)(pitem->p_allocator);		\
	if (preitem)																															\
	{																																				\
		preitem->p_next_item = pitem->p_next_item;															\
	}																																				\
	if (pnextitem)																														\
	{																																				\
		pnextitem->p_pre_item = pitem->p_pre_item;															\
	}																																				\
	if ((pitem->p_header) && (pitem == *(pitem->p_header)))											\
	{																																				\
		*(pitem->p_header) = pitem->p_next_item;																\
	}																																				\
	if (pallocator)																														\
	{																																				\
		return pool_##hashname##_mem_deallocate(pallocator,pitem);							\
	}																																				\
	return 0;																																	\
}																																					\
																																					\
inline int hash_##hashname##_table_erase_value(hs_value_t* pvalue)					\
{																																					\
	if (0 == pvalue)																														\
	{																																				\
		return -1;																															\
	}																																				\
	hash_item_##hashname##_* pdel_item = (hash_item_##hashname##_*)pvalue;																													\
	hash_item_##hashname##_* pre_item = (hash_item_##hashname##_*)(pdel_item->p_pre_item);																					\
	hash_item_##hashname##_* pnext_item = (hash_item_##hashname##_*)(pdel_item->p_next_item);																				\
	char blegalval = 0;																																																								\
																																																																	\
	unsigned int bool_flag_1 = ( (0 == pnext_item) && (0 == pre_item) && (pdel_item->p_allocator) && (*(pdel_item->p_header) == pdel_item));		\
	unsigned int bool_flag_2 = ( (0 != pre_item) && (((hash_item_##hashname##_*)(pre_item->p_next_item)) == pdel_item));										\
	unsigned int bool_flag_3 = ( (0 != pnext_item) && (((hash_item_##hashname##_*)(pnext_item->p_pre_item)) == pdel_item));									\
																																																																	\
	if (bool_flag_1)																																																										\
	{																																																																\
		*(pdel_item->p_header) = pdel_item->p_next_item;																																									\
	}																																																																\
	else if (bool_flag_2 && bool_flag_3)																																																\
	{																																																																\
		pnext_item->p_pre_item = pre_item;																																															\
		pre_item->p_next_item = pnext_item;																																															\
	}																																																																\
	else if (bool_flag_2 && 0 == pnext_item)																																														\
	{																																																																\
		pre_item->p_next_item = pnext_item;																																															\
	}																																																																\
	else if (bool_flag_3 && 0 == pre_item)																																															\
	{																																																																\
		pnext_item->p_pre_item = pre_item;																																															\
	}																																																																\
	else																																																															\
	{																																																																\
		return -1;																																																											\
	}																																																																\
	 return hash_##hashname##_table_erase_node(pdel_item);																																						\
}

#endif