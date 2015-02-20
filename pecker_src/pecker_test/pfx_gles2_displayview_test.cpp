/*
 * pfx_gles2_displayview_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "opengles2_test/pfx_hello_triangle.h"
#include "opengles2_test/pfx_hello_triangle_vbo.h"
#include "opengles2_test/pfx_hello_lena.h"
#include "opengles2_test/pfx_hello_lena_fbo.h"

extern void symbiont_object();

extern "C"
{
 int hehe();
}


int hehe()
{
	   PECKER_LOG_STR("hehe");
	   return 0;
}

static int load_info ()
{
	PECKER_LOG_("load test %s","111");
	return 0;
}
static int a = load_info ();

class  chellogles_activity : public opengles2_activity_t
{
private:
	int m_iresize_count;
public:
	chellogles_activity()
	{

	}
	virtual ~chellogles_activity()
	{
		;
	}
	virtual void on_create(activity_init_state_t& PARAM_OUT init_state)
	{
		opengles2_activity_t::on_create(init_state);
		init_state.m_fixed_window = 0;
		init_state.m_strtitle.init_string("hello activity", strlen("hello activity") + 1);

		symbiont_object();
	}
	virtual void on_start()
	{
		opengles2_activity_t::on_start();
		m_iresize_count = 0;
	}
	virtual void on_finish_modify_view()
	{
		opengles2_activity_t::on_finish_modify_view();
		PECKER_LOG_("resize count = %d\n", m_iresize_count);
	}
};


chello_triangle_render_view_gles2 hello_tri;
chello_triangle_vbo_render_view_gles2 hello_tri_vbo;
chello_lena_view_gles2 lena_v;
chello_lena_fbo_view_gles2 lena_fbo_v;

//#define test_view lena_v
#define test_view lena_fbo_v
//hello_tri_vbo
extern void virtual_class_test();

#if (defined(__ANDROID__)|| defined(__APP_MAIN_SHOW__))
chellogles_activity hellow;


int PFX_main(pecker_sdk::native_form_t* PARAM_INOUT main_form)
{
	PECKER_LOG_INFO("PFX_main...%d",0);
	virtual_class_test();
	main_form->init(&hellow);
	hellow.init(&test_view);
	main_form->show_form(false);
	return 0;
}

extern "C"
{
int pecker_program(void* form)
{
	return PFX_main((pecker_sdk::native_form_t*)form);
}
}



#else
#include <iostream>
void gles2_displayview_test ()
{
	int iwait = 0;
	native_form_t		form;
	chellogles_activity hellow;
	
	form.init(&hellow);
	hellow.init(&test_view);
	//form.create();
	//form.show_dialog(false);
	form.show(false);
	std::cin >> iwait;
	form.set_visiable(false);
	std::cin >> iwait;
	form.set_visiable(true, true);
	std::cin >> iwait;
	form.set_visiable(false);
	std::cin >> iwait;
	form.set_visiable(true, false);
	std::cin >> iwait;
	form.close();
	std::cin >> iwait;
	form.dispose();
}
#endif	  //#if (defined(__ANDROID__)|| defined(__APP_MAIN_SHOW__))


