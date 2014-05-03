/*
 * pfx_matrix_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/data/pfx_vector_codes.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/data/pfx_matrix_codes.h"

USING_PECKER_SDK

template < class mat_t,const pfx_usize_t dim_v >
void print_mat (const mat_t* mat_ptr)
{
	if (null == mat_ptr)
	{
		PECKER_LOG_ ("null mat\n");
	}
	else
	{
		PECKER_LOG_ ("mat = [\n")
		for (pfx_uindex_t i=0; i<dim_v; ++i)
		{
			for (pfx_uindex_t j=0; j<dim_v; ++j)
			{
				PECKER_LOG_ (" %lf ",mat_ptr->m_vector[i].m_value[j]);
			}
			PECKER_LOG_("\n");
		}
		PECKER_LOG_("]\n");
	}
};

template < class mat_t,const pfx_usize_t dim_v >
void print_mat_ex (const mat_t* mat_ptr)
{
	if (null == mat_ptr)
	{
		PECKER_LOG_ ("null mat\n");
	}
	else
	{
		PECKER_LOG_ ("mat = [\n")
			for (pfx_uindex_t i=0; i<dim_v; ++i)
			{
				if (mat_ptr->m_lines[i])
				{
					for (pfx_uindex_t j=0; j<dim_v; ++j)
					{
						PECKER_LOG_ (" %lf ",mat_ptr->m_lines[i].m_value[j]);
					}
				}
				else
				{
					PECKER_LOG_(" null line ");
				}

				PECKER_LOG_("\n");
			}
			PECKER_LOG_("]\n");
	}
};

template < class mat_t,const pfx_usize_t dim_v >
void print_mat_alg (const mat_t* mat_ptr,pfx_usize_t x,pfx_usize_t y)
{
	if (null == mat_ptr)
	{
		PECKER_LOG_ ("null mat\n");
	}
	else
	{
		PECKER_LOG_ ("mat = [\n")
			for (pfx_uindex_t i=0; i<dim_v; ++i)
			{
				if (x == i){continue;}
				for (pfx_uindex_t j=0; j<dim_v; ++j)
				{
					if (y == j){continue;}
					PECKER_LOG_ (" %lf ",mat_ptr->m_vector[i].m_value[j]);
				}
				PECKER_LOG_("\n");
			}
			PECKER_LOG_("]\n");
	}
};
void matrix_test ()
{
	typedef	pfx_vector < dimension_value_operations < float >, 2 > vec2_t;
	typedef pfx_square_matrix < dimension_value_operations < float >, 2 > mat2x2_t;

	typedef	pfx_vector < dimension_value_operations < float >, 3 > vec3_t;
	typedef pfx_square_matrix < dimension_value_operations < float >, 3 > mat3x3_t;

	typedef	pfx_vector < dimension_value_operations < float >, 4 > vec4_t;
	typedef pfx_square_matrix < dimension_value_operations < float >, 4 > mat4x4_t;

	typedef	pfx_vector < dimension_value_operations < float >, 5 > vec5_t;
	typedef pfx_square_matrix < dimension_value_operations < float >, 5 > mat5x5_t;

	mat4x4_t mat4;
	//float fvec1_4[] = {1,2,3,4};
	//float fvec2_4[] = {3,2,1,4};
	//float fvec3_4[] = {3,2,1,5};
	//float fvec4_4[] = {1,2,4,6};

	float fvec1_4[] = {2,1,0,0};
	float fvec2_4[] = {1,2,1,0};
	float fvec3_4[] = {0,1,2,1};
	float fvec4_4[] = {0,0,1,2};
	vec4_t::sets(mat4.row_reference(0),fvec1_4,4);
	vec4_t::sets(mat4.row_reference(1),fvec2_4,4);
	vec4_t::sets(mat4.row_reference(2),fvec3_4,4);
	vec4_t::sets(mat4.row_reference(3),fvec4_4,4);

	print_mat < mat4x4_t::matrix_t,4 >(&mat4.m_mat);
	pfx_usize_t rank_ = mat4.rank_gaussian ();
	PECKER_LOG_ ("rank = %d\n",rank_);

	float det = mat4.determinant();
	PECKER_LOG_ ("det = %lf\n",det);

	mat4x4_t mat_44_inv;
	mat4x4_t* mat4_ptr = mat4.inverse_matrix_gaussian_elimination(mat_44_inv);
	PECKER_LOG_ ("inverse matrix\n");
	if (mat4_ptr)
	{
		print_mat < mat4x4_t::matrix_t,4 >(&(mat4_ptr->m_mat));
	}
	PECKER_LOG_ ("\n\n");
	for (pfx_uindex_t i=0; i<mat4.get_dimensional_count(); ++i)
	for (pfx_uindex_t j=0; j<mat4.get_dimensional_count(); ++j)
	{
		mat4x4_t::matrix_t mat_44 = mat4.m_mat;
		mat4x4_t::matrix_ex_t mat_g44 (mat_44);
		print_mat_alg<mat4x4_t::matrix_t,4> (&mat_44,i,j);
		det = mat4x4_t::algebraic_cofactor_determinant_gaussian_unsafe(mat_g44,i,j);
		PECKER_LOG_ ("det(%d,%d) =%lf(gaussian)\n",i,j,det);
		det = mat4.algebraic_cofactor_determinant(i,j);
		PECKER_LOG_ ("det(%d,%d) =%lf(cross)\n",i,j,det);
		//print_mat < mat5x5_t::matrix_t,5 >(&mat_55);
	}



	PECKER_LOG_ ("mat5\n");
	mat5x5_t mat5;
	float fvec1_5[] = {1,2,3,4,5};
	float fvec2_5[] = {3,2,1,4,3};
	float fvec3_5[] = {3,2,1,5,1};
	float fvec4_5[] = {1,2,4,6,2};
	float fvec5_5[] = {5,6,7,8,9};
	//float fvec1_5[] = {2,1,0,0,6};
	//float fvec2_5[] = {1,2,1,0,7};
	//float fvec3_5[] = {0,1,2,1,8};
	//float fvec4_5[] = {0,0,1,2,9};
	//float fvec5_5[] = {0,0,1,2,10};
	vec5_t::sets(mat5.row_reference(0),fvec1_5,5);
	vec5_t::sets(mat5.row_reference(1),fvec2_5,5);
	vec5_t::sets(mat5.row_reference(2),fvec3_5,5);
	vec5_t::sets(mat5.row_reference(3),fvec4_5,5);
	vec5_t::sets(mat5.row_reference(4),fvec5_5,5);

	print_mat < mat5x5_t::matrix_t,5 >(&mat5.m_mat);
	rank_ = mat5.rank_gaussian ();
	PECKER_LOG_ ("rank = %d\n",rank_);

	mat5x5_t mat_55_inv;
	mat5x5_t* mat5_ptr = mat5.inverse_matrix_gaussian_elimination(mat_55_inv);
	PECKER_LOG_ ("inverse matrix\n");
	if (mat5_ptr)
	{
		print_mat < mat5x5_t::matrix_t,5 >(&(mat5_ptr->m_mat));
	}

	for (pfx_uindex_t i=0; i<mat5.get_dimensional_count(); ++i)
	for (pfx_uindex_t j=0; j<mat5.get_dimensional_count(); ++j)
	{
		mat5x5_t::matrix_t mat_55 = mat5.m_mat;
		mat5x5_t::matrix_ex_t mat_g (mat_55);
		print_mat_alg<mat5x5_t::matrix_t,5> (&mat_55,i,j);
		det = mat5x5_t::algebraic_cofactor_determinant_gaussian_unsafe(mat_g,i,j);
		PECKER_LOG_ ("det(%d,%d) =%lf\n",i,j,det);
		//print_mat < mat5x5_t::matrix_t,5 >(&mat_55);
	}

	//mat5x5_t::matrix_t mat_55 = mat5.m_mat;
	//mat5x5_t::matrix_ex_t mat_g (mat_55);
	//det = mat5x5_t::algebraic_cofactor_determinant_gaussian_unsafe(mat_g,2,0);
	//PECKER_LOG_ ("det =%lf\n",det);
	//print_mat < mat5x5_t::matrix_t,5 >(&mat_55);
	//PECKER_LOG_ ("MAT 5x5....");
	//print_mat < mat5x5_t::matrix_t,5 >(&mat5.m_mat);
	//mat5.transpose_replace();
	//PECKER_LOG_ ("MAT 5x5 transponse....");
	//print_mat < mat5x5_t::matrix_t,5 >(&mat5.m_mat);
	//mat5x5_t::matrix_t mat_55 = mat5.m_mat;
	//mat5x5_t::transpose_matrix(mat5.m_mat,mat_55);
	//print_mat < mat5x5_t::matrix_t,5 >(&mat_55);


	mat3x3_t mat3;
	//float fvec1_3[] = {1,1,2};
	//float fvec2_3[] = {2,2,8};
	//float fvec3_3[] = {1,2,4};

	float fvec1_3[] = {1,1,1};
	float fvec2_3[] = {1,2,3};
	float fvec3_3[] = {1,5,1};

	vec3_t::sets(mat3.row_reference(0),fvec1_3,3);
	vec3_t::sets(mat3.row_reference(1),fvec2_3,3);
	vec3_t::sets(mat3.row_reference(2),fvec3_3,3);
	print_mat < mat3x3_t::matrix_t,3 >(&mat3.m_mat);
	rank_ = mat3.rank_gaussian ();
	PECKER_LOG_ ("rank = %d\n",rank_);
	det = mat3.determinant();
	PECKER_LOG_ ("%lf\n",det);
	mat3x3_t mat_33_inv;
	mat3x3_t* mat3_ptr = mat3.inverse_matrix_gaussian_elimination(mat_33_inv);
	PECKER_LOG_ ("inverse matrix\n");
	if (mat3_ptr)
	{
		print_mat < mat3x3_t::matrix_t,3 >(&(mat3_ptr->m_mat));
	}
	//mat3x3_t::matrix_t mat_33 = mat3.m_mat;
	//mat3x3_t::matrix_ex_t mat_g33 (mat_33);
	//det = mat3x3_t::determinant_gaussian_unsafe(mat_g33);
	//PECKER_LOG_ ("gaussian det = %lf\n",det);

	for (pfx_uindex_t i=0; i<mat3.get_dimensional_count(); ++i)
	for (pfx_uindex_t j=0; j<mat3.get_dimensional_count(); ++j)
	{
		mat3x3_t::matrix_t mat_33 = mat3.m_mat;
		mat3x3_t::matrix_ex_t mat_g33 (mat_33);
		print_mat_alg<mat3x3_t::matrix_t,3> (&mat_33,i,j);
		det = mat3x3_t::algebraic_cofactor_determinant_gaussian_unsafe(mat_g33,i,j);
		PECKER_LOG_ ("det(%d,%d) =%lf(gaussian)\n",i,j,det);
		det = mat3.algebraic_cofactor_determinant(i,j);
		PECKER_LOG_ ("det(%d,%d) =%lf(cross)\n",i,j,det);
		//print_mat < mat5x5_t::matrix_t,5 >(&mat_55);
	}


	mat2x2_t mat2;
	float fvec1_2[] = {1,1};
	float fvec2_2[] = {1,2};

	vec2_t::sets(mat2.row_reference(0),fvec1_2,2);
	vec2_t::sets(mat2.row_reference(1),fvec2_2,2);

	print_mat < mat2x2_t::matrix_t,2 >(&mat2.m_mat);
	rank_ = mat2.rank_gaussian ();
	PECKER_LOG_ ("rank = %d\n",rank_);
	det = mat2.determinant();
	PECKER_LOG_ ("%lf\n",det);
	mat2x2_t::matrix_t mat_22 = mat2.m_mat;
	mat2x2_t::matrix_ex_t mat_g22 (mat_22);
	det = mat2x2_t::determinant_gaussian_unsafe(mat_g22);
	PECKER_LOG_ ("gaussian det = %lf\n",det);

	mat2x2_t mat_22_inv;
	mat2x2_t* mat2_ptr = mat2.inverse_matrix_gaussian_elimination(mat_22_inv);
	PECKER_LOG_ ("inverse matrix\n");
	if (mat2_ptr)
	{
		print_mat < mat2x2_t::matrix_t,2 >(&(mat2_ptr->m_mat));
	}

	return;
}