﻿/*
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
#include "../pecker_framework/data/pfx_ref_root.h"

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
	
	sb1.lock_bits(lock_obj);
	cblock_t* lock_ptr =  lock_obj.lock_modify_object();
	usize__t __init_size = 100;
	lock_ptr->resize(__init_size);
	while (__init_size)
	{
		--__init_size;
		lock_ptr->reference(_index) = __init_size;
	}
	sb1.unlock_bits(lock_obj);

	sb1.share(sb2);
	sb1.share(sb3);

	lock_obj = sb2.lock_bits(lock_obj);
	lock_ptr = lock_obj.lock_modify_object(PFX_BOOL_TRUE);
	uint_t tmpbuf[10] = {11,22,33,44,55,66,77,88,99,00};
	lock_ptr->set_buffer (tmpbuf, sizeof (tmpbuf));
	sb2.unlock_bits(lock_obj);

	sb2.release_object();
	sb3.release_object();
	sb1.release_object();

	PFX_ShareObject< alloc >::cshare_object_t so1,so2,so3;
	PFX_ShareObject< alloc >::cshare_object_t::lock_object_t lobj;
	so1.lock_bits(lobj);
	PFX_ShareObject< alloc >::cshare_object_t::leakable_object_t* lobj_ptr;
	lobj_ptr = lobj.lock_modify_object();
	lobj_ptr->init();
	lobj_ptr->reference() = 20;
	so1.unlock_bits(lobj);
	so1.share(so2);
	so1.share(so3);

	so2.lock_bits(lobj);
	lobj_ptr = lobj.lock_modify_object(PFX_BOOL_TRUE);
	lobj_ptr->reference() = 30;
	so2.unlock_bits(lobj);

	so1.release_object();
	so2.release_object();
	so3.release_object();

	return 0;
}


PFX_Interface ITestShareInterface
{
	virtual ~ITestShareInterface()
	{ 
		; 
	}
	virtual ITestShareInterface* new_share(){ return null; }
	virtual void test() {};
	virtual void release() {};
};




class CTestNativeShareObject
{
public:
	
protected:
	int m_xxx;
public:
	CTestNativeShareObject() :m_xxx(0)
	{
		PECKER_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
	~CTestNativeShareObject()
	{ 
		PECKER_LOG_INFO("release...0x%08X", (lpointer_t)this);
	}
	void test()
	{
		PECKER_LOG_INFO("xxx=%d", m_xxx);
		++m_xxx;
	}
};






class CTestNode;
typedef pecker_simple_allocator< CTestNode > ref_node_test_alloc_t;

class CTestRef 
{
	friend class CTestNode;
	friend struct pecker_simple_allocator< CTestRef >;
	typedef pecker_simple_allocator< CTestRef >	ref_test_alloc_t;
	typedef ref_pool_memanger< ref_node_test_alloc_t, ref_test_alloc_t> ref_pool_t;
private:
	CTestNativeShareObject  m_native;
	csyn_list < ref_node_test_alloc_t > m_mem_list;
	csyn_list < ref_node_test_alloc_t > m_ref_list;
private:
	CTestRef()
	{
		PECKER_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
public:
	~CTestRef()
	{
		PECKER_LOG_INFO("release...0x%08X", (lpointer_t)this);
	}
public:
	ITestShareInterface* new_share(CTestNode* in_ptr);
	
	void test() 
	{
		m_native.test();
	};

	result_t release(CTestNode* in_ptr)
	{
		return ref_pool_t::dispose_node(m_mem_list, m_ref_list, in_ptr);
	};

};


class CTestNode :public cref_node< CTestRef, CTestNode >, 
	public  ITestShareInterface
{
	typedef cref_node< CTestRef, CTestNode > base_t;
	friend struct pecker_simple_allocator< CTestNode >;
private:
	CTestNode()
	{
		PECKER_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
public:
	virtual ~CTestNode()
	{
		PECKER_LOG_INFO("release...0x%08X", (lpointer_t)this);
		release();
	}
	CTestRef* native_ptr()
	{
		return base_t::m_ref_ptr;
	}
	static CTestNode* reinit(CTestNode* __ptr)
	{
		if (__ptr && null == __ptr->native_ptr())
		{
			new(__ptr)CTestNode();
		}
		return __ptr;
	}
	static CTestNode* new_object()
	{
		return CTestRef::ref_pool_t::create_node();
	}
	virtual ITestShareInterface* new_share()
	{
		if (base_t::m_ref_ptr)
		{
			return base_t::m_ref_ptr->new_share(this);
		}
		else
		{
			return null;
		}
	}
	virtual void test()
	{
		if (base_t::m_ref_ptr)
		{
			 base_t::m_ref_ptr->test();
		}
	};
	virtual void release()
	{
		if (base_t::m_ref_ptr)
		{
			result_t status;
			status = base_t::m_ref_ptr->release(this);
		}
	}
};

ITestShareInterface* CTestRef::new_share(CTestNode* in_ptr)
{
	CTestNode* new_node_ptr = ref_pool_t::new_share(m_mem_list, m_ref_list, in_ptr);

	return new_node_ptr;
}

class ctest_node;
class ctest_ref;

typedef pecker_simple_allocator< ctest_node > test_node_alloc;
typedef pecker_simple_allocator< ctest_ref > test_ref_alloc;

class ctest_ref
{
	CTestNativeShareObject m_native;
	DECLARE_FRIEND_CLASS(class ctest_node);
	DECLARE_FRIEND_CLASS(struct pecker_simple_allocator< ctest_ref >);
	DEFINE_NATIVE_REF_POOL(test_node_alloc, test_ref_alloc,m_ref_pool);
	DECLARE_NATIVE_CREATE_NEW_NODE(ctest_node, create_new);
	DECLARE_NATIVE_CREATE_SHARE_NODE(ctest_node, share_new);
	DECLARE_NATIVE_DISPOSE_SHARE_NODE(ctest_node, dispose_new);
	void test()
	{
		m_native.test();
	}

	ctest_ref()
	{
		PECKER_LOG_INFO("create...0x%08X", (lpointer_t)this);;
	}
	virtual ~ctest_ref()
	{
		PECKER_LOG_INFO("release...0x%08X", (lpointer_t)this);;
	}
};

//DECLARE_REF_NODE_CLASS_BEGIN(ctest_node, ctest_ref, ITestShareInterface, base_t)
DECLARE_REF_NODE_CLASS_PROTECTED_BEGIN(ctest_node, ctest_ref, ITestShareInterface, base_t, test_node_alloc, test_ref_alloc)
DECLARE_FRIEND_CLASS(class ctest_ref);
DECLARE_FRIEND_CLASS(struct pecker_simple_allocator< ctest_node >);
public:
	DECLARE_REF_CREATE_NEW_NODE(ctest_node, new_object);
	DECLARE_REF_CREATE_SHARE_NODE(ctest_node, new_share_node);
	DECLARE_REF_DISPOSE_SHARE_NODE(ctest_node, dispose_node);

	//DECLARE_BE_REF_POOL_MEMANGER_FRIEND(test_node_alloc, test_ref_alloc);

	//friend ctest_ref::ref_pool_memanger_t;
	//friend ctest_ref::ref_pool_memanger_t::list_t::list_t;
	//friend ctest_ref::ref_pool_memanger_t::list_t::iterator_t;
	//friend ctest_ref::ref_pool_memanger_t::list_t::list_op_t;

	PFX_INLINE ITestShareInterface* new_share()
	{
		return new_share_node();
	}

	virtual void test()
	{
		if (base_t::m_ref_ptr)
		{
			base_t::m_ref_ptr->test();
		}
	};

	virtual void release()
	{
		 dispose_node();
	}

private:
	ctest_node()
	{ 
		PECKER_LOG_INFO("create...0x%08X", (lpointer_t)this);;
	}
public:
	virtual ~ctest_node()
	{
		PECKER_LOG_INFO("release...0x%08X", (lpointer_t)this);
		dispose_node();
	}
DECLARE_REF_NODE_CLASS_END;

STATIC_NATIVE_CREATE_NEW_NODE(ctest_ref, ctest_node, create_new);
NATIVE_CREATE_SHARE_NODE(ctest_ref, ctest_node, share_new, m_ref_pool);
NATIVE_DISPOSE_SHARE_NODE(ctest_ref, ctest_node, dispose_new, m_ref_pool);

STATIC_REF_CREATE_NEW_NODE(ctest_ref, ctest_node, new_object, create_new);
REF_CREATE_SHARE_NODE(base_t, ctest_node, new_share_node, share_new);
REF_DISPOSE_SHARE_NODE(base_t, ctest_node, dispose_node, dispose_new);



void symbiont_object()
{
	//CTestNode* share_obj_1 = CTestNode::new_object();
	//ITestShareInterface* share_obj_2 = share_obj_1->new_share();
	//ITestShareInterface* share_obj_3 = share_obj_2->new_share();

	//share_obj_1->test();
	//share_obj_2->test();
	//share_obj_3->test();

	//share_obj_1->release();
	//share_obj_2->release();
	//share_obj_3->release();

	ctest_node* share_obj_1 = ctest_node::new_object();
	ITestShareInterface* share_obj_2 = share_obj_1->new_share();
	ITestShareInterface* share_obj_3 = share_obj_2->new_share();

	share_obj_1->test();
	share_obj_2->test();
	share_obj_3->test();

	share_obj_1->release();
	share_obj_2->release();
	share_obj_3->release();
};




