//#include "opengles2_test/pfx_hello_lena_fbo.h"
#include <pfx_app_init.h>
#include <opengles2_test/pfx_hello_lena_fbo.h>

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

chello_lena_fbo_view_gles2 lena_fbo_v;
chellogles_activity hellow;

#define test_view lena_fbo_v

int PFX_main(pecker_sdk::native_form_t* PARAM_INOUT main_form)
{
	PECKER_LOG_INFO("PFX_main...%d",0);
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
