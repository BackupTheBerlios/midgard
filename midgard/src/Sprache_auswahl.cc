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

#include "config.h"
#include "Sprache_auswahl.hh"
#include "midgard_CG.hh"
#include <Gtk_OStream.h>
#include "Schrift.hh"
#include "Sprache.hh"
#include "Waffe.hh"
#include "Fertigkeiten.hh"
#include "Zauber.hh"

void Sprache_auswahl::on_clist_sp_sc_select_row(gint row, gint column, GdkEvent *event)
{   
  std::string zusatz=clist_sp_sc->get_text(row,0);
  if (mod == GEHEIMZEICHEN)
   {
     cH_MidgardBasicElement F(new Fertigkeit(*cH_Fertigkeit("Geheimzeichen")));
     F->setZusatz(zusatz);
     F->set_Erfolgswert(wert);
     hauptfenster->MidgardBasicElement_uebernehmen(F);
   }
  else if (mod == ABRICHTEN)
   {
     cH_MidgardBasicElement F(new Fertigkeit(*cH_Fertigkeit("Abrichten")));
     F->setZusatz(zusatz);
     F->set_Erfolgswert(wert);
     hauptfenster->MidgardBasicElement_uebernehmen(F);
   }
  else if (mod == TIERSPRACHE)
   {
     cH_MidgardBasicElement F(new Zauber(*cH_Zauber("Tiersprache")));
     F->setZusatz(zusatz);
//     F->set_Erfolgswert(wert);
     hauptfenster->MidgardBasicElement_uebernehmen(F);
   }
  else if (mod == MUSIZIEREN)
   {
     cH_MidgardBasicElement F(new Fertigkeit(*cH_Fertigkeit("Musizieren")));
     cH_Fertigkeit(F)->setZusatz(zusatz);
     F->set_Erfolgswert(wert);
     hauptfenster->MidgardBasicElement_uebernehmen(F);
   }
  else if (mod == SCHARFSCHIESSEN)
   {
     cH_MidgardBasicElement F(new Fertigkeit(*cH_Fertigkeit("Scharfschießen")));
     cH_Fertigkeit(F)->setZusatz(zusatz);
     F->set_Erfolgswert(wert);
     hauptfenster->MidgardBasicElement_uebernehmen(F);
   }
  else if (mod == LAND || mod == HEIMATLAND)
   {
     cH_Land s=static_cast<Land*>(clist_sp_sc->selection().begin()->get_data());
     cH_MidgardBasicElement F(new Fertigkeit(*cH_Fertigkeit("Landeskunde")));
     cH_Fertigkeit(F)->setZusatz((s)->Name());     
     F->set_Erfolgswert(wert);
     hauptfenster->MidgardBasicElement_uebernehmen(F);
   }
  else 
   {
     cH_MidgardBasicElement s=static_cast<MidgardBasicElement*>(clist_sp_sc->selection().begin()->get_data());
     if(s->What()==MidgardBasicElement::SPRACHE)
        cH_Sprache(s)->set_Erfolgswert(wert);
     else if(s->What()==MidgardBasicElement::SCHRIFT)
        cH_Schrift(s)->set_Erfolgswert(wert);
     hauptfenster->MidgardBasicElement_uebernehmen(s);
   }
  destroy();
}


Sprache_auswahl::Sprache_auswahl(midgard_CG* h, const Datenbank& Database, 
   const Grundwerte& _Werte,const cH_MidgardBasicElement& _MBE,
   const modus _mod,int _wert,
                             const std::list<cH_MidgardBasicElement> &Waffe,
                             const std::list<cH_MidgardBasicElement> &Sp,
                             const std::list<cH_MidgardBasicElement> &Sc,
                             const std::list<cH_MidgardBasicElement> &L)
 :mod(_mod),hauptfenster(h),Werte(_Werte) , MBE(&_MBE), wert(_wert)
{
  {
   Gtk::OStream os(clist_sp_sc);
   if (mod == GEHEIMZEICHEN || mod==MUSIZIEREN || mod==TIERSPRACHE || mod==ABRICHTEN)
      {
         if(mod == GEHEIMZEICHEN) sp_sc_label->set_text("Geheimzeichen wählen");
         if(mod == MUSIZIEREN) sp_sc_label->set_text("Musikinstrument wählen");
         if(mod == TIERSPRACHE) sp_sc_label->set_text("Tierart wählen");
         if(mod == ABRICHTEN) sp_sc_label->set_text("Tierart wählen");
         std::vector<std::string> VG=(*MBE)->VZusatz();
         for (std::vector<std::string>::const_iterator i=VG.begin();i!=VG.end();++i)
          { 
            os << (*i)<<'\t'<<wert<<'\n';
//            os.flush((*i)->ref(),&HandleContent::unref);
          }
      }
   else if (mod == SCHARFSCHIESSEN)
      {
         sp_sc_label->set_text("Fenkampfwaffe wählen");
         for (std::list<cH_MidgardBasicElement>::const_iterator i=Waffe.begin();i!=Waffe.end();++i)
          { 
            if (cH_Waffe(*i)->Art()=="Schußwaffe" || cH_Waffe(*i)->Art()=="Wurfwaffe")
             {
               os << (*i)->Name()<<'\t'<<wert<<'\n';
               os.flush((*i)->ref(),&HandleContent::unref);
             }
          }
      }
   else if (mod == LAND || mod == HEIMATLAND)
      {
         sp_sc_label->set_text("Land wählen");
         for (std::vector<cH_Land>::const_iterator i=Database.Laender.begin();i!=Database.Laender.end();++i)
          { 
            if(mod!=HEIMATLAND || (*i)->Name()==Werte.Herkunft()->Name())
            os << (*i)->Name()<<'\t'<<wert<<'\n';
            os.flush((*i)->ref(),&HandleContent::unref);
          }
      }
   else if (mod == SPRACHE || mod == MUTTERSPRACHE ||
       mod == NEUESPRACHE || mod == ALTESPRACHE)
      {
         if(mod == MUTTERSPRACHE)
           {
             vector<std::string> V=Werte.Herkunft()->Sprachen();
             vector<std::string> W;
             for(vector<std::string>::const_iterator i=V.begin();i!=V.end();++i)
                if(!cH_Sprache(*i)->Alte_Sprache()) W.push_back(*i) ;
             std::string s;
             for(vector<std::string>::const_iterator i=W.begin();i!=W.end();)
               { s+=*i; if(++i!=W.end()) s+=", ";}
             if(W.size()==1) 
               sp_sc_label->set_text("Muttersprache ("+s+") wählen") ;
             else
               sp_sc_label->set_text("Eine Muttersprache wählen\n("+s+")") ;
           } 
         else  sp_sc_label->set_text("Sprache wählen")  ;
         for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Sprache.begin();i!=Database.Sprache.end();++i)
          { 
            if((*i)->ist_gelernt(Sp)) continue;
            cH_Sprache s(*i);
            if(mod == MUTTERSPRACHE &&  s->Alte_Sprache()) continue;
            if(mod == NEUESPRACHE &&  s->Alte_Sprache()) continue;
            if(mod == ALTESPRACHE && !s->Alte_Sprache()) continue;
            os << s->Name()<<'\t'<<wert<<'\n';
            os.flush((*i)->ref(),&HandleContent::unref);
          }
      }
   else if (mod == SCHRIFT)
      {
         sp_sc_label->set_text("Schrift wählen");
         for (std::list<cH_MidgardBasicElement>::const_iterator i=Database.Schrift.begin();i!=Database.Schrift.end();++i)
          { 
            if((*i)->ist_gelernt(Sc)) continue;
            cH_Schrift s(*i);
            if(s->kann_Sprache(Sp))
             {
               os << s->Name()<<'\t'<<s->Art_der_Schrift()<<'\n';
//               os.flush(&const_cast<cH_MidgardBasicElement&>(*i));
               os.flush((*i)->ref(),&HandleContent::unref);
             }
          }
         if(!clist_sp_sc->rows().size())
           hauptfenster->InfoFenster->AppendShow("Keine Sprache gewählt, deren Schrift zu lernen wäre.\n
                     (siehe unter 'Allgemeinbildung')");
      }
   for (unsigned int i=0;i<clist_sp_sc->columns().size();++i)
      clist_sp_sc->set_column_auto_resize(i,true);
  }
 // Leere Liste wieder zerstören
 if(!clist_sp_sc->rows().size()) destroy();
}
