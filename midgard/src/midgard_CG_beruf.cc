// $Id: midgard_CG_beruf.cc,v 1.57 2002/03/12 12:01:56 thoma Exp $
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
//#include "Berufe_auswahl.hh"
#include <Gtk_OStream.h>
#include "Fertigkeiten.hh"
#include "class_Beruf_Data.hh"
#include "Beruf.hh"

gint midgard_CG::on_button_beruf_release_event(GdkEventButton *ev)
{
  deleteBerufsFertigekeit();
  if (ev->button==1) 
   {
     beruf_gewuerfelt(random.integer(1,100));
   }
  if (ev->button==3) 
   {
     vbox_berufsname->show();
     entry_berufsname->grab_focus();
   }
  table_berufswahl->set_sensitive(false);
  return false;
}

void midgard_CG::on_entry_berufsname_activate()
{
  cH_MidgardBasicElement beruf(&*cH_Beruf(entry_berufsname->get_text(),true));
  list_Beruf.clear();
  list_Beruf.push_back(beruf);
//  MidgardBasicElement_uebernehmen(beruf);
  vbox_berufsname->hide();
}

void midgard_CG::on_spinbutton_beruf_activate()
{
  gtk_spin_button_update(spinbutton_beruf->gtkobj());
  beruf_gewuerfelt(spinbutton_beruf->get_value_as_int());
}


void midgard_CG::deleteBerufsFertigekeit()
{
  for(std::list<cH_MidgardBasicElement>::iterator i=list_Fertigkeit.begin();i!=list_Fertigkeit.end();++i)
   {
     cH_Fertigkeit f(*i);
     if(f->LernArt()=="Beruf") 
      {
        list_Fertigkeit.erase(i);
        break;
      }
     else if(f->LernArt()=="Beruf+") 
      {
        (*i)->add_Erfolgswert(-1);
        f->setLernArt("");
        break;
      }
   }
}


void midgard_CG::showBerufsLernList()
{
  label_lernschma_titel->set_text("Beruf");
  std::list<cH_MidgardBasicElement> L;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Beruf.begin();i!=Database.Beruf.end();++i)
   {
//     if (Database.pflicht.istVerboten(Werte.Spezies()->Name(),Typ,(*i)->Name())) continue;
     if(Werte.Spezies()->istVerbotenSpielbegin(*i)) continue;
     cH_Beruf b(*i);
     if ( !b->Typ(Typ) ||  !b->Stand(Werte.Stand()) ) continue;
     if(!b->Stadt() && Werte.Stadt_Land()=="Stadt") continue;
     if(!b->Land()  && Werte.Stadt_Land()=="Land") continue;
     L.push_back(*i);
   }

  L.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME));
  std::vector<cH_RowDataBase> datavec;
  bool gelerntes=false;
  for(std::list<cH_MidgardBasicElement>::const_iterator i=L.begin();i!=L.end();++i)
    {
      cH_Beruf b(*i);
      std::vector<string> fert=b->Vorteile();
      for(std::vector<string>::const_iterator j=fert.begin();j!=fert.end();++j)
       {
         int kat;
         if(*j=="Schmecken+10") kat=1;
         else kat=cH_Fertigkeit(*j)->Berufskategorie();
         if( (kat==1 && BKategorie.kat_I)   || (kat==2 && BKategorie.kat_II) ||
             (kat==3 && BKategorie.kat_III) || (kat==4 && BKategorie.kat_IV ) )
           {
             if(*j!="Schmecken+10" && cH_Fertigkeit(*j)->ist_gelernt(list_Fertigkeit))
                  gelerntes=true;
             else gelerntes=false;
             datavec.push_back(new Beruf_Data(kat,(*i)->Name(),*j,gelerntes));
           }
       }
    }
  if(gelerntes) label_berufsstern_erklaerung->show();
  Beruf_tree->setDataVec(datavec);
  Beruf_tree->Expand_recursively();
  scrolledwindow_beruf->show();
  scrolledwindow_lernschema->hide();
  scrolledwindow_ange_fert->hide();
}

void midgard_CG::beruf_gewuerfelt(int wurf)
{
 BKategorie=st_BKategorie();
//TODO label_wuerfel->set_text("Würfelergebnis: "+itos(wurf));
 spinbutton_beruf->set_value(wurf);
 std::string kat;
 if(wurf<=20) kat="Kein(e) Beruf/Fertigkeit wählbar";
 if(21<=wurf&&wurf<=50)
  { kat="Eine Fertigkeit aus der Kategorie I wählbar";
    BKategorie.kat_I=true; }
 if(51<=wurf&&wurf<=80)
  { kat="Eine Fertigkeit aus der Kategorie I oder II wählbar";
    BKategorie.kat_I=true; 
    BKategorie.kat_II=true;}
 if(81<=wurf&&wurf<=95)
  { kat="Eine Fertigkeit aus der Kategorie I,II oder III wählbar";
    BKategorie.kat_I=true; 
    BKategorie.kat_II=true;
    BKategorie.kat_III=true;}
 if(96<=wurf&&wurf<=100)
  { kat="Eine Fertigkeit aus der Kategorie III oder IV \n oder zwei aus den Kategorien I und II wählbar (aber trotzdem nur EIN Beruf)";
    BKategorie.kat_I=true; 
    BKategorie.kat_II=true;
    BKategorie.kat_III=true;
    BKategorie.kat_IV=true; }
    label_berufskategorie->set_text(kat);
    label_berufskategorie->show();

  showBerufsLernList();
}

void midgard_CG::on_beruf_tree_leaf_selected(cH_RowDataBase d)
{
    const Beruf_Data *dt=dynamic_cast<const Beruf_Data*>(&*d);
    cH_MidgardBasicElement mbe(&*cH_Beruf(dt->Beruf()));
//    MidgardBasicElement_uebernehmen(mbe);
    list_Beruf.clear(); // es kann nur einen Beruf geben
    list_Beruf.push_back(mbe);
                   
    if(dt->Gelernt()) // Erfolgswert um eins erhöhen
      for (std::list<cH_MidgardBasicElement>::const_iterator k=list_Fertigkeit.begin();k!=list_Fertigkeit.end();++k)
        {
          if((*k)->Name()==dt->Fert())
           { (*k)->add_Erfolgswert(1);
             if((*k)->What()==MidgardBasicElement::FERTIGKEIT)
                cH_Fertigkeit(*k)->setLernArt("Beruf+");
           }
        }
    else // neue Fertigkeit
      {
         cH_MidgardBasicElement MBE(&*cH_Fertigkeit(dt->Fert()));
         cH_Fertigkeit(MBE)->setLernArt("Beruf");
         if(MBE->ZusatzEnum(Typ)) lernen_zusatz(MBE->ZusatzEnum(Typ),MBE);
         if(MBE->Name()!="Landeskunde (Heimat)")
            list_Fertigkeit.push_back(MBE);
      }
    if (!BKategorie.kat_IV || (dt->Kat()==3 || dt->Kat()==4))
      {
         tree_lernschema->clear();
         label_berufskategorie->set_text("");
         label_berufskategorie->hide();
         label_berufsstern_erklaerung->hide();
         scrolledwindow_beruf->hide();
         label_lernschma_titel->set_text("");
      }
    else
      {
         BKategorie.kat_IV=false;
      }
 show_gelerntes();
}
