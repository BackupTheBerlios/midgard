// $Id: Window_Geld_eingeben.cc,v 1.23 2002/01/14 12:59:00 christof Exp $
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

#include "config.h"
#include "Window_Geld_eingeben.hh"
#include "Window_Waffe_Geld.hh"
#include "midgard_CG.hh"
#include "itos.h"

void Window_Geld_eingeben::on_button_close_clicked()
{   
  spinbutton_gold->update();
  spinbutton_silber->update();
  spinbutton_kupfer->update();
   Werte.setGeld(atoi(spinbutton_gold->get_text().c_str()),
                  atoi(spinbutton_silber->get_text().c_str()),
                  atoi(spinbutton_kupfer->get_text().c_str()));
   if (back == true) oberfenster->show_Geld();
   else hauptfenster->Geld_uebernehmen();
   destroy();
}

#warning Es gibt zwei Konstruktoren, je nachdem von wo aus diese Funktion 
#warning aufgerufen wird. Gibt es da eine bessere Lösung? MAT

Window_Geld_eingeben::Window_Geld_eingeben(Window_Waffe_Geld* h,Grundwerte& w)
: Werte(w)
{
  oberfenster = h;
  back = true;
  show_Geld();
}

Window_Geld_eingeben::Window_Geld_eingeben(midgard_CG* h,Grundwerte& w)
: Werte(w)
{
  hauptfenster = h;
  back = false;
  show_Geld();
}

void Window_Geld_eingeben::show_Geld()
{
  spinbutton_gold->set_text(itos(Werte.Gold()));
  spinbutton_silber->set_text(itos(Werte.Silber()));
  spinbutton_kupfer->set_text(itos(Werte.Kupfer()));
}

void Window_Geld_eingeben::on_spinbutton_gold_activate()
{   
 spinbutton_silber->grab_focus();
}   
void Window_Geld_eingeben::on_spinbutton_silber_activate()
{
 spinbutton_kupfer->grab_focus();
}
void Window_Geld_eingeben::on_spinbutton_kupfer_activate()
{
 on_button_close_clicked();
}
