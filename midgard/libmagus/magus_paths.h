// $Id: magus_paths.h,v 1.1 2003/05/07 10:57:50 christof Exp $
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

#ifndef _MAGUS_PATHS
#  define _MAGUS_PATHS

#include <string>

// small class for determining file positions (originally part of midgard_CG)
class magus_paths
{protected:
        std::string argv0; // Dateiname
        std::string magus_verzeichnis;
public:
         magus_paths(const std::string &_argv0,const std::string &_magus_verzeichnis)
         	: argv0(_argv0), magus_verzeichnis(_magus_verzeichnis) {}
         const std::string &MagusVerzeichnis() const {return magus_verzeichnis;}
         const std::string &getArgv0() const { return argv0; }
         std::string BinaryVerzeichnis() const;
        std::string with_path(const std::string &name,bool path_only=false,bool noexit=false) const ;
};

#endif
