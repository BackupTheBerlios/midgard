// $Id: midgard_CG_drucken.cc,v 1.5 2002/12/12 11:20:14 christof Exp $   
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

#include "midgard_CG.hh"
#include "LaTeX_drucken.hh"

// Beschreibung ///////////////////////////////////////////////////
void midgard_CG::on_beschreibung_drucken()
{ 
  LaTeX_drucken L(this);
  L.latex_beschreibung_drucken();
}

// Dokument ///////////////////////////////////////////////////
void midgard_CG::on_abenteurerdokument_drucken()
{  
  LaTeX_drucken L(this);
  L.on_latex_clicked();
}
 
// Leeres Dokument ///////////////////////////////////////////////////
void midgard_CG::on_leeres_abenteurerdokument_drucken()
{  
  LaTeX_drucken L(this);
  L.on_latex_clicked(false);
}
 
void midgard_CG::on_alles_drucken()
{
  LaTeX_drucken L(this);
  L.on_latex_clicked();
  L.latex_beschreibung_drucken();
  L.on_ausruestung_druck(true);
  L.on_ausruestung_druck(false);
//  on_beschreibung_drucken();
//  on_nur_sichtbares_drucken();
//  on_auch_unsichtbares_drucken();
}


bool midgard_CG::on_latex_release_event(GdkEventButton *ev)
{
  if (ev->button==1) on_abenteurerdokument_drucken();
  if (ev->button==2) on_beschreibung_drucken();
  if (ev->button==3) on_nur_sichtbares_drucken();  
  return false;
}
 

// Ausrüstung ///////////////////////////////////////////////////
//gint midgard_CG::on_button_ausruestung_druck_release_event(GdkEventButton *event)
//{
//  if (event->button==1) on_auch_unsichtbares_drucken();
//  if (event->button==3) on_nur_sichtbares_drucken();
//  return false;
//}
      

void midgard_CG::on_nur_sichtbares_drucken()
{
  LaTeX_drucken L(this);
  L.on_ausruestung_druck(false);
}
    
void midgard_CG::on_auch_unsichtbares_drucken()
{ 
  LaTeX_drucken L(this);
  L.on_ausruestung_druck(true);
}
        
// Spielleiterbogen ///////////////////////////////////////////////////////////
void midgard_CG::on_spielleiterbogen_drucken_activate()
{
  LaTeX_drucken L(this);
  L.Spielleiterbogen();
}
 