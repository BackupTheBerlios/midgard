// $Id: libmagus_dll.h,v 1.1 2003/09/17 07:44:31 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2003 Christof Petig
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef LIBMAGUS_DLL_H
#define LIBMAGUS_DLL_H

#ifdef __MINGW32__
#if defined(libmagus_COMPILATION) && defined(DLL_EXPORT)
#define LIBMAGUS_API __declspec(dllexport) 
#elif !defined(libmagus_COMPILATION)
#define LIBMAGUS_API __declspec(dllimport)
#else
#define LIBMAGUS_API
#endif /* libmagus_COMPILATION - DLL_EXPORT */
#else
#define LIBMAGUS_API
#endif /* __MINGW32__ */

#endif
