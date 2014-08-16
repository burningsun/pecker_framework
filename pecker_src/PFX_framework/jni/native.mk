PFX_NATIVE_LOCAL_PATH := $(realpath $(call my-dir)/../../)/pecker_framework/native/

PFX_NATIVE_LOCAL_SUB_FILES :=  


PFX_NATIVE_LOCAL_SRC_FILES := \
					$(PFX_NATIVE_LOCAL_PATH)pfx_file_io.cpp \
					$(PFX_NATIVE_LOCAL_PATH)pecker_stream.cpp \
					$(PFX_NATIVE_LOCAL_PATH)pecker_tick.cpp \
					$(PFX_NATIVE_LOCAL_PATH)syn_lock.cpp \
					$(PFX_NATIVE_LOCAL_PATH)socket_param.cpp \
					$(PFX_NATIVE_LOCAL_PATH)udp_socket.cpp \
					$(PFX_NATIVE_LOCAL_PATH)asyn_udp_comm.cpp \
					$(PFX_NATIVE_LOCAL_PATH)android_native_form.cpp \
					$(PFX_NATIVE_LOCAL_PATH)pfx_resource_reader_android.cpp \
				   $(PFX_NATIVE_LOCAL_SUB_FILES)