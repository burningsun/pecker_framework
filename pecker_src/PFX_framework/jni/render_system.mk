PFX_RENDER_SYSTEM_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_framework/render/render_system/
PFX_RENDER_SYSTEM_DIR_PATH := $(call my-dir)




OPENGLES2_MK := opengles2.mk
GLSL10_MK := glsl10.mk

include $(PFX_RENDER_SYSTEM_DIR_PATH)/$(OPENGLES2_MK)
include $(PFX_RENDER_SYSTEM_DIR_PATH)/$(GLSL10_MK)

PFX_RENDER_SYSTEM_SUB_FILES := $(PFX_OPENGLES2_SRC_FILES) $(PFX_GLSL10_SRC_FILES) 

PFX_RENDER_SYSTEM_SRC_FILES := \
                    $(PFX_RENDER_SYSTEM_LOCAL_PATH)pfx_texture.cpp \
					$(PFX_RENDER_SYSTEM_SUB_FILES)