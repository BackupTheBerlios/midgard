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

// generated 2001/5/14 14:50:20 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to Window_doppelcharaktere.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_doppelcharaktere.hh"
#include "table_grundwerte.hh"

void Window_doppelcharaktere::on_doppelklasse_button_nein_clicked()
{   
 destroy();
}

void Window_doppelcharaktere::on_doppelklasse_button_ja_clicked()
{   
 hauptfenster->doppelcharaktere();
 destroy();
}

Window_doppelcharaktere::Window_doppelcharaktere(table_grundwerte* h)
{
 hauptfenster=h;
}
