// $Id: Windows_Linux.cc,v 1.7 2002/07/10 08:07:04 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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

#include "Windows_Linux.hh"
#ifdef __MINGW32__
#include <windows.h>
#endif

std::string WinLux::recodePathForTeX(std::string p)
{
#ifndef __MINGW32__
   // tja da kann man gegen Leerzeichen nix machen ...
#else
   // Pfad in DOS Darstellung wandeln (keine Leerzeichen)
   char buf[10240];
   if (GetShortPathName(p.c_str(), buf, sizeof buf)) p=buf;
   // recode path name for TeX with slashes
   for (std::string::iterator i=p.begin();i!=p.end();++i)
       if (*i=='\\') *i='/';
#endif
   return p;
};

const std::string WinLux::normal_tilde="\\catcode`\\~=12\n";
const std::string WinLux::active_tilde="\\catcode`\\~=\\active\n";
