// $Id: midgard_CG_optionen_icons.cc,v 1.9 2002/09/09 06:48:02 thoma Exp $
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

  // Grundwerte
  child = dynamic_cast<Gtk::Bin*>(table_grundwerte->button_grundwerte)->get_child();
  Box_setzen(child,StyleIcon(iEigenschaften));
  child = dynamic_cast<Gtk::Bin*>(table_grundwerte->button_abg_werte)->get_child();
  Box_setzen(child,StyleIcon(iAbgeleitet));
  child = dynamic_cast<Gtk::Bin*>(table_grundwerte->togglebutton_edit_werte)->get_child();
  Box_setzen(child,StyleIcon(iEditGrund));
  // Lernschema
  child = dynamic_cast<Gtk::Bin*>(table_lernschema->button_lernpunkte)->get_child();
  Box_setzen(child,StyleIcon(iLernpunkte));
  child = dynamic_cast<Gtk::Bin*>(table_lernschema->togglebutton_lernpunkte_edit)->get_child();
  Box_setzen(child,StyleIcon(iLernEdit));
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
#include "../pixmaps/Dice-W100-trans-50.xpm" 
#include "../pixmaps/Dices2-trans-50.xpm"
#include "../pixmaps/EditChar-trans-50.xpm" 
#include "../pixmaps/Dice-2W6-trans-50.xpm" 
#include "../pixmaps/Edit-trans-50.xpm" 

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
#include "../pixmaps/Ulf/ulf_24_editieren.xpm"
#include "../pixmaps/Ulf/ulf_24_wuerfel.xpm"

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
     else if(typ==iEigenschaften)return st_icons("Eigen-\nschaften",Dice_W100_trans_50_xpm);
     else if(typ==iAbgeleitet) return st_icons("Abgeleitete-\nWerte",Dices2_trans_50_xpm);
     else if(typ==iEditGrund)  return st_icons("Werte\neditieren",EditChar_trans_50_xpm);
     else if(typ==iLernpunkte) return st_icons("Lernpunkte"  ,Dice_2W6_trans_50_xpm);
     else if(typ==iLernEdit)   return st_icons("Lernp. ed."  ,Edit_trans_50_xpm);
   }
  else if(MOptionen->IconCheck(Midgard_Optionen::Ulf).active)
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
     else if(typ==iNein)       return st_icons("Nein"        ,ulf_24_nein_xpm);
     else if(typ==iEigenschaften)return st_icons("Eigen-\nschaften",ulf_24_wuerfel_xpm);
     else if(typ==iAbgeleitet) return st_icons("Abgeleitete-\nWerte",ulf_24_wuerfel_xpm);
     else if(typ==iEditGrund)  return st_icons("Werte\neditieren",ulf_24_editieren_xpm);
     else if(typ==iLernpunkte) return st_icons("Lernpunkte"  ,ulf_24_wuerfel_xpm);
     else if(typ==iLernEdit)   return st_icons("Lernp. ed."  ,ulf_24_editieren_xpm);
   }
  assert(!"never get here");
  abort();
}
