#include "midgard_CG.hh"
#include "Window_Erfahrungspunkte.hh"
#include <gtk--/adjustment.h>

bool steigern_bool;

gint midgard_CG::vscale_value_changed(GdkEventButton *ev)
{
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  int Av=(int)A->get_value();
  steigern_EP_prozent = 100-Av;
  steigern_gtk();
  return false;
}

void midgard_CG::steigern_gtk()
{
  label_EP->set_text(itos(steigern_EP_prozent)+"%");
  label_Gold->set_text(itos(100-steigern_EP_prozent)+"%");
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  A->set_value(100-steigern_EP_prozent);
  if (steigern_bool) checkbutton_EP_Geld->set_active(true);
  else               checkbutton_EP_Geld->set_active(false);
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
  if (!steigern_bool) return true;
  // genug Geld? 
  guint gold_k = (guint)(kosten * ((100-steigern_EP_prozent)/100.));
  guint geld = Werte.Gold();// +Werte.Silber()/10.+Werte.Kupfer()/100.;
  if (gold_k > geld) { regnot("Zu wenig Geld um zu steigern,\n es fehlen "+itos(gold_k-geld)+" GS."); return false;}
  
  // genug EP?
  guint ep_k = (guint)(kosten * ((    steigern_EP_prozent)/100.));
  guint aep=Werte.AEP();  
  guint kep=Werte.KEP();  
  guint zep=Werte.ZEP();  

  guint restep = aep;  
  if (ep_k > restep) { regnot("Zu wenig EP um zu steigern,\n es fehlen "+itos(ep_k-restep)+" Erfahrungspunkte (AEP)."); return false;}

  return true;  
}

