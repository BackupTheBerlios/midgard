#include "midgard_CG.hh"
#include "Window_lernpunkte_editieren.hh"
#include "Window_Waffe_Geld.hh"


void midgard_CG::on_lernpunkte_wuerfeln_clicked()
{
  Random random;
  lernpunkte.beruf=random.integer(1,6)+random.integer(1,6);
  lernpunkte.fertigkeiten=random.integer(1,6)+random.integer(1,6);
  lernpunkte.waffen=random.integer(1,6)+random.integer(1,6);
  if (typ.z=="j" || typ.z == "z") lernpunkte.zauber=random.integer(1,6)+random.integer(1,6);

  int age = lernpunkte.beruf + lernpunkte.fertigkeiten 
          + lernpunkte.waffen + lernpunkte.zauber;

  if (typ.z=="z" ) werte.alter = age/4+19;
  if (typ.z=="n" || typ.z=="j") werte.alter = age/4+16;
  werte.alter *= spezies_constraint.alter;
  alter->set_text(itos(werte.alter));
  
  midgard_CG::zeige_lernpunkte();
}

void midgard_CG::on_lernpunkte_editieren_clicked()
{
  manage(new Window_lernpunkte_editieren(this,lernpunkte)); 
}

void midgard_CG::setze_lernpunkte(st_lernpunkte& l)
{
 lernpunkte = l;
 midgard_CG::zeige_lernpunkte();
}

void midgard_CG::zeige_lernpunkte()
{
 lernpunkte_b->set_text(itos(lernpunkte.beruf));
 lernpunkte_f->set_text(itos(lernpunkte.fertigkeiten));
 lernpunkte_w->set_text(itos(lernpunkte.waffen));
 lernpunkte_z->set_text(itos(lernpunkte.zauber));
}

void midgard_CG::on_button_ruestung_clicked()
{   
  midgard_CG::ruestung("wuerfeln");
}

void midgard_CG::on_button_geld_waffen_clicked()
{   
  werte.gold=werte.silber=werte.kupfer=0;
  manage(new Window_Waffe_Geld::Window_Waffe_Geld(this,werte,vec_waffen));
}

void midgard_CG::waffe_besitz_uebernehmen(vector<st_waffen_besitz>& wbu)
{
 waffe_besitz = wbu;
}

