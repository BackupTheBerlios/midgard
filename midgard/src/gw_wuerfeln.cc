// $Id: gw_wuerfeln.cc,v 1.11 2001/05/25 16:18:39 thoma Exp $
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

// generated 2001/2/2 10:59:38 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to gw_wuerfeln.cc_glade

// This file is for your program, I won't touch it again!

#include "midgard_CG.hh"
#include <strstream>

void midgard_CG::gw_wuerfeln()
{   
 Random random;
 werte.st = constraint_gw(random,spezies_constraint.st);
 werte.ge = constraint_gw(random,spezies_constraint.ge);
 werte.ko = constraint_gw(random,spezies_constraint.ko);
 werte.in = constraint_gw(random,spezies_constraint.in);
 werte.zt = constraint_gw(random,spezies_constraint.zt);

 midgard_CG::zeige_werte(werte,"grund");
}

int midgard_CG::constraint_gw(Random& random,int constraint)
{
 int wert;
 if      (constraint==0) wert = wuerfeln_best_of_two(random);
 else if (constraint<0) 
   do wert = random.integer(1,100);
   while (wert > -constraint);
 else if (constraint > 0) 
   { wert = wuerfeln_best_of_two(random);
     while (wert < constraint) wert = random.integer(1,100);
   }
 return wert;
}

int midgard_CG::constraint_aw(Random& random,int constraint)
{
 int wert = random.integer(1,100);
 if      (constraint==0) return wert;
 else if (constraint<0) 
   while (wert > -constraint);
 else if (constraint > 0) 
   while (wert < constraint) wert = random.integer(1,100);
 return wert;
}

int midgard_CG::wuerfeln_best_of_two(Random& random)
{
 int ran  = random.integer(1,100);
 int ran2 = random.integer(1,100);
 (ran > ran2) ? : ran=ran2;
 return ran;
}
