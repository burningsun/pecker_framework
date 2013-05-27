#include "native/pecker_window_context.h"
#include <GLES2/gl2.h>
USING_PECKER_SDK

class myTestForm :  public pecker_window_context
{
protected:
	HResult on_init()
	{
		_M_window_info._M_window_param._M_window_style = RESIZEABLE_WIN_BORDERSTYLE;
		return P_OK;
	}
	HResult on_render()
	{
		Ipecker_render_device* graphics_dev = get_render_device();
		Ipecker_fragment_operation* frame_op = graphics_dev->get_fragment_operation();
		
		HResult result_ = frame_op->clear_color(0.7f,0.2f,0.7f,1.0f);
		result_ = frame_op->set_clear_mask(PECKER_FP_DEPTH_BUFFER_BIT | PECKER_FP_COLOR_BUFFER_BIT);
		return P_OK;
	}
};

void show_simple_window()
{
	myTestForm simple_form;
	pecker_string strparams;
	pecker_program_apps::init_apps();
	pecker_program_apps::execute_program(&simple_form,strparams);
}