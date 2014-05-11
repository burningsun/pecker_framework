/*
 * pfx_cvector.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CVECTOR_H_
#define		PFX_CVECTOR_H_

#include "../pfx_defines.h"

PECKER_BEGIN

template < class dim_type, const usize_t dim_count >
struct vector_data
{
	typedef typename dim_type dim_t;
	typedef typename vector_data< dim_t, dim_count > vector_t;

	dim_t m_value[dim_count];
	
	static PFX_INLINE usize_t vector_dim_count ()
	{
		return dim_count;
	}
	PFX_INLINE dim_t& operator[] (uindex_t i)
	{
		return m_value[i];
	}
	PFX_INLINE const dim_t& operator[] (uindex_t i) const
	{
		return m_value[i];
	}
};

PECKER_END

#endif			//PFX_CVECTOR_H_
