PFX_RENDER_SYSTEM_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_framework/render/render_system/
PFX_RENDER_SYSTEM_DIR_PATH := $(call my-dir)




OPENGLES2_MK := opengles2.mk

include $(PFX_RENDER_SYSTEM_DIR_PATH)/$(OPENGLES2_MK)

PFX_RENDER_SYSTEM_SUB_FILES := $(PFX_OPENGLES2_SRC_FILES) 

PFX_RENDER_SYSTEM_SRC_FILES := \
					$(PFX_RENDER_SYSTEM_SUB_FILES)