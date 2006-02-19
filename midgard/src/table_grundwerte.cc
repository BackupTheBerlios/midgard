/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2004-2006 Christof Petig
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
#include "table_grundwerte.hh"
#include "midgard_CG.hh"
#include <Misc/itos.h>
#include <SelectMatching.h>
#include <Misc/Trace.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <bool_CheckButton.hh>
#include <libmagus/Ausgabe.hh>
#include <Misc/inbetween.h>
#include <Misc/TemporaryValue.h>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
#if MPC_SIGC_VERSION > 0x120
#  include <sigc++/bind.h>
#endif

void table_grundwerte::init(midgard_CG *h)
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__); 
  hauptfenster=h;
  abentaus=&h->getChar();

  abentaus->signal_anderer_abenteurer().connect(SigC::bind(SigC::slot(*this,&table_grundwerte::zeige_werte),true));
  abentaus->proxies.undo_changed.connect(SigC::bind(SigC::slot(*this,&table_grundwerte::zeige_werte),true));
  abentaus->proxies.wizard.signal_changed().connect(SigC::slot(*this,&table_grundwerte::sync_wizard));
  abentaus->proxies.wizard_mode.signal_changed().connect(SigC::slot(*this,&table_grundwerte::sync_wizard));
}

table_grundwerte::table_grundwerte(GlademmData *_data)
            : table_grundwerte_glade(_data), hauptfenster(), abentaus(),
              block_changed(),edit_werte(),label() 
{
  Vstand.resize(5);
  Vstand[1]="Unfrei";
  Vstand[2]="Volk";  
  Vstand[3]="Mittelschicht";
  Vstand[4]="Adel";

  Vhand.resize(3);
  Vhand[0]="Rechtshänder";
  Vhand[1]="Linkshänder"; 
  Vhand[2]="Beidhändig";  

  Vhandf.resize(3);
  Vhandf[0]="Rechtshänderin";
  Vhandf[1]="Linkshänderin"; 
  Vhandf[2]="Beidhändig";  

   bool_CheckButton *_m=manage(new bool_CheckButton(edit_werte,hauptfenster->make_gtk_box(MagusImage("EditChar-trans-50.xpm"),"Werte\neditieren",false,false)));
   _m->set_mode(false);
   eventbox_werte_edit->add(*_m);
   _m->show();
#warning eigentlich an das Model connectieren   !
   _m->signal_toggled().connect(SigC::slot(*this, &table_grundwerte::on_togglebutton_edit_werte_toggled),true);
   fill_spezies();
  edit_werte=false;
  edit_sensitive(false); // noch weg ?
  frame_wuerfelvariante->hide();
   
  button_grundwerte->set_tooltips(&_tooltips);
  button_grundwerte->add(MagusImage("Dice-W100-trans-50.xpm"),"Eigenschaften\nwürfeln",
       "2x für jede Eigenschaft würfeln, das höhere Ergebnis zählt.",
       SigC::slot(*this,&table_grundwerte::on_button_grundwerte));
  button_grundwerte->add(MagusImage("Dice-W100-trans-50.xpm"),"Eigenschaften\nauswählen",
       "2x würfeln, für den besseren Wert eine Eigenschaft aussuchen, das ganze sechsmal wiederholen.",
       SigC::slot(*this,&table_grundwerte::on_button_grundwerte));
  button_grundwerte->add(MagusImage("Dice-W100-trans-50.xpm"),"Eigenschaften\nverteilen",
       "9x würfeln, die besten sechs Ergebnisse frei verteilen.",
       SigC::slot(*this,&table_grundwerte::on_button_grundwerte));

  button_geschlecht->set_tooltips(&_tooltips);
  button_geschlecht->add(MagusImage("male.png"),"männlich",SigC::slot(*this,&table_grundwerte::on_radiobutton_mann_toggled));
  button_geschlecht->add(MagusImage("female.png"),"weiblich",SigC::slot(*this,&table_grundwerte::on_radiobutton_mann_toggled));

  button_stadt_land->set_tooltips(&_tooltips);
  button_stadt_land->add(MagusImage("stadt.png"),"Stadt",SigC::slot(*this,&table_grundwerte::on_radiobutton_stadt_land_toggled));
  button_stadt_land->add(MagusImage("land.png"),"Land",SigC::slot(*this,&table_grundwerte::on_radiobutton_stadt_land_toggled));
}

void table_grundwerte::zeige_werte(bool typ2_hide)
{ 
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__); 
   if(!hauptfenster) return;
   if (hauptfenster->get_current_page()!=midgard_CG::PAGE_GRUNDWERTE) return;
   
  TemporaryValue<bool> tv(block_changed,true);
  fill_typauswahl();
//   fill_spezies(); // sobald Mann/Frau interessant wird
   midgard_check_werte100();
   
   Abenteurer &A=abentaus->getAbenteurer();

   label_last_edited->set_text(A.LastSavedAt());

   spinbutton_st->set_value(A.St());
   spinbutton_gw->set_value(A.Gw());
   spinbutton_gs->set_value(A.Gs());
   spinbutton_ko->set_value(A.Ko());
   spinbutton_in->set_value(A.In());
   spinbutton_zt->set_value(A.Zt());
   label_sehen->set_text(itos(A.Sehen()));
   label_hoeren->set_text(itos(A.Hoeren()));
   label_riechen->set_text(itos(A.Riechen()));
   label_schmecken->set_text(itos(A.Schmecken()));
   label_tasten->set_text(itos(A.Tasten()));
   label_sechster_sinn->set_text(itos(A.SechsterSinn()));

   spinbutton_au->set_value(A.Au());
   spinbutton_pa->set_value(A.pA());
   spinbutton_sb->set_value(A.Sb());      
   spinbutton_wk->set_value(A.Wk());      
   spinbutton_b->set_value(A.B());     
   spinbutton_lp->set_value(A.LP());      
   spinbutton_ap->set_value(A.AP());   
   abwehr_wert->set_text(itos(A.Abwehr_wert()));
   zaubern_wert->set_text(itos(A.Zaubern_wert()));
   kaw->set_text(itos(A.KAW()));
   wlw->set_text(itos(A.WLW()));
   resistenz->set_text(itos(A.Resistenz()));
   gift_wert->set_text(itos(A.Gift()));
   bo_au->set_text(itos(A.bo_Au())) ;
   bo_sc->set_text(itos(A.bo_Sc())) ;
   bo_an->set_text(itos(A.bo_An())) ;
   bo_ab->set_text(itos(A.bo_Ab())) ;
   bo_za->set_text(itos(A.bo_Za())) ;
   bo_psy->set_text(itos(A.bo_Psy())) ;
   bo_phs->set_text(itos(A.bo_Phs())) ;
   bo_phk->set_text(itos(A.bo_Phk())) ;
   spinbutton_alter->set_value(A.Alter());
   spinbutton_gfp->set_value(A.GFP());
   spinbutton_tage->set_value(A.Steigertage());
   spinbutton_gg->set_value(A.GG());
   spinbutton_sg->set_value(A.SG());
   label_gestalt->set_text(A.Gestalt());  
   spinbutton_Cgewicht->set_value(A.Gewicht());
   spinbutton_groesse->set_value(A.Groesse());
   spinbutton_grad->set_value(A.Grad());      
   entry_spezialisierung->set_text(A.Spezialisierung());

   combo_stand->set_popdown_strings(Vstand);
   combo_stand->get_entry()->set_text(A.Stand());
   combo_hand->set_popdown_strings(A.Geschlecht()==Enums::Frau?Vhandf:Vhand);
   combo_hand->get_entry()->set_text(A.Hand());

   button_stadt_land->set_index(A.Stadt_Land()==Enums::Stadt?0:1);

   entry_herkunft->set_text(A.Herkunft()->Name());
   entry_glaube->set_text(A.Glaube());
   entry_nameC->set_text(A.Name_Abenteurer());
   entry_nameS->set_text(A.Name_Spieler());
   entry_version->set_text(A.Version());

   entry_bezeichnung->set_text(A.Bezeichnung());
   entry_merkmale->set_text(A.Merkmale());

   button_geschlecht->set_index(A.Geschlecht()==Enums::Mann?0:1);
   
   if(typ2_hide)
    {
      if (A.Typ2()->Short().empty()) 
         combo_typ2->hide();
      else  combo_typ2->show();
    }
   combo_spezies->get_entry()->set_text(A.Spezies()->Name());
   combo_typ ->get_entry()->set_text(A.Typ1()->Name(A.Geschlecht()));
   combo_typ2->get_entry()->set_text(A.Typ2()->Name(A.Geschlecht()));
}

const UniqueValue::value_t table_grundwerte::trace_channel
                  =ManuProC::Tracer::channels.get();
static ManuProC::Tracer::Environment trace_channel_e("DEBUG_GRUNDWERTE",table_grundwerte::trace_channel);

void table_grundwerte::sync_wizard(gpointer x)
{  //edit_sensitive();
   VAbentModelProxy &pr=hauptfenster->getChar().proxies;
   bool always_sens=pr.wizard_mode.Value()<=Wizard::Hints
   	|| hauptfenster->getAben().getOptionen().OptionenCheck(Optionen::NSC_only).active;
   ManuProC::Trace _t(trace_channel,__FUNCTION__,always_sens,pr.wizard.Value());
   combo_spezies->set_sensitive(always_sens 
   	|| between(pr.wizard.Value(),Wizard::SPEZIES,Wizard::GRUNDWERTE));
   button_grundwerte->set_sensitive(always_sens 
   	|| between(pr.wizard.Value(),Wizard::SPEZIES,Wizard::GRUNDWERTE)
   	|| // !check_350()
   	false /* Wert unter 350 */ );
   button_geschlecht->set_sensitive(always_sens 
   	|| between(pr.wizard.Value(),Wizard::GESCHLECHT,Wizard::TYP));
   combo_typ->set_sensitive(always_sens 
   	|| between(pr.wizard.Value(),Wizard::GESCHLECHT,Wizard::TYP));
   combo_typ2->set_sensitive(true); // besser nachsehen, ob schon ein Typ gewählt
// always_sens 
//   	|| between(pr.wizard.Value(),Wizard::GESCHLECHT,Wizard::TYP));
   button_stadt_land->set_sensitive(always_sens 
   	|| between(pr.wizard.Value(),Wizard::STADTLAND,Wizard::ABGELEITETEWERTE));
   button_abg_werte->set_sensitive(always_sens 
   	|| between(pr.wizard.Value(),Wizard::STADTLAND,Wizard::ABGELEITETEWERTE));
  if (pr.wizard_mode.Value()==Wizard::Aktiv)
  { switch (pr.wizard.Value())
    { case Wizard::SPEZIES: combo_spezies->grab_focus(); break;
      case Wizard::GRUNDWERTE: button_grundwerte->grab_focus(); break;
      case Wizard::GESCHLECHT: button_geschlecht->grab_focus(); break;
      case Wizard::TYP: combo_typ->grab_focus(); break;
      case Wizard::STADTLAND: button_stadt_land->grab_focus(); break;
      case Wizard::ABGELEITETEWERTE: on_abge_werte_setzen_clicked(); break;
      case Wizard::LERNSCHEMA_SEITE: hauptfenster->notebook_main->set_current_page(PAGE_LERNEN); break;
      case Wizard::NAMEN: hauptfenster->notebook_main->set_current_page(PAGE_GRUNDWERTE);
        edit_werte=true;
        entry_nameC->grab_focus();
        break;
      case Wizard::SPEICHERN: hauptfenster->notebook_main->set_current_page(PAGE_GRUNDWERTE);
        hauptfenster->xml_export_auswahl();
        break;
      case Wizard::ZWEITER_TYP: // siehe unten
        break;
    }
  }
  if (pr.wizard.Value()==Wizard::ZWEITER_TYP) 
  { hauptfenster->notebook_main->set_current_page(PAGE_GRUNDWERTE);
    combo_typ2->show();
    combo_typ2->grab_focus(); 
  }
}

void table_grundwerte::NamenEingeben() 
{ edit_werte=true; entry_nameC->grab_focus(); }

void table_grundwerte::clean_up()
{ if (edit_werte)
    edit_werte=false;
}
