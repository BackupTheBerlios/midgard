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

#include "Berufe_auswahl.hh"
#include "midgard_CG.hh"
#include <cstring>
#include <Gtk_OStream.h>
#include "zufall.h"
#include "Fertigkeiten.hh"
#include <Aux/itos.h>

#include <Aux/EntryValueIntString.h>
#include <rowdata.h>
class Beruf_Data : public RowDataBase
{
      int kat;
      std::string beruf,fert;
      bool gelernte_fertigkeit;

      std::string kat_to_str(const int kat) const
         { if (kat==1) return "I";
           else if (kat==2) return "II";
           else if (kat==3) return "III";
           else if (kat==4) return "IV";
           else return "?";
         }

   public:
      Beruf_Data(const int _kat,
                 const std::string &_beruf,
                 const std::string &_fert,
                 const bool _gelernte_fertigkeit)  
         :kat(_kat),beruf(_beruf),fert(_fert),
            gelernte_fertigkeit(_gelernte_fertigkeit) {}
         
      enum spalten{BERUF,GELERNT,FERT,KAT};
      
      virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
       {
         switch(spalten(seqnr))
          {
            case KAT: return cH_EntryValueIntString(kat_to_str(kat));
            case BERUF: return cH_EntryValueIntString(beruf);
            case FERT: return cH_EntryValueIntString(fert);
            case GELERNT: {
               if(gelernte_fertigkeit) return cH_EntryValueIntString("*");
               else return cH_EntryValueIntString("");
             }
          }
        return cH_EntryValueIntString("?");
       }
      int Kat() const {return kat;}
      std::string Beruf() const {return beruf;}
      std::string Fert() const {return fert;}
      bool Gelernt() const {return gelernte_fertigkeit;}
};
class cH_Beruf_Data : public Handle<const Beruf_Data>
{
protected:
 cH_Beruf_Data() {}
 public:
  cH_Beruf_Data(const Beruf_Data *r) : Handle<const Beruf_Data>(r){}
};
  

//////////////////////////////////////////////////////////////////
Berufe_auswahl::Berufe_auswahl(midgard_CG* h,  
  const Datenbank& _Database,
  const vector<cH_Typen>& _Typ,
  const Grundwerte& _Werte,
  std::list<cH_MidgardBasicElement>& _list_fert)
: list_fert(_list_fert),Typ(_Typ),Database(_Database),  Werte(_Werte)
{
  label_stern_erklaerung->hide();
  hauptfenster=h;
  spinbutton_wurf->hide();
  kat_I=false; kat_II=false; kat_III=false; kat_IV=false;
  setTitles();
  wuerfel();
}

void Berufe_auswahl::setTitles()
{
  std::vector<string> v;
  v.push_back("Beruf");
  v.push_back("Gelernt");
  v.push_back("Fertigkeit");
  v.push_back("Kategorie");
  Beruf_tree->setTitles(v);
}

gint Berufe_auswahl::on_button_wuerfel_button_release_event(GdkEventButton *ev)
{
  kat_I=false; kat_II=false; kat_III=false; kat_IV=false;
  if (ev->button==1) wuerfel();
  if (ev->button==3) spinbutton_wurf->show();
  return false;
}


void Berufe_auswahl::wuerfel()
{
 Random random;
 int wurf=random.integer(1,100);
 gewuerfelt(wurf);
}

void Berufe_auswahl::on_spinbutton_wurf_activate()
{
  gtk_spin_button_update(spinbutton_wurf->gtkobj());
  spinbutton_wurf->hide();
  gewuerfelt(spinbutton_wurf->get_value_as_int());
}

void Berufe_auswahl::gewuerfelt(int wurf)
{
 label_wuerfel->set_text("Würfelergebnis: "+itos(wurf));
 std::string kat;
 if(wurf<=20) kat="Kein(e) Beruf/Fertigkeit wählbar";
 if(21<=wurf&&wurf<=50)
  { kat="Eine Fertigkeit aus der Kategorie I wählbar"; 
    kat_I=true; }
 if(51<=wurf&&wurf<=80)
  { kat="Eine Fertigkeit aus der Kategorie I oder II wählbar"; 
    kat_I=true; 
    kat_II=true;}
 if(81<=wurf&&wurf<=95)
  { kat="Eine Fertigkeit aus der Kategorie I,II oder III wählbar"; 
    kat_I=true; 
    kat_II=true;
    kat_III=true;}
 if(96<=wurf&&wurf<=100)
  { kat="Eine Fertigkeit aus der Kategorie III oder IV \n oder zwei aus den Kategorien I und II wählbar (aber trotzdem nur EIN Beruf)"; 
    kat_I=true; 
    kat_II=true;
    kat_III=true;
    kat_IV=true; }

 label_kategorie->set_text(kat);
 fill_list();
}

void Berufe_auswahl::fill_list()
{
  berufanzahl=0;
  Beruf_tree->clear();
  list_beruf.clear();  
  for(std::list<cH_MidgardBasicElement>::const_iterator i=Database.Beruf.begin();i!=Database.Beruf.end();++i)
   {
     cH_Beruf b(*i);
     if (hauptfenster->region_check(b->Region()))
       if (b->Typ(Typ) &&  b->Stand(Werte.Stand()) )
            list_beruf.push_back(*i);
   }
  list_beruf.sort(cH_MidgardBasicElement::sort(cH_MidgardBasicElement::sort::NAME));
  std::vector<cH_RowDataBase> datavec;
  for(std::list<cH_MidgardBasicElement>::iterator i=list_beruf.begin();i!=list_beruf.end();++i)
     {
      cH_Beruf b(*i);
      if(!b->Stadt() && Werte.Stadt_Land()=="Stadt") continue;
      if(!b->Land()  && Werte.Stadt_Land()=="Land") continue;
      std::vector<string> fert=b->Vorteile();
      for(std::vector<string>::const_iterator j=fert.begin();j!=fert.end();++j)
       {
         int kat;
         if(*j=="Schmecken+10") kat=1;
         else kat=cH_Fertigkeit(*j)->Berufskategorie();
         if( (kat==1 && kat_I)   || (kat==2 && kat_II) || 
             (kat==3 && kat_III) || (kat==4 && kat_IV ) )
           {
             if(*j!="Schmecken+10" && cH_Fertigkeit(*j)->ist_gelernt(list_fert))
                  datavec.push_back(new Beruf_Data(kat,(*i)->Name(),*j,true));
             else
                  datavec.push_back(new Beruf_Data(kat,(*i)->Name(),*j,false));
           }
       }
     }
  Beruf_tree->set_selection_mode(GTK_SELECTION_MULTIPLE);
  Beruf_tree->setDataVec(datavec);
  Beruf_tree->Expand_recursively();
}

void Berufe_auswahl::einBeruf(const Beruf_Data &dt)
{
  cH_MidgardBasicElement mbe(&*cH_Beruf(dt.Beruf()));
  if(!hauptfenster->SpracheSchrift(mbe))
     hauptfenster->MidgardBasicElement_uebernehmen(mbe);
  else hauptfenster->SpracheSchrift(mbe,mbe->Erfolgswert(),true); 
  if(dt.Gelernt()) // Erfolgswert um eins erhöhen
    for (std::list<cH_MidgardBasicElement>::const_iterator k=list_fert.begin();k!=list_fert.end();++k)
      {
        if((*k)->Name()==dt.Fert()) 
         { (*k)->add_Erfolgswert(1);
           if((*k)->What()==MidgardBasicElement::FERTIGKEIT)
              cH_Fertigkeit(*k)->setLernArt("Beruf+");
         }
      }        
  else // neue Fertigkeit
    {
       cH_MidgardBasicElement saf(&*cH_Fertigkeit(dt.Fert()));       
       hauptfenster->MidgardBasicElement_uebernehmen(saf,true);
    }
}

void Berufe_auswahl::on_leaf_selected(cH_RowDataBase d)
{
  const Beruf_Data *dt(dynamic_cast<const Beruf_Data*>(&*d));
  einBeruf(*dt);
  if(!kat_IV || (dt->Kat()==3 || dt->Kat()==4) )
   {
     destroy();
   }
  else 
   {
     if(++berufanzahl==2) destroy();
   }
}

void Berufe_auswahl::on_tree_unselect_row(gint row, gint column, GdkEvent *event)
{
  --berufanzahl;
}

void Berufe_auswahl::on_close_berufe_clicked(void)
{
/*
 try{
   std::vector<cH_RowDataBase> V=Beruf_tree->getSelectedRowDataBase_vec();
   if(V.empty())  destroy();
   else if(V.size()>2) return;
   else if(V.size()==1) 
      { const Beruf_Data *dt(dynamic_cast<const Beruf_Data*>(&*V[0]));
        einBeruf(*dt);
        destroy();
      }
   else if(V.size()==2)
    {
      for(std::vector<cH_RowDataBase>::const_iterator i=V.begin();i!=V.end();++i)
       { const Beruf_Data *dt(dynamic_cast<const Beruf_Data*>(&**i));
         einBeruf(*dt);
       }
      destroy();
    }
 }catch(std::exception &e) {cerr << e.what()<<'\n';}
*/
 destroy();
}
