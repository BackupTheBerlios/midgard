// $Id: Windows_Linux.hh,v 1.9 2002/07/10 08:07:04 thoma Exp $
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

#ifndef _WINLUX_HH_
#define _WINLUX_HH_

#ifdef __MINGW32__
#define NUR_LINUX(x...)
#define WINDOWS_LINUX(a,b) a
#else
#define NUR_LINUX(x...) x
#define WINDOWS_LINUX(a,b) b
#endif

#include <string>

namespace WinLux
{
  static const char dirsep=WINDOWS_LINUX('\\','/');
  static const char psep=WINDOWS_LINUX(';',':');
  // ~ in TeX als normales Zeichen (Dateiname) oder als festes Leerzeichen?
  extern const std::string normal_tilde, active_tilde;
  
  std::string recodePathForTeX(std::string p);
};

#endif
