PFX_GLSL10_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_framework/render/render_system/glsl_10/
PFX_GLSL10_DIR_PATH := $(call my-dir)

PFX_GLSL10_SUB_FILES :=  


PFX_GLSL10_SRC_FILES := \
					$(PFX_GLSL10_LOCAL_PATH)pfx_gles10_shader_source.cpp \
					$(PFX_GLSL10_SUB_FILES) 