// $Id: table_lernschema_beruf.cc,v 1.35 2003/09/05 08:29:29 christof Exp $
/*  Midgard Character Generator Copyright (C) 2001 Malte Thoma
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

#include "table_lernschema.hh"
#include <Gtk_OStream.h>
#include "Fertigkeiten.hh"
#include "class_Beruf_Data.hh"
#include "Beruf.hh"
#include <Misc/itos.h>
#include "midgard_CG.hh"
#include "LernListen.hh"
#include <libmagus/Random.hh>
#include <libmagus/Ausgabe.hh>

void table_lernschema::on_button_beruf()
{
  if(vabenteurer->getLernpunkte().getLernpunkte().Summe() != 0)
    {                                                  
      int s=vabenteurer->getLernpunkte().getLernpunkte().Summe();
      Ausgabe(Ausgabe::Error,"WARNUNG: Es sind noch "+itos(s)+" Lernpunkte "
         "übrig, die zunächst verbraucht werden müssen.");
      return ;                                          
    }
  if(!hauptfenster->getChar()->getOptionen().OptionenCheck(Optionen::NSC_only).active)
      button_beruf->set_sensitive(false);
  hauptfenster->getChar().getWizard().done(Wizard::BERUF1,hauptfenster->getChar().getAbenteurer());
  deleteBerufsFertigekeit();
  if (Programmoptionen.WerteEingebenModel().Value())
   {
     vbox_berufsname->show();
     entry_berufsname->grab_focus();
   }
   else  beruf_gewuerfelt(Random::integer(1,100));
}

void table_lernschema::on_entry_berufsname_activate()
{
  cH_MidgardBasicElement beruf(&*cH_Beruf(entry_berufsname->get_text(),true));
  hauptfenster->getChar()->List_Beruf().clear();
  hauptfenster->getChar()->List_Beruf().push_back(beruf);
  vbox_berufsname->hide();
  show_gelerntes();
}

bool table_lernschema::on_spinbutton_beruf_focus_in(GdkEventFocus *ev)
{ spinbutton_beruf->select_region(0,-1); return false;}

void table_lernschema::on_spinbutton_beruf_activate()
{
  spinbutton_beruf->update();
  table_berufsprozent->hide();
  beruf_gewuerfelt(spinbutton_beruf->get_value_as_int());
}


void table_lernschema::deleteBerufsFertigekeit()
{
  for(std::list<MBEmlt>::iterator i=hauptfenster->getChar()->List_Fertigkeit().begin();i!=hauptfenster->getChar()->List_Fertigkeit().end();++i)
   {
     if((*i)->LernArt()=="Beruf") 
      {
        hauptfenster->getChar()->List_Fertigkeit().erase(i);
        break;
      }
     else if((*i)->LernArt()=="Beruf+") 
      {
        (*i)->addErfolgswert(-1);
        (*i)->setLernArt("");
        break;
      }
   }
}


void table_lernschema::showBerufsLernList()
{
  clean_lernschema_trees();

  Beruf_tree = Gtk::manage(new SimpleTree(5));
  Beruf_tree->signal_leaf_selected().connect(SigC::slot(*static_cast<class table_lernschema*>(this), &table_lernschema::on_beruf_tree_leaf_selected));
  std::vector<std::string> beruf;
  beruf.push_back("Beruf"); 
  beruf.push_back("Gelernt"); 
  beruf.push_back("Fertigkeit");
  beruf.push_back("Erfolgswert");
  beruf.push_back("Kategorie"); 
  Beruf_tree->setTitles(beruf);       

  label_lernschma_titel->set_text("Beruf");
  std::list<MBEmlt> L=LernListen().getBeruf(hauptfenster->getChar().getAbenteurer());

  std::vector<cH_RowDataBase> datavec;
  bool gelerntes=false;
  for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
    {
      std::vector<Beruf::st_vorteil> V=LernListen().getBerufsVorteil(*i,vabenteurer->getLernpunkte().getBKategorie(),hauptfenster->getChar().getAbenteurer());
      for(std::vector<Beruf::st_vorteil>::const_iterator j=V.begin();j!=V.end();++j)
       {
         if(j->name!="Schmecken+10")         
            if(!(cH_Fertigkeit(j->name))->Voraussetzung(hauptfenster->getChar().getAbenteurer())) continue;
         datavec.push_back(new Beruf_Data((*(*i))->Name(),*j));
         if(j->gelernt) gelerntes=true;
       }
    }

  if(gelerntes) Ausgabe(Ausgabe::Log,
               "Ein * bezeichnet eine bereits gelernte Fertigkeit."
               " Für diese wird dann der Erfolgswert um eins erhöht.");
  Beruf_tree->setDataVec(datavec);
  Beruf_tree->show();
  Beruf_tree->Expand_recursively();
  scrolledwindow_lernen->add(*Beruf_tree);  
  scrolledwindow_lernen->show();
  frame_lernpunkte->set_sensitive(false);
}

void table_lernschema::beruf_gewuerfelt(int wurf)
{
  try{
  std::string kat=vabenteurer->getLernpunkte().getBKategorie().wuerfeln(wurf);
  Ausgabe(Ausgabe::ActionNeeded,kat);
  showBerufsLernList();
  }catch(std::exception &e) { Ausgabe(Ausgabe::Error,e.what()); }
}

void table_lernschema::on_beruf_tree_leaf_selected(cH_RowDataBase d)
{
 try{
    const Beruf_Data *dt=dynamic_cast<const Beruf_Data*>(&*d);
    cH_MidgardBasicElement cmbe(&*cH_Beruf(dt->getBeruf()));
    MBEmlt mbe(cmbe);
    hauptfenster->getChar()->List_Beruf().clear(); // es kann nur einen Beruf geben
    hauptfenster->getChar()->List_Beruf().push_back(mbe);

    bool zusatz = Beruf::Berufsfertigkeit(hauptfenster->getChar().getAbenteurer(),dt->getVorteil());
    if(zusatz) 
     { cH_MidgardBasicElement cMBE(&*cH_Fertigkeit(dt->getVorteil().name));
       MBEmlt MBE(cMBE);
       lernen_zusatz((*MBE)->ZusatzEnum(hauptfenster->getChar()->getVTyp()),MBE);
     }

    if (!vabenteurer->getLernpunkte().getBKategorie().kat_IV || (dt->getVorteil().kat==3 || dt->getVorteil().kat==4))
      {
         if(tree_lernschema) tree_lernschema->clear();
//         hauptfenster->set_status("");
         scrolledwindow_lernen->hide();
         label_lernschma_titel->set_text("");
         hauptfenster->getChar().getWizard().done(Wizard::BERUF,hauptfenster->getChar().getAbenteurer());
      }
    else
      {
         vabenteurer->getLernpunkte().getBKategorie().kat_IV=false;
      }
 show_gelerntes();
 }catch(std::exception &e) {Ausgabe(Ausgabe::Error,e.what());}
}
