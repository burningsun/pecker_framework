/*
 * pfx_windows_display_opengles.cpp
 *
 *  Created on: 2013-10-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_windows_display_opengles.h"
#include "../../../native/pfx_log.h"
#include "../pfx_renderbuffer.h"
#include <EGL/eglext.h>

PECKER_BEGIN

CPfx_windows_display_opengles2::CPfx_windows_display_opengles2 () : m_form (null),
m_graphic_device(null),m_major_version(0),m_minor_version(0),m_EGL_window(EGL_NO_SURFACE),
m_EGL_context(EGL_NO_CONTEXT),m_EGL_display(EGL_NO_DISPLAY)
{
	;
}
CPfx_windows_display_opengles2::~CPfx_windows_display_opengles2 ()
{
	close_display_device();
}

pfx_result_t CPfx_windows_display_opengles2::create_graphic_device ()
{
	if (null == m_graphic_device)
	{
		m_graphic_device = new CPfx_render_device_opengles2();
		if (null == m_graphic_device)
		{
			PECKER_LOG_ERR ("CPfx_windows_display_opengles2::create_graphic_device",
				"m_graphic_device = new new CPfx_render_device_opengles2(); %s",
				"m_graphic_device = null");

			return PFX_STATUS_MEM_LOW;
		}
	}
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_windows_display_opengles2::release_grahic_device()
{
	if (null != m_graphic_device)
	{
		delete m_graphic_device;
		m_graphic_device = null;
	}
	return PFX_STATUS_OK;
}

PFX_INLINE_CODE pfx_result_t get_config_setting_for_egl (const PFX_WINDOWS_INFO_t& PARAM_IN windows_info,
	EGLint* PARAM_INOUT  egl_congfig_buffer,
	pfx_nsize_t max_buffer_size,
	pfx_nsize_t& PARAM_INOUT egl_config_stack_size)
{
	RETURN_INVALID_RESULT (max_buffer_size <= 0,PFX_STATUS_OVERRANGE);

	//pfx_index_t egl_config_stack_size;
	pfx_result_t status_;

	//egl_config_stack_size = 0;
	status_ = PFX_STATUS_OK;

	PFX_PIXEL_COLOR_FORMAT_t color_format; 
	PFX_PIXEL_COLOR_FORMAT_t* pcolor_format;

	FOR_ONE_LOOP_BEGIN

	pcolor_format = GET_COLOR_BUFFER_COLOR_SIZE
		((PFX_COLOR_BUFFER_TYPE_t)windows_info.m_present_params.m_buffer_format,
		&color_format);

	if (null == pcolor_format)
	{
		PECKER_LOG_ERR ("get_config_setting_for_egl",
			"pcolor_format = GET_COLOR_BUFFER_COLOR_SIZE(...); pcolor_format = %d;",
			pcolor_format);
		BREAK_LOOP (status_,PFX_STATUS_INVALID_PARAMS);
	}

	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = EGL_RED_SIZE;
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = (EGLint)(pcolor_format->m_red_size);
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = EGL_GREEN_SIZE;
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = (EGLint)(pcolor_format->m_green_size);
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = EGL_BLUE_SIZE;
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = (EGLint)(pcolor_format->m_blue_size);
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = EGL_ALPHA_SIZE;
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = (EGLint)(pcolor_format->m_alpha_size);
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = EGL_ALPHA_MASK_SIZE;
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = (EGLint)(pcolor_format->m_alpha_size);
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	pfx_usize_t depth_size = GET_DEPTH_BUFFER_FORMAT_SIZE 
		((PFX_DEPTH_BUFFER_TYPE_t)(get_bitfield_mask(windows_info.m_present_params.m_renderbuffer_mask,BYTE_3TH_MASK)));

	egl_congfig_buffer[egl_config_stack_size++] = EGL_DEPTH_SIZE;
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = (EGLint)(depth_size);
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	pfx_usize_t stencil_size = GET_STENCIL_BUFFER_FORMAT_SIZE
		((PFX_STENCIL_BUFFER_TYPE_t)(get_bitfield_mask(windows_info.m_present_params.m_renderbuffer_mask,BYTE_2ND_MASK)));

	egl_congfig_buffer[egl_config_stack_size++] = EGL_STENCIL_SIZE;
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size++] = (EGLint)(stencil_size);
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	pfx_usize_t luminance_size = get_bitfield_mask(windows_info.m_present_params.m_renderbuffer_mask,BYTE_1ST_MASK);
	if (luminance_size > 0)
	{
		egl_congfig_buffer[egl_config_stack_size++] = EGL_LUMINANCE_SIZE;
		BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
			status_,PFX_STATUS_OVERRANGE);

		egl_congfig_buffer[egl_config_stack_size++] = (EGLint)(luminance_size);
		BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
			status_,PFX_STATUS_OVERRANGE);
	}

	// multi sample mask
	//....
	BREAK_LOOP_CONDITION_SETS (egl_config_stack_size>=max_buffer_size,
		status_,PFX_STATUS_OVERRANGE);

	egl_congfig_buffer[egl_config_stack_size] =  EGL_NONE;


	FOR_ONE_LOOP_END

	
	return status_;
}

pfx_bool_t CPfx_windows_display_opengles2::is_egl_externsion_supported (EGLDisplay egl_dispaly,const char* pstr_extension)
{
	const char* pstr_extensions = null;
	const char* pstr_start;
	char* pstr_where;
	char* pstr_terminator;

	pstr_where = (char*)strchr(pstr_extension,' ');
	if (pstr_where || '\0' == *pstr_extension)
	{
		return pfx_false;
	}
	pstr_extensions = eglQueryString(egl_dispaly,EGL_EXTENSIONS);
	pstr_start = (char*)pstr_extensions;
	while(1)
	{
		pstr_where = (char*)strstr((const char*)pstr_start,pstr_extension);
		if (null == pstr_where)
		{
			break;
		}
		pstr_terminator = pstr_where + strlen(pstr_extension);
		if (pstr_where == pstr_start || ' '==*(pstr_where-1))
		{
			if (' ' == *pstr_terminator || '\0' == *pstr_terminator)
			{
				return pfx_true;
			}
		}
		pstr_start = pstr_terminator;
	}

	return pfx_false;
}

pfx_result_t CPfx_windows_display_opengles2::egl_init()
{
	pfx_windows_context_base* context_;
	context_ = m_form->get_context();
	const PFX_WINDOWS_INFO_t& windows_info = context_->get_context_info();
	pfx_result_t status_;
	status_ = PFX_STATUS_OK;

	FOR_ONE_LOOP_BEGIN
	// 从窗口中获取底层display接口，windows对应的是HDC
	m_EGL_display = eglGetDisplay((EGLNativeDisplayType)(m_form->get_native_display()));
	
	if (EGL_NO_DISPLAY == m_EGL_display)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"m_EGL_display = eglGetDisplay((EGLNativeDisplayType)(m_form->get_native_display())); %s;",
			"EGL_NO_DISPLAY == m_EGL_display,try EGL_DEFAULT_DISPLAY....");

		m_EGL_display = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	}

	// 获取display失败
	if (EGL_NO_DISPLAY == m_EGL_display)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"try EGL_DEFAULT_DISPLAY to init m_EGL_display; %s;",
			"EGL_NO_DISPLAY == m_EGL_display, return errors!");

		BREAK_LOOP(status_,PFX_STATUS_FAIL);
	}

	status_ = eglInitialize (m_EGL_display,&m_major_version,&m_minor_version);
	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"status_ = eglInitialize(...); status_ = %d;eglGetError = %d",
			status_,eglGetError());
		BREAK_LOOP(status_,PFX_STATUS_FAIL);
	}

	PECKER_LOG_INFO("CPfx_windows_display_opengles2::egl_init",
		"EGL initialized,EGL %d %d",m_major_version,m_minor_version);

	status_ = eglBindAPI(EGL_OPENGL_ES_API);
	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"status_ = eglBindAPI(EGL_OPENGL_ES_API); status_ = %d;eglGetError = %d",
			status_,eglGetError());
		BREAK_LOOP(status_,PFX_STATUS_FAIL);
	}
	FOR_ONE_LOOP_END

	// 检验异常状态并退出
	RETURN_INVALID_RESULT (status_ != PFX_STATUS_OK,status_);

	EGLConfig selection_config;
	EGLint egl_congfig_buffer [MAX_EGL_CONFIGS_BUFFER_SIZE];
	pfx_nsize_t egl_config_stack_size = 0;

	PFX_PIXEL_COLOR_FORMAT_t color_format; 
	PFX_PIXEL_COLOR_FORMAT_t* pcolor_format;

	FOR_ONE_LOOP_BEGIN

	pcolor_format = GET_COLOR_BUFFER_COLOR_SIZE
	((PFX_COLOR_BUFFER_TYPE_t)windows_info.m_present_params.m_buffer_format,
	&color_format);

	if (null == pcolor_format)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"pcolor_format = GET_COLOR_BUFFER_COLOR_SIZE(...); pcolor_format = %d;",
			pcolor_format);
		BREAK_LOOP (status_,PFX_STATUS_INVALID_PARAMS);
	}
	// 获取egl配置参数
	status_ = get_config_setting_for_egl(windows_info,egl_congfig_buffer,MAX_EGL_CONFIGS_BUFFER_SIZE,egl_config_stack_size);
	if (PFX_STATUS_OK != status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"status_ = get_config_setting_for_egl(...); status_ = %d;",
			status_);
		break;
	}
	
	EGLint total_num_configs = 0;
	// 首先获取所有可用的配置
	status_ = eglChooseConfig(m_EGL_display,egl_congfig_buffer,NULL,0,&total_num_configs);
	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"status_ = eglChooseConfig(...); status_ = %d;eglGetError = %d",
			status_,eglGetError());
		BREAK_LOOP(status_,PFX_STATUS_FAIL);
	}
	if (0 == total_num_configs)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"status_ = eglChooseConfig(...); Choose config error EGL,total number of configs =%d;eglGetError = %d",
			total_num_configs,eglGetError());
		BREAK_LOOP(status_,PFX_STATUS_FAIL);
	}
	EGLConfig* pconfigs = new EGLConfig[total_num_configs];

	// 设置EGL配置
	status_ = eglChooseConfig(m_EGL_display,egl_congfig_buffer,pconfigs,total_num_configs,
		&total_num_configs);

	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"2 status_ = eglChooseConfig(...); status_ = %d;eglGetError = %d",
			status_,eglGetError());
		BREAK_LOOP(status_,PFX_STATUS_FAIL);
	}
	if (0 == total_num_configs)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"2 status_ = eglChooseConfig(...); Choose config error EGL,total number of configs =%d;eglGetError = %d",
			total_num_configs,eglGetError());
		BREAK_LOOP(status_,PFX_STATUS_FAIL);
	}

	EGLint config_attrib_value = 0;
	status_ = PFK_STATUS_NULLITEM;
	// 选择一个最合适的配置返回
	for (pfx_index_t i=0;i<total_num_configs;++i)
	{
		// 选择方式，以配置中的颜色RGBA值作为选择标准
		if ((eglGetConfigAttrib(m_EGL_display,pconfigs[i],EGL_RED_SIZE,&config_attrib_value) && (EGLint)(pcolor_format->m_red_size) == config_attrib_value) &&
			(eglGetConfigAttrib(m_EGL_display,pconfigs[i],EGL_GREEN_SIZE,&config_attrib_value) && (EGLint)(pcolor_format->m_green_size) == config_attrib_value) &&
			(eglGetConfigAttrib(m_EGL_display,pconfigs[i],EGL_BLUE_SIZE,&config_attrib_value) && (EGLint)(pcolor_format->m_blue_size) == config_attrib_value) &&
			(eglGetConfigAttrib(m_EGL_display,pconfigs[i],EGL_ALPHA_SIZE,&config_attrib_value) && (EGLint)(pcolor_format->m_alpha_size) == config_attrib_value))
		{
			selection_config = pconfigs[i];
			status_ = PFX_STATUS_OK;
			break;
		}
	}

	if (null != pconfigs)
	{
		delete [] pconfigs;
		pconfigs = null;
	}

	if (PFX_STATUS_OK != status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"can't find a fixed config!,%s",
			"...");
		break;
	}

	if (m_EGL_context)
	{
		status_ = eglDestroyContext(m_EGL_display,m_EGL_context);
	}

	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"status_ = eglDestroyContext(...),status_ = %d,eglGetError = %d",
			status_,eglGetError());
	}
	
	egl_config_stack_size  = 0;
	if (is_egl_externsion_supported(m_EGL_display,"EGL_IMG_context_priority"))
	{
		egl_congfig_buffer [egl_config_stack_size++] = EGL_CONTEXT_PRIORITY_LEVEL_IMG;
		PFX_CONTEXT_PRIORITY_LEVEL_IMG_t ctx_priority_level_img = (PFX_CONTEXT_PRIORITY_LEVEL_IMG_t)PFX_CONTEXT_PRIORITY_LEVEL_VALUE(windows_info.m_present_params.m_renderbuffer_mask);
		switch(ctx_priority_level_img)
		{
		case PFX_CONTEXT_LOW_PREPRIORITY:
			egl_congfig_buffer [egl_config_stack_size++]  = EGL_CONTEXT_PRIORITY_LOW_IMG;
			break;
		case PFX_CONTEXT_MEDIUM_PREPRIORITY:
			egl_congfig_buffer [egl_config_stack_size++]  = EGL_CONTEXT_PRIORITY_MEDIUM_IMG;
			break;
		case PFX_CONTEXT_HIGH_PREPRIORITY:
			egl_congfig_buffer [egl_config_stack_size++]  = EGL_CONTEXT_PRIORITY_HIGH_IMG;
			break;
		default:
			egl_congfig_buffer [egl_config_stack_size++]  = EGL_CONTEXT_PRIORITY_HIGH_IMG;
			break;
		}
	}
	egl_congfig_buffer [egl_config_stack_size]   = EGL_NONE;


	m_EGL_context = eglCreateContext(m_EGL_display,selection_config,null,egl_congfig_buffer);
	if (EGL_NO_CONTEXT == m_EGL_context)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"eglCreateContext(...),m_EGL_context == EGL_NO_CONTEXT, egl error code = %d",
			eglGetError ());
		BREAK_LOOP (status_,PFX_STATUS_INVALID_PARAMS);
	}

	if (EGL_NO_SURFACE == m_EGL_window)
	{
		//EGLint egl_visual_id;
		//eglGetConfigAttrib(m_EGL_display,selection_config,EGL_NATIVE_VISUAL_ID,&egl_visual_id);
		m_EGL_window = eglCreateWindowSurface(m_EGL_display,selection_config,
			(EGLNativeWindowType)(m_form->get_native_window()),
			egl_congfig_buffer);
	}

	if (EGL_NO_SURFACE == m_EGL_window)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"m_EGL_window = eglCreateContext(...),m_EGL_context == EGL_NO_SURFACE, egl error code = %d,try using null hwnd",
			eglGetError ());
		m_EGL_window = eglCreateWindowSurface(m_EGL_display,selection_config,null,egl_congfig_buffer);
	}

	if (EGL_NO_SURFACE == m_EGL_window)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"try using null hwnd,m_EGL_window = eglCreateContext(...),m_EGL_context == EGL_NO_SURFACE, egl error code = %d,",
			eglGetError ());
		BREAK_LOOP (status_,PFX_STATUS_INVALID_PARAMS);
	}

	status_ = eglMakeCurrent(m_EGL_display,m_EGL_window,m_EGL_window,m_EGL_context);
	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_init",
			"status_ = eglMakeCurrent(...),status_ = %d,eglGetError = %d",
			status_,eglGetError());
		BREAK_LOOP (status_,PFX_STATUS_FAIL);
	}

	status_ = PFX_STATUS_OK;

	EGLint width_ = 0;
	EGLint height_ = 0;
	eglQuerySurface(m_EGL_display,m_EGL_window,EGL_WIDTH,&width_);
	eglQuerySurface(m_EGL_display,m_EGL_window,EGL_HEIGHT,&height_);

	m_graphic_device->get_defualt_framebuffer()->get_opertation ()->set_viewport (0,0,width_,height_);

	FOR_ONE_LOOP_END

	return status_;
}
pfx_result_t CPfx_windows_display_opengles2::egl_swapbuffer()
{
	RETURN_INVALID_RESULT (null == m_form || null == m_form->get_context() || null == m_graphic_device ,
		PFX_STATUS_UNINIT);
	pfx_result_t status_;
	status_ = eglSwapBuffers(m_EGL_display,m_EGL_window);
	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_swapbuffer",
			"status_ = eglSwapBuffers(...); status_ = %d,eglGetError = %d",
			status_,eglGetError());

		status_ = PFX_STATUS_ERROR_;

		if (EGL_CONTEXT_LOST == eglGetError())
		{
			// 出现EGL_CONTEXT_LOST的情况则尝试性修复
			IPfx_windows_form* windows_form = m_form;
			m_form->get_context ()->on_release_render_resource ();
			status_ = close_display_device();
			if (PFX_STATUS_OK == status_)
			{
				status_ = init_display_device(windows_form);

				if (PFX_STATUS_OK != status_)
				{
					PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_swapbuffer",
						"status_ = init_display_device(...); status_ = %d",
						status_);
				}
			}
			else
			{
				PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_swapbuffer",
					"status_ = close_display_device(...); status_ = %d",
					status_);
			}
			

		}
	}
	else
	{
		status_ = PFX_STATUS_OK;
	}
	return status_;
}
pfx_result_t CPfx_windows_display_opengles2::egl_close()
{
	if (EGL_NO_DISPLAY == m_EGL_display && EGL_NO_SURFACE == m_EGL_window)
	{
		return PFX_STATUS_OK;
	}
	pfx_result_t status_ = eglSwapBuffers(m_EGL_display,m_EGL_window);

	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_close",
			"status_ = eglSwapBuffers(...); status_ = %d,eglGetError = %d",
			status_,eglGetError());
	}

	FOR_ONE_LOOP_BEGIN
	status_ = eglMakeCurrent(m_EGL_display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
	if (!status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_close",
			"status_ = eglMakeCurrent(...); status_ = %d,eglGetError = %d",
			status_,eglGetError());
		BREAK_LOOP (status_,PFX_STATUS_FAIL);
	}
	else
	{
		status_ = PFX_STATUS_OK;
	}

	if (EGL_NO_CONTEXT != m_EGL_context)
	{
		status_ = eglDestroyContext(m_EGL_display,m_EGL_context);
		if (!status_)
		{
			PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_close",
				"status_ = eglDestroyContext(...); status_ = %d,eglGetError = %d",
				status_,eglGetError());
			BREAK_LOOP (status_,PFX_STATUS_FAIL);
		}
		else
		{
			m_EGL_context = EGL_NO_CONTEXT;
			status_ = PFX_STATUS_OK;
		}
	}

	if (EGL_NO_SURFACE != m_EGL_window)
	{
		status_ = eglDestroySurface (m_EGL_display,m_EGL_window);
		if (!status_)
		{
			PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_close",
				"status_ = eglDestroySurface(...); status_ = %d,eglGetError = %d",
				status_,eglGetError());
			BREAK_LOOP (status_,PFX_STATUS_FAIL);
		}
		else
		{
			m_EGL_window = EGL_NO_SURFACE;
			status_ = PFX_STATUS_OK;
		}
	}

	if (EGL_NO_DISPLAY != m_EGL_display)
	{
		status_ = eglTerminate(m_EGL_display);
		if (!status_)
		{
			PECKER_LOG_ERR ("CPfx_windows_display_opengles2::egl_close",
				"status_ = eglTerminate(...); status_ = %d,eglGetError = %d",
				status_,eglGetError());
			BREAK_LOOP (status_,PFX_STATUS_FAIL);
		}
		else
		{
			m_EGL_display = EGL_NO_DISPLAY;
			status_ = PFX_STATUS_OK;
		}
		
	}
	FOR_ONE_LOOP_END

	return status_;
}

pfx_result_t CPfx_windows_display_opengles2::init_display_device (IPfx_windows_form* PARAM_INOUT windows_form)
{
	RETURN_INVALID_RESULT (null == windows_form,PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT (null != m_form,PFX_STATUS_DENIED);

	pfx_result_t status_;
	pfx_windows_context_base* context_;

	m_form = windows_form;
	context_ = m_form->get_context ();
	
	status_ =  context_->init_context();
	
	if (PFX_STATUS_OK != status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::init_display_device",
			"status_ =  context_->init_context(); status_ = %d",
			status_);
		return status_;
	}

	status_ = egl_init();

	if (PFX_STATUS_OK == status_)
	{
		status_ = create_graphic_device();
	}
	else
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::init_display_device",
			"status_ = egl_init(); status_ = %d",
			status_);

		release_grahic_device();
	}
	return status_;
}

pfx_result_t CPfx_windows_display_opengles2::update_frame(const pfx_64bit_t& PARAM_IN escape_tick,
	pfx_double_t last_frame_tick_interval,
	pfx_boolean_t& PARAM_INOUT exit_render)
{
	RETURN_INVALID_BY_ACT_RESULT ((null == m_form || 
		null == m_form->get_context() || 
		null == m_graphic_device),
		exit_render = pfx_true,PFX_STATUS_ERROR_);

	pfx_windows_context_base* context_;
	pfx_result_t status_;

	context_	= m_form->get_context();	
	status_ = context_->on_render_frame(m_graphic_device,escape_tick,last_frame_tick_interval,exit_render);

	if (PFX_STATUS_OK != status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::update_frame",
			"status_ = context_->on_render_frame(...); status_ = %d",
			status_);
	}
	return status_;
}

pfx_result_t CPfx_windows_display_opengles2::swap_back_buffer ()
{
	RETURN_INVALID_RESULT ((null == m_form || 
		null == m_form->get_context() || 
		null == m_graphic_device),
		PFX_STATUS_ERROR_);
	
	pfx_result_t status_;
	pfx_windows_context_base* context_;
	context_ = m_form->get_context();
	status_ = context_->on_swap_render_frame(m_graphic_device);
	
	if (PFX_STATUS_OK != status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::swap_back_buffer",
			"status_ = context_->on_swap_render_frame(...); status_ = %d",
			status_);
	}
	status_ = egl_swapbuffer();
	
	if (PFX_STATUS_OK != status_)
	{
		PECKER_LOG_ERR ("CPfx_windows_display_opengles2::swap_back_buffer",
			"status_ = egl_swapbuffer(); status_ = %d",
			status_);
	}
	return status_;
}

pfx_result_t CPfx_windows_display_opengles2::close_display_device ()
{
	if (null != m_form || null != m_graphic_device)
	{
		pfx_result_t status_;
		m_form = null;
		release_grahic_device();
		status_ = egl_close();

	}
	
	return PFX_STATUS_OK;
}

PECKER_END


