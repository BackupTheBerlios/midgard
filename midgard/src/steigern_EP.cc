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
   if (checkbutton_EP_Geld->get_active()) 
      { steigern_bool=true;
        frame_lernen_mit->set_sensitive(true);
      }
   else 
      { steigern_bool=false;
        frame_lernen_mit->set_sensitive(false);
      }
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
  // und für die Ausrüstung
  label_golda->set_text(itos(Werte.Gold()));
  label_silbera->set_text(itos(Werte.Silber()));
  label_kupfera->set_text(itos(Werte.Kupfer()));
}


void midgard_CG::desteigern(unsigned int kosten)
{
  guint gold_k=0,ep_k=0;
  if(radiobutton_praxis->get_active())
   {
     ep_k = kosten ;
   }
  else 
   {
     gold_k = (guint)(kosten 
               * ((100-Database.GradAnstieg.get_Steigern_EP_Prozent())/100.));
     ep_k = (guint)(kosten * (Database.GradAnstieg.get_Steigern_EP_Prozent()/100.));
   }
  Werte.add_Gold(gold_k);
  Werte.add_AEP(ep_k);
  Geld_uebernehmen();
  EP_uebernehmen();
}

void midgard_CG::set_lernzeit(unsigned int kosten)
{
  if(radiobutton_unterweisung->get_active())
      Werte.addSteigertage(kosten/10);
  else if(radiobutton_selbst->get_active())
      Werte.addSteigertage(kosten/5.);
  else if(radiobutton_praxis->get_active())
      Werte.addSteigertage(kosten/500.);
}

bool midgard_CG::steigern_usp(unsigned int kosten,const cH_MidgardBasicElement* MBE,const std::string &was)
{
  if (!steigern_bool) // Steigern OHNE EP/Gold/PP
      { set_lernzeit(kosten);
        return true; 
      }

  guint gold_k=0,ep_k=0;
  if(radiobutton_unterweisung->get_active())
   {
     // genug Geld? 
     gold_k = (guint)(kosten * ((100-Database.GradAnstieg.get_Steigern_EP_Prozent())/100.));
     if (gold_k > Werte.Gold()) { regnot("Zu wenig Gold um zu steigern,\n es fehlen "+itos(gold_k-Werte.Gold())+" GS."); return false;}
   }  

  // genug EP?
  bool bkep=false,bzep=false;
  int womit;
  if(MBE) womit = (*MBE)->Steigern_mit_EP();
  else if (was=="Ausdauer") womit=3;
  else if (was=="Zaubern") womit=3;
  else if (was=="Resistenz") womit=3;
  else if (was=="Abwehr") womit=3;
  else assert(!"Fehler in steigern_EP.cc:steigern_usp");
  if(womit==1 || womit==3) bkep=true;
  if(womit==2 || womit==3) bzep=true;

  if(radiobutton_unterweisung->get_active()) 
      ep_k = (guint)(kosten * (Database.GradAnstieg.get_Steigern_EP_Prozent()/100.));
  else
      ep_k = (guint)(kosten);
  guint aep=Werte.AEP();  
  guint kep=Werte.KEP();  
  guint zep=Werte.ZEP();  
  guint pp=0;
  if     (radiobutton_praxis->get_active() && MBE)  pp=(*MBE)->Praxispunkte() ;
  else if(radiobutton_praxis->get_active() && was=="Resistenz")  pp=Werte.ResistenzPP() ;
  else if(radiobutton_praxis->get_active() && was=="Abwehr")  pp=Werte.AbwehrPP() ;
  else if(radiobutton_praxis->get_active() && was=="Zauber")  pp=Werte.ZaubernPP() ;
  else assert(!"Fehler in steigern_EP.cc");

  // Dafür sorgen, daß FP für Praxispunkte nicht verschenkt werden
  while (pp>0 && pp*40 > ep_k ) --pp;
  // Nun von den Kosten 40*pp subtrahieren
  ep_k -= pp*40;

  guint ep = aep;  
  std::string sw;
  if (bkep) {ep += kep;sw  =",KEP";}
  if (bzep) {ep += zep;sw +=",ZEP";}
  if (ep_k > ep) { regnot("Zu wenig EP um zu steigern,\n es fehlen "+itos(ep_k-ep)+" Erfahrungspunkte (AEP"+sw+")."); return false;}

  // jetzt darf gesteigert werden ...
  Werte.add_Gold(-gold_k);  
  set_lernzeit(kosten);
  if (MBE) (*MBE)->add_Praxispunkte(-pp) ;
  else if(was=="Resistenz")  Werte.addResistenzPP(-pp) ;
  else if(was=="Abwehr")  Werte.addAbwehrPP(-pp) ;
  else if(was=="Zauber")  Werte.addZaubernPP(-pp) ;
  else assert(!"Fehler in steigern_EP.cc");

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


