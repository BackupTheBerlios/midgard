#include "midgard_CG.hh"
#include "Window_werte_editieren.hh"

void midgard_CG::werte_editieren()
{
manage(new Window_werte_editieren(this,werte));
}

