// $Id: grundwerte_gw_wuerfeln.cc,v 1.4 2003/08/03 01:43:02 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "Grundwerte.hh"
#include <strstream>
#include <algorithm>
#include <Misc/itos.h>
#include <Misc/Trace.h>
#include "Random.hh"

static const UniqueValue::value_t trace_channel=ManuProC::Tracer::channels.get();
static ManuProC::Tracer::Environment trace_channel_e("DEBUG_GRUNDWERTE",trace_channel);

bool Grundwerte::check_350(const std::vector<int>& a) const
{
  ManuProC::Trace _t(trace_channel,__FUNCTION__);
  int sum=0;
  if(a.empty())
   { sum  = St() + Gs() + Gw() + Ko() + In() + Zt(); 
   }
  else
   { assert(a.size()==6);
     for (std::vector<int>::const_iterator i=a.begin();i!=a.end();++i)
       sum += *i;
   }   
  return sum>=350;
}

// war vorher in check_350
void Grundwerte::Au_pA_wuerfeln()
{ setAu(constraint_aw(Spezies()->Au()) );
  setpA( Random::W100()-30 + 3*(In()/10 + Au()/10) );
}

//////////////////////////////////////////////////////////////////////////

void Grundwerte::gw_wuerfeln_2x()
{   
  ManuProC::Trace _t(trace_channel,__FUNCTION__);
 setBasiswerte(constraint_gw(Spezies()->St()),
     constraint_gw(Spezies()->Gw()),
     constraint_gw(Spezies()->Gs()),
     constraint_gw(Spezies()->Ko()),
     constraint_gw(Spezies()->In()),
     constraint_gw(Spezies()->Zt()));
}

//static inline int max(int a,int b) { return a>b?a:b; }

int Grundwerte::constraint_gw(int constraint)
{
  ManuProC::Trace _t(trace_channel,__FUNCTION__);
 int wert;
 if      (constraint==0) wert = wuerfeln_best_of_two();
 else if (constraint<0) 
 {  wert = Random::integer(1,-constraint);
 }
 else if (constraint > 0) 
   { wert = wuerfeln_best_of_two();
     if (wert < constraint) wert = Random::integer(constraint,100);
   }
 return wert;
}

int Grundwerte::constraint_aw(int constraint)
{
  ManuProC::Trace _t(trace_channel,__FUNCTION__);
 if      (!constraint) return Random::W100();
 else if (constraint<0)  return Random::integer(1,-constraint); 
 else 			          return Random::integer(constraint,100);
}

int Grundwerte::wuerfeln_best_of_two()
{
  ManuProC::Trace _t(trace_channel,__FUNCTION__);
 int ran  = Random::W100();
 int ran2 = Random::W100();
 (ran > ran2) ? : ran=ran2;
 return ran;
}
