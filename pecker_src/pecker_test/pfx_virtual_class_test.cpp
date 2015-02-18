/*
 * pfx_matrix_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/native/pfx_log.h"



USING_PECKER_SDK

class ctext_a
{
public:
	virtual void hehe()	 const
	{
		PECKER_LOG_INFO("hehe a (%s)", "chehe_a");
	}

};

class ctext_b : public ctext_a
{
public:
	virtual void hehe()	const
	{
		PECKER_LOG_INFO("hehe b (%s)", "chehe_b");
	}

};

class ctext_x
{
public:
	int a;
	ctext_x() :a(0)
	{
		;
	}
	virtual ctext_x* hehe()
	{
		PECKER_LOG_INFO("hehe x (%d)", a);
		return this;
	}

	virtual const ctext_a* hi()  const
	{
		static ctext_a a;
		return &a;
	}

	static int hello()	
	{
		return 111;
	}

};

class ctext_y : public ctext_x
{
public:
	ctext_y() 
	{
		a = 1;
	}
	virtual ctext_y* hehe()
	{
		PECKER_LOG_INFO("hehe y (%d)", a);
		return this;
	}

	virtual const ctext_b* hi() const
	{
		static ctext_b b;
		return &b;
	}

	static const char* hello()	
	{
		return "111";
	}
};

void virtual_class_test()
{
	ctext_y	yyy;
	ctext_x* y_ptr = &yyy;
	ctext_x* x_ptr = y_ptr->hehe();
	x_ptr->hi()->hehe();
	PECKER_LOG_INFO("x = %d", x_ptr->a);
}
