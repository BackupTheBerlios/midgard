// $Id: Window_lernpunkte_editieren.cc,v 1.13 2001/06/07 08:08:53 thoma Exp $
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

// generated 2001/2/7 8:11:20 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to lernpunkte_editieren.cc_glade

// This file is for your program, I won't touch it again!

#include "Window_lernpunkte_editieren.hh"
#include "midgard_CG.hh"

void Window_lernpunkte_editieren::on_close_clicked()
{   
  st_lernpunkte l;
  l.beruf        = atoi(lernpunkte_b_ein->get_text().c_str());
  l.fertigkeiten = atoi(lernpunkte_f_ein->get_text().c_str());
  l.waffen       = atoi(lernpunkte_w_ein->get_text().c_str());
  l.zauber       = atoi(lernpunkte_z_ein->get_text().c_str());
  
  hauptfenster->setze_lernpunkte(l);
  destroy();
}

Window_lernpunkte_editieren::Window_lernpunkte_editieren(midgard_CG* h, st_lernpunkte& l)
{
  hauptfenster=h;
  lernpunkte_b_ein->set_text(itos(l.beruf));
  lernpunkte_f_ein->set_text(itos(l.fertigkeiten));
  lernpunkte_w_ein->set_text(itos(l.waffen));
  lernpunkte_z_ein->set_text(itos(l.zauber));
}
