#include "midgard_CG.hh"


bool Infobool=true;
bool Escharbool=false;
bool Rawindrabool=false;
bool KanThaiPanbool=false;
bool Nahuatlanbool=false;
bool Waelandbool=false;
bool Albabool=false;


void midgard_CG::on_checkbutton_info_fenster_toggled()
{   
  if (checkbutton_info_fenster->get_active()) Infobool=true;
  else Infobool=false;
}

void midgard_CG::on_checkbutton_Eschar_toggled()
{   
  if (checkbutton_Eschar->get_active()) Escharbool=true;
  else Escharbool=false;
  midgard_CG::regnot("");
}

void midgard_CG::on_checkbutton_Rawindra_toggled()
{   
  if (checkbutton_Rawindra->get_active()) Rawindrabool=true;
  else Rawindrabool=false;
  midgard_CG::regnot("");
}

void midgard_CG::on_checkbutton_KanThaiPan_toggled()
{   
  if (checkbutton_KanThaiPan->get_active()) KanThaiPanbool=true;
  else KanThaiPanbool=false;
  midgard_CG::fill_typauswahl();
  midgard_CG::typauswahl_button();
}

void midgard_CG::on_checkbutton_Nahuatlan_toggled()
{   
  if (checkbutton_Nahuatlan->get_active()) Nahuatlanbool=true;
  else Nahuatlanbool=false;
  midgard_CG::regnot("");
}

void midgard_CG::on_checkbutton_Waeland_toggled()
{   
  if (checkbutton_Waeland->get_active()) Waelandbool=true;
  else Waelandbool=false;
  midgard_CG::regnot("");
}

void midgard_CG::on_checkbutton_Alba_toggled()
{   
  if (checkbutton_Alba->get_active()) Albabool=true;
  else Albabool=false;
}

void midgard_CG::regnot(string sadd)
{
   string strinfo ="Region noch nicht implementiert\n";
   strinfo += "da sich noch keiner gefunden hat, die Fertigkeiten abzutipppen.\n";
   strinfo += "Freiwiliege sind immer willkommen :-). Meldet euch einfach bei mir:\n";
   strinfo += "thoma@uni-muenster.de";
   strinfo += sadd;
   manage(new WindowInfo(strinfo));
}
