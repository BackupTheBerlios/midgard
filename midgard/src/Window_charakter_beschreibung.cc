// $Id: Window_charakter_beschreibung.cc,v 1.13 2001/06/07 08:08:53 thoma Exp $
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

// generated 2001/2/27 10:54:49 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_charakter_beschreibung.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_charakter_beschreibung.hh"
#include "midgard_CG.hh"

void Window_charakter_beschreibung::on_charakter_beschreibung_uebernehmen_clicked()
{   
 string b=text_charakter_beschreibung->get_chars(0,text_charakter_beschreibung->get_length());
 hauptfenster->charakter_beschreibung_uebernehmen(b);
 destroy();
}

void Window_charakter_beschreibung::on_charakter_beschreibung_drucken_clicked()
{
 string b=text_charakter_beschreibung->get_chars(0,text_charakter_beschreibung->get_length());
 hauptfenster->charakter_beschreibung_drucken(b);
 destroy();
}


void Window_charakter_beschreibung::on_charakter_beschreibung_abbrechen_clicked()
{   
  destroy();
}

Window_charakter_beschreibung::Window_charakter_beschreibung(midgard_CG* h, string s)
{
  hauptfenster=h;
  text_charakter_beschreibung->delete_text(0,text_charakter_beschreibung->get_length());
  gint pos=0;
  text_charakter_beschreibung->insert_text(s.c_str() , s.size(), &pos);  
}
