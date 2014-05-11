/*
 * pfx_iterator_codes.h
 *
 *  Created on: 2014-1-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#ifndef		PFX_ITERATOR_H_
#define		PFX_ITERATOR_H_

#include "../pfx_defines.h"



PECKER_BEGIN

template < class element_type >
PFX_Interface IPfx_increase_iterator
{
	virtual IPfx_increase_iterator < element_type >*	increase_iterator () = 0;
	virtual	const element_type*									get_current_element () const = 0;
};

template < class element_type >
PFX_Interface IPfx_decrease_iterator
{
	virtual IPfx_decrease_iterator < element_type >*	decrease_iterator () = 0;
	virtual	const element_type*									get_current_element () const = 0;
};
PECKER_END

#endif			//PFX_ITERATOR_H_
