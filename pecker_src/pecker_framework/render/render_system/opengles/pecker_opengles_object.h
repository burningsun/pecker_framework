/*
 * pecker_opengles_object.h
 *
 *  Created on: 2013-3-6
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_OPENGLES_OBJECT_H_
#define  PECKER_OPENGLES_OBJECT_H_

#include "../../pecker_render_object.h"

PECKER_BEGIN


class pecker_opengles_v2_object : public pecker_render_object
{
public:
	virtual const pecker_render_system_info &get_render_system_info(pecker_render_system_info P_IN &system_info) const;
	virtual UInt get_object_location() const;
	static HResult get_last_error_code();
};

class pecker_opengles_v3_object : public pecker_render_object
{
public:
	virtual const pecker_render_system_info &get_render_system_info(pecker_render_system_info P_IN &system_info) const;
	virtual UInt get_object_location() const;
	static HResult get_last_error_code();
};

PECKER_END

#endif //PECKER_OPENGLES_OBJECT_H_