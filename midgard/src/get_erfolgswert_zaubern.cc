// $Id: get_erfolgswert_zaubern.cc,v 1.21 2001/08/29 08:44:55 thoma Exp $
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

int midgard_CG::get_erfolgswert_zaubern(const Data_typen& Typ,const Data_typen& Typ2,const std::string& name)
{
   double fac = midgard_CG::get_standard_zauber(Typ,Typ2,name);
   int ifac;
   if (fac == 0.5) ifac = 0; else ifac=-2;

   int ispez=0;
   if (Typ.Short()=="Ma")   ispez = midgard_CG::get_spezial_zauber(Typ.Short(),name);
   if (Typ2.Short()=="Ma") ispez = midgard_CG::get_spezial_zauber(Typ2.Short(),name);

//   std::string erf = itos (atoi(werte.zaubern_wert.c_str())
//                            +werte.bo_za + ifac + ispez) ;
   int erf = Werte.Zaubern_wert()+Werte.bo_Za() + ifac + ispez ;
   return erf;
}
