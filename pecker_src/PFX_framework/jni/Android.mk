LOCAL_PATH :=  $(call my-dir)#$(realpath $(call my-dir)/../../)
PFX_MK := /PFX.mk
PFX_TEST_MK := /PFX_TEST.mk
ZLIB_MK := /depends_lib/zlib.mk
PNGLIB_MK := /depends_lib/pnglib.mk

#����������
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(ZLIB_MK)   #zlib
include $(LOCAL_PATH)$(PNGLIB_MK) #pnglib

LOCAL_MODULE    := PFX_DEPENDS
LOCAL_SRC_FILES := $(ZLIB_LOCAL_SRC_FILES)  $(PNG_LOCAL_SRC_FILES)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_ARM_NEON  := true       
endif # TARGET_ARCH_ABI == armeabi-v7a

#�壬gcc 4.9����ʹ��64bit arm��neonָ��
#ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
#        LOCAL_ARM_NEON  := true
#endif # TARGET_ARCH_ABI == arm64-v8a


LOCAL_LDLIBS    := 


include $(BUILD_STATIC_LIBRARY)

#����ͼ�ο�
include $(CLEAR_VARS)
#include $(LOCAL_PATH)$(ZLIB_MK)
#include $(LOCAL_PATH)$(PNGLIB_MK)
include $(LOCAL_PATH)$(PFX_MK)
include $(LOCAL_PATH)$(PFX_TEST_MK)

LOCAL_STATIC_LIBRARIES := PFX_DEPENDS #����������
LOCAL_SUB_SRC_FILES	:= $(PFX_LOCAL_SRC_FILES) $(PFX_TEST_LOCAL_SRC_FILES)


#LOCAL_CFLAGS := -D_ARM_ASSEM_
#LOCAL_ARM_MODE := arm

LOCAL_MODULE    := PFX_framework
LOCAL_SRC_FILES := $(LOCAL_SUB_SRC_FILES)# android_native_app_glue.cpp PFX_framework.cpp

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_CFLAGS += -mfpu=neon
        LOCAL_ARM_NEON  := true       
endif # TARGET_ARCH_ABI == armeabi-v7a

#ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
#        LOCAL_ARM_NEON  := true
#endif # TARGET_ARCH_ABI == arm64-v8a


LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid 
#���õ�android�Լ����˸�pthread�����ֺ����˸�
#-lpthread
#LOCAL_LDLIBS_RELEASE := -lEGL -lGLESv2 -llog -lz -landroid

include $(BUILD_SHARED_LIBRARY)



