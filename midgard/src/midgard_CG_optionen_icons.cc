// $Id: midgard_CG_optionen_icons.cc,v 1.19 2002/11/11 10:31:00 thoma Exp $
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
  menu_init();
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
  init_statusbar();
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

void midgard_CG::Bin_setzen(Gtk::Widget *child,st_icons I)
{
  if(child && Gtk::Pixmap::isA(child))
     dynamic_cast<Gtk::Pixmap*>(child)->set(I.icon);
}

#include "../pixmaps/pinguin.xpm"
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
//#include "../pixmaps/Erase-50.xpm"
#include "../pixmaps/Dice-W100-trans-50.xpm" 
#include "../pixmaps/Dices2-trans-50.xpm"
#include "../pixmaps/EditChar-trans-50.xpm" 
#include "../pixmaps/Dice-2W6-trans-50.xpm" 
#include "../pixmaps/Edit-trans-50.xpm" 
#include "../pixmaps/Red-Dice-trans-50.xpm" 
#include "../pixmaps/Yellow-Dice-trans-50.xpm"
#include "../pixmaps/Angeb_All-32.xpm" 
#include "../pixmaps/Job-trans-50.xpm" 
#include "../pixmaps/Money-50.xpm" 
#include "../pixmaps/Weapon-trans-50.xpm" 
#include "../pixmaps/Dice_Armor-trans-50.xpm" 
#include "../pixmaps/Dice-Ausruest-50.xpm" 
#include "../pixmaps/KillChar-32.xpm" 
#include "../pixmaps/Trash-32.xpm" 
//#include "../pixmaps/MAGUS_Logo_Small.xpm" 
#include "../pixmaps/MAGUS_Logo_Tiny.xpm" 
#include "../pixmaps/NSC-Mode-26.xpm" 
#include "../pixmaps/NewsGeschichte.xpm" 
#include "../pixmaps/L_Schema_small.xpm" 
#include "../pixmaps/Clear-32.xpm"
#include "../pixmaps/Nein-32.xpm"
#include "../pixmaps/Portrait-32.xpm"
#include "../pixmaps/Steigern-trans-32.xpm"
#include "../pixmaps/Reduzieren-trans-32.xpm"
#include "../pixmaps/Verlernen-trans-32.xpm"
#include "../pixmaps/MAGUS_Logo_Small.xpm"
#include "../pixmaps/Grundwert_small.xpm"
#include "../pixmaps/Steigern_small.xpm"
#include "../pixmaps/Regio_Hausregel-50.xpm"
#include "../pixmaps/Z-NewChar.xpm"


// Ulfs 24-Icons
#include "../pixmaps/Ulf/ulf_knopfleiste_24_anleitung.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_drucken.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_hilfe.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_info.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_menue.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_neu.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_oeffnen.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_schliessen.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_speichern.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_vorwaerts.xpm"
#include "../pixmaps/Ulf/ulf_knopfleiste_24_zurueck.xpm"
#include "../pixmaps/Ulf/ulf_notebook_24_bildeinfuegen.xpm"
#include "../pixmaps/Ulf/ulf_notebook_24_wuerfel.xpm"
#include "../pixmaps/Ulf/ulf_notebook_24_editieren.xpm"
//#include "../pixmaps/Ulf/ulf_notebook_24_loeschen.xpm"
#include "../pixmaps/Ulf/ulf_auswahl_16_ja.xpm"
#include "../pixmaps/Ulf/ulf_auswahl_16_nein.xpm"
#include "../pixmaps/Ulf/ulf_notebook_24_loeschen.xpm"
#include "../pixmaps/Ulf/ulf_notebook_24_reduzieren.xpm"
#include "../pixmaps/Ulf/ulf_notebook_24_steigern.xpm"
#include "../pixmaps/Ulf/ulf_notebook_24_verlernen.xpm"



//#include "../pixmaps/Ulf/ulf_24_editieren.xpm"
//#include "../pixmaps/Ulf/ulf_24_wuerfel.xpm"
#include "../pixmaps/Ulf/ulf_statusleiste_16_wizard.xpm"
#include "../pixmaps/Ulf/ulf_statusleiste_16_npczulassen.xpm"
//#include "../pixmaps/Ulf/ulf_zipfel_24_infocredits.xpm"
#include "../pixmaps/Ulf/ulf_zipfel_24_credits.xpm"
#include "../pixmaps/Ulf/ulf_zipfel_24_einstellungen.xpm"
#include "../pixmaps/Ulf/ulf_zipfel_24_grundwerte.xpm"
#include "../pixmaps/Ulf/ulf_zipfel_24_lernschema.xpm"
#include "../pixmaps/Ulf/ulf_zipfel_24_steigern.xpm"
#include "../pixmaps/Ulf/ulf_zipfel_24_verlauf.xpm"
#include "../pixmaps/Ulf/ulf_zipfel_24_zufallsgenerator.xpm"


midgard_CG::st_icons midgard_CG::StyleIcon(e_icon typ) const
{
  if(MOptionen->IconCheck(Midgard_Optionen::Self).active)
   {
     if     (typ==iNew)        return st_icons("Neu"         ,NewChar_trans_50_xpm   );
     else if(typ==iOpen)       return st_icons("�ffnen"      ,LoadChar_trans_50_xpm  );
     else if(typ==iClose)      return st_icons("Speichern"   ,SaveChar_trans_50_xpm  );
     else if(typ==iPrint)      return st_icons("Drucken"     ,PrintChar_trans_50_xpm );
     else if(typ==iBack)       return st_icons("Zur�ck"      ,Undo_xpm               );
     else if(typ==iForward)    return st_icons("Vorw�rts"    ,redo_xpm               );
     else if(typ==iMenu)       return st_icons("Men�"        ,wizzard_trans_50_2_xpm );
     else if(typ==iInfo)       return st_icons("Info"        ,Info_trans_50_xpm      );
     else if(typ==iHelp)       return st_icons("Hilfe"       ,Help_trans_new1_xpm    );
     else if(typ==iInstruction)return st_icons("Anleitung"   ,Help_trans_new1_xpm    );
     else if(typ==iExit)       return st_icons("Schlie�en"   ,Exit_trans_50_xpm      );
     else if(typ==iJa)         return st_icons("Ja"          ,Excl_32_xpm);
     else if(typ==iNein)       return st_icons("Nein"        ,Nein_32_xpm);
     else if(typ==iOK)         return st_icons("Fenster\nschlie�en",Yellow_Dice_trans_50_xpm);
     else if(typ==iErase)      return st_icons("Textfeld\nl�schen",Clear_32_xpm);
     else if(typ==iEigenschaften)return st_icons("Eigen-\nschaften",Dice_W100_trans_50_xpm);
     else if(typ==iAbgeleitet) return st_icons("Abgeleitete-\nWerte",Dices2_trans_50_xpm);
     else if(typ==iEditGrund)  return st_icons("Werte\neditieren",EditChar_trans_50_xpm);
     else if(typ==iAngeFert) return st_icons("angeborene Fertigkeiten"  ,Angeb_All_32_xpm);
     else if(typ==iLernpunkte) return st_icons("Lernpunkte"  ,Dice_2W6_trans_50_xpm);
     else if(typ==iLernEdit)   return st_icons("Lernp. ed."  ,Edit_trans_50_xpm);
     else if(typ==iEigenschaft)return st_icons("Eigensch."  ,Red_Dice_trans_50_xpm);
     else if(typ==iBeruf)      return st_icons("Beruf"  ,Job_trans_50_xpm);
     else if(typ==iGeld)       return st_icons("Geld"  ,Money_50_xpm);
     else if(typ==iWaffen)     return st_icons("Waffen"  ,Weapon_trans_50_xpm);
     else if(typ==iRuestung)   return st_icons("R�stung"  ,Dice_Armor_trans_50_xpm);
     else if(typ==iAusruestung)return st_icons("Ausr�stung"  ,Dice_Ausruest_50_xpm);
     else if(typ==iBildeinfuegen)return st_icons("Abbildung"  ,Portrait_32_xpm);
     else if(typ==iDeleteAusr  )return st_icons("Gegenstand l�schen"  ,Trash_32_xpm);
     else if(typ==iDeleteA     )return st_icons("Abenteurer aus\nListe l�schen"  ,KillChar_32_xpm);
     else if(typ==iButtonSteigern)   return st_icons("Steigern"  ,Steigern_trans_32_xpm);
     else if(typ==iButtonReduce)   return st_icons("Reduzieren"  ,Reduzieren_trans_32_xpm);
     else if(typ==iButtonVerlernen)   return st_icons("Verlernen"  ,Verlernen_trans_32_xpm);
     else if(typ==iStatusWizard)return st_icons(""  ,MAGUS_Logo_Tiny_xpm);
     else if(typ==iStatusNPC)return st_icons(""  ,NSC_Mode_26_xpm);
     else if(typ==iNotebookCredit)   return st_icons("Info & Credits"  ,MAGUS_Logo_Small_xpm);
     else if(typ==iNotebookGrundwerte)   return st_icons("Grundwerte"  ,Grundwert_small_xpm);
     else if(typ==iNotebookLernen)   return st_icons("Lernschema"  ,L_Schema_small_xpm);
     else if(typ==iNotebookSteigern)   return st_icons("Steigern"  ,Steigern_small_xpm);
//     else if(typ==iNotebookBeschreibung)   return st_icons("Beschreibung"  ,Descr.Char-40.xpm);
//     else if(typ==iNotebookAusruestung)   return st_icons("Ausr�stung"  ,Ausruest_small.xpm);
     else if(typ==iNotebookOptionen)   return st_icons("Optionen"  ,Regio_Hausregel_50_xpm);
     else if(typ==iNotebookNEWS)   return st_icons("News & Geschichte"  ,NewsGeschichte_xpm);
     else if(typ==iNotebookZufall)   return st_icons("Zufallsgenerator"  ,Z_NewChar_xpm);
     else return st_icons("Unbekannt"  ,pinguin_xpm);
   }
  else if(MOptionen->IconCheck(Midgard_Optionen::Ulf).active)
   {
     if     (typ==iNew)        return st_icons("Neu"         ,ulf_knopfleiste_24_neu_XPM   );
     else if(typ==iOpen)       return st_icons("�ffnen"      ,ulf_knopfleiste_24_oeffnen_xpm  );
     else if(typ==iClose)      return st_icons("Speichern"   ,ulf_knopfleiste_24_speichern_xpm  );
     else if(typ==iPrint)      return st_icons("Drucken"     ,ulf_knopfleiste_24_drucken_xpm );
     else if(typ==iBack)       return st_icons("Zur�ck"      ,ulf_knopfleiste_24_zurueck_xpm               );
     else if(typ==iForward)    return st_icons("Vorw�rts"    ,ulf_knopfleiste_24_vorwaerts_xpm               );
     else if(typ==iMenu)       return st_icons("Men�"        ,ulf_knopfleiste_24_menue_xpm );
     else if(typ==iInfo)       return st_icons("Info"        ,ulf_knopfleiste_24_info_xpm      );
     else if(typ==iHelp)       return st_icons("Hilfe"       ,ulf_knopfleiste_24_hilfe_xpm    );
     else if(typ==iInstruction)return st_icons("Anleitung"   ,ulf_knopfleiste_24_anleitung_xpm    );
     else if(typ==iExit)       return st_icons("Schlie�en"   ,ulf_knopfleiste_24_schliessen_xpm      );
     else if(typ==iJa)         return st_icons("Ja"          ,ulf_auswahl_16_ja_xpm);
     else if(typ==iNein)       return st_icons("Nein"        ,ulf_auswahl_16_nein_xpm);
     else if(typ==iOK)         return st_icons("Fenster\nschlie�en",ulf_auswahl_16_ja_xpm);
     else if(typ==iErase)      return st_icons("Textfeld\nl�schen",ulf_auswahl_16_nein_xpm);
     else if(typ==iEigenschaften)return st_icons("Eigen-\nschaften",ulf_notebook_24_wuerfel_xpm);
     else if(typ==iAbgeleitet) return st_icons("Abgeleitete-\nWerte",ulf_notebook_24_wuerfel_xpm);
     else if(typ==iEditGrund)  return st_icons("Werte\neditieren",ulf_notebook_24_editieren_xpm);
     else if(typ==iAngeFert) return st_icons("angeb. Fert."  ,ulf_notebook_24_wuerfel_xpm);
     else if(typ==iLernpunkte) return st_icons("Lernpunkte"  ,ulf_notebook_24_wuerfel_xpm);
     else if(typ==iLernEdit)   return st_icons("Lernp. ed."  ,ulf_notebook_24_editieren_xpm);
     else if(typ==iEigenschaft)return st_icons("Eigensch."  ,ulf_notebook_24_wuerfel_xpm);
     else if(typ==iBeruf)      return st_icons("Beruf"  ,ulf_notebook_24_wuerfel_xpm);
     else if(typ==iGeld)       return st_icons("Geld"  ,ulf_notebook_24_wuerfel_xpm);
     else if(typ==iWaffen)     return st_icons("Waffen"  ,ulf_notebook_24_wuerfel_xpm);
     else if(typ==iRuestung)   return st_icons("R�stung"  ,ulf_notebook_24_wuerfel_xpm);
     else if(typ==iAusruestung)return st_icons("Ausr�stung"  ,ulf_notebook_24_wuerfel_xpm);
     else if(typ==iBildeinfuegen)return st_icons("Abbildung"  ,ulf_notebook_24_bildeinfuegen_xpm);
     else if(typ==iDeleteAusr  )return st_icons("Gegenstand\nl�schen"  ,ulf_notebook_24_loeschen_xpm);
     else if(typ==iDeleteA     )return st_icons("Abenteurer aus\nListe l�schen"  ,ulf_notebook_24_loeschen_xpm);
     else if(typ==iStatusWizard)return st_icons(""  ,ulf_statusleiste_16_wizard_xpm);
     else if(typ==iStatusNPC)   return st_icons(""  ,ulf_statusleiste_16_npczulassen_xpm);
     else if(typ==iButtonSteigern)   return st_icons("Steigern"  ,ulf_notebook_24_steigern_xpm);
     else if(typ==iButtonReduce)   return st_icons("Reduzieren"  ,ulf_notebook_24_reduzieren_xpm);
     else if(typ==iButtonVerlernen)   return st_icons("Verlernen"  ,ulf_notebook_24_verlernen_xpm);
     else if(typ==iNotebookCredit)   return st_icons("Info & Credits"  ,ulf_zipfel_24_credits_xpm);
     else if(typ==iNotebookGrundwerte)   return st_icons("Grundwerte"  ,ulf_zipfel_24_grundwerte_xpm);
     else if(typ==iNotebookLernen)   return st_icons("Lernschema"  ,ulf_zipfel_24_lernschema_xpm);
     else if(typ==iNotebookSteigern)   return st_icons("Steigern"  ,ulf_zipfel_24_steigern_xpm);
//     else if(typ==iNotebookBeschreibung)   return st_icons("Beschreibung"  ,);
//     else if(typ==iNotebookAusruestung)   return st_icons("Ausr�stung"  ,);
     else if(typ==iNotebookOptionen)   return st_icons("Optionen"  ,ulf_zipfel_24_einstellungen_xpm);
     else if(typ==iNotebookNEWS)   return st_icons("News & Geschichte"  ,ulf_zipfel_24_verlauf_xpm);
     else if(typ==iNotebookZufall)   return st_icons("Zufallsgenerator"  ,ulf_zipfel_24_zufallsgenerator_xpm);
     else return st_icons("Unbekannt"  ,pinguin_xpm);
   }
  assert(!"never get here");
  abort();
}
