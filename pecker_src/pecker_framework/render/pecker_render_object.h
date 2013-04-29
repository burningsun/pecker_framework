/*
 * pecker_render_object.h
 *
 *  Created on: 2013-3-6
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_RENDER_OBJECT_H_
#define  PECKER_RENDER_OBJECT_H_

#include "../CPeckerObject.h"
#include "../data/pecker_string.h"

PECKER_BEGIN

struct pecker_color
{
	pecker_color():_M_red(0.0f),
		_M_green(0.0f),
		_M_blue(0.0f),
		_M_alpha(0.0f){;}

	pecker_color(Byte red,Byte green,Byte blue,Byte alpha_value):_M_red( (Float)((SInt)red)/255.0f),
		_M_green( (Float)((SInt)green)/255.0f),
		_M_blue( (Float)((SInt)blue)/255.0f),
		_M_alpha( (Float)((SInt)alpha_value)/255.0f){;}

	pecker_color(Float red,Float green,Float blue,Float alpha_value):_M_red(red),
		_M_green(green),
		_M_blue(blue),
		_M_alpha(alpha_value){;}

	Float _M_red,_M_green,_M_blue,_M_alpha;
};

typedef enum enumRENDER_SYSTEM_TYPE
{
	UNKNOWN_RENDER_SYSTEM = 0,
	SYSTEM_DEFAULT,
	OPENGL_RENDER_SYSTEM,
	OPENGLES_RENDER_SYSTEM,
	DIRECTX_RENDER_SYSTEM,

	OTHER_RENDER_SYSTEM,

	RENDER_SYSTEM_TYPE_COUNT
}RENDER_SYSTEM_TYPE;

struct pecker_render_system_info
{
	RENDER_SYSTEM_TYPE _M_system_type;
	Ulong								 _M_version_part1;
	Ulong								 _M_version_part2;
};

class pecker_render_object
{
protected:
	Long _M_reference_count;
public:
	pecker_render_object();
	virtual ~pecker_render_object();

	virtual const pecker_string &toString(pecker_string P_IN &string_input) const; 
	virtual const pecker_render_system_info &get_render_system_info(pecker_render_system_info P_IN &system_info) const;

	virtual pecker_render_object* get_this_reference();
	virtual HResult release_this_reference();
};

template< class reference_type >
struct smart_reference
{
	reference_type* _M_preference_interface;
	smart_reference(const smart_reference& other)
	{
		if (&other != this)
		{
			_M_preference_interface = other._M_preference_interface;
			if (_M_preference_interface)
			{
				_M_preference_interface->get_this_reference();
			}
			
		}
	}
	smart_reference(reference_type* pattach_interface = null) : _M_preference_interface(pattach_interface)
	{
		if (null != pattach_interface)
		{
			pattach_interface->get_this_reference();
		}
	}
	~smart_reference()
	{
		if (null != _M_preference_interface)
		{
			_M_preference_interface->release_this_reference();
		}
	}
	smart_reference & operator = (const smart_reference& other)
	{
		if (&other != this)
		{
			if (null != _M_preference_interface)
			{
				_M_preference_interface->release_this_reference();
			}
			_M_preference_interface = other._M_preference_interface;
			if (_M_preference_interface)
			{
				_M_preference_interface->get_this_reference();
			}

		}
		return *this;
	}
	smart_reference & operator = (reference_type* pattach_interface)
	{
			if (null != _M_preference_interface)
			{
				_M_preference_interface->release_this_reference();
			}
			_M_preference_interface = pattach_interface;
			if (_M_preference_interface)
			{
				_M_preference_interface->get_this_reference();
			}
			return *this;
	}
};


template< class reference_type >
class pecker_reference_interface
{
public:
	static reference_type* convert_to_reference_interface(pecker_render_object* prender_object)
	{
		reference_type* converted_object = null;
		if (null != prender_object)
		{
			//converted_object = static_cast< reference_type* >(prender_object->get_this_reference());
			pecker_render_object*  ptest_object = null;
			converted_object = dynamic_cast< reference_type* >(prender_object);
			//ptest_object = reinterpret_cast<pecker_render_object*>(converted_object);
			//if (null != ptest_object)
			//if (null != converted_object)
			//{
			//	pecker_render_system_info render_sysinfo;
			//	//ptest_object->get_render_system_info(render_sysinfo);
			//	if (UNKNOWN_RENDER_SYSTEM == render_sysinfo._M_system_type)
			//	{
			//		converted_object = null;
			//	}
			//	else
			//	{
			//		ptest_object->get_this_reference();
			//	}
			//}
			else
			{
				converted_object = null;
			}
		}
		return converted_object;
	}
	static pecker_render_object* base_interface(reference_type* prender_object)
	{
		pecker_render_object* converted_object = null;
		if (null != prender_object)
		{
			converted_object = dynamic_cast< pecker_render_object* >(prender_object);
			if (null != converted_object)
			{
				converted_object = converted_object->get_this_reference();
			}
		}
		return converted_object;
	}
	static smart_reference<reference_type> convert_to_reference_interface_st(pecker_render_object* prender_object)
	{
		smart_reference<reference_type> return_val;
		reference_type* converted_object = null;
		if (null != prender_object)
		{
			pecker_render_object*  ptest_object = null;
			converted_object = dynamic_cast< reference_type* >(prender_object);
			//ptest_object = reinterpret_cast<pecker_render_object*>(converted_object);
			//if (null != ptest_object)
			//{
			//	pecker_render_system_info render_sysinfo;
			//	ptest_object->get_render_system_info(render_sysinfo);
			//	if (UNKNOWN_RENDER_SYSTEM == render_sysinfo._M_system_type)
			//	{
			//		converted_object = null;
			//	}
			//	else
			//	{
			//		return_val = converted_object;
			//	}
			//}
			//else
			//{
			//	converted_object = null;
			//}
		}
		return return_val;
	}
	static pecker_render_object* base_interface_st(smart_reference<reference_type> render_object)
	{
		pecker_render_object* converted_object = null;
		if (null != render_object._M_preference_interface)
		{
			converted_object = dynamic_cast< pecker_render_object* >(render_object._M_preference_interface);
			if (null != converted_object)
			{
				converted_object = converted_object->get_this_reference();
			}
		}
		return converted_object;
	}
};

enum FRAME_BUFFER_OBJECT_TYPE
{
	COLOR_BUFFER_TYPE = 0,
	DEPTH_BUFFER_TYPE,
	STENCIL_BUFFER_TYPE,

	TEXTURE_BUFFER_TYPE,

	RENDER_BUF_TYPE_COUNT
};

//PeckerInterface Ipecker_frame_buffer;
PeckerInterface Ipecker_frame_buffer_object
{
	virtual ~Ipecker_frame_buffer_object(){;}
	virtual HResult attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index = 0)=0;//,HEnum face_type = 0,nSize zoffset = 0) = 0; 
	virtual HResult bind() = 0;
	virtual HEnum get_frame_buffer_object_type() const = 0;
};
PECKER_END

#endif //PECKER_RENDER_OBJECT_H_