// $Id: Midgard_Info.hh,v 1.38 2002/04/24 07:34:11 thoma Exp $
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
#include "glademm_support.hh"

class cH_Region;
class midgard_CG;

#include <vector>

class Midgard_Info : public Midgard_Info_glade
{   
        friend class Midgard_Info_glade;
        
        std::string umbruch(std::string s)
   public:
        Midgard_Info(GlademmData *data);
        void set_Regionen(const std::vector<cH_Region>& Regionen);
        Gtk::ProgressBar *get_progressbar_regionen() const {return progressbar_regionen;}
        Gtk::ProgressBar *get_progressbar_laender() const {return progressbar_laender;}
        Gtk::ProgressBar *get_progressbar_ruestung() const {return progressbar_ruestung;}
        Gtk::ProgressBar *get_progressbar_lernschema() const {return progressbar_lernschema;}
        Gtk::ProgressBar *get_progressbar_beruf() const {return progressbar_beruf;}
        Gtk::ProgressBar *get_progressbar_ang_fert() const {return progressbar_ang_Fert;}
        Gtk::ProgressBar *get_progressbar_fertigkeiten() const {return progressbar_fertigkeiten;}
        Gtk::ProgressBar *get_progressbar_waffen() const {return progressbar_waffen;}
        Gtk::ProgressBar *get_progressbar_aliaswaffen() const {return progressbar_aliaswaffen;}
        Gtk::ProgressBar *get_progressbar_grundkenntnisse() const {return progressbar_grundkenntnisse;}
        Gtk::ProgressBar *get_progressbar_zauber() const {return progressbar_zauber;}
        Gtk::ProgressBar *get_progressbar_zauberwerk() const {return progressbar_zauberwerk;}
        Gtk::ProgressBar *get_progressbar_kido() const {return progressbar_kido;}
        Gtk::ProgressBar *get_progressbar_sprache() const {return progressbar_sprache;}
        Gtk::ProgressBar *get_progressbar_schrift() const {return progressbar_schrift;}
        Gtk::ProgressBar *get_progressbar_spezies() const {return progressbar_spezies;}
        Gtk::ProgressBar *get_progressbar_typen() const {return progressbar_typen;}
        Gtk::ProgressBar *get_progressbar_grad() const {return progressbar_grad;}
        Gtk::ProgressBar *get_progressbar_spezial() const {return progressbar_spezial;}
        Gtk::ProgressBar *get_progressbar_preise() const {return progressbar_preise;}
        void database_hide();
};
#endif
