// $Id: midgard_CG_optionen_icons.cc,v 1.7 2002/09/08 17:59:59 thoma Exp $
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

void midgard_CG::Icons_setzen()
{
  e_icon icon_counter=iNew;
  // toplevel toolbar
  for(Gtk::Toolbar_Helpers::ToolList::iterator i=toolbar_top->tools().begin();i!=toolbar_top->tools().end();++i)
   {
     if((*i)->get_type()==GTK_TOOLBAR_CHILD_SPACE) continue;      
     st_icons I=StyleIcon(icon_counter);
     icon_counter=e_icon(int(icon_counter)+1);

     if(Gtk::Pixmap::isA((*i)->get_content())) 
        dynamic_cast<Gtk::Pixmap*>((*i)->get_content())->set(I.icon);
     if(Gtk::Label::isA((*i)->get_label())) 
        (*i)->get_label()->set_text(I.text);
   }
  // InfoFenster
  Gtk::Widget *child = dynamic_cast<Gtk::Bin*>(InfoFenster->button_bestaetigen)->get_child();
  Box_setzen(child,StyleIcon(iJa));
  child = dynamic_cast<Gtk::Bin*>(InfoFenster->button_abbrechen)->get_child();
  Box_setzen(child,StyleIcon(iNein));
}

void midgard_CG::Box_setzen(Gtk::Widget *child,st_icons I)
{
  if(child && Gtk::Box::isA(child)) 
   {
     Gtk::Box_Helpers::BoxList &ch=dynamic_cast<Gtk::Box*>(child)->children();
     for(Gtk::Box_Helpers::BoxList::iterator i=ch.begin();i!=ch.end();++i)
      {
        if(Gtk::Pixmap::isA((*i)->get_widget())) 
            dynamic_cast<Gtk::Pixmap*>((*i)->get_widget())->set(I.icon);
        if(Gtk::Label::isA((*i)->get_widget()) )
            dynamic_cast<Gtk::Label*>((*i)->get_widget())->set_text(I.text);
      }
   }
}


#include "../pixmaps/NewChar-trans-50.xpm"
#include "../pixmaps/LoadChar-trans-50.xpm"
#include "../pixmaps/SaveChar-trans-50.xpm"
#include "../pixmaps/PrintChar-trans-50.xpm"
#include "../pixmaps/Undo.xpm"
#include "../pixmaps/redo.xpm"
#include "../pixmaps/wizzard-trans-50_2.xpm"
#include "../pixmaps/Info-trans-50.xpm"
#include "../pixmaps/Help-trans-50.xpm"
#include "../pixmaps/Exit-trans-50.xpm"
#include "../pixmaps/Excl-32.xpm"
#include "../pixmaps/Erase-50.xpm"
// Ulfs Icons
#include "../pixmaps/Anleitung.xpm"
#include "../pixmaps/Drucken.xpm"
#include "../pixmaps/Hilfe.xpm"
#include "../pixmaps/Info.xpm"
#include "../pixmaps/Menue.xpm"
#include "../pixmaps/Neu.xpm"
#include "../pixmaps/Oeffnen.xpm"
#include "../pixmaps/Schliessen.xpm"
#include "../pixmaps/Speichern.xpm"
#include "../pixmaps/Vorwaerts.xpm"
#include "../pixmaps/Zurueck.xpm"
#include "../pixmaps/Ulf/Ulf-Ja.xpm"
#include "../pixmaps/Ulf/Ulf-Nein.xpm"
// Ulfs 24-Icons
#include "../pixmaps/Ulf/ulf_24_anleitung.xpm"
#include "../pixmaps/Ulf/ulf_24_drucken.xpm"
#include "../pixmaps/Ulf/ulf_24_hilfe.xpm"
#include "../pixmaps/Ulf/ulf_24_info.xpm"
#include "../pixmaps/Ulf/ulf_24_menue.xpm"
#include "../pixmaps/Ulf/ulf_24_neu.xpm"
#include "../pixmaps/Ulf/ulf_24_oeffnen.xpm"
#include "../pixmaps/Ulf/ulf_24_schliessen.xpm"
#include "../pixmaps/Ulf/ulf_24_speichern.xpm"
#include "../pixmaps/Ulf/ulf_24_vorwaerts.xpm"
#include "../pixmaps/Ulf/ulf_24_zurueck.xpm"
#include "../pixmaps/Ulf/ulf_24_ja.xpm"
#include "../pixmaps/Ulf/ulf_24_nein.xpm"
// StefanP Icons
#include "../pixmaps/SP-Anleitung.xpm"
#include "../pixmaps/SP-Drucken.xpm"
#include "../pixmaps/SP-Hilfe.xpm"
#include "../pixmaps/SP-Info.xpm"
#include "../pixmaps/SP-Menue.xpm"
#include "../pixmaps/SP-Neu.xpm"
#include "../pixmaps/SP-Neugr.xpm"
#include "../pixmaps/SP-Oeffnen.xpm"
#include "../pixmaps/SP-Schliessen.xpm"
#include "../pixmaps/SP-Speichern.xpm"
#include "../pixmaps/SP-Vorwaerts.xpm"
#include "../pixmaps/SP-Zurueck.xpm"

midgard_CG::st_icons midgard_CG::StyleIcon(e_icon typ) const
{
  if(MOptionen->IconCheck(Midgard_Optionen::Self).active)
   {
     if     (typ==iNew)        return st_icons("Neu"         ,NewChar_trans_50_xpm   );
     else if(typ==iOpen)       return st_icons("Öffnen"      ,LoadChar_trans_50_xpm  );
     else if(typ==iClose)      return st_icons("Speichern"   ,SaveChar_trans_50_xpm  );
     else if(typ==iPrint)      return st_icons("Drucken"     ,PrintChar_trans_50_xpm );
     else if(typ==iBack)       return st_icons("Zurück"      ,Undo_xpm               );
     else if(typ==iForward)    return st_icons("Vorwärts"    ,redo_xpm               );
     else if(typ==iMenu)       return st_icons("Menü"        ,wizzard_trans_50_2_xpm );
     else if(typ==iInfo)       return st_icons("Info"        ,Info_trans_50_xpm      );
     else if(typ==iHelp)       return st_icons("Hilfe"       ,Help_trans_new1_xpm    );
     else if(typ==iInstruction)return st_icons("Anleitung"   ,Help_trans_new1_xpm    );
     else if(typ==iExit)       return st_icons("Schließen"   ,Exit_trans_50_xpm      );
     else if(typ==iJa)         return st_icons("Ja"          ,Excl_32_xpm);
     else if(typ==iNein)       return st_icons("Nein"        ,Erase_50_xpm);
   }
  else if(MOptionen->IconCheck(Midgard_Optionen::Ulf).active)
   {
     if     (typ==iNew)        return st_icons("Neu"         ,SP_Neugr_xpm   );
     else if(typ==iOpen)       return st_icons("Öffnen"      ,Oeffnen_xpm  );
     else if(typ==iClose)      return st_icons("Speichern"   ,Speichern_xpm  );
     else if(typ==iPrint)      return st_icons("Drucken"     ,Drucken_xpm );
     else if(typ==iBack)       return st_icons("Zurück"      ,Zurueck_xpm               );
     else if(typ==iForward)    return st_icons("Vorwärts"    ,Vorwaerts_xpm               );
     else if(typ==iMenu)       return st_icons("Menü"        ,Menue_xpm );
     else if(typ==iInfo)       return st_icons("Info"        ,Info_xpm      );
     else if(typ==iHelp)       return st_icons("Hilfe"       ,Hilfe_xpm    );
     else if(typ==iInstruction)return st_icons("Anleitung"   ,Anleitung_xpm    );
     else if(typ==iExit)       return st_icons("Schließen"   ,Schliessen_xpm      );
     else if(typ==iJa)         return st_icons("Ja"          ,Ulf_Ja_xpm);
     else if(typ==iNein)       return st_icons("Nein"        ,Ulf_Nein_xpm);
   }
  else if(MOptionen->IconCheck(Midgard_Optionen::Ulf24).active)
   {
     if     (typ==iNew)        return st_icons("Neu"         ,ulf_24_neu_xpm   );
     else if(typ==iOpen)       return st_icons("Öffnen"      ,ulf_24_oeffnen_xpm  );
     else if(typ==iClose)      return st_icons("Speichern"   ,ulf_24_speichern_xpm  );
     else if(typ==iPrint)      return st_icons("Drucken"     ,ulf_24_drucken_xpm );
     else if(typ==iBack)       return st_icons("Zurück"      ,ulf_24_zurueck_xpm               );
     else if(typ==iForward)    return st_icons("Vorwärts"    ,ulf_24_vorwaerts_xpm               );
     else if(typ==iMenu)       return st_icons("Menü"        ,ulf_24_menue_xpm );
     else if(typ==iInfo)       return st_icons("Info"        ,ulf_24_info_xpm      );
     else if(typ==iHelp)       return st_icons("Hilfe"       ,ulf_24_hilfe_xpm    );
     else if(typ==iInstruction)return st_icons("Anleitung"   ,ulf_24_anleitung_xpm    );
     else if(typ==iExit)       return st_icons("Schließen"   ,ulf_24_schliessen_xpm      );
     else if(typ==iJa)         return st_icons("Ja"          ,ulf_24_ja_xpm);
     else if(typ==iNein)       return st_icons("Nein"        ,ulf_24__nein_xpm);
   }
  else if(MOptionen->IconCheck(Midgard_Optionen::StefanP).active)
   {
     if     (typ==iNew)        return st_icons("Neu"         ,SP_Neu_xpm   );
     else if(typ==iOpen)       return st_icons("Öffnen"      ,SP_Oeffnen_xpm  );
     else if(typ==iClose)      return st_icons("Speichern"   ,SP_Speichern_xpm  );
     else if(typ==iPrint)      return st_icons("Drucken"     ,SP_Drucken_xpm );
     else if(typ==iBack)       return st_icons("Zurück"      ,SP_Zurueck_xpm               );
     else if(typ==iForward)    return st_icons("Vorwärts"    ,SP_Vorwaerts_xpm               );
     else if(typ==iMenu)       return st_icons("Menü"        ,SP_Menue_xpm );
     else if(typ==iInfo)       return st_icons("Info"        ,SP_Info_xpm      );
     else if(typ==iHelp)       return st_icons("Hilfe"       ,SP_Hilfe_xpm    );
     else if(typ==iInstruction)return st_icons("Anleitung"   ,SP_Anleitung_xpm    );
     else if(typ==iExit)       return st_icons("Schließen"   ,SP_Schliessen_xpm      );
     else if(typ==iJa)         return st_icons("Ja"          ,SP_Neu_xpm);
     else if(typ==iNein)       return st_icons("Nein"        ,SP_Schliessen_xpm);
   }
  assert(!"never get here");
  abort();
}
