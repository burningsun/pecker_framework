/*
 * cvector_alg.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CVECTOR_ALG_H_
#define		PFX_CVECTOR_ALG_H_

#include "../pfx_defines.h"

PECKER_BEGIN

typedef enum enumDIMENSION_NAME
{
	DIMENSION_X = 0,
	DIMENSION_Y,
	DIMENSION_Z,
	DIMENSION_W,

	DIMENSION_OTHER
}PFX_DIMENSION_NAME_t;

typedef enum enumFLOAT_PRECISION_QUALIFER
{
	LOW_PRECISION_QUALIFER = 0,
	MID_PRECISION_QUALIFER,
	HIGH_PRECISION_QUALIFER,
	VARY_HIGH_PRECISION_QUALIFER,

	PFX_FLOAT_PRECISION_QUALIFER_COUNT
}PFX_FLOAT_PRECISION_QUALIFER_t;

#define LOW_PRECISION_QUALIFER_VAL (20)
#define MID_PRECISION_QUALIFER_VAL (10)
#define HIGH_PRECISION_QUALIFER_VAL (5)
#define VARY_HIGH_PRECISION_QUALIFER_VAL (1)


PFX_INLINE u32_t FLOAT_PRECISION_QUALIFIER (PFX_FLOAT_PRECISION_QUALIFER_t PQ)
{
	static const u32_t precision_qualifer_table [] = 
	{LOW_PRECISION_QUALIFER_VAL,MID_PRECISION_QUALIFER_VAL,HIGH_PRECISION_QUALIFER_VAL,VARY_HIGH_PRECISION_QUALIFER_VAL,0};
	return precision_qualifer_table[PQ];
};



template < class dim_value, const enum_int_t optional_type = 0 >
struct PFX_DATA_TEMPALE_API vector_dim_op_alg
{
	typedef dim_value			dim_t;

	static PFX_INLINE boolean_t equals (dim_t X, dim_t Y, u32_t delta);

	static PFX_INLINE dim_t abs (dim_t val);

	static PFX_INLINE dim_t add (dim_t a,dim_t b);
	static PFX_INLINE dim_t& add_replace (dim_t& a,dim_t b);

	static PFX_INLINE dim_t sub (dim_t a,dim_t b);
	static PFX_INLINE dim_t& sub_replace (dim_t& a,dim_t b);


	static PFX_INLINE dim_t mul (dim_t a,dim_t b);
	static PFX_INLINE dim_t& mul_replace (dim_t& a,dim_t b);

	static PFX_INLINE dim_t div (dim_t a,dim_t b);
	static PFX_INLINE dim_t& div_replace (dim_t& a,dim_t b);

	static PFX_INLINE dim_t sin (dim_t rad);
	static PFX_INLINE dim_t cos (dim_t rad);
	static PFX_INLINE dim_t tan (dim_t rad);
	static PFX_INLINE dim_t acos (dim_t rad);

	static PFX_INLINE void sincos (dim_t rad,
		dim_t& sin_val,
		dim_t &cos_val);

	static PFX_INLINE dim_t sqrt (dim_t val);
};

template < class dim_value, const enum_int_t optional_type = 0 >
struct PFX_DATA_TEMPALE_API vector_dim_op_traits
{
	typedef typename vector_dim_op_alg < dim_value, optional_type > dim_alg_t;
	typedef typename dim_alg_t::dim_t															dim_t;
	typedef typename dim_alg_t::vector_t														vector_t;
};


template < class vector_type, const enum_int_t optional_type = 0 >
struct PFX_DATA_TEMPALE_API vector_base_op_alg
{
	typedef typename vector_dim_op_traits < vector_type::dim_t, optional_type >::dim_alg_t		dim_alg_t;
	typedef typename dim_alg_t::dim_t					dim_t;
	typedef typename vector_type::vector_t			vector_t;
	typedef typename vector_t*									matrix_t;
	typedef typename vector_t**								matrix_ex_t;

	static PFX_INLINE usize_t vector_dim_count ();

	static PFX_INLINE dim_t&					vector_at	(vector_t&			__vector, uindex_t dim_index);
	static PFX_INLINE dim_t&					matrix_at	(matrix_t&			__matrix, uindex_t i,  uindex_t j);
	static PFX_INLINE dim_t&					matrix_at	(matrix_ex_t&	__matrix, uindex_t i, uindex_t j);
	static PFX_INLINE vector_t&				matrix_at	(matrix_t&			__matrix, uindex_t i, vector_t& PARAM_INOUT vector_out);
	static PFX_INLINE vector_t&				matrix_at	(matrix_ex_t&	__matrix, uindex_t i, vector_t& PARAM_INOUT vector_out);
	static PFX_INLINE vector_t*				matrix_at	(matrix_t&			__matrix, uindex_t i);
	static PFX_INLINE vector_t*&			matrix_at	(matrix_ex_t&	__matrix, uindex_t i);

	static PFX_INLINE vector_t* const&	matrix_at_	(matrix_ex_t&	__matrix, uindex_t i);

	static PFX_INLINE const dim_t&		vector_at_const	(const vector_t&			__vector, uindex_t dim_index);
	static PFX_INLINE const dim_t&		matrix_at_const	(const matrix_t&			__matrix, uindex_t i, uindex_t j);
	static PFX_INLINE const dim_t&		matrix_at_const	(const matrix_ex_t&	__matrix, uindex_t i, uindex_t j);
	static PFX_INLINE const vector_t&	matrix_at_const	(const matrix_t&			__matrix, uindex_t i, vector_t& PARAM_INOUT vector_out);
	static PFX_INLINE const vector_t&	matrix_at_const	(const matrix_ex_t&	__matrix, uindex_t i, vector_t& PARAM_INOUT vector_out);
	static PFX_INLINE const vector_t*	matrix_at_const	(matrix_t&			__matrix, uindex_t i);
	static PFX_INLINE const vector_t* const&	matrix_at_const	(matrix_ex_t&	__matrix, uindex_t i);

	static PFX_INLINE vector_t&				init_vector (vector_t& __vector, const dim_t __val);
	static PFX_INLINE vector_t&				init_vector (vector_t& __vector, const dim_t __val, usize_t dim_count);

	static PFX_INLINE matrix_ex_t&		init_matrix (matrix_ex_t&	__matrix, const matrix_t& s_matrix, usize_t vector_count);
	static PFX_INLINE matrix_ex_t&		init_matrix (matrix_ex_t&	__matrix, const dim_t __val , usize_t vector_count);
	static PFX_INLINE matrix_t&				init_matrix (matrix_t&		__matrix, const dim_t __val , usize_t vector_count);

	static PFX_INLINE matrix_ex_t&		init_matrix (matrix_ex_t& __matrix, const dim_t __val , 
																					usize_t  dim_count, usize_t vector_count);
	
	static PFX_INLINE dim_t&					vector_dot			(const vector_t& __vec_a, const vector_t& __vec__b, 
																								usize_t dim_count, dim_t& PARAM_INOUT __dim_result);

	static PFX_INLINE vector_t&				vector3_cross	(const vector_t& __vec_a, const vector_t& __vec_b, 
																								vector_t& PARAM_INOUT __vec_result);

	static PFX_INLINE dim_t&					vector_dot			(usize_t dim_count, 
																								const matrix_t& __matrix_a, uindex_t i_index, 
																								const matrix_t& __matrix_b, uindex_t j_index, 
																								dim_t& PARAM_INOUT __dim_result);

	static PFX_INLINE dim_t&					vector_dot			(usize_t dim_count, 
																								const matrix_ex_t& __matrix_a, uindex_t i_index,
																								const matrix_ex_t& __matrix_b, uindex_t j_index, 
																								dim_t& PARAM_INOUT __dim_result);

	static PFX_INLINE vector_t&				vector_mul		(const vector_t& __vec_a, const dim_t& __dim, 
																								vector_t& PARAM_INOUT __vec_result);

	static PFX_INLINE vector_t&				vector_div			(const vector_t& __vec_a, const dim_t& __dim, 
																								vector_t& PARAM_INOUT __vec_result);

	static PFX_INLINE vector_t&				vector_mul		(const vector_t& __vec_a, const dim_t& __dim, 
																								usize_t dim_count, vector_t& PARAM_INOUT __vec_result);

	static PFX_INLINE vector_t&				vector_div			(const vector_t& __vec_a, const dim_t& __dim, 
																								usize_t dim_count, vector_t& PARAM_INOUT __vec_result);

	static PFX_INLINE vector_t&				vector_add		(const vector_t& __vec_a, const vector_t& __vec_b, 
																								usize_t dim_count, vector_t& PARAM_INOUT __vec_result);

	static PFX_INLINE vector_t&				vector_add		(const vector_t& __vec_a, const vector_t& __vec_b, 
																								vector_t& PARAM_INOUT __vec_result);

	static PFX_INLINE vector_t&				vector_sub		(const vector_t& __vec_a, const vector_t& __vec_b, 
																								usize_t dim_count, vector_t& PARAM_INOUT __vec_result);

	static PFX_INLINE vector_t&				vector_sub		(const vector_t& __vec_a, const vector_t& __vec_b, 
																								vector_t& PARAM_INOUT __vec_result);

	// 直接相乘法
	static PFX_INLINE matrix_t& matrix_mul_matrix_direct (const matrix_t& __mat_a, 
																								usize_t ai_count, usize_t aj_count, usize_t bj_count, 
																								const matrix_t& __mat_b, 
																								matrix_t&	PARAM_INOUT __mat_result);

	static PFX_INLINE matrix_t& matrix_mul_value_direct (const matrix_t& __mat_a, 
																								usize_t i_count, usize_t j_count,
																								const dim_t& __dim, 
																								matrix_t&	PARAM_INOUT __mat_result);

	static PFX_INLINE matrix_t& matrix_div_value_direct (const matrix_t& __mat_a, 
																								usize_t i_count, usize_t j_count,
																								const dim_t& __dim, 
																								matrix_t&	PARAM_INOUT __mat_result);

	//////////////////////////////////////////////////////////////////////////
	static PFX_INLINE matrix_ex_t& matrix_mul_matrix_direct (const matrix_ex_t& __mat_a, 
																												usize_t ai_count, usize_t aj_count, usize_t bj_count, 
																												const matrix_ex_t& __mat_b, 
																												matrix_ex_t&	PARAM_INOUT __mat_result);

	static PFX_INLINE matrix_ex_t& matrix_mul_value_direct (const matrix_ex_t& __mat_a, 
																												usize_t i_count, usize_t j_count,
																												const dim_t& __dim, 
																												matrix_ex_t&	PARAM_INOUT __mat_result);

	static PFX_INLINE matrix_ex_t& matrix_div_value_direct (const matrix_ex_t& __mat_a, 
																												usize_t i_count, usize_t j_count,
																												const dim_t& __dim, 
																												matrix_ex_t&	PARAM_INOUT __mat_result);
};

template < class vector_type, const enum_int_t optional_type = 0 >
struct PFX_DATA_TEMPALE_API vector_base_op_traits
{
	typedef typename vector_base_op_alg < vector_type, optional_type > vec_alg_t;
	typedef typename vec_alg_t::dim_t																dim_t;
	typedef typename vec_alg_t::vector_t															vector_t;
	typedef typename vec_alg_t::matrix_t															matrix_t;
	typedef typename vec_alg_t::matrix_ex_t														matrix_ex_t
};

template < class square_matrix_type, const enum_int_t optional_type = 0 >
struct square_matrix_base_op_alg
{
	
	typedef typename square_matrix_type::vec_alg_t			vec_alg_t;
	typedef typename vec_alg_t::dim_alg_t								dim_alg_t;
	typedef typename square_matrix_type::dim_t				dim_t;
	typedef typename square_matrix_type::vector_t			vector_t;
	typedef typename square_matrix_type::matrix_t			matrix_t;
	typedef typename square_matrix_type::matrix_ex_t		matrix_ex_t;
	
	typedef class clr_mul_factor
	{
		friend class square_matrix_base_op_alg < square_matrix_type, optional_type >;
	protected:
		dim_t							m_factor;
		uindex_t			m_index;
	}clr_mul_factor_t;

	typedef class cw_buffer
	{
		friend class square_matrix_base_op_alg < square_matrix_type, optional_type >;
	protected:
		typedef dim_t* __vector_t;

		dim_t*			m_dims_instance;
		__vector_t*	m_vectors_prt;

	}cw_buffer_t;

	static PFX_INLINE cw_buffer_t new_cw_buffer (usize_t square_dim);
	static PFX_INLINE result_t release_cw_buffer ();
protected:
	static PFX_INLINE __vector_t* get_cw_matrix (cw_buffer_t& __cw_buf, 
		uindex_t step_index, uindex_t mat_index);
public:

	static PFX_INLINE usize_t get_dim_count ();

	static PFX_INLINE matrix_t& Indentify_matrix (usize_t dim_count,
		matrix_t& __mat, dim_t val, dim_t null_val);

	static PFX_INLINE matrix_ex_t& Indentify_matrix (usize_t dim_count,
		matrix_ex_t& __mat, dim_t val, dim_t null_val);

	static PFX_INLINE matrix_t& transpose_matrix (usize_t dim_count,
		const matrix_t& __mat, 
		matrix_t& __mat_reslut, dim_t val);

	static PFX_INLINE matrix_ex_t& transpose_matrix (usize_t dim_count,
		const matrix_ex_t& __mat, 
		matrix_ex_t& __mat_reslut, dim_t val);


	// 方阵乘法
	static PFX_INLINE vector_t& vector4_mul(const vector_t& __mat_a, const matrix_t& __mat_b,  
																				vector_t&	PARAM_INOUT __mat_result,
																				vector_t* PARAM_INOUT __tempbuffer = NULL,
																				u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE matrix_t& matrix2x2_mul (const matrix_t& __mat_a, const matrix_t& __mat_b,  
																						matrix_t&	PARAM_INOUT __mat_result,
																						cw_buffer_t* PARAM_INOUT __tempbuffer = NULL,
																						u32_t delta = MID_PRECISION_QUALIFER_VAL);
	static PFX_INLINE matrix_t& matrix3x3_mul(const matrix_t& __mat_a, const matrix_t& __mat_b,  
																						matrix_t&	PARAM_INOUT __mat_result,
																						cw_buffer_t* PARAM_INOUT __tempbuffer = NULL,
																						u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE matrix_t& matrixNxN_mul (const matrix_t& __mat_a, const matrix_t& __mat_b,  
																						matrix_t&	PARAM_INOUT __mat_result,
																						cw_buffer_t* PARAM_INOUT __tempbuffer,
																						u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE matrix_ex_t& matrix2x2_mul (const matrix_ex_t& __mat_a, const matrix_ex_t& __mat_b,  
																							matrix_ex_t&	PARAM_INOUT __mat_result,
																							cw_buffer_t* PARAM_INOUT __tempbuffer = NULL,
																							u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE matrix_ex_t& matrix3x3_mul (const matrix_ex_t& __mat_a, const matrix_ex_t& __mat_b,  
																							matrix_ex_t&	PARAM_INOUT __mat_result,
																							cw_buffer_t* PARAM_INOUT __tempbuffer = NULL,
																							u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE matrix_ex_t& matrixNxN_mul (const matrix_ex_t& __mat_a, const matrix_ex_t& __mat_b,  
																							matrix_ex_t&	PARAM_INOUT __mat_result,
																							cw_buffer_t* PARAM_INOUT __tempbuffer = NULL,
																							u32_t delta = MID_PRECISION_QUALIFER_VAL);
protected:
	static PFX_INLINE matrix_ex_t& matrixNxN_mul (usize_t dim_count, 
																							const matrix_ex_t& __mat_a, const matrix_ex_t& __mat_b,  
																							matrix_ex_t&	PARAM_INOUT __mat_result,
																							cw_buffer_t* PARAM_INOUT __tempbuffer,
																							u32_t delta);

public:
	PFX_INLINE void swap_line (matrix_ex_t& PARAM_INOUT __matrix,  
																	uindex_t i, uindex_t j);

	PFX_INLINE dim_t clear_oneline (matrix_ex_t& PARAM_INOUT __matrix,  
																	uindex_t test_line, uindex_t clear_line, 
																	uindex_t line_index, usize_t dim_count);

	PFX_INLINE void clear_oneline_same (matrix_ex_t& PARAM_INOUT __matrix,  
																						uindex_t test_line, 
																						uindex_t clear_line, dim_t mul_factor, 
																						usize_t dim_count);

	PFX_INLINE void restore_oneline (matrix_ex_t& PARAM_INOUT __matrix,  
																				uindex_t restore_line,uindex_t line_index,
																				dim_t mul_factor, usize_t dim_count);

	PFX_INLINE usize_t rev_clear_oneline (matrix_ex_t& PARAM_INOUT __matrix,  
																				uindex_t clear_line,	
																				usize_t dim_count, 
																				clr_mul_factor_t* mul_factor, u32_t delta);

	PFX_INLINE void rev_clear_oneline_same (matrix_ex_t& PARAM_INOUT __matrix,  
																				uindex_t clear_line,
																				usize_t dim_count, 
																				const clr_mul_factor_t* PARAM_IN mul_factor);


	PFX_INLINE void restore_oneline (matrix_ex_t& PARAM_INOUT __matrix,  
																				uindex_t restore_line, uindex_t line_index,
																				dim_t mul_factor, usize_t dim_count,
																				uindex_t except_j);


	PFX_INLINE dim_t clear_oneline (matrix_ex_t& PARAM_INOUT __matrix,  
																				uindex_t test_line, uindex_t clear_line,
																				uindex_t line_index, usize_t dim_count,
																				uindex_t except_j);


	PFX_INLINE void clear_oneline_same (matrix_ex_t& PARAM_INOUT __matrix,  
																		uindex_t test_line, usize_t dim_count);

	PFX_INLINE uindex_t find_test_line (matrix_ex_t& PARAM_INOUT __matrix,  
																		uindex_t line_index, usize_t dim_count);

public:
	// 求行列式的值和行列式
	// 对角线法求解
	static PFX_INLINE dim_t matrix1x1_det (const matrix_ex_t& PARAM_INOUT __mat);

	static PFX_INLINE dim_t matrix2x2_det (const matrix_ex_t& PARAM_INOUT __mat);
	
	static PFX_INLINE dim_t matrix3x3_det (const matrix_ex_t& PARAM_INOUT __mat);

	static PFX_INLINE dim_t matrix1x1_algebraic_cofactor_det (const matrix_ex_t& PARAM_INOUT __mat);

	static PFX_INLINE dim_t matrix2x2_algebraic_cofactor_det (const matrix_ex_t& PARAM_INOUT __mat, 
																												usize_t x, usize_t y);
	static PFX_INLINE dim_t matrix3x3_algebraic_cofactor_det (const matrix_ex_t& PARAM_INOUT __mat, 
																												usize_t x, usize_t y);
	static PFX_INLINE dim_t matrix4x4_algebraic_cofactor_det (const matrix_ex_t& PARAM_INOUT __mat, 
																												usize_t x, usize_t y);

	// 高斯消元法
	static PFX_INLINE dim_t matrix_det (matrix_ex_t& PARAM_INOUT __mat_replace, 
		usize_t dim_count,
		u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE dim_t matrix_algebraic_cofactor_det (matrix_ex_t& PARAM_INOUT __mat_replace, 
		usize_t dim_count, 
		usize_t x, usize_t y,
		u32_t delta = MID_PRECISION_QUALIFER_VAL);
	//
	// 求秩 （方阵）
	static PFX_INLINE usize_t matrix_rank (matrix_ex_t& PARAM_INOUT __mat_replace, 
		usize_t dim_count, u32_t delta = MID_PRECISION_QUALIFER_VAL);

	// 求行列式的值和行列式的代数余子式的值
	// 全主元高斯消元法
	static PFX_INLINE matrix_ex_t* inverse_matrix_for_3d (const matrix_ex_t& PARAM_INOUT __mat_a, 
		matrix_ex_t& PARAM_INOUT __mat_inverse,
		u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE matrix_t* inverse_matrix_for_3d (const matrix_t& PARAM_INOUT __mat_a, 
		matrix_t& PARAM_INOUT __mat_inverse,
		u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE matrix_ex_t* inverse_matrix (matrix_ex_t& PARAM_INOUT __mat_replace,
		usize_t dim_count, 
		matrix_ex_t& PARAM_INOUT __mat_inverse,
		clr_mul_factor_t* mul_factor_ptr, 
		u32_t delta = MID_PRECISION_QUALIFER_VAL);
	//

};







//////////////////////////////////////////////////////////////////////////////






PECKER_END

#endif			//PFX_CVECTOR_ALG_H_
