// $Id: midgard_CG_beruf.cc,v 1.48 2002/02/21 10:23:30 thoma Exp $
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
#include "Berufe_auswahl.hh"
#include <Gtk_OStream.h>
#include "Fertigkeiten.hh"
#include "class_Beruf_Data.hh"

gint midgard_CG::on_button_beruf_release_event(GdkEventButton *ev)
{
  deleteBerufsFertigekeit();
  if (ev->button==1) 
   {
     manage(new Berufe_auswahl(this,Database,Typ,Werte,list_Fertigkeit));
//     beruf_gewuerfelt(random.integer(1,100));
   }
  if (ev->button==3) 
   {
     vbox_berufsname->show();
     entry_berufsname->grab_focus();
   }
  button_beruf->set_sensitive(false);
  return false;
}

void midgard_CG::on_entry_berufsname_activate()
{
  cH_MidgardBasicElement beruf(&*cH_Beruf(entry_berufsname->get_text(),true));
  MidgardBasicElement_uebernehmen(beruf);
  vbox_berufsname->hide();
}

void midgard_CG::on_spinbutton_beruf_activate()
{
  gtk_spin_button_update(spinbutton_wurf->gtkobj());
  beruf_gewuerfelt(spinbutton_wurf->get_value_as_int());
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


void midgard_CG::showBerufsLernList(std::list<cH_MidgardBasicElement>& L)
{
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
               {
                  datavec.push_back(new Beruf_Data(kat,(*i)->Name(),*j,true));  
                  gelerntes=true;
               }
             else
                  datavec.push_back(new Beruf_Data(kat,(*i)->Name(),*j,false));
           }
       }
    }
  if(gelerntes) label_berufsstern_erklaerung->show();
  tree_lernschema->setDataVec(datavec);
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
}

