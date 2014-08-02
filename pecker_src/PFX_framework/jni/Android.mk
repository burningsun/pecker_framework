LOCAL_PATH :=  $(call my-dir)#$(realpath $(call my-dir)/../../)
PFX_MK := /PFX.mk
PFX_TEST_MK := /PFX_TEST.mk
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(PFX_MK)
include $(LOCAL_PATH)$(PFX_TEST_MK)

LOCAL_SUB_SRC_FILES	:= $(PFX_LOCAL_SRC_FILES) $(PFX_TEST_LOCAL_SRC_FILES)


LOCAL_MODULE    := PFX_framework
LOCAL_SRC_FILES := $(LOCAL_SUB_SRC_FILES) android_native_app_glue.cpp PFX_framework.cpp

LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid 
#你妹的android自己搞了个pthread还各种函数阉割
#-lpthread
#LOCAL_LDLIBS_RELEASE := -lEGL -lGLESv2 -llog -lz -landroid

include $(BUILD_SHARED_LIBRARY)
