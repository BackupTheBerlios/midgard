// $Id: midgard_CG_region_check.cc,v 1.25 2002/03/14 16:55:06 thoma Exp $
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

bool midgard_CG::region_check(const std::string& region)
{
//std::cout << "region = "<<"\t"<<flush<<region<<"\t"<<"\n";
  if (region=="") return true;  
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     if(region==(*i)->Abkuerzung() && (*i)->Active()) return true;
   }
  return false;
}

bool midgard_CG::nsc_check(bool nsc_only)
{
  if (nsc_only && !OptionenCheck(NSC_only).active) return false;
  return true;
}

