// generated 2001/2/27 10:54:49 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_charakter_beschreibung.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_charakter_beschreibung.hh"
#include "midgard_CG.hh"

void Window_charakter_beschreibung::on_charakter_beschreibung_uebernehmen_clicked()
{   
 string b=text_charakter_beschreibung->get_chars(0,text_charakter_beschreibung->get_length());
 hauptfenster->charakter_beschreibung_uebernehmen(b);
 destroy();
}

void Window_charakter_beschreibung::on_charakter_beschreibung_drucken_clicked()
{
 string b=text_charakter_beschreibung->get_chars(0,text_charakter_beschreibung->get_length());
 hauptfenster->charakter_beschreibung_drucken(b);
 destroy();
}


void Window_charakter_beschreibung::on_charakter_beschreibung_abbrechen_clicked()
{   
  destroy();
}

Window_charakter_beschreibung::Window_charakter_beschreibung(midgard_CG* h, string s)
{
  hauptfenster=h;
  text_charakter_beschreibung->delete_text(0,text_charakter_beschreibung->get_length());
  gint pos=0;
  text_charakter_beschreibung->insert_text(s.c_str() , s.size(), &pos);  
}
