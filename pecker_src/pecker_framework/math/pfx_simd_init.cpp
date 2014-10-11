/*
* pfx_simd_init.cpp
*
*  Created on: 2014-9-13
*      Author: ¿Ó’Ú≥«  £® cut / cutxyz£© (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#include "pfx_math.h"
#include "../pfx_cpuid.h"

PECKER_BEGIN

extern bool PRINTF_CPU_INFO();
static volatile bool cpu_simd_finded = PRINTF_CPU_INFO();
static volatile result_t binit_math = math_simd_init();


static simd_fabs_unsafe_t           gfabs;
static simd_fadd_unsafe_t           gfadd;
static simd_fdiv_unsafe_t           gfdiv;
static simd_fvec_cross_unsafe_t     gfcross;
static simd_fmat_det_unsafe_t       gfmat_det;
static simd_fmat_dot_unsafe_t       gfmat_dot;
static simd_fmat_inverse_unsafe_t   gfmat_inv;
static simd_fvec_normalize_unsafe_t gfvec_nor;
static simd_fmat_set_unsafe_t       gfmat_set;
static simd_fmat_transpose_unsafe_t gfmat_tran;
static simd_fmul_unsafe_t           gfmul;
static simd_fsub_unsafe_t           gfsub;


const simd_fabs_unsafe_t          * get_simd_fabs_unsafe()
{
	return &gfabs;
}
const simd_fadd_unsafe_t          * get_simd_fadd_unsafe()
{
	return &gfadd;
}
const simd_fdiv_unsafe_t          * get_simd_fdiv_unsafe()
{
	return &gfdiv;
}
const simd_fvec_cross_unsafe_t    * get_simd_fvec_cross_unsafe()
{
	return &gfcross;
}
const simd_fmat_det_unsafe_t      * get_simd_fmat_det_unsafe()
{
	return &gfmat_det;
}
const simd_fmat_dot_unsafe_t      * get_simd_fmat_dot_unsafe()
{
	return &gfmat_dot;
}
const simd_fmat_inverse_unsafe_t  * get_simd_fmat_inverse_unsafe()
{
	return &gfmat_inv;
}
const simd_fvec_normalize_unsafe_t* get_simd_fvec_normalize_unsafe()
{
	return &gfvec_nor;
}
const simd_fmat_set_unsafe_t      * get_simd_fmat_set_unsafe()
{
	return &gfmat_set;
}
const simd_fmat_transpose_unsafe_t* get_simd_fmat_transpose_unsafe()
{
	return &gfmat_tran;
}
const simd_fmul_unsafe_t          * get_simd_fmul_unsafe()
{
	return &gfmul;
}
const simd_fsub_unsafe_t          * get_simd_fsub_unsafe()
{
	return &gfsub;
}


result_t math_simd_init()
{

	result_t res;
	if (!cpu_simd_finded)
	{
		cpu_simd_finded = PRINTF_CPU_INFO();
	}

	if (cpu_simd_finded)
	{
		res = PFX_STATUS_OK;
	}
	else
	{
		res = PFX_STATUS_FAIL;
	}

	
	init_simd_fabs_std(gfabs);
	init_simd_fadd_std(gfadd);
	init_simd_fdiv_std(gfdiv);
	init_simd_fvec_cross_std(gfcross);
	init_simd_fmat_det_std(gfmat_det);
	init_simd_fmat_dot_std(gfmat_dot);
	init_simd_fmat_inv_std(gfmat_inv);
	init_simd_fvec_normalize_std(gfvec_nor);
	init_simd_fmat_set_std(gfmat_set);
	init_simd_fmat_trans_std(gfmat_tran);
	init_simd_fmul_std(gfmul);
	init_simd_fsub_std(gfsub);
	return res;
};
PECKER_END



