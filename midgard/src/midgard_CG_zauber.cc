#include "midgard_CG.hh"
#include "Zauber_auswahl.hh"
#include <Gtk_OStream.h>

void midgard_CG::on_zauber_wahl_clicked()
{
  zauber_clist->clear();
  manage(new Zauber_auswahl(this,typ.s,lernpunkte));
}

void midgard_CG::show_zauber()
{
   zauber_clist->clear();
   midgard_CG::Zauber_get_daten(zauber);
   Gtk::OStream os(zauber_clist);
   for(vector<st_zauber>::iterator i=zauber.begin();
         i!=zauber.end();++i)
      {
         os << i->name<<"\t"<<i->erfolgswert<<"\n";
      }
   for (unsigned int i=0;i<zauber_clist->columns().size();++i)
      zauber_clist->set_column_auto_resize(i,true);
   zauber_clist->set_reorderable(true);
}

void midgard_CG::zauber_uebernehmen(vector<st_ausgewaehlte_zauber>& saz)
{
   zauber.clear();
   vec_zauber = saz;
   for(vector<st_ausgewaehlte_zauber>::iterator i=vec_zauber.begin();
         i!=vec_zauber.end();++i)
      {
         string erf = midgard_CG::get_erfolgswert_zaubern(typ,i->name);
         zauber.push_back(st_zauber(i->ap,i->name,erf,"0","0","0","0","0","0","0","0","0","0","0","0","0",0));
      }
   midgard_CG::show_zauber();
}

void midgard_CG::spezialgebiet_button()
{
 static bool block=false;
 if (block==true) return ;
if (typ.s=="Ma")
{
 int ityp = int(option_magier_spezialgebiet->get_menu()->get_active()->get_user_data());
 if (ityp==option_magier_spezialgebiet::Adept_der_Herrschaft) { werte.spezial="beherrscht"; werte.spezialisierung="Adept der Herrschaft";}
 if (ityp==option_magier_spezialgebiet::Adept_der_Bewegung) { werte.spezial="bewegt"; werte.spezialisierung="Adept der Bewegung";}
 if (ityp==option_magier_spezialgebiet::Adept_der_Erkenntnis) { werte.spezial="erkennt"; werte.spezialisierung="Adept der Erkenntnis";}
 if (ityp==option_magier_spezialgebiet::Adept_der_Sch_fung) { werte.spezial="erschafft"; werte.spezialisierung="Adept der Schöpfung";}
 if (ityp==option_magier_spezialgebiet::Adept_der_Ver_nderung) { werte.spezial="verändert"; werte.spezialisierung="Adept der Veränderung";}
 if (ityp==option_magier_spezialgebiet::Adept_der_Wandlung) { werte.spezial="verwandelt"; werte.spezialisierung="Adept der Wandlung";}
 if (ityp==option_magier_spezialgebiet::Adept_der_Zerst_rung) { werte.spezial="zerstört"; werte.spezialisierung="Adept der Zerstörung";}
 if (ityp==option_magier_spezialgebiet::Erdmagier) { werte.spezial="Erde"; werte.spezialisierung="Erdmagier";}
 if (ityp==option_magier_spezialgebiet::Feuermagier) { werte.spezial="Feuer"; werte.spezialisierung="Feuermagier";}
 if (ityp==option_magier_spezialgebiet::Luftmagier) { werte.spezial="Luft"; werte.spezialisierung="Luftmagier";}
 if (ityp==option_magier_spezialgebiet::Wassermagier) { werte.spezial="Wasser"; werte.spezialisierung="Wassermagier";}
 if (ityp==option_magier_spezialgebiet::Eismagier) { werte.spezial="Eis"; werte.spezialisierung="Eismagier";}
 if (ityp==option_magier_spezialgebiet::Adept_der_g_ttlichen_Ordnung) { werte.spezial="Metall"; werte.spezialisierung="Adept der göttlichen Ordnung";}
 if (ityp==option_magier_spezialgebiet::Adept_des_formbaren_Chaos) { werte.spezial="Magan"; werte.spezialisierung="Adept des formbaren Chaos";}
 if (ityp==option_magier_spezialgebiet::Adept_des_Todes) { werte.spezial="Eis"; werte.spezialisierung="Adept des Todes";}
}
else
{
 string stinfo="Nur für Magier";
 manage (new WindowInfo(stinfo));
 option_magier_spezialgebiet->get_menu()->set_active(0);
 block=true;
 option_magier_spezialgebiet->get_menu()->deactivate();
 block=false;
}  
}
