ZLIB_LOCAL_PATH := $(realpath $(call my-dir)/../../../)/depends_lib/zlib-1.2.8/

ZLIB_LOCAL_SRC_FILES := \
					$(ZLIB_LOCAL_PATH)adler32.c \
					$(ZLIB_LOCAL_PATH)compress.c \
					$(ZLIB_LOCAL_PATH)crc32.c \
					$(ZLIB_LOCAL_PATH)deflate.c \
					$(ZLIB_LOCAL_PATH)infback.c \
					$(ZLIB_LOCAL_PATH)inffast.c \
					$(ZLIB_LOCAL_PATH)inflate.c \
					$(ZLIB_LOCAL_PATH)inftrees.c \
					$(ZLIB_LOCAL_PATH)trees.c \
					$(ZLIB_LOCAL_PATH)uncompr.c \
					$(ZLIB_LOCAL_PATH)zutil.c \



