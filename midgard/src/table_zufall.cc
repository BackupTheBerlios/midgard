/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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

// generated 2002/9/6 20:10:27 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// newer (non customized) versions of this file go to table_zufall.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_zufall.hh"
#include "midgard_CG.hh"
#include "Zufall.hh"

void table_zufall::init(midgard_CG *h)
{
  hauptfenster=h;
}

void table_zufall::on_button_zufall_voll_clicked()
{
   bool old_value=hauptfenster->MOptionen->OberCheck(Midgard_Optionen::NoInfoFenster).active;
   hauptfenster->MOptionen->Ober_setzen_from_menu(Midgard_Optionen::NoInfoFenster,true);
   hauptfenster->getChar().push_back();
   hauptfenster->on_neuer_charakter_clicked();
   hauptfenster->table_lernschema->init(hauptfenster);
   
   Zufall zufall(hauptfenster);
   if(!togglebutton_vorgaben->get_active()) zufall.Voll();
   else
    {
      Zufall::e_Vorgabe v=Zufall::e_Vorgabe(0);
      if(!checkbutton_spezies->get_active()) v=Zufall::e_Vorgabe(v|Zufall::eSpezies);
      if(!checkbutton_typ->get_active())     v=Zufall::e_Vorgabe(v|Zufall::eTyp);
      zufall.Teil(v);
    }
   hauptfenster->MOptionen->Ober_setzen_from_menu(Midgard_Optionen::NoInfoFenster,old_value);
}

void table_zufall::on_togglebutton_vorgaben_toggled()
{
  if(togglebutton_vorgaben->get_active()) 
   {
     frame_vorgaben->show();
     hauptfenster->table_grundwerte->togglebutton_edit_werte->set_active(true);
   }
  else frame_vorgaben->hide();
}
