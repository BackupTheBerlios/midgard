// generated 2001/6/6 10:42:36 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/HELP/midgard/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/xml_fileselection.cc

#include "config.h"
#include "xml_fileselection.hh"
#include <gtk--/button.h>

xml_fileselection_glade::xml_fileselection_glade(
) : Gtk::FileSelection("XML-Datei ausw�hlen")
{   
   
   Gtk::FileSelection *xml_fileselection = this;
   Gtk::Button *ok_button1 = manage(new class Gtk::Button("OK"));
   Gtk::Button *cancel_button1 = manage(new class Gtk::Button("Cancel"));
   xml_fileselection->set_border_width(10);
   xml_fileselection->set_title("XML-Datei ausw�hlen");
   ok_button1->show();
   cancel_button1->show();
   xml_fileselection->show();
   ok_button1->clicked.connect(SigC::slot(static_cast<class xml_fileselection*>(this), &xml_fileselection::on_ok_button1_clicked));
   cancel_button1->clicked.connect(SigC::slot(static_cast<class xml_fileselection*>(this), &xml_fileselection::on_cancel_button1_clicked));
}

xml_fileselection_glade::~xml_fileselection_glade()
{   
}
