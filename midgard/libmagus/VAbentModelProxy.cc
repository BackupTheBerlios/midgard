// $Id: VAbentModelProxy.cc,v 1.16 2004/11/29 13:54:23 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2003-2004 Christof Petig
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
#include "magustrace.h"
#include <Misc/TraceNV.h>
#if MPC_SIGC_VERSION>=0x200
#include <sigc++/compatibility.h>
#endif
#include <sigc++/bind.h>

void VAbentModelProxy::disconnect()
{  while (!sg_conns.empty()) 
   { sg_conns.begin()->disconnect();
     sg_conns.erase(sg_conns.begin());
   }
}

static void adaptor(void *ptr,SigC::Signal0<void> *sig)
{  (*sig)();
}

void VAbentModelProxy::divert(VAbenteurer::st_undo &A)
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,NV("st_undo",&A));
   disconnect();
   for (std::vector<cH_Region>::const_iterator i=Datenbank.Regionen.begin();
		i!=Datenbank.Regionen.end();++i)
      regionen[*i]=Model_ref<bool>(A.abenteurer.getRegion(*i));
   
   Optionen &o=A.abenteurer.getOptionen();
   for (std::list<Optionen::st_Haus>::iterator i=o.getHausregeln().begin();
   		i!=o.getHausregeln().end();++i)
      hausregeln[i->index]=Model_ref<bool>(i->active);
   for (std::list<Optionen::st_OptionenCheck>::iterator i=o.getOptionenCheck().begin();
   		i!=o.getOptionenCheck().end();++i)
      checks[i->index].set_model(Model_ref<bool>(i->active));
      
   wizard.set_model(Model_ref<Wizard::esteps>(A.wizard));
   wizard_mode=Model_ref<Wizard::mode>(A.wizard);
   sg_conns.push_back(A.abenteurer.wie_steigern.signal_changed()
         .connect(SigC::bind(SigC::slot(&adaptor),&sig_steigern_geaendert)));
   sg_conns.push_back(A.abenteurer.wie_steigern_variante.signal_changed()
         .connect(SigC::bind(SigC::slot(&adaptor),&sig_steigern_geaendert)));
   sg_conns.push_back(A.abenteurer.goldanteil.signal_changed()
         .connect(SigC::bind(SigC::slot(&adaptor),&sig_steigern_geaendert)));
   sg_conns.push_back(A.abenteurer.fpanteil.signal_changed()
         .connect(SigC::bind(SigC::slot(&adaptor),&sig_steigern_geaendert)));
   sg_conns.push_back(A.abenteurer.reduzieren.signal_changed()
         .connect(SigC::bind(SigC::slot(&adaptor),&sig_steigern_geaendert)));
   // it most likely changed, perhaps a crc can cover it  ...
   sig_steigern_geaendert();
}

void VAbentModelProxy::divert()
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   disconnect();
   for (regionen_t::iterator i=regionen.begin();i!=regionen.end();++i)
      i->second=Model_ref<bool>();
   
   for (check_t::iterator i=checks.begin();i!=checks.end();++i)
      i->second=Model_ref<bool>();
         
   for (haus_t::iterator i=hausregeln.begin();i!=hausregeln.end();++i)
         i->second=Model_ref<bool>();
      
   wizard.set_model(Model_ref<Wizard::esteps>());
   wizard_mode=Model_ref<Wizard::mode>();
   // it most likely changed, perhaps a crc can cover it  ...
   sig_steigern_geaendert();
}

void VAbentModelProxy::divert(VAbenteurer::Item &A)
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,NV("Item",&A));
   disconnect();
   for (regionen_t::iterator i=A.proxies.regionen.begin();i!=A.proxies.regionen.end();++i)
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
   sg_conns.push_back(A.proxies.sig_steigern_geaendert
         .connect(sig_steigern_geaendert.slot()));
   // it most likely changed, perhaps a crc can cover it  ...
   sig_steigern_geaendert();
}

VAbentModelProxy::~VAbentModelProxy()
{  disconnect();
}
