// generated 2002/5/14 9:41:31 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_grundwerte.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_grundwerte.hh"
#include "midgard_CG.hh"
#include <Misc/itos.h>
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
  edit_sensitive(false);
  zeige_werte();
}
    
void table_grundwerte::zeige_werte(bool typ2_hide=true)
{ 
   if(!hauptfenster) return;
   block_changed=true;
   if (hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::Original).active)  
      original_midgard_check();

   spinbutton_st->set_value(hauptfenster->getWerte().St());
   spinbutton_gw->set_value(hauptfenster->getWerte().Gw());
   spinbutton_gs->set_value(hauptfenster->getWerte().Gs());
   spinbutton_ko->set_value(hauptfenster->getWerte().Ko());
   spinbutton_in->set_value(hauptfenster->getWerte().In());
   spinbutton_zt->set_value(hauptfenster->getWerte().Zt());
   label_sehen->set_text(itos(hauptfenster->getWerte().Sehen()));
   label_hoeren->set_text(itos(hauptfenster->getWerte().Hoeren()));
   label_riechen->set_text(itos(hauptfenster->getWerte().Riechen()));
   label_schmecken->set_text(itos(hauptfenster->getWerte().Schmecken()));
   label_tasten->set_text(itos(hauptfenster->getWerte().Tasten()));
   label_sechster_sinn->set_text(itos(hauptfenster->getWerte().SechsterSinn()));

   spinbutton_au->set_value(hauptfenster->getWerte().Au());
   spinbutton_pa->set_value(hauptfenster->getWerte().pA());
   spinbutton_sb->set_value(hauptfenster->getWerte().Sb());      
   spinbutton_wk->set_value(hauptfenster->getWerte().Wk());      
   spinbutton_b->set_value(hauptfenster->getWerte().B());     
   spinbutton_lp->set_value(hauptfenster->getWerte().LP());      
   spinbutton_ap->set_value(hauptfenster->getWerte().AP());   
   abwehr_wert->set_text(itos(hauptfenster->getWerte().Abwehr_wert()));
   zaubern_wert->set_text(itos(hauptfenster->getWerte().Zaubern_wert()));
   kaw->set_text(itos(hauptfenster->getWerte().KAW()));
   wlw->set_text(itos(hauptfenster->getWerte().WLW()));
   resistenz->set_text(itos(hauptfenster->getWerte().Resistenz()));
   gift_wert->set_text(itos(hauptfenster->getWerte().Gift()));
   bo_au->set_text(itos(hauptfenster->getWerte().bo_Au())) ;
   bo_sc->set_text(itos(hauptfenster->getWerte().bo_Sc())) ;
   bo_an->set_text(itos(hauptfenster->getWerte().bo_An())) ;
   bo_ab->set_text(itos(hauptfenster->getWerte().bo_Ab())) ;
   bo_za->set_text(itos(hauptfenster->getWerte().bo_Za())) ;
   bo_psy->set_text(itos(hauptfenster->getWerte().bo_Psy(hauptfenster->getChar().getVTyp()))) ;
   bo_phs->set_text(itos(hauptfenster->getWerte().bo_Phs(hauptfenster->getChar().getVTyp()))) ;
   bo_phk->set_text(itos(hauptfenster->getWerte().bo_Phk(hauptfenster->getChar().getVTyp()))) ;
   spinbutton_alter->set_value(hauptfenster->getWerte().Alter());
   spinbutton_gfp->set_value(hauptfenster->getWerte().GFP());
   spinbutton_tage->set_value(hauptfenster->getWerte().Steigertage());
   spinbutton_gg->set_value(hauptfenster->getWerte().GG());
   spinbutton_sg->set_value(hauptfenster->getWerte().SG());
   label_gestalt->set_text(hauptfenster->getWerte().Gestalt());  
   spinbutton_Cgewicht->set_value(hauptfenster->getWerte().Gewicht());
   spinbutton_groesse->set_value(hauptfenster->getWerte().Groesse());
   spinbutton_grad->set_value(hauptfenster->getWerte().Grad());      
   entry_spezialisierung->set_text(hauptfenster->getWerte().Spezialisierung());

   combo_stand->set_popdown_strings(Vstand);
   combo_stand->get_entry()->set_text(hauptfenster->getWerte().Stand());
   combo_hand->set_popdown_strings(Vhand);
   combo_hand->get_entry()->set_text(hauptfenster->getWerte().Hand());

   entry_herkunft->set_text(hauptfenster->getWerte().Herkunft()->Name());
   entry_glaube->set_text(hauptfenster->getWerte().Glaube());
   entry_nameC->set_text(hauptfenster->getWerte().Name_Abenteurer());
   entry_nameS->set_text(hauptfenster->getWerte().Name_Spieler());
   entry_version->set_text(hauptfenster->getWerte().Version());

   entry_bezeichnung->set_text(hauptfenster->getWerte().Bezeichnung());
   entry_merkmale->set_text(hauptfenster->getWerte().Merkmale());

   if (hauptfenster->getWerte().Geschlecht()=="w") radiobutton_frau->set_active(true); 
   else radiobutton_mann->set_active(true); 
   
   if(typ2_hide)
    {
      if (hauptfenster->getChar().Typ2()->Short()=="") 
         combo_typ2->hide();
      else  combo_typ2->show();
    }
   combo_spezies->get_entry()->set_text(hauptfenster->getWerte().Spezies()->Name());
   block_changed=false;
}

void table_grundwerte::neuer_charakter()
{
   if(!hauptfenster) return;
   button_grundwerte->set_sensitive(true);
   combo_typ->set_sensitive(false);
   combo_spezies->set_sensitive(true);
   button_abg_werte->set_sensitive(false);
   radiobutton_stadt->set_sensitive(true);
   radiobutton_land->set_sensitive(true);
   table_werte_wuerfeln->hide();
   table_bw_wurf->hide();
   if(hauptfenster->getWerte().Stadt_Land()=="Land")  radiobutton_land->set_active(true);
   if(hauptfenster->getWerte().Stadt_Land()=="Stadt")  radiobutton_stadt->set_active(true);
   fill_typauswahl();
   fill_spezies();
   combo_spezies->get_entry()->set_text(hauptfenster->getWerte().Spezies()->Name());
   combo_typ ->get_entry()->set_text(hauptfenster->getChar().Typ1()->Name(hauptfenster->getWerte().Geschlecht()));
   combo_typ2->get_entry()->set_text(hauptfenster->getChar().Typ2()->Name(hauptfenster->getWerte().Geschlecht()));
   zeige_werte();
   hauptfenster->getChar().safed();
}
