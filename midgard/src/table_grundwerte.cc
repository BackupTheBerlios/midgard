// generated 2002/5/14 9:41:31 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_grundwerte.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_grundwerte.hh"
#include "midgard_CG.hh"
#include <Aux/itos.h>
#include <SelectMatching.h>

void table_grundwerte::init(midgard_CG *h)
{
  hauptfenster=h;

  Vstand.resize(5);
  Vstand[1]="Unfrei";
  Vstand[2]="Volk";  
  Vstand[3]="Mittelschicht";
  Vstand[4]="Adel";

  Vhand.resize(3);
  Vhand[0]="Rechtshänder";
  Vhand[1]="Linkshänder"; 
  Vhand[2]="Beidhändig";  

  togglebutton_edit_werte->set_active(false);
  on_togglebutton_edit_werte_toggled();
  zeige_werte();
}
    
void table_grundwerte::zeige_werte(bool typ2_hide=true)
{ 
   if(!hauptfenster) return;
   if (hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::Original).active)  
      original_midgard_check();

   spinbutton_st->set_value(hauptfenster->getCWerte().St());
   spinbutton_gw->set_value(hauptfenster->getCWerte().Gw());
   spinbutton_gs->set_value(hauptfenster->getCWerte().Gs());
   spinbutton_ko->set_value(hauptfenster->getCWerte().Ko());
   spinbutton_in->set_value(hauptfenster->getCWerte().In());
   spinbutton_zt->set_value(hauptfenster->getCWerte().Zt());
   label_sehen->set_text(itos(hauptfenster->getCWerte().Sehen()));
   label_hoeren->set_text(itos(hauptfenster->getCWerte().Hoeren()));
   label_riechen->set_text(itos(hauptfenster->getCWerte().Riechen()));
   label_schmecken->set_text(itos(hauptfenster->getCWerte().Schmecken()));
   label_tasten->set_text(itos(hauptfenster->getCWerte().Tasten()));
   label_sechster_sinn->set_text(itos(hauptfenster->getCWerte().SechsterSinn()));

   spinbutton_au->set_value(hauptfenster->getCWerte().Au());
   spinbutton_pa->set_value(hauptfenster->getCWerte().pA());
   spinbutton_sb->set_value(hauptfenster->getCWerte().Sb());      
   spinbutton_wk->set_value(hauptfenster->getCWerte().Wk());      
   spinbutton_b->set_value(hauptfenster->getCWerte().B());     
   spinbutton_lp->set_value(hauptfenster->getCWerte().LP());      
   spinbutton_ap->set_value(hauptfenster->getCWerte().AP());   
   abwehr_wert->set_text(itos(hauptfenster->getCWerte().Abwehr_wert()));
   zaubern_wert->set_text(itos(hauptfenster->getCWerte().Zaubern_wert()));
   kaw->set_text(itos(hauptfenster->getCWerte().KAW()));
   wlw->set_text(itos(hauptfenster->getCWerte().WLW()));
   resistenz->set_text(itos(hauptfenster->getCWerte().Resistenz()));
   gift_wert->set_text(itos(hauptfenster->getCWerte().Gift()));
   bo_au->set_text(itos(hauptfenster->getCWerte().bo_Au())) ;
   bo_sc->set_text(itos(hauptfenster->getCWerte().bo_Sc())) ;
   bo_an->set_text(itos(hauptfenster->getCWerte().bo_An())) ;
   bo_ab->set_text(itos(hauptfenster->getCWerte().bo_Ab())) ;
   bo_za->set_text(itos(hauptfenster->getCWerte().bo_Za())) ;
   bo_psy->set_text(itos(hauptfenster->getCWerte().bo_Psy(hauptfenster->getCChar().getVTyp()))) ;
   bo_phs->set_text(itos(hauptfenster->getCWerte().bo_Phs(hauptfenster->getCChar().getVTyp()))) ;
   bo_phk->set_text(itos(hauptfenster->getCWerte().bo_Phk(hauptfenster->getCChar().getVTyp()))) ;
   spinbutton_alter->set_value(hauptfenster->getCWerte().Alter());
   spinbutton_gfp->set_value(hauptfenster->getCWerte().GFP());
   spinbutton_tage->set_value(hauptfenster->getCWerte().Steigertage());
   spinbutton_gg->set_value(hauptfenster->getCWerte().GG());
   spinbutton_sg->set_value(hauptfenster->getCWerte().SG());
   label_gestalt->set_text(hauptfenster->getCWerte().Gestalt());  
   spinbutton_Cgewicht->set_value(hauptfenster->getCWerte().Gewicht());
   spinbutton_groesse->set_value(hauptfenster->getCWerte().Groesse());
   spinbutton_grad->set_value(hauptfenster->getCWerte().Grad());      
   entry_spezialisierung->set_text(hauptfenster->getCWerte().Spezialisierung());

   combo_stand->set_popdown_strings(Vstand);
   combo_stand->get_entry()->set_text(hauptfenster->getCWerte().Stand());
   combo_hand->set_popdown_strings(Vhand);
   combo_hand->get_entry()->set_text(hauptfenster->getCWerte().Hand());

   entry_herkunft->set_text(hauptfenster->getCWerte().Herkunft()->Name());
   entry_glaube->set_text(hauptfenster->getCWerte().Glaube());
   entry_nameC->set_text(hauptfenster->getCWerte().Name_Abenteurer());
   entry_nameS->set_text(hauptfenster->getCWerte().Name_Spieler());
   entry_version->set_text(hauptfenster->getCWerte().Version());

   if (hauptfenster->getCWerte().Geschlecht()=="w") radiobutton_frau->set_active(true); 
   else radiobutton_mann->set_active(true); 
   
   if(typ2_hide)
    {
      if (hauptfenster->getCChar().CTyp2()->Short()=="") 
         combo_typ2->hide();
      else  combo_typ2->show();
    }
   combo_spezies->get_entry()->set_text(hauptfenster->getCWerte().Spezies()->Name());
}

void table_grundwerte::neuer_charakter()
{
   if(!hauptfenster) return;
   button_grundwerte->set_sensitive(true);
   combo_typ->set_sensitive(false);
   button_abg_werte->set_sensitive(false);
   table_werte_wuerfeln->hide();
   table_bw_wurf->hide();
   if(hauptfenster->getCWerte().Stadt_Land()=="Land")  radiobutton_land->set_active(true);
   if(hauptfenster->getCWerte().Stadt_Land()=="Stadt")  radiobutton_stadt->set_active(true);
   fill_typauswahl();
   fill_spezies();
//   spezieswahl_button();
   zeige_werte();
}


