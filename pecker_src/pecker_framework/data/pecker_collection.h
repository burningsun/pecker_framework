/*  Created on: 2013-9-21
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PECKER_COLLECTION_H_
#define PECKER_COLLECTION_H_

#include "../pfx_defines.h"

PFX_C_EXTERN_BEGIN


typedef struct st_collection collection_t;

typedef struct PFX_DATA_API  st_collection_instance
{
	void*	m_last_collect;
	void*	m_container;
}collection_instance_t;

typedef pfx_result_t (*push_func)(collection_t* pcollection,void* pitem) ;
typedef pfx_result_t (*pop_func)(collection_t* pcollection) ;
typedef pfx_result_t (*is_full_func)(collection_t* pcollection) ;


typedef struct PFX_DATA_API st_collection_method
{
	push_func		m_push;
	pop_func		m_pop;
	is_full_func		m_isfull;
}collection_method_t;

struct PFX_DATA_API st_collection
{
	collection_method_t		m_method;
	collection_instance_t	m_instance;
};

PFX_C_EXTERN_END


#endif //PECKER_COLLECTION_H_