/*
 * pecker_render_system.h
 *
 *  Created on: 2013-4-7
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_SYSTEM_H_
#define PECKER_RENDER_SYSTEM_H_

#include "../pecker_render_object.h"
#include "pecker_render_device.h"
#include "../../native/pecker_window.h"

PECKER_BEGIN

#define LUMINANCE_SIZE_BITS_FIELD				BIT_0_to_7_MASK_0_to_31
#define ALPHA_MASK_SIZE_BITS_FIELD				BIT_16_to_23_MASK_0_to_31
#define COLOR_BUFFER_BITS_TYPE_FIELD			BIT_24_to_31_MASK_0_to_31
 
#define RED_SIZE_BITS_FIELD											BIT_0_to_7_MASK_0_to_31
#define GREEN_SIZE_BITS_FIELD										BIT_8_to_15_MASK_0_to_31
#define BLUE_SIZE_BITS_FIELD										BIT_16_to_23_MASK_0_to_31
#define ALPHA_SIZE_BITS_FIELD										BIT_24_to_31_MASK_0_to_31

#define DEPTH_BUFFER_SIZE_BITS_FIELD						BIT_16_to_23_MASK_0_to_31
#define STCENCIL_BUFFER_SIZE_BITS_FIELD					BIT_24_to_31_MASK_0_to_31

#define PBUFFER_BIT_FIELD												BIT_0_MASK_0_to_31
#define PIXMAP_BIT_FIELD												BIT_1_MASK_0_to_31
#define CONFORMANT_BIT_FIELD									BIT_2_MASK_0_to_31
#define MAX_PBUFFER_WIDTH_BIT_FIELD					BIT_3_MASK_0_to_31
#define MAX_PBUFFER_HEIGHT_BIT_FIELD					BIT_4_MASK_0_to_31
#define MAX_PBUFFER_PIXELS_BIT_FIELD						BIT_5_MASK_0_to_31
#define BIND_TO_TEXTURE_RGB_BIT_FIELD					BIT_6_MASK_0_to_31
#define BIND_TO_TEXTURE_RGBA_BIT_FIELD				BIT_7_MASK_0_to_31
#define MAX_TEXTURE_BIT_FIELD									BIT_8_MASK_0_to_31
#define TEXTURE_TARGET_BITS_FIELD							(0x03 << 20)							
#define TEXTURE_FORMAT_BITS_FIELD							(0xff	 << 12)			
#define FSAAMODE_BIT_FIELD										BIT_20_MASK_0_to_31
#define ENABLE_PIXMAP_COPY_BIT_FIELD					BIT_21_MASK_0_to_31

#define SAMPLE_PER_PIXEL_SIZE_BITS_FIELD				BIT_0_to_15_MASK_0_to_31
#define NUMBER_OF_SAMPLE_BUFFER_BITS_FIELD	BIT_16_to_31_MASK_0_to_31

#define TRANSACTION_TYPE_BITS_FIELD						BIT_0_to_7_MASK_0_to_31
#define TRANSACTION_RED_SIZE_BITS_FIELD				BIT_8_to_15_MASK_0_to_31
#define TRANSACTION_GREEN_SIZE_BITS_FIELD			BIT_16_to_23_MASK_0_to_31
#define TRANSACTION_BLUE_SIZE_BITS_FIELD				BIT_24_to_31_MASK_0_to_31

 
// render system常量参数，只会在打开渲染设备前修改，渲染设备打开以后无法修改
struct pecker_render_system_const_param
{
	BitField _M_color_buffer;//   bit order 0~31bit, 0~7 luminance size 8~15 revered 
												//		16~23 alpha mask size,24~31 color buffer type
	BitField _M_color_bpp; //  bit order 0~31bit , 0~7 red 8~15 green 16~23 blue 24~31 alpha
	BitField _M_render_buffer; //   bit order 0~31bit , 0~15 reserved 16~23 depth buffer size 24~31 stcencil buffer size
	BitField _M_config_mask; //  bit order 0~31bit,0 need Pbuffer bit , 1 need pixmap bit, 2 conformant bit,3 max pbuffer width
												   //  4 max pbuffer height, 5 max pbuffer pixels,6 bind to  texture rgb bit,7 bind to texture rgba bit,
												  // 8 mip texture bit , 9 10 11texture target
												  // 12~19 texture format
												  // 20 FSAAmode enable
												  // 21 enable pixmap copy
	BitField _M_sample; //    bit order 0~31bit , 0~15 sample per pixel  16~31 number of multisample buffers
	BitField _M_transparent; //   bit order 0~31bit , 0~7 transparent type 8~15 red 16~23 green 24~31 blue
	
	nINDEX _M_config_ID;
	nSize  _M_pbuffer_width;
	nSize  _M_pbuffer_height;
	nSize	_M_back_buffer_size;
	PVoid _M_pback_buffer;
};

// render system变量参数, 渲染设备打开以后可以修改
struct pecker_render_system_variable_param
{
	HEnum _M_target_type;
	BitField _M_config_mask;
	Handle _M_status_param1;
	Handle _M_status_param2;
	Handle _M_render_complete_param1;
	Handle _M_render_complete_param2;
	Handle _M_render_complete_param3;
	Handle _M_render_complete_param4;
	Handle _M_render_complete_param5;

	HEnum _M_context_prepriority;
	nSize	_M_swap_interval;
	BitField _M_revered_response_field;
};

enum RENDER_SYS_PARAM_COLOR_BUFFER_TYPE
{
	RSYS_RGB_BUFFER = 0,
	RSYS_LUMINANCE_BUFFER,

	RENDER_SYS_PARAM_COLOR_BUFFER_TYPE_COUNT
};

enum CONTEXT_PREPRIORITY_TYPE
{
	CONTEXT_DEFAULT_PREPRIORITY = 0,
	CONTEXT_LOW_PREPRIORITY,
	CONTEXT_MEDIUM_PREPRIORITY,
	CONTEXT_HIGH_PREPRIORITY,


	CONTEXT_PREPRIORITY_TYPE_COUNT
};

enum   RENDER_SYS_VARIABLE_PARAM_TYPE
{
	RSYS_RESET_ALL,
	RSYS_SET_TARGET,
	RSYS_CONTEXT_PREPRIORITY,
	RSYS_SWAP_INTERNVAL,
	RSYS_SET_STATUS,
	RSYS_SET_RENDER_COMPELETE_PARAM,

	
	RENDER_SYS_VARIABLE_PARAM_TYPE_COUNT
};

PeckerInterface Ipecker_render_system
{
	virtual ~Ipecker_render_system(){;}
	virtual HResult set_render_system_param(const pecker_render_system_const_param & sys_param) = 0;
	virtual Ipecker_render_device* open_render_device(Ipecker_window_display* pwindows_display) = 0;
	virtual HResult close_render_device() = 0;
	virtual HResult render_complete() = 0;
	virtual HResult flush_frame_buffer(Bool bfinish = false) = 0;

	virtual HResult set_param(HEnum update_type, const pecker_render_system_variable_param& sys_param) = 0;
	virtual const pecker_render_system_variable_param& get_param(HEnum param_type) const = 0;
	//virtual HResult resize_render_display(nSize x,nSize y,nSize width,nSize height) = 0;
	//virtual HResult parse_render_display() = 0;
	//virtual HResult resume_render_display() = 0;
	//virtual HResult close_render_display() = 0;

	//virtual HResult get_system_info(pecker_render_system_info& P_OUT system_info) = 0;
};

class pecker_render_system_factory
{
public:
	static Ipecker_render_system* create_render_system(const pecker_string &render_system_name);
	static void release_render_system(Ipecker_render_system* &prender_system);
};

PECKER_END

#endif //PECKER_RENDER_SYSTEM_H_
