/*  Midgard Character Generator
 *  Copyright (C) 2004 Christof Petig 
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

#undef libmagus_COMPILATION
#include "Datenbank.hh"
#include "magustrace.h"
#include <Misc/Trace.h>
#include "AbenteurerAuswahl.h"
#include "NotFound.h"
#include "Ausgabe.hh"
#include <Misc/itos.h>
#include "libmagus.hh"
#include <sigc++/bind.h>

ManuProC::Tracer::Channel modelplex_chan=ManuProC::Tracer::channels.get();

static void progress(double d)
{  Ausgabe(Ausgabe::Log, "Progress " +itos(int(d*100))+ "%");
}

#include <iostream>
static void print(void*,const Optionen::st_OptionenCheck *oc,const char *x)
{std::cout << "Option @" << oc << "=" << oc->active.Value() << " "<< x <<"\n";
}
static void print2(void*p,const char *x)
{std::cout << "Model @" << p << "=" << *(int*)p << " "<< x <<"\n";
}

int main(int argc,char **argv)
{  ManuProC::Tracer::Enable(LibMagus::trace_channel,true);
   ManuProC::Tracer::Enable(modelplex_chan,true);
   Ausgabe::setLogLevel(Ausgabe::Debug);
 try {  
   libmagus_init(argc,const_cast<const char**>(argv),&progress);
   
   AbenteurerListe::Item t;
   Abenteurer &a=t.getAbenteurer();
   a.getOptionen().OptionenCheck(Optionen::NSC_only).active.signal_changed()
   	.connect(SigC::bind(SigC::slot(&print),&a.getOptionen()
   	.OptionenCheck(Optionen::NSC_only),"a."));
   t.proxies.checks[Optionen::NSC_only].signal_changed()
   	.connect(SigC::bind(SigC::slot(&print),&a.getOptionen()
   	.OptionenCheck(Optionen::NSC_only),"prox"));
   t.proxies.wizard.signal_changed()
   	.connect(SigC::bind(SigC::slot(&print2),"prox"));
   Model_ref<Wizard::esteps>(t.getWizard()).signal_changed()
           .connect(SigC::bind(SigC::slot(&print2),"t.getWizard"));
std::cout << "proxies &t="<< &t << "\n";
   t.proxies.checks[Optionen::NSC_only]=true;
   t.proxies.wizard=Wizard::START;
std::cout << "a direkt\n";
   a.getOptionen().setOptionCheck("NSC zulassen",true);
   t.getWizard().set(Wizard::GRUNDWERTE);
std::cout << "size " << AbenteurerAuswahl::Chars.size() << '\n';
 } catch (NotFound &e)
 {  Ausgabe(Ausgabe::Error, "NotFound "+ e.Name());  }
}
