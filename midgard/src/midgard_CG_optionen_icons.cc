// $Id: midgard_CG_optionen_icons.cc,v 1.32 2003/04/25 07:12:09 christof Exp $
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
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

void midgard_CG::Icons_setzen()
{
  e_icon icon_counter=iNew;
  // toplevel toolbar
  for(Gtk::Toolbar_Helpers::ToolList::iterator i=toolbar_top->tools().begin();i!=toolbar_top->tools().end();++i)
   {
     if((*i).get_type()==Gtk::TOOLBAR_CHILD_SPACE) continue;      
     st_icons I=StyleIcon(icon_counter);
     icon_counter=e_icon(int(icon_counter)+1);

     if(dynamic_cast<Gtk::Image*>((*i).get_content())) 
        dynamic_cast<Gtk::Image*>((*i).get_content())->set((I.icon));
     if(dynamic_cast<Gtk::Label*>((*i).get_label())) 
        (*i).get_label()->set_text(I.text);
   }

  for(std::vector<st_buttons>::iterator i=IconVec.begin();i!=IconVec.end();++i)
   {
     Gtk::Widget *child = dynamic_cast<Gtk::Bin*>(i->widget)->get_child();     
     Box_setzen(child,StyleIcon(i->icon));
   }
  for(std::vector<st_buttons>::iterator i=IconVecBin.begin();i!=IconVecBin.end();++i)
   {
     Gtk::Widget *child = dynamic_cast<Gtk::Bin*>(i->widget)->get_child();     
     Bin_setzen(child,StyleIcon(i->icon));
   }
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     Midgard_Optionen::IconIndex II=MOptionen->getIconIndex();
     Glib::RefPtr<Gdk::Pixbuf> rp=RegionenPic::PicModel((*i)->Pic(),II);
     (*i)->setRegionPix(rp);
     Glib::RefPtr<Gdk::Pixbuf> rps=RegionenPic::PicModel((*i)->Pic(),II,true);
     (*i)->setRegionPixSmall(rps);
   }
}

void midgard_CG::Box_setzen(Gtk::Widget *child,st_icons I)
{
  if(child && dynamic_cast<Gtk::Box*>(child)) 
   {
     Gtk::Box_Helpers::BoxList &ch=dynamic_cast<Gtk::Box*>(child)->children();
     for(Gtk::Box_Helpers::BoxList::iterator i=ch.begin();i!=ch.end();++i)
      {
        if(dynamic_cast<Gtk::Image*>((*i).get_widget())) 
            dynamic_cast<Gtk::Image*>((*i).get_widget())->set((I.icon));
        if(dynamic_cast<Gtk::Label*>((*i).get_widget()) )
            dynamic_cast<Gtk::Label*>((*i).get_widget())->set_text(I.text);
      }
   }
  else if(child && dynamic_cast<Gtk::Bin*>(child)) 
     Box_setzen(dynamic_cast<Gtk::Bin*>(child)->get_child(),I);
}

void midgard_CG::Bin_setzen(Gtk::Widget *child,st_icons I)
{
  if(child && dynamic_cast<Gtk::Image*>(child))
     dynamic_cast<Gtk::Image*>(child)->set((I.icon));
}

midgard_CG::st_icons midgard_CG::StyleIcon(e_icon typ) const
{  bool ulf=MOptionen->IconCheck(Midgard_Optionen::Ulf).active;
     if     (typ==iNew)        return st_icons("Neu"         ,MagusImage("NewChar-trans-50.xpm")   );
     else if(typ==iOpen)       return st_icons("Öffnen"      ,MagusImage("LoadChar-trans-50.xpm")  );
     else if(typ==iClose)      return st_icons("Speichern"   ,MagusImage("SaveChar-trans-50.xpm")  );
     else if(typ==iPrint)      return st_icons("Drucken"     ,MagusImage("PrintChar-trans-50.xpm") );
     else if(typ==iBack)       return st_icons("Zurück"      ,MagusImage("Undo.xpm")               );
     else if(typ==iForward)    return st_icons("Vorwärts"    ,MagusImage("redo.xpm")               );
     else if(typ==iMenu)       return st_icons("Menü"        ,MagusImage("wizzard-trans-50_2.xpm") );
     else if(typ==iInfo)       return st_icons("Info"        ,MagusImage("Info-trans-50.xpm")      );
     else if(typ==iInstruction)return st_icons("Anleitung"   ,MagusImage("Help-trans-new1.xpm")    );
     else if(typ==iExit)       return st_icons("Schließen"   ,MagusImage("Exit-trans-50.xpm")      );
     else if(typ==iJa)         return st_icons("Ja"          ,MagusImage("Excl-32.xpm"));
     else if(typ==iNein)       return st_icons("Nein"        ,MagusImage("Nein-32.xpm"));
     else if(typ==iOK)         return st_icons("Fenster\nschließen",MagusImage("Yellow-Dice-trans-50.xpm"));
     else if(typ==iErase)      return st_icons("Textfeld\nlöschen",MagusImage("Clear-32.xpm"));
     else if(typ==iEigenschaften)return st_icons("Eigen-\nschaften",MagusImage("Dice-W100-trans-50.xpm"));
     else if(typ==iAbgeleitet) return st_icons("Abgeleitete-\nWerte",MagusImage("Dices2-trans-50.xpm"));
     else if(typ==iEditGrund)  return st_icons("Werte\neditieren",MagusImage("EditChar-trans-50.xpm"));
     else if(typ==iAngeFert) return st_icons(ulf?"angeb. Fert.":"angeborene Fertigkeiten"  ,MagusImage("Angeb_All-32.xpm"));
     else if(typ==iLernpunkte) return st_icons("Lernpunkte"  ,MagusImage("Dice-2W6-trans-50.xpm"));
     else if(typ==iLernEdit)   return st_icons("Lernp. ed."  ,MagusImage("Edit-trans-50.xpm"));
     else if(typ==iEigenschaft)return st_icons("Eigensch."  ,MagusImage("Red-Dice-trans-50.xpm"));
     else if(typ==iBeruf)      return st_icons("Beruf"  ,MagusImage("Job-trans-50.xpm"));
     else if(typ==iGeld)       return st_icons("Geld"  ,MagusImage("Money-50.xpm"));
     else if(typ==iWaffen)     return st_icons("Waffen"  ,MagusImage("Weapon-trans-50.xpm"));
     else if(typ==iRuestung)   return st_icons("Rüstung"  ,MagusImage("Dice_Armor-trans-50.xpm"));
     else if(typ==iAusruestung)return st_icons("Ausrüstung"  ,MagusImage("Dice-Ausruest-50.xpm"));
     else if(typ==iBildeinfuegen)return st_icons("Abbildung"  ,MagusImage("Portrait-32.xpm"));
     else if(typ==iDeleteAusr  )return st_icons("Gegenstand\nlöschen"  ,MagusImage("Trash-32.xpm"));
     else if(typ==iDeleteA     )return st_icons("Abenteurer aus\nListe löschen"  ,MagusImage("KillChar-32.xpm"));
     else if(typ==iButtonSteigern)   return st_icons("Steigern"  ,MagusImage("Steigern-trans-32.xpm"));
     else if(typ==iButtonReduce)   return st_icons("Reduzieren"  ,MagusImage("Reduzieren-trans-32.xpm"));
     else if(typ==iButtonVerlernen)   return st_icons("Verlernen"  ,MagusImage("Verlernen-trans-32.xpm"));
     else if(typ==iStatusWizard)return st_icons(""  ,MagusImage("MAGUS_Logo_Tiny.xpm"));
     else if(typ==iStatusNPC)return st_icons(""  ,MagusImage("NSC-Mode-26.xpm"));
     else if(typ==iNotebookCredit)   return st_icons("Info & Credits"  ,MagusImage("MAGUS_Logo_Small.xpm"));
     else if(typ==iNotebookGrundwerte)   return st_icons("Grundwerte"  ,MagusImage("Grundwert_small.xpm"));
     else if(typ==iNotebookLernen)   return st_icons("Lernschema"  ,MagusImage("L_Schema_small.xpm"));
     else if(typ==iNotebookSteigern)   return st_icons("Steigern"  ,MagusImage("Steigern_small.xpm"));
//     else if(typ==iNotebookBeschreibung)   return st_icons("Beschreibung"  ,MagusImage("Descr.Char-40.xpm"));
//     else if(typ==iNotebookAusruestung)   return st_icons("Ausrüstung"  ,MagusImage("Ausruest_small.xpm"));
     else if(typ==iNotebookOptionen)   return st_icons("Optionen"  ,MagusImage("Regio_Hausregel-50.xpm"));
     else if(typ==iNotebookNEWS)   return st_icons("News & Geschichte"  ,MagusImage("NewsGeschichte.xpm"));
     else if(typ==iNotebookZufall)   return st_icons("Zufallsgenerator"  ,MagusImage("Z-NewChar.xpm"));
     else return st_icons("Unbekannt"  ,MagusImage("pinguin.xpm"));
  abort();
}
