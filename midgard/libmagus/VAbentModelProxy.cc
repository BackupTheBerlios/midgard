// $Id: VAbentModelProxy.cc,v 1.7 2003/12/01 07:52:36 christof Exp $               
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

void VAbentModelProxy::divert(VAbenteurer::st_undo &A)
{  for (std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();
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
   wizard_mode=Model_ref<Wizard::mode>(A.wizard);
}

void VAbentModelProxy::divert(VAbenteurer::Item &A)
{  for (regionen_t::iterator i=A.proxies.regionen.begin();i!=A.proxies.regionen.end();++i)
      regionen[i->first].set_model(i->second);
   for (check_t::iterator i=A.proxies.checks.begin();i!=A.proxies.checks.end();++i)
      checks[i->first].set_model(i->second);
   for (haus_t::iterator i=A.proxies.hausregeln.begin();i!=A.proxies.hausregeln.end();++i)
      hausregeln[i->first].set_model(i->second);
   wizard.set_model(A.proxies.wizard);
   wizard_mode.set_model(A.proxies.wizard_mode);
   
   undo_changed.set_signal(A.signal_undo_changed());
   undo_list_changed.set_signal(A.signal_undo_list_changed());
   werte_eingeben.set_model(A.WerteEingebenModel());
}
