// $Id: midgard_CG_drucken.cc,v 1.9 2003/09/10 07:15:43 christof Exp $   
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
  LaTeX_drucken L;
  L.latex_beschreibung_drucken(getAben());
}

// Dokument ///////////////////////////////////////////////////
void midgard_CG::on_abenteurerdokument_drucken()
{  
  LaTeX_drucken L;
  L.Ausdrucken(getAben());
}
 
// Leeres Dokument ///////////////////////////////////////////////////
void midgard_CG::on_leeres_abenteurerdokument_drucken()
{  
  LaTeX_drucken L;
  L.Ausdrucken();
}
 
void midgard_CG::on_alles_drucken()
{
  LaTeX_drucken L;
  L.Ausdrucken(getAben());
  L.latex_beschreibung_drucken(getAben());
  L.on_ausruestung_druck(getAben(),true);
  L.on_ausruestung_druck(getAben(),false);
}


void midgard_CG::on_latex()
{
  on_abenteurerdokument_drucken();
}
 

void midgard_CG::on_nur_sichtbares_drucken()
{
  LaTeX_drucken L;
  L.on_ausruestung_druck(getAben(),false);
}
    
void midgard_CG::on_auch_unsichtbares_drucken()
{ 
  LaTeX_drucken L;
  L.on_ausruestung_druck(getAben(),true);
}
        
// Spielleiterbogen ///////////////////////////////////////////////////////////
void midgard_CG::on_spielleiterbogen_drucken_activate()
{
  LaTeX_drucken L;
  L.Spielleiterbogen(getChar());
}
 