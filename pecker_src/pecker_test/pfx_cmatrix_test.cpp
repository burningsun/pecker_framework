/*
 * pfx_matrix_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/data/pfx_cmatrix_codes.h"

USING_PECKER_SDK

template < class vec_t, const usize__t dim_v >
void print_vec (const vec_t* vec_ptr)
{
	if (null == vec_ptr)
	{
		PECKER_LOG_ ("null vec\n");
	}
	else
	{
		PECKER_LOG_ ("vec = [")
			for (uindex_t i=0; i<dim_v; ++i)
			{
					float_t x = (*vec_ptr)[i];
					PECKER_LOG_ (" %lf ",x);
			}
			PECKER_LOG_("]\n");
	}
};

template < class mat_t, const usize__t dim_v >
void print_mat (const mat_t* mat_ptr)
{
	if (null == mat_ptr)
	{
		PECKER_LOG_ ("null mat\n");
	}
	else
	{
		PECKER_LOG_ ("mat = [\n")
			for (uindex_t i=0; i<dim_v; ++i)
			{
				for (uindex_t j=0; j<dim_v; ++j)
				{
					float_t x = (*(*mat_ptr)[i])[j];
					PECKER_LOG_ (" %lf ",x);
				}
				PECKER_LOG_("\n");
			}
			PECKER_LOG_("]\n");
	}
};

template < class mat_t,const usize__t dim_v >
void print_mat_alg (const mat_t* mat_ptr,usize__t x,usize__t y)
{
	if (null == mat_ptr)
	{
		PECKER_LOG_ ("null mat\n");
	}
	else
	{
		PECKER_LOG_ ("mat = [\n")
			for (uindex_t i=0; i<dim_v; ++i)
			{
				if (x == i){continue;}
				for (uindex_t j=0; j<dim_v; ++j)
				{
					if (y == j){continue;}
					float_t x = (*(*mat_ptr)[i])[j];
					PECKER_LOG_ (" %lf ",x);
				}
				PECKER_LOG_("\n");
			}
			PECKER_LOG_("]\n");
	}
};
void matrix_test ()
{
	typedef VectorX< float_t, 2 > vector2;
	typedef SquareMatrixX< float_t, 2 > SMat2;
	typedef SquareMatrixEX_unsafe < float_t, 2 > SMat2X;
	typedef VectorX< float_t, 3 > vector3;
	typedef SquareMatrixX< float_t, 3 > SMat3;
	typedef SquareMatrixEX_unsafe < float_t, 3 > SMat3X;
	typedef VectorX< float_t, 4 > vector4;
	typedef SquareMatrixX< float_t, 4 > SMat4;
	typedef SquareMatrixEX_unsafe < float_t, 4 > SMat4X;
	typedef VectorX< float_t, 5 > vector5;
	typedef SquareMatrixX< float_t, 5 > SMat5;
	typedef SquareMatrixEX_unsafe < float_t, 5 > SMat5X;


	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("vec4 test!\n");
	vector4 vec4_0 (1,2,3,4);
	vector4 vec4_1 (1,1,1,1);
	vector4 vec = vector4::mul(vec4_1, 4);
	vec4_1.add_replace(vec);
	vector4 vec_cross;
	vec.cross(vec4_0,vec_cross);
	vec.cross(vec4_1,vec_cross);
	vector4::dim_t dot_ = vec.dot(vec_cross);
	//////////////////////////////////////////////////////////////////////////
	float fvec1_2[] = {1,1};
	float fvec2_2[] = {1,2};
	vector2 vec2_array[2] = 
	{
		vector2(fvec1_2, 2),
		vector2(fvec2_2, 2)
	};

	float fvec1_22[] = {1,1};
	float fvec2_22[] = {1,2};
	vector2 vec2_array2[2] = 
	{
		vector2(fvec1_22, 2),
		vector2(fvec2_22, 2)
	};


	PECKER_LOG_ ("mat2 test!\n");
	SMat2 mat2_0(vec2_array,3);
	print_mat <SMat2, 2> (&mat2_0);

	SMat2 mat2_1(vec2_array2,3);
	print_mat <SMat2, 2>(&mat2_1);
	PECKER_LOG_ (" X \n");
	print_mat <SMat2, 2>(&mat2_0);
	PECKER_LOG_ (" = \n");
	mat2_1.mul_replace(mat2_0);
	print_mat <SMat2, 2>(&mat2_1);
	
	PECKER_LOG_ ("\n");
	SMat2X mat2x_0(mat2_0);
	SMat2X mat2x_1(mat2_1);
	print_mat <SMat2X, 2>(&mat2x_1);
	PECKER_LOG_ (" X \n");
	print_mat <SMat2X, 2>(&mat2x_0);
	PECKER_LOG_ (" = \n");
	mat2x_1.mul_replace(mat2x_0);
	print_mat <SMat2X, 2>(&mat2x_1);

	PECKER_LOG_ (" \n");
	vector2 vec2(1, 2);
	vector2 vec2_result = SMat2::mul(vec2, mat2_0);
	print_vec <vector2, 2> (&vec2);
	PECKER_LOG_ (" X \n");
	print_mat <SMat2, 2>(&mat2_0);
	PECKER_LOG_ (" = \n");
	print_vec <vector2, 2> (&vec2_result);

	vec2_result = SMat2X::mul (vec2, mat2x_0);
	print_vec <vector2, 2> (&vec2_result);


	float_t det_ = mat2_0.det();
	usize__t rank_ = mat2_0.rank();
	PECKER_LOG_ ("mat det = %lf\n",det_);
	PECKER_LOG_ ("mat rank = %d\n",rank_);

	

	det_ = mat2x_0.det();
	rank_ = mat2x_0.rank();
	PECKER_LOG_ ("x mat det = %lf\n",det_);
	PECKER_LOG_ ("x mat rank = %d\n",rank_);

	SMat2 mat2_invert;
	SMat2 mat2_extern;
	mat2_extern.indentify_replace(1);
	mat2_0.inverse_matrix(mat2_invert, mat2_extern);
	PECKER_LOG_ ("invert mat\n");
	print_mat <SMat2, 2> (&mat2_invert);

	SMat2X matx2_invert(mat2_invert);
	SMat2X matx2_extern(mat2_extern);
	mat2x_0.inverse_matrix(matx2_invert, matx2_extern);
	PECKER_LOG_ ("invert matx\n");
	print_mat <SMat2X, 2> (&matx2_invert);

	SMat2::matrix_alg_t::matrix_t mat2_ = SMat2::matrix_reference(mat2_0.m_mat);
	SMat2::matrix_ex_t mat2_ex_tmp(mat2_0.m_mat);
	SMat2::matrix_alg_t::matrix_ex_t mat2_ex = SMat2::matrix_reference(mat2_ex_tmp);
	for (uindex_t i=0; i<2; ++i)
	{
		for (uindex_t j=0; j<2; ++j)
		{
			PECKER_LOG_ ("\n(%d, %d)\n",i,j);
			print_mat_alg<SMat2, 2 >(&mat2_0,i,j);
			det_ = SMat2::matrix_alg_t::matrix2x2_algebraic_cofactor_det(mat2_ex, i, j);
			PECKER_LOG_ ("matex det = %lf\n",det_);
			det_ = SMat2::matrix_alg_t::matrix2x2_algebraic_cofactor_det(mat2_, i, j);
			PECKER_LOG_ ("mat det = %lf\n",det_);

			SMat2 tmp_mat(mat2_0);
			SMat2::matrix_ex_t mat_ex_tmp_(tmp_mat.m_mat);
			SMat2::matrix_alg_t::matrix_ex_t mat_ex_ = SMat2::matrix_reference(mat_ex_tmp_);
			det_ = SMat2::matrix_alg_t::matrix_algebraic_cofactor_det(mat_ex_, 2, i, j);
			PECKER_LOG_ ("mat g det = %lf\n",det_);

			tmp_mat = SMat2(mat2_0);
			mat_ex_tmp_ = SMat2::matrix_ex_t (tmp_mat.m_mat);
			mat_ex_ = SMat2::matrix_reference(mat_ex_tmp_);

			det_ = SMat2X::matrix_alg_t::matrix_algebraic_cofactor_det(mat_ex_, 2, i, j);
			PECKER_LOG_ ("matx g det = %lf\n",det_);
		}

	}
	//////////////////////////////////////////////////////////////////////////
	float fvec1_3[] = {1,1,2};
	float fvec2_3[] = {2,2,8};
	float fvec3_3[] = {1,2,4};

	//float fvec1_3[] = {1,1,1};
	//float fvec2_3[] = {1,2,3};
	//float fvec3_3[] = {1,5,1};
	vector3 vec3_array[3] = 
	{
		vector3(fvec1_3, 3),
		vector3(fvec2_3, 3),
		vector3(fvec3_3, 3)
	};

	PECKER_LOG_ ("mat3 test!\n");
	SMat3 mat3_0(vec3_array,3);
	print_mat <SMat3, 3> (&mat3_0);

	SMat3 mat3_1(vec3_array,3);
	print_mat <SMat3, 3>(&mat3_1);
	PECKER_LOG_ (" X \n");
	print_mat <SMat3, 3>(&mat3_0);
	PECKER_LOG_ (" = \n");
	mat3_1.mul_replace(mat3_0);
	print_mat <SMat3, 3>(&mat3_1);

	PECKER_LOG_ ("\n");
	SMat3X mat3x_0(mat3_0);
	SMat3X mat3x_1(mat3_1);
	print_mat <SMat3X, 3>(&mat3x_1);
	PECKER_LOG_ (" X \n");
	print_mat <SMat3X, 3>(&mat3x_0);
	PECKER_LOG_ (" = \n");
	mat3x_1.mul_replace(mat3x_0);
	print_mat <SMat3X, 3>(&mat3x_1);

	PECKER_LOG_ (" \n");
	vector3 vec3(1, 2, 3);
	vector3 vec3_result = SMat3::mul(vec3, mat3_0);
	print_vec <vector3, 3> (&vec3);
	PECKER_LOG_ (" X \n");
	print_mat <SMat3, 3>(&mat3_0);
	PECKER_LOG_ (" = \n");
	print_vec <vector3, 3> (&vec3_result);
	vec3_result = SMat3X::mul (vec3, mat3x_0);
	print_vec <vector3, 3> (&vec3_result);

	det_ = mat3_0.det();
	rank_ = mat3_0.rank();
	PECKER_LOG_ ("mat det = %lf\n",det_);
	PECKER_LOG_ ("mat rank = %d\n",rank_);

	//SMat3X mat3x_0(mat3_0);

	det_ = mat3x_0.det();
	rank_ = mat3x_0.rank();
	PECKER_LOG_ ("x mat det = %lf\n",det_);
	PECKER_LOG_ ("x mat rank = %d\n",rank_);

	SMat3 mat3_invert;
	SMat3 mat3_extern;
	mat3_extern.indentify_replace(1);
	mat3_0.inverse_matrix(mat3_invert, mat3_extern);
	PECKER_LOG_ ("invert mat\n");
	print_mat <SMat3, 3> (&mat3_invert);

	SMat3X matx3_invert(mat3_invert);
	SMat3X matx3_extern(mat3_extern);
	mat3x_0.inverse_matrix(matx3_invert, matx3_extern);
	PECKER_LOG_ ("invert matx\n");
	print_mat <SMat3X, 3> (&matx3_invert);

	SMat3::matrix_alg_t::matrix_t mat3_ = SMat3::matrix_reference(mat3_0.m_mat);
	SMat3::matrix_ex_t mat3_ex_tmp(mat3_0.m_mat);
	SMat3::matrix_alg_t::matrix_ex_t mat3_ex = SMat3::matrix_reference(mat3_ex_tmp);
	for (uindex_t i=0; i<3; ++i)
	{
		for (uindex_t j=0; j<3; ++j)
		{
			PECKER_LOG_ ("\n(%d, %d)\n",i,j);
			print_mat_alg<SMat3, 3 >(&mat3_0,i,j);
			det_ = SMat3::matrix_alg_t::matrix3x3_algebraic_cofactor_det(mat3_ex, i, j);
			PECKER_LOG_ ("matex det = %lf\n",det_);
			det_ = SMat3::matrix_alg_t::matrix3x3_algebraic_cofactor_det(mat3_, i, j);
			PECKER_LOG_ ("mat det = %lf\n",det_);

			SMat3 tmp_mat(mat3_0);
			SMat3::matrix_ex_t mat_ex_tmp_(tmp_mat.m_mat);
			SMat3::matrix_alg_t::matrix_ex_t mat_ex_ = SMat3::matrix_reference(mat_ex_tmp_);
			det_ = SMat3::matrix_alg_t::matrix_algebraic_cofactor_det(mat_ex_, 3, i, j);
			PECKER_LOG_ ("mat g det = %lf\n",det_);

			tmp_mat = SMat3(mat3_0);
			mat_ex_tmp_ = SMat3::matrix_ex_t (tmp_mat.m_mat);
			mat_ex_ = SMat3::matrix_reference(mat_ex_tmp_);

			det_ = SMat3X::matrix_alg_t::matrix_algebraic_cofactor_det(mat_ex_, 3, i, j);
			PECKER_LOG_ ("matx g det = %lf\n",det_);
		}

	}
	//////////////////////////////////////////////////////////////////////////
	PECKER_LOG_ ("mat4 test!\n");
	SMat4 mat4_0(1, 2, 3, 4,
								3, 2, 1, 4,
								3, 2, 1, 5,
								1, 2, 4, 6);
	SMat4 mat4_1(mat4_0);
	print_mat <SMat4, 4> (&mat4_0);

	PECKER_LOG_ ("\n");
	SMat4X mat4x_0(mat4_0);
	SMat4X mat4x_1(mat4_1);
	print_mat <SMat4X, 4>(&mat4x_1);
	PECKER_LOG_ (" X \n");
	print_mat <SMat4X, 4>(&mat4x_0);
	PECKER_LOG_ (" = \n");
	mat4x_1.mul_replace(mat4x_0);
	print_mat <SMat4X, 4>(&mat4x_1);

	PECKER_LOG_ (" \n");
	vector4 vec4(1, 2, 3, 4);
	vector4 vec4_result = SMat4::mul(vec4, mat4_0);
	print_vec <vector4, 4> (&vec4);
	PECKER_LOG_ (" X \n");
	print_mat <SMat4, 4>(&mat4_0);
	PECKER_LOG_ (" = \n");
	print_vec <vector4, 4> (&vec4_result);

	vec4_result = SMat4X::mul (vec4, mat4x_0);
	print_vec <vector4, 4> (&vec4_result);

	det_ = mat4_0.det();
	rank_ = mat4_0.rank();
	PECKER_LOG_ ("mat det = %lf\n",det_);
	PECKER_LOG_ ("mat rank = %d\n",rank_);


	det_ = mat4x_0.det();
	rank_ = mat4x_0.rank();
	PECKER_LOG_ ("x mat det = %lf\n",det_);
	PECKER_LOG_ ("x mat rank = %d\n",rank_);

	SMat4 mat_invert;
	SMat4 mat_extern;
	mat_extern.indentify_replace(1);
	mat4_0.inverse_matrix(mat_invert, mat_extern);
	PECKER_LOG_ ("invert mat\n");
	print_mat <SMat4, 4> (&mat_invert);

	SMat4X matx_invert(mat_invert);
	SMat4X matx_extern(mat_extern);
	mat4x_0.inverse_matrix(matx_invert, matx_extern);
	PECKER_LOG_ ("invert matx\n");
	print_mat <SMat4X, 4> (&matx_invert);

	SMat4::matrix_alg_t::matrix_t mat_ = SMat4::matrix_reference(mat4_0.m_mat);
	SMat4::matrix_ex_t mat_ex_tmp(mat4_0.m_mat);
	SMat4::matrix_alg_t::matrix_ex_t mat_ex = SMat4::matrix_reference(mat_ex_tmp);
	for (uindex_t i=0; i<4; ++i)
	{
		for (uindex_t j=0; j<4; ++j)
		{
			PECKER_LOG_ ("\n(%d, %d)\n",i,j);
			print_mat_alg<SMat4, 4 >(&mat4_0,i,j);
			det_ = SMat4::matrix_alg_t::matrix4x4_algebraic_cofactor_det(mat_ex, i, j);
			PECKER_LOG_ ("matex det = %lf\n",det_);
			det_ = SMat4::matrix_alg_t::matrix4x4_algebraic_cofactor_det(mat_, i, j);
			PECKER_LOG_ ("mat det = %lf\n",det_);

			SMat4 tmp_mat(mat4_0);
			SMat4::matrix_ex_t mat_ex_tmp_(tmp_mat.m_mat);
			SMat4::matrix_alg_t::matrix_ex_t mat_ex_ = SMat4::matrix_reference(mat_ex_tmp_);
			det_ = SMat4::matrix_alg_t::matrix_algebraic_cofactor_det(mat_ex_, 4, i, j);
			PECKER_LOG_ ("mat g det = %lf\n",det_);

			tmp_mat = SMat4(mat4_0);
			mat_ex_tmp_ = SMat4::matrix_ex_t (tmp_mat.m_mat);
			mat_ex_ = SMat4::matrix_reference(mat_ex_tmp_);

			det_ = SMat4X::matrix_alg_t::matrix_algebraic_cofactor_det(mat_ex_, 4, i, j);
			PECKER_LOG_ ("matx g det = %lf\n",det_);
		}
		
	}
	
	PECKER_LOG_ ("mat5 test!\n");
	float_t fvec1_5[] = {1,2,3,4,5};
	float_t fvec2_5[] = {3,2,1,4,3};
	float_t fvec3_5[] = {3,2,1,5,1};
	float_t fvec4_5[] = {1,2,4,6,2};
	float_t fvec5_5[] = {5,6,7,8,9};
	////float fvec1_5[] = {2,1,0,0,6};
	////float fvec2_5[] = {1,2,1,0,7};
	////float fvec3_5[] = {0,1,2,1,8};
	////float fvec4_5[] = {0,0,1,2,9};
	////float fvec5_5[] = {0,0,1,2,10};

	vector5 vec5_array[5] = 
	{	vector5(fvec1_5, 5),
		vector5(fvec2_5, 5),
		vector5(fvec3_5, 5),
		vector5(fvec4_5, 5),
		vector5(fvec5_5, 5)
	};

	SMat5 mat5_0(vec5_array,5);

	print_mat <SMat5, 5> (&mat5_0);

	SMat5 mat5_1(vec5_array,5);
	print_mat <SMat5, 5>(&mat5_1);
	PECKER_LOG_ (" X \n");
	print_mat <SMat5, 5>(&mat5_0);
	PECKER_LOG_ (" = \n");
	mat5_1.mul_replace(mat5_0);
	print_mat <SMat5, 5>(&mat5_1);

	PECKER_LOG_ ("\n");
	SMat5X mat5x_0(mat5_0);
	SMat5X mat5x_1(mat5_1);
	print_mat <SMat5X, 5>(&mat5x_1);
	PECKER_LOG_ (" X \n");
	print_mat <SMat5X, 5>(&mat5x_0);
	PECKER_LOG_ (" = \n");
	mat5x_1.mul_replace(mat5x_0);
	print_mat <SMat5X, 5>(&mat5x_1);

	PECKER_LOG_ (" \n");
	vector5 vec5(vec5_array[0]);
	vector5 vec5_result = SMat5::mul(vec5, mat5_0);
	print_vec <vector5, 5> (&vec5);
	PECKER_LOG_ (" X \n");
	print_mat <SMat5, 5>(&mat5_0);
	PECKER_LOG_ (" = \n");
	print_vec <vector5, 5> (&vec5_result);
	vec5_result = SMat5X::mul (vec5, mat5x_0);
	print_vec <vector5, 5> (&vec5_result);


	det_ = mat5_0.det();
	rank_ = mat5_0.rank();
	PECKER_LOG_ ("mat det = %lf\n",det_);
	PECKER_LOG_ ("mat rank = %d\n",rank_);


	det_ = mat5x_0.det();
	rank_ = mat5x_0.rank();
	PECKER_LOG_ ("x mat det = %lf\n",det_);
	PECKER_LOG_ ("x mat rank = %d\n",rank_);


	SMat5 mat5_invert;
	SMat5 mat5_extern;
	mat5_0.inverse_matrix(mat5_invert, mat5_extern);

	PECKER_LOG_ ("invert mat\n");
	print_mat <SMat5, 5> (&mat5_invert);

	SMat5X matx5_invert(mat5_invert);
	SMat5X matx5_extern(mat5_extern);
	mat5x_0.inverse_matrix(matx5_invert, matx5_extern);
	PECKER_LOG_ ("invert matx\n");
	print_mat <SMat5X, 5> (&matx5_invert);

	SMat5::matrix_alg_t::matrix_t mat5_ = SMat5::matrix_reference(mat5_0.m_mat);
	SMat5::matrix_ex_t mat5_ex_tmp(mat5_0.m_mat);
	SMat5::matrix_alg_t::matrix_ex_t mat5_ex = SMat5::matrix_reference(mat5_ex_tmp);
	for (uindex_t i=0; i<5; ++i)
	{
		for (uindex_t j=0; j<5; ++j)
		{
			PECKER_LOG_ ("\n(%d, %d)\n",i,j);
			print_mat_alg<SMat5, 5 >(&mat5_0,i,j);

			SMat5 tmp_mat(mat5_0);
			SMat5::matrix_ex_t mat_ex_tmp_(tmp_mat.m_mat);
			SMat5::matrix_alg_t::matrix_ex_t mat_ex_ = SMat5::matrix_reference(mat_ex_tmp_);

			det_ = SMat5::matrix_alg_t::matrix_algebraic_cofactor_det(mat_ex_, 5, i, j);
			PECKER_LOG_ ("mat g det = %lf\n",det_);

			tmp_mat = SMat5(mat5_0);
			mat_ex_tmp_ = SMat5::matrix_ex_t (tmp_mat.m_mat);
			mat_ex_ = SMat5::matrix_reference(mat_ex_tmp_);

			det_ = SMat5X::matrix_alg_t::matrix_algebraic_cofactor_det(mat_ex_, 5, i, j);
			PECKER_LOG_ ("matx g det = %lf\n",det_);
		}

	}

	return;
}