// $Id: VAbenteurer.cc,v 1.4 2003/11/24 16:21:42 christof Exp $            
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

static VAbenteurer::Item::iterator unconstify(const VAbenteurer::Item::const_iterator &i)
{  return reinterpret_cast<const VAbenteurer::Item::iterator &>(i);
}

void VAbenteurer::Item::undosave(const std::string &s)
{
  modified();
  current_undo->text=s;
  iterator i=unconstify(current_undo);
  ++i;
  if (i!=end()) undos.erase(i,unconstify(end()));
  undos.push_back(st_undo(getAbenteurer()));
  current_undo=--undos.end();
}

void VAbenteurer::Item::setUndo(const_iterator it)
{  current_undo=unconstify(it);
   _signal_undo_changed();
}

VAbenteurer::iterator VAbenteurer::push_back()
{ 
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   VA.push_back(st_abenteurer()); 
   return --end();
}


void AbenteurerAuswahl::setAbenteurer(const VAbenteurer::iterator &i)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
 ai=i;
 // signal!!!
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

VAbenteurer AbenteurerAuswahl::Chars;

VAbenteurer::iterator AbenteurerAuswahl::actualIterator()
{  if (ai==Chars.end()) ai=Chars.push_back();
   return ai;
}

VAbenteurer::const_iterator AbenteurerAuswahl::actualIterator() const
{  return const_cast<AbenteurerAuswahl*>(this)->actualIterator();
}

AbenteurerAuswahl::AbenteurerAuswahl()
  : ai(Chars.end())
{  // actualIterator(); // mindestens einen erzeugen
   signal_anderer_abenteurer().connect(SigC::slot(*this,&AbenteurerAuswahl::divert_proxy));
}

bool AbenteurerAuswahl::valid() const
{  return ai!=Chars.end();
}

void AbenteurerAuswahl::divert_proxy()
{  proxies.divert(*actualIterator());
}

void VAbenteurer::st_abenteurer::divert_proxy()
{  // proxies.divert(*actualIterator()); ??
}
