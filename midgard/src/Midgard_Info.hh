// $Id: Midgard_Info.hh,v 1.21 2001/11/06 14:26:21 thoma Exp $
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

// generated 2001/4/1 21:32:45 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Midgard Info.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _MIDGARD_INFO_HH
#  include "Midgard_Info_glade.hh"
#  define _MIDGARD_INFO_HH
#include "glademm_support.hh"

class midgard_CG;

class Midgard_Info : public Midgard_Info_glade
{   
        
        midgard_CG* hauptfenster;
        friend class Midgard_Info_glade;
        gint timeout();
        SigC::Connection des;

   public:
        Midgard_Info(bool selfclean=false,midgard_CG* h=NULL);
        Gtk::ProgressBar *get_progressbar_laender() const {return progressbar_laender;}
        Gtk::ProgressBar *get_progressbar_ruestung() const {return progressbar_ruestung;}
        Gtk::ProgressBar *get_progressbar_ang_fert() const {return progressbar_ang_Fert;}
        Gtk::ProgressBar *get_progressbar_fertigkeiten() const {return progressbar_fertigkeiten;}
        Gtk::ProgressBar *get_progressbar_waffen() const {return progressbar_waffen;}
        Gtk::ProgressBar *get_progressbar_grundkenntnisse() const {return progressbar_grundkenntnisse;}
        Gtk::ProgressBar *get_progressbar_zauber() const {return progressbar_zauber;}
        Gtk::ProgressBar *get_progressbar_zauberwerk() const {return progressbar_zauberwerk;}
        Gtk::ProgressBar *get_progressbar_kido() const {return progressbar_kido;}
        Gtk::ProgressBar *get_progressbar_sprache() const {return progressbar_sprache;}
        Gtk::ProgressBar *get_progressbar_schrift() const {return progressbar_schrift;}
        Gtk::ProgressBar *get_progressbar_pflicht() const {return progressbar_pflicht;}
        Gtk::ProgressBar *get_progressbar_ausnahmen() const {return progressbar_ausnahmen;}
        void on_button_close_clicked();
};
#endif
