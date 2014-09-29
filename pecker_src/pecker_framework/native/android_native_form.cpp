/*
* android_native_form.cpp
*
*  Created on: 2014-7-30
*      Author: �����  �� cut / cutxyz��
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#include "android_native_form.h"

#if (OS_CONFIG == OS_ANDROID)

#include <stdlib.h>
#include <unistd.h>
#include "pfx_log.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))

/* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

static int PFX_main_defult(pecker_sdk::android_native_form* PARAM_INOUT main_form)
{
	main_form->show_form();
	return 0;
}

PECKER_BEGIN


android_native_form::PFX_main_callback android_native_form::PFX_main_func =  PFX_main_defult;

result_t android_native_form::CInputEvent_source::process(cnative_form_t* PARAM_INOUT app_form_ptr)
{
    AInputEvent* event = NULL;
    while (AInputQueue_getEvent(app_form_ptr->m_inputQueue, &event) >= 0)
    {
        LOGV("New input event: type=%d\n", AInputEvent_getType(event));
        if (AInputQueue_preDispatchEvent(app_form_ptr->m_inputQueue, event))
        {
            continue;
        }
        sint_t handled = 0;
        if (m_bindEvent)
        {
        	handled = m_bindEvent->process(app_form_ptr,event);

        };
        AInputQueue_finishEvent(app_form_ptr->m_inputQueue, event, handled);
    }
}


android_native_form::android_native_form() :
m_attech_activity_ptr(null),
m_config_ptr(null),
m_hwmd(null),
m_hdc(null),
m_activity_status(PFX_ACTIVE_NO_INIT),
m_component_ptr(null),
m_started_window(false),
m_parent_form_ptr(null),
m_dlg_result(0),
m_bmust_init_window(true),
m_inputQueue(null),
//msgread(0),
//msgwrite(0),
m_brunning(false)
{
	m_msg_trans_proxy.m_object_ptr		= this;
	m_msg_trans_proxy.m_callback		= &android_native_form::on_app_entry;
	m_msg_trans_proxy.m_proxy_status	= null;

	m_input_poll_source.m_event_ptr = &m_input_event;
	InitCriticalSection(&m_cs);
}

android_native_form::~android_native_form()
{

	dispose();
	m_bmust_init_window = true;
	DelCriticalSection(&m_cs);
}

result_t android_native_form::on_message(flag_t message, long_t wParam, long_t lParam)
{
	result_t status = PFX_STATUS_INVALID_PARAMS;
	if (m_component_ptr)
	{
		status = m_component_ptr->on_event(message, wParam, lParam);
	}
	return status;
}

void android_native_form::onDestroy(ANativeActivity* activity)
{
    LOGV("Destroy: %p\n", activity);

 	android_native_form* form_ptr;
 	//critical_section_lock_t __lock;
 	IActivity_component* android_activity_ptr;

     form_ptr = (android_native_form*)activity->instance;

     if (!form_ptr){return;}

     //__lock.lock(form_ptr->mutex);

     form_ptr->dispose();

     //__lock.unlock();
}

void android_native_form::onStart(ANativeActivity* activity)
{
	LOGV("Start: %p\n", activity);

 	android_native_form* form_ptr;
 	critical_section_lock_t __lock;
 	IActivity_component* android_activity_ptr;

     form_ptr = (android_native_form*)activity->instance;

     if (!form_ptr){return;}

     __lock.lock(form_ptr->m_cs);
     android_activity_ptr = form_ptr->m_component_ptr;
     if (android_activity_ptr)
     {
    	 android_activity_ptr->on_start();
     }
     form_ptr->m_activity_status = PFX_ACTIVE_START;
     __lock.unlock();
}

void android_native_form::onResume(ANativeActivity* activity)
{
	LOGV("Resume: %p\n", activity);
 	android_native_form* form_ptr;
 	critical_section_lock_t __lock;
 	IActivity_component* android_activity_ptr;

     form_ptr = (android_native_form*)activity->instance;

     if (!form_ptr){return;}

     __lock.lock(form_ptr->m_cs);
     android_activity_ptr = form_ptr->m_component_ptr;
     if (android_activity_ptr)
     {
    	 android_activity_ptr->on_resume();
    	 android_activity_ptr->on_free_instance_state();
     }
     form_ptr->m_activity_status = PFX_ACTIVE_RESUME;
     __lock.unlock();
}

void* android_native_form::onSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
     void* savedState = null;
     *outLen = 0;

 	 LOGV("SaveInstanceState: %p\n", activity);

 	android_native_form* form_ptr;
 	critical_section_lock_t __lock;
 	IActivity_component* android_activity_ptr;

     form_ptr = (android_native_form*)activity->instance;

     if (!form_ptr){return null;}

     __lock.lock(form_ptr->m_cs);
     android_activity_ptr = form_ptr->m_component_ptr;
     if (android_activity_ptr)
     {
    	 android_activity_ptr->on_save_instance_state();
     }
     __lock.unlock();
    return savedState;
}

void android_native_form::onPause(ANativeActivity* activity)
{
	LOGV("Pause: %p\n", activity);

	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;

    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);
    android_activity_ptr = form_ptr->m_component_ptr;
    if (android_activity_ptr)
    {
    	android_activity_ptr->on_pause();
    }
    form_ptr->m_activity_status = PFX_ACTIVE_PAUSE;
    __lock.unlock();
}

void android_native_form::onStop(ANativeActivity* activity)
{
	LOGV("Stop: %p\n", activity);

	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;

    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);
    android_activity_ptr = form_ptr->m_component_ptr;
    if (android_activity_ptr)
    {
    	android_activity_ptr->on_stop();
    }
    form_ptr->m_activity_status = PFX_ACTIVE_STOP;
    __lock.unlock();
}

void android_native_form::onConfigurationChanged(ANativeActivity* activity)
{
	LOGV("ConfigurationChanged: %p\n", activity);

	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;

    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);
    android_activity_ptr = form_ptr->m_component_ptr;
    if (android_activity_ptr)
    {
    	 AConfiguration_fromAssetManager(form_ptr->m_config_ptr,
    	                    activity->assetManager);

    	android_activity_ptr->on_config_changed();
    }
    form_ptr->m_activity_status = PFX_ACTIVE_CONFIG_CHANGED;
    __lock.unlock();
}

void android_native_form::onLowMemory(ANativeActivity* activity)
{
	LOGV("LowMemory: %p\n", activity);

	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;

    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);
    android_activity_ptr = form_ptr->m_component_ptr;
    if (android_activity_ptr)
    {
    	android_activity_ptr->on_low_memery();
    }
    form_ptr->m_activity_status = PFX_ACTIVE_LOW_MEMORY;
    __lock.unlock();

}

void android_native_form::onWindowFocusChanged(ANativeActivity* activity, int focused)
{

	LOGV("WindowFocusChanged: %p -- %d\n", activity, focused);
	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;

    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);
    android_activity_ptr = form_ptr->m_component_ptr;
    if (android_activity_ptr)
    {
    	android_activity_ptr->on_focus_changed(focused);
    }
    if (focused)
    {
    	form_ptr->m_activity_status = PFX_ACTIVE_GAINED_FOCUS;
    }
    else
    {
    	form_ptr->m_activity_status = PFX_ACTIVE_LOST_FOCUS;
    }
    __lock.unlock();

}

void android_native_form::onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;

	LOGV("NativeWindowCreated: %p -- %p\n", activity, window);
    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);

    android_activity_ptr = form_ptr->m_component_ptr;
	if (android_activity_ptr)
	{
		PECKER_LOG_INFO(" form_ptr->m_bmust_init_window = %d",
				form_ptr->m_bmust_init_window);
		if (form_ptr->m_bmust_init_window)
		{
			result_t status;
			form_ptr->m_hwmd = window;
			form_ptr->m_init_state.m_windows_rect =
			viewport_rect_t(0,0,ANativeWindow_getWidth(window),
					ANativeWindow_getHeight(window));
			status = android_activity_ptr->on_init(form_ptr);

			PECKER_LOG_INFO(" android_activity_ptr->on_init(form_ptr) status = %d",
					status);

			if (PFX_STATUS_OK == status)
			{
				form_ptr->m_bmust_init_window = false;
			}
		}
		else
		{
			android_activity_ptr->on_modify_view();

			form_ptr->m_hwmd = window;
			form_ptr->m_init_state.m_windows_rect =
			viewport_rect_t(0,0,ANativeWindow_getWidth(window),
					ANativeWindow_getHeight(window));

			android_activity_ptr->on_finish_modify_view();
		}

	}

	form_ptr->m_activity_status = PFX_ACTIVE_WIN_CREATE;
    __lock.unlock();
    PECKER_LOG_INFO("form_ptr->m_hwmd = %08X",form_ptr->m_hwmd);
}

void android_native_form::onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;


	LOGV("NativeWindowDestroyed: %p -- %p\n", activity, window);
    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);
    android_activity_ptr = form_ptr->m_component_ptr;
    if (android_activity_ptr)
    {
    	android_activity_ptr->on_modify_view();
    }
    form_ptr->m_activity_status = PFX_ACTIVE_WIN_DESTROY;
    __lock.unlock();
}

void android_native_form::onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
	LOGV("InputQueueCreated: %p -- %p\n", activity, queue);

	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;

    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);
    if (form_ptr->m_inputQueue)
    {
    	 LOGV("detaching input queue to looper");
        AInputQueue_detachLooper(form_ptr->m_inputQueue);
    }
    form_ptr->m_inputQueue = queue;
    if (form_ptr->m_inputQueue)
    {
        LOGV("Attaching input queue to looper");
        AInputQueue_attachLooper(form_ptr->m_inputQueue,
        		form_ptr->m_looper, FORM_LOOPER_ID_INPUT, NULL,
                &(form_ptr->m_input_poll_source));
    }
    __lock.unlock();
}

void android_native_form::onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{

	LOGV("InputQueueDestroyed: %p -- %p\n", activity, queue);

	android_native_form* form_ptr;
	critical_section_lock_t __lock;
	IActivity_component* android_activity_ptr;

    form_ptr = (android_native_form*)activity->instance;

    if (!form_ptr){return;}

    __lock.lock(form_ptr->m_cs);

    if (form_ptr->m_inputQueue)
    {
        AInputQueue_detachLooper(form_ptr->m_inputQueue);
    }
    form_ptr->m_inputQueue = null;//queue;
    if (form_ptr->m_inputQueue)
    {
        LOGV("Attaching input queue to looper");
        AInputQueue_attachLooper(form_ptr->m_inputQueue,
        		form_ptr->m_looper, FORM_LOOPER_ID_INPUT, NULL,
                &(form_ptr->m_input_poll_source));
    }
    __lock.unlock();
}

void android_native_form::print_cur_config()
{
	char lang[2], country[2];
    AConfiguration_getLanguage(m_config_ptr, lang);
    AConfiguration_getCountry(m_config_ptr, country);

    LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
            "keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
            "modetype=%d modenight=%d",
            AConfiguration_getMcc(m_config_ptr),
            AConfiguration_getMnc(m_config_ptr),
            lang[0], lang[1], country[0], country[1],
            AConfiguration_getOrientation(m_config_ptr),
            AConfiguration_getTouchscreen(m_config_ptr),
            AConfiguration_getDensity(m_config_ptr),
            AConfiguration_getKeyboard(m_config_ptr),
            AConfiguration_getNavigation(m_config_ptr),
            AConfiguration_getKeysHidden(m_config_ptr),
            AConfiguration_getNavHidden(m_config_ptr),
            AConfiguration_getSdkVersion(m_config_ptr),
            AConfiguration_getScreenSize(m_config_ptr),
            AConfiguration_getScreenLong(m_config_ptr),
            AConfiguration_getUiModeType(m_config_ptr),
            AConfiguration_getUiModeNight(m_config_ptr));
}

result_t	android_native_form::init(IActivity_component* activity_ptr,
		android_native_form* parent_form_ptr //= null
		)
{
	if (!activity_ptr)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	if (m_component_ptr && (PFX_ACTIVE_NO_INIT != m_activity_status ||
		PFX_ACTIVE_DESTROY != m_activity_status)
		)
	{
		return PFX_STATUS_DENIED;
	}
	m_component_ptr		= activity_ptr;
	m_activity_status	= PFX_ACTIVE_NO_INIT;
	m_init_state.m_windows_rect.m_x			= 100;
	m_init_state.m_windows_rect.m_y			= 100;
	m_init_state.m_windows_rect.m_width		= 800;
	m_init_state.m_windows_rect.m_height	= 600;

	m_component_ptr->on_create(m_init_state);

	if (m_init_state.m_windows_rect.m_width > 0 &&
		m_init_state.m_windows_rect.m_height > 0)
	{
		m_activity_status = PFX_ACTIVE_CREATE;
		m_parent_form_ptr = parent_form_ptr;
		return PFX_STATUS_OK;
	}
	else
	{
		m_component_ptr = null;
		return PFX_STATUS_FAIL;
	}
}
result_t android_native_form::listen_message()
{
	PECKER_LOG_INFO("begin listen_message %d", m_brunning);
	while (m_brunning)
	{
        int ident;
        int events;
        Event_pull_source* source_ptr;
        source_ptr = null;
        //PECKER_LOG_INFO("waitting ALooper_pollAll...running = %d", m_brunning);
        ident = ALooper_pollAll(100, null, &events,
                (void**)&source_ptr);

        if (ident >= 0)
        {
        	PECKER_LOG_INFO("ALooper_pollAll = %d", ident);
        	PECKER_LOG_INFO("source_ptr = %p", source_ptr);

        	result_t status;
        	if (source_ptr && ident == source_ptr->get_event_ID())
        	{
        		status = source_ptr->process(this);
        	}
        }

		//SleepMS(2000);

	}
	PECKER_LOG_INFO("end listen_message %d", m_brunning);
	return PFX_STATUS_OK;
}




result_t android_native_form::create_window(
		ANativeActivity* activity_ptr,
		void* savedState,
		size_t savedStateSize)
{
	LOGV("Creating: %p\n", activity_ptr);
	result_t status;
	status = this->attech_android_activity(activity_ptr);
	if (status)
	{
		PECKER_LOG_ERR("attech_android_activity = %d",status);
		return status;
	}
	this->register_android_activity_callback_unsafe(activity_ptr);

	LOGV("this->m_brunning: %d\n", this->m_brunning);
	critical_section_lock_t __lock;
	__lock.lock(m_cs);
	if (this->m_brunning)
	{
		return status;
	}

	this->m_brunning = false;


	__lock.unlock();



	LOGV("start_thread...");
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	status = m_msg_trans_thread.start_thread
			(&m_msg_trans_proxy,&attr,2000);

	if (status)
	{
		return status;
	}



	// �ȴ���ʱ5��
	usize__t try_count = 50;
	while (try_count--)
	{
		PECKER_LOG_INFO("wait try = %d,  m_started_window =%d",
				try_count,
				this->m_started_window);

		if (this->m_started_window)
		{
			break;
		}
		SleepMS(100);
	}
	if (!(this->m_started_window))
	{
		status = PFX_STATUS_TIMEOUT;
	}

	PECKER_LOG_INFO("create_window fin wait try = %d,  m_started_window =%d",
			try_count,
			this->m_started_window);

	return status;
}
	
result_t android_native_form::dispose()
{
	critical_section_lock_t __lock;
	__lock.lock(m_cs);
	m_brunning = false;
	m_started_window = false;
	if (m_component_ptr)
	{
		m_component_ptr->on_destroy();
	}

    if (m_inputQueue)
    {
        AInputQueue_detachLooper(m_inputQueue);
    }
    if (m_config_ptr)
    {
    	AConfiguration_delete(m_config_ptr);
    }

    m_component_ptr = null;
    m_inputQueue = null;
    m_config_ptr = null;

    if (m_attech_activity_ptr)
    {
    	m_attech_activity_ptr = null;
    }
    m_brunning = false;

    m_activity_status = PFX_ACTIVE_DESTROY;

    PECKER_LOG_INFO("dispose fin %d",0);
	return PFX_STATUS_OK;
}

long android_native_form::on_app_entry(proxy_status_t* __proxy_status_ptr)
{
	PECKER_LOG_INFO("on_app_entry proxy=%p", __proxy_status_ptr);
	m_config_ptr = AConfiguration_new();
	AConfiguration_fromAssetManager(m_config_ptr,
			m_attech_activity_ptr->assetManager);
	print_cur_config();
	m_looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	//................
	m_brunning = false;
	m_started_window = true;

	//
	int exit_code = PFX_main_func (this);

	PECKER_LOG_INFO("finish PFX_main %d",exit_code);
	result_t status = listen_message();
	PECKER_LOG_INFO("finish listen_message %d", status);
	//
	m_bmust_init_window = true;
	m_brunning = false;
	m_started_window = false;
	status = dispose();
	PECKER_LOG_INFO("exit app %d", status);
	exit(0);
	return 0;

}

static cstring_ascii_t gstr_app_path;
static struct AAssetManager* gAsset_manager = null;

const cstring_ascii_t& android_native_form::get_app_path()
{
	return gstr_app_path;
}

struct AAssetManager* android_native_form::get_app_assertManager()
{
	return gAsset_manager;
}

void android_native_form::app_main (PFX_main_callback __PFX_main_func, ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
	PECKER_LOG_INFO("activtiy = %p, savedState= %p savedStateSize = %d",
			activity, savedState, savedStateSize);
	static android_native_form form; //= new pecker_sdk::android_native_form();
	PECKER_LOG_INFO ("app main form = %p",&form);
	if (__PFX_main_func)
	{
		PFX_main_func = __PFX_main_func;
	}

	JNIEnv* env = activity->env;
	jclass clazz = env->GetObjectClass(activity->clazz);
	jmethodID methodID = env->GetMethodID(clazz, "getPackageCodePath",
			"()Ljava/lang/String;");
	jobject jstring_object = env->CallObjectMethod(activity->clazz, methodID);
	jboolean isCopy;

	const char* chr_path = env->GetStringUTFChars((jstring) jstring_object, &isCopy);

	usize__t path_size = env->GetStringLength((jstring) jstring_object);
	gstr_app_path.init_string(chr_path, path_size);
	gstr_app_path.append_string("\0",1);
	gstr_app_path.resize_string(path_size);

	env->ReleaseStringUTFChars((jstring) jstring_object,chr_path);


	gAsset_manager = activity->assetManager;

	form.create_window(activity, savedState, savedStateSize);
}


PECKER_END








#endif //(OS_CONFIG == OS_WINDOWS)