// generated 2002/5/23 18:30:41 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_steigern.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_steigern.hh"
#include <Aux/itos.h>
#include "Fertigkeiten.hh"
#include "midgard_CG.hh"
#include "dtos1.h"

void table_steigern::init(midgard_CG *h)
{
  hauptfenster=h;
  zeige_werte();
  load_for_page(notebook_lernen->get_current_page_num());
  steigern_mit_EP_bool=true;
  checkbutton_EP_Geld->set_active(steigern_mit_EP_bool);

  if(SpruecheMitPP().empty())
      { radiobutton_pp_spezial->hide();
        frame_pp_spezial->hide();
      }
  else
     { 
        radiobutton_pp_spezial->remove();
        Gtk::Label *l=manage(new class Gtk::Label(SpruecheMitPP(),0));
        l->show();
        radiobutton_pp_spezial->add(*l);
        frame_pp_spezial->set_label(SpruecheMitPP());
     }
    
}

void table_steigern::neuer_charakter()
{
 label_EP->set_text("50%");  
 label_Gold->set_text("50%");
 vscale_EP_Gold->get_adjustment()->set_value(50);
 scrolledwindow_landauswahl->hide();
 spinbutton_pp_eingeben->hide(); 
 vbox_praxispunkte->hide();
 togglebutton_praxispunkte->set_active(false);
}



void table_steigern::on_notebook_lernen_switch_page(Gtk::Notebook_Helpers::Page *page,guint pagenr)
{
  if(hauptfenster) load_for_page(pagenr);
}

void table_steigern::load_for_page(guint pagenr)
{
  if(pagenr==PAGE_FERTIGKEITEN)
     on_fertigkeiten_laden_clicked();
  if(pagenr==PAGE_WAFFEN)
     on_waffen_laden_clicked();
  if(pagenr==PAGE_ZAUBER)
     on_zauber_laden_clicked();
  if(pagenr==PAGE_KIDO)
     on_kido_laden_clicked();
  if(pagenr==PAGE_SPRACHE)
     on_sprache_laden_clicked();

  if(pagenr==PAGE_BESITZ)
   {
     init_waffenbesitz();
     clist_ruestung->set_sensitive(false);
     button_ruestung_1->set_active(false);
     button_ruestung_2->set_active(false);
   }


  // Sensitive & Show
  if(pagenr==PAGE_ZAUBER || pagenr==PAGE_KIDO)
   {
     frame_fertigkeit->hide();
     radiobutton_verlernen->set_active(true);
     if(pagenr==PAGE_ZAUBER) frame_zauber_zusatz->show();
     if(hauptfenster->getCChar().CTyp1()->SpruecheMitPP() || hauptfenster->getCChar().CTyp2()->SpruecheMitPP())
        radiobutton_praxis->set_sensitive(true);
     else
        radiobutton_praxis->set_sensitive(false);
   }
  else
   {
     frame_fertigkeit->show();
     radiobutton_steigern->set_active(true);
     frame_zauber_zusatz->hide();
     radiobutton_praxis->set_sensitive(true);
   }
}



void table_steigern::on_button_geld_s_toggled()
{
//  if(!button_gold_eingeben->get_active()) return;
  show_goldeingabe(button_gold_eingeben->get_active());  
  spinbutton_gold->grab_focus();
}

void table_steigern::show_goldeingabe(bool b)
{
  if(b)
   {
     spinbutton_gold->set_value(hauptfenster->getCWerte().Gold());
     spinbutton_silber->set_value(hauptfenster->getCWerte().Silber());
     spinbutton_kupfer->set_value(hauptfenster->getCWerte().Kupfer());
     spinbutton_gold->show();
     spinbutton_silber->show();
     spinbutton_kupfer->show();
     label_gold->hide();
     label_silber->hide();
     label_kupfer->hide();
   }
  else
   {
     spinbutton_gold->hide();
     spinbutton_silber->hide();
     spinbutton_kupfer->hide();
     label_gold->set_text(itos(hauptfenster->getCWerte().Gold()));
     label_silber->set_text(itos(hauptfenster->getCWerte().Silber()));
     label_kupfer->set_text(itos(hauptfenster->getCWerte().Kupfer()));
     label_gold->show();
     label_silber->show();
     label_kupfer->show();
   }
}


void table_steigern::zeige_werte()
{
   gfp->set_text(itos(hauptfenster->getCWerte().GFP()));
  
   label_s_grad->set_text(itos(hauptfenster->getCWerte().Grad()));
   label_s_ap->set_text(itos(hauptfenster->getCWerte().AP()));
   label_s_abwehr->set_text(itos(hauptfenster->getCWerte().Abwehr_wert()));
   label_s_zaubern->set_text(itos(hauptfenster->getCWerte().Zaubern_wert()));
   label_s_resistenz->set_text(itos(hauptfenster->getCWerte().Resistenz()));
   label_pp_abwehr->set_text(itos(hauptfenster->getCWerte().AbwehrPP()));
   label_pp_zaubern->set_text(itos(hauptfenster->getCWerte().ZaubernPP()));
   label_pp_spezial->set_text(itos(hauptfenster->getCWerte().SpezialPP()));
   label_pp_resistenz->set_text(itos(hauptfenster->getCWerte().ResistenzPP()));
   label_steigertage->set_text(dtos1(hauptfenster->getCWerte().Steigertage()));
   label_alter->set_text(itos(hauptfenster->getCWerte().Alter()));
   label_grad_GFP->set_text(hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Grad_fehlt,hauptfenster->getCWerte()));
   label_ausdauer_GFP->set_text(hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Ausdauer,hauptfenster->getCWerte()));
   label_abwehr_GFP->set_text(hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Abwehr,hauptfenster->getCWerte()));
   label_resistenz_GFP->set_text(hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Resistenz,hauptfenster->getCWerte()));
   std::string z=hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Zaubern,hauptfenster->getCWerte());
   if(!hauptfenster->getCChar().CTyp1()->is_mage() && !hauptfenster->getCChar().CTyp2()->is_mage()) z="";
   label_zauber_GFP->set_text(z);

  show_goldeingabe(false);
  show_EPeingabe(false);
  checkbutton_gfp->set_active(false);
  on_button_gfp_s_toggled();

  steigern_typ->set_text(hauptfenster->getCChar().CTyp1()->Name(hauptfenster->getCWerte().Geschlecht()));
  if (hauptfenster->getCChar().CTyp2()->Name(hauptfenster->getCWerte().Geschlecht())!="")
      steigern_typ->set_text(hauptfenster->getCChar().CTyp1()->Name(hauptfenster->getCWerte().Geschlecht())
            +"/"+hauptfenster->getCChar().CTyp2()->Name(hauptfenster->getCWerte().Geschlecht()));

  label_steigern_spezies->set_text(hauptfenster->getCWerte().Spezies()->Name());

  if (hauptfenster->getCChar().is_mage())  table_magier_steigern->show() ;
  else                 table_magier_steigern->hide() ;

  if(MidgardBasicElement_mutable(&*cH_Fertigkeit("KiDo")).ist_gelernt(hauptfenster->getCChar().CList_Fertigkeit()))   
         table_kido_steigern->show();
  else   table_kido_steigern->hide();

  if(!hauptfenster->getCChar().getVTyp().empty() && hauptfenster->getCChar().is_mage())
  {
    button_grad_zaubern->set_sensitive(true);
    frame_pp_zaubern->set_sensitive(true);
    radiobutton_pp_zauber->set_sensitive(true);
  }  
 else
  {
    button_grad_zaubern->set_sensitive(false);
    frame_pp_zaubern->set_sensitive(false);
    radiobutton_pp_zauber->set_sensitive(false);
  }
 show_label();

}

