LOCAL_PATH :=  $(call my-dir)#$(realpath $(call my-dir)/../../)
PFX_MK := /PFX.mk
PFX_TEST_MK := /PFX_TEST.mk
ZLIB_MK := /depends_lib/zlib.mk
PNGLIB_MK := /depends_lib/pnglib.mk
NE10_MK :=  /depends_lib/ne10.mk

#ʹ��arm_neon.hò����bug������neon֧�ֲ�ȫ��
#arm��ne10��Դ����ȫ�����д
#�ӻ����뿴�������������㣺1��r0,r1,r2ͨ�üĴ�������
# r0��һ�������ͷ���ֵ��r1�ڶ���������r2����������
#ע�⣺
# �ӻ������еĺ�������û�ԼĴ�����ѹջ�����˳�������ʱ��û����ջ����
# NEON�Ĵ���Ҳû���ƵĲ�������������

#NE������
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(NE10_MK)   #NE10

LOCAL_MODULE_TAGS := eng
LOCAL_MODULE := libNE10

LOCAL_C_INCLUDES :=     $(NE10LIB_LOCAL_PATH)/common/ \
                        $(NE10LIB_LOCAL_PATH)/inc \
                        $(NE10LIB_LOCAL_PATH)/modules/math \
                        
LOCAL_SRC_FILES :=  \
   $(ne10_csource_files)
   # $(ne10_source_files)
LOCAL_CPP_EXTENSION := .cc
LOCAL_CFLAGS := -D_ARM_ASSEM_

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_CFLAGS += -mfpu=neon
LOCAL_SRC_FILES += $(ne10_sourcev7_files) $(ne10_neonv7_source)
#LOCAL_ARM_NEON  := true #����android��SB�ĵ��������־�����ö�û 
endif

#NE10�޷���ARMV8 AArch64����������±���

#����ARMV8 AArch64���������ѹ����û����-mfpu=neon -mfpu=neon-fp-armv8
#ֻ�ܵȸ�����,������GCC�ĵ�������
#Feature modifiers used with ��-march�� and ��-mcpu�� can be one the following:
#��crc�� Enable CRC extension.
#��crypto�� Enable Crypto extension. This implies Advanced SIMD is enabled.
#��fp�� Enable floating-point instructions.
#��simd�� Enable Advanced SIMD instructions. This implies floating-point instructions
#are enabled. This is the default for all current possible values for options
#��-march�� and ��-mcpu=��.
#��arm���������£��µ�AArch64�ܹ�ȥ����neon��ѡ
#Floating Point and NEON
#The Floating Point and NEON instructions are included in the main instruction set (rather than targeting a
#coprocessor as in earlier architectures). This means that these instructions set the core condition flags
#(NZCV) directly rather than having a separate set of status flags. This makes mixing control and data flow
#much easier when using the NEON/FP register bank.
#�壬ARM�Ĵ������ĵ����ᵽAArch64�ṹ�Ĵ���������������neon��ָ�����ָ�����һ����Ԫ�ǣ�
#����ָ��Ŀ���ֱ��ʹ��neonָ��走������ԭ��armv7д��neon���ֱ�ӹ���

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
#LOCAL_CFLAGS += -mcpu=neon
#LOCAL_CFLAGS += -mfpu=neon-fp-armv8
#LOCAL_SRC_FILES += $(ne10_neon_source)
#LOCAL_ARM_NEON  := true #����android��SB�ĵ��������־�����ö�û 
endif




LOCAL_ARM_MODE := arm

include $(BUILD_STATIC_LIBRARY)


#����������
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(ZLIB_MK)   #zlib
include $(LOCAL_PATH)$(PNGLIB_MK) #pnglib
LOCAL_STATIC_LIBRARIES := libNE10 #����������

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


LOCAL_MODULE    := PFX_framework
LOCAL_SRC_FILES := $(LOCAL_SUB_SRC_FILES)# android_native_app_glue.cpp PFX_framework.cpp





#LOCAL_ARM_MODE := arm

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_CFLAGS += -mfpu=neon
        LOCAL_ARM_NEON  := true  
 #       LOCAL_CFLAGS := -DHAVE_NEON=1      
endif # TARGET_ARCH_ABI == armeabi-v7a

#ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
#        LOCAL_ARM_NEON  := true
#endif # TARGET_ARCH_ABI == arm64-v8a


LOCAL_LDLIBS    := -llog -lEGL -lGLESv1_CM -lGLESv2 -landroid 
#���õ�android�Լ����˸�pthread�����ֺ����˸�
#-lpthread
#LOCAL_LDLIBS_RELEASE := -lEGL -lGLESv2 -llog -lz -landroid

include $(BUILD_SHARED_LIBRARY)



