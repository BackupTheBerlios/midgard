
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

void table_grundwerte::init(midgard_CG *h)
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__); 
  hauptfenster=h;
  label=0;

  static bool only_once=false;
  if(!only_once)
  {
   only_once=true;
  Vstand.resize(5);
  Vstand[1]="Unfrei";
  Vstand[2]="Volk";  
  Vstand[3]="Mittelschicht";
  Vstand[4]="Adel";

  Vhand.resize(3);
  Vhand[0]="Rechtshänder";
  Vhand[1]="Linkshänder"; 
  Vhand[2]="Beidhändig";  

    bool_CheckButton *_m=manage(new bool_CheckButton(edit_werte,hauptfenster->make_gtk_box(MagusImage("EditChar-trans-50.xpm"),"Werte\neditieren",false,false)));
   _m->set_mode(false);
   eventbox_werte_edit->add(*_m);
   eventbox_werte_edit->show_all();
   _m->signal_toggled().connect(SigC::slot(*this, &table_grundwerte::on_togglebutton_edit_werte_toggled),true);

  }
  edit_werte=false;
  edit_sensitive(false); // noch weg ?
  zeige_werte(); // noch weg
}

void table_grundwerte::zeige_werte(bool typ2_hide)
{ 
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__); 
   if(!hauptfenster) return;
   block_changed=true;
   midgard_check_werte100();

   spinbutton_st->set_value(hauptfenster->getChar()->St());
   spinbutton_gw->set_value(hauptfenster->getChar()->Gw());
   spinbutton_gs->set_value(hauptfenster->getChar()->Gs());
   spinbutton_ko->set_value(hauptfenster->getChar()->Ko());
   spinbutton_in->set_value(hauptfenster->getChar()->In());
   spinbutton_zt->set_value(hauptfenster->getChar()->Zt());
   label_sehen->set_text(itos(hauptfenster->getChar()->Sehen()));
   label_hoeren->set_text(itos(hauptfenster->getChar()->Hoeren()));
   label_riechen->set_text(itos(hauptfenster->getChar()->Riechen()));
   label_schmecken->set_text(itos(hauptfenster->getChar()->Schmecken()));
   label_tasten->set_text(itos(hauptfenster->getChar()->Tasten()));
   label_sechster_sinn->set_text(itos(hauptfenster->getChar()->SechsterSinn()));

   spinbutton_au->set_value(hauptfenster->getChar()->Au());
   spinbutton_pa->set_value(hauptfenster->getChar()->pA());
   spinbutton_sb->set_value(hauptfenster->getChar()->Sb());      
   spinbutton_wk->set_value(hauptfenster->getChar()->Wk());      
   spinbutton_b->set_value(hauptfenster->getChar()->B());     
   spinbutton_lp->set_value(hauptfenster->getChar()->LP());      
   spinbutton_ap->set_value(hauptfenster->getChar()->AP());   
   abwehr_wert->set_text(itos(hauptfenster->getChar()->Abwehr_wert()));
   zaubern_wert->set_text(itos(hauptfenster->getChar()->Zaubern_wert()));
   kaw->set_text(itos(hauptfenster->getChar()->KAW()));
   wlw->set_text(itos(hauptfenster->getChar()->WLW()));
   resistenz->set_text(itos(hauptfenster->getChar()->Resistenz()));
   gift_wert->set_text(itos(hauptfenster->getChar()->Gift()));
   bo_au->set_text(itos(hauptfenster->getChar()->bo_Au())) ;
   bo_sc->set_text(itos(hauptfenster->getChar()->bo_Sc())) ;
   bo_an->set_text(itos(hauptfenster->getChar()->bo_An())) ;
   bo_ab->set_text(itos(hauptfenster->getChar()->bo_Ab())) ;
   bo_za->set_text(itos(hauptfenster->getChar()->bo_Za())) ;
   bo_psy->set_text(itos(hauptfenster->getChar()->bo_Psy())) ;
   bo_phs->set_text(itos(hauptfenster->getChar()->bo_Phs())) ;
   bo_phk->set_text(itos(hauptfenster->getChar()->bo_Phk())) ;
   spinbutton_alter->set_value(hauptfenster->getChar()->Alter());
   spinbutton_gfp->set_value(hauptfenster->getChar()->GFP());
   spinbutton_tage->set_value(hauptfenster->getChar()->Steigertage());
   spinbutton_gg->set_value(hauptfenster->getChar()->GG());
   spinbutton_sg->set_value(hauptfenster->getChar()->SG());
   label_gestalt->set_text(hauptfenster->getChar()->Gestalt());  
   spinbutton_Cgewicht->set_value(hauptfenster->getChar()->Gewicht());
   spinbutton_groesse->set_value(hauptfenster->getChar()->Groesse());
   spinbutton_grad->set_value(hauptfenster->getChar()->Grad());      
   entry_spezialisierung->set_text(hauptfenster->getChar()->Spezialisierung());

   combo_stand->set_popdown_strings(Vstand);
   combo_stand->get_entry()->set_text(hauptfenster->getChar()->Stand());
   combo_hand->set_popdown_strings(Vhand);
   combo_hand->get_entry()->set_text(hauptfenster->getChar()->Hand());

   entry_herkunft->set_text(hauptfenster->getChar()->Herkunft()->Name());
   entry_glaube->set_text(hauptfenster->getChar()->Glaube());
   entry_nameC->set_text(hauptfenster->getChar()->Name_Abenteurer());
   entry_nameS->set_text(hauptfenster->getChar()->Name_Spieler());
   entry_version->set_text(hauptfenster->getChar()->Version());

   entry_bezeichnung->set_text(hauptfenster->getChar()->Bezeichnung());
   entry_merkmale->set_text(hauptfenster->getChar()->Merkmale());

   if (hauptfenster->getChar()->Geschlecht()==Enums::Frau) radiobutton_frau->set_active(true); 
   else radiobutton_mann->set_active(true); 
   
   if(typ2_hide)
    {
      if (hauptfenster->getAben().Typ2()->Short()=="") 
         combo_typ2->hide();
      else  combo_typ2->show();
    }
   combo_spezies->get_entry()->set_text(hauptfenster->getChar()->Spezies()->Name());
   combo_typ ->get_entry()->set_text(hauptfenster->getAben().Typ1()->Name(hauptfenster->getChar()->Geschlecht()));
   combo_typ2->get_entry()->set_text(hauptfenster->getAben().Typ2()->Name(hauptfenster->getChar()->Geschlecht()));
   block_changed=false;
}

void table_grundwerte::neuer_charakter()
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__); 
   if(!hauptfenster) return;
   block_changed=true;
   button_grundwerte->set_sensitive(true);
   combo_typ->set_sensitive(false);
   combo_spezies->set_sensitive(true);
   button_abg_werte->set_sensitive(false);
   radiobutton_stadt->set_sensitive(true);
   radiobutton_land->set_sensitive(true);
   frame_wuerfelvariante->hide();
   if(hauptfenster->getChar()->Stadt_Land()==Enums::Land)  radiobutton_land->set_active(true);
   if(hauptfenster->getChar()->Stadt_Land()==Enums::Stadt)  radiobutton_stadt->set_active(true);
   fill_typauswahl();
   fill_spezies();
   combo_spezies->get_entry()->set_text(hauptfenster->getChar()->Spezies()->Name());
   combo_typ ->get_entry()->set_text(hauptfenster->getAben().Typ1()->Name(hauptfenster->getChar()->Geschlecht()));
   combo_typ2->get_entry()->set_text(hauptfenster->getAben().Typ2()->Name(hauptfenster->getChar()->Geschlecht()));
   block_changed=false;
   zeige_werte();
   hauptfenster->getChar().saved();
}

#include <Misc/Trace.h>
const UniqueValue::value_t table_grundwerte::trace_channel
                  =ManuProC::Tracer::channels.get();
