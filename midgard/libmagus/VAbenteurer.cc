// $Id: VAbenteurer.cc,v 1.9 2004/03/22 07:49:21 christof Exp $            
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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

#include "AbenteurerAuswahl.h"
#include <sstream>
#include <Misc/Trace.h>
#include "magustrace.h"
#include <sigc++/object_slot.h>
#include <stdexcept>
#include <Ausgabe.hh>
#include <fstream>

VAbenteurer::iterator VAbenteurer::push_back_silent()
{ 
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   VA.push_back(st_abenteurer());
   iterator res=--VA.end(); 
   // reinitialize proxy connects (they have been copied)
   res->init();
   return res;
}

VAbenteurer::iterator VAbenteurer::push_back()
{ 
   ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   VAbenteurer::iterator i=push_back_silent();
   list_changed();
   return i;
}

bool VAbenteurer::unsaved_exist()
{ 
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   for(VAbenteurer::iterator i=begin();i!=end();++i)
       if(!i->gespeichert()) return true;
   return false;
}

void VAbenteurer::delete_empty()
{ 
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
 reloop:
   for(VAbenteurer::iterator i=begin();i!=end();++i)
    { const Grundwerte &W=i->getAbenteurer(); 
      if(i->gespeichert() && W.Name_Abenteurer().empty())
        { VA.erase(i); 
          goto reloop;
        } 
    }
}

VAbenteurer::iterator VAbenteurer::load(std::istream &datei)
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,"std::istream");
   iterator i=push_back_silent();
   try
   {  if(!(i->getAbenteurer().xml_import_stream(datei)))
      {  Ausgabe(Ausgabe::Error,"XML Aufbau fehlerhaft");
         throw std::runtime_error("XML fehlerhaft");
      }
      i->saved();
      list_changed();
      return i;
   }
   catch (...)
   {  erase_silent(i);
      throw;
   }
}

VAbenteurer::iterator VAbenteurer::load(const std::string &dateiname)
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,dateiname);
   std::ifstream fi(dateiname.c_str());
   if (!fi.good()) 
   {  Ausgabe(Ausgabe::Error,"Kann '"+dateiname+"' nicht öffnen/lesen");
      throw std::runtime_error(dateiname);
   }
   try
   {  iterator i=load(fi);
      i->setFilename(dateiname);
      list_changed();
      return i;
   }
   catch (std::exception &e)
   {  Ausgabe(Ausgabe::Error,"Fehler "+std::string(e.what())+" beim Einlesen von '"+dateiname+"'");
      throw;
   }
}

VAbenteurer::iterator VAbenteurer::erase_silent(iterator i)
{  return VA.erase(i);
}

VAbenteurer::iterator VAbenteurer::erase(iterator j)
{  iterator i=erase_silent(j);
   list_changed();
   return i;
}

// ===================== Item =========================

void VAbenteurer::Item::divert_proxy()
{  ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__,this);
   proxies.divert(*current_undo);
   proxies.divert(*current_undo);
}

void VAbenteurer::Item::init()
{  ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__,this);
   current_undo=--undos.end();
   _signal_undo_changed.connect(SigC::slot(*this,&Item::divert_proxy));
   divert_proxy();
}

VAbenteurer::Item::Item(const Abenteurer &A,bool g) 
	: bgespeichert(g) 
{  ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__,this,g);
   undos.push_back(st_undo(A)); 
   init(); 
}
		
VAbenteurer::Item::Item(const Item &i) 
	: undos(i.undos), filename(i.filename), bgespeichert(i.bgespeichert)
{  ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__,this,"Item");
   init(); }


static VAbenteurer::Item::iterator unconstify(const VAbenteurer::Item::const_iterator &i)
{  return reinterpret_cast<const VAbenteurer::Item::iterator &>(i);
}

void VAbenteurer::Item::undosave(const std::string &s)
{ ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__,this,s);
  iterator i=unconstify(current_undo);
  ++i;
  if (i!=end()) undos.erase(i,unconstify(end()));
  undos.push_back(getUndo());
  current_undo=--undos.end();
  modified();
  current_undo->text=s;
  signal_undo_list_changed()();
}

void VAbenteurer::Item::setUndo(const_iterator it)
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,this,&*it);
   current_undo=unconstify(it);
   _signal_undo_changed();
}

// ================== AbenteurerAuswahl ====================

void AbenteurerAuswahl::setAbenteurer(const VAbenteurer::iterator &i)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
 ai=i;
 signal_anderer_abenteurer()();
}

AbenteurerAuswahl::AbenteurerAuswahl()
  : ai(Chars.end())
{  // actualIterator(); // mindestens einen erzeugen
   signal_anderer_abenteurer().connect(SigC::slot(*this,&AbenteurerAuswahl::divert_proxy));
#warning mit undo_changed noch verbinden?   
}

bool AbenteurerAuswahl::valid() const
{  return ai!=Chars.end();
}

void AbenteurerAuswahl::divert_proxy()
{  ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__);
   proxies.divert(*actualIterator());
}

VAbenteurer AbenteurerAuswahl::Chars;

VAbenteurer::iterator AbenteurerAuswahl::actualIterator()
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,this);
   if (ai==Chars.end()) ai=Chars.push_back();
   return ai;
}

VAbenteurer::const_iterator AbenteurerAuswahl::actualIterator() const
{  return const_cast<AbenteurerAuswahl*>(this)->actualIterator();
}

