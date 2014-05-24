/*
 * pfx_share_object_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_share_object.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/data/pfx_cblock.h"

USING_PECKER_SDK

int auto_obj_test ()
{
	typedef  pecker_simple_allocator < uint_t > alloc;
	uint_t* test_buf = alloc::allocate_objects(10);
	if (test_buf)
	{
		cauto_release_buffer< alloc > auto_release(test_buf);
	}

	typedef cblock < alloc > cblock_t;
	cblock_t block;
	block.init_buffer(100);
	uindex_t _index = block.size();
	while (_index)
	{
		--_index;
		block.reference(_index) = _index;
	}

	block.force_clean();

	typedef cshare_leakable_object < cblock_t > __schare_block_t;
	__schare_block_t sb1,sb2,sb3;
	__schare_block_t::lock_object_t lock_obj;
	
	sb1.lock(lock_obj);
	cblock_t* lock_ptr =  lock_obj.lock_modify_object();
	usize__t __init_size = 100;
	lock_ptr->resize(__init_size);
	while (__init_size)
	{
		--__init_size;
		lock_ptr->reference(_index) = __init_size;
	}
	sb1.unlock(lock_obj);

	sb1.share(sb2);
	sb1.share(sb3);

	lock_obj = sb2.lock(lock_obj);
	lock_ptr = lock_obj.lock_modify_object(PFX_BOOL_TRUE);
	uint_t tmpbuf[10] = {11,22,33,44,55,66,77,88,99,00};
	lock_ptr->set_buffer (tmpbuf, sizeof (tmpbuf));
	sb2.unlock(lock_obj);

	sb2.release_object();
	sb3.release_object();
	sb1.release_object();

	PFX_ShareObject< alloc >::cshare_object_t so1,so2,so3;
	PFX_ShareObject< alloc >::cshare_object_t::lock_object_t lobj;
	so1.lock(lobj);
	PFX_ShareObject< alloc >::cshare_object_t::leakable_object_t* lobj_ptr;
	lobj_ptr = lobj.lock_modify_object();
	lobj_ptr->init();
	lobj_ptr->reference() = 20;
	so1.unlock(lobj);
	so1.share(so2);
	so1.share(so3);

	so2.lock(lobj);
	lobj_ptr = lobj.lock_modify_object(PFX_BOOL_TRUE);
	lobj_ptr->reference() = 30;
	so2.unlock(lobj);

	so1.release_object();
	so2.release_object();
	so3.release_object();

	return 0;
}
