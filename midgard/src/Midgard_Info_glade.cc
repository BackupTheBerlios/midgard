// generated 2001/11/26 10:07:09 CET by thoma@Tiger.
// using glademm V0.6.2b_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/Midgard_Info.cc

#include "config.h"
#include "Midgard_Info.hh"
#include <gtk--/label.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/Zauber-trans-50.xpm"
#include "../pixmaps/EditChar-trans-50.xpm"
#include "../pixmaps/Edit-2W6-trans-50.xpm"
#include "../pixmaps/KiDo-trans-50.xpm"
#include <gtk--/separator.h>
#include "../pixmaps/LoadChar-trans-50.xpm"
#include "../pixmaps/Lang_Script-trans-50.xpm"
#include <gtk--/button.h>
#include "../pixmaps/Schliessen1-50.xpm"
#include "../pixmaps/Eschar-trans-50.xpm"
#include "../pixmaps/Job-trans-50.xpm"
#include "../pixmaps/LoadZaub-trans-50.xpm"
#include "../pixmaps/SchliessenIII-50.xpm"
#include "../pixmaps/midgard_logo.xpm"
#include "../pixmaps/logo-work-3-v1.0pre_small.xpm"
#include <gtk--/table.h>
#include "../pixmaps/pinguin.xpm"
#include "../pixmaps/Money-50.xpm"

Midgard_Info_glade::Midgard_Info_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   
   
   Gtk::Window *Midgard_Info = this;
   Gtk::Label *label328 = manage(new class Gtk::Label("Malte Thoma"));
   Gtk::Pixmap *pixmap1 = manage(new class Gtk::Pixmap(Zauber_trans_50_xpm));
   Gtk::Pixmap *pixmap2 = manage(new class Gtk::Pixmap(EditChar_trans_50_xpm));
   Gtk::Pixmap *pixmap3 = manage(new class Gtk::Pixmap(Edit_2W6_trans_50_xpm));
   Gtk::Label *label332 = manage(new class Gtk::Label("Christof Petig"));
   Gtk::Label *label330 = manage(new class Gtk::Label("Alessandro Filippetti "));
   Gtk::Pixmap *pixmap4 = manage(new class Gtk::Pixmap(KiDo_trans_50_xpm));
   Gtk::HSeparator *hseparator17 = manage(new class Gtk::HSeparator());
   Gtk::Label *label336 = manage(new class Gtk::Label("http://midgard.berlios.de"));
   Gtk::Label *label338 = manage(new class Gtk::Label("midgard-general@lists.berlios.de"));
   Gtk::Pixmap *pixmap5 = manage(new class Gtk::Pixmap(LoadChar_trans_50_xpm));
   Gtk::Pixmap *pixmap6 = manage(new class Gtk::Pixmap(Lang_Script_trans_50_xpm));
   Gtk::Label *label334 = manage(new class Gtk::Label("Nils Richter"));
   Gtk::Label *label327 = manage(new class Gtk::Label("Autor"));
   Gtk::Label *label331 = manage(new class Gtk::Label("Gtk, C++ & xml\n"
		"Unterst�tzung"));
   Gtk::Label *label329 = manage(new class Gtk::Label("Grafik"));
   Gtk::Label *label333 = manage(new class Gtk::Label("KanThaiPan"));
   Gtk::Label *label335 = manage(new class Gtk::Label("Download"));
   Gtk::Label *label337 = manage(new class Gtk::Label("Kontakt"));
   Gtk::HSeparator *hseparator18 = manage(new class Gtk::HSeparator());
   Gtk::HSeparator *hseparator19 = manage(new class Gtk::HSeparator());
   Gtk::Label *label340 = manage(new class Gtk::Label("Der Midgard Charaktergenerator (MCG) f�r Linux"));
   versionsnummer = manage(new class Gtk::Label("Version: 0.3beta0"));
   toolbar_close = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   
   Gtk::Button *button_close = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar_close->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Schliessen1_50_xpm))->gtkobj()), 0, 0));
   Gtk::Label *label389 = manage(new class Gtk::Label("Sebastian Horstmann\n"
		"& Malte Thoma"));
   Gtk::Label *label390 = manage(new class Gtk::Label("Eschar"));
   Gtk::Pixmap *pixmap48 = manage(new class Gtk::Pixmap(Eschar_trans_50_xpm));
   Gtk::Label *label392 = manage(new class Gtk::Label("Joachim Jordan"));
   Gtk::Pixmap *pixmap49 = manage(new class Gtk::Pixmap(Job_trans_50_xpm));
   Gtk::Label *label400 = manage(new class Gtk::Label("http://developer.berlios.de/projects/midgard/"));
   Gtk::Pixmap *pixmap56 = manage(new class Gtk::Pixmap(LoadZaub_trans_50_xpm));
   Gtk::Label *label391 = manage(new class Gtk::Label("Hexenzauber\n"
		"&Druidenkraft"));
   Gtk::Label *label399 = manage(new class Gtk::Label("CVS Repository"));
   Gtk::Label *label406 = manage(new class Gtk::Label("Christof Petig"));
   Gtk::Label *label407 = manage(new class Gtk::Label("M$-Windows\n"
		"portierung"));
   Gtk::Pixmap *pixmap60 = manage(new class Gtk::Pixmap(SchliessenIII_50_xpm));
   Gtk::VSeparator *vseparator18 = manage(new class Gtk::VSeparator());
   Gtk::Pixmap *pixmap65 = manage(new class Gtk::Pixmap(midgard_logo_xpm));
   Gtk::Pixmap *pixmap61 = manage(new class Gtk::Pixmap(logo_work_3_v1_0pre_small_xpm));
   Gtk::Label *label412 = manage(new class Gtk::Label("L�nder"));
   Gtk::Label *label413 = manage(new class Gtk::Label("R�stungen"));
   Gtk::Label *label414 = manage(new class Gtk::Label("angeb. Fertigkeiten"));
   Gtk::Label *label415 = manage(new class Gtk::Label("Fertigkeiten"));
   Gtk::Label *label416 = manage(new class Gtk::Label("Zauber"));
   Gtk::Label *label417 = manage(new class Gtk::Label("Zauberwerk"));
   Gtk::Label *label419 = manage(new class Gtk::Label("Schriften"));
   Gtk::Label *label418 = manage(new class Gtk::Label("Sprachen"));
   Gtk::Label *label420 = manage(new class Gtk::Label("KiDo"));
   progressbar_laender = manage(new class Gtk::ProgressBar());
   progressbar_ruestung = manage(new class Gtk::ProgressBar());
   progressbar_ang_Fert = manage(new class Gtk::ProgressBar());
   progressbar_fertigkeiten = manage(new class Gtk::ProgressBar());
   progressbar_zauber = manage(new class Gtk::ProgressBar());
   progressbar_sprache = manage(new class Gtk::ProgressBar());
   progressbar_zauberwerk = manage(new class Gtk::ProgressBar());
   progressbar_kido = manage(new class Gtk::ProgressBar());
   progressbar_schrift = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label421 = manage(new class Gtk::Label("Grundkenntnisse"));
   progressbar_grundkenntnisse = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label422 = manage(new class Gtk::Label("Waffen"));
   progressbar_waffen = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label423 = manage(new class Gtk::Label("Verbote"));
   Gtk::Label *label424 = manage(new class Gtk::Label("Ausnahmen"));
   progressbar_pflicht = manage(new class Gtk::ProgressBar());
   progressbar_ausnahmen = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label425 = manage(new class Gtk::Label("Spezies"));
   Gtk::Label *label426 = manage(new class Gtk::Label("Charakterklassen"));
   progressbar_spezies = manage(new class Gtk::ProgressBar());
   progressbar_typen = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label427 = manage(new class Gtk::Label("Grad Anstieg"));
   progressbar_grad = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label428 = manage(new class Gtk::Label("Spezialgebiete"));
   progressbar_spezial = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label429 = manage(new class Gtk::Label("Praxispunkte"));
   progressbar_praxispunkte = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label430 = manage(new class Gtk::Label("Regionale Waffen"));
   progressbar_aliaswaffen = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label432 = manage(new class Gtk::Label("Lernschema"));
   Gtk::Label *label431 = manage(new class Gtk::Label("Berufe"));
   progressbar_lernschema = manage(new class Gtk::ProgressBar());
   progressbar_beruf = manage(new class Gtk::ProgressBar());
   
   Gtk::Label *label436 = manage(new class Gtk::Label("Ausr�stung/Preise"));
   progressbar_preise = manage(new class Gtk::ProgressBar());
   
   Gtk::Table *table77 = manage(new class Gtk::Table(22, 3, false));
   frame_datenbank = manage(new class Gtk::Frame("Laden der Datenbank"));
   
   Gtk::Pixmap *pixmap57 = manage(new class Gtk::Pixmap(pinguin_xpm));
   Gtk::Pixmap *pixmap7 = manage(new class Gtk::Pixmap(Money_50_xpm));
   Gtk::Label *label401 = manage(new class Gtk::Label("Der MCG unterliegt der GNU Public Licence"));
   Gtk::Label *label339 = manage(new class Gtk::Label("MIDGARD ist Copyright 1981-2001 by Verlag f�r F&SF-Spiele, Stelzenberg"));
   Gtk::Table *table49 = manage(new class Gtk::Table(19, 5, false));
   label328->set_alignment(0, 0.5);
   label328->set_padding(0, 0);
   pixmap1->set_alignment(0.5, 0.5);
   pixmap1->set_padding(0, 0);
   pixmap2->set_alignment(0.5, 0.5);
   pixmap2->set_padding(0, 0);
   pixmap3->set_alignment(0.5, 0.5);
   pixmap3->set_padding(0, 0);
   label332->set_alignment(0, 0.5);
   label332->set_padding(0, 0);
   label330->set_alignment(0, 0.5);
   label330->set_padding(0, 0);
   pixmap4->set_alignment(0.5, 0.5);
   pixmap4->set_padding(0, 0);
   label336->set_alignment(0, 0.5);
   label336->set_padding(0, 0);
   label338->set_alignment(0, 0.5);
   label338->set_padding(0, 0);
   pixmap5->set_alignment(0.5, 0.5);
   pixmap5->set_padding(0, 0);
   pixmap6->set_alignment(0.5, 0.5);
   pixmap6->set_padding(0, 0);
   label334->set_alignment(0, 0.5);
   label334->set_padding(0, 0);
   label327->set_usize(48, 16);
   label327->set_alignment(0, 0.5);
   label327->set_padding(0, 0);
   label331->set_alignment(0, 0.5);
   label331->set_padding(0, 0);
   label329->set_usize(48, 16);
   label329->set_alignment(0, 0.5);
   label329->set_padding(0, 0);
   label333->set_alignment(0, 0.5);
   label333->set_padding(0, 0);
   label335->set_alignment(0, 0.5);
   label335->set_padding(0, 0);
   label337->set_alignment(0, 0.5);
   label337->set_padding(0, 0);
   label340->set_alignment(0, 0.5);
   label340->set_padding(0, 0);
   versionsnummer->set_alignment(0, 0.5);
   versionsnummer->set_padding(0, 0);
   toolbar_close->set_border_width(5);
   toolbar_close->set_space_size(5);
   toolbar_close->set_tooltips(true);
   label389->set_alignment(0, 0.5);
   label389->set_padding(0, 0);
   label390->set_alignment(0, 0.5);
   label390->set_padding(0, 0);
   pixmap48->set_alignment(0.5, 0.5);
   pixmap48->set_padding(0, 0);
   label392->set_alignment(0, 0.5);
   label392->set_padding(0, 0);
   pixmap49->set_alignment(0.5, 0.5);
   pixmap49->set_padding(0, 0);
   label400->set_alignment(0, 0.5);
   label400->set_padding(0, 0);
   pixmap56->set_alignment(0.5, 0.5);
   pixmap56->set_padding(0, 0);
   label391->set_alignment(0, 0.5);
   label391->set_padding(0, 0);
   label399->set_alignment(0, 0.5);
   label399->set_padding(0, 0);
   label406->set_alignment(0, 0.5);
   label406->set_padding(0, 0);
   label407->set_alignment(0, 0.5);
   label407->set_padding(0, 0);
   pixmap60->set_alignment(0.5, 0.5);
   pixmap60->set_padding(0, 0);
   pixmap65->set_alignment(0.5, 0.5);
   pixmap65->set_padding(0, 0);
   pixmap61->set_alignment(0.5, 0.5);
   pixmap61->set_padding(0, 0);
   label412->set_alignment(0, 0.5);
   label412->set_padding(0, 0);
   label413->set_alignment(0, 0.5);
   label413->set_padding(0, 0);
   label414->set_alignment(0, 0.5);
   label414->set_padding(0, 0);
   label415->set_alignment(0, 0.5);
   label415->set_padding(0, 0);
   label416->set_alignment(0, 0.5);
   label416->set_padding(0, 0);
   label417->set_alignment(0, 0.5);
   label417->set_padding(0, 0);
   label419->set_alignment(0, 0.5);
   label419->set_padding(0, 0);
   label418->set_alignment(0, 0.5);
   label418->set_padding(0, 0);
   label420->set_alignment(0, 0.5);
   label420->set_padding(0, 0);
   label421->set_alignment(0, 0.5);
   label421->set_padding(0, 0);
   label422->set_alignment(0, 0.5);
   label422->set_padding(0, 0);
   label423->set_alignment(0, 0.5);
   label423->set_padding(0, 0);
   label424->set_alignment(0, 0.5);
   label424->set_padding(0, 0);
   label425->set_alignment(0, 0.5);
   label425->set_padding(0, 0);
   label426->set_alignment(0, 0.5);
   label426->set_padding(0, 0);
   label427->set_alignment(0, 0.5);
   label427->set_padding(0, 0);
   label428->set_alignment(0, 0.5);
   label428->set_padding(0, 0);
   label429->set_alignment(0, 0.5);
   label429->set_padding(0, 0);
   label430->set_alignment(0, 0.5);
   label430->set_padding(0, 0);
   label432->set_alignment(0, 0.5);
   label432->set_padding(0, 0);
   label431->set_alignment(0, 0.5);
   label431->set_padding(0, 0);
   label436->set_alignment(0, 0.5);
   label436->set_padding(0, 0);
   table77->attach(*label412, 0, 1, 0, 1, GTK_FILL, 0, 0, 0);
   table77->attach(*label413, 0, 1, 1, 2, GTK_FILL, 0, 0, 0);
   table77->attach(*label414, 0, 1, 4, 5, GTK_FILL, 0, 0, 0);
   table77->attach(*label415, 0, 1, 5, 6, GTK_FILL, 0, 0, 0);
   table77->attach(*label416, 0, 1, 9, 10, GTK_FILL, 0, 0, 0);
   table77->attach(*label417, 0, 1, 10, 11, GTK_FILL, 0, 0, 0);
   table77->attach(*label419, 0, 1, 13, 14, GTK_FILL, 0, 0, 0);
   table77->attach(*label418, 0, 1, 12, 13, GTK_FILL, 0, 0, 0);
   table77->attach(*label420, 0, 1, 11, 12, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_laender, 1, 2, 0, 1, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_ruestung, 1, 2, 1, 2, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_ang_Fert, 1, 2, 4, 5, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_fertigkeiten, 1, 2, 5, 6, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_zauber, 1, 2, 9, 10, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_sprache, 1, 2, 12, 13, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_zauberwerk, 1, 2, 10, 11, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_kido, 1, 2, 11, 12, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_schrift, 1, 2, 13, 14, GTK_FILL, 0, 0, 0);
   table77->attach(*label421, 0, 1, 6, 7, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_grundkenntnisse, 1, 2, 6, 7, GTK_FILL, 0, 0, 0);
   table77->attach(*label422, 0, 1, 7, 8, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_waffen, 1, 2, 7, 8, GTK_FILL, 0, 0, 0);
   table77->attach(*label423, 0, 1, 14, 15, GTK_FILL, 0, 0, 0);
   table77->attach(*label424, 0, 1, 15, 16, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_pflicht, 1, 2, 14, 15, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_ausnahmen, 1, 2, 15, 16, GTK_FILL, 0, 0, 0);
   table77->attach(*label425, 0, 1, 16, 17, GTK_FILL, 0, 0, 0);
   table77->attach(*label426, 0, 1, 17, 18, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_spezies, 1, 2, 16, 17, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_typen, 1, 2, 17, 18, GTK_FILL, 0, 0, 0);
   table77->attach(*label427, 0, 1, 18, 19, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_grad, 1, 2, 18, 19, GTK_FILL, 0, 0, 0);
   table77->attach(*label428, 0, 1, 19, 20, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_spezial, 1, 2, 19, 20, GTK_FILL, 0, 0, 0);
   table77->attach(*label429, 0, 1, 20, 21, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_praxispunkte, 1, 2, 20, 21, GTK_FILL, 0, 0, 0);
   table77->attach(*label430, 0, 1, 8, 9, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_aliaswaffen, 1, 2, 8, 9, GTK_FILL, 0, 0, 0);
   table77->attach(*label432, 0, 1, 2, 3, GTK_FILL, 0, 0, 0);
   table77->attach(*label431, 0, 1, 3, 4, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_lernschema, 1, 2, 2, 3, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_beruf, 1, 2, 3, 4, GTK_FILL, 0, 0, 0);
   table77->attach(*label436, 0, 1, 21, 22, GTK_FILL, 0, 0, 0);
   table77->attach(*progressbar_preise, 1, 2, 21, 22, GTK_FILL, 0, 0, 0);
   frame_datenbank->set_label_align(0, 0);
   frame_datenbank->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame_datenbank->add(*table77);
   pixmap57->set_alignment(0.5, 0.5);
   pixmap57->set_padding(0, 0);
   pixmap7->set_alignment(0.5, 0.5);
   pixmap7->set_padding(0, 0);
   label401->set_alignment(0, 0.5);
   label401->set_padding(0, 0);
   label339->set_alignment(0, 0.5);
   label339->set_padding(0, 0);
   table49->attach(*label328, 2, 3, 4, 5, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap1, 0, 1, 4, 5, 0, 0, 0, 0);
   table49->attach(*pixmap2, 0, 1, 6, 7, 0, 0, 0, 0);
   table49->attach(*pixmap3, 0, 1, 5, 6, 0, 0, 0, 0);
   table49->attach(*label332, 2, 3, 5, 6, GTK_FILL, 0, 0, 0);
   table49->attach(*label330, 2, 3, 6, 7, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap4, 0, 1, 7, 8, 0, 0, 0, 0);
   table49->attach(*hseparator17, 0, 3, 11, 12, GTK_FILL, 0, 0, 5);
   table49->attach(*label336, 2, 3, 12, 13, GTK_FILL, 0, 0, 0);
   table49->attach(*label338, 2, 3, 14, 15, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap5, 0, 1, 12, 13, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*pixmap6, 0, 1, 14, 15, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*label334, 2, 3, 7, 8, GTK_FILL, 0, 0, 0);
   table49->attach(*label327, 1, 2, 4, 5, GTK_FILL, 0, 5, 0);
   table49->attach(*label331, 1, 2, 5, 6, GTK_FILL, 0, 5, 0);
   table49->attach(*label329, 1, 2, 6, 7, GTK_FILL, 0, 5, 0);
   table49->attach(*label333, 1, 2, 7, 8, GTK_FILL, 0, 5, 0);
   table49->attach(*label335, 1, 2, 12, 13, GTK_FILL, 0, 5, 0);
   table49->attach(*label337, 1, 2, 14, 15, GTK_FILL, 0, 5, 0);
   table49->attach(*hseparator18, 0, 3, 15, 16, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table49->attach(*hseparator19, 0, 3, 3, 4, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table49->attach(*label340, 0, 3, 1, 2, 0, 0, 5, 5);
   table49->attach(*versionsnummer, 0, 3, 2, 3, 0, 0, 0, 0);
   table49->attach(*toolbar_close, 2, 3, 18, 19, 0, 0, 0, 0);
   table49->attach(*label389, 2, 3, 8, 9, GTK_FILL, 0, 0, 0);
   table49->attach(*label390, 1, 2, 8, 9, GTK_FILL, 0, 5, 0);
   table49->attach(*pixmap48, 0, 1, 8, 9, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*label392, 2, 3, 9, 10, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap49, 0, 1, 9, 10, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*label400, 2, 3, 13, 14, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap56, 0, 1, 13, 14, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*label391, 1, 2, 9, 10, GTK_FILL, 0, 5, 0);
   table49->attach(*label399, 1, 2, 13, 14, GTK_FILL, 0, 5, 0);
   table49->attach(*label406, 2, 3, 10, 11, GTK_FILL, 0, 0, 0);
   table49->attach(*label407, 1, 2, 10, 11, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap60, 0, 1, 10, 11, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*vseparator18, 3, 4, 0, 18, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*pixmap65, 0, 3, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*pixmap61, 4, 5, 0, 4, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table49->attach(*frame_datenbank, 4, 5, 4, 18, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*pixmap57, 0, 1, 16, 17, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*pixmap7, 0, 1, 17, 18, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*label401, 1, 3, 16, 17, GTK_FILL, 0, 0, 0);
   table49->attach(*label339, 1, 3, 17, 18, GTK_FILL, 0, 0, 0);
   Midgard_Info->set_title("Midgard");
   Midgard_Info->add(*table49);
   label328->show();
   pixmap1->show();
   pixmap2->show();
   pixmap3->show();
   label332->show();
   label330->show();
   pixmap4->show();
   hseparator17->show();
   label336->show();
   label338->show();
   pixmap5->show();
   pixmap6->show();
   label334->show();
   label327->show();
   label331->show();
   label329->show();
   label333->show();
   label335->show();
   label337->show();
   hseparator18->show();
   hseparator19->show();
   label340->show();
   versionsnummer->show();
   toolbar_close->show();
   label389->show();
   label390->show();
   pixmap48->show();
   label392->show();
   pixmap49->show();
   label400->show();
   pixmap56->show();
   label391->show();
   label399->show();
   label406->show();
   label407->show();
   pixmap60->show();
   vseparator18->show();
   pixmap65->show();
   pixmap61->show();
   label412->show();
   label413->show();
   label414->show();
   label415->show();
   label416->show();
   label417->show();
   label419->show();
   label418->show();
   label420->show();
   progressbar_laender->show();
   progressbar_ruestung->show();
   progressbar_ang_Fert->show();
   progressbar_fertigkeiten->show();
   progressbar_zauber->show();
   progressbar_sprache->show();
   progressbar_zauberwerk->show();
   progressbar_kido->show();
   progressbar_schrift->show();
   label421->show();
   progressbar_grundkenntnisse->show();
   label422->show();
   progressbar_waffen->show();
   label423->show();
   label424->show();
   progressbar_pflicht->show();
   progressbar_ausnahmen->show();
   label425->show();
   label426->show();
   progressbar_spezies->show();
   progressbar_typen->show();
   label427->show();
   progressbar_grad->show();
   label428->show();
   progressbar_spezial->show();
   label429->show();
   progressbar_praxispunkte->show();
   label430->show();
   progressbar_aliaswaffen->show();
   label432->show();
   label431->show();
   progressbar_lernschema->show();
   progressbar_beruf->show();
   label436->show();
   progressbar_preise->show();
   table77->show();
   frame_datenbank->show();
   pixmap57->show();
   pixmap7->show();
   label401->show();
   label339->show();
   table49->show();
   Midgard_Info->show();
   button_close->clicked.connect(SigC::slot(static_cast<class Midgard_Info*>(this), &Midgard_Info::on_button_close_clicked));
}

Midgard_Info_glade::~Midgard_Info_glade()
{   
}
