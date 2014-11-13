FT2_LOCAL_PATH := $(realpath $(call my-dir)/../../../)/depends_lib/freetype-2.5.3/

FT2_LOCAL_EXPORT_C_INCLUDES := $(FT2_LOCAL_PATH)include/config \
                    $(FT2_LOCAL_PATH)include \
                    $(FT2_LOCAL_PATH)include/internal \
                    $(FT2_LOCAL_PATH)include/internal/services \
                    $(FT2_LOCAL_PATH)src
                    
FT2_LOCAL_CFLAGS := -DFT2_BUILD_LIBRARY=1 
#-DANDROID_NDK 
                    
                    
FT2LIB_LOCAL_SRC_FILES := \
					$(FT2_LOCAL_PATH)src/base/ftsystem.c \
					$(FT2_LOCAL_PATH)src/base/ftinit.c \
					$(FT2_LOCAL_PATH)src/base/ftdebug.c \
					$(FT2_LOCAL_PATH)src/base/ftbase.c \
					$(FT2_LOCAL_PATH)src/base/ftbbox.c \
					$(FT2_LOCAL_PATH)src/base/ftglyph.c \
					$(FT2_LOCAL_PATH)src/base/ftbdf.c \
					$(FT2_LOCAL_PATH)src/base/ftbitmap.c \
					$(FT2_LOCAL_PATH)src/base/ftcid.c \
					$(FT2_LOCAL_PATH)src/base/ftfstype.c \
					$(FT2_LOCAL_PATH)src/base/ftgasp.c  \
					$(FT2_LOCAL_PATH)src/base/ftgxval.c \
					$(FT2_LOCAL_PATH)src/base/ftlcdfil.c \
					$(FT2_LOCAL_PATH)src/base/ftmm.c  \
					$(FT2_LOCAL_PATH)src/base/ftotval.c \
					$(FT2_LOCAL_PATH)src/base/ftpatent.c \
					$(FT2_LOCAL_PATH)src/base/ftpfr.c  \
					$(FT2_LOCAL_PATH)src/base/ftstroke.c   \
					$(FT2_LOCAL_PATH)src/base/ftsynth.c \
					$(FT2_LOCAL_PATH)src/base/fttype1.c \
					$(FT2_LOCAL_PATH)src/base/ftwinfnt.c \
					$(FT2_LOCAL_PATH)src/base/ftxf86.c \
					$(FT2_LOCAL_PATH)src/bdf/bdf.c \
					$(FT2_LOCAL_PATH)src/cid/type1cid.c \
					$(FT2_LOCAL_PATH)src/cff/cff.c \
					$(FT2_LOCAL_PATH)src/pcf/pcf.c \
					$(FT2_LOCAL_PATH)src/pfr/pfr.c \
					$(FT2_LOCAL_PATH)src/sfnt/sfnt.c \
					$(FT2_LOCAL_PATH)src/truetype/truetype.c \
					$(FT2_LOCAL_PATH)src/type1/type1.c \
					$(FT2_LOCAL_PATH)src/type42/type42.c \
					$(FT2_LOCAL_PATH)src/winfonts/winfnt.c \
					$(FT2_LOCAL_PATH)src/raster/raster.c \
					$(FT2_LOCAL_PATH)src/smooth/smooth.c \
					$(FT2_LOCAL_PATH)src/autofit/autofit.c \
					$(FT2_LOCAL_PATH)src/cache/ftcache.c \
					$(FT2_LOCAL_PATH)src/gzip/ftgzip.c \
					$(FT2_LOCAL_PATH)src/lzw/ftlzw.c \
					$(FT2_LOCAL_PATH)src/bzip2/ftbzip2.c \
					$(FT2_LOCAL_PATH)src/gxvalid/gxvalid.c \
					$(FT2_LOCAL_PATH)src/otvalid/otvalid.c \
					$(FT2_LOCAL_PATH)src/psaux/psaux.c \
					$(FT2_LOCAL_PATH)src/pshinter/pshinter.c \
					$(FT2_LOCAL_PATH)src/psnames/psnames.c \
					 



