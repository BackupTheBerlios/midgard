
#include "config.h"
#include "table_grundwerte.hh"
#include "midgard_CG.hh"
#include <Misc/itos.h>
#include <SelectMatching.h>
#include <Misc/Trace.h>

#include<gtkmm/label.h>
#include<gtkmm/image.h>
#include<gtkmm/box.h>
#include <bool_CheckButton.hh>
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

void table_grundwerte::init(midgard_CG *h)
{
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__); 
  hauptfenster=h;
  label=0;

  Vstand.resize(5);
  Vstand[1]="Unfrei";
  Vstand[2]="Volk";  
  Vstand[3]="Mittelschicht";
  Vstand[4]="Adel";

  Vhand.resize(3);
  Vhand[0]="Rechtshänder";
  Vhand[1]="Linkshänder"; 
  Vhand[2]="Beidhändig";  

  static bool only_once=false;
  if(!only_once)
  {
   only_once=true;
    bool_CheckButton *_m=manage(new bool_CheckButton(edit_werte,hauptfenster->make_gtk_box(MagusImage("EditChar-trans-50.xpm"),"Werte\neditieren",false,false)));
   _m->set_mode(false);
   eventbox_werte_edit->add(*_m);
   eventbox_werte_edit->show_all();
   _m->signal_toggled().connect(SigC::slot(*this, &table_grundwerte::on_togglebutton_edit_werte_toggled),true);
   
   if (!h->get_window()) h->realize();
   if (h->get_window())
   {  Glib::RefPtr<Gdk::Pixbuf> pb=MagusImage("Gross_dfr4.light");
      Glib::RefPtr<Gdk::Pixmap> pm=Gdk::Pixmap::create(h->get_window(),pb->get_width(),pb->get_height(),h->get_window()->get_depth());
      Glib::RefPtr<Gdk::GC> gc=Gdk::GC::create(pm);
      pm->draw_pixbuf(gc,pb,0,0,0,0,-1,-1,Gdk::RGB_DITHER_NORMAL,0,0);
      Glib::RefPtr<Gtk::Style> st=h->grundwerte_background->get_style()->copy();
      st->set_bg_pixmap(Gtk::STATE_NORMAL,pm);
      h->grundwerte_background->set_style(st);
   }
  }
  edit_werte=false;
  edit_sensitive(false);
  zeige_werte();
}
    
void table_grundwerte::zeige_werte(bool typ2_hide)
{ 
  ManuProC::Trace _t(table_grundwerte::trace_channel,__FUNCTION__); 
   if(!hauptfenster) return;
   block_changed=true;
   midgard_check_werte100();

   spinbutton_st->set_value(hauptfenster->St());
   spinbutton_gw->set_value(hauptfenster->Gw());
   spinbutton_gs->set_value(hauptfenster->Gs());
   spinbutton_ko->set_value(hauptfenster->Ko());
   spinbutton_in->set_value(hauptfenster->In());
   spinbutton_zt->set_value(hauptfenster->Zt());
   label_sehen->set_text(itos(hauptfenster->Sehen()));
   label_hoeren->set_text(itos(hauptfenster->Hoeren()));
   label_riechen->set_text(itos(hauptfenster->Riechen()));
   label_schmecken->set_text(itos(hauptfenster->Schmecken()));
   label_tasten->set_text(itos(hauptfenster->Tasten()));
   label_sechster_sinn->set_text(itos(hauptfenster->SechsterSinn()));

   spinbutton_au->set_value(hauptfenster->Au());
   spinbutton_pa->set_value(hauptfenster->pA());
   spinbutton_sb->set_value(hauptfenster->Sb());      
   spinbutton_wk->set_value(hauptfenster->Wk());      
   spinbutton_b->set_value(hauptfenster->B());     
   spinbutton_lp->set_value(hauptfenster->LP());      
   spinbutton_ap->set_value(hauptfenster->AP());   
   abwehr_wert->set_text(itos(hauptfenster->Abwehr_wert()));
   zaubern_wert->set_text(itos(hauptfenster->Zaubern_wert()));
   kaw->set_text(itos(hauptfenster->KAW()));
   wlw->set_text(itos(hauptfenster->WLW()));
   resistenz->set_text(itos(hauptfenster->Resistenz()));
   gift_wert->set_text(itos(hauptfenster->Gift()));
   bo_au->set_text(itos(hauptfenster->bo_Au())) ;
   bo_sc->set_text(itos(hauptfenster->bo_Sc())) ;
   bo_an->set_text(itos(hauptfenster->bo_An())) ;
   bo_ab->set_text(itos(hauptfenster->bo_Ab())) ;
   bo_za->set_text(itos(hauptfenster->bo_Za())) ;
   bo_psy->set_text(itos(hauptfenster->bo_Psy(hauptfenster->getChar()->getVTyp()))) ;
   bo_phs->set_text(itos(hauptfenster->bo_Phs(hauptfenster->getChar()->getVTyp()))) ;
   bo_phk->set_text(itos(hauptfenster->bo_Phk(hauptfenster->getChar()->getVTyp()))) ;
   spinbutton_alter->set_value(hauptfenster->Alter());
   spinbutton_gfp->set_value(hauptfenster->GFP());
   spinbutton_tage->set_value(hauptfenster->Steigertage());
   spinbutton_gg->set_value(hauptfenster->GG());
   spinbutton_sg->set_value(hauptfenster->SG());
   label_gestalt->set_text(hauptfenster->Gestalt());  
   spinbutton_Cgewicht->set_value(hauptfenster->Gewicht());
   spinbutton_groesse->set_value(hauptfenster->Groesse());
   spinbutton_grad->set_value(hauptfenster->Grad());      
   entry_spezialisierung->set_text(hauptfenster->Spezialisierung());

   combo_stand->set_popdown_strings(Vstand);
   combo_stand->get_entry()->set_text(hauptfenster->Stand());
   combo_hand->set_popdown_strings(Vhand);
   combo_hand->get_entry()->set_text(hauptfenster->Hand());

   entry_herkunft->set_text(hauptfenster->Herkunft()->Name());
   entry_glaube->set_text(hauptfenster->Glaube());
   entry_nameC->set_text(hauptfenster->Name_Abenteurer());
   entry_nameS->set_text(hauptfenster->Name_Spieler());
   entry_version->set_text(hauptfenster->Version());

   entry_bezeichnung->set_text(hauptfenster->Bezeichnung());
   entry_merkmale->set_text(hauptfenster->Merkmale());

   if (hauptfenster->Geschlecht()==Enums::Frau) radiobutton_frau->set_active(true); 
   else radiobutton_mann->set_active(true); 
   
   if(typ2_hide)
    {
      if (hauptfenster->getChar()->Typ2()->Short()=="") 
         combo_typ2->hide();
      else  combo_typ2->show();
    }
   combo_spezies->get_entry()->set_text(hauptfenster->Spezies()->Name());
   combo_typ ->get_entry()->set_text(hauptfenster->getChar()->Typ1()->Name(hauptfenster->Geschlecht()));
   combo_typ2->get_entry()->set_text(hauptfenster->getChar()->Typ2()->Name(hauptfenster->Geschlecht()));
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
   if(hauptfenster->Stadt_Land()==Enums::Land)  radiobutton_land->set_active(true);
   if(hauptfenster->Stadt_Land()==Enums::Stadt)  radiobutton_stadt->set_active(true);
   fill_typauswahl();
   fill_spezies();
   combo_spezies->get_entry()->set_text(hauptfenster->Spezies()->Name());
   combo_typ ->get_entry()->set_text(hauptfenster->getChar()->Typ1()->Name(hauptfenster->Geschlecht()));
   combo_typ2->get_entry()->set_text(hauptfenster->getChar()->Typ2()->Name(hauptfenster->Geschlecht()));
   block_changed=false;
   zeige_werte();
   hauptfenster->getChar().saved();
}

#include <Misc/Trace.h>
const UniqueValue::value_t table_grundwerte::trace_channel
                  =ManuProC::Tracer::channels.get();
