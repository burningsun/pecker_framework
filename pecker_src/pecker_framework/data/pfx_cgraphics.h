/*
 * pfx_cgrapghics.h
 *
 *  Created on: 2015-1-2
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CGRAPHICS_H_
#define		PFX_CGRAPHICS_H_

#include "pfx_cbst_codes.h"
#include "pfx_region.h"
#include "pecker_value_compare.h"
PECKER_BEGIN

template < class __region >
struct graphic_node_data
{
	typedef __region region_t;

	typedef typename region_t::element_t element_t;
	typedef typename region_t::length_t  length_t;
	typedef typename region_t::angle_t   angle_t;
	typedef typename region_t::pos_t     pos_t;

	region_t*  m_area_ptr;
	angle_t    m_angle;
	length_t   m_length;
	flag_t     m_direction;
};

template < class __region >
struct region_cmp_angle
{

	typedef pecker_value_compare< typename __region::angle_t >	cmp_t;
	static PFX_INLINE int compare(const __region& node_a, const __region& node_b)
	{
		return cmp_t::compare(node_a.m_angle, node_b.m_angle);
	}
	static PFX_INLINE int compare(const __region* PARAM_IN node_a_ptr, const __region* PARAM_IN node_b_ptr)
	{
		return cmp_t::compare((node_a_ptr->m_angle), (node_b_ptr->m_angle));
	}
};


template < class __node_data, class __cmp_data >
struct graphic_node
{

	typedef __node_data node_data_t;
	typedef class graphic_node< __node_data, __cmp_data >	 node_t;
	typedef node_t cmp_t;
	typedef node_t alloc_t;

	typedef node_t   element_t;
	typedef node_t*  handle_t;
	typedef node_t   allocator_t;

	typedef cbst < AVL_BST_operate < allocator_t, cmp_t > > maps_t;

	static PFX_INLINE int compare(const node_t& node_a, const node_t& node_b)
	{
		return __cmp_data::compare(node_a.m_area_ptr, node_b.m_area_ptr);
	}
	static PFX_INLINE int compare(const node_t* PARAM_IN node_a_ptr, const node_t* PARAM_IN node_b_ptr)
	{
		return __cmp_data::compare((node_a_ptr->m_area_ptr), (node_b_ptr->m_area_ptr));
	}
	static PFX_INLINE element_t* allocate_object()
	{
		return new element_t;
	}
	static PFX_INLINE result_t deallocate_object(element_t*& PARAM_INOUT del_element_ptr)
	{
		result_t status;
		if (del_element_ptr)
		{
			delete del_element_ptr;
			del_element_ptr = null;
			status = PFX_STATUS_OK;
		}
		else
		{
			status = PFX_STATUS_INVALID_PARAMS;
		}
		return status;
	}

	typename node_data_t::region_t* m_area_ptr;
	//maps_t m_direct_nodes;
	
	
};


PECKER_END

#endif			//PFX_CBST_H_
