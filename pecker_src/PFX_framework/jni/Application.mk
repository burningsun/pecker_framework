APP_PLATFORM := android-17
APP_ABI := armeabi-v7a
#APP_ABI := arm64-v8a
#APP_ABI := all
#APP_OPTIM := release 
APP_OPTIM := debug
NDK_TOOLCHAIN_VERSION := 4.9
#LOCAL_ARM_NEON := true
#APP_CFLAGS += -Wreturn-local-addr
#APP_CFLAGS += -Wno-error=format-security
APP_CFLAGS += -w #你妹的，只能去掉所有的警告
#-Wformat-extra-args