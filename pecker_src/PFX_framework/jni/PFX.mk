PFX_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_framework/
PFX_DIR_PATH := $(call my-dir)
MATH_MK := math.mk
NATIVE_MK := native.mk
RENDER_MK := render.mk
include $(PFX_DIR_PATH)/$(NATIVE_MK)
include $(PFX_DIR_PATH)/$(RENDER_MK)
include $(PFX_DIR_PATH)/$(MATH_MK)

PFX_LOCAL_SUB_FILES := $(PFX_MATH_LOCAL_SRC_FILES)\
                        $(PFX_NATIVE_LOCAL_SRC_FILES)\
						$(PFX_RENDER_LOCAL_SRC_FILES)
 
PFX_LOCAL_INIT_SRC_FILES := \
					$(PFX_LOCAL_PATH)pfx_defines.cpp \
					$(PFX_LOCAL_PATH)pfx_api_info.cpp \
					$(PFX_LOCAL_PATH)pfx_hal_info.cpp \
					$(PFX_LOCAL_PATH)pfx_cpu_arm.cpp \
					$(PFX_LOCAL_PATH)pfx_hal_info_gles2.cpp

PFX_LOCAL_SRC_FILES := \
					$(PFX_LOCAL_INIT_SRC_FILES) \
				   $(PFX_LOCAL_SUB_FILES)
				   


