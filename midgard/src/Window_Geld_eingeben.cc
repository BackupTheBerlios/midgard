// $Id: Window_Geld_eingeben.cc,v 1.7 2001/05/21 06:48:23 thoma Exp $
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

// generated 2001/3/12 10:16:00 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_Geld_eingeben.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_Geld_eingeben.hh"
#include "Window_Waffe_Geld.hh"
#include "midgard_CG.hh"
#include "itos.h"

void Window_Geld_eingeben::on_button_close_clicked()
{   
   werte.gold = atoi(spinbutton_gold->get_text().c_str());
   werte.silber = atoi(spinbutton_silber->get_text().c_str());
   werte.kupfer = atoi(spinbutton_kupfer->get_text().c_str());
   if (back == true) oberfenster->Geld();
   destroy();
}

Window_Geld_eingeben::Window_Geld_eingeben(Window_Waffe_Geld* h,st_werte& w)
: werte(w)
{
  oberfenster = h;
  back = true;
  spinbutton_gold->set_text(itos(werte.gold));
  spinbutton_silber->set_text(itos(werte.silber));
  spinbutton_kupfer->set_text(itos(werte.kupfer));
}

Window_Geld_eingeben::Window_Geld_eingeben(midgard_CG* h,st_werte& w)
: werte(w)
{
//  oberfenster = h;
  back = false;
  spinbutton_gold->set_text(itos(werte.gold));
  spinbutton_silber->set_text(itos(werte.silber));
  spinbutton_kupfer->set_text(itos(werte.kupfer));
}

