// $Id: VAbentModelProxy.cc,v 1.3 2003/09/04 12:18:59 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2003 Christof Petig
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

#include "VAbentModelProxy.hh"
#include "VAbenteurer.hh"
#include "Datenbank.hh"

void VAbentModelProxy::divert(divert_base &new_one)
{  VAbenteurer::st_abenteurer &A=static_cast<VAbenteurer::st_abenteurer &>(new_one);
   for (std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();
		i!=Datenbank.Regionen.end();++i)
      regionen[*i]=Model_ref<bool>(A.abenteurer.getRegion(*i));
   
   Optionen &o=A.abenteurer.getOptionen();
   for (std::list<Optionen::st_Haus>::iterator i=o.getHausregeln().begin();
   		i!=o.getHausregeln().end();++i)
      hausregeln[i->index]=Model_ref<bool>(i->active);
   for (std::list<Optionen::st_OptionenCheck>::iterator i=o.getOptionenCheck().begin();
   		i!=o.getOptionenCheck().end();++i)
      checks[i->index]=Model_ref<bool>(i->active);
      
   wizard=Model_ref<Wizard::esteps>(A.wizard);
}
