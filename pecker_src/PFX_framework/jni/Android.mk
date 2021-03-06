$(call __ndk_info, ����Android.mk�ļ�)
LOCAL_PATH :=  $(call my-dir)#$(realpath $(call my-dir)/../../)
LOCAL_SLN_PATH :=  $(realpath $(call my-dir)/../)
PFX_MK := /PFX.mk
PFX_TEST_MK := /PFX_TEST.mk
ZLIB_MK := /depends_lib/zlib.mk
PNGLIB_MK := /depends_lib/pnglib.mk
FFT2LIB_MK := /depends_lib/freetype2.mk
APP_MK := /Application.mk

$(call __ndk_info, ����mk�ļ�) 


#####################################################
$(call __ndk_info, ����������)
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(ZLIB_MK)   #zlib
include $(LOCAL_PATH)$(PNGLIB_MK) #pnglib
include $(LOCAL_PATH)$(FFT2LIB_MK)#freetype2lib

LOCAL_MODULE    := PFX_DEPENDS

LOCAL_C_INCLUDES += $(FT2_LOCAL_EXPORT_C_INCLUDES)
LOCAL_CFLAGS  += $(FT2_LOCAL_CFLAGS)

LOCAL_SRC_FILES :=$(ZLIB_LOCAL_SRC_FILES) $(PNG_LOCAL_SRC_FILES) $(FT2LIB_LOCAL_SRC_FILES) 

#LOCAL_CFLAGS += -fshort-wchar

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_ARM_NEON  := true       
endif # TARGET_ARCH_ABI == armeabi-v7a

#�壬gcc 4.9����ʹ��64bit arm��neonָ��
#ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
#        LOCAL_ARM_NEON  := true
#endif # TARGET_ARCH_ABI == arm64-v8a


LOCAL_LDLIBS    :=  
#-ldl -llog

include $(BUILD_STATIC_LIBRARY)
########################################################


########################################################
$(call __ndk_info, ����ͼ�ο�)
#����ͼ�ο�
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(PFX_MK)
include $(LOCAL_PATH)$(APP_MK)

LOCAL_STATIC_LIBRARIES := PFX_DEPENDS #����������

LOCAL_SUB_SRC_FILES	:= $(PFX_LOCAL_SRC_FILES) 

LOCAL_MODULE    := PFX_CORE_GLES_A
LOCAL_SRC_FILES := $(LOCAL_SUB_SRC_FILES)

$(call __ndk_info, APP_OPTIM =,$(APP_OPTIM))
$(call __ndk_info, OPTIM_FLAG =,$(OPTIM_FLAG))
LOCAL_CFLAGS += $(OPTIM_FLAG)

#LOCAL_CFLAGS += -fshort-wchar
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_CFLAGS += -mfpu=neon
        LOCAL_ARM_NEON  := true 
        $(call __ndk_info,LOCAL_ARM_NEON=,$(LOCAL_ARM_NEON))      
endif # TARGET_ARCH_ABI == armeabi-v7a

LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid 
#���õ�android�Լ����˸�pthread�����ֺ����˸�
#-lpthread
#LOCAL_LDLIBS_RELEASE := -lEGL -lGLESv2 -llog -lz -landroid
include $(BUILD_STATIC_LIBRARY)
################################################################


#################################################################
$(call __ndk_info, ����ͼ�ζ�̬��)
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(PFX_MK)
include $(LOCAL_PATH)$(APP_MK)

LOCAL_STATIC_LIBRARIES := PFX_DEPENDS #����������

LOCAL_SUB_SRC_FILES	:= $(PFX_LOCAL_SRC_FILES) 

LOCAL_MODULE    := PFX_CORE_GLES_S
LOCAL_SRC_FILES := $(LOCAL_SUB_SRC_FILES)

$(call __ndk_info, APP_OPTIM =,$(APP_OPTIM))
$(call __ndk_info, OPTIM_FLAG =,$(OPTIM_FLAG))
LOCAL_CFLAGS += $(OPTIM_FLAG)

#LOCAL_CFLAGS += -fshort-wchar
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_CFLAGS += -mfpu=neon
        LOCAL_ARM_NEON  := true 
        $(call __ndk_info,LOCAL_ARM_NEON=,$(LOCAL_ARM_NEON))      
endif # TARGET_ARCH_ABI == armeabi-v7a

LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid 
include $(BUILD_SHARED_LIBRARY)
############################################################

#############################################################
$(call __ndk_info, ����ִ�г���)
#ִ�г���
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(APP_MK)
include $(LOCAL_PATH)$(PFX_TEST_MK)
include $(LOCAL_PATH)$(PFX_MK)


#LOCAL_STATIC_LIBRARIES := PFX_CORE_GLES_A#����������
LOCAL_SHARED_LIBRARIES := PFX_CORE_GLES_S#����������

LOCAL_SUB_SRC_FILES	:=  $(PFX_TEST_LOCAL_SRC_FILES)

LOCAL_MODULE    := PFX_framework
LOCAL_SRC_FILES := $(LOCAL_SUB_SRC_FILES) \
                   $(PFX_LOCAL_PATH)pfx_android_load_pfx.cpp

$(call __ndk_info, APP_OPTIM =,$(APP_OPTIM))
$(call __ndk_info, OPTIM_FLAG =,$(OPTIM_FLAG))
LOCAL_CFLAGS += $(OPTIM_FLAG) \
                -DMASTER_LIB


ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_CFLAGS += -mfpu=neon
        LOCAL_ARM_NEON  := true 
        $(call __ndk_info,LOCAL_ARM_NEON=,$(LOCAL_ARM_NEON))      
endif # TARGET_ARCH_ABI == armeabi-v7a

LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid -ldl 

include $(BUILD_SHARED_LIBRARY)
###################################################################

#############################################################
$(call __ndk_info, PFX����ʱ��)
#ִ�г���
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(APP_MK)
include $(LOCAL_PATH)$(PFX_MK)

LOCAL_STATIC_LIBRARIES := PFX_DEPENDS #����������

LOCAL_SUB_SRC_FILES	:= $(PFX_LOCAL_SRC_FILES) 

LOCAL_SUB_SRC_FILES	:=  $(LOCAL_SUB_SRC_FILES)\
                        $(PFX_LOCAL_PATH)pfx_android_load_pfx.cpp

LOCAL_MODULE    := pecker_framework
LOCAL_SRC_FILES := $(LOCAL_SUB_SRC_FILES) 
                   
$(call __ndk_info, APP_OPTIM =,$(APP_OPTIM))
$(call __ndk_info, OPTIM_FLAG =,$(OPTIM_FLAG))
LOCAL_CFLAGS += $(OPTIM_FLAG) \
                -DPURE_NATIVE_CODE


ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_CFLAGS += -mfpu=neon
        LOCAL_ARM_NEON  := true 
        $(call __ndk_info,LOCAL_ARM_NEON=,$(LOCAL_ARM_NEON))      
endif # TARGET_ARCH_ABI == armeabi-v7a

LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid -ldl 

include $(BUILD_SHARED_LIBRARY)
###################################################################

#############################################################
$(call __ndk_info, ����ִ�г���)
#ִ�г���
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(PFX_TEST_MK)
include $(LOCAL_PATH)$(APP_MK)
include $(LOCAL_PATH)$(PFX_MK)


LOCAL_SHARED_LIBRARIES := pecker_framework#����������

LOCAL_SUB_SRC_FILES	:=  $(PFX_TEST_LOCAL_SRC_FILES)

LOCAL_MODULE    := PFX_test
LOCAL_SRC_FILES := $(LOCAL_SUB_SRC_FILES) 

$(call __ndk_info, APP_OPTIM =,$(APP_OPTIM))
$(call __ndk_info, OPTIM_FLAG =,$(OPTIM_FLAG))
LOCAL_CFLAGS += $(OPTIM_FLAG) \
                -DPURE_NATIVE_CODE
#LOCAL_LDFLAGS += -Wl,--export-dynamic 

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_CFLAGS += -mfpu=neon
        LOCAL_ARM_NEON  := true 
        $(call __ndk_info,LOCAL_ARM_NEON=,$(LOCAL_ARM_NEON))      
endif # TARGET_ARCH_ABI == armeabi-v7a

LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid -ldl 

$(call __ndk_info, LOCAL_CFLAGS =, $(LOCAL_CFLAGS))

include $(BUILD_SHARED_LIBRARY)
##################################################################
