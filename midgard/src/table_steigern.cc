
#include "config.h"
#include "table_steigern.hh"
#include <Misc/itos.h>
#include "Fertigkeiten.hh"
#include "midgard_CG.hh"
#include "dtos1.h"
#include <bool_CheckButton.hh>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
#include <libmagus/Ausgabe.hh>

void table_steigern::refresh()
{
  flashing_gradanstieg->set(MagusImage("Anpass-trans-50.xpm"),MagusImage("Anpass-trans-50_invers.xpm"),0);
  flashing_eigenschaft->set(MagusImage("Red-Dice-trans-50.xpm"),MagusImage("Red-Dice-trans-50_invers.xpm"),0);

  zeige_werte();
  steigern_mit_EP_bool=true;

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

   fertigkeiten_zeigen();
   waffen_zeigen();
   on_zauber_laden_clicked();
   on_kido_laden_clicked();
   sprachen_zeigen();
   schriften_zeigen();
   init_waffenbesitz();

     clist_ruestung->set_sensitive(false);
     button_ruestung_1->set_active(false);
     button_ruestung_2->set_active(false);

  spinbutton_eigenschaften_grad_anstieg->hide();  
  load_for_page(notebook_lernen->get_current_page());
}

void table_steigern::init(midgard_CG *h)
{
  hauptfenster=h;
  vabenteurer->signal_anderer_abenteurer().connect(SigC::slot(*this,&table_steigern::refresh));
  vabenteurer->proxies.undo_changed.connect(SigC::slot(*this,&table_steigern::refresh));
//  vabenteurer->proxies.wizard.signal_changed().connect(SigC::slot(*this,&table_steigern::wizard_changed));
}

#if 0
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
#endif


void table_steigern::on_notebook_lernen_switch_page(GtkNotebookPage *page,guint pagenr)
{
//  if(hauptfenster /*&& !hauptfenster->in_dtor*/) load_for_page(pagenr);
}

void table_steigern::load_for_page(guint pagenr)
{
  // Sensitive & Show
  if(pagenr==PAGE_ZAUBER || pagenr==PAGE_KIDO)
   {
     radiobutton_verlernen->set_active(true); // wieso das denn?
     if(pagenr==PAGE_ZAUBER) 
       { frame_zauber_zusatz->show();
     if(W.Typ1()->SpruecheMitPP() || W.Typ2()->SpruecheMitPP())
        radiobutton_praxis->set_sensitive(true);
     else
        radiobutton_praxis->set_sensitive(false);
       }
   }
  else
   {
     radiobutton_steigern->set_active(true);
     frame_zauber_zusatz->hide();
     radiobutton_praxis->set_sensitive(true);
   }
}



/*
void table_steigern::on_button_geld_s_toggled()
{
  show_goldeingabe(button_gold_eingeben->get_active());  
  spinbutton_gold->grab_focus();
}
*/

void table_steigern::show_goldeingabe(bool b,int button)
{
  LabelSpin_silber->set_value(hauptfenster->getAben().Silber());
  LabelSpin_kupfer->set_value(hauptfenster->getAben().Kupfer());
  LabelSpin_gold->set_value(hauptfenster->getAben().Gold());
  if(b)
   {
     if     (button == 1) 
       { 
         LabelSpin_silber->edit_new();
         LabelSpin_kupfer->edit_new();
         LabelSpin_gold->edit_new();
       }
     else if(button == 3) 
       { 
         LabelSpin_silber->edit_add();
         LabelSpin_kupfer->edit_add();
         LabelSpin_gold->edit_add();
       }
   }
  else
   {
      LabelSpin_gold->deaktivate();
      LabelSpin_silber->deaktivate();
      LabelSpin_kupfer->deaktivate();
   }             
}


void table_steigern::zeige_werte()
{
   const Abenteurer &W=hauptfenster->getAben();
    LabelSpin_gfp->set_value(W.GFP());

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
   std::string grad_GFP=Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Grad_fehlt,W);
   label_grad_GFP->set_text(grad_GFP);
   if(grad_GFP=="erreicht") flashing_gradanstieg->setTime(1000);
   else                     flashing_gradanstieg->setTime(0);
   if(W.eigenschaften_steigern_erlaubt())
      flashing_eigenschaft->setTime(1000);
   else flashing_eigenschaft->setTime(0);

   label_ausdauer_GFP->set_text(Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Ausdauer,W));
   label_abwehr_GFP->set_text(Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Abwehr,W));
   label_resistenz_GFP->set_text(Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Resistenz,W));
   std::string z=Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Zaubern,W);
   if(!W.Typ1()->is_mage() && !W.Typ2()->is_mage()) z="";
   label_zauber_GFP->set_text(z);

  show_goldeingabe(false);
  show_EPeingabe(false);
  
  checkbutton_gfp->set_active(false);
  LabelSpin_gfp->deaktivate();

  if (!W.Typ2()->Name(W.Geschlecht()).empty())
      steigern_typ->set_text(W.Typ1()->Name(W.Geschlecht())
            +"/"+W.Typ2()->Name(W.Geschlecht()));
  else
     steigern_typ->set_text(W.Typ1()->Name(W.Geschlecht()));

  label_steigern_spezies->set_text(W.Spezies()->Name());

  if(MBEmlt(cH_Fertigkeit("KiDo"))->ist_gelernt(W.List_Fertigkeit()))   
         table_kido_steigern->show();
  else   table_kido_steigern->hide();

  if(W.is_mage())
  { table_magier_steigern->show() ;
    button_grad_zaubern->set_sensitive(true);
    frame_pp_zaubern->set_sensitive(true);
    radiobutton_pp_zauber->set_sensitive(true);
  }  
 else
  { table_magier_steigern->hide() ;    
    button_grad_zaubern->set_sensitive(false);
    frame_pp_zaubern->set_sensitive(false);
    radiobutton_pp_zauber->set_sensitive(false);
  }
 show_label();
     if(MBEmlt(cH_Fertigkeit("Lesen von Zauberschrift"))->ist_gelernt(W.List_Fertigkeit()))
              togglebutton_spruchrolle->set_sensitive(true);
         else togglebutton_spruchrolle->set_sensitive(false);
}

table_steigern::table_steigern(GlademmData *_data) 
         : table_steigern_glade(_data),hauptfenster(),//LL(),
            steigern_mit_EP_bool(true) 
{  clist_ruestung->set_model(RuestungStore);
   clist_ruestung->append_column("Rüstung",ruestung_columns.name);
   clist_ruestung->append_column("",ruestung_columns.abkz);
   clist_ruestung->append_column("LP\nVerlust",ruestung_columns.lp_verlust);
   clist_ruestung->append_column("min.\nStärke",ruestung_columns.min_staerke);
   clist_ruestung->append_column("Gw\nVerlust",ruestung_columns.rw_verlust);
   clist_ruestung->append_column("B\nVerlust",ruestung_columns.b_verlust);
   clist_ruestung->get_selection()->signal_changed().connect(SigC::slot(*this,&table_steigern::on_ruestung_selection_changed));
   bool_CheckButton *_m=manage(new bool_CheckButton(steigern_mit_EP_bool,hauptfenster->make_gtk_box(MagusImage("EP-Steigern-50.xpm"),"Mit EP/PP\nsteigern",false)));
   _m->set_mode(false);
   _m->signal_toggled().connect(SigC::slot(*this, &table_steigern::on_checkbutton_EP_Geld_toggled),true);
   eventbox_eppp_steigern->add(*_m);
   eventbox_eppp_steigern->show_all();
}
