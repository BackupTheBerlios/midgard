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

// generated 2001/8/15 8:35:09 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to Window_Erfahrungspunkte.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_Erfahrungspunkte.hh"

#include "midgard_CG.hh"

void Window_Erfahrungspunkte::on_button_close_clicked()
{   
  spinbutton_AEP->update();
  spinbutton_KEP->update();
  spinbutton_ZEP->update();
  Werte.setEP(spinbutton_AEP->get_value_as_int(),
              spinbutton_KEP->get_value_as_int(),
              spinbutton_ZEP->get_value_as_int());
  hauptfenster->EP_uebernehmen();
  destroy();
}

Window_Erfahrungspunkte::Window_Erfahrungspunkte(midgard_CG* h,Grundwerte& w)
: Werte(w)
{
  hauptfenster=h;
  spinbutton_AEP->set_value(Werte.AEP());
  spinbutton_KEP->set_value(Werte.KEP());
  spinbutton_ZEP->set_value(Werte.ZEP());
}

void Window_Erfahrungspunkte::on_spinbutton_AEP_activate()
{
 spinbutton_KEP->grab_focus();
}

void Window_Erfahrungspunkte::on_spinbutton_KEP_activate()
{
 spinbutton_ZEP->grab_focus();
}

void Window_Erfahrungspunkte::on_spinbutton_ZEP_activate()
{
 on_button_close_clicked();
}
