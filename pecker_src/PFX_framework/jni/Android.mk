LOCAL_PATH :=  $(call my-dir)#$(realpath $(call my-dir)/../../)
PFX_MK := /PFX.mk
PFX_TEST_MK := /PFX_TEST.mk
ZLIB_MK := /depends_lib/zlib.mk
PNGLIB_MK := /depends_lib/pnglib.mk
NE10_MK :=  /depends_lib/ne10.mk

#使用arm_neon.h貌似有bug，而且neon支持不全，
#arm的ne10开源库用全汇编来写
#从汇编代码看，编译器需满足：1、r0,r1,r2通用寄存器代表
# r0第一个参数和返回值，r1第二个参数，r2第三个参数
#注意：
# 从汇编代码中的函数看，没对寄存器做压栈处理，退出函数的时候没做出栈处理，
# NEON寄存器也没类似的操作，不可重入

#NE算术库
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
#LOCAL_ARM_NEON  := true #尼玛android的SB文档，这个标志蛋蛋用都没 
endif

#NE10无法在ARMV8 AArch64交叉编译器下编译

#跪了ARMV8 AArch64交叉编译器压根就没不认-mfpu=neon -mfpu=neon-fp-armv8
#只能等更新了,下面是GCC文档的描述
#Feature modifiers used with ‘-march’ and ‘-mcpu’ can be one the following:
#‘crc’ Enable CRC extension.
#‘crypto’ Enable Crypto extension. This implies Advanced SIMD is enabled.
#‘fp’ Enable floating-point instructions.
#‘simd’ Enable Advanced SIMD instructions. This implies floating-point instructions
#are enabled. This is the default for all current possible values for options
#‘-march’ and ‘-mcpu=’.
#到arm官网看了下，新的AArch64架构去掉了neon可选
#Floating Point and NEON
#The Floating Point and NEON instructions are included in the main instruction set (rather than targeting a
#coprocessor as in earlier architectures). This means that these instructions set the core condition flags
#(NZCV) directly rather than having a separate set of status flags. This makes mixing control and data flow
#much easier when using the NEON/FP register bank.
#插，ARM的处理器文档还提到AArch64结构的处理器将浮点数和neon的指令集跟主指令集合在一个单元那，
#用主指令集的可以直接使用neon指令，妈蛋，所以原来armv7写的neon汇编直接跪了

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
#LOCAL_CFLAGS += -mcpu=neon
#LOCAL_CFLAGS += -mfpu=neon-fp-armv8
#LOCAL_SRC_FILES += $(ne10_neon_source)
#LOCAL_ARM_NEON  := true #尼玛android的SB文档，这个标志蛋蛋用都没 
endif




LOCAL_ARM_MODE := arm

include $(BUILD_STATIC_LIBRARY)


#编译依赖库
include $(CLEAR_VARS)
include $(LOCAL_PATH)$(ZLIB_MK)   #zlib
include $(LOCAL_PATH)$(PNGLIB_MK) #pnglib
LOCAL_STATIC_LIBRARIES := libNE10 #附加依赖库

LOCAL_MODULE    := PFX_DEPENDS
LOCAL_SRC_FILES := $(ZLIB_LOCAL_SRC_FILES)  $(PNG_LOCAL_SRC_FILES)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
        LOCAL_ARM_NEON  := true       
endif # TARGET_ARCH_ABI == armeabi-v7a

#插，gcc 4.9不能使用64bit arm的neon指令
#ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
#        LOCAL_ARM_NEON  := true
#endif # TARGET_ARCH_ABI == arm64-v8a


LOCAL_LDLIBS    := 


include $(BUILD_STATIC_LIBRARY)

#编译图形库
include $(CLEAR_VARS)
#include $(LOCAL_PATH)$(ZLIB_MK)
#include $(LOCAL_PATH)$(PNGLIB_MK)
include $(LOCAL_PATH)$(PFX_MK)
include $(LOCAL_PATH)$(PFX_TEST_MK)

LOCAL_STATIC_LIBRARIES := PFX_DEPENDS #附加依赖库
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
#你妹的android自己搞了个pthread还各种函数阉割
#-lpthread
#LOCAL_LDLIBS_RELEASE := -lEGL -lGLESv2 -llog -lz -landroid

include $(BUILD_SHARED_LIBRARY)



