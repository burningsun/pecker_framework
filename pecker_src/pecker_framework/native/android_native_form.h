/*
* android_native_form.h
*
*  Created on: 2014-8-4
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PFX_ANDROID_NATIVE_FORM_H_
#define PFX_ANDROID_NATIVE_FORM_H_
#include "../pfx_defines.h"

#include "../data/pfx_region.h"
#include "../include/cstring_pfx.h"
#include "pfx_thread.h"

#if (OS_CONFIG == OS_ANDROID)


#include <android/native_activity.h>
#include <android/native_window.h>
#include <android/configuration.h>
#include <android/looper.h>
#include <string.h>


PECKER_BEGIN

typedef struct PFX_NATIVE_API st_activity_init_state
{
	unsigned m_native_style : 1; // 0 使用m_reverd前的字段初始化，
	// 1 使用m_style，m_extern_style字段初始化
	unsigned m_fixed_window : 1; // 0 resize ; 1 fixed
	unsigned m_minable : 1; // 最小化
	unsigned m_maxable : 1; // 最大化
	unsigned m_pixlmap : 1;
	unsigned m_reverd : 28;

	bitfield_t		m_style;
	bitfield_t		m_extern_style;

	void*			m_instance_ptr;

	viewport_rect_t	m_windows_rect;
	cstring_ascii_t	m_strtitle;
	cstring_ascii_t m_str_cmdline;

	st_activity_init_state() :m_native_style(0),
		m_fixed_window(1),
		m_minable(0),
		m_maxable(0),
		m_pixlmap(0),
		m_reverd(0),
		m_style(0),
		m_extern_style(0),
		m_instance_ptr(null)
	{
		;
	}
	~st_activity_init_state()
	{
		;
	}
}activity_init_state_t;

typedef enum enumACTIVE_STATUS
{
	PFX_ACTIVE_NO_INIT = 0,
	PFX_ACTIVE_CREATE,
	PFX_ACTIVE_WIN_CREATE,
	PFX_ACTIVE_START,
	PFX_ACTIVE_RESTART,
	PFX_ACTIVE_RESUME,
	PFX_ACTIVE_PAUSE,
	PFX_ACTIVE_STOP,
	PFX_ACTIVE_WIN_DESTROY,
	PFX_ACTIVE_DESTROY,

	PFX_ACTIVE_CONFIG_CHANGED,
	PFX_ACTIVE_RESIZED,
	PFX_ACTIVE_CLIENT_RECT_CHANGED,
	PFX_ACTIVE_GAINED_FOCUS,
	PFX_ACTIVE_LOST_FOCUS,
	PFX_ACTIVE_LOW_MEMORY,
	PFX_ACTIVE_STATUS_COUNT
}PFX_ACTIVE_STATUS_t;

class PFX_NATIVE_API android_native_form
{
public:
	typedef android_native_form cnative_form_t;
	// activity 接口
	PFX_Interface PFX_NATIVE_API IActivity_component
	{
		virtual ~IActivity_component(){ ; }
		virtual void on_create(activity_init_state_t& PARAM_OUT init_state) = 0;
		virtual void on_start() = 0;
		virtual result_t on_init(cnative_form_t* PARAM_INOUT active_form_ptr) = 0;

		virtual result_t on_restart() = 0;
		virtual void on_resume() = 0;
		virtual void on_pause() = 0;
		virtual void on_stop() = 0;
		virtual void on_destroy() = 0;

		virtual void on_modify_view() = 0;
		virtual void on_finish_modify_view() = 0;

		virtual	result_t on_event(flag_t message, long_t wParam, long_t lParam) = 0;

		virtual void on_save_instance_state () = 0;
		virtual void on_free_instance_state () = 0;
		virtual void on_focus_changed (boolean_t bfocus) = 0;
		virtual void on_config_changed() = 0;
		virtual void on_low_memery () = 0;
	};

	// 事件处理接口
	PFX_Interface IEvent
	{
		virtual ~IEvent(){;}
		virtual enum_int_t get_type_ID () const = 0;
		virtual sint_t process (cnative_form_t* PARAM_INOUT app_form_ptr,
				void* event_ptr) = 0;
	};
	PFX_Interface IEvent_source
	{
		virtual ~IEvent_source(){;}
		virtual enum_int_t getID () const = 0;
		virtual result_t bind_event (IEvent* event_ptr) = 0;
		virtual result_t process (cnative_form_t* PARAM_INOUT app_form_ptr) = 0;
	};
	//
	typedef enum enumFORM_LOOPER_ID
	{
		FORM_LOOPER_ID_NULL = 0,
	    FORM_LOOPER_ID_MAIN,
	    FORM_LOOPER_ID_INPUT,

	    /**
	     * Start of user-defined ALooper identifiers.
	     */
	   FORM_LOOPER_ID_USER,

	   FORM_LOOPER_ID_COUNT
	}FORM_LOOPER_ID_t;

	typedef struct st_Event_pull_source
	{
		PFX_INLINE enum_int_t get_event_ID () const
		{
			if (m_event_ptr)
			{
				return m_event_ptr->getID();
			}
			else
			{
				return FORM_LOOPER_ID_NULL;
			}
		}
	    PFX_INLINE result_t process (cnative_form_t* PARAM_INOUT app_form_ptr)
	    {
	    	if (m_event_ptr)
	    	{
	    		return m_event_ptr->process(app_form_ptr);
	    	}
	    	else
	    	{
	    		return PFX_STATUS_UNINIT;
	    	}
	    }
	    IEvent_source* m_event_ptr;
	    st_Event_pull_source():m_event_ptr(null){;}
	    ~st_Event_pull_source(){;}
	}Event_pull_source;

protected:
	typedef long (android_native_form::*on_message_translate_callback_t) (proxy_status_t* __proxy_status_ptr);
	typedef thread_proxy < android_native_form, on_message_translate_callback_t >	thread_proxy_t;


	///////////////////////////////////////////

	friend class CInputEvent_source;

	class CInputEvent_source : public IEvent_source
	{
	private:
		IEvent* m_bindEvent;
	public:
		CInputEvent_source():m_bindEvent(null){;}
		~CInputEvent_source(){m_bindEvent = null;}
		PFX_INLINE enum_int_t getID () const
		{
			return FORM_LOOPER_ID_INPUT;
		}
		PFX_INLINE result_t bind_event (IEvent* event_ptr)
		{
			if (event_ptr && event_ptr->get_type_ID() == getID())
			{
				m_bindEvent = event_ptr;
				return PFX_STATUS_OK;
			}
			else
			{
				return PFX_STATUS_INVALID_PARAMS;
			}
		}
		result_t process (cnative_form_t* PARAM_INOUT app_form_ptr);
	};


	//////////////////////////////////
	// NDK相关的回掉函数
public:
	static const cstring_ascii_t& get_app_path ();
	static struct AAssetManager* get_app_assertManager ();
public:
	typedef int (*PFX_main_callback)(pecker_sdk::android_native_form* PARAM_INOUT main_form);
	static void app_main (PFX_main_callback __PFX_main_func, 
		ANativeActivity* activity, void* savedState, size_t savedStateSize);
	
protected:
	static PFX_main_callback PFX_main_func;
protected:
	static void onDestroy(ANativeActivity* activity);

	static void onStart(ANativeActivity* activity);

	static void onResume(ANativeActivity* activity);

	static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen);

	static void onPause(ANativeActivity* activity);

	static void onStop(ANativeActivity* activity);

	static void onConfigurationChanged(ANativeActivity* activity);

	static void onLowMemory(ANativeActivity* activity);

	static void onWindowFocusChanged(ANativeActivity* activity, int focused);

	static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);

	static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) ;

	static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);

	static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);



////////////////////////////////////////////////////
public:
	void print_cur_config();

	static const screen_info_t* get_screen_info ();
// android....
protected:
	ANativeActivity* m_attech_activity_ptr;

	AConfiguration*  m_config_ptr;

	cs_t             m_cs;

	ALooper*         m_looper;

	//enum_int_t 			msgread;
	//enum_int_t			msgwrite;
    AInputQueue*     	m_inputQueue;
    CInputEvent_source	m_input_event;
    Event_pull_source   m_input_poll_source;

protected:
	PFX_INLINE result_t attech_android_activity(ANativeActivity* PARAM_INOUT attech_ptr)
	{
		if (attech_ptr)
		{
			m_attech_activity_ptr = attech_ptr;
			return PFX_STATUS_OK;
		}
		return PFX_STATUS_INVALID_PARAMS;
	}
protected:
	PFX_INLINE void register_android_activity_callback_unsafe (ANativeActivity* PARAM_INOUT activity_ptr)
	{
	    activity_ptr->callbacks->onDestroy = onDestroy;
	    activity_ptr->callbacks->onStart = onStart;
	    activity_ptr->callbacks->onResume = onResume;
	    activity_ptr->callbacks->onSaveInstanceState = onSaveInstanceState;
	    activity_ptr->callbacks->onPause = onPause;
	    activity_ptr->callbacks->onStop = onStop;
	    activity_ptr->callbacks->onConfigurationChanged = onConfigurationChanged;
	    activity_ptr->callbacks->onLowMemory = onLowMemory;
	    activity_ptr->callbacks->onWindowFocusChanged = onWindowFocusChanged;
	    activity_ptr->callbacks->onNativeWindowCreated = onNativeWindowCreated;
	    activity_ptr->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
	    activity_ptr->callbacks->onInputQueueCreated = onInputQueueCreated;
	    activity_ptr->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;

	    activity_ptr->instance = this;
	}
private:
	volatile bool m_brunning;
	volatile bool m_bmust_init_window;
protected:
	volatile ANativeWindow*		m_hwmd;
	volatile long_t				m_hdc;
//	long_t				m_pixelmap;
protected:
	thread_proxy_t	m_msg_trans_proxy;
	thread_t		m_msg_trans_thread;
protected:
	android_native_form* m_parent_form_ptr;
protected:
	activity_init_state_t	m_init_state;
	IActivity_component*	m_component_ptr;
	PFX_ACTIVE_STATUS_t		m_activity_status;
	volatile bool			m_started_window;
	volatile result_t		m_dlg_result;
protected:
	result_t	listen_message();
	long		on_app_entry(proxy_status_t* __proxy_status_ptr);
protected:
	result_t 	on_message(flag_t message, long_t wParam, long_t lParam);

protected:
	result_t	create_window(
			ANativeActivity* PARAM_INOUT activity_ptr,
			void* savedState,
			size_t savedStateSize);

/////////////////////
protected:
//public:
	android_native_form();
public:
	virtual ~android_native_form();
public:

	result_t	init(IActivity_component* activity_ptr, 
			android_native_form* parent_form_ptr = null);
	result_t	dispose();

	PFX_INLINE result_t	set_input_event (IEvent* PARAM_IN event_ptr)
	{
		if (event_ptr)
		{
			return m_input_event.bind_event(event_ptr);
		}
		else
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
	}
	PFX_INLINE ALooper* get_looper ()
	{
		return m_looper;
	}
	PFX_INLINE AAssetManager* get_assetManager ()
	{
		if (m_attech_activity_ptr)
		{
			return m_attech_activity_ptr->assetManager;
		}
		else
		{
			return null;
		}
	}
	PFX_INLINE void show_form (bool fullscreen = true//	该参数无效
		)
	{
		m_brunning = true;
	}

	PFX_INLINE void close ()
	{
		m_brunning = false;
	}

	PFX_INLINE result_t get_dlg_result()  const
	{
		result_t status = m_dlg_result;
		return status;
	}

	PFX_INLINE  long_t get_native_window() const
	{
		return (long_t)m_hwmd;
	}
	PFX_INLINE  long_t get_native_display() const
	{
		return (long_t)m_hdc;
	}
	PFX_INLINE  long_t get_native_pixelmap() const
	{
		return 0;//(long_t)m_pixelmap;
	}
	PFX_INLINE const activity_init_state_t&	get_activity_state() const
	{
		return m_init_state;
	}

public:
	static const cstring_ascii_t& get_meta_data_value (ANativeActivity* activity,
			const char* str_name_ptr,
			cstring_ascii_t& value);
	static const cstring_ascii_t& get_app_path(ANativeActivity* activity,
				cstring_ascii_t& str_path);
	static const cstring_ascii_t& get_user_package_name(ANativeActivity* activity,
					cstring_ascii_t& str_name);

};


PECKER_END



#endif//	(OS_CONFIG == OS_WINDOWS)


#endif //PFX_WINDOWS_NATIVE_FORM_H_
