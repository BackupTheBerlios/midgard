// $Id: midgard_CG_optionen_icons.cc,v 1.2 2002/08/28 08:43:07 thoma Exp $
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
   }
  else if(MOptionen->IconCheck(Midgard_Optionen::Ulf).active)
   {
     return st_icons("Neu"         ,NewChar_trans_50_xpm   );
//     return pair<std::string,Gtk::Pixmap *>("Neu",manage(new Gtk::Pixmap(NewChar_trans_50_xpm)));
   }
  assert(!"never get here");
  abort();
}

void midgard_CG::Icons_setzen()
{
  e_icon icon_counter=iNew;
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
}
