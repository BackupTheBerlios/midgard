// generated 2002/11/16 21:14:11 CET by thoma@Tiger.(none)
// using glademm V1.1.2a_cvs
//
// newer (non customized) versions of this file go to BegruessungsWindow.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "BegruessungsWindow.hh"
#include "midgard_CG.hh"
#include "MVC_bool_Widget.hh"
#include "../pixmaps/KillChar-32.xpm"

BegruessungsWindow::BegruessungsWindow(midgard_CG* h) 
 : hauptfenster(h) 
{
  Gtk::Pixmap *p= manage(new class Gtk::Pixmap(KillChar_32_xpm));
  MVC_bool_Widget *W = manage(new MVC_bool_Widget(hauptfenster->MOptionen->OberCheck(Midgard_Optionen::BegruessungsFenster).active,*p));
  W->set_mode(false);
  W->show_all();
  table_buttons->attach(*W, 1, 2, 6, 7, GTK_SHRINK, GTK_SHRINK, 0, 0);
}




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

/*
void BegruessungsWindow::on_togglebutton_never_again_toggled()
{  
  hauptfenster->MOptionen->setOber("Automatisches �ffnen des Begr�ssungsfensters",togglebutton_never_again->get_active());
}
*/

void BegruessungsWindow::end()
{
  destroy();
}

