// generated 2001/8/15 8:35:09 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to Window_Erfahrungspunkte.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_Erfahrungspunkte.hh"

#include "midgard_CG.hh"

void Window_Erfahrungspunkte::on_button_close_clicked()
{   
  spinbutton_AEP->update();
  spinbutton_KEP->update();
  spinbutton_ZEP->update();
  Werte.set_EP(spinbutton_AEP->get_value_as_int(),
               spinbutton_KEP->get_value_as_int(),
               spinbutton_ZEP->get_value_as_int());
  hauptfenster->EP_uebernehmen();
  destroy();
}

Window_Erfahrungspunkte::Window_Erfahrungspunkte(midgard_CG* h,Grundwerte& w)
: Werte(w)
{
  hauptfenster=h;
  spinbutton_AEP->set_value(Werte.AEP());
  spinbutton_KEP->set_value(Werte.KEP());
  spinbutton_ZEP->set_value(Werte.ZEP());
}

void Window_Erfahrungspunkte::on_spinbutton_AEP_activate()
{
 spinbutton_KEP->grab_focus();
}

void Window_Erfahrungspunkte::on_spinbutton_KEP_activate()
{
 spinbutton_ZEP->grab_focus();
}

void Window_Erfahrungspunkte::on_spinbutton_ZEP_activate()
{
 on_button_close_clicked();
}
