// $Id: midgard_CG_region_check.cc,v 1.18 2001/06/12 09:31:06 thoma Exp $
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

bool midgard_CG::region_check(const string& region)
{
//cout << "region = "<<"\t"<<region<<"\t"<<BRbool<<"\n";
  if (region=="") return true;  

  if (region=="K" && KanThaiPanbool) return true;
  if (region=="S" && Kuestenstaatenbool) return true;
  if (region=="G" && Gildenbriefbool) return true;
  if (region=="A" && Albabool)       return true;
  if (region=="R" && Rawindrabool)     return true;
  if (region=="W" && Waelandbool)    return true;
  if (region=="E" && Escharbool)     return true;
  if (region=="N" && Nahuatlanbool)  return true;
  if (region=="H&D" && HDbool)     return true;
  if (region=="B&R" && BRbool)     return true;

  else return false;
}
