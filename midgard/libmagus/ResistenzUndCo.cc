// $Id: ResistenzUndCo.cc,v 1.3 2004/11/29 17:26:50 christof Exp $               
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

#include "ResistenzUndCo.hh"

Handle<const ResistenzUndCo> ResistenzUndCo::Ausdauer=new ResistenzUndCo(eAusdauer);
Handle<const ResistenzUndCo> ResistenzUndCo::Abwehr=new ResistenzUndCo(eAbwehr);
Handle<const ResistenzUndCo> ResistenzUndCo::Zaubern=new ResistenzUndCo(eZaubern);
Handle<const ResistenzUndCo> ResistenzUndCo::Resistenz=new ResistenzUndCo(eResistenz);

std::string ResistenzUndCo::What_str(was_t was_ist_es)
{  if (was_ist_es==eAusdauer) return "Ausdauer";
   if (was_ist_es==eAbwehr) return "Abwehr";
   if (was_ist_es==eZaubern) return "Zaubern";
   if (was_ist_es==eResistenz) return "Resistenz";
   return "Schrott";
}

Handle<const ResistenzUndCo> ResistenzUndCo::getMBE(was_t w)
{ switch (w)
  { case eAusdauer: return Ausdauer;
    case eAbwehr: return Abwehr;
    case eZaubern: return Zaubern;
    case eResistenz: return Resistenz;
  }
  abort();
}
