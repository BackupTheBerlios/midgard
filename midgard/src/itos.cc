// $Id: itos.cc,v 1.18 2002/01/04 10:05:14 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "itos.h"
#include <cstdio>

#ifdef __MINGW32__
extern "C" { int snprintf(char *str, size_t size, const  char  *format, ...); }
#endif

std::string itos(int i)
{
 char buffer[100];
 snprintf(buffer,sizeof buffer,"%i",i);
 return(buffer);
}

std::string dtos(double i)
{
 char buffer[100];
 snprintf(buffer,sizeof buffer,"%.1f",i);
 return(buffer);
}

std::string dtos_full(double i)
{
 char buffer[100];
 snprintf(buffer,sizeof buffer,"%f",i);
 return(buffer);
}
   