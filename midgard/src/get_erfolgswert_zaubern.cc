// $Id: get_erfolgswert_zaubern.cc,v 1.10 2001/05/25 10:22:38 thoma Exp $
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

string midgard_CG::get_erfolgswert_zaubern(const styp& typ,const styp& typ_2,const string& name)
{
   double fac = midgard_CG::get_standard_zauber(typ,typ_2,name);
   int ifac;
   if (fac == 0.5) ifac = 0; else ifac=-2;

   int ispez=0;
   if (typ.s=="Ma")   ispez = midgard_CG::get_spezial_zauber(typ.s,name);
   if (typ_2.s=="Ma") ispez = midgard_CG::get_spezial_zauber(typ_2.s,name);

   string erf = itos (atoi(werte.zaubern_wert.c_str())
                            +werte.bo_za + ifac + ispez) ;
   return(erf);
}
