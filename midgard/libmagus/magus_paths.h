// $Id: magus_paths.h,v 1.8 2006/01/08 08:46:28 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003-2004 Christof Petig
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

#ifndef _MAGUS_PATHS
#  define _MAGUS_PATHS

#include <string>
#include <vector>
#include "libmagus_dll.h"

// small class for determining file positions (originally part of midgard_CG)
class magus_paths
{protected:
        static LIBMAGUS_API std::string argv0; // Dateiname
        static LIBMAGUS_API std::string magus_verzeichnis;
        static LIBMAGUS_API std::vector<std::string> paths;
public:
         static void init(const std::string &_argv0,const std::string &_magus_verzeichnis="");
         static const std::string &MagusVerzeichnis() {return magus_verzeichnis;}
         static const std::string &getArgv0() { return argv0; }
         static std::string BinaryVerzeichnis();
         static std::string with_path(const std::string &name,bool path_only=false,bool noexit=false);
         static void append_dir(const std::string &name);
         static void prepend_dir(const std::string &name);
         
#ifdef __MINGW32__
private:
         static void register_magus(const std::string &argv0);
public:
         static void register_magus();
#endif
};

#endif
