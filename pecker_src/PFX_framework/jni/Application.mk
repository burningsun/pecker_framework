$(call __ndk_info, ����Application.mk�ļ�)

APP_PLATFORM := android-17
APP_ABI := armeabi-v7a
#APP_ABI := arm64-v8a
#APP_ABI := all
#RELEASE_OPTIM := release
#DEBUG_OPTIM   := debug 
APP_OPTIM := release
#APP_OPTIM := debug
NDK_TOOLCHAIN_VERSION := 4.9
#LOCAL_ARM_NEON := true
#APP_CFLAGS += -Wreturn-local-addr
#APP_CFLAGS += -Wno-error=format-security
#APP_CFLAGS += -w #���õģ�ֻ��ȥ�����еľ���
#APP_CFLAGS += -Wformat-extra-args
#APP_CFLAGS += -Wformat

OPTIM_FLAG := 

ifeq ($(APP_OPTIM),release)
OPTIM_FLAG += -D_RELEASE
else
OPTIM_FLAG += -D_DEBUG
endif #($(APP_OPTIM),release)
