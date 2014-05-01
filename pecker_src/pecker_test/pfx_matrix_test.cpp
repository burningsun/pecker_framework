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
	typedef	pfx_vector < dimension_value_operations < float >, 4 > vec4_t;
	typedef pfx_square_matrix < dimension_value_operations < float >, 4 > mat4x4_t;

	typedef	pfx_vector < dimension_value_operations < float >, 5 > vec5_t;
	typedef pfx_square_matrix < dimension_value_operations < float >, 5 > mat5x5_t;

	mat4x4_t mat;
	float fvec1[] = {1,2,3,4};
	float fvec2[] = {3,2,1,4};
	float fvec3[] = {3,2,1,5};
	float fvec4[] = {1,2,4,6};

	//float fvec1[] = {2,1,0,0};
	//float fvec2[] = {1,2,1,0};
	//float fvec3[] = {0,1,2,1};
	//float fvec4[] = {0,0,1,2};
	vec4_t::sets(mat.row_reference(0),fvec1,4);
	vec4_t::sets(mat.row_reference(1),fvec2,4);
	vec4_t::sets(mat.row_reference(2),fvec3,4);
	vec4_t::sets(mat.row_reference(3),fvec4,4);

	print_mat < mat4x4_t::matrix_t,4 >(&mat.m_mat);
	float det = mat.determinant();

	PECKER_LOG_ ("%lf\n",det);
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

	for (pfx_uindex_t i=0; i<mat5.get_dimensional_count(); ++i)
	for (pfx_uindex_t j=0; j<mat5.get_dimensional_count(); ++j)
	{
		mat5x5_t::matrix_t mat_55 = mat5.m_mat;
		mat5x5_t::matrix_ex_t mat_g (mat_55);
		print_mat_alg<mat5x5_t::matrix_t,5> (&mat_55,i,j);
		det = mat5x5_t::algebraic_cofactor_determinant_gaussian(mat_g,i,j);
		PECKER_LOG_ ("det(%d,%d) =%lf\n",i,j,det);
		//print_mat < mat5x5_t::matrix_t,5 >(&mat_55);
	}

	//mat5x5_t::matrix_t mat_55 = mat5.m_mat;
	//mat5x5_t::matrix_ex_t mat_g (mat_55);
	//det = mat5x5_t::algebraic_cofactor_determinant_gaussian(mat_g,2,0);
	//PECKER_LOG_ ("det =%lf\n",det);
	//print_mat < mat5x5_t::matrix_t,5 >(&mat_55);

	return;
}