// $Id: VAbentModelProxy.hh,v 1.9 2006/02/27 13:34:42 christof Exp $               
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

#ifndef CLASS_VABENTMODELPROXY_HH
#define CLASS_VABENTMODELPROXY_HH

#include <map>
#include <vector>
#include <BaseObjects/ModelPlex.h>
#include <BaseObjects/SignalPlex.h>
#include "Region.hh"
#include "Optionen.hh"
#include "Wizard.hh"

namespace AbenteurerListe {
class Item;
class st_undo;
}

struct VAbentModelProxy
{  // struct divert_base {};

   typedef std::map<cH_Region,ModelPlex<bool> > regionen_t; 
   regionen_t regionen;
   
   typedef std::map<Optionen::OptionenCheckIndex,ModelPlex<bool> > check_t;
   check_t checks;
   
   typedef std::map<Optionen::HausIndex,ModelPlex<bool> > haus_t;
   haus_t hausregeln;
   
   ModelPlex<Wizard::esteps> wizard;
   ModelPlex<Wizard::mode> wizard_mode;
   ModelPlex<bool> werte_eingeben;
   SignalPlex1<SigC::Signal0<void> > undo_changed;
   SignalPlex1<SigC::Signal0<void> > undo_list_changed;
   // dieses Signal feuert, wenn wie_steigern,goldanteil,fpanteil geändert wurde
private:   
   std::vector<SigC::Connection> sg_conns;
   VAbentModelProxy(const VAbentModelProxy &);
   const VAbentModelProxy &operator=(const VAbentModelProxy &);
public:   
   VAbentModelProxy() {}
   
   SigC::Signal0<void> sig_steigern_geaendert;
   
   void divert(AbenteurerListe::Item &new_one);
   void divert(AbenteurerListe::st_undo &new_one);
   // divert to nothing
   void divert();
   
   ~VAbentModelProxy();

private:
   void disconnect();
};
#endif
