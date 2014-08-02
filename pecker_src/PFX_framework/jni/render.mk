PFX_RENDER_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_framework/render/

PFX_RENDER_DIR_PATH := $(call my-dir)

RENDER_SYSTEM_MK := render_system.mk

include $(PFX_RENDER_DIR_PATH)/$(RENDER_SYSTEM_MK)


PFX_RENDER_LOCAL_SUB_FILES := $(PFX_RENDER_SYSTEM_SRC_FILES) 


PFX_RENDER_LOCAL_SRC_FILES := \
					$(PFX_RENDER_LOCAL_PATH)pfx_image.cpp \
				   $(PFX_RENDER_LOCAL_SUB_FILES)