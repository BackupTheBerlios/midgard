/*  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2004-2005 Christof Petig
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
#include <Misc/Trace.h>
#include <Misc/itos.h>
#include <bool_CheckButton.hh>
#include <libmagus/Ausgabe.hh>
#include <libmagus/Datenbank.hh>
#include <libmagus/magustrace.h>
#include "table_steigern.hh"
#include "Fertigkeiten.hh"
#include "midgard_CG.hh"
#include "dtos1.h"
#include "class_SimpleTree.hh"
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

void table_steigern::refresh_moeglich()
{
}

void table_steigern::refresh_werte()
{ const Abenteurer &W=hauptfenster->getAben();
   label_s_grad->set_text(itos(W.Grad()));
   label_s_ap->set_text(itos(W.AP()));
   label_s_abwehr->set_text(itos(W.Abwehr_wert()));
   label_s_zaubern->set_text(itos(W.Zaubern_wert()));
   label_s_resistenz->set_text(itos(W.Resistenz()));
   label_pp_abwehr->set_text(itos(W.AbwehrPP()));
   label_pp_zaubern->set_text(itos(W.ZaubernPP()));
   label_pp_spezial->set_text(itos(W.SpezialPP()));
   label_pp_resistenz->set_text(itos(W.ResistenzPP()));
   label_alter->set_text(itos(W.Alter()));

   if(W.eigenschaften_steigern_erlaubt())
      flashing_eigenschaft->setTime(1000);
   else flashing_eigenschaft->setTime(0);

   label_ausdauer_GFP->set_text(Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Ausdauer,W));
   label_abwehr_GFP->set_text(Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Abwehr,W));
   label_resistenz_GFP->set_text(Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Resistenz,W));

   std::string z=Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Zaubern,W);
   if(!W.Typ1()->is_mage() && !W.Typ2()->is_mage()) z="";
   label_zauber_GFP->set_text(z);


}

void table_steigern::refresh_faehigkeiten()
{
   fertigkeiten_zeigen();
   waffen_zeigen();
   on_zauber_laden_clicked();
   on_kido_laden_clicked();
   sprachen_zeigen();
   schriften_zeigen();
   init_waffenbesitz();
}

void table_steigern::refresh_gesteigert()
{ const Abenteurer &W=hauptfenster->getAben();
   LabelSpin_gfp->set_value(W.GFP());
   label_steigertage->set_text(dtos1(W.Steigertage()));
   std::string grad_GFP=Datenbank.GradAnstieg.getGFP_for_str(Grad_anstieg::Grad_fehlt,W);
   label_grad_GFP->set_text(grad_GFP);
   if(grad_GFP=="erreicht") flashing_gradanstieg->setTime(1000);
   else                     flashing_gradanstieg->setTime(0);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
   if (grad_GFP=="erreicht") 
      handlebox_steigern_4->set_label("neuer Grad erreicht");
   else if (W.eigenschaften_steigern_erlaubt())
      handlebox_steigern_4->set_label("Eigenschaftsanstieg möglich");
   else 
      handlebox_steigern_4->set_label(grad_GFP);

  handlebox_steigern_1->set_label(W.Spezies()->Name()+" "+W.Typ1()->Short()
      + "," + W.Typ2()->Short() + " Grad "+itos(W.Grad()));
#endif
  LabelSpin_silber->set_value(W.Silber());
  LabelSpin_kupfer->set_value(W.Kupfer());
  LabelSpin_gold->set_value(W.Gold());

  LabelSpin_aep->set_value(W.AEP());
  LabelSpin_kep->set_value(W.KEP());
  LabelSpin_zep->set_value(W.ZEP());
}

void table_steigern::refresh()
{ ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__);
  if (hauptfenster->get_current_page()!=midgard_CG::PAGE_STEIGERN) return;

  zeige_werte();
//  steigern_mit_EP_bool=true;

  refresh_faehigkeiten();
     clist_ruestung->set_sensitive(false);
     button_ruestung_1->set_active(false);
     button_ruestung_2->set_active(false);

  spinbutton_eigenschaften_grad_anstieg->hide();  
  // welche buttons sind möglich
  load_for_page(notebook_lernen->get_current_page());
 togglebutton_praxispunkte->set_active(false);
}

void table_steigern::init(midgard_CG *h)
{
  hauptfenster=h;
  hauptfenster->getChar().signal_anderer_abenteurer().connect(SigC::slot(*this,&table_steigern::refresh));
  hauptfenster->getChar().proxies.undo_changed.connect(SigC::slot(*this,&table_steigern::refresh));
//  hauptfenster->getChar().proxies.wizard.signal_changed().connect(SigC::slot(*this,&table_steigern::wizard_changed));
//  h->signal_any_wizard_change().connect(SigC::slot(*this,&table_steigern::wizard_changed));
}

void table_steigern::on_notebook_lernen_switch_page(GtkNotebookPage *page,guint pagenr)
{
//  if(hauptfenster /*&& !hauptfenster->in_dtor*/) load_for_page(pagenr);
   refresh();
}


void table_steigern::load_for_page(guint pagenr)
{ // Sensitive & Show
  if(pagenr==PAGE_ZAUBER) 
   { frame_zauber_zusatz->show();
     const Abenteurer &W=hauptfenster->getAben();
     button_wie_tun->set_index_sensitive(Button_Praxis,
         W.Typ1()->SpruecheMitPP() || W.Typ2()->SpruecheMitPP());
     button_wie_tun->set_index_sensitive(Button_Spruchrolle,
         MBEmlt(cH_Fertigkeit("Lesen von Zauberschrift"))->ist_gelernt(W.List_Fertigkeit()));
     button_rolle->show();
   }
  else 
   { frame_zauber_zusatz->hide();
     button_wie_tun->set_index_sensitive(Button_Praxis,true);
     button_wie_tun->set_index_sensitive(Button_Spruchrolle,false);
     button_rolle->hide();
   }
}

std::string Steigerntyp(const Grundwerte &W)
{  if (W.wie_steigern==Grundwerte::ws_Praxispunkte) 
   { if (W.wie_steigern_variante==Grundwerte::wsv_NurPraxispunkte) 
       return "nur durch Praxis";
     else return "durch Praxis+EP";
   }
   if (W.wie_steigern==Grundwerte::ws_Spruchrolle) 
   { if (W.wie_steigern_variante==Grundwerte::wsv_SpruchrolleAlways) 
       return "durch Spruchrolle (ohne EW)";
     else return "Spruchrolle (MAGuS würfelt EW)";
   }
   if (W.wie_steigern==Grundwerte::ws_Selbststudium) 
      return "im Selbststudium";
   if (W.wie_steigern==Grundwerte::ws_Unterweisung && !W.fpanteil) 
      return "ohne Kosten";
   if (W.wie_steigern==Grundwerte::ws_Unterweisung) 
      return "mit Lehrmeister";
   return "?";
}

void table_steigern::zeige_werte()
{  ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__);
   clean_up();
   const Abenteurer &W=hauptfenster->getAben();

   refresh_gesteigert();
   refresh_werte();

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
  if (!W.Typ2()->Name(W.Geschlecht()).empty())
      steigern_typ->set_text(W.Typ1()->Name(W.Geschlecht())
            +"/"+W.Typ2()->Name(W.Geschlecht()));
  else
     steigern_typ->set_text(W.Typ1()->Name(W.Geschlecht()));
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

  label_steigern_spezies->set_text(W.Spezies()->Name());
 show_label();
   Abenteurer2Window();
}

table_steigern::table_steigern(GlademmData *_data) 
         : table_steigern_glade(_data),hauptfenster(),block_update()
//            steigern_mit_EP_bool(true) 
{  RuestungStore=Gtk::ListStore::create(ruestung_columns);
   clist_ruestung->set_model(RuestungStore);
   clist_ruestung->append_column("Rüstung",ruestung_columns.name);
   clist_ruestung->append_column("",ruestung_columns.abkz);
   clist_ruestung->append_column("LP\nVerlust",ruestung_columns.lp_verlust);
   clist_ruestung->append_column("min.\nStärke",ruestung_columns.min_staerke);
   clist_ruestung->append_column("Gw\nVerlust",ruestung_columns.rw_verlust);
   clist_ruestung->append_column("B\nVerlust",ruestung_columns.b_verlust);
   clist_ruestung->get_selection()->signal_changed().connect(SigC::slot(*this,&table_steigern::on_ruestung_selection_changed));

// die drei Zeilen können auch noch weg
     vbox_praxispunkte->hide();
     spinbutton_pp_eingeben->hide();
 scrolledwindow_landauswahl->hide();
 // Praxispunkte editierbar machen (testweise)
   alte_fert_tree->getStore()->set_editable(Data_SimpleTree::PPa); 
   alte_waffen_tree->getStore()->set_editable(Data_SimpleTree::PPa); 
   alte_sprache_tree->getStore()->set_editable(Data_SimpleTree::PPa);
   alte_schrift_tree->getStore()->set_editable(Data_SimpleTree::PPsa); 
  flashing_gradanstieg->set(MagusImage("Anpass-trans-50.xpm"),MagusImage("Anpass-trans-50_invers.xpm"),0);
  flashing_eigenschaft->set(MagusImage("Red-Dice-trans-50.xpm"),MagusImage("Red-Dice-trans-50_invers.xpm"),0);
//  steigern_mit_EP_bool.signal_changed().connect(SigC::slot(*this,&table_steigern::Window2Abenteurer));
  
  button_was_tun->set_tooltips(&_tooltips);
  button_was_tun->add(MagusImage("Steigern-trans-32.xpm"),"Steigern");
  // Ist dieser Knopf gedrückt können die bereits gelernten Fertigkeiten (durch anklicken) gesteigert werden.
  button_was_tun->add(MagusImage("Verlernen-trans-32.xpm"),"Reduzieren");
  // Ist dieser Knopf gedrückt werden die Erfolgswerte bereits gelernter Fertigkeiten (durch anklicken) reduziert und die Fähigkeit schließlich verlernt.
  button_was_tun->add(MagusImage("PP-Eingeben-trans-32.xpm"),"PP ändern");
  // Ist dieser Knopf gedrückt können die Praxispunkte geändert werden (doppelklick in der entsprechenden Spalte)
  button_was_tun->set_style(true,true,true);

  button_wie_tun->set_tooltips(&_tooltips);
  button_wie_tun->add(MagusImage("Teacher-trans32.xpm"),"Unterweisung");
  // Steigern mit Gold und EP
  button_wie_tun->add(MagusImage("Self-Learning-32.xpm"),"Selbststudium");
  // Steigern mit EP
  button_wie_tun->add(MagusImage("Learning_by_Doing-32.xpm"),"Praxis");
  // Zum Steigern werden in erster Linie Praxispunkte verwendet. Es werden jedoch keine FP verschenkt, fehlenden FP werden durch EP aufgefüllt.
  // Es wird um eine Stufe gesteigert und wenn die PP nicht reichen mit EP aufgefüllt.
  // Es werden alle PP verwendet, um so hoch wie möglich zu steigern.
  // Mit EP auffüllen, FP verfallen lassen
  button_wie_tun->add(MagusImage("LearnRoll-trans-50.xpm"),"Spruchrolle");
  button_wie_tun->set_style(true,true,true);

  button_sonder->set_tooltips(&_tooltips);
  button_sonder->add(MagusImage("EP-Steigern-50.xpm"),"Steigern mit Gold+EP");
  // Ist dieser Knopf aktiviert, werden die Erfahrungspunkte entsprechend des eingestellten Verhältnisses reduziert. Ist dieser Knopf deaktiviert, kann beliebig gesteigert werden.
  button_sonder->add(MagusImage("Money-50.xpm"),"⅓ Goldanteil spendiert");
  button_sonder->add(MagusImage("Money-50.xpm"),"½ Goldanteil spendiert");
  button_sonder->add(MagusImage("Money-50.xpm"),"⅔ Goldanteil spendiert");
  button_sonder->add(MagusImage("NSC-Mode-32.xpm"),"ohne EP+Gold steigern");
  button_sonder->set_style(true,true);
  
  button_rolle->set_tooltips(&_tooltips);
  button_rolle->add(MagusImage("Automat-32.xpm"),"Der Erfolgswurf ist gelungen.");
  button_rolle->add(MagusImage("Green-Dice-trans-50.xpm"),"MAGuS würfelt, ob das Lernen\n"
  "von Spruchrolle erfolgreich ist.");
  button_rolle->hide();

  button_pp_variante->set_tooltips(&_tooltips);
  button_pp_variante->add(MagusImage("Learning_by_Doing-32.xpm"),"Praxispunkte mit EP auffüllen");
  button_pp_variante->add(MagusImage("Learning_by_Doing-32.xpm"),"Ausschließlich Praxispunkte verwenden\n"
      "(angebrochene Praxispunkte verfallen)");
  button_pp_variante->hide();

  button_EP->set_tooltips(&_tooltips);
  button_EP->add(MagusImage("EP-Eingabe2-50.xpm"),"EP\neingeben",SigC::slot(*this,&table_steigern::on_button_EP_eingeben));
  button_EP->add(MagusImage("EP-Eingabe2-50.xpm"),"EP\naddieren",SigC::slot(*this,&table_steigern::on_button_EP_eingeben));

  button_GFP->set_tooltips(&_tooltips);
  button_GFP->add(MagusImage("Helper-50.xpm"),"GFP\neingeben",SigC::slot(*this,&table_steigern::on_checkbutton_gfp));
  button_GFP->add(MagusImage("Helper-50.xpm"),"GFP\naddieren",SigC::slot(*this,&table_steigern::on_checkbutton_gfp));

  button_gold->set_tooltips(&_tooltips);
  button_gold->add(MagusImage("Money-50.xpm"),"Geld\neingeben",SigC::slot(*this,&table_steigern::on_button_gold_eingeben));
  button_gold->add(MagusImage("Money-50.xpm"),"Geld\naddieren",SigC::slot(*this,&table_steigern::on_button_gold_eingeben));
}

// es geht hier nur um die Steigerneigenschaften ...
void table_steigern::Abenteurer2Window()
{ ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__,block_update);
  if (block_update) return;
  const Abenteurer &A=hauptfenster->getAben();

  block_update=true;
   if (button_was_tun->get_index()!=Button_PP_eingeben)
     button_was_tun->set_index(A.reduzieren ? Button_Verlernen : Button_Steigern);

   switch (A.wie_steigern)
   { case Grundwerte::ws_Spruchrolle:
       button_wie_tun->set_index(Button_Spruchrolle);
       break;
     case Grundwerte::ws_Praxispunkte:
       button_wie_tun->set_index(Button_Praxis);
       break;
     case Grundwerte::ws_Selbststudium:
       button_wie_tun->set_index(Button_Selbststudium);
       break;
     case Grundwerte::ws_Unterweisung:
       button_wie_tun->set_index(Button_Unterweisung);
       break;
   }   
   if (A.fpanteil==0)
       button_sonder->set_index(Button_Ohne);
   else if ((A.fpanteil+A.goldanteil)<=34)
       button_sonder->set_index(Button_2Drittel);
   else if ((A.fpanteil+A.goldanteil)<=51)
       button_sonder->set_index(Button_1Halb);
   else if ((A.fpanteil+A.goldanteil)<=67)
       button_sonder->set_index(Button_1Drittel);
   else button_sonder->set_index(Button_GoldEP);
  block_update=false;
  steigern_gtk();
}

void table_steigern::Window2Abenteurer()
{ ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__,block_update);
  if (block_update) return;
  Abenteurer &A=hauptfenster->getAben();

  block_update=true;
  if (button_was_tun->get_index()!=Button_PP_eingeben)
    A.reduzieren=button_was_tun->get_index()==Button_Verlernen;

  unsigned gold_spendiert=0;
  switch (button_sonder->get_index())
  { case Button_1Drittel: gold_spendiert=33; break;
    case Button_1Halb: gold_spendiert=50; break;
    case Button_2Drittel: gold_spendiert=67; break;
  }
  switch (button_wie_tun->get_index())
  { case Button_Spruchrolle:
       A.wie_steigern=Grundwerte::ws_Spruchrolle;
       A.wie_steigern_variante=hauptfenster->getChar().proxies.werte_eingeben
         ?Grundwerte::wsv_SpruchrolleAlways
         :Grundwerte::wsv_SpruchrolleRoll;
        A.goldanteil=0;
        A.fpanteil=10;
       break;
    case Button_Praxis:
       A.wie_steigern=Grundwerte::ws_Praxispunkte;
       A.wie_steigern_variante=Grundwerte::wsv_PraxispunkteFP;
       A.goldanteil=0;
       A.fpanteil=100;
       break;
    case Button_Selbststudium:
      A.wie_steigern=Grundwerte::ws_Selbststudium;
      A.goldanteil=0;
      A.fpanteil=133;
      break;
    case Button_Unterweisung:
      Gtk::Adjustment *adj=vscale_EP_Gold->get_adjustment();
      int Av=int(adj->get_value());
      if (Av<gold_spendiert) Av=gold_spendiert;
      A.goldanteil=Av-gold_spendiert;
      A.fpanteil=100-Av;
      A.wie_steigern=Grundwerte::ws_Unterweisung;
      break;
  }   
  if (button_sonder->get_index()==Button_Ohne)
    A.goldanteil=A.fpanteil=0;
  if (button_was_tun->get_index()!=Button_PP_eingeben)
    A.reduzieren=button_was_tun->get_index()==Button_Verlernen;
  block_update=false;
  steigern_gtk();
}

bool table_steigern::pp_eingeben_click(GdkEventButton*)
{ if (!togglebutton_praxispunkte->get_active())
  { togglebutton_praxispunkte->set_active(true);
    vbox_praxispunkte->show();
  }
  return false;
}
void table_steigern::button_sonder_changed()
{ Window2Abenteurer();
}
void table_steigern::button_wie_tun_changed()
{ // wie steigern: Prax geändert: show
  //   Spruchr : show, redisplay
  Window2Abenteurer();
}
void table_steigern::button_rolle_changed()
{ Window2Abenteurer();
}
void table_steigern::button_ppvar_changed()
{ Window2Abenteurer();
}
void table_steigern::button_was_tun_changed()
{ Window2Abenteurer();
}

void table_steigern::steigern_gtk()
{ ManuProC::Trace _t(LibMagus::trace_channel,__PRETTY_FUNCTION__,block_update);
  if (block_update) return;
  const Abenteurer &A=hauptfenster->getAben();
  block_update=true;
  label_EP->set_text(itos(A.fpanteil)+"%");
  label_Gold->set_text(itos(A.goldanteil)+"%");
  int gold_add=0;
  if ((A.fpanteil+A.goldanteil)<=34) gold_add=67;
  else if ((A.fpanteil+A.goldanteil)<=51) gold_add=50;
  else if ((A.fpanteil+A.goldanteil)<=67) gold_add=33;
  ManuProC::Trace(LibMagus::trace_channel,"",A.fpanteil,A.goldanteil,gold_add);
  if (33<=A.fpanteil && A.fpanteil<=67)
  { if (A.goldanteil+gold_add>67) gold_add=67-A.goldanteil;
    Gtk::Adjustment *Adj=vscale_EP_Gold->get_adjustment();
    Adj->set_value(A.goldanteil+gold_add);
    vscale_EP_Gold->set_sensitive(true);
  }
  else vscale_EP_Gold->set_sensitive(false);
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
  std::string steigern_text=itos(A.GFP())+"GFP; "+
      itos(A.fpanteil.Value())+"%EP "+itos(A.goldanteil.Value())+"%GS";
  int EP=A.VerfuegbareFP();
  if (EP) steigern_text+=" = "+itos(EP)+"FP";
  handlebox_steigern_2->set_label(steigern_text);
  
  if (button_was_tun->get_index()!=Button_PP_eingeben)
    handlebox_steigern_3->set_label((A.reduzieren.Value()?"verlernen ":"lernen ")
      +Steigerntyp(A));
  else
    handlebox_steigern_3->set_label("Praxispunkte ändern");
#endif
  block_update=false;
}

bool table_steigern::vscale_value_changed(GdkEventButton *ev)
{ Window2Abenteurer();
  return false;
}
