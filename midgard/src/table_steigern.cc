// generated 2002/5/23 18:30:41 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_steigern.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_steigern.hh"
#include <Misc/itos.h>
#include "Fertigkeiten.hh"
#include "midgard_CG.hh"
#include "dtos1.h"
#include "LernListen.hh"
#include "../pixmaps/Anpass-trans-50.xpm"
#include "../pixmaps/Anpass-trans-50_invers.xpm"

void table_steigern::init(midgard_CG *h)
{
  hauptfenster=h;
  if(LL) delete LL ;
  LL = new LernListen(hauptfenster->getDatabase());
  flashing_gradanstieg->set(Anpass_trans_50_xpm,Anpass_trans_50_invers_xpm,0);

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
  if(hauptfenster && !hauptfenster->in_dtor) load_for_page(pagenr);
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
//     frame_fertigkeit->hide();
     radiobutton_verlernen->set_active(true);
     if(pagenr==PAGE_ZAUBER) 
       { frame_zauber_zusatz->show();
         if(MBEmlt(&*cH_Fertigkeit("Lesen von Zauberschrift"))->ist_gelernt(hauptfenster->getChar()->List_Fertigkeit()))
              togglebutton_spruchrolle->set_sensitive(true);
         else togglebutton_spruchrolle->set_sensitive(false);
       }
     if(hauptfenster->getChar()->Typ1()->SpruecheMitPP() || hauptfenster->getChar()->Typ2()->SpruecheMitPP())
        radiobutton_praxis->set_sensitive(true);
     else
        radiobutton_praxis->set_sensitive(false);
   }
  else
   {
//     frame_fertigkeit->show();
     radiobutton_steigern->set_active(true);
     frame_zauber_zusatz->hide();
     radiobutton_praxis->set_sensitive(true);
   }
  spinbutton_eigenschaften_grad_anstieg->hide();  
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
     spinbutton_gold->set_value(hauptfenster->getWerte().Gold());
     spinbutton_silber->set_value(hauptfenster->getWerte().Silber());
     spinbutton_kupfer->set_value(hauptfenster->getWerte().Kupfer());
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
     label_gold->set_text(itos(hauptfenster->getWerte().Gold()));
     label_silber->set_text(itos(hauptfenster->getWerte().Silber()));
     label_kupfer->set_text(itos(hauptfenster->getWerte().Kupfer()));
     label_gold->show();
     label_silber->show();
     label_kupfer->show();
   }
}


void table_steigern::zeige_werte()
{
   const Grundwerte &W=hauptfenster->getWerte();
   gfp->set_text(itos(W.GFP()));

   steigern_gtk();
  
   label_s_grad->set_text(itos(W.Grad()));
   label_s_ap->set_text(itos(W.AP()));
   label_s_abwehr->set_text(itos(W.Abwehr_wert()));
   label_s_zaubern->set_text(itos(W.Zaubern_wert()));
   label_s_resistenz->set_text(itos(W.Resistenz()));
   label_pp_abwehr->set_text(itos(W.AbwehrPP()));
   label_pp_zaubern->set_text(itos(W.ZaubernPP()));
   label_pp_spezial->set_text(itos(W.SpezialPP()));
   label_pp_resistenz->set_text(itos(W.ResistenzPP()));
   label_steigertage->set_text(dtos1(W.Steigertage()));
   label_alter->set_text(itos(W.Alter()));
   std::string grad_GFP=hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Grad_fehlt,W);
   label_grad_GFP->set_text(grad_GFP);
   if(grad_GFP=="erreicht") 
      flashing_gradanstieg->setTime(1000);

   label_ausdauer_GFP->set_text(hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Ausdauer,W));
   label_abwehr_GFP->set_text(hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Abwehr,W));
   label_resistenz_GFP->set_text(hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Resistenz,W));
   std::string z=hauptfenster->getCDatabase().GradAnstieg.getGFP_for_str(Grad_anstieg::Zaubern,W);
   if(!hauptfenster->getChar()->Typ1()->is_mage() && !hauptfenster->getChar()->Typ2()->is_mage()) z="";
   label_zauber_GFP->set_text(z);

  show_goldeingabe(false);
  show_EPeingabe(false);
  checkbutton_gfp->set_active(false);
  on_button_gfp_s_toggled();

  steigern_typ->set_text(hauptfenster->getChar()->Typ1()->Name(W.Geschlecht()));
  if (hauptfenster->getChar()->Typ2()->Name(W.Geschlecht())!="")
      steigern_typ->set_text(hauptfenster->getChar()->Typ1()->Name(W.Geschlecht())
            +"/"+hauptfenster->getChar()->Typ2()->Name(W.Geschlecht()));

  label_steigern_spezies->set_text(W.Spezies()->Name());

  if (hauptfenster->getChar()->is_mage())  table_magier_steigern->show() ;
  else                 table_magier_steigern->hide() ;

  if(MBEmlt(&*cH_Fertigkeit("KiDo"))->ist_gelernt(hauptfenster->getChar()->List_Fertigkeit()))   
         table_kido_steigern->show();
  else   table_kido_steigern->hide();

  if(!hauptfenster->getChar()->getVTyp().empty() && hauptfenster->getChar()->is_mage())
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

