// $Id: Midgard_Undo.cc,v 1.2 2002/04/18 17:51:07 thoma Exp $
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


#include "Midgard_Undo.hh"

void Midgard_Undo::push_back(std::string text,std::string speicher)
{
//  clear(count); // Wenn etwas angeh�ngt wird, dann alles ab hier l�schen
  count=VU.size();
  VU.push_back(st_undo(count,text,speicher));
}

std::string Midgard_Undo::get(unsigned int c)
{
cout << "Size= "<<VU.size()<<' '<<c<<'\t'<<flush;
cout << VU[c].speicher.size()<<'\n';
  if(VU.size()>c) return VU[c].speicher ;
  else            return "";
}

std::string Midgard_Undo::get_last() 
{
 std::string s=get(count);
 if(count>0) --count;
 return s;
}

std::string Midgard_Undo::get_next() 
{
 ++count;
 if(count>=VU.size()) count=VU.size()-1;
 return get(count);
}
