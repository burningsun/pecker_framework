
#ifndef PFX_CMATRIX4
#define PFX_CMATRIX4

#include "../data/pfx_cmatrix4.h" 
PECKER_BEGIN

typedef square_matrix_data< float_t, 4 > matrix4f_t;
typedef square_matrix_data< float_t, 3 > matrix3f_t;
typedef square_matrix_data< float_t, 2 > matrix2f_t;
typedef matrix4f_t::vector_t			 vector4f_t;
typedef matrix3f_t::vector_t			 vector3f_t;
typedef matrix2f_t::vector_t			 vector2f_t;

typedef square_matrix_data< sint_t, 4 >	 matrix4i_t;
typedef square_matrix_data< sint_t, 3 >	 matrix3i_t;
typedef square_matrix_data< sint_t, 2 >	 matrix2i_t;
typedef matrix4i_t::vector_t			 vector4i_t;
typedef matrix3i_t::vector_t			 vector3i_t;
typedef matrix2i_t::vector_t			 vector2i_t;


#if (MATRIX_OPTIMIZATION_CONFIG == NO_MATRIX_OPTIMIZATION)
typedef PFX_CMatrix4x4< matrix4f_t > cmatrix4f_method_t;

typedef cmatrix4f_method_t::vector4_t	cvector4f_t;
typedef cmatrix4f_method_t::vector3_t	cvector3f_t;
typedef cmatrix4f_method_t::vector2_t	cvector2f_t;
typedef cmatrix4f_method_t::matrix4_t	cmatrix4f_t;
typedef cmatrix4f_method_t::matrix3_t	cmatrix3f_t;
typedef cmatrix4f_method_t::matrix2_t	cmatrix2f_t;


typedef PFX_CMatrix4x4< matrix4i_t > cmatrix4i_method_t;

typedef cmatrix4i_method_t::vector4_t	cvector4i_t;
typedef cmatrix4i_method_t::vector3_t	cvector3i_t;
typedef cmatrix4i_method_t::vector2_t	cvector2i_t;
typedef cmatrix4i_method_t::matrix4_t	cmatrix4i_t;
typedef cmatrix4i_method_t::matrix3_t	cmatrix3i_t;
typedef cmatrix4i_method_t::matrix2_t	cmatrix2i_t;

#endif // #if (MATRIX_OPTIMIZATION_CONFIG == NO_MATRIX_OPTIMIZATION)
//
#if (MATRIX_OPTIMIZATION_CONFIG == INTEL_SSE)
//
#endif // #if (MATRIX_OPTIMIZATION_CONFIG == ARM_NEON)
//
#if (MATRIX_OPTIMIZATION_CONFIG == ARM_NEON)
//
#endif // #if (MATRIX_OPTIMIZATION_CONFIG == INTEL_SSE)


PECKER_END

#endif//PFX_CMATRIX4


