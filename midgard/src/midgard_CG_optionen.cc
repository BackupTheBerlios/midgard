// $Id: midgard_CG_optionen.cc,v 1.127 2004/01/08 13:32:35 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "midgard_CG.hh"
#include "WindowInfo.hh"
#include <fstream>
#include <Misc/TagStream.h>
#include <xml.h>
#include <Misc/Trace.h>

void midgard_CG::lernschema_sensitive(bool active)
{
 ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__);
assert(active);
#warning hier fehlts
#if 0
   table_lernschema->frame_lernpunkte->set_sensitive(true);
   frame_steigern->set_sensitive(true);
   frame_lernschema->set_sensitive(true);
   table_lernschema->button_herkunft->set_sensitive(true);
   table_lernschema->button_lernpunkte->set_sensitive(true);
   table_lernschema->togglebutton_lernpunkte_edit->set_sensitive(true);
   table_lernschema->button_lernschema_geld->set_sensitive(true);
   table_lernschema->button_lernschema_waffen->set_sensitive(true);
   table_lernschema->button_ruestung->set_sensitive(true);   
   table_lernschema->button_ausruestung->set_sensitive(true);   
   table_lernschema->button_angeborene_fert->show();
   table_lernschema->button_kido_auswahl->set_sensitive(true);
   table_lernschema->button_angeborene_fert->set_sensitive(true);
   table_lernschema->button_beruf->set_sensitive(true);
#endif   
}

void midgard_CG::Schummeln()
{
#warning fehlt
#if 0
  if(schummeln)
   {
     MOptionen->set_Original(true,Magus_Optionen::Original);
     MOptionen->OptionenExecute_setzen_from_menu(Magus_Optionen::LernschemaSensitive);
     table_steigern->steigern_mit_EP_bool=false;
     MOptionen->set_Original(true,Optionen::NSC_only);
     table_grundwerte->edit_werte=true;
   }
  else
   {
     MOptionen->set_Original(false,Magus_Optionen::Original);
     table_steigern->steigern_mit_EP_bool=true;
     MOptionen->set_Original(false,Optionen::NSC_only);
     table_grundwerte->edit_werte=false;
   }
#endif   
}
