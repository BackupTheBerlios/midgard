#include "midgard_CG.hh"
#include "Window_Erfahrungspunkte.hh"
#include <gtk--/adjustment.h>

bool steigern_bool;

gint midgard_CG::vscale_value_changed(GdkEventButton *ev)
{
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  int Av=A->get_value();
  label_EP->set_text(itos(100-Av)+"%");
  label_Gold->set_text(itos(Av)+"%");
  steigern_EP_prozent = 100-Av;
  return false;
}

void midgard_CG::on_checkbutton_EP_Geld_toggled()
{
   if (checkbutton_EP_Geld->get_active()) steigern_bool=true;
   else steigern_bool=false;
}

void midgard_CG::on_button_EP_clicked()
{
  manage(new Window_Erfahrungspunkte(this,Werte));
}
 
void midgard_CG::EP_uebernehmen()
{
  label_aep->set_text(itos(Werte.AEP()));
  label_kep->set_text(itos(Werte.KEP()));
  label_zep->set_text(itos(Werte.ZEP()));
}
                  
void midgard_CG::Geld_uebernehmen()
{
  label_gold->set_text(itos(Werte.Gold()));
  label_silber->set_text(itos(Werte.Silber()));
  label_kupfer->set_text(itos(Werte.Kupfer()));
}

bool midgard_CG::steigern(unsigned int kosten)
{
  unsigned int gold_k = kosten * ((100-steigern_EP_prozent)/100.);
  unsigned int ep_k   = kosten * ((    steigern_EP_prozent)/100.);
  unsigned int geld = Werte.Gold()+Werte.Silber()/10.+Werte.Kupfer()/100.;
  
//  if (gold_k > geld) { regnot("Zu wenig Geld um zu steigern"); return bool;}

  abort();
}

