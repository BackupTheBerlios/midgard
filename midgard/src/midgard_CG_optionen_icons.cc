// $Id: midgard_CG_optionen_icons.cc,v 1.4 2002/09/04 14:28:17 thoma Exp $
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
     if     (typ==iNew)        return st_icons("Neu"         ,Neu_xpm   );
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
     else if(typ==iJa)         return st_icons("Ja"          ,Neu_xpm);
     else if(typ==iNein)       return st_icons("Nein"        ,Schliessen_xpm);
   }
  assert(!"never get here");
  abort();
}

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

