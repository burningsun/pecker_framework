﻿/*
 * pfx_display_context_gles.cpp
 *
 *  Created on: 2014-7-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_display_context_gles.h"

PECKER_BEGIN
cdisplay_context_gles::cdisplay_context_gles() :m_last_status(PFX_STATUS_OK),
m_on_render_view_ptr(null), m_bshow_window(false), m_egl_context_ID(0)
{
	m_thread_proxy.m_object_ptr		= this;
	m_thread_proxy.m_proxy_status	= &m_proxy_status;
	m_thread_proxy.m_callback		= &cdisplay_context_gles::render;
}

cdisplay_context_gles::~cdisplay_context_gles()
{
	close_view();
}

result_t cdisplay_context_gles::pfx_config_to_egl_config(EGLint egl_context_ID,
	const window_contex_t& PARAM_INOUT __context,
	configs_stack_t& PARAM_OUT config_list)
{
	enum_int_t config_cmd;
	enum_int_t config_data;
	config_list.clean();

	// EGL context ID 存在的时候直接选取即可
	if (egl_context_ID > 0)
	{
		config_cmd = EGL_CONFIG_ID;
		config_data = egl_context_ID;
		config_list.push_back(config_cmd);
		config_list.push_back(config_data);

		config_cmd = EGL_NONE;
		config_list.push_back(config_cmd);

		return PFX_STATUS_OK;
	}

	//if (0 ==config._M_color_format)
	//{
	config_cmd	= EGL_RED_SIZE;
	config_data = __context.m_red_size;
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);

	config_cmd = EGL_GREEN_SIZE;
	config_data = __context.m_green_size;
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);

	config_cmd = EGL_BLUE_SIZE;
	config_data = __context.m_blue_size;
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);

	config_cmd = EGL_ALPHA_SIZE;
	config_data = __context.m_alpha_size;
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);


	config_cmd = EGL_DEPTH_SIZE;
	config_data = __context.m_depth_size;
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);

	config_cmd = EGL_STENCIL_SIZE;
	config_data = __context.m_stencil_size;
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);

	config_cmd = EGL_ALPHA_MASK_SIZE;
	config_data = __context.m_alpha_mask_size;
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);

	config_cmd = EGL_COLOR_BUFFER_TYPE;
	config_data = PFX_RSYSCBT_TO_EGL_RSYSCBT((PFX_RSYS_PARAM_COLOR_BUFFER_TYPE_t)
		__context.m_color_buffer_type);
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);

	if (EGL_LUMINANCE_BUFFER == config_data)
	{
		config_cmd = EGL_LUMINANCE_SIZE;
		config_data = __context.m_luminance_size;
		config_list.push_back(config_cmd);
		config_list.push_back(config_data);
	}

	config_cmd = EGL_SURFACE_TYPE;
	config_list.push_back(config_cmd);
	config_data = EGL_WINDOW_BIT;

	if (__context.m_pbuffer_bit)
	{
		config_data |= EGL_PBUFFER_BIT;
	}

	if (__context.m_pixmal_bit)
	{
		config_data |= EGL_PIXMAP_BIT;
	}
	config_list.push_back(config_data);


	config_cmd = EGL_RENDERABLE_TYPE;
	config_data = EGL_OPENGL_ES2_BIT;
	config_list.push_back(config_cmd);
	config_list.push_back(config_data);

	if (__context.m_fsaamode_bit)
	{
		config_cmd = EGL_SAMPLE_BUFFERS;
		config_data = __context.m_multisample_count;
		config_list.push_back(config_cmd);
		config_list.push_back(config_data);
		if (config_data > 0)
		{
			config_cmd = EGL_SAMPLES;
			config_data = __context.m_sample_per_pixel;
			config_list.push_back(config_cmd);
			config_list.push_back(config_data);
		}
	}

	config_cmd = EGL_NONE;
	config_list.push_back(config_cmd);

	return PFX_STATUS_OK;
}

result_t cdisplay_context_gles::select_config(EGLint PARAM_INOUT &egl_context_ID,
	EGLDisplay hdc,
	const window_contex_t& PARAM_INOUT __contet,
	EGLConfig& PARAM_OUT selection_config,
	configs_stack_t& PARAM_OUT config_list,
	EGLconfig_list_t& PARAM_OUT __egl_configs)
{
	result_t status;

	FOR_ONE_LOOP_BEGIN
	// 转换成egl使用的config
	status = pfx_config_to_egl_config(egl_context_ID, __contet, config_list);
	BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);
	BREAK_LOOP_CONDITION_SETS(!config_list.get_block_ptr(), status, PFX_STATUS_MEM_LOW);

	EGLint total_num_configs = 0;
	const EGLint* config_list_ptr = (const EGLint*)(config_list.get_block_ptr()->begin());
	// 获取egl config的总数
	if (!eglChooseConfig(hdc, config_list_ptr, NULL, 0, &total_num_configs))
	{
		PECKER_LOG_ERR("cdisplay_context_gles::select_config", 
			"eglChooseConfig(for get total config number), EGL ERROR 0x%x", 
			::eglGetError());
		status = PFX_STATUS_FAIL;
		break;
	}

	if (0 == total_num_configs)
	{
		PECKER_LOG_ERR("cdisplay_context_gles::select_config", 
			"Choose config error EGL,total number of configs = %d", 
			total_num_configs);
		status = PFX_STATUS_FAIL;
		break;
	}

	status = __egl_configs.resize(total_num_configs);
	BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);
	EGLConfig* configs_ptr = (EGLConfig*)__egl_configs.get_block_ptr()->begin();
	EGLint num_configs;

	// 设置EGL的配置，配置可能有多个
	if (!eglChooseConfig(hdc, config_list_ptr, configs_ptr, total_num_configs, &num_configs))
	{
		PECKER_LOG_ERR("cdisplay_context_gles::select_config", 
			"eglChooseConfig error EGL, EGL ERROR 0x % x", eglGetError());
		status = PFX_STATUS_FAIL;
		break;
	}

	EGLint config_attrib_value = 0;
	status = PFX_STATUS_FAIL;
	// 选择跟我们设置参数最近的一个egl配置返回
	for (EGLint i = 0; i < num_configs; ++i)
	{
		// 选择方式，以配置中的颜色RGBA值作为选择标准
		if ((eglGetConfigAttrib(hdc, configs_ptr[i], EGL_RED_SIZE, &config_attrib_value) && 
			__contet.m_red_size == config_attrib_value) &&
			(eglGetConfigAttrib(hdc, configs_ptr[i], EGL_GREEN_SIZE, &config_attrib_value) && 
			__contet.m_green_size == config_attrib_value) &&
			(eglGetConfigAttrib(hdc, configs_ptr[i], EGL_BLUE_SIZE, &config_attrib_value) && 
			__contet.m_blue_size == config_attrib_value) &&
			(eglGetConfigAttrib(hdc, configs_ptr[i], EGL_ALPHA_SIZE, &config_attrib_value) && 
			__contet.m_alpha_size == config_attrib_value))
		{
			selection_config = configs_ptr[i];
			eglGetConfigAttrib(hdc, selection_config, EGL_CONFIG_ID, &egl_context_ID);
			status = PFX_STATUS_OK;
			break;
		}
	}


	 FOR_ONE_LOOP_END
	return status;
}

result_t cdisplay_context_gles::init_egl_context(
	window_contex_t& PARAM_INOUT __context,
	EGL_device_t& PARAM_INOUT __egl_device,
	EGLint& PARAM_OUT contextID,
	configs_stack_t& PARAM_OUT config_list,
	cOn_render_view_t* on_view_ptr)
{
	//configs_stack_t config_list;
	EGLconfig_list_t egl_configs;
	result_t status;
	char_t str_log_buffer[256];
	char_t* str_log_ptr = str_log_buffer;
	usize__t log_len = 0;
	usize__t try_count = 0;
	// 尝试配置
	do 
	{
		EGLint egl_config_id = 0;
		status = select_config(egl_config_id,
			__egl_device.m_EGLDisplay,
			__context,
			__egl_device.m_EGLConfig,
			config_list,
			egl_configs);

		// 一旦配置失败就退出
		if (PFX_STATUS_OK != status)
		{
			log_len = sprintf_s(str_log_buffer,
				sizeof(str_log_buffer),
				"select_config error = %d try_count = %d", 
				status,
				try_count);
			if (on_view_ptr)
			{
				on_view_ptr->on_message_box
					(status, str_log_ptr, log_len);
			}
			break;
		}

		// 已经存在一个context，则删除
		if (__egl_device.m_EGLContext)
		{
			::eglDestroyContext(__egl_device.m_EGLDisplay, 
				__egl_device.m_EGLContext);
		}

		config_list.clean();
		enum_int_t attrible_cmd;
		enum_int_t attrible_data;

		// 获取EGL_IMG_context_priority的扩展配置属性
		if (cnative_render_state_gles2::is_egl_externsion_supported
			(__egl_device.m_EGLDisplay, "EGL_IMG_context_priority"))
		{
			attrible_cmd	= EGL_CONTEXT_PRIORITY_LEVEL_IMG;
			attrible_data = PFX_CPLV_TO_EGL_CPLV
				((PFX_CONTEX_PREPRIORITY_t)__context.m_context_priority);
			config_list.push_back(attrible_cmd);
			config_list.push_back(attrible_data);
		}
		attrible_cmd = EGL_NONE;
		config_list.push_back(attrible_cmd);
		if (config_list.size() <= 0)
		{
			status = PFX_STATUS_MEM_LOW;
			break;
		}
		const EGLint* attrib_list_ptr = (const EGLint*)
			config_list.get_block_ptr()->begin();

		// 创建EGLContext
		status = PFX_STATUS_FAIL;
		__egl_device.m_EGLContext = ::eglCreateContext
			(__egl_device.m_EGLDisplay, __egl_device.m_EGLConfig, null, attrib_list_ptr);
		
		if (EGL_NO_CONTEXT != __egl_device.m_EGLContext)
		{
			// 创建EGLContext成功就退出
			contextID = egl_config_id;
			status = PFX_STATUS_OK;
			break;
		}
		else
		{
			if (egl_config_id > 0)
			{
				log_len = sprintf_s(str_log_buffer,
					sizeof(str_log_buffer),
					"eglCreateContext, unable to create a context by config id, ERROR = 0x%x try = %d",
					eglGetError(),
					try_count);

				if (on_view_ptr)
				{
					on_view_ptr->on_message_box
						(status, str_log_ptr, log_len);
				}
				break;
			}
			else if (__context.m_pbuffer_bit)
			{
				// 有些平台不支持PBUFFER，尝试去掉PBUFFER标识
				__context.m_pbuffer_bit = 0;
				++try_count;
				continue;
			}
			else if (__context.m_stencil_size)
			{
			   // 有些平台不支持模板缓冲，尝试去掉模板缓冲标识
				__context.m_stencil_size = 0;
				++try_count;
				continue;
			}
			else if (__context.m_fsaamode_bit && __context.m_multisample_count > 1)
			{
				// 有些平台对支持的最大sample数量不同，尝试减少采样数
				--__context.m_multisample_count;
				++try_count;
				continue;
			}
			else if (__context.m_fsaamode_bit && __context.m_sample_per_pixel)
			{
				// 配对采用属性
				if (__context.m_sample_per_pixel > 4)
				{
					__context.m_sample_per_pixel = 4;
				}
				else if (__context.m_sample_per_pixel > 2)
				{
					__context.m_sample_per_pixel = 2;
				}
				else
				{
					__context.m_sample_per_pixel	= 0;
					__context.m_multisample_count	= 0;
					__context.m_fsaamode_bit		= 0;
				}
				++try_count;
				continue;
			}
			else
			{
				//有的方法都试了，没招了
				log_len = sprintf_s(str_log_buffer,
					sizeof(str_log_buffer),
					"eglCreateContext ERROR = 0x%x try_count = %d",
					::eglGetError(),
					try_count);
			
				if (on_view_ptr)
				{
					on_view_ptr->on_message_box
						(status, str_log_ptr, log_len);
				}
				break;
			}
		}
		
	} 
	while (EGL_NO_CONTEXT == __egl_device.m_EGLContext);
	return status;
}

result_t cdisplay_context_gles::create_egl_device(window_contex_t& PARAM_INOUT __context,
	EGL_device_t& PARAM_OUT __egl_device, 
	EGLint& PARAM_OUT __contextID,
	cOn_render_view_t* on_view_ptr)
{
	result_t status;
	char_t*		msg_info_ptr = null;
	usize__t 	msg_info_len = 0;
	char_t		msg_temp_buff[256];
	configs_stack_t config_list;
	// 从窗口中获取底层display接口，windows对应的是HDC
	__egl_device.m_EGLDisplay = ::eglGetDisplay((EGLNativeDisplayType)(__context.m_hdc));
	if (EGL_NO_DISPLAY == __egl_device.m_EGLDisplay)
	{
		__egl_device.m_EGLDisplay = ::eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	}
	// 获取display失败
	if (EGL_NO_DISPLAY == __egl_device.m_EGLDisplay)
	{
		status = PFX_STATUS_FAIL;
		msg_info_ptr = "::eglGetDisplay fail! (EGL_NO_DISPLAY == _M_EGLDisplay)";
		msg_info_len = strlen(msg_info_ptr);
		if (on_view_ptr)
		{
			on_view_ptr->on_message_box(status, msg_info_ptr, msg_info_len);
		}
		return status;
	}
	// 初始化EGL
	if (!::eglInitialize(__egl_device.m_EGLDisplay, 
		&__egl_device.m_MajorVersion, &__egl_device.m_MinorVersion))
	{
		status = PFX_STATUS_FAIL;
		msg_info_len = sprintf_s(msg_temp_buff, sizeof(msg_temp_buff),
			"Unable to initialise EGL,EGL ERROR 0x%x", ::eglGetError());
		if (on_view_ptr)
		{
			msg_info_ptr = msg_temp_buff;
			on_view_ptr->on_message_box(status, msg_info_ptr, msg_info_len);
		}
		return status;
	}
	PECKER_LOG_INFO("cdisplay_context_gles::create_egl_device", 
		"EGL initialized,EGL %d %d", 
		__egl_device.m_MajorVersion, 
		__egl_device.m_MinorVersion);
	// 绑定底层渲染API
	if (!::eglBindAPI(EGL_OPENGL_ES_API))
	{
		status = PFX_STATUS_FAIL;
		msg_info_len = sprintf_s(msg_temp_buff, sizeof(msg_temp_buff),
			"Unable to bind API EGL,EGL ERROR 0x%x", ::eglGetError());
		if (on_view_ptr)
		{
			msg_info_ptr = msg_temp_buff;
			on_view_ptr->on_message_box(status, msg_info_ptr, msg_info_len);
		}
		return status;
	}

	// 创建EGLContext
	status = init_egl_context(__context, __egl_device, __contextID, config_list, on_view_ptr);
	if (PFX_STATUS_OK != status)
	{
		return status;
	}

	// 创建egl窗口
	__egl_device.m_EGLWindow = EGL_NO_SURFACE;
	const EGLint* attrib_list_ptr = null;
	if (config_list.get_block_ptr())
	{
		attrib_list_ptr = (const EGLint*)config_list.get_block_ptr()->begin();
	}

	// 如果pixmap标志被设置，使用pixmaps的方式创建surface
	if (__context.m_hpixelmap && __context.m_pixmal_bit)
	{
		PECKER_LOG_INFO("cdisplay_context_gles::create_egl_device", 
			"open device EGL, using pixmaps,about to create egl surface,%s", 
			"... ...");
		__egl_device.m_EGLWindow = 
			::eglCreatePixmapSurface(__egl_device.m_EGLDisplay, 
			__egl_device.m_EGLConfig, 
			(EGLNativePixmapType)(__context.m_hpixelmap),
			attrib_list_ptr);
	}
	// 使用指定窗口创建surface
	if (EGL_NO_SURFACE == __egl_device.m_EGLWindow)
	{
		//EGLint egl_visual_id;
		//::eglGetConfigAttrib(__egl_device.m_EGLDisplay, 
		//	__egl_device.m_EGLConfig, 
		//	EGL_NATIVE_VISUAL_ID, 
		//	&egl_visual_id);

		PECKER_LOG_INFO("cdisplay_context_gles::create_egl_device", 
			"open device EGL,using native window handle,about to create egl surface,%s",
			"... ...");
		__egl_device.m_EGLWindow = ::eglCreateWindowSurface
			(__egl_device.m_EGLDisplay, 
			__egl_device.m_EGLConfig,
			(EGLNativeWindowType)(__context.m_hwnd),
			attrib_list_ptr);
	}
	//使用null创建surface
	if (EGL_NO_SURFACE == __egl_device.m_EGLWindow)
	{
		PECKER_LOG_INFO("cdisplay_context_gles::create_egl_device", 
			"open device EGL,using null window handle value,about to create egl surface,%s", 
			"... ...");
		__egl_device.m_EGLWindow = ::eglCreateWindowSurface
			(__egl_device.m_EGLDisplay,
			__egl_device.m_EGLConfig,
			null,
			attrib_list_ptr);
	}
	// 多次尝试都创建补成功，放弃继续尝试，退出
	if (EGL_NO_SURFACE == __egl_device.m_EGLWindow)
	{
		PECKER_LOG_ERR("cdisplay_context_gles::create_egl_device", 
			"create window surface EGL,unable to create surface,%s", 
			"... ...");
		msg_info_ptr = "create window surface EGL,unable to create surface";
		msg_info_len = strlen(msg_info_ptr);
		status = PFX_STATUS_FAIL;
		if (on_view_ptr)
		{
			on_view_ptr->on_message_box(status, msg_info_ptr, msg_info_len);
		}
		return status;
	}

	if (!eglMakeCurrent(__egl_device.m_EGLDisplay, 
		__egl_device.m_EGLWindow, 
		__egl_device.m_EGLWindow, 
		__egl_device.m_EGLContext))
	{
		PECKER_LOG_ERR("cdisplay_context_gles::create_egl_device", 
			"make current EGL,unable to make context current ERROR = 0x%x", 
			::eglGetError());
		msg_info_len = sprintf_s(msg_temp_buff, sizeof(msg_temp_buff),
			"make current EGL,unable to make context current ERROR = 0x%x",
			::eglGetError());
		msg_info_ptr = msg_temp_buff;
		status = PFX_STATUS_FAIL;
		if (on_view_ptr)
		{
			on_view_ptr->on_message_box(status, msg_info_ptr, msg_info_len);
		}
		return status;
	}


	EGLint width = 0;
	EGLint height = 0;
	eglQuerySurface(__egl_device.m_EGLDisplay, 
		__egl_device.m_EGLWindow, 
		EGL_WIDTH, 
		&width);

	eglQuerySurface(__egl_device.m_EGLDisplay,
		__egl_device.m_EGLWindow, 
		EGL_HEIGHT, 
		&height);

	__context.m_viewport.m_x		= 0;
	__context.m_viewport.m_y		= 0;
	__context.m_viewport.m_width	= width;
	__context.m_viewport.m_height	= height;

	return status;
}

result_t cdisplay_context_gles::destroy_egl_device(
	EGL_device_t& PARAM_OUT __egl_device,
	EGLint& PARAM_INOUT __contextID,
	cOn_render_view_t* on_view_ptr)
{
	if (EGL_NO_DISPLAY == __egl_device.m_EGLDisplay || 
		EGL_NO_SURFACE == __egl_device.m_EGLWindow)
	{
		__contextID = 0;
		return PFX_STATUS_OK;
	}
	result_t	status;
	EGLBoolean	egl_result;

	status = PFX_STATUS_OK;

	egl_result = ::eglMakeCurrent(__egl_device.m_EGLDisplay, 
		EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

	PECKER_LOG_INFO("cdisplay_context_gles::destroy_egl_device", 
		"eglMakeCurrent before close render device,ERROR = 0x%x(0x3000 success)", 
		::eglGetError());

	if (EGL_NO_CONTEXT != __egl_device.m_EGLContext)
	{
		egl_result = ::eglDestroyContext(__egl_device.m_EGLDisplay, __egl_device.m_EGLContext);
		if (egl_result)
		{
			__egl_device.m_EGLContext = EGL_NO_CONTEXT;
			PECKER_LOG_INFO("cdisplay_context_gles::destroy_egl_device", 
				"close render device,eglDestroyContext ok! %s", 
				"... ...");
		}
		else
		{
			PECKER_LOG_ERR("cdisplay_context_gles::destroy_egl_device", 
				"close render device,eglDestroyContext fail! ERROR = 0x%x", 
				::eglGetError());
			status = PFX_STATUS_FAIL;
		}
	}
	if (EGL_NO_SURFACE != __egl_device.m_EGLWindow)
	{
		egl_result = eglDestroySurface(__egl_device.m_EGLDisplay, __egl_device.m_EGLWindow);
		if (egl_result)
		{
			__egl_device.m_EGLWindow = EGL_NO_SURFACE;
			PECKER_LOG_INFO("cdisplay_context_gles::destroy_egl_device", 
				"close render device,eglDestroySurface ok! %s", 
				"... ...");
		}
		else
		{
			PECKER_LOG_ERR("cdisplay_context_gles::destroy_egl_device", 
				"close render device,eglDestroySurface fail! ERROR = 0x%x", 
				::eglGetError());
			status = PFX_STATUS_FAIL;
		}
	}

	egl_result = ::eglTerminate(__egl_device.m_EGLDisplay);
	if (egl_result)
	{
		__egl_device.m_EGLDisplay = EGL_NO_DISPLAY;
		PECKER_LOG_INFO("cdisplay_context_gles::destroy_egl_device", 
			"close render device,eglTerminate ok! %s", 
			"... ...");
	}
	else
	{
		PECKER_LOG_ERR("cdisplay_context_gles::destroy_egl_device", 
			"close render device,eglTerminate fail! ERROR = 0x%x", 
			::eglGetError());
		status = PFX_STATUS_FAIL;
	}
	if (PFX_STATUS_OK != status && on_view_ptr)
	{
		on_view_ptr->on_message_box(status,
			"cdisplay_context_gles::destroy_egl_device",
			strlen("cdisplay_context_gles::destroy_egl_device"));
	}

	__contextID = 0;
	return status;
}

void cdisplay_context_gles::on_msg(
	const EGL_device_t& PARAM_IN device,
	cnative_render_state_gles2& PARAM_INOUT __state,
	u64_t	__escape_time,
	flag_t& PARAM_OUT msg_type,
	usize__t& PARAM_OUT param_size,
	void*& PARAM_OUT param_data_ptr)
{
	return ;
}
long_t cdisplay_context_gles::render(proxy_status_t* PARAM_INOUT status_ptr)
{
	result_t status = PFX_STATUS_OK;
	cnative_render_state_gles2& render_state = 
		cnative_render_state_gles2::singletone();
	pecker_tick ticker;
	ticker.init();
	ticker.start();
	
	while (m_bshow_window)
	{
		m_on_render_view_ptr->on_exit_complate(false);
		if (m_on_render_view_ptr->is_on_hideview())
		{
			SleepMS(1000);
			continue;
		}
		m_on_render_view_ptr->on_hide_complate(false);
		back_buffer_t	__backbuffer;
		window_contex_t __context;
		u64_t			esacape_tick;
		flag_t			msg_flag = 0;
		void*			msg_params_ptr = null;
		usize__t		msg_param_buffer_size = 0;
		display_device_t* display_device_ptr = (display_device_t*)&m_egl_device;

		// 初始化窗口的context
		m_on_render_view_ptr->on_init(__context);
		if (__context.m_back_buffer_ptr)
		{
			__backbuffer = *__context.m_back_buffer_ptr;
			__context.m_back_buffer_ptr = &__backbuffer;
		}
		else
		{
			__context.m_back_buffer_ptr = &__backbuffer;
			__backbuffer.m_width = __context.m_viewport.m_width;
			__backbuffer.m_height = __context.m_viewport.m_height;
		}
		
		// 创建渲染设备
		status = create_egl_device(__context, m_egl_device,
			m_egl_context_ID, m_on_render_view_ptr);

		if (PFX_STATUS_OK != status)
		{
			break;
		}

		// 加载渲染数据
		esacape_tick = ticker.get_microsecond();
		m_on_render_view_ptr->on_load(*display_device_ptr,
			render_state,
			esacape_tick,
			msg_flag,
			msg_param_buffer_size,
			msg_params_ptr);

		// 处理窗口回传的消息参数
		on_msg(m_egl_device,
			render_state,
			esacape_tick,
			msg_flag,
			msg_param_buffer_size,
			msg_params_ptr);

		while (m_bshow_window)
		{
			// 窗口不可见的时候销毁渲染设备，
			// 某些系统会在隐藏窗口的时候，自动销毁EGL对象和OPENGL 
			// ES相关的对象，所以在此显示的时候需要重建
			if (m_on_render_view_ptr->is_on_hideview())
			{
				break;
			}

			// 渲染回调
			esacape_tick = ticker.get_microsecond();
			m_on_render_view_ptr->on_view(*display_device_ptr,
				render_state,
				esacape_tick,
				msg_flag,
				msg_param_buffer_size,
				msg_params_ptr);

			// 处理窗口回传的消息参数
			on_msg(m_egl_device,
				render_state,
				esacape_tick,
				msg_flag,
				msg_param_buffer_size,
				msg_params_ptr);

			// 将渲染数据发送到显卡，交换窗口帧缓存
			status = render_complete(m_egl_device,
				!((bool)(__context.m_pixmal_bit)));

			// 渲染结果回调，出错的时候给窗口通知
			m_on_render_view_ptr->on_render_complete(*display_device_ptr,
				render_state, status);

			// 渲染出错时，销毁设备重新创建
			if (status)
			{
				break;
			}

			// 窗口变化的时候，对应的窗口帧缓存会变，所以这时候需要
			// 销毁渲染设备，重新创建
			if (m_on_render_view_ptr->is_on_resize())
			{
				break;
			}
			// 通过窗口状态退出渲染线程
			if (m_on_render_view_ptr->is_on_exit())
			{
				m_bshow_window = false;
				break;
			}

		}
		//销毁渲染设备
		status = destroy_egl_device(m_egl_device, m_egl_context_ID, m_on_render_view_ptr);
		//
		m_on_render_view_ptr->on_hide_complate(true);
		if (status)
		{
			break;
		}
	}
	m_on_render_view_ptr->on_exit_complate(true);
	return status;
}

result_t cdisplay_context_gles::render_complete(
	const EGL_device_t& PARAM_IN device,
	bool bswap_buffer //= true
	)
{
	EGLBoolean egl_result;
	if (bswap_buffer)
	{
		egl_result = ::eglWaitGL();
	}
	else
	{
		egl_result = ::eglSwapBuffers(device.m_EGLDisplay,
			device.m_EGLWindow);
	}
	if (egl_result)
	{
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_FAIL;
	}
}

result_t cdisplay_context_gles::show_view(cOn_render_view_t* PARAM_INOUT on_view_callback_ptr)
{
	if (!on_view_callback_ptr)
	{
		return PFX_STATUS_INVALID_VALUE;
	}
	if (m_on_render_view_ptr)
	{
		return PFX_STATUS_UNIQUE;
	}
	m_on_render_view_ptr = m_on_render_view_ptr;
	m_bshow_window = true;
	return m_thread.start_thread(&m_thread_proxy);
}
result_t cdisplay_context_gles::close_view()
{
	result_t status;
	m_bshow_window = false;
	status = m_thread.wait_thread_exit(5000);
	return status;
}

PECKER_END

