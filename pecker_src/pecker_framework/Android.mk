LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/native/native.mk
LOCAL_SUB_FILES := $(NATIVE_SRC_FILES)
include $(CLEAR_VARS)


LOCAL_MODULE    := pecker_framework_test
### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES := \
				   PeckerObject.cpp \
				   $(LOCAL_SUB_FILES) \
				   btst_tree_test.cpp \
				   pecker_framework_test.cpp

LOCAL_LDLIBS_RELEASE := -lEGL -lGLESv2 -llog -lz -landroid
LOCAL_LDLIBS := $(LOCAL_LDLIBS_RELEASE)

include $(BUILD_SHARED_LIBRARY)
