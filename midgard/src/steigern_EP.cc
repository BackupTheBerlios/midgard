#include "midgard_CG.hh"
#include "Window_Erfahrungspunkte.hh"
#include <gtk--/adjustment.h>

bool steigern_bool;

gint midgard_CG::vscale_value_changed(GdkEventButton *ev)
{
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  int Av=(int)A->get_value();
//  steigern_EP_prozent = 100-Av;
  Database.GradAnstieg.set_Steigern_EP_Prozent(100-Av);
  steigern_gtk();
  return false;
}

void midgard_CG::steigern_gtk()
{
  label_EP->set_text(itos(Database.GradAnstieg.get_Steigern_EP_Prozent())+"%");
  label_Gold->set_text(itos(100-Database.GradAnstieg.get_Steigern_EP_Prozent())+"%");
  Gtk::Adjustment *A=vscale_EP_Gold->get_adjustment();
  A->set_value(100-Database.GradAnstieg.get_Steigern_EP_Prozent());
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


void midgard_CG::desteigern(unsigned int kosten)
{
  guint gold_k = (guint)(kosten 
               * ((100-Database.GradAnstieg.get_Steigern_EP_Prozent())/100.));
  guint ep_k = (guint)(kosten * (Database.GradAnstieg.get_Steigern_EP_Prozent()/100.));
  Werte.add_Gold(gold_k);
  Werte.add_AEP(ep_k);
  Geld_uebernehmen();
  EP_uebernehmen();
}

bool midgard_CG::steigern(unsigned int kosten,const cH_MidgardBasicElement* fert)
{
  if (!steigern_bool) return true;
  // genug Geld? 
  guint gold_k = (guint)(kosten * ((100-Database.GradAnstieg.get_Steigern_EP_Prozent())/100.));
  guint geld = Werte.Gold();// +Werte.Silber()/10.+Werte.Kupfer()/100.;
  if (gold_k > geld) { regnot("Zu wenig Geld um zu steigern,\n es fehlen "+itos(gold_k-geld)+" GS."); return false;}
  
  // genug EP?
  bool bkep=false,bzep=false;
  int womit;
  if(fert) womit = (*fert)->Steigern_mit_EP();
  else womit=3;
  if(womit==1 || womit==3) bkep=true;
  if(womit==2 || womit==3) bzep=true;

  guint ep_k = (guint)(kosten * (Database.GradAnstieg.get_Steigern_EP_Prozent()/100.));
  guint aep=Werte.AEP();  
  guint kep=Werte.KEP();  
  guint zep=Werte.ZEP();  

  guint ep = aep;  
  std::string sw;
  if (bkep) {ep += kep;sw  =",KEP";}
  if (bzep) {ep += zep;sw +=",ZEP";}
  if (ep_k > ep) { regnot("Zu wenig EP um zu steigern,\n es fehlen "+itos(ep_k-ep)+" Erfahrungspunkte (AEP"+sw+")."); return false;}

  // jetzt darf gesteigert werden ...
  Werte.add_Gold(-gold_k);  
  if(bkep)
   { if (ep_k<=kep) {Werte.add_KEP(-ep_k);ep_k =0 ;}
     else           {ep_k-=kep; Werte.set_KEP(0);} 
   }
  if(bzep)
   { if (ep_k<=zep) {Werte.add_ZEP(-ep_k);ep_k =0 ;}
     else           {ep_k-=zep; Werte.set_ZEP(0);} 
   }
  Werte.add_AEP(-ep_k);
  Geld_uebernehmen();
  EP_uebernehmen();
  return true;  
}
