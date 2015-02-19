LOCAL_PATH := $(call my-dir)
LOCAL_LIB_PATH :=  $(realpath $(call my-dir)/../../../../PFX_framework/libs/)
LOCAL_LIB_INCLUDE :=  $(realpath $(call my-dir)/../../../../pecker_framework)
LOCAL_LIB_TEST_INCLUDE :=  $(realpath $(call my-dir)/../../../../pecker_test)

 $(call __ndk_info, $(LOCAL_LIB_PATH))
 $(call __ndk_info, $(LOCAL_LIB_INCLUDE))
 $(call __ndk_info, $(LOCAL_LIB_TEST_INCLUDE))
 
$(call __ndk_info, ±‡“Î“¿¿µø‚)
include $(CLEAR_VARS)
LOCAL_MODULE := PFX_CORE_GLES_S

PFX_LIB_NAME := $(LOCAL_LIB_PATH)/armeabi-v7a/libPFX_CORE_GLES_S.so
$(call __ndk_info, $(PFX_LIB_NAME))
LOCAL_SRC_FILES := $(PFX_LIB_NAME)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_LIB_INCLUDE) 
                           
include $(PREBUILT_SHARED_LIBRARY)


$(call __ndk_info, ±‡“Î÷¥––≥Ã–Ú)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_LIB_INCLUDE) \
                    $(LOCAL_LIB_TEST_INCLUDE)
                    
 $(call __ndk_info, $(LOCAL_C_INCLUDES))
                    
LOCAL_MODULE    := PFX_Sample
LOCAL_SRC_FILES := \
                   $(LOCAL_LIB_TEST_INCLUDE)/pfx_load_image.cpp \
                   PFX_Sample.cpp 

LOCAL_SHARED_LIBRARIES := PFX_CORE_GLES_S#∏Ωº”“¿¿µø‚

LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid -ldl 




include $(BUILD_SHARED_LIBRARY)
