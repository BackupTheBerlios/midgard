// $Id: VAbenteurer.cc,v 1.1 2003/09/01 06:48:57 christof Exp $            
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

#include "VAbenteurer.hh"
#include <sstream>
#include <Misc/Trace.h>
#include "magustrace.h"

void VAbenteurer::undosave(const std::string &s)
{
  modified();
  std::stringstream ss;
  ai->abenteurer.speicherstream(ss);
  ai->undo.push_back(s,ss.str());
}

void VAbenteurer::push_back()
{ 
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   VA.push_back(st_abenteurer()); 
   ai=--VA.end(); 
}


void VAbenteurer::setAbenteurer(const std::list<VAbenteurer::st_abenteurer>::iterator &i)
{
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
 ai=i;
}

bool VAbenteurer::unsaved_exist()
{ 
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
   for(std::list<st_abenteurer>::iterator i=VA.begin();i!=VA.end();++i)
       if(!i->gespeichert) return true;
   return false;
}

void VAbenteurer::delete_empty()
{ 
  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
 reloop:
   ai=--VA.end(); 
   for(std::list<st_abenteurer>::iterator i=VA.begin();i!=VA.end();++i)
    { const Grundwerte &W=i->abenteurer; 
      if(i->gespeichert && W.Name_Abenteurer().empty())
        { VA.erase(i); 
          goto reloop;
        } 
    }
}

