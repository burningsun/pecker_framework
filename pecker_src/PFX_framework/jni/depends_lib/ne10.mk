NE10LIB_LOCAL_PATH := $(realpath $(call my-dir)/../../../)/depends_lib/Ne10/

ne10_neonv7_source := \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_abs.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_addc.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_addmat.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_add.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_cross.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_detmat.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_divc.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_div.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_dot.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_identitymat.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_invmat.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_len.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_mla.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_mlac.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulcmatvec.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulc.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulmat.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_mul.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_normalize.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_rsbc.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_setc.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_subc.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_submat.neon.c \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_sub.neon.s \
   $(NE10LIB_LOCAL_PATH)modules/math/NE10_transmat.neon.s \

ne10_sourcev7_files := \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_abs.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_addc.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_addmat.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_add.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_cross.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_detmat.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_divc.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_div.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_dot.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_identitymat.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_invmat.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_len.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mla.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mlac.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulcmatvec.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulc.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulmat.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mul.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_normalize.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_rsbc.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_setc.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_subc.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_submat.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_sub.asm.s \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_transmat.asm.s \

    
    ne10_csource_files := \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_abs.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_addc.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_addmat.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_add.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_cross.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_detmat.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_divc.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_div.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_dot.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_identitymat.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_invmat.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_len.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mla.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mlac.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulcmatvec.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulc.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mulmat.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_mul.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_normalize.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_rsbc.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_setc.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_subc.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_submat.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_sub.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_transmat.c \
    $(NE10LIB_LOCAL_PATH)modules/math/NE10_init_math.c \
    $(NE10LIB_LOCAL_PATH)modules/NE10_init.c \