// $Id: midgard_CG_attribut_check.cc,v 1.13 2001/06/07 08:08:53 thoma Exp $
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

int midgard_CG::attribut_check(string at)
{
   int b=0;

   if (at=="St" && werte.st>=81) ++b;
   if (at=="St" && werte.st>=96) ++b;
   if (at=="Ge" && werte.ge>=81) ++b;
   if (at=="Ge" && werte.ge>=96) ++b;
   if (at=="Ko" && werte.ko>=81) ++b;
   if (at=="Ko" && werte.ko>=96) ++b;
   if (at=="In" && werte.in>=81) ++b;
   if (at=="In" && werte.in>=96) ++b;
   if (at=="Zt" && werte.zt>=81) ++b;
   if (at=="Zt" && werte.zt>=96) ++b;
   if (at=="RW" && werte.rw>=81) ++b;
   if (at=="RW" && werte.rw>=96) ++b;
   if (at=="Sb" && werte.sb>=81) ++b;
   if (at=="Sb" && werte.sb>=96) ++b;
   if (at=="pA" && werte.pa>=81) ++b;
   if (at=="pA" && werte.pa>=96) ++b;
 return b;
}
