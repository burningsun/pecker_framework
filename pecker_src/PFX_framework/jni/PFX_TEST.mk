PFX_TEST_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_test/
#PFX_DIR_PATH := $(call my-dir)
#NATIVE_MK := native/native.mk
#RENDER_MK := render/render.mk
#include $(PFX_DIR_PATH)/$(NATIVE_MK)
#include $(PFX_DIR_PATH)/$(RENDER_MK)

PFX_TEST_LOCAL_SUB_FILES := 
 


PFX_TEST_LOCAL_SRC_FILES := \
					$(PFX_TEST_LOCAL_PATH)pfx_cmatrix_test.cpp \
					$(PFX_TEST_LOCAL_PATH)main.cpp \
				   $(PFX_TEST_LOCAL_SUB_FILES)
				   


