PFX_OPENGLES2_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_framework/render/render_system/opengles2/
PFX_OPENGLES2_DIR_PATH := $(call my-dir)

PFX_OPENGLES2_SUB_FILES :=  


#OPENGLES2_MK := opengles2/opengles2.mk
#include $(PFX_OPENGLES2_DIR_PATH)/$(OPENGLES2_MK)

#你妹的pfx_framebuffer_object_gles.cpp名字太长，开debug模式直接编译器老爆莫名其妙错误
#将pfx_framebuffer_object_gles.cpp改pfx_framebuffer_obj_gles.cpp错误排除
PFX_OPENGLES2_SRC_FILES := \
					$(PFX_OPENGLES2_LOCAL_PATH)pfx_buffer_object_gles.cpp \
					$(PFX_OPENGLES2_LOCAL_PATH)pfx_shader_program_gles.cpp \
					$(PFX_OPENGLES2_LOCAL_PATH)pfx_texture_gles.cpp \
					$(PFX_OPENGLES2_LOCAL_PATH)pfx_framebuffer_obj_gles.cpp \
					$(PFX_OPENGLES2_LOCAL_PATH)pfx_render_state_gles.cpp \
					$(PFX_OPENGLES2_LOCAL_PATH)pfx_display_context_gles.cpp \
					$(PFX_OPENGLES2_SUB_FILES)

					