// $Id: Midgard_Info.hh,v 1.43 2003/09/29 06:56:09 christof Exp $
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

#ifndef _MIDGARD_INFO_HH
#  include "Midgard_Info_glade.hh"
#  define _MIDGARD_INFO_HH

class cH_Region;
class midgard_CG;

#include <vector>

class Midgard_Info : public Midgard_Info_glade
{   
        friend class Midgard_Info_glade;
        
        std::string umbruch(std::string s);
   public:
        Midgard_Info(GlademmData *data);
        void set_Regionen(const std::vector<cH_Region>& Regionen);
//        Gtk::ProgressBar *get_progressbar_regionen() const {return progressbar_regionen;}
//        void database_hide();
};
#endif
