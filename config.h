/* 
 * Copyright (C) 2005,2006 MaNGOS <http://www.mangosproject.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SC_CONFIG_H
#define SC_CONFIG_H

#include "../../framework/Platform/CompilerDefs.h"

#ifdef WIN32
  #include "svn_revision.h"
#else
  #define SVN_REVISION        "246"
#endif

// Format is YYYYMMDDRR where RR is the change in the conf file
// for that day.
#define SD2_CONF_VERSION    2008011901

#ifdef WIN32
  #define MANGOS_DLL_EXPORT extern "C" __declspec(dllexport)
#elif defined( __GNUC__ )
  #define MANGOS_DLL_EXPORT extern "C"
#else
  #define MANGOS_DLL_EXPORT extern "C" export
#endif

#ifndef _VERSION
  #if PLATFORM == PLATFORM_WIN32
    #define _VERSION "(Revision " SVN_REVISION ")"
  #else
    #define _VERSION "(Revision " SVN_REVISION ")"
  #endif
#endif

#if PLATFORM == PLATFORM_WINDOWS
  #ifdef _WIN64
    #define _FULLVERSION _VERSION " (Win64)"
  #else
    #define _FULLVERSION _VERSION " (Win32)"
  #endif
  #define _SCRIPTDEV2_CONFIG  "scriptdev2.conf"
#else
  #define _FULLVERSION _VERSION " (Unix)"
  #define _SCRIPTDEV2_CONFIG  "@prefix@/etc/scriptdev2.conf"
#endif

#endif