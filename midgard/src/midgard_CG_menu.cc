#include "midgard_CG.hh"

void midgard_CG::menu_init()
{
  if (menu) {menu->destroy();menu=0;}
  menu=manage(new Gtk::Menu());

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

//Regionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *regionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *regionen = manage(new class Gtk::MenuItem("Regionen")); 
  regionen->set_submenu(*regionen_menu);

  
//  Gtk::CheckMenuItem *_mi;
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {
     menu_region=manage(new Gtk::CheckMenuItem((*i)->Name()));         
     menu_region->activate.connect(SigC::bind(SigC::slot(this,&midgard_CG::on_checkbutton_Regionen_menu),menu_region,*i));
     regionen_menu->append(*menu_region);
     menu_region->set_active(false);
     menu_region->show();
   }

/* 
  menu_Eschar=manage(new Gtk::CheckMenuItem("Eschar"));
  menu_Eschar->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_Eschar_menu));
  menu_Eschar->set_active(Escharbool);

  menu_Rawindra=manage(new Gtk::CheckMenuItem("Rawindra"));
  menu_Rawindra->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_Rawindra_menu));
  menu_Rawindra->set_active(Rawindrabool);

  menu_KanThaiPan=manage(new Gtk::CheckMenuItem("KanThaiPan"));
  menu_KanThaiPan->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_KanThaiPan_menu));
  menu_KanThaiPan->set_active(KanThaiPanbool);

  menu_Nahuatlan=manage(new Gtk::CheckMenuItem("Nahuatlan"));
  menu_Nahuatlan->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_Nahuatlan_menu));
  menu_Nahuatlan->set_active(Nahuatlanbool);

  menu_Waeland=manage(new Gtk::CheckMenuItem("Waeland"));
  menu_Waeland->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_Waeland_menu));
  menu_Waeland->set_active(Waelandbool);

  menu_Alba=manage(new Gtk::CheckMenuItem("Alba"));
  menu_Alba->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_Alba_menu));
  menu_Alba->set_active(Albabool);

  menu_HD=manage(new Gtk::CheckMenuItem("Hexenzauber und Druidenkraft"));
  menu_HD->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_HD_menu));
  menu_HD->set_active(HDbool);

  menu_BR=manage(new Gtk::CheckMenuItem("Barbarenwut und Ritterehre"));
  menu_BR->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_BR_menu));
  menu_BR->set_active(BRbool);

  menu_Gildenbrief=manage(new Gtk::CheckMenuItem("Gildenbrief"));
  menu_Gildenbrief->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_Gildenbrief_menu));
  menu_Gildenbrief->set_active(Gildenbriefbool);

  menu_Kuestenstaaten=manage(new Gtk::CheckMenuItem("Kuestenstaaten"));
  menu_Kuestenstaaten->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_Kuestenstaaten_menu));
  menu_Kuestenstaaten->set_active(Kuestenstaatenbool);


  optionen_menu->append(*menu_Alba);
  optionen_menu->append(*menu_Eschar);
  optionen_menu->append(*menu_Rawindra);
  optionen_menu->append(*menu_KanThaiPan);
  optionen_menu->append(*menu_Kuestenstaaten);
  optionen_menu->append(*menu_Nahuatlan);
  optionen_menu->append(*menu_Waeland);
  optionen_menu->append(*menu_HD);
  optionen_menu->append(*menu_BR);
  optionen_menu->append(*menu_Gildenbrief);

  menu_Alba->show();
  menu_Eschar->show();
  menu_KanThaiPan->show();
//  menu_Kuestenstaaten->show();
//  menu_Nahuatlan->show();
  menu_Rawindra->show();
//  menu_Waeland->show();

  if (Originalbool) 
   { menu_HD->show();
     menu_BR->show();
     menu_Gildenbrief->show();
   }
*/
  menu->append(*regionen);
  regionen->show();


//Optionen/////////////////////////////////////////////////////////////////////
  Gtk::Menu *optionen_menu = manage(new class Gtk::Menu());
  Gtk::MenuItem *optionen = manage(new class Gtk::MenuItem("Optionen")); 
  optionen->set_submenu(*optionen_menu);
 
  menu_original=manage(new Gtk::CheckMenuItem("Originalregeln"));
  optionen_menu->append(*menu_original);
  menu_original->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_original_menu));
  menu_original->set_active(Originalbool);
  menu_original->show();

  menu_info=manage(new Gtk::CheckMenuItem("Info Fenster anzeigen"));
  optionen_menu->append(*menu_info);
  menu_info->activate.connect(SigC::slot(this,&midgard_CG::on_checkbutton_info_fenster_menu));
  menu_info->set_active(Infobool);
  menu_info->show();

  menu->append(*optionen);
  optionen->show();

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
