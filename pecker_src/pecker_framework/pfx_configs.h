﻿/*
 * pfx_configs.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CONFIGS_H_
#define		PFX_CONFIGS_H_

#define	WINDOW_XP		(1)
#define	WINDOW_7_8		(1<<1)
#define	WINDOW_RT		(1<<2)
#define	WINDOW_PHONE	(1<<3)
#define	WINDOW_CE		(1<<4)

#define OS_32BIT

//#define	ANDROID			(1)

#define	OS_WINDOWS		(1)
#define	OS_ANDROID		(1<<1)
#define	OS_LINUX		(1<<2)

//CONFIGS
#define AUTO_DETECT_TARGET_OS

#ifdef AUTO_DETECT_TARGET_OS
#ifdef _MSC_VER
#define OS_CONFIG				OS_WINDOWS
#define OS_VERSION_CONFIG		WINDOW_7_8
#else
#ifdef __GNUC__
#define OS_CONFIG				OS_ANDROID
#define OS_VERSION_CONFIG		(17)
#endif
#endif

#else //#ifndef AUTO_DETECT_TARGET_OS
#define OS_CONFIG				OS_WINDOWS
#define OS_VERSION_CONFIG		WINDOW_7_8
#endif //AUTO_DETECT_TARGET_OS





typedef enum enumBASE_RENDER_SYSTEM_TYPE
{
   UNKOWN_BASE_RENDER_SYSTEM = 0,
   DIRECTX_BASE_RENDER_SYSTEM,
   OPENGLES_BASE_RENDER_SYSTEM,
   BASE_RENDER_SYSTEM_TYPE_COUNT
}BASE_RENDER_SYSTEM_TYPE_t;

#ifdef RTTI_OPEN
#define DYNAMIC_CAST(TYPENAME)	dynamic_cast< TYPENAME >
#define STATIC_CAST(TYPENAME)	static_cast< TYPENAME >
#define CONST_CAST(TYPENAME) 	const_cast< TYPENAME >
#define REINTERPRET_CAST(TYPENAME) reinterpret_cast< TYPENAME >
#define SAFE_CAST(TYPENAME)		 safe_cast< TYPENAME >
#else
#define DYNAMIC_CAST(TYPENAME)	(TYPENAME)
#define STATIC_CAST(TYPENAME)	(TYPENAME)
#define CONST_CAST(TYPENAME) 	(TYPENAME)
#define REINTERPRET_CAST(TYPENAME) (TYPENAME)
#define SAFE_CAST(TYPENAME)		 (TYPENAME)
#endif

typedef enum enumMATRIX_OPTIMIZATION
{
	NO_MATRIX_OPTIMIZATION = 0,
	INTEL_SSE,
	ARM_NEON,
	MATRIX_OPTIMIZATION_COUNT
}MATRIX_OPTIMIZATION_t;

#define MATRIX_OPTIMIZATION	 (NO_MATRIX_OPTIMIZATION)

#define RENDER_SYSTEM_TYPE (OPENGLES_BASE_RENDER_SYSTEM)
#define RENDER_SYSTEM_VERSION (2)

#endif			//PFX_CONFIGS_H_
