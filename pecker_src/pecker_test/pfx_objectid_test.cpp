﻿/*
 * pfx_list_test.cpp
 *
 *  Created on: 2014-3-28
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_clist.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"

USING_PECKER_SDK

template < class Aaa >
class testA
{
public:
	static const object_id_t& final_type()
	{
		typedef testA< Aaa > this_type_t;
		typedef testA< Aaa > base_type_t;
		static object_id_t obj_id;
		return cobject_id< this_type_t, base_type_t >::to_object_id (obj_id);
	}
	PFX_INLINE virtual const object_id_t& type_id() const
	{
		return final_type ();
	}
};

template < class Aaa, const usize__t x = 0 >
class testB: testA< Aaa >
{
public:
	static const object_id_t& final_type()
	{
		typedef testA< Aaa > base_type_t;
		typedef testB< Aaa, x > this_type_t;
		static object_id_t obj_id;
		return cobject_id< this_type_t, base_type_t >::to_object_id (obj_id);
	}
	PFX_INLINE virtual const object_id_t& type_id() const
	{
		return final_type ();
	}
};

template < class Aaa, const usize__t x = 0 >
class testC: testA< Aaa >
{

public:
	static const object_id_t& final_type()
	{
		typedef testA< Aaa > base_type_t;
		typedef testC< Aaa, x > this_type_t;
		static object_id_t obj_id;
		return cobject_id< this_type_t, base_type_t >::to_object_id (obj_id);
	}
	PFX_INLINE virtual const object_id_t& type_id() const
	{
		return final_type ();
	}
};

template < class Aaa, const usize__t x = 0 >
class testD: testB< Aaa, x >
{
public:
	static const object_id_t& final_type()
	{
		typedef testB< Aaa, x > base_type_t;
		typedef testD< Aaa, x > this_type_t;
		static object_id_t obj_id;
		return cobject_id< this_type_t, base_type_t >::to_object_id (obj_id);
	}
	PFX_INLINE virtual const object_id_t& type_id() const
	{
		return final_type ();
	}
};

void test_object_id()
{
	testA< int > a[3];
	testB< int > b[3];
	testC< int > c[3];
	testD< int > d[3];

	testB< int, 1 > b1[3];
	testC< int, 1 > c1[3];
	testD< int, 1 > d1[3];

	for (uindex_t i = 0; i < 3; ++i)
	{
		boolean_t check_res;
		uint_t aid;
		uint_t bid;
		uint_t cid;
		uint_t did;
		PECKER_LOG_("\nround %d\n", i);

		PECKER_LOG_("\ntestA < int >\n", 0);
		aid = a[i].type_id ().final_type_id ();
		PECKER_LOG_("typeid = %d\n", aid);

		PECKER_LOG_("\ntestB < int >\n", 0);
		bid = b[i].type_id ().final_type_id ();
		PECKER_LOG_("typeid = %d\n", bid);
		check_res = __type_id::__IS_type (b[i].type_id (), a[i].type_id ());
		PECKER_LOG_("is testA < int >? %d\n", check_res);

		PECKER_LOG_("\ntestC < int >\n", 0);
		cid = c[i].type_id ().final_type_id ();
		PECKER_LOG_("typeid = %d", cid);
		check_res = __type_id::__IS_type (c[i].type_id (), a[i].type_id ());
		PECKER_LOG_("is testA < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (c[i].type_id (), b[i].type_id ());
		PECKER_LOG_("is testB < int >? %d\n", check_res);

		PECKER_LOG_("\ntestD < int >\n",0);
		did = d[i].type_id ().final_type_id ();
		PECKER_LOG_("typeid = %d", did);
		check_res = __type_id::__IS_type (d[i].type_id (), a[i].type_id ());
		PECKER_LOG_("is testA < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (d[i].type_id (), b[i].type_id ());
		PECKER_LOG_("is testB < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (d[i].type_id (), c[i].type_id ());
		PECKER_LOG_("is testC < int >? %d\n", check_res);

		PECKER_LOG_("\ntestB < int >\n",0);
		bid = b1[i].type_id ().final_type_id ();
		PECKER_LOG_("typeid = %d\n", bid);
		check_res = __type_id::__IS_type (b1[i].type_id (), a[i].type_id ());
		PECKER_LOG_("is testA < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (b1[i].type_id (), b[i].type_id ());
		PECKER_LOG_("is testB < int >? %d\n", check_res);

		PECKER_LOG_("\ntestC < int >\n",0);
		cid = c[i].type_id ().final_type_id ();
		PECKER_LOG_("typeid = %d", cid);
		check_res = __type_id::__IS_type (c1[i].type_id (), a[i].type_id ());
		PECKER_LOG_("is testA < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (c1[i].type_id (), b[i].type_id ());
		PECKER_LOG_("is testB < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (c1[i].type_id (), c[i].type_id ());
		PECKER_LOG_("is testC < int >? %d\n", check_res);

		PECKER_LOG_("\ntestD < int >\n",0);
		did = d[i].type_id ().final_type_id ();
		PECKER_LOG_("typeid = %d", did);
		check_res = __type_id::__IS_type (d1[i].type_id (), a[i].type_id ());
		PECKER_LOG_("is testA < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (d1[i].type_id (), b[i].type_id ());
		PECKER_LOG_("is testB < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (d1[i].type_id (), c[i].type_id ());
		PECKER_LOG_("is testC < int >? %d\n", check_res);
		check_res = __type_id::__IS_type (d1[i].type_id (), d[i].type_id ());
		PECKER_LOG_("is testD < int >? %d\n", check_res);
	}
	return;
}
