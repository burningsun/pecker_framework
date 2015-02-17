PFX_TEST_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_test/
#PFX_DIR_PATH := $(call my-dir)
#NATIVE_MK := native/native.mk
#RENDER_MK := render/render.mk
#include $(PFX_DIR_PATH)/$(NATIVE_MK)
#include $(PFX_DIR_PATH)/$(RENDER_MK)

PFX_TEST_LOCAL_SUB_FILES := 
 


PFX_TEST_LOCAL_SRC_FILES := \
					$(PFX_TEST_LOCAL_PATH)pfx_list_test.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_string_test.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_file_inputdata_cmd.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_bst_test.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_avl_bst_test.cpp \
                    $(PFX_TEST_LOCAL_PATH)pfx_rb_bst_test.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_carray_test.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_stress_test_bst.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_cmatrix_test.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_share_object_test.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_objectid_test.cpp\
					$(PFX_TEST_LOCAL_PATH)pfx_load_image.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_graphics_test.cpp \
					$(PFX_TEST_LOCAL_PATH)main.cpp \
					$(PFX_TEST_LOCAL_PATH)pfx_gles2_displayview_test.cpp \
					$(PFX_TEST_LOCAL_SUB_FILES)
				   
				   #$(PFX_TEST_LOCAL_PATH)androidactivity_gles2_test.cpp\
				   


