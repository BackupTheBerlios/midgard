// $Id: Midgard_Info.cc,v 1.45 2001/09/19 13:30:28 thoma Exp $
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

// generated 2001/4/1 21:39:00 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Midgard_Info.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Midgard_Info.hh"
#include <gtk--/main.h>
#include "midgard_CG.hh"

void Midgard_Info::on_button_close_clicked()
{   
  des.disconnect();
  destroy();
}

Midgard_Info::Midgard_Info(bool selfclean,midgard_CG* h)
:hauptfenster(h)
{
//   versionsnummer->set_text("Version: 0.8beta3");
   versionsnummer->set_text("Version: "+(std::string)VERSION);
   if (selfclean) 
    { toolbar_close->hide();
//      hauptfenster->hide();
      des = Gtk::Main::timeout.connect(slot(this,&Midgard_Info::timeout),8000);
    }
}

gint Midgard_Info::timeout()
{ 
 destroy();
// hauptfenster->show();
 return 0; 
}
      