// $Id: dtos1.cc,v 1.2 2003/08/02 14:55:38 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "dtos1.h"
#include <cstdio>

#ifdef __MINGW32__
extern "C" { int snprintf(char *str, size_t size, const  char  *format, ...); }
#endif

std::string dtos1(double i)
{
 char buffer[100];
 snprintf(buffer,sizeof buffer,"%.1f",i);
 return(buffer);
}

   