
#include "config.h"
#include "BegruessungsWindow.hh"
#include "midgard_CG.hh"
#include "bool_CheckButton.hh"
extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

BegruessungsWindow::BegruessungsWindow(midgard_CG* h) 
 : hauptfenster(h) 
{
  Gtk::Image *p= manage(new class Gtk::Image(MagusImage("KillChar-32.xpm")));
  bool_CheckButton *W = Gtk::manage(new bool_CheckButton(Programmoptionen->OberCheck(Magus_Optionen::BegruessungsFenster).active,*p));
  W->set_mode(false);
  W->show_all();
  table_buttons->attach(*W, 1, 2, 6, 7, Gtk::SHRINK, Gtk::SHRINK, 0, 0);
}




void BegruessungsWindow::on_button_eingabe_clicked()
{  // ProgrammOptionen: Eingabe aktiv ...
   hauptfenster->NamenEingeben();
   end();
}

void BegruessungsWindow::on_button_neu_clicked()
{  
  end();
}

void BegruessungsWindow::on_button_zufall_clicked()
{  
//   hauptfenster->notebook_main->set_page(PAGE_ZUFALL);
#warning mit libmagus realisieren
//   hauptfenster->table_zufall->init(hauptfenster);
//   hauptfenster->table_zufall->on_button_zufall_voll_clicked();
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
  Programmoptionen->setOber("Automatisches Öffnen des Begrüssungsfensters",togglebutton_never_again->get_active());
}
*/

void BegruessungsWindow::end()
{
  delete this;
}

