// $Id: ResistenzUndCo.cc,v 1.2 2004/06/23 11:00:25 christof Exp $               
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

Handle<ResistenzUndCo> ResistenzUndCo::Ausdauer=new ResistenzUndCo(eAusdauer);
Handle<ResistenzUndCo> ResistenzUndCo::Abwehr=new ResistenzUndCo(eAbwehr);
Handle<ResistenzUndCo> ResistenzUndCo::Zaubern=new ResistenzUndCo(eZaubern);
Handle<ResistenzUndCo> ResistenzUndCo::Resistenz=new ResistenzUndCo(eResistenz);

std::string ResistenzUndCo::What_str(was_t was_ist_es)
{  if (was_ist_es==eAusdauer) return "Ausdauer";
   if (was_ist_es==eAbwehr) return "Abwehr";
   if (was_ist_es==eZaubern) return "Zaubern";
   if (was_ist_es==eResistenz) return "Resistenz";
   return "Schrott";
}
