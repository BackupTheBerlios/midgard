#include "midgard_CG.hh"

void midgard_CG::menu_init()
{
  Gtk::MenuItem *save = manage(new class Gtk::MenuItem("Charakter speichern"));
  menu->append(*save);
  save->activate.connect(SigC::slot(this,&midgard_CG::on_speichern_clicked));
  save->show();

  Gtk::MenuItem *close = manage(new class Gtk::MenuItem("MCG Beenden"));
  menu->append(*close);
  close->activate.connect(SigC::slot(this,&midgard_CG::on_schliessen_CG_clicked));
  close->show();

//Drucken ///////////////////////////////////////////////////////////////////
  Gtk::Menu *drucken_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *drucken = manage(new class Gtk::MenuItem("Drucken")); 
  drucken->set_submenu(*drucken_menu);

  Gtk::MenuItem *latex = manage(new class Gtk::MenuItem("Charakter drucken (LaTeX)"));
  drucken_menu->append(*latex);
  latex->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_latex_clicked),true));
  latex->show();

  Gtk::MenuItem *latex_empty = manage(new class Gtk::MenuItem("Leeres Charakterdokument drucken"));
  drucken_menu->append(*latex_empty);
  latex_empty->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_latex_clicked),false));
  latex_empty->show();

  menu->append(*drucken);
  drucken->show();

//Import/Export////////////////////////////////////////////////////////////////
  Gtk::Menu *im_ex_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *im_ex = manage(new class Gtk::MenuItem("Import/Export"));
  im_ex->set_submenu(*im_ex_menu);

  Gtk::MenuItem *xml_import = manage(new class Gtk::MenuItem("xml Import"));
  im_ex_menu->append(*xml_import);
  xml_import->activate.connect(SigC::slot(this,&midgard_CG::xml_import_auswahl));
  xml_import->show();

  Gtk::MenuItem *xml_export = manage(new class Gtk::MenuItem("xml Export"));
  im_ex_menu->append(*xml_export);
  xml_export->activate.connect(SigC::slot(this,&midgard_CG::xml_export_auswahl));
  xml_export->show();

  Gtk::MenuItem *Elsa_export = manage(new class Gtk::MenuItem("Export im Format für gedruckte Abenteuer"));
  im_ex_menu->append(*Elsa_export);
  Elsa_export->activate.connect(SigC::slot(this,&midgard_CG::spielleiter_export));
  Elsa_export->show();
  
  menu->append(*im_ex);
  im_ex->show();
///////////////////////////////////////////////////////////////////////////////

  menu->show();
}
