#include "midgard_CG.hh"


bool Infobool=true;
bool Escharbool=false;
bool Rawindrabool=false;
bool KanThaiPanbool=false;


void midgard_CG::on_checkbutton_info_fenster_toggled()
{   
  if (checkbutton_info_fenster->get_active()) Infobool=true;
  else Infobool=false;
}

void midgard_CG::on_checkbutton_Eschar_toggled()
{   
  if (checkbutton_Eschar->get_active()) Escharbool=true;
  else Escharbool=false;
cerr<< "Noch nicht implementiert\n";
}

void midgard_CG::on_checkbutton_Rawindra_toggled()
{   
  if (checkbutton_Rawindra->get_active()) Rawindrabool=true;
  else Rawindrabool=false;
cerr<< "Noch nicht implementiert\n";
}

void midgard_CG::on_checkbutton_KanThaiPan_toggled()
{   
  if (checkbutton_KanThaiPan->get_active()) KanThaiPanbool=true;
  else KanThaiPanbool=false;
cerr<< "Noch nicht implementiert\n";
}
