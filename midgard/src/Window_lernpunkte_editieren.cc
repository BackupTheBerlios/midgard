// generated 2001/2/7 8:11:20 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to lernpunkte_editieren.cc_glade

// This file is for your program, I won't touch it again!

#include "Window_lernpunkte_editieren.hh"
#include "midgard_CG.hh"

void Window_lernpunkte_editieren::on_close_clicked()
{   
  st_lernpunkte l;
  l.beruf        = atoi(lernpunkte_b_ein->get_text().c_str());
  l.fertigkeiten = atoi(lernpunkte_f_ein->get_text().c_str());
  l.waffen       = atoi(lernpunkte_w_ein->get_text().c_str());
  l.zauber       = atoi(lernpunkte_z_ein->get_text().c_str());
  
  hauptfenster->setze_lernpunkte(l);
  destroy();
}

Window_lernpunkte_editieren::Window_lernpunkte_editieren(midgard_CG* h, st_lernpunkte& l)
{
  hauptfenster=h;
  lernpunkte_b_ein->set_text(itos(l.beruf));
  lernpunkte_f_ein->set_text(itos(l.fertigkeiten));
  lernpunkte_w_ein->set_text(itos(l.waffen));
  lernpunkte_z_ein->set_text(itos(l.zauber));
}
