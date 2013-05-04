/*
 * pecker_render_system_gl.cpp
 *
 *  Created on: 2013-4-30
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#include <stdlib.h>
#include <string.h>
#include "pecker_render_system_gl.h"
#include <GLES2/gl2.h>
#include <EGL/eglext.h>
#include "../../../native/pecker_log.h"


PECKER_BEGIN



static HEnum gRSYS_color_buffer_type_table[RENDER_SYS_PARAM_COLOR_BUFFER_TYPE_COUNT] = {EGL_RGB_BUFFER,EGL_LUMINANCE_BUFFER};

pecker_render_system_gles2::pecker_render_system_gles2():_M_device_is_open(false)
{
	set_bytes_in_bitfield_mask(_M_config._M_color_buffer,0,0,0,RSYS_RGB_BUFFER);
	set_bytes_in_bitfield_mask(_M_config._M_color_bpp,8,8,8,8);
	set_bytes_in_bitfield_mask(_M_config._M_render_buffer,0,0,16,8);
	set_u16_in_bitfield_mask(_M_config._M_sample,4,1);
	set_bytes_in_bitfield_mask(_M_config._M_transparent,0,0,0,0);
	_M_config._M_config_mask = BIT_0_MASK_0_to_31;

	_M_config._M_pbuffer_width = 0;
	_M_config._M_pbuffer_height = 0;
	_M_config._M_back_buffer_size = 0;
	_M_config._M_pback_buffer = null;
}

pecker_render_system_gles2::~pecker_render_system_gles2()
{

}
HResult pecker_render_system_gles2::set_render_system_param(const pecker_render_system_param & sys_param)
{
	_M_config = sys_param;
	return P_OK;
}

Ipecker_render_device* pecker_render_system_gles2::open_render_device(Ipecker_window_display* pwindows_display)
{
	if (null == pwindows_display)
	{
		return null;
	}
	if (_M_device_is_open)
	{
		return &_M_graphic_device;
	}

	_M_config._M_pbuffer_width = pwindows_display->get_width();
	_M_config._M_pbuffer_height = pwindows_display->get_height();

	// 从窗口中获取底层display接口，windows对应的是HDC
	_M_EGLDisplay = eglGetDisplay((EGLNativeDisplayType)(pwindows_display->get_native_display()));
	
	if (EGL_NO_DISPLAY == _M_EGLDisplay)
	{
		_M_EGLDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	}

	// 获取display失败
	if (EGL_NO_DISPLAY == _M_EGLDisplay)
	{
		return null;
	}

	if(!eglInitialize(_M_EGLDisplay, &_M_MajorVersion, &_M_MinorVersion))
	{
		PECKER_LOG_ERR("Unable to initialise EGL","EGL ERROR %d",eglGetError());
		return null;
	}

	PECKER_LOG_INFO("EGL initialized","EGL %d %d",_M_MajorVersion,_M_MinorVersion);
	
	// 绑定底层渲染API
	if (!eglBindAPI(EGL_OPENGL_ES_API))
	{
		PECKER_LOG_ERR("Unable to bind API EGL","EGL ERROR %d",eglGetError());
		return null;
	}

	pecker_render_system_param backup_config = _M_config;

	Ipecker_render_device*  preturn_value =  &_M_graphic_device;
	do 
	{
		nINDEX egl_config_id = 0;
		if (P_OK == select_config(_M_config,egl_config_id,_M_EGLConfig))
		{
			// 已经存在一个context，则删除
			if (_M_EGLContext)
			{
				eglDestroyContext(_M_EGLDisplay,_M_EGLContext);
			}
			_M_optimation_tmp_config_stack1.clear();
			rsys_config_stack* pcontext_attrible_stack = &_M_optimation_tmp_config_stack1;
			HEnum attrible_cmd;
			HEnum attrible_data;
			
			// 使用opengl es 2.0
			attrible_cmd = EGL_CONTEXT_CLIENT_VERSION;
			attrible_data = 2;
			pcontext_attrible_stack->push(attrible_cmd);
			pcontext_attrible_stack->push(attrible_data);

			//
			if (is_egl_externsion_supported(_M_EGLDisplay,"EGL_IMG_context_priority"))
			{
				attrible_cmd = EGL_CONTEXT_PRIORITY_LEVEL_IMG;
				switch(_M_config._M_context_prepriority)
				{
				case CONTEXT_LOW_PREPRIORITY:
					attrible_data = EGL_CONTEXT_PRIORITY_LOW_IMG;
					break;
				case CONTEXT_MEDIUM_PREPRIORITY:
					attrible_data = EGL_CONTEXT_PRIORITY_MEDIUM_IMG;
					break;
				case CONTEXT_HIGH_PREPRIORITY:
					attrible_data = EGL_CONTEXT_PRIORITY_HIGH_IMG;
					break;
				default:
					attrible_data = EGL_CONTEXT_PRIORITY_HIGH_IMG;
					//_M_config._M_context_prepriority = CONTEXT_DEFAULT_PREPRIORITY;
					break;
				}
				pcontext_attrible_stack->push(attrible_cmd);
				pcontext_attrible_stack->push(attrible_data);
			}
			attrible_cmd = EGL_NONE;
			pcontext_attrible_stack->push(attrible_cmd);
			const EGLint* pattrib_list = (const EGLint*)(pcontext_attrible_stack->begin()); 
			_M_EGLContext = eglCreateContext(_M_EGLDisplay,_M_EGLConfig,pattrib_list);
			BitField temp_bitfield;
			if (EGL_NO_CONTEXT == _M_EGLContext)
			{
				if (_M_config._M_config_ID > 0)
				{
					PECKER_LOG_ERR("create context EGL","unable to create a context by config id,ERROR=%d",eglGetError());
					preturn_value = null;
					break;
				}
				else if (_M_config._M_config_mask | BIT_0_MASK_0_to_31)
				{
					_M_config._M_config_mask = & (~BIT_0_MASK_0_to_31);
					continue;
				}
				else if (get_bitfield_mask(_M_config._M_render_buffer,BIT_24_to_31_MASK_0_to_31) > 0)
				{
					_M_config._M_render_buffer = set_bitfield_mask(_M_config._M_render_buffer,0,BIT_24_to_31_MASK_0_to_31);
					continue;
				}
				else if ( (temp_bitfield = get_bitfield_mask(_M_config._M_sample,BIT_16_to_23_MASK_0_to_31)) > 1)
				{
					--temp_bitfield;
					_M_config._M_render_buffer = set_bitfield_mask(_M_config._M_render_buffer,temp_bitfield,BIT_16_to_31_MASK_0_to_31);
					continue;
				}
				else if (BIT_20_MASK_0_to_31 | _M_config._M_config_mask)
				{
					if ( get_bitfield_mask(_M_config._M_sample,BIT_16_to_31_MASK_0_to_31) == 1)
					{
						temp_bitfield = get_bitfield_mask(_M_config._M_sample,BIT_0_to_15_MASK_0_to_31);
						if (temp_bitfield > 4)
						{
							temp_bitfield = 4;
							_M_config._M_render_buffer = set_bitfield_mask(_M_config._M_render_buffer,temp_bitfield,BIT_0_to_15_MASK_0_to_31);
						}
						else if (temp_bitfield > 2)
						{
							temp_bitfield = 2;
							_M_config._M_render_buffer = set_bitfield_mask(_M_config._M_render_buffer,temp_bitfield,BIT_0_to_15_MASK_0_to_31);
						}
						else
						{
							temp_bitfield = 0;
							_M_config._M_render_buffer = set_bitfield_mask(_M_config._M_render_buffer,temp_bitfield,BIT_0_to_15_MASK_0_to_31);
							_M_config._M_render_buffer = set_bitfield_mask(_M_config._M_render_buffer,0,BIT_24_to_31_MASK_0_to_31);
						}
						
				}
				continue;
			}
			else
			{
				PECKER_LOG_ERR("create context EGL","give up to try create context %s","... ...");
				preturn_value = null;
				break;
			}

		}
		else
		{
			
			PECKER_LOG_ERR("select config error","restore the orignal config! %s","... ....");
			preturn_value = null;
			break;
		}
	} while (EGL_NO_CONTEXT == _M_EGLContext);
	
	if (null == preturn_value)
	{
		_M_config = backup_config;
	}

	return preturn_value;
}

HResult pecker_render_system_gles2::close_render_device()
{
	return P_OK;
}

HResult pecker_render_system_gles2::resize_render_display(nSize x,nSize y,nSize width,nSize height,Ipecker_window_display* pwindows_display)
{
	return P_OK;
}

HResult pecker_render_system_gles2::swap_frame_buffer()
{
	//eglWaitGL()
	//eglSwapBuffers()
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_render_system_gles2::flush_frame_buffer()
{
	glFlush();
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_render_system_gles2::parse_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}
HResult pecker_render_system_gles2::resume_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}
HResult pecker_render_system_gles2::close_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}

HResult pecker_render_system_gles2::pecker_config_to_egl_config(const pecker_render_system_param& config,rsys_config_stack& P_OUT egl_config)
{
	HEnum config_cmd;
	HEnum config_data;
	egl_config.clear();
	if (config._M_config_ID > 0)
	{
		config_cmd = EGL_CONFIG_ID;
		config_data = config._M_config_ID;
		egl_config.push(config_cmd);
		egl_config.push(config_data);
		config_cmd = EGL_NONE;
		egl_config.push(config_cmd);
		return P_OK;
	}

	//if (0 ==config._M_color_format)
	//{
		config_cmd = EGL_RED_SIZE;
		config_data = get_bitfield_mask(config._M_color_bpp,BIT_0_to_7_MASK_0_to_31);
		egl_config.push(config_cmd);
		egl_config.push(config_data);

		config_cmd = EGL_GREEN_SIZE;
		config_data = get_bitfield_mask(config._M_color_bpp,BIT_8_to_15_MASK_0_to_31);
		egl_config.push(config_cmd);
		egl_config.push(config_data);

		config_cmd = EGL_BLUE_SIZE;
		config_data = get_bitfield_mask(config._M_color_bpp,BIT_16_to_23_MASK_0_to_31);
		egl_config.push(config_cmd);
		egl_config.push(config_data);

		config_cmd = EGL_ALPHA_SIZE;
		config_data = get_bitfield_mask(config._M_color_bpp,BIT_24_to_31_MASK_0_to_31);
		egl_config.push(config_cmd);
		egl_config.push(config_data);
	//}


	config_cmd = EGL_DEPTH_SIZE;
	config_data = get_bitfield_mask(config._M_render_buffer,BIT_16_to_23_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_STENCIL_SIZE;
	config_data = get_bitfield_mask(config._M_render_buffer,BIT_24_to_31_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_ALPHA_MASK_SIZE;
	config_data = get_bitfield_mask(config._M_render_buffer,BIT_16_to_23_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_COLOR_BUFFER_TYPE;
	config_data = get_bitfield_mask(config._M_color_buffer,BIT_24_to_31_MASK_0_to_31);
	if (config_data < RENDER_SYS_PARAM_COLOR_BUFFER_TYPE_COUNT)
	{
		config_data = gRSYS_color_buffer_type_table[config_data];
		egl_config.push(config_cmd);
		egl_config.push(config_data);
	}

	if (EGL_LUMINANCE_BUFFER == config_data)
	{
		config_cmd = EGL_LUMINANCE_SIZE;
		config_data = get_bitfield_mask(config._M_color_buffer,BIT_0_to_7_MASK_0_to_31);
		egl_config.push(config_cmd);
		egl_config.push(config_data);
	}

	config_cmd = EGL_SURFACE_TYPE;
	egl_config.push(config_cmd);
	config_data = EGL_WINDOW_BIT;

	if (BIT_0_MASK_0_to_31 | config._M_config_mask)
	{
		config_data |= EGL_PBUFFER_BIT;
	}

	if (BIT_1_MASK_0_to_31 | config._M_config_mask)
	{
		config_data |= EGL_PIXMAP_BIT;
	}
	egl_config.push(config_data);


	config_cmd = EGL_RENDERABLE_TYPE;
	config_data = EGL_OPENGL_ES2_BIT;
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	if (BIT_20_MASK_0_to_31 | config._M_config_mask)
	{
		config_cmd = EGL_SAMPLE_BUFFERS;
		config_data = get_bitfield_mask(config._M_sample,BIT_16_to_31_MASK_0_to_31);
		egl_config.push(config_cmd);
		egl_config.push(config_data);
		if (config_data > 0)
		{
			config_cmd = EGL_SAMPLES;
			config_data = get_bitfield_mask(config._M_sample,BIT_0_to_15_MASK_0_to_31);
			egl_config.push(config_cmd);
			egl_config.push(config_data);
		}
	}

	config_cmd = EGL_NONE;
	egl_config.push(config_cmd);

	return P_OK;
}

Bool pecker_render_system_gles2::is_egl_externsion_supported(EGLDisplay egl_display,const char* pstr_extension)
{
	const char* pstr_extensions = null;
	const char* pstr_start;
	char* pstr_where;
	char* pstr_terminator;

	pstr_where = (char*)strchr(pstr_extension,' ');
	if (pstr_where || '\0' == *pstr_extension)
	{
		return false;
	}
	pstr_extensions = eglQueryString(egl_display,EGL_EXTENSIONS);
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
				return true;
			}
		}
		pstr_start = pstr_terminator;
	}

	return false;
}

HResult pecker_render_system_gles2::select_config(const pecker_render_system_param& config,nINDEX &config_id,EGLConfig &selection_config)
{
	HResult return_value;

	// 转换成egl使用的config
	return_value = pecker_render_system_gles2::pecker_config_to_egl_config(config,_M_optimation_tmp_config_stack1);//使用类对象的加速栈优化，快速内存分配
	if (P_OK != return_value)
	{
		return  return_value;
	}

	EGLint total_num_configs = 0;
	const EGLint* pconfig_list = (const EGLint*)(_M_optimation_tmp_config_stack1.begin()); 
	// 获取egl config的总数
	if (!eglChooseConfig(_M_EGLDisplay,pconfig_list,NULL,0,&total_num_configs))
	{
		PECKER_LOG_ERR("Choose config error for get total number configs EGL","EGL ERROR %d",eglGetError());
		return_value = P_FAIL;
		return return_value;
	}

	if (0 == total_num_configs)
	{
		PECKER_LOG_ERR("Choose config error EGL","total number of configs = %d",total_num_configs);
		return_value = P_FAIL;
		return return_value;
	}

	//根据上面获取的egl总数，利用类对象的加速栈优化，快速内存分配
	_M_optimation_tmp_config_stack2.init(total_num_configs);
	EGLConfig* pconfigs = (EGLConfig*)(_M_optimation_tmp_config_stack2.get_begin_reference());
	EGLint num_configs;
	// 设置EGL的配置，配置可能有多个
	if (!eglChooseConfig(_M_EGLDisplay,pconfig_list,pconfigs,total_num_configs,&num_configs))
	{
		PECKER_LOG_ERR("Choose config error EGL","EGL ERROR %d",eglGetError());
		return_value = P_FAIL;
		return return_value;
	}

	EGLint config_attrib_value = 0;
	return_value = P_FAIL;
	// 选择跟我们设置参数最近的一个egl配置返回
	for (nINDEX i=0;i<num_configs;++i)
	{
		// 选择方式，以配置中的颜色RGBA值作为选择标准
		if ((eglGetConfigAttrib(_M_EGLDisplay,pconfigs[i],EGL_RED_SIZE,&config_attrib_value) && get_bitfield_mask(config._M_color_bpp,BIT_0_to_7_MASK_0_to_31) == config_attrib_value) &&
			(eglGetConfigAttrib(_M_EGLDisplay,pconfigs[i],EGL_GREEN_SIZE,&config_attrib_value) && get_bitfield_mask(config._M_color_bpp,BIT_8_to_15_MASK_0_to_31) == config_attrib_value) &&
			(eglGetConfigAttrib(_M_EGLDisplay,pconfigs[i],EGL_BLUE_SIZE,&config_attrib_value) && get_bitfield_mask(config._M_color_bpp,BIT_16_to_23_MASK_0_to_31) == config_attrib_value) &&
			(eglGetConfigAttrib(_M_EGLDisplay,pconfigs[i],EGL_ALPHA_SIZE,&config_attrib_value) && get_bitfield_mask(config._M_color_bpp,BIT_24_to_31_MASK_0_to_31) == config_attrib_value) )
		{
			EGLint egl_config_id;
			selection_config = pconfigs[i];
			eglGetConfigAttrib(_M_EGLDisplay,selection_config,EGL_CONFIG_ID,&egl_config_id);
			config_id = egl_config_id;
			return_value = P_OK;
			break;
		}
	}



	return return_value;
}

PECKER_END

