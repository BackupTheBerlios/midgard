// generated 2001/5/15 23:18:16 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/HELP/midgard/midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
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
#include "../pixmaps/Money-50.xpm"
#include <gtk--/button.h>
#include "../pixmaps/Schliessen1-50.xpm"
#include <gtk--/toolbar.h>
#include "../pixmaps/Eschar-trans-50.xpm"
#include "../pixmaps/Job-trans-50.xpm"
#include <gtk--/table.h>

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
   Gtk::Label *label336 = manage(new class Gtk::Label("midgard.berlios.de"));
   Gtk::Label *label338 = manage(new class Gtk::Label("midgard-general@lists.berlios.de"));
   Gtk::Pixmap *pixmap5 = manage(new class Gtk::Pixmap(LoadChar_trans_50_xpm));
   Gtk::Pixmap *pixmap6 = manage(new class Gtk::Pixmap(Lang_Script_trans_50_xpm));
   Gtk::Label *label334 = manage(new class Gtk::Label("Nils Richter"));
   Gtk::Label *label327 = manage(new class Gtk::Label("Autor"));
   Gtk::Label *label331 = manage(new class Gtk::Label("Gtk und C++\n"
		"Unterst�tzung"));
   Gtk::Label *label329 = manage(new class Gtk::Label("Grafik"));
   Gtk::Label *label333 = manage(new class Gtk::Label("KanThaiPan"));
   Gtk::Label *label335 = manage(new class Gtk::Label("Download"));
   Gtk::Label *label337 = manage(new class Gtk::Label("Kontakt"));
   Gtk::HSeparator *hseparator18 = manage(new class Gtk::HSeparator());
   Gtk::Label *label339 = manage(new class Gtk::Label("MIDGARD ist Copyright 1981-2001 by Verlag f�r F&SF-Spiele, Stelzenberg"));
   Gtk::Pixmap *pixmap7 = manage(new class Gtk::Pixmap(Money_50_xpm));
   Gtk::HSeparator *hseparator19 = manage(new class Gtk::HSeparator());
   Gtk::Label *label340 = manage(new class Gtk::Label("Midgard Charaktergenerator f�r Linux"));
   versionsnummer = manage(new class Gtk::Label("Version: 0.3beta0"));
   
   Gtk::Toolbar *toolbar32 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button61 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar32->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(Schliessen1_50_xpm))->gtkobj()), 0, 0));
   Gtk::Label *label389 = manage(new class Gtk::Label("Sebastian Horstmann"));
   Gtk::Label *label390 = manage(new class Gtk::Label("Eschar"));
   Gtk::Pixmap *pixmap48 = manage(new class Gtk::Pixmap(Eschar_trans_50_xpm));
   Gtk::Label *label342 = manage(new class Gtk::Label("Hier w�rde ich gerne das offizielle Midgard Logo \n"
		"einf�gen, habe aber noch(?) keine Erlaubnis von Elsa :-("));
   Gtk::Label *label391 = manage(new class Gtk::Label("Hexenzauber\n"
		"&Druidenkraft"));
   Gtk::Label *label392 = manage(new class Gtk::Label("Joachim Jordan"));
   Gtk::Pixmap *pixmap49 = manage(new class Gtk::Pixmap(Job_trans_50_xpm));
   Gtk::Table *table49 = manage(new class Gtk::Table(16, 3, false));
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
   label339->set_alignment(0, 0.5);
   label339->set_padding(0, 0);
   pixmap7->set_alignment(0.5, 0.5);
   pixmap7->set_padding(0, 0);
   label340->set_alignment(0, 0.5);
   label340->set_padding(0, 0);
   versionsnummer->set_alignment(0, 0.5);
   versionsnummer->set_padding(0, 0);
   toolbar32->set_border_width(5);
   toolbar32->set_space_size(5);
   toolbar32->set_tooltips(true);
   label389->set_alignment(0, 0.5);
   label389->set_padding(0, 0);
   label390->set_alignment(0, 0.5);
   label390->set_padding(0, 0);
   pixmap48->set_alignment(0.5, 0.5);
   pixmap48->set_padding(0, 0);
   label342->set_alignment(0, 0.5);
   label342->set_padding(0, 0);
   label391->set_alignment(0, 0.5);
   label391->set_padding(0, 0);
   label392->set_alignment(0, 0.5);
   label392->set_padding(0, 0);
   pixmap49->set_alignment(0.5, 0.5);
   pixmap49->set_padding(0, 0);
   table49->attach(*label328, 2, 3, 4, 5, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap1, 0, 1, 4, 5, 0, 0, 0, 0);
   table49->attach(*pixmap2, 0, 1, 6, 7, 0, 0, 0, 0);
   table49->attach(*pixmap3, 0, 1, 5, 6, 0, 0, 0, 0);
   table49->attach(*label332, 2, 3, 5, 6, GTK_FILL, 0, 0, 0);
   table49->attach(*label330, 2, 3, 6, 7, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap4, 0, 1, 7, 8, 0, 0, 0, 0);
   table49->attach(*hseparator17, 0, 3, 10, 11, GTK_FILL, 0, 0, 5);
   table49->attach(*label336, 2, 3, 11, 12, GTK_FILL, 0, 0, 0);
   table49->attach(*label338, 2, 3, 12, 13, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap5, 0, 1, 11, 12, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*pixmap6, 0, 1, 12, 13, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*label334, 2, 3, 7, 8, GTK_FILL, 0, 0, 0);
   table49->attach(*label327, 1, 2, 4, 5, GTK_FILL, 0, 5, 0);
   table49->attach(*label331, 1, 2, 5, 6, GTK_FILL, 0, 5, 0);
   table49->attach(*label329, 1, 2, 6, 7, GTK_FILL, 0, 5, 0);
   table49->attach(*label333, 1, 2, 7, 8, GTK_FILL, 0, 5, 0);
   table49->attach(*label335, 1, 2, 11, 12, GTK_FILL, 0, 5, 0);
   table49->attach(*label337, 1, 2, 12, 13, GTK_FILL, 0, 5, 0);
   table49->attach(*hseparator18, 0, 3, 13, 14, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table49->attach(*label339, 1, 3, 14, 15, GTK_FILL, 0, 5, 5);
   table49->attach(*pixmap7, 0, 1, 14, 15, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*hseparator19, 0, 3, 3, 4, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table49->attach(*label340, 0, 3, 1, 2, 0, 0, 5, 5);
   table49->attach(*versionsnummer, 0, 3, 2, 3, 0, 0, 0, 0);
   table49->attach(*toolbar32, 2, 3, 15, 16, 0, 0, 0, 0);
   table49->attach(*label389, 2, 3, 8, 9, GTK_FILL, 0, 0, 0);
   table49->attach(*label390, 1, 2, 8, 9, GTK_FILL, 0, 5, 0);
   table49->attach(*pixmap48, 0, 1, 8, 9, GTK_FILL, GTK_FILL, 0, 0);
   table49->attach(*label342, 0, 3, 0, 1, GTK_FILL, 0, 5, 0);
   table49->attach(*label391, 1, 2, 9, 10, GTK_FILL, 0, 0, 0);
   table49->attach(*label392, 2, 3, 9, 10, GTK_FILL, 0, 0, 0);
   table49->attach(*pixmap49, 0, 1, 9, 10, GTK_FILL, GTK_FILL, 0, 0);
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
   label339->show();
   pixmap7->show();
   hseparator19->show();
   label340->show();
   versionsnummer->show();
   toolbar32->show();
   label389->show();
   label390->show();
   pixmap48->show();
   label342->show();
   label391->show();
   label392->show();
   pixmap49->show();
   table49->show();
   Midgard_Info->show();
   button61->clicked.connect(SigC::slot(static_cast<class Midgard_Info*>(this), &Midgard_Info::on_button_close_clicked));
}

Midgard_Info_glade::~Midgard_Info_glade()
{   
}
