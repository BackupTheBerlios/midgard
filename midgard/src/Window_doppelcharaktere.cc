// generated 2001/5/14 14:50:20 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to Window_doppelcharaktere.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_doppelcharaktere.hh"
#include "midgard_CG.hh"

void Window_doppelcharaktere::on_doppelklasse_button_nein_clicked()
{   
 destroy();
}

void Window_doppelcharaktere::on_doppelklasse_button_ja_clicked()
{   
 hauptfenster->doppelcharaktere();
 destroy();
}

Window_doppelcharaktere::Window_doppelcharaktere(midgard_CG* h)
{
 hauptfenster=h;
}
