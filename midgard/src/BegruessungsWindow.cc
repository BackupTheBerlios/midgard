// generated 2002/11/16 21:14:11 CET by thoma@Tiger.(none)
// using glademm V1.1.2a_cvs
//
// newer (non customized) versions of this file go to BegruessungsWindow.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "BegruessungsWindow.hh"
#include "midgard_CG.hh"

void BegruessungsWindow::on_button_eingabe_clicked()
{  
   hauptfenster->table_grundwerte->togglebutton_edit_werte->set_active(true);
   hauptfenster->table_grundwerte->entry_nameC->grab_focus();
   end();
}

void BegruessungsWindow::on_button_neu_clicked()
{  
  end();
}

void BegruessungsWindow::on_button_zufall_clicked()
{  
//   hauptfenster->notebook_main->set_page(PAGE_ZUFALL);
   hauptfenster->table_zufall->init(hauptfenster);
   hauptfenster->table_zufall->on_button_zufall_voll_clicked();
   end();
}

void BegruessungsWindow::on_button_load_clicked()
{  
  hauptfenster->xml_import_auswahl();
   end();
}

void BegruessungsWindow::on_togglebutton_never_again_toggled()
{  
  hauptfenster->MOptionen->setOber("Automatisches Öffnen des Begrüssungsfensters",togglebutton_never_again->get_active());
}

void BegruessungsWindow::end()
{
  destroy();
}

